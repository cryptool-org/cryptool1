#if !defined(AFX_DLGDIFFIEHELLMANVISUALIZATION_H__CE0FF917_D502_11D6_A88B_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANVISUALIZATION_H__CE0FF917_D502_11D6_A88B_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanVisualization.h : Header-Datei
//

#include "DiffieHellmanParty.h"
#include "ButtonControl.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanVisualization 

class CDlgDiffieHellmanVisualization : public CDialog
{
// Konstruktion
public:
	void UpdateGUI(int);
	bool CheckInternalStatus();
	void CreateErrorMessage(DHError&);
	CDlgDiffieHellmanVisualization(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgDiffieHellmanVisualization();
	
// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanVisualization)
	enum { IDD = IDD_DIFFIEHELLMANVISUALIZATION };
	CString	m_Generator;
	CString	m_Prime;
	CString	m_SecretAlice;
	CString	m_SecretBob;
	CString	m_SharedKeyAlice;
	CString	m_SharedKeyBob;
	CString	m_SessionKeyAlice;
	CString	m_SessionKeyBob;
	CString	m_SessionKey;
	BOOL	m_bShowInfoDialogues;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanVisualization)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
private:
	BitmapButtonControl *pButtonControl;
	DiffieHellmanParty *Alice;
	DiffieHellmanParty *Bob;

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanVisualization)
	afx_msg void OnSetPublicParameters();
	afx_msg void OnSetsecrets();
	virtual BOOL OnInitDialog();
	afx_msg void OnCreatesharedkey();
	afx_msg void OnExchangesharedkeys();
	afx_msg void OnGeneratefinalkey();
	afx_msg void OnButtonalice1();
	afx_msg void OnButtonbob1();
	afx_msg void OnButtonalice2();
	afx_msg void OnButtonbob2();
	afx_msg void OnButtonalice3();
	afx_msg void OnButtonbob3();
	afx_msg void OnCheckDisablehelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANVISUALIZATION_H__CE0FF917_D502_11D6_A88B_00025532117A__INCLUDED_
