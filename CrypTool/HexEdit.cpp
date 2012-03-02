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


// HexEdit1.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "HexEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHexEdit

CHexEdit::CHexEdit()
{
	BinData = (char *) calloc(128,1);
	BinBuffLen = 128;
	BinLen = 0;
	active = 0;
	m_validchars = "0123456789ABCDEF";
	m_fixedbytelength = 0;
	m_fillchar = '0';
	m_insert = 0;
}

CHexEdit::~CHexEdit()
{
	free(BinData);
}


BEGIN_MESSAGE_MAP(CHexEdit, CEdit)
	//{{AFX_MSG_MAP(CHexEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_MESSAGE(WM_PASTE, OnPaste)
	ON_CONTROL_REFLECT_EX(EN_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CHexEdit 

void CHexEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	char *b;
	int s1, e1;

	if (nChar >= 'a' && nChar <= 'z')
		nChar=nChar-'a'+'A';
	if(!isvalidchar(nChar))
		return;
	preproc(&b,&s1, &e1, nChar);
	CEdit::OnChar(nChar, nRepCnt, nFlags);
	postproc(b, s1, e1);
}

void CHexEdit::SetFixedByteLength(int l) 
{ 
	m_fixedbytelength = l; 
	char *b;
	int s1, e1;
	preproc(&b,&s1, &e1, 0);
	postproc(b, s1, e1);
	//SetLimitText(2*l);
}

bool CHexEdit::isvalidchar(char c)
{
	if (strchr(m_validchars,c))
		return true;
	if ((c == 8) || (c == 3) || (c == 16) || (c == 18) || (c == 22) || (c == 23)|| (c == 24))
		return true;
	return false;
}

void CHexEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	char *b;
	int s1, e1;

	switch(nChar)
	{
	case VK_INSERT:
		m_insert = !m_insert;
		break;
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
	case VK_DOWN:
	case VK_END:
	case VK_HOME:
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
		GetSel(s1,e1);
		if((s1 == e1) && (s1%3 == 2)) {
			if(nChar == VK_LEFT) SetSel(s1-1,s1-1);
			if(nChar == VK_RIGHT) SetSel(s1+1,s1+1);
		}
		SetRedraw(TRUE);
		Invalidate(TRUE);
		break;
	default:
		preproc(&b,&s1, &e1, nChar);
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
		postproc(b, s1, e1);
		break;
	}
}

int CHexEdit::extend(int val, int max)
{
	if((max == val) && ((val % 2) == 0))
		return (val + (val >> 1) - 1);
	return (val + (val >> 1));
}

int CHexEdit::shrink(int val)
{
	return (val - (val / 3));
}

void CHexEdit:: preproc( char **oldstring, int *start, int *end, char ch )
{
	int i,j,l;
	char *b1, *b2;

	SetRedraw(FALSE);
	active = 1;
	l = GetWindowTextLength();
	b1 = (char *) malloc(l+2);
	b2 = (char *) malloc(l+2);
	GetWindowText(b1,l+1);
	GetSel(*start,*end);
	b1[l]=0;
	for(i=j=0;i<l;i++)
	{
		if(2 != (i%3))
		{
			b2[j] = b1[i];
			j++;
		}
	}
	b2[j]=0;
	//SetSel(0, l);
	//ReplaceSel(b2); // can lead to an endless recursion and stack overflow if edit control cannot display all chars
	SetWindowText(b2);
	int sstart = shrink(*start);
	int send = shrink(*end);
	if (!m_insert && sstart == send && send < j && strchr(m_validchars,ch))
		send++;
	SetSel(sstart,send);
	*oldstring = b1;
	free(b2);
}

void CHexEdit::postproc( char *oldstring, int start, int end )
{
	char *b1,*b2,*b3;
	int i,j;
	int la,lt; //  actual, target length in hex digits
	int s2,e2;

	b1 = oldstring;
	la = GetWindowTextLength();
	b3 = (char *) malloc(la+1);
	GetWindowText(b3,la+1);
	if (m_fixedbytelength) {
		lt = 2 * m_fixedbytelength;
	} else { // count valid hex chars (^V can insert non hex chars just before postproc is called)
		lt = 0;
		for (i = 0; i < la; i++)
			if (HexVal(b3[i]) != -1)
				lt++;
	}
	int ltspace = lt + (lt - 1) / 2 ;
	b2 = (char *) malloc(ltspace + 1); // make room for ' '
	_strupr(b3);
	if(BinBuffLen * 2 < lt)
	{
		free(BinData);
		BinBuffLen = lt/2 + 128;
		BinData = (char *) calloc(BinBuffLen,1);
	}
	GetSel(s2,e2);
	for(i = j = 0; i < la && j < ltspace; i++)
	{
		char c = b3[i];
		if(strchr(m_validchars,c))
		{
			ASSERT(j < ltspace);
			if(2 == (j%3))
				b2[j++] = ' ';
			ASSERT(j < ltspace);
			b2[j++] = c;
		}
	}
	ASSERT(j <= ltspace);
	while (j < ltspace) {
		ASSERT(j < ltspace);
		if(2 == (j%3))
			b2[j++] = ' ';
		ASSERT(j < ltspace);
		b2[j++] = m_fillchar;
	}
	ASSERT(j == ltspace);
	b2[j]=0;
	//SetSel(0, la);
	//ReplaceSel(b2); // can lead to an endless recursion and stack overflow if edit control cannot display all chars
	SetWindowText(b2);
	SetSel(extend(s2,lt),extend(e2,lt));
	LineScroll(LineFromChar());
	SetRedraw(TRUE);
	if(strcmp(b1,b2) || (start != extend(s2,lt)) || (end != extend(e2,lt)))
	{
		Invalidate(TRUE);
		for(i=0;i<j;i+=3)
		{
			BinData[i/3] = HexVal(b2[i])*16 + HexVal(b2[i+1]);
		}
		BinLen = (j+2)/3;
	}

	free(b1);
	free(b2);
	free(b3);
	active = 0;
}

