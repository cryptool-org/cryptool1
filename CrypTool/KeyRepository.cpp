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
