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

// DlgAutomatedPermAnalysis.cpp : implementation file
//

#include "stdafx.h"
#include "DlgAutomatedPermAnalysis.h"
#include "automated_permanalysis.h"
#include "DlgPermKey.h"
#include "DialogeMessage.h"
#include "KeyRepository.h"
#include "DlgKeyPermutation.h"

#include "CrypToolView.h"
#include "ScintillaWnd.h"
#include "ScintillaDoc.h"
#include "ScintillaView.h"
#include "HexEditCtrlView.h"
#include "FileTools.h"
#include "CrypToolTools.h"
#include "DlgTextOptions.h"


#define BLOCK_SIZE 1024

// CDlgAutomatedPermAnalysis dialog

IMPLEMENT_DYNAMIC(CDlgAutomatedPermAnalysis, CDialog)

CDlgAutomatedPermAnalysis::CDlgAutomatedPermAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAutomatedPermAnalysis::IDD, pParent)
	, m_chk_inRowbyRow(1)
	, m_chk_permRowbyRow(1)
	, m_chk_outRowbyRow(1)
	, m_chk_inColbyCol(1)
	, m_chk_permColbyCol(1)
	, m_chk_outColbyCol(1)
	, m_editRangeFrom(_T("1"))
	, m_editRangeTo(_T("100"))
	, m_DataType(0)
	, m_edTab(0)
	, s_activeDocument(0)
	, s_plaintext(0)
	, s_ciphertext(0)
	, fn_activeDocument(0)
	, fn_plaintext(0)
	, fn_ciphertext(0)
{
}

int CDlgAutomatedPermAnalysis::setSourceFilename(const char *filename, char *&fn, __int64 &sz )
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

	m_editRangeTo.Format("%I64i", (sz < MAX_PERM_LENGTH) ? sz : MAX_PERM_LENGTH );
	return 0;
}


CDlgAutomatedPermAnalysis::~CDlgAutomatedPermAnalysis()
{
	delete []fn_activeDocument;
	delete []fn_plaintext;
	delete []fn_ciphertext;
}


void CDlgAutomatedPermAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO9, m_DataType);
	DDX_Check(pDX, IDC_CHECK4,  m_chk_inRowbyRow);
	DDX_Check(pDX, IDC_CHECK13, m_chk_inColbyCol);
	DDX_Check(pDX, IDC_CHECK11, m_chk_permRowbyRow);
	DDX_Check(pDX, IDC_CHECK14, m_chk_permColbyCol);
	DDX_Check(pDX, IDC_CHECK12, m_chk_outRowbyRow);
	DDX_Check(pDX, IDC_CHECK15, m_chk_outColbyCol);
	DDX_Text(pDX, IDC_EDIT_RANGE_FROM, m_editRangeFrom);
	DDX_Text(pDX, IDC_EDIT_RANGE_TO, m_editRangeTo);
	DDX_Control(pDX, IDC_TAB1, m_TC_textspace);
	DDX_Control(pDX, IDC_BUTTON2, m_ctrlTextOptions);
	DDX_Control(pDX, IDC_FILE_SELECT, m_ctrlFileSelect);
}


BEGIN_MESSAGE_MAP(CDlgAutomatedPermAnalysis, CDialog)
	ON_BN_CLICKED(ID_BTN_BERECHNEN, &CDlgAutomatedPermAnalysis::OnBnClickedCompute)
	ON_BN_CLICKED(IDC_CHECK4, &CDlgAutomatedPermAnalysis::OnBnClickedinRowByRow)
	ON_BN_CLICKED(IDC_CHECK13, &CDlgAutomatedPermAnalysis::OnBnClickedinColByCol)
	ON_BN_CLICKED(IDC_CHECK11, &CDlgAutomatedPermAnalysis::OnBnClickedPermRowByRow)
	ON_BN_CLICKED(IDC_CHECK14, &CDlgAutomatedPermAnalysis::OnBnClickedPermColByCol)
	ON_BN_CLICKED(IDC_CHECK12, &CDlgAutomatedPermAnalysis::OnBnClickedOutRowByRow)
	ON_BN_CLICKED(IDC_CHECK15, &CDlgAutomatedPermAnalysis::OnBnClickedOutColByCol)
	ON_BN_CLICKED(IDC_RADIO9, &CDlgAutomatedPermAnalysis::OnBnClickedRadioBinary)
	ON_BN_CLICKED(IDC_RADIO14, &CDlgAutomatedPermAnalysis::OnBnClickedRadioText)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgAutomatedPermAnalysis::OnBnClickedTextOptions)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDlgAutomatedPermAnalysis::OnTcnSelchangeTabEditor)
	ON_BN_CLICKED(IDC_BUTTON70, &CDlgAutomatedPermAnalysis::OnBnClickedLoadActiveDocument)
	ON_BN_CLICKED(IDCANCEL, &CDlgAutomatedPermAnalysis::OnBnClickedClose)
	ON_CBN_SELENDOK(IDC_FILE_SELECT, &CDlgAutomatedPermAnalysis::OnCbnSelendokFileSelect)
