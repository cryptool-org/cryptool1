#if !defined(AFX_DLGDIFFIEHELLMANSECRETINPUT_H__5F417B9F_EFB8_11D6_A8A3_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANSECRETINPUT_H__5F417B9F_EFB8_11D6_A8A3_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanSecretInput.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanSecretInput 

class CDlgDiffieHellmanSecretInput : public CDialog
{
private:
	Big m_Prime;
	std::string m_Party;

// Konstruktion
public:
	CDlgDiffieHellmanSecretInput(CWnd* pParent = NULL);			// Standardkonstruktor
	CDlgDiffieHellmanSecretInput(std::string,Big&,CWnd* pParent = NULL);				// Zus�tzlicher Konstruktor
	CDlgDiffieHellmanSecretInput(std::string,std::string,Big&,CWnd* pParent = NULL);	// Zus�tzlicher Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanSecretInput)
	enum { IDD = IDD_DIFFIEHELLMAN_SECRETINPUT };
	CButton	m_CtrlOKButton;
	CButton	m_ButtonGenSec;
	CEdit	m_SecretControl;
	CString	m_Secret;
	CString	m_PartyHeader;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanSecretInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanSecretInput)
	virtual void OnOK();
	afx_msg void OnGenerateSecret();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANSECRETINPUT_H__5F417B9F_EFB8_11D6_A8A3_00025532117A__INCLUDED_
