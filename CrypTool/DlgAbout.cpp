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
	DDX_Text(pDX, IDC_EDIT_SECUDE2, strVersionSecude2);
	DDX_Text(pDX, IDC_EDIT_MIRACL, strVersionMiracl);
	DDX_Text(pDX, IDC_EDIT_OPENSSL, strVersionOpenSSL);
	DDX_Text(pDX, IDC_EDIT_NTL, strVersionNTL);
	DDX_Text(pDX, IDC_EDIT_SCINTILLA, strVersionScintilla);
	DDX_Text(pDX, IDC_ABOUTBOX_CRYPTOOL, m_cryptoolTxt);
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
	
	// hole Bibliotheksinformationen
	this->determineLibraryVersions();

	// Anzeige aktualisieren
	UpdateData(false);

	// TODO: Zusätzliche Initialisierung hier einfügen
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgAbout::determineLibraryVersions()
{
	// Secude Bibliothek geladen?
	if(theApp.SecudeStatus == 2)
	{
		int i=0;
		strcpy(pc_str,theApp.SecudeLib.aux_sprint_version(NULL));
		while (pc_str[i]!=0x0d)
			i++;        // nur bis zum newline
		pc_str[i]=0;

		// Bibliotheks-Version und Firmenbezeichnung in zwei Zeilen trennen
		this->strVersionSecude1 = pc_str;
		int index = this->strVersionSecude1.Find("SECUDE ");
		this->strVersionSecude1.Delete(index, this->strVersionSecude1.GetLength() - index);
		this->strVersionSecude1.Insert(this->strVersionSecude1.GetLength()-1, ",");
		this->strVersionSecude2 = pc_str;
		this->strVersionSecude2.Delete(0, index);
	}
	else
	{
		// Secude Bibliothek konnte nicht geladen werden
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SECUDE_DLL_NOT_AVAILABLE,pc_str,STR_LAENGE_STRING_TABLE);
		this->strVersionSecude1 = pc_str;
		this->strVersionSecude2 = "";
	}


	// Miracl
	// *** TODO ***
	this->strVersionMiracl = "Miracl Library TODO";


	// OpenSSL
	// *** TODO ***
	this->strVersionOpenSSL = "OpenSSL Library TODO";


	// NTL
	// *** TODO ***
	this->strVersionNTL = NTL_VERSION;
	this->strVersionNTL.Insert(0, "NTL Library ");


	// Scintilla
	// *** TODO ***
	this->strVersionScintilla = "Scintilla TODO";
}

