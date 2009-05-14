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

// DiffieHellmanParty.h

#ifndef _DIFFIEHELLMANPARTY_
#define _DIFFIEHELLMANPARTY_

#pragma warning( push )
#pragma warning( disable: 4290 )

/*****************************************************************/
// Sollen NUR ECHTE PRIMZAHLEN als Primzahlmodul zugelassen werden?
#define B_VALID_PRIMES_ONLY			false
// Dürfen NUR Geheimnisse KLEINER dem Primzahlmodul gewählt werden?
#define B_SMALL_SECRETS_ONLY		false
/*****************************************************************/

// Miracl-Bibliothek (für große Zahlen)
#include "../libmiracl/include/BIG.H"

#include <string>

class DHError;

class DiffieHellmanParty
{
private:
	// Privates Geheimnis der Partei
	Big Secret;
	// Der öffentliche Schlüssel (zu senden an andere Partei)
	Big PublicKey;
	// Der am Ende zu ermittelnde GEMEINSAME Session Key
	Big SessionKey;
	// Kopien der öffentlichen Parameter
	Big Generator;
	Big Prime;

	// Interne Statusflags
	bool bHasSecret;
	long ErrorCode;
	
	// Hilfsvariablen (keine Big-Objekte sondern std::string)
	std::string strGenerator;
	std::string strPrime;
	std::string strPublicKey;
	std::string strSessionKey;
	std::string strSecret;
	
public:
	// Konstruktion/Destruktion
	DiffieHellmanParty(std::string,std::string)throw(DHError);
	virtual ~DiffieHellmanParty();
	// Get-Methoden
	std::string GetPublicKey()throw(DHError);
	std::string GetSessionKey(std::string)throw(DHError);
	std::string GetStrGenerator() { return strGenerator; };
	std::string GetStrPrime() { return strPrime; };
	Big& GetGenerator() { return Generator; };
	Big& GetPrime() { return Prime; };
	// Set-Methoden
	void SetSecret()throw(DHError);
	void SetSecret(std::string)throw(DHError);

	// Diese Methode GIBT DAS GEHEIMNIS PREIS
	// "quick-n-dirty"-Implementierung der Klasse DiffieHellmanLogFile
	std::string GetStrSecret() { return strSecret; };
	bool HasSecret() { return bHasSecret; };
};

// Klasse zur Ausnahmebehandlung/Fehlerbehandlung
class DHError
{
private:
	long ErrorCode;

public:
	DHError(long e) { ErrorCode = e; };
	
	long GetErrorCode() { return ErrorCode; };
};

// Fehlercodes
#define E_GENERATOR_INVALID									1
#define E_PRIME_INVALID										2
#define E_SECRET_INVALID									4
#define E_PUBLIC_KEY_INVALID								8
#define E_OTHERS_PUBLIC_KEY_INVALID							16
#define E_SESSION_KEY_INVALID								32
//*** Sonstige #define-Anweisungen
#define MAX_KEY_LENGTH_IN_BYTE								310 // 1024 Bit in etwa 308,xx Dezimalstellen

#pragma warning ( pop )
#endif