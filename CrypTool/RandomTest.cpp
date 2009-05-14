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
// Copyright 2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Matej Matejicek 2001
// Deutsche Bank AG Frankfurt - IT Security
//////////////////////////////////////////////////////////////////
//
// Zufallsgenerator_Tests_Alles.cpp: Implementierung der Klasse Zufallsgenerator_Tests.
//
//////////////////////////////////////////////////////////////////////

// Für CrypTool
#include "stdafx.h"
#include "CrypToolApp.h"
#include "s_prng.h"
#include "FileTools.h"
#include "RandomTest.h"
#include "ParseIniFile2.h"
#include "CrypToolTools.h"
// Für Zuffalszahlen
#include <time.h>
// Für File-Stream
#include <fstream>
#include <cstdlib>

// Pre-Processor
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//Definition der "Konstanten"-Parameter
#define RAND_RANGE 10240
#define DEFAULT_LONG_RUNS_GROESSE 34
#define POKER_MUSTER 256


//////////////////////////////////////////////////////////////////////
// Zufallsgenerator_Tests Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Zufallsgenerator_Tests::Zufallsgenerator_Tests()
{
	//Initiallwerte
	bestanden = FALSE;
	test_ergeb = 0;
	def_param = 3.8;
	def = TRUE;
	def2 = TRUE;
	tupel = 3;
	fips = FALSE;
}

Zufallsgenerator_Tests::~Zufallsgenerator_Tests()
{
}

void Zufallsgenerator_Tests::vergleiche_test_ergeb()
{
	if(Get_test_ergeb() <= Get_DefParam()) Set_result(TRUE);
	else Set_result(FALSE);
}

void Zufallsgenerator_Tests::Set_DefParam( double n )
{ 
	def_param = n; 
}

BOOL Zufallsgenerator_Tests::SetOffset( UINT n )
{
	offs = n;
	return TRUE;
}

BOOL Zufallsgenerator_Tests::SetTestLength( UINT n )
{
	CStdioFile file;
	file.Open(infile, CFile::modeRead);
	
	if ((n + offs) > file.GetLength()) 
	{
		file.Close();
		return FALSE;
	}
	else
	{
		file.Close();
		testlen = n;
		return TRUE;
	}
}

//////////////////////////////////////////////////////////////////////
// Freq_Test Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Freq_Test::Freq_Test() //Default Werte
{
	degr = 1;
	def_param = 2;
}

Freq_Test::~Freq_Test()
{
}

