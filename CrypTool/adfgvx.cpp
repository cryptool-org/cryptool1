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

// adfgvx.cpp

#include "stdafx.h"
#include "adfgvx.h"
//library for vectors
#include <vector>
#include <sstream>
using namespace std;
// necessary to access the CrypTool alphabet
#include "CrypToolApp.h"
#include "libanalyse\NGram.h"

adfgvx::adfgvx () {
	codeMatrix[0][0] = 'A';
	codeMatrix[0][1] = 'B';
	codeMatrix[0][2] = 'C';
	codeMatrix[0][3] = 'D';
	codeMatrix[0][4] = 'E';
	codeMatrix[0][5] = 'F';
	codeMatrix[1][0] = 'G';
	codeMatrix[1][1] = 'H';
	codeMatrix[1][2] = 'I';
	codeMatrix[1][3] = 'J';
	codeMatrix[1][4] = 'K';
	codeMatrix[1][5] = 'L';
	codeMatrix[2][0] = 'M';
	codeMatrix[2][1] = 'N';
	codeMatrix[2][2] = 'O';
	codeMatrix[2][3] = 'P';
	codeMatrix[2][4] = 'Q';
	codeMatrix[2][5] = 'R';
	codeMatrix[3][0] = 'S';
	codeMatrix[3][1] = 'T';
	codeMatrix[3][2] = 'U';
	codeMatrix[3][3] = 'V';
	codeMatrix[3][4] = 'W';
	codeMatrix[3][5] = 'X';
	codeMatrix[4][0] = 'Y';
	codeMatrix[4][1] = 'Z';
	codeMatrix[4][2] = '0';
	codeMatrix[4][3] = '1';
	codeMatrix[4][4] = '2';
	codeMatrix[4][5] = '3';
	codeMatrix[5][0] = '4';
	codeMatrix[5][1] = '5';
	codeMatrix[5][2] = '6';
	codeMatrix[5][3] = '7';
	codeMatrix[5][4] = '8';
	codeMatrix[5][5] = '9';
	for (int row=0;row<6;row++)
		for(int col=0;col<6;col++)
			this->compMatrix[row*6+col][0] = codeMatrix[row][col];
	this->lastPasswordFound = "";

	this->subChars[0]=0;
	this->subChars[1]=0;
  //default: german letter frequency, 5 topmost letters only, highest frequency: E == 16%
  SetFrequencyTable("ENISR",16);
}

int adfgvx::valueOf (char ch) {
	switch (ch) {
		case 'A' : {return 0; break;}
		case 'D' : {return 1; break;}
		case 'F' : {return 2; break;}
		case 'G' : {return 3; break;}
		case 'V' : {return 4; break;}
		case 'X' : {return 5; break;}
	}
	return -1;
}

//function to analyse the bigram-frequency
void adfgvx::countBigram() {
	
	//calculate characters of ciphertext
	int chars = ciphertext.length();
	int row, col;
	

	for (row=0;row<6;row++)
		for(col=0;col<6;col++)
			countMatrix[row][col] = 0;

	//delete conten of countBigrammVector
	this->countBigrammVector.clear();
	
	permMatrixIterator = permMatrix.begin();
	char bigram[2];
	row = 0;

	//read two characters row by row and count bigrams
	for (int i=0; i<chars/2; i++) {
		if (permMatrixIterator == permMatrix.end()) {
			permMatrixIterator = permMatrix.begin();
			row++;
		}
		bigram[0] = permMatrixIterator->column[row];
		permMatrixIterator++;
		if (permMatrixIterator == permMatrix.end()) {
			permMatrixIterator = permMatrix.begin();
			row++;
		}
		bigram[1] = permMatrixIterator->column[row];
		permMatrixIterator++;
		countMatrix[valueOf(bigram[0])][valueOf(bigram[1])]++;
	}

	for (row=0;row<6;row++)
		for(col=0;col<6;col++) {
			cblistelem listelem;
			listelem.index = row*6+col;
			listelem.frequency = countMatrix[row][col] / chars * 2 * 100;
			this->countBigrammVector.push_back(listelem);
		}
}

