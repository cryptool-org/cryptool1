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

// RSAStereotypedMSGDlg.cpp : Implementierungsdatei 
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "RSAStereotypedMSGDlg.h"
#include "NTLExpPars.h"
#include "FileTools.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSAStereotypedMSGDlg Dialogfeld

CRSAStereotypedMSGDlg::CRSAStereotypedMSGDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRSAStereotypedMSGDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRSAStereotypedMSGDlg)
	m_baseOfCipher = 0;
	m_cipher = _T("");
	m_bitsOfN = 0;
	m_h = 4;
	m_N = _T("");
	m_e = _T("");
	m_choice = 0;
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRSAStereotypedMSGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRSAStereotypedMSGDlg)
	DDX_Control(pDX, IDC_SPINLENGTH, m_spinLengthControl);
	DDX_Control(pDX, IDC_SPINPOS, m_spinPosControl);
	DDX_Radio(pDX, IDC_RADIONUMBER, m_baseOfCipher);
	DDX_Text(pDX, IDC_EDITCIPHER, m_cipher);
	DDX_Text(pDX, IDC_EDITBITSOFN, m_bitsOfN);
	DDX_Text(pDX, IDC_EDITH, m_h);
	DDX_Text(pDX, IDC_EDITN, m_N);
	DDX_Text(pDX, IDC_EDITE, m_e);
	DDX_Radio(pDX, IDC_RADIOCHOICE, m_choice);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRSAStereotypedMSGDlg, CDialog)
	//{{AFX_MSG_MAP(CRSAStereotypedMSGDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDITPLAIN, OnChangeEditplain)
	ON_EN_CHANGE(IDC_EDITLENGTH, OnChangeEditlength)
	ON_EN_CHANGE(IDC_EDITPOS, OnChangeEditpos)
	ON_EN_CHANGE(IDC_EDITN, OnChangeEditn)
	ON_EN_CHANGE(IDC_EDITE, OnChangeEdite)
	ON_BN_CLICKED(IDC_BUTTONENCRYPT, OnButtonencrypt)
	ON_BN_CLICKED(IDC_RADIONUMBER, OnRadionumber)
	ON_BN_CLICKED(IDC_RADIOHEX, OnRadiohex)
	ON_EN_KILLFOCUS(IDC_EDITCIPHER, OnKillfocusEditcipher)
	ON_EN_CHANGE(IDC_EDITH, OnChangeEdith)
	ON_EN_UPDATE(IDC_EDITCIPHER, OnUpdateEditcipher)
	ON_BN_CLICKED(IDC_BUTTONSTART, OnButtonstart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTONCANCELATTACK, OnButtoncancelattack)
	ON_BN_CLICKED(IDC_RANDOM, OnRandom)
	ON_WM_SETCURSOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTONLOG, OnButtonlog)
	ON_BN_CLICKED(IDC_RADIOCHOICE, OnRadiochoice)
	ON_BN_CLICKED(IDC_BUTTONDELETE, OnButtondelete)
	ON_EN_CHANGE(IDC_EDITPLAINFULL, OnChangeEditplainfull)
	ON_EN_KILLFOCUS(IDC_EDITE, OnKillfocusEdite)
	ON_BN_CLICKED(IDC_RADIOCHOICE2, OnRadiochoice)
	ON_EN_KILLFOCUS(IDC_EDITN, OnKillfocusEditn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRSAStereotypedMSGDlg Nachrichten-Handler

BOOL CRSAStereotypedMSGDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	//OnRadiochoice();
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CRSAStereotypedMSGDlg::OnPaint() 
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

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CRSAStereotypedMSGDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


// When the plaintext is edited, the range of the spinbuttons must be
// adjusted and the preview must be updated.
void CRSAStereotypedMSGDlg::OnChangeEditplain() 
{

	updatePreview();
	checkParameters();
}

// This function gets called, when the preview has to be updated.
// This is the case, when either of the parameters N, e, plaintext,
// unknown position or unknown length changes.

void CRSAStereotypedMSGDlg::updatePreview()
{
	
	// Get the source information,...
	bool b=m_choice==0;
	CString tmp;	
	GetDlgItemText(IDC_EDITPLAIN, tmp);
	int pos=GetDlgItemInt(IDC_EDITPOS);
	int length=GetDlgItemInt(IDC_EDITLENGTH);
	

	CString preview;

	// ...cut it apart at the right position...
	CString left=tmp.Left(pos);
	CString right=tmp.Right(tmp.GetLength()-pos);
	// ... and make it fit.
	if(left.GetLength()>25){
		CString tmp="..."; 
		left=left.Right(22);
		left=tmp+left;
	}
	if(right.GetLength()>25)
		right=right.Left(22)+"...";
	// Put everything together again.
	preview=left;
	if(length>10)
		length=10;
	for(int i=0; i<length;i++)
		preview+="*";
	preview+=right;
	
	SetDlgItemText(IDC_EDITPREVIEW, preview);	
}

void CRSAStereotypedMSGDlg::OnChangeEditlength() 
{
	
	CString tmp;

	bool b=m_choice==0;

	GetDlgItemText(IDC_EDITPLAIN, tmp);

	int pos, length;
	pos=GetDlgItemInt(IDC_EDITPOS);
	length=GetDlgItemInt(IDC_EDITLENGTH);
	
	if(!b){
		CString fullPlainText;
		GetDlgItemText(IDC_EDITPLAINFULL, fullPlainText);
		int fullLenght = fullPlainText.GetLength();
		int maxLength = fullLenght;

		if(maxLength<length){
			length=maxLength;
			SetDlgItemInt(IDC_EDITLENGTH,length);
		}

		int maxPos=fullLenght-length;

		if(maxPos<pos){
			pos=maxPos;
			SetDlgItemInt(IDC_EDITPOS,pos);
		}


	fullPlainText.Delete(pos, length);
	SetDlgItemText(IDC_EDITPLAIN, fullPlainText);
	}

	updatePreview();
}

void CRSAStereotypedMSGDlg::OnChangeEditpos() 
{
	CString tmp;

	bool b=m_choice==0;

	GetDlgItemText(IDC_EDITPLAIN, tmp);

	int pos, length;
	pos=GetDlgItemInt(IDC_EDITPOS);
	length=GetDlgItemInt(IDC_EDITLENGTH);
	
	if(!b){
		CString fullPlainText;
		GetDlgItemText(IDC_EDITPLAINFULL, fullPlainText);
		int fullLenght = fullPlainText.GetLength();
		int maxPos=fullLenght;

		if(maxPos<pos){
			pos=maxPos;
			SetDlgItemInt(IDC_EDITPOS,pos);
		}

		int maxLength = fullLenght-pos;

		if(maxLength<length){
			length=maxLength;
			SetDlgItemInt(IDC_EDITLENGTH,length);
		}

		fullPlainText.Delete(pos, length);
		SetDlgItemText(IDC_EDITPLAIN, fullPlainText);
	}
	updatePreview();
}

void CRSAStereotypedMSGDlg::OnChangeEditn() 
{
	CheckEncryptButton();
	checkParameters();
}
// Check whether an encryption ist possible
void CRSAStereotypedMSGDlg::CheckEncryptButton()
{
	UpdateData();
	((CButton*)GetDlgItem(IDC_BUTTONENCRYPT))->EnableWindow(false);
	NTLExpPars myPars;
	ZZ N=myPars.parseExp(m_N);
	ZZ e=myPars.parseExp(m_e);
	if(N>0)
		if(e>0)
			((CButton*)GetDlgItem(IDC_BUTTONENCRYPT))->EnableWindow(true);
}
// Reads the String from an edit and converts it to NTL's ZZ (big integer).
ZZ CRSAStereotypedMSGDlg::GetDlgItemZZ(int ID, int base)
{
	CString tmp;
	GetDlgItemText(ID,tmp);
	return setToStringValue(tmp,base);
}

void CRSAStereotypedMSGDlg::OnChangeEdite() 
{
	CheckEncryptButton();
	checkParameters();
}

// Simple RSA encryption: m^e mod N, no padding.
void CRSAStereotypedMSGDlg::OnButtonencrypt() 
{
	UpdateData();
	ZZ cipher;
	ZZ plain=GetDlgItemZZ(IDC_EDITPLAINFULL,256);
	NTLExpPars myPars;
	ZZ N=myPars.parseExp(m_N);
	ZZ e=myPars.parseExp(m_e);
	
	// if the plaintext is to long, RSA encryption
	// does not work.
	int maxChars=NumBits(N)/8;
	if(plain>N){
		CString form, myTitle;
		this->GetWindowText(myTitle);
		form.Format(IDS_RSA_SM_MAXCHAR, maxChars);
		MessageBox(form, myTitle);
	}
	else{
		cipher=PowerMod(plain, e, N);
		UpdateData();
		if(m_baseOfCipher==0)
			SetDlgItemZZ(IDC_EDITCIPHER, cipher, 10,0);
		else
			SetDlgItemZZ(IDC_EDITCIPHER, cipher, 16,2);
		checkParameters();
	}
}
// function to set write the value of a ZZ into an edit box.
void CRSAStereotypedMSGDlg::SetDlgItemZZ(int ID, ZZ value, int base, int group)
{
	SetDlgItemText(ID, toString(value, base, group));
}

void CRSAStereotypedMSGDlg::OnRadionumber() 
{
	updateCipher();
}

void CRSAStereotypedMSGDlg::OnRadiohex() 
{
	updateCipher();
}
// This is caled, when the base of the cipertext is changed
// or user leaves the textbox. It makes sure, the input is
// valid and formatted
void CRSAStereotypedMSGDlg::updateCipher()
{
	int group=0; // determines the grouping of the figures
	int newbase=0;
	int oldbase = m_baseOfCipher;
	UpdateData();
	if(oldbase==0)
		oldbase=10;
	else
		oldbase=16;
	if(m_baseOfCipher==0)
		newbase=10;
	else{
		newbase=16;
		group=2;
	}
	m_cipher=toString(setToStringValue(m_cipher,oldbase),newbase,group);
	UpdateData(false);
}

void CRSAStereotypedMSGDlg::OnKillfocusEditcipher() 
{
	updateCipher();	
}

void CRSAStereotypedMSGDlg::OnChangeEdith() 
{
	checkParameters();
}


// This function checks, whether all parameters for the attack
// are right and enables or disables the start button.
void CRSAStereotypedMSGDlg::checkParameters()
{
	UpdateData();
	((CButton*)GetDlgItem(IDC_BUTTONSTART))->EnableWindow(false);
	StereotypedAttack sa;
	NTLExpPars myPars;
	sa.setN(myPars.parseExp(m_N));
	sa.setE(myPars.parseExp(m_e));
	sa.setH(GetDlgItemZZ(IDC_EDITH, 10));
	int cbase;
	if(m_baseOfCipher==0)
		cbase=10;
	else
		cbase=16;

	if(sa.getBound()>0){
		SetDlgItemZZ(IDC_EDITPOSLENGTH, to_ZZ(floor(log(sa.getBound())/log((double)256))),10,0);
		SetDlgItemInt(IDC_EDITDIM, GetDlgItemInt(IDC_EDITE)*GetDlgItemInt(IDC_EDITH));
		if(GetDlgItemZZ(IDC_EDITPLAIN,256)>0&&
			GetDlgItemZZ(IDC_EDITCIPHER,cbase)>0)
				((CButton*)GetDlgItem(IDC_BUTTONSTART))->EnableWindow(true);
	}else
		SetDlgItemInt(IDC_EDITPOSLENGTH, 0);
}

void CRSAStereotypedMSGDlg::OnUpdateEditcipher() 
{
	checkParameters();
}

void CRSAStereotypedMSGDlg::OnButtonstart() 
{
	
	SetDlgItemText(IDC_EDITSOLUTION, "");
	
	int cbase=10;
	int pos, length;
	if(m_baseOfCipher==1)
		cbase=16;
	
	CString tmp;
	GetDlgItemText(IDC_EDITPLAIN, tmp);
	if (power(GetDlgItemZZ(IDC_EDITPLAIN,256),GetDlgItemInt(IDC_EDITE)) // test, whether full plaintext known
		==GetDlgItemZZ(IDC_EDITCIPHER,cbase)){
		CString tmp, myTitle;
		tmp.LoadString(IDS_RSA_SM_FULLPLAIN);
		this->GetWindowText(myTitle);
		MessageBox(tmp,myTitle);
	} else {
	pos=GetDlgItemInt(IDC_EDITPOS);
	length=GetDlgItemInt(IDC_EDITLENGTH);
	int maxLength = GetDlgItemInt(IDC_EDITPOSLENGTH);
	if(length>maxLength){
		CString tmp, myTitle;
		tmp.LoadString(IDS_RSA_SM_UNKNOWNTOOBIG);
		this->GetWindowText(myTitle);
		MessageBox(tmp,myTitle);
	}
	
	sa.setRightText(setToStringValue(tmp.Right(tmp.GetLength()-pos),256));
	sa.setLeftText(setToStringValue(tmp.Left(pos),256));
	sa.setUnknownLength(length);
	sa.setN(GetDlgItemZZ(IDC_EDITN,10));
	sa.setE(GetDlgItemZZ(IDC_EDITE,10));
	sa.setH(GetDlgItemZZ(IDC_EDITH,10));
	sa.setCiphertext(GetDlgItemZZ(IDC_EDITCIPHER,cbase));
	
	enableDisable(false);
	GetDlgItem(IDC_BUTTONCANCELATTACK)->EnableWindow(true);
	GetDlgItem(IDC_BUTTONSTART)->EnableWindow(false);
	SetTimer(1, 1000, 0);
	pThread = AfxBeginThread (thrFunction, this);
}
}

void CRSAStereotypedMSGDlg::OnTimer(UINT nIDEvent) 
{
	// update and format overall elapsed time
	int elapsedTime=sa.getOverallTime();
	CString timeStr;
	timeStr.Format("%3dh%3dm%3ds",elapsedTime/3600,
		(elapsedTime/60)%60,(elapsedTime)%60);
	SetDlgItemText(IDC_EDITOVERALLTIME,timeStr);

	if(sa.status>SA_CANCELED){ // attack still running
		// update information
		CString t;
		int bLT=sa.getLatticeTime();
		t.Format("%3dh%3dm%3ds",bLT/3600,(bLT/60)%60,(bLT)%60);
		SetDlgItemText(IDC_EDITLATTICETIME,t);
		int rLT=sa.getReductionTime();
		t.Format("%3dh%3dm%3ds",rLT/3600,(rLT/60)%60,(rLT)%60);
		SetDlgItemText(IDC_EDITREDUCETIME,t);
		SetDlgItemInt(IDC_EDITREDUCTIONS,sa.reductions);
	}
	if(sa.status==SA_SUCCESSFUL){// finished successfully
		KillTimer(1);
		CString res=toString(sa.getSolution(),256,0);
		CString full;
		GetDlgItemText(IDC_EDITPLAIN, full);
		full.Insert(GetDlgItemInt(IDC_EDITPOS),res);
		SetDlgItemText(IDC_EDITSOLUTION, res);
		SetDlgItemText(IDC_EDITPLAINFULL, full);
		CString tmp, myTitle;
		tmp.LoadString(IDS_RSA_SM_SUCCESS);
		this->GetWindowText(myTitle);
		MessageBox(tmp,myTitle);
	}
	if(sa.status==SA_FAILED){// finished without success
		KillTimer(1);
		CString tmp, myTitle;
		tmp.LoadString(IDS_RSA_SM_NOSUCCESS);
		this->GetWindowText(myTitle);
		MessageBox(tmp,myTitle);
	}
	if(sa.status==SA_CANCELED||sa.status>SA_REDUCING){
		KillTimer(1);
		GetDlgItem(IDC_BUTTONSTART)->EnableWindow(true);
		GetDlgItem(IDC_BUTTONCANCELATTACK)->EnableWindow(false);
		enableDisable(true);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
	}
	CDialog::OnTimer(nIDEvent);
}
//////////////////////////////////////////////
// Function of the thread, calls the attack function of the 
// StereotypedAttack object.
//////////////////////////////////////////////
UINT CRSAStereotypedMSGDlg::thrFunction (LPVOID pParam){
	CRSAStereotypedMSGDlg* pDlg=(CRSAStereotypedMSGDlg*) pParam;
	pDlg->sa.attack();
	return 0;
}

void CRSAStereotypedMSGDlg::OnButtoncancelattack() 
{
	// make sure cancel is not pushed twice
	GetDlgItem(IDC_BUTTONCANCELATTACK)->EnableWindow(false);
	if(sa.status!=0) // is the attack running?
		sa.cancel();
	// wait until thread is really finished
	WaitForSingleObject(pThread->m_hThread, INFINITE);
}

void CRSAStereotypedMSGDlg::OnOK() 
{
	if(sa.status>SA_CANCELED&&sa.status<=SA_REDUCING){
		sa.cancel();
		WaitForSingleObject(pThread->m_hThread, INFINITE);
	}
	CDialog::OnCancel();
}

void CRSAStereotypedMSGDlg::OnRandom() 
{
	if (UpdateData()){
		if(m_bitsOfN<=10){
			CString tmp, myTitle;
			tmp.LoadString(IDS_RSA_SM_WRONGN);
			this->GetWindowText(myTitle);
			MessageBox(tmp,myTitle);
		}
		else{
			BeginWaitCursor();
			int bitsOfQ=m_bitsOfN/2;
			int bitsOfP=(m_bitsOfN+1)/2;
			SetSeed(to_ZZ(GetTime()*10000)); 
			ZZ p = GenPrime_ZZ(bitsOfP); // generate N, p and q
			ZZ q = GenPrime_ZZ(bitsOfQ);
			ZZ N = p*q;	
			SetDlgItemText(IDC_EDITN,toString(N,10,0));
			EndWaitCursor();
		}
	}
	OnChangeEditplainfull();
}

void CRSAStereotypedMSGDlg::enableDisable(bool b)
{
	GetDlgItem(IDC_EDITN)->EnableWindow(b);
	GetDlgItem(IDC_EDITE)->EnableWindow(b);
	GetDlgItem(IDC_EDITPLAIN)->EnableWindow(b);
	GetDlgItem(IDC_EDITPLAINFULL)->EnableWindow(b);
	GetDlgItem(IDC_EDITCIPHER)->EnableWindow(b);
	GetDlgItem(IDC_EDITPOS)->EnableWindow(b);
	GetDlgItem(IDC_EDITLENGTH)->EnableWindow(b);
	GetDlgItem(IDC_SPINPOS)->EnableWindow(b);
	GetDlgItem(IDC_SPINLENGTH)->EnableWindow(b);
	GetDlgItem(IDC_EDITH)->EnableWindow(b);
	GetDlgItem(IDC_RADIONUMBER)->EnableWindow(b);
	GetDlgItem(IDC_RADIOHEX)->EnableWindow(b);
	GetDlgItem(IDC_EDITBITSOFN)->EnableWindow(b);
	GetDlgItem(IDC_BUTTONENCRYPT)->EnableWindow(b);
	GetDlgItem(IDC_BUTTONDELETE)->EnableWindow(b);
	GetDlgItem(IDC_RANDOM)->EnableWindow(b);
}

BOOL CRSAStereotypedMSGDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(sa.status!=SA_CANCELED&&sa.status<=SA_REDUCING)
		SetCursor(LoadCursor(NULL, IDC_WAIT));
	else
		SetCursor(LoadCursor(NULL, IDC_ARROW));

	return TRUE;
}

