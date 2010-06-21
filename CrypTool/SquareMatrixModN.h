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
// Deklaration der Klasse
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////

#ifndef SQUARE_MATRIX_INCLUDED
#define SQUARE_MATRIX_INCLUDED

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif
#include <stdlib.h> // fuer srand, rand
#include <time.h> // fuer time

#define BOOL int
#define TRUE 1
#define FALSE 0

// Werte fuer Feld laPositionVektor
#define SQ_MAT_LIN_KOMB_INIT   -1
#define SQ_MAT_LIN_KOMB_NEU    -2

// Klasse fuer quadratische Matrix
// mit Invertiermoeglichkeit modulo einer natuerlichen Zahl

class CSquareMatrixModN
{
private:
	// Daten
	long **mat;
	// Dimension der Matrix
	int dim;
	// Modul = Maechtigkeit des Alphabeths
	int modul;
	// Maximale Laenge einer Zahl mod modul fuer Breite des Ausgabefeldes
	int feldbreite;
	// Inverse Elemente von 0 bis modul-1
	int *inverse_elemente;
	
	
	// Determinante berechnen
	long determinante (int*, int*, int) const;
	
	// Konvertierung eines Eintrages
	long convert_long (long) const;
	
	
	// Felder fuer die Invertierung einer Matrix mittels Gauss-Jordan Verfahren
	// Diese Felder haben alle die Laenge modul; der Speicher wird im Konstruktor 
	// angefordert und im Destruktor wieder freigegeben.
	// Sie werden nur benoetigt, wenn bei Gauss-Jordan Verfahren kein invertierbares
	// Element mehr fuer die aktuelle Position auf der Hauptdiagonalen verfuegbar 
	// ist, so dass das Verfahren nicht fortgresetzt werden kann, da die "1" auf der
	// Hauptdiagonalen nicht erzeugt werden kann.
	int *iaZeileVektor;			// An der Stelle i steht anfangs SQ_MAT_LIN_KOMB_INIT.
								// Falls beim Invertieren erstmalig der Wert i 
								// an der entsprechenden Stelle auf der Hauptdiagonalen 
								// auftritt, wird die Zeile des Vektors in der Matrix 
								// in diesem Feld gespeichert.
								// Kann dieser Wert i durch eine Linearkombination 
								// gebildet werden, so wird SQ_MAT_LIN_KOMB_NEU an der 
								// Stelle i eingetragen. i ergibt sich aus der Summe von
								// den beiden in iaLinearKombination1 und 
								// iaLinearKombination2 eingetragenen Werten; die Vektoren
								// fuer diese beiden Werte koennen mittels dieser Variablen
								// laPositionVektor ermittelt werden.
	int *iaLinearKombination1;	// siehe Erklaerung zu laPositionVektor.
	int *iaLinearKombination2;	// siehe Erklaerung zu laPositionVektor.
	int *iaFaktoren;			// Dieses Feld enthaelt die Faktoren, mit denen die
								// Vektoren der Linearkombination multipliziert werden
								// muessen, damit an der entsprechenden Stelle auf der
								// Hauptdiagonalen ein invertierbares Elemnent steht.
	
	// Hilfsvariablen zum Bilden der Linearkombination bei Invertierung der Matrix
	// mittels Gauss-Jordan Verfahren. Die beiden Zeilenvektoren werden nachher 
	// in der Matrix eingefuegt. Sie ersetzen eine Zeile, die in die 
	// Linaerkombination eingegangen ist.
	// Diese Felder haben alle die Laenge dim; der Speicher wird im Konstruktor 
	// angefordert und im Destruktor wieder freigegeben.
	int *iaHilfsfeld_hilfsmat,	// Zeilenvektor linke Seite
		 *iaHilfsfeld_mat1;		// Zeilenvektor rechte Seite

	// Hilfsfunktion fuer die Invertierung mittels Gauss-Jordan Verfahren
	// zum Berechnen der Faktoren fuer die Linearkombination 
	void BerechneFaktoren(int) const;
   void destroy();


public:
	// Konstruktor mit Parameter: Dimension, Modul
	CSquareMatrixModN(int, int);
	~CSquareMatrixModN();
	
	// Zugriffsfunktion: Operator, der ein Element der Matrix liefert
	long& operator() (int, int);
	long operator() (int, int) const;
	
	// Konvertierung der Eintraege nach [0:modul-1]
	void convert_mod ();
	
	// Ein- und Ausgabe
	friend ostream& operator<< (ostream & os, const CSquareMatrixModN &);
	friend istream& operator>> (istream & is, CSquareMatrixModN &);
	
	// Zuweisung
	CSquareMatrixModN& operator= (const CSquareMatrixModN &);
	
	// Rueckgabe der Dimension
	int get_dim (void) const;
	
	// Rueckgabe des Moduls
	int get_mod (void) const;
	
	// Rueckgabe des Feldbreite fuer die Ausgabe der Matrix
	int get_feldbreite (void) const;
	
	// Ausgabe des inversen Elements einer Zahl
	// Falls es nicht existiert, wird 0 zurueckgegeben
	int get_inverses_element (int) const;
	
	// Invertieren modulo einer Zahl
	// Es sollte immer die Funktion invert aufgerufen werden.
	// Diese ruft - in Anhaengigkeit von der entprechenden Matrix -
	// entweder invert_adjunkten_verfahren oder invert_gauss_jordan auf.
	BOOL invert(CSquareMatrixModN *) const;
	BOOL invert_adjunkten_verfahren(CSquareMatrixModN *) const;
	BOOL invert_gauss_jordan(CSquareMatrixModN *) const;
	
	// Berechnung einer zufaelligen invertierbaren Matrix der entsprechenden Dimension
	// Rueckgabewert: TRUE, falls eine invertirbare Matrix existiert.
	BOOL zufaellige_invertierbare_matrix (void);

   BOOL initialize( int, int );
   BOOL is_initialized() { return (dim > 0); }
};

#endif
