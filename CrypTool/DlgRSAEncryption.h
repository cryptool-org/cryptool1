//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
//////////////////////////////////////////////////////////////////


#ifndef AFX_RSAENC_H__9BB28A41_A60A_11D2_8881_00C04F795E28__INCLUDED_
#define AFX_RSAENC_H__9BB28A41_A60A_11D2_8881_00C04F795E28__INCLUDED_

// RsaEnc.h : Header-Datei
//
#include "KeyFileHandling.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRSAEncryption 

class CDlgRSAEncryption : public CDialog
{
// Konstruktion
public:
	bool disableButtons;
	bool encryptButtonVisible;
	CDlgRSAEncryption(CWnd* pParent = NULL);   // Standardkonstruktor

	CString Name;
	CString Firstname;
	CString CreatTime;

	CString UserKeyId; //roger???

// Dialogfelddaten
	//{{AFX_DATA(CDlgRSAEncryption)
	enum { IDD = IDD_RSA_ENCRYPTION };
	CButton	m_ctrlCancel;
	CButton	m_ctrlTime;
	CButton	m_ctrlOK;
	CListCtrl	m_listview;
	BOOL	m_ShowDuration;
	CString	m_strHeadlineSelect;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgRSAEncryption)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	int m_lastSelectedRow;
	int sortBy;
	unsigned nKeylistType;

	CString KeyType;
	CString KeyInfo;

//	CString UserKeyId; //Roger???

	void InitAsymKeyListBox(unsigned nLocalKeylistType);
	void UpdateRowSel(int row);
	int GetSpecifRow(UINT mask);

	CSortAsymKeyList sortedAsymKeyList;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgRSAEncryption)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_RSAENC_H__9BB28A41_A60A_11D2_8881_00C04F795E28__INCLUDED_
