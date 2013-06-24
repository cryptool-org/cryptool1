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
#include "HillAnalysis.h"

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
	, m_check_VM(1)
	, m_check_MV(1)
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
	DDX_Control(pDX, IDC_TAB1, m_TC_textspace);
	DDX_Control(pDX, IDC_FILE_SELECT, m_ctrlFileSelect);
	DDX_Check(pDX, IDC_CHECK_VM,   m_check_VM);
	DDX_Check(pDX, IDC_CHECK_MV,   m_check_MV);
}

BEGIN_MESSAGE_MAP(CDlgHillAnaylsis, CDialog)
	ON_CBN_SELCHANGE(IDC_DIM_VON, OnSelchangeDimVon)
	ON_CBN_SELCHANGE(IDC_DIM_BIS, OnSelchangeDimBis)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDlgHillAnaylsis::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDOK, &CDlgHillAnaylsis::OnBnClickedSearchKey)
	ON_BN_CLICKED(IDCANCEL, &CDlgHillAnaylsis::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgHillAnaylsis::OnBnClickedTextOptions)
	ON_CBN_SELENDOK(IDC_FILE_SELECT, &CDlgHillAnaylsis::OnCbnSelendokFileSelect)
	ON_BN_CLICKED(IDC_CHECK_VM, &CDlgHillAnaylsis::OnBnClickedCheckVM)
	ON_BN_CLICKED(IDC_CHECK_MV, &CDlgHillAnaylsis::OnBnClickedCheckMV)
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

int CDlgHillAnaylsis::setSourceFilename(const char *filename, char *&fn, __int64 &sz )
{
	if ( !filename )
	{
		delete []fn;
		fn = NULL;
		sz = 0;
		return -1;
	}
	if ( getFileSize(filename, sz) )
	{
		delete []fn;
		fn = new char[strlen(filename)+1];
		strcpy(fn, filename);
	}
	else
		return -1;

	return 0;
}

#define CT_LEXER_LANGUAGE	"CrypTool"
#define CT_LEXER_LIB		"LexCrypTool"
#define STYLE_NONEALPHABET	"2"

