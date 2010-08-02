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


// SideChannelAttack.cpp

// ****************************************************************************
//
// 05.11.2003 Florian Marchal
// Implementierung eines Seitenkanalangriffs
// [speziell: Angriff auf Hybridverschlüsselung]
//
// ****************************************************************************

#include "stdafx.h"
#include "SideChannelAttack.h"
#include "AsymmetricEncryption.h"
#include "FileTools.h"
// #include "..\AES\mars\mars.h"
#include "ChrTools.h"
#include "CrypToolTools.h"
#include "DlgEntropyInfo.h"
#include "SymEncBase.h"

void HybridEncryptedFileInfo::init()
{
	sessionKeyEncrypted.octets=0;
	sessionKeyEncrypted.noctets=0;
	cipherText.octets=0;
	cipherText.noctets=0;
}

void HybridEncryptedFileInfo::free()
{
	if(sessionKeyEncrypted.octets)
	{
		delete sessionKeyEncrypted.octets;
		sessionKeyEncrypted.octets = 0;
		sessionKeyEncrypted.noctets = 0;
	}
	if(cipherText.octets)
	{
		delete cipherText.octets;
		cipherText.octets = 0;
		cipherText.noctets = 0;
	}
}	

void HybridEncryptedFileInfo::operator=(HybridEncryptedFileInfo &_hi)
{
	strncpy(receiverString, _hi.receiverString, SCA_MAX_LENGTH_RECEIVERSTRING);
	strncpy(receiverFirstname, _hi.receiverFirstname, SCA_MAX_LENGTH_RECEIVERFIRSTNAME);
	strncpy(receiverLastname, _hi.receiverLastname, SCA_MAX_LENGTH_RECEIVERLASTNAME);
	strncpy(receiverKeyType, _hi.receiverKeyType, SCA_MAX_LENGTH_RECEIVERKEYTYPE);
	strncpy(receiverIDStamp, _hi.receiverIDStamp, SCA_MAX_LENGTH_RECEIVERIDSTAMP);
	strncpy(sessionKeyLength, _hi.sessionKeyLength, SCA_MAX_LENGTH_SESSIONKEYLENGTH);
	strncpy(symmetricMethod, _hi.symmetricMethod, SCA_MAX_LENGTH_SYMMETRICMETHOD);
	strncpy(asymmetricMethod, _hi.asymmetricMethod, SCA_MAX_LENGTH_ASYMMETRICMETHOD);

	if(sessionKeyEncrypted.octets) delete []sessionKeyEncrypted.octets;
	sessionKeyEncrypted.octets = new char[_hi.sessionKeyEncrypted.noctets];
	if(!sessionKeyEncrypted.octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	memcpy(sessionKeyEncrypted.octets, _hi.sessionKeyEncrypted.octets, _hi.sessionKeyEncrypted.noctets);
	sessionKeyEncrypted.noctets = _hi.sessionKeyEncrypted.noctets;

	if(cipherText.octets) delete []cipherText.octets;
	cipherText.octets = new char[_hi.cipherText.noctets];
	if(!cipherText.octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	memcpy(cipherText.octets, _hi.cipherText.octets, _hi.cipherText.noctets);
	cipherText.noctets = _hi.cipherText.noctets;
}

c_scaBigNumberSettings::c_scaBigNumberSettings()
{
	m_old_mip = get_mip();
	mirsys(MAX_BIT_LENGTH/32+128,0);
	mip = get_mip();
	set_io_buffer_size(MAX_BIT_LENGTH + 1);
	set_mip(m_old_mip);
}

c_scaBigNumberSettings::~c_scaBigNumberSettings()
{
	set_mip(mip);
	mirexit();
	set_mip(m_old_mip);
}


//////////////////////////////////////////////////////////////////////////
//  SIDE CHANNEL ATTACK -- SERVER
SCA_Server::SCA_Server()
{
	// Einstellung aus .ini-Datei holen (Signifikante Bitlänge!!!)
	// Default-Wert: 128 Bit

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "SideChannelAttack" ) == ERROR_SUCCESS )
	{
		unsigned long u_significantBits = 128;

		CT_READ_REGISTRY_DEFAULT(u_significantBits, "BitlengthSecret", u_significantBits);
		significantBits = u_significantBits;

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}
	if(!significantBits) throw SCA_Error(E_SCA_INTERNAL_ERROR);

	// Speicher reservieren
	formerSessionKeys = new OctetString[significantBits+3];
	if(!formerSessionKeys) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	formerResponses = new bool[significantBits+3];
	if(!formerResponses) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	

	this->decryptedSessionKey.octets = new char[SCA_MAX_LENGTH_OCTETSTRING];
	if(!decryptedSessionKey.octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	
	this->decryptedCipherText.octets = 0;

	receivedEncryptedSessionKey = "0";
	receivedDecryptedSessionKey = "0";

	for(int i=0;i<significantBits+3;i++)
	{
		formerSessionKeys[i].octets = 0;
		formerSessionKeys[i].noctets = 0;
	
		formerResponses[i] = false;
	}

	this->numberOfReceptions = 0;
}

SCA_Server::~SCA_Server()
{
	// Speicher aufräumen
	if(decryptedSessionKey.octets) delete []decryptedSessionKey.octets;
	if(decryptedCipherText.octets) delete []decryptedCipherText.octets;
	
	for(int i=0;i<significantBits+3;i++)
	{
		if(formerSessionKeys[i].octets) delete []formerSessionKeys[i].octets;
		formerSessionKeys[i].octets = 0;
	}
   delete []formerSessionKeys;

	if(formerResponses) delete []formerResponses;
}

void SCA_Server::setPublicKey(std::string _e)
{
	this->e = (char*)_e.c_str();
}

void SCA_Server::setModulus(std::string _n)
{
	this->n = (char*)_n.c_str();
}	

void SCA_Server::setPrivateKey(std::string _d)
{
	this->d = (char*)_d.c_str();
}

void SCA_Server::setPSEData(std::string path, std::string pin)
{
	psePath = path;
	psePin = pin;
}

OctetString *SCA_Server::getFormerSessionKey(int index)
{
	if(index > numberOfReceptions)
		throw SCA_Error(E_SCA_INTERNAL_ERROR);

	return &formerSessionKeys[index];
}

bool SCA_Server::getFormerResponse(int index)
{
	if(index > numberOfReceptions)
		throw SCA_Error(E_SCA_INTERNAL_ERROR);

	return formerResponses[index];
}

// Diese Funktion "empfängt" eine beliebige hybridverschlüsselte Datei--
// kann die Datei nicht korrekt entschlüsselt werden, so gibt die Funktion
// FALSE zurück; wird die Datei korrekt entschlüsselt, wird TRUE zurückgegeben
bool SCA_Server::receiveHybridEncryptedFile(HybridEncryptedFileInfo &_hi)
{
	HybridEncryptedFileInfo hi = _hi;
	// Session Key mit privatem Schlüssel entschlüsseln und  
	// in der Variablen <decryptedSessionKey> ablegen
	decryptSessionKeyRSA(hi, psePath, psePin, &decryptedSessionKey);
	// verschlüsselte Nachricht <hi.cipherText> mit entschlüsseltem 
	// Session Key <decryptedSessionKey> entschlüsseln und in
	// <decryptedCipherText> ablegen
	decryptMessageAES(&hi.cipherText, &decryptedSessionKey, &decryptedCipherText,significantBits);
	// Feststellen, ob die Entschlüsselung korrekt funktioniert hat
	bool success = wasDecryptionSuccessful(&decryptedCipherText);
	// Antwort des Servers und zugehörigen entschlüsselten Session Key
	// für eventuelle spätere Verwendung (Report usw.) speichern
	ASSERT(numberOfReceptions < significantBits + 3);
	formerSessionKeys[numberOfReceptions].octets = new char[SCA_MAX_LENGTH_OCTETSTRING];
	if(!formerSessionKeys[numberOfReceptions].octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	formerSessionKeys[numberOfReceptions].noctets = 0;
	memcpy(formerSessionKeys[numberOfReceptions].octets, decryptedSessionKey.octets, decryptedSessionKey.noctets);
	formerSessionKeys[numberOfReceptions].noctets = decryptedSessionKey.noctets;
	// zugehörige Antwort des Servers speichern
	formerResponses[numberOfReceptions] = success;
	// Zähler erhöhen
	numberOfReceptions++;
	// Antwort des Servers zurückgeben
	return success;
}

bool SCA_Server::wasDecryptionSuccessful(OctetString *decryptedCipherText)
{
	// Florian Marchal, 05.01.2004
	// ACHTUNG,		das unten angegebene Verfahren zur Erkennung eines korrekt
	//				entschlüsselten Dokuments ist nur ein workaround. Korrekte
	//				Entschlüsselung von Entropie des Dokuments abhängig machen

	// Florian Marchal, 25.11.2004
	// ACHTUNG,		Erkennung mittels Entropie IMMER NOCH NICHT implementiert.
	//				Stattdessen gibt es zumindest ein Optionsmenü (unter weitere
	//				Optionen), mit dem man das Schlüsselwort einstellen kann,
	//				nach dem in den entsprechenden Nachrichten gesucht wird.
	
	// Diese Funktion sucht nach dem Schlüsselwort innerhalb des übergebenen OctetStrings
	// und gibt basierend auf dem Erfolg der Suche TRUE oder FALSE zurück (Ampel GRÜN/ROT)

   bool result = false;

	char *temp = new char[decryptedCipherText->noctets+1];
	if(!temp) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	memcpy(temp, decryptedCipherText->octets, decryptedCipherText->noctets);
	memcpy(temp + decryptedCipherText->noctets, "\0", 1);
	std::string strTemp = temp;

	char keyword[STR_LAENGE_STRING_TABLE+1];
   LoadString(AfxGetInstanceHandle(), IDS_SCA_KEYWORD, keyword, STR_LAENGE_STRING_TABLE);
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "SideChannelAttack" ) == ERROR_SUCCESS )
	{
		unsigned long u_keyword_maxLength = STR_LAENGE_STRING_TABLE;
		CT_READ_REGISTRY_DEFAULT(keyword, "Keyword", keyword, u_keyword_maxLength );
		CT_CLOSE_REGISTRY();
	}

   if ( !strlen(keyword) ) 
      LoadString(AfxGetInstanceHandle(), IDS_SCA_KEYWORD, keyword, STR_LAENGE_STRING_TABLE);

	ASSERT(strlen(keyword) != 0); // memcmp would always return true if keyword were empty
	// in this case we would never leave step 2 of nextHybridEncryptedFile

	// flomar, 07/15/2010
	// previously, we were doing a normal string search here; this is ok as long 
	// as we're dealing with documents that don't contain binary zeros; now we're 
	// using "memcmp" to be able to deal with binary zeros
	for(unsigned int i=0; i<=(decryptedCipherText->noctets - strlen(keyword)); i++) {
		if(memcmp(temp + i, keyword, strlen(keyword)) == 0) {
         result = true;
         break;
		}
	}

   delete []temp;

	return result;
	
	/*
	// Entropie des entschlüsselten Dokuments prüfen und somit entscheiden,
	// ob die Verschlüsselung erfolgreich war oder nicht.
	double entropy = determineEntropy(this->decryptedCipherText);
	// falls die Entropie <5.5 ist, handelt es sich um ein TEXTdokument;
	// ist die Entropie jedoch gleich oder größer 5.5, so handelt es
	// sich wahrscheinlich um ein BINÄRdokument
	if(entropy < 5.5) return true;
	*/
}

