/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

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
