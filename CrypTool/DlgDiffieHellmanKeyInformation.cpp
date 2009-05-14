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