END_MESSAGE_MAP()


void CDlgAutomatedPermAnalysis::initSCEdit()
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

// CDlgAutomatedPermAnalysis message handlers
BOOL CDlgAutomatedPermAnalysis::OnInitDialog()
{
	CDialog::OnInitDialog();

	hWndEditPlain = CreateWindowEx(WS_EX_CLIENTEDGE, "Scintilla", "", 
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN, 21, 86, 438, 260, *this, NULL, NULL, NULL);
	hWndEditCipher = CreateWindowEx(WS_EX_CLIENTEDGE, "Scintilla", "", 
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN, 21, 86, 438, 260, *this, NULL, NULL, NULL);

	// avoid Scintilla margins to the left of the text window (make them disappear)
	FromHandle(hWndEditPlain)->SendMessage(SCI_SETMARGINWIDTHN, 0, 0);
	FromHandle(hWndEditPlain)->SendMessage(SCI_SETMARGINWIDTHN, 1, 0);
	FromHandle(hWndEditPlain)->SendMessage(SCI_SETMARGINWIDTHN, 2, 0);
	FromHandle(hWndEditCipher)->SendMessage(SCI_SETMARGINWIDTHN, 0, 0);
	FromHandle(hWndEditCipher)->SendMessage(SCI_SETMARGINWIDTHN, 1, 0);
	FromHandle(hWndEditCipher)->SendMessage(SCI_SETMARGINWIDTHN, 2, 0);

	::ShowWindow(hWndEditCipher, SW_HIDE);


// Registry Access ....
	UpdateData();
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "PermutationAnalysis") == ERROR_SUCCESS)
	{
		unsigned long ul_inRowbyRow, ul_permRowbyRow, ul_outRowbyRow, ul_inColbyCol, ul_permColbyCol, ul_outColbyCol;
		char numStr[64]; 
		unsigned long l = 63;
		CT_READ_REGISTRY_DEFAULT(ul_inRowbyRow,   "inRowbyRow",   1);
		CT_READ_REGISTRY_DEFAULT(ul_permRowbyRow, "permRowbyRow", 1);
		CT_READ_REGISTRY_DEFAULT(ul_outRowbyRow,  "outRowbyRow",  1);
		CT_READ_REGISTRY_DEFAULT(ul_inColbyCol,   "inColbyCol",   1);
		CT_READ_REGISTRY_DEFAULT(ul_permColbyCol, "permColbyCol", 1);
		CT_READ_REGISTRY_DEFAULT(ul_outColbyCol,  "outColbyCol",  1);
		CT_READ_REGISTRY_DEFAULT(numStr, "EditRangeFrom", "1", l); m_editRangeFrom = numStr;
		CT_READ_REGISTRY_DEFAULT(numStr,   "EditRangeTo", "100", l);  m_editRangeTo   = numStr;
		CT_READ_REGISTRY_DEFAULT(l, "DataType", 0); m_DataType = 0;

		m_chk_inRowbyRow   = ul_inRowbyRow;   m_chk_inColbyCol   = ul_inColbyCol;
		m_chk_outRowbyRow  = ul_outRowbyRow;  m_chk_outColbyCol  = ul_outColbyCol;
		m_chk_permRowbyRow = ul_permRowbyRow; m_chk_permColbyCol = ul_permColbyCol;
		CT_CLOSE_REGISTRY();
	}

	UpdateData(FALSE);

	m_ctrlTextOptions.EnableWindow((BOOL)m_DataType);

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

	CString str;
	str.LoadString(IDS_SELECT_DOCUMENT);
	m_ctrlFileSelect.AddString(str);

	m_sel_tab1 = m_sel_tab2 = 0;
	deque<void*>::iterator it = theApp.m_fileList.begin();
	while ( it != theApp.m_fileList.end() )
	{
		CCryptDoc *pDoc = (CCryptDoc*)*it;
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

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgAutomatedPermAnalysis::OpenFile(const char *fileName) 
{
	UpdateData(true);

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

	UpdateData(false);
}

void CDlgAutomatedPermAnalysis::SaveFile() 
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

////////////////////////////////////////////////////////////////////////
void str_permutation( permkey *pk, CString &str )
{
	int i;
	char num[20];
	str = _T("");
	for (i=1; i<pk->permSize; i++)
	{
		_itoa(pk->permKey[i], num, 10);
		str += num;
		str += _T(", ");
	}
	_itoa(pk->permKey[i], num, 10);
	str += num;
}

#define PARAM_TOKEN "PARAMETER: "


bool copy_perm_key::copy_key(long ndx)
{
	permkey *p = p_key;
	while ( ndx && p ) 
	{
		p = p->next;
		ndx--;
	}
	if ( !p )
		return false;

	CString str, strKey;
	str_permutation(p, str);
	
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PERMUTATION,pc_str,STR_LAENGE_STRING_TABLE);
	strKey.Format("%s %s%s%i,%i,%i,%i,%i,%i", 
		str, PARAM_TOKEN, (m_dataType) ? TEXT_TOKEN : BINARY_TOKEN, p->dirPlain, p->dirPerm, p->dirCipher, 0, 0, 0);
	CopyKey ( pc_str, strKey );

	return true;
}