void CRSAStereotypedMSGDlg::OnClose() 
{
	OnOK();
}

void CRSAStereotypedMSGDlg::OnButtonlog() 
{
	char *filename = new char[CRYPTOOL_PATH_LENGTH];
	GetTmpName(filename, "cry", ".txt");
	ofstream Outfile;
	Outfile.open(filename);
	Outfile << sa.Log;
	Outfile.close();

	CAppDocument *NewDoc = theApp.OpenDocumentFileNoMRU(filename);
	delete filename;
}

void CRSAStereotypedMSGDlg::OnRadiochoice() 
{
	UpdateData();
	bool b=m_choice==0;
	((CEdit*)GetDlgItem(IDC_EDITCIPHER))->SetReadOnly(!b);
	((CEdit*)GetDlgItem(IDC_EDITPLAIN))->SetReadOnly(!b);
	((CEdit*)GetDlgItem(IDC_EDITPLAINFULL))->SetReadOnly(b);

	SetDlgItemText(IDC_EDITCIPHER,"");
	SetDlgItemText(IDC_EDITPLAIN,"");
	SetDlgItemText(IDC_EDITPLAINFULL,"");
	SetDlgItemText(IDC_EDITPLAINLENGTH, "");
	
	
	SetDlgItemText(IDC_EDITPOS,"");
	SetDlgItemText(IDC_EDITLENGTH,"");
	GetDlgItem(IDC_BUTTONENCRYPT)->ShowWindow(!b);
	GetDlgItem(IDC_BUTTONDELETE)->ShowWindow(!b);
	GetDlgItem(IDC_STATIC_ENTER_KNOWN)->ShowWindow(b);
	GetDlgItem(IDC_STATIC_SHOW_KNOWN)->ShowWindow(!b);
	GetDlgItem(IDC_STATIC_ENTER_POS)->ShowWindow(b);
	GetDlgItem(IDC_STATIC_HIGHLIGHT_POS)->ShowWindow(!b);
	GetDlgItem(IDC_EDITPLAINLENGTH)->ShowWindow(!b);
	GetDlgItem(IDC_PTLENGTH)->ShowWindow(!b);
	GetDlgItem(IDC_STATIC_PLAINTEXT)->ShowWindow(!b);
	GetDlgItem(IDC_EDITPLAINFULL)->ShowWindow(!b);
	GetDlgItem(IDC_BUTTONENCRYPT)->ShowWindow(!b);
	
	UpdateSliders();
}

