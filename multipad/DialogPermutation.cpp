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
	m_PastedKey = _T("");
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
	DDX_Control(pDX, IDC_EDIT3, m_PastedKeyCtrl);
	DDX_Text   (pDX, IDC_EDIT3, m_PastedKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogPermutation, CDialog)
	//{{AFX_MSG_MAP(CDialogPermutation)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)
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

void CDialogPermutation::OnPasteKey() 
{
	char *tmpStr;
	char key1[256]; 
	char key2[256];

	theApp.DoWaitCursor(0);
	UpdateData(TRUE);
	m_PastedKeyCtrl.SetSel(0,-1);
	m_PastedKeyCtrl.Paste();
	m_PastedKeyCtrl.GetWindowText(m_PastedKey);
	tmpStr = m_PastedKey.GetBuffer(256);
	for (int i=0; i<m_PastedKey.GetLength() && tmpStr[i] != ';'; i++)
		key1[i] = tmpStr[i];
	key1[i] = 0;
	m_Perm1 = key1;
	i++;
	if (i < m_PastedKey.GetLength())
	{	
		int j = 0;
		for ( ; i < m_PastedKey.GetLength(); i++ )
			key2[j++] = tmpStr[i];
		key2[j] = 0;
		m_Perm2 = key2;
	}
	else m_Perm2 = _T("");
	UpdateData(FALSE);

	theApp.DoWaitCursor(-1);
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
