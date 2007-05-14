// DlgRot13Caesar.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "DlgRot13Caesar.h"
#include "CrypToolTools.h"

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
	//}}AFX_DATA_INIT
	caesarSelected = 1;
	m_type = IDS_STRING_CAESAR;
}


void CDlgRot13Caesar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRot13Caesar)
	DDX_Control(pDX, IDC_TO, m_CtrlTo);
	DDX_Control(pDX, IDC_FROM, m_CtrlFrom);
	DDX_Control(pDX, ID_ENCRYPT, m_EncryptionButton);
	DDX_Control(pDX, ID_DECRYPT, m_DecryptionButton);
	DDX_Control(pDX, IDC_DIST, m_dist_control);
	DDX_Control(pDX, IDC_KEY, m_CtrlKey);
	DDX_Control(pDX, IDC_EDIT_ALPHCODE, m_CtrlAlphCode);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_RADIO2, m_CtrlRadioRot13);
	DDX_Control(pDX, IDC_MESSAGE_ROT13, m_CtrlMessageRot13);
	DDX_Control(pDX, IDC_EDIT1, m_CtrlShowAlSize);
}


BEGIN_MESSAGE_MAP(CDlgRot13Caesar, CDialog)
	//{{AFX_MSG_MAP(CDlgRot13Caesar)
	ON_BN_CLICKED(IDC_RADIO2, OnRot13Rad)
	ON_BN_CLICKED(IDC_RADIO1, OnCaesarRad)
	ON_BN_CLICKED(IDC_RADIO5, DisableAlphCode)
	ON_BN_CLICKED(IDC_RADIO6, EnableAlphCode)
	ON_EN_UPDATE(IDC_KEY, OnUpdateKey)
	ON_EN_UPDATE(IDC_EDIT_ALPHCODE, OnUpdateAlphCode)
	ON_BN_CLICKED(IDC_PASTE_KEY, OnPasteKey)
	ON_BN_CLICKED(ID_ENCRYPT, OnEncrypt)
	ON_BN_CLICKED(ID_DECRYPT, OnDecrypt)
	ON_BN_CLICKED(IDC_RADIO3, EnableFirstPosNull)
	ON_BN_CLICKED(IDC_RADIO4, DisableFirstPosNull)
	ON_EN_KILLFOCUS(IDC_EDIT_ALPHCODE, OnExitAlphCode)
	ON_BN_CLICKED(IDC_BUTTON_TxtOpt, OnTxtOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgRot13Caesar 

BOOL CDlgRot13Caesar::OnInitDialog() 
{
	CDialog::OnInitDialog();

	VERIFY(m_paste.AutoLoad(IDC_PASTE_KEY,this));
	VERIFY(m_font.CreatePointFont(100,"Courier New"));
	m_CtrlFrom.SetFont(&m_font);
	m_CtrlTo.SetFont(&m_font);
	m_CtrlKey.SetFont(&m_font);
	m_CtrlKey.SetLimitText(1);
	m_CtrlAlphCode.SetLimitText(getCifLength());
	m_CtrlFrom.SetWindowText(theApp.TextOptions.m_alphabet);
	m_CtrlTo.SetWindowText  ("");
	m_CtrlKey.SetWindowText ("");

	GetDlgItem(IDC_BUTTON_TxtOpt)->EnableWindow(!bHexEnabled); //On HexDump disable button


	int length = theApp.TextOptions.m_alphabet.GetLength();
	if ( length % 2 )
	{
		m_CtrlRadioRot13.EnableWindow(FALSE);
		LoadString(AfxGetInstanceHandle(),IDS_ROT13_INFO_NEGATIVE,pc_str,STR_LAENGE_STRING_TABLE);
		m_CtrlMessageRot13.SetWindowText(pc_str);
	}

	LoadString(AfxGetInstanceHandle(),IDS_ROT13_CAESAR_CASE,pc_str,STR_LAENGE_STRING_TABLE);
	char l_str[1024];
	sprintf(l_str, pc_str, length);
	m_CtrlShowAlSize.SetWindowText(l_str);

	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1); 
	CheckRadioButton(IDC_RADIO5, IDC_RADIO6, IDC_RADIO5);
	UpdateData();


	firstPosNull = 1;
	alphCode = 0;
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS) == ERROR_SUCCESS)
	{
		
		CT_READ_REGISTRY_DEFAULT(firstPosNull, "firstPosNull", firstPosNull);
		CT_READ_REGISTRY_DEFAULT(alphCode,"alphCode",alphCode);
		
		UpdateData(false);

		CT_CLOSE_REGISTRY();
	}
	if(!alphCode)
		CheckRadioButton(IDC_RADIO5, IDC_RADIO6, IDC_RADIO5);
	else
		CheckRadioButton(IDC_RADIO5, IDC_RADIO6, IDC_RADIO6);


	if(firstPosNull)
		CheckRadioButton(IDC_RADIO3, IDC_RADIO4, IDC_RADIO3);
	else
		CheckRadioButton(IDC_RADIO3, IDC_RADIO4, IDC_RADIO4);

	OnCaesarRad();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
