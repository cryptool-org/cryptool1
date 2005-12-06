#if !defined(AFX_DLGFILEPROPERTIES_H__3D89C9AE_32B4_4A62_BA7A_8528F5079608__INCLUDED_)
#define AFX_DLGFILEPROPERTIES_H__3D89C9AE_32B4_4A62_BA7A_8528F5079608__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFileProperties.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFileProperties 

class CDlgFileProperties : public CDialog
{
// Konstruktion
public:
	CString m_title;
	void copyFileInfos(CString contentName, CString title);
	CDlgFileProperties(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgFileProperties)
	enum { IDD = IDD_FILE_PROPERTIES };
	CButton	m_ShowKey;
	CButton	m_ShowFatherWindow;
	CString	m_filename;
	CString	m_fileType;
	CString	m_fileSize;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgFileProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgFileProperties)
	afx_msg void OnShowFather();
	afx_msg void OnShowKey();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGFILEPROPERTIES_H__3D89C9AE_32B4_4A62_BA7A_8528F5079608__INCLUDED_
