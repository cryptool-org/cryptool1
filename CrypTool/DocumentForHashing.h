/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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


// DocumentForHashing.h: Schnittstelle f�r die Klasse DocumentForHashing.
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
// Beschreibung:	gibt das Zeichen zur�ck, das an Position 'index' im Dokument steht;
// Parameter:		Position im Dokument [in];
// R�ckgabewert:	Zeichen [out];
	{
		return m_DocumentData[index];
	}

	void SetDocumentDataAt(const int index, const char ch_new)
	{
		m_DocumentData[index] = ch_new;
	}
	
	char *GetDocumentData() const
// Beschreibung:	gibt das ganze Dokument zur�ck;
// Parameter:		keine;
// R�ckgabewert:	Dokument [out];
	{
		return m_DocumentData;
	}

	int GetDocumentLength() const
// Beschreibung:	gibt die L�nge des Dokuments zur�ck;
// Parameter:		keine;
// R�ckgabewert:	L�nge des Dokuments in Bytes [out];
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
