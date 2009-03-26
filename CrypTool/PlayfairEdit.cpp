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


// MyPlayFairEdit1.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgPlayfairAnalysis.h"
#include "Cryptography.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayfairEdit

CPlayfairEdit::CPlayfairEdit()
{
	m_mode_ovr = TRUE;
}

CPlayfairEdit::~CPlayfairEdit()
{
}


BEGIN_MESSAGE_MAP(CPlayfairEdit, CEdit)
	//{{AFX_MSG_MAP(CPlayfairEdit)
	ON_WM_CHAR()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CPlayfairEdit 



void CPlayfairEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ( nChar == 22 && 47 == (nFlags & 47) )
	{
		OnEditPaste();
		return;
	}
	int cStart, cEnd;
	GetSel(cStart, cEnd);
	if (cStart == cEnd)
		SetSel( cStart, cStart+1 );
	CEdit::OnChar(nChar, nRepCnt, nFlags);
	GetSel(cStart, cEnd);
}

void CPlayfairEdit::OnEditPaste() 
{
	OpenClipboard();
	HANDLE hndl;
	char *globBuff, *dataBuff;
	long  dataLen;

	if ( hndl = ::GetClipboardData(CF_TEXT) )
	{
		globBuff = (char *) GlobalLock(hndl);
		dataLen = strlen(globBuff);
		dataBuff = globBuff;
		char *tmpIn  = new char[dataLen+1];
		char *tmpOut = new char[4*dataLen+1];
		memcpy( tmpIn, dataBuff, dataLen);
		tmpIn[dataLen] = '\0';
		unsigned char *p = (unsigned char*)dataBuff;
		CString P = _T("");
		for ( int i=0; i<dataLen; i++ )
		{
			if ( m_TextWasPreformatted )
			{ // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
				if(!m_Alg->myisalpha2(p[i]))  
					p[i] = m_Alg->getAlphabet()->replaceInvalidLetter(true, MyToUpper(p[i]));
				if ( p[i] >= 32 && m_Alg->myisalpha2(p[i]) )
				{
					/*********** ToDo TrennZeichen + Zeichenweise Upcase: ********/
					if ( P.GetLength() > 0 && P[P.GetLength()-1] == p[i] )
						P += 'X';
					P += p[i];
				}
			}
			else
			{
				if ( p[i] >= 32 && m_Alg->myisalpha2(p[i]) )
				{
					P += p[i];
				}	
				else  // Alles andere als ' ' kodieren
				{
					P += '*';
				}
			}
		}
		// *** Check the Pasted String if it is a stream of numbers
		int startc, endc;
		GetSel(startc, endc );
		ReplaceSel( P );
		startc += P.GetLength();
		SetSel( startc, startc );
		GlobalUnlock(hndl);
		CloseClipboard();
	}
}


