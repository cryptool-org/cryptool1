//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// FixedView.cpp : implementation file
//

#include "stdafx.h"
#include "multipad.h"
#include "FixedView.h"
#include "fileutil.h"
#include "cryptdoc.h"

/////////////////////////////////////////////////////////////////////////////
// CFixedView

IMPLEMENT_DYNCREATE(CFixedView, CMyEditView)

CFixedView::CFixedView()
{
	m_AscBlocks = 4;
	SepChar = 0;
	m_nWordWrap = WrapNone;
	m_blocklen = 5;
	m_winlen = 10;
}

CFixedView::~CFixedView()
{
}


BEGIN_MESSAGE_MAP(CFixedView, CMyEditView)
	//{{AFX_MSG_MAP(CFixedView)
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFixedView diagnostics

#ifdef _DEBUG
void CFixedView::AssertValid() const
{
	CMyEditView::AssertValid();
}

void CFixedView::Dump(CDumpContext& dc) const
{
	CMyEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFixedView message handlers

void CFixedView::OnInitialUpdate() 
{
    m_Font.CreatePointFont(80, "Courier", NULL);
    SetFont(&m_Font);
	CMyEditView::OnInitialUpdate();
//	MyUpdate();
}

void CFixedView::SerializeRaw(CArchive & ar)
{
	char *buffer, *buffer2;
	int bufflen=20000, len, l, l1, l2, buff2len;
	long start, end, textlen, pos;

	GetRichEditCtrl().GetSel(start, end);
	buffer = (char *) malloc(bufflen+3);

	if (ar.IsStoring())
	{
		SetRedraw(FALSE);
		textlen = GetRichEditCtrl().GetTextLength();

		for(pos = 0; pos < textlen; ) {
			GetRichEditCtrl().SetSel(pos, pos+bufflen);
			len = GetRichEditCtrl().GetSelText(buffer);
			l = ASCUndumpMem(buffer, len, buffer, SepChar);
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

		l2 = 5 * m_AscBlocks; // Zeichen je Zeile
		l1 = bufflen / l2; //maximale Zeilenanzahl im Puffer;
		buff2len = l1 * (6 * m_AscBlocks + 2);
		buffer2 = (char *)malloc(buff2len); // Zielpuffergröße
		l1 = l1 * l2; // maximale Anzahl Zeichen um eine ganze Zeile zu füllen (im Puffer)

		// ReadFromArchive takes the number of characters as argument

		pos = 0;
		do {
			l = ar.Read(buffer, l1);
			if(l==0) break;
			l = ASCDumpMem(buffer2, buff2len, (char *) buffer, l, 5, m_AscBlocks, &SepChar);
			buffer2[l] = '\0';
			GetRichEditCtrl().SetSel(pos, pos);
			GetRichEditCtrl().ReplaceSel(buffer2);
			pos += l;
		} while(l);
		free(buffer2);
		Invalidate();
		ASSERT_VALID(this);
	}
	free(buffer);
	ASSERT_VALID(this);
}

/*
void CFixedView::OnSize(UINT nType, int cx, int cy) 
{
	CMyEditView::OnSize(nType, cx, cy);
	
	m_winlen = cx / 8;
	MyUpdate();
}

void CFixedView::OnUpdate( CView* pSender, LPARAM lHint, CObject* pHint )
{
	MyUpdate();
	CMyEditView::OnUpdate(pSender,lHint,pHint);
}

void CFixedView::MyUpdate()
{
	int WinLen, NewASCWidth, l, buffsize = 20000;
	long start, end, pos, l1, l2, l3, b3l;
	int cpl, llen;
	char *buffer1, *buffer2, *buffer3;

	WinLen=m_winlen;
	CAscDoc* pDoc = (class CAscDoc *)GetDocument();
	m_blocklen=pDoc->m_blocklen;		
	NewASCWidth = WinLen / (m_blocklen+1);
	NewASCWidth = max(NewASCWidth, 4);

	if(NewASCWidth != m_AscBlocks) { // Größe anpassen!
		buffer1 = (char *) malloc(buffsize+1);
		GetRichEditCtrl().GetSel(start, end);
		m_AscBlocks = NewASCWidth;
		cpl = m_AscBlocks *5;
		buffer2 = (char *) malloc(buffsize+cpl+1);
		llen = m_AscBlocks * 6 + 1;
		UINT nLen = GetTextLength();
		b3l = (buffsize / cpl + 2) * llen + 1;
		buffer3 = (char *) malloc(b3l+1);
		l1 = l2 = l3 = pos = 0;
		SetRedraw(FALSE);
		do {
			GetRichEditCtrl().SetSel(pos, pos + buffsize);
			l1 = GetRichEditCtrl().GetSelText(buffer1);
			ASSERT(l1<=buffsize);
			if(l1 == 0) break;
			ASSERT(l2+l1 <= buffsize+cpl);
			l2 += ASCUndumpMem(buffer1, l1, buffer2+l2, SepChar);
			ASSERT(l2 <= buffsize+cpl);
			l = l2/cpl;
			l = l*cpl;
			l3 = ASCDumpMem(buffer3, b3l, buffer2, l, 5, m_AscBlocks, &SepChar);
			ASSERT(l3 < b3l);
			buffer3[l3] = 0;
			GetRichEditCtrl().ReplaceSel(buffer3);
			pos += l3;
			memcpy(buffer2, buffer2+l, l2-l);
			l2 -= l;
			ASSERT(l2 < cpl);
		} while(l);
		l3 = ASCDumpMem(buffer3, b3l, buffer2, l2, 5, m_AscBlocks, &SepChar);
		buffer3[l3] = 0;
		GetRichEditCtrl().SetSel(pos, pos);
		GetRichEditCtrl().ReplaceSel(buffer3);
		pos += l3;
		free(buffer1);
		free(buffer2);
		free(buffer3);
		GetRichEditCtrl().SetSel(start, end);
		SetRedraw(TRUE);
		Invalidate();
	}
	ASSERT_VALID(this);
}
*/

void CFixedView::OnSize(UINT nType, int cx, int cy) 
{
	int WinLen, NewASCWidth, l, buffsize = 20000;
	long start, end, pos, l1, l2, l3, b3l;
	int cpl, llen;
	char *buffer1, *buffer2, *buffer3;
	BOOL modified;

	CMyEditView::OnSize(nType, cx, cy);

// **** to be done ****
	
	WinLen = cx / 8 - 1;
	NewASCWidth = WinLen / 6;
	NewASCWidth = max(NewASCWidth, 4);
	if(NewASCWidth != m_AscBlocks) { // Größe anpassen!
		modified = GetRichEditCtrl().GetModify();
		buffer1 = (char *) malloc(buffsize+1);
		GetRichEditCtrl().GetSel(start, end);
		m_AscBlocks = NewASCWidth;
		cpl = m_AscBlocks * 5;
		buffer2 = (char *) malloc(buffsize+cpl+1);
		llen = m_AscBlocks * 6 + 1;
		UINT nLen = GetTextLength();
		b3l = (buffsize / cpl + 2) * llen + 1;
		buffer3 = (char *) malloc(b3l+1);
		l1 = l2 = l3 = pos = 0;
		SetRedraw(FALSE);
		do {
			GetRichEditCtrl().SetSel(pos, pos + buffsize);
			l1 = GetRichEditCtrl().GetSelText(buffer1);
			ASSERT(l1<=buffsize);
			if(l1 == 0) break;
			ASSERT(l2+l1 <= buffsize+cpl);
			l2 += ASCUndumpMem(buffer1, l1, buffer2+l2, SepChar);
			ASSERT(l2 <= buffsize+cpl);
			l = l2/cpl;
			l = l*cpl;
			l3 = ASCDumpMem(buffer3, b3l, buffer2, l, 5, m_AscBlocks, &SepChar);
			ASSERT(l3 < b3l);
			buffer3[l3] = 0;
			GetRichEditCtrl().ReplaceSel(buffer3);
			pos += l3;
			memcpy(buffer2, buffer2+l, l2-l);
			l2 -= l;
			ASSERT(l2 < cpl);
		} while(l);
		l3 = ASCDumpMem(buffer3, b3l, buffer2, l2, 5, m_AscBlocks, &SepChar);
		buffer3[l3] = 0;
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


void CFixedView::OnEditPaste() 
{
	long start1, end1, len1, len2, start2, end2;
	CHARFORMAT cformat;
	PARAFORMAT pformat;

	GetRichEditCtrl().GetSel(start1,end1);
	len1 = GetTextLength();
	GetRichEditCtrl().GetSelectionCharFormat(cformat);
	GetRichEditCtrl().GetParaFormat(pformat);

	SetRedraw(FALSE);

	CRichEditView::OnEditPaste();
	
	GetRichEditCtrl().GetSel(start2,end2);
	len2 = GetTextLength();

	GetRichEditCtrl().SetSel(start1,end2);

	SetCharFormat(cformat);
	SetParaFormat(pformat);
	GetRichEditCtrl().SetSel(start2, end2);

	SetRedraw(TRUE);
	Invalidate(TRUE);
}

HRESULT CFixedView::QueryAcceptData(LPDATAOBJECT lpdataobj, CLIPFORMAT *lpcfFormat, DWORD dwReco, BOOL bReally, HGLOBAL hMetaFile)
{
	ASSERT(lpcfFormat != NULL);
	if (!bReally) // not actually pasting
		return S_OK;

	COleDataObject dataobj;
	dataobj.Attach(lpdataobj, FALSE);
	// if format is 0, then force particular formats if available
	if (*lpcfFormat == 0 && (m_nPasteType == 0))
	{
		if (dataobj.IsDataAvailable(CF_TEXT))
		{
			*lpcfFormat = CF_TEXT;
			return S_OK;
		}
	}
	return S_FALSE;
}

