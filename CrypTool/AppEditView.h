#ifndef AFX_MYEDITVIEW_H__AD95E45B_D56B_11D3_878E_00C04F795E36__INCLUDED_
#define AFX_MYEDITVIEW_H__AD95E45B_D56B_11D3_878E_00C04F795E36__INCLUDED_

// MyEditView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Ansicht CAppEditView 

class CAppEditView : public CRichEditView
{
protected:
	CAppEditView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CAppEditView)

// Attribute
public:

// Operationen
public:
	virtual HRESULT QueryAcceptData( LPDATAOBJECT lpdataobj, CLIPFORMAT FAR * lpcfFormat, DWORD dwReco, BOOL bReally, HGLOBAL hMetaFile );
	virtual void SerializeRaw(CArchive& ar);

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CAppEditView)
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CAppEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	CFont font;
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//{{AFX_MSG(CAppEditView)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnGotoVater();
	afx_msg void OnShowKey();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_MYEDITVIEW_H__AD95E45B_D56B_11D3_878E_00C04F795E36__INCLUDED_
