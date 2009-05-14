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

// DlgPrimeTest.cpp : Implementierungsdatei
//
//#define PRIMETEST_TIME_MEASUREMENT
#include "stdafx.h"
#include "CrypToolApp.h"
#include "DialogeMessage.h"
#include "DlgPrimeTest.h"
#include ".\dlgprimetest.h"
#include "DlgFactorisationDemo.h"

#include "PrimeTest.h"
#include "PrimeTestAKS.h"
#include "PrimePolynom.h"


// CDlgPrimeTest-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgPrimeTest, CDialog)
CDlgPrimeTest::CDlgPrimeTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrimeTest::IDD, pParent)
  , m_radio(0)
  , m_algo(0)
{
  m_editNumber = _T("");
}

CDlgPrimeTest::~CDlgPrimeTest()
{
}

//////////////////////////////////////////////////////////////////////////////
UINT runAKShelper( PVOID x )
{
  CDlgPrimeTest *dlg;
  dlg = (CDlgPrimeTest*)x;
  dlg->runAKS();
  return 0;
}

double CDlgPrimeTest::getProgress()
{
	return pAKS->getProgress();
}

void CDlgPrimeTest::runAKS()
{
	PrimeTestAKS AKS((const char*)inputNumber, &theApp.fs.m_canceled);
	pAKS = &AKS;

	// AKS thread
	CString title;
	CString message;
	message.Format(IDS_STRING_MSG_AKS_TEST_COMPLETE,AKS.loga());
	title.Format(IDS_STRING_MSG_AKS_TEST);
	theApp.fs.setModelTitleFormat(this, title, message);
	theApp.fs.Display();

#ifdef PRIMETEST_TIME_MEASUREMENT
  // ----------------------------------
  // Time measurement
  clock_t time1, time2;
  double test_time;
  
  // Start timer
  time1 = clock();
  // ----------------------------------
#endif

	// Perform AKS

	int res = AKS.aks();
	if (res == 2) // overflow
		res = 4; // error
#ifdef PRIMETEST_TIME_MEASUREMENT
  // ----------------------------------
  // Time measurement
  // End timer
  time2 = clock();
  
  // Calc duration
  test_time = ((double)time2 - (double)time1)/1000;
  
  // Set result to member field
  algoTime = test_time;
  // ----------------------------------
#endif
	theApp.fs.cancel(); // remove progress dialog
	WaitForSingleObject( theApp.fs.pEvent.m_hObject, INFINITE ); // wait until dialog gone
	UpdateResultField(res, inputNumber);
	pAKS = 0;
}

//////////////////////////////////////////////////////////////////////////////

void CDlgPrimeTest::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_PRIMETEST_EDIT_RESULT, m_Result);
  DDX_Radio(pDX, IDC_PRIMETEST_RADIO_MILLERRABIN, m_algo);
  DDX_Control(pDX, IDC_PRIMETEST_EDIT_NUMBER, m_control_editName);
  DDX_Control(pDX, IDC_PRIMETEST_EDIT_NUMBER, m_control_editName);
  DDX_Text(pDX, IDC_PRIMETEST_EDIT_NUMBER, m_editNumber);
  DDX_Control(pDX, IDC_STATIC_PRIM_RES, m_picPrime);
  DDX_Control(pDX, IDC_STATIC_PRIM_RES2, m_picNotPrime);
  DDX_Control(pDX, IDC_BUTTON_JUMP_TO_FACTORIZATION, m_control_buttonJumpToFactorization);
}


BEGIN_MESSAGE_MAP(CDlgPrimeTest, CDialog)
  ON_BN_CLICKED(IDC_PRIMETEST_BUTTON_TEST, OnBnClickedPrimetestButtonTest)
  ON_BN_CLICKED(IDC_PRIMETEST_BUTTON_CANCEL, OnBnClickedPrimetestButtonCancel)
  ON_BN_CLICKED(IDC_PRIMETEST_BUTTON_LOADNUMBER, OnBnClickedPrimetestButtonLoadnumber)
  ON_EN_CHANGE(IDC_PRIMETEST_EDIT_NUMBER, OnEnChangePrimetestEditNumber)
  ON_BN_CLICKED(IDC_PRIMETEST_RADIO_FERMAT, OnBnClickedPrimetestRadio)
  ON_BN_CLICKED(IDC_PRIMETEST_RADIO_SOLOVAY, OnBnClickedPrimetestRadio)
  ON_BN_CLICKED(IDC_PRIMETEST_RADIO_MILLERRABIN, OnBnClickedPrimetestRadio)
  ON_BN_CLICKED(IDC_PRIMETEST_RADIO_AKS, OnBnClickedPrimetestRadio)
  ON_BN_CLICKED(IDC_BUTTON_JUMP_TO_FACTORIZATION, CDlgPrimeTest::OnBnClickedButtonJumpToFactorization)
