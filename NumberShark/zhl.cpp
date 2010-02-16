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
#include "zhl.h"
#include "math.h"
#include "stdlib.h"

#define MAX_LAENGE 100

// nur fürs debuggen
#include <iostream>
using namespace std;
// bis hier


// Mögliche Verbesserung 1: 
// Der Best-Case für die Zahlen, die der Spieler erhält, ist i.A. noch 
// viel zu hoch. Der Spieler bekommt i.A. weniger als die größten x/2 freien Zahlen.
// Dies hängt irgendwie mit den Teilern der noch vorhandenen Zahlen zusammen.
// Also: Der Spieler erhält die größten x/2-y Zahlen. Was ist y?
// Eine Berechnung von Äquivalenzklassen würde vermutlich helfen.
// An dieser Stelle kann noch verbessert werden (mehr und frühere Abbrüche).

// Mögliche Verbesserung 2: 
// Des weiteren kann der Algorithmus noch verbessert werden, wenn die Zahlen 
// in einer "besseren" Reihenfolge ausprobiert werden. 
// Es müssen für alle möglichen Kandidaten Vorabberechnungen gemacht werden,
// und dann in einer entsprechenden Reihenfolge verwendet werden.
// Idee 1: Greedy: Größtes Delta, also <Zahl Spieler> - <Zahlen Zahlenhai>
// Idee 2: Wenigste Zahlen für Zahlenhai (vermutlich nicht so gut???)
// Idee 3: Kombination von 1 und 2: Von den wenigsten Zahlen für den Zahlenhai
//         die Kombination mit dem größten Delta auswählen (auf den ersten Blick gut)
// Das sollte auch zu mehr und früheren Abbrüchen führen. 

// Mögliche Verbesserung 3: 
// Zusätzlich abbrechen, wenn der Zahlenhai mit den x/2+y (was ist y - hängt auch von 
// den Teilern ab) kleinsten Werten schon mehr Punkte als im besten gefundenen Fall hat.
// Wurde ausprobiert, bringt nichts: die Berechnung wird dadurch nicht früher abgebrochen 

// Grundlegender Ansatz für den Algorithmus:
// - Brute Force mit Abbruch, wenn selbst im Best Case nicht mehr die bis dato 
//   gefundene Lösung erreicht werden kann. 
// - Es gibt ein Datenfeld, auf dem gearbeitet wird (Backtracking-Algorithmus)
// - Ein weiteres Datenfeld enthält die bis zum jeweiligen Zeitpunkt optimale Folge
// - Es wird nur solange gesucht, bis mit der aktuellen Folge auch im Best Case 
//   keine bessere Lösung als die vorhandene mehr möglich ist. 
//   Das reduziert den Suchraum gewaltig.
//   Hier ist auch am meisten Potenzial zur Optimierung 
//   (siehe Methode zusatzZahlenSummeSpieler und deren Aufruf, Abbruchkriterium 2)
//   - ist bestimmt noch nicht ganz ausgeschöpft.
// - Möglichst viel vorab einmal berechnen und speichern:
//   - Die möglichen Teiler aller Zahlen werden vorab einmal berechnet
//   - Zur Berechnung von zu eliminierenden Zahlen wird 
//   - Mehrmals verwendete komplexe Berechnungen nur einmal ausführen
// - Keine dynamische Speicherplatzallokation im Algorithmus
// Durch diesen Ansatz ist die Grenze der erfolgreichen Berechnung in annehmbarer Zeit
// nach hinten verschoben worden, aber ab einem Zeitpunkt explodiert der Zustandsraum 
// dennoch - vermutlich probleminhärent.

// Hinweise zur Reduktion des Suchraumes:
// http://www.research.att.com/~njas/sequences/A019312
// http://www.research.att.com/~njas/sequences/a019312.txt
// - Graphen einzeln betrachten, es sind i. A. mehrere, bringt das etwas?
// Erster Zug: Größte Primzahl
// Zweiter Zug: oft Größtes Quadrat (stimmt das?) 
// Problem dabei: Was ist, wenn die Wurzel wieder viele Teiler hat, 
// z.B. 64 -> 8,4,2 zum Zahlenhai


