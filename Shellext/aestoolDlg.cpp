// aestoolDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "aestool.h"
#include "aestoolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAestoolDlg Dialogfeld

CAestoolDlg::CAestoolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAestoolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAestoolDlg)
	m_title = _T("");
	m_NameSrc = _T("");
	m_NameDst = _T("");
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAestoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAestoolDlg)
	DDX_Control(pDX, IDC_BUTTON2, m_SucheDst);
	DDX_Control(pDX, IDC_BUTTON1, m_SucheSrc);
	DDX_Text(pDX, IDC_STATIC4, m_title);
	DDX_Text(pDX, IDC_EDIT2, m_NameSrc);
	DDX_Text(pDX, IDC_EDIT3, m_NameDst);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAestoolDlg, CDialog)
	//{{AFX_MSG_MAP(CAestoolDlg)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnSucheSrc)
	ON_BN_CLICKED(IDC_BUTTON2, OnSucheDst)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAestoolDlg Nachrichten-Handler

BOOL CAestoolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{	
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen

	// EXEFile bestimmen
	GetModuleFileName(GetModuleHandle(NULL), EXEName.GetBuffer(512), 511);
	EXEName.ReleaseBuffer();
	EXEFile.Open(EXEName, CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary, NULL);
	EXEFile.Seek(-12, CFile::end);
	EXEFile.Read(& DataLen, sizeof(long));
	EXEFile.Read(& NameLen, sizeof(long));
	EXEFile.Read(& Magic, sizeof(long));
	if( Magic == FILE_MAGIC ) { // restore encrypted data
		m_direction = DIR_DECRYPT;
		m_title = "Entschlüsseln einer Datei";
		EXEFile.Seek(-12-NameLen, CFile::end);
		EXEFile.Read(OrgName.GetBuffer(NameLen+2), NameLen);
		OrgName.GetBuffer(NameLen+2)[NameLen]=0;
		OrgName.ReleaseBuffer();
		m_NameSrc = EXEName;
		m_SucheSrc.EnableWindow(FALSE);
		m_NameDst = OrgName;
		m_SucheDst.EnableWindow(TRUE);
	}
	else { // create a new encrypted file
		m_direction = DIR_ENCRYPT;
		m_title = "Verschlüsseln einer Datei";
		m_SucheSrc.EnableWindow(TRUE);
		m_SucheDst.EnableWindow(FALSE);
	}

	UpdateData(FALSE);

	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CAestoolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CAestoolDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CAestoolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CAestoolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAestoolDlg::OnSucheSrc() 
{
	int p1,p2;

	CFileDialog Dlg(TRUE, NULL, m_NameSrc, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		"All Files (*.*)|*.*||", this);
	if(IDCANCEL == Dlg.DoModal()) return;
	m_NameSrc = Dlg.GetPathName();
	m_NameDst = Dlg.GetPathName();
	p1 = m_NameDst.ReverseFind('.');
	p2 = m_NameDst.ReverseFind('\\');
	if(p1 > p2) { // name extension found
		m_NameDst = m_NameDst.Left(p1);
		if(Dlg.GetFileExt().CompareNoCase("exe")) { // extension not .exe
			m_NameDst += ".exe";
		}
		else { // extension .exe
			m_NameDst += "x.exe";
		}
	}
	else { // No name extension found
		m_NameDst += ".exe";
	}
	m_SucheDst.EnableWindow(TRUE);
	UpdateData(FALSE);
}

void CAestoolDlg::OnSucheDst() 
{
	CFileDialog Dlg(FALSE, NULL, m_NameDst, OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		(m_direction == DIR_ENCRYPT?"Exe Files (*.exe)|*.exe||":"All Files (*.*)|*.*||"), this);

	if(IDCANCEL == Dlg.DoModal()) return;
	m_NameDst = Dlg.GetPathName();
	UpdateData(FALSE);
}

void CAestoolDlg::OnOK() 
{
	CFile OutFile;
	CFileException e;
	char *buffer;
	int bufflen, i;

	OutFile.Open(m_NameDst, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary, &e);
	if(m_direction == DIR_ENCRYPT) {// Verschlüsselung
		CFile SrcFile;
		SrcFile.Open(m_NameSrc, CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary, NULL);
		DataLen = SrcFile.GetLength();
		bufflen = max(DataLen+16, 4096);
		buffer = (char *) malloc(bufflen);
		// copy EXEFile
		EXEFile.SeekToBegin();
		while(i=EXEFile.ReadHuge(buffer, bufflen))
			OutFile.WriteHuge(buffer, bufflen);
		// load Sourcedata
		SrcFile.ReadHuge(buffer, DataLen);
		SrcFile.Close();

		// encrypt data

		// store data
		OutFile.WriteHuge(buffer, DataLen);
		free (buffer);

		// store misc data
		// store Filename
		NameLen = m_NameSrc.GetLength() - 1 - m_NameSrc.ReverseFind('\\');
		OutFile.Write(m_NameSrc.Right(NameLen), NameLen);

		// store lengthes, magic
		Magic = FILE_MAGIC;
		OutFile.Write(&DataLen, sizeof(long));
		OutFile.Write(&NameLen, sizeof(long));
		OutFile.Write(&Magic, sizeof(long));
	}
	else { // Entschlüsselung
		bufflen = DataLen;
		buffer = (char *) malloc(bufflen);

		// Load Sourcedata
		EXEFile.Seek( - 12 - DataLen - NameLen, CFile::end);
		EXEFile.ReadHuge(buffer, DataLen);

		// decrypt

		// store data
		OutFile.WriteHuge(buffer, DataLen);

		free (buffer);
	}

	OutFile.Close();
	EXEFile.Close();

	CDialog::OnOK();
}
