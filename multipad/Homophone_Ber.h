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

class Homophone_Ber 
{
public:
	void load_enc_table(const char* keyStr);
	const char * GetKeyStr();
	void Make_dec_table();
	char dec_data[257];
	int Encrypt(int);
	int key[range];
	double freq[range];
	int enc_data[range][2];
	void Generate_key();
	void Init_Data();
	void Make_enc_table();
	Homophone_Ber();
	virtual ~Homophone_Ber();

private:
	int Get_index(int);
	int Get_random_number(int);
	bool Check_key();
	int Get_free_position();
	zzgen zz;
	bool do_not_round_me[range];
	void Decrease_ciphers();
	void Increase_ciphers();
	int Checksum();
};

#endif // !defined(AFX_HOMOPHONE_BER_H__C0728084_FD9D_11D4_80F2_000629C93170__INCLUDED_)
