//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// HexView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "HexView.h"
#include "fileutil.h"
#include "MyDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHexView

IMPLEMENT_DYNCREATE(CHexView, CMyEditView)

CHexView::CHexView()
{
	m_hexwidth = 8;
}

CHexView::~CHexView()
{
}


BEGIN_MESSAGE_MAP(CHexView, CMyEditView)
	//{{AFX_MSG_MAP(CHexView)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateFalse)
	ON_COMMAND(ID_EDIT_CLEAR, OnEmpty)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateFalse)
	ON_COMMAND(ID_EDIT_CUT, OnEmpty)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REPLACE, OnUpdateFalse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CHexView 

void CHexView::OnDraw(CDC* pDC)
{
	CMyDocument* pDoc = (CMyDocument*)GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CHexView

#ifdef _DEBUG
void CHexView::AssertValid() const
{
	CMyEditView::AssertValid();
}

void CHexView::Dump(CDumpContext& dc) const
{
	CMyEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CHexView 

void CHexView::OnInitialUpdate() 
{
	CDC *m_cdc;

    m_Font.CreatePointFont(80, "Courier", NULL);
    SetFont(&m_Font);
	CMyEditView::OnInitialUpdate();
	m_charoffset = 0;
	m_lineindex = 0;
	GetEditCtrl().GetLine(0, m_line, sizeof(m_line));
	m_cdc = GetDC();
	CharSize = m_cdc->GetOutputTextExtent("12345678901234567890",1);
	ReleaseDC(m_cdc);
}

void CHexView::OnUpdateFalse(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(FALSE);
}

void CHexView::OnEmpty() 
{
	// ignore this command
}

int CHexView::AdjustCursor(int direction)
{
	// wenn direction==0 dann Cursor nach rechts falls benötigt
	// 1: Cursor nach links falls benötigt

	int s,e;

	GetEditCtrl().GetSel(s,e);
	m_charoffset = s;
	m_curline = GetEditCtrl().LineFromChar(s);
	m_lineindex = GetEditCtrl().LineIndex(m_curline);
	m_lineoffset = s - m_lineindex;
	m_curlen = GetEditCtrl().GetLine(m_curline, m_line, sizeof(m_line));
	if(m_lineoffset < 7) {
		m_lineoffset=7;
	}
	if(m_lineoffset < 3*m_hexwidth+9) {
		if(direction == 0) {
			for(;m_lineoffset < 3*m_hexwidth+9; m_lineoffset++)
				if(m_line[m_lineoffset]!=' ')  break;
		}
		else {
			for(;m_lineoffset > 6; m_lineoffset--)
				if(m_line[m_lineoffset]!=' ')  break;
		}
	}
	if(m_lineoffset >= m_curlen) {
		m_lineoffset = m_curlen-1;
	}
	m_charoffset = m_lineoffset + m_lineindex;
	GetEditCtrl().SetSel(m_charoffset, m_charoffset);

	return m_lineindex;

}

void CHexView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int n, old_offset;
	char new_c, buff[5];
	BOOL invalid;

	SetRedraw(FALSE);
	invalid = AdjustCursor(0);
	if(m_lineoffset < 3*m_hexwidth+9) { // edit hexadecimal area
		if(nChar == '\t') { // Tab char toggles between hex and ascii
			n = (m_lineoffset-7)/3; // number of char to edit
			GetEditCtrl().SetSel(m_lineindex+3*m_hexwidth+9+n,m_lineindex+3*m_hexwidth+9+n);
			AdjustCursor(0);
			SetRedraw(TRUE);
			Invalidate(TRUE);
			return;
		}
		if(IsHex(nChar)) { // hex character --> do the editing
			n = (m_lineoffset-7)/3; // number of char to edit
			if(('a'<=nChar) && (nChar <= 'f')) nChar = nChar+'A'-'a';
			m_line[m_lineoffset] = nChar;
			new_c = 16*HexVal(m_line[7+3*n]) + HexVal(m_line[8+3*n]);
			// select the ASCII char to change
			GetEditCtrl().SetSel(m_lineindex+3*m_hexwidth+9+n,m_lineindex+3*m_hexwidth+10+n);
			buff[1]=0;
			buff[0]='.';
            if(IsPrint(new_c))
				buff[0] = new_c;
			GetEditCtrl().ReplaceSel( buff, FALSE );
			// select and change HEX part
			GetEditCtrl().SetSel(m_charoffset, m_charoffset+1);
			old_offset = m_charoffset;
			buff[0]=nChar;
			GetEditCtrl().ReplaceSel( buff, FALSE );
			AdjustCursor(0);
			// check to wrap to next line
			if(m_lineoffset >= 3*m_hexwidth+9) {
				if(GetEditCtrl().GetLineCount() > m_curline+1) {
					n = GetEditCtrl().LineIndex(m_curline+1);
					GetEditCtrl().SetSel(n,n);
					AdjustCursor(0);
				}
				else {
					GetEditCtrl().SetSel(old_offset, old_offset);
					MessageBeep(MB_ICONHAND); // end of file reached
				}
			}
			invalid = TRUE;
		}
		else {
			MessageBeep(MB_ICONASTERISK); // no hex character pressed
		}
	}
	else { // edit ASCII part
		if(nChar == '\t') { // Tab char toggles between hex and ascii
			n = m_lineoffset - (3*m_hexwidth+9); // number of char to edit
			GetEditCtrl().SetSel(m_lineindex+3*n+7,m_lineindex+3*n+7);
			AdjustCursor(0);
			SetRedraw(TRUE);
			Invalidate(TRUE);
			return;
		}
		if(!IsPrint(nChar)) {
			MessageBeep(MB_ICONHAND);
			SetRedraw(TRUE);
			return;
		}
		n = m_lineoffset - (3*m_hexwidth+9); // number of char to edit
		// edit Hex Section
		sprintf(buff,"%02.2X",nChar);
		GetEditCtrl().SetSel(m_lineindex+3*n+7,m_lineindex+3*n+9);
		GetEditCtrl().ReplaceSel( buff, FALSE );
		// edit ASCII Section
		GetEditCtrl().SetSel(m_charoffset, m_charoffset+1);
		buff[0]=nChar;
		buff[1]=0;
		GetEditCtrl().ReplaceSel( buff, FALSE );
		// check to wrap to next line
		if(m_lineoffset == m_curlen-1) {
			if(GetEditCtrl().GetLineCount() > m_curline+1) {
				n = GetEditCtrl().LineIndex(m_curline+1)+3*m_hexwidth+9;
				GetEditCtrl().SetSel(n,n);
			}
			else
				MessageBeep(MB_ICONHAND); // end of file reached
		}
		AdjustCursor(0);
		invalid = TRUE;

	}
	SetRedraw(TRUE);
	if(invalid) Invalidate(TRUE);
}

void CHexView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar) {
		case(VK_DELETE):
			break;
		default:
			CMyEditView::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}

