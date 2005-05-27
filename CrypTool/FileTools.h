/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


///////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

#ifndef __FILETOOLS_H
#define __FILETOOLS_H

#include "secure.h"

// Erstellen eines eindeutigen Namens f�r eine tempor�re Datei.
// Der gew�hlte Dateiname beginntm it prefix und endet mit ext.
// ext sollte den '.' mit einschiessen. z.B. ext = ".tmp"
// Konvention f�r prefix: prefix = "cry". Damit lassen sich alle tempor�ren Dateien
// im temp-Verzeichnis einfach finden.
void GetTmpName( char *dest, const char *prefix, const char *ext );

// Erstellen eines Hexdumps eines Lokalen Speicherbereiches
// Das Ziel ist ebenfalls ebenfalls ein lokaler Speicherbereich mit dem gleichen Handle
// Es werden jeweils len Bytes in eine Zeile geschrieben.
// Jede Zeile besteht aus einem Adressteil, enem HEX-Teil und anschlie�end einem Teil in dem die
// abdruckbaren Zeichen aufgef�hrt sind.
// returncode:	0: Fehler aufgetreten
//				1: Ohne Fehler abgeschlossen
//				2: Datei wurde abgeschnitten
int HexDumpMem(char *Dest, int DestSize, unsigned char *Src, int SrcSize, const int len, long start=0);

// Erstellen eines Hexdumps aus einem Octetstring
// Das Ziel ist ebenfalls ein Octetstring f�r den mittels new[] automatisch Speicher allokiert wird
// Es werden jeweils len Bytes in eine Zeile geschrieben.
// Jede Zeile besteht aus einem Adressteil, enem HEX-Teil und anschlie�end einem Teil in dem die
// abdruckbaren Zeichen aufgef�hrt sind.
// R�ckgabewert: Anzahl der geschriebenen Zeichen
int HexDumpOct(OctetString& Dest, OctetString& Src, const int len, long start=0);


void Add2OString(OctetString* osTarget, const char* Source, const int Length);

// Erstellen eines formatierten Dumps f�r Dateien, die keine Zeilenumbr�che enthalten.
// Quelle und Ziel sind jeweils Dateien.
// Je nach eingestelltem Alphabet werden die Dateien in der eingestellten Blockl�nge blocklen
// mit Leerzeichen oder anderen Zeichen formatiert. Es werden numblocks Bl�cke in eine Zeile geschrieben.
// returncode:	0: Fehler aufgetreten
//				1: Ohne Fehler abgeschlossen
//				2: Datei wurde abgeschnitten
int ASCDump(const char *outfile, const char *infile, const int blocklen, const int numblocks, int maxlen);

// Erstellen eines formatierten Dumps f�r Dateien, die keine Zeilenumbr�che enthalten.
// Quelle und Ziel sind jeweils Datenfelder.
// Je nach eingestelltem Alphabet werden die Dateien in der eingestellten Blockl�nge blocklen
// mit Leerzeichen oder anderen Zeichen formatiert. Es werden numblocks Bl�cke in eine Zeile geschrieben.
// returncode:	L�nge der Daten, 0 bei Fehler
int ASCDumpMem(char *Dest, int DestLen, const char *Src, int SrcLen, int blocklen, const int numblocks, char *SepChar);

int ASCUndumpMem(const char *inbuff, const int inlen, char *outbuff, char SepChar);

// Umkopieren einer Datei
// Quelle und Ziel sind jeweils Dateien.
// Kopieren ist teilweise notwendig um das verwendete Konzept tempor�rer Dateien, die nach
// Gebrauch gel�scht werden zu erhalten.
// returncode:	0: Fehler aufgetreten
//				1: Ohne Fehler abgeschlossen
int FileCpy(const char *outfile, const char *infile);

// Widerherstellen des Textformates der Eingangadatei
// Quelle und Ziel sind jeweils Dateien.
// Die Fumktio ForceReformat wird ausgef�hrt, wenn in den Textoptionen vermerkt ist, da� das
// Textformat erhalten werden soll.
BOOL Reformat(const char *reffile, const char *newfile, BOOL FixedAlphabet);

// Widerherstellen des Textformates der Eingangadatei
// Quelle und Ziel sind jeweils Dateien.
// Bei Chiffren, die sich auf ein beschr�nktes Alphabet (z.B. A-Z) st�tzen kann die urspr�ngliche
// Formatierung wiedergewonnen werden, indem einerseits die Gro�/Kleinschreibug wiederhergestellt
// wird und andererseits die nicht chiffrierten "Sonderzeiche" (z.B. Leerzeichen, Satzzeichen und
// Zeilenumbr�che wierder eingef�gt werden. Ist FixedAlphabet==TRUE so wird das Alphabet "A"-"Z"
// verwendet und es wird Gro�/Kleinschreibung korrigiert. Bei FALSE wird das in den Textoptionen
// definierte Alphabet verwendet und es wird die Optionseinstellung zum Verwenden von
// Gro�/Kleinschreibung �bernommen.
BOOL ForceReformat(const char *reffile, const char *newfile, BOOL FixedAlphabet);

// Test auf Zeichen, die in einem Textfenster (Editor) auftreten d�rfen
BOOL IsText(const unsigned char c);

// Test auf im HexDump darstellbare Zeichen
BOOL IsPrint(const unsigned char c);

// Lesen eines strukturierten Hexdumps (s.o.) und �berf�hren in Bin�rdarstellung.
// Die L�nge len wird automatisch ermittelt.
int HexUndumpMem(const char *inbuff, const int inlen, char *outbuff, int *state);

// Kontrolle auf "0"-"9", "a"-"f", "A"-"F"
BOOL IsHex(const unsigned char c);

// Konvertierung eines Zeichens in seinen Dezimalwert
int HexVal(const unsigned char c);

// ermitteln der L�ne der Datei name. Falls die Datei nicht ge�ffnet weden kann wird "0" zur�ckgegeben
int filesize( const char *name );

// Konstanten f�r die Formatierung von Hexdumps
// nach MAX_ADR_LEN-Zeichen kommt das erste Hexdigit
#define MAX_ADR_LEN	7
// Nach einem Hexzeichen sind HEX_SEP blanks
#define HEX_SEP	1
// Nach den Hexdaten sind ASC_SEP blanks vorgesehen
#define ASC_SEP	2
// eine Zeile ist demnach MAX_ADR_LEN + 4*<hexzeichen> + ASC_SEP  Zeichen lang (ohne abschlie�ende CR LF)

#endif