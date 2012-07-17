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

// DlgPrimesGenerator.cpp: Implementierungsdatei
//


#include "stdafx.h"
#include "CrypToolApp.h"
#include <stdlib.h>

#include "DlgPrimesGeneratorDemo.h"
#include "Keyrepository.h"
#include "DialogeMessage.h"
#include "FileTools.h"
#include "CrypToolTools.h"
#include "IntegerArithmetic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ITERATIONS_PRIME_NUMBER_GENERATION 20000

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgPrimesGeneratorDemo 

// flomar, 06/12/12
// this function is used to generate single pairs (p/q) of random prime numbers
UINT singleThreadGeneratePrimeNumbers(PVOID argument);
// flomar, 01/24/09
// this function is used to generate multiple prime numbers
UINT singleThreadGenerateMultiplePrimeNumbers(PVOID argument);

CDlgPrimesGeneratorDemo::CDlgPrimesGeneratorDemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrimesGeneratorDemo::IDD, pParent)
{
	m_hide_button_accept = false;
	//{{AFX_DATA_INIT(CDlgPrimesGeneratorDemo)
	m_radio1 = 0;
	m_radio4 = 0;
	m_radio6 = 0;
	m_edit1 = _T("2^7");
	m_edit2 = _T("2^8");
	m_edit3 = _T("2^7");
	m_edit4 = _T("2^8");
	m_edit5 = _T("0");
	m_edit6 = _T("0");
	separator = _T(" ");
	//}}AFX_DATA_INIT
	abortGenerationPrimeNumbers = false;
	generationPrimeNumbersAborted = false;
	generateMultiplePrimeNumbersEnabled = false;
	abortGenerationMultiplePrimeNumbers = false;
	generationMultiplePrimeNumbersAborted = false;
}

CDlgPrimesGeneratorDemo::CDlgPrimesGeneratorDemo(CString lower, CString upper, CWnd *pParent)
	: CDialog(CDlgPrimesGeneratorDemo::IDD, pParent)
{
	m_hide_button_accept = false;
	//{{AFX_DATA_INIT(CDlgPrimesGeneratorDemo)
	m_radio1 = 0;
	m_radio4 = 0;
	m_radio6 = 0;
	m_edit1 = lower;
	m_edit2 = upper;
	m_edit3 = _T("2^7");
	m_edit4 = _T("2^8");
	m_edit5 = _T("0");
	m_edit6 = _T("0");
	separator = _T(" ");
	//}}AFX_DATA_INIT
	abortGenerationPrimeNumbers = false;
	generationPrimeNumbersAborted = false;
	generateMultiplePrimeNumbersEnabled = false;
	abortGenerationMultiplePrimeNumbers = false;
	generationMultiplePrimeNumbersAborted = false;
}

void CDlgPrimesGeneratorDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPrimesGeneratorDemo)
	DDX_Control(pDX, IDC_EDIT2, m_control_edit2);
	DDX_Control(pDX, IDC_EDIT1, m_control_edit1);
	DDX_Control(pDX, IDC_BUTTON_GENERATE, m_control_button_generate);
	DDX_Control(pDX, IDC_BUTTON_ACCEPT, m_control_button_accept);
	DDX_Control(pDX, IDC_EDIT4, m_control_edit4);
	DDX_Control(pDX, IDC_EDIT3, m_control_edit3);
	DDX_Control(pDX, IDC_EDIT5, m_control_edit5);
	DDX_Control(pDX, IDC_EDIT6, m_control_edit6);
	DDX_Control(pDX, IDC_EDIT_SEPARATOR, m_control_separator);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Radio(pDX, IDC_RADIO4, m_radio4);
	DDX_Radio(pDX, IDC_RADIO6, m_radio6);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
	DDX_Text(pDX, IDC_EDIT5, m_edit5);
	DDX_Text(pDX, IDC_EDIT6, m_edit6);
	DDX_Text(pDX, IDC_EDIT_SEPARATOR, separator);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrimesGeneratorDemo, CDialog)
	//{{AFX_MSG_MAP(CDlgPrimesGeneratorDemo)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, OnButtonGenerate)
	ON_BN_CLICKED(IDC_BUTTON_ACCEPT, OnButtonAccept)
	ON_BN_CLICKED(IDC_ENDDIALOG, OnEndDialog)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdateEdit)
	ON_EN_UPDATE(IDC_EDIT3, OnUpdateEdit)
	ON_EN_UPDATE(IDC_EDIT4, OnUpdateEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgPrimesGeneratorDemo 


//=========================================================================================================
void CDlgPrimesGeneratorDemo::OnRadio4() 
{
	UpdateData(true);
	m_control_edit3.EnableWindow(true);
	m_control_edit4.EnableWindow(true);
	m_control_edit6.EnableWindow(true);
	UpdateData(false);
}

void CDlgPrimesGeneratorDemo::OnRadio5() 
{
	UpdateData(true);
	m_control_edit3.EnableWindow(false);
	m_control_edit4.EnableWindow(false);
	m_control_edit6.EnableWindow(true);
	// don't forget to copy from P to Q
	m_edit3 = m_edit1;
	m_edit4 = m_edit2;
	// m_edit6 = m_edit5;
	UpdateData(false);
}

void CDlgPrimesGeneratorDemo::OnRadio6() 
{
	UpdateData(true);
	
	// enable group boxes (and contents) on the right side of the dialog
	CWnd *window1 = GetDlgItem(IDC_RADIO4);
	if(window1) window1->EnableWindow(true);
	CWnd *window2 = GetDlgItem(IDC_RADIO5);
	if(window2) window2->EnableWindow(true);
	// make sure we enable the gui stuff on the right side only if radio button 4 is enabled; 
	// because if button 4 is not enabled, the user obviously wants only one value range
	if(m_radio4 == 0) {
		m_control_edit3.EnableWindow(true);
		m_control_edit4.EnableWindow(true);
		m_control_edit6.EnableWindow(true);
	}
	// also, enable the result field on the left side 
	m_control_edit5.EnableWindow(true);
	// disable the separator input field
	m_control_separator.EnableWindow(false);

	UpdateData(false);
}

void CDlgPrimesGeneratorDemo::OnRadio7() 
{
	UpdateData(true);
	
	// disable group boxes (and contents) on the right side of the dialog
	CWnd *window1 = GetDlgItem(IDC_RADIO4);
	if(window1) window1->EnableWindow(false);
	CWnd *window2 = GetDlgItem(IDC_RADIO5);
	if(window2) window2->EnableWindow(false);
	m_control_edit3.EnableWindow(false);
	m_control_edit4.EnableWindow(false);
	m_control_edit6.EnableWindow(false);
	// also, disable the result field on the left side 
	//(since we don't display primes in there anyway)
	m_control_edit5.EnableWindow(false);
	// enable the separator input field
	m_control_separator.EnableWindow(true);

	UpdateData(false);
}

BOOL CDlgPrimesGeneratorDemo::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Zusätzliche Initialisierung hier einfügen
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PRIMES,pc_str,STR_LAENGE_STRING_TABLE);
	
	m_control_edit1.SetFocus();
	CString Primes;
