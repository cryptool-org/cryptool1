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


// DlgSideChannelAttackVisualizationHEAlice.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSideChannelAttackVisualizationHEAlice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSideChannelAttackVisualizationHEAlice 


CDlgSideChannelAttackVisualizationHEAlice::CDlgSideChannelAttackVisualizationHEAlice(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSideChannelAttackVisualizationHEAlice::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSideChannelAttackVisualizationHEAlice)
	m_OriginalSessionKey = _T("");
	//}}AFX_DATA_INIT

	// Beziehung zu Vaterdialog herstellen
	this->parent = pParent;
}


void CDlgSideChannelAttackVisualizationHEAlice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSideChannelAttackVisualizationHEAlice)
	DDX_Control(pDX, IDC_LIST_TASKS, m_ControlTasks);
	DDX_Text(pDX, IDC_EDIT_ORIGINALSESSIONKEY, m_OriginalSessionKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSideChannelAttackVisualizationHEAlice, CDialog)
	//{{AFX_MSG_MAP(CDlgSideChannelAttackVisualizationHEAlice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSideChannelAttackVisualizationHEAlice 

BOOL CDlgSideChannelAttackVisualizationHEAlice::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// ** TODO **
		
	// Ansicht aktualisieren
	updateDisplay();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


// Diese Funktion aktualisiert die angezeigten Daten unter Rücksichtnahme
// des internen Status des Objekts 
void CDlgSideChannelAttackVisualizationHEAlice::updateDisplay()
{
	// inits
	m_ControlTasks.ResetContent();
	m_OriginalSessionKey = "";
		
	// *** AKTUELLEN ZEIGER AUF SCA-OBJEKT HOLEN ***
	SCA_Client *alice = ((CDlgSideChannelAttackVisualizationHE*)parent)->getSCAClient();

	// Status holen
	SCA_ClientStatusInfo status = alice->getStatusInfo();

	// *** TASK-TABELLE MIT INFOS FÜLLEN ***
	// wenn noch gar keine hybridverschlüsselte Datei gewählt wurde,
	// entsprechende Nachricht erzeugen, Anzeige aktualisieren und return
	if(!status.isHybEncFileDefined)
	{
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_NOHYBENCFILEDEFINED, pc_str, STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(pc_str);
		UpdateData(false);
		return;
	}
	// wurde die hybridverschlüsselte DATEI VON ALICE ERSTELLT...
	if(status.hasCreatedMessage)
	{
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_CREATEDMESSAGE, pc_str, STR_LAENGE_STRING_TABLE);	
		m_ControlTasks.AddString(pc_str);
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_CHOSESESSIONKEY, pc_str, STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(pc_str);
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_ENCRYPTEDMESSAGE, pc_str, STR_LAENGE_STRING_TABLE);	
		m_ControlTasks.AddString(pc_str);
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_GOTPUBLICKEY, pc_str, STR_LAENGE_STRING_TABLE);	
		m_ControlTasks.AddString(pc_str);
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_ENCRYPTSESSIONKEY, pc_str, STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(pc_str);
	}
	// oder wurde eine BEREITS EXISTENTE DATEI GEWÄHLT?
	else
	{
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_CHOSEEXISTINGHYBENCFILE, pc_str, STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(pc_str);
	}
	// wurde die hybridverschlüsselte Datei schon übertragen?
	if(status.hasTransmittedMessage)
	{
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_TRANSMITTEDHYBENCFILE, pc_str, STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(pc_str);
	}


	// *** ÜBRIGE FELDER FÜLLEN ***
	if(status.hasCreatedMessage)
	{
		m_OriginalSessionKey = alice->getSessionKey().c_str();
	}
	else
	{
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_SESSIONKEYUNKNOWN, pc_str, STR_LAENGE_STRING_TABLE);
		m_OriginalSessionKey = pc_str;
	}

	UpdateData(false);
}
