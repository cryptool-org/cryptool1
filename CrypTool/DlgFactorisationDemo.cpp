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

// DlgTutorialFactorisation.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgFactorisationDemo.h"
#include "IntegerArithmetic.h"
#include "DlgProgressFactorisation.h"
#include "DialogeMessage.h"


#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFactorisationDemo 

CDlgFactorisationDemo::CDlgFactorisationDemo(CWnd* pParent)
	: CDialog(CDlgFactorisationDemo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFactorisationDemo)
	m_CompositeNoStr = _T("");
	m_bruteForce = TRUE;
	m_Brent = TRUE;
	m_Pollard = TRUE;
	m_Williams = TRUE;
	m_Lenstra = TRUE;
	m_QSieve = TRUE;
	m_Factorisation = _T("");
	m_Name = _T("");
	m_benoetigte_zeit_global = _T("");
	m_benoetigte_zeit_pro_factorisation = _T("");
	//}}AFX_DATA_INIT
	factorList = 0;
	duration1 = 0;
	duration2 = 0;
	m_inputReadOnly = 0;
}

CDlgFactorisationDemo::~CDlgFactorisationDemo()
{
	while ( factorList != 0 )
	{
		NumFactor *tmp = factorList;
		factorList = factorList->next;
		delete tmp;
	}
}


void CDlgFactorisationDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFactorisationDemo)
	DDX_Control(pDX, IDC_BUTTON1, m_DialogeDetails);
	DDX_Control(pDX, IDC_CHECK1, m_bruteForceCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_CompositeNoCtrl);
	DDX_Control(pDX, IDC_BUTTON_VOLLSTAENDIG_FAKTORISATION, m_vollstaendig);
	DDX_Control(pDX, IDC_BUTTON_Faktorisieren, m_weiter);
	DDX_Control(pDX, IDC_RICHEDIT2, m_FactorisationCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_CompositeNoStr);
	DDX_Check(pDX, IDC_CHECK1, m_bruteForce);
	DDX_Check(pDX, IDC_CHECK2, m_Brent);
	DDX_Check(pDX, IDC_CHECK3, m_Pollard);
	DDX_Check(pDX, IDC_CHECK4, m_Williams);
	DDX_Check(pDX, IDC_CHECK5, m_Lenstra);
	DDX_Check(pDX, IDC_CHECK6, m_QSieve);
	DDX_Text(pDX, IDC_RICHEDIT2, m_Factorisation);
	DDX_Text(pDX, IDC_EDIT2, m_Name);
	DDX_Text(pDX, IDS_STRING_BENOETIGTE_ZEIT_FAKT, m_benoetigte_zeit_global);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFactorisationDemo, CDialog)
	//{{AFX_MSG_MAP(CDlgFactorisationDemo)
	ON_BN_CLICKED(IDC_BUTTON_cancel, OnButtonEnd)
	ON_BN_CLICKED(IDC_BUTTON_Faktorisieren, OnButtonFactorisation)
	ON_BN_CLICKED(IDC_BUTTON_VOLLSTAENDIG_FAKTORISATION, OnButtonVollstaendigFaktorisation)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEditEingabe)
	ON_BN_CLICKED(IDC_BUTTON1, OnShowFactorisationDetails)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_NUMBER, OnBnClickedLoadNumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgFactorisationDemo 

void CDlgFactorisationDemo::OnButtonEnd() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////////////
CDlgProgressFactorisation dlg;


UINT singleThreadBrent( PVOID x )
{
	CTutorialFactorisation *f;
	f = (CTutorialFactorisation*)x;
	BOOL ret = f->Brent();
	return 0;
}

UINT singleThreadPollard( PVOID x )
{
	CTutorialFactorisation *f;
	f = (CTutorialFactorisation*)x;
	BOOL ret = f->Pollard();
	return 0;
}

UINT singleThreadWilliams( PVOID x )
{
	CTutorialFactorisation *f;
	f = (CTutorialFactorisation*)x;
	BOOL ret = f->Williams();
	return 0;
}

UINT singleThreadLenstra( PVOID x )
{
	CTutorialFactorisation *f;
	f = (CTutorialFactorisation*)x;
	BOOL ret = f->Lenstra();
	return 0;
}

UINT singleThreadQuadraticSieve( PVOID x )
{
	CTutorialFactorisation *f;
	f = (CTutorialFactorisation*)x;
	BOOL ret = f->QuadraticSieve();
	return 0;
}