zhl::zhl(unsigned short n)
{
	anzahlZahlen = n;

	gesamtsumme = anzahlZahlen*(anzahlZahlen+1)/2;
	summeZahlenhai = 0;
	summeSpieler = 0;

	wegOptimalLaenge = 0;
	wegOptimalSummeZahlenhai = gesamtsumme;
	wegOptimalSummeSpieler = 0;

	anzahlZahlenGewaehlt = 0;
	anzahlZahlenZusaetzlich = 0;

	unsigned short i, j;

	// Speicher anlegen
	// zahlen[0] wird nicht verwendet!
	zahlen = new werteZahlen[anzahlZahlen+1];
	wegAktuell = new unsigned short[anzahlZahlen+1];
	wegOptimal = new unsigned short[anzahlZahlen+1];
	teiler = new unsigned short*[anzahlZahlen+1];
	unsigned int laenge = __min((int)(2*ceil(sqrt((double)anzahlZahlen))), MAX_LAENGE); 
	// sollte reichen: (int)(2*ceil(sqrt((double)anzahlZahlen)))
	// Kommentar zur Auswahl der Länge:
	// Ist viel zu hoch: bei n=30000 besitzt die Zahl 27720 die meisten Teiler mit 96, 
	// angelegt werden ungefähr 350 (ist aber kein Problem, da einmaliger Aufwand!)

	for (i=1; i<=anzahlZahlen; i++)
	{
		teiler[i] = new unsigned short[laenge];
	}

	unsigned short andererTeiler;
	for (i=1; i<=anzahlZahlen; i++)
	{
		zahlen[i] = frei;
		wegAktuell[i] = 0;
		wegOptimal[i] = 0;

		// teiler und Anzahl der Teiler initialisieren
		teiler[i][0] = 0;
		for (j=2; j<=(unsigned short)floor(sqrt((double)i)); j++)
		{
			if (!(i%j))
			{
				// j teilt i ohne Rest <=> j ist Teiler von i
				andererTeiler = i/j;
				assert(i==j*andererTeiler);

				teiler[i][0]++;
				teiler[i][teiler[i][0]] = j;

				if (andererTeiler != j)
				{
					// gegebenenfalls den anderen Teiler mit aufnehmen
					teiler[i][0]++;
					teiler[i][teiler[i][0]] = andererTeiler;
				}
			}
		}
		// Zahl selber hinzufuegen
		if (i != 1)
		{
			teiler[i][0]++;
			teiler[i][teiler[i][0]] = i;
		}
	}

/*	// debug ausgabe
	unsigned short zahlMaxTeiler = 0;
	unsigned short maxTeiler = 0;
	for (i=1; i<=anzahlZahlen; i++)
	{
		cout << i << ": " << teiler[i][0] << " - ";
		for (j=1; j<=teiler[i][0]; j++)
		{
			cout << teiler[i][j] << " ";
		}
		cout << endl;
		if (teiler[i][0] > maxTeiler)
		{
			maxTeiler = teiler[i][0];
			zahlMaxTeiler = i;
		}
	}
	cout << "Maximale Anzahl Teiler (von " << zahlMaxTeiler << "): " << maxTeiler+1 << endl;
*/
/*	Ausgabe für n=10:
	n eingeben (2 <= n <= 30000): 10
	1: 0 -
	2: 1 - 2
	3: 1 - 3
	4: 2 - 2 4
	5: 1 - 5
	6: 3 - 2 3 6
	7: 1 - 7
	8: 3 - 2 4 8
	9: 2 - 3 9
	10: 3 - 2 5 10
	Maximale Anzahl Teiler (von 6): 4
*/
	konstellationen = 0;
}

zhl::~zhl(void)
{
	// Speicher wieder freigeben
	delete[] zahlen;
	for (unsigned int i=1; i<=anzahlZahlen; i++)
		delete[] teiler[i];
	delete[] teiler;
	delete[] wegAktuell;
	delete[] wegOptimal;
}

void zhl::loesungenSuchen(void)
{
	// Als erstes hoechste Primzahl auswaehlen
	unsigned short teiler[2] = {1,1}; // {anzahl, einziger Teiler}
	unsigned short rueckgaengig[MAX_LAENGE];
	rueckgaengig[0] = 0; // zaehlen der Elemente im ersten Element

	zuSpielerAusgewaehlt(maxPrime(anzahlZahlen), teiler, rueckgaengig);
	
	// alle primzahlen >= n/2 kommen weg
	zahlenZuZahlenhai(rueckgaengig);

	// rekursiv Lösungen suchen
	loesungenSuchenRek(1);

	assert(1 <= rueckgaengig[0]);
	assert(1 == rueckgaengig[1]);
	assert(1 == anzahlZahlenGewaehlt);
}

