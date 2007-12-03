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


#if !defined(AFX_DLGSIGNATUREATTACK_H__A1F6ED91_B4D2_11D6_9DD2_000629718A52__INCLUDED_)
#define AFX_DLGSIGNATUREATTACK_H__A1F6ED91_B4D2_11D6_9DD2_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSignatureAttack.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSignatureAttack 

class CDlgSignatureAttack : public CDialog
{
// Konstruktion
public:
	
	CDlgSignatureAttack(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSignatureAttack)
	enum { IDD = IDD_SIGNATURE_ATTACK };
	CEdit	m_control_file_harmless;
	CEdit	m_control_file_dangerous;
	CButton	m_control_compute;
	CString	m_file_harmless;
	CString	m_file_dangerous;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgSignatureAttack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSignatureAttack)
	afx_msg void OnOptions();
	afx_msg void OnBrowseOriginal();
	afx_msg void OnBrowseFake();
	afx_msg void OnCompute();
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateFileFake();
	afx_msg void OnUpdateFileOriginal();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GenerateMessageText(int Errorcode, UINT MessageBoxStyle = MB_ICONEXCLAMATION);
	void BrowseDocument(CString &);
	bool AreValidPaths();
public:
	afx_msg void OnBnClickedButtonUsedefaultmessages();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGSIGNATUREATTACK_H__A1F6ED91_B4D2_11D6_9DD2_000629718A52__INCLUDED_
