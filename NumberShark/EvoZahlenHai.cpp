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

#include "StdAfx.h"
#include "EvoZahlenHai.h"
#include "MFC-ZahlenHai.h"

#include "zahl.h"
#include "math.h"

//Konstruktor
EvoZahlenHai::EvoZahlenHai(void)
{
	upperLimit = 0;
	numbers = 0;
	currentRound = 0;	
	pointsplayer = 0;
	pointscomputer = 0;
	usablenumbersleft = 0;
	computerNumbers.n=0;
	computerNumbers.pNumbers=0;

	optimalNumbers = 0;
	optimalNumbersCount = 0;
}
//Konstruktor
//Wenn 
EvoZahlenHai::EvoZahlenHai(CString serStr)
{
	int i;
	//upperLimit
	upperLimit = getNextIntValue(serStr);
		
	//currentRound
	currentRound = getNextIntValue(serStr);
	
	//pointsPlayer
	pointsplayer = getNextIntValue(serStr);
	
	//pointsComputer
	pointscomputer = getNextIntValue(serStr);
		
	//numbers
	numbers = new int[upperLimit+1];
	
	for(i=1; i<=upperLimit; i++)
	{
		if(i < upperLimit)
		{
			numbers[i] = getNextIntValue(serStr, ',');
		}
		else
		{
			numbers[i] = getNextIntValue(serStr);
		}
	}
		
	//usableNumbersLeft
	usablenumbersleft = getNextIntValue(serStr);
	
	//optimalNumbersCount
	optimalNumbersCount = getNextIntValue(serStr);
		
	//optimalNumbers
	optimalNumbers = new int[upperLimit+1];
	
	for(i=1; i<=upperLimit; i++)
	{
		if(i < upperLimit)
		{
			optimalNumbers[i] = getNextIntValue(serStr, ',');
			if(optimalNumbers[i] == -1)//letztes Element des bisher optimalen Spiels
			{
				optimalNumbers[i] = getNextIntValue(serStr);//
                break;		
			}
		}
		else
		{
			optimalNumbers[i] = getNextIntValue(serStr);
		}
	}

	//computerNumbers.n
	computerNumbers.n = getNextIntValue(serStr);;
	
	//computerNumbers.pnumbers

	computerNumbers.pNumbers = new int[upperLimit+1];
	
	for(i=1; i<=upperLimit; i++)
	{
		
		if(i < upperLimit)
		{
			computerNumbers.pNumbers[i] = getNextIntValue(serStr, ',');
			if(computerNumbers.pNumbers[i] == -1)//letztes Element des bisher optimalen Spiels
			{
				computerNumbers.pNumbers[i] = getNextIntValue(serStr);//
                break;		
			}
		}
		else
		{
			computerNumbers.pNumbers[i] = getNextIntValue(serStr);
		}
	}
}
//Destruktor
EvoZahlenHai::~EvoZahlenHai(void)
{
	delete numbers;
	delete computerNumbers.pNumbers;

	delete optimalNumbers;
}

