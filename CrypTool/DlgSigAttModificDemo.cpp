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
	m_file = _T("");
	m_hashvalue = _T("");
	m_sigbit = 0;
	m_method = 0;
	m_printable = 0;
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
	DDX_Text(pDX, IDC_FILE, m_file);
	DDX_Text(pDX, IDC_HASHVALUE, m_hashvalue);
	DDX_Text(pDX, IDC_SIGBIT, m_sigbit);
	DDX_Radio(pDX, IDC_METHOD, m_method);
	DDX_Radio(pDX, IDC_RADIO3, m_printable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSigAttModificDemo, CDialog)
	//{{AFX_MSG_MAP(CDlgSigAttModificDemo)
	ON_BN_CLICKED(IDC_SERACH, OnSerach)
	ON_BN_CLICKED(IDOK, OnModify)
	ON_BN_CLICKED(IDC_RADIO2, OnAttachment)
	ON_BN_CLICKED(IDC_METHOD, OnMethod)
	ON_BN_CLICKED(IDC_RADIO3, OnPrintable)
	ON_BN_CLICKED(IDC_RADIO4, OnUnprintable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSigAttModificDemo 

void CDlgSigAttModificDemo::OnSerach() 
{
	UpdateData(TRUE);
	
	CString filename;

	CFileDialog FDlg(TRUE, NULL, filename, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		"All Files (*.*)|*.*|TXT Files (*.txt)|*.txt||", this);
	if (IDCANCEL == FDlg.DoModal())
	{
		return;
	}

	m_file = FDlg.GetPathName();

	UpdateData(FALSE);
}

void CDlgSigAttModificDemo::OnModify() 
{
	UpdateData(TRUE);

	CString msg;
	ifstream ifstr_Document;
	int ii, DocumentLength;
	struct stat stat_object;

	if (FALSE == m_hashvalue.IsEmpty())
	{
		for (ii = 0; ii < m_hashvalue.GetLength(); ii ++)
		{
			if (!(m_hashvalue[ii] >= '0' && m_hashvalue[ii] <= '9'
				|| m_hashvalue[ii] >= 'a' && m_hashvalue[ii] <= 'f'
				|| m_hashvalue[ii] >= 'A' && m_hashvalue[ii] <= 'F'))
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

	ifstr_Document.open(m_file, ios::in | ios::binary);
	if (!ifstr_Document)
	{
		return;
	}
	
	stat((const char *) m_file, & stat_object);
	if (0 == stat_object.st_size)
	{
		return;
	}
	DocumentLength = stat_object.st_size;

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
		m_Document = new ModifiedDocument_Blanks(Text, DocumentLength, m_sigbit, -12, -12);
	}
	else
	{
		m_Document = new ModifiedDocument_Attachments(Text, DocumentLength, m_sigbit, m_printable);
	}
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