void CHexView::OnEditUndo() 
{
	GetEditCtrl().Undo();
	GetEditCtrl().Undo();
}

void CHexView::OnEditCopy() 
{
	int l, i, j;
	HGLOBAL glob;
	HANDLE hndl;
	int start,end;
	int startl, endl;
	int startc, endc;
	int clen, cstart, cend;
	int startind, endind;
	char line[1024], *p;

	GetEditCtrl().GetSel(start,end);
	startl = GetEditCtrl().LineFromChar(start);
	endl = GetEditCtrl().LineFromChar(end);
	startc = start - GetEditCtrl().LineIndex(startl);
	endc = end - GetEditCtrl().LineIndex(endl);
	if(startc < 3*m_hexwidth+6) { // HEX mode
		if(startc < 7) startind = 0;
		else startind = (startc-6)/3;
		if(endc < 7) endind = 0;
		else if(endc < 3*m_hexwidth+6) endind = (endc-8)/3;
		else endind = m_hexwidth;
	}
	else { // Character mode
		if(startc < 3*m_hexwidth+9) startind = 0;
		else startind = startc - 3*m_hexwidth-9;
		if(endc < 3*m_hexwidth+9) endind = 0;
		else endind = endc - 3*m_hexwidth-10;
	}

//	if(startc < 7) startind = 0;
//	else if(startc < 3*m_hexwidth+6) startind = (startc-6)/3;
//	else if(startc < 3*m_hexwidth+9) startind = 0;
//	else startind = startc - 3*m_hexwidth-9;
//	if(endc < 7) endind = 0;
//	else if(endc < 3*m_hexwidth+6) endind = (endc-6)/3;
//	else if(endc < 3*m_hexwidth+9) endind = 0;
//	else endind = endc - 3*m_hexwidth-9;

	l=(endl-startl)*m_hexwidth-startind+endind+2;
	glob = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, l);

	p= (char *) GlobalLock(glob);
	for(i=startl;i<=endl;i++) {
		clen = GetEditCtrl().GetLine(i,line,sizeof(line)-1);
		if(i==startl) cstart = startind;
		else cstart = 0;
		if(i==endl) cend = endind;
		else cend = m_hexwidth-1;
		for(j=cstart; j<=cend; j++) {
			*p = 16*HexVal(line[7+3*j]) + HexVal(line[8+3*j]);
			p++;
		}
	}
	*p=0;

	GlobalUnlock(glob);
	OpenClipboard();
	hndl = SetClipboardData(CF_TEXT,glob);
	if(hndl==0) l = GetLastError();
	CloseClipboard();
}