//Die einzelnen Zahlen die sich der Computer nach jedem Zug genommen werden zurückgegeben um sie dann in die Liste zu schreiben
ComputerNumbers EvoZahlenHai::getComputerNumbers()
{
	return computerNumbers;
}
//wird für die maxPoints benötigt
//array kopieren
EvoZahlenHai& EvoZahlenHai::operator=(const EvoZahlenHai& Spiel)
{
	upperLimit = Spiel.upperLimit;
	pointsplayer = Spiel.pointsplayer;
	pointscomputer = Spiel.pointscomputer;
	
	delete numbers;
	numbers = new int [upperLimit+1];
	
	for(int i=1; i<=upperLimit; i++)
	numbers[i] = Spiel.numbers[i];

	delete optimalNumbers;
	optimalNumbers = new int[upperLimit+1];
	for(int j=1; j<=upperLimit; j++)
		optimalNumbers[j] = Spiel.optimalNumbers[j];
	optimalNumbersCount = Spiel.optimalNumbersCount;
	
	return *this;
}
//Start der Runde
int EvoZahlenHai::startRound(int playerchoice)
{
	//Wenn der Computer keine Teiler findet dann wird die gewählte Zahl dem Computer zugeschrieben
	if(takeComputerNumber(playerchoice)==ZAHLENHAI_KEINE_TEILER_GEFUNDEN)
	{
		numbers[playerchoice] = COMPUTER;
		currentRound++;	
		pointsPlayerComputer();
		return ZAHLENHAI_KEINE_TEILER_GEFUNDEN;
	}
	//gezogene Zahl wird auf PLAYER gesetzt
    else
	{
		numbers[playerchoice] = PLAYER;
		currentRound++;
		pointsPlayerComputer();

		optimalNumbers[++optimalNumbersCount] = playerchoice;
	}
	
	return playerchoice;
}
//Wenn der Spieler seine Zahl gewählt hat, durchsucht der Computer alle noch vorhanden Zahlen nach Teilern 
//von der vom Spieler gewählten Zahl
int EvoZahlenHai::takeComputerNumber(int playerchoice)
{
	delete computerNumbers.pNumbers;
	computerNumbers.n = 0;
	computerNumbers.pNumbers = new int[upperLimit+1];
	memset(computerNumbers.pNumbers, 0, upperLimit);

	bool found = false;

	for(int i=1; i<(upperLimit/2 + 1); i++)
	{
		if (numbers[i]==FREE)
		{	//wenn ein Teiler gefunden wurde wird dieser Zahl der Status COMPUTER gegeben
			if( (!(playerchoice%i)) && playerchoice != i)
			{
				numbers[i]=COMPUTER;
				found = true;
				//Kann entfallen wenn der Spieler die Knopf "Maximale Punkte" gedrückt hat
				//Zahlen die sich der Computer wählt werden in die struct geschrieben
				computerNumbers.pNumbers[computerNumbers.n++] = i;
			}
			
		}
		else continue;
	}

    if(found) return ZAHLENHAI_TEILER_GEFUNDEN;
	
	return ZAHLENHAI_KEINE_TEILER_GEFUNDEN;
}
//wird für die maxPoints benötigt
//Die aktuelle Punktezahl des Spieler wird zu allen restlichen noch vorhanden Zahlen(alle die FREE sind) dazu addiert und zurückgegeben
int EvoZahlenHai::maxPossiblePointsPlayer()
{
	int freeNumbers = 0;
	
	int primeBorder = upperLimit/2 + 1;

	for(int i=1; i<=upperLimit; i++)
	{
		if(numbers[i]==FREE && !(i >= primeBorder && isPrime(i)))
			freeNumbers +=i;
	}

	int maxPossiblePointsPlayer = freeNumbers + pointsplayer;

	return maxPossiblePointsPlayer;
}
// Die Anzahl der Zahl die der Spieler noch drücken kann wird errechnet und ausgegeben
int EvoZahlenHai::usableNumbersLeft()
{
	int count = 0;
	
	for(int i=1; i<=upperLimit; i++)
		if(numbers[i]==FREE) count++;
		
    return count;
}
//Initialisierung
void EvoZahlenHai::init(int limit)
{	
	upperLimit = limit;
	
	// special case: INIT
	if(!upperLimit)
	{
		delete numbers;
		numbers = 0;
		currentRound = 0;
		pointsplayer = 0;
		pointscomputer = 0;

		delete optimalNumbers;
		optimalNumbersCount = 0;

		return;
	}
	
	//Wenn der Speicher für numbers schon belegt ist, wird dieser wieder freigegeben
	delete numbers;
	numbers = new int[upperLimit+1];
	//alle Zahlen zwischen 1 und der Obergrenze werden auf FREE gesetzt
	for(int i=1; i<=upperLimit; i++)
		numbers[i] = FREE;

	delete optimalNumbers;
	optimalNumbers = new int[upperLimit+1];
	for(int j=1; j<=upperLimit; j++)
		optimalNumbers[j] = 0;
	optimalNumbersCount = 0;

	pointsplayer = 0;
	pointscomputer = 0;
	currentRound = 0;
}
//Die Gesamtpunktezahlen von Spieler und Hai werden errechnet
void EvoZahlenHai::pointsPlayerComputer()
{
	pointsplayer = 0;
	pointscomputer = 0;	
	
	for(int i=0; i<=upperLimit; i++)
	{
		if(numbers[i]==PLAYER)
			pointsplayer +=i;
		if(numbers[i]==COMPUTER)
			pointscomputer +=i;
	}
}

// Falls keine teilbaren Zahlen mehr vorhanden sind, werden die restlichen Zahlen dem Computerzugeschrieben
void EvoZahlenHai::assignFreeNumbersToComputer()
{
	for(int i=1; i<=upperLimit; i++)
		if(numbers[i]==FREE) 
		{
			numbers[i]=COMPUTER;
			getComputerNumbers();
		}
	pointsPlayerComputer();
}

//Die Eingabe des Spielers wird auf Gültigkeit überprüft, ist die Zahl innerhalb der Grenzen und ist sie FREE
bool EvoZahlenHai::checkPlayerNumber(int playerchoice)
{
	if(numbers[playerchoice]==PLAYER || numbers[playerchoice]==COMPUTER)
		return false;
	
	return true;
}

//Das Spiel ist beendet, wenn keine Zahl mehr auf FREE gesetzt ist
bool EvoZahlenHai::gameFinished()
{
	for(int i=1; i<=upperLimit; i++)
		if(numbers[i] == FREE) return false;
		
	return true;
}