void Freq_Test::test() //Frequency-Test Verfahren
{
	UINT TestDurchlaeufe;

	BOOL SuccessFlag = TRUE;

	CStdioFile file;
	file.Open(infile, CFile::modeRead);
	ASSERT(file.GetLength() < ULONG_MAX);
	unsigned long ByteLengthOfInput = (unsigned long)file.GetLength();
	file.Close();

	if ((def == TRUE) && (fips == FALSE))
	{
		offs = 0;
		testlen = ByteLengthOfInput;
	}

	if (fips == TRUE)
	{
		offs = 0;
		testlen = 2500;
	}

	unsigned char ch;
	unsigned i,n=0, lang_test;
	unsigned long anf, bis; // Neue Variabeln für RandomTest Sequenz???

	// Initialisirung von dem Zuffalsgenerator
	srand( (unsigned) time(NULL) );

	double null = 0.0, eins = 0.0;
	ifstream read(infile, ios::in | ios::binary );

	if (def2 == TRUE) lang_test=10;
	else if (def2 == FALSE) lang_test=1;

	for (TestDurchlaeufe=0; TestDurchlaeufe<lang_test; TestDurchlaeufe++)
	{
		if ( def2 == TRUE ) //Benutzen wir Random Offset und Testlänge ???
		{
			anf = ((unsigned) (offs + (rand() % RAND_RANGE))) % ByteLengthOfInput;
			bis = ((unsigned) (testlen + (rand() % RAND_RANGE))) % ByteLengthOfInput;

			while(((anf + bis) >= ByteLengthOfInput) || (bis <= 12))
			{
				bis = 0, anf = 0;
				anf = ((unsigned) (offs + (rand() % RAND_RANGE))) % ByteLengthOfInput;
				bis = ((unsigned) (testlen + (rand() % RAND_RANGE))) % ByteLengthOfInput;
			}
		}

		else 
		{
			anf = offs;
			bis = testlen;
		}

		//if (anf < 0) anf = 0;

		n = 0;
		null=0; eins=0;


		if (read && read.seekg(anf))
		{
			while(n < bis) // Zaehlen von Einzen und Nullen
			{
				//read >> ch;
				read.get((char&) ch);
				n++;
				for(i=0;i<8;i++)
				{
					if ( bitt( ch, i ) ) eins++; //BITT Makro-Funktion würde benutzt - defeinition in Header Datei
					else null++;
				}
			}
		}
		else //Wenn Positionierung in Datei nicht erfolgt, dann Schleife fortsetzen
		{
			anf = 0;
			SuccessFlag = TRUE;
			continue;
		}

		double x=(((null - eins) * (null - eins)) / (n*8));
		Set_test_ergeb( x );	//Nach den Formel [(n_0-n_1)^2]/n
														//n_0 - die Anzahl der Nullen in der Datei
														//n_1 - die Anzahl der Einsen in der Datei
														//n	  - die Anzahl der Bits der Datei
		vergleiche_test_ergeb();

		ASSERT(eins < LONG_MAX);
		einsen = (long)eins;

		if (TRUE != (SuccessFlag &= GetResult())) break;
		else 
		{
			ASSERT(null < LONG_MAX);
			nullen = (long)null;
			testlaenge = n;
			continue;
		}

// Nicht vergessen: spaeter wieder raus
///////////////////////////////////////
	}

	read.close();
	Set_result(SuccessFlag);
}


//////////////////////////////////////////////////////////////////////
// Serial_Test Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Serial_Test::Serial_Test()
{
	degr = 2;
	def_param = 1;
}

Serial_Test::~Serial_Test()
{
}

