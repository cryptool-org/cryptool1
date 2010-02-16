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

// Klasse ZahlenHaiLoesungen

#pragma once
#include "assert.h"

class zhl
{
public:
	// summe aller zahlen von 1 bis n
	unsigned long gesamtsumme;
	// Summe der Zahlen des Zahlenhais bei der aktuell optimalen Lösung
	unsigned long wegOptimalSummeZahlenhai;
	// Summe der Zahlen des Spielers bei der aktuell optimalen Lösung
	unsigned long wegOptimalSummeSpieler;
	// Anzahl der vom Spieler ausgewählten Zahlen in der Berechnung
	unsigned long konstellationen;
	// Gewählte Zahlen des Spielers bei der aktuell optimalen Lösung
	unsigned short* wegOptimal;
	// Anzahl der Zahlen bei der aktuell optimalen Lösung
	unsigned short wegOptimalLaenge;
private:
	// n =
	unsigned short anzahlZahlen;
	// Anzahl der vom Spieler gewählten Zahlen bei der aktuell berechneten (Teil-)Lösung
	// Diese können sowohl beim Zahlenhai als auch beim Spieler sein
	unsigned short anzahlZahlenGewaehlt;
	// Anzahl der vom zusätzlich verwendeten Zahlen bei der aktuell berechneten (Teil-)Lösung
	// Diese ist beim Zahlenhai 
	unsigned short anzahlZahlenZusaetzlich;
	// Summe der Zahlen des Zahlenhais bei der aktuell berechneten (Teil-)Lösung
	unsigned long summeZahlenhai;
	// Summe der Zahlen des Spielers bei der aktuell berechneten (Teil-)Lösung
	unsigned long summeSpieler;
	// Datentyp für zahlen, siehe unten
	enum werteZahlen{frei=0, zahlenhai=1, spieler=2};
	// Feld in dem der Besitzer der Zahlen (= entsprechender Index) markiert wird
	werteZahlen* zahlen;
	// Gewählte Zahlen des Spielers bei der aktuell berechneten (Teil-)Lösung
	unsigned short* wegAktuell;
	// teiler[i][0] = Anzahl der Teiler von i (ohne 1, einschliesslich i)
	// teiler[i][1]...teiler[i][teiler[i][0]]: die Teiler von i (ohne 1, einschliesslich i)
	unsigned short** teiler;

public:
	zhl(unsigned short);
	void loesungenSuchen();
	~zhl(void);
private:
	void loesungenSuchenRek(unsigned short);
	unsigned long zusatzZahlenSummeSpieler(void);
	//unsigned long zusatzZahlenSummeZahlenhai(void);
	void zahlenZuZahlenhai(unsigned short[]);
	void zuZahlenhaiAusgewaehlt(unsigned short);
	void zuZahlenhai(unsigned short);
	bool zuSpielerAusgewaehlt(unsigned short, unsigned short[], unsigned short[]);
	bool isPrime(unsigned short);
	unsigned short maxPrime(unsigned short);

public:
	// flomar, 02/16/2010
	static UINT maxPointsSearch(LPVOID param);
};
