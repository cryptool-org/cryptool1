// DlgTutorialFactorisation.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgTutorialFactorisation.h"
#include "CryptologyUsingMiracl.h"
#include "DlgRuntime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgTutorialFactorisation 
long ExitFactorisationCode;


DlgTutorialFactorisation::DlgTutorialFactorisation(CWnd* pParent)
	: CDialog(DlgTutorialFactorisation::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgTutorialFactorisation)
	m_CompositeNoStr = _T("");
	m_bruteForce = FALSE;
	m_Brent = FALSE;
	m_Pollard = FALSE;
	m_Williams = FALSE;
	m_Lenstra = FALSE;
	m_QSieve = FALSE;
	m_Factorisation = _T("");
	//}}AFX_DATA_INIT
	factorList = 0;
}

DlgTutorialFactorisation::~DlgTutorialFactorisation()
{
	while ( factorList != 0 )
	{
		NumFactor *tmp = factorList;
		factorList = factorList->next;
		delete tmp;
	}
}


void DlgTutorialFactorisation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgTutorialFactorisation)
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgTutorialFactorisation, CDialog)
	//{{AFX_MSG_MAP(DlgTutorialFactorisation)
	ON_BN_CLICKED(IDC_BUTTON_cancel, OnButtonEnd)
	ON_BN_CLICKED(IDC_BUTTON_Faktorisieren, OnButtonFactorisation)
	ON_BN_CLICKED(IDC_BUTTON_VOLLSTAENDIG_FAKTORISATION, OnButtonVollstaendigFaktorisation)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEditEingabe)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten DlgTutorialFactorisation 

void DlgTutorialFactorisation::OnButtonEnd() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	CDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////////////
CDlgRuntime dlg;


UINT singleThreadBrent( PVOID x )
{
	TutorialFactorisation *f;
	f = (TutorialFactorisation*)x;
	BOOL ret = f->Brent();
	dlg.PostMessage(WM_TIMER,47,NULL);
	return 0;
}

UINT singleThreadPollard( PVOID x )
{
	TutorialFactorisation *f;
	f = (TutorialFactorisation*)x;
	BOOL ret = f->Pollard();
	dlg.PostMessage(WM_TIMER,47,NULL);
	return 0;
}

UINT singleThreadWilliams( PVOID x )
{
	TutorialFactorisation *f;
	f = (TutorialFactorisation*)x;
	BOOL ret = f->Williams();
	dlg.PostMessage(WM_TIMER,47,NULL);
	return 0;
}

UINT singleThreadLenstra( PVOID x )
{
	TutorialFactorisation *f;
	f = (TutorialFactorisation*)x;
	BOOL ret = f->Lenstra();
	dlg.PostMessage(WM_TIMER,47,NULL);
	return 0;
}

UINT singleThreadQuadraticSieve( PVOID x )
{
	TutorialFactorisation *f;
	f = (TutorialFactorisation*)x;
	BOOL ret = f->QuadraticSieve();
	dlg.PostMessage(WM_TIMER,47,NULL);
	return 0;
}