//function to compare list elements in alphabetical order
bool alphaSort (pmlistelem l1, pmlistelem l2) {
	return l1.passCharacter < l2.passCharacter;
}
//function to compare position of list elements
bool numberSort (pmlistelem l1, pmlistelem l2) {
	return l1.position < l2.position;
}
//function to sort countBigramVector in frequency order
bool frequencySort (cblistelem l1, cblistelem l2) {
	return l1.frequency > l2.frequency;
}
//function to get a character of the permMatrix
char adfgvx::getMatrix(int row, int col) {
	return this->codeMatrix[row][col];
}
//function to set a character of the permMatrix
void adfgvx::setMatrix(int row, int col, char c) {
	this->codeMatrix[row][col]=MyToUpper(c);
}
//function to check if permMatrix is valid 
int adfgvx::checkMatrix() 
{
	bool found = false;
	int row, col;
	//initialize compare matrix, mark every character as unvisited
	for (row=0;row<6;row++)
		for(col=0;col<6;col++)
			this->compMatrix[row*6+col][1] = 'N';

	//check every character of codeMatrix
	for (row=0;row<6;row++)
		for(col=0;col<6;col++) 
		{
			found = false;
			for (int colComp=0;colComp<36;colComp++)
				if (this->compMatrix[colComp][0] == this->codeMatrix[row][col]) 
				{
					found = true;
					if (this->compMatrix[colComp][1] == 'N') this->compMatrix[colComp][1] = 'X';
					else return 2;
				}
			if (!found) return 3;
		}
	return 0;
}

//function to substitute characters with permMatrix
char* adfgvx::substitute(char input)//, char* subChar) //FIXED?
{

	//characters for the substitution
	char character[6] = {'A','D','F','G','V','X'};

	//this search could be optimized by using an additional index array
	int i,j;
	for (i=0; i<6; i++) {
		for (j=0; j<6; j++) {
			if (input == this->codeMatrix[i][j]) {
				//retarr[0] = character[i];
				//retarr[1] = character[j];
				
				this->subChars[0] = character[i];//FIXED?
				this->subChars[1] = character[j];//FIXED?
				//return retarr;
				return subChars;
			}
		}
	}

	//return null if character wasn't found
	return 0;
}
//function to resubstitute characters with permMatrix
char adfgvx::resubstitute(char c1, char c2) 
{

	int index1, index2;
	
	switch (c1) {
		case 'A' : {index1 = 0; break;}
		case 'D' : {index1 = 1; break;}
		case 'F' : {index1 = 2; break;}
		case 'G' : {index1 = 3; break;}
		case 'V' : {index1 = 4; break;}
		case 'X' : {index1 = 5; break;}
	}

	switch (c2) {
		case 'A' : {index2 = 0; break;}
		case 'D' : {index2 = 1; break;}
		case 'F' : {index2 = 2; break;}
		case 'G' : {index2 = 3; break;}
		case 'V' : {index2 = 4; break;}
		case 'X' : {index2 = 5; break;}
	}

	return this->codeMatrix[index1][index2];
}
//function to read inputfile into string plaintext
void adfgvx::readPlaintext(const char* ifile) {

	//open inputfile (plaintext)
	std::ifstream input(ifile);

	stringstream ststr;
	this->plaintext = "";
	char ch;
	while (input.get(ch))
	{
		switch (ch)
		{
			//case 'Ä': ;
			case 'ä': {ststr << "AE"; break;}
			//case 'Ö': ;
			case 'ö': { ststr << "OE"; break; }
			//case 'Ü': ;
			case 'ü': { ststr << "UE"; break; }
			case 'ß': { ststr << "SS"; break; }
			default: ststr << ch;
		}
	}
	//close inputfile (plaintext)
	this->plaintext = ststr.str().c_str();
	input.close();

	/*
	string str;
	this->plaintext = "";
	char ch, chr[2];
	chr[1] = 0;
	while (input.get(ch))
	{
		switch (ch)
		{
			case 'Ä': ;
			case 'ä': {str.append("AE"); break;}
			case 'Ö': ;
			case 'ö': {str.append("OE"); break; }
			case 'Ü': ;
			case 'ü': {str.append("UE"); break; }
			case 'ß': {str.append("SS"); break; }
			default: { chr[0] = ch; str.append(chr); }
		}
	}
	//close inputfile (plaintext)
	this->plaintext = str.c_str();
	input.close();
*/


}
//function to write string plaintext to inputfile
void adfgvx::writePlaintext(const char* ofile) {
	
	//open outputfile (ciphertext)
	std::ofstream output(ofile);
	
	for (unsigned int i = 0; i < plaintext.length(); i++)
		output.put(this->plaintext[i]);
			
	//Streams schließen
	output.close();
}


