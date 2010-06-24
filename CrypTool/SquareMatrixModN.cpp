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
// Klasse SQUARE_MATRIX
//////////////////////////////////////////////////////////////////
// Klasse fuer eine quadratische Matrix mit invertiermoeglichleit
// modulo einer Zahl
//
// Definitionen der Methoden der Klasse
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrypToolApp.h"
#include "SquareMatrixModN.h"

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#include <iomanip.h>
#else
#include <iostream>
#include <iomanip>
using namespace std;
#endif

#include <stdlib.h>

CSquareMatrixModN::CSquareMatrixModN(int dimension, int alphabetgroesse) :
   mat(0),
   dim(0),
   modul(0),
   feldbreite(0)
{
   initialize( dimension, alphabetgroesse );
}

BOOL CSquareMatrixModN::initialize( int dimension, int alphabetgroesse )
{
   if ( dim )
   {
      destroy();
   }

   if ( dimension < 0 ) 
      dimension = 0;
   if ( alphabetgroesse < 1 )
      alphabetgroesse = 1;

	dim = dimension;
	modul = alphabetgroesse;

   if ( dim <= 0 )
      return FALSE;

	if (modul < 10)
	{
		feldbreite = 2;
	}
	else if (modul < 100)
	{
		feldbreite = 3;
	}
	else if (modul < 1000)
	{
		feldbreite = 4;
	}
	else
	{
		feldbreite = 5;
	}
	
	// Speicher fuer Matrix anlegen
	mat = new long*[dim];
	
	int i;
	for (i=0; i<dim; i++)
	{
		mat[i] = new long[dim];
	}
	
	// Matrix initialisieren
	for (i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
		{
			mat[i][j] = 0;
		}
	}
	
	// Inverse Elemente berechnen
	inverse_elemente = new int[modul];
	for (i=0; i<modul; i++)
	{
		inverse_elemente[i] = 0; // wir nehmen an, dass kein inverses Element existiert
	}
	
	// Jetzt werden alle inversen Elemente modulo modul gesucht. 
	// Wird ein Element gefunden, so wird dies im Feld bei beiden eingetragen.
	for (i=1; i<modul; i++) // Fuer i=0 existiert kein inverses Element
	{
		if (! inverse_elemente[i]) // noch nicht gefunden -> also suchen
		{
			// Inverses Element suchen
			int j;
			for (j=1; (j<modul) && (((i*j)%modul) != 1); j++); 
			if (((i*j)%modul) == 1)
			{
				inverse_elemente[i] = j;
				inverse_elemente[j] = i;
			}
		}
	}
	
	iaZeileVektor = new int[modul];
	iaLinearKombination1 = new int[modul];
	iaLinearKombination2 = new int[modul];
	iaFaktoren = new int[modul];

	iaHilfsfeld_hilfsmat = new int[dim];
	iaHilfsfeld_mat1 = new int[dim];

#ifdef _DEBUG
	TRACE("Element:");
	for (i=0; i<modul; i++)
	{
		TRACE("%3d",i);
	}
	TRACE("\nInverse:");
	for (i=0; i<modul; i++)
	{
		TRACE("%3d",inverse_elemente[i]);
	}
	TRACE("\n");
#endif

   return TRUE;
}

void  CSquareMatrixModN::destroy()
{
	for (int i=0; i<dim; i++)
	{
		delete[] mat[i];
	}
	
	delete[] mat;
	delete[] inverse_elemente;
	
   delete[] iaZeileVektor;
	delete[] iaLinearKombination1;
	delete[] iaLinearKombination2;
	delete[] iaFaktoren;
	
	delete[] iaHilfsfeld_hilfsmat;
	delete[] iaHilfsfeld_mat1;

   dim = 0;
}

CSquareMatrixModN::~CSquareMatrixModN()
{
   if ( dim )
      destroy();
}

// Konvertierung eines Eintrages in den Bereich [0:modul-1]
long CSquareMatrixModN::convert_long (long zahl) const
{
	if (zahl < 0)
	{
		zahl %= modul;  // nach [-(modul-1):0] transformieren
		zahl += modul;  // nach [1:modul] transformieren
	}
	return zahl % modul;  // und noch normales modulo
}

// Konvertierung der aller Eintraege der Matrix nach [0:modul-1]
void CSquareMatrixModN::convert_mod ()
{
	for (int i=0; i<dim; i++)
		for (int j=0; j<dim; j++)
			mat[i][j] = convert_long(mat[i][j]);
}

// Operator, der einen Eintrag der Matrix liefert
long& CSquareMatrixModN::operator() (int zeile, int spalte)
{
	return mat[zeile][spalte];
}
long CSquareMatrixModN::operator() (int zeile, int spalte) const
{
	return mat[zeile][spalte];
}

// Dimension der Matrix zurueckgeben
int CSquareMatrixModN::get_dim (void) const
{
	return dim;
}

// Modul zurueckgeben
int CSquareMatrixModN::get_mod (void) const
{
	return modul;
}

// Feldbreite zurueckgeben
int CSquareMatrixModN::get_feldbreite (void) const
{
	return feldbreite;
}

