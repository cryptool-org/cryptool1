/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// About.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgAbout.h"
#include "DlgAuthors.h"

// für NTL Bibliothek
#include "..\libNTL\include\NTL\version.h"
namespace OPENSSL {
#include "crypto.h" // clashes with secude.h
}
#include "gmp.h"

#define YEAR ((((__DATE__ [7] - '0') * 10 + (__DATE__ [8] - '0')) * 10 \
+ (__DATE__ [9] - '0')) * 10 + (__DATE__ [10] - '0'))

#define MONTH (__DATE__ [2] == 'n' ? 0 \
: __DATE__ [2] == 'b' ? 1 \
: __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 2 : 3) \
: __DATE__ [2] == 'y' ? 4 \
: __DATE__ [2] == 'n' ? 5 \
: __DATE__ [2] == 'l' ? 6 \
: __DATE__ [2] == 'g' ? 7 \
: __DATE__ [2] == 'p' ? 8 \
: __DATE__ [2] == 't' ? 9 \
: __DATE__ [2] == 'v' ? 10 : 11)

#define DAY ((__DATE__ [4] == ' ' ? 0 : __DATE__ [4] - '0') * 10 \
+ (__DATE__ [5] - '0'))


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAbout 


CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/)
: CDialog(CDlgAbout::IDD, pParent)
{
	
}

void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAbout)
	DDX_Text(pDX, IDC_EDIT_SECUDE1, strVersionSecude1);
	// DDX_Text(pDX, IDC_EDIT_SECUDE2, strVersionSecude2);
	DDX_Text(pDX, IDC_EDIT_MIRACL, strVersionMiracl);
	DDX_Text(pDX, IDC_EDIT_OPENSSL, strVersionOpenSSL);
	DDX_Text(pDX, IDC_EDIT_NTL, strVersionNTL);
	DDX_Text(pDX, IDC_EDIT_SCINTILLA, strVersionScintilla);
	DDX_Text(pDX, IDC_EDIT_CRYPTOVISION, strVersionCryptovision);
	DDX_Text(pDX, IDC_EDIT_GMP, strVersionGMP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
//{{AFX_MSG_MAP(CDlgAbout)
ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgAbout 


void CDlgAbout::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CDialog::OnLButtonDblClk(nFlags, point);
	
	CDlgAuthors klasse;
	klasse.DoModal();
	
} 

BOOL CDlgAbout::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// hole Bibliotheksinformationen
	determineLibraryVersions();

	// flomar, 01/20/2009
	// release information as well as contact information is
	// displayed in a text field now to allow copy-and-paste
	CWnd *windowReleaseInformation = GetDlgItem(IDC_EDIT_RELEASE_INFORMATION);
	CWnd *windowContactInformation = GetDlgItem(IDC_EDIT_CONTACT_INFORMATION);

	if(windowReleaseInformation) {
		CString stringReleaseInformation;
		// get CrypTool version
		LoadString(AfxGetInstanceHandle(),IDR_MAINFRAME,pc_str,STR_LAENGE_STRING_TABLE);
		stringReleaseInformation.Append(pc_str);
		stringReleaseInformation.Append("\r\n\r\n");
		// get build information
		CString buildDate;
		buildDate.Format("%d-%02d-%02d",YEAR, MONTH + 1, DAY);
		CString version;
		version.Format("MSC %d.%02d",_MSC_VER/100,_MSC_VER%100);
		CString StrBuildInfo;
		StrBuildInfo.Format(IDS_BUILD_INFO, buildDate, version);
		stringReleaseInformation.Append(StrBuildInfo);
		// display information
		windowReleaseInformation->SetWindowText(stringReleaseInformation);

	}
	if(windowContactInformation) {
		CString stringContactInformation;
		// get contact information
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ABOUT_CONTACT_INFORMATION,pc_str,STR_LAENGE_STRING_TABLE);
		stringContactInformation.Append(pc_str);
		// display information
		windowContactInformation->SetWindowText(stringContactInformation);
	} 


	// Anzeige aktualisieren
	UpdateData(false);

	// TODO: Zusätzliche Initialisierung hier einfügen
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgAbout::determineLibraryVersions()
{
	// Secude (dynamisch)
	if(theApp.SecudeStatus == 2)
	{
		// Secude Bibliothek geladen?
		int i=0;
		strcpy(pc_str,theApp.SecudeLib.aux_sprint_version(NULL));
		// nur bis zum newline
		while (pc_str[i]!=0x0d) i++;
		pc_str[i]=0;

		// Bibliotheks-Version und Firmenbezeichnung in zwei Zeilen trennen
		// *** ACHTUNG *** Trennung ist hartcodiert (s.u.)
		this->strVersionSecude1 = pc_str;
		int index = this->strVersionSecude1.Find("SECUDE ");
		this->strVersionSecude1.Delete(index, this->strVersionSecude1.GetLength() - index);
		// Only version information required
		// this->strVersionSecude1.Insert(this->strVersionSecude1.GetLength()-1, ",");
		// this->strVersionSecude2 = pc_str;
		// this->strVersionSecude2.Delete(0, index);
	}
	else
	{
		// Secude Bibliothek konnte nicht geladen werden
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SECUDE_DLL_NOT_AVAILABLE,pc_str,STR_LAENGE_STRING_TABLE);
		this->strVersionSecude1 = pc_str;
		this->strVersionSecude2 = "";
	}


	// Miracl (statisch)
	// *** TODO *** ???
	this->strVersionMiracl = "4.4.3";
	this->strVersionMiracl.Insert(0, "Miracl ");


	// OpenSSL
	this->strVersionOpenSSL = OPENSSL::SSLeay_version(SSLEAY_VERSION);

	// NTL (statisch)
	this->strVersionNTL = NTL_VERSION;
	this->strVersionNTL.Insert(0, "NTL ");


	// Scintilla
	int scv =
#include "../scintilla/version.txt"
	;
	this->strVersionScintilla.Format("%d.%d.%d",scv/100, (scv/10)%10, scv%10);
	this->strVersionScintilla.Insert(0, "Scintilla ");

	// GMP (dynamisch)
	CString StrGMPWindowText;
	StrGMPWindowText.Format("GMP %s", gmp_version);
	this->strVersionGMP = StrGMPWindowText;

	// CRYPTOVISION (statisch)
	this->strVersionCryptovision = "1.3.0";
	this->strVersionCryptovision.Insert(0, "cv cryptovision (tm) cv act library ");
}

