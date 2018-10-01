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

// DlgSecretSharingParameter.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSecretSharingOptions.h"
#include "DlgSecretSharingParameter.h"
#include ".\dlgsecretsharingparameter.h"
#include "CrypToolTools.h"

// CDlgSecretSharingParameter-Dialogfeld

CDlgSecretSharingParameter::CDlgSecretSharingParameter(CString kPara, CString nPara, CString tPara, CString pPara, long* coeffPara, long limitPara, int limitParties, bool flagPara, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSecretSharingParameter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSecretSharingParameter)
	m_secret = kPara;
	m_threshold = tPara;
	m_participants = nPara;
	m_myPrime = pPara;
	m_myCoeff = _T("");
	//}}AFX_DATA_INIT
	limit = limitPara;
	parties = limitParties;
	oldPrime = atoi(LPCSTR(pPara));
	setupCoeff = coeffPara;
	isNew = flagPara;
}


CDlgSecretSharingParameter::~CDlgSecretSharingParameter()
{
}

void CDlgSecretSharingParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_K, m_secret);
	DDX_Text(pDX, IDC_EDIT_N, m_participants);
	DDX_Text(pDX, IDC_EDIT_T, m_threshold);
	DDX_Text(pDX, IDC_EDIT_MYPRIME, m_myPrime);
	DDX_Text(pDX, IDC_EDIT_MYCOEFF, m_myCoeff);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDC_EDIT_MYPRIME, m_ctrl_myPrime);
}


BEGIN_MESSAGE_MAP(CDlgSecretSharingParameter, CDialog)
	ON_BN_CLICKED(IDB_GENERATENEW, OnButtonGenerateNew)
	ON_EN_UPDATE(IDC_EDIT_MYPRIME, OnEnUpdateEditMyprime)
	ON_BN_CLICKED(IDOK, OnButtonClickedOk)
	ON_EN_UPDATE(IDC_EDIT_MYCOEFF, OnUpdateEditMycoeff)
END_MESSAGE_MAP()

BOOL CDlgSecretSharingParameter::OnInitDialog()
{
	CDialog::OnInitDialog();
	this->t = atoi(LPCSTR(this->m_threshold));
	//Einlesen der ursprünglichen Koeffizienten
	CString tmpCoeff;
	tmpCoeff.Format("%d", setupCoeff[0]);
	m_myCoeff += tmpCoeff;
	for (int i = 1; i < t-1; i++)
	{
		m_myCoeff += ',';
		tmpCoeff.Format("%d", setupCoeff[i]);
		m_myCoeff += tmpCoeff;
	}
	UpdateData(false);
	return TRUE;
}

// CDlgSecretSharingParameter-Meldungshandler

