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


#if !defined(AFX_DLGDIFFIEHELLMANSECRETINPUT_H__5F417B9F_EFB8_11D6_A8A3_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANSECRETINPUT_H__5F417B9F_EFB8_11D6_A8A3_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanSecretInput.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanSecretInput 

class CDlgDiffieHellmanSecretInput : public CDialog
{
private:
	Big m_Prime;
	std::string m_Party;
	bool m_SecretExceedsPrime;

// Konstruktion
public:
	CDlgDiffieHellmanSecretInput(CWnd* pParent = NULL);			// Standardkonstruktor
	CDlgDiffieHellmanSecretInput(std::string,Big&,CWnd* pParent = NULL);				// Zus�tzlicher Konstruktor
	CDlgDiffieHellmanSecretInput(std::string,std::string,Big&,CWnd* pParent = NULL);	// Zus�tzlicher Konstruktor
	bool SecretExceedsPrime() { return m_SecretExceedsPrime; }
// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanSecretInput)
	enum { IDD = IDD_DIFFIEHELLMAN_SECRETINPUT };
	CButton	m_CtrlOKButton;
	CButton	m_ButtonGenSec;
	CEdit	m_SecretControl;
	CString	m_Secret;
	CString	m_PartyHeader;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanSecretInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanSecretInput)
	virtual void OnOK();
	afx_msg void OnGenerateSecret();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANSECRETINPUT_H__5F417B9F_EFB8_11D6_A8A3_00025532117A__INCLUDED_
