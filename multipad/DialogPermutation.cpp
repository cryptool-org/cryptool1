// DialogPermutation.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DialogPermutation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogPermutation 


CDialogPermutation::CDialogPermutation(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPermutation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogPermutation)
	m_Perm1 = _T("");
	m_Perm2 = _T("");
	//}}AFX_DATA_INIT
}


void CDialogPermutation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPermutation)
	DDX_Text(pDX, IDC_EDIT1, m_Perm1);
	DDV_MaxChars(pDX, m_Perm1, 32);
	DDX_Text(pDX, IDC_EDIT2, m_Perm2);
	DDV_MaxChars(pDX, m_Perm2, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogPermutation, CDialog)
	//{{AFX_MSG_MAP(CDialogPermutation)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDialogPermutation 

void CDialogPermutation::OnDecrypt() 
{
	UpdateData(TRUE);
	m_P1len = MakePerm(&m_Perm1, m_P1, m_P1inv);
	m_P2len = MakePerm(&m_Perm2, m_P2, m_P2inv);
	UpdateData(FALSE);
	m_Dec = 1;
	OnOK();
}

void CDialogPermutation::OnEncrypt() 
{
	UpdateData(TRUE);
	m_P1len = MakePerm(&m_Perm1, m_P1, m_P1inv);
	m_P2len = MakePerm(&m_Perm2, m_P2, m_P2inv);
	UpdateData(FALSE);
	m_Dec = 0;
	OnOK();
}



int CDialogPermutation::MakePerm( CString *Pin, int p[], int pinv[])
{
	int i, j, k, id[26], plen;

	Pin->MakeUpper();
	for(i=0;i<Pin->GetLength();) {
		if(strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", Pin->GetAt(i)))
			i++;
		else
			Pin->Delete(i);
	}
	plen = min(Pin->GetLength(), 26);
	if(plen == 0) return 0;
	for(i=0;i<plen;i++) id[i]=i;
	for(i=0;i<plen;i++) {
		j = (Pin->GetAt(i)-'A') % (plen-i);
		p[i] = id[j];
		for(k=j; k<(plen-i); k++) id[k] = id[k+1];
	}
	for(i=0; i<plen; i++) pinv[p[i]]=i;

	return plen;
}
