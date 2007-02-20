#pragma once


// CSelectPasteDecoding dialog

class CSelectPasteDecoding : public CDialog
{
	DECLARE_DYNCREATE(CSelectPasteDecoding)

public:
	CSelectPasteDecoding(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectPasteDecoding();

// Dialog Data
	enum { IDD = IDD_SELECTPASTEDECODING };
	static int selectPasteDecoding(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
