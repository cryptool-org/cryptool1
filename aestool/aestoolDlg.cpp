// aestoolDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "aestool.h"
#include "aestoolDlg.h"
#include "rijndael-api-fst.h"
#include "splash.h"
#include "help.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CAestoolApp theApp;

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
	m_HexString = _T("");
	m_Radio = -1;
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAestoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAestoolDlg)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_RADIO1, m_Radio1Ctl);
	DDX_Control(pDX, IDC_RADIO2, m_Radio2Ctl);
	DDX_Control(pDX, IDC_EDIT3, m_CNameDst);
	DDX_Control(pDX, IDC_EDIT2, m_CNameSrc);
	DDX_Control(pDX, IDC_EDIT1, m_HexIn);
	DDX_Control(pDX, IDC_BUTTON2, m_SucheDst);
	DDX_Control(pDX, IDC_BUTTON1, m_SucheSrc);
	DDX_Text(pDX, IDC_STATIC4, m_title);
	DDX_Text(pDX, IDC_EDIT2, m_NameSrc);
	DDX_Text(pDX, IDC_EDIT3, m_NameDst);
	DDX_Text(pDX, IDC_EDIT1, m_HexString);
	DDV_MaxChars(pDX, m_HexString, 47);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio);
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
	ON_BN_CLICKED(IDC_RADIO1, OnRadio)
	ON_BN_CLICKED(IDC_BUTTON3, OnHelp)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
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

	m_Radio = 0;
	m_OK.EnableWindow(FALSE);
	ScanCMDLine(theApp.m_lpCmdLine);

	// EXEFile bestimmen
//	EXEName = m_CMD_inName;
	GetModuleFileName(GetModuleHandle(NULL), EXEName.GetBuffer(512), 511);
	EXEName.ReleaseBuffer();

	if(m_CMD_inName.IsEmpty() || !TestEncryptedFile(m_CMD_inName)) {
		if (!TestEncryptedFile(EXEName)) { // create a new encrypted file
			m_SucheSrc.EnableWindow(TRUE);
			m_SucheDst.EnableWindow(FALSE);
			if(!m_CMD_inName.IsEmpty()) {
				FILE *ft;
				m_NameSrc = m_CMD_inName;
				if(ft = fopen(m_NameSrc, "r")) {
					fclose(ft);
					SetDestName();
					if(!m_CMD_outName.IsEmpty()) m_NameDst = m_CMD_outName;
					if(m_HexIn.BinLen > 0) { // do encryption and exit
						DoEncrypt();
						EndDialog( IDOK );
					}
				}
			}
		}
		else {
			CSplash dia;
			dia.DoModal();
			if(m_HexIn.BinLen > 0) { // do decryption and exit
				if(IDRETRY != DoDecrypt()) EndDialog( IDOK );
			}
		}
	}

	UpdateData(FALSE);
	m_CNameSrc.SetSel(0,-1);
	m_CNameDst.SetSel(0,-1);

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
	UpdateData(TRUE);
	CFileDialog Dlg(TRUE, NULL, m_NameSrc, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		"All Files (*.*)|*.*|EXE Files (*.exe)|*.exe|AES Files (*.aes)|*.aes||", this);
	if(IDCANCEL == Dlg.DoModal()) return;
	m_NameSrc = Dlg.GetPathName();
	m_direction = DIR_ENCRYPT;
	if(TestEncryptedFile(m_NameSrc)) {// verschlüsselte Datei --> entschlüsseln
		m_Radio1Ctl.EnableWindow(FALSE);
		m_Radio2Ctl.EnableWindow(FALSE);
	}
	else { // neue Datei verschlüsseln
		m_Radio1Ctl.EnableWindow(TRUE);
		m_Radio2Ctl.EnableWindow(TRUE);
		SetDestName();
	}
	if(m_HexString.IsEmpty()) m_HexIn.SetFocus();
	else {
		m_OK.EnableWindow(TRUE);
		m_OK.SetFocus();
	}
	UpdateData(FALSE);
	m_CNameSrc.SetSel(0,-1);
	m_CNameDst.SetSel(0,-1);
}

void CAestoolDlg::OnSucheDst() 
{
	CString mask;

	if(m_direction == DIR_DECRYPT)
		mask = "All Files (*.*)|*.*||";
	else if(m_Radio == 0)
		mask = "Exe Files (*.exe)|*.exe||";
	else
		mask = "AES Files (*.aes)|*.aes||";
	UpdateData(TRUE);
	CFileDialog Dlg(FALSE, NULL, m_NameDst, OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		mask, this);

	if(IDCANCEL == Dlg.DoModal()) return;
	m_NameDst = Dlg.GetPathName();
	if(m_HexString.IsEmpty()) m_HexIn.SetFocus();
	else m_OK.SetFocus();
	UpdateData(FALSE);
	m_CNameSrc.SetSel(0,-1);
	m_CNameDst.SetSel(0,-1);
}

