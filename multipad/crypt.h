//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

#ifndef __CRYPT_H
#define __CRYPT_H

#include "DlgFortschritt.h"

//////////////////////////////////////////////////////////////////
//
//
//

#define IDS_STRINGLENGTH 1024
void Message(int IDS_STRING_ID, int FLAGS, int No1 = 0, int No2 = 0);
void Message(int IDS_STRING_ID, int FLAGS, int No, const char * str, bool transpose = false);
void Message(int IDS_STRING_ID, int FLAGS, const char* str1, const char* str2 = NULL);

/////////////////////////////////////////////////////////////////
//
//
//

typedef struct {
	const char	*infile;
	const char	*OldTitle;
	int			keylen;
	char		*key;
	int			flags;
	void		*result;
} CryptPar;


// ================================================================
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
// ================================================================



#define CRYPT_DISPLAY_BG		0x001
#define CRYPT_FREE_MEM			0x002
#define CRYPT_DO_WAIT_CURSOR	0x004
#define CRYPT_DISPLAY_IMMEDIATE	0x008
#define CRYPT_DO_PROGRESS		0x010
#define CRYPT_ASCII				0x020
#define CRYPT_DONE				0x080000000


void CaesarAsc(const char *infile, const char *OldTitle);	
void VigenereAsc(const char *infile, const char *OldTitle);	
void XorBin(const char *infile, const char *OldTitle);	
void AddBin(const char *infile, const char *OldTitle);	
void PlayfairBin(const char *infile, const char *OldTitle);	
void homophoncrypt(const char *infile, const char *OldTitle);	
void PlayfairAnalyse(const char *infile, const char *OldTitle);	
void VernamBin(const char *infile, const char *OldTitle);	
void EntropyASCII(const char *infile, const char *OldTitle);	
void EntropyBin(const char *infile, const char *OldTitle);	
UINT  Autocorr(PVOID p);	
UINT  Vitanycorr(PVOID p);	
UINT  Periode(PVOID p);	
UINT  zzgenit(PVOID p);	
UINT  FloatingEntropy(PVOID p);	
void HistogramASCII(const char *infile, const char *OldTitle);	
void HistogramBin(const char *infile, const char *OldTitle);	
void MakeNewName(char *dest, unsigned int len, const char *format, const char *old);
void MakeNewName2(char *dest, int len, const char *format, const char *old, const char *alg);
void MakeNewName3(char *dest, unsigned int len, const char *format, const char *alg, const char *old, const char *key);
void Hill(const char *infile, const char *OldTitle);
void Mono(const char *infile, const char *OldTitle);
UINT  AnaSubst(PVOID p);	
void AESCrypt (char* infile, const char *OldTitle, int AlgId, char * NewFileName = NULL, char* NewFileKey = NULL );
void HomophoneAsc(const char *infile, const char *OldTitle);
void HomophoneHex(const char *infile, const char *OldTitle);	
void NGramAsc(const char *infile, const char *OldTitle);
void NGramBin(const char *infile, const char *OldTitle);
void PermutationAsc(const char *infile, const char *OldTitle);
void Hashdemo(const char *infile,const char *OldTitle);
void HashOfAFile();
void SignatureTutorial(const char *infile, const char* OldTitle);


BOOL CheckAlphabet( int minSize = 1);
BOOL CheckTextSize( SymbolArray &text, int Threshold = 1 );
void LoadText( const char *infile, SymbolArray &text );
void OpenNewDoc( const char *outfile, const char* keyStr, const char* OldTitle, int IDS_STRING_ID, 
				 BOOL Decrypt = FALSE, int KeyType = SCHLUESSEL_LINEAR );

#endif // __CRYPT_H