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


// SideChannelAttack.h

// ****************************************************************************
//
// 05.11.2003 Florian Marchal
// Implementierung eines Seitenkanalangriffs
// [speziell: Angriff auf Hybridverschl�sselung]
//
// ****************************************************************************

#ifndef _SIDECHANNELATTACK_
#define _SIDECHANNELATTACK_

class istream;
class ostream;
class SCA_Error;
class SCA_Client;
class SCA_Server;
class SCA_Attacker;

#include "CrypToolApp.h"
#include "Cryptography.h"
#include <big.h>
#include <string>
#include <iostream>
#include <fstream>
#include "AsymmetricEncryption.h"
#include "../libmiracl/include/BIG.H"
#include "DlgKeyAsymGeneration.h"
#include "KeyFileHandling.h"

extern char* CaPseDatei;
extern char* CaPseVerzeichnis, *PseVerzeichnis;

// Speicher f�r Schl�ssel im Big-Format (in Byte)
#define SCA_MAXIMUM_KEY_LENGTH_IN_BYTE								310		
// Zu allokierender Speicher f�r OctetStrings (in Byte)
#define SCA_MAX_LENGTH_OCTETSTRING									2048
// s.u.
#define SCA_MAX_LENGTH_RECEIVERSTRING								256
#define SCA_MAX_LENGTH_RECEIVERFIRSTNAME							48
#define SCA_MAX_LENGTH_RECEIVERLASTNAME								48
#define SCA_MAX_LENGTH_RECEIVERKEYTYPE								24
#define SCA_MAX_LENGTH_RECEIVERIDSTAMP								24
#define SCA_MAX_LENGTH_SESSIONKEYLENGTH								256
#define SCA_MAX_LENGTH_SYMMETRICMETHOD								24
#define SCA_MAX_LENGTH_ASYMMETRICMETHOD								24

// Struktur f�r hybridverschl�sselte Datei
struct HybridEncryptedFileInfo
{
	char receiverString[SCA_MAX_LENGTH_RECEIVERSTRING];
	char receiverFirstname[SCA_MAX_LENGTH_RECEIVERFIRSTNAME];
	char receiverLastname[SCA_MAX_LENGTH_RECEIVERLASTNAME];
	char receiverKeyType[SCA_MAX_LENGTH_RECEIVERKEYTYPE];
	char receiverIDStamp[SCA_MAX_LENGTH_RECEIVERIDSTAMP];
	char sessionKeyLength[SCA_MAX_LENGTH_SESSIONKEYLENGTH];
	char symmetricMethod[SCA_MAX_LENGTH_SYMMETRICMETHOD];
	char asymmetricMethod[SCA_MAX_LENGTH_ASYMMETRICMETHOD];
	OctetString sessionKeyEncrypted;
	OctetString cipherText;
	// Funktionen zum Initialisieren und Freigeben von Speicher
	void init(); 
	void free();
	// Operator-�berladung
	void operator=(HybridEncryptedFileInfo&);
};

typedef HybridEncryptedFileInfo hybEncInfo;

struct SessionKeyReception
{
	OctetString octetstring;
	bool success;
};

void convertOctetStringToBigNumber(const OctetString*, Big&);
void convertBigNumberToOctetString(Big, OctetString*, int outnoctets = 0);
bool convertBigTo32BitLong(const Big, long&);
void convertOctetStringToHexString(const OctetString*, char*);
double determineEntropy(const char*);
void decryptMessageAES(OctetString*,OctetString*,OctetString*,int);
void decryptSessionKeyRSA(HybridEncryptedFileInfo&, std::string, std::string, OctetString*);
bool extractCertFilename(const char*, CString&);
bool extractCertInfo(const char*, CString&, CString&, CString&, CString&);
CString generateCertFilename(CString,CString,CString,CString,bool fileExtension = true);
void extractHybridEncryptedFileInformation(const char*, hybEncInfo&);
void generateSCAReport(SCA_Client*,SCA_Server*,SCA_Attacker*,const char*);
bool isNullKey(const OctetString*);
// f�r AES-Verschl�sselung/Entschl�sselung
void doaescrypt(int,char,int,char*,unsigned char*,int,unsigned char*);
void getPublicKey(const char*,const char*,const char*,char*,char*);


