
#include "stdafx.h"
#include "resource.h"
#include "aestoolcrypto.h"
#include <stdlib.h> // random
#include <time.h> // time
#include "rijndael-api-fst.h"


void aescbc(const void *key,int keylen,const void *iv,char direction,const void *datain, long datalen, void *dataout)
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
	VERIFY(cipherInitRijndael(&cipher,MODE_CBC,ivhex));
	long ret;
	if (direction == DIR_DECRYPT)
		ret = blockDecryptRijndael(&cipher, &keyin, (unsigned char *)datain, datalen*8, (unsigned char *)dataout);
	else
		ret = blockEncryptRijndael(&cipher, &keyin, (unsigned char *)datain, datalen*8, (unsigned char *)dataout);
	VERIFY(ret == datalen*8);
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
	char *buffer1 = 0, *buffer2 = 0;
	bool dstfilecreated = false;
	try {
		long i;

		long DataLen = srcinfo.getDataLength();
		buffer1 = (char *) malloc(DataLen);
		buffer2 = (char *) malloc(DataLen);
		if (buffer1 == 0 || buffer2 == 0) {
			if (buffer1) free(buffer1);
			if (buffer2) free(buffer2);
			errormsg.LoadString(IDS_STRING_NOMEMORY);
			return 0;
		}

		// Load Sourcedata
		unsigned mode = CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone;
		CFile SrcFile(srcinfo.getName(), mode);
		
		long datadistance2end = // not including the IV befor data
			TAILLEN + AESIVLEN + srcinfo.getDataLength() + srcinfo.getInfoBlockLength();
		SrcFile.Seek(-datadistance2end, CFile::end);
		SrcFile.ReadHuge(buffer1, DataLen);
		SrcFile.Close();

		// decrypt

		aescbc(key,keylen,srcinfo.getIV(),DIR_DECRYPT,buffer1,DataLen,buffer2);

		// remove padding
		// remove trailing 0's
		for(i=DataLen-1;i>0 && buffer2[i]==0;i--);
		// check trailing 1
		if(buffer2[i]!=1) { // display error
			errormsg.LoadString(IDS_STRING_KEYERROR);
			if (buffer1) free(buffer1);
			if (buffer2) free(buffer2);
			return 0;
		}
		DataLen = i;

		// store data
		mode = CFile::modeCreate | CFile::modeWrite | CFile::typeBinary | CFile::shareDenyWrite;
		CFile OutFile(dstname, mode);
		dstfilecreated = true;
		
		if(DataLen > 0)
			OutFile.WriteHuge(buffer2, DataLen);

	} catch (CFileException *e) {
		AesGetErrorMessage(*e,errormsg);
		if (dstfilecreated) DeleteFile(dstname);
		if (buffer1) free (buffer1);
		if (buffer2) free (buffer2);
		e->Delete();
		return 0;
	}
	if (buffer1) free (buffer1);
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
	char *buffer = 0;
	int bufflen;
	int i;
	bool dstfilecreated = false;
	
	try {
		unsigned mode = CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone;
		CFile SrcFile(srcinfo.getName(), mode);

		long DataLen = SrcFile.GetLength();
		bufflen = max(DataLen+16, 4096);
		buffer = (char *) malloc(bufflen);
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
			while((i = EXEFile.ReadHuge(buffer, bufflen)) > 0)
				OutFile.WriteHuge(buffer,i);
			EXEFile.Close();
		}
		// load Sourcedata
		SrcFile.ReadHuge(buffer, DataLen);
		SrcFile.Close();

		// generate random IV
		srand((unsigned)time(0));
		for (i = 0; i < sizeof(iv); i++) 
			iv[i] = (unsigned char)(rand() & 0xFF);
		// output IV
		OutFile.Write(iv,sizeof(iv));

		// insert padding
		buffer[DataLen]=1;
		for(i=DataLen+1;i<bufflen;i++) buffer[i]=0;
		DataLen = (DataLen+16) & ~15;

		// encrypt data
		aescbc(key,keylen,iv,DIR_ENCRYPT,buffer,DataLen,buffer);

		// store data
		OutFile.WriteHuge(buffer, DataLen);
		free (buffer); buffer = 0;

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
	file.Read(&m_datalen, sizeof(long));
	file.Read(&m_infoblocklen, sizeof(long));
	file.Read(&m_magic, sizeof(long));

	if (m_magic == FILE_MAGIC12) {
		m_exists = false; // treat like non-existing file
		return VERSION; 
	}

	long minlen = 2*AESIVLEN + m_datalen + m_infoblocklen + TAILLEN;
	if (m_magic != FILE_MAGIC)
		return OK;
	if (minlen < 0 || m_len < minlen) {
		m_exists = false;
		return CORRUPT;
	}
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