//	if ( PasteKey( pc_str, Primes ) )
	if (false)
	{
		UpdateData(true);
		int d = Primes.Find(';', 0);
		m_edit5 = Primes.Mid(0, d);
		m_edit6 = Primes.Mid(d+1);
		UpdateData(false);
	}
	else
	{
		m_control_button_accept.EnableWindow(false);
	}
	
	if(m_radio4) OnRadio5();

	if (m_hide_button_accept)
		m_control_button_accept.ShowWindow(SW_HIDE);

	// enable/disable generation of multiple prime numbers radio button
	CWnd *generateMultiplePrimeNumbersWindow = GetDlgItem(IDC_RADIO7);
	if(generateMultiplePrimeNumbersEnabled) {
		if(generateMultiplePrimeNumbersWindow) {
			generateMultiplePrimeNumbersWindow->EnableWindow(true);
		}
	}
	else {
		if(generateMultiplePrimeNumbersWindow) {
			generateMultiplePrimeNumbersWindow->EnableWindow(false);
		}
	}

	// fetch the separator for the prime number display from the registry
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_READ, IDS_REGISTRY_SETTINGS, "PrimeNumberGeneration") == ERROR_SUCCESS)
	{
		unsigned long u_length = 1024;
		char c_primeNumberSeparator[1025] = " ";

		CT_READ_REGISTRY(c_primeNumberSeparator, "Separator", u_length);

		UpdateData();
		separator.SetString(c_primeNumberSeparator);
		UpdateData(FALSE);

		CT_CLOSE_REGISTRY();
	}

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

BOOL CDlgPrimesGeneratorDemo::GetRandomPrime(CString &OutStr, GeneratePrimes &P)
{
	BOOL flag = FALSE;

	for ( int i=1; i<=ITERATIONS_PRIME_NUMBER_GENERATION && !flag; i++ )			 // 
	{
		P.RandP();
				
		if (0==m_radio1) flag = P.MillerRabinTest(100);
		if (1==m_radio1) flag = P.SolvayStrassenTest(100);
		if (2==m_radio1) flag = P.FermatTest(100);
	}
    if (flag)
	{
		P.GetPrime( OutStr );
	}
	else
	{
		OutStr = "0";
	}
	return flag;			// wenn keine Primzahl innerhalb der Grenzen gefunden wurde, erfolgt eine
						// entsprechende Fehlermeldung
}

