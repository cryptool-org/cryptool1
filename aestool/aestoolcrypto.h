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


#ifndef _AESTOOLCRYPTO
#define _AESTOOLCRYPTO

#pragma once

#define FILE_MAGIC12	0x18273645 
#define FILE_MAGIC	0x32904ffc 
#define TAILLEN 12
#define AESBLOCKLEN 16 /* assumed to be power of 2 */
#define AESIVLEN 16

/*

  CrypTool AES file format
  
  Parameters: 
	key: AES key, 128,192 or 256 bits
	IV:  AES initialisation vector, 128 bit
	MAGIC: fixed to 0x32904FFC, LE coded
	data: data to be encrypted

  Definitions:
	padded-data: data || 0x01 || 0x00 ... 
		(0x00 repeated until length of padded-data divisible by 16)
	encdatalen: length(padded-data) = (length(data) + 1 + 15) & ~15
	infoblock: MAGIC || namelen (4 bytes, LE) || name (namelen bytes) || 0x00 ...
		(0x00 repeated until length of infoblock divisible by 16)
	infoblockbaselen: 8
	encinfoblocklen: (infoblockbaselen + namelen + 15) & ~15
	taillen: 12
	totallen: prefixlen + 2*length(IV) + encdatalen + encinfoblocklen + taillen
			  

  File format:
  BOF
  PREFIX (prefixlen bytes)
	arbitrary data (e.g. aestool.exe)

  IV (16 bytes) 

  ENCDATA (encdatalen bytes, s. INFOBLOCK)
	AES-CBC(IV,key,padded-data)

  IV (16 byte) 

  ENCINFOBLOCK (infoblocklen bytes, s. below)
	AES-CBC(IV,key,infoblock)
	
  TAIL (taillen bytes)
	encdatalen (4 bytes, LE)
	encinfoblocklen (4 bytes, LE)
    MAGIC (4 bytes, LE)

  EOF

*/

class SrcInfo {
protected:
	CString m_name;
	bool m_exists; // other fields are valid only if this is set true
	ULONGLONG m_len; // length of the file
	bool m_encrypted; // fields below are valid if this is set to true
	long m_magic; // magic value indicating file format
	unsigned char m_iv[16]; // initialisation vector
	ULONGLONG m_datalen; // length of the encrypted data
	long m_infoblocklen;
	unsigned char *m_infoblockdata;
public:
	SrcInfo() : m_exists(0), m_infoblockdata(0) { }
	~SrcInfo() { delete [] m_infoblockdata; }
	enum ReturnCode { OK, NOTREADABLE, VERSION, CORRUPT, NOMEM };
	ReturnCode setName(CString name); // opens file to determin if it is encrypted
	CString getName() const { return m_name; }
	bool exists() const { return m_exists; }
	bool isEncrypted() const { return m_exists && m_encrypted; }
	ULONGLONG getLength() const { ASSERT(m_exists); return m_len; }
	const void *getIV() const { ASSERT(isEncrypted()); return m_iv; }
	ULONGLONG getDataLength() const { ASSERT(isEncrypted()); return m_datalen; }
	const void *getInfoBlockData() const { ASSERT(isEncrypted()); return m_infoblockdata; }
	const long getInfoBlockLength() const { ASSERT(isEncrypted()); return m_infoblocklen; }

	bool isEXE() const { return m_name.Right(4).CompareNoCase(".exe") == 0; }
};

class InfoBlock {
protected:
	CString m_origname; // name before encryption
public:
	InfoBlock() { };
	InfoBlock(CString origname) : m_origname(origname) { 
		int bs = origname.ReverseFind('\\') + 1;
		m_origname = origname.Right(origname.GetLength() - bs);
	}
	enum ReturnCode { OK, VERSION, CORRUPT, NOMEM };
	ReturnCode decrypt(const SrcInfo &srcinfo,void *key,int keylen); // decrypt info block from SrcInfo; ret: 1: ok
	int encryptwrite(CFile &file,const void *key,int keylen,const void *iv); // encrypt and write to file; ret: 1: ok
	CString getOrigName() const { return m_origname; }
	int getLength() { 
		return (8 + m_origname.GetLength() + AESBLOCKLEN - 1) & ~(AESBLOCKLEN - 1); 
	}
};

bool AesToolDecrypt(const void *key,int keylen,const SrcInfo &srcinfo,
					LPCSTR dstname,CString &errormsg);
// return value: 1: OK, 0: Error

bool AesToolEncrypt(const void *key,int keylen,const SrcInfo &srcinfo,
					LPCTSTR dstname,LPCTSTR exename,CString &errormsg);
// return value: 1: OK, 0: Error
// exename == 0: AES format
// exename != 0: Name of the file to output before encrypted data

// **************************************************************************************************
// flomar, 11/29/2011: implementation of PKCS#5-esque (PBKDF2) passwords using SHA256 through OpenSSL
//
// the actual password derivation function
void createPKCS5Password(const char *password,
												 const char *salt,
												 const unsigned int iterations,
												 unsigned char **derivedPassword,
												 unsigned int *derivedPasswordLength);
// this function computes an SHA256 HMAC
void computeHMACSHA256(unsigned char *key,
											 const unsigned int keyLength,
											 unsigned char *message,
											 const unsigned int messageLength,
											 unsigned char **hmac,
											 unsigned int *hmacLength);
// **************************************************************************************************

#endif