// Feldbreite zurueckgeben
int CSquareMatrixModN::get_inverses_element (int element) const
{
	element = convert_long(element);
	ASSERT((0 <= element) && (element < modul));
	return inverse_elemente[element];
}


// Ueberladener Ausgabeoperator
ostream& operator<< (ostream &os, const CSquareMatrixModN &m)
{
	for (int i=0; i<m.get_dim(); i++)
	{
		os << " |";
		for (int j=0; j<m.get_dim(); j++)
		{
			os << setw(m.get_feldbreite()) << m(i,j);
		}
		os << " |\n";
	}
	
	return os;
}

// Ueberladener Eingabeoperator
istream& operator>> (istream& is, CSquareMatrixModN &m)
{
	for (int i=0; i<m.get_dim(); i++)
	{
		for (int j=0; j<m.get_dim(); j++)
		{
			is >> m(i,j);
		}
	}
	
	m.convert_mod();
	
	return is;
}

// Ueberladener Zuweisungsoperator
CSquareMatrixModN& CSquareMatrixModN::operator= (const CSquareMatrixModN &m)
{
	int min = (m.get_dim() < dim) ? m.get_dim() : dim;
	
	for (int i=0; i<min; i++)
	{
		for (int j=0; j<min; j++)
		{
			mat[i][j] = m(i,j);
		}
	}
	return (*this);
}

// Berechnen einer Determinanten oder Adjunkten
// Parameter: Matrix, Felder mit Indices der zu beruecksichtigenden 
// Zeilen und Spalten und Variable mit der Laenge dieser Felder
long CSquareMatrixModN::determinante (int *zeilen,
                                  int *spalten,
                                  int laenge) const
{
	long det = 0;
	int i,
		j;
	
	if (laenge == 0)
	{
		return 1;
	}
	else
	{
		// In spaltenneu werden die Indizes der Spalten
		// gespeichert, die zur Berechnung der Adjunkten fuer den aktuellen
		// Eintrag betrachtet werden muessen
		// Fuer die Zeilen wird dies gemacht durch Uebergabe der Adresse
		// des zweiten Elements des Vektors zeilen, d. h. zeilen+1,
		// da wir nach der ersten Zeile entwickeln und daher alle ausser
		// der ersten in der Rekursion betrachten muessen.
		
		int *spaltenneu;
		
		spaltenneu = new int[laenge-1];
		
		// Wir entwickeln immer nach der ersten Zeile
		for (i=0; i<laenge-1; i++)
		{
			spaltenneu[i] = spalten[i+1];
		}
		
		// Jetzt die Adjunkten berechnen
		for (j=0; j<laenge; j++)
		{
			// Fuer jeden neuen Spaltenvektor muss nur ein Eintrag geaendert
			// werden gegenueber dem Vorgaenger
			if (j >= 1)
			{
				spaltenneu[j-1] = spalten[j-1];
			}
			
			long rek_det = determinante(zeilen+1, spaltenneu, laenge-1);
			
			if ((j%2)==0)
			{
				det += (mat[zeilen[0]][spalten[j]] * rek_det);
			}
			else
			{
				det -= (mat[zeilen[0]][spalten[j]] * rek_det);
			}
			
			det = convert_long(det);
		}
		
		delete[] spaltenneu;
	}
	
	return det; // es gilt: 0 <= det < modul
}

// Invertieren modulo einer Zahl
// Ergebnis wird in mat1 zurueckgeliefert
BOOL CSquareMatrixModN::invert(CSquareMatrixModN *mat1) const
{
	// Matrix ausgeben
#ifdef _DEBUG
	for (int my_k=0; my_k<dim; my_k++)
	{
		for (int my_l=0; my_l<dim; my_l++)
		{
			TRACE("%3d ", mat[my_k][my_l]);
		}
		TRACE("\n");
	}
	TRACE("\n");
#endif

	if ( theApp.beginLog() )
	{
		theApp.log() << "\n C_SQUARE_MOD_N HILL MATRIX \n";
		theApp.log() << "DIM: " << 	dim << std::endl;
		for ( int i=0; i<dim; i++ )
		{
			for ( int j=0; j<dim; j++ )
				theApp.log() << mat[i][j] << " ";
			theApp.log() << std::endl;
		}
		theApp.endLog();
	}
	
	// Falls die Matrix mat1 andere Dimension hat, FALSE zurueckgeben
	if (mat1->get_dim() != dim)
	{
		return FALSE;
	}
	
	if (dim <= 4)
	{
		return invert_adjunkten_verfahren(mat1);
	}
	else
	{
		return invert_gauss_jordan(mat1);
	}
}

