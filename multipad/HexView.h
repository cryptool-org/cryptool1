//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_HEXVIEW_H__0EFC0691_5F70_11D3_8772_00C04F795E36__INCLUDED_
#define AFX_HEXVIEW_H__0EFC0691_5F70_11D3_8772_00C04F795E36__INCLUDED_

// HexView.h : Header-Datei
//

#include "MyEditView.h"

/////////////////////////////////////////////////////////////////////////////
// Ansicht CHexView 

class CHexView : public CMyEditView
{
protected:
	CHexView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CHexView)

// Attribute
public:

// Operationen
public:
	virtual void SerializeRaw(CArchive& ar);
	CSize CharSize;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CHexView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CHexView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	int AdjustCursor(int direction);
	int m_curlen;
	int m_lineoffset;
	int m_curline;
	int m_hexwidth;
	int m_charoffset;
	int m_lineindex;
	char m_line[1024];
	CFont m_Font;
	//{{AFX_MSG(CHexView)
	afx_msg void OnUpdateFalse(CCmdUI* pCmdUI);
	afx_msg void OnEmpty();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditUndo();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_HEXVIEW_H__0EFC0691_5F70_11D3_8772_00C04F795E36__INCLUDED_
