#ifndef AFX_MYEDITVIEW_H__AD95E45B_D56B_11D3_878E_00C04F795E36__INCLUDED_
#define AFX_MYEDITVIEW_H__AD95E45B_D56B_11D3_878E_00C04F795E36__INCLUDED_

// MyEditView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Ansicht CMyEditView 

class CMyEditView : public CRichEditView
{
protected:
	CMyEditView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CMyEditView)

// Attribute
public:

// Operationen
public:
	virtual HRESULT QueryAcceptData( LPDATAOBJECT lpdataobj, CLIPFORMAT FAR * lpcfFormat, DWORD dwReco, BOOL bReally, HGLOBAL hMetaFile );
	virtual void SerializeRaw(CArchive& ar);

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CMyEditView)
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CMyEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CMyEditView)
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