void CAestoolDlg::OnOK() 
{
	if(m_direction == DIR_ENCRYPT) {// Verschlüsselung
		DoEncrypt();
	}
	else { // Entschlüsselung
		if(IDRETRY == DoDecrypt()) return;
	}

	CDialog::OnOK();
}

void CAestoolDlg::ScanCMDLine(char * cmd)
{
	CString l;
	char c;
	int state = 0, len;

	l = cmd;
	l.TrimLeft();
	l.TrimRight();

	while(l.GetLength()) {
		if(l.GetAt(0) == '-') { // tagged argument
			c = l.GetAt(1);
			l.Delete(0,2);
			l.TrimLeft();
			switch(c) {
			case ('i'):
				len = findStr(l);
				m_CMD_inName = l.Left(len);
				l.Delete(0, len);
				l.TrimLeft();
				break;
			case ('o'):
				len = findStr(l);
				m_CMD_outName = l.Left(len);
				l.Delete(0, len);
				l.TrimLeft();
				break;
			case ('k'):
				len = findStr(l);
				m_CMD_inKey = l.Left(len);
				l.Delete(0, len);
				l.TrimLeft();
				break;
			}
		}
		else { // positional argument
			if(m_CMD_inName.IsEmpty()) { // set in name
				len = findStr(l);
				m_CMD_inName = l.Left(len);
				l.Delete(0, len);
				l.TrimLeft();
			}
			else if(m_CMD_outName.IsEmpty()) { // set out name
				len = findStr(l);
				m_CMD_outName = l.Left(len);
				l.Delete(0, len);
				l.TrimLeft();
			}
			else if(m_CMD_inKey.IsEmpty()) { // set key
				len = findStr(l);
				m_CMD_inKey = l.Left(len);
				l.Delete(0, len);
				l.TrimLeft();
			}
		}
	}

}

int CAestoolDlg::findStr(CString l)
{
	int i, f;

	for(f=i=0; i<l.GetLength(); i++) {
		if(l.GetAt(i) == '\"') { // toggle "-mode
			f = 1 - f;
		}
		else if(f) { // "-mode, skip all
			continue;
		}
		else { // normal mode
			if(strchr(" \r\n\t", l.GetAt(i)))
				break;
		}
	}
	return i;
}

void CAestoolDlg::SetDestName()
{
	int p1, p2, l;
	CString ext1, ext2;

	if(m_Radio == 0) ext1 = ".exe";
	else ext1 = ".aes";
	m_NameDst = m_NameSrc;
	p1 = m_NameDst.ReverseFind('.');
	p2 = m_NameDst.ReverseFind('\\');
	l = m_NameDst.GetLength();
	if(p1 > p2) { // name extension found
		ext2 = m_NameDst.Right(l-p1);
		m_NameDst = m_NameDst.Left(p1);
		if(ext1.CompareNoCase(ext2)) { // extension not .exe (or .aes)
			m_NameDst += ext1;
		}
		else { // extension .exe
			m_NameDst += "x" + ext1;
		}
	}
	else { // No name extension found
		m_NameDst += ext1;
	}
	m_Radio1Ctl.EnableWindow(FALSE);
	m_Radio2Ctl.EnableWindow(FALSE);
	m_SucheDst.EnableWindow(TRUE);
}

void CAestoolDlg::DoEncrypt()
{
	CFile OutFile;
	CFile EXEFile;
	CFileException e;
	char *buffer, keybuffhex[64],keybuffbin[32];
	int bufflen, i, keylen;

	OutFile.Open(m_NameDst, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary, &e);

	CFile SrcFile;
	SrcFile.Open(m_NameSrc, CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary, NULL);
	DataLen = SrcFile.GetLength();
	bufflen = max(DataLen+16, 4096);
	buffer = (char *) malloc(bufflen);
	if(m_Radio == 0) { // copy EXE-File first
		EXEFile.Open(EXEName, CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary, NULL);
		while(i=EXEFile.ReadHuge(buffer, bufflen))
			OutFile.WriteHuge(buffer, bufflen);
		EXEFile.Close();
	}
	// load Sourcedata
	SrcFile.ReadHuge(buffer, DataLen);
	SrcFile.Close();

	// encrypt data
	// insert padding
	buffer[DataLen]=1;
	for(i=DataLen+1;i<bufflen;i++) buffer[i]=0;
	DataLen = (DataLen+16) & ~15;
	//encrypt

	keylen = m_HexIn.BinLen;

	for(i=0;i<32;i++) keybuffbin[i]=0;
	for(i=0;i<keylen; i++) keybuffbin[i] = m_HexIn.BinData[i];

	if(keylen <= 16) keylen = 16;
	else if(keylen <= 24) keylen = 24;
	else keylen = 32;

	for(i=0; i<keylen; i++) {
		sprintf(keybuffhex+2*i,"%02.2X",keybuffbin[i]);
	}
	keyInstanceRijndael keyin;
	cipherInstanceRijndael cipher;
	makeKeyRijndael(&keyin,DIR_ENCRYPT,keylen*8,keybuffhex);
	cipherInitRijndael(&cipher,MODE_CBC,"00000000000000000000000000000000");
	blockEncryptRijndael(&cipher, &keyin, (unsigned char *)buffer, DataLen*8, (unsigned char *)buffer);

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

	OutFile.Close();
}

