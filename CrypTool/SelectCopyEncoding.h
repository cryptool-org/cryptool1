#pragma once
#include "afxwin.h"


// CSelectCopyEncoding dialog

#define ENCODING_NO 0
#define ENCODING_HEX 1
#define ENCODING_BASE64 2


class CSelectCopyEncoding : public CDialog
{
	DECLARE_DYNAMIC(CSelectCopyEncoding)

public:
	CSelectCopyEncoding(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectCopyEncoding();

// Dialog Data
	enum { IDD = IDD_SELECTCOPYENCODING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog(void);
	static int selectCopyEncoding(void);
	// static int m_encode_type;
};