//function to read inputfile into string ciphertext
int adfgvx::readCiphertext(const char* ifile) {

	//open inputfile (plaintext)
	std::ifstream input(ifile);

	this->ciphertext = "";
	
	//count character of input file
	char ch; 
	int chars = 0;

	while (input.get(ch)) {
		//if the input is set in blocks, ignore the blanks and newLines
		if(ch!=(' ')&&ch!=10)
		{
			ch = MyToUpper(ch);
			if (ch!='A' && ch!='D' && ch!='F' && ch!='G' && ch!='V' && ch!='X') 
			return 4;
			this->ciphertext+=ch;
			chars++;
		}
	}
	//check if number of characters is even
	if (chars % 2 != 0) 
		return 5;
		
	//close inputfile (plaintext)
	input.close();

	return 0;
}

//function to write string ciphertext to inputfile
void adfgvx::writeCiphertext(const char* ofile, int blockSizeStage2, bool newLineStage2)
{
	//open outputfile (ciphertext)
	std::ofstream output(ofile);
	
	for (unsigned int i = 0; i < ciphertext.length(); i++)
	{
		output.put(ciphertext[i]);
		//old version: if ((i+1)%blockSize==0&&blockSize>0)
		//was prone to division by zero
		if (blockSizeStage2>0 && (i+1)%blockSizeStage2==0)
			if(newLineStage2)
				output.put('\n');
			else
				output.put(' ');
	}

		

	//Streams schließen
	output.close();

}

//function to do step one (substitution) of adfgvx 
void adfgvx::substitution(const char* pass) 
{	
	//initialize list and iterator 
	unsigned int i=0;

	//insert elements with characters of the password and pointers to the empty queue
	//number of passwordcharacters equals number of columns
	while (pass[i] != '\0') {	
		pmlistelem element;
		pmvector column;
		element.passCharacter = pass[i];
		element.column = column;
		this->permMatrix.push_back(element);
		i++;
	}

	this->permMatrixIterator = permMatrix.begin();

	//reading character by character from the input stream

	for (i = 0; i < plaintext.length(); i++)
	{
		//substitute characters from A to z and 0 to 9 only
		if( ( ( 'A' <= plaintext[i] ) && ( 'z' >= plaintext[i] ) ) 
			|| ( ( '0' <= plaintext[i] ) && ( '9' >= plaintext[i] ) ) )
		{
			substitute(MyToUpper(plaintext[i]));
			//only characters, that can be substituted via the matrix, are encoded
			if (subChars!=0)
			{
				//insert substituted characters into permutation matrix
				if (permMatrixIterator == permMatrix.end()) 
					permMatrixIterator = permMatrix.begin();
				permMatrixIterator->column.push_back(subChars[0]);
				permMatrixIterator++;
				if (permMatrixIterator == permMatrix.end()) 
					permMatrixIterator = permMatrix.begin();
				permMatrixIterator->column.push_back(subChars[1]);
				permMatrixIterator++;
				//store substitution for eventual separate output
				this->stage1String += subChars[0];
				this->stage1String += subChars[1];		
			}
		}
	}
}

//function to write substitution only to file for separate output
void adfgvx::writeStage1(const char* stage1, int blockSizeStage1, bool newLineStage1)
{
	//open outputfile (ciphertext)
	std::ofstream output(stage1);
	
	for (unsigned int i=0;i<this->stage1String.length();i++)
	{
		output.put(this->stage1String[i]);
		
		if (blockSizeStage1!=0&&(i+1)%blockSizeStage1==0)
			if(newLineStage1)
			{
				output.put('\n');
				//new line after square blocksize number
				/*if ((i+1)%(blockSizeStage1*blockSizeStage1)==0)
					output.put('\n');*/
			}
			else
				output.put(' ');
		
	}

	//Streams schließen
	output.close();
}

