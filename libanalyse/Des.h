/////////////////////////////////////////////////////////////////
//
// Diese Datei ist Bestandteil der Diplomarbeit
// "Eine C++-Bibliothek zur informationstheoretischen Kryptanalyse 
// von Stromchiffren und PZ-Folgen" am Europaeischen Institut fuer
// Systemsicherheit, Prof. Dr. Th. Beth
//
// von und (c) 1997-98 Michael Friedrich
//
/////////////////////////////////////////////////////////////////

#ifndef _DES_H
#define _DES_H 1

#ifndef _DEFAULT_H
#include "Default.h"
#endif
#ifndef _String_h
#include "la_string.h"
#endif
#ifndef _CIPHER_H
#include "Cipher.h"
#endif
#ifndef _SBOX_H
#include "SBox.h"
#endif
#ifndef _PERMUTATION_H
#include "Permutation.h"
#endif

/////////////////////////////////////////////////////////////////////
// DESdata: DES' Permutationen und Substitutionen (statisch)
// Es muss genau 1 Objekt dieser Klasse erzeugt werden!
// (Wird in Des.cpp getan:)  desdata

class DESData
{
public:
// Constructors
	DESData();
	~DESData();
// Attributes
	const SBox& S(int i) const {return *m_S[i];}
	static SBoxPerm2 IP;
	static SBoxPerm2 IPinv;
	static SBoxPerm2 P;
	static SBoxPerm2 E;
// Implementation
private:
	SBox *m_S[8];
	static PermTable m_IPperm;
	static PermTable m_IPperminv;
	static PermTable m_Pperm;
	static PermTable m_Eperm;
	static int m_count;
};

extern DESData desdata; // alle Member-Objekte per desdata.X aufrufen


/////////////////////////////////////////////////////////////////////
// DESF: Rundenfunktion des DES

class DESF : public BlockCipher
{
public:
// Constructors
	DESF(unsigned long k1, unsigned long k2);
// Operations
	BLOCKCIPHER_WITH_SIZE_1
	domain operator()(codomain x, int round) const;
// Implementation
private:
	unsigned long m_Key[16][2];
};


/////////////////////////////////////////////////////////////////////
// DES: DES 64bit Blockchiffre
class DES : public FeistelCipher
{
public:
// Constructors
	DES(unsigned long k1, unsigned long k2);
// Operations
	// inherited from FreistelCipher
// Implementation
private:
	DESF m_desf;
};

#endif /* _DES_H */