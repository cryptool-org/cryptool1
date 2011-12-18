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



#include "stdafx.h"
#include "resource.h"
#include "aestoolcrypto.h"
#include <stdlib.h> // random
#include <time.h> // time
#include "rijndael-api-fst.h"

#define BUFFSIZE (4096)

void aescbc(const void *key,int keylen,const void *iv,char direction,const void *datain, unsigned long datalen, void *dataout)
// all len(ths) in bytes, direction: DIR_DECRYPT or DIR_ENCRYPT
// datain and dataout may be identical for encryption
{
	int i;
	unsigned char *p;
	char keyhex[2*256/8+1];
	char ivhex[2*256/8+1];

	int keylen0 = keylen;
	if(keylen0 <= 16) 
		keylen = 16;
	else if(keylen0 <= 24) 
		keylen = 24;
	else 
		keylen = 32;

	p = (unsigned char*)key;
	for(i=0; i < keylen; i++)
		sprintf(keyhex+2*i,"%02.2X", i < keylen0 ? p[i] : 0);
	
	p = (unsigned char*)iv;
	for(i=0; i < AESIVLEN; i++)
		sprintf(ivhex+2*i,"%02.2X", p[i]);
	
	keyInstanceRijndael keyin;
	cipherInstanceRijndael cipher;
	VERIFY(makeKeyRijndael(&keyin,direction,keylen*8,keyhex));
	VERIFY(cipherInitRijndael(&cipher,ivhex));
	unsigned long ret;
	if (direction == DIR_DECRYPT)
		ret = blockDecryptRijndael(&cipher, &keyin, (unsigned char *)datain, datalen, (unsigned char *)dataout);
	else
		ret = blockEncryptRijndael(&cipher, &keyin, (unsigned char *)datain, datalen, (unsigned char *)dataout);
	VERIFY(ret == datalen);
}

void AesGetErrorMessage(CFileException &e,CString &errormsg)
{
	e.GetErrorMessage(errormsg.GetBuffer(1024),1024);
	errormsg.ReleaseBuffer();
}

bool AesToolDecrypt(const void *key,int keylen,const SrcInfo &srcinfo,
					LPCSTR dstname,CString &errormsg)
// return value: 1: OK, 0: Error
{
	unsigned char *buffer1 = 0, *buffer2 = 0;
	unsigned long bufflen;
	ULONGLONG ResData;
	bool dstfilecreated = false;
	try {
		long i;

		ULONGLONG DataLen = ResData = srcinfo.getDataLength();
		bufflen = BUFFSIZE;
		buffer2 = (unsigned char *) malloc(bufflen+32);
		buffer1 = buffer2+32;
		if (buffer1 == 0 || buffer2 == 0) {
			if (buffer2) free(buffer2);
			errormsg.LoadString(IDS_STRING_NOMEMORY);
			return 0;
		}

		// Load Sourcedata
		unsigned mode = CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone;
		CFile SrcFile(srcinfo.getName(), mode);

		// prepare key
		char keyhex[2*256/8+1];
		char ivhex[2*256/8+1];

		int keylen0 = keylen;
		if(keylen0 <= 16) 
			keylen = 16;
		else if(keylen0 <= 24) 
			keylen = 24;
		else 
			keylen = 32;

		unsigned char * p = (unsigned char*)key;
		for(i=0; i < keylen; i++)
			sprintf(keyhex+2*i,"%02.2X", i < keylen0 ? p[i] : 0);
	
		p = (unsigned char *) srcinfo.getIV();
		for(i=0; i < AESIVLEN; i++)
			sprintf(ivhex+2*i,"%02.2X", p[i]);

		keyInstanceRijndael keyin;
		cipherInstanceRijndael cipher;
		VERIFY(makeKeyRijndael(&keyin,DIR_DECRYPT,keylen*8,keyhex));
		VERIFY(cipherInitRijndael(&cipher,ivhex));

		ULONGLONG datadistance2end = // not including the IV before data
			TAILLEN + AESIVLEN + srcinfo.getDataLength() + srcinfo.getInfoBlockLength();
		SrcFile.Seek(srcinfo.getLength()-datadistance2end, CFile::begin);

		// Prepare Outfile
		mode = CFile::modeCreate | CFile::modeWrite | CFile::typeBinary | CFile::shareDenyWrite;
		CFile OutFile(dstname, mode);
		dstfilecreated = true;

		// load Sourcedata
		while((i = SrcFile.Read(buffer1, (UINT) (min(bufflen,ResData)))) > 0) {

			ResData -= i;
			// decrypt data
			long ret = blockDecryptRijndael(&cipher, &keyin, buffer1, i, buffer2);
			VERIFY(ret == i);

			if(ResData == 0) {
				// remove padding
				// remove trailing 0's
				for(i--;i>0 && buffer2[i]==0;i--);
				// check trailing 1
				if(buffer2[i]!=1) { // display error
					char stringBuffer[2048+1];
					char stringErrorMessage[2048+1];
					memset(stringBuffer, 0, 2048+1);
					memset(stringErrorMessage, 0, 2048+1);
					LoadString(AfxGetInstanceHandle(), IDS_STRING_KEYERROR, stringBuffer, 2048);
					sprintf(stringErrorMessage, stringBuffer, SrcFile.GetFileName().GetBuffer());
					errormsg = stringErrorMessage;
					if (buffer2) free(buffer2);
					return 0;
				}
			}
			// store data
			OutFile.Write(buffer2, i);
		}

		SrcFile.Close();

	} catch (CFileException *e) {
		AesGetErrorMessage(*e,errormsg);
		if (dstfilecreated) DeleteFile(dstname);
		if (buffer2) free (buffer2);
		e->Delete();
		return 0;
	}
	if (buffer2) free (buffer2);
	return 1;
}

