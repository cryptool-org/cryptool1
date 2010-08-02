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


// SideChannelAttack.h

// ****************************************************************************
//
// 05.11.2003 Florian Marchal
// Implementierung eines Seitenkanalangriffs
// [speziell: Angriff auf Hybridverschlüsselung]
//
// ****************************************************************************

#ifndef _SIDECHANNELATTACK_
#define _SIDECHANNELATTACK_

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif

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

// Speicher für Schlüssel im Big-Format (in Byte)
#define SCA_MAXIMUM_KEY_LENGTH_IN_BYTE								310*16
// Zu allokierender Speicher für OctetStrings (in Byte)
#define SCA_MAX_LENGTH_OCTETSTRING									2048*16
// s.u.
#define SCA_MAX_LENGTH_RECEIVERSTRING								256*16
#define SCA_MAX_LENGTH_RECEIVERFIRSTNAME							48
#define SCA_MAX_LENGTH_RECEIVERLASTNAME					      48
#define SCA_MAX_LENGTH_RECEIVERKEYTYPE								24
#define SCA_MAX_LENGTH_RECEIVERIDSTAMP								24
#define SCA_MAX_LENGTH_RECEIVERKEYID								24
#define SCA_MAX_LENGTH_SESSIONKEYLENGTH							256*16
#define SCA_MAX_LENGTH_SYMMETRICMETHOD								24
#define SCA_MAX_LENGTH_ASYMMETRICMETHOD							24

// Struktur für hybridverschlüsselte Datei
struct HybridEncryptedFileInfo
{
	char receiverString[SCA_MAX_LENGTH_RECEIVERSTRING];
	char receiverFirstname[SCA_MAX_LENGTH_RECEIVERFIRSTNAME];
	char receiverLastname[SCA_MAX_LENGTH_RECEIVERLASTNAME];
	char receiverKeyType[SCA_MAX_LENGTH_RECEIVERKEYTYPE];
	char receiverIDStamp[SCA_MAX_LENGTH_RECEIVERIDSTAMP];
	char receiverKeyId[SCA_MAX_LENGTH_RECEIVERKEYID];
	char sessionKeyLength[SCA_MAX_LENGTH_SESSIONKEYLENGTH];
	char symmetricMethod[SCA_MAX_LENGTH_SYMMETRICMETHOD];
	char asymmetricMethod[SCA_MAX_LENGTH_ASYMMETRICMETHOD];
	OctetString sessionKeyEncrypted;
	OctetString cipherText;
	// Funktionen zum Initialisieren und Freigeben von Speicher
	void init(); 
	void free();
	// Operator-Überladung
	void operator=(HybridEncryptedFileInfo&);
};

typedef HybridEncryptedFileInfo hybEncInfo;

struct SessionKeyReception
{
	OctetString octetstring;
	bool success;
};

class c_scaBigNumberSettings  
{
public:
	miracl *m_old_mip;
	miracl *mip;
	c_scaBigNumberSettings();
	virtual ~c_scaBigNumberSettings();
};


void convertOctetStringToBigNumber(const OctetString*, Big&);
void convertBigNumberToOctetString(Big, OctetString*, int outnoctets = 0);
bool convertBigTo32BitLong(const Big, long&);
void convertOctetStringToHexString(const OctetString*, char*);
double determineEntropy(const char*);
void decryptMessageAES(OctetString*,OctetString*,OctetString*,int);
void decryptSessionKeyRSA(HybridEncryptedFileInfo&, std::string, std::string, OctetString*);
bool extractCertFilename(const char*, CString&);
bool extractCertInfo(const char*, CString&, CString&, CString&, CString&, CString&);
CString generateCertFilename(CString,CString,CString,CString,CString,bool fileExtension = true);
void extractHybridEncryptedFileInformation(const char*, hybEncInfo&);
void generateSCAReport(SCA_Client*,SCA_Server*,SCA_Attacker*,const char*);
bool isNullKey(const OctetString*);
// für AES-Verschlüsselung/Entschlüsselung
// void doaescrypt(int,char,int,char*,unsigned char*,int,unsigned char*);
void getPublicKey(const char*,const char*,const char*,char*,char*);


