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

// RSAFactorHintDlg.cpp : Implementierungsdatei 
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "RSAFactorHintDlg.h"
#include "FileTools.h"
#include "NTLExpPars.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CRSAFactorHintDlg Dialogfeld

CRSAFactorHintDlg::CRSAFactorHintDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRSAFactorHintDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRSAFactorHintDlg)
	m_msbLsb = 0;
	m_base = 0;
	m_bitsOfN = 0;
	m_choice = 0;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRSAFactorHintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRSAFactorHintDlg)
	DDX_Radio(pDX, IDC_RADIOMSB, m_msbLsb);
	DDX_Radio(pDX, IDC_RADIONUMBER, m_base);
	DDX_Text(pDX, IDC_EDITBITSOFN, m_bitsOfN);
	DDX_Radio(pDX, IDC_RADIOCHOICE, m_choice);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRSAFactorHintDlg, CDialog)
	//{{AFX_MSG_MAP(CRSAFactorHintDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIONUMBER, OnRadionumber)
	ON_BN_CLICKED(IDC_RADIOHEX, OnRadiohex)
	ON_BN_CLICKED(IDC_RADIOBIN, OnRadio3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCELATTACK, OnCancelattack)
	ON_BN_CLICKED(IDSTART, OnStart)
	ON_BN_CLICKED(IDC_R, OnRandom)
	ON_EN_KILLFOCUS(IDC_EDITN, OnKillfocusEditn)
	ON_EN_CHANGE(IDC_EDITBITSOFN, OnChangeEditbitsofn)
	ON_WM_SETCURSOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTONCLOSE, OnButtonclose)
	ON_BN_CLICKED(IDC_BUTTONLOG, OnButtonlog)
	ON_BN_CLICKED(IDC_RADIOCHOICE, OnRadiochoice)
	ON_EN_CHANGE(IDC_EDITN, OnChangeEditn)
	ON_EN_CHANGE(IDC_EDITBITSOFP, OnChangeEditbitsofp)
	ON_EN_CHANGE(IDC_EDITB, OnChangeEditb)
	ON_BN_CLICKED(IDC_RADIOLSB, OnRadiolsb)
	ON_BN_CLICKED(IDC_BUTTONDEFAULT, OnButtondefault)
	ON_EN_CHANGE(IDC_EDITGUESSP_LEFT, OnChangeGuessP)
	ON_BN_CLICKED(IDC_RADIOCHOICE2, OnRadiochoice)
	ON_BN_CLICKED(IDC_RADIOMSB, OnRadiolsb)
	ON_EN_CHANGE(IDC_EDITGUESSP_RIGHT, OnChangeGuessP)
	ON_EN_KILLFOCUS(IDC_EDITGUESSP_RIGHT, OnKillfocusGuessP)
	ON_EN_KILLFOCUS(IDC_EDITGUESSP_LEFT, OnKillfocusGuessP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRSAFactorHintDlg Nachrichten-Handler

BOOL CRSAFactorHintDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen

	UpdateData(false);
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CRSAFactorHintDlg::OnPaint() 
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

HCURSOR CRSAFactorHintDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

///////////////////////////////////////////
//   Is called when the attack is to begin.
///////////////////////////////////////////
void CRSAFactorHintDlg::OnStart() 
{
	
	UpdateData();
	int m_b=GetDlgItemInt(IDC_EDITB);
	int m_bitsOfP=GetDlgItemInt(IDC_EDITBITSOFP);
	if (m_bitsOfP==0){
			CString tmp, myTitle;
			tmp.LoadString(IDS_RSA_FH_ENTERP);
			this->GetWindowText(myTitle);
			MessageBox(tmp,myTitle);
		}
	else
		if(m_b>m_bitsOfP){
			CString msg, myTitle;
			msg.Format(IDS_RSA_FH_BITSOFP,
				m_bitsOfP,
				m_b);
			this->GetWindowText(myTitle);
			MessageBox(msg,myTitle);
		}
		else
			if(m_bitsOfN==0){
				CString tmp, myTitle;
				tmp.LoadString(IDS_RSA_FH_CHOOSEN);
				this->GetWindowText(myTitle);
				MessageBox(tmp,myTitle);
			}
			else
				if(GetDlgItemInt(IDC_EDITDIM)==0){
					int needed = (int)((double)(m_bitsOfN+3)/4)+1;
					CString form, myTitle;
					form.Format(IDS_RSA_FH_ATLEASTKNOWN,
						m_b,
						needed);
					this->GetWindowText(myTitle);
					MessageBox(form,myTitle);
				}
				else{
					disableEnable(false); // disable example geneartion
					GetDlgItem(IDCANCELATTACK)->EnableWindow(true);
					GetDlgItem(IDSTART)->EnableWindow(false);
					SetTimer(1, 1000, 0); // this timer updates the GUI
					elapsedTime=0;
					
					int newbase=2; // representation of the Parameters N
					UpdateData();  // and P
					if(m_base==0)
						newbase=10;
					if(m_base==1)
						newbase=16;
					
					fh.setN(m_N);
					ZZ P = m_GuessP;
					if(m_msbLsb==0)
						P*=power(to_ZZ(2),m_bitsOfP-m_b);
					fh.setP(P);
					fh.setBitsOfP(m_bitsOfP);
					fh.setB(GetDlgItemInt(IDC_EDITB));
					
					SetDlgItemText(IDC_EDITFACTORP,"");
					SetDlgItemText(IDC_EDITFACTORQ,"");
					
					UpdateData();
					fh.status=1;
					pThread = AfxBeginThread (thrFunction, this); 
				}
				
}
///////////////////////////////////////////
// Reads the String from an edit and converts it to NTL's ZZ (big integer).
///////////////////////////////////////////

ZZ CRSAFactorHintDlg::GetDlgItemZZ(int ID, int base)
{
	CString tmp;
	GetDlgItemText(ID,tmp);
	return setToStringValue(tmp,base);
}

///////////////////////////////////////////
// Create a random example
///////////////////////////////////////////
void CRSAFactorHintDlg::OnRandom() 
{
	UpdateData();
	int m_bitsOfP=GetDlgItemInt(IDC_EDITBITSOFP);
	if (m_bitsOfN<=10){
		CString tmp, myTitle;
		tmp.LoadString(IDS_RSA_FH_WRONGN);
		this->GetWindowText(myTitle);
		MessageBox(tmp,myTitle);
	}
	else if(m_bitsOfP<=5 || m_bitsOfP>=m_bitsOfN){
		CString tmp, myTitle;
		tmp.LoadString(IDS_RSA_FH_WRONGP);
		this->GetWindowText(myTitle);
		MessageBox(tmp,myTitle);
	}
	else{
		BeginWaitCursor();
		int bitsOfQ=(m_bitsOfN-m_bitsOfP);
		
		SetSeed(to_ZZ(GetTime()*10000)); 
		m_p = GenPrime_ZZ(m_bitsOfP); // generate N, p and q
		ZZ q = GenPrime_ZZ(bitsOfQ);
		m_N=m_p*q;
		int newbase=2;  // check which representation to use
		if(m_base==0)
			newbase=10;
		if(m_base==1)
			newbase=16;
//		m_N=toString(N,newbase,newbase*newbase*2);
//		m_P=toString(m_p,newbase,newbase*newbase*2);


		UpdateData(false);
		updateP();
		updateDim();
		EndWaitCursor();
	}
}

void CRSAFactorHintDlg::OnRadionumber() 
{
	updateNP();
}

void CRSAFactorHintDlg::OnRadiohex() 
{
	updateNP();
}

void CRSAFactorHintDlg::OnRadio3() 
{
	updateNP();
}
///////////////////////////////////////////
// Update dialog when a value has changed
///////////////////////////////////////////


void CRSAFactorHintDlg::updateNP()
{
	UpdateData();
	int group= m_base*m_base*2;
	int base=(m_base*6+10)%20;
	SetDlgItemText(IDC_EDITN,toString(m_N,base,group));
	SetDlgItemText(IDC_EDITP_LEFT,toString(m_p,base,group));
	SetDlgItemText(IDC_EDITP_RIGHT,toString(m_p,base,group));
	if(m_GuessP>0){
		//if(m_msbLsb==0){
			int figuresOfP;
			int figuresOfGuess;
			int groupOffset=0;
			if(group>0&&m_p>0){
				figuresOfP=(int)ceil(log(m_p)/log((double)base));
				figuresOfGuess=(int)ceil(log(m_GuessP)/log((double)base));
				groupOffset=(figuresOfP-figuresOfGuess)%group;
			}
			CString filledString=toString(m_GuessP,base,group,groupOffset,0);
			SetDlgItemText(IDC_EDITGUESSP_LEFT,filledString);
			int m_b=GetDlgItemInt(IDC_EDITB);
			int NumFigures =(int) ceil(log(power(to_ZZ(2),m_b))/log((double)base));
			SetDlgItemText(IDC_EDITGUESSP_RIGHT,toString(m_GuessP,base,group,0,NumFigures));

	}else{
		SetDlgItemText(IDC_EDITGUESSP_LEFT,"");
		SetDlgItemText(IDC_EDITGUESSP_RIGHT,"");
	}
	((CEdit*)GetDlgItem(IDC_EDITP_RIGHT))->SetSel(0,-1);
	((CEdit*)GetDlgItem(IDC_EDITGUESSP_RIGHT))->SetSel(0,-1);
	UpdateData(false);

}


////////////////////////////////
// called if attack is to be canceled
////////////////////////////////
void CRSAFactorHintDlg::OnCancelattack() 
{
	// make sure cancel is not pushed twice
	GetDlgItem(IDCANCELATTACK)->EnableWindow(false);
	if(fh.status!=0) // is the attack running?
		fh.cancel();
	// wait until thread is really finished
	WaitForSingleObject(pThread->m_hThread, INFINITE);

	
}
/////////////////////////////////////////////////
// This function updates the time and checks, whether the attack ist
// finished.
/////////////////////////////////////////////////
void CRSAFactorHintDlg::OnTimer(UINT nIDEvent) 
{
	// get and format overall time
	elapsedTime=fh.getOverallTime();
	CString timeStr;
	timeStr.Format("%2dh%2dm%2ds",elapsedTime/3600,
		(elapsedTime/60)%60,(elapsedTime)%60);
	SetDlgItemText(IDC_EDITOVERALLTIME,timeStr);

	if(fh.status>0){// running
		// update information
		CString t;
		int bLT=fh.getLatticeTime();
		t.Format("%2dh%2dm%2ds",bLT/3600,(bLT/60)%60,(bLT)%60);
		SetDlgItemText(IDC_EDITLATTICETIME,t);
		int rLT=fh.getReductionTime();
		t.Format("%2dh%2dm%2ds",rLT/3600,(rLT/60)%60,(rLT)%60);
		SetDlgItemText(IDC_EDITREDUCETIME,t);
		SetDlgItemInt(IDC_EDITREDUCTIONS,(int)fh.reductions);
	}
	if(fh.status==6){// successfully finished
		SetDlgItemText(IDC_EDITFACTORP,toString(fh.getP(),10,0));
		SetDlgItemText(IDC_EDITFACTORQ,toString(fh.getQ(),10,0));
	}
	if(fh.status==7){// failed
		SetDlgItemText(IDC_EDITFACTORP,"???");
		SetDlgItemText(IDC_EDITFACTORQ,"???");
	}

	if(fh.status==0||fh.status>5){ // attack finished 
		GetDlgItem(IDSTART)->EnableWindow(true);
		GetDlgItem(IDCANCELATTACK)->EnableWindow(false);
		KillTimer(1);
		disableEnable(true);
		if(fh.status==0){
			CString tmp, myTitle;
			tmp.LoadString(IDS_RSA_FH_CANCEL);
			this->GetWindowText(myTitle);
			MessageBox(tmp,myTitle);
		}
		if(fh.status==6){
			CString tmp, myTitle;
			tmp.LoadString(IDS_RSA_FH_SUCCESS);
			this->GetWindowText(myTitle);
			MessageBox(tmp,myTitle);
		}
		if(fh.status==7){
			CString tmp, myTitle;
			tmp.LoadString(IDS_RSA_FH_NOSUCCESS);
			this->GetWindowText(myTitle);
			MessageBox(tmp,myTitle);
		}
		SetCursor(LoadCursor(NULL, IDC_ARROW));
	}
	CDialog::OnTimer(nIDEvent);
}
//////////////////////////////////////////
// Function of the thread, calls the attack function of the 
// FactorHint object.
//////////////////////////////////////////
UINT CRSAFactorHintDlg::thrFunction (LPVOID pParam){
	// pointer to the calling dialog
	CRSAFactorHintDlg* pDlg=(CRSAFactorHintDlg*) pParam;

	// determine kind of attack and start it
	if(pDlg->m_msbLsb==0)  
		pDlg->fh.MSBFact();
	else
		pDlg->fh.LSBFact();
	return 0;
}

void CRSAFactorHintDlg::OnKillfocusEditn() 
{
	if(m_base==0){
		NTLExpPars myPars;
		CString tmp;
		GetDlgItemText(IDC_EDITN, tmp);
		m_N = myPars.parseExp(tmp);
	}else
		m_N=GetDlgItemZZ(IDC_EDITN,(m_base*6+10)%20);
	updateNP();	
}


void CRSAFactorHintDlg::OnChangeEditbitsofn() 
{
	UpdateData();
	if(m_choice==1){
		m_N=to_ZZ(0);
		m_p=to_ZZ(0);
		m_GuessP=to_ZZ(0);
		updateNP();
	}
	updateDim();
}

void CRSAFactorHintDlg::OnChangeEditb() 
{
	UpdateData();
	if(m_choice==1){
		updateP();
	}

	updateDim();
}

//////////////////////////////////////////////
// Function to enable or disable the dialog items
//////////////////////////////////////////////

void CRSAFactorHintDlg::disableEnable(bool v)
{
	GetDlgItem( IDC_R )->EnableWindow(m_choice==1&&v);
	GetDlgItem(IDC_BUTTONDEFAULT)->EnableWindow(m_choice==1&&v);
	GetDlgItem( IDC_EDITN )->EnableWindow(v);
	GetDlgItem( IDC_EDITN )->EnableWindow(v);
	GetDlgItem( IDC_EDITP_LEFT )->EnableWindow(v);
	GetDlgItem( IDC_EDITP_RIGHT )->EnableWindow(v);
	GetDlgItem( IDC_EDITGUESSP_LEFT )->EnableWindow(v);
	GetDlgItem( IDC_EDITGUESSP_RIGHT )->EnableWindow(v);
	GetDlgItem( IDC_EDITB )->EnableWindow(v);
	GetDlgItem( IDC_EDITBITSOFP )->EnableWindow(v);
	GetDlgItem( IDC_EDITBITSOFN )->EnableWindow(v);
	GetDlgItem( IDC_RADIONUMBER )->EnableWindow(v);
	GetDlgItem( IDC_RADIOHEX )->EnableWindow(v);
	GetDlgItem( IDC_RADIOBIN )->EnableWindow(v);
	GetDlgItem( IDC_RADIOLSB )->EnableWindow(v);
	GetDlgItem( IDC_RADIOMSB )->EnableWindow(v);
	GetDlgItem( IDC_RADIOCHOICE )->EnableWindow(v);
	GetDlgItem( IDC_RADIOCHOICE2 )->EnableWindow(v);
}
//////////////////////////////////////////////
// Show hourglass while busy.
//////////////////////////////////////////////
BOOL CRSAFactorHintDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{

	if(fh.status>0&&fh.status<6)
		SetCursor(LoadCursor(NULL, IDC_WAIT));
	else
		SetCursor(LoadCursor(NULL, IDC_ARROW));

	return TRUE;
}
/////////////////////////////////////////////
// called when dialog is closed
/////////////////////////////////////////////
void CRSAFactorHintDlg::OnClose() 
{
	if(fh.status!=0&&fh.status<=5){
		fh.cancel();
		WaitForSingleObject(pThread->m_hThread, INFINITE);
	}
	CDialog::OnCancel();
}

void CRSAFactorHintDlg::OnButtonclose() 
{
	OnClose();
}

void CRSAFactorHintDlg::OnButtonlog() 
{
	char *filename = new char[CRYPTOOL_PATH_LENGTH];
	GetTmpName(filename, "cry", ".txt");
	ofstream Outfile;
	Outfile.open(filename);
	Outfile << fh.log;
	Outfile.close();

	CAppDocument *NewDoc = theApp.OpenDocumentFileNoMRU(filename);
	delete filename;

}

void CRSAFactorHintDlg::OnRadiochoice() 
{
	UpdateData();
	bool b=(m_choice==0);
	((CEdit*)GetDlgItem(IDC_EDITN))->SetReadOnly(!b);
	((CEdit*)GetDlgItem(IDC_EDITGUESSP_LEFT))->SetReadOnly(!b);
	((CEdit*)GetDlgItem(IDC_EDITGUESSP_RIGHT))->SetReadOnly(!b);
	((CEdit*)GetDlgItem(IDC_EDITBITSOFN))->SetReadOnly(b);
	((CEdit*)GetDlgItem(IDC_EDITB))->SetReadOnly(b);
	GetDlgItem(IDC_R)->EnableWindow(!b);
	GetDlgItem(IDC_BUTTONDEFAULT)->EnableWindow(!b);
	m_N=to_ZZ(0);
	m_p=to_ZZ(0);
	m_GuessP=to_ZZ(0);
	updateNP();
	if(b){//user values
		SetDlgItemText(IDC_EDITBITSOFN,"200");
		SetDlgItemText(IDC_EDITBITSOFP,"");
		SetDlgItemText(IDC_EDITB,"");
	}else{
		SetDlgItemText(IDC_EDITBITSOFN,"200");
		SetDlgItemText(IDC_EDITBITSOFP,"100");
		SetDlgItemText(IDC_EDITB,"80");
	}
	UpdateData(false);
	updateDim();
}

void CRSAFactorHintDlg::OnChangeEditn() 
{
	updateDim();
	ZZ N;
	if(m_base==0){
		NTLExpPars myPars;
		CString tmp;
		GetDlgItemText(IDC_EDITN, tmp);
		N = myPars.parseExp(tmp);
	}else
		N=GetDlgItemZZ(IDC_EDITN,(m_base*6+10)%20);
	m_bitsOfN=(int)NumBits(N);
	UpdateData(false);
}

void CRSAFactorHintDlg::OnChangeEditbitsofp() 
{
	UpdateData();
	if(m_choice==1){
		m_N=to_ZZ(0);
		m_p=to_ZZ(0);
		m_GuessP=to_ZZ(0);
		updateNP();
	}
	updateDim();
}


void CRSAFactorHintDlg::updateDim()
{
	UpdateData();
	// calculate parameters of the attack
	int bitsOfN=(int)NumBits(m_N);
	int needed = (int)((double)(bitsOfN+3)/4); //amount of bits needed
	
	SetDlgItemInt(IDC_EDITNEEDED,needed+1);
	
	int b= GetDlgItemInt(IDC_EDITB);
	int diff=b-needed;
	if(diff>0) // if attack possible
		//calculate dimension of lattice
		SetDlgItemInt(IDC_EDITDIM,(int)(bitsOfN/diff)); 
	else
		SetDlgItemInt(IDC_EDITDIM,0);
	//GetDlgItem(IDSTART)->EnableWindow(!IsZero(m_N));
	UpdateData(false);
}

void CRSAFactorHintDlg::OnRadiolsb() 
{
	UpdateData();
	if(m_choice==1)
		updateP();
	GetDlgItem(IDC_EDITGUESSP_LEFT)->ShowWindow(m_msbLsb==0);
	GetDlgItem(IDC_EDITGUESSP_RIGHT)->ShowWindow(m_msbLsb==1);
	GetDlgItem(IDC_EDITP_LEFT)->ShowWindow(m_msbLsb==0);
	GetDlgItem(IDC_EDITP_RIGHT)->ShowWindow(m_msbLsb==1);
	((CEdit*)GetDlgItem(IDC_EDITP_RIGHT))->SetSel(0,-1);
	((CEdit*)GetDlgItem(IDC_EDITGUESSP_RIGHT))->SetSel(0,-1);
	updateDim();
}

void CRSAFactorHintDlg::OnButtondefault() 
{
	SetDlgItemText(IDC_EDITBITSOFN,"200");
	SetDlgItemText(IDC_EDITBITSOFP,"100");
	SetDlgItemText(IDC_EDITB, "80");
}

void CRSAFactorHintDlg::updateP()
{
	int b=GetDlgItemInt(IDC_EDITB); 

	ZZ X=to_ZZ(1);
	UpdateData();

	ZZ P=m_p;
	int m_bitsOfP=GetDlgItemInt(IDC_EDITBITSOFP);
	if(b>m_bitsOfP)
		b=m_bitsOfP;
	if(m_msbLsb==0){ // if MSB example
		X<<=m_bitsOfP-b;
		m_GuessP=m_p-(m_p%X);  // delete lower bits
		m_GuessP/=X;
	}
	else{
		X<<=b; 
		m_GuessP=m_p%X; // else delte Higher bits
	}
	SetDlgItemText(IDC_EDITGUESSP_LEFT,toString(m_GuessP,(m_base*6+10)%20, m_base*m_base*2));
	SetDlgItemText(IDC_EDITGUESSP_RIGHT,toString(m_GuessP,(m_base*6+10)%20, m_base*m_base*2));

	updateNP();	
}

void CRSAFactorHintDlg::OnChangeGuessP() 
{
	UpdateData();
	if(m_choice==0){
		int base=(m_base*6+10)%20;
		CString GuessPString;
		if(m_msbLsb==0){
			GetDlgItemText(IDC_EDITGUESSP_LEFT,GuessPString);
			//	SetDlgItemText(IDC_EDITGUESSP_RIGHT,GuessPString);
		}
		else{
			GetDlgItemText(IDC_EDITGUESSP_RIGHT,GuessPString);
			//	SetDlgItemText(IDC_EDITGUESSP_LEFT,GuessPString);
		}
		ZZ tmpGuessP=setToStringValue(GuessPString,base);
		int bitsOfGuess=NumBits(tmpGuessP);
		int z=0;
		for(int i=0; i<GuessPString.GetLength()
			&&(GuessPString.GetAt(i)=='0'
			||GuessPString.GetAt(i)==' '); i++)
			if(GuessPString.GetAt(i)=='0')
				z++;
			int zeroBits=NumBits(power(to_ZZ(base),z)-1);
			bitsOfGuess+=zeroBits;
			m_GuessP=tmpGuessP;
			SetDlgItemInt(IDC_EDITB, bitsOfGuess);
	}
	UpdateData(false);
	//updateDim();
}

void CRSAFactorHintDlg::OnKillfocusGuessP() 
{
	int base=(m_base*6+10)%20;
	CString GuessPString;
	if(m_msbLsb==0){
		GetDlgItemText(IDC_EDITGUESSP_LEFT,GuessPString);
		SetDlgItemText(IDC_EDITGUESSP_RIGHT,GuessPString);
	}
	else{
		GetDlgItemText(IDC_EDITGUESSP_RIGHT,GuessPString);
		SetDlgItemText(IDC_EDITGUESSP_LEFT,GuessPString);
	}
	m_GuessP=setToStringValue(GuessPString,base);
}
