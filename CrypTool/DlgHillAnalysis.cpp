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
// TextEingabeHillAngriff.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgHillAnalysis.h"
#include "HillEncryption.h"
#include "CrypToolView.h"
#include "ScintillaWnd.h"
#include "ScintillaDoc.h"
#include "ScintillaView.h"
#include "HexEditCtrlView.h"
#include "FileTools.h"
#include "CrypToolTools.h"

#define BLOCK_SIZE 1024


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHillAnaylsis 


CDlgHillAnaylsis::CDlgHillAnaylsis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHillAnaylsis::IDD, pParent)
	, m_edTab(0)
	, s_activeDocument(0)
	, s_plaintext(0)
	, s_ciphertext(0)
	, fn_activeDocument(0)
	, fn_plaintext(0)
	, fn_ciphertext(0)
{
}

CDlgHillAnaylsis::~CDlgHillAnaylsis()
{
	delete []fn_activeDocument;
	delete []fn_plaintext;
	delete []fn_ciphertext;
}


void CDlgHillAnaylsis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DIM_VON, m_DimensionVon);
	DDX_Control(pDX, IDC_DIM_BIS, m_DimensionBis);
	DDX_Control(pDX, IDC_BUTTON2, m_ctrl_loadActiveDocument);
	DDX_Control(pDX, IDC_TAB1, m_TC_textspace);
}


BEGIN_MESSAGE_MAP(CDlgHillAnaylsis, CDialog)
	ON_CBN_SELCHANGE(IDC_DIM_VON, OnSelchangeDimVon)
	ON_CBN_SELCHANGE(IDC_DIM_BIS, OnSelchangeDimBis)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgHillAnaylsis::OnBnClickedButtonLoadActiveDocument)
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, &CDlgHillAnaylsis::OnBnClickedButtonOpenfile)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDlgHillAnaylsis::OnTcnSelchangeTab1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgHillAnaylsis 