// Gauss-Jordan Verfahren zum Invertieren einer Matrix:
// ( hilfsmat | mat1 ) (Anfangs ist hilfsmat=mat und mat1 die Einheitsmatrix)
// Auf dieser Matrix werden Zeilenoperationen ausgefuehrt, bis mat die
// Einheitsmatrix ist oder dies nicht geht, also mat nicht invertierbar ist. 
BOOL CSquareMatrixModN::invert_gauss_jordan(CSquareMatrixModN *mat1) const
{
	int i,j,k,l;	// Laufvariablen: i,k=Zeilenindex, j,l=Spaltenindex
	
	int iZeileInvertierbaresElement;	// Falls ein invertierbares Element auf der Haupdiagonalen
										// existiert, gibt ... die entsprechende Zeile an.

	long **hilfsmat;
	// Hilfsmatrix anlegen und Werte aus mat kopieren
	hilfsmat = new long*[dim];
	
	for (i=0; i<dim; i++)
	{
		hilfsmat[i] = new long[dim];
	}
	
	// Matrix initialisieren
	for (i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
		{
			hilfsmat[i][j] = mat[i][j];
		}
	}
	
#ifdef _DEBUG
	int my_k,my_l;
	for (my_k=0; my_k<dim; my_k++)
	{
		for (my_l=0; my_l<dim; my_l++)
		{
			TRACE("%3d ", hilfsmat[my_k][my_l]);
		}
		TRACE("\n");
	}
	TRACE("\n");
#endif

	// Matrix mat1 mit der Einheitsmatrix initialisieren
	for (i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
		{
			(*mat1)(i,j) = (i==j) ? 1 : 0;
		}
	}
	
	// Es wird versucht, zeilenweise die folgende Form herzustellen
	// (x = beliebiger Wert)
	// ( 1 x x . x | x x x . x ) 
	// ( 0 1 x . x | x x x . x )
	// ( 0 0 1 . x | x x x . x )
	// ( ......... | ......... )
	// ( 0 0 0 . 1 | x x x . x )
	// i = aktuelle Zeile
	bool bNichtInvertierbar = false;
	for (i=0; (i<dim) && (! bNichtInvertierbar); i++)
	{
		// die Variablen werden fuer jede Zeile benoetigt, also neu initialisieren
		for (k=0; k<modul; k++)
		{
			iaZeileVektor[k] = SQ_MAT_LIN_KOMB_INIT;
			iaLinearKombination1[k] = SQ_MAT_LIN_KOMB_INIT;
			iaLinearKombination2[k] = SQ_MAT_LIN_KOMB_INIT;
		}

		// Enthaelt eine der noch nicht verwendeten Zeilen eine invertierbare Zahl
		bool bInvertierbareZahlGefunden = false;
		int iInversesElement;
		k=i;
		while ((k<dim) && (! bInvertierbareZahlGefunden))
		{
			ASSERT ((0 <= hilfsmat[k][i]) && (hilfsmat[k][i] < modul));

			// Wir merken uns die Zeile von jedem Wert hilfsmat[k][i]
			// die Zeile k in der Matrix im Feld (Wir merken uns immer die erste Zeile)
			if ( (iaZeileVektor[hilfsmat[k][i]] == SQ_MAT_LIN_KOMB_INIT) ) 
			{
				iaZeileVektor[hilfsmat[k][i]] = k;
			}

			iInversesElement = inverse_elemente[hilfsmat[k][i]];
			
			if (iInversesElement)
			{
				bInvertierbareZahlGefunden = true;
			}
			k++;
		}

		// Wurde ein invertierbares Element gefunden, ...
		if (bInvertierbareZahlGefunden)
		{
			// ... so ist k am Ende der Schleife einmal zu oft erhoeht worden.
			// (In k steht die Zeile mit dem invertierbaren Element.)
			iZeileInvertierbaresElement = k-1;
		}

		// Eventuell kann eine invertierbare Zahl nicht gefunden werden,
		// obwohl die Matrix invertierbar ist. Aus einer Linearkombination
		// verschiedener Zeilen koennen invertierbare Zahlen an der
		// entsprechenden Stelle hergestellt werden.
		// Vergleiche Angriff fuer das Hill Verfahren in hill.cpp
		//
		// Wir haben uns oben gemerkt (iaZeileVektor), welche Zahlen in der entsprechenden
		// Spalte zur Verfuegung stehen. Jetzt werden sukzessiv alle Linearkombinationen
		// gebildet. Dies geschieht durch Addition von jeweils zwei Werten.
		// iaZeileVektor wurde mit SQ_MAT_LIN_KOMB_INIT initialisiert. Wenn eine neue
		// Linearkombination gefunden worden ist, enthaelt der entsprechende Wert in 
		// iaZeileVektor den Wert SQ_MAT_LIN_KOMB_NEU.
		int iInvertierbaresElement = 0; // Wenn spaeter != 0, wurde ein Element gefunden.

		if (! bInvertierbareZahlGefunden)
		{
			ASSERT(iInversesElement == 0); 
			
			bool bNeuesElementGefunden = true;
			
			// Schleifenbedingungen:
			// 1: Abbruch sofort, wenn ein invertierbares Element gefunden worden ist. 
			// 2: Falls neue Elemente gefunden worden sind, sind die beiden for-Schleifen
			//    erneut auszufuehren, weil sich neue - vorher nicht vorhandene - 
			//    Linearkombinationen ergeben koennten.
			while ( (! iInversesElement) && (bNeuesElementGefunden))
			{
				bNeuesElementGefunden = false;
				
				// Bilden aller Linearkombinationen, dabei muss ein Element auch mit sich
				// selbst linearkombiniert werden.
				// Die Linearkombinationen werden durch sukzessive Addition zweier Zahlen gebildet.
				for (k=0; (k<modul) && (! iInversesElement); k++)
				{
					for (l=k; (l<modul) && (! iInversesElement); l++)
					{
						// Wurde ein neues Element gefunden ?
						// Wenn ja, merken, aus welchen beiden es linearkombiniert worden ist.
						// Bemerkung:
						// Es ist wichtig, dass sich kein Zyklus in den Linearkombinationen ergibt.
						// Dies ist aber sichergestellt, da im Feld iaZeileVektor nur dann
						// neue Eintraege gemacht werden, wenn es noch den Initialwert besitzt.
						if ( (iaZeileVektor[k] != SQ_MAT_LIN_KOMB_INIT) &&
							(iaZeileVektor[l] != SQ_MAT_LIN_KOMB_INIT) &&
							(iaZeileVektor[(k+l)%modul] == SQ_MAT_LIN_KOMB_INIT) )
						{
							bNeuesElementGefunden = true;
							
							iaZeileVektor[(k+l)%modul] = SQ_MAT_LIN_KOMB_NEU;
							iaLinearKombination1[(k+l)%modul] = k;
							iaLinearKombination2[(k+l)%modul] = l;
							
							// Ist dieses neu gefundene Element invertierbar ?
							iInversesElement = get_inverses_element((k+l)%modul);
							if (iInversesElement)
							{
								iInvertierbaresElement = (k+l)%modul;
							}
						}
					}
				}
			}
		}
		
#ifdef _DEBUG
		for (my_k=0; my_k<dim; my_k++)
		{
			for (my_l=0; my_l<dim; my_l++)
			{
				TRACE("%3d ", hilfsmat[my_k][my_l]);
			}
			TRACE("\n");
		}
		TRACE("\n");
#endif

#ifdef _DEBUG
		for (l=0; l<modul; l++)
		{
			TRACE("%2d ", l);
		}
		TRACE("\niaZeileVektor:\n");
		for (l=0; l<modul; l++)
		{
			TRACE("%2d ", iaZeileVektor[l]);
		}
		TRACE("\niaLinearKombination1:\n");
		for (l=0; l<modul; l++)
		{
			TRACE("%2d ", iaLinearKombination1[l]);
		}
		TRACE("\niaLinearKombination2:\n");
		for (l=0; l<modul; l++)
		{
			TRACE("%2d ", iaLinearKombination2[l]);
		}
		TRACE("\n");
#endif
		
		// Falls kein invertierbares Element bei der 'normalen' Suche gefunden werden konnte, aber 
		// bei der Suche nach Linearkombinationen, dann ist diese Linearkombination jetzt 
		// wirklich in die Matrix zu schreiben; im Anschluss werden alle Elemente links von dem zu 
		// invertierenden Zeichen auf Null gebracht und die Zeile neu berechnet (Form: 0 ... 0 1 x ... x).
		// Die neue Zeile muss eine der Zeilen ersetzen, die in die Linearkombination
		// eingegangen sind.
		if ( (! bInvertierbareZahlGefunden) && (iInvertierbaresElement) )
		{
			// Die Linearkombination in der richtigen Zeile der Matrix bilden
			// In den beiden Feldern iaLinearKombination1[j] und iaLinearKombination2[j] wurden die 
			// Werte gespeichert, aus denen sich j zusammensetzt, falls laPositionVektor[j] == HILL_LIN_KOMB_NEU.
			// Mit der Rekursiven Prozedur werden die Faktoren (die a_i in x = a_1 * x_1 + ... + a_k * x_k.)
			// der Linearkombination berechnet und in das Feld iaFaktoren
			
			// iInvertierbaresElement kann nicht gleich 0 sein !
			ASSERT ( (1 <= iInvertierbaresElement) && (iInvertierbaresElement < modul));
			for (k=0; k<modul; k++)
			{
				iaFaktoren[k] = 0;
			}

			BerechneFaktoren(iInvertierbaresElement);

#ifdef _DEBUG
			ASSERT (iaFaktoren[0] == 0); // Die 0 kann nicht vorkommen (, da sie nichts veraendert).
			for (k=1; k<modul; k++)
			{
				ASSERT ( (0 <= iaFaktoren[k]) && (iaFaktoren[k] < modul) );
			}
			TRACE("\n");
			for (l=0; l<modul; l++)
			{
				TRACE("%2d ", l);
			}
			TRACE("\niaFaktoren:\n");
			for (l=0; l<modul; l++)
			{
				TRACE("%2d ", iaFaktoren[l]);
			}
			TRACE("\n");
#endif
			
			// Linearkombination erzeugen in Hilfsfeldern
			// (Die neue Zeile muss eine der Zeilen ersetzen, die in die Linearkombination
			// eingegangen sind. Daher wird die Linearkombination zuerst in zwei 
			// Hilfsfeldern gebildet.)

			// Erst Felder initialisieren ...
			for (l=0; l<dim; l++)
			{
				iaHilfsfeld_hilfsmat[l] = 0;
				iaHilfsfeld_mat1[l] = 0;
			}
		
			// ... und jetzt die Vektoren mit den entsprechenden Faktoren multiplizieren
			// und auf die vorhandene Linearkombination addieren.
			// um keinen Ueberlauf zu riskieren (falls modul und dim groesser werden),
			// fuehren wir nach jeder Addition die Modulo Berechnung durch.
			for (k=0; k<modul; k++)
			{
				if (iaFaktoren[k] != 0) // sonst ist iaZeileVektor[k] undefiniert
				{
					ASSERT ((i <= iaZeileVektor[k]) && (iaZeileVektor[k] < dim));
					for (l=0; l<dim; l++)
					{
						iaHilfsfeld_hilfsmat[l] += (iaFaktoren[k] * hilfsmat[iaZeileVektor[k]][l]);
						iaHilfsfeld_hilfsmat[l] %= modul;
						iaHilfsfeld_mat1[l] += (iaFaktoren[k] * (*mat1)(iaZeileVektor[k],l));
						iaHilfsfeld_mat1[l] %= modul;
					}
				}
			}

#ifdef _DEBUG
			TRACE("\n");
			for (l=0; l<dim; l++)
			{
				TRACE("%2d ", l);
			}
			TRACE("\niaHilfsfeld_hilfsmat:\n");
			for (l=0; l<dim; l++)
			{
				TRACE("%2d ", iaHilfsfeld_hilfsmat[l]);
			}
			TRACE("\n");
#endif

			// die neue Zeile (die beiden Zeilenvektoren) wird jetzt in der Matrix
			// in die Zeile mit dem kleinsten Wert auf der Hauptdiagonalen geschrieben,
			// die in die Linearkombination eingegangen ist. (Es koennte auch jede andere
			// Zeile sein; die Wahl ist beliebig.)
			// Suche diese Zeile und schreibe sie in k.
			// (Aktuell zu bearbeitende Zeile = i.)
			l=0;
			while ((l<modul) && (iaFaktoren[l]==0))
			{
				l++;
			}
			ASSERT((0 <= l) && (l < modul));
			iZeileInvertierbaresElement = iaZeileVektor[l];
			ASSERT((i <= iZeileInvertierbaresElement) && (iZeileInvertierbaresElement < dim));

#ifdef _DEBUG
			for (l=0; l<i; l++)
			{
				ASSERT(iaHilfsfeld_hilfsmat[l] == 0);
			}
#endif

			for (l=i; l<dim; l++)
			{
				hilfsmat[iZeileInvertierbaresElement][l] = iaHilfsfeld_hilfsmat[l] % modul;
			}
			for (l=0; l<dim; l++)
			{
				(*mat1)(iZeileInvertierbaresElement,l) = iaHilfsfeld_mat1[l] % modul;
			}
			
			bInvertierbareZahlGefunden = true;
			ASSERT((0 <= hilfsmat[iZeileInvertierbaresElement][i]) &&
					(hilfsmat[iZeileInvertierbaresElement][i] < modul));
			iInversesElement = inverse_elemente[hilfsmat[iZeileInvertierbaresElement][i]];
			ASSERT(iInversesElement!=0);

			bInvertierbareZahlGefunden = TRUE;
		}


/*		// Wir beschraenken uns auf den MODUL 26, dann kann naemlich obiges
		// Phaenomen nur auftreten, wenn sich eine 13 und eine weitere gerade Zahl (ungleich 0) 
		// in der entsprechenden Spalte befindet. (13 ist die einzige ungerade Zahl, die 
		// modulo 26 nicht invertierbar ist. 1,3,5,7,11,15,17,19,21,23,25 sind invertierbar)
		// Loesung: Wir addieren die Zeile mit der geraden Zahl einfach auf
		// die Zeile mit 13 auf.
		// VON HIER nur fuer MODUL = 26 !!!
		if ((! bInvertierbareZahlGefunden) && (modul == 26))
		{
			// Gibt es in der aktuellen Spalte ein Element 13 ?
			j=i;
			
#ifdef _DEBUG
			for (int my_i=0; my_i < dim; my_i++)
			{
				ASSERT ((0 <= hilfsmat[my_i][i]) && (hilfsmat[my_i][i] < modul));
			}
			
#endif
			
			while ((j<dim) && (hilfsmat[j][i] != 13))
			{
				j++;
			}
			
			// Falls es ein solches gibt, gibt es auch ein gerades Element != 0 ?
			if ( (j<dim) && (hilfsmat[j][i] == 13) )
			{
				k=i;
				while ((k<dim) && ((hilfsmat[k][i] == 0) || ((hilfsmat[k][i] % 2) != 0)) )
				{
					k++;
				}
				
				// Falls es das auch gibt, k-te Zeile auf j-te addieren, siehe oben.
				if ( (k<dim) && (hilfsmat[k][i] != 0) && ((hilfsmat[k][i] % 2) == 0))
				{
					int l;
					for (l=i; l<dim; l++)
					{
						hilfsmat[j][l] += hilfsmat[k][l];
						hilfsmat[j][l] %= modul;
					}
					for (l=0; l<dim; l++)
					{
						(*mat1)(j,l) += (*mat1)(k,l);
						(*mat1)(j,l) %= modul;
					}
					
					bInvertierbareZahlGefunden = true;
					ASSERT((0 <= hilfsmat[j][i]) && (hilfsmat[j][i] < modul));
					iInversesElement = inverse_elemente[hilfsmat[j][i]];
					ASSERT(iInversesElement!=0);
				}
				
				j++;
			}
		}
		// BIS HIER nur fuer MODUL = 26 !!!
		*/

		// Matrix ausgeben
#ifdef _DEBUG
		for (my_k=0; my_k<dim; my_k++)
		{
			for (my_l=0; my_l<dim; my_l++)
			{
				TRACE("%3d ", hilfsmat[my_k][my_l]);
			}
			TRACE("\n");
		}
		TRACE("\n");
#endif
		
		// Wurde eine weitere Zeile gefunden ?
		if (bInvertierbareZahlGefunden)
		{
			// die iZeileInvertierbaresElement-te Zeile wird mit der aktuellen (i-ten) vertauscht ...
			if (i != iZeileInvertierbaresElement)
			{
				int hilf;
				for (l=0; l<dim; l++)
				{
					hilf = hilfsmat[i][l];
					hilfsmat[i][l] = hilfsmat[iZeileInvertierbaresElement][l];
					hilfsmat[iZeileInvertierbaresElement][l] = hilf;
					hilf = (*mat1)(i,l);
					(*mat1)(i,l) = (*mat1)(iZeileInvertierbaresElement,l);
					(*mat1)(iZeileInvertierbaresElement,l) = hilf;
				}
			}
			
			// Matrix ausgeben
#ifdef _DEBUG
			for (my_k=0; my_k<dim; my_k++)
			{
				for (my_l=0; my_l<dim; my_l++)
				{
					TRACE("%3d ", hilfsmat[my_k][my_l]);
				}
				TRACE("\n");
			}
			TRACE("\n");
#endif
			
			// ... und an der Stelle (i,i) eine 1 erstellt
			// Also muss die (neue) i-te Zeile mit dem Inversen der Zahl
			// an der Stelle (i,i) multipliziert werden.
			for (l=i; l<dim; l++)
			{
				hilfsmat[i][l] = (hilfsmat[i][l]*iInversesElement) % modul;
			}
			ASSERT(hilfsmat[i][i] == 1);
			for (l=0; l<dim; l++)
			{
				(*mat1)(i,l) = ((*mat1)(i,l)*iInversesElement) % modul;
			}
			
			// jetzt unterhalb von hilfsmat[i][i] Nullen herstellen
			for (k=i+1; k<dim; k++)
			{
				int iFaktor = modul - (hilfsmat[k][i] % modul);
				ASSERT((1 <= iFaktor) && (iFaktor <= modul));
				
				for (l=i; l<dim; l++)
				{
					hilfsmat[k][l] += (hilfsmat[i][l]*iFaktor) % modul;
					hilfsmat[k][l] %= modul;
				}
				for (l=0; l<dim; l++)
				{
					(*mat1)(k,l) += ((*mat1)(i,l)*iFaktor) % modul;
					(*mat1)(k,l) %= modul;
				}
			}
			// Matrix ausgeben
#ifdef _DEBUG
			for (my_k=0; my_k<dim; my_k++)
			{
				for (my_l=0; my_l<dim; my_l++)
				{
					TRACE("%3d ", hilfsmat[my_k][my_l]);
				}
				TRACE("\n");
			}
			TRACE("\n");
#endif
		}
		else
		{
			bNichtInvertierbar = true;
		}
	}
	
	if (bNichtInvertierbar)
	{
		// Hilfsmatrix freigeben
		for (int i=0; i<dim; i++)
		{
			delete[] hilfsmat[i];
		}
		delete[] hilfsmat;
		
		return false;
	}
	else
	{
		// Jetzt muss noch in mat alles rechts oberhalb der Hauptdiagonalen auf Null gebracht werden,
		// damit auf der linken Seite (mat) die Einheitsmatrix steht.
		// (x = beliebiger Wert)
		// ( 1 x x . x | x x x . x )    ( 1 0 0 . 0 | x x x . x ) 
		// ( 0 1 x . x | x x x . x )    ( 0 1 0 . 0 | x x x . x )
		// ( 0 0 1 . x | x x x . x ) => ( 0 0 1 . 0 | x x x . x )
		// ( ......... | ......... )    ( ......... | ......... )
		// ( 0 0 0 . 1 | x x x . x )    ( 0 0 0 . 1 | x x x . x )
		// i = Zeilenindex
		// j = Spaltenindex
		for (j=1; j<dim; j++)
		{
			for (int i=0; i<j; i++)
			{
				int iFaktor = modul - (hilfsmat[i][j] % modul);
				ASSERT((1 <= iFaktor) && (iFaktor <= modul));
				
				for (k=j; k<dim; k++)
				{
					hilfsmat[i][k] += (hilfsmat[j][k]*iFaktor) % modul;
					hilfsmat[i][k] %= modul;
				}
				for (k=0; k<dim; k++)
				{
					(*mat1)(i,k) += ((*mat1)(j,k)*iFaktor) % modul;
					(*mat1)(i,k) %= modul;
				}
			}
		}
		
		// Matrix ausgeben
#ifdef _DEBUG
		for (int my_k=0; my_k<dim; my_k++)
		{
			for (int my_l=0; my_l<dim; my_l++)
			{
				// Ist es auch wirklich die Einheitsmatrix ?
				ASSERT(hilfsmat[my_k][my_l] == ((my_k==my_l) ? 1 : 0));
				TRACE("%3d ", hilfsmat[my_k][my_l]);
			}
			TRACE("\n");
		}
		TRACE("\n");
#endif
		
		
		// Alle Eintraege der Matrix mat1 auf [0:modul-1] transformieren
		mat1->convert_mod();
		
#ifdef _DEBUG
		// Test, ob Inverse der Matrix richtig bestimmt:
		for (i=0; i<dim; i++)
		{
			for (int j=0; j<dim; j++)
			{
				long hilf = 0;
				for (k=0; k<dim; k++)
				{
					hilf += mat[i][k]*(*mat1)(k,j);
				}
				
				// Ist es die Einheitsmatrix ?
				ASSERT ( ((i==j) && ((hilf%modul)==1)) || ((i!=j) && ((hilf%modul)==0)) );
			}
		}
#endif
		
		// Hilfsmatrix freigeben
		for (int i=0; i<dim; i++)
		{
			delete[] hilfsmat[i];
		}
		delete[] hilfsmat;
		
		return true;
	}
}

