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

//wird für die maxPoints benötigt

#include "stdafx.h"
#include "afxwin.h"

#include "resource.h"
#include <time.h>
#include "math.h"
#include "zahl.h"
#include "MFC-ZahlenHaiDlg.h"

// flomar, 02/23/2010
extern SearchStatus searchStatus;

__int64 numberOfRounds;

bool ContinueSearchFromFile;

//int globalPoints;
int maxEndPoints;
int endTime;

int doSearch;

CMFCZahlenHaiDlg zahlenHaiDlg;
EvoZahlenHai optimalesSpiel;

CString bestWay;

struct item {
	int index;
	EvoZahlenHai Spiel;
};

__int64 getNextInt64Value(CString &str, char Sep)
{
	int index = str.Find(Sep);
	if( index > 0 )
	{
		__int64 z =_atoi64(str);
		str.Delete(0, index+1);
		return z;
	}
	return -1;
}

int getNextIntValue(CString &str, char Sep)
{
	int index = str.Find(Sep);
	if( index > 0 )
	{
		int z =atoi(str);
		str.Delete(0, index+1);
		return z;
	}
	return -1;
}
BOOL readSearchState(int &startTime, __int64 &numberOfRounds, int &StackPointer, item *Stack, int upperLimit )
{
	CStdioFile file;
	CString title;
	char charUpperLimit[6];
		
	title.Empty();
	CString buffer="";
	buffer.LoadString(IDS_SEARCH1);
	_itoa(upperLimit, charUpperLimit, 10);
	title +=buffer;
	title += charUpperLimit;
	buffer.LoadString(IDS_SEARCH2);
	title +=buffer;
	//char Buffer[100];

	int openOk = file.Open(title,CFile::modeRead);
	
	//ASSERT(openOk);
	if(openOk)
	{
        CString Line;
		file.ReadString(Line);
		startTime= getNextIntValue(Line);
		numberOfRounds = getNextInt64Value(Line);
		StackPointer=0;
		StackPointer = getNextIntValue(Line);
	
		for(int i =0; i<=StackPointer; i++)
		{
			file.ReadString(Line);
			Stack[i].index=getNextIntValue(Line);
			EvoZahlenHai tmp(Line);
			Stack[i].Spiel=tmp;
		}

		file.Close();
	}
	return openOk;
}
CString writeSearchValue(__int64 numberOfRounds, int StackPointer, int startTime)
{
	char charWriteBuffer[25];
	CString stringBuffer;
	stringBuffer.Empty();
	
	//Verstrichene Zeit
	int stopTime = clock();
	endTime = stopTime - startTime;
	endTime = endTime/1000;
	_itoa(endTime, charWriteBuffer, 10);
	stringBuffer += charWriteBuffer;
	
	stringBuffer+= " | ";
	_ui64toa(numberOfRounds, charWriteBuffer, 10);
	stringBuffer+= charWriteBuffer;
	stringBuffer+= " | ";
	_itoa(StackPointer, charWriteBuffer, 10);
	stringBuffer+= charWriteBuffer;
	stringBuffer+= " | ";
	stringBuffer+="\r\n";
	
   return stringBuffer;
}

void writeStack(item *Stack, int StackPointer, CStdioFile &file) 
{
	for(int i=0; i<=StackPointer; i++)
	{
		CString writeBuffer=Stack[i].Spiel.toString();
		char charIndex[6];
		_itoa(Stack[i].index, charIndex, 10);
		file.WriteString(charIndex);
		file.WriteString(" | " +writeBuffer+"\r\n");
	}
}

void writeSearchState(item *Stack, int StackPointer, int upperLimit, __int64 numberOfRounds, int startTime)
{
	CStdioFile file;
	CString title;
	char charUpperLimit[6];

	title.Empty();
	CString buffer="";
	buffer.LoadString(IDS_SEARCH1);
	_itoa(upperLimit, charUpperLimit, 10);
	title +=buffer;
	title += charUpperLimit;
	buffer.LoadString(IDS_SEARCH2);
	title +=buffer;

	int openOk = file.Open(title, CFile::modeCreate | CFile::modeWrite);
	if(openOk!=0)
	{
		ASSERT(openOk);

		file.WriteString(writeSearchValue(numberOfRounds, StackPointer, startTime));
		writeStack(Stack, StackPointer,file);

		file.Close();
	}
	/*else
	{
		// keine Schreibrechte
		CString message="";
		message.LoadString(IDS_NO_SEARCH);
		AfxMessageBox(message,IDOK,MB_ICONINFORMATION);
	}*/
	
}