void CDlgSecretSharingParameter::OnButtonGenerateNew()
{
	//die geänderten Werte werden aus dem Dialog übernommen
	UpdateData(true);
	BOOL bError;
	int err_ndx;
	//falls es sich um einen berechenbaren Ausdruck handelt
	bError = EvalFormula(this->m_myPrime, err_ndx, true);
	if (bError==0)
	{
		m_ctrl_myPrime.SetSel(err_ndx-1,m_myPrime.GetLength());
		m_ctrl_myPrime.SetFocus();
		LoadString(AfxGetInstanceHandle(), IDS_STRING_INPUT_FALSE, pc_str, 100);
		AfxMessageBox(pc_str, MB_ICONEXCLAMATION);
		return;
	}
	int tmpPrime = atoi(LPCSTR(this->m_myPrime));
	int tmpSecret = atoi(LPCSTR(this->m_secret));
	int tmpThreshold = atoi(LPCSTR(this->m_threshold));
	int tmpParticipants = atoi(LPCSTR(this->m_participants));
	
//Primzahl geändert?
	if ((tmpPrime != this->oldPrime) && (tmpPrime != 0))
	{
		CTutorialFactorisation TestPrime;
		BOOL isPrime = false;
		isPrime = TestPrime.IsPrime(this->m_myPrime);
		if (!isPrime)
		{
			LoadString(AfxGetInstanceHandle(), IDS_STRING_SECRETSHARING_NOPRIME, pc_str, 110);
			AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
			this->m_ctrl_myPrime.SetFocus();
			this->m_ctrl_myPrime.SetSel(0, this->m_myPrime.GetLength());
			//this->m_myCoeff = "";
			tmpPrime = oldPrime;
			UpdateData(false);
			return;
		}
		else
		{
			if (tmpPrime > limit)
			{
				CString strMsg;
				strMsg.Format(IDS_STRING_SECRETSHARING_EXCEEDSLIMIT, limit);
				AfxMessageBox(strMsg, MB_ICONINFORMATION|MB_OK); 
				CDlgSecretSharingOptions *dlgOpt;
				dlgOpt = new CDlgSecretSharingOptions();
				dlgOpt->m_prime.Format("%d", limit);
				dlgOpt->m_limit.Format("%d", parties);
				UpdateData(true);
				if (dlgOpt->DoModal() == IDOK)
				{
					this->limit = atoi(LPCSTR(dlgOpt->m_prime));
					this->parties = atoi(LPCSTR(dlgOpt->m_limit));
					UpdateData(false);
				}
				delete dlgOpt;
				//this->m_myPrime = "";
				//UpdateData(false);
				return;
			}
			if (tmpPrime <= tmpSecret || tmpPrime <= tmpParticipants)
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_SECRETSHARING_PRIMELESS, pc_str, 150);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				this->m_myPrime = "";
				UpdateData(false);
				return;
			}
			if ((tmpPrime <= limit) && (tmpPrime > tmpSecret && tmpPrime > tmpParticipants))
			{
				int i;
				//Anpassung der Koeffizienten
				for (i =0 ; i < t-1; i++)
				{
					setupCoeff[i] = (rand() % tmpPrime) + 1;
				}
				CString tmpCoeff;
				tmpCoeff.Format("%d", setupCoeff[0]);
				this->m_myCoeff = "";
				m_myCoeff += tmpCoeff;
				for (i = 1; i < t-1; i++)
				{
					m_myCoeff += ',';
					tmpCoeff.Format("%d", setupCoeff[i]);
					m_myCoeff += tmpCoeff;
				}
				m_ctrlButtonOK.EnableWindow(true);
				oldPrime = tmpPrime;
				UpdateData(false);
			}
		}
	}
	else
	{
		int i;
		int n = atoi(LPCSTR(this->m_participants));
		if (n > tmpSecret)
		{
			P.SetLimits(n, limit);
		}
		else P.SetLimits(tmpSecret, limit);
		BOOL flag = FALSE;
		while (!flag)
		{
			P.RandP();
			flag = P.FermatTest(100);
		}
		P.GetPrime(m_myPrime);
		tmpPrime = atoi(LPCSTR(m_myPrime));
		//Anpassung der Koeffizienten
		for (i =0 ; i < t-1; i++)
		{
			setupCoeff[i] = (rand() % tmpPrime) + 1;
		}
		CString tmpCoeff;
		tmpCoeff.Format("%d", setupCoeff[0]);
		this->m_myCoeff = "";
		m_myCoeff += tmpCoeff;
		for (i = 1; i < t-1; i++)
		{
			m_myCoeff += ',';
			tmpCoeff.Format("%d", setupCoeff[i]);
			m_myCoeff += tmpCoeff;
		}
		m_ctrlButtonOK.EnableWindow(true);
		oldPrime = tmpPrime;
		UpdateData(false);
		UpdateData(false);
	}
}


void CDlgSecretSharingParameter::OnEnUpdateEditMyprime()
{
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(true);
	m_ctrl_myPrime.GetSel(sels, sele);
	CheckEdit(m_myPrime, sels, sele);
	res.Empty();

	for (k = i = 0; i < m_myPrime.GetLength(); i++) 
	{
		c = m_myPrime[i];
		res += c;
		k++;
	}
	m_myPrime = res;
	UpdateData(false);
	m_ctrl_myPrime.SetSel(sels,sele);
}

