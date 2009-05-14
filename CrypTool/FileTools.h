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