int SCA_Server::getNumberOfPositiveResponses()
{
	int successful = 0;
	ASSERT(numberOfReceptions <= significantBits + 3);
	for(int i=0;i<numberOfReceptions;i++)
		if(formerResponses[i]) successful++;

	return successful;
}

void SCA_Server::cancelRSAParameters()
{
	e = "0";
	n = "0";
	d = "0";
}

void SCA_Server::cancelPSEData()
{
	psePath = "";
	psePin = "";
}

void SCA_Server::cancelReceptions()
{
	for(int i=0;i<significantBits+3;i++)
	{
		if(formerSessionKeys[i].octets) delete formerSessionKeys[i].octets;
		formerSessionKeys[i].octets = 0;
		formerSessionKeys[i].noctets = 0;
	}
	
	numberOfReceptions = 0;	
}

void SCA_Server::cancelAttackerReceptions()
{
	for(int i=1;i<significantBits+3;i++)
	{
		if(formerSessionKeys[i].octets) delete formerSessionKeys[i].octets;
		formerSessionKeys[i].octets = 0;
		formerSessionKeys[i].noctets = 0;
	}
	
	numberOfReceptions = 1;	
}

//////////////////////////////////////////////////////////////////////////
//  SIDE CHANNEL ATTACK -- CLIENT
SCA_Client::SCA_Client()
{
	this->sessionKey = "";

	this->hi.init();
	
	statusInfo.isHybEncFileDefined = false;
	statusInfo.hasCreatedMessage = false;
	statusInfo.hasTransmittedMessage = false;
}

SCA_Client::~SCA_Client()
{
   hi.free();
}

void SCA_Client::useExistingHybEncFile(HybridEncryptedFileInfo &_hi)
{
	hi = _hi;
	statusInfo.isHybEncFileDefined = true;
	statusInfo.hasCreatedMessage = false;
}

void SCA_Client::useCreatedHybEncFile(HybridEncryptedFileInfo &_hi, std::string _s)
{
	hi = _hi;
	statusInfo.isHybEncFileDefined = true;
	statusInfo.hasCreatedMessage = true;

	sessionKey = _s;
}

HybridEncryptedFileInfo &SCA_Client::transmitHybEncFile()
{
	statusInfo.hasTransmittedMessage = true;
	return hi;
}

void SCA_Client::cancelHybridEncryptedFile()
{
	statusInfo.isHybEncFileDefined = false;
	statusInfo.hasCreatedMessage = false;
	statusInfo.hasTransmittedMessage = false;
}

void SCA_Client::cancelSessionKey()
{
	sessionKey = "";
}

void SCA_Client::cancelTransmission()
{
	statusInfo.hasTransmittedMessage = false;
}

