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
	m_nWordWrap = WrapNone;
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
	GetRichEditCtrl().GetLine(0, m_line, sizeof(m_line));
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

	long s,e;

	GetRichEditCtrl().GetSel(s,e);
	m_charoffset = s;
	m_curline = GetRichEditCtrl().LineFromChar(s);
	m_lineindex = GetRichEditCtrl().LineIndex(m_curline);
	m_lineoffset = s - m_lineindex;
	m_curlen = GetRichEditCtrl().GetLine(m_curline, m_line, sizeof(m_line));
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
	GetRichEditCtrl().SetSel(m_charoffset, m_charoffset);

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
			GetRichEditCtrl().SetSel(m_lineindex+3*m_hexwidth+9+n,m_lineindex+3*m_hexwidth+9+n);
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
			GetRichEditCtrl().SetSel(m_lineindex+3*m_hexwidth+9+n,m_lineindex+3*m_hexwidth+10+n);
			buff[1]=0;
			buff[0]='.';
            if(IsPrint(new_c))
				buff[0] = new_c;
			GetRichEditCtrl().ReplaceSel( buff, FALSE );
			// select and change HEX part
			GetRichEditCtrl().SetSel(m_charoffset, m_charoffset+1);
			old_offset = m_charoffset;
			buff[0]=nChar;
			GetRichEditCtrl().ReplaceSel( buff, FALSE );
			AdjustCursor(0);
			// check to wrap to next line
			if(m_lineoffset >= 3*m_hexwidth+9) {
				if(GetRichEditCtrl().GetLineCount() > m_curline+1) {
					n = GetRichEditCtrl().LineIndex(m_curline+1);
					GetRichEditCtrl().SetSel(n,n);
					AdjustCursor(0);
				}
				else {
					GetRichEditCtrl().SetSel(old_offset, old_offset);
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
			GetRichEditCtrl().SetSel(m_lineindex+3*n+7,m_lineindex+3*n+7);
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
		GetRichEditCtrl().SetSel(m_lineindex+3*n+7,m_lineindex+3*n+9);
		GetRichEditCtrl().ReplaceSel( buff, FALSE );
		// edit ASCII Section
		GetRichEditCtrl().SetSel(m_charoffset, m_charoffset+1);
		buff[0]=nChar;
		buff[1]=0;
		GetRichEditCtrl().ReplaceSel( buff, FALSE );
		// check to wrap to next line
		if(m_lineoffset == m_curlen-1) {
			if(GetRichEditCtrl().GetLineCount() > m_curline+1) {
				n = GetRichEditCtrl().LineIndex(m_curline+1)+3*m_hexwidth+9;
				GetRichEditCtrl().SetSel(n,n);
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
	GetRichEditCtrl().Undo();
	GetRichEditCtrl().Undo();
}

void CHexView::OnEditCopy() 
{
	int l, i, j;
	HGLOBAL glob;
	HANDLE hndl;
	long start,end;
	long startl, endl;
	long startc, endc;
	long clen, cstart, cend;
	long startind, endind;
	char line[1024], *p;

	GetRichEditCtrl().GetSel(start,end);
	startl = GetRichEditCtrl().LineFromChar(start);
	endl = GetRichEditCtrl().LineFromChar(end);
	startc = start - GetRichEditCtrl().LineIndex(startl);
	endc = end - GetRichEditCtrl().LineIndex(endl);
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
		clen = GetRichEditCtrl().GetLine(i,line,sizeof(line)-1);
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
	long start,end;
	long startl;
	long startc;
	long startind;
	char buff[10];
	unsigned char *p;
	CHARRANGE range={0,-1};

	SetRedraw(FALSE);
	GetRichEditCtrl().GetSel(start,end);
	startl = GetRichEditCtrl().LineFromChar(start);
	startc = start - GetRichEditCtrl().LineIndex(startl);
	if(startc < 3*m_hexwidth+6) { // HEX mode
		if(startc < 7) startind = 0;
		else startind = (startc-6)/3;
	}
	else { // Character mode
		if(startc < 3*m_hexwidth+9) startind = 0;
		else startind = startc - 3*m_hexwidth-9;
	}
	max_l = (GetRichEditCtrl().GetLineCount() - startl) * m_hexwidth - startind;

	OpenClipboard();
//*** to be done *******	
//	hndl = GetClipboardData(range, RECO_PASTE, , );

	p = (unsigned char *) GlobalLock(hndl);
	l = GlobalSize(hndl)-1;
	l = min(l, max_l);
	startc = GetRichEditCtrl().LineIndex(startl) + 7 + 3 * startind;
	GetRichEditCtrl().SetSel(startc, startc);
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
	int WinLen, NewHexWidth, state, l, OldHexWidth, OldLineLength, buffsize = 20000;
	int maxl, llen;
	char *buffer1, *buffer3;
	unsigned char *buffer2;
	long start, end, pos, l1, l2, l3, adr;
	BOOL modified;

	CMyEditView::OnSize(nType, cx, cy);
	
	WinLen = cx / 8 - 1;
	NewHexWidth = (WinLen - 11) / 4;
	NewHexWidth = max(NewHexWidth, 8);
	if(NewHexWidth != m_hexwidth) { // Hexgröße anpassen!
		modified = GetRichEditCtrl().GetModify();
		buffer1 = (char *) malloc(buffsize+1);
		OldHexWidth = m_hexwidth;
		OldLineLength = OldHexWidth * 4 + 11;
		m_hexwidth = NewHexWidth;
		llen = m_hexwidth * 4 + 11;
		maxl = buffsize / m_hexwidth + 1;
		buffer2 = (unsigned char *) malloc(buffsize/4 + m_hexwidth);
		GetRichEditCtrl().GetSel(start, end);
		UINT nLen = GetTextLength();
		buffer3 = (char *) malloc(maxl * llen + 1);
		pos = adr = state = l1 = l2 = l3 = 0;
		SetRedraw(FALSE);
		do {
			GetRichEditCtrl().SetSel(pos, pos + buffsize);
			l1 = GetRichEditCtrl().GetSelText(buffer1);
			ASSERT(l1<=buffsize);
			if(l1 == 0) break;
			l = HexUndumpMem(buffer1, l1, (char *)(buffer2 + l2), &state);
			ASSERT(l2+l < buffsize/4 + m_hexwidth);
			l2 += l;
			l = l2 / m_hexwidth;
			l = l * m_hexwidth; // Anzahl kompletter Zeilen
			l3 = HexDumpMem(buffer3, maxl * llen + 1, buffer2, l, m_hexwidth, adr);
			buffer3[l3]=0;
			adr += l;
			memcpy(buffer2, buffer2+l, l2-l);
			l2 -= l;
			GetRichEditCtrl().ReplaceSel(buffer3);
			pos += l3;
		} while(1);
		l3 = HexDumpMem(buffer3, maxl * llen + 1, buffer2, l2, m_hexwidth, adr);
		GetRichEditCtrl().SetSel(pos, pos);
		GetRichEditCtrl().ReplaceSel(buffer3);
		pos += l3;
		free(buffer1);
		free(buffer2);
		free(buffer3);
		GetRichEditCtrl().SetSel(start, end);
		GetRichEditCtrl().SetModify(modified);
		SetRedraw(TRUE);
		Invalidate();
	}
	ASSERT_VALID(this);
}


void CHexView::SerializeRaw(CArchive & ar)
{
	char *buffer;
	char *buffer2;
	int bufflen = 20000, state, l, width;
	long start, end, textlen, pos, len, l1, buff2len, adr;

	GetRichEditCtrl().GetSel(start, end);
	buffer = (char *) malloc(bufflen+3);

	if (ar.IsStoring())
	{
		SetRedraw(FALSE);
		textlen = GetRichEditCtrl().GetTextLength();

		state = 0;
		for(pos = 0; pos < textlen; ) {
			GetRichEditCtrl().SetSel(pos, pos+bufflen);
			len = GetRichEditCtrl().GetSelText(buffer);
			l = HexUndumpMem(buffer, len, buffer, &state);
			TRY
			{
				ar.Write(buffer, l);
			}
			CATCH_ALL(e)
			{
				THROW_LAST();
			}
			END_CATCH_ALL
			pos += len;
		}
		SetRedraw(TRUE);
	}
	else
	{
		CFile* pFile = ar.GetFile();
		ASSERT(pFile->GetPosition() == 0);
		DWORD nFileSize = pFile->GetLength();

		width = m_hexwidth-1;
		l1 = bufflen / width; //maximale Zeilenanzahl im Puffer;
		buff2len = l1 * (4 * width + 11);
		buffer2 = (char *)malloc(buff2len + 1); // Zielpuffergröße
		l1 = l1 * width; // maximale Anzahl Zeichen um eine ganze Zeile zu füllen (im Puffer)

		// ReadFromArchive takes the number of characters as argument

		adr = pos = 0;
		do {
			l = ar.Read(buffer, l1);
			if(l==0) break;
			l = HexDumpMem(buffer2, buff2len, (unsigned char *) buffer, l, width, adr);
			GetRichEditCtrl().SetSel(pos, pos);
			GetRichEditCtrl().ReplaceSel(buffer2);
			pos += l;
			adr += l1;
		} while(l);
		free(buffer2);
		ASSERT_VALID(this);
	}
	free(buffer);
	GetRichEditCtrl().SetSel(start, end);
	SetRedraw(TRUE);
	Invalidate();
	ASSERT_VALID(this);
}

HRESULT CHexView::QueryAcceptData(LPDATAOBJECT lpdataobj, CLIPFORMAT *lpcfFormat, 
								  DWORD dwReco, BOOL bReally, HGLOBAL hMetaFile)
{
	return 1;
}

