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

// DocumentForHashing.h: Schnittstelle für die Klasse DocumentForHashing.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCUMENTFORHASHING_H__2EEFBED1_C007_11D6_9DDC_000629718A52__INCLUDED_)
#define AFX_DOCUMENTFORHASHING_H__2EEFBED1_C007_11D6_9DDC_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ErrorcodesForSignatureAttack.h"

class DocumentForHashing  
{
public:
	DocumentForHashing()
	{
		m_DocumentData = NULL;
	}

	DocumentForHashing(const char *text, const int length)
	{
		m_DocumentData = NULL;
		SetData(text, length);		
	}

	virtual ~DocumentForHashing()
	{
		if (NULL != m_DocumentData)
		{
			delete []m_DocumentData;
		}
	}

	char GetDocumentDataAt(const int index) const
// Beschreibung:	gibt das Zeichen zurück, das an Position 'index' im Dokument steht;
// Parameter:		Position im Dokument [in];
// Rückgabewert:	Zeichen [out];
	{
		return m_DocumentData[index];
	}

	void SetDocumentDataAt(const int index, const char ch_new)
	{
		m_DocumentData[index] = ch_new;
	}
	
	char *GetDocumentData() const
// Beschreibung:	gibt das ganze Dokument zurück;
// Parameter:		keine;
// Rückgabewert:	Dokument [out];
	{
		return m_DocumentData;
	}

	int GetDocumentLength() const
// Beschreibung:	gibt die Länge des Dokuments zurück;
// Parameter:		keine;
// Rückgabewert:	Länge des Dokuments in Bytes [out];
	{
		return m_DocumentLength;
	}

protected:
	int m_DocumentLength;
	char *m_DocumentData;

private:
	void SetData(const char *text, const int &length)
	{
		m_DocumentLength = length;
		m_DocumentData = new char[m_DocumentLength];
		memcpy(m_DocumentData, text, length);
	}

};

#endif // !defined(AFX_DOCUMENTFORHASHING_H__2EEFBED1_C007_11D6_9DDC_000629718A52__INCLUDED_)
