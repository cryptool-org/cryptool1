//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#include "AppConv.h"

AppConverter::AppConverter()
{
	m_Modulus = 36;
	SetAlphabet("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
}

int AppConverter::Filter(char c) const
{
	return Alphabet[c];
}
char AppConverter::Conv(symbol_arg s) const
{
	return InvAlphabet[(char)s];
}

void AppConverter::SetAlphabet(CString NewAlphabet)
{
	int i;

	m_Modulus = NewAlphabet.GetLength();
	for(i=0;i<256;i++) Alphabet[i]=-1;
	for(i=0;i<((int)m_Modulus);i++) {
		Alphabet[NewAlphabet[i]] = i;
		InvAlphabet[i] = NewAlphabet[i];
	}
}

const AppConverter AppConv;