void CDlgRot13Caesar::EnableAlphCode()
{
	alphCode = 1;
	if(caesarSelected)
		OnCaesarRad();
}
void CDlgRot13Caesar::DisableAlphCode()
{
	alphCode = 0;
	if(caesarSelected)
		OnCaesarRad();
}
void CDlgRot13Caesar::OnRot13Rad()
{
	CString Rot13Key = theApp.TextOptions.m_alphabet.GetAt(theApp.TextOptions.m_alphabet.GetLength() / 2 -1);
	m_CtrlKey.SetWindowText(Rot13Key);
	m_CtrlAlphCode.SetWindowText(getAlphCode(Rot13Key));
	m_CtrlKey.EnableWindow(FALSE);
	m_CtrlAlphCode.EnableWindow(FALSE);
	m_type = IDS_STRING_ROT13;
	m_paste.EnableWindow(FALSE);
	caesarSelected = 0;
}

void CDlgRot13Caesar::OnCaesarRad()
{
	if ( CheckPasteKeyVariant(IDS_CRYPT_CAESAR) || CheckPasteKeyVariant(IDS_CRYPT_ROT13) )
		m_paste.EnableWindow(TRUE);
	else
		m_paste.EnableWindow(FALSE);

	if(alphCode)
	{
		m_CtrlKey.EnableWindow(FALSE);
		m_CtrlAlphCode.EnableWindow(TRUE);
		m_CtrlAlphCode.SetFocus();
	}
	else
	{
		m_CtrlKey.EnableWindow(TRUE);
		m_CtrlAlphCode.EnableWindow(FALSE);
		m_CtrlKey.SetFocus();
	}
	m_type = IDS_STRING_CAESAR;
	caesarSelected = 1;
}
void CDlgRot13Caesar::OnUpdateAlphCode()
{
	if(alphCode)
	{
		CString str;
		m_CtrlAlphCode.GetWindowText(str);
		if(str.GetLength() == 2)
		{
			m_CtrlKey.SetWindowText(getAlphChar(str));
		}
		else
			m_CtrlKey.SetWindowText("");
	}
}
void CDlgRot13Caesar::OnExitAlphCode()
{
		CString cs;
		m_CtrlAlphCode.GetWindowText(cs);


int alphLen = theApp.TextOptions.m_alphabet.GetLength();
	
	if(firstPosNull)
		alphLen--;

	if(cs.GetLength() != getCifLength())
	{
		for(int i=cs.GetLength();i<getCifLength();i++)
		{
			cs.Insert(0,"0");
		}
		m_CtrlAlphCode.SetWindowText(cs);
	}




	if(_ttoi(cs) < 1 )
	{
		cs.Empty();
		m_CtrlAlphCode.SetWindowText(cs);
	}
	else if(_ttoi(cs) > alphLen)
	{
		LoadString(AfxGetInstanceHandle(),IDS_ROT13_CAESAR_TOO_LARGE_KEY,pc_str,255);
		if(AfxMessageBox(pc_str,MB_YESNO,MB_ICONINFORMATION) == 6)
		{
			cs = "1";
			for(int i=cs.GetLength();i<getCifLength();i++)
				cs.Insert(0,"0");

			m_CtrlAlphCode.SetWindowText(cs);
		}
		else
			m_CtrlAlphCode.SetWindowText("");
	}
}

