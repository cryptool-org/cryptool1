#if !defined(AFX_DLG_HOMOPHONE_H__C0728083_FD9D_11D4_80F2_000629C93170__INCLUDED_)
#define AFX_DLG_HOMOPHONE_H__C0728083_FD9D_11D4_80F2_000629C93170__INCLUDED_

#include "Homophone_Ber.h"	// Hinzugefügt von der Klassenansicht
#include "TextAnalyse.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define range		256


// Dlg_homophone.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Dlg_homophone 

class Dlg_homophone : public CDialog
{
// Konstruktion
public:
	int GetSpecificRow(UINT mask);
	int m_lastSelectedRow;
	void UpdateSelectedRow(int newRow);
	BOOL DeactivateDecryptionButton;
	void LoadListBox();
	bool Get_crypt();
	int Display();
	Dlg_homophone(CWnd* pParent = NULL);   // Standardkonstruktor
	HomophoneEncryption HB;
	TextAnalyse TA;
	char c_SourceFile[128];
// Dialogfelddaten
	//{{AFX_DATA(Dlg_homophone)
	enum { IDD = IDD_DIALOG_HOMOPHONE };
	CEdit	m_EditNoOfHomophonesCtrl;
	CEdit	m_NoOfHomophonesCtrl;
	CButton	m_ButtonDecryption;
	CEdit	m_BitlengthCtrl;
	CEdit	m_KeyCtrl;
	CListCtrl	m_listview;
	CEdit       m_dummyCtrl;
	CString	m_KeyCStr;
	int		m_BaseHomophones;
	int		m_Bitlength;
	int		m_NoOfHomophones;
	int		m_EditNoOfHomophones;
	CString	m_RowHomophonesList;
	CString	m_HomophonesList;
	BOOL	m_EncryptFormatCharacters;
	//}}AFX_DATA
	int m_crypt;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Dlg_homophone)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CFont m_Font;
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Dlg_homophone)
	afx_msg void OnErzeugen();
	virtual BOOL OnInitDialog();
	afx_msg void OnLoadKey();
	afx_msg void OnDecrypt();
	afx_msg void OnEncrypt();
	afx_msg void OnHex();
	afx_msg void OnDecimal();
	afx_msg void OnActualizeNoOfHomophones();
	afx_msg void OnSelectList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkSelect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReturnSelect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelectEncryptFormatCharacters();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Init_ListBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_HOMOPHONE_H__C0728083_FD9D_11D4_80F2_000629C93170__INCLUDED_
