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

// RSABloemerMayDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "RSABloemerMayDlg.h"
#include "NTLExpPars.h"
#include "FileTools.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSABloemerMayDlg Dialogfeld

CRSABloemerMayDlg::CRSABloemerMayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRSABloemerMayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRSABloemerMayDlg)
	m_m = 4;
	m_N = _T("");
	m_e = _T("");
	m_d = _T("");
	m_P = _T("");
	m_Q = _T("");
	m_delta = _T("");
	m_BitsOfN = _T("");
	m_choice = 0;
	m_maxdelta = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRSABloemerMayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRSABloemerMayDlg)
	DDX_Text(pDX, IDC_EDITM, m_m);
	DDX_Text(pDX, IDC_EDITN, m_N);
	DDX_Text(pDX, IDC_EDITE, m_e);
	DDX_Text(pDX, IDC_EDITD, m_d);
	DDX_Text(pDX, IDC_EDITP, m_P);
	DDX_Text(pDX, IDC_EDITQ, m_Q);
	DDX_Text(pDX, IDC_EDITDELTA, m_delta);
	DDX_Text(pDX, IDC_EDITBITSOFN, m_BitsOfN);
	DDX_Radio(pDX, IDC_RADIOCHOICE, m_choice);
	DDX_Text(pDX, IDC_EDITMAXDELTA, m_maxdelta);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRSABloemerMayDlg, CDialog)
	//{{AFX_MSG_MAP(CRSABloemerMayDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONSTART, OnStart)
	ON_BN_CLICKED(IDC_RANDOM, OnRandom)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CANCELATTACK, OnCancelattack)
	ON_EN_CHANGE(IDC_EDITM, OnChangeEditm)
	ON_EN_KILLFOCUS(IDC_EDITDELTA, OnKillfocusEditdelta)
	ON_EN_CHANGE(IDC_EDITN, OnChangeEditn)
	ON_EN_CHANGE(IDC_EDITE, OnChangeEdite)
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_BUTTONDEFAULT, OnButtondefault)
	ON_BN_CLICKED(IDC_BUTTONLOG, OnButtonlog)
	ON_BN_CLICKED(IDC_RADIOCHOICE, OnRadiochoice)
	ON_EN_CHANGE(IDC_EDITD, OnChangeEditd)
	ON_EN_CHANGE(IDC_EDITBITSOFN, OnChangeEditbitsofn)
	ON_EN_CHANGE(IDC_EDITDELTA, OnChangeEditdelta)
	ON_BN_CLICKED(IDC_BUTTON1, OnCancel)
	ON_BN_CLICKED(IDC_RADIOCHOICE2, OnRadiochoice)
	ON_BN_CLICKED(IDC_BUTTONLOG2, OnButtonlog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRSABloemerMayDlg Nachrichten-Handler

BOOL CRSABloemerMayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	elapsedTime=0;
	OnChangeEditm();
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CRSABloemerMayDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CRSABloemerMayDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//////////////////////////////////////////////
// Start the attack.
//////////////////////////////////////////////

void CRSABloemerMayDlg::errorMessageBox(long ID)
{
    CString tmp, myTitle;
	tmp.Format(ID);
	this->GetWindowText(myTitle);
	MessageBox(tmp, myTitle);
}

void CRSABloemerMayDlg::OnStart() 
{
	UpdateData();
	CString tmp;
	if(!(CStringToDouble(m_delta)>0)){
		errorMessageBox(IDS_RSA_BM_DELTAVALUE);
		return;
	}
	if(CStringToDouble(m_delta)>0.29){
		errorMessageBox(IDS_RSA_BM_DELTATOOBIG);
		return;
	}
	if(CStringToDouble(m_delta)>CStringToDouble(m_maxdelta)){
		errorMessageBox(IDS_RSA_BM_MAXDELTA);
		return;
	}	

	NTLExpPars myPars;
	if ( 8 > NumBits(myPars.parseExp(m_N)) )
	{
		errorMessageBox(IDS_RSA_BM_CHECKN);
		// FIXME 
		return;
	}
	if ( 8 > NumBits(myPars.parseExp(m_e)) )
	{
		errorMessageBox(IDS_RSA_BM_CHECKE);
		// FIXME 
		return;
	}
	if ( 4 > NumBits(myPars.parseExp(m_d)) )
	{
		errorMessageBox(IDS_RSA_BM_CHECKD);
		// FIXME
		return;
	}



	// Start Attack
	// disable everything that could make trouble
	GetDlgItem(IDC_BUTTONSTART)->EnableWindow(false);
	GetDlgItem(IDC_CANCELATTACK)->EnableWindow(true);
	enableDisable(false);

	// timer to update the time display
	SetTimer(1, 1000, 0);
	elapsedTime=0;
	// read all the parameters
	sa.setN(myPars.parseExp(m_N));
	sa.setE(myPars.parseExp(m_e));
	sa.setDelta(CStringToDouble(m_delta));
	sa.setM(m_m);
	sa.setT(GetDlgItemInt(IDC_EDITT));
	sa.status=1;
	SetDlgItemText(IDC_EDITP,"");
	SetDlgItemText(IDC_EDITQ,"");
	// start the attack by calling the thread function
	pThread = AfxBeginThread (thrFunction, this);

}
//////////////////////////////////////////////
// Gnerate a random example
//////////////////////////////////////////////
void CRSABloemerMayDlg::OnRandom() 
{
	UpdateData();

	double delta=CStringToDouble(m_delta);
	int bitsOfN = atoi(m_BitsOfN);

	SetDlgItemText(IDC_EDITDELTA, doubleToCString(delta));
	SetDlgItemInt(IDC_EDITBITSOFN, bitsOfN);
	CString tmp;
	if (bitsOfN<=5){
		tmp.Format(IDS_RSA_BM_NTOOSMALL);
		CString myTitle;
		this->GetWindowText(myTitle);
		MessageBox(tmp,myTitle);
	}
	else if(delta>0.29 || delta<0){
		tmp.Format(IDS_RSA_BM_DELTARANGE);
		CString myTitle;
		this->GetWindowText(myTitle);
		MessageBox(tmp,myTitle);
	}
	else{
		BeginWaitCursor(); // show hourglass
		// generate N,p,q with PRNG
		int bitsOfP=(bitsOfN/2);
		int bitsOfQ=(bitsOfN/2);
		SetSeed(to_ZZ(GetTime()*10000));
		ZZ p = GenPrime_ZZ(bitsOfP);
		ZZ q = GenPrime_ZZ(bitsOfQ);
		ZZ N = p*q;

		// find d as close to N^delta as possible
		ZZ d =to_ZZ(pow(to_RR(N),to_RR(delta)))-1;

		ZZ e;
		ZZ phi=(p-1)*(q-1);
		// decrement d until its invertible
		while(InvModStatus(e, d, phi)&&d>1) d--;
		// calculate actual delta
		if(d>1&&N>0){
			m_N=toString(N,10,0);
			m_e=toString(e,10,0);
			m_d=toString(d,10,0);
			UpdateData(false);
			GetDlgItem(IDC_BUTTONSTART)->EnableWindow(N>0 && e>0);
		}
		else{
			tmp.Format(IDS_RSA_BM_NOEXAMPLE);
			CString myTitle;
			this->GetWindowText(myTitle);
			MessageBox(tmp,myTitle);
		}
		EndWaitCursor();
	}
}
//////////////////////////////////////////////
// Reads the String from an edit and converts it to NTL's ZZ (big integer).
//////////////////////////////////////////////
ZZ CRSABloemerMayDlg::GetDlgItemZZ(int ID, int base)
{
	CString tmp;
	GetDlgItemText(ID,tmp);
	return setToStringValue(tmp,base);
}
//////////////////////////////////////////////
// Function of the thread, calls the attack function of the 
// BloemerMayAttack object.
//////////////////////////////////////////////
UINT CRSABloemerMayDlg::thrFunction (LPVOID pParam){
	CRSABloemerMayDlg* pDlg=(CRSABloemerMayDlg*) pParam;
	pDlg->sa.attack();
	return 0;
}

//////////////////////////////////////////////
// This function updates the time and checks, whether the attack ist
// finished.
//////////////////////////////////////////////
void CRSABloemerMayDlg::OnTimer(UINT nIDEvent) 
{
	// update and format overall elapsed time
	elapsedTime=sa.getOverallTime();
	CString timeStr;
	timeStr.Format("%3dh%3dm%3ds",elapsedTime/3600,
		(elapsedTime/60)%60,(elapsedTime)%60);
	SetDlgItemText(IDC_EDITOVERALLTIME,timeStr);

	if(sa.status>0){ // attack still running
		// update information
		CString t;
		int bLT=sa.getLatticeTime();
		t.Format("%3dh%3dm%3ds",bLT/3600,(bLT/60)%60,(bLT)%60);
		SetDlgItemText(IDC_EDITLATTICETIME,t);
		int rLT=sa.getReductionTime();
		t.Format("%3dh%3dm%3ds",rLT/3600,(rLT/60)%60,(rLT)%60);
		SetDlgItemText(IDC_EDITREDUCETIME,t);
		SetDlgItemInt(IDC_EDITREDUCTIONS,sa.reductions);
		int fRT=sa.getResultantTime();
		t.Format("%3dh%3dm%3ds",fRT/3600,(fRT/60)%60,(fRT)%60);
		SetDlgItemText(IDC_EDITRESULTANTTIME,t);
		SetDlgItemInt(IDC_EDITRESULTANT,sa.getResultants());
	}
	if(sa.status==6){// finished successfully
		m_P=toString(sa.getP(),10,0);
		m_Q=toString(sa.getQ(),10,0);
		NTLExpPars myPars;
		ZZ e=myPars.parseExp(m_e);
		m_d=toString(InvMod(e,(sa.getP()-1)*(sa.getQ()-1)),10,0);
		UpdateData(false);
	}
	if(sa.status==7){// finished without success
		KillTimer(1);
		CString tmp;
		tmp.LoadString(IDS_RSA_BM_NOSOLUTION);
		CString myTitle;
		this->GetWindowText(myTitle);
		MessageBox(tmp,myTitle);
	}
	if(sa.status==0||sa.status>5){
		KillTimer(1);
		enableDisable(true);
		GetDlgItem(IDC_BUTTONSTART)->EnableWindow(true);
		GetDlgItem(IDC_CANCELATTACK)->EnableWindow(false);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
	}
	CDialog::OnTimer(nIDEvent);
}
//////////////////////////////////////////////
// attack canceled by user
//////////////////////////////////////////////
void CRSABloemerMayDlg::OnCancelattack() 
{
	// make sure cancel is not pushed twice
	GetDlgItem(IDC_CANCELATTACK)->EnableWindow(false);
	sa.cancel();
	// wait until thread is really finished
	WaitForSingleObject(pThread->m_hThread, INFINITE);
}

/////////////////////////////////////////////
//	When m is changed update all depending values
/////////////////////////////////////////////
void CRSABloemerMayDlg::OnChangeEditm() 
{
	UpdateData();
	if(m_m>3){
		int t=sa.optimalT(GetDlgItemInt(IDC_EDITM)); // calculate optimal t
		SetDlgItemInt(IDC_EDITT,t);
		// calculate delta
		double d= sa.maxDelta(GetDlgItemInt(IDC_EDITM),GetDlgItemInt(IDC_EDITT));
		CString tmp;
		tmp=doubleToCString(d);
		SetDlgItemText(IDC_EDITMAXDELTA,tmp);
		// calculate dimension of lattice
		SetDlgItemInt(IDC_EDITLATTICEDIM, (m_m+1)*(t+1));
	}else{
		SetDlgItemText(IDC_EDITMAXDELTA,"");
		// calculate dimension of lattice
		SetDlgItemInt(IDC_EDITLATTICEDIM,0);
	}
	GetDlgItem(IDC_BUTTONSTART)->EnableWindow(m_m>3);
}


void CRSABloemerMayDlg::OnKillfocusEditdelta() 
{

}
/////////////////////////////////////////////
// called when dialog is closed
/////////////////////////////////////////////

void CRSABloemerMayDlg::OnCancel() 
{
	if(sa.status>0&&sa.status<6){
		// cancel the attack and wait before window is closed
		sa.cancel();
		WaitForSingleObject(pThread->m_hThread, INFINITE);
	}
	CDialog::OnCancel();

}

/////////////////////////////////////////////
//	Checks wheter values of N and e are valid
/////////////////////////////////////////////
void CRSABloemerMayDlg::OnChangeEditn() 
{
	checkStartButton();
}
/////////////////////////////////////////////
//	Checks wheter values of N and e are valid
/////////////////////////////////////////////
void CRSABloemerMayDlg::OnChangeEdite() 
{
	checkStartButton();
}
//////////////////////////////////////////////
// Function to enable or disable the dialog items
//////////////////////////////////////////////

void CRSABloemerMayDlg::enableDisable(bool v)
{

	GetDlgItem(IDC_EDITN)->EnableWindow(v);
	GetDlgItem(IDC_EDITE)->EnableWindow(v);
	GetDlgItem(IDC_EDITD)->EnableWindow(v);
	GetDlgItem(IDC_EDITBITSOFN)->EnableWindow(v);
	GetDlgItem(IDC_RANDOM)->EnableWindow(v);
	GetDlgItem(IDC_BUTTONDEFAULT)->EnableWindow(v);
	GetDlgItem(IDC_EDITDELTA)->EnableWindow(v);
	GetDlgItem(IDC_EDITM)->EnableWindow(v);
	GetDlgItem(IDC_RADIOCHOICE)->EnableWindow(v);
	GetDlgItem(IDC_RADIOCHOICE2)->EnableWindow(v);

}
//////////////////////////////////////////////
// Show hourglass while busy.
//////////////////////////////////////////////
BOOL CRSABloemerMayDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	
	if(sa.status>0&&sa.status<6)
		SetCursor(LoadCursor(NULL, IDC_WAIT));
	else
		SetCursor(LoadCursor(NULL, IDC_ARROW));

	return TRUE;
}


