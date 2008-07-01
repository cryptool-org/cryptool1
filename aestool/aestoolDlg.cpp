/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


// aestoolDlg.cpp : Implementierungsdatei
// $Id$

#include "stdafx.h"
#include "io.h"
#include "aestool.h"
#include "aestoolDlg.h"
#include "aestoolcrypto.h"
#include "splash.h"
#include "help.h"
#include "direct.h"
#include <stdio.h>

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

CAestoolDlg::CAestoolDlg(CString key,CString in,CString out,CWnd* pParent /*=NULL*/)
	: m_CMD_inKey(key), m_CMD_inName(in), m_CMD_outName(out), 
	  CDialog(CAestoolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAestoolDlg)
	m_Format = -1;
	m_PWShowHide = 0;
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Format = 0;
	if (!out.IsEmpty())
		m_Format = out.Right(4).CompareNoCase(".exe") == 0 ? 0 : 1;
}

void CAestoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAestoolDlg)
	DDX_Control(pDX, IDC_STATIC_TITLE, m_CStaticTitle);
	DDX_Control(pDX, IDOK, m_CButtonOK);
	DDX_Control(pDX, IDC_RADIO_EXE, m_CRadioExe);
	DDX_Control(pDX, IDC_RADIO_AES, m_CRadioAes);
	DDX_Control(pDX, IDC_EDIT_SRC, m_CEditSrc);
	DDX_Control(pDX, IDC_EDIT_KEY, m_CHEditKey);
	DDX_Control(pDX, IDC_BUTTON_SRC, m_CButtonSrc);
	DDX_Radio(pDX, IDC_RADIO_PSHOW, m_PWShowHide);
	DDX_Radio(pDX, IDC_RADIO_EXE, m_Format);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAestoolDlg, CDialog)
	//{{AFX_MSG_MAP(CAestoolDlg)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SRC, OnSucheSrc)
	ON_BN_CLICKED(IDC_BUTTON3, OnHelp)
	ON_EN_CHANGE(IDC_EDIT_KEY, EnDisableOK)
	ON_EN_CHANGE(IDC_EDIT_SRC, OnChangeSrc)
	ON_BN_CLICKED(IDC_RADIO_PSHOW, OnRadioPWShow)
	ON_BN_CLICKED(IDC_RADIO_PHIDE, OnRadioPWHide)
	ON_BN_CLICKED(IDC_RADIO_EXE, OnRadioFormat)
	ON_BN_CLICKED(IDC_RADIO_AES, OnRadioFormat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAestoolDlg Nachrichten-Handler

BOOL CAestoolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//__asm int 3

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	//m_consoleDetached = (INVALID_HANDLE_VALUE == GetStdHandle(STD_OUTPUT_HANDLE) ||
	//					 _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),0) == -1);

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
	
	m_CButtonOK.EnableWindow(FALSE);

	m_CHEditKey.SetWindowText(m_CMD_inKey);
	m_CHEditKey.SetLimitText(95);
	// EXEFile bestimmen
	GetModuleFileName(GetModuleHandle(NULL), EXEName.GetBuffer(512), 511);
	EXEName.ReleaseBuffer();

	m_SrcInfo.setName(EXEName);
	if (m_SrcInfo.isEncrypted()) {
		m_CMD_inName = EXEName;
		UpdateData(FALSE);
#if 0 // FIXME LATER Warning is moved: "NOTE" in Help Dialog
		CSplash dia;
		if(IDCANCEL == dia.DoModal()) EndDialog( IDCANCEL );
#endif
	}
	m_CEditSrc.SetWindowText(m_CMD_inName);
	// m_CEditSrc.DragAcceptFiles();
	OnChangeSrc();

	UpdateData(FALSE);
	m_CEditSrc.SetSel(0,-1);

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
	CString name;
	m_CEditSrc.GetWindowText(name);
	CFileDialog Dlg(TRUE, NULL, name, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		"All Files (*.*)|*.*|EXE Files (*.exe)|*.exe|AES Files (*.aes)|*.aes||", this);
	if(IDCANCEL == Dlg.DoModal()) return;
	m_CEditSrc.SetWindowText(Dlg.GetPathName());
	int curPos = Dlg.GetPathName().GetLength();
	m_CEditSrc.SetSel(curPos, curPos);
	if (m_CHEditKey.BinLen == 0)
		m_CHEditKey.SetFocus();
	else 
		m_CButtonOK.SetFocus();
	//OnChangeSrc() does the real work
}

