// ASN1Decoder.cpp

#include "stdafx.h"
#include "ASN1Decoder.h"
#include "CrypToolApp.h"

extern char *CaPseVerzeichnis;

// Konstruktor
// Parameter:		Pfad zur Datei, die den ASN1-Code enth�lt
ASN1Decoder::ASN1Decoder(std::string f) throw (ASN1Error)
{
	Filename = f;
	if(Filename.empty()) throw ASN1Error(E_INVALID_FILENAME);
	bCertIsProtected = false;
	// Dokumentinhalt in Octet-String einlesen
	OctetString *encoded = theApp.SecudeLib.aux_file2OctetString( f.c_str() );
	if( encoded == NULL && ((CCrypToolApp*)AfxGetApp())->SecudeLib.LASTERROR == EFILENOTEXISTING) throw ASN1Error(E_FILE_NOT_EXISTING);
	if( encoded == NULL ) throw ASN1Error(E_IO_ERROR);
	// Dokumentinhalt nach M�glichkeit decodieren (als dump)
	ASN1Dump = theApp.SecudeLib.sdumpasn( encoded, 0, 0 );
	// Speicher freigeben
	theApp.SecudeLib.aux_free_OctetString(&encoded);
}

ASN1Decoder::~ASN1Decoder()
{
	
}

// Diese Funktion pr�ft, ob die entsprechende Datei eine g�ltige ASN1-Datei ist
// Parameter:			KEINE
// R�ckgabewert:		Falls es sich um eine ASN1-Datei handelt, true, ansonsten false
bool ASN1Decoder::IsASN1Structure() 
{
	if(ASN1Dump.find("FATAL: decoding failed!") == -1 && ASN1Dump.find("junk at end of PDU") == -1) return true;
	else return false;
}

// Diese Funktion �berpr�ft, ob die ASN1-Datei ein Zertifikat beinhaltet
// Parameter:			KEINE
// R�ckgabewert:		Falls es sich um ein Zertifikat handelt, true, ansonsten false
bool ASN1Decoder::IsCertificate()
{
	if(!IsASN1Structure()) return false;
	
	PSE PseHandle = ((CCrypToolApp*)AfxGetApp())->SecudeLib.af_open( (char*)Filename.c_str(), CaPseVerzeichnis, "NULL" , NULL);
	if(PseHandle == NULL)
	{
		// Ist die PSE vielleicht pin-gesch�tzt?
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
// R�ckgabewert:		true falls erfolgreich, ansonsten false
void ASN1Decoder::StoreASN1Dump(std::string filename) throw (ASN1Error) 
{
	if(!IsASN1Structure()) throw ASN1Error(E_NO_VALID_ASN1_STRUCTURE);
	ofstream Outfile;
	Outfile.open(filename.c_str(), ios::out | ios::trunc);
	if(!Outfile) throw ASN1Error(E_IO_ERROR);
	Outfile << ASN1Dump.c_str();
	Outfile.close();
}

// Diese Funktion extrahiert, sofern eine korrekte PIN vorliegt oder keine PIN n�tig ist, aus einer
// PSE-Datei das Zertifikat und speichert dieses auf der Festplatte
// Parameter:			Den Pfad zur Datei und die PIN, die zum �ffnen n�tig ist
// R�ckgabewert:		true f�r eine erfolgreiche Speicherung
void ASN1Decoder::StoreCertDump(std::string filename, std::string pin) throw (ASN1Error)
{
	PSE PseHandle = ((CCrypToolApp*)AfxGetApp())->SecudeLib.af_open( (char*)Filename.c_str(), CaPseVerzeichnis, (char*)pin.c_str() , NULL);

	if(PseHandle == NULL) throw ASN1Error(E_CERT_WRONG_PIN);
	// Namen auf NULL setzen, da wir von vornherein nicht wissen, um wessen Zertifikat es sich handelt,
	// und das entsprechende Zertifikat extrahieren
	DName name; name.element_IF_2=NULL;
	Certificates *zertifikate = ((CCrypToolApp*)AfxGetApp())->SecudeLib.af_pse_get_Certificates(PseHandle, ENCRYPTION, name);
	Certificate *zertifikat = zertifikate->usercertificate;
	char *ausgabe = ((CCrypToolApp*)AfxGetApp())->SecudeLib.aux_sprint_Certificate(PseHandle, NULL, zertifikat);
	ofstream outfile;
	outfile.open(filename.c_str(), ios::out | ios::trunc);
	if(!outfile) throw ASN1Error(E_IO_ERROR);
	outfile << ausgabe;
	outfile.close();
	// Speicher freigeben
	theApp.SecudeLib.aux_free_Certificates(&zertifikate);
}

// Diese Funktion gibt lediglich ggf. an, ob das Zertifikat einer PSE durch eine PIN gesch�tzt ist
// Parameter:				KEINE
// R�ckgabewert:			true falls man eine PIN zum �ffnen braucht, andernfalls false
bool ASN1Decoder::IsCertProtected() const
{
	return bCertIsProtected;
}
