// DiffieHellmanParty.cpp

#include "stdafx.h"
#include "DiffieHellmanParty.h"

// Konstruktor
// Parameter:		1) Generator, 2) Primzahl (die öffentlichen Parameter)
DiffieHellmanParty::DiffieHellmanParty(std::string g, std::string p)throw(DHError)
{
	// Initialisierungen
	this->bHasSecret = false;
	this->ErrorCode = 0;
	// Überprüfung g, setzen der Fehlerflags
	if(g.length() > MAX_KEY_LENGTH_IN_BYTE || g.empty()) this->ErrorCode |= E_GENERATOR_INVALID;
	// Überprüfung p, setzen der Fehlerflags
	if(p.length() > MAX_KEY_LENGTH_IN_BYTE || p.empty()) this->ErrorCode |= E_PRIME_INVALID;
	// Initialisierung der öffentlichen Parameter
	Generator = (char*)g.c_str();
	strGenerator = g;
	Prime = (char*)p.c_str();
	strPrime = p;
	// Primzahl testen
	if(!prime(Prime) && B_VALID_PRIMES_ONLY) this->ErrorCode |= E_PRIME_INVALID;
	// Generator testen
	if(Generator < 0) this->ErrorCode |= E_GENERATOR_INVALID;
	// Fehler auswerfen, falls nötig
	if(this->ErrorCode) throw DHError(this->ErrorCode);
}

// Destruktor
DiffieHellmanParty::~DiffieHellmanParty()
{

}

// Diese Funktion berechnet den Schlüssel, der an die andere (!) Partei geschickt wird,
// damit diese den SessionKey errechnen kann
std::string DiffieHellmanParty::GetPublicKey()throw(DHError)
{
	this->ErrorCode = 0;
	if(!this->bHasSecret) this->ErrorCode |= E_SECRET_INVALID;
	PublicKey = pow(Generator, Secret, Prime);
	// Wert der Big-Variablen PublicKey einem String zuweisen (dazu dynamischen Speicher verwenden)
	char *tempkey = new char[MAX_KEY_LENGTH_IN_BYTE];
	tempkey << PublicKey;
	strPublicKey = tempkey;
	delete tempkey;
	if(strPublicKey.length() > MAX_KEY_LENGTH_IN_BYTE) this->ErrorCode |= E_PUBLIC_KEY_INVALID;
	// Fehler auswerfen, falls nötig
	if(this->ErrorCode) throw DHError(this->ErrorCode);
	return strPublicKey;
}

// Diese Funktion gibt den FINALEN SESSION KEY zurück
// Parameter:		Den vom Gegenüber übergebenen öffentlichen Schlüssel
std::string DiffieHellmanParty::GetSessionKey(std::string k)throw(DHError)
{
	this->ErrorCode = 0;
	if(!this->bHasSecret) this->ErrorCode |= E_SECRET_INVALID;	
	if(k.length() > MAX_KEY_LENGTH_IN_BYTE) this->ErrorCode |= E_OTHERS_PUBLIC_KEY_INVALID;
	Big OthersPublicKey = (char*)k.c_str();
	SessionKey = pow(OthersPublicKey, Secret, Prime);
	// Session Key in String-Variablen ablegen
	char *tempkey = new char[MAX_KEY_LENGTH_IN_BYTE];
	tempkey << SessionKey;
	strSessionKey = tempkey;
	delete tempkey;
	if(strSessionKey.length() > MAX_KEY_LENGTH_IN_BYTE) this->ErrorCode |= E_SESSION_KEY_INVALID;
	// Fehler auswerfen, falls nötig
	if(this->ErrorCode) throw DHError(this->ErrorCode);
	return strSessionKey;
}

// Diese Funktion setzt das Geheimnis (ein zufälliges Geheimnis wird erzeugt)
// Parameter:		keine
void DiffieHellmanParty::SetSecret()
{
	// Geheimnis "ausdenken"
	irand((long)time(NULL));
	bigrand(Prime.getbig(), Secret.getbig());
	char *tempkey = new char[MAX_KEY_LENGTH_IN_BYTE];
	tempkey << Secret;
	strSecret = tempkey;
	delete tempkey;
	this->bHasSecret = true;
}

// Diese Funktion setzt das Geheimnis auf einen bestimmten Wert
// Parameter:		Das zu setzende Geheimnis
void DiffieHellmanParty::SetSecret(std::string s)throw(DHError)
{
	this->ErrorCode = 0;
	Secret = (char*)s.c_str();
	strSecret = s.c_str();
	// Fehlerflag setzen, falls nötig
	if((Secret>=Prime && B_SMALL_SECRETS_ONLY) || Secret<0) this->ErrorCode |= E_SECRET_INVALID;
	if(this->ErrorCode) throw DHError(this->ErrorCode);
	this->bHasSecret = true;
}