int CAestoolDlg::DoDecrypt()
{
	CFile SrcFile;
	CFile OutFile;
	CFileException e;
	char *buffer1, *buffer2, keybuffhex[64],keybuffbin[32];
	int bufflen, i, keylen;

	bufflen = DataLen;
	buffer1 = (char *) malloc(bufflen);
	buffer2 = (char *) malloc(bufflen);

	// Load Sourcedata
	SrcFile.Open(m_NameSrc, CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary, NULL);
	SrcFile.Seek( - 12 - DataLen - NameLen, CFile::end);
	SrcFile.ReadHuge(buffer1, DataLen);
	SrcFile.Close();

	// decrypt

	keylen = m_HexIn.BinLen;

	for(i=0;i<32;i++) keybuffbin[i]=0;
	for(i=0;i<keylen; i++) keybuffbin[i] = m_HexIn.BinData[i];

	if(keylen <= 16) keylen = 16;
	else if(keylen <= 24) keylen = 24;
	else keylen = 32;

	for(i=0; i<keylen; i++) {
		sprintf(keybuffhex+2*i,"%02.2X",keybuffbin[i]);
	}
	keyInstanceRijndael keyin;
	cipherInstanceRijndael cipher;
	makeKeyRijndael(&keyin,DIR_DECRYPT,keylen*8,keybuffhex);
	cipherInitRijndael(&cipher,MODE_CBC,"00000000000000000000000000000000");
	blockDecryptRijndael(&cipher, &keyin, (unsigned char *) buffer1, DataLen*8, (unsigned char *) buffer2);


	// remove padding
	// remove trailing 0's
	for(i=DataLen-1;buffer2[i]==0;i--);
	// check trailing 1
	if(buffer2[i]!=1) { // display error
		return AfxMessageBox(IDS_STRING_DECERROR, MB_RETRYCANCEL );
	}
	DataLen = i;

	// store data
	OutFile.Open(m_NameDst, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary, &e);
	OutFile.WriteHuge(buffer2, DataLen);

	free (buffer1);
	free (buffer2);

	OutFile.Close();

	return IDOK;
}

int CAestoolDlg::TestEncryptedFile(CString Filename)
{
	m_SrcFile.Open(Filename, CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary, NULL);
	m_SrcFile.Seek(-12, CFile::end);
	m_SrcFile.Read(& DataLen, sizeof(long));
	m_SrcFile.Read(& NameLen, sizeof(long));
	m_SrcFile.Read(& Magic, sizeof(long));
	if( Magic == FILE_MAGIC ) { // restore encrypted data
		m_direction = DIR_DECRYPT;
		AfxFormatString1(m_title, IDS_STRING_DECRYPT, "");
		m_SrcFile.Seek(-12-NameLen, CFile::end);
		m_SrcFile.Read(OrgName.GetBuffer(NameLen+2), NameLen);
		OrgName.GetBuffer(NameLen+2)[NameLen]=0;
		OrgName.ReleaseBuffer();
		m_NameSrc = Filename;
		m_NameDst = OrgName;
		m_SucheDst.EnableWindow(TRUE);
		m_Radio1Ctl.EnableWindow(FALSE);
		m_Radio2Ctl.EnableWindow(FALSE);
		if(!m_CMD_outName.IsEmpty()) m_NameDst = m_CMD_outName;
		return 1;
	}
	m_direction = DIR_ENCRYPT;
	AfxFormatString1(m_title, IDS_STRING_ENCRYPT, "");
	return 0;
}

int CAestoolDlg::ChangeDestName()
{
	int p1;
	CString ext;

	if(m_Radio == 0) ext = ".exe";
	else ext = ".aes";
	p1 = m_NameDst.ReverseFind('.');
	m_NameDst = m_NameDst.Left(p1);
	m_NameDst += ext;
	if(!m_NameDst.CompareNoCase(m_NameSrc)) {
		m_NameDst = m_NameDst.Left(p1);
		m_NameDst += "x";
		m_NameDst += ext;
	}
	m_SucheDst.EnableWindow(TRUE);
	return 0;
}

void CAestoolDlg::OnRadio() 
{
	UpdateData();
	ChangeDestName();
	UpdateData(FALSE);
	m_CNameSrc.SetSel(0,-1);
	m_CNameDst.SetSel(0,-1);
}

void CAestoolDlg::OnHelp() 
{
	CHelp dia;

	dia.DoModal();
}

void CAestoolDlg::OnChangeEdit1() 
{
	UpdateData(TRUE);
	if(!m_HexString.IsEmpty()) {
		m_OK.EnableWindow(TRUE);
	}
}
