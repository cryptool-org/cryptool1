#pragma once
#include "afxwin.h"
#include "PrimeTestAKS.h"
#include "DlgPrimeTestRunning.h"

//#define PRIMETEST_TIME_MEASUREMENT

// CDlgPrimeTest-Dialogfeld

class CDlgPrimeTest : public CDialog
{
	DECLARE_DYNAMIC(CDlgPrimeTest)

public:

  CDlgPrimeTest(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgPrimeTest();
  void SetThreadResult(int res);

// Dialogfelddaten
	enum { IDD = IDD_PRIME_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
  
	DECLARE_MESSAGE_MAP()

  CString inputNumber;          // holds checked and converted input number 
  void UpdateResultField(int result, CString text);
  
public:
  afx_msg void OnBnClickedPrimetestButtonTest();
  afx_msg void OnBnClickedPrimetestButtonCancel();
  afx_msg void OnBnClickedPrimetestButtonLoadnumber();
  afx_msg void OnBnClickedAlgo();
  afx_msg void OnBnClickedPrimetestRadio();
  afx_msg void OnEnChangePrimetestEditNumber();

  virtual BOOL OnInitDialog();

  CEdit m_Result;               // member field for CEditResult
  CEdit m_control_editName;     
  CString m_editNumber;         // member field for CEditNumber
  int m_radio;                  // member field for CRadio
  int m_algo;                   // holds chosen algorithm (set by radio buttons)
  
  CDlgPrimeTestRunning* dlgRun;  // Dialog to cancel thread
  PrimeTestAKS primAKS;         // Class to perform AKS

  CStatic m_picPrime;
  CStatic m_picNotPrime;

#ifdef PRIMETEST_TIME_MEASUREMENT
  // Time required by the prime test algo
  double algoTime;
#endif

};
