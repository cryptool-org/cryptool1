// BitParity.cpp: Implementierung der Klasse BitParity.
//
// von Jan Blumenstein, Deutsche Bank AG, September 2002
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "BitParity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

BitParity::BitParity()
{
	int counter, exponent, ii, jj, number;

	for (ii = 0; ii < 256; ii ++)
	{
		counter = 0;
		exponent = 128;
		number = ii;

		for (jj = 0; jj < 8; jj ++)
		{
			if (number & 1)
			{
				counter += (number & 1);
			}

			number >>= 1;
		}

		m_ParityBitTable[ii] = counter;
	}
}

int BitParity::GetSumOfBits(const char *String, const long NumberOfBits) const
{
	char last_byte;
	int ii, result = 0;

	for (ii = 0; ii < NumberOfBits / 8; ii ++)
	{
		result += GetParity(String[ii]);
	}

	if (NumberOfBits % 8)
	{
		last_byte = String[ii] & (0xff << (8 - (NumberOfBits % 8)));
		result += GetParity(last_byte);
	}

	return result;
}
