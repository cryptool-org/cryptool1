/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

/*************************************************
 
  This class realizes a cracker/analizer for 
  texts encrypted using the monoalphabetic substitution.

  This realization is based upon the paper "A Fast
  Method for the Cryptoanalysis of Substitution
  Ciphers" by Thomas Jakobsen.


  (c) Copyright by EUROSEC GmbH Chiffriertechnik & Sicherheit


  Released:	AV, 19.10.2004

 *************************************************/

 
#include "stdafx.h"
#include "MonoSubstCracker.h" 
#include "ChrTools.h"


// Do not optimize this code
#pragma optimize( "", off )


/*****************************************************************************
	  Cracker thread (contains the main cracker functionality)
******************************************************************************/
UINT monoSubstCrackerThread(PVOID p) 
{
	///////////////////////
	// variable definitions
	MonoSubstCrackerParameters *parameters;	// parameters

	bool	finished = false;		// algorithm termination flag
	bool	end_inner_loop = false;	// inner loop termination flag

	bool	end = false;	// algorithm termination flag
	float	best_error;		// holds the value of the best (smallest) error
	float	curr_error;		// holds the current (temp) error

	char	*best_key;		// holds the currently best key
	char	*curr_key;		// holds the current key (transformed best_key)
	char	*show_key;		// used to hold decryption key for showing in the dialog
	
	float	*single_stats;	// contains frequencies of single characters ('A'->'Z')
	
	float	*std_dmatrix;	// standard distribution matrix
	float	*best_dmatrix;	// best distribution matrix
	float	*curr_dmatrix;	// current (temp) distribution matrix

	int		swap_index_1, swap_index_2;	// indexes of elements to be swapped (key transformation)
	int		freq_index_1 = 0, freq_index_2 = 0;	// variables for element swapping
	
	char	*ciphertext;	// holds the original encrypted text
	char	*temp_text;		// holds the temporarily "decrypted" text

	int		language = EN;	// default language
	int		chnum;			// number of letters in the current alphabet
	char	c;				// temp character


	//////////////////////////////////////
	// Retrieve parameters
	parameters = (MonoSubstCrackerParameters *) p;
	parameters->Dialog->setThreadFinished(false);

	/////////////////////////
	// Variable initialization
	chnum = getAlphabetSize();
	best_key	 = (char *)  malloc( (1+chnum) * sizeof(char) );
	curr_key	 = (char *)  malloc( (1+chnum) * sizeof(char) );
	show_key	 = (char *)  malloc( (1+chnum) * sizeof(char) );
	best_key[chnum] = '\0';
	curr_key[chnum] = '\0';
	show_key[chnum] = '\0';

	single_stats = (float *) malloc( chnum * sizeof(float));

	std_dmatrix  = (float *) malloc( chnum * chnum * sizeof(float));
	best_dmatrix = (float *) malloc( chnum * chnum * sizeof(float));
	curr_dmatrix = (float *) malloc( chnum * chnum * sizeof(float));
	
	ciphertext = parameters->data;
	temp_text  = (char *) malloc ((strlen(ciphertext)+1) * sizeof(char));
	temp_text[strlen(ciphertext)] = '\0';

	//////////////////////////////////////
	// Preparation:
	//  Construct an initial key guess based on 
	//  character frequencies in the cipher text.
	int ret = initializeStandardDMatrix(std_dmatrix, parameters);
	if ( ret != OK )
	{
		// free memory
		free (best_key);
		free (curr_key);
		free (show_key);
		free (single_stats);
		free (std_dmatrix);
		free (best_dmatrix);
		free (curr_dmatrix);
		free (temp_text);

		parameters->Dialog->setThreadFinished(true);
		parameters->Dialog->setThreadFailed(true);
		return 0;
	}
	createStatistics (ciphertext, single_stats, curr_dmatrix);
	createInitialKey (best_key, single_stats);

	//////////////////////////////////////
	// Create distribution matrix for the initial key
	// - decrypt the text = encrypt with the inverted key
	invertKey (best_key, curr_key);
	encryptText (curr_key, ciphertext, temp_text);
	// - new statistics for the produced text
	createStatistics (temp_text, single_stats, best_dmatrix);	

	///////////////////////////////////
	//  Calculate the error for the initial key and 
	//  store it as the currently best value
	best_error = computeError (best_dmatrix, std_dmatrix);

	////////////////////////
	// Set values in the dialog
	if (!parameters->nogui)
	{
		LoadString(AfxGetInstanceHandle(), IDS_MONO_SUBST_AUTO_LANG_DE, pc_str, STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(), IDS_MONO_SUBST_AUTO_LANG_EN, pc_str1, STR_LAENGE_STRING_TABLE);
		parameters->Dialog->setLanguageInfo (lang==EN?pc_str1:pc_str);
		parameters->Dialog->setKey (best_key);
		memcpy (curr_key, best_key, getAlphabetSize()+1); // including \0
		invertKey(curr_key, show_key);

		encryptText(show_key, ciphertext, temp_text);
		prepareText(temp_text);
		parameters->Dialog->setText (temp_text);
	}

	do
	{
		//////////////////////////////////
		// Prepare variables for this loop.
		memcpy (curr_key, best_key, getAlphabetSize()+1); // copy best_key to curr_key including \0
		memcpy (curr_dmatrix, best_dmatrix, sizeof(float)*getAlphabetSize()*getAlphabetSize()); // copy best to curr

		//////////////////////////////////
		// Inner loop is used for testing new keys
		// produced by swapping two characters in the
		// original key.
		do
		{
			// Transform the key: swap two characters.
			// Characters are choosen, which have similar 
			// frequency values in the cipher text.
			swap_index_1 = freq_index_1;
			swap_index_2 = freq_index_1 + freq_index_2;
			c = curr_key[swap_index_1];
			curr_key[swap_index_1]=curr_key[swap_index_2];
			curr_key[swap_index_2]=c;
			
			// Check whether indexes are OK. 
			// If not, either a new round has to be started
			// or the algorithm is done.
			freq_index_1++;
			if( (freq_index_1+freq_index_2) > getAlphabetSize() )
			{
				freq_index_1 = 0;
				freq_index_2++;

				if ( freq_index_2==getAlphabetSize() )
				{
					// Algorithm finished
					finished = true;
					break;
				}

				break;
			}

			/////////////////////////////
			// Transform the distribution matrix accordingly to 
			// the key changes (exchange the columns and rows)
			// and computes the resulting error for this distribution
			// matrix.
			transformDMatrix (best_dmatrix, swap_index_1, swap_index_2, curr_dmatrix);
			curr_error = computeError(curr_dmatrix, std_dmatrix);

			// If the calculated error is less than the best error until now,
			// copy current key, distribution matrix, and error value.
			// Otherwise end the inner loop and try again with a modification
			// of the best key.
			if(curr_error >= best_error)
			{
				end_inner_loop = true;
				break;
			}

			// Current values are the best.
			// Thus, copy data and start next pass.
			freq_index_1 = freq_index_2 = 0;
			best_error = curr_error;
			memcpy (best_key, curr_key, getAlphabetSize()+1); // copy curr to best including \0
			memcpy (best_dmatrix, curr_dmatrix, sizeof(float)*getAlphabetSize()*getAlphabetSize()); // copy curr to best

			// Check whether the thread has to be canceled (dialog has been closed)
			if (parameters->Dialog->getGuiFinished())
			{
				finished = true;
				break;
			}

			// Show current values
			if (!parameters->nogui)
			{
				invertKey(curr_key, show_key);
				encryptText(show_key, ciphertext, temp_text);
				prepareText(temp_text);
				parameters->Dialog->setText (temp_text);
				prepareText(curr_key);
				parameters->Dialog->setKey (curr_key);
			}
		}while (!end_inner_loop && !finished);
	}while (!finished);

	// Show result
	if (parameters->nogui)
	{
		invertKey(best_key, show_key);
		encryptText(show_key, ciphertext, temp_text);
		prepareText(temp_text);
		parameters->Dialog->setText (temp_text);
		parameters->Dialog->setKey (best_key);
		LoadString(AfxGetInstanceHandle(), IDS_MONO_SUBST_AUTO_LANG_DE, pc_str, STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(), IDS_MONO_SUBST_AUTO_LANG_EN, pc_str1, STR_LAENGE_STRING_TABLE);
		parameters->Dialog->setLanguageInfo (lang==EN?pc_str1:pc_str);
	}

	parameters->Dialog->setThreadFinished(true);

	// free memory
	free (best_key);
	free (curr_key);
	free (show_key);
	free (single_stats);
	free (std_dmatrix);
	free (best_dmatrix);
	free (curr_dmatrix);
	free (temp_text);

	return 0;
}