// return value: 1: OK, 0: Error

bool AesToolEncrypt(const void *key,int keylen,const SrcInfo &srcinfo,
					LPCTSTR dstname,LPCTSTR exename,CString &errormsg)
// exename == 0: AES format
// exename != 0: Name of the file to output before encrypted data
{
	unsigned char iv[AESIVLEN];
	CString Message;
	CFile EXEFile;
	CFileException e;
	unsigned char *buffer = 0;
	int bufflen;
	int i;
	bool dstfilecreated = false;
	ULONGLONG ResData;
	
	try {
		unsigned mode = CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone;
		CFile SrcFile(srcinfo.getName(), mode);

		ULONGLONG DataLen = ResData = SrcFile.GetLength();
		bufflen = BUFFSIZE;
		buffer = (unsigned char *) malloc(bufflen+16);
		if (!buffer) {
			errormsg.Format(IDS_STRING_NOMEMORY);
			return 0;
		}

		if(exename) { 
			mode = CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone;
			if (!EXEFile.Open(exename, mode, &e)) {
				AesGetErrorMessage(e,errormsg);
				free(buffer);
				return 0;
			}
		}

		mode = CFile::modeCreate | CFile::modeWrite | CFile::typeBinary | CFile::shareDenyWrite;
		CFile OutFile(dstname, mode);
		dstfilecreated = true;

		if(exename) { // copy EXE-File first
			while((i = EXEFile.Read(buffer, bufflen)) > 0)
				OutFile.Write(buffer,i);
			EXEFile.Close();
		}
		// generate random IV
		srand((unsigned)time(0));
		for (i = 0; i < sizeof(iv); i++) 
			iv[i] = (unsigned char)(rand() & 0xFF);
		// output IV
		OutFile.Write(iv,sizeof(iv));

		// prepare key
		char keyhex[2*256/8+1];
		char ivhex[2*256/8+1];

		int keylen0 = keylen;
		if(keylen0 <= 16) 
			keylen = 16;
		else if(keylen0 <= 24) 
			keylen = 24;
		else 
			keylen = 32;

		unsigned char * p = (unsigned char*)key;
		for(i=0; i < keylen; i++)
			sprintf(keyhex+2*i,"%02.2X", i < keylen0 ? p[i] : 0);
	
		p = (unsigned char*)iv;
		for(i=0; i < AESIVLEN; i++)
			sprintf(ivhex+2*i,"%02.2X", p[i]);

		keyInstanceRijndael keyin;
		cipherInstanceRijndael cipher;
		VERIFY(makeKeyRijndael(&keyin,DIR_ENCRYPT,keylen*8,keyhex));
		VERIFY(cipherInitRijndael(&cipher,ivhex));

		// load Sourcedata
		DataLen = 0;
		while((i = SrcFile.Read(buffer, bufflen)) > 0) {
			ResData -= i;
			if(ResData == 0) { // insert padding
				buffer[i] = 1;
				for(i++; i & 15; i++) buffer[i]=0;
			}
			// encrypt data
			long ret = blockEncryptRijndael(&cipher, &keyin, buffer, i, buffer);
			VERIFY(ret == i);
			// store data
			DataLen += i;
			OutFile.Write(buffer, i);

		}
		SrcFile.Close();

		free (buffer); buffer = NULL;

		// output IV
		OutFile.Write(iv,sizeof(iv));

		// store info block
		InfoBlock info(srcinfo.getName());
		if (info.encryptwrite(OutFile,key,keylen,iv) == InfoBlock::NOMEM) {
			errormsg.Format(IDS_STRING_NOMEMORY);
			OutFile.Close();
			DeleteFile(dstname);
			return 0;
		}

		// store lengthes, magic
		long Magic = FILE_MAGIC;
		OutFile.Write(&DataLen, sizeof(long));
		long infolen = info.getLength();
		OutFile.Write(&infolen, sizeof(long));
		OutFile.Write(&Magic, sizeof(long));

		OutFile.Close();
	} catch (CFileException *e) {
		AesGetErrorMessage(*e,errormsg);
		if (dstfilecreated) DeleteFile(dstname);
		if (buffer)	free(buffer);
		e->Delete();
 		return 0;
	}
	return 1;
}