//==============================================================================================================
void CDlgPrimesGeneratorDemo::OnButtonGenerate() 
// erzeugt zwei Zufalls-Primzahlen innerhalb der angegebenen Grenzen
// Fehler werden mit entsprechenden Messages behandelt
{
	UpdateData(true);

	int PSet,QSet;
	
	if(!((0==m_edit1.IsEmpty())&&(0==m_edit2.IsEmpty()) &&
		 (0==m_edit3.IsEmpty())&&(0==m_edit4.IsEmpty())) )
	{
		Message( IDS_STRING_ENTER_UPPER_LOWER_BOUND, MB_ICONINFORMATION );
		return;
	}
	
	CString UpnFormula;
	int err_ndx;
	BOOL error;
	
	error = CheckFormula(m_edit1,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_edit1.SetSel(err_ndx-1,m_edit1.GetLength());
		m_control_edit1.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		return;
	}
	error = CheckFormula(m_edit2,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_edit2.SetSel(err_ndx-1,m_edit2.GetLength());
		m_control_edit2.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		return;
	}
	error = CheckFormula(m_edit3,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_edit3.SetSel(err_ndx-1,m_edit3.GetLength());
		m_control_edit3.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		return;
	}
	error = CheckFormula(m_edit4,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_edit4.SetSel(err_ndx-1,m_edit4.GetLength());
		m_control_edit4.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		return;
	}
	
	// normally, we would either create one or two prime numbers at this point; but if the 
	// "create a set of prime numbers" check box is selected, we need to generate a set (1 to n) 
	// of prime numbers in a separate thread that needs to be manually interrupted by the user
	if(m_radio6 == 1) {
		// we need this initialization to allow multiple generation threads
		abortGenerationMultiplePrimeNumbers = false;
		mapGeneratedPrimeNumbers.clear();
		// show the progress dialog
		theApp.fs.Set(0);
		theApp.fs.setTitle(IDS_STRING_MULTIPLE_PRIME_NUMBERS_GENERATION_TITLE);
		// display value range in progress dialog
		char temp[1024];
		LoadString(AfxGetInstanceHandle(), IDS_STRING_MULTIPLE_PRIME_NUMBERS_GENERATION_TEXT, pc_str, STR_LAENGE_STRING_TABLE);
		sprintf(temp, pc_str, m_edit1, m_edit2);
		theApp.fs.setFormat(temp);
		// start the prime number generation thread
		AfxBeginThread(singleThreadGenerateMultiplePrimeNumbers, PVOID(this));
		// show the progress dialog
		if(theApp.fs.DoModal()) {
			// as soon as the user cancels the progress dialog, 
			// abort the prime number generation thread
			abortGenerationMultiplePrimeNumbers = true;
		}

		// write the prime numbers to a file
		char filename[CRYPTOOL_PATH_LENGTH];
		GetTmpName(filename, "cry", ".txt");
		ofstream outfile(filename);
		if(outfile) {
			for(	mapGeneratedPrimeNumbersIterator = mapGeneratedPrimeNumbers.begin();
						mapGeneratedPrimeNumbersIterator != mapGeneratedPrimeNumbers.end();
						mapGeneratedPrimeNumbersIterator++) {
				// write prime number
				CString primeNumber = (*mapGeneratedPrimeNumbersIterator).first;
				// append separator
				primeNumber.Append(separator);
				// write the prime number (and the separator)
				outfile.write(primeNumber, primeNumber.GetLength());
			}
			outfile.close();
		}
		// show the prime numbers in a new document
		theApp.OpenDocumentFileNoMRU(filename);

		// display a notification message
		CString message;
		// display the search interval (m_edit1, m_edit2) and the amount of prime numbers found;
		// moreover, display a different message if the generation process was cancelled by the user, 
		// thus rendering the set of generated prime numbers incomplete for the given value range
		if(generationMultiplePrimeNumbersAborted == false)
			LoadString(AfxGetInstanceHandle(), IDS_STRING_MULTIPLE_PRIME_NUMBERS_GENERATION_NOTIFICATION, pc_str, STR_LAENGE_STRING_TABLE);
		else
			LoadString(AfxGetInstanceHandle(), IDS_STRING_MULTIPLE_PRIME_NUMBERS_GENERATION_NOTIFICATION_CANCELLED, pc_str, STR_LAENGE_STRING_TABLE);
		// either way, reset the abortion flag (otherwise we'll get weird errors)
		generationMultiplePrimeNumbersAborted = false;
		// build the notification message
		sprintf(temp, pc_str, m_edit1, m_edit2, mapGeneratedPrimeNumbers.size());
		message.Append(temp);
		MessageBox(message, "CrypTool", MB_ICONINFORMATION);
		// write the separator to the registry
		if(CT_OPEN_REGISTRY_SETTINGS(KEY_WRITE, IDS_REGISTRY_SETTINGS, "PrimeNumberGeneration") == ERROR_SUCCESS) {	
			if(separator == "") separator = " ";
			CT_WRITE_REGISTRY(separator, "Separator");
			CT_CLOSE_REGISTRY();
		}
		// leave this function cleanly
		UpdateData(false);
		return;
	}
	else {
		// flomar, 06/12/12: since generating single prime numbers is very 
		// time-consuming for large limits, we generate them in a separate 
		// thread as well (see generation of multiple primes)
		if(0==m_radio4)
		{
			// we use separate limits for prime number generation (edit1/edit2, and edit3/edit4)
			PSet=P.SetLimits(m_edit1, m_edit2);
			QSet=Q.SetLimits(m_edit3, m_edit4);
		}
		else {
			// we use identical limits for prime number generation (edit1/edit2 for both)
			PSet=P.SetLimits(m_edit1, m_edit2);
			QSet=Q.SetLimits(m_edit1, m_edit2);
		}
		// if the limits are properly set, start the prime number generation thread
		if(PSet == 1 && QSet == 1) {
			// we need this initialization to allow multiple generation threads
			abortGenerationPrimeNumbers = false;
			// show the progress dialog
			theApp.fs.Set(0);
			theApp.fs.setTitle(IDS_STRING_PRIME_NUMBERS_GENERATION_TITLE);
			// display value range in progress dialog
			char temp[1024];
			if(m_radio4 == 0) {
				LoadString(AfxGetInstanceHandle(), IDS_STRING_PRIME_NUMBERS_GENERATION_TEXT2, pc_str, STR_LAENGE_STRING_TABLE);
				sprintf(temp, pc_str, m_edit1, m_edit2, m_edit3, m_edit4);
			}
			else {
				LoadString(AfxGetInstanceHandle(), IDS_STRING_PRIME_NUMBERS_GENERATION_TEXT1, pc_str, STR_LAENGE_STRING_TABLE);
				sprintf(temp, pc_str, m_edit1, m_edit2);
			}
			theApp.fs.setFormat(temp);
			// start the prime number generation thread
			AfxBeginThread(singleThreadGeneratePrimeNumbers, PVOID(this));
			// show the progress dialog
			if(theApp.fs.DoModal()) {
				// as soon as the user cancels the progress dialog, 
				// abort the prime number generation thread
				abortGenerationPrimeNumbers = true;
			}
		}
		else if ( PSet == 3)
		{
			m_control_edit1.SetFocus();
			m_control_edit1.SetSel(0,-1);
			Message( IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION );
		}
		else if ( PSet == 2)
		{
			m_control_edit2.SetFocus();
			m_control_edit2.SetSel(0,-1);
			Message( IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION );
		}
		else if (  QSet ==3)
		{
			m_control_edit3.SetFocus();
			m_control_edit3.SetSel(0,-1);
			Message( IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION );
		}
		else if (  QSet ==2)
		{
			m_control_edit4.SetFocus();
			m_control_edit4.SetSel(0,-1);
			Message( IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION );
		}
		else if (  PSet ==1 )
		{
			m_control_edit3.SetFocus();
			m_control_edit3.SetSel(0,-1);
			Message( IDS_STRING_MSG_LOWERBOUND_UPPERBOUND, MB_ICONSTOP );
		}
		else 
		{
			m_control_edit1.SetFocus();
			m_control_edit1.SetSel(0,-1);
			Message( IDS_STRING_MSG_LOWERBOUND_UPPERBOUND, MB_ICONSTOP );
		}
	}

	// enable/disable 'accept' button (used by the RSA demonstration)
	if(!m_edit5.IsEmpty() && m_edit5!="0" && !m_edit6.IsEmpty() && m_edit5!="0")
		m_control_button_accept.EnableWindow(true);
	else
		m_control_button_accept.EnableWindow(false);

	UpdateData(false);
}

