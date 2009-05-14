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

// DlgStatisticsSignatureAttack.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgStatisticsSignatureAttack.h"
#include "TimeCalculation.h"
#include "ErrorcodesForSignatureAttack.h"
#include "FileTools.h"
#include "CrypToolTools.h"
#include "HashingOperations.h"

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
	m_ExpectedSteps = _T("");
	m_ExpectedTime = _T("");
	m_HashOperationsPerformed = _T("");
	m_ExpectedSteps = _T("");
	m_ExpectedTime = _T("");
	//}}AFX_DATA_INIT
}


void CDlgStatisticsSignatureAttack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStatisticsSignatureAttack)
	DDX_Control(pDX, IDC_STATIC_DANGEROUS, m_control_dangerous);
	DDX_Control(pDX, IDC_STATIC_HARMLESS, m_control_harmless);
	DDX_Control(pDX, IDC_LIST_OF_RUNS, m_control_ListOfRuns);
	DDX_Text(pDX, IDC_EXPECTED_STEPS, m_ExpectedSteps);
	DDX_Text(pDX, IDC_EXPECTED_TIME, m_ExpectedTime);
	DDX_Text(pDX, IDC_TOTAL_STEPS, m_TotalSteps);
	DDX_Text(pDX, IDC_EFFECTIVE_TIME, m_EffectiveTime);
	DDX_Text(pDX, IDC_HASH_OPERATIONS_PERFORMED, m_HashOperationsPerformed);
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
	CString msg;
	int colWidth = 80, ii, jj;
	TimeCalculation ExpectedTC(m_ResSigAtt->GetExpectedTime()), EffectiveTC(m_ResSigAtt->GetEffectiveTime());

#ifndef _SIG_ATT_HASH_ONLY
	char strDuration[20];
	double_fmt( ExpectedTC.GetSeconds(), strDuration, 2 );
	m_ExpectedTime.Format(IDS_STRING_SIG_ATT_STA_TIME, ExpectedTC.GetYears(),
		ExpectedTC.GetDays(), ExpectedTC.GetHours(), ExpectedTC.GetMinutes(), strDuration);
#endif

#ifdef _SIG_ATT_HASH_ONLY
	_snprintf(string, sizeof(string) - 1, "Rate: %.0f Hashes / sec", m_ResSigAtt->GetExpectedTime());
	m_ExpectedTime = string;
#endif

	m_control_ListOfRuns.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	LoadString(AfxGetInstanceHandle(), IDS_STRING_SIG_ATT_RUN_NUMBER, pc_str, STR_LAENGE_STRING_TABLE);
	m_control_ListOfRuns.InsertColumn(1, pc_str, LVCFMT_CENTER, colWidth - 30, 1);
	msg.Format(IDS_STRING_SIG_ATT_STA_CYCLE);
	m_control_ListOfRuns.InsertColumn(2, msg, LVCFMT_LEFT, colWidth + 50, 2);
	msg.Format(IDS_STRING_SIG_ATT_STA_ENTRY);
	m_control_ListOfRuns.InsertColumn(3, msg, LVCFMT_LEFT, colWidth + 50, 3);
	msg.Format(IDS_STRING_SIG_ATT_STA_SUM);
	m_control_ListOfRuns.InsertColumn(4, msg, LVCFMT_LEFT, colWidth + 44, 4);	
	m_control_ListOfRuns.DeleteAllItems();
	
	for (ii = 0; ii < m_ResSigAtt->GetRuns(); ii ++)
	{
		_snprintf(string, sizeof(string) - 1, "%i", ii + 1);
		jj = m_control_ListOfRuns.InsertItem(ii, string);
		m_control_ListOfRuns.SetItemText(jj, 1, itoa_fmt((__int64)m_ResSigAtt->GetCollisionStepsOfRun(ii)));
		m_control_ListOfRuns.SetItemText(jj, 2, itoa_fmt((__int64)m_ResSigAtt->GetConfirmationStepsOfRun(ii)));
		m_control_ListOfRuns.SetItemText(jj, 3, itoa_fmt((__int64)m_ResSigAtt->GetTotalStepsOfRun(ii)));
	}

	double_fmt( EffectiveTC.GetSeconds(), strDuration, 2 );
	m_EffectiveTime.Format(IDS_STRING_SIG_ATT_STA_TIME, EffectiveTC.GetYears(),
			EffectiveTC.GetDays(), EffectiveTC.GetHours(), EffectiveTC.GetMinutes(), strDuration);

	m_ExpectedSteps = itoa_fmt(m_ResSigAtt->GetExpectedSteps());
	m_TotalSteps              = itoa_fmt((__int64)m_ResSigAtt->GetTotalSteps());
	m_HashOperationsPerformed = itoa_fmt((__int64)m_ResSigAtt->GetHashOperationsPerformed());

	msg.Format(IDS_STRING_SIG_ATT_STA_HARMLESS, m_ModifiedBytesHarmless);
	m_control_harmless.SetWindowText(msg);
	msg.Format(IDS_STRING_SIG_ATT_STA_DANGEROUS, m_ModifiedBytesDangerous);
	m_control_dangerous.SetWindowText(msg);

	UpdateData(FALSE);
	return(TRUE);
}

