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
