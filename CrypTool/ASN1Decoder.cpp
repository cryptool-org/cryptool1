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

// ASN1Decoder.cpp

#include "stdafx.h"
#include "ASN1Decoder.h"
#include "CrypToolApp.h"

#pragma warning ( push )
// nothrow ignored
#pragma warning ( disable: 4290 )

extern char *CaPseVerzeichnis;

// Konstruktor
// Parameter:		Pfad zur Datei, die den ASN1-Code enthält
ASN1Decoder::ASN1Decoder(std::string f) throw (ASN1Error)
{
	Filename = f;
	if(Filename.empty()) throw ASN1Error(E_INVALID_FILENAME);
	bCertIsProtected = false;
	// Dokumentinhalt in Octet-String einlesen
	OctetString *encoded = theApp.SecudeLib.aux_file2OctetString( f.c_str() );
	if( encoded == NULL && ((CCrypToolApp*)AfxGetApp())->SecudeLib.LASTERROR == EFILENOTEXISTING) throw ASN1Error(E_FILE_NOT_EXISTING);
	if( encoded == NULL ) throw ASN1Error(E_IO_ERROR);
	// Dokumentinhalt nach Möglichkeit decodieren (als dump)
	char * decoded = theApp.SecudeLib.sdumpasn( encoded, 0, 0 );
	ASN1Dump = decoded;
	// Speicher freigeben
	theApp.SecudeLib.aux_free_String(&decoded);
	theApp.SecudeLib.aux_free_OctetString(&encoded);
}

ASN1Decoder::~ASN1Decoder()
{
	
}

// Diese Funktion prüft, ob die entsprechende Datei eine gültige ASN1-Datei ist
// Parameter:			KEINE
// Rückgabewert:		Falls es sich um eine ASN1-Datei handelt, true, ansonsten false
bool ASN1Decoder::IsASN1Structure() 
{
	if(ASN1Dump.find("FATAL: decoding failed!") == -1 && ASN1Dump.find("junk at end of PDU") == -1) return true;
	else return false;
}

// Diese Funktion überprüft, ob die ASN1-Datei ein Zertifikat beinhaltet
// Parameter:			KEINE
// Rückgabewert:		Falls es sich um ein Zertifikat handelt, true, ansonsten false
bool ASN1Decoder::IsCertificate()
{
	if(!IsASN1Structure()) return false;
	
	PSE PseHandle = ((CCrypToolApp*)AfxGetApp())->SecudeLib.af_open( (char*)Filename.c_str(), CaPseVerzeichnis, "NULL" , NULL);
	if(PseHandle == NULL)
	{
		// Ist die PSE vielleicht pin-geschützt?
		if( ((CCrypToolApp*)AfxGetApp())->SecudeLib.LASTERROR == EPIN )
		{
			bCertIsProtected = true;
			return true;
		}
		else return false;
	}
	return true;
}

// Diese Funktion speichert den ASN1-Dump  auf der Festplatte
// Parameter:			Der Pfad, unter dem man den ASN1-Dump finden kann
// Rückgabewert:		true falls erfolgreich, ansonsten false
void ASN1Decoder::StoreASN1Dump(std::string filename) throw (ASN1Error) 
{
	if(!IsASN1Structure()) throw ASN1Error(E_NO_VALID_ASN1_STRUCTURE);
	ofstream Outfile;
	Outfile.open(filename.c_str(), ios::out | ios::trunc);
	if(!Outfile) throw ASN1Error(E_IO_ERROR);
	Outfile << ASN1Dump.c_str();
	Outfile.close();
}

// Diese Funktion extrahiert, sofern eine korrekte PIN vorliegt oder keine PIN nötig ist, aus einer
// PSE-Datei das Zertifikat und speichert dieses auf der Festplatte
void ASN1Decoder::StoreCertDump(std::string filename, std::string pin) throw (ASN1Error)
{
	PSE PseHandle = ((CCrypToolApp*)AfxGetApp())->SecudeLib.af_open( (char*)Filename.c_str(), CaPseVerzeichnis, (char*)pin.c_str() , NULL);

	if(PseHandle == NULL) throw ASN1Error(E_CERT_WRONG_PIN);
	
	Certificates *zertifikate = ((CCrypToolApp*)AfxGetApp())->SecudeLib.af_pse_get_Certificates(PseHandle, ENCRYPTION, NULL);
	if ( NULL == zertifikate) 
		throw ASN1Error(E_NO_VALID_CERTIFICATE_STRUCTURE);
	Certificate *zertifikat = zertifikate->usercertificate;
	char *ausgabe = ((CCrypToolApp*)AfxGetApp())->SecudeLib.aux_sprint_Certificate(PseHandle, NULL, zertifikat);
	if ( NULL == ausgabe ) 
		throw ASN1Error(E_NO_VALID_CERTIFICATE_STRUCTURE);
	ofstream outfile;
	outfile.open(filename.c_str(), ios::out | ios::trunc);
	if(!outfile) throw ASN1Error(E_IO_ERROR);
	outfile << ausgabe;
	outfile.close();
	// Speicher freigeben
	theApp.SecudeLib.aux_free_String(&ausgabe);
	theApp.SecudeLib.aux_free_Certificates(&zertifikate);
}

// Diese Funktion gibt lediglich ggf. an, ob das Zertifikat einer PSE durch eine PIN geschützt ist
// Parameter:				KEINE
// Rückgabewert:			true falls man eine PIN zum Öffnen braucht, andernfalls false
bool ASN1Decoder::IsCertProtected() const
{
	return bCertIsProtected;
}
#pragma warning ( pop )
