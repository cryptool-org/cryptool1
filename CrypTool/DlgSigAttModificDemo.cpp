// DlgSigAttModificDemo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSigAttModificDemo.h"
#include "FileTools.h"
#include "ModifiedDocumentForHashing.h"
#include "ModifiedDocument_Blanks.h"
#include "ModifiedDocument_Attachments.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSigAttModificDemo 


CDlgSigAttModificDemo::CDlgSigAttModificDemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSigAttModificDemo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSigAttModificDemo)
	m_hashvalue = _T("FF");
	m_sigbit = 8;
	m_method = 0;
	m_printable = 0;
	m_parity = 0;
	//}}AFX_DATA_INIT
}


void CDlgSigAttModificDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSigAttModificDemo)
	DDX_Control(pDX, IDC_METHOD, m_control_method);
	DDX_Control(pDX, IDC_RADIO4, m_control_unprintable);
	DDX_Control(pDX, IDC_RADIO3, m_control_printable);
	DDX_Control(pDX, IDC_CHECK2, m_control_double);
	DDX_Control(pDX, IDC_CHECK1, m_control_eol);
	DDX_Control(pDX, IDC_HASHVALUE, m_control_hashvalue);
	DDX_Text(pDX, IDC_HASHVALUE, m_hashvalue);
	DDX_Text(pDX, IDC_SIGBIT, m_sigbit);
	DDX_Radio(pDX, IDC_METHOD, m_method);
	DDX_Radio(pDX, IDC_RADIO3, m_printable);
	DDX_Text(pDX, IDC_PARITY, m_parity);
	DDV_MinMaxInt(pDX, m_parity, 0, 1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSigAttModificDemo, CDialog)
	//{{AFX_MSG_MAP(CDlgSigAttModificDemo)
	ON_BN_CLICKED(IDOK, OnModify)
	ON_BN_CLICKED(IDC_RADIO2, OnAttachment)
	ON_BN_CLICKED(IDC_METHOD, OnMethod)
	ON_BN_CLICKED(IDC_RADIO3, OnPrintable)
	ON_BN_CLICKED(IDC_RADIO4, OnUnprintable)
	ON_EN_UPDATE(IDC_HASHVALUE, OnUpdateHashvalue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSigAttModificDemo 

void CDlgSigAttModificDemo::OnModify() 
{
	UpdateData(TRUE);

	CAppDocument *NewDocument;
	char outfile[1024];
	CString msg;
	ifstream ifstr_Document;
	ofstream ofstr_Document;
	int ii, jj, DocumentLength;
	struct stat stat_object;

	if (FALSE == m_hashvalue.IsEmpty())
	{
		m_hashvalue.MakeLower();
		for (ii = 0; ii < m_hashvalue.GetLength(); ii ++)
		{
			if (!(m_hashvalue[ii] >= '0' && m_hashvalue[ii] <= '9'
				|| m_hashvalue[ii] >= 'a' && m_hashvalue[ii] <= 'f'))
			{
				m_control_hashvalue.SetSel(0, -1, 0);
				//UpdateData(FALSE);
				return;
			}
		}
	}

	if (0 == m_method && 1 != m_control_eol.GetCheck() && 1 != m_control_double.GetCheck())
	{
		msg.Format(IDS_STRING_SIG_ATT_NO_CHECK);
		MessageBox(msg, "CrypTool", MB_ICONEXCLAMATION | MB_APPLMODAL);
		m_control_eol.SetCheck(1);

		return;
	}

	ifstr_Document.open(m_Path, ios::in | ios::binary);
	if (!ifstr_Document)
	{
		return;
	}
	
	stat((const char *) m_Path, & stat_object);
	if (0 == stat_object.st_size)
	{
		return;
	}
	DocumentLength = stat_object.st_size;

#ifdef _SIG_ATT_SPEED_INCREMENT

	DocumentLength += 2;

#endif

	char *Text= new char[DocumentLength];

	ii = 0;
	while (0 == ifstr_Document.eof())
	{
		ifstr_Document.read(Text + ii, 1);
		ii ++;
	}
	ifstr_Document.close();

	ModifiedDocumentForHashing *m_Document;
	if (!m_method)
	{
		m_Document = new ModifiedDocument_Blanks(Text, DocumentLength, m_sigbit,
			m_control_eol.GetCheck(), m_control_double.GetCheck());
	}
	else
	{
		m_Document = new ModifiedDocument_Attachments(Text, DocumentLength, m_sigbit, m_printable);
	}

	char *HashValue = new char[(m_hashvalue.GetLength() + 1) / 2];
	char temp, value;
	

	for (ii = jj = 0; ii < m_hashvalue.GetLength(); ii ++)
	{
		if (m_hashvalue[ii] >= '0' && m_hashvalue[ii] <= '9')
		{
			temp = m_hashvalue[ii] - 48;
		}
		else
		{
			temp = m_hashvalue[ii] - 87;
		}

		if (!(ii % 2))
		{
			value = 16 * temp;
		}
		else
		{
			value += temp;
			HashValue[jj] = value;
			jj ++;
		}		
	}

	m_Document->ModifyDocument(HashValue);

	GetTmpName(outfile,"cry",".tmp");
	ofstr_Document.open(outfile, ios::out | ios::binary);
	if (!ofstr_Document)
	{
		return;
	}
	ofstr_Document.write(m_Document->GetDocumentData(), m_Document->GetDocumentLength());
	ofstr_Document.close();
	NewDocument = theApp.OpenDocumentFileNoMRU(outfile);
	
	char title[1024];
	_snprintf(title, sizeof(title) - 1, "Modifikation von <%s>", m_Title);
	NewDocument->SetTitle(title);

	delete m_Document;
	delete []HashValue;
}

void CDlgSigAttModificDemo::OnAttachment() 
{
	m_method = 1;	

	m_control_eol.EnableWindow(FALSE);
	m_control_double.EnableWindow(FALSE);
	m_control_printable.EnableWindow(TRUE);
	m_control_unprintable.EnableWindow(TRUE);

	UpdateData(FALSE);
}

void CDlgSigAttModificDemo::OnMethod() 
{
	m_method = 0;

	m_control_eol.EnableWindow(TRUE);
	m_control_double.EnableWindow(TRUE);
	m_control_printable.EnableWindow(FALSE);
	m_control_unprintable.EnableWindow(FALSE);
	
	UpdateData(FALSE);	
}

void CDlgSigAttModificDemo::OnPrintable() 
{
	m_printable = 0;	
}

void CDlgSigAttModificDemo::OnUnprintable() 
{
	m_printable = 1;	
}

void CDlgSigAttModificDemo::OnUpdateHashvalue() 
{
	char temp;
	int ii, parity = 0, table[16] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0}; // quick and dirty

	UpdateData(TRUE);
	for (ii = 0; ii < m_hashvalue.GetLength(); ii ++)
	{
		if (m_hashvalue[ii] >= '0' && m_hashvalue[ii] <= '9')
		{
			temp = m_hashvalue[ii] - 48;
		}
		else
		{
			temp = m_hashvalue[ii] - 87;
		}

		parity += table[temp];
	}
	m_parity = parity % 2;
	UpdateData(FALSE);
}

void CDlgSigAttModificDemo::SetData(char *Path, const CString &Title)
{
	m_Path = Path;
	m_Title = Title;
}