/*****************************************************************************
	This function is called for cracking 
	monoalphabetic substitution chiffres.
******************************************************************************/
UINT AutoAnaSubst(PVOID p) 
{
	CryptPar *par;			// parameters provided by the CrypToolApp
	int		language = EN;	// default language
	int		chnum = 26;		// number of letters in the current alphabet
	FILE	*file;			// file which contains data to be decrypted
	char	*ciphertext;	// ciphertext
	char	tempc;			// temp character
	int		count=0, newline = 0, i=0; // counters
	char	*message = NULL;
	int		characterNumber = 0;  // number of characters in the ciphertext

	CDlgOptionsAutoSubstitutionAnalysis		OptionsDialog;		// option dialog
	CDlgAutoSubstitutionAnalysis			Dialog;				// main dialog
	CDlgAutoSubstitutionAnalysisAlgorithmChoice		algChoice;	// algorithm choice dialog
	
	MonoSubstCrackerParameters	param;



	//////////////////////////
	// Show algorithm options choice
	if (algChoice.DoModal()==IDOK)
	{
		if (algChoice.m_algChoice == 2)
		{
			// Start old analysis algorithm
			AfxBeginThread (AnaSubst, ((LPVOID) p));
			return 0;
		}
	}
	else
		return 0; // cancel button pressed
	

	////////////////////////////////////
	par = (CryptPar *) p;

	///////////////////////////////////////
	// Read in data
	if( (file = fopen( par->infile, "rt" )) == NULL )
	{
		LoadString(AfxGetInstanceHandle(), IDS_MONO_SUBST_AUTO_FILE_OPEN_ERROR, pc_str, STR_LAENGE_STRING_TABLE);
		message = (char*)malloc((strlen(pc_str)+strlen(par->infile)+1)*sizeof(char));
		message[0]='\0';
		strcat(message, pc_str);
		strcat(message, par->infile);
		AfxMessageBox(message, MB_ICONINFORMATION|MB_OK);
		return 0;
	}

	// Count characters in the file and especially newlines
	while ( (tempc = fgetc(file)) != EOF)
	{
		if (tempc == '\n')
			newline++;
		count++;
	}
	ciphertext = (char *) malloc ((count+newline+1) * sizeof(char));
	rewind(file);
	count=0;
	while ( (tempc = (char) fgetc(file)) != EOF )
		ciphertext[count++] = tempc;
	ciphertext[count] = '\0';

	//////////////////////////
	// Show options dialog
	lang = LANGUAGE_UNKNOWN_ERROR;
	do
	{
		if (OptionsDialog.DoModal()!=IDOK)
		{
			// Free memory
			free (ciphertext);
			// free the file handle
			fclose(file);
			return 0;
		}

		///////////////////////
		// 
		space_in_alphabet = OptionsDialog.m_space_in_alphabet==TRUE?true:false;
		Dialog.setSpaceInAlphabet(space_in_alphabet);

		// Set the number of cipher text characters in the dialog
		// Count valid characters in input
		characterNumber = 0;
		while(--count>=0)
			if (MyIsAlpha(ciphertext[count]) || (space_in_alphabet && ciphertext[count]==0x20))
				characterNumber++;
		char tempbuffer[20];
		_itoa(characterNumber, tempbuffer, 10);
		Dialog.setCharacterNumber(tempbuffer);

		if ((lang = guessLanguage(ciphertext)) == LANGUAGE_UNKNOWN_ERROR)
		{
			LoadString(AfxGetInstanceHandle(), IDS_MONO_SUBST_AUTO_LANGREC_FAILED, pc_str, STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
		}
	} while (lang == LANGUAGE_UNKNOWN_ERROR);


	// Warn user if provided input is too short.
	if (characterNumber < 200)
	{
		LoadString(AfxGetInstanceHandle(), IDS_MONO_SUBST_AUTO_SHORT_TEXT_WARNING, pc_str, STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
	}


	// Set the number of letters in the alphabet
	chnum = getAlphabetSize();

	rewind(file);
	count=0;
	while ( (tempc = (char) fgetc(file)) != EOF )
	{
		// Replace 'SPACE' by '[' to enable pointer arithmetic later on
		if (space_in_alphabet)
		{
			if (tempc == (char)'[')
			{
				ciphertext[count++] = (char) 7; // bell
				continue;
			}
			if (tempc == 32) // SPACE
			{
				ciphertext[count++] = (char) '[';
				continue;
			}
		}

		// '\n' needs to be replaced by "\r\n" for formatted printout in the dialog later on
		if (tempc == '\n')
			ciphertext[count++] = (char) '\r';
		ciphertext[count++] = tempc;
	}
	ciphertext[count] = '\0';

	fclose(file);

	/////////////////////////////////////
	// Initialize parameter structure
	param.Dialog = &Dialog;
	param.data = ciphertext;
	param.language = lang;
	param.space_in_alphabet = space_in_alphabet;
	param.nogui = OptionsDialog.m_nogui==FALSE?false:true;

	SHOW_HOUR_GLASS

	// Start thread for text analysis
	AfxBeginThread (monoSubstCrackerThread, ((LPVOID) &param));

	Sleep(1000);
	if (!Dialog.getThreadFailed())
	{
		if (OptionsDialog.m_nogui==TRUE)
			while (!Dialog.getThreadFinished()) Sleep(1000);

		HIDE_HOUR_GLASS

		if (Dialog.DoModal() == IDOK)
		{
			// Create new CrypDoc document containing decrypted text
			char outfile[CRYPTOOL_PATH_LENGTH];
			GetTmpName(outfile,"cry",".tmp");
			if((file = fopen (outfile, "wt")) == NULL)
			{
				LoadString(AfxGetInstanceHandle(), IDS_MONO_SUBST_AUTO_FILE_OPEN_ERROR, pc_str, STR_LAENGE_STRING_TABLE);
				message = (char*)malloc((strlen(pc_str)+strlen(outfile)+1)*sizeof(char));
				message[0]='\0';
				strcat(message, pc_str);
				strcat(message, outfile);
				AfxMessageBox(message, MB_ICONINFORMATION|MB_OK);
				return 0;
			}
			fprintf(file, "%s", Dialog.getText());
			fclose(file);

			// Start manual analysis if requested and possible
			if (Dialog.getManualAnalysis())
			{ 
				if (!space_in_alphabet)
				{
					// Please note that manual analysis works on 26 character alphabets only
					char manualKey[27]; manualKey[26] = 0;
					invertKey(Dialog.getKey().GetBuffer(26), manualKey);
					ManualAnaSubst((char*)par->infile, par->OldTitle, (const char*)manualKey);
				}
				else
				{

				}
			}
			else
			{
				char *title = (char *)malloc ((strlen(par->OldTitle)+60)*sizeof(char));
				title[0] = '\0'; 
				strcat(title, par->OldTitle);
				strcat(title, " -Substitution- ");
				strcat(title, Dialog.getKey());
				theApp.ThreadOpenDocumentFileNoMRU(outfile, title, "");
				remove(outfile);
				free (title);
			}
		}
	}

	// Check whether the thread is still running
	if (!Dialog.getThreadFinished())
		Dialog.setGuiFinished(true);
	do { Sleep(500); } while (!Dialog.getThreadFinished());


	free (ciphertext);
	if(message)
		free(message);

	return 0;
}


/*************************************************
 Creates frequency statistic on the provided text
 *************************************************/
int createStatistics(char *text, float *single, float *digram)
{
		int		length = strlen(text);
		int		i, j;
		int		single_total = 0, digram_total = 0; // counters
		char	c, di; // temp characters
		int		chnum; // number of letters in the alphabet

		chnum = getAlphabetSize();

		// initialize the temp structures
		for (i=0; i<chnum; i++) 
		{
			for (j=0; j<chnum; j++)
				*(digram + chnum*i + j) = 0;
			single[i] = 0;
		}

		// check first character
		c = MyToUpper(text[0]);
		if (isInAlphabet(c))
		{
			single[MyToUpper(c)-'A']++;
			single_total++;
		}

		// go through the remaining characters and count single characters and digrams
		for (i=1; i<length; i++) 
		{
			di = c;	// last single character is begin of the new digram
			c = MyToUpper(text[i]);
			if (!isInAlphabet(c))
				continue;

			// single character
			single[c-'A']++;
			single_total++;

			// digram
			if (!isInAlphabet(di))
				continue;

			*(digram + chnum*((int)di-'A') + c-'A') += 1;
			digram_total++;
		} // end for

		for (i=0; i<chnum; i++) 
		{
			for (j=0; j<chnum; j++)
				*(digram + chnum*i + j) = (float) *(digram + chnum*i + j) / (float) digram_total;
			single[i] = (float) single[i] / (float) single_total;
		} // end for

	return 0;
}


/*************************************************
 Creates initial key based on the frequency analysis.
 *************************************************/
int createInitialKey(char *key, float *stats)
{
	int		notdone = 1;// flag
	int		i;			// index
	char	c;			// temp character
	float	f;			// temp float
	int		chnum;		// number of letters in the alphabet
	char	*freq;		// array containing letters sorted by frequencies (e.g. EN: "etasionrlchudmpfgybwvkxqjz")
	char	*key_temp;	// temp key

	chnum = getAlphabetSize();
	key_temp = (char *) malloc ((chnum+1)*sizeof(char));

	// key initialization
	for (i=0; i<chnum; i++)
		key_temp[i] = i+'A';
	key_temp[i] = '\0';

	// sort the arrays
	while (notdone)
    {
      notdone = 0;
      for (i=0; i<chnum-1; i++)
        if (stats[i] < stats[i+1])
        {
			f = stats[i];
			stats[i] = stats[i+1];
			stats[i+1] = f;
			c = key_temp[i];
			key_temp[i] = key_temp[i+1];
			key_temp[i+1] = c;
			notdone = 1;
        } // end if
    } // end while

	// create the resulting initial key
	freq = getSortedLetters();
	for (i=0; i<chnum; i++)
		key[MyToUpper(freq[i])-'A'] = key_temp[i];

	free (key_temp);

	return OK;
}


/*************************************************
 Initializes the standard distribution matrix
 depending on the assumed (known) language.
 *************************************************/
int initializeStandardDMatrix(float *stats, MonoSubstCrackerParameters *parameters)
{
	char *message = NULL;		// error message
	int   	    i, j;			// indexes
	int			stat[27][27];	// holds the statistic
	int			di_count=0;		// digram counter
	char		last, current;	// first and second letter of a digram
	int			number = 26;	// number of characters in the alphabet
	FILE*		in_file;		// file containing reference data


	// Init stat structure
	if (space_in_alphabet)
		number = 27;
	else
		number = 26;

	for (i=0; i<number; i++)
		for (j=0; j<number; j++)
			stat[i][j]=0;

	//////////////////////////////
	// Open the file
	in_file  = fopen (theApp.TextOptions.getReferenceFile(), "rt");
    if (!in_file)
	{
		parameters->Dialog->setThreadFailed(true);
		LoadString(AfxGetInstanceHandle(), IDS_MONO_SUBST_AUTO_FILE_OPEN_ERROR, pc_str, STR_LAENGE_STRING_TABLE);
		message = (char*)malloc((strlen(pc_str)+strlen(theApp.TextOptions.getReferenceFile())+1)*sizeof(char));
		message[0]='\0';
		strcat(message, pc_str);
		strcat(message, theApp.TextOptions.getReferenceFile());
		AfxMessageBox(message, MB_ICONINFORMATION|MB_OK);
		// Cannot open file containing reference data
		return FILE_OPENING_ERROR;
	}

	////////////////////////////////
	// Count digrams
	last = '\0';
	while ( (current = MyToUpper(fgetc(in_file))) != EOF)
	{
		//////////////////////////////////////
		// Spaces and German "Umlaute" have to be 
		//  counted explicitly ("ue", "ae", etc.)
		switch(current) 
		{
			case ('Ü'):
			case ('ü'):
				stat['U'-'A']['E'-'A']+=1;
				last = (char)'E';
				di_count++;
				if ( isInAlphabet(last) )
				{
					stat[last-'A']['U'-'A']+=1;
					di_count++;
				}
				break;
			case ('Ö'):
			case ('ö'):
				stat['O'-'A']['E'-'A']+=1;
				last = (char)'E';
				di_count++;
				if ( isInAlphabet(last) )
				{
					stat[last-'A']['O'-'A']+=1;
					di_count++;
				}
				break;
			case ('Ä'):	
			case ('ä'):
				stat['A'-'A']['E'-'A']+=1;
				last = (char)'E';
				di_count++;
				if ( isInAlphabet(last) )
				{
					stat[last-'A']['A'-'A']+=1;
					di_count++;
				}
				break;
			case ('ß'):
				stat['S'-'A']['S'-'A']+=1;
				last = (char)'S';
				di_count++;
				if ( isInAlphabet(last) )
				{
					stat[last-'A']['S'-'A']+=1;
					di_count++;
				}
				break;
			case (' '):
				if (space_in_alphabet)
				{
					current = '[';
					if (last>='A' && last<='Z')
					{
						stat[last-'A'][current-'A']+=1;
						di_count++;
					}
					last = current;
				}
				break;// isspace() cannot really be used since it returns a non-zero value if c is a white-space character (0x09 - 0x0D or 0x20). We need 0x20 only!
			case ('['):
				last = 0;
				break;
			default:
				if ( isInAlphabet(current) && isInAlphabet(last))
				{
					stat[last-'A'][current-'A']+=1;
					di_count++;
				}
				last = current;
		} // end switch
	} // end while

	for (i=0; i<number; i++) 
		for (j=0; j<number; j++) 
			*(stats + number*i +j) = (float)stat[i][j]/(float)di_count;

	fclose(in_file);
	// Finished
	////////////////////////////////

	return OK;
}


/*************************************************
 Computes the error
 *************************************************/
float computeError (float *matrix, float *standard)
{
	int		chnum;		// number of letters in the alphabet
	chnum = getAlphabetSize();

	float error = 0.0;
	for (int i=0; i<chnum; i++)
		for (int j=0; j<chnum; j++)
			error += (float) fabs(*(matrix + chnum*i + j) - *(standard + chnum*i + j));
	return error;
}


/*************************************************
 Creates a copy of the source matrix and swaps
 rows and columns in the copy.
 *************************************************/
int transformDMatrix (float *source, int index1, int index2, float *target)
{
	int		i;
	int		chnum;		// number of letters in the alphabet
	chnum = getAlphabetSize();

	// copy source matrix first
	memcpy (target, source, sizeof(float)*getAlphabetSize()*getAlphabetSize());

	// swap columns and rows
	for (i=0; i<chnum; i++)
	{
		*(target + chnum*index1 + i) = *(source + chnum*index2 + i);
		*(target + chnum*index2 + i) = *(source + chnum*index1 + i);
	}

	float swap1 = *(target + chnum*index1 + index1);
	float swap2 = *(target + chnum*index1 + index2);
	float swap3 = *(target + chnum*index2 + index1);
	float swap4 = *(target + chnum*index2 + index2);
	for (i=0; i<chnum; i++)
	{
		*(target + chnum*i + index1) = *(source + chnum*i + index2);
		*(target + chnum*i + index2) = *(source + chnum*i + index1);
	}
	*(target + chnum*index1 + index1) = swap1;
	*(target + chnum*index1 + index2) = swap2;
	*(target + chnum*index2 + index1) = swap3;
	*(target + chnum*index2 + index2) = swap4;

	return OK;
}


/*************************************************
 Inverts the key = makes from an encryption key a
 decryption key and vice versa.
 *************************************************/
int invertKey(char *source, char *target)
{
	int temp;
	int chnum = getAlphabetSize();// number of letters in the alphabet
    
	for (int i=0; i<chnum; i++)
	{
		temp = MyToUpper(source[i]);
		if ( isInAlphabet(temp) )
			target[temp-'A'] = i+'A';
		else
			return -1; // got a problem = the key contains a non-letter character
	} // endfor

	source[chnum] = '\0';
	target[chnum] = '\0';

	return OK;
}


/*************************************************
 Encrypts the text 
 *************************************************/
void encryptText (char *key, char *plain, char *cipher)
{
	char	temp;

	unsigned int i;
	for (i=0; i<strlen(plain); i++)
	{
		temp = plain[i];
		if (temp>='A' && temp<='Z')
			cipher[i] = MyToUpper(key[MyToUpper(temp)-'A']);
		else if (temp>='a' && temp<='z')
			cipher[i] = MyToLower(key[MyToUpper(temp)-'A']);
		else if (temp==91 && space_in_alphabet) // '['
			cipher[i] = MyToLower(key[temp-'A']);
		else
			cipher[i] = plain[i];
	}

	cipher[i] = '\0';
}


/*************************************************
 Returns the language-specific number of 
 characters in the alphabet.
 *************************************************/
int getAlphabetSize ()
{
	if (space_in_alphabet)
		return 27;
	else
		return 26;
}


/*************************************************
 Returns all letters of an alphabet sorted 
 by their frequenciew.
 *************************************************/
char *getSortedLetters ()
{
	if (!space_in_alphabet)
		switch (lang)
		{
			case EN:
				return "etasionrlchudmpfgybwvkxqjz";
			case DE:
				return "enisratdhulcgmowbfkzpvjyxq";
			default:
				return NULL;
		} // end switch
	else
		switch (lang)
		{
			case EN:
				return "[etasionrlchudmpfgybwvkxqjz";
			case DE:
				return "[enisratdhulcgmowbfkzpvjyxq";
			default:
				return NULL;
		} // end switch
}


/*************************************************
 Guess the language of the ciphertext based on the
 coincidence index (Friedman).
 Returns either DE or EN.
 *************************************************/
int guessLanguage(char *ciphertext)
{
	int			i;		// index
	char		c;		// temp character
	int			chnum;	// number of letters in the alphabet
	float		ic=0.0;	// index of coincidence
	int			count=0;


	// Initialize the temp structures
	int length = strlen(ciphertext);
	chnum = getAlphabetSize();
	float *stat = (float*) malloc (chnum * sizeof(float));

	for (i=0; i<chnum; i++)
		stat[i] = 0;

	// Go through the text and calculate freq statistic
    for (i=0; i<length; i++)
	{
		c = MyToUpper(ciphertext[i]);
		if (c>='A' && c<='Z')
		{
			stat[c-'A']++;
			count++;
		}
		else if (space_in_alphabet && isspace(c))
		{
			stat[26]++;
			count++;
		}
	}

	if (!space_in_alphabet)
	{ // use all collected frequencies
		for (i=0; i<chnum; i++)
			stat[i] /= count;
	}
	else // assume that the most frequent character is SPACE and do not use it
	{
		float max = 0.0; int index = 0;
		for (i=0; i<chnum; i++)
		{
			if (stat[i] > max)
			{
				max = stat[i];
				index = i;
			}
			stat[i] /= count-1;
		}
		//stat[index] = 0;
		for (i=index; i<chnum-1;)
			stat[i] = stat[++i];
	}

	///////////////////////////
	// Calculate index of coincidence
	for (i=0; i<26; i++) 
		ic += stat[i] * ( ((float) count) * stat[i] - 1) / (float) (count - 1);

	free (stat);

	////////////////////////////
	// Guess the language.
	// Please note that we like to
	// distinguish english and german only.
	// Other languages are not taken into
	// consideration.
	//if (ic>0.065 && ic<=0.07)
	if (ic<=0.07)
		return EN;
	//else if (ic>0.07 && ic<0.083)
	else 
		return DE;
}


/*****************************************************************************
	Mapps algorithm-specifc characters in a string, which has to be shown 
	to the user. In general, '[' is mapped to SPACE and 'BELL' to '['.
******************************************************************************/
void prepareText(char *text)
{

	unsigned int count;
	if (space_in_alphabet)
		for (count=0; count<strlen(text); count++)
		{
			// Map '[' to 'SPACE' etc.
			if (text[count] == (char) 7)
				text[count] =  '[';
			if (text[count] == 91)
				text[count] =  ' ';
		}
}


/*****************************************************************************
  Manual substitution routine.
  Extracted from AnaSubst() in cryptography.cpp
******************************************************************************/
void ManualAnaSubst(char* infile, const char* old_title, const char* key)
{
	int i;
	int Laenge;


	// Required for manual analysis dialog:
	//  set global vars defined in cryptography.cpp
	Eingabedatei = infile;
	for (i=0; i<26; i++)
	{
		MaxPermu[i]=(int*)malloc(sizeof(int));
		*MaxPermu[i] = key[i];
	}

	CDlgManualSubstAnalysis Dialogbox;
	if (Dialogbox.DoModal()==IDOK)
	{
		char outfile[128], title[128];
		GetTmpName(outfile,"cry",".txt");

		SymbolArray text(AlphaSpaceConv);
		text.Read(infile);
		Laenge=text.GetSize();

		LPTSTR string = new TCHAR[Laenge + 1];
		int len;

		for (len=i=0 ; i<Laenge; i++)
		{
			if (text[i]!=26)
			{
				if (*MaxPermu[text[i]]!=-1)
					string[len++]=(char)(*MaxPermu[text[i]]);
				else 
					string[len++]=(char)text[i]+'a';
			}
		}
		string[len]=0;

		char *Ausgabe2=string;
		// Kopieren von char *Ausgabe2 in die Datei <outfile> (mit Hilfe der Secude Funktionen)
		OctetString help;
		help.noctets=strlen(Ausgabe2);
		help.octets=Ausgabe2;
		theApp.SecudeLib.aux_OctetString2file(&help,outfile,2);
		delete string;

		ForceReformat(infile, outfile, TRUE);

		// Berechnung der (Teil-)Permutation zur Anzeige im Titel
		char schluessel[27];
		for (i=0; i<26;i++)
			schluessel[i] = '*';

		for (i=0; i<26;i++)
		{
			if (*MaxPermu[i] != -1)
				schluessel[(*MaxPermu[i])-'A'] = i+'A';
		}
		schluessel[26]='\0';

		LoadString(AfxGetInstanceHandle(),IDS_STRING_POSSIBLE_PLAINTEXT_OF,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName2(title,sizeof(title),pc_str,schluessel,old_title);
		theApp.ThreadOpenDocumentFileNoMRU(outfile, title, schluessel);
	}
	// Den allokierten Speicherplatz freigeben
	for (i=0; i<26; i++)
		free (MaxPermu[i]);
	
}


/*****************************************************************************
 Checks whether a character belongs to current alphabet.
******************************************************************************/
bool isInAlphabet(char c)
{
	c = MyToUpper(c);
	if (space_in_alphabet)
		return (c>='A' && c<='[')?true:false;
	else
		return (c>='A' && c<='Z')?true:false;
}


#pragma optimize( "", on )
