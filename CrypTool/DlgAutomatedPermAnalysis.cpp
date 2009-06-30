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
	, m_refTextType(0)
	, m_chk_inRowbyRow(1)
	, m_chk_permRowbyRow(1)
	, m_chk_outRowbyRow(1)
	, m_chk_inColbyCol(1)
	, m_chk_permColbyCol(1)
	, m_chk_outColbyCol(1)
	, fn_source(0)
	, fn_reference(0)
	, source_filesize(0)
	, m_editRangeFrom(_T("1"))
	, m_editRangeTo(_T("1"))
	, m_DataType(0)
{
}

int CDlgAutomatedPermAnalysis::setSourceFilename(const char *filename)
{
	if ( getFileSize(filename, source_filesize) && ( source_filesize > 0 ) )
	{
		delete []fn_source;
		fn_source = new char[strlen(filename)+1];
		strcpy(fn_source, filename);
		return 0;
	}
	return -1;
	m_editRangeTo.Format("%I64i", source_filesize);
	return 0;
}


CDlgAutomatedPermAnalysis::~CDlgAutomatedPermAnalysis()
{
	delete []fn_source;
	delete []fn_reference;
}

void CDlgAutomatedPermAnalysis::setRefCaption()
{
	UpdateData();
	CString strTmp;
	strTmp.Format( (m_refTextType) ? IDS_CIPHERTEXT : IDS_PLAINTEXT );
	m_ctrlRefernceHeader.SetWindowTextA(strTmp);

	UpdateData(FALSE);
}

void CDlgAutomatedPermAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO2, m_refTextType);
	DDX_Radio(pDX, IDC_RADIO9, m_DataType);
	DDX_Check(pDX, IDC_CHECK4,  m_chk_inRowbyRow);
	DDX_Check(pDX, IDC_CHECK13, m_chk_inColbyCol);
	DDX_Check(pDX, IDC_CHECK11, m_chk_permRowbyRow);
	DDX_Check(pDX, IDC_CHECK14, m_chk_permColbyCol);
	DDX_Check(pDX, IDC_CHECK12, m_chk_outRowbyRow);
	DDX_Check(pDX, IDC_CHECK15, m_chk_outColbyCol);
	DDX_Text(pDX, IDC_EDIT_RANGE_FROM, m_editRangeFrom);
	DDX_Text(pDX, IDC_EDIT_RANGE_TO, m_editRangeTo);
	DDX_Control(pDX, IDC_REFERENCE_HEADER, m_ctrlRefernceHeader);
}


BEGIN_MESSAGE_MAP(CDlgAutomatedPermAnalysis, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgAutomatedPermAnalysis::OnBnClickedLoadFile)
	ON_BN_CLICKED(ID_BTN_BERECHNEN, &CDlgAutomatedPermAnalysis::OnBnClickedCompute)
	ON_BN_CLICKED(IDC_CHECK4, &CDlgAutomatedPermAnalysis::OnBnClickedinRowByRow)
	ON_BN_CLICKED(IDC_CHECK13, &CDlgAutomatedPermAnalysis::OnBnClickedinColByCol)
	ON_BN_CLICKED(IDC_CHECK11, &CDlgAutomatedPermAnalysis::OnBnClickedPermRowByRow)
	ON_BN_CLICKED(IDC_CHECK14, &CDlgAutomatedPermAnalysis::OnBnClickedPermColByCol)
	ON_BN_CLICKED(IDC_CHECK12, &CDlgAutomatedPermAnalysis::OnBnClickedOutRowByRow)
	ON_BN_CLICKED(IDC_CHECK15, &CDlgAutomatedPermAnalysis::OnBnClickedOutColByCol)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgAutomatedPermAnalysis::setRefCaption)
	ON_BN_CLICKED(IDC_RADIO1, &CDlgAutomatedPermAnalysis::setRefCaption)
	ON_BN_CLICKED(IDC_RADIO9, &CDlgAutomatedPermAnalysis::OnBnClickedRadioText)
	ON_BN_CLICKED(IDC_RADIO14, &CDlgAutomatedPermAnalysis::OnBnClickedRadioBinary)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgAutomatedPermAnalysis::OnBnClickedTextOptions)
END_MESSAGE_MAP()


// CDlgAutomatedPermAnalysis message handlers

