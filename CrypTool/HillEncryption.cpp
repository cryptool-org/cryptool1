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

//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Klasse HILL
//////////////////////////////////////////////////////////////////
// Klasse zur Verschluesselung / Entschluesselung mittels
// Hill-Cipher. 
// Quelle: Cryptography, Theory and Practice (Stinson),
//         Seite 14 ff, 37 ff
//
// Definitionen der Methoden der Klasse
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "HillEncryption.h"
#include "CrypToolApp.h"
#include "CrypToolTools.h"
#include <string.h>

//////////////////////////////////////////////////////////////////
// Private Funktionen
//////////////////////////////////////////////////////////////////

// Speicher fuer Matrizen anlegen
void CHillEncryption::anlegen_mat (void)
{
	enc_mat = new CSquareMatrixModN(dim, modul);
	dec_mat = new CSquareMatrixModN(dim, modul);
}

// Speicher fuer Matrizen freigeben
void CHillEncryption::freigeben_mat (void)
{
	delete enc_mat;
	enc_mat = 0;
	delete dec_mat;
	dec_mat = 0;
}

// Funktion zum Fuellen der Felder zahlen und zeichen und 
// Berechnung von modul
// also darf modul erst nach Aufruf von init_zahlen_zeichen benutzt werden.
void CHillEncryption::init_zahlen_zeichen (const char* erlaubte_zeichen)
{
	size_t hilf = strlen(erlaubte_zeichen);
	ASSERT (1 <= hilf); // ein Zeichen brauchen wir mindestens
	ASSERT (hilf <= 256); // es gibt hoechstens 256 verschiedene Zeichen

	modul = (int) hilf;

	// Felder auf "leer" initialisieren

	int i;
	for (i=0; i<256; i++)
	{
		zeichen[i] = 0; // = '\0' = Stringendezeichen
		zahlen[i] = -1; // 0 wird die interne Darstellung des ersten Zeichens
						 // daher mit -1 initialisieren
	}

	// jetzt die Felder, die gefuellt werden muessen, fuellen
	if(!m_alphabetOffset)
	{
		for (i=0; i<modul; i++)
		{
			zeichen[i] = erlaubte_zeichen[i];
			// Dieses ASSERT fuehrt zum Abbruch, falls Zeichen im String doppelt vorkommen
			ASSERT (zahlen[(unsigned char)erlaubte_zeichen[i]] == -1);
			zahlen[(unsigned char)erlaubte_zeichen[i]] = i;
		}
	}
	else
	{
		for (i=0; i<modul; i++)
		{
			zeichen[i] = erlaubte_zeichen[(i+modul-1)%modul];
			// Dieses ASSERT fuehrt zum Abbruch, falls Zeichen im String doppelt vorkommen
			ASSERT (zahlen[(unsigned char)erlaubte_zeichen[i]] == -1);
			zahlen[(unsigned char)erlaubte_zeichen[i]] = (i+1) % modul;
		}
	
	}

	// ASCII-maessig kleinste Zeichen suchen. Dies wird das Fuellzeichen.
	// wir benutzen hier unsigned Vergleiche, damit das Leerzeichen dann
	// das Fuellzeichen wird, wenn es im Alphabet vorhanden ist und keine
	// Steuerzeichen (0x00-0x1f) im Alphabet vorhanden sind.
	ASSERT(modul >= 1);
	//read from registry
	unsigned long useFirstCharFromAlph = 1;
	CString strOwnCharForPadding;

	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "Hill") == ERROR_SUCCESS)
	{
		CT_READ_REGISTRY_DEFAULT(useFirstCharFromAlph, "PaddingDefaultChr", useFirstCharFromAlph);

		unsigned long u_length = 2; 
		char cFirstCharFromAlph[3];
		cFirstCharFromAlph[1] = '\0';
		if ( strlen( zeichen ) )
			cFirstCharFromAlph[0] = zeichen[0];
		CT_READ_REGISTRY_DEFAULT(cFirstCharFromAlph,"PaddingOwnChr",cFirstCharFromAlph, u_length);
		strOwnCharForPadding = cFirstCharFromAlph;

		CT_CLOSE_REGISTRY();
	}

	CString strCharForPadding;
   if ( useFirstCharFromAlph || 0 > CString(erlaubte_zeichen).Find( strOwnCharForPadding[0] ) )
		strCharForPadding = zeichen[0];
   else
		strCharForPadding = strOwnCharForPadding;
	
	fuellzeichen = *(LPCTSTR)strCharForPadding;
}


//////////////////////////////////////////////////////////////////
// Public Funktionen
//////////////////////////////////////////////////////////////////

// Konstruktor 
// Dimension muss spaeter mittels Methode set_dim() gesetzt werden
// (Die Dimension wird standardmaessig auf 1 gesetzt.)
CHillEncryption::CHillEncryption(const char* erlaubte_zeichen) :
	enc_mat(0),
	dec_mat(0),
	plaintext(0),
	ciphertext(0)
{
		//read from registry
	m_alphabetOffset = 0;

	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "Hill") == ERROR_SUCCESS)
	{
		CT_READ_REGISTRY_DEFAULT(m_alphabetOffset, "OrdChrOffset", m_alphabetOffset);
		CT_CLOSE_REGISTRY();
	}
	init_zahlen_zeichen(erlaubte_zeichen);
	laPositionVektor = new long[modul];
	iaLinearKombination1 = new int[modul];
	iaLinearKombination2 = new int[modul];
	iaFaktoren = new int[modul];
	set_dim(1);
}

// Konstruktor mit Dimension
CHillEncryption::CHillEncryption(const char* erlaubte_zeichen, int d) :
	enc_mat(0),
	dec_mat(0),
	plaintext(0),
	ciphertext(0)
{
		//read from registry
	m_alphabetOffset = 1;

	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "Hill") == ERROR_SUCCESS)
	{
		CT_READ_REGISTRY_DEFAULT(m_alphabetOffset, "OrdChrOffset", m_alphabetOffset);
		CT_CLOSE_REGISTRY();
	}
	init_zahlen_zeichen(erlaubte_zeichen);
	laPositionVektor = new long[modul];
	iaLinearKombination1 = new int[modul];
	iaLinearKombination2 = new int[modul];
	iaFaktoren = new int[modul];
	ASSERT ( (1 <= d) && (d <= HILL_MAX_DIM_GROSS) );
	set_dim (d);
}

CHillEncryption::~CHillEncryption()
{
	freigeben_mat ();

	delete[] plaintext;
	delete[] ciphertext;
	delete[] laPositionVektor;
	delete[] iaLinearKombination1;
	delete[] iaLinearKombination2;
	delete[] iaFaktoren;
}

// Abbildung [erlaubte Zeichen] -> [0..modul-1]
int CHillEncryption::my_char_to_int (char c) const
{
	ASSERT (zahlen[(unsigned char)c] != -1);

	return zahlen[(unsigned char)c];
}

// Abbildung [0..modul-1] -> [erlaubte Zeichen]
char CHillEncryption::my_int_to_char (int i) const
{
	ASSERT ( (0 <= i) && (i <= modul-1) );
	
	return zeichen[i];
}

// Darf das Zeichen in dieser Instanz benutzt werden ?
BOOL CHillEncryption::ist_erlaubtes_zeichen (char c) const
{
	return (zahlen[(unsigned char)c] != -1);
}

// Gibt das Fuellzeichen zurueck, mit dem ein letzter Block, sofern nicht vollstaendig,
// aufgefuellt worden ist.
char CHillEncryption::get_fuellzeichen (void) const
{
	return (fuellzeichen);
}

