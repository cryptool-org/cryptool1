//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// FixedView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFixedView view

#include "MyEditView.h"

class CFixedView : public CMyEditView
{
protected:
	CFont m_Font;
	CFixedView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFixedView)
	int m_winlen;

// Attributes
public:

// Operations
public:
	char SepChar;
	int m_AscBlocks,m_blocklen;
	virtual void SerializeRaw(CArchive& ar);
	void MyUpdate();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFixedView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnUpdate( CView*, LPARAM, CObject*);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFixedView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CFixedView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
