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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// HexView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "HexView.h"
#include "FileTools.h"
#include "AppDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHexView

IMPLEMENT_DYNCREATE(CHexView, CAppEditView)

CHexView::CHexView()
{
	m_hexwidth = 8;
	m_SizeActive = FALSE;
	m_NewSize = 0;
	m_nWordWrap = WrapNone;
	m_EOF = 0; // EndOfFile = false
}

CHexView::~CHexView()
{
}


BEGIN_MESSAGE_MAP(CHexView, CAppEditView)
	//{{AFX_MSG_MAP(CHexView)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateFalse)
	ON_COMMAND(ID_EDIT_CLEAR, OnEmpty)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI(ID_TOTXT, OnUpdateTotxt)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateFalse)
	ON_COMMAND(ID_EDIT_CUT, OnEmpty)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REPLACE, OnUpdateFalse)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateFalse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CHexView 

void CHexView::OnDraw(CDC* pDC)
{
	CAppDocument* pDoc = (CAppDocument*)GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CHexView

#ifdef _DEBUG
void CHexView::AssertValid() const
{
	CAppEditView::AssertValid();
}

void CHexView::Dump(CDumpContext& dc) const
{
	CAppEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CHexView 

void CHexView::OnInitialUpdate() 
{
	CDC *m_cdc;

    m_Font.CreatePointFont(80, "Courier", NULL);
    SetFont(&m_Font);
	CAppEditView::OnInitialUpdate();
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

	char *t;
	long s,e;

	GetRichEditCtrl().GetSel(s,e);
	m_charoffset = s;
	m_curline = GetRichEditCtrl().LineFromChar(s);
	m_lineindex = GetRichEditCtrl().LineIndex(m_curline);
	m_lineoffset = s - m_lineindex;
	m_curlen = GetRichEditCtrl().GetLine(m_curline, m_line, sizeof(m_line));
	t = strchr(m_line, 0x0d);
	if(t) m_curlen = t-m_line;
	if(m_lineoffset < 7) {
		m_lineoffset=7;
	}
	if(m_lineoffset < 3*m_hexwidth+9) { // in hex-block
		if(direction == 0) {
			for(;m_lineoffset < 3*m_hexwidth+9; m_lineoffset++)
				if(m_line[m_lineoffset]!=' ')  break;
		}
		else {
			for(;m_lineoffset > 6; m_lineoffset--)
				if(m_line[m_lineoffset]!=' ')  break;
		}
	}
	if(m_lineoffset > m_curlen) {
		m_lineoffset = m_curlen; // position at end of line
	}
	m_charoffset = m_lineoffset + m_lineindex;
	GetRichEditCtrl().SetSel(m_charoffset, m_charoffset);

	return m_lineindex;

}

void CHexView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int n, old_offset, char_offset, i;
	char new_c, buff[5], oldChar;
	BOOL invalid;

	m_EOF = false;

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
			n = (m_lineoffset-MAX_ADR_LEN)/3; // number of char to edit

			// total offset of char to edit
			char_offset = m_curline * m_hexwidth + n;

			if(('a'<=nChar) && (nChar <= 'f')) nChar = nChar+'A'-'a';
			oldChar = 16*HexVal(m_line[7+3*n]) + HexVal(m_line[8+3*n]);
			if((!IsPrint(oldChar)) && (oldChar != 10) && (oldChar != 13))
				m_NoPrintChars = max(m_NoPrintChars-1,0);
			m_line[m_lineoffset] = nChar;
			new_c = 16*HexVal(m_line[7+3*n]) + HexVal(m_line[8+3*n]);
			if((!IsPrint(new_c)) && (new_c != 10) && (new_c != 13))
				m_NoPrintChars++;
			// select the ASCII char to change
			GetRichEditCtrl().SetSel(m_lineindex+3*m_hexwidth+9+n,m_lineindex+3*m_hexwidth+10+n);
			buff[1]=0;
			buff[0]='.';
            if(IsPrint(new_c))
				buff[0] = new_c;
			GetRichEditCtrl().ReplaceSel( buff, TRUE );
			// select and change HEX part
			GetRichEditCtrl().SetSel(m_charoffset, m_charoffset+1);
			old_offset = m_charoffset;
			buff[0]=nChar;
			GetRichEditCtrl().ReplaceSel( buff, TRUE );
			AdjustCursor(0);
			// adjust trailing blanks
			if(m_totlen - char_offset - 1 < m_TrailBlanks) { // possibly reduce number of trailing nulls
				if(new_c != 0) m_TrailBlanks = m_totlen - char_offset - 1;
			}
			if((m_totlen - char_offset - 1 == m_TrailBlanks) && (new_c == 0)){ // possibly increase number of trailing nulls
				for(i = m_totlen-1; i>=0; i--) if( GetCharAt(i) != 0) break;
				m_TrailBlanks = m_totlen - i - 1;
			}
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
					m_EOF = true;
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

		// Adjust trailing blanks
		char_offset = m_curline * m_hexwidth + n;
		m_TrailBlanks = min(m_TrailBlanks, m_totlen - n - 1);

		if(m_lineoffset >= m_curlen) { // end of line reached, jump to next line
			if(m_curline < GetRichEditCtrl().GetLineCount()-1) { // jump to next line
				n = GetRichEditCtrl().LineIndex(m_curline+1)+3*m_hexwidth+MAX_ADR_LEN+ASC_SEP;
				GetRichEditCtrl().SetSel(n,n);
				n = 0; // number of char to edit;
				m_curline++; // current line
				m_lineindex = GetRichEditCtrl().LineIndex(m_curline);
				m_lineoffset = MAX_ADR_LEN + 3*m_hexwidth + ASC_SEP;
				m_charoffset = m_lineoffset + m_lineindex;
				m_curlen = GetRichEditCtrl().GetLine(m_curline, m_line, sizeof(m_line));
			}
			else { // end of file reached
				MessageBeep(MB_ICONHAND); // end of file reached
				SetRedraw(TRUE);
				return;
			}
		}
		// edit Hex Section
		GetRichEditCtrl().SetSel(m_lineindex+3*n+7,m_lineindex+3*n+9);
		GetRichEditCtrl().GetSelText(buff);
		oldChar = (char) strtol(buff, NULL, 16);
		if((!IsPrint(oldChar)) && (oldChar != 10) && (oldChar != 13))
			m_NoPrintChars = max(m_NoPrintChars-1,0);
		sprintf(buff,"%02.2X",nChar);
		GetRichEditCtrl().SetSel(m_lineindex+3*n+7,m_lineindex+3*n+9);
		GetRichEditCtrl().ReplaceSel( buff, TRUE );
		// edit ASCII Section
		GetRichEditCtrl().SetSel(m_charoffset, m_charoffset+1);
		buff[0]=nChar;
		buff[1]=0;
		GetRichEditCtrl().ReplaceSel( buff, TRUE );
		// check to wrap to next line
		if(m_lineoffset >= m_curlen-1) {
			if(GetRichEditCtrl().GetLineCount() > m_curline+1) {
				n = GetRichEditCtrl().LineIndex(m_curline+1)+3*m_hexwidth+MAX_ADR_LEN+ASC_SEP;
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
		case(8):
			break; 
		default:
			CAppEditView::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}

void CHexView::OnEditUndo() 
{
 	SetRedraw(FALSE);
 	GetRichEditCtrl().Undo();
// 	GetRichEditCtrl().Undo();
 	SetRedraw(TRUE);
 	Invalidate(TRUE);
}

void CHexView::OnEditCopy() 
{
	int l, i, j;
	HGLOBAL glob1, glob2;
	HANDLE hndl;
	long start,end;
	long startl, endl;
	long startc, endc;
	long clen, cstart, cend;
	long startind, endind;
	char line[1024], *p1, *p2;

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

	l=(endl-startl)*m_hexwidth-startind+endind+2;
	glob1 = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, l);
	glob2 = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, l+sizeof(long));

	p2=p1= (char *) GlobalLock(glob1);
	for(i=startl;i<=endl;i++) {
		clen = GetRichEditCtrl().GetLine(i,line,sizeof(line)-1);
		if(i==startl) cstart = startind;
		else cstart = 0;
		if(i==endl) cend = endind;
		else cend = m_hexwidth-1;
		for(j=cstart; j<=cend; j++) {
			*p1 = 16*HexVal(line[7+3*j]) + HexVal(line[8+3*j]);
			p1++;
		}
	}
	*p1=0;
	p1=p2;
	p2= (char *) GlobalLock(glob2);
	((long *) p2)[0] = l-1;
	p2 += sizeof(long);
	memcpy(p2, p1, l-1);

	GlobalUnlock(glob1);
	GlobalUnlock(glob2);

	OpenClipboard();
	hndl = SetClipboardData(CF_TEXT,glob1);
	if(hndl==0) l = GetLastError();
	hndl = SetClipboardData(theApp.m_HexFormat,glob2);
	if(hndl==0) l = GetLastError();
	CloseClipboard();
}

void CHexView::OnEditPaste() 
{
	int i, max_l;
	HANDLE hndl;
	long start,end;
	long startl;
	long startc;
	long startind, dataLen;
	char buff[10], *dataBuff, *globBuff;
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
	hndl = ::GetClipboardData(theApp.m_HexFormat);
	if(hndl) {
		globBuff = (char *) GlobalLock(hndl);
		dataLen = ((long *) globBuff)[0];
		dataBuff = globBuff+sizeof(long);
	}
	else {
		hndl = ::GetClipboardData(CF_TEXT);
		globBuff = (char *) GlobalLock(hndl);
		dataLen = strlen(globBuff);
		dataBuff = globBuff;
	}
	p = (unsigned char*) dataBuff;
	startc = GetRichEditCtrl().LineIndex(startl) + 7 + 3 * startind;
	GetRichEditCtrl().SetSel(startc, startc);

	for(i=0;i<dataLen;i++)
	{
		if(m_EOF)
		{
			m_EOF = false;
			break;
		}

		if(*p<16)
		{
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
	int WinLen, NewHexWidth, state, l, OldHexWidth, OldLineLength, buffsize = 1000;
	int maxl, llen;
	char *buffer1, *buffer3;
	unsigned char *buffer2;
	long start, end, pos, l1, l2, l3, adr;
	BOOL modified;

	if(cy) CAppEditView::OnSize(nType, cx, cy);

	m_NewSize = cx;
	if(m_SizeActive == TRUE) return;
	m_SizeActive = TRUE;
	while(m_NewSize > 0) {
		WinLen = m_NewSize / 8 - 1;
		m_NewSize = 0;
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
				ASSERT(l >= 0);
				ASSERT(l2 >= 0);
				ASSERT(l2+l < buffsize/4 + m_hexwidth);
				l2 += l;
				l = l2 / m_hexwidth;
				l = l * m_hexwidth; // Anzahl kompletter Zeilen
				ASSERT(l2 >= 0);
				l3 = HexDumpMem(buffer3, maxl * llen + 1, buffer2, l, m_hexwidth, adr);
				buffer3[l3]=0;
				adr += l;
				ASSERT(l2 >= 0);
				memcpy(buffer2, buffer2+l, l2-l);
				l2 -= l;
				GetRichEditCtrl().ReplaceSel(buffer3);
				//pos += l3; // does not work mit VC++7 because CRNL -> CR (?)
				//workaround: get cursor pos
				long junk;
				GetRichEditCtrl().GetSel(pos,junk);
				ASSERT(pos == junk);
			} while(1);
			l3 = HexDumpMem(buffer3, maxl * llen + 1, buffer2, l2, m_hexwidth, adr);
			GetRichEditCtrl().SetSel(pos, pos);
			GetRichEditCtrl().ReplaceSel(buffer3);
			pos += l3;
			GetRichEditCtrl().SetSel(pos-2, pos);
			GetRichEditCtrl().GetSelText(buffer3);
			if(buffer3[0] == 13)
				GetRichEditCtrl().ReplaceSel("");
			free(buffer1);
			free(buffer2);
			free(buffer3);
			GetRichEditCtrl().SetSel(start, end);
			GetRichEditCtrl().SetModify(modified);
			GetRichEditCtrl().EmptyUndoBuffer();
			SetRedraw(TRUE);
			Invalidate();
		}
	}
	m_SizeActive = 0;
	ASSERT_VALID(this);
}


void CHexView::SerializeRaw(CArchive & ar)
{
	char *buffer;
	char *buffer2;
	int bufflen = 20000, state, l, width, i, t;
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
			if (len == 0)
				break; // HACK: VS7: textlen seems to be 1 byte too long for every line ending...
			l = HexUndumpMem(buffer, len, buffer, &state);
			ASSERT(l >= 0);
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
		ASSERT(pFile->GetLength() < ULONG_MAX);
		unsigned long nFileSize = (unsigned long)pFile->GetLength();


redo:	
		pFile->SeekToBegin();
		width = m_hexwidth;
		l1 = bufflen / width; //maximale Zeilenanzahl im Puffer;
		buff2len = l1 * (4 * width + 11);
		buffer2 = (char *)malloc(buff2len + 1); // Zielpuffergröße
		l1 = l1 * width; // maximale Anzahl Zeichen um eine ganze Zeile zu füllen (im Puffer)

		// ReadFromArchive takes the number of characters as argument

		m_totlen = m_TrailBlanks = m_NoPrintChars = adr = pos = 0;
		do {
			l = pFile->Read(buffer, l1);
			m_totlen += l;
			for(t=l; t>=0; t--) if(buffer[t] != 0) break;
			if(t==-1) m_TrailBlanks += l;
			else m_TrailBlanks = l-t;
			if(l==0) break;
			for(i=0;i<l;i++)
				if((!IsPrint(buffer[i])) && (buffer[i] != 10) && (buffer[i] != 13))
					m_NoPrintChars++;
			l = HexDumpMem(buffer2, buff2len, (unsigned char *) buffer, l, width, adr);
			GetRichEditCtrl().SetSel(pos, -1);
			GetRichEditCtrl().ReplaceSel(buffer2, FALSE);
			if(width != m_hexwidth) {
				free(buffer2);
				goto redo;
			}
			pos += l;
			adr += l1;
		} while(l);
		GetRichEditCtrl().EmptyUndoBuffer();
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


void CHexView::OnUpdateTotxt(CCmdUI* pCmdUI) 
{
	if(m_NoPrintChars > m_TrailBlanks)
	{
        pCmdUI->Enable(FALSE);
	}
	else
	{
        pCmdUI->Enable(TRUE);
	}
}

char CHexView::GetCharAt(int offset)
{
	int line, n;
	char buffer[1024], c;

	line = offset / m_hexwidth;
	GetRichEditCtrl().GetLine(line, buffer, sizeof(buffer) - 1);

	n = offset % m_hexwidth;
	c = 16*HexVal(buffer[7+3*n]) + HexVal(buffer[8+3*n]);

	return c;
}
