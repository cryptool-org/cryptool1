// DlgStatisticsSignatureAttack.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgStatisticsSignatureAttack.h"
#include "TimeCalculation.h"
#include "ErrorcodesForSignatureAttack.h"
#include "FileTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgStatisticsSignatureAttack 

CDlgStatisticsSignatureAttack::CDlgStatisticsSignatureAttack(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStatisticsSignatureAttack::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStatisticsSignatureAttack)
	m_HashOperationsPerformed = _T("");
	m_ExpectedSteps = _T("");
	m_ExpectedTime = _T("");
	m_ExpectedSteps = _T("");
	m_ExpectedTime = _T("");
	//}}AFX_DATA_INIT
}


void CDlgStatisticsSignatureAttack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStatisticsSignatureAttack)
	DDX_Control(pDX, IDC_LIST_OF_RUNS, m_control_ListOfRuns);
	DDX_Text(pDX, IDC_HASH_OPERATIONS_PERFORMED, m_HashOperationsPerformed);
	DDX_Text(pDX, IDC_EXPECTED_STEPS, m_ExpectedSteps);
	DDX_Text(pDX, IDC_EXPECTED_TIME, m_ExpectedTime);
	DDX_Text(pDX, IDC_TOTAL_STEPS, m_TotalSteps);
	DDX_Text(pDX, IDC_EFFECTIVE_TIME, m_EffectiveTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStatisticsSignatureAttack, CDialog)
	//{{AFX_MSG_MAP(CDlgStatisticsSignatureAttack)
	ON_BN_CLICKED(IDOK, OnPrintStatistics)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgStatisticsSignatureAttack 

BOOL CDlgStatisticsSignatureAttack::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_PrintStatistics = false;

	char string[1024];
	int colWidth = 80, ii, jj;
	TimeCalculation ExpectedTC(m_ResSigAtt->GetExpectedTime()), EffectiveTC(m_ResSigAtt->GetEffectiveTime());

#ifndef _SIG_ATT_HASH_ONLY

	_snprintf(string, sizeof(string) - 1, "%I64i Jahre, %i Tage, %i Stunden, %i Minuten und %.2f Sekunden",
		ExpectedTC.GetYears(), ExpectedTC.GetDays(), ExpectedTC.GetHours(),
		ExpectedTC.GetMinutes(), ExpectedTC.GetSeconds());

#endif

#ifdef _SIG_ATT_HASH_ONLY

	_snprintf(string, sizeof(string) - 1, "Rate: %.0f Hashes / sec", m_ResSigAtt->GetExpectedTime());

#endif
	
	m_ExpectedTime = string;

	_snprintf(string, sizeof(string) - 1, "%I64i", m_ResSigAtt->GetExpectedSteps());
	m_ExpectedSteps = string;
	m_control_ListOfRuns.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	LoadString(AfxGetInstanceHandle(), IDS_STRING_SIG_ATT_RUN_NUMBER, pc_str, STR_LAENGE_STRING_TABLE);
	m_control_ListOfRuns.InsertColumn(1, pc_str, LVCFMT_CENTER, colWidth - 30, 1);
	LoadString(AfxGetInstanceHandle(), IDS_STRING_SIG_ATT_STEPS, pc_str, STR_LAENGE_STRING_TABLE);
	m_control_ListOfRuns.InsertColumn(2, "Schritte bis Kollision", LVCFMT_LEFT, colWidth + 50, 2);
	LoadString(AfxGetInstanceHandle(), IDS_STRING_SIG_ATT_STEPS, pc_str, STR_LAENGE_STRING_TABLE);
	m_control_ListOfRuns.InsertColumn(3, "Überprüfung der Kollision", LVCFMT_LEFT, colWidth + 50, 3);
	LoadString(AfxGetInstanceHandle(), IDS_STRING_SIG_ATT_STEPS, pc_str, STR_LAENGE_STRING_TABLE);
	m_control_ListOfRuns.InsertColumn(4, "Gesamtschritte", LVCFMT_LEFT, colWidth + 44, 4);	
	m_control_ListOfRuns.DeleteAllItems();
	
	for (ii = 0; ii < m_ResSigAtt->GetRuns(); ii ++)
	{
		_snprintf(string, sizeof(string) - 1, "%i", ii + 1);
		jj = m_control_ListOfRuns.InsertItem(ii, string);
		_snprintf(string, sizeof(string) - 1, "%.12I64i", m_ResSigAtt->GetCollisionStepsOfRun(ii));
		m_control_ListOfRuns.SetItemText(jj, 1, string);
		_snprintf(string, sizeof(string) - 1, "%.12I64i", m_ResSigAtt->GetConfirmationStepsOfRun(ii));
		m_control_ListOfRuns.SetItemText(jj, 2, string);
		_snprintf(string, sizeof(string) - 1, "%.12I64i", m_ResSigAtt->GetTotalStepsOfRun(ii));
		m_control_ListOfRuns.SetItemText(jj, 3, string);
	}
	_snprintf(string, sizeof(string) - 1, "%I64i Jahre, %i Tage, %i Stunden, %i Minuten und %.2f Sekunden",
		EffectiveTC.GetYears(),	EffectiveTC.GetDays(), EffectiveTC.GetHours(),
		EffectiveTC.GetMinutes(), EffectiveTC.GetSeconds());
	m_EffectiveTime = string;

	_snprintf(string, sizeof(string) - 1, "%I64i", m_ResSigAtt->GetTotalSteps());
	m_TotalSteps = string;

	_snprintf(string, sizeof(string) - 1, "%I64i", m_ResSigAtt->GetHashOperationsPerformed());
	m_HashOperationsPerformed = string;

	UpdateData(FALSE);

	return(TRUE);
}