void CAestoolDlg::OnOK() 
{
	
	UpdateData(TRUE); // fetch m_Format

	InfoBlock infoblock;
	if (m_SrcInfo.isEncrypted())
		switch (infoblock.decrypt(m_SrcInfo,m_CHEditKey.BinData,m_CHEditKey.BinLen)) {
		case InfoBlock::CORRUPT:
			char stringBuffer[2048+1];
			char stringErrorMessage[2048+1];
			memset(stringBuffer, 0, 2048+1);
			memset(stringErrorMessage, 0, 2048+1);
			LoadString(AfxGetInstanceHandle(), IDS_STRING_KEYERROR, stringBuffer, 2048);
			sprintf(stringErrorMessage, stringBuffer, m_SrcInfo.getName().GetBuffer());
			AfxMessageBox(stringErrorMessage, MB_OK);
			m_CHEditKey.SetSel(0,-1); m_CHEditKey.SetFocus();
			return;
		case InfoBlock::NOMEM:
			AfxMessageBox(IDS_STRING_NOMEMORY,MB_OK);
			return;
		}

	CString mask;
	if(m_SrcInfo.isEncrypted())
		mask = "All Files (*.*)|*.*||";
	else if(m_Format == 0)
		mask = "Exe Files (*.exe)|*.exe||";
	else
		mask = "AES Files (*.aes)|*.aes||";
	CString dstname = 
		m_CMD_outName.IsEmpty() ? 
			defaultDstName(&m_SrcInfo,&infoblock,m_Format == 0) :
			m_CMD_outName;
	CFileDialog Dlg(FALSE, NULL, dstname, 
		OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY, mask, this);

	if(IDCANCEL == Dlg.DoModal()) return;
	dstname = Dlg.GetPathName();

	CString text = dstname;
	bool success;
	unsigned id;
	if(m_SrcInfo.isEncrypted()) {
		success = AesToolDecrypt(m_CHEditKey.BinData,m_CHEditKey.BinLen,
								 m_SrcInfo,dstname,text);
		id = success ? IDS_STRING_DECOK : IDS_STRING_DECERROR;
	} else {
		success = AesToolEncrypt(m_CHEditKey.BinData,m_CHEditKey.BinLen,
								 m_SrcInfo,dstname,
								 (m_Format == 0 ? (LPCTSTR)EXEName : 0),
								 text);
		id = success ? IDS_STRING_ENCOK : IDS_STRING_ENCERROR;
	}
	CString msg;
	msg.Format(id,text);
	AfxMessageBox(msg,MB_OK);
}


void CAestoolDlg::OnRadioFormat() 
{
	UpdateData();
}

void CAestoolDlg::OnHelp() 
{
	CHelp dia;
	dia.DoModal();
}

void CAestoolDlg::EnDisableOK()
{
	bool enable = 
		m_CHEditKey.GetWindowTextLength() > 0 &&
		m_SrcInfo.exists();
	m_CButtonOK.EnableWindow(enable);
}

void CAestoolDlg::OnChangeSrc()	// wird aufgerufen, wenn der Benutzer die Quelldatei von Hand
									//ändert
{
	// update source file information
	CString text;
	CString name;
	m_CEditSrc.GetWindowText(name);

	// change app title
	text.Format(name.IsEmpty() ? IDS_STRING_AESTOOL : IDS_STRING_AESTOOL_FILE,name);
	free((void*)theApp.m_pszAppName);
	theApp.m_pszAppName = strdup(text);

	switch (m_SrcInfo.setName(name)) {
	case SrcInfo::VERSION:
		AfxMessageBox(IDS_STRING_VERSION,MB_OK);
		break;
	case SrcInfo::CORRUPT:
		AfxMessageBox(IDS_STRING_CORRUPT,MB_OK);
		break;
	case SrcInfo::NOMEM:
		AfxMessageBox(IDS_STRING_NOMEMORY,MB_OK);
		break;
	}			
	bool encrypted = m_SrcInfo.isEncrypted();
	// enable/disable ok button
	EnDisableOK();
	// update descriptive text at the top of the dialog box
	text.Format(encrypted ? IDS_STRING_DECRYPT : IDS_STRING_ENCRYPT);
	m_CStaticTitle.SetWindowText(text);
	// change text of ok button
	text.Format(encrypted ? IDS_STRING_ENTSCHLUESSELN : IDS_STRING_VERSCHLUESSELN);
	m_CButtonOK.SetWindowText(text);
	// enable/disable direction radio buttons
	m_CRadioExe.EnableWindow(!encrypted);
	m_CRadioAes.EnableWindow(!encrypted);
}

void CAestoolDlg::OnRadioPWShow() 
{
	m_CHEditKey.SetPasswordChar(0);
	m_CHEditKey.Invalidate();
	// set the focus to the password field
	m_CHEditKey.SetFocus();

}

void CAestoolDlg::OnRadioPWHide() 
{
	m_CHEditKey.SetPasswordChar('*');
	m_CHEditKey.Invalidate();
	// set the focus to the password field
	m_CHEditKey.SetFocus();
}


CString CAestoolDlg::defaultDstName(SrcInfo *si, InfoBlock *ib,bool selfextracting /* = true*/)
// ib has to be defined only if si->isEncrypted()
// selfextracting must only be defined if !si->isEncrypted()
{
	ASSERT(si->exists());
	CString srcname = si->getName();
	CString dstname;
	if (si->isEncrypted()) { // decrypt
		int backslash = srcname.ReverseFind('\\');
		dstname = srcname.Left(backslash + 1); // dir portion of m_name 
		dstname += ib->getOrigName();
	} else { // encrypt
		int dot = srcname.ReverseFind('.');
		if (dot == -1)
			dstname = srcname;
		else 
			dstname = srcname.Left(dot);
		if (selfextracting)
			dstname += ".exe";
		else 
			dstname += ".aes";
	}
	return dstname;
}			




