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


// DlgDiffieHellmanKeyInformation.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgDiffieHellmanKeyInformation.h"
#include "FileTools.h"

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#include <fstream.h>
#else
#include <iostream>
#include <fstream>
using namespace std;
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanKeyInformation 


CDlgDiffieHellmanKeyInformation::CDlgDiffieHellmanKeyInformation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanKeyInformation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanKeyInformation)
	m_SessionKeyAlice = _T("");
	m_SessionKeyBob = _T("");
	m_BitLengthAlice = 0;
	m_BitLengthBob = 0;
	m_Verification = _T("");
	//}}AFX_DATA_INIT
}

CDlgDiffieHellmanKeyInformation::CDlgDiffieHellmanKeyInformation(std::string akey, std::string bkey, DiffieHellmanLogFile *plog, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanKeyInformation::IDD, pParent)
{
	m_SessionKeyAlice = akey.c_str();
	m_SessionKeyBob = bkey.c_str();

	Big a = (char*)akey.c_str();
	Big b = (char*)bkey.c_str();

	this->pLogFile = plog;

	// Schlüssellängen berechnen
	// Die Funktion ceil() rundet die Werte auf einen "glatten" Wert, zumal Bitlängen der Form x.xxx
	// in der Realität nicht existieren können.
	this->m_BitLengthAlice = ceil(BitLength((CString)akey.c_str(),10));
	this->m_BitLengthBob   = ceil(BitLength((CString)bkey.c_str(),10));

	// Für a=1 oder b=1 gibt die Funktion BitLength() das falsche Ergebnis NULL zurück!
	if(a == 1) this->m_BitLengthAlice = 1;
	if(b == 1) this->m_BitLengthBob   = 1;

	// Text für Ergebnisbenachrichtigung definieren
	if( a == b ) LoadString(AfxGetInstanceHandle(), IDS_DH_KEY_VERIFICATION_YES, pc_str, STR_LAENGE_STRING_TABLE);
	else LoadString(AfxGetInstanceHandle(), IDS_DH_KEY_VERIFICATION_NO, pc_str, STR_LAENGE_STRING_TABLE);
	this->m_Verification = pc_str;
}

void CDlgDiffieHellmanKeyInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanKeyInformation)
	DDX_Text(pDX, IDC_KEY_ALICE, m_SessionKeyAlice);
	DDX_Text(pDX, IDC_KEY_BOB, m_SessionKeyBob);
	DDX_Text(pDX, IDC_BITLENGTHALICE, m_BitLengthAlice);
	DDX_Text(pDX, IDC_BITLENGTHBOB, m_BitLengthBob);
	DDX_Text(pDX, IDC_RESULT, m_Verification);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanKeyInformation, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanKeyInformation)
	ON_BN_CLICKED(IDC_SHOWLOGTEXT, OnShowlogtext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDiffieHellmanKeyInformation 

// Diese Funktion wird aufgerufen, sobald der Benutzer die Log-Datei des
// durchgeführten Schlüsselaustausch anzeigen will.
// INFORMATION: Ein Zeiger auf ein Objekt der Klasse DiffieHellmanLogFile 
// wurde bereits erzeugt, mit den während des Verfahrens verwendeten Parametern
// initialisiert und der Klasse als Parameter pLogFile übergeben.
void CDlgDiffieHellmanKeyInformation::OnShowlogtext() 
{
	std::string a = this->pLogFile->GetLogText();	

	char *filename = new char[CRYPTOOL_PATH_LENGTH];
	GetTmpName(filename, "cry", ".txt");

	ofstream Outfile;
	Outfile.open(filename, std::ios::out | std::ios::trunc);
	Outfile << this->pLogFile->GetLogText().c_str();
	Outfile.close();

	CAppDocument *NewDoc = theApp.OpenDocumentFileNoMRU(filename);

	delete filename;

	// Message-Box über erfolgreichen Verlauf der Logtexterzeugung einblenden
	LoadString(AfxGetInstanceHandle(), IDS_DH_KEY_LOGTEXT_CREATED, pc_str, STR_LAENGE_STRING_TABLE);
	MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
	
}
