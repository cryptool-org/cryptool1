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

namespace act
{
	// Functions to encode a signature (r, s) in ASN1 format and backwards.
	//  - for encode: r and s must be in hex notation
	//  - for decode: the user has to allocate r and s
	void EncodeSignature (const char* r, const char* s, Blob& signature);
	void DecodeSignature (const Blob& signature, char* r, char* s);


	// Function to encode an ASN1 object identifier in binary form
	// example EncodeOID("0.2.262.1.10.1.3.8") = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x08 }
	Blob EncodeOID (const char* oid);


	// Converts a signed decimal number or hexadecimal number (with prefix "0x" / "-0x")
	// into a Blob (Twos-Complement representation for negative numbers)
	Blob EncodeNumber (const char* number);
	Blob EncodeNumber (int number);


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
	Blob EncodePrimeCurveParam (const Blob& p,
								const Blob& a,
								const Blob& b,
								const Blob& Gx,
								const Blob& Gy,
								const Blob& n,
								const Blob& h,
								int output_type=UNCOMPRESSED);
	Blob EncodePrimeCurveParam (const Blob& p,
								const Blob& a,
								const Blob& b,
								const Blob& G,
								const Blob& n,
								const Blob& h,
								int output_type=UNCOMPRESSED);

	// dto. for elliptic curves over GF(2^m), tri- or pentanomial basis.
	Blob EncodeTrinomialCurveParam (const int m, 
									const int k, // t^m + t^k + 1
									const Blob& a,
									const Blob& b,
									const Blob& Gx,
									const Blob& Gy,
									const Blob& n,
									const Blob& h,
									int output_type=UNCOMPRESSED);
	Blob EncodeTrinomialCurveParam (const int m, 
									const int k,
									const Blob& a,
									const Blob& b,
									const Blob& G,
									const Blob& n,
									const Blob& h,
									int output_type=UNCOMPRESSED);
	Blob EncodePentanomialCurveParam (	const int m, 
										const int k3,
										const int k2, 
										const int k1, // t^m + t^k3 + t^k2 + t^k1 + 1
										const Blob& a,
										const Blob& b,
										const Blob& Gx,
										const Blob& Gy,
										const Blob& n,
										const Blob& h,
										int output_type=UNCOMPRESSED);
	Blob EncodePentanomialCurveParam (	const int m, 
										const int k3,
										const int k2, 
										const int k1,
										const Blob& a,
										const Blob& b,
										const Blob& G,
										const Blob& n,
										const Blob& h,
										int output_type=UNCOMPRESSED);
	//read pfx file and get private key
	Blob getPKCS8Key(const Blob& pfx_data,const char* password);
	//read pfx file and get the own (user) certificate
	Blob getOwnCertificateFromPfx(const Blob& pfx_data,const char* password);


	bool blob2file(const char* filename, const act::Blob &blob);
	bool file2blob(const char* filename, Blob &blob);
		

} // namespace act

#endif

