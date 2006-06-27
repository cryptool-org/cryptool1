#pragma once
#include "afxwin.h"


// CDlgSecretSharingParameter-Dialogfeld

class CDlgSecretSharingParameter : public CDialog
{
public:
	CString m_secret;
	CString m_participants;
	CString m_threshold;
	CString m_myPrime;
	CString m_myCoeff;
	GeneratePrimes P;

	long *setupCoeff;

	CDlgSecretSharingParameter(CWnd* pParent = NULL);   // Standardkonstruktor
	CDlgSecretSharingParameter(CString kPara, CString nPara, CString tPara, CString pPara, long* coeffPara, long limitPara, int limitParties, bool flagPara, CWnd* pParent = NULL);
	virtual ~CDlgSecretSharingParameter();
	void CheckEdit(CString &m_edit,int & sels, int & sele);

// Dialogfelddaten
	//{{AFX_DATA(CDlgSecretSharingSetup)
	enum { IDD = IDD_SECRETSHARING_PARAMETER };
	CButton m_ctrlButtonOK;
	CEdit m_ctrl_myPrime;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSecretSharingParameter)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSecretSharingParameter)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGenerateNew();
	afx_msg void OnButtonClickedOk();
	afx_msg void OnEnUpdateEditMyprime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()		

private:
	int t, oldPrime;
	long limit;
	int parties;
	bool isNew;
public:
	afx_msg void OnUpdateEditMycoeff();
};
