//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

#if !defined(AFX_ASCEDIT_H__2B17B659_F65C_430E_BDB5_9181C5B3C75F__INCLUDED_)
#define AFX_ASCEDIT_H__2B17B659_F65C_430E_BDB5_9181C5B3C75F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AscEdit.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CAscEdit 

class CAscEdit : public CEdit
{
// Konstruktion
public:
	CAscEdit();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CAscEdit)
	//}}AFX_VIRTUAL

// Implementierung
public:
	int busy;
	virtual ~CAscEdit();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CAscEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	int m_mode;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ASCEDIT_H__2B17B659_F65C_430E_BDB5_9181C5B3C75F__INCLUDED_