void Serial_Test::test()
{
	unsigned long ByteLengthOfInput = 0; // Variabel die Länge der untersuchte Datei speichert
	UINT alle = 0; // Variabel die alle bestandene Testversuche zählt

	BOOL SuccessFlag = TRUE;

	//Laden von der Dateilänge
	CStdioFile file;
	file.Open(infile, CFile::modeRead);
	ASSERT(file.GetLength() < ULONG_MAX);
	ByteLengthOfInput = (unsigned long)file.GetLength();
	file.Close();

	//Sollen Defaultwerte eingesetzt werden?
	if ((def == TRUE) && (fips == FALSE))
	{
		offs = 0;
		testlen = ByteLengthOfInput;
	}

	//Wenn test() in einer FIPS-PUB-140-1 Test-Batterie gestartet ist dann sollen
	//offs und testlen Variabeln auf Test-Batterie Defaultwerte gesetzt werden
	if (fips == TRUE)
	{
		offs = 0;
		testlen = 2500;
	}

	unsigned char ch; //Variabel für lesen der Datei
	unsigned long i, lang_test;	//i - zählt der Byteposition in der Datei
						//lang_test - Zahl der bestimmt wieviel Mal der Test durchgeführt werden soll
	unsigned long anf, bis; // Neue Variabeln für RandomTest Sequenz (anf-anfang; bis-ende)

	srand( (unsigned) time(NULL) ); // Initialisirung von dem Zuffalsgenerator

	double null = 0.0, eins = 0.0;  // null - Zahl der Nullen in der Datei
									// eins - Zahl der Einsen in der Datei

	ifstream read(infile, ios::in | ios::binary ); // File-Stream der untersuchenden Datei

	if (def2 == TRUE) lang_test=10; //Wird der Test einmal oder 10x durchgeführt werden
	else if (def2 == FALSE) lang_test=1;

	for (unsigned int TestDurchlaeufe=0; TestDurchlaeufe<lang_test ;TestDurchlaeufe++) //Test wird mehrmals (einmal) durchgeführt
	{
		if ( def2 == TRUE ) //Benutzen wir Random Offset und Testlänge ?
		{
			anf = ((unsigned) (offs + (rand() % RAND_RANGE))) % ByteLengthOfInput;
							//Offset + Random_Number(in Intervall 0-RAND_RANGE) - und das alles
							//in Intervall von 0 bis ByteLengthOfInput
			if(def == FALSE)
			{
				bis = ((unsigned) (testlen + (rand() % RAND_RANGE))) % ByteLengthOfInput;
							//Bei Defaultwerten addiert man
			}
			else
			{
				bis = ((unsigned) (testlen - (rand() % RAND_RANGE))) % ByteLengthOfInput;
							//Bei "custom" Werten suptrahiert man
			}
	
			while((anf + bis) > ByteLengthOfInput) //Ob die Dateilänge überschriten ist
			{
				anf = ((unsigned) (offs + (rand() % RAND_RANGE))) % ByteLengthOfInput;
				if ( def == FALSE ) bis = ((unsigned) (testlen + (rand() % RAND_RANGE))) % ByteLengthOfInput;
				else bis = ((unsigned) (testlen - (rand() % RAND_RANGE))) % ByteLengthOfInput;
			}
		}

		else 
		{
			anf = offs;
			bis = testlen;
		}

// == Ab hier der eigentliche serial Test
		double n_0 = 0, n_1 = 0, n_00 = 0, n_01 = 0, n_10 = 0, n_11 = 0;
									//Lokalen Variablen wo man die Zahlen der Paaren oder Einsen und Nullen
									//zählen
		unsigned long n=0;
		if (read.seekg(anf) && read) //Main-Schleife
		{
			int temp = 2, flag = 0; //temp - eine Flag das wir wissen was zuletzt eine Nummer (0 oder 1)war
									//flag - eine Flag der uns zeigt das eine neue Byte gelesen ist
			while(n < bis) //Zahlen von Einzen und Nullen von 0 bis "bis"
			{
				//read >> ch;
				read.get((char&) ch);
				n++;
				flag = 1;
				for(i=1; i<=8 ;i++)
				{
					if (temp == 2)
					{
						if (i > 2) ch /= 2;
						if ( ch % 2 )//bitt( ch, i ) )
						{
							n_1++;
							ch /= 2;
							i++;
							if ( ch % 2 )//bitt( ch, i ) )
							{
								n_1++;
								n_11++;
								temp = 1;
								continue;
							}
							else 
							{
								n_0++;
								n_10++;
								temp = 0;
								continue;
							}
						}
						else
						{
							n_0++;
							ch /= 2;
							i++;
							if ( ch % 2 )//bitt( ch, i ) )
							{
								n_1++;
								n_01++;
								temp = 1;
							}
							else 
							{
								n_0++;
								n_00++;
								temp = 0;
							}
						}
					}
					else if (temp == 1)
					{
						if (flag == 0) ch /= 2;
						flag = 0;
						if ( ch % 2 )//bitt( ch, i ) )
						{
							n_1++;
							n_11++;
						}
						else
						{
							n_0++;
							n_10++;
							temp = 0;
							continue;
						}
					}
					else if (temp == 0)
					{
						if (flag == 0) ch /= 2;
						flag = 0;
						if ( ch % 2 )//bitt( ch, i ) )
						{
							n_1++;
							n_01++;
							temp = 1;
							continue;
						}
						else
						{
							n_0++;
							n_00++;
						}
					}
							
				}
			}
		}
		else //Wenn Positionierung in Datei nicht erfolgt, dann Schleife fortsetzen
		{
			anf = 0;
			SuccessFlag = TRUE;
			continue;
		}
		Set_test_ergeb( (4 * ((n_00 * n_00) + (n_01 * n_01) + (n_10 * n_10) + (n_11 * n_11)) / (n * 8 - 1)) - ((2 * (n_0 * n_0 + n_1 * n_1))/(n * 8)) + 1);	
						//Nach den Formel [4 / (n - 1) * (n_00^2 + n_01^2 + n_10^2 + n_11^2)] - [(2 / n) * (n_0^2 + n_1^2)] + 1
						//n_0 - die Anzahl der Nullen in der Datei
						//n_1 - die Anzahl der Einsen in der Datei
						//n	  - die Anzahl der Bits der Datei	

		vergleiche_test_ergeb();

		if (TRUE != (SuccessFlag &= GetResult())) break;
		else continue;
	}

}