//===============================================================================================
void CDlgPrimesGeneratorDemo::OnButtonAccept() 

// wenn der Button "Übernehmen" gewählt wird, kann der Dialog nur verlassen werden,
// wenn das Produkt der beiden Primzahlen kleiner als c_MaxPrime_high ist

{
	UpdateData(true);
	if ( m_edit5 != "0" && m_edit6 != "0" )
	{
		LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PRIMES,pc_str,STR_LAENGE_STRING_TABLE);
		CString Primes = m_edit5 + CString( ";" ) + m_edit6;
		CopyKey ( pc_str, Primes );
		CDialog::OnOK();
	}
	UpdateData(false);
}




void CDlgPrimesGeneratorDemo::OnEndDialog() 
{
	UpdateData(true);
	m_edit5=m_edit6="0";	
	CDialog::OnCancel();
	UpdateData(false);
}



void CDlgPrimesGeneratorDemo::OnUpdateEdit() 
{
	UpdateData(true);

	// empty result fields (m_edit5, m_edit6) by default
	m_edit5 = "";
	m_edit6 = "";
	UpdateData(false);

	// flomar, 04/10/2012: remove invalid characters from formula(s)
	int selectionStart;
	int selectionEnd;
	// m_edit1
	m_control_edit1.GetSel(selectionStart, selectionEnd);
	removeInvalidCharactersFromFormula(m_edit1, selectionStart, selectionEnd);
	UpdateData(false);
	m_control_edit1.SetSel(selectionStart, selectionEnd);
	// m_edit2
	m_control_edit2.GetSel(selectionStart, selectionEnd);
	removeInvalidCharactersFromFormula(m_edit2, selectionStart, selectionEnd);
	UpdateData(false);
	m_control_edit2.SetSel(selectionStart, selectionEnd);
	// m_edit3
	m_control_edit3.GetSel(selectionStart, selectionEnd);
	removeInvalidCharactersFromFormula(m_edit3, selectionStart, selectionEnd);
	UpdateData(false);
	m_control_edit3.SetSel(selectionStart, selectionEnd);
	// m_edit4
	m_control_edit4.GetSel(selectionStart, selectionEnd);
	removeInvalidCharactersFromFormula(m_edit4, selectionStart, selectionEnd);
	UpdateData(false);
	m_control_edit4.SetSel(selectionStart, selectionEnd);
	// m_edit5
	m_control_edit5.GetSel(selectionStart, selectionEnd);
	removeInvalidCharactersFromFormula(m_edit5, selectionStart, selectionEnd);
	UpdateData(false);
	m_control_edit5.SetSel(selectionStart, selectionEnd);
	// m_edit6
	m_control_edit6.GetSel(selectionStart, selectionEnd);
	removeInvalidCharactersFromFormula(m_edit6, selectionStart, selectionEnd);
	UpdateData(false);
	m_control_edit6.SetSel(selectionStart, selectionEnd);

	// if the "both are equal" checkbox is marked, copy from P to Q
	if(m_radio4)
	{
		UpdateData(true);
		m_edit3 = m_edit1;
		m_edit4 = m_edit2;
		m_edit6 = m_edit5;
		UpdateData(false);
	}

	// disable the 'accept' button by default
	// (it is implicitly enabled after successful generation)
	m_control_button_accept.EnableWindow(false);
}

