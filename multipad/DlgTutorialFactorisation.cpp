// DlgTutorialFactorisation.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgTutorialFactorisation.h"
#include "CryptologyUsingMiracl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgTutorialFactorisation 


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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten DlgTutorialFactorisation 

void DlgTutorialFactorisation::OnButtonEnd() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CDialog::OnOK();
}

void DlgTutorialFactorisation::OnButtonFactorisation() 
{
	UpdateData(TRUE);
	
	CString next_factor;

	next_factor=Search_First_Composite_Factor();
	
	// Falls noch zusammengesetzten Faktoren die eingegebene Zahl teilen:
	if (next_factor!="lolo")
	{
		TutorialFactorisation fact;

		fact.SetN(next_factor);

		if ( TutorialFactorisation::IsPrime(next_factor) )
		{// Die eingegebene Zahl ist eine Primzahl
			return;
		}
		BOOL factorized = FALSE; 
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

		}
		else
		{
			// Hier wird man angefordert mit einem anderen Algorithmus zu arbeiten!!

		}
		
		UpdateData(FALSE);

		Set_NonPrime_Factor_Red();
	}
	// Zahl wurde vollständig faktorisiert!!!
	else
	{
		//Zahl wurde vollständig faktorisiret!
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
