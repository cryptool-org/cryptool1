// MyPlayFairEdit1.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DialogPlayfair.h"
#include "crypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPlayFairEdit

CMyPlayFairEdit::CMyPlayFairEdit()
{
	m_mode_ovr = TRUE;
}

CMyPlayFairEdit::~CMyPlayFairEdit()
{
}


BEGIN_MESSAGE_MAP(CMyPlayFairEdit, CEdit)
	//{{AFX_MSG_MAP(CMyPlayFairEdit)
	ON_WM_CHAR()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CMyPlayFairEdit 



void CMyPlayFairEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
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
}



void CMyPlayFairEdit::OnEditPaste() 
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
					p[i] = m_Alg->getAlphabet()->replaceInvalidLetter(true, toupper(p[i]));
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


