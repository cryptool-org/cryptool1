//////////////////////////////////////////////////////////////////
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

// Dlg_PlayfairKey.cpp: Implementierungsdatei
//
// Men�folge: Ver-/entschl�sseln -> Klassisch -> Playfair...
//

#include "assert.h"
#include "stdafx.h"
#include "multipad.h"
#include "Dlg_PlayfairKey.h"
#include "playfair.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_PlayfairKey 

CDlg_PlayfairKey::CDlg_PlayfairKey(const char *infile,const char *outfile,int r,int c,CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_PlayfairKey::IDD, pParent)
{
	int i,j;

	//{{AFX_DATA_INIT(CDlg_PlayfairKey)
	m_Alg = new Playfair("",0,infile,outfile,r,c,1);
	m_sechs = 0;
	m_preformat=1;
	m_use=1;
	for (i=0;i<m_Alg->getSize();i++)
	{
		for (j=0;j<m_Alg->getSize();j++)
		{
			m_mat[i][j]=m_Alg->getCharOfMatrix(i,j);
		}
	}
	//}}AFX_DATA_INIT

	m_Dec = 0;
}

CDlg_PlayfairKey::~CDlg_PlayfairKey()
{
	assert (m_Alg);
/*	//{{AFX_DATA_INIT(CDlg_PlayfairKey) */
    delete m_Alg; m_Alg = NULL;
/*	//}}AFX_DATA_INIT */
}

//////////////////////////////////////////////////////////////////////////////
//
void CDlg_PlayfairKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_PlayfairKey)
	DDX_Control(pDX, IDC_KEYENTER, m_text_ctl);
	DDX_Text(pDX, IDC_KEYENTER, m_text);
	DDV_MaxChars(pDX, m_text, 36);
	DDX_Radio(pDX, IDC_RADIO3, m_sechs);
	DDX_Text(pDX, IDC_EDIT11, m_mat[0][0]);
	DDX_Text(pDX, IDC_EDIT12, m_mat[0][1]);
	DDX_Text(pDX, IDC_EDIT13, m_mat[0][2]);
	DDX_Text(pDX, IDC_EDIT14, m_mat[0][3]);
	DDX_Text(pDX, IDC_EDIT15, m_mat[0][4]);
	DDX_Control(pDX, IDC_EDIT16, m_matc[0]);
	DDX_Text(pDX, IDC_EDIT16, m_mat[0][5]);
	DDX_Text(pDX, IDC_EDIT21, m_mat[1][0]);
	DDX_Text(pDX, IDC_EDIT22, m_mat[1][1]);
	DDX_Text(pDX, IDC_EDIT23, m_mat[1][2]);
	DDX_Text(pDX, IDC_EDIT24, m_mat[1][3]);
	DDX_Text(pDX, IDC_EDIT25, m_mat[1][4]);
	DDX_Control(pDX, IDC_EDIT26, m_matc[1]);
	DDX_Text(pDX, IDC_EDIT26, m_mat[1][5]);
	DDX_Text(pDX, IDC_EDIT31, m_mat[2][0]);
	DDX_Text(pDX, IDC_EDIT32, m_mat[2][1]);
	DDX_Text(pDX, IDC_EDIT33, m_mat[2][2]);
	DDX_Text(pDX, IDC_EDIT34, m_mat[2][3]);
	DDX_Text(pDX, IDC_EDIT35, m_mat[2][4]);
	DDX_Control(pDX, IDC_EDIT36, m_matc[2]);
	DDX_Text(pDX, IDC_EDIT36, m_mat[2][5]);
	DDX_Text(pDX, IDC_EDIT41, m_mat[3][0]);
	DDX_Text(pDX, IDC_EDIT42, m_mat[3][1]);
	DDX_Text(pDX, IDC_EDIT43, m_mat[3][2]);
	DDX_Text(pDX, IDC_EDIT44, m_mat[3][3]);
	DDX_Text(pDX, IDC_EDIT45, m_mat[3][4]);
	DDX_Control(pDX, IDC_EDIT46, m_matc[3]);
	DDX_Text(pDX, IDC_EDIT46, m_mat[3][5]);
	DDX_Text(pDX, IDC_EDIT51, m_mat[4][0]);
	DDX_Text(pDX, IDC_EDIT52, m_mat[4][1]);
	DDX_Text(pDX, IDC_EDIT53, m_mat[4][2]);
	DDX_Text(pDX, IDC_EDIT54, m_mat[4][3]);
	DDX_Text(pDX, IDC_EDIT55, m_mat[4][4]);
	DDX_Control(pDX, IDC_EDIT56, m_matc[4]);
	DDX_Text(pDX, IDC_EDIT56, m_mat[4][5]);
	DDX_Control(pDX, IDC_EDIT61, m_matc[5]);
	DDX_Text(pDX, IDC_EDIT61, m_mat[5][0]);
	DDX_Control(pDX, IDC_EDIT62, m_matc[6]);
	DDX_Text(pDX, IDC_EDIT62, m_mat[5][1]);
	DDX_Control(pDX, IDC_EDIT63, m_matc[7]);
	DDX_Text(pDX, IDC_EDIT63, m_mat[5][2]);
	DDX_Control(pDX, IDC_EDIT64, m_matc[8]);
	DDX_Text(pDX, IDC_EDIT64, m_mat[5][3]);
	DDX_Control(pDX, IDC_EDIT65, m_matc[9]);
	DDX_Text(pDX, IDC_EDIT65, m_mat[5][4]);
	DDX_Control(pDX, IDC_EDIT66, m_matc[10]);
	DDX_Text(pDX, IDC_EDIT66, m_mat[5][5]);
	DDX_Check(pDX, IDC_PREFORM, m_preformat);
	DDX_Control(pDX, IDC_PREFORM, m_prec);
	DDX_Check(pDX, IDC_CHECK1, m_use);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_PlayfairKey, CDialog)
	//{{AFX_MSG_MAP(CDlg_PlayfairKey)
	ON_EN_UPDATE(IDC_KEYENTER, OnUpdateEdit1)
	ON_BN_CLICKED(IDC_RADIO3, OnSechs)
	ON_BN_CLICKED(IDC_RADIO4, OnSechs)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlg_PlayfairKey 

