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
	void Generate_key();
	int Get_key(int);
	int Get_cipher(int);
	Homophone_Ber();
	virtual ~Homophone_Ber();

private:
	int Get_free_position();
	void Set_key(int,int);
	int key[range];
	zzgen zz;
	bool Get_do_not_round_me(int);
	void Set_do_not_round_me(int,bool);
	bool do_not_round_me[26];
	void decrease_ciphers();
	void increase_ciphers();
	int checksum();
	int round(double);
	double Get_freq(int);
	void Set_cipher(int,int);
	void Set_freq(int,double);
	void Calculate_ciphers();
	int ciphers [26];
	double freq[26];
};

#endif // !defined(AFX_HOMOPHONE_BER_H__C0728084_FD9D_11D4_80F2_000629C93170__INCLUDED_)
