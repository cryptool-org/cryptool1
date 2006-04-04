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


#if !defined(AFX_HASHDEMO_H__06BADA81_9DFF_11D5_AB3E_0006291976BD__INCLUDED_)
#define AFX_HASHDEMO_H__06BADA81_9DFF_11D5_AB3E_0006291976BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Hashdemo.h : Header-Datei
//

#define MAX_LAENGE_STRTEXT 16000

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHashDemo 

class CDlgHashDemo : public CDialog
{
// Konstruktion
	CString	m_strHashDiffRE;
	CString m_strNewHashBin;
	CString m_strOrigHashBin;
	CString m_strTitle;
	OctetString m_hash, m_newHash; 
	OctetString m_dataOrig; 
	CString m_strText; // initial content of m_ctrlText;  

	// Texte für Auswahl der Hashfunktionen
	CString m_strHashFunctionMD2;
	CString m_strHashFunctionMD4;
	CString m_strHashFunctionMD5;
	CString m_strHashFunctionSHA;
	CString m_strHashFunctionSHA1;
	CString m_strHashFunctionRIPEMD160;

public:
	unsigned long loadData( const char *infile, const char *title, unsigned long filesize, unsigned long max_filesize = MAX_LAENGE_STRTEXT );
	CDlgHashDemo(CWnd* pParent = NULL);   // Standardkonstruktor
    ~CDlgHashDemo();

protected:
// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgHashDemo)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Dialogfelddaten
	//{{AFX_DATA(CDlgHashDemo)
	enum { IDD = IDD_HASH_DEMO };
	CComboBox	m_comboCtrlSelectHashFunction;
	CEdit	m_ctrlText;
	CRichEditCtrl	m_ctrlHashDiff;
	CFont   m_font;
	int		m_rb_DarstHW;
	CString	m_strOrigHash; // display original hash in hex
	CString	m_strNewHash;
	//}}AFX_DATA
	

// Implementierung
private:
	void SetRed();
	void SetHashDiff(OctetString &hash1,OctetString &hash2);
	void showDiffNewHashBin(OctetString &hash);
	void showDiffOrigHashBin(OctetString &hash);
	void ComputeHash(OctetString *data, OctetString *hashValue);

	void getNextBlock(CString &dispByte, unsigned short inByte, unsigned short numberBase, char seperator = '\0');
	void showHashBin(OctetString &hash);
	void showHashHex(OctetString &hash);
	void showHashDec(OctetString &hash);
	void showNewHashHex(OctetString &hash);
	void showNewHashDec(OctetString &hash);
	void showNewHashBin(OctetString &hash);
	

protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgHashDemo)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioBin();
	afx_msg void OnRadioDec();
	afx_msg void OnRadioHex();
	afx_msg void OnChangeEditText();
	afx_msg void OnSelendokComboSelectHashFunction();
	//}}AFX_MSG


	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_HASHDEMO_H__06BADA81_9DFF_11D5_AB3E_0006291976BD__INCLUDED_
