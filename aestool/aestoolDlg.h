// aestoolDlg.h : Header-Datei
//

#if !defined(AFX_AESTOOLDLG_H__A8D430F4_1896_11D5_8ACA_0010A4F6E7D5__INCLUDED_)
#define AFX_AESTOOLDLG_H__A8D430F4_1896_11D5_8ACA_0010A4F6E7D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HexEdit1.h"

/////////////////////////////////////////////////////////////////////////////
// CAestoolDlg Dialogfeld

#define FILE_MAGIC	0x18273645
#define DIR_ENCRYPT	0
#define DIR_DECRYPT	1

class CAestoolDlg : public CDialog
{
// Konstruktion
public:
	int DoDecrypt();
	void DoEncrypt ( void );
	void SetDestName( void );
	int findStr(CString l);
	void ScanCMDLine( char * cmd );
	CString m_CMD_inKey;
	CString m_CMD_outName;
	CString m_CMD_inName;
	int m_direction;
	CString OrgName;
	long NameLen;
	long DataLen;
	long Magic;
	CFile EXEFile;
	CString EXEName;
	CAestoolDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CAestoolDlg)
	enum { IDD = IDD_AESTOOL_DIALOG };
	CEdit	m_CNameDst;
	CEdit	m_CNameSrc;
	CHexEdit	m_HexIn;
	CButton	m_SucheDst;
	CButton	m_SucheSrc;
	CString	m_title;
	CString	m_NameSrc;
	CString	m_NameDst;
	CString	m_HexString;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAestoolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CAestoolDlg)
	virtual BOOL OnInitDialog();
	afx_msg	void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSucheSrc();
	afx_msg void OnSucheDst();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_AESTOOLDLG_H__A8D430F4_1896_11D5_8ACA_0010A4F6E7D5__INCLUDED_)
