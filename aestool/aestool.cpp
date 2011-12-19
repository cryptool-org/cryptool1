/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/


// aestool.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include "aestool.h"
#include "aestoolDlg.h"
#include "aestoolcrypto.h"
#include "help.h"
#include ".\aestool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAestoolApp

BEGIN_MESSAGE_MAP(CAestoolApp, CWinApp)
	//{{AFX_MSG_MAP(CAestoolApp)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAestoolApp Konstruktion

CAestoolApp::CAestoolApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CAestoolApp-Objekt

CAestoolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAestoolApp Initialisierung
static bool hex2bin(const char *hex, unsigned char *bin,int &binlen)
{
	char hexbyte[] = "00";
	unsigned byte;
	int n;
	binlen = 0;
	while (*hex) {
		hexbyte[0] = *hex++;
		hexbyte[1] = *hex ? *hex++ : '0'; // treat string ending in the middle of a byte by appending '0'
		if (0 == sscanf(hexbyte,"%x%n",&byte,&n) || n != 2)
			return 0;
		bin[binlen++] = (unsigned char)byte;
	}
	return 1;

}

static CString umlauteweg(CString cs)
{
	LPCTSTR s = (LPCTSTR)cs;
	CString res;
	while (*s) {
		switch (*s) {
		case 'ä': res += "ae"; break;
		case 'ö': res += "oe"; break;
		case 'ü': res += "ue"; break;
		case 'Ä': res += "Ae"; break;
		case 'Ö': res += "Oe"; break;
		case 'Ü': res += "Ue"; break;
		case 'ß': res += "ss"; break;
		default: res += *s;
		}
		s++;
	}
	return res;
}

BOOL CAestoolApp::InitInstance()
{
	::CoInitializeEx(NULL, COINIT_MULTITHREADED);

	AfxEnableControlContainer();

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Größe Ihrer fertigen 
	//  ausführbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht benötigen, entfernen.

//#ifdef _AFXDLL
//	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
//#else
//	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
//#endif

	m_pszAppName = _strdup("AES-Tool");

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
			fprintf(stderr,"%s\n",(LPCTSTR)umlauteweg(msg));
			exit(1);
		}
		CString errormsg;
		unsigned char key[256/8];
		int keylen = 0;
		memset(key,0,sizeof(key));
		if (m_CMD_inKey.GetLength() > 256/8*2) {
			msg.Format(IDS_STRING_KEY_TOO_LONG);
			fprintf(stderr,"%s\n",(LPCTSTR)umlauteweg(msg));
			exit(1);
		}
		if (!hex2bin(m_CMD_inKey,key,keylen)) {
			msg.Format(IDS_STRING_INVALID_KEY);
			fprintf(stderr,"%s\n",(LPCTSTR)umlauteweg(msg));
			exit(1);
		}
		if (srcinfo.isEncrypted()) {
			if (!AesToolDecrypt(key,keylen,srcinfo,m_CMD_outName,errormsg)) {
				msg.Format(IDS_STRING_DECERROR,errormsg);
				fprintf(stderr,"%s\n",(LPCTSTR)umlauteweg(msg));
				exit(1);
			}
		} else { // src not encrypted -> encrypt it
			char EXEName[1024];
			GetModuleFileName(GetModuleHandle(NULL), EXEName,sizeof(EXEName));
			bool exe = m_CMD_outName.Right(4).CompareNoCase(".exe") == 0;
			if (!AesToolEncrypt(key,keylen,srcinfo,m_CMD_outName,
					(exe ? EXEName : 0),errormsg)) {
				msg.Format(IDS_STRING_ENCERROR,errormsg);
				fprintf(stderr,"%s\n",(LPCTSTR)umlauteweg(msg));
				exit(1);
			}
		}
		exit(0);
	} else {
		// gui mode
		FreeConsole(); // close extra console window (does nothing if started from dos box)

		CAestoolDlg dlg(m_CMD_inKey,m_CMD_inName,m_CMD_outName);
		m_pMainWnd = &dlg;
		dlg.DoModal();
	}

	// Da das Dialogfeld geschlossen wurde, FALSE zurückliefern, so dass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}

#pragma warning( disable : 4100 )
#if 0 // MFC 6.0 is not anymore supported by cryptool
void CAestoolApp::WinHelp(DWORD dwData, UINT nCmd) 
{
	CHelp hlp;
	hlp.DoModal();
}
#endif
void CAestoolApp::WinHelpInternal(DWORD dwData, UINT nCmd) 
{
	CHelp hlp;
	hlp.DoModal();
}



void CAestoolApp::ScanCMDLine(char * cmd)
{
	CString l;
	char c;
	int len;

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

int CAestoolApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	::CoUninitialize();

	return CWinApp::ExitInstance();
}