// *** SCA_Server ***
// beschreibt den Server, der durch einen Seitenkanalangriff attackiert wird.
class SCA_Server
{
	// signifikante Bitl�nge
	int significantBits;
	// RSA
	Big e;
	Big n;
	Big d;
	// PSE-Informationen
	std::string psePath;
	std::string psePin;
	// der empfangene Session Key in VERSCHL�SSELTER Form [Big]
	Big receivedEncryptedSessionKey;
	// der empfangene Session Key in ENTSCHL�SSELTER Form [Big]
	Big receivedDecryptedSessionKey;
	// der empfangene Session Key in ENTSCHL�SSELTER Form [OctetString]
	OctetString decryptedSessionKey;
	// der empfangene Chiffretext in ENTSCHL�SSELTER Form
	OctetString decryptedCipherText;
	// speichert ALLE bisher empfangenen Session Keys 
	OctetString *formerSessionKeys;
	// speichert ALLE bisherigen Antworten JA oder NEIN (bzgl. des entsprechenden Session Keys)
	bool *formerResponses;
	// Wie viele Empf�nge gab es bisher?
	int numberOfReceptions; 
	// diese Funktion �berpr�ft, ob der �bergebene Text korrekt entschl�sselt wurde
	bool wasDecryptionSuccessful(OctetString*);

public:
	SCA_Server();
	virtual ~SCA_Server();
	// Zugriffsmethoden
	void setPublicKey(std::string);
	void setModulus(std::string);
	void setPrivateKey(std::string);
	void setPSEData(std::string,std::string);
	Big getPublicKey() { return e; };
	// Mit dieser Funktion "empf�ngt" der Server eine hybridverschl�sselte Datei. Als
	// R�ckgabewert gibt die Funktion zur�ck, ob die verschl�sselte Datei korrekt
	// entschl�sselt werden konnte
	bool receiveHybridEncryptedFile(HybridEncryptedFileInfo&);
	// wie viele Empf�nge gab es bisher?
	int getNumberOfReceptions() { return numberOfReceptions; };
	// Mit dieser Funktion kann man sich einen beliebigen der bisherigen Session Keys holen
	OctetString *getFormerSessionKey(int);
	// Mit dieser Funktion kann man ermitteln, ob die Antwort des Servers auf den
	// Empfang eines bestimmten Session Keys JA oder NEIN war
	bool getFormerResponse(int);
	// Die Anzahl der mit "erfolgreich" beantworteten Entschl�sselungen/Nachrichtenempf�nge
	int getNumberOfPositiveResponses();
	// Funktionen, die den Server auf einen bestimmten Zustand (ZUR�CK)setzen
	void cancelRSAParameters();
	void cancelPSEData();
	void cancelReceptions(); // ALLE
	void cancelAttackerReceptions(); // NUR ANGREIFER
};


// *** SCA_Client ***
// Statusinformationen
struct SCA_ClientStatusInfo
{
	// hat Alice schon eine hybridverschl�sselte Datei
	// ausgew�hlt oder selbst erzeugt?
	bool isHybEncFileDefined;		
	// hat Alice die Nachricht an Bob SELBST verfasst?
	// --> 2. M�glichkeit: HybEncDatei war schon vorhanden]
	bool hasCreatedMessage;
	// hat Alice die [verschl�sselte] Nachricht schon an Bob gesendet?
	bool hasTransmittedMessage;
};

// beschreibt den Client, der dem Server eine geheime Nachricht schicken will,
// die per HYBRIDVERSCHL�SSELUNG gesichert wurde.
class SCA_Client
{
	// Struktur auf hybridverschl�sselte Datei
	HybridEncryptedFileInfo hi;
	// der Session Key
	std::string sessionKey;
	// Struktur mit Statusinformationen
	SCA_ClientStatusInfo statusInfo;

public:
	SCA_Client();
	
	// Zugriffsfunktionen
	HybridEncryptedFileInfo &getHybEncFile() { return hi; };
	HybridEncryptedFileInfo &transmitHybEncFile();
	std::string getSessionKey() { return sessionKey; };
	const SCA_ClientStatusInfo getStatusInfo() { return statusInfo; };
	void useExistingHybEncFile(HybridEncryptedFileInfo&);
	void useCreatedHybEncFile(HybridEncryptedFileInfo&,std::string);
	// Funktionen, die den Client auf einen bestimmten Zustand (ZUR�CK)setzen
	void cancelHybridEncryptedFile();
	void cancelSessionKey();
	void cancelTransmission();
};


// *** SCA_Attacker ***
// beschreibt den Angreifer, der den Server �ber einen Seitenkanal attackiert.
class SCA_Attacker
{
private:

