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
	void Init_Data();
	int Get_random_number(int);
	void Generate_key();
	void Calculate_ciphers(int);
	int Get_key(int);
	int Get_cipher(int);
	double Get_freq(int);
	void Set_cipher(int,int);
	void Set_freq(int,double);
	Homophone_Ber();
	virtual ~Homophone_Ber();

private:
	bool Check_key();
	int Get_free_position();
	void Set_key(int,int);
	int key[range];
	zzgen zz;
	bool Get_do_not_round_me(int);
	void Set_do_not_round_me(int,bool);
	bool do_not_round_me[range];
	void decrease_ciphers(int);
	void increase_ciphers(int);
	int checksum(int);
	int round(double);
	int ciphers [range];
	double freq[range];
};

#endif // !defined(AFX_HOMOPHONE_BER_H__C0728084_FD9D_11D4_80F2_000629C93170__INCLUDED_)