// Funktionen zum Setzen der Dimension
void CHillEncryption::set_dim (int d)
{
	ASSERT ( (1 <= d) && (d <= HILL_MAX_DIM_GROSS) );

	dim = d;
	
	// Alle Daten ueber Matrizen und Texte loeschen
	// und neue Matrizen anlegen
	freigeben_mat ();
	anlegen_mat ();
	
	if (plaintext)
	{
		delete[] plaintext;
	}
	plaintext = 0;
	laenge_plain = 0;
	
	if (ciphertext)
	{
		delete[] ciphertext;
	}
	ciphertext = 0;
	laenge_cipher = 0;
}

// Funktionen zum Ermitteln der Dimension
int CHillEncryption::get_dim (void) const
{
	return dim;
}

// Funktionen zum Ermitteln des Moduls
int CHillEncryption::get_modul (void) const
{
	return modul;
}

// Funktion zum Ermitteln der Laenge der Texte
long CHillEncryption::get_laenge_plain (void) const
{
	return laenge_plain;
}

long CHillEncryption::get_laenge_cipher (void) const
{
	return laenge_cipher;
}

// Funktionen zum Setzen des unverschluesselten Textes
void CHillEncryption::set_plaintext (char *str)
{
	if (plaintext)
	{
		delete[] plaintext;
	}
	
	long laenge_str = strlen(str);
	
	if (laenge_str == 0)
	{
		laenge_plain = 0;
	}
	else
	{
		laenge_plain = (((laenge_str-1)/dim)+1)*dim;   // = ceil(laenge_str/dim)
	}
	
	plaintext = new int[laenge_plain];
	
	long i;
	for (i=0; i<laenge_str; i++)
	{
		plaintext[i] = my_char_to_int(str[i]);
	}
	// Auffuellen mit Fuellzeichen am Ende
	for (i=laenge_str; i<laenge_plain; i++)
	{
		plaintext[i] = my_char_to_int(get_fuellzeichen());
	}
}

// Funktionen zum Ermitteln des unverschluesselten Textes
void CHillEncryption::get_plaintext (char *str) const
{
	// hier wird kopiert, Laenge des Feldes muss sein:
	// objekt.get_laenge_plain() + 1;
	
	for (long i=0; i<laenge_plain; i++)
	{
		str[i] = my_int_to_char(plaintext[i]);
	}
	str[laenge_plain] = '\0';
}

// Funktionen zum Setzen des verschluesselten Textes
void CHillEncryption::set_ciphertext (char *str)
{
	if (ciphertext)
	{
		delete[] ciphertext;
	}
	
	long laenge_str = strlen(str);
	
	if (laenge_str == 0)
	{
		laenge_cipher = 0;
	}
	else
	{
		laenge_cipher = (((laenge_str-1)/dim)+1)*dim;   // = ceil(laenge_str/dim)
	}
	
	ciphertext = new int[laenge_cipher];
	
	long i;
	for (i=0; i<laenge_str; i++)
	{
		ciphertext[i] = my_char_to_int(str[i]);
	}
	// Auffuellen mit dem Fuellzeichen am Ende
	for (i=laenge_str; i<laenge_cipher; i++)
	{
		ciphertext[i] = my_char_to_int(get_fuellzeichen());
	}
}

// Funktionen zum Ermitteln des verschluesselten Textes
void CHillEncryption::get_ciphertext (char *str) const
{
	// hier wird kopiert, Laenge des Feldes muss sein:
	// objekt.get_laenge_cipher() + 1;
	
	for (long i=0; i<laenge_cipher; i++)
	{
		str[i] = my_int_to_char(ciphertext[i]);
	}
	str[laenge_cipher] = '\0';
}


// Funktionen zum Setzen der Verschluesselungsmatrix
BOOL CHillEncryption::set_dec_mat (CSquareMatrixModN &mat)
{
	// Beide Matrizen muessen die gleiche Dimension haben
	ASSERT (mat.get_dim() == dim);

	*dec_mat = mat;
	
	return dec_mat->invert(enc_mat);
}

// Funktionen zum Ermitteln der Verschluesselungsmatrix
void CHillEncryption::get_dec_mat (CSquareMatrixModN *mat) const
{
	// Beide Matrizen muessen die gleiche Dimension haben
	ASSERT (mat->get_dim() == dim);

	*mat = *dec_mat;
}

// Funktionen zum Setzen der Entschluesselungsmatrix
BOOL CHillEncryption::set_enc_mat (CSquareMatrixModN &mat)
{
	// Beide Matrizen muessen die gleiche Dimension haben
	ASSERT (mat.get_dim() == dim);

	*enc_mat = mat;

	return enc_mat->invert(dec_mat);
}

// Funktionen zum Ermitteln der Entschluesselungsmatrix
void CHillEncryption::get_enc_mat (CSquareMatrixModN *mat) const
{
	// Beide Matrizen muessen die gleiche Dimension haben
	ASSERT (mat->get_dim() == dim);

	*mat = *enc_mat;
}

