/////////////////////////////////////////////////////////////////////////////
// 
// RSA-Demonstration: (c) Deutsche Bank AG 1998 - 2002
// ~~~~~~~~~~~~~~~~~~
//
// Dialog für die Durchführung des RSA-Kryptosystems im Detail
//
//


#if !defined(AFX_RSA_MIT_KLEINENPZ_H__42495664_FB3E_11D4_BEF2_0006291976BD__INCLUDED_)
#define AFX_RSA_MIT_KLEINENPZ_H__42495664_FB3E_11D4_BEF2_0006291976BD__INCLUDED_

#include "DlgPrimesGeneratorDemo.h"	// Hinzugefügt von der Klassenansicht
#include "DlgOptionsRSADemo.h"
#include "DlgFactorisationDemo.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// Fenster CMyRSADemoEdit 

class CMyRSADemoEdit : public CEdit
{
	BOOL pasteFlag;
	// Konstruktion
public:
	CMyRSADemoEdit();
	BOOL PasteKey() { return pasteFlag; }
// Attribute
public:

// Operationen
public:
	int mode;
	int EncryptTextOrNumbers;
// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CMyRSADemoEdit)
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMyRSADemoEdit();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CMyRSADemoEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMyPaste();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.




/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRSADemo 
class CDlgRSADemo : public CDialog
{
	
	enum s_status  {
	s_publicKeyOnly = 1,
	s_privateKey    = 0,
	s_prime_pValid  = 2,
	s_prime_qValid  = 4,
	s_modul_NValid  = 8,
	s_key_eValid    = 16,
	s_key_dValid    = 32,
	s_InputValid    = 64,
	s_OptionsValid  = 128 };

// Konstruktion
public:
	
	CDlgRSADemo(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgRSADemo();

// Dialogfelddaten
	//{{AFX_DATA(CDlgRSADemo)
	enum { IDD = IDD_RSA_DEMO };
	CStatic	m_RSA_mode_factorisation;
	CStatic	m_RSA_caption_prime_q;
	CStatic	m_RSA_caption_prime_p;
	CButton	m_frame_rsa_mode;
	CButton	m_GeneratePrimes;
	CButton	m_ButtonOptionen;
	CButton	m_ButtonEncrypt;
	CButton	m_ButtonDecrypt;
	CEdit	m_control_edit_p;
	CString	m_edit_p;
	CEdit	m_control_edit_q;
	CString	m_edit_q;
	CEdit	m_control_edit_N;
	CString	m_edit_N;
	CString	m_edit_phi_of_N;
	CEdit	m_control_edit_e;
	CString	m_edit_e;
	CString	m_edit_d;
	CMyRSADemoEdit	m_control_RSA_input;
	CEdit	m_control_edit_RSA_step_1;
	CEdit	m_control_edit_RSA_step_2;
	CEdit	m_control_edit_RSA_step_3;
	CString	m_edit_RSA_input;
	CString	m_edit_RSA_step_1;
	CString	m_edit_RSA_step_2;
	CString	m_edit_RSA_step_3;
	CString	m_Header_RSA_input;
	CString	m_Header_RSA_step_1;
	CString	m_Header_RSA_step_2;
	CString	m_Header_RSA_step_3;
	int	m_EncryptTextOrNumbers;
	int	m_RSAPublicKeyOnly;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgRSADemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgRSADemo)
	afx_msg void OnButtonGeneratePrimes();
	afx_msg void OnButtonUpdateRSAParameter();
	afx_msg void OnButtonOptions();
	afx_msg void OnButtonEncrypt();
	afx_msg void OnButtonDecrypt();

	virtual void OnEndDialog();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnUpdatePrimeP();
	afx_msg void OnUpdatePrimeQ();
	afx_msg void OnUpdateModulN();
	afx_msg void OnUpdatePublicKeyE();
	afx_msg void OnUpdateRSAInput();

