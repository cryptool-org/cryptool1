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


///////////////////////////////////////////////////////////////////
//
//
//

#include "KeyRepository.h"
#include "Resource.h"

//////////////////////////////////////////////////////////////////////////////
KeyData keylist[KEYDATA_TABLE_SIZE];

// =============== TOOLS ====================================================
const int CryptMethods[] =  {
		IDS_CRYPT_CAESAR,         
		IDS_CRYPT_VIGENERE,       
		IDS_CRYPT_HILL,
		IDS_CRYPT_HOMOPHONE,      
		IDS_CRYPT_SUBSTITUTION,   
		IDS_CRYPT_PLAYFAIR,       
		IDS_CRYPT_ADDITION,       
		IDS_CRYPT_XOR,            
		IDS_CRYPT_VERNAM,         
		IDS_CRYPT_PERMUTATION,    
		IDS_CRYPT_IDEA,           
		IDS_CRYPT_RC2,            
		IDS_CRYPT_RC4,            
		IDS_CRYPT_TRIPLE_DES_ECB, // ACHTUNG "Triple DES (ECB)" steht vor "DES (ECB)" --> Teilstringproblem!
		IDS_CRYPT_TRIPLE_DES_CBC, 
		IDS_CRYPT_DES_ECB,        
		IDS_CRYPT_DES_CBC,        
		IDS_CRYPT_MARS,    
		IDS_CRYPT_RC6,     
		IDS_CRYPT_RIJNDAEL,
		IDS_CRYPT_SERPENT,
		IDS_CRYPT_TWOFISH,
		IDS_CRYPT_PRIMES,
		IDS_CRYPT_RSADEMO_PARAMETER,
		IDS_PARAM_PERMUTATION,
		IDS_PARAM_HOMOPHONE,
		IDS_PARAM_PLAYFAIR,
		IDS_PARAM_RSA_DEMO,
		IDS_ANALYSIS_SUBSTITUTION,
		IDS_CRYPT_ADFGVX,
		IDS_CRYPT_SOLITAIRE,
		IDS_CRYPT_ROT13,
		IDS_CRYPT_ATBASH,
		IDS_CRYPT_DESL,
		IDS_CRYPT_DESXL,
		IDS_CRYPT_DESX,
		IDS_CRYPT_SIMPLETRANSPOSITION,
		0
};

BOOL ExtractStrKeyType( char * KeyType, const char* keyStr )
{
	int i,j = 0;
	CString KeyString = keyStr;
	while ( CryptMethods[j] != 0 )
	{
		LoadString(AfxGetInstanceHandle(),CryptMethods[j++],pc_str,STR_LAENGE_STRING_TABLE);		
		if ( 0 <= (i = KeyString.Find( pc_str )) )
		{
			strncpy( KeyType, pc_str, KEYDATA_HASHSTRING_LENGTH );
			KeyType[KEYDATA_HASHSTRING_LENGTH] = '\0';
			return TRUE;
		}
	}
	return FALSE;
}


BOOL IsKeyEmpty( const char* KeyType)
{
	int hash = 0;
	char intKeyType[KEYDATA_HASHSTRING_LENGTH+1];
	if ( !ExtractStrKeyType( intKeyType, KeyType ) ) 
		return FALSE;

//	if ( KeyType[0] == '\0' ) return FALSE;
	for ( int i=0; intKeyType[i] != '\0' && i < KEYDATA_HASHSTRING_LENGTH; i++ ) hash += (int)intKeyType[i];

	hash %= KEYDATA_TABLE_SIZE;
	int counter = 0;
	while ( strcmp( intKeyType, keylist[hash].keytype ) && keylist[hash].keytype[0] != '\0' ) 
	{
		hash = (hash+1) % KEYDATA_TABLE_SIZE; // suche 
		if ( counter++ > KEYDATA_TABLE_SIZE ) exit(0);
	}
	if (  keylist[hash].keytype[0] == '\0' ) return FALSE;
	return TRUE;
}

BOOL CopyKey ( const char* KeyType, const CString &Key )
{
	int hash = 0;
	char intKeyType[KEYDATA_HASHSTRING_LENGTH+1];
	if ( !ExtractStrKeyType( intKeyType, KeyType ) ) 
		return FALSE;

	for ( int i=0; intKeyType[i] != '\0' && i < KEYDATA_HASHSTRING_LENGTH; i++ ) hash += (int)intKeyType[i];

	hash %= KEYDATA_TABLE_SIZE;
	int counter = 0;
	while ( strcmp( intKeyType, keylist[hash].keytype ) && keylist[hash].keytype[0] != '\0' ) 
	{
		hash = (hash+1) % KEYDATA_TABLE_SIZE; // suche 
		if ( counter++ > KEYDATA_TABLE_SIZE ) exit(0);
	}
	if ( keylist[hash].keytype[0] == '\0' ) strcpy( keylist[hash].keytype, intKeyType );
	keylist[hash].key = Key;
	return TRUE;
}


BOOL PasteKey( const char* KeyType, CString &Key )
{
	int hash = 0;
	char intKeyType[KEYDATA_HASHSTRING_LENGTH+1];
	if ( !ExtractStrKeyType( intKeyType, KeyType ) ) 
		return FALSE;
	for ( int i=0; intKeyType[i] != '\0' && i < KEYDATA_HASHSTRING_LENGTH; i++ ) hash += (int)intKeyType[i];

	hash %= KEYDATA_TABLE_SIZE;
	int counter = 0;
	while ( strcmp( intKeyType, keylist[hash].keytype ) && keylist[hash].keytype[0] != '\0' ) 
	{
		hash = (hash+1) % KEYDATA_TABLE_SIZE; // suche 
		if ( counter++ > KEYDATA_TABLE_SIZE ) exit(0);
	}
	if (  keylist[hash].keytype[0] == '\0' ) return FALSE;
	if ( !keylist[hash].key.GetLength() ) return FALSE;
	Key = keylist[hash].key;
	return TRUE;
}