void DlgTutorialFactorisation::OnButtonFactorisation() 
{
	UpdateData(TRUE);
	
	if ( m_CompositeNoStr.GetLength() )
	{
		m_weiter.EnableWindow(true);
		m_vollstaendig.EnableWindow(true);	
	}

	CString next_factor;
	char line [256];
	next_factor=Search_First_Composite_Factor();
	theApp.DoWaitCursor(0);			// aktiviert die Sanduhr
	
	// Falls noch zusammengesetzten Faktoren die eingegebene Zahl teilen:
	if (next_factor!="lolo")
	{
		bool ja_nein;
		{
			TutorialFactorisation f;
			ja_nein=f.SetN(next_factor);
		}
		if (ja_nein==true)
		{
			BOOL factorized = FALSE;
			CString f1, f2;

			if (!m_bruteForce && !m_Brent && !m_Pollard && !m_Williams && !m_Lenstra && !m_QSieve)
			{
				//Sie m�ssen mindestens ein Verfahren w�hlen!
				LoadString(AfxGetInstanceHandle(),IDS_STRING_FAKTORISATION_VERFAHREN,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
				return;
			}
			if ( TutorialFactorisation::IsPrime(next_factor) )
			{// Die eingegebene Zahl ist eine Primzahl
				LoadString(AfxGetInstanceHandle(),IDS_STRING_FAKTORISATION_PRIMZAHL,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
				return;
			}
			if ( !factorized && m_bruteForce )
			{
				TutorialFactorisation fact;
				fact.SetN(next_factor);
				if ( TRUE == (factorized = fact.BruteForce()) )
				{
					fact.GetFactor1Str( f1 );
					fact.GetFactor2Str( f2 );
				}
			}
			if ( !factorized && m_Brent )
			{
				ExitFactorisationCode = 0;
				TutorialFactorisation fact;
				fact.SetN(next_factor);
				AfxBeginThread( singleThreadBrent, PVOID(&fact) );
				dlg.SetCaption("Brent");
				if ( IDOK != dlg.DoModal() )
				{
					ExitFactorisationCode = -1;
					Sleep( 200 );
				}
				factorized = fact.isItFactorized();
				if ( TRUE == factorized )
				{
					fact.GetFactor1Str( f1 );
					fact.GetFactor2Str( f2 );
				}
			}
			if ( !factorized && m_Pollard )
			{
/*
				TutorialFactorisation fact;
				fact.SetN(next_factor);
				if ( TRUE == (factorized = fact.Pollard()) )
				{
					fact.GetFactor1Str( f1 );
					fact.GetFactor2Str( f2 );
				}
*/
				ExitFactorisationCode = 0;
				TutorialFactorisation fact;
				fact.SetN(next_factor);
				AfxBeginThread( singleThreadPollard, PVOID(&fact) );
				Sleep(200);
				dlg.SetCaption("Pollard");
				if ( IDOK != dlg.DoModal() )
				{
					ExitFactorisationCode = -1;
					Sleep( 200 );
				}
				factorized = fact.isItFactorized();
				if ( TRUE == factorized )
				{
					fact.GetFactor1Str( f1 );
					fact.GetFactor2Str( f2 );
				}

			}

			if ( !factorized && m_Williams )
			{
/*
				TutorialFactorisation fact;
				fact.SetN(next_factor);
				if ( TRUE == (factorized = fact.Williams()) )
				{
					fact.GetFactor1Str( f1 );
					fact.GetFactor2Str( f2 );
				}
*/
				TutorialFactorisation fact;
				fact.SetN(next_factor);
				ExitFactorisationCode = 0;
				AfxBeginThread( singleThreadWilliams, PVOID(&fact) );
				Sleep(200);
				dlg.SetCaption("Williams");
				if ( IDOK != dlg.DoModal() )
				{
					ExitFactorisationCode = -1;
					Sleep( 200 );
				}
				factorized = fact.isItFactorized();
				if ( TRUE == factorized )
				{
					fact.GetFactor1Str( f1 );
					fact.GetFactor2Str( f2 );
				}
			}

			if ( !factorized && m_Lenstra )
			{
/*
				TutorialFactorisation fact;
				fact.SetN(next_factor);
				if ( TRUE == (factorized = fact.Lenstra()) )
				{
					fact.GetFactor1Str( f1 );
					fact.GetFactor2Str( f2 );
				}
*/
				TutorialFactorisation fact;
				fact.SetN(next_factor);
				ExitFactorisationCode = 0;
				AfxBeginThread( singleThreadLenstra, PVOID(&fact) );
				Sleep(200);
				dlg.SetCaption("Lenstra");
				if ( IDOK != dlg.DoModal() )
				{
					ExitFactorisationCode = -1;
					Sleep( 200 );
				}
				factorized = fact.isItFactorized();
				if ( TRUE == factorized )
				{
					fact.GetFactor1Str( f1 );
					fact.GetFactor2Str( f2 );
				}

			}
			
			if ( !factorized && m_QSieve )
			{
				TutorialFactorisation fact;
				fact.SetN(next_factor);
				ExitFactorisationCode = 0;
				AfxBeginThread( singleThreadQuadraticSieve, PVOID(&fact) );
				Sleep(200);
				dlg.SetCaption("Quadratic Sieve");
				if ( IDOK != dlg.DoModal() )
				{
					ExitFactorisationCode = -1;
					Sleep( 2000 );
				}
				factorized = fact.isItFactorized();
				if ( TRUE == factorized )
				{
					fact.GetFactor1Str( f1 );
					fact.GetFactor2Str( f2 );
				}
			}		
			Sleep( 200 );
			if ( factorized )
			{
				expandFactorisation( next_factor, f1, f2 );
			}
			else
			{
				// Hier wird man angefordert mit einem anderen Algorithmus zu arbeiten!!
				LoadString(AfxGetInstanceHandle(),IDS_STRING_FAKTORISATION_NEU_WAEHLEN,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
			}

			theApp.DoWaitCursor(1);			// deaktiviert die Sanduhr
			UpdateData(FALSE);
			Set_NonPrime_Factor_Red();
		}
		else
		{
			// Falsche Eingabe
			LoadString(AfxGetInstanceHandle(),IDS_STRING_FAKTORISATION_FALSCHE_EINGABE,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str);
			AfxMessageBox(line);
		}
	}
	
	// Die Zahl ist jetzt vollst�ndig faktorisiert
	else
	{
		m_weiter.EnableWindow(false);
		m_vollstaendig.EnableWindow(false);	
		
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FAKTORISATION_VOLLSTAENDIG,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox(line);
	}
}

/*
BOOL IsSmallerNumStr( CString &NumStr1, CString &NumStr2 )
{
	
}
*/

void DlgTutorialFactorisation::expandFactorisation(CString &composite, CString &f1, CString &f2)
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
			factorList->isPrime = TutorialFactorisation::IsPrime( f1 );
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
				factorList->isPrime = TutorialFactorisation::IsPrime( f1 );
				factorList->next = ndx;
			}
			else if ( ndx->factorStr == f1 )
			{
				factorList->exponent++;
			}
			else
			{
				while ( 0 != ndx->next && ( (ndx->next->factorStr.GetLength() < f1.GetLength()) ||
					  (ndx->next->factorStr.GetLength() == f1.GetLength() && ndx->next->factorStr < f1) ) ) 
					      ndx = ndx->next;
				if ( ndx->next && ndx->next->factorStr == f1 ) ndx->next->exponent++;
				else
				{
					NumFactor * insFactor = new NumFactor;
					insFactor->exponent = expFactor;
					insFactor->factorStr = f1;
					insFactor->isPrime = TutorialFactorisation::IsPrime( f1 );
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
			factorList->isPrime = TutorialFactorisation::IsPrime( f2 );
			factorList->next = ndx;
		}
		else if ( ndx->factorStr == f2 )
		{
			factorList->exponent++;
		}
		else
		{
			while ( 0 != ndx->next && ( (ndx->next->factorStr.GetLength() < f2.GetLength()) ||
				  (ndx->next->factorStr.GetLength() == f2.GetLength() && ndx->next->factorStr < f2) ) ) 
					  ndx = ndx->next;
			if ( ndx->next && ndx->next->factorStr == f2 ) ndx->next->exponent++;
			else
			{
				NumFactor * insFactor = new NumFactor;
				insFactor->exponent = expFactor;
				insFactor->factorStr = f2;
				insFactor->isPrime = TutorialFactorisation::IsPrime( f2 );
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






void DlgTutorialFactorisation::Set_NonPrime_Factor_Red()
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

CString DlgTutorialFactorisation::Search_First_Composite_Factor()
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

void DlgTutorialFactorisation::OnButtonVollstaendigFaktorisation() 
{
	NumFactor *ndx = factorList;
	do
		{
		UpdateData(TRUE);
		theApp.DoWaitCursor(0);			// Aktiviert die Sanduhr
		CString next_factor;
		char line [256];
		next_factor=Search_First_Composite_Factor();
		
		// Falls noch zusammengesetzten Faktoren die eingegebene Zahl teilen:
		if (next_factor!="lolo")
		{
			TutorialFactorisation fact;

			//fact.SetN(next_factor);
			
			bool ja_nein;
			ja_nein=fact.SetN(next_factor);
			if (ja_nein==true)
			{

			
				BOOL factorized = FALSE; 
				if (!m_bruteForce && !m_Brent && !m_Pollard && !m_Williams && !m_Lenstra && !m_QSieve)
				{
					//Sie m�ssen mindestens ein Verfahren w�hlen!
					LoadString(AfxGetInstanceHandle(),IDS_STRING_FAKTORISATION_VERFAHREN,pc_str,STR_LAENGE_STRING_TABLE);
					sprintf(line,pc_str);
					AfxMessageBox(line);
					return;
				}
				if ( TutorialFactorisation::IsPrime(next_factor) )
				{// Die eingegebene Zahl ist eine Primzahl
					LoadString(AfxGetInstanceHandle(),IDS_STRING_FAKTORISATION_PRIMZAHL,pc_str,STR_LAENGE_STRING_TABLE);
					sprintf(line,pc_str);
					AfxMessageBox(line);
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
					
					LoadString(AfxGetInstanceHandle(),IDS_STRING_FAKTORISATION_NICHT_VOLLSTAENDIG,pc_str,STR_LAENGE_STRING_TABLE);
					sprintf(line,pc_str);
					AfxMessageBox(line);
					
					return;
				}
		
				theApp.DoWaitCursor(1);			// deaktiviert die Sanduhr
				UpdateData(FALSE);
				Set_NonPrime_Factor_Red();
			}
			else
			{
				// Falsche Eingabe
				LoadString(AfxGetInstanceHandle(),IDS_STRING_FAKTORISATION_FALSCHE_EINGABE,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
				return;
			}
		}
		// Die Zahl ist jetzt vollst�ndig faktorisiert
		else
		{
			m_weiter.EnableWindow(false);
			m_vollstaendig.EnableWindow(false);	

			LoadString(AfxGetInstanceHandle(),IDS_STRING_FAKTORISATION_VOLLSTAENDIG,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str);
			AfxMessageBox(line);
			return;
		}
		{
			ndx = factorList;
		}
	}

	while (ndx);
	
}

BOOL DlgTutorialFactorisation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_weiter.EnableWindow(false);
	// TODO: Zus�tzliche Initialisierung hier einf�gen
	m_vollstaendig.EnableWindow(false);
		// Initialisiere die Schl�sselliste mit allen verf�gbaren asymmetrischen Schl�sseln
	m_bruteForceCtrl.SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

void DlgTutorialFactorisation::OnUpdateEditEingabe() 
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
//		if(AppConv.IsInAlphabet(c)) { // valid character
			res += c;
			k++;
//		}
//		else { // invalid character
		//	MessageBeep(MB_OK);
		//	if(k<sels) sels--;
		//	if(k<sele) sele--;
//		}
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
	factorList = 0;

	UpdateData(FALSE);
	m_CompositeNoCtrl.SetSel(sels,sele);


}

void DlgTutorialFactorisation::CheckEdit(CString &m_edit, int &sels, int &sele)
{
			// sorgt daf�r, da� keine syntaktisch falsche Eingabe in die Eingabefelder
		// m�glich ist, f�hrende Nullen werden entfernt, die Variablen sels und sele dienen der
		// Formatierung
	{
		while((0==m_edit.IsEmpty())&&('0'==m_edit.GetAt(0)))
			//Ruft Funktion IsEmpty auf. Diese gibt 0 zur�ck, wenn der CString nicht leer ist
			//GetAt(a) gibt Zeichen zur�ck, das an der a. Position steht
			//in diesem Fall, wenn dieses Zeichen 0 ist, dann geht er in die Schleife
			//Diese Funktionen gelten f�r die �bergebenen Wert aus dem Dialog.
			//* �berpr�fung, ob �berhaupt was in dem Eingabefeld steht, UND ob das erste Zeichen 0 ist.
		{
			m_edit=m_edit.Right(m_edit.GetLength()-1);
			//* Var. m_edit ist Beispielsweise 0567. Der R�ckgabe der Funktion Right gibt dir letzten x
			//* Stellen eines CStrings zur�ck, in diesem Fall gibt er mir 3 Stllen zur�ck (length-1), so dass die 0 gel�scht wird
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
				||ch=='('||ch==')'||ch=='['||ch==']'||ch=='{'||ch=='}')
			{
				
			}
			
			else
			{
				m_edit=m_edit.Left(i)+m_edit.Right(m_edit.GetLength()-i-1);	
				//* die ersten i Stellen von links werden mit den Stellen rechts vom ung�ltigen Zeichen verbunden
				//* -1 damit das Zeichen an der Position i von m_edit gel�scht wird.

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