// rekursive Hilfsfunktion fuer Funktion Invertierung Mittels Gauss-Jordan Verfahren
//
// Mit der Prozedur werden die Faktoren (die a_i in x = a_1 * x_1 + ... + a_k * x_k.)
// der Linearkombination berechnet und in das Feld iaFaktoren geschrieben.
// In den beiden Feldern iaLinearKombination1[j] und iaLinearKombination2[j] wurden die 
// Werte gespeichert, aus denen sich j zusammensetzt, falls iaZeileVektor[j] == SQ_MAT_LIN_KOMB_NEU.
// (Der Parameter fuer den ersten Aufruf ist die Wurzel des Rekursionsbaumes,
// muss also das gefundene Element sein, welches invertierbar ist (% modul).)
//
// Die Funktionalitaet der Funktion kann nicht durch eine Schleife (ohne Stack oder Queue)
// erhalten werden, da ein Element sich aus zwei anderen ergeben haben kann, welche 
// sich wieder aus zwei anderen ergeben haben, usw.
void CSquareMatrixModN::BerechneFaktoren(int i) const
{
	// i kann nicht gleich 0 sein, da die Addition von 0 den Wert nicht veraendert,
	// dies also in keiner Linearkombination enthalten sein kann.
	ASSERT ( (1 <= i) && (i < modul));
	ASSERT ( (iaZeileVektor[i]==SQ_MAT_LIN_KOMB_NEU) ||
			 ((0 <= iaZeileVektor[i]) && (iaZeileVektor[i] < dim)) );

	if (iaZeileVektor[i]==SQ_MAT_LIN_KOMB_NEU)
	{
		BerechneFaktoren(iaLinearKombination1[i]);
		BerechneFaktoren(iaLinearKombination2[i]);
	}
	else // 0 <= iaZeileVektor[i] < dim, also ein Vektor, der keine Linearkombination ist
	{
		ASSERT ( (iaLinearKombination1[i] == SQ_MAT_LIN_KOMB_INIT) && 
				(iaLinearKombination2[i] == SQ_MAT_LIN_KOMB_INIT) );
		iaFaktoren[i]++;
	}
}