END_MESSAGE_MAP()


// CDlgPrimeTest-Meldungshandler
void CDlgPrimeTest::OnBnClickedPrimetestButtonTest()
{

#ifdef PRIMETEST_TIME_MEASUREMENT
  // ----------------------------------
  // Fields needed for time measurement
  clock_t time1, time2;
  double test_time;
  // ----------------------------------
#endif
  
  int res;
  int err_ndx;
  CString strBigNum;
	Big numBig;

  // Clear edit field
  m_Result.SetWindowText("");

  // Hide result images
  m_picNotPrime.ShowWindow(FALSE);
  m_picPrime.ShowWindow(FALSE);

  // Read number:
  if(m_editNumber.IsEmpty())
  {
    Message( IDS_STRING_PRIMETEST_ERROR_EMPTY, MB_ICONSTOP ); 
  }
  else
  {
    // ----------------------------
    int error = CheckFormula(m_editNumber,10,strBigNum,err_ndx);
    if (error == 0)
	  {
		  //Fehler in der Eingabe, von Parser abgefangen
		  m_control_editName.SetSel(0,m_editNumber.GetLength());
		  m_control_editName.SetFocus();
		  Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		  return;
	  }
    // ----------------------------

    // Check input number or term
    if(evaluate::CEvalIntExpr( numBig, m_editNumber.GetBuffer( m_editNumber.GetLength()+1) ) == false)
    {
		  // Zahl zu gross
		  m_control_editName.SetSel(0,m_editNumber.GetLength());
		  m_control_editName.SetFocus();
		  Message( IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION );
		  return;
    }
    else
    {
      // Convert Big number to CString
      BigToCString( numBig, strBigNum );
    }

    // Set number as string to PrimeTest class
    // This field is used from the thread to retrieve the input number
    inputNumber = strBigNum.GetBuffer(strBigNum.GetLength()+1);
    
#ifdef PRIMETEST_TIME_MEASUREMENT
    // ----------------------------------
    // Start timer for time measurement
    time1 = clock();
    // ----------------------------------
#endif
    
    // Use chosen algorithm
    switch(m_algo)
    {
      case(0):  // Miller-Rabin
      {
        SHOW_HOUR_GLASS   // Change mouse pointer

        GeneratePrimes P;
        P.SetP(numBig);
        if(P.MillerRabinTest(100))
        {
          // change return value
          res = 1;
        }
        else
        {
          // change return value
          res = 0;
        }
        HIDE_HOUR_GLASS   // Change mouse pointer
        break;
      }
      case(1):  // Fermat
      {
        SHOW_HOUR_GLASS   // Change mouse pointer

        GeneratePrimes P;
        P.SetP(numBig);
        if(P.FermatTest(100))
        {
          // change return value
          res = 1;
        }
        else
        {
          // change return value
          res = 0;
        }
        
        HIDE_HOUR_GLASS   // Change mouse pointer
        break;
      }
      case(2):  // Solovay-Strassen
      {
        SHOW_HOUR_GLASS   // Change mouse pointer

        PrimeTest prim = PrimeTest(strBigNum.GetBuffer(strBigNum.GetLength()+1));
        // Call Solovay-Strassen with required accuracy
        res = prim.solovay_strassen("99.999999999999999");
        
        HIDE_HOUR_GLASS   // Change mouse pointer
        break;
      }
      case(3):  // AKS
      {

        // Start AKS in seperate Thread
		AfxBeginThread(runAKShelper, this, THREAD_PRIORITY_NORMAL);
		return;
      }
      default:
        // No provided algorithm has been chosen
        res = 5;
      break;
    }

#ifdef PRIMETEST_TIME_MEASUREMENT
    // ----------------------------------
    // Determine time duration of algo
    time2 = clock();
    test_time = ((double)time2 - (double)time1)/1000;
    
    // Set duration to member field 
    algoTime = test_time;
    // ----------------------------------
#endif

    UpdateResultField(res, strBigNum);
  }
}