	// signifikante Bitl�nge
	int significantBits;
	// Abgefangene HybEncDatei (Basis f�r Angriffe)
	HybridEncryptedFileInfo hi;
	// hat der Angreifer �berhaupt schon eine HybEncDatei abgefangen?
	bool isHybridEncryptedFileIntercepted;
	// Aktuell durchzuf�hrender Schritt des Algorithmus
	int currentStep;
	// wurde der Angriff beendet?
	bool bIsAttackDone;
	// Angriff wurde beendet
	void attackIsDone(std::string);
	// der erratene Session-Key
	std::string secret;
	// Struktur zum Speichern der originalen HybEnc-Datei, die Alice
	// an Bob versandt hat und von Trudy abgeh�rt wird
	HybridEncryptedFileInfo originalHybEncFileInfo;
	// modifizierter Session Key [alternierend]
	OctetString modifiedSessionKey;
	// diese Funktion berechnet z, das abh�ngig von N und B ist
	Big computeZ(Big,Big);
	// Funktion zur Berechnung des Logarithmus Dualis
	int log2(Big);
	// F�r die Durchf�hrung des Algorithmus ben�tigte Variablen
	struct AlgorithmVariables
	{
		Big z;		// z
		int b1;		// b
		int b2;		// b'
		Big y;		// y
		std::string e;	// e (des Zielservers)
		std::string n;	// n (des Zielservers)
	} algVars;
	// alle bisher modifizierten Geheimnisse/Session Keys werden aus
	// statistischen Gr�nden in einem Array gespeichert
	OctetString *formerlyModifiedSessionKeys;
	// wie viele Challenges wurden bisher modifiziert/versandt?
	int numberOfModifications;
	// speichert ALLE bisherigen Antworten JA oder NEIN (bzgl. des entsprechenden Session Keys)
	bool *formerResponses;
	// der Angreifer ver�ndert die urspr�ngliche HybEncDatei, die Alice
	// an Bob versandt hat; dazu wird lediglich der SessionKey "ersetzt"
	void modifyHybridEncryptedFile(OctetString*, char*);

public:
	SCA_Attacker();
	~SCA_Attacker();

	// der Angreifer erh�lt den �ffentlichen Schl�ssel
	// des anzugreifenden Servers
	void setTargetPublicKey(std::string,std::string);
	// der Angreifer h�rt den Kanal zwischen Alice und Bob
	// ab und erlangt Informationen �ber die von Alice versandte Nachricht
	void interceptHybridEncryptedFile(HybridEncryptedFileInfo&);	
	// hat der Angreifer schon eine Challenge angefangen?
	bool hasInterceptedHybridEncryptedFile() { return isHybridEncryptedFileIntercepted; };
	// gibt den abgefangenen und verschl�sselten Session Key zur�ck
	OctetString *getInterceptedSessionKey() { return &originalHybEncFileInfo.sessionKeyEncrypted; };
	// in welchem Schritt des Angriffs befinden wir uns?
	int getCurrentStep() { return currentStep; };
	// der Angreifer berechnet eine (n�chste) Challenge
	// aufgrund der bisher ermittelten Werten
	HybridEncryptedFileInfo nextHybridEncryptedFile();
	// der Angreifer wertet die vom Server zur�ckgegebene
	// Antwort aus und f�hrt mit seinem Angriff fort
	void processServerResponse(bool);	
	// ist der Algorithmus zu Ende durchgef�hrt?
	bool isDone() { return bIsAttackDone; };
	// gibt den berechneten Session Key zur�ck
	std::string getComputedSecret() { return secret; };
	// Zeiger auf modifizierte Challenge (0-indiziert)
	OctetString *getModifiedChallenge(int);
	// wie viele modifizierte Session Keys gibt es?
	int getNumberOfModifications() { return numberOfModifications; };
	// wie viele anfragen wurden vom server positiv beantowrtet?
	int getNumberOfPositiveResponses();
	// Funktionen, die den Angreifer auf einen bestimmten Zustand (ZUR�CK)setzen
	void cancelRSAParameters();
	void cancelInterception();
	void cancelAttack();
};


// *** SCA_Error ***
class SCA_Error
{
private:
	long errorCode;

public:
	SCA_Error(long e) { errorCode = e; };
	long getErrorCode() { return errorCode; };
};


// *** Fehlercodes ***

// Beliebiger "interner" Fehler
#define E_SCA_INTERNAL_ERROR								1	
// Der angeforderte Speicher ist nicht verf�gbar
#define	E_SCA_MEMORY_ALLOCATION								2
// Fehler beim Parsen der hybridverschl�sselten Datei
#define E_SCA_HYBENCFILE_EXTRACTION							4
// die f�r den Angriff n�tigen Voraussetzungen sind nicht erf�llt
#define E_SCA_ATTACK_CONDITIONS_NOT_MET						8
// interner Miracl-Fehler
#define E_SCA_MIRACL_ERROR									16
// Falsche PIN f�r Zugriff auf PSE angegeben
#define E_SCA_WRONG_PSE_PIN									32
// Timer nicht verf�gbar
#define E_SCA_TIMER_NOT_AVAILABLE							64

#endif