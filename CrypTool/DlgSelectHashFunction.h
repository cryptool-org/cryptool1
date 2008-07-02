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


#if !defined(AFX_SELCTAHASHFUNCTION_H__F4D10A11_197E_11D6_9392_00B0D0161C45__INCLUDED_)
#define AFX_SELCTAHASHFUNCTION_H__F4D10A11_197E_11D6_9392_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelctAHashfunction.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSelectHashFunction 

class CDlgSelectHashFunction : public CDialog
{
// Konstruktion
public:
	CDlgSelectHashFunction(CWnd* pParent = NULL);   // Standardkonstruktor

	bool    m_deactivateMD4;
	bool    m_deactivateSHA2;
	int		m_selectedHashFunction;
	CString m_sHashAlg;
// Dialogfelddaten
	//{{AFX_DATA(CDlgSelectHashFunction)
	enum { IDD = IDD_SELECT_HASHFUNCTION };
	CButton	m_selectedHashFunctionMD4Ctrl;
	int		m_selectedHashFunctionMD2;
	int		m_selectedHashFunctionMD4;
	int		m_selectedHashFunctionMD5;
	int		m_selectedHashFunctionSHA;
	int		m_selectedHashFunctionSHA_1;
	int		m_selectedHashFunctionSHA_256;
	int		m_selectedHashFunctionSHA_512;
	int		m_selectedHashFunctionRIPEMD_160;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSelectHashFunction)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSelectHashFunction)
	afx_msg void OnSelectedMD2();
	afx_msg void OnSelectedMD4();
	afx_msg void OnSelectedMD5();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectSHA();
	afx_msg void OnSelectedSHA_1();
	afx_msg void OnSelectedSHA_256();
	afx_msg void OnSelectedSHA_512();
	afx_msg void OnSelectedRIPEMD_160();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SELCTAHASHFUNCTION_H__F4D10A11_197E_11D6_9392_00B0D0161C45__INCLUDED_
