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