void CDlgAutomatedPermAnalysis::OnBnClickedCompute()
{
	UpdateData();

	int tmp = m_edTab;
	m_edTab = 0; SaveFile();
	m_edTab = 1; SaveFile();
	m_edTab = tmp;

	automated_permanalysis analysis;
	int id_error;

	if ( (id_error = analysis.setFilenames( fn_plaintext,  fn_ciphertext, m_DataType)) )
	{
		Message(id_error, MB_ICONSTOP);
		return;
	}

	int lowerLimit, upperLimit;
	int inDir = col_dir, permDir = col_dir, outDir = col_dir;

	UpdateData();
	lowerLimit = atoi((char*)m_editRangeFrom.GetBuffer());
	if ( !lowerLimit )
	{
		lowerLimit = 1;
		m_editRangeFrom.Format(_T("%d"), lowerLimit);
	}
	upperLimit = atoi((char*)m_editRangeTo.GetBuffer());
	if ( !upperLimit )
	{
		upperLimit = analysis.get_size();
	}
	if ( upperLimit > MAX_PERM_LENGTH )
		upperLimit == MAX_PERM_LENGTH;
	m_editRangeTo.Format(_T("%d"), upperLimit);

	UpdateData(FALSE);

	if (m_chk_inRowbyRow)   inDir   = (m_chk_inColbyCol)   ? both_dir : row_dir;
	if (m_chk_permRowbyRow) permDir = (m_chk_permColbyCol) ? both_dir : row_dir;
	if (m_chk_outRowbyRow)  outDir  = (m_chk_outColbyCol)  ? both_dir : row_dir;

	if ( (id_error = analysis.setAnalyseParam(lowerLimit, upperLimit, inDir, permDir, outDir)) ) 
	{
		Message(id_error, MB_ICONSTOP);
		return;
	}

	if ( analysis.iterate_key_param() )
	{
		CDlgKeyList dlgKeyList;
		dlgKeyList.m_keyList.append_hl( IDS_HEADERTEXT_KEY, 200 );
		dlgKeyList.m_keyList.append_hl( IDS_HEADERTEXT_READIN, 90 );
		dlgKeyList.m_keyList.append_hl( IDS_HEADERTEXT_PERMUTATION, 90 );
		dlgKeyList.m_keyList.append_hl( IDS_HEADERTEXT_READOUT, 90 );

		key_list.p_key      = (permkey *)analysis.getKeyList();
		key_list.m_dataType = m_DataType;

		permkey *p_key = key_list.p_key;
		while ( p_key )
		{
			key_list_row key;
			CString str;
			str_permutation( p_key, str );
			key.push_back( str );
			str.LoadStringA( (p_key->dirPlain  == col_dir) ? IDS_IOP_COL : IDS_IOP_ROW );
			key.push_back( str );
			str.LoadStringA( (p_key->dirPerm   == col_dir) ? IDS_IOP_COL : IDS_IOP_ROW );
			key.push_back( str );
			str.LoadStringA( (p_key->dirCipher == col_dir) ? IDS_IOP_COL : IDS_IOP_ROW );
			key.push_back( str );

			dlgKeyList.m_keyList.append_key( key );
			p_key = p_key->next;
		}

		dlgKeyList.m_strHeader.LoadString( IDS_HEADER_PERMKEYLIST );
		dlgKeyList.m_strDlgTitle.LoadString( IDS_DIALOGHEADER_PERMKEY_LIST );
		dlgKeyList.set_copy_key_class( &key_list );
		dlgKeyList.DoModal();

#if 0
		Message(ID_PA_KEYFOUND, MB_ICONINFORMATION);
		CDlgPermKey dlg;
		dlg.setPermKey1(analysis.getKeyList(), m_DataType);
		dlg.DoModal();
#endif
	}
	else
	{
		Message(ID_PA_NOKEYFOUND, MB_ICONINFORMATION);
	}
}