void CRSABloemerMayDlg::checkStartButton()
{
	NTLExpPars myPars;
	UpdateData();
	ZZ N=myPars.parseExp(m_N);
	ZZ e=myPars.parseExp(m_e);
	ZZ d=myPars.parseExp(m_d);
	if(N>0&&d>0)
		m_delta= doubleToCString(log(d)/log(N));
	m_BitsOfN.Format("%d",NumBits(N));
	GetDlgItem(IDC_BUTTONSTART)->EnableWindow(N>0 && e>0 && m_m>3);
	UpdateData(false);
}

void CRSABloemerMayDlg::OnButtondefault() 
{
	m_BitsOfN="300";
	m_delta="0,26";
	UpdateData(false);
}

void CRSABloemerMayDlg::OnButtonlog() 
{
	char *filename = new char[CRYPTOOL_PATH_LENGTH];
	GetTmpName(filename, "cry", ".txt");
	ofstream Outfile;
	Outfile.open(filename);
	Outfile << sa.log;
	Outfile.close();
	CAppDocument *NewDoc = theApp.OpenDocumentFileNoMRU(filename);
	delete filename;
	
}

CString CRSABloemerMayDlg::doubleToCString(double v)
{
	CString retval;
	int vorKomma=(int)v;
	int nachKomma=(int)((v-vorKomma)*10000);
	retval.Format("%d,%04d",vorKomma,nachKomma);
	return retval;
}

