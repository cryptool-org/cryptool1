/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Christian Tobias
//////////////////////////////////////////////////////////////////


#ifndef AFX_DLG_SUBSTRESULT_H__02B71C3B_0C28_11D3_8D60_00C04F795E36__INCLUDED_
#define AFX_DLG_SUBSTRESULT_H__02B71C3B_0C28_11D3_8D60_00C04F795E36__INCLUDED_

// Dlg_SubstResult.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgManualSubstAnalysis 

class CDlgManualSubstAnalysis : public CDialog
{
// Konstruktion
public:

	CBitmapButton m_bmpUndo;
	CBitmapButton m_bmpRedo;

	 CDlgManualSubstAnalysis(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgManualSubstAnalysis();

// Dialogfelddaten
	//{{AFX_DATA(CDlgManualSubstAnalysis)
	enum { IDD = IDD_MANUAL_SUBST_ANALYSIS };
	CButton	m_ButtonCopyKey;
	CString	m_edit2;
	CString	m_edit3;
	CString	m_edit27;
	CString	m_edit4;
	CString	m_edit5;
	CString	m_edit6;
	CString	m_edit7;
	CString	m_edit8;
	CString	m_edit9;
	CString	m_edit10;
	CString	m_edit11;
	CString	m_edit12;
	CString	m_edit13;
	CString	m_edit14;
	CString	m_edit15;
	CString	m_edit16;
	CString	m_edit17;
	CString	m_edit18;
	CString	m_edit19;
	CString	m_edit20;
	CString	m_edit21;
	CString	m_edit22;
	CString	m_edit23;
	CString	m_edit24;
	CString	m_edit25;
	CString	m_edit26;
	CString	m_edit1;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgManualSubstAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	bool EingabeGueltig (CString& Eingabe);
	void FeldLeer();
	void OnButton1();
	void holeDaten();
	void schreibeDaten();
	void OnChange(int Feldnummer);
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgManualSubstAnalysis)
	afx_msg void OnButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit6();
	afx_msg void OnChangeEdit7();
	afx_msg void OnChangeEdit8();
	afx_msg void OnChangeEdit9();
	afx_msg void OnChangeEdit10();
	afx_msg void OnChangeEdit11();
	afx_msg void OnChangeEdit12();
	afx_msg void OnChangeEdit13();
	afx_msg void OnChangeEdit14();
	afx_msg void OnChangeEdit15();
	afx_msg void OnChangeEdit16();
	afx_msg void OnChangeEdit17();
	afx_msg void OnChangeEdit18();
	afx_msg void OnChangeEdit19();
	afx_msg void OnChangeEdit20();
	afx_msg void OnChangeEdit21();
	afx_msg void OnChangeEdit22();
	afx_msg void OnChangeEdit23();
	afx_msg void OnChangeEdit24();
	afx_msg void OnChangeEdit25();
	afx_msg void OnChangeEdit26();
	afx_msg void OnChangeEdit27();
	afx_msg void OnUndo();
	virtual void OnOK();
	afx_msg void OnCopyKey();
	afx_msg void OnRedo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	struct KeyList
	{
		KeyList* next;
		int	 key[26];
	} *m_ptrKeyList;
	KeyList *m_ptrKeyAct;

	BOOL GetPrevKey(int* Eingabe);
	BOOL GetNextKey(int* Eingabe);
	BOOL UpdateKeyList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLG_SUBSTRESULT_H__02B71C3B_0C28_11D3_8D60_00C04F795E36__INCLUDED_