//////////////////////////////////////////////////////////////////////
// Long_Run Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Long_Run_Test::Long_Run_Test()
{
	longrun_lang = DEFAULT_LONG_RUNS_GROESSE;
	fips_flag = FALSE; //By default wird das in keiner FIPS Test-Batterie verwendet 
}

Long_Run_Test::~Long_Run_Test()
{

}

BOOL Long_Run_Test::longrun(CString infile, unsigned run_groesse)
{
	//Man untersucht die ganze Datei nach einem Longrun, wenn gefunden dan TRUE, wenn nicht dan FALSE
	char ch = '\0';
	unsigned long run = 0, bit = 0, longest_run = 0, i = 0, ByteLengthOfInput = 0;
		//run - Lokalzähler der Run
		//longest_run - Dir gröste Run
		//i - Dateipositionzähler
		//ByteLengthOfInput - Testlänge

	CStdioFile file_;
	file_.Open(infile, CFile::modeRead);
	ASSERT(file_.GetLength() < ULONG_MAX);
	if (fips_flag == FALSE)	ByteLengthOfInput = (unsigned long)file_.GetLength();
	else ByteLengthOfInput = 2500;
	file_.Close();

	ifstream file( infile, ios::in | ios::binary );
	if ( file ) //Main-Schleife - sucht nach einem Run, wenn gefunden dann überprüft mann ob das das
				//längste Run ist
	{
		int flag = 2;
		while ( i < ByteLengthOfInput )
		{
			if ( flag == 2 )
			{
				//file >> ch;
				file.get(ch);
				i++;
			}
			if ( !( i < ByteLengthOfInput ) ) break;
			if (bit >= 8) 
			{
				//file >> ch;
				file.get(ch);
				i++;
				if ( !( i < ByteLengthOfInput ) ) break;
				bit=0;
			}
			while( bitt( ch, bit ) )
			{
				if ( flag == 0 )
				{
					if ( longest_run < run ) longest_run = run;
					run = 0;
				}
				flag = 1;
				if ( bit >= 8 ) 
				{
					//file >> ch;
					file.get(ch);
					i++;
					if ( !( i < ByteLengthOfInput ) ) break;
					bit=0;
					continue;
				}
				run++;
				//ch /= 2;
				bit++;
			}
			while( !( bitt( ch, bit ) ) )
			{
				if ( flag == 1 )
				{
					if ( longest_run < run ) longest_run = run;
					run = 0;
				}
				flag = 0;
				if ( bit >= 8 ) 
				{
					//file >> ch;
					file.get(ch);
					i++;
					if ( !( i < ByteLengthOfInput ) ) break;
					bit=0;
					continue;
				}
				run++;
				//ch /= 2;
				bit++;
			}
		}

		if ( longest_run >= run_groesse ) 
		{
			longest_run_final = longest_run;
			return FALSE;
		}
		else 
		{
			longest_run_final = longest_run;
			return TRUE;
		}
	}
	file.close();
	return FALSE;
}

void Long_Run_Test::test()
{
	Set_result(longrun( infile, longrun_lang)); //Wenn longrun == TRUE ist auch test_result auf TRUE gestellt
}

//////////////////////////////////////////////////////////////////////
// Runs_Test Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Runs_Test::Runs_Test()
{
	runlang = 3;
	def_param = 2;
	degr = 2;
}

