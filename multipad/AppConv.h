//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

#define IMPLEMENT_CONVERTERCLASS 1

#include "..\libanalyse\stdinc.h"
#include <afx.h>

class AppConverter : public ByteConverter
{
	typedef ByteConverter baseclass;
public:
// Constructors
	AppConverter();
	CLONE(AppConverter);
	void SetAlphabet(CString NewAlphabet);
// Implementation
protected:
	signed int Alphabet[256];
	char InvAlphabet[256];
	int Filter(char c) const;
	char Conv(symbol_arg s) const;
};

extern const AppConverter AppConv;
extern const AppConverter AppConv;
extern const AppConverter AppConv;
