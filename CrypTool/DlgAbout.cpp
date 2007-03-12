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
	DDX_Control(pDX, IDC_ABOUTBOX_CRYPTOOL, m_cryptoolTxt_ctrl);
	DDX_Text(pDX, IDC_EDIT_SECUDE1, strVersionSecude1);
	// DDX_Text(pDX, IDC_EDIT_SECUDE2, strVersionSecude2);
	DDX_Text(pDX, IDC_EDIT_MIRACL, strVersionMiracl);
	DDX_Text(pDX, IDC_EDIT_OPENSSL, strVersionOpenSSL);
	DDX_Text(pDX, IDC_EDIT_NTL, strVersionNTL);
	DDX_Text(pDX, IDC_EDIT_SCINTILLA, strVersionScintilla);
	DDX_Text(pDX, IDC_ABOUTBOX_CRYPTOOL, m_cryptoolTxt);
	DDX_Text(pDX, IDC_EDIT_CRYPTOVISION, strVersionCryptovision);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT_GMP, CStatInformAboutGMP);
	DDX_Control(pDX, IDC_EDIT_BUILD_INFO, m_ctrlBuildInfo);
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

#if 0
	CFont m_Font_small;
	LOGFONT LogFont_small;
	CFont *defaultFont_small = m_cryptoolTxt_ctrl.GetFont();
	defaultFont_small->GetLogFont( &LogFont_small ); // Default Systemschrift ermitteln
	LogFont_small.lfHeight = -8;
	m_Font_small.CreateFontIndirect( &LogFont_small ); // Font initialisieren
	m_ctrlBuildInfo.SetFont(&m_Font_small);
#endif

	CFont m_Font;
	LOGFONT LogFont;
	CFont *defaultFont = m_cryptoolTxt_ctrl.GetFont();
	defaultFont->GetLogFont( &LogFont ); // Default Systemschrift ermitteln
	LogFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	m_Font.CreateFontIndirect( &LogFont ); // Font initialisieren
	m_cryptoolTxt_ctrl.SetFont(&m_Font);


	// hole Information zu CrypTool-Version
	LoadString(AfxGetInstanceHandle(),IDR_MAINFRAME,pc_str,STR_LAENGE_STRING_TABLE);
	m_cryptoolTxt = pc_str;

	// Buid-Info
	CString buildDate;
	buildDate.Format("%d-%02d-%02d",YEAR, MONTH + 1, DAY);
	CString version;
	version.Format("MSC %d.%02d",_MSC_VER/100,_MSC_VER%100);
	CString StrBuildInfo;
	StrBuildInfo.Format(IDS_BUILD_INFO, buildDate, version);
	m_ctrlBuildInfo.SetWindowText(StrBuildInfo);


	// hole Bibliotheksinformationen
	determineLibraryVersions();

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
	this->CStatInformAboutGMP.SetWindowText(StrGMPWindowText);

	// CRYPTOVISION (statisch)
	this->strVersionCryptovision = "1.3.0";
	this->strVersionCryptovision.Insert(0, "cv cryptovision (tm) cv act library ");
}