Runs_Test::~Runs_Test()
{

}

void Runs_Test::test()
{
	BOOL SuccessFlag = TRUE;

	Set_degr((2 * runlang) - 2);
	CStdioFile file;
	file.Open(infile, CFile::modeRead);
	ASSERT(file.GetLength() < ULONG_MAX);
	unsigned long ByteLengthOfInput = (unsigned long)file.GetLength();
	file.Close();

	unsigned long anf = 0, bis = 0; // Neue Variabeln für RandomTest Sequenz???
	UINT alle = 0;
	int lang_test = 0;

	if ((def == TRUE) && (fips == FALSE))
	{
		offs = 0;
		testlen = ByteLengthOfInput;
	}

	if (fips == TRUE)
	{
		offs = 0;
		testlen = 2500;
	}

	// Initialisirung von dem Zuffalsgenerator
	srand( (unsigned) time(NULL) );

	if (def2 == TRUE) lang_test=10;
	else if (def2 == FALSE) lang_test=1;

	for (int TestDurchlaeufe=0; TestDurchlaeufe<lang_test ;TestDurchlaeufe++)
	{
		if ( def2 == TRUE ) //Benutzen wir Random Offset und Testlänge ???
		{
			anf = ((unsigned) (offs + (rand() % RAND_RANGE))) % ByteLengthOfInput;
			if(def == FALSE)
			{
				bis = ((unsigned) (testlen + (rand() % RAND_RANGE))) % ByteLengthOfInput;
			}
			else
			{
				bis = ((unsigned) (testlen - (rand() % RAND_RANGE))) % ByteLengthOfInput;
			}
	
			while((anf + bis) > ByteLengthOfInput)
			{
				anf = ((unsigned) (offs + (rand() % RAND_RANGE))) % ByteLengthOfInput;
				if ( def == FALSE ) bis = ((unsigned) (testlen + (rand() % RAND_RANGE))) % ByteLengthOfInput;
				else bis = ((unsigned) (testlen - (rand() % RAND_RANGE))) % ByteLengthOfInput;
			}
		}

		else 
		{
			anf = offs;
			bis = testlen;
		}

		double summe1 = 0, summe2 = 0;
			// summe1 und summe2 sind in der Formel mit dem man der test-statistischen Wert rechnet
		for (long i=1; i <= runlang; i++)
		{	
			// zaehle_luck_block - die Funktion die Lucken und Blöcke zählt
			double b = zaehle_luck_block( i, TRUE, infile, anf, bis );
			double l = zaehle_luck_block( i, FALSE, infile, anf, bis );
			double e = erwartet( bis, (int) i);

			summe1 += (((b - e) * (b - e))/e); // sqrt(block-"erwartete Häufigkeit")/"erwartete Häufigkeit"
			summe2 += (((l - e) * (l - e))/e);
		}
		Set_test_ergeb( summe1 + summe2 );
		vergleiche_test_ergeb();

		if (TRUE != (SuccessFlag &= GetResult())) break;
		else continue;

	}
}