void CDlgAutomatedPermAnalysis::check_dir(int &rowByRow, int &colByCol, int isRowByRow)
{
	UpdateData();
	if (  isRowByRow && !colByCol ) colByCol = 1;
	if ( !isRowByRow && !rowByRow ) rowByRow = 1;
	UpdateData(FALSE);
}

void CDlgAutomatedPermAnalysis::OnBnClickedinRowByRow()
{
	check_dir( m_chk_inRowbyRow, m_chk_inColbyCol, 1 );
}

void CDlgAutomatedPermAnalysis::OnBnClickedinColByCol()
{
	check_dir( m_chk_inRowbyRow, m_chk_inColbyCol, 0 );
}

void CDlgAutomatedPermAnalysis::OnBnClickedPermRowByRow()
{
	check_dir( m_chk_permRowbyRow, m_chk_permColbyCol, 1 );
}

void CDlgAutomatedPermAnalysis::OnBnClickedPermColByCol()
{
	check_dir( m_chk_permRowbyRow, m_chk_permColbyCol, 0 );
}

void CDlgAutomatedPermAnalysis::OnBnClickedOutRowByRow()
{
	check_dir( m_chk_outRowbyRow, m_chk_outColbyCol, 1 );
}

void CDlgAutomatedPermAnalysis::OnBnClickedOutColByCol()
{
	check_dir( m_chk_outRowbyRow, m_chk_outColbyCol, 0 );
}

#define CT_LEXER_LANGUAGE	"CrypTool"
#define CT_LEXER_LIB		"LexCrypTool"
#define STYLE_NONEALPHABET	"2"

void CDlgAutomatedPermAnalysis::setViewOptions()
{
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
}

void CDlgAutomatedPermAnalysis::OnBnClickedRadioText()
{
	UpdateData();
	setViewOptions();
	m_ctrlTextOptions.EnableWindow();
}

void CDlgAutomatedPermAnalysis::OnBnClickedRadioBinary()
{
	UpdateData();
	setViewOptions();
	m_ctrlTextOptions.EnableWindow(FALSE);
}

void CDlgAutomatedPermAnalysis::OnBnClickedTextOptions()
{
	theApp.TextOptions.DoModal();
	UpdateData();
	setViewOptions();
}

void CDlgAutomatedPermAnalysis::OnTcnSelchangeTabEditor(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
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
			m_ctrlFileSelect.SetCurSel(m_sel_tab2);
			if ( m_sel_tab2 )
				::SetFocus(hWndEditCipher);
			break;
		default: assert( 0 );
	};

	UpdateData();
	setViewOptions();

	*pResult = 0;
}

void CDlgAutomatedPermAnalysis::OnBnClickedLoadActiveDocument()
{
	OpenFile(fn_activeDocument);
}

void CDlgAutomatedPermAnalysis::OnBnClickedClose()
{
	UpdateData();
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "PermutationAnalysis") == ERROR_SUCCESS)
	{
		CT_WRITE_REGISTRY((unsigned long)m_chk_inRowbyRow,   "inRowbyRow");
		CT_WRITE_REGISTRY((unsigned long)m_chk_permRowbyRow, "permRowbyRow");
		CT_WRITE_REGISTRY((unsigned long)m_chk_outRowbyRow,  "outRowbyRow");
		CT_WRITE_REGISTRY((unsigned long)m_chk_inColbyCol,   "inColbyCol");
		CT_WRITE_REGISTRY((unsigned long)m_chk_permColbyCol, "permColbyCol");
		CT_WRITE_REGISTRY((unsigned long)m_chk_outColbyCol,  "outColbyCol");
		CT_WRITE_REGISTRY(               m_editRangeFrom,	 "EditRangeFrom"); 
		CT_WRITE_REGISTRY(               m_editRangeTo,		 "EditRangeTo"); 
		CT_WRITE_REGISTRY((unsigned long)m_DataType,		 "DataType");

		CT_CLOSE_REGISTRY();
	}

	UpdateData(FALSE);
	OnCancel();
}

void CDlgAutomatedPermAnalysis::OnCbnSelendokFileSelect()
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