void zhl::loesungenSuchenRek(unsigned short stufe)
{
	// stufe nur zur Überprüfung der Konsistenz vorhanden!
	// kann später gelöscht werden
	assert(stufe == anzahlZahlenGewaehlt);

	int i, j;

	// Abbruchkriterium 1 überprüfen
	// gibt es überhaupt noch freie Felder
	// falls nein: eine Lösung wurde gefunden
	if (anzahlZahlenGewaehlt + anzahlZahlenZusaetzlich == anzahlZahlen)
	{
		assert (summeZahlenhai + summeSpieler == gesamtsumme);
		for (j=1; j<=anzahlZahlen; j++)
		{
			assert (frei != zahlen[j]);
		}

		// Vergleich mit bisherigem Optimum
		if (wegOptimalSummeSpieler < summeSpieler)
		{
			// Optimum neu setzen
			wegOptimalSummeSpieler = summeSpieler;
			wegOptimalSummeZahlenhai = summeZahlenhai;
			wegOptimalLaenge = anzahlZahlenGewaehlt;
			for (j=0; j<wegOptimalLaenge; j++)
			{
				wegOptimal[j] = wegAktuell[j];
			}
/*			// debug ausgabe:
			cout << "Neues Optimum " << wegOptimalLaenge << " gefunden: " 
				<< "Spieler: " << wegOptimalSummeSpieler 
				<< ", Zahlenhai: " << wegOptimalSummeZahlenhai << endl;
			for (j=0; j<wegOptimalLaenge; j++)
			{
				cout << wegOptimal[j] << " ";
			}
			cout << "\n**********" << endl;
*/
		}
/*		// debug ausgabe
		else
		{
			cout << "Kein neues Optimum gefunden: " 
				<< "Spieler: " << summeSpieler 
				<< ", Zahlenhai: " << summeZahlenhai
				<< "\n**********" << endl;
		}
*/	}
	else
	{
		unsigned short rueckgaengig[MAX_LAENGE];

		// Hier kommt die Auswahl, welches freie Element genommen werden soll, hin
		// siehe "Mögliche Verbesserung 2"
		// Dann muss über ein Feld iteriert werden, nicht einfach von anzahlZahlen bis 2

		for (i=anzahlZahlen; i>=2; i--)
		{
			if (frei == zahlen[i])
			{
				rueckgaengig[0] = 0; // zaehlen der Elemente im ersten Element

/*				// debug ausgabe
				cout << "1: Vor auswahl, Stufe = " << stufe << ", i = " << i << endl;
				cout << "zahlen: ";
				for (j=1; j<=anzahlZahlen; j++)
				{
					cout << zahlen[j] << " ";
				}
				cout << endl;
				cout << "rueckgaengig:";
				for (j=0; j<=rueckgaengig[0]; j++)
				{
					cout  << " " << rueckgaengig[j];
					if (0==j) cout << ":";
				}
				cout << endl;
				cout << "-----" << endl;
*/
				// Zahlen bei beiden eintragen
				// Rückgabe false => Kein Wert für Zahlenhai => rückgängig und abbrechen
				if (zuSpielerAusgewaehlt(i, teiler[i], rueckgaengig))
				{
					// jetzt der Zahlenhai
					zahlenZuZahlenhai(rueckgaengig);

/*					// debug ausgabe
					cout << "2: Vor rekursion, Stufe = " << stufe << ", i = " << i << endl;
					cout << "zahlen: ";
					for (j=1; j<=anzahlZahlen; j++)
					{
						cout << zahlen[j] << " ";
					}
					cout << endl;
					cout << "rueckgaengig:";
					for (j=0; j<=rueckgaengig[0]; j++)
					{
						cout  << " " << rueckgaengig[j];
						if (0==j) cout << ":";
					}
					cout << endl;
					cout << "-----" << endl;
*/
					// Abbruchkriterium 2 überprüfen
					// Kann eine Lösung, die besser als die momentan beste gefundene überhaupt noch gefunden werden?
					// Der Zahlenhai bekommt mindestens die kleinsten (x+1)/2 freien Zahlen
					// Der Spieler bekommt höchstens die größten x/2 freien Zahlen
// Bringt nichts:
//					if ((zusatzZahlenSummeZahlenhai() + summeZahlenhai < wegOptimalSummeZahlenhai) && 
//						(zusatzZahlenSummeSpieler() + summeSpieler > wegOptimalSummeSpieler)    )
					if (zusatzZahlenSummeSpieler() + summeSpieler > wegOptimalSummeSpieler)
					{
						loesungenSuchenRek(stufe+1);
					}

/*					// debug ausgabe
					cout << "3: Vor rueckgaengig machen, Stufe = " << stufe << ", i = " << i << endl;
					cout << "zahlen: ";
					for (j=1; j<=anzahlZahlen; j++)
					{
						cout << zahlen[j] << " ";
					}
					cout << endl;
					cout << "rueckgaengig:";
					for (j=0; j<=rueckgaengig[0]; j++)
					{
						cout  << " " << rueckgaengig[j];
						if (0==j) cout << ":";
					}
					cout << endl;
					cout << "-----" << endl;
*/				}

				// Änderungen in Zahlen rückgängig machen
				zahlen[i] = frei;
				summeSpieler -= i;
				for (j=1; j<=rueckgaengig[0]; j++)
				{
					assert(zahlenhai == zahlen[rueckgaengig[j]]);
					zahlen[rueckgaengig[j]] = frei;
					summeZahlenhai -= rueckgaengig[j];
				}
				anzahlZahlenGewaehlt--;
				anzahlZahlenZusaetzlich -= rueckgaengig[0];
				assert (anzahlZahlenZusaetzlich >= 0);
				assert(stufe == anzahlZahlenGewaehlt);

/*				// debug ausgabe
				cout << "4: Nach rueckgaengig machen, Stufe = " << stufe << ", i = " << i << endl;
				cout << "zahlen: ";
				for (j=1; j<=anzahlZahlen; j++)
				{
					cout << zahlen[j] << " ";
				}
				cout << endl;
				cout << "rueckgaengig:";
				for (j=0; j<=rueckgaengig[0]; j++)
				{
					cout  << " " << rueckgaengig[j];
					if (0==j) cout << ":";
				}
				cout << endl;
				cout << "-----" << endl;
*/			}
		}
	}
}

