// Homophone_Ber.h: Schnittstelle für die Klasse Homophone_Ber.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOMOPHONE_BER_H__C0728084_FD9D_11D4_80F2_000629C93170__INCLUDED_)
#define AFX_HOMOPHONE_BER_H__C0728084_FD9D_11D4_80F2_000629C93170__INCLUDED_

#include "zzgen.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define range	256

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


class HomophoneEncryption 
{
	HomophoneData   data;
	zzgen			zz;

	char			GetIndex( const int );
	int				Get_random_number(int);
	bool			Check_key();
	int				Get_free_position();
	void			Decrease_ciphers();
	void			Increase_ciphers();
	int				Checksum();

public:
					HomophoneEncryption();
	virtual		   ~HomophoneEncryption();

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
					{	return (int)ceil( log( data.SizeHomophoneKey )/log(base) ); }
	void			Resize( const int Size )
					{	data.Resize( Size ); }
	void			Make_enc_table();
	void			Make_dec_table();
	void			load_enc_table(const char* keyStr);
	void			Generate_key();
	const char*		GetKeyStr();
	int				Encrypt(int);
    char			Decrypt( const int );
};

#endif // !defined(AFX_HOMOPHONE_BER_H__C0728084_FD9D_11D4_80F2_000629C93170__INCLUDED_)