void CDlgRot13Caesar::OnUpdateKey()
{
	//if(!alphCode)
	//{
	static int BUSY = 0;  // FIXME
	if (BUSY) return;

	BUSY++;

	BOOL validKey_flag = FALSE;
	int cStart, cEnd;

	m_CtrlKey.GetSel(cStart, cEnd);

// Read the Key
	CString alphabet = theApp.TextOptions.m_alphabet;
	m_CtrlKey.GetWindowText(m_key);

// Process non empty text
	if ( !m_key.IsEmpty() ) 
	{
		if ( theApp.TextOptions.m_ConvertCase )  // Only Capital Letters ?
			m_key.MakeUpper();

		for (m_dist = 0; m_dist < alphabet.GetLength(); m_dist++)
			if ( m_key == alphabet.GetAt(m_dist) )
			{
				// Inform about the Caesar distance
				if(firstPosNull)
                    m_dist = (m_dist) % alphabet.GetLength();
				else
					m_dist = (m_dist+1) % alphabet.GetLength();

				//if(firstPosNull)
				//	m_dist--;

				CString target;
				target.Format("%d", m_dist);   

				m_dist_control.SetWindowText(target);

				// Output the encryption mapping
				char to[1024];
				for (int ii = 0; ii < alphabet.GetLength(); ii ++)
				{
					to[ii] = alphabet.GetAt((ii+m_dist) % alphabet.GetLength());
				}
				to[ii] = '\0';
				m_CtrlTo.SetWindowText(to);

				// 
				m_CtrlKey.SetWindowText(m_key);

				// Button Management
				m_EncryptionButton.EnableWindow();
				m_DecryptionButton.EnableWindow();
				validKey_flag = TRUE;
				break;
			}
	}
	if ( !validKey_flag ) // ALL BLANK
	{
		m_dist_control.SetWindowText("");
		m_CtrlKey.SetWindowText("");
		m_CtrlTo.SetWindowText("");
		m_EncryptionButton.EnableWindow(FALSE);
		m_DecryptionButton.EnableWindow(FALSE);
	}
	m_CtrlKey.SetSel(cStart, cEnd);

	BUSY--;
	if(!alphCode)
	{

				CString str;
				m_CtrlKey.GetWindowText(str);
				m_CtrlAlphCode.SetWindowText(getAlphCode(str));
	}
	//}
}

char CDlgRot13Caesar::CheckPasteKeyVariant(int SID)
{
	CString cs;
	char ch_key = '\0';
	LoadString(AfxGetInstanceHandle(),SID,pc_str,STR_LAENGE_STRING_TABLE);

	if ( PasteKey(pc_str,cs) )
		if (0 <= theApp.TextOptions.m_alphabet.Find(cs))
			ch_key = cs.GetBuffer(cs.GetLength())[0];
	return ch_key;
}

void CDlgRot13Caesar::OnPasteKey() 
{
	char ch_key[2]; ch_key[1] = '\0';
	ch_key[0] = CheckPasteKeyVariant(IDS_CRYPT_CAESAR);
	if ( !ch_key[0] )
		ch_key[0] = CheckPasteKeyVariant(IDS_CRYPT_ROT13);

	if ( ch_key[0] )
		m_CtrlKey.SetWindowText(ch_key);
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_ROT13_CAESAR_BAD_KEY,pc_str,255);
		AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
	}
}

