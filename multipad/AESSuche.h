//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// Dialogfeld AESSuche 

#if !defined(AFX_AESSUCHE_H__D6167951_518F_11D4_A04D_002035F23D41__INCLUDED_)
#define AFX_AESSUCHE_H__D6167951_518F_11D4_A04D_002035F23D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////////
// Dialogfeld AESSuche 
#define STARS 5

class CMyHexEdit : public CHexEdit
{
public:
	CMyHexEdit();
	bool isvalidchar(char);
	int starcount;
};

class AESSuche : public CDialog
{
// Konstruktion
public:
	AESSuche(CWnd* pParent = NULL);   // Standardkonstruktor

	char m_data[65];
	int m_mask[STARS];
	int m_len;
	int m_text_len;
	long m_co,m_max;
	int Display(char *,int);
	int Display(char *);
	int GetLen();
	int GetBinlen();
	char *GetData();
	void GetDataInt(char *);
	int Step();

// Dialogfelddaten
	//{{AFX_DATA(AESSuche)
	enum { IDD = IDD_DIALOG1 };
	CString	m_text;
	CMyHexEdit m_text_ctl;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(AESSuche)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(AESSuche)
	afx_msg void OnUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_AESSUCHE_H__D6167951_518F_11D4_A04D_002035F23D41__INCLUDED_
