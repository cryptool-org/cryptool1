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