// Den vorher gesetzten unverschluesselten Text mit der
// Verschluesselungsmatrix verschluesseln
BOOL CHillEncryption::verschluesseln()
{
	if (plaintext && enc_mat)
	{
		if (ciphertext)
		{
			delete[] ciphertext;
		}
		laenge_cipher = laenge_plain;
		ciphertext = new int[laenge_cipher];
		
		for (long i=0; i<laenge_plain/dim; i++)
		{
			for (int j=0; j<dim; j++)
			{
				long hilf = 0;
				for (int k=0; k<dim; k++)
				{
					if(iHillMultiplicationType)
						hilf += (*enc_mat)(k,j) * plaintext[dim*i+k];
					else
						hilf += (*enc_mat)(j,k) * plaintext[dim*i+k];

					hilf %= modul;
				}
				ciphertext[dim*i+j] = hilf;
			}
		}

#ifdef _DEBUG
		TRACE("Plaintext:\n");
		int my_i;
		for (my_i=0; (my_i<20) && (my_i<laenge_plain); my_i++)
		{
			TRACE("%3d ", plaintext[my_i]);
		}
		TRACE("\n");
		for (my_i=0; (my_i<20) && (my_i<laenge_plain); my_i++)
		{
			TRACE("  %c ", my_int_to_char(plaintext[my_i]));
		}
		TRACE("\nCiphertext:\n");
		for (my_i=0; (my_i<20) && (my_i<laenge_cipher); my_i++)
		{
			TRACE("%3d ", ciphertext[my_i]);
		}
		TRACE("\n");
		for (my_i=0; (my_i<20) && (my_i<laenge_plain); my_i++)
		{
			TRACE("  %c ", my_int_to_char(ciphertext[my_i]));
		}
		TRACE("\nVerschluesselungsmatrix:\n");
		for (my_i=0; my_i<dim; my_i++)
		{
			for (int my_j=0; my_j<dim; my_j++)
			{
				if(iHillMultiplicationType)
					TRACE("%d ", (*enc_mat)(my_i,my_j));
				else
					TRACE("%d ", (*enc_mat)(my_j,my_i));
			}
			TRACE("\n");
		}
		TRACE("\nModul = %d.\n", modul);
		TRACE("\n");
#endif
		
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// Den vorher gesetzten verschluesselten Text mit der
// Entschluesselungsmatrix entschluesseln
BOOL CHillEncryption::entschluesseln()
{
	if (ciphertext && dec_mat)
	{
		if (plaintext)
		{
			delete[] plaintext;
		}
		laenge_plain = laenge_cipher;
		plaintext = new int[laenge_plain];
		
		long i;
		for (i=0; i<laenge_cipher/dim; i++)
		{
			for (int j=0; j<dim; j++)
			{
				long hilf = 0;
				for (int k=0; k<dim; k++)
				{
					if(iHillMultiplicationType)
						hilf += (*dec_mat)(k,j) * ciphertext[dim*i+k];
					else
						hilf += (*dec_mat)(j,k) * ciphertext[dim*i+k];

					hilf %= modul;
				}
				plaintext[dim*i+j] = hilf;
			}
		}
		
#ifdef _DEBUG
		TRACE("Plaintext:\n");

		int my_i;
		for (my_i=0; (my_i<20) && (my_i<laenge_plain); my_i++)
		{
			TRACE("%3d ", plaintext[my_i]);
		}
		TRACE("\n");
		for (my_i=0; (my_i<20) && (my_i<laenge_plain); my_i++)
		{
			TRACE("  %c ", my_int_to_char(plaintext[my_i]));
		}
		TRACE("\nCiphertext:\n");
		for (my_i=0; (my_i<20) && (my_i<laenge_cipher); my_i++)
		{
			TRACE("%d ", ciphertext[my_i]);
		}
		TRACE("\n");
		for (my_i=0; (my_i<20) && (my_i<laenge_plain); my_i++)
		{
			TRACE("  %c ", my_int_to_char(ciphertext[my_i]));
		}
		TRACE("\nEntschluesselungsmatrix:\n");
		for (my_i=0; my_i<dim; my_i++)
		{
			for (int my_j=0; my_j<dim; my_j++)
			{
				if(iHillMultiplicationType)
					TRACE("%3d ", (*dec_mat)(my_i,my_j));
				else
					TRACE("%3d ", (*dec_mat)(my_j,my_i));
			}
			TRACE("\n");
		}
		TRACE("\nModul = %d.\n", modul);
		TRACE("\n");
#endif

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


// ==================================================================
// 
//  
// 

void CHillEncryption::my_sprintf(char *str, int i)
{
	if (modul > 100)
		sprintf(str, "%03i", i);
	else
		sprintf(str, "%02i", i);
}


void CHillEncryption::OutputHillmatrix(CString &MatOut)
{

	char num[4];
	CString tmpStr;

	MatOut.LoadString(IDS_HILL_DUMP);

	CString strExmpl;
	//reading example from userinput
	int  i_act_example[256];
	char c_act_example[256];  

	for (int i=0; (i<dim && i<laenge_plain); i++)
	{
		strExmpl += (CString)my_int_to_char(plaintext[i]);
		i_act_example[i] = plaintext[i];
		c_act_example[i] = (char)my_int_to_char(i_act_example[i]);
	}
	c_act_example[dim] = '\0';
	LPCTSTR example = strExmpl;
	MatOut.Replace("%PLAINTEXT%", example);


	if ( !dec_mat && !enc_mat ) 
		return;

	int floor_rows = modul / 4;
	int remainder = modul % 4;

	// int iShiftPos = 0;
	// if(!firstPosNull)iShiftPos = 1;

	tmpStr = _T("");
	for (int i=0; i<=floor_rows; i++)
	{
		int ndx = i;
		
		if ( i == floor_rows && 0 == remainder ) break;
		tmpStr += '\t';
		for (int j=0; j<4; j++)
		{
			if (i == floor_rows && j >= remainder) break;

			if(m_alphabetOffset)
				tmpStr = tmpStr + (char)my_int_to_char((ndx + 1)%modul) + ' ' + CString(" --> ")  + '\t';	
			else
				tmpStr = tmpStr + (char)my_int_to_char(ndx) + ' ' + CString(" -->") + '\t';
				
			my_sprintf(num, ndx+m_alphabetOffset);

			tmpStr += CString(num) + ' ';
		    tmpStr += '\t';
			ndx += floor_rows;
			if ( j<remainder ) ndx++;						
		}
		tmpStr += '\n';
	}
	MatOut.Replace("%ALPHABET_MAPPING%", tmpStr);

	tmpStr.Format(_T("%d"), theApp.TextOptions.getAlphabet().GetLength() );
	MatOut.Replace("%ALPHABET_SIZE%", tmpStr);

	if(!m_alphabetOffset)
		MatOut.Replace("%ALPHABET_CODING_OFFSET%", _T("0"));
	else
		MatOut.Replace("%ALPHABET_CODING_OFFSET%", _T("1"));

	if(iHillMultiplicationType)
	{
		tmpStr.LoadString(IDS_HILL_MULTIPLICATION_TYPE_LEFT);
		MatOut.Replace("%HILL_MULTIPLICATION_TYPE%", tmpStr);
		tmpStr.LoadString(IDS_HILL_VECTORTYPE_ROW);
		MatOut.Replace("%HILL_VECTORTYPE%", tmpStr);
		tmpStr.LoadString(IDS_HILL_VECTOR_MATRIX_MULTTYPE_LEFT);
		MatOut.Replace("%HILL_VECTOR_MATRIX_MULTTYPE%", tmpStr);		
	}
	else
	{
		tmpStr.LoadString(IDS_HILL_MULTIPLICATION_TYPE_RIGHT);
		MatOut.Replace("%HILL_MULTIPLICATION_TYPE%", tmpStr);
		tmpStr.LoadString(IDS_HILL_VECTORTYPE_COL);
		MatOut.Replace("%HILL_VECTORTYPE%", tmpStr);
		tmpStr.LoadString(IDS_HILL_VECTOR_MATRIX_MULTTYPE_RIGHT);
		MatOut.Replace("%HILL_VECTOR_MATRIX_MULTTYPE%", tmpStr);		
	}
	
		
	tmpStr.Format(_T("%d"), dim);
	MatOut.Replace("%HILL_DIMENSION%", tmpStr);

	tmpStr.Format(_T("%d"), iClearTextAlphCharCount );
	MatOut.Replace("%HILL_PLAINTEXT_SIZE%", tmpStr);
	
	tmpStr.Format(_T("%d"), iClearTextNotAlphCharCount );
	MatOut.Replace("%HILL_NON_ALPHABET_CHARS%", tmpStr);


	
	// HILL ENCRYPTION TEXT MATRIX
	if ( enc_mat )
	{
		tmpStr = _T("H[t] =");
		for (int i=0; i<dim; i++)
		{
			if(i==0)
				tmpStr = tmpStr + CString("\t[\t");
			else
				tmpStr = tmpStr + CString("\t\t\t[\t");
			for (int j=0; j<dim; j++)
			{
				tmpStr = tmpStr + (char)my_int_to_char((*enc_mat)(i,j)) + '\t';
			}
			tmpStr = tmpStr + ']' + '\n';
		} 
		MatOut.Replace("%HILL_ENCRYPTION_TEXTMATRIX%", tmpStr);

		// HILL_ENCRYPTION INT MATRIX
		tmpStr = CString("H[n] =");
		for (int i=0; i<dim; i++)
		{
			if(i==0)
				tmpStr = tmpStr + CString("\t[\t");
			else
				tmpStr = tmpStr + CString("\t\t\t[\t");
			for (int j=0; j<dim; j++)
			{
				my_sprintf(num, getPositionOfCharForOutput(((*enc_mat)(i,j))));
				tmpStr = tmpStr + num + '\t';
			}
			tmpStr = tmpStr + ']' + '\n';
		} 
		MatOut.Replace("%HILL_ENCRYPTION_INTMATRIX%", tmpStr);

		// HILL PLAINTEXT VECTOR
		tmpStr = CString("\n\nP[n] = \t[\t");
		for (int i=0; i<dim; i++)
		{
			my_sprintf(num, getPositionOfCharForOutput(i_act_example[i]));
			tmpStr = tmpStr + num + '\t';
		}
		tmpStr = tmpStr + ']';
		MatOut.Replace("%HILL_PLAINTEXT_VECTOR%", tmpStr);


		int  i_res_example[256];
		char c_res_example[256];  

		// HILL ENCRYPTION
		tmpStr = _T("");		
		for (int i=0; i<dim; i++)
		{
			int ciph = 0;
			for (int j=0; j<dim; j++)
			{
				if(iHillMultiplicationType)
					ciph +=i_act_example[j]*(*enc_mat)(j,i);
				else
					ciph +=(*enc_mat)(i,j)*i_act_example[j];
				ciph %= modul;
			}
			i_res_example[i] = ciph;
			c_res_example[i] = (char)my_int_to_char(ciph);
			
			my_sprintf(num, ciph);

			tmpStr = tmpStr + (char)my_int_to_char(ciph) + CString("\t<--\t") + CString(num) + CString(" = ");
			for (int j=0; j<dim; j++)
			{
				char num2[4];

				my_sprintf(num, i_act_example[j]);
				if (iHillMultiplicationType)
				{
					my_sprintf(num2, getPositionOfCharForOutput(((*enc_mat)(j,i))));
					tmpStr = tmpStr + CString(num) + '*' + CString(num2) + ' ';
				}
				else
				{
					my_sprintf(num2, getPositionOfCharForOutput(((*enc_mat)(i,j))));
					tmpStr = tmpStr + CString(num2) + '*' + CString(num) + ' ';
				}
				if ( j < dim-1 ) tmpStr = tmpStr + '+' + ' ';
			}
			my_sprintf(num, modul);
			tmpStr = tmpStr + CString(" (mod ") + CString(num) + ')' + '\n';
		}

		for (int i=0; i<dim; i++)
		{
			i_act_example[i] = i_res_example[i];
			c_act_example[i] = c_res_example[i];
		}
	}
	MatOut.Replace("%HILL_ENCRYPTION%",tmpStr);
	MatOut.Replace("%CIPHERTEXT%", c_act_example);

	// Hill Decryption text matrix
	if ( dec_mat )
	{
		tmpStr = "D[t] =";
		for (int i=0; i<dim; i++)
		{
			if(i==0)
				tmpStr = tmpStr + CString("\t[\t");
			else
				tmpStr = tmpStr + CString("\t\t\t[\t");
			for (int j=0; j<dim; j++)
			{
				tmpStr = tmpStr + (char)my_int_to_char(((*dec_mat)(i,j))) + '\t';
			}
			tmpStr = tmpStr + ']' + '\n';
		}
		MatOut.Replace("%HILL_DECRYPTION_TEXTMATRIX%", tmpStr);

		// Hill Decryption int matrix
		tmpStr = "D[n] =";
		for (int i=0; i<dim; i++)
		{
			if(i==0)
                tmpStr = tmpStr + CString("\t[\t");
			else
				tmpStr = tmpStr + CString("\t\t\t[\t");
			for (int j=0; j<dim; j++)
			{
				if(iHillMultiplicationType)
					my_sprintf(num, getPositionOfCharForOutput(((*dec_mat)(j,i))));
				else
					my_sprintf(num, getPositionOfCharForOutput(((*dec_mat)(i,j))));
				tmpStr = tmpStr + num + '\t';
			}
			tmpStr = tmpStr + ']' + '\n';
		} 
		MatOut.Replace("%HILL_DECRYPTION_INTMATRIX%", tmpStr);

		// CIPHERTEXT VECTOR
		tmpStr = "C[n] = \t[\t";
		for (int i=0; i<dim; i++)
		{
			my_sprintf(num, getPositionOfCharForOutput(i_act_example[i]));
			tmpStr = tmpStr + num + '\t';
		}
		tmpStr = tmpStr + ']';
		MatOut.Replace("%HILL_CIPHERTEXT_VECTOR%", tmpStr);

		// HILL DECRYPTION
		int  i_res_example[256];
		char c_res_example[256];  

		tmpStr = _T("");		
		for (int i=0; i<dim; i++)
		{
			int ciph = 0;
			for (int j=0; j<dim; j++)
			{
				if(iHillMultiplicationType)
					ciph +=i_act_example[j]*(*dec_mat)(j,i);
				else
					ciph +=i_act_example[j]*(*dec_mat)(i,j);
				ciph %= modul;
			}
			i_res_example[i] = ciph;
			c_res_example[i] = (char)my_int_to_char(ciph);
			
			my_sprintf(num, ciph);

			tmpStr = tmpStr + (char)my_int_to_char(ciph) + CString("\t<--\t") + CString(num) + CString(" = ");
			for (int j=0; j<dim; j++)
			{
				char num2[4];
				my_sprintf(num, i_act_example[j]);
				if(iHillMultiplicationType)
				{
					my_sprintf(num2, getPositionOfCharForOutput(((*dec_mat)(j,i))));
					tmpStr = tmpStr + CString(num) + '*' + CString(num2) + ' ';
				}
				else
				{
					my_sprintf(num2, getPositionOfCharForOutput(((*dec_mat)(i,j))));
					tmpStr = tmpStr + CString(num2) + '*' + CString(num) + ' ';
				}
				
				if ( j < dim-1 ) tmpStr = tmpStr + '+' + ' ';
			}
			if ( modul > 100 )	sprintf(num, "%03i", modul);
			else 	            sprintf(num, "%02i", modul);					
			tmpStr = tmpStr + CString(" (mod ") + CString(num) + ')' + '\n';
		}

		for (int i=0; i<dim; i++)
		{
			i_act_example[i] = i_res_example[i];
			c_act_example[i] = c_res_example[i];
		}
		MatOut.Replace("%HILL_DECRYPTION%", tmpStr);
	}   	
}



// Known-Plaintext-Angriff fuer die vorher gesetzten 
// unverschluesselten und verschluesselten texte
// Es werden alle moeglichen Kombinationen von Schluesselpaaren
// ausprobiert; ist eine Kombination gefunden, so wird diese
// von der Methode zurueckgeliefert; es wird vorher ueberprueft,
// ob sich der gesamte Text damit ver- / entschluesseln laesst.
// Die Matrix mat muß im rufenden Programm wieder freigegeben werden !!!
int CHillEncryption::angriff(int min, int max, CSquareMatrixModN* &mat, int rc_angriff_dims[HILL_MAX_DIM_GROSS])
{
	BOOL gefunden = FALSE;
	int rc_angriff = HILL_NICHT_OK_NICHT_GEFUNDEN; // Werte: siehe hill.h

	long i;    // mehrmals benoetigte Laufvariable

	for (i=0; i<HILL_MAX_DIM_GROSS; i++)
	{
		rc_angriff_dims[i] = HILL_UNDEF;
	}

	min = (min >= 1) ? min : 1;
	max = (max <= HILL_MAX_DIM_GROSS) ? max : HILL_MAX_DIM_GROSS;

	// prevent the memory leak in funcion SucheSchluessel( ... ) (see below)
	if ( max > laenge_plain  ) max = laenge_plain;
	if ( max > laenge_cipher ) max = laenge_cipher;
	
	// nun ist min >= 1 und max <= HILL_MAX_DIM_GROSS
	
	int testdim = min;
	
	while ( (testdim <= max) && (! gefunden) )
	{
		// Schluessel auf richtige Laenge fuer testdim bringen
		// Der letzte (eventuell unvollstaendige) Block wird mit Fuellzeichen aufgefüllt
		// Es gilt: ((laenge_plain-1)/testdim+1)*testdim = ceiling(laenge.../testdim)
		// Da beide Texte die gleiche Laenge haben muessen, wird nur eine Variable
		// dafuer benutzt: local_laenge
		long local_laenge_plain = ((laenge_plain-1)/testdim+1)*testdim,
			local_laenge_cipher = ((laenge_cipher-1)/testdim+1)*testdim;
		
		// Falls diese Variablen nicht gleich lang sind, kann mittels Hill-Verfahren aus dem 
		// Klartext nicht der verschlüsselte Text erzeugt worden sein oder umgekehrt.
		// Bei Texten unterschiedlicher Laenge wird versucht, den Schluessel aus der 
		// maximal moeglichen Laenge, so dass aber aus beiden Texten der letzte Block
		// vollstaendig ist, zu ermitteln. Der letzte Block muss vollstaendig sein, da ein
		// Auffuellen mit X eventuell zu falschen Ergebnissen fuehrt, wenn der eine Text  
		// nicht bis zum Ende angegeben worden ist. 
		long local_laenge;
		if (local_laenge_plain == local_laenge_cipher)
		{
			local_laenge = local_laenge_plain;
		}
		else
		{
			// Minimum suchen
			if (laenge_plain <= laenge_cipher)
			{
				local_laenge = laenge_plain;
			}
			else
			{
				local_laenge = laenge_cipher;
			}
			// Jetzt so setzen, dass ohne Rest durch testdim teilbar
			// (= untere Gaussklammer)
			local_laenge = (local_laenge/testdim)*testdim;
		}
		
		int *plain,
			*cipher;
		plain = new int[local_laenge];
		cipher = new int[local_laenge];
		
		long i;
		if (local_laenge_plain == local_laenge_cipher)
		{
			for (i=0; i<laenge_plain; i++)
			{
				plain[i] = plaintext[i];
			}
			for (i=laenge_plain; i<local_laenge; i++)
			{
				plain[i] = my_char_to_int(get_fuellzeichen());
			}
			
			for (i=0; i<laenge_cipher; i++)
			{
				cipher[i] = ciphertext[i];
			}
			for (i=laenge_cipher; i<local_laenge; i++)
			{
				cipher[i] = my_char_to_int(get_fuellzeichen());
			}
		}
		else
		{
			// Kein Auffuellen mit Fuellzeichen notwendig, da beide Texte mindestens die 
			// Laenge local_laenge haben
			for (i=0; i<local_laenge; i++)
			{
				plain[i] = plaintext[i];
			}
			
			for (i=0; i<local_laenge; i++)
			{
				cipher[i] = ciphertext[i];
			}
		}
		
#ifdef _DEBUG
		TRACE("Plaintext:\n");
		int my_i;

		for (my_i=0; (my_i<20) && (my_i<local_laenge); my_i++)
		{
			TRACE("%3d ", plain[my_i]);
		}
		TRACE("\n");
		for (my_i=0; (my_i<20) && (my_i<local_laenge); my_i++)
		{
			TRACE("  %c ", my_int_to_char(plain[my_i]));
		}
		TRACE("\nCiphertext:\n");
		for (my_i=0; (my_i<20) && (my_i<local_laenge); my_i++)
		{
			TRACE("%3d ", cipher[my_i]);
		}
		TRACE("\n");
		for (my_i=0; (my_i<20) && (my_i<local_laenge); my_i++)
		{
			TRACE("  %c ", my_int_to_char(cipher[my_i]));
		}
		TRACE("\n");
#endif

		CSquareMatrixModN plainmat(testdim, modul),
					  ciphermat(testdim, modul),
					  hilfsmat(testdim, modul);
		
		CSquareMatrixModN* ergebnismat;
		ergebnismat = new CSquareMatrixModN(testdim,modul);

		SucheSchluessel (0, // Rekursionsstufe
			testdim,
			local_laenge/testdim,  //Anzahl der Bloecke
			plain, cipher, &gefunden, &rc_angriff, ergebnismat,
			&plainmat, &ciphermat, &hilfsmat);

		if (gefunden)
		{
			// Falls der Schluessel gefunden worden ist und die Laenge der Texte unterschiedlich
			// ist, muss der Rueckgabewert noch angepasst werden.
			if ( (local_laenge_plain != local_laenge_cipher) &&
				 gefunden && (rc_angriff == HILL_OK) )
			{
				rc_angriff = HILL_OK_LAENGE_UNTERSCHIEDLICH;
			}

			mat = ergebnismat;
			dim = testdim;
		}
		else
		{
			// Ergebnis der Suche merken und wieder auf Anfangswert setzen
			rc_angriff_dims[testdim-1] = rc_angriff;
			rc_angriff = HILL_NICHT_OK_NICHT_GEFUNDEN;

			delete ergebnismat;
		}
		
		delete[] plain;
		delete[] cipher;

		testdim++;
	}

	// Falls der Schluessel nicht gefunden wurde, so ist zu ueberpruefen, ob der Grund
	// immer derselbe ist.
	if (! gefunden)
	{
		rc_angriff = rc_angriff_dims[min-1];
		i = min;
		while ( (i < max) && (rc_angriff != HILL_UNDEF))
		{
			if (rc_angriff_dims[i] != rc_angriff)
			{
				rc_angriff = HILL_UNDEF;
			}

			i++;
		}

		// Jetzt ist rc_angriff entweder gleich HILL_NICHT_OK_WIDERSPRUCH oder
		// HILL_NICHT_OK_NICHT_GEFUNDEN, falls dieses Ergebnis fuer alle Dimensionen 
		// ermittelt wurde.
		// Tauchen beide Konstanten mindestens ein Mal auf, so ist rc_angriff = HILL_UNDEF.
	}
	
	return rc_angriff;
}


// Rekursive Hilfsfunktion fuer angriff
// Die Hilfs-Matrix (letzter Parameter) ist eine obere Dreiecksmatrix, die auf der Hauptdiagonalen
// nur Einsen hat. Sie wird sukzessive aufgebaut, jeweils eine Zeile pro Rekursionsstufe.
// sie dient der Ueberpruefung der Unabhaengigkeit der gefundenen Vektoren und in der letzten
// Rekursionsstufe zur Speicherung weiterer Zwischenergebnisse.
//
// Falls es keinen Vektor mehr gibt, der von den anderen unabhängig ist,
// so werden alle möglichen Linearkombinationen der vorhandenen Vektoren ausprobiert
void CHillEncryption::SucheSchluessel (int iRekursionsStufe,	// aktuelle Rekursionsstufe mit
													// 0 <= iRekursionsStufe < iTestdim
							int iTestDim,	// zu testende Dimension des Schluessels
							long lAnzahlBloecke,	// Anzahl der Bloecke
							int* aiPlain,	// Klartext
							int* aiCipher,	// verschluesselter Text
							BOOL* pbGefunden,	// Flag fuer Schluessel gefunden
							int* rc_angriff,  // Werte siehe: hill.h
							CSquareMatrixModN* pErgebnisMat,	// gefundener Schluessel
							CSquareMatrixModN* pPlainMat,	// Matrix, die aus Klartext aufgebaut wird
							CSquareMatrixModN* pCipherMat,	// Matrix, die aus verschluesseltem Text aufgebaut wird
							CSquareMatrixModN* pHilfsMat	// Hilfsmatrix
							)
{
	// Matrix ausgeben
#ifdef _DEBUG
	int my_k, my_l;
	TRACE("Hilfsmatrix:\n");
	for (my_k=0; my_k<iTestDim; my_k++)
	{
		for (my_l=0; my_l<iTestDim; my_l++)
		{
			TRACE("%2d ", (*pHilfsMat)(my_k,my_l));
		}
		TRACE("\n");
	}
	TRACE("\n");
#endif


	// Ein Schluessel kann gefunden werden, wenn es mindestens soviele linear
	// unabhaengige Vektoren (= Bloecke) gibt, wie die Dimension des Schluessels.
	// Wir versuchen, indem das Feld Dimension-mal von vorne durchlaufen wird,
	// genuegend unabhaengige Vektoren zu finden. In jeder Rekursuionsstufe wird 
	// eine neue Zeile in die Matrizen PlainMat und CipherMat geschrieben. 
	// Diese Zeile ist von den vorherigen unabhaengig.
	// Laufzeit: linear in der Laenge des Textes !
	// Die Hilfsmatrix soll am Ende so aussehen (obere Dreiecksmatrix mit 1 auf Hauptdiagonalen):
	// (x = beliebiger Wert)
	// ( 1 x x . x )
	// ( 0 1 x . x )
	// ( 0 0 1 . x )
	// ( ......... )
	// ( 0 0 0 . 1 )
	// Dann wurde Dimension-viele unabhaengige Vektoren gefunden
	
	ASSERT ((0 <= iRekursionsStufe) && (iRekursionsStufe < iTestDim));


	int inverses_element; // ... des Elements auf der Hauptdiagonalen, welches 
						  // auf eins gebracht werden soll.
	int faktor; // Wird zur Addition der schon vorhandenen Zeilen auf die 
				// momentan zu untersuchende benoetigt.
	int j,k; // Laufvariablen fuer Zeile und Spalte der Matrizen

	for (j=0; j<modul; j++)
	{
		laPositionVektor[j] = HILL_LIN_KOMB_INIT;
		iaLinearKombination1[j] = HILL_LIN_KOMB_INIT;
		iaLinearKombination2[j] = HILL_LIN_KOMB_INIT;
	}

	BOOL bVektorGefunden = FALSE;
	for (long i=0; (i<lAnzahlBloecke) && (! bVektorGefunden); i++)
	{
		// Einen weiteren unabhaengigen Vektor suchen und in die Hilfs-Matrix schreiben, falls gefunden
		// Es wird versucht, ob der aktuelle Vektor (Position i) zu den anderen in der Hilfs-Matrix
		// unabhaengig ist, indem er in die Hilfs-Matrix eingefuegt wird, wobei die Stellen
		// links von der Hauptdiagonalen auf Null gesetzt werden (durch Addition der bislang gefundenen
		// unabhaengigen Vektoren). Falls da Element auf der Hauptdiagonalen ein invereses Element
		// besitzt, so wird dieser Vektor zu den anderen hinzugenommen, ansonsten wird weitergesucht.

		// Block in die entsprechenden Zeile der Hilfs-Matrix schreiben
		// und die entsprechenden Bloecke in den Matrizen fuer den Klartext 
		// und verschluesselten Text speichern
		for (k=0; k<iTestDim; k++)
		{
			(*pHilfsMat)(iRekursionsStufe,k) = aiPlain[i*iTestDim+k];
			(*pPlainMat)(iRekursionsStufe,k) = aiPlain[i*iTestDim+k];
			(*pCipherMat)(iRekursionsStufe,k) = aiCipher[i*iTestDim+k];
		}
		
		// die Elemente links von der Hauptdiagonalen auf Null bringen
		for (j=0; j<iRekursionsStufe; j++)
		{
			faktor = modul - ((*pHilfsMat)(iRekursionsStufe,j) % modul);
			ASSERT((1 <= faktor) && (faktor <= modul));
			
			// das faktor-fache der j-ten Zeile auf die iRekursionsStufe-te Zeile addieren
			for (k=0; k<iTestDim; k++)
			{
				(*pHilfsMat)(iRekursionsStufe,k) += (faktor * (*pHilfsMat)(j,k));
				(*pHilfsMat)(iRekursionsStufe,k) %= modul; 
			}
		}

		ASSERT((0 <= (*pHilfsMat)(iRekursionsStufe,iRekursionsStufe)) && 
			   ((*pHilfsMat)(iRekursionsStufe,iRekursionsStufe) < modul));

		// Wir merken uns die Position von jedem Wert ((*pHilfsMat)(iRekursionsStufe,iRekursionsStufe))
		// an der Stelle i im Feld (Wir merken uns immer die erste passende Position)
		if ( (laPositionVektor[(*pHilfsMat)(iRekursionsStufe,iRekursionsStufe)] == HILL_LIN_KOMB_INIT) ) 
		{
			laPositionVektor[(*pHilfsMat)(iRekursionsStufe,iRekursionsStufe)] = i;
		}

		inverses_element = pHilfsMat->get_inverses_element((*pHilfsMat)(iRekursionsStufe,iRekursionsStufe));

		if (inverses_element)
		{
			// neuen linear unabhaengigen Vektor gefunden
			for (k=iRekursionsStufe; k<iTestDim; k++)
			{
				(*pHilfsMat)(iRekursionsStufe,k) *= inverses_element;
				(*pHilfsMat)(iRekursionsStufe,k) %= modul;
			}
			ASSERT((*pHilfsMat)(iRekursionsStufe,iRekursionsStufe) == 1);
			bVektorGefunden = TRUE;
		}
	}

	// Eventuell kann eine weitere Zeile nicht gefunden werden, obwohl eine erzeugt werden kann
	// aus einer Linearkombination verschiedener Zeilen.
	// Vergleiche Inversion ueber Gauss Jordan Verfahren in sq_mat.cpp
	//
	// laPositionVektor[j] enthaelt die Position des Vektors, der in der aktuellen Zeile 
	// in der naechsten zu betrachtenden Spalte den Wert j besitzt, wenn alle Eintraege
	// links von der Spalte auf Null gebracht werden.
	// Anfangs wurde laPositionVektor mit HILL_LIN_KOMB_INIT initialisiert,
	// der Wert HILL_LIN_KOMB_NEU heisst, dass dieser Wert hier neu gefunden wurde
	//
	// Nun werden alle Linearkombinationen gebildet, bis eine invertierbare Zahl gefunden wird
	// beziehungsweise alle Linearkombinationen gebildet wurden und keine invertierbare Zahl 
	// gefunden werden konnte. Laufzeit: O(modul^2);
	int iInvertierbaresElement = 0; // Wenn spaeter != 0, wurde ein Element gefunden.

	if (! bVektorGefunden)
	{
		ASSERT(inverses_element == 0); 

		bool bNeuesElementGefunden = true;

		// Schleifenbedingungen:
		// 1: Abbruch sofort, wenn ein invertierbares Element gefunden worden ist. 
		// 2: Falls neue Elemente gefunden worden sind, sind die beiden for-Schleifen
		//    erneut auszufuehren, weil sich neue - vorher nicht vorhandene - 
		//    Linearkombinationen ergeben koennten.
		while ( (! inverses_element) && (bNeuesElementGefunden))
		{
			bNeuesElementGefunden = false;

			// Bilden aller Linearkombinationen, dabei muss ein Element auch mit sich
			// selbst linearkombiniert werden.
			// Die Linearkombinationen werden durch sukzessive Addition zweier Zahlen gebildet.
			for (long i=0; (i<modul) && (! inverses_element); i++)
			{
				for (j=i; (j<modul) && (! inverses_element); j++)
				{
					// Wurde ein neues Element gefunden ?
					// Wenn ja, merken, aus welchen beiden es linearkombiniert worden ist.
					// Bemerkung:
					// Es ist wichtig, dass sich kein Zyklus in den Linearkombinationen ergibt.
					// Dies ist aber sichergestellt, da im Feld laPositionVektor nur dann
					// neue Eintraege gemacht werden, wenn es noch den Initialwert besitzt.
					if ( (laPositionVektor[i] != HILL_LIN_KOMB_INIT) &&
						 (laPositionVektor[j] != HILL_LIN_KOMB_INIT) &&
						 (laPositionVektor[(i+j)%modul] == HILL_LIN_KOMB_INIT) )
					{
						bNeuesElementGefunden = true;

						laPositionVektor[(i+j)%modul] = HILL_LIN_KOMB_NEU;
						iaLinearKombination1[(i+j)%modul] = i;
						iaLinearKombination2[(i+j)%modul] = j;

						// Ist dieses neu gefundene Element invertierbar ?
						inverses_element = pHilfsMat->get_inverses_element((i+j)%modul);
						if (inverses_element)
						{
							iInvertierbaresElement = (i+j)%modul;
						}
					}
				}
			}
		}
	}

#ifdef _DEBUG
	TRACE("Hilfsmatrix:\n");
	for (my_k=0; my_k<iTestDim; my_k++)
	{
		for (my_l=0; my_l<iTestDim; my_l++)
		{
			TRACE("%3d ", (*pHilfsMat)(my_k,my_l));
		}
		TRACE("\n");
	}
	TRACE("\nPlaintext\n");
	for (my_k=0; (my_k<10) && (my_k<lAnzahlBloecke*iTestDim); my_k++)
	{
		TRACE("%3d ", aiPlain[my_k]);
	}
	TRACE("\n");
	for (my_k=0; (my_k<10) && (my_k<lAnzahlBloecke*iTestDim); my_k++)
	{
		TRACE("  %c ", my_int_to_char(aiPlain[my_k]));
	}
	TRACE("\nCiphertext\n");
	for (my_k=0; (my_k<10) && (my_k<lAnzahlBloecke*iTestDim); my_k++)
	{
		TRACE("%3d ", aiCipher[my_k]);
	}
	TRACE("\n");
	for (my_k=0; (my_k<10) && (my_k<lAnzahlBloecke*iTestDim); my_k++)
	{
		TRACE("  %c ", my_int_to_char(aiCipher[my_k]));
	}
	TRACE("\n");

#endif

#ifdef _DEBUG
	for (j=0; j<modul; j++)
	{
		TRACE("%2d ", j);
	}
	TRACE("\nlaPositionVektor:\n");
	for (j=0; j<modul; j++)
	{
		TRACE("%2d ", laPositionVektor[j]);
	}
	TRACE("\niaLinearKombination1:\n");
	for (j=0; j<modul; j++)
	{
		TRACE("%2d ", iaLinearKombination1[j]);
	}
	TRACE("\niaLinearKombination2:\n");
	for (j=0; j<modul; j++)
	{
		TRACE("%2d ", iaLinearKombination2[j]);
	}
	TRACE("\n");
#endif

	// Falls kein invertierbares Element bei der 'normalen' Suche gefunden werden konnte, aber 
	// bei der Suche nach Linearkombinationen, dann ist diese Linearkombination jetzt 
	// wirklich in die Matrix zu schreiben; im Anschluss werden alle Elemente links von dem zu 
	// invertierenden Zeichen auf Null gebracht un die Zeile neu berechnet (Form: 0 ... 0 1 x ... x).
	if ( (! bVektorGefunden) && (iInvertierbaresElement) )
	{
		// Die Linearkombination in der richtigen Zeile der Matrix bilden
		// In den beiden Feldern iaLinearKombination1[j] und iaLinearKombination2[j] wurden die 
		// Werte gespeichert, aus denen sich j zusammensetzt, falls laPositionVektor[j] == HILL_LIN_KOMB_NEU.
		// Mit der Rekursiven Prozedur werden die Faktoren (die a_i in x = a_1 * x_1 + ... + a_k * x_k.)
		// der Linearkombination berechnet und in das Feld iaFaktoren
		
		// iInvertierbaresElement kann nicht gleich 0 sein !
		ASSERT ( (1 <= iInvertierbaresElement) && (iInvertierbaresElement < modul));
		long i;
		for (i=0; i<modul; i++)
		{
			iaFaktoren[i] = 0;
		}

		BerechneFaktoren(iInvertierbaresElement, lAnzahlBloecke);

#ifdef _DEBUG
		ASSERT (iaFaktoren[0] == 0); // Die 0 kann nicht vorkommen (, da sie nichts veraendert).
		for (i=1; i<modul; i++)
		{
			ASSERT ( (0 <= iaFaktoren[i]) && (iaFaktoren[i] < modul) );
		}
#endif
		
		// Linearkombination erzeugen
		// Erst alle Felder initialisieren ...
		for (k=0; k<iTestDim; k++)
		{
			(*pHilfsMat)(iRekursionsStufe,k) = 0;
			(*pPlainMat)(iRekursionsStufe,k) = 0;
			(*pCipherMat)(iRekursionsStufe,k) = 0;
		}
		// ... und jetzt die Vektoren mit den entsprechenden Faktoren multiplizieren
		// und auf die vorhandene Linearkombination addieren.
		// um keinen Ueberlauf zu riskieren (falls modul und iTestDim groesser werden),
		// fuehren wir nach jeder Addition die Modulo Berechnung durch.
		for (j=0; j<modul; j++)
		{
			if (iaFaktoren[j] != 0) // sonst ist laPositionVektor[j] undefiniert
			{
				ASSERT ((0 <= laPositionVektor[j]) && (laPositionVektor[j] < lAnzahlBloecke));
				for (k=0; k<iTestDim; k++)
				{
					(*pHilfsMat)(iRekursionsStufe,k) += (iaFaktoren[j] * aiPlain[laPositionVektor[j]*iTestDim+k]);
					(*pHilfsMat)(iRekursionsStufe,k) %= modul;
					(*pPlainMat)(iRekursionsStufe,k) += (iaFaktoren[j] * aiPlain[laPositionVektor[j]*iTestDim+k]);
					(*pPlainMat)(iRekursionsStufe,k) %= modul;
					(*pCipherMat)(iRekursionsStufe,k) += (iaFaktoren[j] * aiCipher[laPositionVektor[j]*iTestDim+k]);
					(*pCipherMat)(iRekursionsStufe,k) %= modul;
				}
			}
		}
		
		// die Elemente links von der Hauptdiagonalen auf Null bringen
		for (j=0; j<iRekursionsStufe; j++)
		{
			faktor = modul - ((*pHilfsMat)(iRekursionsStufe,j) % modul);
			ASSERT((1 <= faktor) && (faktor <= modul));
			
			// das faktor-fache der j-ten Zeile auf die iRekursionsStufe-te Zeile addieren
			for (k=0; k<iTestDim; k++)
			{
				(*pHilfsMat)(iRekursionsStufe,k) += (faktor * (*pHilfsMat)(j,k));
				(*pHilfsMat)(iRekursionsStufe,k) %= modul; 
			}
		}

		inverses_element = pHilfsMat->get_inverses_element((*pHilfsMat)(iRekursionsStufe,iRekursionsStufe));

		// Das Element muss ein Inverses besitzen, da es das entsprechende Element der 
		// gefundenen Linearkombination ist (, die wie oben gefunden invertierbar ist). 
		ASSERT(inverses_element != 0);

		// neuen linear unabhaengigen Vektor gefunden
		for (k=iRekursionsStufe; k<iTestDim; k++)
		{
			(*pHilfsMat)(iRekursionsStufe,k) *= inverses_element;
			(*pHilfsMat)(iRekursionsStufe,k) %= modul;
		}
		ASSERT((*pHilfsMat)(iRekursionsStufe,iRekursionsStufe) == 1);
		bVektorGefunden = TRUE;
	}
	
	if (bVektorGefunden)
	{
		// Sind wir in der letzten Rekursionsstufe, d.h. sind die Matrizen fertig aufgebaut
		if (iRekursionsStufe == (iTestDim - 1))
		{
			// Schluessel ist gefunden, muss nur noch berechnet werden:
			// Hilfs-Matrix = inverse Klartext-Matrix
			// Schluessel = Hilfs-Matrix * Verschluesselter Text-Matrix
			// Der Schluessel wird in pErgebnisMat zurueckgegeben
			
			// P = Plaintextmatrix
			// C = Ciphertextmatrix
			// K = Keymatrix
			// P^(-1) = Inverse von P, ...
			// Wir haben also: 
			// K = P^(-1) * C  (Verschluesselung: P * K = C) 
			
			// Klartext-Matrix invertieren
			if (pPlainMat->invert(pHilfsMat))
			{
				for (int k=0; k<iTestDim; k++)
				{
					for (int l=0; l<iTestDim; l++)
					{
						(*pErgebnisMat)(k,l) = 0;
						for (int m=0; m<iTestDim ; m++)
						{
							(*pErgebnisMat)(k,l) += (*pHilfsMat)(k,m) * (*pCipherMat)(m,l);
						}
					}
				}
				
				pErgebnisMat->convert_mod();
				
				// Die Matrix pErgebnisMat kann nur dann ein Schluessel sein, wenn die
				// Matrix invertierbar ist
				if (pErgebnisMat->invert(pHilfsMat))
				{
					// Jetzt ueberpruefen, ob man den gesamten Text
					// mit dem gefundenen Schluessel verschluesseln kann:
					int *cipher_neu = new int[lAnzahlBloecke*iTestDim];
					
					for (long j1=0; j1<lAnzahlBloecke; j1++)
					{  
						for (int j2=0; j2<iTestDim; j2++)
						{ 
							long hilf = 0;
							for (int j3=0; j3<iTestDim; j3++)
							{
								hilf += (*pErgebnisMat)(j3,j2) * aiPlain[iTestDim*j1+j3];
								hilf %= modul;
							}
							cipher_neu[iTestDim*j1+j2] = hilf;
						}
					}
					
					*pbGefunden = TRUE;
					*rc_angriff = HILL_OK;
					
					for (int j=0; (j<(lAnzahlBloecke*iTestDim)) && (*pbGefunden); j++)
					{
						if (aiCipher[j] != cipher_neu[j])
						{
							*pbGefunden = FALSE;
							*rc_angriff = HILL_NICHT_OK_WIDERSPRUCH;
						}
					}
					
					delete[] cipher_neu;
				}
				else
				{
					// Es ist ein Widerspruch aufgetreten, denn:
					// - Es wurden im Klartext dimension-viele linear unabhaengige Vektoren gefunden
					//   => die Klartext-Matrix ist invertierbar
					// - Da das Produkt zweier invertierbarer Matrizen offensichtlich invertierbar ist,
					//   muss also auch die Matrix mit dem verschluesselten Text invertierbar sein.
					//   (Wegen der Verschluesselung mit der (invertierbaren) Schluesselmatrix
					//   Verschluesselung: P * K = C, P,K invertierbar => C invertierbar)
					// - Die Schluesselmatrix ist aber nicht invertierbar, also Widerspruch !
					//   K = P^(-1) * C nicht invertierbar, obwohl P^(-1) und C invertierbar
					// Der Klartext passt also nicht zum verschluesselten Text
					*rc_angriff = HILL_NICHT_OK_WIDERSPRUCH;
				}
			}
			else
			{
				// Fehler aufgetreten, die Zeilen sind nicht unabhaengig !!!
				//AfxMessageBox("INTERNER FEHLER !!!");
				// Dies sollte nicht passieren !
				// Solche Ausgabe sollen nicht kommen, daher: 
				ASSERT(false);

#ifdef _DEBUG
				// Matrizen ausgeben
				TRACE("Klartextmatrix:\n");
				for (my_k=0; my_k<iTestDim; my_k++)
				{
					for (my_l=0; my_l<iTestDim; my_l++)
					{
						TRACE("%2d ", (*pPlainMat)(my_k,my_l));
					}
					TRACE("\n");
				}
				TRACE("\n");
				TRACE("Ciphertextmatrix:\n");
				for (my_k=0; my_k<iTestDim; my_k++)
				{
					for (my_l=0; my_l<iTestDim; my_l++)
					{
						TRACE("%2d ", (*pCipherMat)(my_k,my_l));
					}
					TRACE("\n");
				}
				TRACE("\n");
#endif
			}
		}
		else
		{
			// Matrizen weiter aufbauen, also weiter in der Rekursion
			SucheSchluessel (iRekursionsStufe+1, iTestDim, lAnzahlBloecke, aiPlain, aiCipher,
				pbGefunden, rc_angriff, pErgebnisMat, pPlainMat, pCipherMat, pHilfsMat);
		}
	}
	else
	{
		*rc_angriff = HILL_NICHT_OK_NICHT_GEFUNDEN; // Text ist zu kurz !
	}
}

// rekursive Hilfsfunktion fuer Funktion Angriff
//
// Mit der Prozedur werden die Faktoren (die a_i in x = a_1 * x_1 + ... + a_k * x_k.)
// der Linearkombination berechnet und in das Feld iaFaktoren geschrieben.
// In den beiden Feldern iaLinearKombination1[j] und iaLinearKombination2[j] wurden die 
// Werte gespeichert, aus denen sich j zusammensetzt, falls laPositionVektor[j] == HILL_LIN_KOMB_NEU.
// (Der Parameter fuer den ersten Aufruf ist die Wurzel des Rekursionsbaumes,
// muss also das gefundene Element sein, welches invertierbar ist (% modul).)
//
// Die Funktionalitaet der Funktion kann nicht durch eine Schleife (ohne Stack oder Queue)
// erhalten werden, da ein Element sich aus zwei anderen ergeben haben kann, welche 
// sich wieder aus zwei anderen ergeben haben, usw.
void CHillEncryption::BerechneFaktoren(int i, long lAnzahlBloecke)
{
	// i kann nicht gleich 0 sein, da die Addition von 0 den Wert nicht veraendert,
	// dies also in keiner Linearkombination enthalten sein kann.
	ASSERT ( (1 <= i) && (i < modul));
	ASSERT ( (laPositionVektor[i]==HILL_LIN_KOMB_NEU) ||
			 ((0 <= laPositionVektor[i]) && (laPositionVektor[i] < lAnzahlBloecke)) );

	if (laPositionVektor[i]==HILL_LIN_KOMB_NEU)
	{
		BerechneFaktoren(iaLinearKombination1[i], lAnzahlBloecke);
		BerechneFaktoren(iaLinearKombination2[i], lAnzahlBloecke);
	}
	else // 0 <= laPositionVektor[i] < lAnzahlBloecke, also ein Vektor, der keine Linearkombination ist
	{
		ASSERT ( (iaLinearKombination1[i] == HILL_LIN_KOMB_INIT) && 
				 (iaLinearKombination2[i] == HILL_LIN_KOMB_INIT) );
		iaFaktoren[i]++;
	}
}
int CHillEncryption::getPositionOfCharForOutput(int iPos)
{
	return ( m_alphabetOffset && !iPos ) ? modul : iPos;
}