void CDlgHillAnaylsis::setViewOptions()
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
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN, 22, 75, 434, 266, *this, NULL, NULL, NULL);
	hWndEditCipher = CreateWindowEx(WS_EX_CLIENTEDGE, "Scintilla", "", 
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN, 22, 75, 434, 266, *this, NULL, NULL, NULL);
	::ShowWindow(hWndEditCipher, SW_HIDE);

	for (int i=1; i<=HILL_MAX_DIM_GROSS; i++)
	{
		CString cs;
		cs.Format("%d", i);
		m_DimensionVon.AddString(cs);
		m_DimensionBis.AddString(cs);
	}

	m_check_MV = m_check_VM = 1;

	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "HillAnalysis") == ERROR_SUCCESS)
	{
		unsigned long ul_MV, ul_VM, ul_dimFrom, ul_dimTo;
		CT_READ_REGISTRY_DEFAULT(ul_MV,      "try_mult_dir_matr_vec",    1);
		CT_READ_REGISTRY_DEFAULT(ul_VM,      "try_mult_dir_vec_matr",    1);
		CT_READ_REGISTRY_DEFAULT(ul_dimFrom, "dimensionFrom",            1);
		CT_READ_REGISTRY_DEFAULT(ul_dimTo,   "dimensionTo",              10);

		UpdateData();
		m_check_MV = ul_MV;
		m_check_VM = ul_VM;
		m_DimensionVon.SetCurSel(ul_dimFrom -1);
		m_DimensionBis.SetCurSel(ul_dimTo   -1);
		UpdateData(FALSE);

		CT_CLOSE_REGISTRY();
	}

	// Standartmaessig alle Dimensionen beruecksichtigen
	m_DimensionVon.SetCurSel(0);
	m_DimensionBis.SetCurSel(HILL_MAX_DIM_GROSS-1);
	von = 1;
	bis = HILL_MAX_DIM_GROSS;
	
	DWORD dwExStyle= m_TC_textspace.GetExtendedStyle();
	m_TC_textspace.SetExtendedStyle(dwExStyle | TCS_EX_FLATSEPARATORS);

	CString tabHeader = _T("");
	tabHeader.LoadString(IDS_PLAINTEXT);
	m_TC_textspace.InsertItem(0,tabHeader);
	tabHeader=_T("");
	tabHeader.LoadString(IDS_CIPHERTEXT);
	m_TC_textspace.InsertItem(1,tabHeader);
	m_TC_textspace.ShowWindow(TRUE);

	setViewOptions();

	UpdateData(TRUE);

	CString str;
	str.LoadString(IDS_SELECT_DOCUMENT);
	m_ctrlFileSelect.AddString(str);

	CCryptDoc *pDoc = 0;
	m_sel_tab1 = m_sel_tab2 = 0;
	deque<void*>::iterator it = theApp.m_fileList.begin();
	while ( it != theApp.m_fileList.end() )
	{
		pDoc = (CCryptDoc*)*it;
		str = pDoc->GetTitle();
		if ( fn_activeDocument && theApp.active == it )
		{
			CString tmpStr;
			tmpStr.LoadString(IDS_ACTIVE);
			str.Insert(0, tmpStr);
		}
		m_ctrlFileSelect.AddString(str);
		it++;
	}
	m_ctrlFileSelect.SetCurSel(m_sel_tab1);

	str.LoadString(IDS_OPEN_FILE);
	m_ctrlFileSelect.AddString(str);

	// flomar, June 2013: if there is a valid document when starting this dialog, 
	// we want to automatically load its contents into the ciphertext window
	if(pDoc) {
		// select the ciphertext tab
		m_TC_textspace.SetCurSel(1);
		// load the document into the ciphertext window-- the 'm_edTab = 1' instruction is mandatory
		// for the 'OpenFile' method to use the ciphertext window instead of the cleartext window
		m_edTab = 1;
		pDoc->UpdateContent();
		OpenFile(pDoc->ContentName);
		// hide the cleartext window, and show the ciphertext window
		::ShowWindow(hWndEditPlain,  SW_HIDE);
		::ShowWindow(hWndEditCipher, SW_SHOW);
		// select the 'active document' entry
		m_ctrlFileSelect.SetCurSel(1);
		// focus the ciphertext window
		::SetFocus(hWndEditCipher);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgHillAnaylsis::OnSelchangeDimVon() 
{
	von = m_DimensionVon.GetCurSel() + 1;
	if (von > bis)
	{
		bis = von;
		m_DimensionBis.SetCurSel(bis-1);
	}
}

void CDlgHillAnaylsis::OnSelchangeDimBis() 
{
	bis = m_DimensionBis.GetCurSel() + 1;
	if (bis < von)
	{
		von = bis;
		m_DimensionVon.SetCurSel(von-1);
	}
} 

void CDlgHillAnaylsis::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_edTab = m_TC_textspace.GetCurSel();

	switch ( m_edTab ) {
		case 0:
			::ShowWindow(hWndEditCipher, SW_HIDE);
			::ShowWindow(hWndEditPlain,  SW_SHOW);
			m_ctrlFileSelect.SetCurSel(m_sel_tab1);
			if ( m_sel_tab1 )
				::SetFocus(hWndEditPlain);
			break;
		case 1:
			::ShowWindow(hWndEditCipher, SW_SHOW);
			::ShowWindow(hWndEditPlain,  SW_HIDE);
			if ( m_sel_tab2 )
				::SetFocus(hWndEditCipher);
			break;
		default: assert( 0 );
	};

	UpdateData();
	setViewOptions();

	*pResult = 0;
}