BOOL CSquareMatrixModN::invert_adjunkten_verfahren(CSquareMatrixModN *mat1) const
{
	// Inverse der Determinanten berechnen. Diese muss nicht immer 
	// existieren (nur bei Primzahlen existiert sie immer)
	// Beispiel: Existiert nur fuer:
	// Sei modul = 26:
	// gcd(det,26)=1 (siehe Buch Stinson, Cryptography, Seite 16 unten)
	// <=> (det ungerade) und (det != 13)
	
	long det; // Determinante mod modul
	long inv_det; // Inverse der Determinante mod modul
	
	int *zeilenneu,
		*spaltenneu;
	
	zeilenneu = new int[dim];
	spaltenneu = new int[dim];
	
	for (int i=0; i<dim; i++)
	{
		zeilenneu[i] = spaltenneu[i] = i;
	}
	
	det = determinante(zeilenneu, spaltenneu, dim);
	
	det %= modul;
	
	// Inverse der Determinanten berechnen
	if (det < 0)
	{
		ASSERT((-modul < det) && (det <= 0));
		inv_det = -inverse_elemente[-det];
	}
	else
	{
		ASSERT((0 <= det) && (det < modul));
		inv_det = inverse_elemente[det];
	}
	
	if ( ((det*inv_det) % modul) == 1)
	{
		int i;
		for (i=0; i<dim-1; i++)
		{
			zeilenneu[i] = i+1;
		}
		
		for (i=0; i<dim; i++)
		{
			if (i >= 1)
			{
				zeilenneu[i-1] = i-1;
			}
			
			int j;
			for (j=0; j<dim-1; j++)
			{
				spaltenneu[j] = j+1;
			}
			
			for (j=0; j<dim; j++)
			{
				if (j >= 1)
				{
					spaltenneu[j-1] = j-1;
				}
				
				// hier transponieren wir die matrix gleich,
				// d.h. statt mat1(i,j) steht hier mat1(j,i)
				if (((i+j)%2)==0)
				{
					(*mat1)(j,i) = inv_det *
						determinante(zeilenneu,spaltenneu,dim-1);
				}
				else
				{
					(*mat1)(j,i) = - inv_det *
						determinante(zeilenneu,spaltenneu,dim-1);
				}
			}
		}
		
		// Alle Eintraege der Matrix mat1 auf [0:modul-1] transformieren
		mat1->convert_mod();
		
#ifdef _DEBUG
		// Test, ob Inverse der Matrix richtig bestimmt:
		for (i=0; i<dim; i++)
		{
			for (int j=0; j<dim; j++)
			{
				long hilf = 0;
				for (int k=0; k<dim; k++)
				{
					hilf += mat[i][k]*(*mat1)(k,j);
				}
				
				// Ist es die Einheitsmatrix ?
				ASSERT ( ((i==j) && ((hilf%modul)==1)) || ((i!=j) && ((hilf%modul)==0)) );
			}
		}
#endif
		
	}
	
	delete[] zeilenneu;
	delete[] spaltenneu;
	
	return (((det*inv_det) % modul) == 1);
}