int CHexEdit::HexVal(char c)
{
	if(('0' <= c) && (c <= '9'))
		return c-'0';
	if(('A' <= c) && (c <= 'F'))
		return c+10-'A';
	if(('a' <= c) && (c <= 'f'))
		return c+10-'a';
	if (c==0)
		return 0;
	return -1;
}

int CHexEdit::SetHex(char * data, int len)
{
	if(BinBuffLen < len)
	{
		free(BinData);
		BinBuffLen = len + 128;
		BinData = (char *) calloc(BinBuffLen,1);
	}
	memcpy(BinData, data, len);
	BinLen = len;
	return len;
}

int CHexEdit::SetAscii(CString c)
{
	int len,i,j;

	len=c.GetLength();
	if(BinBuffLen < (len+1)/2)
	{
		free(BinData);
		BinBuffLen = (len+1)/2 + 128;
		BinData = (char *) calloc(BinBuffLen,1);
	}
	i=j=0;
	while (i<len)
	{
		if (i%2)
			BinData[j++]+=(HexVal(c[i++]));
		else
			BinData[j]+=(HexVal(c[i++])<<4);
	}
	BinLen = j;
	return j;
}
LRESULT CHexEdit::OnPaste(WPARAM wparam, LPARAM lparam)
{
	// flomar, 03/01/2012: both calls, this leading call to 'preproc' as well as 
	// the trailing call to 'postproc' (see below) are necessary to provide 
	// error-free copy/paste functionality
	char *b;
	int s1, e1;
	preproc(&b,&s1, &e1, 0);
	
	CString clipboardText;

	// at first we try to get the contents of the clipboard
  if(::IsClipboardFormatAvailable(CF_TEXT)) {
    // open the clipboard to get clipboard text
    if(::OpenClipboard(m_hWnd)) {
      HANDLE  hClipBrdData = NULL;
      if((hClipBrdData = ::GetClipboardData(CF_TEXT)) != NULL) {
        LPTSTR  lpClipBrdText = (LPTSTR)::GlobalLock(hClipBrdData);
        if(lpClipBrdText) {
          clipboardText = lpClipBrdText;
          ::GlobalUnlock(hClipBrdData);
        }
      }
			VERIFY(::CloseClipboard());
		}
	
		// now we should have the contents of the clipboard;
		// however, we need to replace the line breaks with spaces 
		// to prevent the input field from getting messed up
		int lineBreakIndex = 0;
		while((lineBreakIndex = clipboardText.Find("\r\n")) != -1) {
			clipboardText.Delete(lineBreakIndex, 2);
			clipboardText.Insert(lineBreakIndex, " ");
		}
	}

	// replace existing selection (don't replace text that was not selected)
	CString oldText;
	GetWindowText(oldText);
	
	int selectionStart = 0;
	int selectionEnd = 0;
	this->GetSel(selectionStart, selectionEnd);

	CString newText;
	newText.Append(oldText.GetBuffer(), selectionStart);
	newText.Append(clipboardText);
	newText.Append(oldText.GetBuffer() + selectionEnd, oldText.GetLength() - selectionEnd);

	// set the new window text
	SetWindowTextA(newText);

	// flomar, 03/01/2012: see comment avove (call to 'preproc')
	postproc(b, s1, e1);
	
	return 0;
}

BOOL CHexEdit::OnUpdate() 
{
	int l,ss1,se1,ss2,se2,i,p;
	char *b1, *b2;

	if(active) return FALSE;

	active = 1;
	SetRedraw(FALSE);
	l = GetWindowTextLength();
	b1 = (char *) malloc(l+2);
	b2 = (char *) malloc(2*l+2);
	GetWindowText(b1,l+1);
	_strupr(b1);
	GetSel(ss1,se1);

	ss2 = se2 = 0;
	for(p=i=0;i<l;i++) {
		if(i==ss1) ss2 = p;
		if(i==se1) se2 = p;
		//if(-1 == HexVal(b1[i])) continue; // ignore non hex
		if(!isvalidchar(b1[i])) continue; // ignore non hex
		b2[p++]=b1[i];
		if((2 == (p%3)) && (i<l-1)) b2[p++] = ' ';
	}
	b2[p]=0;
	SetSel(0, l);
	ReplaceSel(b2);
	SetSel(ss2,se2);

	// FIXME: the following memory allocation was implemented to close a memory leak;
	//        implement a function "reAllocBinData()", because this code snippet is 
	//        used all over this source file.
	int len=strlen(b2);
	if(BinBuffLen < (len+1)/2)
	{
		free(BinData);
		BinBuffLen = (len+1)/2 + 128;
		BinData = (char *) calloc(BinBuffLen,1);
	}
	// FIXME END

	SetRedraw(TRUE);
	Invalidate(TRUE);
	for(i=0;i<p;i+=3) {
		BinData[i/3] = HexVal(b2[i])*16 + HexVal(b2[i+1]);
	}
	BinLen = (p+2)/3;
	active = 0;
	free(b1);
	free(b2);
	return TRUE;
}