void CRSAStereotypedMSGDlg::OnButtondelete() 
{
	int start, end;
	((CEdit*)GetDlgItem(IDC_EDITPLAINFULL))->GetSel(start, end);
	if(start+end==0){
			CString tmp, myTitle;
			tmp.LoadString(IDS_RSA_SM_PLEASEHIGHLIGHT);
			this->GetWindowText(myTitle);
			MessageBox(tmp,myTitle);
		}
	else{
		if(end-start==0){
			CString tmp, myTitle;
			tmp.LoadString(IDS_RSA_SM_ALLKNOWN);
			this->GetWindowText(myTitle);
			MessageBox(tmp,myTitle);
		}
		CString incomplete;
		GetDlgItemText(IDC_EDITPLAINFULL, incomplete);
		incomplete.Delete(start, end-start);
		
		SetDlgItemText(IDC_EDITPLAIN,incomplete);
		SetDlgItemInt(IDC_EDITPOS, start);
		SetDlgItemInt(IDC_EDITLENGTH, end-start);
		checkParameters();
		updatePreview();
	}
}


void CRSAStereotypedMSGDlg::UpdateSliders(){
	
	CString tmp;

	bool b=m_choice==0;

	GetDlgItemText(IDC_EDITPLAIN, tmp);

	int pos, length;
	pos=GetDlgItemInt(IDC_EDITPOS);
	length=GetDlgItemInt(IDC_EDITLENGTH);
	
	if(!b){
		CString fullPlainText;
		GetDlgItemText(IDC_EDITPLAINFULL, fullPlainText);
		int fullLenght = fullPlainText.GetLength();
		int maxPos=fullLenght;
		int maxLength = fullLenght;

		if(maxPos<pos){
			pos=maxPos;
			SetDlgItemInt(IDC_EDITPOS,pos);
		}

		if(maxLength<length){
			length=maxLength;
			SetDlgItemInt(IDC_EDITLENGTH,length);
		}

		(( CSpinButtonCtrl* )GetDlgItem( IDC_SPINPOS ))->SetRange(0,maxPos);
		(( CSpinButtonCtrl* )GetDlgItem( IDC_SPINLENGTH ))->SetRange(0,maxLength);
		
		//fullPlainText.Delete(pos, length);
		//SetDlgItemText(IDC_EDITPLAIN, fullPlainText);

	}else{
		int knownlenght=tmp.GetLength();

		m_spinLengthControl.SetRange32(0,32000);
		m_spinPosControl.SetRange32(0,knownlenght);
	}

}