// Berechnung einer zufaelligen invertierbaren Matrix
BOOL CSquareMatrixModN::zufaellige_invertierbare_matrix(void)
{
	// Es existiert keine invertierbare Matriux, wenn der Modul gleich Eins ist,
	// also nur der Wert 0 erlaubt ist.
	if (modul == 1)
	{
		return FALSE;
	}

	int i,j,k;
	long zufallszahl;
	
	// Zufallszahlengenerator mit der aktuellen Zeit initialisieren
	srand((unsigned)time(NULL));
	
	if (dim == 1)
	{
		// Hier kann nicht das Verfahren fuer Dimensionen groesser als 1
		// benutzt werden, da sonst immer die Einheitsmatrix berechnet wird
		// Wir ueberpruefen zuerst, wieviele Werte eine Inverse besitzten,
		// waehlen dann eine Zufallszahl und nehmen den entsprechenden Wert
		// als Eintrag in der Matrix der Dimension 1x1.
		int anz_inverse = 0;
		for (i=0; i<modul; i++)
		{
			if (get_inverses_element(i))
			{
				anz_inverse++;
			}
		}
		
		zufallszahl = rand() % anz_inverse;
		ASSERT((0 <= zufallszahl) && (zufallszahl < anz_inverse));
		
		i = 0;
		j = 0;
		while (j <= zufallszahl)
		{
			if (get_inverses_element(i))
			{
				j++;
			}
			i++;
		}
		
		ASSERT((0 <= i-1) && (i-1 < modul));
		mat[0][0] = get_inverses_element(i-1);
	}
	else
	{
		// Einheitsmatrix erstellen
		for (i=0; i<dim; i++)
		{
			for (int j=0; j<dim; j++)
			{
				mat[i][j] = (i==j) ? 1 : 0;
			}
		}
		
		// von jeder Zeile wird ein zufaelliges Vielfaches auf jede andere Zeile addiert
		// Laufzeit: O(dim^3)
		// nach dem Abarbeiten einer Zeile alle Eintraege nach [0:modul-1] konvertieren
		for (i=0; i<dim; i++) 
		{
			for (j=0; j<dim; j++)
			{
				// Nun ein Vielfaches der i-ten Zeile auf die j-te Zeile addieren
				if (i != j)
				{
					zufallszahl = rand() % modul;
					ASSERT((0 <= zufallszahl) && (zufallszahl < modul));
					for (k=0; k<dim; k++)
					{
						mat[j][k] += zufallszahl * mat[i][k];
					}
				}
			}
			convert_mod();
		}
		
		// Zum Schluss addieren wir ein Vielfaches der ersten Zeile auf die letzte, 
		// da sonst bei allen zufaelligen Matrizen an der Stelle rechts unten 
		// die 1 steht.
		zufallszahl = rand() % modul;
		ASSERT((0 <= zufallszahl) && (zufallszahl < modul));
		for (k=0; k<dim; k++)
		{
			mat[dim-1][k] += zufallszahl * mat[0][k];
		}
		convert_mod();
	}

	return TRUE;

#ifdef _DEBUG
	// zufaellige Matrix ausgeben
	TRACE("Zufaellige Matrix der Dimension %d mit Modul %d:\n", dim, modul);
	for (i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
		{
			TRACE("%3d", mat[i][j]);
		}
		TRACE("\n");
	}
#endif
}