void CDlgStatisticsSignatureAttack::SetData(ResultsOfSignatureAttack *ResSigAtt)
{
	m_ResSigAtt = ResSigAtt;
}

void CDlgStatisticsSignatureAttack::OnPrintStatistics() 
{
	m_PrintStatistics = true;
	CDialog::OnOK();	
}

void CDlgStatisticsSignatureAttack::PrintStatistics()
{
	CAppDocument *Statistics;
	char doctext[2048], outfile[1024], doctitle[1024];
	int ii, strlen = 0;
	ofstream StatisticsFile;
	TimeCalculation ExpectedTC(m_ResSigAtt->GetExpectedTime()), EffectiveTC(m_ResSigAtt->GetEffectiveTime());

	SHOW_HOUR_GLASS
	
	GetTmpName(outfile, "cry", ".tmp");
	StatisticsFile.open(outfile, ios::out | ios::binary);
	if (!StatisticsFile)
	{
		//GenerateMessageText(IDS_STRING_FILE_NOT_OPEN);
		return;
	}

	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1,
		"\nVERMUTETER AUFWAND\n\n");

	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1,
		"Rechenzeit:  %I64i Jahre, %i Tage, %i Stunden, %i Minuten und %.2f Sekunden\n",
		ExpectedTC.GetYears(), ExpectedTC.GetDays(), ExpectedTC.GetHours(),
		ExpectedTC.GetMinutes(), ExpectedTC.GetSeconds());
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1,
		"Benötigte Schritte:  %I64i\n\n\n\n", m_ResSigAtt->GetExpectedSteps());
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1,
		"TATSÄCHLICH GELEISTETER AUFWAND\n\n");
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1,
		"Rechenzeit:  %I64i Jahre, %i Tage, %i Stunden, %i Minuten und %.2f Sekunden\n",
		EffectiveTC.GetYears(),	EffectiveTC.GetDays(), EffectiveTC.GetHours(),
		EffectiveTC.GetMinutes(), EffectiveTC.GetSeconds());
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1,
		"Ausgeführte Hash-Operationen: %I64i\n\n", m_ResSigAtt->GetHashOperationsPerformed());
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1,
		"RunNr.     Schritte bis Kollision     Überprüfung der Kollision     Gesamtschritte\n\n");

	for (ii = 0; ii < m_ResSigAtt->GetRuns(); ii ++)
	{
		strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1,
			"       %.2i            %.12I64i                         %.12I64i         %.12I64i\n", ii + 1,
			m_ResSigAtt->GetCollisionStepsOfRun(ii),
			m_ResSigAtt->GetConfirmationStepsOfRun(ii),
			m_ResSigAtt->GetTotalStepsOfRun(ii));
	}

	StatisticsFile.write(doctext, strlen);
	StatisticsFile.close();
	Statistics = theApp.OpenDocumentFileNoMRU(outfile);

	// Dokumenttitel für Vorlage erstellen:
	_snprintf(doctitle, sizeof(doctitle) - 1, "Statistik über den Angriff auf die digitale Signatur");
	Statistics->SetTitle(doctitle);
	
	HIDE_HOUR_GLASS
}

bool CDlgStatisticsSignatureAttack::GetPrintStatistics()
{
	return m_PrintStatistics;
}