void SucheNRek(EvoZahlenHai &Spiel, int startTime)
{
	item *Stack;
	CStdioFile file;
	int openStatus;
	openStatus=file.Open("Test",CFile::modeCreate | CFile::modeReadWrite);
	doSearch=1;
	if(openStatus==0)
	{
		/*	LPVOID lpMsgBuf;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf,0,NULL);
		CString title="Ein Fehler ist aufgetreten.";
		MessageBox(NULL,(LPCTSTR)lpMsgBuf,(LPCTSTR)title,MB_ICONWARNING|MB_OK);
		LocalFree( lpMsgBuf );*/

		//Ermitteln des Verzeichnisses in dem sich die Zahlenhai.exe befindet
		CString sharkExe = GetCommandLine();
		int pos = sharkExe.ReverseFind( '\\'); // FIXME --> Thomas
		sharkExe = sharkExe.Mid(0, pos+1);

		//Erstellen der Fehlermeldung wenn keine Schreibrechte vorhanden sind
		char charUpperLimit[6];
		CString title;
		title.Empty();
		CString buffer="";
		buffer.LoadString(IDS_SEARCH1);
		_itoa(Spiel.getUpperLimit(), charUpperLimit, 10);
		title +=buffer;
		title += charUpperLimit;
		buffer.LoadString(IDS_SEARCH2);
		title +=buffer;
		CString message="";
		//message.LoadString(IDS_NO_SEARCH);
		message.Format(IDS_NO_SEARCH,title,sharkExe);

		int answer = AfxMessageBox(message,IDOK,MB_ICONINFORMATION);
		if(answer==IDCANCEL)
		{
			doSearch=0;
			return;
		}
		doSearch=1;
	}
	else
	{
		file.Close();
		_unlink("Test");	
		doSearch=1;
	}

	Stack = new item[Spiel.getUpperLimit()];
	Stack[0].index = 1;
	Stack[0].Spiel = Spiel;

	int StackPointer = 0;
	int upperLimit = Spiel.getUpperLimit();
	
	StackPointer = 0;
	 if (readSearchState(startTime, numberOfRounds, StackPointer, Stack, upperLimit))
	 {
	     //StartTime anpassen 
	 }
	
	 writeSearchState(Stack, StackPointer, upperLimit, numberOfRounds, startTime);

	do {

		if (Stack[StackPointer].index <= upperLimit)
		{
			//Kontrolle ob die ausgewählte Zahl noch FREE ist 
			if(Stack[StackPointer].Spiel.checkPlayerNumber(Stack[StackPointer].index))
			{
				EvoZahlenHai EvoZahlenHaiCopy;
				//Inhalt von Spiel wird in EvoZahlenHaiCopy kopiert
				EvoZahlenHaiCopy = Stack[StackPointer].Spiel;
				//Mit den kopierten Daten in EvoZahlenHaiCopy wird die Runde gestartet
				EvoZahlenHaiCopy.startRound(Stack[StackPointer].index);
				//Abfrage ob sich ein Voranschreiten noch lohnt oder nicht
				Stack[StackPointer].index++;

				if(Stack[StackPointer].Spiel.maxPossiblePointsPlayer() > maxEndPoints)
				{	
					numberOfRounds++;

					if ( 0 == (numberOfRounds % 10000000) )
					{
						//Für jeden Wert den index annehmen kann gibt es ein extra Spiel, welches, in Verbindung mit dem Index gespeichert werden
						//muss
						numberOfRounds--;
						Stack[StackPointer].index--;
						writeSearchState(Stack, StackPointer, upperLimit, numberOfRounds, startTime);
						Stack[StackPointer].index++;
						numberOfRounds++;
					}

					ASSERT(StackPointer+1<upperLimit);
					
					Stack[++StackPointer].Spiel = EvoZahlenHaiCopy;
					Stack[StackPointer].index = 1;
				}
			}
			else 
				Stack[StackPointer].index++;
		}
		else
		{
			if (Stack[StackPointer].Spiel.getPointsPlayer() > maxEndPoints)
			{
				if(Stack[StackPointer].Spiel.getPointsPlayer() > optimalesSpiel.getPointsPlayer())
					optimalesSpiel = Stack[StackPointer].Spiel;
				maxEndPoints=Stack[StackPointer].Spiel.getPointsPlayer();
			}
			StackPointer--;
		}
		if(searchStatus == ABORTED)
			StackPointer=-1;
	}
	while (StackPointer >= 0);
	// wenn keine Zahl mehr FREE ist, wird die ermittelte höchste Punktezahl mit vorherigen
	//Ergebnissen verglichen. Die höhere Zahl wird behalten
	
	delete []Stack;
}

//ist die Zahl z eine Primzahl?
bool isPrime(int z)
{
	if(z <=1)
		return false;
	for(int i = 2; i<=(int)(floor(sqrt((double)z))); i++)
	{
		if(!(z%i)) return false;
	}
	return true;
}

