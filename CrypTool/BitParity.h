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


// BitParity.h: Schnittstelle für die Klasse BitParity.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITPARITY_H__8D72B083_C6E5_11D6_9DE3_000629718A52__INCLUDED_)
#define AFX_BITPARITY_H__8D72B083_C6E5_11D6_9DE3_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BitParity  
{
public:
	BitParity();

	char GetParity(const char ch) const
// Beschreibung:	gibt die Parität (= Anzahl der 1en des Binärwerts (mod 2)) des Binärwertes des übergebenen ASCII-Zeichens
//					zurück;
// Parameter:		ASCII-Zeichen, dessen Parität berechnet werden soll [in];
// Rückgabewert:	Parität des übergebenen ASCII-Zeichens [out];
	{
		return GetSumOfBits(ch) % 2;
	}

	char GetSumOfBits(const char ch) const
// Beschreibung:	gibt die Anzahl der 1en des Binärwertes des übergebenen ASCII-Zeichens zurück;
// Parameter:		ASCII-Zeichen, dessen Anzahl der 1en im Binärwert berechnet werden soll [in];
// Rückgabewert:	Anzahl der 1en [out];
	{
		return m_ParityBitTable[(unsigned char)ch];
	}

	char GetParity(const char *String, const long NumberOfBits) const
// Beschreibung:	gibt die Gesamt-Parität eines character-Strings zurück;
// Parameter:		ASCII-Zeichen, dessen Anzahl der 1en im Binärwert berechnet werden soll [in];
// Rückgabewert:	Anzahl der 1en [out];
	{
		return (GetSumOfBits(String, NumberOfBits) % 2);
	}

	int GetSumOfBits(const char *String, const long NumberOfBits) const;
// Beschreibung:	gibt die Anzahl der 1en (= Parität) der Binärwerte des übergebenen character-Strings zurück;
// Parameter:		character-String, dessen Parität berechnet werden soll [in];
// Rückgabewert:	Parität des übergebenen ASCII-Zeichens [out];

private:
	char m_ParityBitTable[256];

};

#endif // !defined(AFX_BITPARITY_H__8D72B083_C6E5_11D6_9DE3_000629718A52__INCLUDED_)