//////////////////////////////////////////////////////////////////////////
//  SIDE CHANNEL ATTACK -- ATTACKER
SCA_Attacker::SCA_Attacker()
{
	// Einstellung aus .ini-Datei holen (Signifikante Bitlänge!!!)
	// Default-Wert: 128 Bit

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "SideChannelAttack" ) == ERROR_SUCCESS )
	{
		unsigned long u_significantBits = 128;

		CT_READ_REGISTRY_DEFAULT(u_significantBits, "BitlengthSecret", u_significantBits);
		significantBits = u_significantBits;

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}
	if(!significantBits) throw SCA_Error(E_SCA_INTERNAL_ERROR);
	
	// Speicher reservieren
	formerlyModifiedSessionKeys = new OctetString[significantBits+2]; 
	if(!formerlyModifiedSessionKeys) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	formerResponses = new bool[significantBits+2];
	if(!formerResponses) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);

	// Initialisierungen
	this->bIsAttackDone = false;
	this->currentStep = 1;
	this->secret = "";

	// initialisieren der Algorithmus-Variablen
	algVars.z = "0";
	algVars.b1 = significantBits;
	algVars.b2 = 0;
	algVars.y = "0";
	algVars.e = "0";
	algVars.n = "0";

	// bisher keine modifizierten Challenges vorhanden
	for(int i=0;i<significantBits+2;i++)
	{
		formerlyModifiedSessionKeys[i].octets = 0;
		formerlyModifiedSessionKeys[i].noctets = 0;
		
		formerResponses[i] = false;
	}
	this->numberOfModifications = 0;

	this->hi.init();
	this->isHybridEncryptedFileIntercepted = false;

	originalHybEncFileInfo.init();
}

SCA_Attacker::~SCA_Attacker()
{
	// Speicher aufräumen
	for(int i=0;i<significantBits+2;i++)
	{
		if(formerlyModifiedSessionKeys[i].octets) delete formerlyModifiedSessionKeys[i].octets;
	}
   delete []formerlyModifiedSessionKeys;

	if(formerResponses) delete []formerResponses;

	this->hi.free();

	originalHybEncFileInfo.free();

  // _CrtDumpMemoryLeaks();
}

void SCA_Attacker::setTargetPublicKey(std::string e, std::string n)
{
	this->algVars.e = e;
	this->algVars.n = n;
}

void SCA_Attacker::attackIsDone(std::string s)
{
	this->secret = s;

	this->bIsAttackDone = true;
}

OctetString SCA_Attacker::getModifiedChallenge(int index) const
{
	if(index > numberOfModifications) 
		throw SCA_Error(E_SCA_INTERNAL_ERROR);

	return formerlyModifiedSessionKeys[index];
}

// Der Angreifer fängt die Original-Challenge von Alice an Bob ab und
// extrahiert daraus die für den Angriff benötigten Informationen
// und speichert diese in der Struktur <originalHybEncFileInfo>
void SCA_Attacker::interceptHybridEncryptedFile(HybridEncryptedFileInfo &_hi)
{
	this->originalHybEncFileInfo = _hi;
	this->isHybridEncryptedFileIntercepted = true;
}

