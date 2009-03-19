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
{
}

int CDlgAutomatedPermAnalysis::setSourceFilename(const char *filename)
{
	fn_source = new char[strlen(filename)+1];
	strcpy(fn_source, filename);
	ifstream fstrm;
	fstrm.open(fn_source);
	if(!fstrm.is_open())
		return -1;
	fstrm.clear(); // Go to the beginning of the file
	fstrm.seekg(0, ios::end);
	source_filesize = fstrm.tellg();
	fstrm.close();
	m_editRangeTo.Format("%i", source_filesize);
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
	ScinMSG(SCI_SETVIEWEOL, TRUE, 0);
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
	setRefCaption();
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
	if ( (id_error = analysis.setFilenames( (m_refTextType) ? fn_source : fn_reference,
											(m_refTextType) ? fn_reference : fn_source)) )
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

#if 0
void CDlgAutomatedPermAnalysis::OnBnClickedBtnBerechnen()
{
	UpdateData(true);
	automated_permanalysis analysis;
	int id_error;
	if ( (id_error = analysis.setFilenames(tb_klartext, tb_geheimtext)) )
	{
		Message(id_error, MB_ICONSTOP);
		return;
	}
	int lowerLimit, upperLimit;

	switch (rb_permsize) {
		case 0:
			lowerLimit = atoi(tb_fest);
			upperLimit = lowerLimit;
			break;
		case 1:
			lowerLimit = atoi(tb_lowerLimit);
			upperLimit = atoi(tb_upperLimit);
			break;
		case 2:
			lowerLimit = 1;
			upperLimit = -1;
			break;
		default:
			break;
	}

	if ( (id_error = analysis.setAnalyseParam(lowerLimit, upperLimit, rb_einlesen, rb_permutation, rb_auslesen)) ) 
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

void CDlgAutomatedPermAnalysis::OnBnClickedBtnAbbruch()
{
	OnCancel();
}

void CDlgAutomatedPermAnalysis::OnBnClickedRbFest()
{	
	//Objekte Ausgrauen
	((CButton*)GetDlgItem(IDC_TB_FEST))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_LBL_FEST_INFO))->EnableWindow(true);

	//Eingrauen nicht dazugehöriger Objekte
	((CButton*)GetDlgItem(IDC_TB_INTERVALL_MIN))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_TB_INTERVALL_MAX))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_LBL_INTERVALL))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_LBL_INTERVALL_INFO))->EnableWindow(false);
}	

void CDlgAutomatedPermAnalysis::OnBnClickedRbIntervall()
{
	//Objekte Ausgrauen
	((CButton*)GetDlgItem(IDC_TB_INTERVALL_MIN))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_TB_INTERVALL_MAX))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_LBL_INTERVALL))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_LBL_INTERVALL_INFO))->EnableWindow(true);
	
	//Eingrauen nicht dazugehöriger Objekte
	((CButton*)GetDlgItem(IDC_TB_FEST))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_LBL_FEST_INFO))->EnableWindow(false);
}

void CDlgAutomatedPermAnalysis::OnBnClickedRbSuchen()
{
	//Eingrauen nicht dazugehöriger Objekte
	((CButton*)GetDlgItem(IDC_TB_INTERVALL_MIN))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_TB_INTERVALL_MAX))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_LBL_INTERVALL))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_LBL_INTERVALL_INFO))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_TB_FEST))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_LBL_FEST_INFO))->EnableWindow(false);
}

void CDlgAutomatedPermAnalysis::OnBnClickedBtnKlartext()
{
	CFileDialog dlg(TRUE, NULL, NULL);
	if (IDOK == dlg.DoModal() )
	{
		tb_klartext = dlg.GetPathName();
		UpdateData(false);
	}
}

void CDlgAutomatedPermAnalysis::OnBnClickedBtnGeheimtext()
{
	CFileDialog dlg(TRUE, NULL, NULL);
	if ( IDOK == dlg.DoModal() )
	{
		tb_geheimtext = dlg.GetPathName();
		UpdateData(false);
	}
}
#endif


void CDlgAutomatedPermAnalysis::OnBnClickedRadioSourceIsCiphertext()
{
	setRefCaption();
}

void CDlgAutomatedPermAnalysis::OnBnClickedRadioSourceIsPlaintext()
{
	setRefCaption();
}
