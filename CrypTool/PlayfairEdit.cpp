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
			if ( p[i] >= 32 && m_Alg->myisalpha2(p[i]) )
			{
				P += p[i];
			}	
			else  // Alles andere als ' ' kodieren
			{
				P += '*';
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


