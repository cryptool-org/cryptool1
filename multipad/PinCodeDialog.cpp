//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// PinCodeDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "PinCodeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPinCodeDialog 


CPinCodeDialog::CPinCodeDialog(int modus, CString keyinfo, CWnd* pParent /*=NULL*/)
	: CDialog(CPinCodeDialog::IDD, pParent)
{
	UserKeyId = keyinfo;
	Modus = modus;

	//{{AFX_DATA_INIT(CPinCodeDialog)
	m_PinCode = _T("");
	m_InfoBox = _T("");
	m_ModusInfoBox = _T("");
	//}}AFX_DATA_INIT
}


void CPinCodeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPinCodeDialog)
	DDX_Control(pDX, IDC_EDIT2, m_InfoBoxCtrl);
	DDX_Control(pDX, IDC_EDIT3, m_ModusInfoBoxCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_PinEditControl);
	DDX_Text(pDX, IDC_EDIT1, m_PinCode);
	DDX_Text(pDX, IDC_EDIT2, m_InfoBox);
	DDX_Text(pDX, IDC_EDIT3, m_ModusInfoBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPinCodeDialog, CDialog)
	//{{AFX_MSG_MAP(CPinCodeDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CPinCodeDialog 

int CPinCodeDialog::DoModal() 
{
	// TODO: Speziellen Code hier einf�gen und/oder Basisklasse aufrufen
	
	return CDialog::DoModal();
} 

BOOL CPinCodeDialog::OnInitDialog() 
//InitInstance
{
	CDialog::OnInitDialog();
	
	// TODO: Zus�tzliche Initialisierung hier einf�gen

	LOGFONT LogFont;
	LONG defaultFontWeight;
	CFont *defaultFont = m_InfoBoxCtrl.GetFont();
	defaultFont->GetLogFont( &LogFont ); // Default Systemschrift ermitteln
	defaultFontWeight = LogFont.lfWeight; // Default Wert sichern
	LogFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	m_Font.CreateFontIndirect( &LogFont ); // Font initialisieren
	m_ModusInfoBoxCtrl.SetFont(&m_Font);

	if (Modus == 0)
	{
		// Eintrag "UserKeyId"-Dateien l�schen

		LoadString(AfxGetInstanceHandle(),IDS_STRING61410,pc_str,STR_LAENGE_STRING_TABLE);
		m_ModusInfoBox = (CString) pc_str;

		LoadString(AfxGetInstanceHandle(),IDS_STRING32898,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, UserKeyId);
		m_InfoBox = (CString) pc_str1;
	}
	else
	{
		// Geheime Parameter die zu Eintrag "UserKeyId" geh�ren einsehen

		LoadString(AfxGetInstanceHandle(),IDS_STRING61409,pc_str,STR_LAENGE_STRING_TABLE);
		m_ModusInfoBox = (CString) pc_str;

		LoadString(AfxGetInstanceHandle(),IDS_STRING61408,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, UserKeyId);
		m_InfoBox = (CString) pc_str1;
	}
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

void CPinCodeDialog::OnCancel() 
{
	// TODO: Zus�tzlichen Bereinigungscode hier einf�gen
	
	CDialog::OnCancel();
}

void CPinCodeDialog::OnOK() 
{
	// TODO: Zus�tzliche Pr�fung hier einf�gen
	
	CDialog::OnOK();
}
