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


// DiffieHellmanParty.cpp

#include "stdafx.h"
#include "DiffieHellmanParty.h"
// ignore throw warnings
#pragma warning ( disable: 4290 )

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
	PublicKey = (Prime == 1) ? Big(0) : pow(Generator, Secret, Prime);
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
	SessionKey = (Prime == 1) ? Big(0) : pow(OthersPublicKey, Secret, Prime);
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