void CDlgHillAnaylsis::OnBnClickedSearchKey()
{
	UpdateData();
	int tmp = m_edTab;
	m_edTab = 0; SaveFile();
	m_edTab = 1; SaveFile();
	m_edTab = tmp;

   __int64 fsp, fsc;
   getFileSize( fn_plaintext, fsp );
   getFileSize( fn_ciphertext, fsc );
   if ( !fsp )
   {
      CString cs1, cs2;
      cs1.LoadStringA(IDS_RSA_MKPZ_PLAINTEXT);
      cs2.LoadStringA(IDS_SIGDEMO_FILE_EMPTY);
      cs1 += ": " + cs2;
      AfxMessageBox(cs1, MB_ICONSTOP);
      return;
   }
   if ( !fsc )
   {
      CString cs1, cs2;
      cs1.LoadStringA(IDS_RSA_MKPZ_CIPHERTEXT);
      cs2.LoadStringA(IDS_SIGDEMO_FILE_EMPTY);
      cs1 += ": " + cs2;
      AfxMessageBox(cs1, MB_ICONSTOP);
      return;
   }

	CHillAnalysis ha;

	UpdateData(FALSE);
	SHOW_HOUR_GLASS
	long not_found = 1;
	CString err_str = _T(""); 

	if ( not_found && m_check_VM ) {
		ha.init( fn_plaintext, fn_ciphertext, von, bis, 1 );
		not_found = ha.analyze( err_str );
	}
	if ( not_found && m_check_MV ) {
		ha.init( fn_plaintext, fn_ciphertext, von, bis, 0 );
		not_found = ha.analyze( err_str );
	}
	HIDE_HOUR_GLASS
	if ( not_found )
	{
		AfxMessageBox(err_str.GetBuffer(0), MB_ICONSTOP);		
	}
}

void CDlgHillAnaylsis::OnBnClickedCancel()
{
	UpdateData();
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "HillAnalysis") == ERROR_SUCCESS)
	{
		CT_WRITE_REGISTRY((unsigned long)m_check_MV,    "try_mult_dir_matr_vec");
		CT_WRITE_REGISTRY((unsigned long)m_check_VM,    "try_mult_dir_vec_matr");
		CT_WRITE_REGISTRY((unsigned long)m_DimensionVon.GetCurSel() + 1, "dimensionFrom");
		CT_WRITE_REGISTRY((unsigned long)m_DimensionBis.GetCurSel() + 1, "dimensionTo");
		CT_CLOSE_REGISTRY();
	}
	UpdateData(FALSE);

	OnCancel();
}

void CDlgHillAnaylsis::OnBnClickedTextOptions()
{
	theApp.TextOptions.DoModal();
	UpdateData();
	setViewOptions();
}

void CDlgHillAnaylsis::OnCbnSelendokFileSelect()
{
	long sel = m_ctrlFileSelect.GetCurSel();
	switch (m_edTab) { 
		case 0: m_sel_tab1 = sel; break;
		case 1: m_sel_tab2 = sel; break;
		default: break;
	}

	if ( !sel )
	{
		UpdateData(false);
		ScinMSG(SCI_CLEARALL);
		ScinMSG(EM_EMPTYUNDOBUFFER);
		ScinMSG(SCI_SETSAVEPOINT);
		ScinMSG(SCI_CANCEL);
		ScinMSG(SCI_SETUNDOCOLLECTION, 0);
		UpdateData(true);
		return;
	}
	if ( sel == m_ctrlFileSelect.GetCount() -1 )
	{
		CFileDialog dlg(TRUE, NULL, NULL);
		if ( IDOK == dlg.DoModal() )
			OpenFile(dlg.GetPathName().GetBuffer());
		return;
	}

	deque<void*>::iterator it = theApp.m_fileList.begin();
	long i;
	for (i=1; i != sel && it != theApp.m_fileList.end(); i++) 
		it++;
	
	assert(i==sel);

	CCryptDoc *pDoc = (CCryptDoc*)*it;
	pDoc->UpdateContent();
	OpenFile(pDoc->ContentName);
}

void CDlgHillAnaylsis::OnBnClickedCheckVM()
{
	UpdateData();
	if ( !m_check_VM && !m_check_MV ) m_check_MV = 1; 
	UpdateData(FALSE);
}

void CDlgHillAnaylsis::OnBnClickedCheckMV()
{
	UpdateData();
	if ( !m_check_MV && !m_check_VM ) m_check_VM = 1; 
	UpdateData(FALSE);
}
