/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


#if !defined(AFX_DLG_HOMOPHONE_H__C0728083_FD9D_11D4_80F2_000629C93170__INCLUDED_)
#define AFX_DLG_HOMOPHONE_H__C0728083_FD9D_11D4_80F2_000629C93170__INCLUDED_

#include "HomophoneEncryption.h"	// Hinzugef�gt von der Klassenansicht
#include "KeyParameterHomophone.h"	// Hinzugef�gt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define range		256
#define upper_range 4096


// Dlg_homophone.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHomophone 

class CDlgKeyHomophone : public CDialog
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
	CDlgKeyHomophone(CWnd* pParent = NULL);   // Standardkonstruktor
	CHomophoneEncryption HB;
	CKeyParameterHomophone TA;
	char c_SourceFile[128];
	CString m_AlphabetBackup;
// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHomophone)
	enum { IDD = IDD_KEY_HOMOPHONE };
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
	BOOL	m_KodiereUmlaute;
	//}}AFX_DATA
	int m_crypt;

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgKeyHomophone)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CFont m_Font;
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHomophone)
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
	CBitmapButton m_Paste;
	void Init_ListBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLG_HOMOPHONE_H__C0728083_FD9D_11D4_80F2_000629C93170__INCLUDED_
