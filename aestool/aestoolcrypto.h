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

#endif
