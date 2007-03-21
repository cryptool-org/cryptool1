// DlgPasswordQualityMeter.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgPasswordQualityMeter.h"

#include "passwordqualitymeter.h"


// CDlgPasswordQualityMeter-Dialogfeld

CDlgPasswordQualityMeter::CDlgPasswordQualityMeter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPasswordQualityMeter::IDD, pParent)
{
	password = "";
	showPassword = false;

	intQualityKeePass = 0;
	intQualityMozilla = 0;
	intQualityPGP = 0;
	intQualityAverage = 0;

	stringQualityKeePass = "";
	stringQualityMozilla = "";
	stringQualityPGP = "";
	stringQualityAverage = "";
}

CDlgPasswordQualityMeter::~CDlgPasswordQualityMeter()
{
}

void CDlgPasswordQualityMeter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_PASSWORD, password);
	DDX_Check(pDX, IDC_CHECK_SHOWPASSWORD, showPassword);

	DDX_Text(pDX, IDC_QUALITY_KEEPASS, stringQualityKeePass);
	DDX_Text(pDX, IDC_QUALITY_MOZILLA, stringQualityMozilla);
	DDX_Text(pDX, IDC_QUALITY_PGP, stringQualityPGP);
	DDX_Text(pDX, IDC_QUALITY_AVERAGE, stringQualityAverage);

	DDX_Control(pDX, IDC_PROGRESS_KEEPASS, controlQualityKeePass);
	DDX_Control(pDX, IDC_PROGRESS_MOZILLA, controlQualityMozilla);
	DDX_Control(pDX, IDC_PROGRESS_PGP, controlQualityPGP);
	DDX_Control(pDX, IDC_PROGRESS_AVERAGE, controlQualityAverage);
}

BOOL CDlgPasswordQualityMeter::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	UpdateUserInterface();

	UpdateData(false);
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CDlgPasswordQualityMeter::EditPasswordChanged()
{
	UpdateData(true);


	intQualityKeePass = passwordQualityKeePass(password);
	intQualityMozilla = passwordQualityMozilla(password);
	intQualityPGP = passwordQualityPGP(password);

	intQualityAverage = (intQualityKeePass+intQualityMozilla+intQualityPGP)/3;


	UpdateUserInterface();
}

void CDlgPasswordQualityMeter::UpdateUserInterface()
{
	// first scale down quality values if necessary
	if(intQualityKeePass >= 100) intQualityKeePass = 100;
	if(intQualityKeePass < 0) intQualityKeePass = 0;
	if(intQualityMozilla >= 100) intQualityMozilla = 100;
	if(intQualityMozilla < 0) intQualityMozilla = 0;
	if(intQualityPGP >= 100) intQualityPGP = 100;
	if(intQualityPGP < 0) intQualityPGP = 0;
	if(intQualityAverage >= 100) intQualityAverage = 100;
	if(intQualityAverage < 0) intQualityAverage = 0;

	// update (string) quality display
	_itoa(intQualityKeePass, pc_str, 10);
	stringQualityKeePass = pc_str;
	stringQualityKeePass.Append(" %");
	_itoa(intQualityMozilla, pc_str, 10);
	stringQualityMozilla = pc_str;
	stringQualityMozilla.Append(" %");
	_itoa(intQualityPGP, pc_str, 10);
	stringQualityPGP = pc_str;
	stringQualityPGP.Append(" %");
	_itoa(intQualityAverage, pc_str, 10);
	stringQualityAverage = pc_str;
	stringQualityAverage.Append(" %");

	// update (progress bar) quality display
	controlQualityKeePass.SetRange(0, 100);
	controlQualityKeePass.SetPos(intQualityKeePass);
	controlQualityMozilla.SetRange(0, 100);
	controlQualityMozilla.SetPos(intQualityMozilla);
	controlQualityPGP.SetRange(0, 100);
	controlQualityPGP.SetPos(intQualityPGP);
	controlQualityAverage.SetRange(0, 100);
	controlQualityAverage.SetPos(intQualityAverage);
	

	UpdateData(false);
}

BEGIN_MESSAGE_MAP(CDlgPasswordQualityMeter, CDialog)
	ON_EN_CHANGE(IDC_EDIT_PASSWORD, EditPasswordChanged)
END_MESSAGE_MAP()



// CDlgPasswordQualityMeter-Meldungshandler
