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

// DiffieHellmanLogFile.cpp

#include "stdafx.h"
#include "CryptoolApp.h"

#include "DiffieHellmanLogFile.h"

#define BREAK	"\n\n"

// Bereits im Konstruktor wird der später abrufbare Protokolltext für das Diffie-Hellman-
// Verfahren erzeugt.

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

	// Florian Marchal, 10.05.2004
	// Sind <a> oder <b> größer oder gleich <p>, so werden
	// <a> und/oder <b> jeweils Modulo <p> reduziert
	Big bigA = (char*)SecretAlice.c_str();
	Big bigB = (char*)SecretBob.c_str();
	Big bigM = (char*)PrimeModule.c_str();
	// Berechnung der "tatsächlichen" Werte
	Big realA = bigA % bigM;
	Big realB = bigB % bigM;
	std::string strA;
	std::string strB;
	pc_str << realA;
	strA = pc_str;
	pc_str << realB;
	strB = pc_str;
	// Ausgabe Informationstext
	temp.LoadString(IDS_DH_LOG_7);
	this->LogText += temp;
	this->LogText += BREAK;
	// Angabe der tatsächlichen Werte von A...
	temp.LoadString(IDS_DH_LOG_VALUE_A);
	this->LogText += temp;
	this->LogText += strA;
	this->LogText += BREAK;
	// ...und B
	temp.LoadString(IDS_DH_LOG_VALUE_B);
	this->LogText += temp;
	this->LogText += strB;
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