void CDlgSecretSharingParameter::CheckEdit(CString &m_edit, int &sels, int &sele)
{
	while((0 == m_edit.IsEmpty()) && ('0' == m_edit.GetAt(0)))
	{
		m_edit = m_edit.Right(m_edit.GetLength()-1);
		sels = sele =0;								
	}
	int exp_counter=0;
	for(int i = 0; i < m_edit.GetLength(); i++)
	{
		char ch = m_edit.GetAt(i);
		char ch2;
		if (i >= 1) ch2=m_edit.GetAt(i-1);
		if(((ch >= '0')&&(ch <= '9'))||((ch == '^'||ch == '+'||ch == '-' ||ch == '*') && (ch2 != '^' && ch2 != '+' && ch2 != '-'  && ch2 != '*') && i >= 1 )||ch == '('||ch == ')')
		{
				
		}
		else
		{
			m_edit = m_edit.Left(i) + m_edit.Right(m_edit.GetLength() - i-1);	
			if(i <= sele)
			{
				sele--;
				sels--;
			}
			i--;
		}
	}
}

// flomar, 2018/10/01: The original code contained a bug that would display 
// error messages and prevent the user from proceeding although all the 
// given parameters were good.
void CDlgSecretSharingParameter::OnButtonClickedOk()
{
	// Make a copy of the supplied coefficients, but ignore all characters 
	// which are not part of the valid alphabet. Here, the valid alphabet 
	// consists of digits and the comma separator.
	const CString digits = "0123456789";
	const CString separator = ",";
	CString stringCoefficients;
	for(int index=0; index<m_myCoeff.GetLength(); index++) {
		const char character = m_myCoeff[index];
		if(digits.Find(character) != -1 || separator.Find(character) != -1) {
			stringCoefficients.AppendChar(character);
		}
	}
	// Now we split the coefficients using the separator so that we have 
	// isolated string representations of each coefficient in a vector.
	const std::vector<CString> vectorCoefficients = splitString(stringCoefficients, separator);
	// If we don't have the exact number of required coefficients, 
	// we can bail right away with an appropriate error message.
	const int numberOfCoefficients = vectorCoefficients.size();
	const int numberOfCoefficientsRequired = atoi(LPCSTR(m_threshold)) - 1;
	if(numberOfCoefficients != numberOfCoefficientsRequired) {
		CString message;
		message.Format(IDS_STRING_SECRETSHARING_MORECOEFF, numberOfCoefficientsRequired);
		AfxMessageBox(message, MB_ICONINFORMATION);
		m_myCoeff = "";
		m_ctrlButtonOK.EnableWindow(false);
		UpdateData(false);
		return;
	}
	// Now go through all coefficients and make sure they're valid, as in 
	// "smaller than the prime".
	const int prime = atoi(LPCSTR(m_myPrime));
	for(int index=0; index<vectorCoefficients.size(); index++) {
		const CString stringCoefficient = vectorCoefficients[index];
		const int coefficient = atoi(LPCSTR(stringCoefficient));
		if(coefficient >= prime) {
			CString message;
			message.Format(IDS_STRING_SECRETSHARING_BIGCOEFF, MB_ICONINFORMATION);
			m_myCoeff = "";
			m_ctrlButtonOK.EnableWindow(false);
			UpdateData(false);
			return;
		}
	}
	// At this point all coeffiencts seem to be valid. Therefore write them 
	// back to the original data source (that weird long pointer), and make 
	// sure to enable the OK button.
	for(int index=0; index<vectorCoefficients.size(); index++) {
		const CString stringCoefficient = vectorCoefficients[index];
		const int coefficient = atoi(LPCSTR(stringCoefficient));
		if(setupCoeff[index] != (long)(coefficient)) {
			setupCoeff[index] = (long)(coefficient);
			isNew = true;
			m_ctrlButtonOK.EnableWindow(true);
		}
	}
	UpdateData(false);
	OnOK();
}

void CDlgSecretSharingParameter::OnUpdateEditMycoeff()
{
	UpdateData(true);
	m_ctrlButtonOK.EnableWindow(true);
	UpdateData(false);
}