// *** SCA_Server ***
// beschreibt den Server, der durch einen Seitenkanalangriff attackiert wird.
class SCA_Server
{
	// signifikante Bitlänge
	int significantBits;
	// RSA
	Big e;
	Big n;
	Big d;
	// PSE-Informationen
	std::string psePath;
	std::string psePin;
	// der empfangene Session Key in VERSCHLÜSSELTER Form [Big]
	Big receivedEncryptedSessionKey;
	// der empfangene Session Key in ENTSCHLÜSSELTER Form [Big]
	Big receivedDecryptedSessionKey;
	// der empfangene Session Key in ENTSCHLÜSSELTER Form [OctetString]
	OctetString decryptedSessionKey;
	// der empfangene Chiffretext in ENTSCHLÜSSELTER Form
	OctetString decryptedCipherText;
	// speichert ALLE bisher empfangenen Session Keys 
	OctetString *formerSessionKeys;
	// speichert ALLE bisherigen Antworten JA oder NEIN (bzgl. des entsprechenden Session Keys)
	bool *formerResponses;
	// Wie viele Empfänge gab es bisher?
	int numberOfReceptions; 
	// diese Funktion überprüft, ob der übergebene Text korrekt entschlüsselt wurde
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
	// Mit dieser Funktion "empfängt" der Server eine hybridverschlüsselte Datei. Als
	// Rückgabewert gibt die Funktion zurück, ob die verschlüsselte Datei korrekt
	// entschlüsselt werden konnte
	bool receiveHybridEncryptedFile(HybridEncryptedFileInfo&);
	// wie viele Empfänge gab es bisher?
	int getNumberOfReceptions() { return numberOfReceptions; };
	// Mit dieser Funktion kann man sich einen beliebigen der bisherigen Session Keys holen
	OctetString *getFormerSessionKey(int);
	// Mit dieser Funktion kann man ermitteln, ob die Antwort des Servers auf den
	// Empfang eines bestimmten Session Keys JA oder NEIN war
	bool getFormerResponse(int);
	// Die Anzahl der mit "erfolgreich" beantworteten Entschlüsselungen/Nachrichtenempfänge
	int getNumberOfPositiveResponses();
	// Funktionen, die den Server auf einen bestimmten Zustand (ZURÜCK)setzen
	void cancelRSAParameters();
	void cancelPSEData();
	void cancelReceptions(); // ALLE
	void cancelAttackerReceptions(); // NUR ANGREIFER
};


// *** SCA_Client ***
// Statusinformationen
struct SCA_ClientStatusInfo
{
	// hat Alice schon eine hybridverschlüsselte Datei
	// ausgewählt oder selbst erzeugt?
	bool isHybEncFileDefined;		
	// hat Alice die Nachricht an Bob SELBST verfasst?
	// --> 2. Möglichkeit: HybEncDatei war schon vorhanden]
	bool hasCreatedMessage;
	// hat Alice die [verschlüsselte] Nachricht schon an Bob gesendet?
	bool hasTransmittedMessage;
};

// beschreibt den Client, der dem Server eine geheime Nachricht schicken will,
// die per HYBRIDVERSCHLÜSSELUNG gesichert wurde.
class SCA_Client
{
	// Struktur auf hybridverschlüsselte Datei
	HybridEncryptedFileInfo hi;
	// der Session Key
	std::string sessionKey;
	// Struktur mit Statusinformationen
	SCA_ClientStatusInfo statusInfo;

public:
	SCA_Client();
   ~SCA_Client();
	
	// Zugriffsfunktionen
	HybridEncryptedFileInfo &getHybEncFile() { return hi; };
	HybridEncryptedFileInfo &transmitHybEncFile();
	std::string getSessionKey() { return sessionKey; };
	const SCA_ClientStatusInfo getStatusInfo() { return statusInfo; };
	void useExistingHybEncFile(HybridEncryptedFileInfo&);
	void useCreatedHybEncFile(HybridEncryptedFileInfo&,std::string);
	// Funktionen, die den Client auf einen bestimmten Zustand (ZURÜCK)setzen
	void cancelHybridEncryptedFile();
	void cancelSessionKey();
	void cancelTransmission();
};


// *** SCA_Attacker ***
// beschreibt den Angreifer, der den Server über einen Seitenkanal attackiert.
class SCA_Attacker
{
private:

