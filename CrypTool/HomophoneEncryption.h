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
