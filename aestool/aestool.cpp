// aestool.cpp : Legt das Klassenverhalten f�r die Anwendung fest.
//

#include "stdafx.h"
#include "aestool.h"
#include "aestoolDlg.h"
#include "aestoolcrypto.h"
#include "help.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAestoolApp

BEGIN_MESSAGE_MAP(CAestoolApp, CWinApp)
	//{{AFX_MSG_MAP(CAestoolApp)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAestoolApp Konstruktion

CAestoolApp::CAestoolApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einf�gen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CAestoolApp-Objekt

CAestoolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAestoolApp Initialisierung
char hexdigit2bin(const char *p)
{
	char c = *p;
	if (!p)
		c = '0';
	if (c >= 'a' && c <= 'f') 
		c -= ('a' - 10);
	else if (c >= 'A' && c <= 'F') 
		c -= ('A' - 10);
	else 
		c -= '0';
	if (c < 0 || c > 10)
		c = 0;
	return c;
}

char hexbyte2bin(const char *p)
{
	return (hexdigit2bin(p) << 4) | hexdigit2bin(p+1);
}

BOOL CAestoolApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Gr��e Ihrer fertigen 
	//  ausf�hrbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht ben�tigen, entfernen.

#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

	m_pszAppName = strdup("AES-Tool");

	ScanCMDLine(m_lpCmdLine);

	if (!m_CMD_inKey.IsEmpty() && 
		!m_CMD_inName.IsEmpty() && 
		!m_CMD_outName.IsEmpty()) {
		// batch mode
		CString msg;
		SrcInfo srcinfo;
		unsigned id = 0;
		switch (srcinfo.setName(m_CMD_inName)) {
		case SrcInfo::VERSION:
			id = IDS_STRING_VERSION; break;
		case SrcInfo::CORRUPT:
			id = IDS_STRING_CORRUPT; break;
		case SrcInfo::NOMEM:
			id = IDS_STRING_NOMEMORY; break;
		}			
		if (id) {
			msg.Format(id);
			fprintf(stderr,"%s\n",(LPCTSTR)msg);
			exit(1);
		}
		CString errormsg;
		unsigned char key[256/8];
		int keylen = 0;
		memset(key,0,sizeof(key));
		const char *p = (const char *)m_CMD_inKey;		
		while (*p) {
			key[keylen++] = hexbyte2bin(p);
			p++; if (*p) p++;
		}
		// FIXME key, keylen
		if (srcinfo.isEncrypted()) {
			if (!AesToolDecrypt(key,keylen,srcinfo,m_CMD_outName,errormsg)) {
				msg.Format(IDS_STRING_DECERROR,errormsg);
				fprintf(stderr,"%s\n",msg);
				exit(1);
			}
		} else { // src not encrypted -> encrypt it
			char EXEName[1024];
			GetModuleFileName(GetModuleHandle(NULL), EXEName,sizeof(EXEName));
			bool exe = m_CMD_outName.Right(4).CompareNoCase(".exe") == 0;
			if (!AesToolEncrypt(key,keylen,srcinfo,m_CMD_outName,
					(exe ? EXEName : 0),errormsg)) {
				msg.Format(IDS_STRING_DECERROR,errormsg);
				fprintf(stderr,"%s\n",msg);
				exit(1);
			}
		}
		exit(0);
	} else {
		// gui mode
		CAestoolDlg dlg(m_CMD_inKey,m_CMD_inName);
		m_pMainWnd = &dlg;
		int nResponse = dlg.DoModal();
	}
	// Da das Dialogfeld geschlossen wurde, FALSE zur�ckliefern, so dass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}

void CAestoolApp::WinHelp(DWORD dwData, UINT nCmd) 
{
	CHelp hlp;

	hlp.DoModal();
}

void CAestoolApp::ScanCMDLine(char * cmd)
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
				len = findStr(&l);
				m_CMD_inName = l.Left(len);
				l.Delete(0, len);
				l.TrimLeft();
				break;
			case ('o'):
				len = findStr(&l);
				m_CMD_outName = l.Left(len);
				l.Delete(0, len);
				l.TrimLeft();
				break;
			case ('k'):
				len = findStr(&l);
				m_CMD_inKey = l.Left(len);
				l.Delete(0, len);
				l.TrimLeft();
				break;
			}
		}
		else { // positional argument
			if(m_CMD_inName.IsEmpty()) { // set in name
				len = findStr(&l);
				m_CMD_inName = l.Left(len);
				l.Delete(0, len);
				l.TrimLeft();
			}
			else if(m_CMD_outName.IsEmpty()) { // set out name
				len = findStr(&l);
				m_CMD_outName = l.Left(len);
				l.Delete(0, len);
				l.TrimLeft();
			}
			else if(m_CMD_inKey.IsEmpty()) { // set key
				len = findStr(&l);
				m_CMD_inKey = l.Left(len);
				l.Delete(0, len);
				l.TrimLeft();
			}
		}
	}

}

int CAestoolApp::findStr(CString *l)
{
	int i, f;

	for(f=i=0; i<l->GetLength(); i++) {
		if(l->GetAt(i) == '\"') { // toggle "-mode
			l->Delete(i,1);
			i--;
			f = 1 - f;
		}
		else if(f) { // "-mode, skip all
			continue;
		}
		else { // normal mode
			if(strchr(" \r\n\t", l->GetAt(i)))
				break;
		}
	}
	return i;
}