void CDlgHillAnaylsis::initSCEdit()
{
	// Initialize Edit Window
	ScinMSG(SCI_SETREADONLY, (WPARAM)FALSE);
	ScinMSG(SCI_SETMODEVENTMASK, (WPARAM)SC_MOD_INSERTTEXT|SC_MOD_DELETETEXT);
	ScinMSG(SCI_SETEOLMODE, 0, 0);
	ScinMSG(SCI_MARKERDEFINE, 0, SC_MARK_CIRCLE);
	ScinMSG(SCI_SETWRAPMODE,1);
    ScinMSG(SCI_SETWRAPVISUALFLAGS,1);
	ScinMSG(SCI_SETMARGINWIDTHN, 0, 0);
	ScinMSG(SCI_SETWRAPMODE,0,0);
	ScinMSG(SCI_SETMARGINWIDTHN, 2, 0);
	ScinMSG(SCI_SETMARGINWIDTHN, 1, 0);
    ScinMSG(SCI_SETINDENTATIONGUIDES, TRUE, 0);
	ScinMSG(SCI_SETTABWIDTH,3,0);
	ScinMSG(SCI_SETINDENT,3,0);
	ScinMSG(SCI_SETCARETPERIOD,400,0);
	ScinMSG(SCI_SETMODEVENTMASK, SC_MOD_INSERTTEXT|SC_MOD_DELETETEXT, 0);
	ScinMSG(SCI_SETMARGINSENSITIVEN, 2, TRUE);
	ScinMSG(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
	ScinMSG(SCI_MARKERDEFINE, SC_MARKNUM_FOLDER, SC_MARK_PLUS);
	ScinMSG(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
	ScinMSG(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);
	ScinMSG(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
    ScinMSG(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
    ScinMSG(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
	setViewOptions();
}

void CDlgHillAnaylsis::setViewOptions()
{
#if 0
	if (m_DataType) 
	{
		CString Alphabet;
		theApp.TextOptions.getAlphabetWithOptions(Alphabet);
		ScinMSG(SCI_STYLESETFORE, atoi(STYLE_NONEALPHABET), RGB(192,192,192));
		ScinMSG(SCI_SETPROPERTY, (WPARAM)_T("cryptool.nonalphabetstyle"), (LPARAM)STYLE_NONEALPHABET);
		ScinMSG(SCI_SETPROPERTY, (WPARAM)_T("cryptool.alphabet"), (LPARAM)(LPCTSTR)Alphabet);
		ScinMSG(SCI_SETSTYLEBITS, 5, 0);
		ScinMSG(SCI_SETLEXERLANGUAGE,0,(LPARAM)CT_LEXER_LANGUAGE );
		if (SCLEX_NULL == ScinMSG(SCI_GETLEXER)) {
#ifdef BUILD_AS_EXTERNAL_LEXER
			SendMessage(SCI_LOADLEXERLIBRARY,0,(LPARAM)CT_LEXER_LIB);
			SendMessage(SCI_SETLEXERLANGUAGE,0,(LPARAM)CT_LEXER_LANGUAGE );
#endif
			if (SCLEX_NULL == ScinMSG(SCI_GETLEXER)) {
				CString msg;
				msg.Format(IDS_SCINTILLA_LEXER_ERROR,CT_LEXER_LIB);
				MessageBox(msg);
			}
		}
		ScinMSG(SCI_CLEARDOCUMENTSTYLE, 0, 0);
		ScinMSG(SCI_COLOURISE,0,(LPARAM)1); // trigger re-lexing
	} 
	else 
	{
		ScinMSG(SCI_SETVIEWEOL, TRUE, 0); // if omitted and word wrap is active only the first line of a paragraph is shown
		ScinMSG(SCI_SETLEXER, SCLEX_NULL);
		ScinMSG(SCI_CLEARDOCUMENTSTYLE, 0, 0);
	}
	ScinMSG(SCI_SETVIEWEOL, m_DataType ? 1 : 0);
#endif
}

void CDlgHillAnaylsis::OpenFile(const char *fileName) 
{
	ScinMSG(SCI_CLEARALL);
	ScinMSG(EM_EMPTYUNDOBUFFER);
	ScinMSG(SCI_SETSAVEPOINT);
	ScinMSG(SCI_CANCEL);
	ScinMSG(SCI_SETUNDOCOLLECTION, 0);

	FILE *fp = fopen(fileName, "rb");
	if (fp) {
		char data[BLOCK_SIZE];
		int lenFile = fread(data, 1, sizeof(data), fp);
		while (lenFile > 0) {
			ScinMSG(SCI_ADDTEXT, lenFile,
					   reinterpret_cast<LPARAM>(static_cast<char *>(data)));
			lenFile = fread(data, 1, sizeof(data), fp);
		}
		fclose(fp);
	} else {
		/* FIXME
		char msg[MAX_PATH + 100];
		strcpy(msg, "Could not open file \"");
		strcat(msg, fullPath);
		strcat(msg, "\".");
		::MessageBox(wMain, msg, appName, MB_OK);
		*/
	}
	ScinMSG(SCI_SETUNDOCOLLECTION, 1);
	assert(m_edTab < 2);
	::SetFocus(!( m_edTab ) ? hWndEditPlain : hWndEditCipher );
	ScinMSG(EM_EMPTYUNDOBUFFER);
	ScinMSG(SCI_SETSAVEPOINT);
	ScinMSG(SCI_GOTOPOS, 0);
}

void CDlgHillAnaylsis::SaveFile() 
{
	char name[BLOCK_SIZE];
	GetTmpName(name,"cry",".tmp");
	FILE *fp = fopen(name, "wb");
	__int64 sz;
	char *fn = 0;

	if (fp) 
	{
		fn = new char[strlen(name)+1];
		strcpy(fn, name);
		char data[BLOCK_SIZE + 1];
		sz = ScinMSG(SCI_GETLENGTH);
		for (int i = 0; i < sz; i += BLOCK_SIZE) {
			int grabSize = sz - i;
			if (grabSize > BLOCK_SIZE)
				grabSize = BLOCK_SIZE;

			TEXTRANGE tr;
			tr.chrg.cpMin = i;
			tr.chrg.cpMax = i+grabSize;
			tr.lpstrText = data;
			assert(m_edTab < 2);
			::SendMessage(!( m_edTab ) ? hWndEditPlain : hWndEditCipher, EM_GETTEXTRANGE, 0, reinterpret_cast<LPARAM>(&tr));

			fwrite(data, grabSize, 1, fp);
		}
		fclose(fp);
		ScinMSG(SCI_SETSAVEPOINT);
		if ( !m_edTab ) { delete []fn_plaintext;  fn_plaintext = fn;  s_plaintext = sz;  }
		else 	        { delete []fn_ciphertext; fn_ciphertext = fn; s_ciphertext = sz; }
	}
}




BOOL CDlgHillAnaylsis::OnInitDialog() 
{
	CDialog::OnInitDialog();

	hWndEditPlain = CreateWindowEx(WS_EX_CLIENTEDGE, "Scintilla", "", 
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN, 22, 75, 410, 300, *this, NULL, NULL, NULL);
	hWndEditCipher = CreateWindowEx(WS_EX_CLIENTEDGE, "Scintilla", "", 
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN, 22, 75, 410, 300, *this, NULL, NULL, NULL);
	::ShowWindow(hWndEditCipher, SW_HIDE);

	
	// TODO: Zusätzliche Initialisierung hier einfügen

	// Combo-Boxen fuer Bereich der Schluesselsuche initialisieren
	for (int i=1; i<=HILL_MAX_DIM_GROSS; i++)
	{
		CString cs;
		cs.Format("%d", i);
		m_DimensionVon.AddString(cs);
		m_DimensionBis.AddString(cs);
	}

	// Standartmaessig alle Dimensionen beruecksichtigen
	m_DimensionVon.SetCurSel(0);
	m_DimensionBis.SetCurSel(HILL_MAX_DIM_GROSS-1);
	von = 1;
	bis = HILL_MAX_DIM_GROSS;
	
	UpdateData(FALSE);
	DWORD dwExStyle= m_TC_textspace.GetExtendedStyle();
	m_TC_textspace.SetExtendedStyle(dwExStyle | TCS_EX_FLATSEPARATORS);

	CString tabHeader = _T("");
	tabHeader.LoadString(IDS_PLAINTEXT);
	m_TC_textspace.InsertItem(0,tabHeader);
	tabHeader=_T("");
	tabHeader.LoadString(IDS_CIPHERTEXT);
	m_TC_textspace.InsertItem(1,tabHeader);
	m_TC_textspace.ShowWindow(TRUE);

	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgHillAnaylsis::OnSelchangeDimVon() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	von = m_DimensionVon.GetCurSel() + 1;
	if (von > bis)
	{
		bis = von;
		m_DimensionBis.SetCurSel(bis-1);
	}
}

void CDlgHillAnaylsis::OnSelchangeDimBis() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	bis = m_DimensionBis.GetCurSel() + 1;
	if (bis < von)
	{
		von = bis;
		m_DimensionVon.SetCurSel(von-1);
	}
} 

void CDlgHillAnaylsis::OnBnClickedButtonLoadActiveDocument()
{
	OpenFile(fn_activeDocument);
}

void CDlgHillAnaylsis::OnBnClickedButtonOpenfile()
{
	CFileDialog dlg(TRUE, NULL, NULL);
	if ( IDOK == dlg.DoModal() )
	{
		OpenFile(dlg.GetPathName().GetBuffer());
	}
}

void CDlgHillAnaylsis::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	m_edTab = m_TC_textspace.GetCurSel();

	switch ( m_edTab ) {
		case 0:
			::ShowWindow(hWndEditCipher, SW_HIDE);
			::ShowWindow(hWndEditPlain,  SW_SHOW);
			break;
		case 1:
			::ShowWindow(hWndEditCipher, SW_SHOW);
			::ShowWindow(hWndEditPlain,  SW_HIDE);
			break;
		default: assert( 0 );
	};

	UpdateData();
	setViewOptions();

	*pResult = 0;
}