long Runs_Test::zaehle_luck_block(long lang, BOOL was, const char *infile, unsigned int offset, unsigned int bis)
{
	int temp = 0, zahl = 0;
	long flong = 0;
	unsigned char ch = '\0';

	ifstream File( infile, ios::in | ios::binary );

	if (File && File.seekg(offset))
	{
		unsigned i = 0;

		UINT flag = 1;
		UINT bit = 0; //An welchen BIT in der Datei sind wir gerade?
		char Temp_Char; //Temporary char weil mann den "Orginal ch" immer durch 2 teilt
		while ( i < bis )
		{
			if ( flag == 1 ) 
			{
				//File >> ch;
				File.get((char&)ch);
				Temp_Char = ch;
				flag = 0;
			}
			if (was)
			{
				while( bitt (ch, bit) )
				{
					bit++;
					temp++;
					if (bit >= 8)
					{
						i++;
						if (!(i < bis))
						{
							if (temp == lang) zahl++;
							return zahl;
						}
						//File >> ch;
						File.get((char&)ch);
						bit = 0;
						Temp_Char = ch;
						if ( bitt (ch, bit) ) continue;
						else break;
					}
					ch = Temp_Char;
				}
				if (bit >= 8)
				{
					i++;
					if (!(i < bis))
					{
						if (temp == lang) zahl++;
						return zahl;
					}
					//File >> ch;
					File.get((char&)ch);
					bit = 0;
					Temp_Char = ch;
					continue;
				}

				if ( temp == lang ) 
				{	
					zahl++;	
					temp = 0;
				}

				while( !(bitt (ch, bit)) )
				{
					temp = 0;
					//ch /= 2;
					bit++;

					if (bit >= 8)
					{
						i++;
						if (!(i < bis))
						{
							if (temp == lang) zahl++;
							return zahl;
						}
						//File >> ch;
						File.get((char&)ch);
						bit = 0;
						Temp_Char = ch;
						continue;
					}
					ch = Temp_Char;
				}
			}

			else
			{
				while( !(bitt (ch, bit)) )
				{
					bit++;
					temp++;
					if (bit >= 8)
					{
						i++;
						if (!(i < bis))
						{
							if (temp == lang) zahl++;
							return zahl;
						}
						//File >> ch;
						File.get((char&)ch);
						bit = 0;
						Temp_Char = ch;

						continue;
					}
					ch = Temp_Char;

				}

				if ( temp == lang ) 
				{	
					zahl++;	
					temp = 0;
				}

				if (bit >= 8)
				{
					i++;
					if (!(i < bis))
					{
						if (temp == lang) zahl++;
						return zahl;
					}
					//File >> ch;
					File.get((char&)ch);
					bit = 0;
					Temp_Char = ch;
					continue;
				}
		
				while( bitt (ch, bit) )
				{
					temp = 0;
					bit++;
					if (bit >= 8)
					{
						i++;
						if (!(i < bis))
						{
							if (temp == lang) zahl++;
							return zahl;
						}
						//File >> ch;
						File.get((char&)ch);
						bit = 0;
						Temp_Char = ch;

						continue;
					}
					ch = Temp_Char;
				}
			}
		}
	}
	return zahl;
}

double Runs_Test::erwartet(long folge, int i) //Die Funktion die erwartete Run-Verteilung ausrechnet
{
	double n1 = ( (folge*8) - i + 3 );
	double n2 = 2;
		for(int j=0; j < (i+1); j++) n2 *= 2;
	return n1/n2;
}


//////////////////////////////////////////////////////////////////////
// Poker_Test Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Poker_Test::Poker_Test()
{
	degr = 7;
	def_param = 14.070;
}

Poker_Test::~Poker_Test()
{

}

