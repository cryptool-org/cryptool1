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


// Homophone_Ber.h: Schnittstelle für die Klasse Homophone_Ber.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOMOPHONE_BER_H__C0728084_FD9D_11D4_80F2_000629C93170__INCLUDED_)
#define AFX_HOMOPHONE_BER_H__C0728084_FD9D_11D4_80F2_000629C93170__INCLUDED_

#include "zzgen.h"	// Hinzugefügt von der Klassenansicht
#include "KeyParameterHomophone.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #define range	256 See "KeyParameterHomophone.h"

struct HomophoneData
{
	int				SizeHomophoneKey;
	bool			doNotRoundMe[range];
	double			frequency[range];
	int			  * key;
	char		  * decryptionData;
	int			    encryptionData1[range];  
	int             encryptionData0[range];
	BOOL            Init   ( const int Size );
	void			Init_Data();
	void            Release();
	BOOL            Resize ( const int Size );
};


class CHomophoneEncryption 
{
	HomophoneData   data;
	zzgen			zz;

	int				keyType;
	char			GetIndex( const int );
	int				Get_random_number(int);
	bool			Check_key();
	int				Get_free_position();
	void			Decrease_ciphers();
	void			Increase_ciphers();
	int				Checksum();

public:
					CHomophoneEncryption();
	virtual		   ~CHomophoneEncryption();

	int				GetKeyType() 
					{   return keyType; } 
	void            SetFrequency( const int i, double freq )
					{	data.frequency[i] = freq; }
	int				GetEncryptionData1(const int i)
					{	return data.encryptionData1[i]; }
	int				GetEncryptionData0(const int i)
					{	return data.encryptionData0[i]; }
	int				GetKey(const int i )
					{	return data.key[i]; }
	void            Init_Data()  
					{	data.Init_Data(); }
	int				GetKeySize() 
					{	return data.SizeHomophoneKey; }
	double			GetFrequency( const int i )
					{	return data.frequency[i]; }
	int				LogKeySize( int base )
					{	return (int)ceil( log( (double) data.SizeHomophoneKey )/log((double) base) ); }
	void			Resize( const int Size )
					{	data.Resize( Size ); }
	void			Make_enc_table(const int _keyType = HOM_ENC_TXT);
	void			Make_dec_table();
	void			load_enc_table(const char* keyStr);
	void			Generate_key();
	const char*		GetKeyStr();
	int				Encrypt(int);
    char			Decrypt( const int );
};

#endif // !defined(AFX_HOMOPHONE_BER_H__C0728084_FD9D_11D4_80F2_000629C93170__INCLUDED_)
