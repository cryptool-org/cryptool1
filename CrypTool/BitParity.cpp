/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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
