#ifndef __KEY_REPOSITORY_H
#define __KEY_REPOSITORY_H

///////////////////////////////////////////////////////////////////
//
//
//

#include "stdafx.h"
#include "CrypToolApp.h"

#define KEYDATA_TABLE_SIZE 113
#define KEYDATA_HASHSTRING_LENGTH 30

class KeyData {
	char     keytype[KEYDATA_HASHSTRING_LENGTH];
    CString  key;

public:
	KeyData() { keytype[0] = '\0'; key = _T(""); }
    friend BOOL CopyKey ( const char* KeyType, const CString &Key );
	friend BOOL PasteKey( const char* KeyType, CString &Key ); 
	friend BOOL IsKeyEmpty( const char* KeyType);
};

BOOL CopyKey ( const char* KeyType, const CString &Key );
BOOL PasteKey( const char* KeyType, CString &Key ); 
BOOL IsKeyEmpty( const char* KeyType);
BOOL ExtractStrKeyType( char * KeyType, const char* keyStr );

extern KeyData keylist[KEYDATA_TABLE_SIZE];



#endif