void CDlg_PlayfairKey::OnCheck() 
// Doppelte Zeichen ignorieren oder nicht
{
	UpdateData(TRUE);
	m_Alg->PassUse(m_use);
	UpdateData(FALSE);
	OnUpdateEdit1();
}

void CDlg_PlayfairKey::OnSechs() 
// statt 5x5 wurde 6x6 oder umgekehrt ausgew�hlt
{
	int i;

	UpdateData(TRUE);
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	if (m_sechs == 1)
	{
		m_Alg->SetSize(true);
		for (i=0;i<11;i++)
			m_matc[i].EnableWindow(TRUE);
	}
	else
	{
		m_Alg->SetSize(false);
		for (i=0;i<11;i++)
			m_matc[i].EnableWindow(FALSE);
		for (i=0;i<6;i++)
			m_mat[i][5]="";
		for (i=0;i<5;i++)
			m_mat[5][i]="";
	}
	UpdateData(FALSE);
	OnUpdateEdit1();
}

void CDlg_PlayfairKey::OnChange() 
{
	char tmp[100];
	int i,j;

	UpdateData(TRUE);
	strcpy(tmp,m_text);
	m_Alg->SetPass( tmp );
	for (i=0;i<m_Alg->getSize();i++)
	{
		for (j=0;j<m_Alg->getSize();j++)
		{
			m_mat[i][j]=m_Alg->getCharOfMatrix(i,j);
		}
	}
	UpdateData(FALSE);
}

char *CDlg_PlayfairKey::GetData()
{
	return m_text.GetBuffer(25);
}

int CDlg_PlayfairKey::Display()
{
	int res;
	res=DoModal();
	return res;
}

void CDlg_PlayfairKey::OnUpdateEdit1() 
{
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(TRUE); /* get the displayed value in m_text */
	m_text_ctl.GetSel(sels, sele);
	res.Empty();

	m_text.MakeUpper();

	for(k=i=0;i<m_text.GetLength();i++) {
		c = m_text[i];
		if(!m_Alg->myisalpha2(c))  // TG, Umlaute oder franz�sische Zeichen zu etwas �hnlichem ersetzen.
			c = m_Alg->getAlphabet()->replaceInvalidLetter(c);
		if(m_Alg->myisalpha2(c)) { // valid character
			res += c;
			k++;
		}
		else { // invalid character (e.g. white spaces)
			MessageBeep(MB_OK);
			if(k<sels) sels--;
			if(k<sele) sele--;
		} 
	}

	m_text = res;
	UpdateData(FALSE);
	m_text_ctl.SetSel(sels,sele);
	OnChange();
} 

void CDlg_PlayfairKey::OnDecrypt() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	m_Dec = 1;
	OnOK();
}

void CDlg_PlayfairKey::OnEncrypt() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	m_Dec = 0;
	OnOK();
}