// Basierend auf dem MOMENTANTEN ZUSTAND des Angriffs ermittelt der
// Angreifer die nächste Challenge [an den Server] und gibt sie zurück
HybridEncryptedFileInfo SCA_Attacker::nextHybridEncryptedFile()
{
	// ** SCHRITT 1 **
	if( currentStep == 1 )
	{
		// <z> berechnen-- dazu sind B und N nötig
		Big base = "2";
		int exp  = algVars.b1;
		Big B = pow(base,exp);
		Big N = (char*)algVars.n.c_str();
		
		// <z> zuweisen
		algVars.z = computeZ(N,B);

		// <b'> auf den Wert von <b> setzen
		algVars.b2 = algVars.b1;

		// zum nächsten Schritt
		currentStep++;
	}
	// ** SCHRITT 2 **
	if( currentStep == 2 )
	{
		// neue Anfrage berechnen;     Cneu=Calt*(2z + 1)^e % N
		Big oldChallenge = "0";

		convertOctetStringToBigNumber(&this->originalHybEncFileInfo.sessionKeyEncrypted, oldChallenge);
		Big publicKey = (char*)algVars.e.c_str();
		Big modulus = (char*)algVars.n.c_str();

		Big newChallenge;
		
		newChallenge = (2*algVars.z)+1;
		newChallenge = pow(newChallenge, publicKey, modulus);
		newChallenge = (oldChallenge * newChallenge) % modulus;
	
		// Big-Objekt in Octet-String konvertieren
		// ACHTUNG!!!!
		// Als Ausgangslänge [in Octets] des Octet-Strings die Bitlänge
		// des RSA-Moduls der hybridverschlüsselten Datei angeben
		int outNoctets = ((atoi(originalHybEncFileInfo.sessionKeyLength)+7)/8);
				
		convertBigNumberToOctetString(newChallenge, &modifiedSessionKey, outNoctets);

		// berechnete MODIFIZIERTE Challenge zu statistischen Zwecken speichern
		ASSERT(numberOfModifications < significantBits+2);
		this->formerlyModifiedSessionKeys[numberOfModifications].octets = new char[SCA_MAX_LENGTH_OCTETSTRING];
		if(!formerlyModifiedSessionKeys[numberOfModifications].octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
		this->formerlyModifiedSessionKeys[numberOfModifications].noctets = 0;
		memcpy(	formerlyModifiedSessionKeys[numberOfModifications].octets, modifiedSessionKey.octets, modifiedSessionKey.noctets );
		formerlyModifiedSessionKeys[numberOfModifications].noctets = modifiedSessionKey.noctets;
		numberOfModifications++;

		// der "alte" Session Key wird durch den "neuen" <newSessionKey> ersetzt
		hi = originalHybEncFileInfo;
      if ( hi.sessionKeyEncrypted.octets )   // FIXME HK: MEMORY LEAK PREVENTION
         delete []hi.sessionKeyEncrypted.octets;
		hi.sessionKeyEncrypted = modifiedSessionKey;
		
		return hi;
	}
	// ** SCHRITT 3 **
	if( currentStep == 3 )
	{
		algVars.y = ( algVars.z / 2);

		currentStep++;
	}
	// ** SCHRITT 4 **
	if( currentStep == 4 )
	{
		// ***TODO**** for b'+1 times...
		while( algVars.b2 >= 0 )
		{
			// Cneu=Calt*(z+y+1)^e % N
			Big oldChallenge = "0";
			convertOctetStringToBigNumber(&this->originalHybEncFileInfo.sessionKeyEncrypted, oldChallenge);
			Big publicKey = (char*)algVars.e.c_str();
			Big modulus = (char*)algVars.n.c_str();
			
			Big newChallenge;

			newChallenge = (algVars.z + algVars.y + 1);
			newChallenge = pow(newChallenge, publicKey, modulus);
			newChallenge = (oldChallenge * newChallenge) % modulus;
	
			// Big-Objekt in Octet-String konvertieren
			// ACHTUNG!!!!
			// Als Ausgangslänge [in Octets] des Octet-Strings die Bitlänge
			// des RSA-Moduls der hybridverschlüsselten Datei angeben
			int outNoctets = ((atoi(originalHybEncFileInfo.sessionKeyLength)+7)/8);

			convertBigNumberToOctetString(newChallenge, &modifiedSessionKey, outNoctets);

			// berechnete MODIFIZIERTE Challenge zu statistischen Zwecken speichern
			ASSERT(numberOfModifications < significantBits+2);
			this->formerlyModifiedSessionKeys[numberOfModifications].octets = new char[SCA_MAX_LENGTH_OCTETSTRING];
			if(!formerlyModifiedSessionKeys[numberOfModifications].octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
			this->formerlyModifiedSessionKeys[numberOfModifications].noctets = 0;
			memcpy(	formerlyModifiedSessionKeys[numberOfModifications].octets, modifiedSessionKey.octets, modifiedSessionKey.noctets );
			formerlyModifiedSessionKeys[numberOfModifications].noctets = modifiedSessionKey.noctets;
			numberOfModifications++;
	
			algVars.b2 = (algVars.b2 - 1);

			// der "alte" Session Key wird durch den "neuen" <newSessionKey> ersetzt
			hi = originalHybEncFileInfo;
         if ( hi.sessionKeyEncrypted.octets )  // FIXME HK: prevent memory leak
            delete []hi.sessionKeyEncrypted.octets;
			hi.sessionKeyEncrypted = modifiedSessionKey;

			return hi;
		}

		currentStep++;
	}
	// ** SCHRITT 5 **
	if( currentStep == 5 )
	{
		// FINALE BERECHNUNG
		Big modulus = (char*)algVars.n.c_str();
		Big z = algVars.z;
		
		Big finalChallenge = (modulus/(z+1));

		Big bitMask;
	
		// entsprechende Bitmaske erstellen
		bitMask = "2";
		bitMask = pow( bitMask, significantBits );

		// nur die least significant bits (LSB) betrachten
		finalChallenge = finalChallenge % bitMask;

		std::string strResult;

		// Das Geheimnis müsste nun erraten sein!
		char *t = new char[80]; // FIXME HK enough MEMORY FOR 256 +3 BIT SECRETS
		if(!t) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
		t << finalChallenge;
		strResult = t;
		delete []t;

		// ENDE DES ANGRIFFS
		attackIsDone(strResult);
	}
	
	return hi;
}

// Ausgehend von der Antwort des Servers auf die zuletzt versandte
// Challenge (TRUE oder FALSE) modifiziert der Angreifer die nächste Challenge
void SCA_Attacker::processServerResponse(bool response)
{
	// das Element [numberOfModifications] ist schon das _NÄCHSTE_, d.h.
	// numberOfModifications wurde schon in der Funktion "nextHybrid..." des
	// Angreifers inkrementiert, deshalb n-1 verwenden
	formerResponses[numberOfModifications-1] = response;

	if( currentStep == 2 )
	{
		// hat der Server mit SUCCESS geantwortet?
		if(response)
		{
			algVars.z = (algVars.z * 2);
			ASSERT(algVars.b2 >= 0);
			algVars.b2 = (algVars.b2 - 1);
			return;
		}
	
		currentStep++;
	}
	if( currentStep == 4 )
	{
		// hat der Server mit SUCCESS genantwortet?
		if(response)
		{
			algVars.z = (algVars.z + algVars.y);
		}

		algVars.y = (algVars.y / 2);
	}
}

int SCA_Attacker::getNumberOfPositiveResponses() const
{
	int successful = 0;

	for(int i=0;i<numberOfModifications;i++)
		if(formerResponses[i]) successful++;

	return successful;
}

Big SCA_Attacker::computeZ(Big N, Big B)
{
	// Bitlänge des RSA-Modul <N> berechnen
	char temp[SCA_MAXIMUM_KEY_LENGTH_IN_BYTE+1];
	temp << N;
	std::string strModul = temp;
	double bitLengthModul = ceil(BitLength((CString)strModul.c_str(),10));

	// Bitlänge der bekannten Grenzen berechnen (2^b = B)
	int b = log2( B );
	
	// wenn die Bedingung L(N) > 3b+c (c = 3 genug) nicht eingehalten wird,
	// eine passende Ausnahme auswerfen.
	if( ! (bitLengthModul > (float)(3* b + 3)) )
		throw SCA_Error(E_SCA_ATTACK_CONDITIONS_NOT_MET);

	// N/B berechnen (für Berechnung von <z> nötig)
	Big fraction = ( N/B );

	Big z = "0";
	Big two = "2";
	
	for(int i=(int)bitLengthModul;i>0;i--)
	{
		if( pow(two,i) < fraction ) 
		{
			z = pow(two,i);
			break;
		}
	}
	
	return z;
}

// Diese Funktion berechnet den Logarithmus Dualis einer 2-er-Potenz.
// Ist die übergebene Zahl KEINE 2-er-Potenz, so wirft die Funktion eine Exception.
int SCA_Attacker::log2(Big b)
{
	// TODO: throw exception

	int i=0;

	while( b != "0" )
	{
		b = b/2;

		if(b == "0") break;

		i++;
	}
		
	return i;
}

void SCA_Attacker::cancelRSAParameters()
{
	this->algVars.e = "";
	this->algVars.n = "";	
}

void SCA_Attacker::cancelInterception()
{
	isHybridEncryptedFileIntercepted = false;
}

void SCA_Attacker::cancelAttack()
{
	// initialisieren der Algorithmus-Variablen
	algVars.z = "0";
	algVars.b1 = significantBits;
	algVars.b2 = 0;
	algVars.y = "0";
	
	currentStep = 1;
	secret = "";

	bIsAttackDone = false;	


	for(int i=0;i<significantBits+2;i++)
	{
		if(formerlyModifiedSessionKeys[i].octets) delete formerlyModifiedSessionKeys[i].octets;
		formerlyModifiedSessionKeys[i].octets = 0;
		formerlyModifiedSessionKeys[i].noctets = 0;
	}
	numberOfModifications = 0;
}

// ****************************************************************************
// ************************* GLOBALE FUNKTIONEN *******************************
// ****************************************************************************

// Diese Funktion wandelt einen OctetString (Binärdarstellung) in ein
// entsprechendes Big-Objekt um, damit man damit "rechnen" kann
void convertOctetStringToBigNumber(const OctetString *binaryIn, Big &bigOut)
{
	bigOut = "0";
	
	for(unsigned i=0;i<binaryIn->noctets;i++)
		bigOut = bigOut*256 + (unsigned char)binaryIn->octets[i];
}

// Diese Funktion wandelt ein Big-Objekt in einen Octet-String um
void convertBigNumberToOctetString(Big bigIn, OctetString *binaryOut, int outnoctets)
{
	if(outnoctets < 0) throw SCA_Error(E_SCA_INTERNAL_ERROR);

	char tmp;
	long number;
	Big temp = "0";

	if(outnoctets != 0)
	{
		// Speicher für Rückgabestruktur anfordern
		binaryOut->octets = new char[outnoctets];
		if(!binaryOut->octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
		binaryOut->noctets = outnoctets;

		// Rückgabestruktur "nullen"
		for(int i=0;i<outnoctets;i++)
			binaryOut->octets[i] = (unsigned char)0;

		while( bigIn > 0 )
		{
			temp = bigIn % 256;
			bigIn = bigIn / 256;

			if( --outnoctets < 0) throw SCA_Error(E_SCA_INTERNAL_ERROR);

			// BINÄRFORM des Zeichens ermitteln
			number = 0;
			
			// Falls Konvertierung unmöglich: Fehler auswerfen
			if(!convertBigTo32BitLong(temp, number))
				throw SCA_Error(E_SCA_INTERNAL_ERROR);

			tmp = (unsigned char)number;

			// Octet-String um EIN WEITERES ZEICHEN erweitern
			binaryOut->octets[outnoctets] = tmp;
		}			
	
		return;
	}
	
	
	// Speicher für Rückgabestruktur anfordern
	binaryOut->octets = new char[2048]; // FIXME HK: ENOUGH MEMORY FOR 16K NUMBERS
	if(!binaryOut->octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	binaryOut->noctets = 0;

	temp = "0";

	while( bigIn > 0 )
	{
		temp = bigIn % 256;
		bigIn = bigIn / 256;

		// BINÄRFORM des Zeichens in <tmp> an binaryOut anhängen
		number = 0;
		
		// Falls Konvertierung unmöglich: Fehler auswerfen
		if(!convertBigTo32BitLong(temp, number))
			throw SCA_Error(E_SCA_INTERNAL_ERROR);
		
		tmp = (unsigned char)number;
				
      ASSERT( binaryOut->noctets < 2048 );
		// Octet-String um EIN WEITERES ZEICHEN erweitern
		binaryOut->octets[binaryOut->noctets++] = tmp;
	}
	
	// neuen Octet-String erstellen
	OctetString *copy = new OctetString;
	if(!copy) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	copy->octets = new char[2048]; // FIXME HK: ENOUGH MEMORY FOR 16K NUMBERS
	if(!copy->octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	copy->noctets = 0;

	// Kopie vom ersten Octet-String erstellen
	memcpy(copy->octets, binaryOut->octets, binaryOut->noctets);
	copy->noctets = binaryOut->noctets;
	
	// Re-Init
	binaryOut->noctets = 0;

	// Octet-String UMDREHEN (invertieren)
	ASSERT(copy->noctets > 0);
	for(unsigned i=0; i<copy->noctets;i++)
	{
		int reverseIndex = copy->noctets - i - 1;
		// Octet-String aktualisieren
		memcpy(binaryOut->octets + binaryOut->noctets, copy->octets + reverseIndex, 1);
		binaryOut->noctets++;
	}

	// Speicher freigeben
	delete []copy->octets;
	delete copy;

	return;
}

// Diese Funktion wandelt ein Big-Objekt in einen 32-Bit-Integer-Wert
// um. Für <bigIn> größer 255 (int) gibt die Funktion FALSE zurück.
// Für <bigIn> kleiner oder gleich 255 (int) wird TRUE zurückgegeben
// und die konvertierte Zahl in <longOut>
bool convertBigTo32BitLong(const Big bigIn, long &longOut)
{
	if( bigIn > 255) return false;
	
	if( bigIn < 0 ) return false;

	// Big-Objekt in String umwandeln
	char temp[SCA_MAXIMUM_KEY_LENGTH_IN_BYTE+1];
	temp << bigIn;

	// Rückgabewert ermitteln
	longOut = (long)atoi(temp);

	return true;
}

void convertOctetStringToHexString(const OctetString *binaryIn, char *hexOut)
{
	int j=0;

	for(unsigned i=0; i<binaryIn->noctets; i++)
	{
		hexOut[j++] = ToHex(((unsigned char)binaryIn->octets[i]) / 16);
		hexOut[j++] = ToHex(((unsigned char)binaryIn->octets[i]) % 16);
	}

	// binäre Null anhängen
	hexOut[j] = '\0';
}

double determineEntropy(const char *data)
{
	char tempfile[1024];
	GetTmpName(tempfile, "cry", ".tmp");

	ofstream outfile(tempfile);
	outfile.write(data, strlen(data));
	outfile.close();

	SymbolArray text(AppConv);
	LoadText( tempfile, text );
	
	// TODO... (wieso nur EIN argument???)
	if ( !CheckTextSize( text ) )
		throw SCA_Error(E_SCA_INTERNAL_ERROR);
	
	int nalph = text.GetModulus();
	int nsymbol = 0;

	//SHOW_HOUR_GLASS

	NGram distr(text);
	for (int i = 0; i < nalph; i++) 
		if (distr[i])
			nsymbol++;

	//HIDE_HOUR_GLASS

	return distr.Entropie();
}

void decryptMessageAES(OctetString *cipherTextIn, OctetString *key, OctetString *clearTextOut, int sigBits) 
{
	// nur die niederwertigsten signifikanten Bits betrachten
	// Speicher für temporären Session Key
	char *lsbKey = new char[sigBits/8];	
	if(!lsbKey) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	// nur die signifikanten Bits in Zwischenspeicher kopieren
	memcpy(lsbKey, key->octets + (key->noctets - sigBits/8), sigBits/8);
	// nur die signifikanten Bits zurück in die Variable <key> schreiben
	memcpy(key->octets, lsbKey, sigBits/8);
	// Speicher freigeben
	delete []lsbKey;

   key->noctets = sigBits/8;
	// Speicher reservieren
	char decryptedSessionKeyHEX[65]; // FIXME HK: ENOUGH BUFFER FOR A 256 BIT AES KEY IN HEX-STR REPRESENTATION
	// entschlüsselten Session Key in HEXFORMAT umwandeln
	convertOctetStringToHexString(key, decryptedSessionKeyHEX);
	// Länge des Session Keys ermitteln (in BYTE)
	int keyLength = sigBits/8;
	// AES-Modus: ENTSCHLÜSSELN
	// char aesMode = DIR_DECRYPT;
	// Default-Algorithmus: Rijndael
	int algorithmId = 3;
	// Datenlänge bestimmen
	int dataLength = cipherTextIn->noctets;
	// Speicher anfordern
	char *cipherText = new char[dataLength + 32];
	if(!cipherText)	throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	char *clearText = new char[dataLength + 64];
	if(!clearText) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	// Speicher kopieren
	memcpy(cipherText, (unsigned char*)cipherTextIn->octets, cipherTextIn->noctets);

	// Note:  keyLength in bytes --> to be transformed in bits
	sym_decrypt(IDS_CRYPT_RIJNDAEL, CORE_PROVIDER, decryptedSessionKeyHEX, keyLength<<3, 
		cipherText, dataLength, clearText, dataLength);

	// Speicher für Rückgabewert allokieren
	if(clearTextOut->octets) delete clearTextOut->octets;
	clearTextOut->octets = new char[dataLength];
	if(!clearTextOut->octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	// entschlüsseltes Ergebnis speichern
	memcpy(clearTextOut->octets, clearText, dataLength);
	clearTextOut->noctets = dataLength;
	// Speicher freigeben
	delete []cipherText;
	delete []clearText;
}

// Diese Funktion entschlüsselt den in der HI-Struktur enthaltenen RSA-VERSCHLÜSSELTEN SESSION KEY und legt 
// ihn im letzten Eingabeparameter <decryptedSessionKey> ab. Die beiden Parameter <psePath> und <psePin> sind
// für den Zugriff auf die PSE-Datei notwendig, die den benötigten RSA-Schlüssel enthält
void decryptSessionKeyRSA(HybridEncryptedFileInfo &hi, std::string psePath, std::string psePin, OctetString *decryptedSessionKey)
{
	// Initialisierung der Variablen
	BitString in;
	OctetString out;
	in.nbits=8*(hi.sessionKeyEncrypted.noctets);
	in.bits=hi.sessionKeyEncrypted.octets;
	//out initialisieren:
	out.noctets=0;
	out.octets=(char*)malloc(in.nbits/8+256);
	if (out.octets == NULL) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	// PSE des Servers öffnen
	PSE PseHandle = theApp.SecudeLib.af_open((char*)psePath.c_str(), NULL, (char*)psePin.c_str(), NULL);
	if (PseHandle==NULL)
	{
		// Freigeben von dynamisch angelegtem Speicher
		free(out.octets);
		// Exception auswerfen
		if (theApp.SecudeLib.LASTERROR==EPIN) throw SCA_Error(E_SCA_WRONG_PSE_PIN);
		else throw SCA_Error(E_SCA_INTERNAL_ERROR);	
	}
	//Besorgen des privaten Schlüssels
	Key Schluessel;
	Schluessel.key=NULL;
	Schluessel.pse_sel=NULL;
	Schluessel.alg=theApp.SecudeLib.rsa_aid;
	Schluessel.add_object=NULL;
	Schluessel.add_object_type=NULL;
	Schluessel.key_size=NULL;
	Schluessel.private_key=NULL;
	//Entschlüsseln der Daten mittels af_decrypt_all
	int fret = theApp.SecudeLib.af_decrypt_all (PseHandle, &in, &out, &Schluessel);
	if (fret==-1)
	{	
		free(out.octets);
		throw SCA_Error(E_SCA_INTERNAL_ERROR);
	}
	//Ausgabe der verschluesselten Daten
	CString DecSessionKey;
	for (unsigned int j=0;j<out.noctets;j++)
	{
			char array[3];
			_snprintf(array,3,"%02.2X",(unsigned char) out.octets[j]);
			DecSessionKey+=array;					
	}
	// neuen entschlüsselten Session key zuweisen
	memcpy(decryptedSessionKey->octets, out.octets, out.noctets);
	decryptedSessionKey->noctets = out.noctets;
	// Freigeben von dynamisch angelegtem Speicher
	free(out.octets);
	theApp.SecudeLib.af_close (PseHandle);
}

// Diese Funktion extrahiert aus einer HYBRIDVERSCHLÜSSELTEN DATEI den Dateinamen
// des entsprechenden Zertifikats
bool extractCertFilename(const char* infile, CString &filename)
{
	OctetString *message = theApp.SecudeLib.aux_file2OctetString(infile);
	if(!message) return false;

	int start = 0;
	int end = 0;
	int save1,save2;

	// Beginn ermitteln
	if(!find(message, IDS_STRING_HYBRID_RECIEVER, start, end))
		return false;
	save1 = end;

	// Ende ermitteln
	if(!find(message, IDS_STRING_HYBRID_LENGTH_ENC_KEY, start, end))
		return false;
	save2 = start;

	// Grenzen setzen (Beginn==start, Ende=end)
	start = save1;
	end = save2;

	filename = message->octets;

	// ungewünschte Informationen abschneiden (vorne und hinten)
	filename.Delete(end, filename.GetLength()-end);
	filename.Delete(0,start);

	// Endung anhängen
	filename = filename + ".pse";
		
	return true;
}


// Diese Funktion extrahiert aus einem PSE-Dateinamen [Name][Vorname][Verfahren][Id-Stamp][Schlüsselkennung] den
// Namen, den Vornamen, das Verfahren, den ID-Stamp, die Schlüsselkennung und legt die Variablen entsprechend ab
bool extractCertInfo(const char *infile, CString &firstname, CString &lastname, CString &keytype, CString &time, CString &keyid)
{
	CString temp = "";
	CString help = "";
	int start = 0;
	int end = 0;
	
	if(!extractCertFilename(infile, temp))
		return false;

	// zunächst Endung entfernen
	temp.Delete(temp.GetLength()-4, 4);

	//[LASTNAME][FIRSTNAME][KEYTYPE][ID][KEYIDENTIFIER]

	// ACHTUNG: Nicht jede PSE besitzt einen Keyidentifier!!! Diesen daher nur bei Bedarf versuchen zu extrahieren.
	// ERKENNUNG ÜBER:	wenn die Zeichen "[" und "]" insgesamt 8 mal vorkommen -> OHNE keyid
	//					wenn ................................ 10 mal vorkommen -> MIT keyid
	// Eckige Klammern zählen...
    int bracketCount = 0;
	for(int i=0; i<temp.GetLength(); i++)
		if(temp[i] == ']' || temp[i] == '[')
			bracketCount++;

	if(bracketCount == 10)
	{
		// KEYID ermitteln
		help = temp;
		end = help.Find("]",0);
		help.Delete(0, end+1);
		end = help.Find("]",0);
		help.Delete(0, end+1);
		end = help.Find("]",0);
		help.Delete(0, end+1);
		end = help.Find("]",0);
		help.Delete(0, end+1);
		help.Delete(0,1);
		help.Delete(help.GetLength()-1,1);
		// KEYID zuweisen
		keyid = help;

		// ID ermitteln
		help = temp;
		end = help.Find("]",0);
		help.Delete(0, end+1);
		end = help.Find("]",0);
		help.Delete(0, end+1);
		end = help.Find("]",0);
		help.Delete(0, end+1);	// [xxx][ID]
		start = help.Find("[", 1);
		end = help.Find("]", start);
		help.Delete(start, end-start+1);
		help.Delete(0,1);
		help.Delete(help.GetLength()-1,1);
		// ID/TIMESTAMP zuweisen
		time = help;
	}
	else
	{
		// ID ermitteln
		help = temp;
		end = help.Find("]",0);
		help.Delete(0, end+1);
		end = help.Find("]",0);
		help.Delete(0, end+1);
		end = help.Find("]",0);
		help.Delete(0, end+1);
		help.Delete(0,1);
		help.Delete(help.GetLength()-1,1);
		// ID/TIMESTAMP zuweisen
		time = help;
	}

	// KEYTYPE ermitteln
	help = temp;
	end = help.Find("]",0);
	help.Delete(0,end+1);
	end = help.Find("]",0);
	help.Delete(0,end+1);
	end = help.Find("]",0);
	help.Delete(end, help.GetLength()-end);
	help.Delete(0,1);
	// KEYTYPE zuweisen
	keytype = help;


	// FIRSTNAME ermitteln
	help = temp;
	end = help.Find("]",0);
	help.Delete(0,end+1);
	end = help.Find("]",0);
	help.Delete(end, help.GetLength()-end);
	help.Delete(0,1);
	// FIRSTNAME zuweisen
	firstname = help;

	// LASTNAME ermitteln
	help = temp;
	end = help.Find("]",0);
	help.Delete(end, help.GetLength()-end);
	help.Delete(0,1);
	// LASTNAME zuweisen
	lastname = help;

	return true;
}

// Diese Funktion macht nichts weiter, als aus den Eingabeparametern FIRSTNAME, LASTNAME,
// KEYTYPE und TIME den Namen der entsprechenden PSE-Datei zu generieren.
CString generateCertFilename(CString firstname, CString lastname, CString keytype, CString time, CString keyid, bool fileExtension)
{
	CString filename = "";

	filename += "[";
	filename += lastname;
	filename += "][";
	filename += firstname;
	filename += "][";
	filename += keytype;
	filename += "][";
	filename += time;
	filename += "]";

	// key id NUR DANN anhängen, wenn eine key id existiert!
	if(!keyid.IsEmpty())
	{
		filename += "[";
		filename += keyid;
		filename += "]";
	}

	// Dateiendung anhängen
	if(fileExtension)
		filename += ".pse";
	
	return filename;
}

// Diese Funktion extrahiert aus einer hybridverschlüsselten Datei eine Struktur
// <HybridEncryptedFileInfo>, die folgende Einträge speichert:
//	- Empfänger der Datei (Name, Vorname, Schlüsseltyp, ID)
//  - Session Key (Länge, verschlüsselte Form)
//  - symmetrische Verschlüsselungsmethode
//  - asymmetrische Verschlüsselungsmethode
//  - Chiffretext
void extractHybridEncryptedFileInformation(const char *receivedFile, hybEncInfo &hi)
{
	CString receiverFirstname = "";
	CString receiverLastname = "";
	CString receiverKeyType = "";
	CString receiverIDStamp = "";
	CString receiverKeyId = "";

	// Zunächst wird die übergebene Datei eingelesen
	OctetString *infile = theApp.SecudeLib.aux_file2OctetString(receivedFile);
	if(!infile) throw SCA_Error(E_SCA_HYBENCFILE_EXTRACTION);

	// Variablen zum Speichern der Positionen der einzelnen Strings
	int pos_start_receiver = 0;
	int pos_end_receiver = 0;
	int pos_start_encryptedSessionKeyLength = 0;
	int pos_end_encryptedSessionKeyLength = 0;
	int pos_start_encryptedSessionKey = 0;
	int pos_end_encryptedSessionKey = 0;
	int pos_start_symmetricMethod = 0;
	int pos_end_symmetricMethod = 0;
	int pos_start_asymmetricMethod = 0;
	int pos_end_asymmetricMethod = 0;
	int pos_start_cipherText = 0;
	int pos_end_cipherText = 0;
		
	// Positionsfindung der einzelnen Strings um das Format hybridverschlüsselter
	// Dateien zu erkennen
	if	(
			!find(infile, IDS_STRING_HYBRID_RECIEVER, pos_start_receiver, pos_end_receiver) ||
			!find(infile, IDS_STRING_HYBRID_LENGTH_ENC_KEY, pos_start_encryptedSessionKeyLength, pos_end_encryptedSessionKeyLength) ||
			!find(infile, IDS_STRING_HYBRID_ENC_KEY, pos_start_encryptedSessionKey, pos_end_encryptedSessionKey) ||
			!find(infile, IDS_STRING_HYBRID_SYM_METHOD, pos_start_symmetricMethod, pos_end_symmetricMethod) ||
			!find(infile, IDS_STRING_HYBRID_ASYM_METHOD, pos_start_asymmetricMethod, pos_end_asymmetricMethod) ||
			!find(infile, IDS_STRING_HYBRID_CIPHERTEXT, pos_start_cipherText, pos_end_cipherText)
		)
	{
		// Speicher freigeben und zurückkehren
		theApp.SecudeLib.aux_free_OctetString(&infile);	
		throw SCA_Error(E_SCA_HYBENCFILE_EXTRACTION);	
	}

	// Das Format ist gültig; die einzelnen Strings werden nun rausgezogen
	// ========================================================================
	// Empfängerstring
	memcpy(hi.receiverString, infile->octets + pos_end_receiver, pos_start_encryptedSessionKeyLength - pos_end_receiver);
	// Länge des Session Key
	memcpy(hi.sessionKeyLength, infile->octets + pos_end_encryptedSessionKeyLength, pos_start_encryptedSessionKey - pos_end_encryptedSessionKeyLength);
	// verschlüsselter Session Key
	OctetString *encryptedSessionKey = new OctetString;
	if(!encryptedSessionKey) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	encryptedSessionKey->octets = new char[pos_start_symmetricMethod - pos_end_encryptedSessionKey];
	if(!encryptedSessionKey->octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	memcpy(encryptedSessionKey->octets, infile->octets + pos_end_encryptedSessionKey, pos_start_symmetricMethod - pos_end_encryptedSessionKey);
	encryptedSessionKey->noctets = pos_start_symmetricMethod - pos_end_encryptedSessionKey;
	// symmetrisches Verfahren
	memcpy(hi.symmetricMethod, infile->octets + pos_end_symmetricMethod, pos_start_asymmetricMethod - pos_end_symmetricMethod);
	// asymmetrisches Verfahren
	memcpy(hi.asymmetricMethod, infile->octets + pos_end_asymmetricMethod, pos_start_cipherText - pos_end_asymmetricMethod);
	// Chiffretext
	OctetString *cipherText = new OctetString;
	if(!cipherText) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	cipherText->octets = new char[infile->noctets - pos_end_cipherText];
	if(!cipherText->octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	memcpy(cipherText->octets, infile->octets + pos_end_cipherText, infile->noctets - pos_end_cipherText);
	cipherText->noctets = infile->noctets - pos_end_cipherText;
	// ========================================================================

	// Empfänger (einzelne Komponenten)
	extractCertInfo(receivedFile, receiverFirstname, receiverLastname, receiverKeyType, receiverIDStamp, receiverKeyId);

	// Rückgabestruktur definieren
	strcpy(hi.receiverFirstname, (char*)(LPCTSTR)receiverFirstname);
	strcpy(hi.receiverLastname, (char*)(LPCTSTR)receiverLastname);
	strcpy(hi.receiverKeyType, (char*)(LPCTSTR)receiverKeyType);
	strcpy(hi.receiverIDStamp, (char*)(LPCTSTR)receiverIDStamp);
	strcpy(hi.receiverKeyId, (char*)(LPCTSTR)receiverKeyId);

	hi.sessionKeyEncrypted.octets = new char[encryptedSessionKey->noctets];
	if(!hi.sessionKeyEncrypted.octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	memcpy(hi.sessionKeyEncrypted.octets, encryptedSessionKey->octets, encryptedSessionKey->noctets);
	hi.sessionKeyEncrypted.noctets = encryptedSessionKey->noctets;
	hi.cipherText.octets = new char[cipherText->noctets];
	if(!hi.cipherText.octets) throw SCA_Error(E_SCA_MEMORY_ALLOCATION);
	memcpy(hi.cipherText.octets, cipherText->octets, cipherText->noctets);
	hi.cipherText.noctets = cipherText->noctets;

	// Speicher freigeben und zurückkehren
	theApp.SecudeLib.aux_free_OctetString(&infile);	

   delete []encryptedSessionKey->octets;
   delete encryptedSessionKey;
	delete []cipherText->octets;
	delete cipherText;
}

void generateSCAReport(SCA_Client *_alice, SCA_Server *_bob, SCA_Attacker *_trudy, const char *filename)
{
	OctetString tempOctetString;
	char *temp = new char[4097]; // FIXME HK: HEX REPRESENTATION OF UP TO 16K RSA KEY PARAMETER
	char *protocolString = new char[16000];

	*protocolString = (unsigned char)0;

	// *** PREPARATIONS ***
	// Sub-Überschrift erstellen
	LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_HEADINGPREPARATIONS, pc_str, STR_LAENGE_STRING_TABLE);
	strcat(protocolString, pc_str);
	// Fallunterscheidung (Alice hat hybridverschlüsselte Datei SELBST ERSTELLT oder NICHT)
	if(_alice->getStatusInfo().hasCreatedMessage)
	{
		// Alice hat eine Nachricht M erstellt, die sie an Bob versenden möchte
		LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_ALICECREATEDMESSAGE, pc_str, STR_LAENGE_STRING_TABLE);
		strcat(protocolString, pc_str);
		// Alice hat einen zufälligen Session Key gewählt
		LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_ALICECHOSESESSIONKEY, pc_str, STR_LAENGE_STRING_TABLE);
		strcat(protocolString, pc_str);
		// Ausgabe des Session Keys
		strcat(protocolString, (char*)_alice->getSessionKey().c_str());
		// Alice hat die Nachricht M symmetrisch mit dem Session Key verschlüsselt
		LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_ALICEENCRYPTEDMESSAGE, pc_str, STR_LAENGE_STRING_TABLE);
		strcat(protocolString, pc_str);
		// Alice wählt Bobs öffentlichen RSA-Schlüssel e
		LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_ALICECHOSEPUBLICKEY, pc_str, STR_LAENGE_STRING_TABLE);
		strcat(protocolString, pc_str);
		// Ausgabe des öffentlichen Schlüssels
		convertBigNumberToOctetString(_bob->getPublicKey(), &tempOctetString);
		convertOctetStringToHexString(&tempOctetString, temp);
		strcat(protocolString, temp);
		// Alice verschlüsselt den Session Key symmetrisch mit e zu SK'
		LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_ALICEENCRYPTEDSESSIONKEY, pc_str, STR_LAENGE_STRING_TABLE);
		strcat(protocolString, pc_str);
		// Ausgabe des verschlüsselten Session Keys
		convertOctetStringToHexString(&_alice->getHybEncFile().sessionKeyEncrypted, temp);
		strcat(protocolString, temp);
		strcat(protocolString, "\n");
	}
	else
	{
		// Alice hat eine FREMDE, BEREITS ERSTELLTE Nachricht M verwendet
		LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_ALICETOOKEXISTINGFILE, pc_str, STR_LAENGE_STRING_TABLE);
		strcat(protocolString, pc_str);
	}

	// *** MESSAGE TRANSMISSION ***
	// Sub-Überschrift erstellen
	LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_HEADINGMESSAGETRANSMISSION, pc_str, STR_LAENGE_STRING_TABLE);
	strcat(protocolString, pc_str);
	// Alice hat die Nachricht an Bob übertragen
	LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_ALICETRANSMITTEDMESSAGE, pc_str, STR_LAENGE_STRING_TABLE);
	strcat(protocolString, pc_str);

	// *** MESSAGE INTERCEPTION ***
	// Sub-Überschrift erstellen
	LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_HEADINGMESSAGEINTERCEPTION, pc_str, STR_LAENGE_STRING_TABLE);
	strcat(protocolString, pc_str);
	// Trudy fängt die Nachricht ab
	LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_TRUDYINTERCEPTEDMESSAGE, pc_str, STR_LAENGE_STRING_TABLE);
	strcat(protocolString, pc_str);
	// Ausgabe des abgefangenen, verschlüsselten Session Keys
	convertOctetStringToHexString( &_trudy->getInterceptedSessionKey(), temp);
	strcat(protocolString, temp);

	// *** ATTACK CYCLE ***
	// Sub-Überschrift erstellen
	LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_HEADINGATTACKCYCLE, pc_str, STR_LAENGE_STRING_TABLE);
	strcat(protocolString, pc_str);
	// Trudy modifiziert den Session Key
	LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_TRUDYMODIFIEDSESSIONKEYS, pc_str, STR_LAENGE_STRING_TABLE);
	strcat(protocolString, pc_str);
	// Dieser Schritt wird SCA_SIGNIFICANT_BITS+2 mal durchgeführt
	LoadString(AfxGetInstanceHandle(), IDS_SCA_REPORT_TRUDYREPEATSMODIFICATION, pc_str, STR_LAENGE_STRING_TABLE);
	sprintf(temp, pc_str, _trudy->getNumberOfModifications());
	strcat(protocolString, temp);

	// *** DATEN IN AUSGABEDATEI SCHREIBEN ***
	ofstream outfile(filename);
   bool error = !outfile;

   if ( !error )
   {
	   outfile.write(protocolString, strlen(protocolString));
	   outfile.close();
   }
   delete []temp;
   delete []protocolString;

   if( error ){
      throw SCA_Error(E_SCA_INTERNAL_ERROR);
   }
}

