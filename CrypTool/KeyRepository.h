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