void Poker_Test::test()
{
//////////////////////////////////////////////
	UINT TestDurchlaeufe=0;

	//long tmp2 = 0;
	//UINT alle = 0;

	BOOL SuccessFlag = TRUE;

	CStdioFile file;
	file.Open(infile, CFile::modeRead);
	ASSERT(file.GetLength() < ULONG_MAX);
	unsigned long ByteLengthOfInput = (unsigned long)file.GetLength();
	file.Close();

	if ((def == TRUE) && (fips == FALSE))
	{
		offs = 0;
		testlen = ByteLengthOfInput;
	}

	if (fips == TRUE)
	{
		offs = 0;
		testlen = 2500;
	}

	unsigned char ch;
	unsigned n=0, lang_test, feld_platz=0;
	unsigned long anf, bis; // Neue Variabeln für RandomTest Sequenz???

	// Initialisirung von dem Zuffalsgenerator
	srand( (unsigned) time(NULL) );


	ifstream read(infile, ios::in | ios::binary );

	if (def2 == TRUE) lang_test=10;
	else if (def2 == FALSE) lang_test=1;

	for (TestDurchlaeufe=0; TestDurchlaeufe<lang_test; TestDurchlaeufe++)
	{
		if ( def2 == TRUE ) //Benutzen wir Random Offset und Testlänge ???
		{
			anf = ((unsigned) (offs + (rand() % RAND_RANGE))) % ByteLengthOfInput;
			bis = ((unsigned) (testlen + (rand() % RAND_RANGE))) % ByteLengthOfInput;

			while(((anf + bis) >= ByteLengthOfInput) || (bis <= 12))
			{
				anf = 0; bis = 0;
				anf = ((unsigned) (offs + (rand() % RAND_RANGE))) % ByteLengthOfInput;
				bis = ((unsigned) (testlen + (rand() % RAND_RANGE))) % ByteLengthOfInput;
			}
		}

		else 
		{
			anf = offs;
			bis = testlen;
		}

		if (anf < 0) anf = 0;

		n = 0;
		//null=0; eins = 0;
		int bit;
		double tupel_block = 0; //Zahl der untersuchten nicht überlappenden Blöcke
		ASSERT(tupel < 32);
		unsigned potenz = 1; //Potenz der Nummer 2

		long z[POKER_MUSTER] = { 0 }; //hier speichert man die Anzahl der Poker-Muster
//		z = new int[tuper-1] = 0;

		if (read.seekg(anf) && read)
		{
			//read >> ch;
			read.get((char&)ch);
			bit = 0;

			while(n < bis) //Zahlen von Einzen und Nullen
			{
	
				feld_platz=0;

				for(unsigned i=0;i<tupel;i++) //Da untersucht man einzel Tupel_blocks nach einem "Poker-Muster"
										 //Wenn ein Muster gufunden ist ist der Anzahl der bestimmten Musterzahl um 1 erhöht
				{
					potenz = 1;
					for (unsigned pot = 0; pot < i; pot++) potenz *= 2;
					feld_platz += ( ( bitt( ch, bit ) ) * (potenz)); //Hier rechnet man Pokermuster Platz
					//ch /= 2;
					bit++;
					if (bit == 8)
					{
						//read >> ch;
						read.get((char&)ch);
						n++;
						if (n==bis) break;
						bit = 0;
					}
				}
				z[feld_platz]++;
				tupel_block++;
				if (tupel_block == (((bis*8)-(bis*8)%tupel)/tupel)) break;
			}
		}
		else //Wenn Positionierung in Datei nicht erfolgt, dann Schleife fortsetzen
		{
			anf = 0;
			SuccessFlag = TRUE;
			continue;
		}


		potenz = 1;
		for (unsigned pot = 0; pot < tupel; pot++) potenz *= 2;

		double summe = 0;
		for (unsigned i = 0; i < potenz; i++) summe += (z[i] * z[i]);

		Set_test_ergeb( ((potenz/tupel_block) * summe) - tupel_block );	//Nach den Formel (2^tupellänge/n-ipple * (summe[i=von 0 bis tupellänge-1](sqrt(n-ipple_i)) - n-ipple)
																		//n-ipple - die Anzahl der nicht überlappenden Dipple, Tripple, usw.
		tmp_Test_Ergebnis = Get_test_ergeb();
		vergleiche_test_ergeb();

		if (TRUE != (SuccessFlag &= GetResult())) break;
		else continue;
	}

	/*if (alle == TestDurchlaeufe) Set_result(TRUE);
	else Set_result(FALSE);*/

}

// Modifizierte Entropie Funktion (aus der crypt.h und crypt.cpp)
double Entropy_mod( const char* infile, SymbolArray &text )
{
	LoadText( infile, text );
	if ( !CheckTextSize( text ) ) return 0;
	CWaitCursor WCursor;
	NGram distr(text);
	return distr.Entropie();
	HIDE_HOUR_GLASS
}

// Modifizierte binäre Entropie Funktion (aus der crypt.h und crypt.cpp)
double EntropyBin_mod(const char *infile, const char *OldTitle)
{
    SymbolArray text(IdConv);
	return Entropy_mod( infile, text );
}

