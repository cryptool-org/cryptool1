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

#pragma once

// Potentielle Rückgabewerte für Funktion takeComputerNumber()
const int ZAHLENHAI_TEILER_GEFUNDEN					= 1; // IDENTISCH MIT BOOLSCH 'TRUE'
const int ZAHLENHAI_KEINE_TEILER_GEFUNDEN			= 0; // IDENTISCH MIT BOOLSCH 'FALSE'

#define STR_LAENGE_STRING_TABLE 1000

enum StatusNumber
{
	FREE,
	COMPUTER,
	PLAYER
};

struct ComputerNumbers 
{
	int n; //Anzahl der Zahlen die der Hai jede Runde zieht

	int *pNumbers; // Zeiger auf Numbers
};

class EvoZahlenHai
{
	ComputerNumbers computerNumbers;
		
	int *numbers;
	int currentRound;
	int pointsplayer;
	int pointscomputer;
	int usablenumbersleft;
	
	int *optimalNumbers;
	int optimalNumbersCount;
			
public:
	EvoZahlenHai(void);
	~EvoZahlenHai(void);

	EvoZahlenHai(CString);
	int upperLimit;
	CString toString();
	CString getBestWay();
	
	ComputerNumbers getComputerNumbers();
	EvoZahlenHai& operator=(const EvoZahlenHai& Spiel);

	bool checkPlayerNumber(int);	//Eingabe des Spielers wird auf Gültigkeit kontrolliert
	bool factorLeft(); // Jede Runde wird kontrolliert ob noch teilbare Zahlen vorhanden sind
	bool gameFinished();	//Wenn keine Zahl mehr auf FREE gesetzt ist, ist das Spiel beendet

	void pointsPlayerComputer();	//Die Punkte von Spieler und Hai werden zu der jeweiligen Gesamtpunktezahl zusammenaddiert
	void assignFreeNumbersToComputer();	// Wenn keine teilbaren Zahlen mehr frei sind erhält der Computer automatisch die restlichen zahlen
	void init(int);		//Initialiesierung

	int startRound(int);	//wird bei jeder Auswahl einer Zahl gestartet
	int maxPossiblePointsPlayer();	//aktuelle Punktestand vom Spieler + Summe aller verbliebenen Zahlen wird mit der aktuellen Höchstpunktezahl verglichen
	int getCurrentRound(){return currentRound;};	//die aktuelle Runde wird erfasst
	int getPointsPlayer(){return pointsplayer;};	//die Punkte vom Spieler werden erfasst
	int getPointsComputer(){return pointscomputer;};	//die Punkte vom Computer werden erfasst
	int *getNumbers() {return numbers;};	//vom Spieler getätigte Zahl
	int getUpperLimit() {return upperLimit;};	//die vom Spieler gewünschte Obergrenze für das Spiel
	int takeComputerNumber(int);	//Der Hai sucht sich die Teiler der vom Spieler gewählten Zahl heraus	
	int usableNumbersLeft();// Die Anzahl der Zahlen die dem Spieler noch zur Verfügung stehen wird angezeigt
	int getOptimalNumbersCount() { return optimalNumbersCount; }; // Die Anzahl der beim "optimalen Spiel" gewählten Zahlen
	int *getOptimalNumbers() { return optimalNumbers; } // vom Spieler im "optimalen Spiel" gewählte Zahlen

	//char* itoa_fmt (unsigned long ul_num);

	CString setSeperator(__int64 value);

	
};