BOOL CDlgAutomatedPermAnalysis::OnInitDialog()
{
	CDialog::OnInitDialog();
	hWndEditReference = CreateWindowEx(WS_EX_CLIENTEDGE, "Scintilla", "", 
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN, 23, 155, 434, 216, *this, NULL, NULL, NULL);

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
	setRefCaption();

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
		CT_READ_REGISTRY_DEFAULT(numStr,   "EditRangeTo", "", l);  m_editRangeTo   = numStr;
		CT_READ_REGISTRY_DEFAULT(l, "DataType", 0); m_DataType = l;

		m_chk_inRowbyRow   = ul_inRowbyRow;   m_chk_inColbyCol   = ul_inColbyCol;
		m_chk_outRowbyRow  = ul_outRowbyRow;  m_chk_outColbyCol  = ul_outColbyCol;
		m_chk_permRowbyRow = ul_permRowbyRow; m_chk_permColbyCol = ul_permColbyCol;
		CT_CLOSE_REGISTRY();
	}
	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgAutomatedPermAnalysis::OpenFile(const char *fileName) 
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
	::SetFocus(hWndEditReference);
	ScinMSG(EM_EMPTYUNDOBUFFER);
	ScinMSG(SCI_SETSAVEPOINT);
	ScinMSG(SCI_GOTOPOS, 0);
}

void CDlgAutomatedPermAnalysis::SaveFile() 
{
	char name[BLOCK_SIZE];
	GetTmpName(name,"cry",".tmp");
	FILE *fp = fopen(name, "wb");
	if (fp) 
	{
		delete []fn_reference;
		fn_reference = new char[strlen(name)+1];
		strcpy(fn_reference, name);
		char data[BLOCK_SIZE + 1];
		int lengthDoc = ScinMSG(SCI_GETLENGTH);
		for (int i = 0; i < lengthDoc; i += BLOCK_SIZE) {
			int grabSize = lengthDoc - i;
			if (grabSize > BLOCK_SIZE)
				grabSize = BLOCK_SIZE;

			TEXTRANGE tr;
			tr.chrg.cpMin = i;
			tr.chrg.cpMax = i+grabSize;
			tr.lpstrText = data;
			::SendMessage(hWndEditReference, EM_GETTEXTRANGE, 0, reinterpret_cast<LPARAM>(&tr));

			fwrite(data, grabSize, 1, fp);
		}
		fclose(fp);
		ScinMSG(SCI_SETSAVEPOINT);
	}
}


void CDlgAutomatedPermAnalysis::OnBnClickedLoadFile()
{
	CFileDialog dlg(TRUE, NULL, NULL);
	if ( IDOK == dlg.DoModal() )
	{
		OpenFile(dlg.GetPathName().GetBuffer());
	}
	// TODO: Add your control notification handler code here
}

void CDlgAutomatedPermAnalysis::OnBnClickedCompute()
{
	UpdateData();
	SaveFile();

	automated_permanalysis analysis;
	int id_error;
	if ( (id_error = analysis.setFilenames( (!m_refTextType) ? fn_source : fn_reference,
											(!m_refTextType) ? fn_reference : fn_source, m_DataType, m_refTextType)) )
	{
		Message(id_error, MB_ICONSTOP);
		return;
	}

	int lowerLimit, upperLimit;
	int inDir = col_dir, permDir = col_dir, outDir = col_dir;

	lowerLimit = atoi((char*)m_editRangeFrom.GetBuffer());
	upperLimit = atoi((char*)m_editRangeTo.GetBuffer());
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
		CDlgPermKey dlg;
		dlg.setPermKey1(analysis.getKeyList());
		dlg.DoModal();
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

void CDlgAutomatedPermAnalysis::OnBnClickedRadioSourceIsCiphertext()
{
	setRefCaption();
}

void CDlgAutomatedPermAnalysis::OnBnClickedRadioSourceIsPlaintext()
{
	setRefCaption();
}

#define CT_LEXER_LANGUAGE	"CrypTool"
#define CT_LEXER_LIB		"LexCrypTool"
#define STYLE_NONEALPHABET	"2"

void CDlgAutomatedPermAnalysis::setViewOptions()
{
	if (!m_DataType) 
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
}

void CDlgAutomatedPermAnalysis::OnBnClickedRadioBinary()
{
	UpdateData();
	setViewOptions();
}

void CDlgAutomatedPermAnalysis::OnBnClickedTextOptions()
{
//	CDlgTextOptions dlg;
//	dlg.DoModal();
	theApp.TextOptions.DoModal();
	UpdateData();
	setViewOptions();
}