void CDlgRot13Caesar::OnEncrypt() 
{
	UpdateData(true);
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(unsigned long(firstPosNull), "firstPosNull");
		CT_WRITE_REGISTRY(unsigned long(alphCode), "alphCode");
		CT_CLOSE_REGISTRY();
	}
	m_Decrypt = 0;
	OnOK();
}

void CDlgRot13Caesar::OnDecrypt() 
{
	UpdateData(true);
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(unsigned long(firstPosNull), "firstPosNull");
		CT_WRITE_REGISTRY(unsigned long(alphCode), "alphCode");
		CT_CLOSE_REGISTRY();
	}
	m_Decrypt = 1;
	OnOK();	
}
CString CDlgRot13Caesar::getAlphCode(CString alphChar)
{
	CString str;
	for(int i=0;i<theApp.TextOptions.m_alphabet.GetLength();i++)
	{
		if(theApp.TextOptions.m_alphabet[i] == alphChar)
		{
			if(!firstPosNull)i++;
			str.Format("%d",i);
			if(str.GetLength() == 1)
				str.Insert(0,"0");
			return str;
		}
	}
	return "";
}
CString CDlgRot13Caesar::getAlphChar(CString alphPos)
{	
	int pos = _ttoi(alphPos);
	if(!firstPosNull)pos--;
	if(pos < 0 || pos >= theApp.TextOptions.m_alphabet.GetLength())
	{
	//	m_CtrlAlphCode.SetWindowText("");
		return "";
	}
	else
		return theApp.TextOptions.m_alphabet[pos];
}
void CDlgRot13Caesar::EnableFirstPosNull()
{
	firstPosNull = 1;
	CString str;
	if(alphCode)
	{
		m_CtrlAlphCode.GetWindowText(str);
		m_CtrlKey.SetWindowText(getAlphChar(str));
	}
	else
	{
		m_CtrlKey.GetWindowText(str);
		m_CtrlAlphCode.SetWindowText(getAlphCode(str));
	}
}
void CDlgRot13Caesar::DisableFirstPosNull()
{
	firstPosNull = 0;
	CString str;
	if(alphCode)
	{
		m_CtrlAlphCode.GetWindowText(str);
		m_CtrlKey.SetWindowText(getAlphChar(str));
	}
	else
	{
		m_CtrlKey.GetWindowText(str);
		m_CtrlAlphCode.SetWindowText(getAlphCode(str));
	}
}
void CDlgRot13Caesar::OnTxtOptions()
{

	theApp.TextOptions.DoModal();

	if(alphCode)
		OnUpdateAlphCode();
	else
		OnUpdateKey();
	if(caesarSelected)
		OnCaesarRad();
	else
		OnRot13Rad();

	
	m_CtrlFrom.SetWindowText(theApp.TextOptions.m_alphabet);

	int length = theApp.TextOptions.m_alphabet.GetLength();
	if ( length % 2 )
	{
		m_CtrlRadioRot13.EnableWindow(FALSE);
		LoadString(AfxGetInstanceHandle(),IDS_ROT13_INFO_NEGATIVE,pc_str,STR_LAENGE_STRING_TABLE);
		m_CtrlMessageRot13.SetWindowText(pc_str);
	}
	else
	{
		m_CtrlRadioRot13.EnableWindow(TRUE);
		m_CtrlMessageRot13.SetWindowText("");
	}
m_CtrlKey.SetFont(&m_font);
	LoadString(AfxGetInstanceHandle(),IDS_ROT13_CAESAR_CASE,pc_str,STR_LAENGE_STRING_TABLE);
	char l_str[1024];
	sprintf(l_str, pc_str, length);
	m_CtrlShowAlSize.SetWindowText(l_str);


}
int CDlgRot13Caesar::getCifLength()
{
	int length = theApp.TextOptions.m_alphabet.GetLength();
	CString str;
	str.Format("%d",length);

	return str.GetLength();

}