double CRSABloemerMayDlg::CStringToDouble(CString c)
{
	double v;
	int kommaPos=c.Find(",");
	if(kommaPos>-1){
		v=atof(c.Left(kommaPos));
		CString t=c.Right(c.GetLength()-kommaPos-1);
		t=t+"0000";
		t=t.Left(4);
		v+=atof(t)/10000;
	}else 
		v=atof(c);
	return v;
}

void CRSABloemerMayDlg::OnRadiochoice() 
{
	UpdateData();
	bool b=(m_choice==0);
	
	((CEdit*)GetDlgItem(IDC_EDITN))->SetReadOnly(!b);
	((CEdit*)GetDlgItem(IDC_EDITE))->SetReadOnly(!b);
	((CEdit*)GetDlgItem(IDC_EDITD))->SetReadOnly(!b);
	((CEdit*)GetDlgItem(IDC_EDITBITSOFN))->SetReadOnly(b);
	GetDlgItem(IDC_RANDOM)->EnableWindow(!b);
	GetDlgItem(IDC_BUTTONDEFAULT)->EnableWindow(!b);
	m_N="";
	m_e="";
	m_d="";
	if(b){
		m_BitsOfN="";
		m_delta="0,26";
	}else{
		m_BitsOfN="300";
		m_delta="0,26";
	}

	UpdateData(false);
}

void CRSABloemerMayDlg::OnChangeEditd() 
{
	checkStartButton();
}

void CRSABloemerMayDlg::OnChangeEditbitsofn() 
{
	UpdateData();
	m_N="";
	m_e="";
	m_d="";
	UpdateData(false);
}

void CRSABloemerMayDlg::OnChangeEditdelta() 
{
	UpdateData();
	m_d="";
	if(m_choice==1){
		m_N="";
		m_e="";
	}
	UpdateData(false);
}
