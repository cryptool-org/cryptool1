// DlgSecretSharingReveal.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSecretSharingReveal.h"
#include "SecretSharingLog.h"
#include "IntegerArithmetic.h"
#include "FileTools.h"

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#include <fstream.h>
#else
#include <iostream>
#include <fstream>
using namespace std;
#endif

// CDlgSecretSharingReveal-Dialogfeld

CDlgSecretSharingReveal::CDlgSecretSharingReveal(int nNew, int gNew, bool *selected, long *paraSelected, Big *sharesSelected, SecretSharingLog *logSS, Big secret_calc, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSecretSharingReveal::IDD, pParent)
{
	m_secret = _T("");
	n = nNew;
	p = gNew;
	isSel = selected;
	para = paraSelected;
	sh = sharesSelected;
	this->logF = logSS;
	this->result = secret_calc;
}

CDlgSecretSharingReveal::~CDlgSecretSharingReveal()
{
}

void CDlgSecretSharingReveal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PARTICIPANTS, m_list_participants);
	DDX_Text(pDX, IDC_EDIT_SECRET, m_secret);
	DDX_Control(pDX, IDC_BUTTON_LOG, m_ctrl_showLog);
}


BEGIN_MESSAGE_MAP(CDlgSecretSharingReveal, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LOG, OnShowLog)
END_MESSAGE_MAP()

BOOL CDlgSecretSharingReveal::OnInitDialog()
{
	CDialog::OnInitDialog();
	int colWidth = 150;  //Spaltenbreite in Pixel
	m_list_participants.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	LoadString(AfxGetInstanceHandle(), IDS_STRING_MEMBER, pc_str, STR_LAENGE_STRING_TABLE);
	m_list_participants.InsertColumn( 0, pc_str, LVCFMT_LEFT, colWidth, 0);
	LoadString(AfxGetInstanceHandle(), IDS_STRING_VALUESS, pc_str, STR_LAENGE_STRING_TABLE);
	m_list_participants.InsertColumn( 1, pc_str, LVCFMT_LEFT, colWidth, 1);
	LoadString(AfxGetInstanceHandle(), IDS_STRING_SHARE, pc_str, STR_LAENGE_STRING_TABLE);
	m_list_participants.InsertColumn( 2, pc_str, LVCFMT_LEFT, colWidth, 2);
	m_list_participants.DeleteAllItems();
	CString pubValue, pubResult;
	int row = 0;
	for (int i = 0; i < n; i++)
	{
		if (isSel[i] == true)
		{
			CString number;
			CString entry = "";
			entry.LoadString(IDS_STRING_MEMBER2);
			number.Format(" %d", i+1);
			entry += number;
			m_list_participants.InsertItem(i, entry);
			BigToCString(sh[i], pubResult, 10);
			pubValue.Format("%d", para[i]);
			m_list_participants.SetItemText(row, 1, pubValue);
			m_list_participants.SetItemText(row, 2, pubResult);
			row++;
		}
	}
	BigToCString(result, m_secret, 10);
	UpdateData(false);
	return TRUE;  
}

// CDlgSecretSharingReveal-Meldungshandler

void CDlgSecretSharingReveal::OnShowLog()
{
	char *filename = new char[CRYPTOOL_PATH_LENGTH];
	GetTmpName(filename, "log", ".txt");

	ofstream Outfile;
	Outfile.open(filename, std::ios::out | std::ios::trunc);
	Outfile <<  this->logF->GetLogText().c_str();
	Outfile.close();

	CAppDocument *NewDoc = theApp.OpenDocumentFileNoMRU(filename);

	delete filename;

	// Message-Box über erfolgreichen Verlauf der Logtexterzeugung einblenden
	LoadString(AfxGetInstanceHandle(), IDS_DH_KEY_LOGTEXT_CREATED, pc_str, STR_LAENGE_STRING_TABLE);
	MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);

	m_ctrl_showLog.EnableWindow(false);
	UpdateData(false);
}
