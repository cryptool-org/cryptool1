// DlgRot13Caesar.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "DlgRot13Caesar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRot13Caesar 


CDlgRot13Caesar::CDlgRot13Caesar(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRot13Caesar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRot13Caesar)
	m_key = _T("");
	m_radio = 1;
	m_from = _T("");
	m_to = _T("");
	//}}AFX_DATA_INIT
	s_alternativeWindowText[0]=0;
}

int CDlgRot13Caesar::Display()
{
	int res;

	res = DoModal();
	return res;
}

void CDlgRot13Caesar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRot13Caesar)
	DDX_Control(pDX, IDC_TO, m_to_control);
	DDX_Control(pDX, IDC_FROM, m_from_control);
	DDX_Control(pDX, ID_ENCRYPT, m_EncryptionButton);
	DDX_Control(pDX, ID_DECRYPT, m_DecryptionButton);
	DDX_Control(pDX, IDC_DIST, m_dist_control);
	DDX_Control(pDX, IDC_KEY, m_key_control);
	DDX_Text(pDX, IDC_KEY, m_key);
	DDV_MaxChars(pDX, m_key, 1);
	DDX_Radio(pDX, IDC_ROT13_RAD, m_radio);
	DDX_Text(pDX, IDC_FROM, m_from);
	DDX_Text(pDX, IDC_TO, m_to);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRot13Caesar, CDialog)
	//{{AFX_MSG_MAP(CDlgRot13Caesar)
	ON_BN_CLICKED(IDC_ROT13_RAD, OnRot13Rad)
	ON_BN_CLICKED(IDC_CAESAR_RAD, OnCaesarRad)
	ON_EN_UPDATE(IDC_KEY, OnUpdateKey)
	ON_BN_CLICKED(IDC_PASTE_KEY, OnPasteKey)
	ON_BN_CLICKED(ID_ENCRYPT, OnEncrypt)
	ON_BN_CLICKED(ID_DECRYPT, OnDecrypt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgRot13Caesar 

void CDlgRot13Caesar::OnRot13Rad()
{
	UpdateData(TRUE);
	CString tmp = theApp.TextOptions.m_alphabet;
	if (tmp.GetLength() % 2)
	{
		LoadString(AfxGetInstanceHandle(),IDS_ROT13_CAESAR_CASE,pc_str,255);
		AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
		m_radio = 1;
		UpdateData(FALSE);
		this->OnCaesarRad();
		return;
	}
	m_paste.ShowWindow(SW_HIDE);
	m_type = IDS_STRING_ROT13;
	m_key_control.EnableWindow(FALSE);
	m_key = this->GetRot13Key();
	this->UpdateDist();
	this->SetCryptButtons(TRUE);
	m_paste.EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CDlgRot13Caesar::OnCaesarRad()
{
	UpdateData(TRUE);
	m_type = IDS_STRING_CAESAR;
	m_key_control.EnableWindow(TRUE);
	m_key = _T("");
	this->UpdateDist();
	this->SetCryptButtons(FALSE);
	CString Title;
	strncpy(s_alternativeWindowText, "Caesar Schlüsseleingabe", 126);
	s_alternativeWindowText[126]=0;
	Title=s_alternativeWindowText;
	m_paste.ShowWindow(SW_SHOW);
	if ( IsKeyEmpty( Title ))
	{
		m_paste.EnableWindow(TRUE);
	}
	else
	{
		m_paste.EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void CDlgRot13Caesar::OnUpdateKey()
{
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(TRUE); /* get the displayed value in m_text */


	m_key_control.GetSel(sels, sele);
	res.Empty();
	
	if(theApp.TextOptions.m_IgnoreCase) m_key.MakeUpper();

	for(k=i=0;i<m_key.GetLength();i++) {
		c = m_key[i];
		if(AppConv.IsInAlphabet(c)) { // valid character
			res += c;
			k++;
		}
		else { // invalid character
			MessageBeep(MB_OK);
			if(k<sels) sels--;
			if(k<sele) sele--;
		}
	}

	m_key = res;
	m_key_control.SetSel(sels,sele);
	this->UpdateDist();
	this->SetCryptButtons(FALSE);
	UpdateData(FALSE);
}

void CDlgRot13Caesar::UpdateDist()
{
	if (m_key.IsEmpty())
	{
		m_dist_control.SetWindowText("");
	}
	else
	{
		CString target;
		for (int ii = 0; ii < m_source.GetLength(); ii ++)
		{
			if (m_key.GetAt(0) == m_source.GetAt(ii))
			{
				break;
			}
		}
		m_dist = ii + 1;
		target.Format("%d", m_dist);   
		m_dist_control.SetWindowText(target);
	}
}

BOOL CDlgRot13Caesar::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_source = theApp.TextOptions.m_alphabet;	
	m_font.CreatePointFont(100,"Courier New");
	m_from_control.SetFont(&m_font);
	m_to_control.SetFont(&m_font);
	VERIFY(m_paste.AutoLoad(IDC_PASTE_KEY,this));
	this->OnCaesarRad();
	this->SetCryptButtons(FALSE);
	return TRUE;
}

void CDlgRot13Caesar::OnPasteKey() 
{
	UpdateData(TRUE);

	CString Title;
	strncpy(s_alternativeWindowText, "Caesar Schlüsseleingabe", 126);
	s_alternativeWindowText[126]=0;
	Title=s_alternativeWindowText;
	ExtractStrKeyType( strTitle, Title );
	if ( PasteKey(strTitle,m_key) )
	{
		if (m_source.Find(m_key) >= 0)
		{
			this->UpdateDist();
			this->SetCryptButtons(TRUE);
		}
		else
		{
			LoadString(AfxGetInstanceHandle(),IDS_ROT13_CAESAR_BAD_KEY,pc_str,255);
			AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
			m_key.Empty();
			UpdateData(FALSE);
			this->OnUpdateKey();
		}
	}
	UpdateData(FALSE);
}

void CDlgRot13Caesar::OnEncrypt() 
{
	m_Decrypt = 0;
	OnOK();
}

void CDlgRot13Caesar::OnDecrypt() 
{
	m_Decrypt = 1;
	OnOK();	
}

void CDlgRot13Caesar::SetCryptButtons(BOOL force)
{
	if (force)
	{
		this->UpdateFromTo(TRUE);
		m_EncryptionButton.EnableWindow(TRUE);
		m_DecryptionButton.EnableWindow(TRUE);
	}
	else
	{
		if (m_key.GetLength())
		{
			this->UpdateFromTo(TRUE);
			m_EncryptionButton.EnableWindow(TRUE);
			m_DecryptionButton.EnableWindow(TRUE);
		}
		else
		{
			this->UpdateFromTo(FALSE);
			m_EncryptionButton.EnableWindow(FALSE);
			m_DecryptionButton.EnableWindow(FALSE);
		}
	}
}

char * CDlgRot13Caesar::GetData( void )
{
	return m_key.GetBuffer(MAX_VIGENERE + 1);
}

void CDlgRot13Caesar::UpdateFromTo(BOOL show)
{
	if (show)
	{
		CString to = m_source;
		int ii, jj, length = m_source.GetLength();
		
		m_from = this->FinalizeOutput(m_source);
		for (ii = 0; ii < length; ii ++)
		{
			jj = ii + m_dist < length ? ii + m_dist : ii + m_dist - length;
			to.SetAt(ii, m_source.GetAt(jj));
		}
		m_to = this->FinalizeOutput(to);
	}
	else 
	{
		m_from = m_source; // _T("");
		m_to   = m_source; //  _T("");
	}
}

CString CDlgRot13Caesar::FinalizeOutput(CString tmp)
{
	int ii, jj, length = tmp.GetLength();

	if (tmp.GetLength() > MAX_DISPLAY)
	{
		CString result(' ', MAX_DISPLAY + MAX_EXTRA + 2);

		for (ii = 0; ii < MAX_DISPLAY / 2; ii ++)
		{
			result.SetAt(ii, tmp.GetAt(ii));
		}
		for (ii = 0; ii < MAX_EXTRA; ii ++)
		{
			result.SetAt(ii + MAX_DISPLAY / 2 + 1, FILL_CHAR);
		}		
		for (ii = 0; ii < MAX_DISPLAY / 2; ii ++)
		{
			jj = ii + length - MAX_DISPLAY / 2;
			result.SetAt(ii + MAX_DISPLAY / 2 + MAX_EXTRA + 2, tmp.GetAt(jj));
		}

		return result;
	}
	else
	{
		return tmp;
	}
}

CString CDlgRot13Caesar::GetRot13Key()
{
	int length = m_source.GetLength();
	ASSERT (!(length % 2));
	return m_source.GetAt(length / 2 - 1);
}