	// signifikante Bitlänge
	int significantBits;
	// Abgefangene HybEncDatei (Basis für Angriffe)
	HybridEncryptedFileInfo hi;
	// hat der Angreifer überhaupt schon eine HybEncDatei abgefangen?
	bool isHybridEncryptedFileIntercepted;
	// Aktuell durchzuführender Schritt des Algorithmus
	int currentStep;
	// wurde der Angriff beendet?
	bool bIsAttackDone;
	// Angriff wurde beendet
	void attackIsDone(std::string);
	// der erratene Session-Key
	std::string secret;
	// Struktur zum Speichern der originalen HybEnc-Datei, die Alice
	// an Bob versandt hat und von Trudy abgehört wird
	HybridEncryptedFileInfo originalHybEncFileInfo;
	// modifizierter Session Key [alternierend]
	OctetString modifiedSessionKey;
	// diese Funktion berechnet z, das abhängig von N und B ist
	Big computeZ(Big,Big);
	// Funktion zur Berechnung des Logarithmus Dualis
	int log2(Big);
	// Für die Durchführung des Algorithmus benötigte Variablen
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
	// statistischen Gründen in einem Array gespeichert
	OctetString *formerlyModifiedSessionKeys;
	// wie viele Challenges wurden bisher modifiziert/versandt?
	int numberOfModifications;
	// speichert ALLE bisherigen Antworten JA oder NEIN (bzgl. des entsprechenden Session Keys)
	bool *formerResponses;
	// der Angreifer verändert die ursprüngliche HybEncDatei, die Alice
	// an Bob versandt hat; dazu wird lediglich der SessionKey "ersetzt"
	void modifyHybridEncryptedFile(OctetString*, char*);

public:
	SCA_Attacker();
	~SCA_Attacker();

	// der Angreifer erhält den öffentlichen Schlüssel
	// des anzugreifenden Servers
	void setTargetPublicKey(std::string,std::string);
	// der Angreifer hört den Kanal zwischen Alice und Bob
	// ab und erlangt Informationen über die von Alice versandte Nachricht
	void interceptHybridEncryptedFile(HybridEncryptedFileInfo&);	
	// hat der Angreifer schon eine Challenge angefangen?
	bool hasInterceptedHybridEncryptedFile() const { return isHybridEncryptedFileIntercepted; };
	// gibt den abgefangenen und verschlüsselten Session Key zurück
	OctetString getInterceptedSessionKey() const { return originalHybEncFileInfo.sessionKeyEncrypted; };
	// in welchem Schritt des Angriffs befinden wir uns?
	int getCurrentStep() const { return currentStep; };
	// der Angreifer berechnet eine (nächste) Challenge
	// aufgrund der bisher ermittelten Werten
	HybridEncryptedFileInfo nextHybridEncryptedFile();
	// der Angreifer wertet die vom Server zurückgegebene
	// Antwort aus und fährt mit seinem Angriff fort
	void processServerResponse(bool);	
	// ist der Algorithmus zu Ende durchgeführt?
	bool isDone() const { return bIsAttackDone; };
	// gibt den berechneten Session Key zurück
	std::string getComputedSecret() const { return secret; };
	// Zeiger auf modifizierte Challenge (0-indiziert)
	OctetString getModifiedChallenge(int) const;
	// wie viele modifizierte Session Keys gibt es?
	int getNumberOfModifications() const { return numberOfModifications; };
	// wie viele anfragen wurden vom server positiv beantowrtet?
	int getNumberOfPositiveResponses() const;
	// Funktionen, die den Angreifer auf einen bestimmten Zustand (ZURÜCK)setzen
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
// Der angeforderte Speicher ist nicht verfügbar
#define	E_SCA_MEMORY_ALLOCATION								2
// Fehler beim Parsen der hybridverschlüsselten Datei
#define E_SCA_HYBENCFILE_EXTRACTION							4
// die für den Angriff nötigen Voraussetzungen sind nicht erfüllt
#define E_SCA_ATTACK_CONDITIONS_NOT_MET						8
// interner Miracl-Fehler
#define E_SCA_MIRACL_ERROR									16
// Falsche PIN für Zugriff auf PSE angegeben
#define E_SCA_WRONG_PSE_PIN									32
// Timer nicht verfügbar
#define E_SCA_TIMER_NOT_AVAILABLE							64

#endif