SrcInfo::ReturnCode SrcInfo::setName(CString name)
{
	if (name == m_name && m_exists)
		return OK;
	m_name = name;
	m_exists = false;
	CFile file;
	long mode = CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary;
	if (!file.Open(name,mode))
		return NOTREADABLE;
	m_exists = true;

	m_encrypted = false;
	m_len = file.GetLength();
	if (m_len < TAILLEN) 
		return OK;
	file.Seek(-TAILLEN, CFile::end);
	m_datalen = m_len;
	file.Read(&m_datalen, sizeof(long));
	if(m_datalen > m_len) {
		m_datalen -= (1 << 31);
		m_datalen -= (1 << 31);
	}
	file.Read(&m_infoblocklen, sizeof(long));
	file.Read(&m_magic, sizeof(long));

	if (m_magic == FILE_MAGIC12) {
		m_exists = false; // treat like non-existing file
		return VERSION; 
	}

	if (m_magic != FILE_MAGIC)
		return OK;
	m_encrypted = true;
	m_infoblockdata = new unsigned char[m_infoblocklen];
	if (!m_infoblockdata) {
		m_exists = false;
		return NOMEM;
	}
	file.Seek(-(AESIVLEN + m_infoblocklen + TAILLEN), CFile::end);
	file.Read(m_iv,AESIVLEN);
	file.Read(m_infoblockdata,m_infoblocklen);
	return OK;
}

InfoBlock::ReturnCode InfoBlock::decrypt(const SrcInfo &srcinfo,void *key,int keylen)
{
	VERIFY(srcinfo.isEncrypted());
	unsigned char *buffer = new unsigned char[srcinfo.getInfoBlockLength()];
	if (!buffer)
		return NOMEM;

	aescbc(key,keylen,srcinfo.getIV(),DIR_DECRYPT,
		srcinfo.getInfoBlockData(),srcinfo.getInfoBlockLength(),buffer);
	
	long magic = *(long*)buffer;
	if (magic != FILE_MAGIC)
		return delete [] buffer, CORRUPT;
	long namelen = *(long*)(buffer + 4);
	if (8 + namelen > srcinfo.getInfoBlockLength())
		return delete [] buffer, CORRUPT;
	m_origname = CString((LPCTSTR)(buffer + 8),namelen);
	delete [] buffer;
	return OK;
}

int InfoBlock::encryptwrite(CFile &file,const void *key,int keylen,const void *iv)
// encrypt and write to file; ret: 1: ok
{
	int bufferlen = getLength();
	unsigned char *buffer = new unsigned char [bufferlen];
	if (!buffer)
		return NOMEM;
	// magic
	int i = 0;
	*(long*)(buffer + i) = FILE_MAGIC;
	i += sizeof(long);
	// original name length
	*(long*)(buffer + i) = m_origname.GetLength();
	i += sizeof(long);
	// orignal name
	memcpy(buffer + i,(LPCTSTR)m_origname,m_origname.GetLength());
	i += m_origname.GetLength();
	// zero padding
	while (i < bufferlen)
		buffer[i++] = 0;
	aescbc(key,keylen,iv,DIR_ENCRYPT,buffer,bufferlen,buffer);
	file.Write(buffer,bufferlen);
	delete [] buffer;
return 0;

}

