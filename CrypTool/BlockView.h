//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// FixedView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBlockView view

#include "AppEditView.h"

class CBlockView : public CAppEditView
{
protected:
	CFont m_Font;
	CBlockView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CBlockView)
	int m_winlen;

// Attributes
public:

// Operations
public:
	virtual HRESULT QueryAcceptData( LPDATAOBJECT lpdataobj, CLIPFORMAT FAR * lpcfFormat, DWORD dwReco, BOOL bReally, HGLOBAL hMetaFile );
	char SepChar;
	int m_AscBlocks,m_blocklen;
	virtual void SerializeRaw(CArchive& ar);
//	void MyUpdate();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlockView)
	public:
	virtual void OnInitialUpdate();
//	virtual void OnUpdate( CView*, LPARAM, CObject*);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBlockView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CBlockView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditPaste();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