//die höchste Primzahl in dem gewünschten Zahlenbereich wird herausgesucht
int maxPrime(int upperLimit)
{
	for(int z=upperLimit; z>(upperLimit/2); z--)
	{       
		if(isPrime(z))
			return z;
	}
	return 1;
}

//Funktion die für die Suche nach der maximalen Punktezahl gestartet werden wird
int maxPoints(int upperLimit)
{	
	CWaitCursor wait;
	maxEndPoints = 0;
	
	EvoZahlenHai Spiel;
			

	int startTime = clock();
	Spiel.init(upperLimit);
	numberOfRounds=0;
	ContinueSearchFromFile = false;

	Spiel.startRound(maxPrime(upperLimit));

	//Suche(Spiel);
	SucheNRek(Spiel, startTime);

	//Ende der Zeitmessung
	int stopTime = clock();
	endTime = stopTime - startTime;//startTime muss gegebenfalls durch die ausgelesene Zeit ersetzt werden
	endTime = endTime/1000;

	int n;
	int *nos;
	
	n = optimalesSpiel.getOptimalNumbersCount();
	nos = optimalesSpiel.getOptimalNumbers();	

	char bestWayBuffer[10];
	bestWay.Empty();

	for(int i=1; i<=n; i++)
	{
		_itoa(nos[i], bestWayBuffer, 10);
		bestWay += bestWayBuffer;
		if(i < n)
			bestWay += " , ";
	}

	if(doSearch==0)
		maxEndPoints = -1;

	return maxEndPoints;
}

UINT maxPointsStatic(LPVOID param)
{
	int upperLimit = (int)((LPVOID)(param));

	CWaitCursor wait;
	maxEndPoints = 0;
	
	EvoZahlenHai Spiel;
			

	int startTime = clock();
	Spiel.init(upperLimit);
	numberOfRounds=0;
	ContinueSearchFromFile = false;
	//}

	Spiel.startRound(maxPrime(upperLimit));

	searchStatus = RUNNING;

	//Suche(Spiel);
	SucheNRek(Spiel, startTime);

	if(searchStatus != ABORTED)
		searchStatus = DONE;

	//Ende der Zeitmessung
	int stopTime = clock();
	endTime = stopTime - startTime;//startTime muss gegebenfalls durch die ausgelesene Zeit ersetzt werden
	endTime = endTime/1000;

	int n;
	int *nos;
	
	n = optimalesSpiel.getOptimalNumbersCount();
	nos = optimalesSpiel.getOptimalNumbers();	

	char bestWayBuffer[10];
	bestWay.Empty();

	for(int i=1; i<=n; i++)
	{
		_itoa(nos[i], bestWayBuffer, 10);
		bestWay += bestWayBuffer;
		if(i < n)
			bestWay += " , ";
	}

	//globalPoints = maxEndPoints;
	if(doSearch==0)
		maxEndPoints = -1;

	if(searchStatus == DONE) {
        zahlenHaiDlg.calculationResult(maxEndPoints, upperLimit);
	}
	return maxEndPoints;
}

__int64 getNumberOfRounds(){return numberOfRounds;}
int getTime(){return endTime;}
//Vorherige Version der Suche durch eine Rekursion
/*
void Suche(EvoZahlenHai &Spiel)
{
	//numberOfRounds und Suchtiefe müssen mit den Werten aus der Datein gesetzt werden, wenn diese geöffnet wurde
	numberOfRounds++;
	Suchtiefe++;

	int upperLimit = Spiel.getUpperLimit();
	
	for(int i=1 ; i<=upperLimit; i++)
	{
		//Kontrolle ob die ausgewählte Zahl noch FREE ist 
		if(Spiel.checkPlayerNumber(i))
		{
			
			EvoZahlenHai EvoZahlenHaiCopy;
			//Inhalt von Spiel wird in EvoZahlenHaiCopy kopiert
			EvoZahlenHaiCopy = Spiel;
			//Mit den kopierten Daten in EvoZahlenHaiCopy wird die Runde gestartet
			EvoZahlenHaiCopy.startRound(i);
			//Abfrage ob sich ein Voranschreiten noch lohnt oder nicht
			if(Spiel.maxPossiblePointsPlayer() > maxEndPoints)
			{	
				//Programm Suche startet wieder von vorn bis keine Zahl mehr FREE ist
				Suche(EvoZahlenHaiCopy);
			}
		}
	}
	// wenn keine Zahl mehr FREE ist, wird die ermittelte höchste Punktezahl mit vorherigen
	//Ergebnissen verglichen. Die höhere Zahl wird behalten
 	if (Spiel.getPointsPlayer() > maxEndPoints)
	{
		if(Spiel.getPointsPlayer() > optimalesSpiel.getPointsPlayer())
			optimalesSpiel = Spiel;

		maxEndPoints=Spiel.getPointsPlayer();
	}
	Suchtiefe--;
}
*/