// use this function to enable the generation of muliple prime numbers;
// by default, the generation of multiple prime numbers is not possible
void CDlgPrimesGeneratorDemo::enableGenerateASetOfPrimeNumbersFunctionality() {
	generateMultiplePrimeNumbersEnabled = true;
}

UINT singleThreadGeneratePrimeNumbers(PVOID argument)
{
	// get the parent dialog
	CDlgPrimesGeneratorDemo *dlg = (CDlgPrimesGeneratorDemo*)(argument);
	if(!dlg) return 0;
	// halt this thread until the progress bar is visible (avoid concurrency issues)
	while(theApp.fs.m_displayed == 0)
		Sleep(5);
	// generate random primes P and Q
	bool doneP = false;
	bool doneQ = false;
	// initialize progress bar
	theApp.fs.Set(0);
	for(int i=1; i<=ITERATIONS_PRIME_NUMBER_GENERATION && !(doneP && doneQ); i++)
	{
		if(!doneP) {
			dlg->P.RandP();
			if(dlg->m_radio1 == 0) doneP = dlg->P.MillerRabinTest(100);
			if(dlg->m_radio1 == 1) doneP = dlg->P.SolvayStrassenTest(100);
			if(dlg->m_radio1 == 2) doneP = dlg->P.FermatTest(100);
		}
		if(!doneQ) {
			dlg->Q.RandP();
			if(dlg->m_radio1 == 0) doneQ = dlg->Q.MillerRabinTest(100);
			if(dlg->m_radio1 == 1) doneQ = dlg->Q.SolvayStrassenTest(100);
			if(dlg->m_radio1 == 2) doneQ = dlg->Q.FermatTest(100);
		}
		// update progress bar
		theApp.fs.Set(i*100/ITERATIONS_PRIME_NUMBER_GENERATION);
	}
	// when we're done, set the respective dialog fields
	if(doneP && doneQ) {
		dlg->P.GetPrime(dlg->m_edit5);
		dlg->Q.GetPrime(dlg->m_edit6);
	}
	else {
		dlg->m_edit5 = "0";
		dlg->m_edit6 = "0";
		if(!doneP) Message(IDS_STRING_MSG_LEFT_PRIMES_NOT_FOUND, MB_ICONSTOP);
		if(!doneQ) Message(IDS_STRING_MSG_RIGHT_PrIMES_NOT_FOUND, MB_ICONSTOP);
	}
	// end progress bar
	theApp.fs.cancel();
	// end the thread
	AfxEndThread(0);
	return 0;
}

