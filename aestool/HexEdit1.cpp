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


// HexEdit1.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "HexEdit1.h"

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
	SelOrigin = 0;
}

CHexEdit::~CHexEdit()
{
	free(BinData);
}


BEGIN_MESSAGE_MAP(CHexEdit, CEdit)
	//{{AFX_MSG_MAP(CHexEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CHexEdit 

void CHexEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	char *b;
	int s1, e1;

	preproc(&b,&s1, &e1);

	if(('a' <= nChar) && (nChar <= 'f')) nChar = nChar - 'a' + 'A';
	if((-1 != HexVal((char)nChar)) || (nChar == 8) ||
		(nChar == 3) || (nChar == 16) || (nChar == 18) || (nChar == 22)) {
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
		b=b;

	postproc(b, s1, e1);
}

void CHexEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	char *b;
	int s1, e1;

	switch(nChar) {
	case(VK_LEFT):
	case(VK_RIGHT):
	case(VK_END):
	case(VK_HOME):
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
		preproc(&b,&s1, &e1);
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
		postproc(b, s1, e1);
		break;
	}
}

int CHexEdit::extend(int val, int max)
{
	if((max == val) && ((val % 2) == 0)) return (val + (val >> 1) - 1);
	return (val + (val >> 1));
}

int CHexEdit::shrink(int val)
{
	return (val - (val / 3));
}

void CHexEdit:: preproc( char **oldstring, int *start, int *end )
{
	int i,j,l;
	char *b1, *b2;

	SetRedraw(FALSE);
	active = 1;
	l = LineLength();
	b1 = (char *) malloc(l+2);
	b2 = (char *) malloc(l+2);
	GetLine(0,b1,l+1);
	GetSel(*start,*end);
	b1[l]=0;
	for(i=j=0;i<l;i++) {
		if(2 != (i%3)) {
			b2[j] = b1[i];
			j++;
		}
	}
	b2[j]=0;
	SetSel(0, l);
	ReplaceSel(b2);
	SetSel(shrink(*start),shrink(*end));
	*oldstring = b1;
	free(b2);
}

void CHexEdit::postproc( char *oldstring, int start, int end )
{
	char *b1,*b2,*b3;
	int i,j,l,s2,e2;

	b1 = oldstring;
	l = LineLength();
	b3 = (char *) malloc(l+2);
	b2 = (char *) malloc(l + l + 2);
	GetLine(0,b3,l+1);
	_strupr(b3);
	if(BinBuffLen * 2 < l) {
		free(BinData);
		BinBuffLen = l/2 + 128;
		BinData = (char *) calloc(BinBuffLen,1);
	}
	GetSel(s2,e2);
	for(i=j=0;i<l;i++) {
		if(-1 != HexVal(b3[i])) {
			if(2 == (j%3)) {
				b2[j] = ' ';
				j++;
			}
			b2[j] = b3[i];
			j++;
		}
	}
	b2[j]=0;
	SetSel(0, l);
	ReplaceSel(b2);
	SetSel(extend(s2,l),extend(e2,l));
	SetRedraw(TRUE);
	if(strcmp(b1,b2) || (start != extend(s2,l)) || (end != extend(e2,l))) {
		Invalidate(TRUE);
		for(i=0;i<j;i+=3) {
			BinData[i/3] = (char)(HexVal(b2[i])*16 + HexVal(b2[i+1]));
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
	if(('0' <= c) && (c <= '9')) return c-'0';
	if(('A' <= c) && (c <= 'F')) return c+10-'A';
	if(('a' <= c) && (c <= 'f')) return c+10-'a';
	if(c==0) return 0;	// for ease of conversion
	return -1;
}

int CHexEdit::SetHex(char * data, int len)
{
	if(BinBuffLen < len) {
		free(BinData);
		BinBuffLen = len + 128;
		BinData = (char *) calloc(BinBuffLen,1);
	}
	memcpy(BinData, data, len);
	BinLen = len;
	return len;
}

void CHexEdit::OnUpdate() 
{
	int l,ss1,se1,ss2,se2,i,p;
	char *b1, *b2;

	if(active) return;

	active = 1;
	SetRedraw(FALSE);
	l = LineLength();
	b1 = (char *) malloc(l+2);
	b2 = (char *) malloc(2*l+2);
	GetLine(0,b1,l+1);
	_strupr(b1);
	GetSel(ss1,se1);

	ss2 = se2 = 0;
	for(p=i=0;i<l;i++) {
		if(i==ss1) ss2 = p;
		if(i==se1) se2 = p;
		if(-1 == HexVal(b1[i])) continue; // ignore non hex
		b2[p++]=b1[i];
		if((2 == (p%3)) && (i<l-1)) b2[p++] = ' ';
	}
	b2[p]=0;
	SetSel(0, l);
	ReplaceSel(b2);
	SetSel(ss2,se2);
	SetRedraw(TRUE);
	Invalidate(TRUE);
	for(i=0;i<p;i+=3) {
		BinData[i/3] = (char)(HexVal(b2[i])*16 + HexVal(b2[i+1]));
	}
	BinLen = (p+2)/3;
	active = 0;
	free(b1);
	free(b2);
}
