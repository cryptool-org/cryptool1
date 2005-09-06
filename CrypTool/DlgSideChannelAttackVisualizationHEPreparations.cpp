/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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


// DlgSideChannelAttackVisualizationHEPreparations.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSideChannelAttackVisualizationHEPreparations.h"

#include "KeyFileHandling.h"
#include "DlgKeyAsymGeneration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char *Pfad;

// Hybridverschl�sselungsdialog
#include "DlgHybridEncryptionDemo.h"
// f�r content-name usw
#include "FileTools.h"
#include "CryptDoc.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSideChannelAttackVisualizationHEPreparations 


CDlgSideChannelAttackVisualizationHEPreparations::CDlgSideChannelAttackVisualizationHEPreparations(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSideChannelAttackVisualizationHEPreparations::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSideChannelAttackVisualizationHEPreparations)
		// HINWEIS: Der Klassen-Assistent f�gt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	this->initMode = 0;
	this->initFile = "";
	this->initFileTitle = "";
	this->finalHybEncFile = "";
	this->useExistingHybEncFile = false;
}


void CDlgSideChannelAttackVisualizationHEPreparations::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSideChannelAttackVisualizationHEPreparations)
		// HINWEIS: Der Klassen-Assistent f�gt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSideChannelAttackVisualizationHEPreparations, CDialog)
	//{{AFX_MSG_MAP(CDlgSideChannelAttackVisualizationHEPreparations)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgSideChannelAttackVisualizationHEPreparations 



