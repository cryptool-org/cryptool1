// DiffieHellmanParty.h

#ifndef _DIFFIEHELLMANPARTY_
#define _DIFFIEHELLMANPARTY_

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
	Big& GetGenerator() { return Generator; };
	Big& GetPrime() { return Prime; };
	// Set-Methoden
	void SetSecret()throw(DHError);
	void SetSecret(std::string)throw(DHError);
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


#endif