void CDlgFactorisationDemo::OnButtonFactorisation() 
{
	int i, started;
	CString name;


	// differ between English and German version ("quadratisches Sieb" <-> "quadratic sieve")
	LoadString(AfxGetInstanceHandle(), IDS_QUADRATIC_SIEVE, pc_str, STR_LAENGE_STRING_TABLE);
	CTutorialFactorisation Brent(0,"Brent"), Pollard(1,"Pollard"), 
			Williams(2,"Williams"), Lenstra(3,"Lenstra"), QSieve(4, pc_str);

//	Da man die gesamte Laufzeit braucht, wurden die folgenden Deklaration global gemacht!!
//	clock_t FactStart;
//	clock_t FactFinish;
//	double duration;

	UpdateData(TRUE);
	CString UpnFormula;
	int err_ndx;
	BOOL error;
	error = CheckFormula(m_CompositeNoStr,10,UpnFormula,err_ndx);
	if (error==0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_CompositeNoCtrl.SetSel(err_ndx-1,m_CompositeNoStr.GetLength());
		m_CompositeNoCtrl.SetFocus();
		Message(IDS_STRING_INPUT_FALSE, MB_ICONEXCLAMATION);
		// flomar, October 2012: the new 'single go' implementation
		dlg.abortFactorizationInOneGo();
		return;
	}

	int laenge_eingabe;
	laenge_eingabe = m_CompositeNoStr.GetLength();
	
	if ( laenge_eingabe )
	{
		m_weiter.EnableWindow(true);
		m_vollstaendig.EnableWindow(true);	
	}
	
	CString next_factor = Search_First_Composite_Factor();
		
	// Falls noch zusammengesetzten Faktoren die eingegebene Zahl teilen:
	if (next_factor!="lolo")
	{
		int Out_SetN = f.SetN(next_factor);
		int bitlength_next_factor = f.bitlength();
		if (Out_SetN==EVAL_NULL || Out_SetN==EVAL_EINS)
		{
			//Sie müssen eine ganze Zahl eingeben, die von 0 und 1 verschieden ist.
			m_CompositeNoCtrl.SetSel(0,-1);
			m_CompositeNoCtrl.SetFocus();
			Message(IDS_STRING_FAKTORISATION_NOT_NULL_OR_ONE, MB_ICONEXCLAMATION);
			// flomar, October 2012: the new 'single go' implementation
			dlg.abortFactorizationInOneGo();
			return;

		}
		if (Out_SetN==EVAL_OK)
		{
			BOOL factorized = FALSE;
			CString f1, f2;

			SHOW_HOUR_GLASS			// aktiviert die Sanduhr
			if (!m_bruteForce && !m_Brent && !m_Pollard && !m_Williams && !m_Lenstra && !m_QSieve)
			{
				//Sie müssen mindestens ein Verfahren wählen!
				Message(IDS_STRING_FAKTORISATION_VERFAHREN, MB_ICONEXCLAMATION);
				// flomar, October 2012: the new 'single go' implementation
				dlg.abortFactorizationInOneGo();
				return;
			}
			if ( f.IsPrime(next_factor) )
			{// Die eingegebene Zahl ist eine Primzahl
				Message(IDS_STRING_FAKTORISATION_PRIMZAHL, MB_ICONEXCLAMATION);
				// flomar, October 2012: the new 'single go' implementation
				dlg.abortFactorizationInOneGo();
				return;
			}
			
			FactStart = clock();

			if ( !factorized && m_bruteForce )
			{
				CTutorialFactorisation fact;
				fact.SetN(next_factor);
				if ( TRUE == (factorized = fact.BruteForce()) )
				{
					fact.GetFactor1Str( f1 );
					fact.GetFactor2Str( f2 );
					name = "Brute Force";
				}
			}

			if (next_factor.GetLength()>21)
			{
				dlg.m_zahl=_T("");
				dlg.m_zahl.Insert(0, next_factor.Mid(0,9));
				dlg.m_zahl += CString("...");
				dlg.m_zahl += next_factor.Right(9);				
			}
			else
			{
				dlg.m_zahl=_T("");
				dlg.m_zahl=next_factor;
			}
			dlg.m_curThread = 0;
			dlg.m_numThreads = 0;
			dlg.m_displayed = 0;
			dlg.m_OldThread = -1;
			dlg.m_registeredThreads = 0;
			dlg.m_retcode = IDCANCEL;
			dlg.m_Factorisations[0] = &Brent;
			dlg.m_Factorisations[1] = &Pollard;
			dlg.m_Factorisations[2] = &Williams;
			dlg.m_Factorisations[3] = &Lenstra;
			dlg.m_Factorisations[4] = &QSieve;

			for(i=0;i<5;i++) {
				dlg.m_Factorisations[i]->m_iterations = 0;
				dlg.m_Factorisations[i]->factorized = 0;
				dlg.m_Factorisations[i]->status = 0;
				dlg.m_Factorisations[i]->SetN(next_factor);
			}

			started = 0;
			if ( !factorized && m_Brent )
			{
				Brent.m_Thread = AfxBeginThread( singleThreadBrent, PVOID(&Brent) );
				started++;
			}
			if ( !factorized && m_Pollard )
			{
				Pollard.m_Thread = AfxBeginThread( singleThreadPollard, PVOID(&Pollard) );
				started++;
			}

			if ( !factorized && m_Williams )
			{
				Williams.m_Thread = AfxBeginThread( singleThreadWilliams, PVOID(&Williams) );
				started++;
			}

			if ( !factorized && m_Lenstra )
			{
				Lenstra.m_Thread = AfxBeginThread( singleThreadLenstra, PVOID(&Lenstra) );
				started++;
			}
			
			if ( !factorized && m_QSieve )
			{
				if ( 132 < bitlength_next_factor*log(2.0)/log(10.0) )
				{
					Message(IDS_FACTORISATION_OVERFLOW, MB_ICONEXCLAMATION);
					UpdateData();
					m_QSieve = 0;
					UpdateData(FALSE);
				} 
				else if ( 93 < bitlength_next_factor*log(2.0)/log(10.0) )
				{
					LoadString(AfxGetInstanceHandle(),IDS_FACTORISATION_MEMORY_REQUEST,pc_str,STR_LAENGE_STRING_TABLE);
					if ( IDNO == MessageBox(pc_str, NULL, MB_YESNO) )
					{
						QSieve.m_Thread = AfxBeginThread( singleThreadQuadraticSieve, PVOID(&QSieve) );
						started++;
					}
					else
					{
						UpdateData();
						m_QSieve = 0;
						UpdateData(FALSE);
					}
				}
				else
				{
					QSieve.m_Thread = AfxBeginThread( singleThreadQuadraticSieve, PVOID(&QSieve) );
					started++;
				}
			}

			bool l_factorisation_aborted = false;
			int  l_dlg_return;

			dlg.m_totalThreads = started;
			LoadString(AfxGetInstanceHandle(),IDS_STRING_FACTORISATION_TIMER,pc_str,STR_LAENGE_STRING_TABLE);
			dlg.SetCaption(pc_str);
			if ( started && IDOK != (l_dlg_return = dlg.DoModal()) )
			{
				if (l_dlg_return == IDCANCEL) l_factorisation_aborted = true;
				// flomar, October 2012: the new 'single go' implementation
				dlg.abortFactorizationInOneGo();
			}

			for(i=0;i<5;i++) {
				if(dlg.m_Factorisations[i]->factorized) {
					factorized = TRUE;
					name = dlg.m_Factorisations[i]->m_Name;
					dlg.m_Factorisations[i]->GetFactor1Str( f1 );
					dlg.m_Factorisations[i]->GetFactor2Str( f2 );
				}
			}

			
			if ( factorized )
			{
				expandFactorisation( next_factor, f1, f2 );
				m_Name = name;
			}
			else if ( l_factorisation_aborted )
				{
					Message(IDS_STRING_FAKTORISATION_ABORTED, MB_ICONEXCLAMATION);
					// flomar, October 2012: the new 'single go' implementation
					dlg.abortFactorizationInOneGo();
				}
				// Hier wird man angefordert mit einem anderen Algorithmus zu arbeiten!!
				else
				{
					// special case: if the user selected only the brute-force method,
					// tell him about the limit up to which this method is looking for primes
					if(	m_bruteForce == TRUE && m_Brent == FALSE && m_Pollard == FALSE && 
							m_Williams == FALSE && m_Lenstra == FALSE && m_QSieve == FALSE) {
						char bruteForcePrimeLimit[2048];
						memset(bruteForcePrimeLimit, 0, 2048);
						LoadString(AfxGetInstanceHandle(),IDS_STRING_FACTORIZATION_BRUTE_FORCE_LIMIT,pc_str,STR_LAENGE_STRING_TABLE);
						sprintf(bruteForcePrimeLimit, pc_str, LIMIT1);
						AfxMessageBox(bruteForcePrimeLimit, MB_ICONEXCLAMATION);
						//m_Name = "";
					}
					else {
						// this is the normal "use another algorithm" notification
						Message(IDS_STRING_FAKTORISATION_NEU_WAEHLEN, MB_ICONEXCLAMATION);
						// flomar, October 2012: the new 'single go' implementation
						dlg.abortFactorizationInOneGo();
				}
			}

			FactFinish = clock();
			duration1 =((double) (FactFinish - FactStart) / CLOCKS_PER_SEC) + duration1; //gesamte Laufzeit
			duration2 =((double) (FactFinish - FactStart) / CLOCKS_PER_SEC) ; //einzelne Laufzeit
			
			double temp;
			modf(duration1,&temp);
			zeit_condtruct1.day= (int) floor(temp/86400);
			zeit_condtruct1.hour= (int) floor((temp - zeit_condtruct1.day*86400)/3600);
			zeit_condtruct1.min= (int) floor((temp - zeit_condtruct1.day*86400- zeit_condtruct1.hour*3600)/60);
			zeit_condtruct1.sec= (int) (temp - zeit_condtruct1.day*86400- zeit_condtruct1.hour*3600-zeit_condtruct1.min*60);
			zeit_condtruct1.msec= (int) floor((duration1-temp)*1000);
			
			modf(duration2,&temp);
			zeit_condtruct2.day= (int) floor(temp/86400);
			zeit_condtruct2.hour= (int) floor((temp - zeit_condtruct2.day*86400)/3600);
			zeit_condtruct2.min= (int) floor((temp - zeit_condtruct2.day*86400- zeit_condtruct2.hour*3600)/60);
			zeit_condtruct2.sec= (int) (temp - zeit_condtruct2.day*86400- zeit_condtruct2.hour*3600-zeit_condtruct2.min*60);
			zeit_condtruct2.msec= (int) floor((duration2-temp)*1000);
			
			char line2[256], timeStr2[64];
			CString timeStr1;
			
			if ( zeit_condtruct1.day >= 1)
				timeStr1.Format(IDS_STRING_FMT_DAYS, zeit_condtruct1.day,zeit_condtruct1.hour, zeit_condtruct1.min,zeit_condtruct1.sec);
			else if (zeit_condtruct1.hour >= 1)
				timeStr1.Format(IDS_STRING_FMT_HRS, zeit_condtruct1.hour, zeit_condtruct1.min,zeit_condtruct1.sec);
			else if (zeit_condtruct1.min >= 1)
				timeStr1.Format(IDS_STRING_FMT_MIN, zeit_condtruct1.min,zeit_condtruct1.sec);
			else
				timeStr1.Format(IDS_STRING_FMT_SEC, zeit_condtruct1.sec, zeit_condtruct1.msec);
			timeStr1.TrimLeft();
			int nfactors = 0;
			for (NumFactor *factor = factorList; factor ; factor = factor->next)
				nfactors += factor->exponent;
			m_benoetigte_zeit_global.Format(IDS_FACTORS_FOUND, nfactors, timeStr1);
			if ( zeit_condtruct2.day >= 1)
			{	
				LoadString(AfxGetInstanceHandle(),IDS_STRING_FMT_DAYS,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(timeStr2,pc_str, zeit_condtruct2.day,zeit_condtruct2.hour, zeit_condtruct2.min,zeit_condtruct2.sec);
			}
			else if (zeit_condtruct2.hour >= 1)
			{	
				LoadString(AfxGetInstanceHandle(),IDS_STRING_FMT_HRS,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(timeStr2,pc_str, zeit_condtruct2.hour, zeit_condtruct2.min,zeit_condtruct2.sec);
			}
			else if (zeit_condtruct2.min >= 1)
			{	
				LoadString(AfxGetInstanceHandle(),IDS_STRING_FMT_MIN,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(timeStr2,pc_str, zeit_condtruct2.min,zeit_condtruct2.sec);
			}
			else
			{	
				LoadString(AfxGetInstanceHandle(),IDS_STRING_FMT_SEC,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(timeStr2,pc_str, zeit_condtruct2.sec, zeit_condtruct2.msec);
			}
			
			LoadString(AfxGetInstanceHandle(),IDS_STRING_BENOETIGTE_ZEIT_FAKT,pc_str,STR_LAENGE_STRING_TABLE);		
			sprintf( line2, pc_str, timeStr2 );
			m_benoetigte_zeit_pro_factorisation=timeStr2;
						
			HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
			UpdateData(FALSE);
			Set_NonPrime_Factor_Red();
			if ( factorized )
			{
				DetailsFactorisation.InsertFactDetail(next_factor, f1, f2, 
					                                  m_Name, m_benoetigte_zeit_pro_factorisation, 
													  (int)f.IsPrime( f1 ) + ((int)f.IsPrime(f2))*2,
													  (int)ceil(BitLength(f1)), (int)ceil(BitLength(f2)));
				m_DialogeDetails.EnableWindow();
			}
			else 
			{
				if ( l_factorisation_aborted )
				{
					LoadString(AfxGetInstanceHandle(),IDS_STRING_FAKTORISATION_ABORT_MSG,pc_str,STR_LAENGE_STRING_TABLE);		
				}
				else
				{
					LoadString(AfxGetInstanceHandle(),IDS_STRING_FAKTORISATION_STOP_MSG,pc_str,STR_LAENGE_STRING_TABLE);
				}
				DetailsFactorisation.InsertFactDetail(next_factor, CString(""), CString(""), CString(pc_str), 
					                                  m_benoetigte_zeit_pro_factorisation, 
													  0, 0, 0);
				m_DialogeDetails.EnableWindow();
			}
		}
		else if(Out_SetN == EVAL_NEG)
		{
			// Falsche Eingabe: Eingabe ist keine positive ganze Zahl
			m_CompositeNoCtrl.SetSel(0,-1);
			m_CompositeNoCtrl.SetFocus();
			Message(IDS_STRING_FAKTORISATION_FALSCHE_EINGABE, MB_ICONEXCLAMATION);			
			// flomar, October 2012: the new 'single go' implementation
			dlg.abortFactorizationInOneGo();
		}
		else
		{
			// Eingabe ist zu groß (1024-bit); wird nicht von der Demo unterstützt.
			m_CompositeNoCtrl.SetSel(0,-1);
			m_CompositeNoCtrl.SetFocus();
			Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
			// flomar, October 2012: the new 'single go' implementation
			dlg.abortFactorizationInOneGo();
		}
	}
	
	// Die Zahl ist jetzt vollständig faktorisiert
	else
	{
		m_weiter.EnableWindow(false);
		m_vollstaendig.EnableWindow(false);	
		Message(IDS_STRING_FAKTORISATION_VOLLSTAENDIG, MB_ICONINFORMATION);
	}
}

/*
BOOL IsSmallerNumStr( CString &NumStr1, CString &NumStr2 )
{
	
}
*/

void CDlgFactorisationDemo::expandFactorisation(CString &composite, CString &f1, CString &f2)
{
	long expFactor = 1;
	if ( factorList )
	{ // 1. delete composite
		NumFactor * ndx = factorList;
		if ( 0 != ndx && ndx->factorStr == composite )
		{
			expFactor = ndx->exponent;
			factorList = ndx->next;
			delete ndx;
		}
		else
		{
			if ( 0 != ndx  ) 
				while ( 0 != ndx->next && ndx->next->factorStr != composite ) ndx = ndx->next;
			if ( ndx->next && ndx->next->factorStr == composite )
			{	
				expFactor = ndx->next->exponent;
				NumFactor *toDel = ndx->next;
				ndx->next = ndx->next->next;
				delete toDel;
			}
		}
	}
	{ // 2. insert first factor
		NumFactor * ndx = factorList;
		if ( 0 == ndx )
		{
			factorList = new NumFactor;
			factorList->exponent = expFactor;
			factorList->factorStr = f1;
			factorList->isPrime = f.IsPrime( f1 );
			factorList->next = 0;
		}
		else
		{
			if ( ndx->factorStr.GetLength() > f1.GetLength() || 
			    (ndx->factorStr.GetLength() == f1.GetLength() && ndx->factorStr > f1) )
			{
				factorList = new NumFactor;
				factorList->exponent = expFactor;
				factorList->factorStr = f1;
				factorList->isPrime = f.IsPrime( f1 );
				factorList->next = ndx;
			}
			else if ( ndx->factorStr == f1 )
			{
				factorList->exponent = factorList->exponent + expFactor;
			}
			else
			{
				while ( 0 != ndx->next && ( (ndx->next->factorStr.GetLength() < f1.GetLength()) ||
					  (ndx->next->factorStr.GetLength() == f1.GetLength() && ndx->next->factorStr < f1) ) ) 
					      ndx = ndx->next;
				if ( ndx->next && ndx->next->factorStr == f1 ) ndx->next->exponent = ndx->next->exponent + expFactor;
				else
				{
					NumFactor * insFactor = new NumFactor;
					insFactor->exponent = expFactor;
					insFactor->factorStr = f1;
					insFactor->isPrime = f.IsPrime( f1 );
					insFactor->next = ndx->next;
					ndx->next = insFactor;
				}
			}
		}
	}
	{ // 3. insert second factor
		NumFactor * ndx = factorList;
			if ( ndx->factorStr.GetLength() > f2.GetLength() || 
			    (ndx->factorStr.GetLength() == f2.GetLength() && ndx->factorStr > f2) )
		{
			factorList = new NumFactor;
			factorList->exponent = expFactor;
			factorList->factorStr = f2;
			factorList->isPrime = f.IsPrime( f2 );
			factorList->next = ndx;
		}
		else if ( ndx->factorStr == f2 && ndx->isPrime ==0)
		{
//			Roger 30.10.2001
//			factorList->exponent++;
			factorList->exponent= factorList->exponent + expFactor;
		}
		else if ( ndx->factorStr == f2 && ndx->isPrime ==1)
		{
//			Roger 30.10.2001
			factorList->exponent = factorList->exponent + expFactor;
//			factorList->exponent= (factorList->exponent)*2;
		}
		else
		{
			while ( 0 != ndx->next && ( (ndx->next->factorStr.GetLength() < f2.GetLength()) ||
				  (ndx->next->factorStr.GetLength() == f2.GetLength() && ndx->next->factorStr < f2) ) ) 
					  ndx = ndx->next;
			if ( ndx->next && ndx->next->factorStr == f2 ) ndx->next->exponent = ndx->next->exponent + expFactor;
			else
			{
				NumFactor * insFactor = new NumFactor;
				insFactor->exponent = expFactor;
				insFactor->factorStr = f2;
				insFactor->isPrime = f.IsPrime( f2 );
				insFactor->next = ndx->next;
				ndx->next = insFactor;
			}
		}
	}
	{ // 4. Print actual factorisation
		m_Factorisation = _T("");
		NumFactor * ndx = factorList;
		while ( ndx )
		{
			m_Factorisation += ndx->factorStr.GetBuffer(128);
			if ( ndx->exponent > 1 )
			{
				char tmpStr[20]; sprintf(tmpStr,"^%i", ndx->exponent);
				m_Factorisation += tmpStr;
			}
			if ( ndx->next )
			{	
				m_Factorisation += " * ";
			}
			ndx = ndx->next;
		}
	}

}


void CDlgFactorisationDemo::Set_NonPrime_Factor_Red()
{
	CHARFORMAT cf;
	// flomar, 09/06/2012: don't forget to initialize the struct properly, otherwise we 
	// may encounter weird behavior under VS2010; for some reason VS2008 seems to be fine 
	// even without explicitly initializing everything to zero
	memset(&cf, 0, sizeof(cf));
	// go on as usual...
	cf.cbSize = sizeof (CHARFORMAT);
	cf.dwMask= CFM_COLOR;//
	cf.crTextColor =RGB(0,0,0);
	m_FactorisationCtrl.SetSel(0,-1);
	m_FactorisationCtrl.SetSelectionCharFormat(cf);
	
	NumFactor *ndx = factorList;
	if ( !ndx ) return;
	int anfang = 0, ende = 0, expLen;
	int firstcomposite = -1;
	while ( ndx )
	{
		if ( ndx->exponent > 1 ) 
		{
			// Beginn Bugfix Jan Blumenstein (JB)

			expLen = (int)floor(log(double(ndx->exponent))/log(10.0))+2;
			//expLen = ceil(log(double(ndx->exponent))/log(10.0))+1;	// falsch, wenn ndx->exponent = 10, 100, 1000, ...

			// Ende Bugfix JB
		}
		else
		{
			expLen = 0;
		}
		ende = anfang + ndx->factorStr.GetLength();
		// Markiere Text ....
		if ( !ndx->isPrime )
		{
			cf.cbSize = sizeof (CHARFORMAT);
			cf.dwMask= CFM_COLOR;
			cf.crTextColor =RGB(255,0,0);
			m_FactorisationCtrl.SetSel(anfang, ende);
			m_FactorisationCtrl.SetSelectionCharFormat(cf);
			if (firstcomposite == -1)
				firstcomposite = anfang;
		}
		ndx = ndx->next;
		anfang = ende + 3 + expLen;
	}
	
	// scroll to first composite factor (or to the beginning if completely factorized)
	m_FactorisationCtrl.HideSelection(FALSE,TRUE);
	if (firstcomposite == -1)
		firstcomposite = 0;
	m_FactorisationCtrl.SetSel(firstcomposite, firstcomposite);	


}

CString CDlgFactorisationDemo::Search_First_Composite_Factor()
{
	NumFactor *ndx = factorList;
	if ( !ndx ) return m_CompositeNoStr;
	while ( ndx )
	{
		if ( !ndx->isPrime )
		{
			return ndx->factorStr;
		}
		ndx = ndx->next;
	}
	return "lolo";
}

void CDlgFactorisationDemo::OnButtonVollstaendigFaktorisation() 
{
	// flomar, October 2012: belated implementation of 'factorize all'
	// functionality; the solution is quite hackish; essentially, what 
	// I'm doing is this: initialize the 'dlg' object so that an internal 
	// 'aborted' variable is set to false; after that I repeatedly call 
	// the function 'OnButtonFaktorisieren' to factorize the current 
	// composite factor-- whenever an error occurs or the user cancels 
	// the factorization, the 'aborted' variable is set to true by 
	// calling the function 'dlg.abortFactorizationInOneGo()', which 
	// in turn will break the main factorization loop; after countless 
	// hours of debugging and getting familiar with the existing code 
	// base for the 'single go' approach I decided to do it this 
	// way; in case you like pain, feel free to re-write it...

	// get the initial composite factor
	CString initialCompositeFactor = Search_First_Composite_Factor();
	// initialize control variable for our loop
	dlg.startFactorizationInOneGo();
	// this while loop repeatedly runs the "factorize" function until 
	// either the composite factor is completey factorized (nice 
	// 'keyword' BTW), or the factorization was aborted/cancelled
	while(Search_First_Composite_Factor() != "lolo" && !dlg.wasFactorizationInOneGoAborted()) {
		OnButtonFactorisation();
	}
	// this trailing call to "factorize" will automatically prompt 
	// the user with the factorization result and internally disable 
	// the "factorize" and "factorize all" buttons (this becomes 
	// effective only if the factorization was not aborted)
	if(!dlg.wasFactorizationInOneGoAborted()) {
		OnButtonFactorisation();
	}
}

BOOL CDlgFactorisationDemo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_weiter.EnableWindow(false);
	// TODO: Zusätzliche Initialisierung hier einfügen
	m_vollstaendig.EnableWindow(false);
		// Initialisiere die Schlüsselliste mit allen verfügbaren asymmetrischen Schlüsseln
	m_bruteForceCtrl.SetCheck(1);
	if ( m_CompositeNoStr.GetLength() )
	{
		m_weiter.EnableWindow(true);
		m_weiter.SetFocus();
	}
	if ( !factorList )
	{
		m_DialogeDetails.EnableWindow(FALSE);
	}
	if ( m_inputReadOnly )
	{
		m_CompositeNoCtrl.SetReadOnly(TRUE);
		m_weiter.SetFocus();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgFactorisationDemo::InitialiseFactorList()
{
	m_Factorisation = "";
	m_benoetigte_zeit_global="";
	m_benoetigte_zeit_pro_factorisation="";
	duration1=0;
	duration2=0;
	while ( factorList != 0 )
	{
		NumFactor *tmp = factorList;
		factorList = factorList->next;
		delete tmp;
	}
	factorList = 0;
	DetailsFactorisation.ClearFactDetail();	
	m_Name = ""; 
}

void CDlgFactorisationDemo::OnUpdateEditEingabe() 
{
	
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(TRUE); // get the displayed value in m_text 
	m_CompositeNoCtrl.GetSel(sels, sele);
	
	CheckEdit(m_CompositeNoStr,sels,sele);

	res.Empty();

	if(theApp.TextOptions.getIgnoreCase()) m_CompositeNoStr.MakeUpper();

	for(k=i=0;i<m_CompositeNoStr.GetLength();i++) {
		c = m_CompositeNoStr[i];
		res += c;
		k++;
	}
	m_CompositeNoStr = res;
	if ( m_CompositeNoStr.GetLength() )
	{
		m_weiter.EnableWindow(true);
		m_vollstaendig.EnableWindow(true);		
	}
	else
	{
		m_weiter.EnableWindow(false);
		m_vollstaendig.EnableWindow(false);	
	}

	InitialiseFactorList();
	m_DialogeDetails.EnableWindow(FALSE);

	UpdateData(FALSE);
	m_CompositeNoCtrl.SetSel(sels,sele);
}

void CDlgFactorisationDemo::CheckEdit(CString &m_edit, int &sels, int &sele)
{
			// sorgt dafür, daß keine syntaktisch falsche Eingabe in die Eingabefelder
		// möglich ist, führende Nullen werden entfernt, die Variablen sels und sele dienen der
		// Formatierung
	{
		while((0==m_edit.IsEmpty())&&('0'==m_edit.GetAt(0)))
			//Ruft Funktion IsEmpty auf. Diese gibt 0 zurück, wenn der CString nicht leer ist
			//GetAt(a) gibt Zeichen zurück, das an der a. Position steht
			//in diesem Fall, wenn dieses Zeichen 0 ist, dann geht er in die Schleife
			//Diese Funktionen gelten für die übergebenen Wert aus dem Dialog.
			//* Überprüfung, ob überhaupt was in dem Eingabefeld steht, UND ob das erste Zeichen 0 ist.
		{
			m_edit=m_edit.Right(m_edit.GetLength()-1);
			//* Var. m_edit ist Beispielsweise 0567. Der Rückgabe der Funktion Right gibt dir letzten x
			//* Stellen eines CStrings zurück, in diesem Fall gibt er mir 3 Stllen zurück (length-1), so dass die 0 gelöscht wird
			sels=sele=0;								
		}

		int exp_counter=0;
		for(int i=0;i<m_edit.GetLength();i++)
		{
			char ch=m_edit.GetAt(i);
			char ch2;
			if (i>=1) ch2=m_edit.GetAt(i-1);
			//* GetAt=holt sich das Zeichen an der i. Stelle
			if(((ch>='0')&&(ch<='9'))
				||((ch=='^'||ch=='+'||ch=='-' ||ch=='*') && (ch2!='^' && ch2!='+' && ch2!='-'  && ch2!='*') && i>=1 )
				//||((ch=='^'||ch=='+'||ch=='-' ||ch=='/') && i==0)
				||ch=='('||ch==')')
			{
				
			}
			
			else
			{
				m_edit=m_edit.Left(i)+m_edit.Right(m_edit.GetLength()-i-1);	
				//* die ersten i Stellen von links werden mit den Stellen rechts vom ungültigen Zeichen verbunden
				//* -1 damit das Zeichen an der Position i von m_edit gelöscht wird.

				if(i<=sele)
				{
					sele--;
					sels--;
				}
				i--;
			}
		}
		
	}
}

void CDlgFactorisationDemo::OnShowFactorisationDetails() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	DetailsFactorisation.m_factorisedNumber = "";
	DetailsFactorisation.m_Factor1isPrime   = "";
	DetailsFactorisation.m_Factor2isPrime   = "";
	DetailsFactorisation.m_factor2          = "";
	DetailsFactorisation.m_factor1          = "";
	DetailsFactorisation.m_Factorisation    = m_Factorisation;

	DetailsFactorisation.m_orignNumber = m_CompositeNoStr;
	DetailsFactorisation.m_benoetigte_zeit_global = m_benoetigte_zeit_global;
	if ( DetailsFactorisation.DoModal() == IDCANCEL )
	{
		// ToDo: Flag Setzen für das Speichern der Datei
		CAppDocument *NewDoc;
		NewDoc = theApp.OpenDocumentFileNoMRU(DetailsFactorisation.outfile);
		remove(DetailsFactorisation.outfile);
		LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_HL_OUTPUT,
				pc_str,STR_LAENGE_STRING_TABLE);
		char line[256];
		CString tmp = DetailsFactorisation.m_orignNumber;
		if ( tmp.GetLength() < 20 )
		{
			sprintf( line, pc_str, tmp.GetBuffer(0) );
		}
		else
		{
			CString tmp2 = tmp.Left(9) + "..." + tmp.Right(8);
			sprintf( line, pc_str, tmp2.GetBuffer(0) );
		}
		NewDoc->SetTitle(line);
		// Message(STR_LAENGE_STRING_TABLE, MB_ICONINFORMATION);

		// flomar, 05/08/2012: when the "details" dialog is closed 
		// with IDCANCEL, we're closing *this* dialog as well; this 
		// is for user convenience in the RSA demonstration dialog;
		// we might change this approach so the regular execution of 
		// the factorization dialog (without the RSA demonstration 
		// dialog on top) is not affected
		EndDialog(IDCANCEL);
	}
}

void CDlgFactorisationDemo::OnBnClickedLoadNumber()
{
  // TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	//SEQUENCE_OF_Extension *thisextension = NULL;
	CFile file;	
  char *buffer = 0;
  CFileException e;

	// pop up file selector box
	CFileDialog Dlg(TRUE, ".*", NULL, OFN_HIDEREADONLY,"All Files (*.*)|*.*||", this);
	
  if(IDCANCEL == Dlg.DoModal())
  {
    return;
  }

  // Get path name to prime number file
  CString p_file = Dlg.GetPathName();
  
  try {

    // read input file
    if(!file.Open(p_file,CFile::modeRead | CFile::typeBinary, &e )) 
    {
      // Unable to open file
      Message(IDS_STRING_FILEOPENERROR, MB_ICONEXCLAMATION);
	    return;
    }

	  ASSERT(file.GetLength() < ULONG_MAX);
	  unsigned long fileLength = (unsigned long)file.GetLength();
  	
    // Create buffer
	  buffer = (char *) calloc(fileLength + 1,sizeof(char));
	  if (!buffer) 
    {
      Message(AFX_IDP_FAILED_MEMORY_ALLOC, MB_ICONEXCLAMATION);
		  return;
	  }

	  // load Sourcedata
    file.Read(buffer, fileLength);
    file.Close();

    // Save sourcedata in string and remove whitespaces
    CString str = buffer;
    str.Remove('\n');
    str.Remove(0x0d);
    str.Remove(0x20);
    free(buffer);

		// flomar, 11/09/2011: furthermore, remove all non-digit characters  and then check if we 
		// are below the 8192kbit threshold (or a decimal length of 2467, see IDS_STRING_BIG_NUMBER);
		// I don't want to invoke the BigNumber class at this point, as this would be too much of an 
		// overkill for simply displaying a warning message (which would be displayed by subsequent 
		// calls later on anyway) a tad earlier just for user convenience
		CString strTemp = "";
		for(int i=0; i<str.GetLength(); i++) {
			char character = str[i];
			if(character >= '0' && character <= '9') {
				strTemp.AppendChar(character);
			}
		}
		str = strTemp;
		if(str.GetLength() > 2467) {
			Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
			str.Truncate(2467);
		}
    
    UpdateData(true);
    SetDlgItemText(IDC_EDIT1, str);
    UpdateData(false);

  } catch (CFileException *e) 
  {
    e->Delete();
		if (buffer)	free(buffer);
 		return;
	}
}

/////////////////////////////////////////////////////////////////////////////
// 
//
//

int CDlgFactorisationDemo::GetRSAFactorisation(CString &str_p, CString &str_q)
{
	int factorCounter = 0;
	NumFactor *ndx = factorList;
	if ( !ndx ) return NUMBER_NOT_FACTORISED;
	while ( ndx )
	{
		if ( ndx->exponent > 1 || !ndx->isPrime ) 
		{
			return NUMBER_NOT_RSA_MODUL;
		}
		factorCounter++;
		if ( 1 == factorCounter )
		{
			str_p = ndx->factorStr;
		}
		else if ( 2 == factorCounter )
		{
			str_q = ndx->factorStr;
		}
		else
		{
			break;
		}
		ndx = ndx->next;		
	}
	if ( factorCounter == 2 )
	{
		return NUMBER_RSA_MODUL;
	}
	else
	{
		return NUMBER_NOT_RSA_MODUL;
	}
}