// Der Spieler bekommt höchstens die größten floor(x/2) freien Zahlen
inline unsigned long zhl::zusatzZahlenSummeSpieler(void)
{
	assert (0 <= anzahlZahlenGewaehlt + anzahlZahlenZusaetzlich);
	assert (anzahlZahlenGewaehlt + anzahlZahlenZusaetzlich <= anzahlZahlen);
	// es können nicht 0 oder 1 Zahl übrigbleiben
	// 0: anderer Zweig oben
	// 1: gehört dem Zahlenhai

	short anz = (anzahlZahlen - anzahlZahlenGewaehlt - anzahlZahlenZusaetzlich)/2;
	int i = anzahlZahlen;
	unsigned long summe = 0;
	while (anz > 0)
	{
		if (frei == zahlen[i])
		{
			summe += i;
			anz--;
		}
		i--;
	}
	assert (i >= ((anzahlZahlen - anzahlZahlenGewaehlt - anzahlZahlenZusaetzlich - 1) / 2) );
	return summe;
}

/*
// Der Zahlenhai bekommt mindestens die kleinsten ceil(x/2) freien Zahlen
inline unsigned long zhl::zusatzZahlenSummeZahlenhai(void)
{
	assert (0 <= anzahlZahlenGewaehlt + anzahlZahlenZusaetzlich);
	assert (anzahlZahlenGewaehlt + anzahlZahlenZusaetzlich <= anzahlZahlen);
	// es können nicht 0 oder 1 Zahl übrigbleiben
	// 0: anderer Zweig oben
	// 1: gehört dem Zahlenhai

	short anz = (anzahlZahlen - anzahlZahlenGewaehlt - anzahlZahlenZusaetzlich + 1)/2;
	int i = 2;
	unsigned long summe = 0;
	while (anz > 0)
	{
		if (frei == zahlen[i])
		{
			summe += i;
			anz--;
		}
		i++;
	}
	assert (i <= ((anzahlZahlen + anzahlZahlenGewaehlt + anzahlZahlenZusaetzlich + 1) / 2));
	return summe;
}
*/
// alle Zahlen dem Zahlenhai zuordnen, die nicht mehr verwendet werden können
// Bedingung: 
// 1. Besitzt keine noch zu verwendenden Teiler 
//    Wird überprüft für Zahlen zwischen ceil((n+1)/2) und n
// 2. Teilt keine noch zu verwendende Zahl (und hat auch keinen zu verwendenden Teiler)
//    Wird überprüft für 2..floor(n/2)
// (Natürlich müssen die Zahlen in beiden Fällen noch frei sein.)
inline void zhl::zahlenZuZahlenhai(unsigned short rueckgaengig[])
{
	static unsigned short i=0, j=0; 
	static bool teilerGefunden = false;

	// 1.
	for (i=anzahlZahlen; i>=anzahlZahlen/2+1; i--)
	{
		if (frei == zahlen[i])
		{
			teilerGefunden = false;
			for (j=1; j<teiler[i][0] && !teilerGefunden; j++)
			{
				if (frei == zahlen[teiler[i][j]])
				{
					teilerGefunden = true;
				}
			}
			if (!teilerGefunden)
			{
				zuZahlenhai(i);
				rueckgaengig[0]++;
				assert(rueckgaengig[0]<MAX_LAENGE);
				rueckgaengig[rueckgaengig[0]] = i;
			}
		}
	}
	
	// 2.
	for (i=anzahlZahlen/2; i>=2; i--)
	{
		if (frei == zahlen[i])
		{
			teilerGefunden = false;
			for (j=1; j<teiler[i][0] && !teilerGefunden; j++)
			{
				if (frei == zahlen[teiler[i][j]])
				{
					teilerGefunden = true;
				}
			}
			if (!teilerGefunden)
			{
				// prüfe, ob die Zahl eine andere teilt
				for(j=2*i; j<=anzahlZahlen && !teilerGefunden; j+=i)
				{
					if (frei == zahlen[j])
					{
						teilerGefunden = true;
					}
				}
			}
			if (!teilerGefunden)
			{
				zuZahlenhai(i);
				rueckgaengig[0]++;
				assert(rueckgaengig[0]<MAX_LAENGE);
				rueckgaengig[rueckgaengig[0]] = i;
			}
		}
	}
}