// Nach jedem Zug wird kontrolliert ob noch teilbare Zahlen, mit den entsprechenden Teilern vorhanden sind.
bool EvoZahlenHai::factorLeft()
{
	int i=0;
	int j=0;
	
	for(i=1; i<=upperLimit; i++)
		for(j=1; j<=upperLimit; j++)
			if(j!=i && numbers[i]==FREE && numbers[j]==FREE)
				if(!(j%i))
					return false;
	return true;
}

//Bester Weg
CString EvoZahlenHai::getBestWay()
{
	int n;
	int *nos;

	CString bestWay;
	char bestWayBuffer[10];

	n = getOptimalNumbersCount();
	nos = getOptimalNumbers();	

	for(int i=1; i<=n; i++)
	{
		_itoa(nos[i], bestWayBuffer, 10);
		bestWay += bestWayBuffer;
		if(i < n)
			bestWay += ", ";
	}

	return bestWay;
}
//Speichern der aktuellen Werte der Suche in einem String
CString EvoZahlenHai::toString()
{
	int i;
	CString writeBuffer;
	char charWriteBuffer[25];

	//upperLimit
	_itoa(upperLimit, charWriteBuffer, 10);
	writeBuffer += charWriteBuffer;
	writeBuffer += " | ";

	//currentRound
	_itoa(currentRound, charWriteBuffer, 10);
	writeBuffer += charWriteBuffer;
	writeBuffer += " | ";

	//pointsPlayer
	_itoa(pointsplayer, charWriteBuffer, 10);
	writeBuffer += charWriteBuffer;
	writeBuffer += " | ";

	//pointsComputer
	_itoa(pointscomputer, charWriteBuffer, 10);
	writeBuffer += charWriteBuffer;
	writeBuffer += " | ";
	
	//numbers
	for(i=1; i<=upperLimit; i++)
	{
		_itoa(numbers[i], charWriteBuffer, 10);
		writeBuffer += charWriteBuffer;
		if(i < upperLimit)
			writeBuffer += " , ";
	}
	writeBuffer += " | ";
	
	//usableNumbersLeft
	_itoa(usablenumbersleft, charWriteBuffer, 10);
	writeBuffer += charWriteBuffer;
	writeBuffer += " | ";

	//optimalNumbersCount
	_itoa(optimalNumbersCount, charWriteBuffer, 10);
	writeBuffer += charWriteBuffer;
	writeBuffer += " | ";
	
	//optimalNumbers
	for(i=1; i<=optimalNumbersCount; i++)
	{
		_itoa(optimalNumbers[i], charWriteBuffer, 10);
		writeBuffer += charWriteBuffer;
		if(i < optimalNumbersCount)
			writeBuffer += " , ";
	}
	writeBuffer += " | ";

	//computerNumbers.n
	_itoa(computerNumbers.n, charWriteBuffer, 10);
	writeBuffer += charWriteBuffer;
	writeBuffer += " | ";
	//computerNumbers.pnumbers
	for(i=1; i<=computerNumbers.n; i++)
	{
		_itoa(computerNumbers.pNumbers[i], charWriteBuffer, 10);
		writeBuffer += charWriteBuffer;
		if(i <upperLimit-1)
			writeBuffer += " , ";
	}
	writeBuffer += " | ";
	
	return writeBuffer;
}
/*
//Setzten der Tausenderpunkte
char* EvoZahlenHai::itoa_fmt(unsigned long ul_num)
{
	char pc_str[1000];
	unsigned long str_length, str_ptr;
	char * str, c_pt;

	// pre-compute the length of the output string
	str_length = (!ul_num) ? 2 : (unsigned long)floor(log((double)ul_num)/log(10.0))+2;
	str_length += (str_length-2)/3;
	str = new char [str_length];

	str_ptr = str_length-1;
	
	// write num blocks
	do {
		str_ptr = (str_ptr >= 3) ? str_ptr-3 : 0;
		itoa((int)(ul_num % 1000), str + str_ptr, 10);
		ul_num /= 1000;
		if (str_ptr) str_ptr--;
	} while (ul_num);

	// write 'dots'
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PT,pc_str,STR_LAENGE_STRING_TABLE);
	c_pt = pc_str[0];
	do {
		str_ptr += strlen(str+str_ptr);
		if ( str_ptr < str_length -1 ) str[str_ptr] = c_pt;
	} while ( str_ptr < str_length-1 );

	return str;
}*/
CString EvoZahlenHai::setSeperator(__int64 value)
{

	CString valueStr="";
	 CString seperator="";
	 char Buffer[100];
	 seperator.LoadString(IDS_STRING_PT);
	 valueStr=_i64toa(value,Buffer,10);
	 int length=valueStr.GetLength();
	 for(int i=length-3; i>0;i=i-3)
	 {
		 if(length>3)
			 valueStr.Insert(i,seperator);
	 }
	 
	 return valueStr;
}