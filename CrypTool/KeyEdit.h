#if !defined(AFX_KEYEDIT_H__2330231F_80B3_11D5_A856_00025532117A__INCLUDED_)
#define AFX_KEYEDIT_H__2330231F_80B3_11D5_A856_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KeyEdit.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CKeyEdit 

class CKeyEdit : public CEdit
{
// Konstruktion
public:
	CKeyEdit();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CKeyEdit)
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CKeyEdit();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CKeyEdit)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_KEYEDIT_H__2330231F_80B3_11D5_A856_00025532117A__INCLUDED_
