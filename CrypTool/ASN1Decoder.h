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

// ASN1Decoder.h
// Schnittstelle für die Klassen ASN1Decoder und ASN1DecoderError

#ifndef _ASN1DECODER_
#define _ASN1DECODER_

#pragma warning ( push )
// nothrow ignored
#pragma warning ( disable: 4290 )

#include <string>
#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#include <fstream.h>
#else
#include <iostream>
#include <fstream>
using namespace std;
#endif

class ASN1Error;

class ASN1Decoder  
{
private:
	std::string Filename;
	std::string ASN1Dump;
	std::string CertDump;

	bool bCertIsProtected;
	
public:
	// Konstruktor
	ASN1Decoder(std::string) throw (ASN1Error);
	// Destruktor
	virtual ~ASN1Decoder();

	bool IsASN1Structure();
	bool IsCertificate();
	bool IsCertProtected() const;

	void StoreASN1Dump(std::string) throw (ASN1Error);
	void StoreCertDump(std::string, std::string) throw (ASN1Error);
};

// Klasse zur Ausnahmebehandlung/Fehlerbehandlung
class ASN1Error
{
private:
	long ErrorCode;
public:
	ASN1Error(long e){ ErrorCode = e;};
	virtual ~ASN1Error() { };
	long GetErrorCode() const { return ErrorCode; };
};

// Fehlermeldungen
#define E_INVALID_FILENAME								1
#define E_NO_VALID_ASN1_STRUCTURE						2
#define E_IO_ERROR										4
#define E_CERT_WRONG_PIN								8
#define E_FILE_NOT_EXISTING								16
#define E_NO_VALID_CERTIFICATE_STRUCTURE				32

#pragma warning ( pop )
#endif