// Updates result field
void CDlgPrimeTest::UpdateResultField(int result, CString text)
{
  //UpdateData(true);
  CString strResult = "";

  // by default, disable button "jump to factorization"
  this->m_control_buttonJumpToFactorization.EnableWindow(false);

#ifdef PRIMETEST_TIME_MEASUREMENT
  // ----------------------------------
  // Output time required by algo
  strResult.Format("(%f seconds) ",algoTime);
  // ----------------------------------
#endif

  switch(result)
  {
    case(0):    // nicht prim
        LoadString(AfxGetInstanceHandle(),IDS_STRING_PRIMETEST_RESULT_NOTPRIME,pc_str,STR_LAENGE_STRING_TABLE);
        strResult += pc_str;
        strResult += text;
        
        // Show not prime image
        m_picNotPrime.ShowWindow(TRUE);
        m_picPrime.ShowWindow(FALSE);
        
        // enable button "jump to factorization"
        m_control_buttonJumpToFactorization.EnableWindow(true);

				// set the focus/cursor begind (!) the number to be tested
				m_control_editName.SetSel(-1, -1);
				m_control_editName.SetFocus();
    break;
    case(1):    // prim
        LoadString(AfxGetInstanceHandle(),IDS_STRING_PRIMETEST_RESULT_PRIME,pc_str,STR_LAENGE_STRING_TABLE);
        strResult += pc_str;
        strResult += text;

        // Show prime image
        m_picPrime.ShowWindow(TRUE);
        m_picNotPrime.ShowWindow(FALSE);

				// set the focus/cursor begind (!) the number to be tested
				m_control_editName.SetSel(-1, -1);
				m_control_editName.SetFocus();
    break;
    case(2):    // vermutlich
        LoadString(AfxGetInstanceHandle(),IDS_STRING_PRIMETEST_RESULT_PROBABLEPRIME,pc_str,STR_LAENGE_STRING_TABLE);
        strResult += pc_str;
        strResult += text;

        // Show prime image
        m_picPrime.ShowWindow(TRUE);
        m_picNotPrime.ShowWindow(FALSE);

				// set the focus/cursor begind (!) the number to be tested
				m_control_editName.SetSel(-1, -1);
				m_control_editName.SetFocus();
    break;
    case(3):    // cancel
        LoadString(AfxGetInstanceHandle(),IDS_STRING_PRIMETEST_RESULT_CANCEL,pc_str,STR_LAENGE_STRING_TABLE);
        strResult = pc_str;
        //strResult.Format("(%i) test abgebrochen",m_algo);
        
        // hide result pictures
        m_picNotPrime.ShowWindow(FALSE);
        m_picPrime.ShowWindow(FALSE);
    break;
    default:    // error
        LoadString(AfxGetInstanceHandle(),IDS_STRING_PRIMETEST_RESULT_ERROR,pc_str,STR_LAENGE_STRING_TABLE);
        strResult = pc_str;
        //strResult.Format("fehler bei der Verarbeitung");
        
        // hide result pictures
        m_picNotPrime.ShowWindow(FALSE);
        m_picPrime.ShowWindow(FALSE);
    break;
  }

  SetDlgItemText(IDC_PRIMETEST_EDIT_RESULT, strResult);
  //UpdateData(false);
}

void CDlgPrimeTest::OnBnClickedPrimetestButtonCancel()
{
  UpdateData(true);
	CDialog::OnCancel();
	UpdateData(false);
}

void CDlgPrimeTest::OnBnClickedPrimetestButtonLoadnumber()
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
    
    UpdateData(true);
    SetDlgItemText(IDC_PRIMETEST_EDIT_NUMBER, str);
    UpdateData(false);

  } catch (CFileException *e) 
  {
    e->Delete();
		if (buffer)	free(buffer);
 		return;
	}
}

BOOL CDlgPrimeTest::OnInitDialog()
{
  CDialog::OnInitDialog();

  //m_Result.SetReadOnly(TRUE); // Doesn't look good with gray background!

  return TRUE;  // return TRUE unless you set the focus to a control
  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDlgPrimeTest::OnEnChangePrimetestEditNumber()
{
  // TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
  // diese Benachrichtigung nicht senden, es sei denn, Sie setzen den CDialog::OnInitDialog() außer Kraft.
  // Funktion und Aufruf CRichEditCtrl().SetEventMask()
  // mit dem ENM_CHANGE-Flag ORed in der Eingabe.

  UpdateData(true);

  // Clear result field
  SetDlgItemText(IDC_PRIMETEST_EDIT_RESULT, "");

  // disable button "jump to factorization"
  this->m_control_buttonJumpToFactorization.EnableWindow(false);

  // Hide result fields
  m_picPrime.ShowWindow(FALSE);
  m_picNotPrime.ShowWindow(FALSE);

  UpdateData(false);
}

void CDlgPrimeTest::OnBnClickedPrimetestRadio()
{
  UpdateData(true);

  // Clear result field
  SetDlgItemText(IDC_PRIMETEST_EDIT_RESULT, "");

	// deactivate factorization button
	m_control_buttonJumpToFactorization.EnableWindow(false);

  // hide result pictures
  m_picNotPrime.ShowWindow(FALSE);
  m_picPrime.ShowWindow(FALSE);

	UpdateData(false);
}

void CDlgPrimeTest::OnBnClickedButtonJumpToFactorization()
{
  // show factorization demo dialog with the current number
  CDlgFactorisationDemo dlg;
  dlg.m_CompositeNoStr = this->m_editNumber;
  AfxInitRichEdit();
  dlg.DoModal();
}
