#pragma once

// CDlgPrimeTestRunning-Dialogfeld

class CDlgPrimeTestRunning : public CDialog
{
	DECLARE_DYNAMIC(CDlgPrimeTestRunning)

public:
	CDlgPrimeTestRunning(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgPrimeTestRunning();

// Dialogfelddaten
	enum { IDD = IDD_PRIME_TEST_RUNNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedCancel();
  void CloseWindow();
  virtual BOOL OnInitDialog();
  virtual INT_PTR DoModal();
  void EndDialog(int nResult);
  void SetMessageParam(UINT messageID); 

private:
  UINT m_messageID;
};
