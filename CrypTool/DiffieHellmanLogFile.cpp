// DiffieHellmanLogFile.cpp

#include "stdafx.h"
#include "CryptoolApp.h"

#include "DiffieHellmanLogFile.h"

#define BREAK	"\n\n"

// Bereits im Konstruktor wird der später abrufbare Protokolltext für das Diffie-Hellman-
// Verfahren erzeugt.

// 25.12.2002, Florian Marchal
//
// Es handelt sich hierbei um eine "Quick-and-Dirty"-Implementierung, d.h. die 
// übergebenen Eingabeparameter werden _NICHT_ geprüft. Man könnte theoretisch auch
// in dieser Klasse die übergebenen Parameter im Hinblick auf das DH-Verfahren
// überprüfen (z.B.: ist prime eine Primzahl, ist 1 < generator < prime usw...),
// jedoch ist dies hinsichtlich des Zeitplans für mein Praxisprojekt (WS 2002/2003)
// nicht mehr realisierbar.

DiffieHellmanLogFile::DiffieHellmanLogFile(std::string prime,
										   std::string generator,
										   std::string secret_alice,
										   std::string secret_bob,
										   std::string shared_alice,
										   std::string shared_bob,
										   std::string session_alice,
										   std::string session_bob)
{
	// Initialisierungen
	this->PrimeModule = prime;
	this->Generator = generator;
	this->SecretAlice = secret_alice;
	this->SecretBob = secret_bob;
	this->SharedKeyAlice = shared_alice;
	this->SharedKeyBob = shared_bob;
	this->SessionKeyAlice = session_alice;
	this->SessionKeyBob = session_bob;

	// Log-Text erzeugen
	this->LogText = "";

	CString temp;

	temp.LoadString(IDS_DH_LOG_1);
	this->LogText += temp;

	this->LogText += BREAK;

	this->LogText += "p: ";
	this->LogText += this->PrimeModule;

	this->LogText += BREAK;

	this->LogText += "g: ";
	this->LogText += this->Generator;

	this->LogText += BREAK;

	temp.LoadString(IDS_DH_LOG_2);
	this->LogText += temp;

	this->LogText += BREAK;

	this->LogText += "a: ";
	this->LogText += this->SecretAlice;

	this->LogText += BREAK;

	this->LogText += "b: ";
	this->LogText += this->SecretBob;

	this->LogText += BREAK;

	temp.LoadString(IDS_DH_LOG_3);
	this->LogText += temp;

	this->LogText += BREAK;

	this->LogText += "A: ";
	this->LogText += this->SharedKeyAlice;

	this->LogText += BREAK;

	this->LogText += "B: ";
	this->LogText += this->SharedKeyBob;

	this->LogText += BREAK;

	temp.LoadString(IDS_DH_LOG_4);
	this->LogText += temp;

	this->LogText += BREAK;

	temp.LoadString(IDS_DH_LOG_5);
	this->LogText += temp;

	this->LogText += BREAK;

	this->LogText += "SA: ";
	this->LogText += this->SessionKeyAlice;

	this->LogText += BREAK;

	this->LogText += "SB: ";
	this->LogText += this->SessionKeyBob;

	this->LogText += BREAK;

	temp.LoadString(IDS_DH_LOG_6);
	this->LogText += temp;
}

std::string DiffieHellmanLogFile::GetLogText()
{
	// Text nach 70 Zeichen umbrechen
	MakeUpText(this->LogText, 70);
	return this->LogText;
}

void DiffieHellmanLogFile::MakeUpText(std::string &in, int columns)
{
	// noch zu implementieren
}

