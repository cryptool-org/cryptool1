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
	CTutorialFactorisation Brent(0,"Brent"), Pollard(1,"Pollard"), 
			Williams(2,"Williams"), Lenstra(3,"Lenstra"), QSieve(4,"Quadratic Sieve");

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
		return;
	}

	int laenge_eingabe;
	laenge_eingabe = m_CompositeNoStr.GetLength();
	
	if ( laenge_eingabe )
	{
		m_weiter.EnableWindow(true);
		m_vollstaendig.EnableWindow(true);	
	}
	
	
	CString next_factor;
	

	next_factor=Search_First_Composite_Factor();
		
	// Falls noch zusammengesetzten Faktoren die eingegebene Zahl teilen:
	if (next_factor!="lolo")
	{
		int Out_SetN;
			Out_SetN=f.SetN(next_factor);
		int bitlength_next_factor = f.bitlength();
		if (Out_SetN==EVAL_NULL || Out_SetN==EVAL_EINS)
		{
			//Sie müssen eine ganze Zahl eingeben, die von 0 und 1 verschieden ist.
			m_CompositeNoCtrl.SetSel(0,-1);
			m_CompositeNoCtrl.SetFocus();
			Message(IDS_STRING_FAKTORISATION_NOT_NULL_OR_ONE, MB_ICONEXCLAMATION);
			return;

		}
		if (Out_SetN==EVAL_OK)
		{
			BOOL factorized = FALSE;
			CString f1, f2;

			theApp.DoWaitCursor(1);			// aktiviert die Sanduhr
			if (!m_bruteForce && !m_Brent && !m_Pollard && !m_Williams && !m_Lenstra && !m_QSieve)
			{
				//Sie müssen mindestens ein Verfahren wählen!
				Message(IDS_STRING_FAKTORISATION_VERFAHREN, MB_ICONEXCLAMATION);
				return;
			}
			if ( f.IsPrime(next_factor) )
			{// Die eingegebene Zahl ist eine Primzahl
				Message(IDS_STRING_FAKTORISATION_PRIMZAHL, MB_ICONEXCLAMATION);
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
					if ( IDOK != MessageBox(pc_str, NULL, MB_OKCANCEL) )
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

			dlg.m_totalThreads = started;
			LoadString(AfxGetInstanceHandle(),IDS_STRING_FACTORISATION_TIMER,pc_str,STR_LAENGE_STRING_TABLE);
			dlg.SetCaption(pc_str);
			if ( IDOK != dlg.DoModal() )
			{
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
			
			else
			{
				// Hier wird man angefordert mit einem anderen Algorithmus zu arbeiten!!
				Message(IDS_STRING_FAKTORISATION_NEU_WAEHLEN, MB_ICONEXCLAMATION);
				m_Name = "";
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
			
			char line1[256], line2[256], timeStr1[64],timeStr2[64];
			
			if ( zeit_condtruct1.day >= 1)
			{	
				LoadString(AfxGetInstanceHandle(),IDS_STRING_FMT_DAYS,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(timeStr1,pc_str, zeit_condtruct1.day,zeit_condtruct1.hour, zeit_condtruct1.min,zeit_condtruct1.sec);
			}
			else if (zeit_condtruct1.hour >= 1)
			{	
				LoadString(AfxGetInstanceHandle(),IDS_STRING_FMT_HRS,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(timeStr1,pc_str, zeit_condtruct1.hour, zeit_condtruct1.min,zeit_condtruct1.sec);
			}
			else if (zeit_condtruct1.min >= 1)
			{	
				LoadString(AfxGetInstanceHandle(),IDS_STRING_FMT_MIN,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(timeStr1,pc_str, zeit_condtruct1.min,zeit_condtruct1.sec);
			}
			else
			{	
				LoadString(AfxGetInstanceHandle(),IDS_STRING_FMT_SEC,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(timeStr1,pc_str, zeit_condtruct1.sec, zeit_condtruct1.msec);
			}
			
			LoadString(AfxGetInstanceHandle(),IDS_STRING_BENOETIGTE_ZEIT_FAKT,pc_str,STR_LAENGE_STRING_TABLE);		
			sprintf( line1, pc_str, timeStr1 );
			m_benoetigte_zeit_global = line1;	

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
						
			theApp.DoWaitCursor(-1);			// deaktiviert die Sanduhr
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
		}
		else if (Out_SetN==1)
		{
			// Falsche Eingabe: Eingabe ist keine positive ganze Zahl
			m_CompositeNoCtrl.SetSel(0,-1);
			m_CompositeNoCtrl.SetFocus();
			Message(IDS_STRING_FAKTORISATION_FALSCHE_EINGABE, MB_ICONEXCLAMATION);			
		}
		else
		{
			// Eingabe ist zu groß (1024-bit); wird nicht von der Demo unterstützt.
			m_CompositeNoCtrl.SetSel(0,-1);
			m_CompositeNoCtrl.SetFocus();
			Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
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
	// Reset the old coloring
	cf.cbSize = sizeof (CHARFORMAT);
	cf.dwMask= CFM_COLOR;//
	cf.crTextColor =RGB(0,0,0);
	m_FactorisationCtrl.SetSel(0,-1);
	m_FactorisationCtrl.SetSelectionCharFormat(cf);
	
	NumFactor *ndx = factorList;
	if ( !ndx ) return;
	int anfang = 0, ende = 0, expLen; 
	while ( ndx )
	{
		if ( ndx->exponent > 1 ) 
		{
			expLen = (long)ceil( log(double(ndx->exponent))/log(10.0))+1;
		}
		else
			expLen = 0;
		ende = anfang + strlen(ndx->factorStr.GetBuffer(128));
		// Markiere Text ....
		if ( !ndx->isPrime )
		{
			cf.cbSize = sizeof (CHARFORMAT);
			cf.dwMask= CFM_COLOR;
			cf.crTextColor =RGB(250,0,0);
			m_FactorisationCtrl.SetSel(anfang, ende);
			m_FactorisationCtrl.SetSelectionCharFormat(cf);
		}
		ndx = ndx->next;
		anfang = ende + 3 + expLen;
	}
	
	// remove the selection 
	m_FactorisationCtrl.SetSel(0,0);	


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
	NumFactor *ndx = factorList;
	do
		{
		UpdateData(TRUE);
		theApp.DoWaitCursor(0);			// Aktiviert die Sanduhr
		CString next_factor;
		next_factor=Search_First_Composite_Factor();
		
		// Falls noch zusammengesetzten Faktoren die eingegebene Zahl teilen:
		if (next_factor!="lolo")
		{
			CTutorialFactorisation fact;

			//fact.SetN(next_factor);
			
			int Out_SetN;
			Out_SetN=fact.SetN(next_factor);
			if (Out_SetN==2)
			{

			
				BOOL factorized = FALSE; 
				if (!m_bruteForce && !m_Brent && !m_Pollard && !m_Williams && !m_Lenstra && !m_QSieve)
				{
					//Sie müssen mindestens ein Verfahren wählen!
					Message(IDS_STRING_FAKTORISATION_VERFAHREN, MB_ICONEXCLAMATION);
					return;
				}
				if ( f.IsPrime(next_factor) )
				{// Die eingegebene Zahl ist eine Primzahl
					Message(IDS_STRING_FAKTORISATION_PRIMZAHL, MB_ICONINFORMATION);
					return;
				}
				if ( !factorized && m_bruteForce )
				{
					factorized = fact.BruteForce();
				}
				if ( !factorized && m_Brent )
				{
					factorized = fact.Brent();
				}
				if ( !factorized && m_Pollard )
				{
					factorized = fact.Pollard();
				}

				if ( !factorized && m_Williams )
				{
					factorized = fact.Williams();
				}

				if ( !factorized && m_Lenstra )
				{
					factorized = fact.Lenstra();
				}
				
				if ( !factorized && m_QSieve )
				{
					factorized = fact.QuadraticSieve();
				}		
				if ( factorized )
				{
					CString f1, f2;
					fact.GetFactor1Str( f1 );
					fact.GetFactor2Str( f2 );
					expandFactorisation( next_factor, f1, f2 );
					// Zahl wurde Faktorisiert
				}
				else
				{
					// Hier wird man angefordert mit einem anderen Algorithmus zu arbeiten!!
					Message(IDS_STRING_FAKTORISATION_NICHT_VOLLSTAENDIG, MB_ICONINFORMATION);
					return;
				}
		
				theApp.DoWaitCursor(1);			// deaktiviert die Sanduhr
				UpdateData(FALSE);
				Set_NonPrime_Factor_Red();
			}

			else if (Out_SetN==1)
			{
				// Falsche Eingabe: Eingabe ist keine positive ganze Zahl
				Message(IDS_STRING_FAKTORISATION_FALSCHE_EINGABE, MB_ICONEXCLAMATION);
				return;
			}
			else
			{
				// Eingabe ist zu groß (1024-bit); wird nicht von der Demo unterstützt.
				Message(STR_LAENGE_STRING_TABLE, MB_ICONINFORMATION);
				return;
			}
		}
		// Die Zahl ist jetzt vollständig faktorisiert
		else
		{
			m_weiter.EnableWindow(false);
			m_vollstaendig.EnableWindow(false);	
			Message(IDS_STRING_FAKTORISATION_VOLLSTAENDIG, MB_ICONINFORMATION);
			return;
		}
		{
			ndx = factorList;
		}
	}

	while (ndx);
	
}

BOOL CDlgFactorisationDemo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_weiter.EnableWindow(false);
	// TODO: Zusätzliche Initialisierung hier einfügen
	m_vollstaendig.EnableWindow(false);
		// Initialisiere die Schlüsselliste mit allen verfügbaren asymmetrischen Schlüsseln
	m_bruteForceCtrl.SetCheck(1);
	m_DialogeDetails.EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
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

	if(theApp.TextOptions.m_IgnoreCase) m_CompositeNoStr.MakeUpper();

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
	{ // reset !
		factorList = 0;
		DetailsFactorisation.ClearFactDetail();	
		m_DialogeDetails.EnableWindow(FALSE);
		m_Name = ""; 
	}
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

	DetailsFactorisation.m_orignNumber = m_CompositeNoStr;
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
	}
}
