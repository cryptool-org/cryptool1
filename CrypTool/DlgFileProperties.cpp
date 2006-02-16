// DlgFileProperties.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgFileProperties.h"
#include "DlgShowKey.h"
#include "DlgShowKeyHill10x10.h"
#include "DlgShowKeyHill5x5.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFileProperties 


CDlgFileProperties::CDlgFileProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFileProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFileProperties)
	m_tmpFilename = _T("");
	m_fileType = _T("");
	m_fileSize = _T("");
	m_strTitle = _T("");
	m_strFilePath = _T("");
	m_strPathTemp = _T("");
	m_fileName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgFileProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFileProperties)
	DDX_Text(pDX, IDC_EDIT1, m_tmpFilename);
	DDX_Text(pDX, IDC_EDIT132, m_fileType);
	DDX_Text(pDX, IDC_EDIT2, m_fileSize);
	DDX_Text(pDX, IDC_EDIT4, m_strTitle);
	DDX_Text(pDX, IDC_EDIT5, m_strFilePath);
	DDX_Text(pDX, IDC_EDIT6, m_strPathTemp);
	DDX_Text(pDX, IDC_EDIT3, m_fileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFileProperties, CDialog)
	//{{AFX_MSG_MAP(CDlgFileProperties)
	ON_BN_CLICKED(IDC_BUTTON1, OnShowKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgFileProperties 


void CDlgFileProperties::OnShowKey() 
{
	if ( m_keyType == SCHLUESSEL_LINEAR )
	{
		CDlgShowKey AusgabeFenster;
		char CryptMethod[KEYDATA_HASHSTRING_LENGTH+1];
		if ( ExtractStrKeyType( CryptMethod, m_strTitle ) )
		{
			strcpy( AusgabeFenster.strTitle, CryptMethod );
			AusgabeFenster.m_Key = m_key;
			AusgabeFenster.DoModal();
		}
		else
		{
			// ToDo: passende Fehlermeldung
		}
	}
	else if ( m_keyType == SCHLUESSEL_QUADRATISCH )
	{
		// Hill Verfahren: 
		// Format des Schluessels: Zeilenweise, durch jeweils ein Leerzeichen getrennt
		// HILL_MAX_DIM=5: 5x5 hat also 25+4=29 Zeichen
		if (m_key.GetLength() <= HILL_MAX_DIM*HILL_MAX_DIM+(HILL_MAX_DIM-1))
		{
			CDlgShowKeyHill5x5 AusgabeFenster;
			AusgabeFenster.SchluesselAnzeigen(m_key);				
			// Es wird immer der Schluessel zum Verschluesseln angezeigt
			AusgabeFenster.m_decrypt = FALSE;
			AusgabeFenster.DoModal();
		}
		else
		{
			CDlgShowKeyHill10x10 AusgabeFenster;
			AusgabeFenster.SchluesselAnzeigen(m_key);				
			// Es wird immer der Schluessel zum Verschluesseln angezeigt
			AusgabeFenster.m_decrypt = FALSE;
			AusgabeFenster.DoModal();
		}
	}
	else
	{
		ASSERT(false);
	}
}

BOOL CDlgFileProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();

	VERIFY(m_showKey.AutoLoad(IDC_BUTTON1,this));
	
	if (m_key.GetLength())
		m_showKey.EnableWindow();
	else
		m_showKey.EnableWindow(FALSE);
	// TODO: Zus�tzliche Initialisierung hier einf�gen
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

void CDlgFileProperties::copyFileInfos(CString contentName, 
									   CString fName, CString title,
									   CString key, int keyType, CString strView)
{
	

	CFile file;
	file.Open(contentName, CFile::modeRead );
	{
		char *str = itoa_fmt (file.GetLength());
		LoadString(AfxGetInstanceHandle(),IDS_BYTES,pc_str,STR_LAENGE_STRING_TABLE);
		m_fileSize.Format("%s %s", str, pc_str);
		delete []str;
	}
	m_strTitle = title;

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
// Handle Temporary FILE
	_splitpath( contentName.GetBuffer(contentName.GetLength()), drive, dir, fname, ext );	
	m_tmpFilename = CString(fname) + CString(ext);
	m_strPathTemp = CString(drive) + CString(dir);

// Handle Files + Filepath
	if (fName.GetLength())
	{
		_splitpath( fName.GetBuffer(fName.GetLength()), drive, dir, fname, ext );
		m_strFilePath = CString(drive) + CString(dir);
		m_fileName    = CString(fname) + CString(ext);
	}
	else
	{
		GetCurrentDirectory(_MAX_DIR, dir);
		m_strFilePath = dir;
		LoadString(AfxGetInstanceHandle(),IDS_FILENAME_NOT_YET,pc_str,STR_LAENGE_STRING_TABLE);
		m_fileName = pc_str;
	}

	m_key		= key;
	m_keyType	= keyType;

// 
	m_fileType = strView;
}
