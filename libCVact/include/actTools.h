//////////////////////////////////////////////////////////////////////////////////
// Name:      actTools.h
// Product:   cv act library
// Purpose:   useful global functions
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_TOOLS_H
#define ACT_TOOLS_H

#include "actMode.h"
#include "actBlob.h"
#include "actIKey.h"

namespace act
{
	// Functions for RSA public key and private key operation.
	// Both functions return the plain result of the modular
	// exponentiation using the public or private exponent.
	//
	// 1) Calculate m^e mod n, where e is the public exponent
	Blob RSAPublicKeyOperation(IKey* rsa_key, const Blob& m); 
	// 2) Calculate c^d mod n, where d is the private exponent
	Blob RSAPrivateKeyOperation(IKey* rsa_key, const Blob& c); 


	// Function for PKCS#3 Diffie-Hellman.
	// The function initializes an act::IKey Diffie-Hellman key object
	// from PKCS#3 DH parameters p and g (prime and generator).
	void PKCS3DHKeyToDHKey(const Blob& prime, const Blob& generator, IKey *dhKey); 


	// Functions to encode an (EC-)DSA signature (r, s) in ASN1 format and backwards.
	//
	// 1) Plain signature I/O as string
	//	  - for encode: r and s must be in hex notation
	//	  - for decode: the user has to allocate r and s buffers
	void EncodeSignature(const char* r, const char* s, Blob& signature_ASN1);
	void DecodeSignature(const Blob& signature_ASN1, char* r, char* s);
	// 2) Plain signature I/O as byte array (Blob)
	//	  - r and s I/O in big endian representation
	void EncodeSignature(const Blob& r, const Blob& s, Blob& signature_ASN1);
	void DecodeSignature(const Blob& signature_ASN1, Blob& r, Blob& s);


	// Function to encode an ASN1 object identifier in binary form
	// example EncodeOID("0.2.262.1.10.1.3.8") = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x08 }
	Blob EncodeOID(const char* oid);


	// Converts a signed decimal number or hexadecimal number (with prefix "0x" / "-0x")
	// into a Blob (Twos-Complement representation for negative numbers)
	Blob EncodeNumber(const char* number);
	Blob EncodeNumber(int number);


	// Converts an unsigned hexadecimal number (independent of prefix "0x")
	// into a Blob and backwards.
	//  - for blob2hex: the user has to allocate hexnumber
	Blob hex2blob(const char* hexnumber);
	void blob2hex(const Blob& b, char* hexnumber); 


	// Tools for elliptic curves over GF(P).
	// The basepoint can be given by it's coordinates (Gx, Gy) or as
	// COMPRESSED, UNCOMPRESSED or HYBRID octetstring G corresponding
	// to ANSI X9.62/63 standard.
	// By default, the basepoint will be encoded in UNCOMPRESSED format.

	Blob EncodePrimeCurveParam(const Blob& p, const Blob& a, const Blob& b, 
		const Blob& Gx, const Blob& Gy, const Blob& n, const Blob& h, 
		int output_type=UNCOMPRESSED);

	Blob EncodePrimeCurveParam(const Blob& p, const Blob& a, const Blob& b, 
		const Blob& G, const Blob& n, const Blob& h, int output_type=UNCOMPRESSED);

	// dto. for elliptic curves over GF(2^m), tri- or pentanomial basis.
	
	// f(t) = t^m + t^k + 1
	Blob EncodeTrinomialCurveParam(const int m, const int k, 
		const Blob& a, const Blob& b, const Blob& Gx, const Blob& Gy,
		const Blob& n, const Blob& h, int output_type=UNCOMPRESSED);

	// f(t) = t^m + t^k + 1
	Blob EncodeTrinomialCurveParam(const int m, const int k,
		const Blob& a, const Blob& b, const Blob& G, const Blob& n,
		const Blob& h, int output_type=UNCOMPRESSED);

	// f(t) = t^m + t^k3 + t^k2 + t^k1 + 1
	Blob EncodePentanomialCurveParam(const int m, const int k3, const int k2,
		const int k1, const Blob& a, const Blob& b, const Blob& Gx, const Blob& Gy,
		const Blob& n, const Blob& h, int output_type=UNCOMPRESSED);

	// f(t) = t^m + t^k3 + t^k2 + t^k1 + 1
	Blob EncodePentanomialCurveParam(const int m, const int k3, const int k2,
		const int k1, const Blob& a, const Blob& b, const Blob& G,
		const Blob& n, const Blob& h, int output_type=UNCOMPRESSED);


	// Read pfx file and get private key
	Blob getPKCS8Key(const Blob& pfx_data, const char* password);
	// Read pfx file and get the own (user) certificate
	Blob getOwnCertificateFromPfx(const Blob& pfx_data, const char* password);


	// file i/o for act::Blob
	bool blob2file(const char* filename, const act::Blob &blob);
	bool file2blob(const char* filename, Blob &blob);


	// CRC functions

	// CRC-16   (direct mode, no zero bit augmentation)
	//
	// Poly   : 0x8005   (x^16 + x^15 + x^2 + 1)
	// RefIn  : True     (bit reflection on the input bytes)
	// RefOut : True     (bit reflection on the final CRC value)
	// XorOut : 0x0000   (no XOR on the returned CRC value)
	unsigned long CalculateCRC16(const act::byte* message, size_t message_len, 
		unsigned long crc_init_value = 0x0000);
	unsigned long CalculateCRC16(const act::Blob& message, 
		unsigned long crc_init_value = 0x0000);

	// CRC-16 CCIT   (direct mode, no zero bit augmentation)
	//
	// Poly   : 0x1021   (x^16 + x^12 + x^5 + 1)
	// RefIn  : False    (no bit reflection on the input bytes)
	// RefOut : False    (no bit reflection on the final CRC value)
	// XorOut : 0x0000   (no XOR on the returned CRC value)
	unsigned long CalculateCRC16CCITT(const act::byte* message, size_t message_len,
		unsigned long crc_init_value = 0xFFFF);
	unsigned long CalculateCRC16CCITT(const act::Blob& message, 
		unsigned long crc_init_value = 0xFFFF);

	// CRC-32   (direct mode, no zero bit augmentation)
	//
	// Poly   : 0x04C11DB7   (x^32 + x^26 +  x^23 + x^22 + x^16 + x^12 + x^11 + ...
	//                         ... + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x^ + 1)
	// RefIn  : True         (bit reflection on the input bytes)
	// RefOut : True         (bit reflection on the final CRC value)
	// XorOut : 0xFFFFFFFF   (XOR on the returned CRC value)
	unsigned long CalculateCRC32(const act::byte* message, size_t message_len,
		unsigned long crc_init_value = 0xFFFFFFFF);
	unsigned long CalculateCRC32(const act::Blob& message, 
		unsigned long crc_init_value = 0xFFFFFFFF);

} // namespace act

#endif

