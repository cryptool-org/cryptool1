#pragma once


class CHillAnalysis
{
	char *fn_plain, *fn_cipher;
	int   dim_from, dim_to;
	int   alphabet_offset, mul_direction;

public:
	CHillAnalysis(void);
	~CHillAnalysis(void);

	int init(const char *fn_Plain, const char *fn_Cipher, int dim_From, int dim_To, int alphabet_Offset, int mul_Direction);
	int analyze();
};
