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
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DialogCert.cpp: Implementierungsdatei
//
// Programmiert von Bartol Filipovic, 2000

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowCertificate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowCertificate 


CDlgShowCertificate::CDlgShowCertificate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowCertificate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShowCertificate)
	m_CertEdit = _T("");
	m_dummy = _T("");
	//}}AFX_DATA_INIT
	Cert = _T("");
}


CDlgShowCertificate::CDlgShowCertificate(CString CertIn, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowCertificate::IDD, pParent)
{
	Cert = CertIn;
}


void CDlgShowCertificate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowCertificate)
	DDX_Control(pDX, IDC_EDIT2, m_dummyCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_CertEditCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_CertEdit);
	DDX_Text(pDX, IDC_EDIT2, m_dummy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowCertificate, CDialog)
	//{{AFX_MSG_MAP(CDlgShowCertificate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowCertificate 

BOOL CDlgShowCertificate::OnInitDialog() 
{
	int i;
	CString tmp,tmp2;
	
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	tmp = Cert;

	LOGFONT LogFont;
	CFont *defaultFont = m_dummyCtrl.GetFont(); // this->GetFont() sollte auch funktionieren
	defaultFont->GetLogFont( &LogFont ); // Default Systemschrift ermitteln
	strncpy(LogFont.lfFaceName, "Courier", 32); // Auf Courier umstellen
	m_Font.CreateFontIndirect( &LogFont ); // Font initialisieren
	m_CertEditCtrl.SetFont(&m_Font);

	while(!tmp.IsEmpty()) {
		i = tmp.Find('\r');
		if(i==-1) {
			m_CertEdit += (tmp+((CString)"\r\n"));
			break;
		}
		else {
			tmp2 = tmp.Mid(0,i);
			m_CertEdit += (tmp2+((CString)"\r\n"));
			tmp = tmp.Mid(i+2);
		}
	}
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
 

void CDlgShowCertificate::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	CDialog::OnCancel();
}

void CDlgShowCertificate::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	
	CDialog::OnOK();
}
