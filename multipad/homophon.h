// Homophone.h: Schnittstelle für die Klasse Homophone.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOMOPHONE_H__E37EA770_8EDD_11D4_806A_000629C93170__INCLUDED_)
#define AFX_HOMOPHONE_H__E37EA770_8EDD_11D4_806A_000629C93170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Homophone  
{
public:
	void decrypt_text();
	short encr_text[81];
	void print_encr_text();
	void encrypt_text();
	void randomize_values();
	bool value_already_used(int);
	void print_crypt();
	int crypt [26] [100];
	void replace_letter_by_number();
	void SetInput(char *);
	char *GetPassphrase();
	void SetPassphrase(char *);
	void SetOutFp(FILE *);
	bool do_not_round_me [26];	// no value will be rounded more than once
	void do_it();
	double round(double);		
	void print_number();
	void make_number();
	void increase_number();
	void decrease_number();
	int checksum();
	int number[256];
	double float_value[256];
	Homophone(FILE *,FILE *);
	virtual ~Homophone();
	int alphsize,fsize;
	char *alphabet,*inbuf;
	char passphrase[257];
	FILE *out;
    SymbolArray text;
};

#endif // !defined(AFX_HOMOPHONE_H__E37EA770_8EDD_11D4_806A_000629C93170__INCLUDED_)
#endif // !defined(AFX_HOMOPHONE_H__E37EA770_8EDD_11D4_806A_000629C93170__INCLUDED_)
#endif // !defined(AFX_HOMOPHONE_H__E37EA770_8EDD_11D4_806A_000629C93170__INCLUDED_)
