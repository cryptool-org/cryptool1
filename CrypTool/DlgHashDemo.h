#if !defined(AFX_HASHDEMO_H__06BADA81_9DFF_11D5_AB3E_0006291976BD__INCLUDED_)
#define AFX_HASHDEMO_H__06BADA81_9DFF_11D5_AB3E_0006291976BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Hashdemo.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHashDemo 

class CDlgHashDemo : public CDialog
{
// Konstruktion
public:
	void SetRed();
	void SetHashDiff(OctetString &hash1,OctetString &hash2);
	void showDiffNewHashBin(OctetString &hash);
	void showDiffOrigHashBin(OctetString &hash);
	CString m_strNewHashBin;
	CString m_strOrigHashBin;
	void SetTitle(char* titel);
	void showNewHashHex(OctetString &hash);
	void showNewHashDec(OctetString &hash);
	void showNewHashBin(OctetString &hash);
	OctetString m_newHashMD2,m_newHashMD5,m_newHashSHA;
	void SetNewHash(OctetString &hashMD2,OctetString &hashMD5,OctetString &hashSHA);
	OctetString * m_Messg;
	OctetString m_sndHashSHA;
	OctetString m_sndHashMD5;
	OctetString m_sndHashMD2;
	OctetString m_hashMD2,m_hashMD5, m_hashSHA;
	OctetString *msg;
	void SetHash(OctetString &hashMD2,OctetString &hashMD5,OctetString &hashSHA);
	CDlgHashDemo(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgHashDemo)
	enum { IDD = IDD_HASH_DEMO };
	CRichEditCtrl	m_ctrlHashDiff;
	CEdit	m_ctrlOrigHash;
	CEdit	m_ctrlNewHash;
	CString	m_strText;
	CFont m_font;
	int		m_rb_DarstHW;
	int		m_Auswahl_HW;
	CString	m_strOrigHash;
	CString	m_strNewHash;
	CString m_strHash;
	CString	m_strTitel;
	CString	m_strTitel2;
	CString	m_strDiffHash;
	CString	m_strHashDiffRE;
	//}}AFX_DATA
	


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgHashDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
private:
	void showHashBin(OctetString &hash);
	void showHashHex(OctetString &hash);
	void showHashDec(OctetString &hash);
	void hashTextWithSha();
	void hashTextWithMd5();
	void hashTextWithMd2();
	char title[256];
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgHashDemo)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioMd2();
	afx_msg void OnRadioMd5();
	afx_msg void OnRadioSha();
	afx_msg void OnRadioBin();
	afx_msg void OnRadioDec();
	afx_msg void OnRadioHex();
	afx_msg void OnChangeEditText();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_HASHDEMO_H__06BADA81_9DFF_11D5_AB3E_0006291976BD__INCLUDED_