// der Spieler hat eine Zahl ohne Teiler ausgewählt
// die geht direkt an den Zahlenhai, der Spieler bekommt nichts
inline void zhl::zuZahlenhaiAusgewaehlt(unsigned short i)
{
	assert (frei == zahlen[i]);
	zahlen[i] = zahlenhai;
	summeZahlenhai += i;
	wegAktuell[anzahlZahlenGewaehlt] = i;
	anzahlZahlenGewaehlt++;
	konstellationen++;
}

// eine Zahl wird ausgewählt, die direkt geht an den Zahlenhai geht, 
// wurde aber nicht vom Spieler ausgewählt (und somit nicht im Weg gespeichert)
inline void zhl::zuZahlenhai(unsigned short i)
{
	assert (frei == zahlen[i]);
	zahlen[i] = zahlenhai;
	summeZahlenhai += i;
	anzahlZahlenZusaetzlich++;
}

// Der Spieler hat eine Zahl ausgewählt, die mindestens einen Teiler besitzt
// Diese geht an den Spieler, die Teiler an den Zahlenhai
// Rückgabe: true, falls der Zahlenhai mindestens eine Zahl erhält, 
//			 false bei 0 Zahlen => Schritt zurücknehmen
inline bool zhl::zuSpielerAusgewaehlt(unsigned short i, unsigned short teiler[], unsigned short rueckgaengig[])
{
	assert (frei == zahlen[i]);
	zahlen[i] = spieler;
	summeSpieler += i;
	wegAktuell[anzahlZahlenGewaehlt] = i;
	anzahlZahlenGewaehlt++;
	konstellationen++;

	bool wertFuerZahlenhai = false;
	// alle freien teiler an den zahlenhai
	static unsigned short j=1;
	for (j=1; j<=teiler[0]; j++)
	{
		assert(!(i%teiler[j]));
		if (frei == zahlen[teiler[j]])
		{
			zuZahlenhai(teiler[j]);
			rueckgaengig[0]++;
			assert(rueckgaengig[0]<MAX_LAENGE);
			rueckgaengig[rueckgaengig[0]] = teiler[j];
			wertFuerZahlenhai = true;
		}
	}

	return wertFuerZahlenhai;
}

//ist die Zahl z eine Primzahl?
inline bool zhl::isPrime(unsigned short z)
{
	return 1 == teiler[z][0];
}

// kopiert aus Zahlenhai 1.1.0 (und abgeaendert), zahl.cpp:
//die höchste Primzahl in dem gewünschten Zahlenbereich wird herausgesucht
unsigned short zhl::maxPrime(unsigned short upperLimit)
{
	for(unsigned short z=upperLimit; z>(upperLimit/2); z--)
	{       
		if(isPrime(z))
			return z;
	}
	return 1;
}

// flomar, 02/16/2010
UINT zhl::maxPointsSearch(LPVOID param)
{
	int upperLimit = (int)((LPVOID)(param));

	// create the zhl object
	zhl zhlObject(upperLimit);
	// start the search
	zhlObject.loesungenSuchen();

	// calculate the score of the best possible way
	unsigned short score = 0;
	for(int i=0; i<zhlObject.wegOptimalLaenge; i++) {
		score += zhlObject.wegOptimal[i];
	}

	return score;
}