void CDlgStatisticsSignatureAttack::SetData(ResultsOfSignatureAttack *ResSigAtt,
									const int ModifiedBytesHarmless, const int ModifiedBytesDangerous)
{
	m_ResSigAtt					= ResSigAtt;
	m_ModifiedBytesHarmless		= ModifiedBytesHarmless;
	m_ModifiedBytesDangerous	= ModifiedBytesDangerous;
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
	CString msg, Time;
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

	HashingOperations HO(m_ResSigAtt->GetHashAlgorithmID());
	msg.Format(IDS_SIGATT_STAT_HEADER, HO.GetHashAlgorithmName());
	strlen += _snprintf(doctext + strlen, sizeof(doctext) -1, "%s\n\n", msg);
	
	msg.Format(IDS_SIGATT_STAT_ORIGINAL_FILE, m_ResSigAtt->getStrFilenameOriginal());
	strlen += _snprintf(doctext + strlen, sizeof(doctext) -1, "%s\n", msg);
	msg.Format(IDS_SIGATT_STAT_FAKE_FILE, m_ResSigAtt->getStrFilenameFake());
	strlen += _snprintf(doctext + strlen, sizeof(doctext) -1, "%s\n", msg);

	msg.Format(IDS_STRING_SIG_ATT_STA_EXPENSE);
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1, "\n%s\n\n", msg);

	msg.Format(IDS_STRING_SIG_ATT_STA_CALCTIME);

	char strDuration[20];
	double_fmt( ExpectedTC.GetSeconds(), strDuration, 2 );
	Time.Format(IDS_STRING_SIG_ATT_STA_TIME, ExpectedTC.GetYears(),
		ExpectedTC.GetDays(), ExpectedTC.GetHours(), ExpectedTC.GetMinutes(), strDuration);
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1, "%s:  %s\n", msg, Time);
	msg.Format(IDS_STRING_SIG_ATT_STA_STEPS, itoa_fmt((__int64)m_ResSigAtt->GetExpectedSteps()));
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1, "%s\n\n\n", msg);

	msg.Format(IDS_STRING_SIG_ATT_STA_EFFEXPENSE);
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1, "%s\n\n", msg);
	msg.Format(IDS_STRING_SIG_ATT_STA_CALCTIME);
	double_fmt( EffectiveTC.GetSeconds(), strDuration, 2 );
	Time.Format(IDS_STRING_SIG_ATT_STA_TIME, EffectiveTC.GetYears(),
		EffectiveTC.GetDays(), EffectiveTC.GetHours(), EffectiveTC.GetMinutes(), strDuration);
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1, "%s:  %s\n", msg, Time);
	msg.Format(IDS_STRING_SIG_ATT_STA_STEPS, itoa_fmt((__int64)m_ResSigAtt->GetTotalSteps()));
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1, "%s\n",msg);
	msg.Format(IDS_STRING_SIG_ATT_STA_PERFORMED, itoa_fmt((__int64)m_ResSigAtt->GetHashOperationsPerformed()));
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1, "%s\n\n", msg);
	msg.Format(IDS_STRING_SIG_ATT_STA_TITLE);
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1, "%s", msg);

	for (ii = 0; ii < m_ResSigAtt->GetRuns(); ii ++)
	{
		strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1,
			"   %.2i      %22s     %25s     %20s\n",
			ii + 1,
			itoa_fmt((__int64)m_ResSigAtt->GetCollisionStepsOfRun(ii)),
			itoa_fmt((__int64)m_ResSigAtt->GetConfirmationStepsOfRun(ii)),
			itoa_fmt((__int64)m_ResSigAtt->GetTotalStepsOfRun(ii)));
	}

	msg.Format(IDS_STRING_SIG_ATT_STA_ADDEDBYTES);
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1, "\n\n\n%s\n\n", msg);
	msg.Format(IDS_STRING_SIG_ATT_STA_HARMLESS, m_ModifiedBytesHarmless);
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1, "%s\n", msg);
	msg.Format(IDS_STRING_SIG_ATT_STA_DANGEROUS, m_ModifiedBytesDangerous);
	strlen += _snprintf(doctext + strlen, sizeof(doctext) - 1, "%s", msg);

	StatisticsFile.write(doctext, strlen);
	StatisticsFile.close();
	Statistics = theApp.OpenDocumentFileNoMRU(outfile);

	msg.Format(IDS_STRING_SIG_ATT_STA_DOCTITLE);
	_snprintf(doctitle, sizeof(doctitle) - 1, "%s", msg);
	Statistics->SetTitle(doctitle);
	HIDE_HOUR_GLASS
}

bool CDlgStatisticsSignatureAttack::GetPrintStatistics() const
{
	return m_PrintStatistics;
}