	afx_msg void OnRadioRSAText();
	afx_msg void OnRadioRSANumbers();
	afx_msg void OnRadioRSAComplete();
	afx_msg void OnRadioRSAPublicKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL CheckIfNumberStream();
	CDlgPrimesGeneratorDemo *DlgRSAPrimes;
	CDlgFactorisationDemo	*DlgFactorisation;
	CDlgOptionsRSADemo		*DlgOptions;
	CRSADemo                *RSA;
	long					 m_RSAKeyStatus;

	PreCheckNumExpression( CEdit &editCtrl, CString &editStr, const char *expr );
	void ButtonManagement();
	void InitPublicRSAParameter();
	void InitPrivateRSAParameter();
	BOOL CheckIntegerInput( CString &NumStr, CEdit &EditCtrl );
	int  CheckInversion();
	void MessageIntegerRSAError( CEdit &EditCtrl, int id_IDS, BOOL select );

	void EncryptNumbers();
	void DecryptNumbers();

	BOOL CheckRSAParameter();
	BOOL ReSegmentation( int mode );
	void Segmentation  ( int mode );
	void SetDlgOptions();
	BOOL SkipWS();
	void HeadingDecryption(BOOL encryptText);
	void HeadingEncryption(BOOL decryptText);
	void RequestForInput( BOOL clearInput = FALSE );
	void SetHeadLine( CString &mHeader, int IDS_STRING_ID, int base = 0, int BlockLength = 0 );	
	int GetBase();

	bool KeyStatusPublicKeyOnly() { return (s_publicKeyOnly == (m_RSAKeyStatus & s_publicKeyOnly) ); }
	bool KeyStatusPrivateKey()    { return !(s_publicKeyOnly == (m_RSAKeyStatus & s_publicKeyOnly) ); }
	bool KeyStatusPrimePValid()   { return (s_prime_pValid == (m_RSAKeyStatus & s_prime_pValid) ); }
	bool KeyStatusPrimeQValid()   { return (s_prime_qValid == (m_RSAKeyStatus & s_prime_qValid) ); }
	bool KeyStatusModulNValid()   { return (s_modul_NValid == (m_RSAKeyStatus & s_modul_NValid) ); }
	bool KeyStatusKeyEValid()     { return (s_key_eValid   == (m_RSAKeyStatus & s_key_eValid) ); }
	bool KeyStatusKeyDValid()     { return (s_key_dValid   == (m_RSAKeyStatus & s_key_dValid) ); }
	bool KeyStatusInputValid()    { return (s_InputValid   == (m_RSAKeyStatus & s_InputValid) ); }
	bool KeyStatusOptionsValid()  { return (s_OptionsValid == (m_RSAKeyStatus & s_OptionsValid) ); }

	void SetKeyStatus( const long Status, bool value )
	{ m_RSAKeyStatus = (value) ? m_RSAKeyStatus | Status : m_RSAKeyStatus & (Status^0xFFFF); }
	void SetStatusPublicKeyOnly(bool value) { SetKeyStatus( s_publicKeyOnly, value); }	
	void SetStatusPrivateKey(bool value)    { SetKeyStatus( s_publicKeyOnly, !value); }
	void SetStatusPrimePValid(bool value)   { SetKeyStatus( s_prime_pValid, value); }
	void SetStatusPrimeQValid(bool value)   { SetKeyStatus( s_prime_qValid, value); }
	void SetStatusModulNValid(bool value)   { SetKeyStatus( s_modul_NValid, value); }
	void SetStatusKeyEValid(bool value)     { SetKeyStatus( s_key_eValid, value); }
	void SetStatusKeyDValid(bool value)     { SetKeyStatus( s_key_dValid, value); }
	void SetStatusInputValid(bool value)    { SetKeyStatus( s_InputValid, value); }
	void SetStatusOptionsValid(bool value)  { SetKeyStatus( s_OptionsValid, value); }
};



#endif // AFX_RSA_MIT_KLEINENPZ_H__42495664_FB3E_11D4_BEF2_0006291976BD__INCLUDED_
