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


#if !defined(AFX_DLGHMAC_H__8CFA9814_3E86_445A_8C71_A60FD455A1CE__INCLUDED_)
#define AFX_DLGHMAC_H__8CFA9814_3E86_445A_8C71_A60FD455A1CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHMAC.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHMAC 

class CDlgHMAC : public CDialog
{
// Konstruktion
	void hash(OctetString *data, char *digest, int &len);
	void hash(CString &data, char *digest, int &len);
	CString hex_dump( const char *data, int len );
public:
	CString MacToHex(OctetString *hash);
	void String2Octets(OctetString *osTarget,const char* Source, const int Length);
	void SetMac(CString input);
	void SetOuterHash();
	CString CalculateMac(CString tmpStr);
	CString strText;

	CDlgHMAC(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgHMAC)
	enum { IDD = IDD_HMAC };
	CEdit	m_ctrl_secondkey;
	CEdit	m_ctrl_key;
	CEdit	m_mac;
	CEdit	m_text;
	int		m_alg;
	int		m_position;
	CString	m_key;
	CString	m_secondkey;
	CString	m_str_mac;
	CString m_originalMessage;
	CString m_outerHash;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgHMAC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgHMAC)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONSecondKey();
	afx_msg void OnEditText();
	afx_msg void OnEditKey();
	afx_msg void OnEditOriginalMessage();
	afx_msg void OnBUTTONFront();
	afx_msg void OnBUTTONBack();
	afx_msg void OnBUTTONBoth();
	afx_msg void OnBUTTONDouble();
	afx_msg void OnEditSecondKey();
	afx_msg void OnBUTTONHashFunction();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// this function is used for the live-update functionality of this dialog; as soon as a dialog 
	// control is ivoked that changes a variable, use this function to both re-calculate the MAC and 
	// update the user interface accordingly
	void calculateMACAndUpdateGUI();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGHMAC_H__8CFA9814_3E86_445A_8C71_A60FD455A1CE__INCLUDED_
