
// ECCDecReceiver.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgECCDecReceiver

#include "KeyFileHandling.h"

class CDlgECCDecReceiver : public CDialog
{
// Konstruktion
public:
	bool disableButtons;
	CDlgECCDecReceiver(CWnd* pParent = NULL);   // Standardkonstruktor

	CString UserKeyId;
	CString KeyType;
	CString KeyInfo;
	CString Name;
	CString Firstname;
	CString CreatTime;

	CString m_sDialogText;
	CString m_sCancelText;
	CString m_sOKText;
	BOOL	m_bHideDuration;

// Dialogfelddaten
	//{{AFX_DATA(CDlgECCDecReceiver)
	enum { IDD = IDD_ECCDECRECEIVER };
	CButton	m_OKCtrl;
	CButton	m_CancelCtrl;
	CButton	m_ShowDurationCtrl;
	CListCtrl	m_listview;
	CEdit	m_PinCodeEditctrl;
	CString	m_PinCode;
	BOOL	m_ShowDuration;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgECCDecReceiver)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementierung
protected:

	int FindRow( CString pattern);
	int m_lastSelectedRow;
	int sortBy;
	unsigned nKeylistType;

	void InitAsymKeyListBox(unsigned nLocalKeylistType);
	void UpdateRowSel(int row);
	int GetSpecifRow(UINT mask);

	CSortAsymKeyList sortedAsymKeyList;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgECCDecReceiver)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.
