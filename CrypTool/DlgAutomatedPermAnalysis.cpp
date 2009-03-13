// DlgAutomatedPermAnalysis.cpp : implementation file
//

#include "stdafx.h"
#include "DlgAutomatedPermAnalysis.h"
#include "automated_permanalysis.h"


// CDlgAutomatedPermAnalysis dialog

IMPLEMENT_DYNAMIC(CDlgAutomatedPermAnalysis, CDialog)

CDlgAutomatedPermAnalysis::CDlgAutomatedPermAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAutomatedPermAnalysis::IDD, pParent)
	, rb_einlesen(2)
	, rb_permutation(2)
	, rb_auslesen(2)
	, tb_klartext(_T(""))
	, tb_geheimtext(_T(""))
	, rb_permsize(2)
	, tb_fest(_T(""))
	, tb_lowerLimit(_T(""))
	, tb_upperLimit(_T(""))
{

}

CDlgAutomatedPermAnalysis::~CDlgAutomatedPermAnalysis()
{
}

void CDlgAutomatedPermAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RB_EIN_SW, rb_einlesen);
	DDX_Radio(pDX, IDC_RB_PERM_SW, rb_permutation);
	DDX_Radio(pDX, IDC_RB_AUS_SW, rb_auslesen);
	DDX_Text(pDX, IDC_TB_KLARTEXT, tb_klartext);
	DDX_Text(pDX, IDC_TB_GEHEIMTEXT, tb_geheimtext);
	DDX_Radio(pDX, IDC_RB_FEST, rb_permsize);
	DDX_Text(pDX, IDC_TB_FEST, tb_fest);
	DDX_Text(pDX, IDC_TB_INTERVALL_MIN, tb_lowerLimit);
	DDX_Text(pDX, IDC_TB_INTERVALL_MAX, tb_upperLimit);
}


BEGIN_MESSAGE_MAP(CDlgAutomatedPermAnalysis, CDialog)
	ON_BN_CLICKED(ID_BTN_BERECHNEN, &CDlgAutomatedPermAnalysis::OnBnClickedBtnBerechnen)
	ON_BN_CLICKED(IDC_RB_FEST, &CDlgAutomatedPermAnalysis::OnBnClickedRbFest)
	ON_BN_CLICKED(ID_BTN_ABBRUCH, &CDlgAutomatedPermAnalysis::OnBnClickedBtnAbbruch)
	ON_BN_CLICKED(IDC_RB_INTERVALL, &CDlgAutomatedPermAnalysis::OnBnClickedRbIntervall)
	ON_BN_CLICKED(IDC_RB_SUCHEN, &CDlgAutomatedPermAnalysis::OnBnClickedRbSuchen)
	ON_BN_CLICKED(IDC_BTN_KLARTEXT, &CDlgAutomatedPermAnalysis::OnBnClickedBtnKlartext)
	ON_BN_CLICKED(IDC_BTN_GEHEIMTEXT, &CDlgAutomatedPermAnalysis::OnBnClickedBtnGeheimtext)
END_MESSAGE_MAP()


// CDlgAutomatedPermAnalysis message handlers

BOOL CDlgAutomatedPermAnalysis::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAutomatedPermAnalysis::OnBnClickedBtnBerechnen()
{
	UpdateData(true);
	automated_permanalysis analysis;
	int lowerLimit, upperLimit;

	if(tb_klartext == "")
	{
		MessageBoxA("Bitte geben Sie eine Klartext-Datei an!","Fehler",MB_ICONSTOP);
	}
	if(tb_geheimtext == "")
	{
		MessageBoxA("Bitte geben Sie eine Geheimtext-Datei an!","Fehler",MB_ICONSTOP);
	}

	if(rb_permsize == 0)
	{
		lowerLimit = atoi (tb_fest);
		upperLimit = lowerLimit;
	}
	
	if(rb_permsize == 1)
	{
		lowerLimit = atoi (tb_lowerLimit);
		upperLimit = atoi (tb_upperLimit);
	}
	if( upperLimit == -1)
		MessageBoxA("Es können nur positive ganze Zahlen angegeben werden!","Fehler",MB_ICONSTOP);

	if(rb_permsize == 2)
	{
		lowerLimit = 1;
		upperLimit = -1; //FileSize wird übergeben
	}

	analysis.setFilenames(tb_klartext, tb_geheimtext);
	analysis.setAnalyseParam(lowerLimit, upperLimit, rb_einlesen, rb_permutation, rb_auslesen);

	analysis.iterate_key_param();

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
	int result = dlg.DoModal();

	if(result != IDOK)
		return;

	CString filename = dlg.GetPathName();
	tb_klartext = filename;
	
	UpdateData(false);
}

void CDlgAutomatedPermAnalysis::OnBnClickedBtnGeheimtext()
{
CFileDialog dlg(TRUE, NULL, NULL);
	int result = dlg.DoModal();

	if(result != IDOK)
		return;

	CString filename = dlg.GetPathName();
	tb_geheimtext = filename;

	UpdateData(false);
}