// Diese Funktion überprüft, ob der übergebene OctetString ein NULLSCHLÜSSEL ist,
// d.h. es wird getestet, ob JEDES EINZELNE Octet NULL ist
bool isNullKey(const OctetString *key)
{
	int zeroOctetCounter = 0;
	for(unsigned ii=0;ii<key->noctets;ii++)
	{
		if(key->octets[ii] == (unsigned char)0)
			zeroOctetCounter++;
	}
	// Falls JEDES Octet NULL, true zurückgeben
	if(zeroOctetCounter == key->noctets)
		return true;	
	else
		return false;
}

// Diese Funktion "holt" aus einer PSE (Parameter: Vorname, Nachname, Zeitstempel) den
// öffentlichen RSA-Schlüssel e und den RSA-Modul n, beides im HEX-Format
void getPublicKey(const char *_f, const char *_l, const char *_t, char *publicKeyHEX, char *modulusHEX)
{
	CKeyFile KeyHandling;
	CString caDB_keyid_name = KeyHandling.CreateDistName(_l, _f, _t);
	// cDB_keyid_name: unter diesem Bezeichner/Namen wurde das Zertifikat in die CA-Datenbank geschrieben	

	LPTSTR string3 = new TCHAR[caDB_keyid_name.GetLength()+1];
	_tcscpy(string3, caDB_keyid_name);
	char *string4=string3; // string4 wird benutzt, um in der CA-Datenbank die Parameter abzufragen 

	// Öffnen der CA-PSE
	PSE PseHandle;
	PseHandle=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
	if (PseHandle==NULL)
	{
		// Freigeben von dynamisch angelegtem Speicher
		delete []string3;
		return;
	}	

	// Besorgen des Zertifikates der Adressaten
	SET_OF_IssuedCertificate *Liste;
	Liste=theApp.SecudeLib.af_cadb_get_user (PseHandle, string4);
	if (Liste==NULL)
	{
		// Freigeben von dynamisch angelegtem Speicher
		theApp.SecudeLib.af_close (PseHandle);
		delete []string3;
		return;
	}	

	Certificate *Zert;
	OctetString *SNummer;
	SNummer=Liste->element->serial;
	Zert=theApp.SecudeLib.af_cadb_get_Certificate (PseHandle, SNummer);
	if (Zert==NULL)
	{
		// Freigeben von dynamisch angelegtem Speicher
		theApp.SecudeLib.aux_free_SET_OF_IssuedCertificate (&Liste);
		theApp.SecudeLib.af_close (PseHandle);
		delete []string3;
		return;
	}

	// Besorgen des öffentlichen Schlüssels des Adressaten aus seinem Zertifikat
	Key Schluessel;
	Schluessel.key=Zert->tbs->subjectPK;
	Schluessel.pse_sel=NULL;
	Schluessel.alg=theApp.SecudeLib.rsa_aid;
	Schluessel.add_object=NULL;
	Schluessel.add_object_type=NULL;
	Schluessel.key_size=NULL;
	Schluessel.private_key=NULL;

	KeyBits *ki;
	ki=theApp.SecudeLib.d_KeyBits(&(Schluessel.key->subjectkey));

   for ( size_t i=0; i<ki->part1.noctets; i++ )
      sprintf( modulusHEX   + (2*i), "%02X", (unsigned char)ki->part1.octets[i] );

   for ( size_t i=0; i<ki->part2.noctets; i++ )
      sprintf( publicKeyHEX + (2*i), "%02X", (unsigned char)ki->part2.octets[i] );

   delete []string3;
}