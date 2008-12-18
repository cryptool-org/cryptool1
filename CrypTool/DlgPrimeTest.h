#pragma once
#include "afxwin.h"
#include "PrimeTestAKS.h"
#include "DlgShowProgress.h"

//#define PRIMETEST_TIME_MEASUREMENT

// CDlgPrimeTest-Dialogfeld

class CDlgPrimeTest : public CDialog, public CProgressModel
{
	DECLARE_DYNAMIC(CDlgPrimeTest)

public:

  CDlgPrimeTest(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgPrimeTest();

// Dialogfelddaten
	enum { IDD = IDD_PRIME_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
  
	DECLARE_MESSAGE_MAP()

  CString inputNumber;          // holds checked and converted input number 
  PrimeTestAKS *pAKS;	// pointer to AKS object during thread execution
  void UpdateResultField(int result, CString text);
public:
  afx_msg void OnBnClickedPrimetestButtonTest();
  afx_msg void OnBnClickedPrimetestButtonCancel();
  afx_msg void OnBnClickedPrimetestButtonLoadnumber();
  afx_msg void OnBnClickedPrimetestRadio();
  afx_msg void OnEnChangePrimetestEditNumber();
  afx_msg void OnBnClickedButtonJumpToFactorization();

  virtual BOOL OnInitDialog();

  virtual double getProgress();
  void runAKS();

  CEdit m_Result;               // member field for CEditResult
  CEdit m_control_editName;     
  CString m_editNumber;         // member field for CEditNumber
  CButton m_control_buttonJumpToFactorization;
  int m_radio;                  // member field for CRadio
  int m_algo;                   // holds chosen algorithm (set by radio buttons)
  
  CStatic m_picPrime;
  CStatic m_picNotPrime;

#ifdef PRIMETEST_TIME_MEASUREMENT
  // Time required by the prime test algo
  double algoTime;
#endif
};
