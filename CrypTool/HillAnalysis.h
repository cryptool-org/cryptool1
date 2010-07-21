#pragma once
#include "stdafx.h"

class CHillAnalysis
{
	char *fn_plain, *fn_cipher;
	int   dim_from, dim_to;
	int   mul_direction;

public:
	CHillAnalysis(void);
	~CHillAnalysis(void);

	int init(const char *fn_Plain, const char *fn_Cipher, int dim_From, int dim_To, int mul_Direction);
	int analyze(CString &err_str);
};
