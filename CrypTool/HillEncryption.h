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
// Deklaration der Klasse
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////

#ifndef HILL_CIPHER_INCLUDED
#define HILL_CIPHER_INCLUDED

#include "SquareMatrixModN.h"

// Klasse fuer Hill-Cipher

#define HILL_MAX_DIM 5 
#define HILL_MAX_DIM_GROSS 10


// Rueckgabewerte der Klasse beim Angriff:
#define HILL_UNDEF                        -1
#define HILL_OK                            0
#define HILL_OK_LAENGE_UNTERSCHIEDLICH     1
#define HILL_NICHT_OK_NICHT_GEFUNDEN      10
#define HILL_NICHT_OK_WIDERSPRUCH         11

// Werte fuer Feld laPositionVektor
#define HILL_LIN_KOMB_INIT   -1		// wie SQ_MAT_LIN_KOMB_INIT aus sq_mat.h
#define HILL_LIN_KOMB_NEU    -2		// wie SQ_MAT_LIN_KOMB_NEU aus sq_mat.h

class CHillEncryption
{

private:
	// Daten
	int *plaintext,
		*ciphertext;
	long laenge_plain,   // Laenge der Felder plaintext und ciphertext
        laenge_cipher;

	// Felder fuer den Angriff (Funktion SucheSchluessel)
	// Diese Felder haben alle die Laenge modul; der Speicher wird im Konstruktor 
	// angefordert und im Destruktor wieder freigegeben.
	// Sie werden nur benoetigt, wenn bei Gauss-Jordan Verfahren kein invertierbares
	// Element mehr fuer die aktuelle Position auf der Hauptdiagonalen verfuegbar 
	// ist, so dass das Verfahren nicht fortgresetzt werden kann, da die "1" auf der
	// Hauptdiagonalen nicht erzeugt werden kann.
	long *laPositionVektor;		// An der Stelle i steht anfangs HILL_LIN_KOMB_INIT.
								// Falls bei der Schluessel-Suche erstmalig der Wert i 
								// an der entsprechenden Stelle auf der Hauptdiagonalen 
								// auftritt, wird die Position des Vektors in der Eingabe 
								// in diesem Feld gespeichert.
								// Kann dieser Wert i durch eine Linearkombination 
								// gebildet werden, so wird HILL_LIN_KOMB_NEU an der 
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
	
	
	// Fuer Funktionen my_int_to_char und my_char_to_int 
	// (Zuordnung Zahl <-> Zeichen)
	// (hier wuerde eigentlich die Laenge modul reichen !)
	char zeichen[256]; 
	int zahlen[256];
	
	// Mit diesem Zeichen werden eventuell unvollstaendige Bloecke aufgefuellt
	// Es wird das ASCII-maessig kleinste Zeichen benutzt, um eine
	// Unabhaengigkeit von der Reichenfolge der Zeichen zu gewaehrleisten.
	char fuellzeichen;

	// Dimension der Matrix
	int dim;
	// Modul = Maechtigkeit des Alphabeths
	int modul;
	
	// Matrizen zum Ver- und Entschluesseln
	CSquareMatrixModN *dec_mat,	*enc_mat;
	
	// Speicher fuer Matrizen anlegen bzw. freigeben
	void anlegen_mat (void);
	void freigeben_mat (void);
	
	// Funktion zum fuellen der Felder zahlen und zeichen und Berechnung von modul
	void init_zahlen_zeichen (const char*);
	
	// Die Funktion wird von der Funktion angriff benoetigt
	void SucheSchluessel (int,int,long,int*,int*,BOOL*,int*,CSquareMatrixModN*,
		CSquareMatrixModN*,CSquareMatrixModN*,CSquareMatrixModN*);

	// Hilfsfunktion fuer den Angriff zum Berechnen der Faktoren fuer die
	// Linearkombination 
	void BerechneFaktoren(int, long);

	int getPositionOfCharForOutput(int iPos);
	void my_sprintf(char *str, int i);
	
public:
	CHillEncryption(const char*);
	// Konstruktor mit Dimension
	CHillEncryption(const char*,int);
	~CHillEncryption();
	
	// Abbildung [erlaubte Zeichen] <-> [0..modul-1]
	int				my_char_to_int (char) const;
	char			my_int_to_char (int) const;
	unsigned long	m_alphabetOffset;  
	// Darf dieses Zeichen benutzt werden ?
	BOOL ist_erlaubtes_zeichen (char) const;
	
	// Fuellzeichen ermitteln
	char get_fuellzeichen (void) const;
	
	// Funktionen zum Setzen / Ermitteln der Dimension
	void set_dim (int);
	int get_dim (void) const;
	
	// Funktionen zum Ermitteln des Moduls
	int get_modul (void) const;
	
	// Funktion zum Ermitteln der Laenge der Texte
	long get_laenge_plain (void) const;
	long get_laenge_cipher (void) const;
	
	// Funktionen zum Setzen / Ermitteln des Klartextes
	void set_plaintext (char*);
	void get_plaintext (char*) const;   // hier wird kopiert, Laenge des Feldes:
	// objekt.get_laenge() + 1;
	
	// Funktionen zum Setzen / Ermitteln des verschluesselten Textes
	void set_ciphertext (char*);
	void get_ciphertext (char*) const; // hier wird kopiert, Laenge des Feldes:
	// objekt.get_laenge() + 1;
	
	// Funktionen zum Setzen / Ermitteln der Verschluesselungsmatrix
	BOOL set_enc_mat (CSquareMatrixModN&);
	void get_enc_mat (CSquareMatrixModN*) const;
	
	// Funktionen zum Setzen / Ermitteln der Entschluesselungsmatrix
	BOOL set_dec_mat (CSquareMatrixModN&);
	void get_dec_mat (CSquareMatrixModN*) const;
	
	// Funktion liefert FALSE, falls Text oder Matrix nicht vorhanden sind
	BOOL verschluesseln(void);
	BOOL entschluesseln(void);
	
	// Eingabeparameter: Dimension von ... bis ...,
	// Ausgabeparameter: Verschluesselungsmatrix
	// Achtung: Die Funktion legt eine CSquareMatrixModN an, sofern der Returnwert
	// HILL_OK oder HILL_OK_LAENGE_UNTERSCHIEDLICH (d.h. Schluessel gefunden) ist;
	// diese muss von der rufenden Funktuion wieder freigegeben werden !
	// Rueckgabeparameter siehe oben mit define
	// Falls der Schluessel nicht gefunden werden konnte, so ist der Rueckgabewert
	// HILL_NICHT_OK_NICHT_GEFUNDEN (Text war zu kurz oder die Texte passten 
	// nicht zueinander) oder HILL_NICHT_OK_WIDERSPRUCH (Schluessel wurde gefunden
	// aber der Text kann nicht mit diesem Schluessel verschluesselt worden sein),
	// sofern fuer jede der zu durchsuchenden Dimensionen diese Ergebnis erhalten 
	// worden ist. Trat jedes Ergebnis mindestens ein Mal auf, so ist der 
	// Rueckgabewert HILL_UNDEF.
	// Der vierte Parameter ist ein Integer Feld der Länge HILL_MAX_DIM_GROSS !!!
	int angriff(int,int,CSquareMatrixModN*&,int*);

	void OutputHillmatrix(CString &MatOut);
};

#endif