//function to undo step one (substitution) of adfgvx 
void adfgvx::resubstitution() {

	//calculate characters of ciphertext
	int chars = ciphertext.length();
	
	//initialize plaintext
	this->plaintext = "";

	permMatrixIterator = permMatrix.begin();
	char bigram[2];
	int row = 0;

	//read two characters row by row and write them resubstituted to string plaintext
	for (int i=0; i<chars/2; i++) 
	{
		if (permMatrixIterator == permMatrix.end())
		{
			permMatrixIterator = permMatrix.begin();
			row++;
		}
		bigram[0] = permMatrixIterator->column[row];
		permMatrixIterator++;

		if (permMatrixIterator == permMatrix.end())
		{
			permMatrixIterator = permMatrix.begin();
			row++;
		}
		bigram[1] = permMatrixIterator->column[row];
		permMatrixIterator++;
		
		char resub =resubstitute(bigram[0], bigram[1]);
		if (resub=='*')
		{
			this->plaintext += bigram[0];
			this->plaintext += bigram[1];
		}
		else
			this->plaintext += MyToLower(resub);
		//store substituted and repermutated text for separate output
		this->stage1String += bigram[0];
		this->stage1String += bigram[1];
	}
}

//function to do step two (permutation) of adfgvx 
void adfgvx::permutation() {

	//permutate permutation matrix in alphabetic order
	std::sort(permMatrix.begin(), permMatrix.end(), alphaSort);

	//Read column by column in new order
	permMatrixIterator = permMatrix.begin();
	for (permMatrixIterator = permMatrix.begin(); permMatrixIterator!=permMatrix.end(); permMatrixIterator++) {
		for(unsigned int i=0; i<permMatrixIterator->column.size();i++)
			this->ciphertext += permMatrixIterator->column[i];
	}
}
//function to undo step two (permutation) of adfgvx 
void adfgvx::repermutation (const char* pass) {

	//initialize list and iterator 
	int i=0;

	//calculate characters of ciphertext
	int chars = ciphertext.length(); 

	//calculate rows of permutation matrix
	int rows = chars / strlen(pass);
	
	//number of overall columns
	int cols=strlen(pass);

	//calculate number of columns, with one more character than the other rows
	int extracols = chars % cols;

	//initialize permMatrix
	permMatrix.clear();

	//insert elements with characters of the password and pointers to the empty queue
	//number of passwordcharacters equals number of columns
	while (pass[i] != '\0') 
	{	
		pmlistelem element;
		pmvector column;
		element.passCharacter = pass[i];
		//element.position = strlen(pass) - strlen(strchr(pass, pass[i]));
		element.position = i;
		element.column = column;
		permMatrix.push_back(element);
		i++;
	}

	//permutate permMatrix in alphabetic order
	std::sort(permMatrix.begin(), permMatrix.end(), alphaSort);
	
	int count = 0;

	//reading character by character from the input stream 
	//into the permMatrix
	permMatrixIterator = permMatrix.begin();

	for (permMatrixIterator = permMatrix.begin(); permMatrixIterator != permMatrix.end(); permMatrixIterator++) {
		
		//read all characters for one column
		for (i=0; i<rows; i++)
			permMatrixIterator->column.push_back(this->ciphertext[count++]);
			
		//if position indicates an extra character, read it
		if (permMatrixIterator->position < extracols)
			permMatrixIterator->column.push_back(this->ciphertext[count++]);
	}

	//permutate permMatrix in original order
	std::sort(permMatrix.begin(), permMatrix.end(), numberSort);
	//debugging only
	//CString reperm;
	//for (int i=0; i<permMatrix.size;i++)
	//	reperm.Append(permMatrix.at(i));

	//cout << reperm;
}


