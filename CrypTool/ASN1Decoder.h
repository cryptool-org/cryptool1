// ASN1Decoder.h
// Schnittstelle für die Klassen ASN1Decoder und ASN1DecoderError

#ifndef _ASN1DECODER_
#define _ASN1DECODER_

#include <string>
#include <fstream>
#include <iostream>

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

#endif