void CDlgSideChannelAttackVisualizationHEPreparations::OnOK() 
{
	//CDialog::OnOK();
	
	int result = 0;
	
	if(initMode & SCA_MODE_NO_FILE)
	{
		// Will der Benutzer selbst eine Datei hybridverschl�sseln?
		LoadString(AfxGetInstanceHandle(), IDS_SCA_HYBRIDENCRYPTION_BY_USER, pc_str, STR_LAENGE_STRING_TABLE);
		result = AfxMessageBox(pc_str, MB_YESNO);
		// auswerten...
		if(result == IDNO)
		{
			// ACHTUNG!!! Hier m�chte der Benutzer die Hybridverschl�sselung NICHT SELBST durchf�hren,
			//            ergo: Hybridverschl�sselte Datei f�r bereits angelegten User verwenden!
			useExistingHybEncFile = true;

			// Default-PSE-Datei verwenden
			LoadString(AfxGetInstanceHandle(), IDS_SCA_HYBRIDENCRYPTEDFILE_DEFAULT_PSEFILE, pc_str, STR_LAENGE_STRING_TABLE);
			// Dateinamen setzen (VOLLER PFAD!)
			finalHybEncFile = "";
			finalHybEncFile += CString(Pfad);
			finalHybEncFile += CString(pc_str);
			
			// Zertifikatsinformationen ermitteln (Name, Vorname, Schl�sseltyp...)
			if(!extractCertInfo(finalHybEncFile, scaCertInfo.firstname, scaCertInfo.lastname, scaCertInfo.keytype, scaCertInfo.time, scaCertInfo.keyid))
			{
				char buffer[STR_LAENGE_STRING_TABLE];
				LoadString(AfxGetInstanceHandle(), IDS_SCA_ERROR_CERTINFOEXTRACTION, buffer, STR_LAENGE_STRING_TABLE);
				sprintf(pc_str, buffer, (LPCTSTR)(this->finalHybEncFile));
				MessageBox(pc_str, "CrypTool", MB_OK);
				return;
			}

			CDialog::OnOK();
			return;
		}

		// Benutzer m�chte eine Datei w�hlen und hybridverschl�sseln
		CDlgHybridEncryptionDemo dlg;
		dlg.activateSCABehaviour();
		if(dlg.DoModal() == IDOK)
		{
			scaCertInfo = dlg.getCertInfo();
			// Namen der PSE-Datei ermitteln
			certFilename = generateCertFilename(scaCertInfo.firstname, scaCertInfo.lastname, scaCertInfo.keytype, scaCertInfo.time, scaCertInfo.keyid);
			finalHybEncFile = dlg.getSCAFile();
			// ORIGINAL-Session-Key ermitteln (Alice muss Session Key kennen)
			originalSessionKey = dlg.m_strSymKey;
			CDialog::OnOK();
		}
		return;
	}
	else if(initMode & SCA_MODE_INVALID_FILE)
	{
		char buffer[STR_LAENGE_STRING_TABLE];
		LoadString(AfxGetInstanceHandle(), IDS_SCA_TEXTFILE_OPENED, buffer, STR_LAENGE_STRING_TABLE);
		sprintf(pc_str, buffer, (LPCTSTR)initFileTitle);
		result = AfxMessageBox(pc_str, MB_YESNO);

		if(result == IDYES)
		{
			// Benutzer m�chte die ge�ffnete Datei hybridverschl�sseln und dann als
			// Basis f�r den Angriff verwenden
			CDlgHybridEncryptionDemo dlg;
			dlg.activateSCABehaviour();
			dlg.m_strBuffTitle = initFileTitle;
			dlg.m_strPathSelDoc = initFile;
			if(dlg.DoModal() == IDOK)
			{
				scaCertInfo = dlg.getCertInfo();
				
				// Namen der PSE-Datei ermitteln
				certFilename = generateCertFilename(scaCertInfo.firstname, scaCertInfo.lastname, scaCertInfo.keytype, scaCertInfo.time, scaCertInfo.keyid);
				// ORIGINAL-Session-Key ermitteln (Alice muss Session Key kennen)
				originalSessionKey = dlg.m_strSymKey;
				finalHybEncFile = dlg.getSCAFile();
				CDialog::OnOK();
			}
			return;
		}
		else
		{
			// Benutzer m�chte andere Datei w�hlen und hybridverschl�sseln
			CDlgHybridEncryptionDemo dlg;
			dlg.activateSCABehaviour();
			if(dlg.DoModal() == IDOK)
			{
				scaCertInfo = dlg.getCertInfo();
				
				// Namen der PSE-Datei ermitteln
				certFilename = generateCertFilename(scaCertInfo.firstname, scaCertInfo.lastname, scaCertInfo.keytype, scaCertInfo.time, scaCertInfo.keyid);
				// ORIGINAL-Session-Key ermitteln (Alice muss Session Key kennen)
				originalSessionKey = dlg.m_strSymKey;
				finalHybEncFile = dlg.getSCAFile();
				CDialog::OnOK();
			}
			return;
		}
	}
	else if(initMode & SCA_MODE_VALID_FILE)
	{
		char buffer[STR_LAENGE_STRING_TABLE];
		LoadString(AfxGetInstanceHandle(), IDS_SCA_HYBENCFILE_ALREADY_OPENED, buffer, STR_LAENGE_STRING_TABLE);
		sprintf(pc_str, buffer, (LPCTSTR)initFileTitle);
		result = AfxMessageBox(pc_str, MB_YESNO);

		if(result == IDYES)
		{
			// Benutzer m�chte eine bereits existente und hybridverschl�sselte
			// Datei, die ge�ffnet ist, als Basis f�r Angriff verwenden
			useExistingHybEncFile = true;
			
			// Dateizugriff erm�glichen
						
			// Zertifikatsinformationen (und Namen der PSE-Datei) ermitteln
			if(	!extractCertInfo(this->initFile, scaCertInfo.firstname, scaCertInfo.lastname, scaCertInfo.keytype, scaCertInfo.time, scaCertInfo.keyid) ||
				!extractCertFilename(this->initFile, certFilename))
			{
				char buffer[STR_LAENGE_STRING_TABLE];
				LoadString(AfxGetInstanceHandle(), IDS_SCA_ERROR_CERTINFOEXTRACTION, buffer, STR_LAENGE_STRING_TABLE);
				sprintf(pc_str, buffer, (LPCTSTR)(this->initFile));
				MessageBox(pc_str, "CrypTool", MB_OK);
				return;
			}
										
			// ORIGINAL-Session-Key ermitteln nicht m�glich, da Datei bereits verschl�sselt
			LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_SESSIONKEYUNKNOWN, pc_str, STR_LAENGE_STRING_TABLE);
			originalSessionKey = pc_str;

			finalHybEncFile = initFile;
			CDialog::OnOK();
			return;
		}
		else
		{
			// Benutzer m�chte andere Datei w�hlen und hybridverschl�sseln
			CDlgHybridEncryptionDemo dlg;
			dlg.activateSCABehaviour();
			if(dlg.DoModal() == IDOK)
			{
				scaCertInfo = dlg.getCertInfo();

				// Namen der PSE-Datei ermitteln
				certFilename = generateCertFilename(scaCertInfo.firstname, scaCertInfo.lastname, scaCertInfo.keytype, scaCertInfo.time, scaCertInfo.keyid);
				// ORIGINAL-Session-Key ermitteln (Alice muss Session Key kennen)
				originalSessionKey = dlg.m_strSymKey;
				finalHybEncFile = dlg.getSCAFile();
				CDialog::OnOK();
			}
			return;
		}
	}

	return;
}

void CDlgSideChannelAttackVisualizationHEPreparations::setInitMode(int i)
{
	initMode = i;
}


void CDlgSideChannelAttackVisualizationHEPreparations::setInitFile(CString i)
{
	initFile = i;
}

void CDlgSideChannelAttackVisualizationHEPreparations::setInitFileTitle(CString t)
{
	initFileTitle = t;
}

CString CDlgSideChannelAttackVisualizationHEPreparations::getFinalHybEncFile()
{
	return finalHybEncFile;
}

SCACertificateInformation CDlgSideChannelAttackVisualizationHEPreparations::getCertInfo()
{
	return scaCertInfo;
}

CString CDlgSideChannelAttackVisualizationHEPreparations::getOriginalSessionKey()
{
	return originalSessionKey;
}