// we need this threaded function to generate multiple prime numbers;
// they are stored in "mapGeneratedPrimeNumbers"
UINT singleThreadGenerateMultiplePrimeNumbers(PVOID argument)
{
	// get the parent dialog
	CDlgPrimesGeneratorDemo *dlg = (CDlgPrimesGeneratorDemo*)(argument);
	if(!dlg) return 0;
	// halt this thread until the progress bar is visible (avoid concurrency issues)
	while(theApp.fs.m_displayed == 0)
		Sleep(5);
	// see which algorithm was chosen for prime generation
	int chosenAlgorithm = dlg->m_radio1;
	// we consider only the first choice for the value range (m_edit1, m_edit2)
	Big value;
	Big valueRangeStart;
	Big valueRangeEnd;
	// TODO: error checking
	if(!evaluate::CEvalIntExpr(valueRangeStart, dlg->m_edit1))
		return 0;
	if(!evaluate::CEvalIntExpr(valueRangeEnd, dlg->m_edit2))
		return 0;
	GeneratePrimes generator;
	// a counter for the progress bar (0-100)
	double progress = 0;
	// the amount the progress bar is increased by with each checked number;
	// this variable is only used for ranges smaller than 100 though, as we
	// had problems with that particular scenario (i.e. 50/100 is not 0.5 in 
	// terms of "Big" numbers)
	double fixedProgressIncrease = 0;
	Big range = valueRangeEnd - valueRangeStart + 1;
	if(range < 100) {
		char temp[4];
		temp << range;
		int rangeInt = (int)atoi(temp);
		fixedProgressIncrease = (double)1 / (double)rangeInt;
	}
	// now, as long as the user does not abort the thread, keep testing for prime numbers
	for(value = valueRangeStart; value < valueRangeEnd && !dlg->abortGenerationMultiplePrimeNumbers; value = value+1) 
	{
		CString stringPrimeNumber;
		generator.SetP(value);
		// result of the prime generation
		int result = 0;
		// now, use the correct algorithm
		if(chosenAlgorithm == 0)
			result = generator.MillerRabinTest(100);
		if(chosenAlgorithm == 1)
			result = generator.SolvayStrassenTest(100);
		if(chosenAlgorithm == 2)
			result = generator.FermatTest(100);
		// if there was a positive result, add the prime numer to the result string
		if(result) {
			if(generator.GetPrime(stringPrimeNumber)) {
				if(!dlg->mapGeneratedPrimeNumbers.count(stringPrimeNumber)) {
					dlg->mapGeneratedPrimeNumbers[stringPrimeNumber] = "generated";	
				}
			}	
		}
		// we increase the progress bar if necessary (with case differentiation, see above)
		if(range < 100) {
			progress += fixedProgressIncrease;
		}
		else {
			Big step = (valueRangeEnd - valueRangeStart) / 100;
			if((value - valueRangeStart) >= (step + step * progress))
				progress++;
		}	
		theApp.fs.Set((int)progress);
	}
	// end the progress bar
	theApp.fs.cancel();

	// this is a very dirty hack, but it should work: if "value" is smaller than "valueRangeEnd",
	// we have an indication that the progress bar was cancelled purposely by the user
	if(value < valueRangeEnd)
		dlg->generationMultiplePrimeNumbersAborted = true;
	else
		dlg->generationMultiplePrimeNumbersAborted = false;
	
	// end the thread
	AfxEndThread(0);
	return 0;
}