void CHexView::OnEditPaste() 
{
	int l, i, max_l;
	HANDLE hndl;
	int start,end;
	int startl;
	int startc;
	int startind;
	char buff[10];
	unsigned char *p;

	SetRedraw(FALSE);
	GetEditCtrl().GetSel(start,end);
	startl = GetEditCtrl().LineFromChar(start);
	startc = start - GetEditCtrl().LineIndex(startl);
	if(startc < 3*m_hexwidth+6) { // HEX mode
		if(startc < 7) startind = 0;
		else startind = (startc-6)/3;
	}
	else { // Character mode
		if(startc < 3*m_hexwidth+9) startind = 0;
		else startind = startc - 3*m_hexwidth-9;
	}
	max_l = (GetEditCtrl().GetLineCount() - startl) * m_hexwidth - startind;

	OpenClipboard();
	hndl = GetClipboardData(CF_TEXT);
	p = (unsigned char *) GlobalLock(hndl);
	l = GlobalSize(hndl)-1;
	l = min(l, max_l);
	startc = GetEditCtrl().LineIndex(startl) + 7 + 3 * startind;
	GetEditCtrl().SetSel(startc, startc);
	for(i=0;i<l;i++) {
		if(*p<16) {
			buff[0]='0';
			_itoa(*p,buff+1,16);
		}
		else _itoa(*p,buff,16);
		p++;
		OnChar(buff[0],0,0);
		OnChar(buff[1],0,0);
	}
	GlobalUnlock(hndl);
	CloseClipboard();
	SetRedraw(TRUE);
	Invalidate(TRUE);
}


void CHexView::OnSize(UINT nType, int cx, int cy) 
{
	int WinLen, NewHexWidth, state, l, maxline;
	char *buffer, *NewBuffer;
	char *OldBuffer;

	CMyEditView::OnSize(nType, cx, cy);
	
	WinLen = cx / 8;
	NewHexWidth = (WinLen - 10) / 4;
	NewHexWidth = max(NewHexWidth, 8);
	if(NewHexWidth != m_hexwidth) { // Hexgröße anpassen!
		m_hexwidth = NewHexWidth;
//		OldBuffer = LockBuffer();
		UINT nLen = GetWindowTextLength();
		OldBuffer = (char *) malloc(nLen+3);
		GetWindowText(OldBuffer, nLen+2);
		buffer = (char *) malloc(nLen/4); // maximale Größe fuer das Ergebnis
		state = 0;
		l = HexUndumpMem(OldBuffer, nLen, (char *) buffer, &state);
		free(OldBuffer);
		maxline = (l / m_hexwidth) + 1;
		maxline =  maxline * (m_hexwidth * 4 + 11)+2; // maximale Größe des Dumps + 1
		NewBuffer = (char *) malloc(maxline);
		l = HexDumpMem(NewBuffer, maxline, (unsigned char *) buffer, l, m_hexwidth);
		NewBuffer[l] = '\0';
		free(buffer);
		SetWindowText(NewBuffer);
		free(NewBuffer);
		Invalidate();
	}
	ASSERT_VALID(this);
}


void CHexView::SerializeRaw(CArchive & ar)
{
	unsigned char *buffer;
	char *buffer2;
	int state, l, maxline;

	if (ar.IsStoring())
	{
		LPCTSTR lpszText = LockBuffer();
		ASSERT(lpszText != NULL);
		UINT nLen = GetBufferLength();
		buffer = (unsigned char *) malloc(nLen/4); // maximale Größe fuer das Ergebnis
		state = 0;
		l = HexUndumpMem(lpszText, nLen, (char *) buffer, &state);
		TRY
		{
			ar.Write(buffer, l);
		}
		CATCH_ALL(e)
		{
			UnlockBuffer();
			THROW_LAST();
		}
		END_CATCH_ALL
		free(buffer);
		UnlockBuffer();
	}
	else
	{
		CFile* pFile = ar.GetFile();
		ASSERT(pFile->GetPosition() == 0);
		DWORD nFileSize = pFile->GetLength();
		// ReadFromArchive takes the number of characters as argument

		DWORD nLen = nFileSize;

		maxline = (nFileSize / m_hexwidth) + 1;
		l =  maxline * (m_hexwidth * 4 + 11) + 2; // maximale Größe des Dumps + 1

		buffer = (unsigned char *) malloc(nFileSize); // Zwischenpuffer

		buffer2 = (char *) malloc(l);
		ar.Read(buffer, nLen);
		l = HexDumpMem(buffer2, l, buffer, nFileSize, m_hexwidth);
		// Replace the editing edit buffer with the newly loaded data
		free(buffer);
		buffer2[l] = '\0';

		SetWindowText(buffer2);
		free(buffer2);
		Invalidate();
		ASSERT_VALID(this);
	}
	ASSERT_VALID(this);
}