//main encryption function
int adfgvx::encrypt(const char* ifile, const char* ofile, const char* pass, int blockSizeStage2, bool newLineStage2, bool printStage1, int blockSizeStage1, bool newLineStage1, const char* stage1) {
	
	//craziest bug ever: if the plaintext begins with 'A' or 'D', the ciphertext initially is not empty
	this->ciphertext="";
	//check password length
	if (strlen(pass) == 0) return 1;
	
	//check if matrix has only valid charactes and if no character is missing
	int check = this->checkMatrix();
	if (check != 0) return check;

	this->readPlaintext(ifile);
	this->substitution(pass);
	if(printStage1)
	//if(blockSizeStage1>0)
		this->writeStage1(stage1, blockSizeStage1, newLineStage1);
	this->permutation();
	this->writeCiphertext(ofile, blockSizeStage2, newLineStage2);

	//no error occured
	return 0;
}


//main decryption function
int adfgvx::decrypt(const char* ifile, const char* ofile, const char* pass, int blockSizeStage2, bool newLineStage2, bool printStage1, int blockSizeStage1, bool newLineStage1, const char* stage1) {
	
	//initialize return value with zero (no error)
	int check = 0;
	
	//check password length
	if (strlen(pass) == 0) return 1;

	//check if matrix has only valid charactes and if no character is missing
	check = this->checkMatrix();
	if (check != 0) return check;
	
	//check if input has only valid characters and read input
	check = this->readCiphertext(ifile);
	if (check != 0) return check;
	
	//re-permutate permMatrix after reading characters from string ciphertext
	this->repermutation(pass);

	//re-substitute charactes in permMatrix and write to string plaintext
	this->resubstitution();
	
	if(printStage1)
		this->writeStage1(stage1, blockSizeStage1, newLineStage1);

	//write string plaintext to outfile
	this->writePlaintext(ofile);

	return check;
}

// **************** ANALYSIS FUNCTIONS ********************* //