// **************************************************************************************************
// flomar, 11/29/2011: implementation of PKCS#5-esque (PBKDF2) passwords using SHA256 through OpenSSL
namespace __SSL {
	#include "..\OpenSSL\sha.h"
}

void createPKCS5Password(const char *password, const char *salt, const unsigned int iterations, unsigned char **derivedPassword, unsigned int *derivedPasswordLength) {
	// some constants for the password creation
	const unsigned int passwordLength = strlen(password);
	const unsigned int saltLength = strlen(salt);
	// set the correct length for the derived password (SHA256 equals 32 bytes)
	*derivedPasswordLength = 32;
	// allocate memory for derived password
	*derivedPassword = new unsigned char[*derivedPasswordLength];
	// hash password, salt, and block index
	__SSL::SHA256_CTX ctx;
	__SSL::SHA256_Init(&ctx);
	__SSL::SHA256_Update(&ctx, password, passwordLength);
	__SSL::SHA256_Update(&ctx, salt, saltLength);
	for(unsigned int i=0; i<4; i++) {
		// the block index is constant at "1" for our implementation
		const unsigned int blockIndex = 1;
		unsigned char byte = (unsigned char)(blockIndex >> ((3-i)*8));
		__SSL::SHA256_Update(&ctx, &byte, 1);
	}
	__SSL::SHA256_Final(*derivedPassword, &ctx);
	// execute the desired number of iterations (see input parameter "iterations")
	unsigned char *temp = new unsigned char[*derivedPasswordLength];
	for(unsigned int iteration=1; iteration<iterations; iteration++) {
			__SSL::SHA256_CTX ctx;
			__SSL::SHA256_Init(&ctx);
			__SSL::SHA256_Update(&ctx, password, passwordLength);
			__SSL::SHA256_Update(&ctx, *derivedPassword, *derivedPasswordLength);
			__SSL::SHA256_Final(temp, &ctx);
			for(unsigned int i=0; i<*derivedPasswordLength; i++) {
				(*derivedPassword)[i] ^= temp[i];
			}
	}
	delete[] temp;
}

void computeHMACSHA256(unsigned char *key, const unsigned int keyLength, unsigned char *message, const unsigned int messageLength, unsigned char **hmac, unsigned int *hmacLength) {
	const unsigned int blockSize = 64;
	// the local key we're working on
	unsigned char localKey[blockSize];
	// hash key if it's too long
	if(keyLength > blockSize) {
		__SSL::SHA256(key, keyLength, localKey);
	}
	// pad key if it's too short
	if(keyLength < blockSize) {
		memcpy(localKey, key, keyLength);
		memcpy(localKey + keyLength, 0, blockSize - keyLength);
	}
	// otherwise simply copy key to localKey
	if(keyLength == blockSize) {
		memcpy(localKey, key, keyLength);
	}
	// create inner and outer key pads for SHA256 (32 bytes)
	unsigned char outerKeyPad[32];
	memset(outerKeyPad, 92, 32);				// 92 == 0x5c
	unsigned char innerKeyPad[32];
	memset(innerKeyPad, 54, 32);				// 54 == 0x36
	// apply local key
	for(unsigned int i=0; i<32; i++) {
		outerKeyPad[i] ^= localKey[i];
		innerKeyPad[i] ^= localKey[i];
	}
	// compute HMAC
	unsigned char innerHash[32];
	unsigned char outerHash[32];
	__SSL::SHA256_CTX ctxOuter;
	__SSL::SHA256_Init(&ctxOuter);
	__SSL::SHA256_Update(&ctxOuter, outerKeyPad, 32);
	__SSL::SHA256_CTX ctxInner;
	__SSL::SHA256_Update(&ctxInner, innerKeyPad, 32);
	__SSL::SHA256_Update(&ctxInner, message, messageLength);
	__SSL::SHA256_Final(innerHash, &ctxInner);
	__SSL::SHA256_Update(&ctxOuter, innerHash, 32);
	__SSL::SHA256_Final(outerHash, &ctxOuter);
	// set output variables
	memcpy(*hmac, outerHash, 32);
	*hmacLength = 32;
}
// **************************************************************************************************