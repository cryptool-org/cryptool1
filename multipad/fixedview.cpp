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
	m_blocklen = 5;
	m_winlen = 10;
}

CFixedView::~CFixedView()
{
}


BEGIN_MESSAGE_MAP(CFixedView, CMyEditView)
	//{{AFX_MSG_MAP(CFixedView)
	ON_WM_SIZE()
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
	MyUpdate();
}

void CFixedView::SerializeRaw(CArchive & ar)
{
	unsigned char *buffer;
	char *buffer2;
	int l, maxline;

	if (ar.IsStoring())
	{
		LPCTSTR lpszText = LockBuffer();
		ASSERT(lpszText != NULL);
		UINT nLen = GetBufferLength();
		buffer = (unsigned char *) malloc(nLen); // maximale Größe fuer das Ergebnis
		l = ASCUndumpMem(lpszText, nLen, (char *) buffer, SepChar);
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

		CAscDoc* pDoc = (class CAscDoc *)GetDocument();
		m_blocklen=pDoc->m_blocklen;
		
		maxline = (nFileSize / (m_blocklen*m_AscBlocks)) + 1;
		l =  nFileSize + nFileSize/m_blocklen + maxline; // maximale Größe des Dumps + 1

		buffer = (unsigned char *) malloc(nFileSize); // Zwischenpuffer

		buffer2 = (char *) malloc(l);
		ar.Read(buffer, nLen);
		l = ASCDumpMem(buffer2, l, (char *) buffer, nFileSize, m_blocklen, m_AscBlocks, &SepChar);
		// Replace the editing edit buffer with the newly loaded data
		buffer2[l] = '\0';
		free(buffer);

		SetWindowText(buffer2);
		free(buffer2);
		Invalidate();
		ASSERT_VALID(this);
	}
	ASSERT_VALID(this);
}

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
	int WinLen, NewASCWidth, l, maxline;
	char *buffer, *NewBuffer, *OldBuffer;

	WinLen=m_winlen;
	CAscDoc* pDoc = (class CAscDoc *)GetDocument();
	m_blocklen=pDoc->m_blocklen;
		
	NewASCWidth = WinLen / (m_blocklen+1);
	NewASCWidth = max(NewASCWidth, 4);
	if(NewASCWidth != m_AscBlocks) { // Größe anpassen!
		m_AscBlocks = NewASCWidth;
		UINT nLen = GetWindowTextLength();
		OldBuffer = (char *) malloc(nLen+3);
		GetWindowText(OldBuffer, nLen+2);
		buffer = (char *) malloc(nLen); // maximale Größe fuer das Ergebnis
		l = ASCUndumpMem(OldBuffer, nLen, (char *) buffer, SepChar);
		free(OldBuffer);
		maxline = (l / (m_AscBlocks * m_blocklen)) + 1;
		maxline =  maxline * (m_AscBlocks * (m_blocklen+1) + 2); // maximale Größe des Dumps + 1
		NewBuffer = (char *) malloc(maxline);
		l = ASCDumpMem(NewBuffer, maxline, buffer, l, m_blocklen, m_AscBlocks, &SepChar);
		NewBuffer[l] = '\0';
		free(buffer);
		SetWindowText(NewBuffer);
		free(NewBuffer);
		Invalidate();
	}
	ASSERT_VALID(this);
}
