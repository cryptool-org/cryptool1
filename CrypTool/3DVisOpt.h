#if !defined(AFX_3DVISOPT_H__15C59C13_FFA8_4BC3_930C_4F19DDCD0199__INCLUDED_)
#define AFX_3DVISOPT_H__15C59C13_FFA8_4BC3_930C_4F19DDCD0199__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DVisOpt.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld C3DVisOpt 

class C3DVisOpt : public CDialog
{
// Konstruktion
public:
	unsigned short resolution;
	C3DVisOpt(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(C3DVisOpt)
	enum { IDD = IDD_SET_VISOPT };
	CSliderCtrl	m_CtrlSliderResolution;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(C3DVisOpt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(C3DVisOpt)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_3DVISOPT_H__15C59C13_FFA8_4BC3_930C_4F19DDCD0199__INCLUDED_
