/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

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

// Erstellen eines eindeutigen Namens für eine temporäre Datei.
// Der gewählte Dateiname beginntm it prefix und endet mit ext.
// ext sollte den '.' mit einschiessen. z.B. ext = ".tmp"
// Konvention für prefix: prefix = "cry". Damit lassen sich alle temporären Dateien
// im temp-Verzeichnis einfach finden.
void GetTmpName( char *dest, const char *prefix, const char *ext );

// Erstellen eines Hexdumps eines Lokalen Speicherbereiches
// Das Ziel ist ebenfalls ebenfalls ein lokaler Speicherbereich mit dem gleichen Handle
// Es werden jeweils len Bytes in eine Zeile geschrieben.
// Jede Zeile besteht aus einem Adressteil, enem HEX-Teil und anschließend einem Teil in dem die
// abdruckbaren Zeichen aufgeführt sind.
// returncode:	0: Fehler aufgetreten
//				1: Ohne Fehler abgeschlossen
//				2: Datei wurde abgeschnitten
int HexDumpMem(char *Dest, int DestSize, unsigned char *Src, int SrcSize, const int len, long start=0);

// Erstellen eines Hexdumps aus einem Octetstring
// Das Ziel ist ebenfalls ein Octetstring für den mittels new[] automatisch Speicher allokiert wird
// Es werden jeweils len Bytes in eine Zeile geschrieben.
// Jede Zeile besteht aus einem Adressteil, enem HEX-Teil und anschließend einem Teil in dem die
// abdruckbaren Zeichen aufgeführt sind.
// Rückgabewert: Anzahl der geschriebenen Zeichen
int HexDumpOct(OctetString& Dest, OctetString& Src, const int len, long start=0);


void Add2OString(OctetString* osTarget, const char* Source, const int Length);

// Erstellen eines formatierten Dumps für Dateien, die keine Zeilenumbrüche enthalten.
// Quelle und Ziel sind jeweils Dateien.
// Je nach eingestelltem Alphabet werden die Dateien in der eingestellten Blocklänge blocklen
// mit Leerzeichen oder anderen Zeichen formatiert. Es werden numblocks Blöcke in eine Zeile geschrieben.
// returncode:	0: Fehler aufgetreten
//				1: Ohne Fehler abgeschlossen
//				2: Datei wurde abgeschnitten
int ASCDump(const char *outfile, const char *infile, const int blocklen, const int numblocks, int maxlen);

// Erstellen eines formatierten Dumps für Dateien, die keine Zeilenumbrüche enthalten.
// Quelle und Ziel sind jeweils Datenfelder.
// Je nach eingestelltem Alphabet werden die Dateien in der eingestellten Blocklänge blocklen
// mit Leerzeichen oder anderen Zeichen formatiert. Es werden numblocks Blöcke in eine Zeile geschrieben.
// returncode:	Länge der Daten, 0 bei Fehler
int ASCDumpMem(char *Dest, int DestLen, const char *Src, int SrcLen, int blocklen, const int numblocks, char *SepChar);

int ASCUndumpMem(const char *inbuff, const int inlen, char *outbuff, char SepChar);

// Umkopieren einer Datei
// Quelle und Ziel sind jeweils Dateien.
// Kopieren ist teilweise notwendig um das verwendete Konzept temporärer Dateien, die nach
// Gebrauch gelöscht werden zu erhalten.
// returncode:	0: Fehler aufgetreten
//				1: Ohne Fehler abgeschlossen
int FileCpy(const char *outfile, const char *infile);

// Widerherstellen des Textformates der Eingangadatei
// Quelle und Ziel sind jeweils Dateien.
// Die Fumktio ForceReformat wird ausgeführt, wenn in den Textoptionen vermerkt ist, daß das
// Textformat erhalten werden soll.
BOOL Reformat(const char *reffile, const char *newfile, BOOL FixedAlphabet);

// Widerherstellen des Textformates der Eingangadatei
// Quelle und Ziel sind jeweils Dateien.
// Bei Chiffren, die sich auf ein beschränktes Alphabet (z.B. A-Z) stützen kann die ursprüngliche
// Formatierung wiedergewonnen werden, indem einerseits die Groß/Kleinschreibug wiederhergestellt
// wird und andererseits die nicht chiffrierten "Sonderzeiche" (z.B. Leerzeichen, Satzzeichen und
// Zeilenumbrüche wierder eingefügt werden. Ist FixedAlphabet==TRUE so wird das Alphabet "A"-"Z"
// verwendet und es wird Groß/Kleinschreibung korrigiert. Bei FALSE wird das in den Textoptionen
// definierte Alphabet verwendet und es wird die Optionseinstellung zum Verwenden von
// Groß/Kleinschreibung übernommen.
BOOL ForceReformat(const char *reffile, const char *newfile, BOOL FixedAlphabet);

// Test auf Zeichen, die in einem Textfenster (Editor) auftreten dürfen
BOOL IsText(const unsigned char c);

// Test auf im HexDump darstellbare Zeichen
BOOL IsPrint(const unsigned char c);

// Lesen eines strukturierten Hexdumps (s.o.) und Überführen in Binärdarstellung.
// Die Länge len wird automatisch ermittelt.
int HexUndumpMem(const char *inbuff, const int inlen, char *outbuff, int *state);

// Kontrolle auf "0"-"9", "a"-"f", "A"-"F"
BOOL IsHex(const unsigned char c);

// Konvertierung eines Zeichens in seinen Dezimalwert
int HexVal(const unsigned char c);

// ermitteln der Läne der Datei name. Falls die Datei nicht geöffnet weden kann wird "0" zurückgegeben
int filesize( const char *name );
int getFileSize(const char *filename, __int64 &size);

int readSource(const char* infile, char *&mSrc, int &lSrc, BOOL TEXTMODE );
int writeDest (const char* pData, int lData, char *&outFileName, BOOL TEXTMODE, const char *refFileName );



// Konstanten für die Formatierung von Hexdumps
// nach MAX_ADR_LEN-Zeichen kommt das erste Hexdigit
#define MAX_ADR_LEN	7
// Nach einem Hexzeichen sind HEX_SEP blanks
#define HEX_SEP	1
// Nach den Hexdaten sind ASC_SEP blanks vorgesehen
#define ASC_SEP	2
// eine Zeile ist demnach MAX_ADR_LEN + 4*<hexzeichen> + ASC_SEP  Zeichen lang (ohne abschließende CR LF)

#endif