//function to permutate the possible transposition-passwords
CString adfgvx::nextPassword(int minlength, int maxlength, CString start) {
	
	pmvector password;
	CString pwd;
	bool startSet;
	int length;

	char character[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M',
            'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	
	//differ between start is empty or not	
	//if (start.Compare("") != 0) 
	if (start.GetLength() >0)
	{
		length = start.GetLength();
		startSet = true;
		password.clear();
		for (int i=0; i < start.GetLength(); i++)
			password.push_back(start[i]);
	}
	else 
	{
		length=minlength;
		startSet = false;
	}
	
	do {
		if (startSet) {
			startSet = false;
			if (this->lastPasswordFound.Compare(start) == 0)
				next_permutation(password.begin(),password.end());
		}
		else
		{
			password.clear();
			for (int i=0; i<length; i++)
				password.push_back(character[i]);
		}
		length++;

		do {
			pwd.Delete(0,pwd.GetLength());
			for (unsigned int i=0; i<password.size(); i++)
				pwd += password[i];
			this->repermutation(pwd);
			this->countBigram();
	
		} while (!(this->goodenough(false)) && next_permutation(password.begin(),password.end()));
	
	} while ( !(this->goodenough(false)) && ((int)password.size() < maxlength) );

	if (this->goodenough(false)) {
		this->lastPasswordFound = pwd;
		return pwd;
	}
	else 
		this->lastPasswordFound = "";
		return "";
}

//function to force the use of a specific password
void adfgvx::ForcePassword (CString pwd)
{
	this->repermutation(pwd);
	this->countBigram();
	this->goodenough(true);
}

//function to evaluate a transposition-password
bool adfgvx::goodenough(bool forcePassword = false) 
{
	//float rtn = 0; 
	std::sort(this->countBigrammVector.begin(), this->countBigrammVector.end(), frequencySort);
	cblist::iterator countBigrammIterator;
	countBigrammIterator = countBigrammVector.begin();
	if (!forcePassword && countBigrammIterator->frequency < m_iHighestFrequency)
		return false;
	else
  {
    //fill the matrix with asterisks
		for (int row=0;row<6;row++)
			for(int col=0;col<6;col++)
				this->codeMatrix[row][col] = '*';

    //insert characters into the substitution matrix until the frequency table is empty
    for(int i=0;m_szFrequency[i]&&i<sizeof(m_szFrequency);i++)
    {
      this->codeMatrix [countBigrammIterator->index / 6][countBigrammIterator->index % 6] = m_szFrequency[i];
		  countBigrammIterator++;      
    }
		return true;
	}
}


//***** INPUT VALIDATION *****//

//function to validate the transposition-password
/*
	return-values:
	0:	valid password
	6:	password-length-error
	7:	redundancy-error
	4:	invalid-character-error
*/
int adfgvx::CheckPassword(int minLength, int maxLength, CString password)
{
	char pwdChar;
	int i;
	int testCounter;

	//check the password-length
	if ((minLength|maxLength)<0)
		return	6;

	//scan the password for irregular characters
	testCounter=0;
	for(i=0;i<password.GetLength();i++)
	{
		pwdChar=password.GetAt(i);
		// irregular characters are characters NOT part of the CrypTool alphabet
		if(theApp.TextOptions.getAlphabet().Find(pwdChar) == -1) {
			testCounter++;
		}
	}	
	if ((testCounter==0));	
	else
		return 4;

	//scan the password for redundant characters
	testCounter=-1;
	for (i=0;i<password.GetLength();i++)
	{	
		pwdChar=password.GetAt(i);
		if (password.Find(pwdChar,(i+1))>-1)
		{	
			testCounter=testCounter++;
		}
	}	
	if ((testCounter==-1));
	else
		return 7;

	//all tests passed
	return 0;
}

// function to remove invalid & redundant characters from the transposition-password
CString adfgvx::CleansePassword(int errorCode, CString password)
{
	char pwdChar;
	int index;
	
	//invalid characters
	if (errorCode==4)
	{
		for(int i=0;i<password.GetLength();i++)
		{
			pwdChar=password.GetAt(i);
			// invalid characters are characters NOT part of the CrypTool alphabet
			if(theApp.TextOptions.getAlphabet().Find(pwdChar) == -1) {
				password.Remove(pwdChar);
				i--;//if i is not decreased, the character following pwdChar slips through untested
			}
		}	
	}


	//redundant characters
	if (errorCode==7)
	{
		for (int i=0;i<password.GetLength();i)
		{	
			pwdChar=password.GetAt(i);
			index=password.Find(pwdChar,i+1);
			if (index>0)
				password.Delete(index);
			else
				i++;

		}	
	}
	return password;

}

//function to convert the password to a string of numbers
CString adfgvx::LettersToNumbers(CString password)
{
	CString numberedPassword="";
	int pwdLength=password.GetLength();
	vector <int> numbers(pwdLength);
	int current, next;
	
	for (current=0;current<pwdLength;current++)
		for(next=current+1;next<pwdLength;next++)
			if(password.GetAt(current)>password.GetAt(next))
				numbers.at(current)++;
			else
				numbers.at(next)++;

	if(pwdLength>0)
		numberedPassword += '-';
	for (int i=0;i<pwdLength;i++)
	{
		numberedPassword += ToString(numbers.at(i)+1);
		numberedPassword += '-';
	}
	
	return numberedPassword;
}

int adfgvx::CheckStringBox(CString input)
{
	// !=36 Zeichen? =>1
	if(input.GetLength()!=36)
		return 1;

	for (int i=0;i<input.GetLength();i++)	
	{
		char temp = input.GetAt(i);
		
		//invalid characters? =>2
		if(('A'<=temp && temp<='z') || ('0'<=temp && temp<='9'));
		else
			return 2;

		//redundant characters? =>3
		for(int j=i+1;j<input.GetLength();j++)
			if(input.GetAt(j)==temp)
				return 3;
		
		
	}
	
	//pwd ok =>0
	return 0;
}

	
void adfgvx::SetFrequencyTable(char* szFrequency, int iHighestFrequency)
{
  memset(m_szFrequency,0,sizeof(m_szFrequency));
  memcpy(m_szFrequency,szFrequency,min(sizeof(m_szFrequency),strlen(szFrequency)));
  m_iHighestFrequency = iHighestFrequency;
}