// MyPlayFairEdit1.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DialogPlayfair.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPlayFairEdit

CMyPlayFairEdit::CMyPlayFairEdit()
{
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
	if ( nChar == 22 && nFlags == 47 )
	{
		OnEditPaste();
	}

	char b2[2];
	int i,j,k, len;
	char s[MAXSHOWLETTER+2];
	
	if((!m_Alg->myisalpha2(nChar)) && (nChar>32))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
			nChar = m_Alg->getAlphabet()->replaceInvalidLetter(true, nChar);
	if (m_Alg->myisalpha2(nChar))
	{
		b2[1]=0;
		b2[0]=toupper(nChar);
		GetSel(i,j);
		if(i==j)
			SetSel(i,j=i+1);
		ReplaceSel(b2);
		SetSel(j,j);
	}
	else if(nChar==8)
	{
		len = GetLine (0, s, MAXSHOWLETTER);
		GetSel(i,j);
		if(i==j&&i==0)
			return;
		b2[0] = (len==i)?'\0':NULLELEMENT;
		b2[1] = 0;
		for(k=(i==0?0:i-1);k<j;k++)
		{
			SetSel(k,k+1);
			ReplaceSel(b2);
		}
		SetSel(i-1,i-1);
	}
	else if(nChar==3||nChar==22||nChar==24)
	{
		CEdit::OnChar(nChar,nRepCnt,nFlags);
	}
	else
	{
		if ((nChar=='J')||(('0'<=nChar)&&(nChar<='9'))) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_PLAYFAIR_WARNMSG003,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(s,pc_str);
			AfxMessageBox (s);
			b2[0] = '\0';
		} else
			b2[0] = NULLELEMENT;
		b2[1] = '\0';
		GetSel(i,j);
		if(i==j)
			SetSel(i,j=i+1);
		ReplaceSel(b2);
		SetSel(j,j);
	}
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