void CRSAStereotypedMSGDlg::OnChangeEditplainfull() 
{
	ZZ plain=GetDlgItemZZ(IDC_EDITPLAINFULL,256);
	NTLExpPars myPars;
	ZZ N=myPars.parseExp(m_N);
	CString tmp;
	GetDlgItemText(IDC_EDITPLAINFULL,tmp);
	CString chars;
	ZZ MaxChars ;
	if(N>0)
		MaxChars = to_ZZ(floor(log(N+255)/log(256.0)));
	else
		MaxChars = 0;
	chars.Format("%d(%s)",tmp.GetLength(),toString(MaxChars,10,0));
	SetDlgItemText(IDC_EDITPLAINLENGTH,chars);
	SetDlgItemText(IDC_EDITCIPHER,"");
	UpdateSliders();
	updatePreview();
}

void CRSAStereotypedMSGDlg::OnKillfocusEdite() 
{
	UpdateData();
	NTLExpPars myPars;
	ZZ e=myPars.parseExp(m_e);
	m_e=toString(e,10,0);
	UpdateData(false);
}

void CRSAStereotypedMSGDlg::OnKillfocusEditn() 
{
	UpdateData();
	NTLExpPars myPars;
	ZZ N=myPars.parseExp(m_N);
	m_N=toString(N,10,0);
	UpdateData(false);
}
