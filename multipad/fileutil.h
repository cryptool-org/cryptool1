//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

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

// Umkopieren einer Datei.
// Quelle und Ziel sind jeweils Dateien.
// Kopieren ist teilweise notwendig um das verwendete Konzept tempor�rer Dateien, die nach
// Gebrauch gel�scht werden zu erhalten.
// maxsize ist die maximale Gr��e der resultierenden Datei.
// returncode:	0: Fehler aufgetreten
//				1: Ohne Fehler abgeschlossen
//				2: Datei wurde abgeschnitten
int FileCpy(const char *outfile, const char *infile, int maxsize);

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