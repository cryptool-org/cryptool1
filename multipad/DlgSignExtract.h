#ifndef AFX_DLGSIGNEXTRACT_H__9FCAFEFF_FF13_11D3_879C_00C04F795E36__INCLUDED_
#define AFX_DLGSIGNEXTRACT_H__9FCAFEFF_FF13_11D3_879C_00C04F795E36__INCLUDED_

// DlgSignExtract.h : Header-Datei
//
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic, 2000
//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSignExtract 

class CDlgSignExtract : public CDialog
{
// Konstruktion
public:
	// CDlgSignExtract(CWnd* pParent = NULL);   // Standardkonstruktor
	CDlgSignExtract(char* infile_name, const char *title, CWnd* pParent = NULL);

// Dialogfelddaten
	//{{AFX_DATA(CDlgSignExtract)
	enum { IDD = IDD_DIALOG_EXTRACT_SIGNATURE };
	CEdit	m_TextAlgCtrl;
	CEdit	m_TextKeyCtrl;
	CEdit	m_TextSignerCtrl;
	CEdit	m_DefEditCtrl;
	CEdit	m_TextMsgCtrl;
	CEdit	m_TextSigCtrl;
	CEdit	m_MessageCtrl;
	CEdit	m_SignatureCtrl;
	CButton	m_RadioHexadezimal;
	CButton	m_RadioDezimal;
	CButton	m_RadioOktal;
	CButton	m_RadioOctets;
	int		m_sigButtonGroup;
	CString	m_KeyInfo;
	CString	m_Signature;
	CString	m_SignatureLength;
	CString	m_Message;
	CString	m_MessageLength;
	CString	m_InfoAboutSigner;
	CString	m_SigHashAlg;
	CString	m_TextSig;
	CString	m_TextMsg;
	CString	m_TextSigner;
	CString	m_TextKey;
	CString	m_TextAlg;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSignExtract)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	char *inFileName;
	const char *doctitle;
	int hexdumpCols;
	int base;

	L_NUMBER c[MAXLGTH]; // only correct initialized then verifiying EC signatures
	L_NUMBER d[MAXLGTH]; // only correct initialized then verifiying EC signatures
	Signature Signatur; // only correct initialized then verifiying RSA or DSA signatures
	OctetString message; // signed message, enthält später die signierte Nachricht

	int SignatureType;

	CFont Font;
	CFont Font2;

	int UpdateSigEditBox();

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSignExtract)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRadioOctets();
	afx_msg void OnRadioOktal();
	afx_msg void OnRadioDezimal();
	afx_msg void OnRadioHexadezimal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGSIGNEXTRACT_H__9FCAFEFF_FF13_11D3_879C_00C04F795E36__INCLUDED_
