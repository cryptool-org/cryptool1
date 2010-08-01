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

// DlgSideChannelAttackVisualizationHEBob.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSideChannelAttackVisualizationHEBob.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSideChannelAttackVisualizationHEBob 


CDlgSideChannelAttackVisualizationHEBob::CDlgSideChannelAttackVisualizationHEBob(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSideChannelAttackVisualizationHEBob::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSideChannelAttackVisualizationHEBob)
	//}}AFX_DATA_INIT

	// Beziehung zu Vaterdialog herstellen
	this->parent = pParent;
}


void CDlgSideChannelAttackVisualizationHEBob::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSideChannelAttackVisualizationHEBob)
	DDX_Control(pDX, IDC_LIST_TASKS, m_ControlTasks);
	DDX_Control(pDX, IDC_LIST_RECEIVEDSESSIONKEYS, m_ListReceivedSessionKeys);
	DDX_Text(pDX, IDC_EDIT_KEYWORD, keyword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSideChannelAttackVisualizationHEBob, CDialog)
	//{{AFX_MSG_MAP(CDlgSideChannelAttackVisualizationHEBob)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSideChannelAttackVisualizationHEBob 

BOOL CDlgSideChannelAttackVisualizationHEBob::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// load the keyword from the registry
	if(CT_OPEN_REGISTRY_SETTINGS( KEY_READ, IDS_REGISTRY_SETTINGS, "SideChannelAttack" ) == ERROR_SUCCESS ) {
		unsigned long u_length = 1024;
		char c_SCA_keyWord[1025];
      LoadString(AfxGetInstanceHandle(), IDS_SCA_KEYWORD, c_SCA_keyWord, STR_LAENGE_STRING_TABLE);
      CT_READ_REGISTRY_DEFAULT( c_SCA_keyWord, "Keyword", c_SCA_keyWord, u_length );
		keyword = c_SCA_keyWord;
      if ( !keyword.GetLength() ) 
			keyword.LoadStringA( IDS_SCA_KEYWORD );
		CT_CLOSE_REGISTRY();
		UpdateData(FALSE);
	}

	// Anzeige aktualisieren
	updateDisplay();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

// Diese Funktion aktualisiert die angezeigten Daten unter Rücksichtnahme
// des internen Status des Objekts 
void CDlgSideChannelAttackVisualizationHEBob::updateDisplay()
{
	// inits
	char temp[STR_LAENGE_STRING_TABLE+20];
	m_ControlTasks.ResetContent();
		
	// AKTUELLEN Zeiger auf entsprechendes SCA-Objekt holen
	SCA_Server *bob = (SCA_Server*)((CDlgSideChannelAttackVisualizationHE*)parent)->getSCAServer();
	
	// *** TASK-TABELLE MIT INFOS FÜLLEN ***
	if(bob->getNumberOfReceptions())
	{
		// ** Wie viele Nachrichten hat Bob bisher empfangen? **
		// Unterscheidung zwischen Singular und Plural
		// (vgl. DlgSideChannelAttackVisualizationHEAlice::updateDisplay)
		if(bob->getNumberOfReceptions() == 1)
		{
			LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_RECEIVEDMESSAGE, pc_str, STR_LAENGE_STRING_TABLE);
			m_ControlTasks.AddString(pc_str);
		}
		else if(bob->getNumberOfReceptions() > 1)
		{
			LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_RECEIVEDMESSAGES, pc_str, STR_LAENGE_STRING_TABLE);
			sprintf(temp, pc_str, bob->getNumberOfReceptions());
			m_ControlTasks.AddString(temp);
		}
			
		// ** Wie viele positive Antworten hat Bob gegeben ? **
		// ** (oder: wie viele Nachrichten konnte Bob erfolgreich entschlüsseln ? **
		// Unterscheidung zwischen Singular und Plural (s.o.)
		if(bob->getNumberOfReceptions() == 1 && bob->getNumberOfPositiveResponses() == 1)
		{
			LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_SUCCESSRESPONSE, pc_str, STR_LAENGE_STRING_TABLE);
			m_ControlTasks.AddString(pc_str);
		}
		else if(bob->getNumberOfReceptions() == 1 && bob->getNumberOfPositiveResponses() == 0)
		{
			LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_FAILURERESPONSE, pc_str, STR_LAENGE_STRING_TABLE);
			m_ControlTasks.AddString(pc_str);

		}
		else if(bob->getNumberOfPositiveResponses() > 1)
		{
			LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_SUCCESSRESPONSES, pc_str, STR_LAENGE_STRING_TABLE);
			sprintf(temp, pc_str, bob->getNumberOfPositiveResponses(), bob->getNumberOfReceptions());
			m_ControlTasks.AddString(temp);
		}
	}
	else
	{
		// Bob hat bisher keinerlei Nachrichten empfangen
		LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_RECEIVEDNOMESSAGES, temp, STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(temp);
	}

	// *** SESSION KEY TABELLE FÜLLEN ***
	// m_listview in Report-Mode initialisieren!!!
	m_ListReceivedSessionKeys.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	// laufende Nummer des Eintrags
	LoadString(AfxGetInstanceHandle(), IDS_SCA_SESSIONKEYNUMBER, pc_str, STR_LAENGE_STRING_TABLE);
	m_ListReceivedSessionKeys.InsertColumn(0, pc_str, LVCFMT_LEFT, 30, 0);
	// Antwort des Servers: JA | NEIN
	LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_ANSWER, pc_str, STR_LAENGE_STRING_TABLE);
	m_ListReceivedSessionKeys.InsertColumn(1, pc_str, LVCFMT_LEFT, 95, 1);
	// Vom Server empfangener Session Key (128 Bit, Hexadezimal)
	LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_RECEIVEDSESSIONKEYHEX, pc_str, STR_LAENGE_STRING_TABLE);
	m_ListReceivedSessionKeys.InsertColumn(2, pc_str, LVCFMT_LEFT, 240, 2);

	// alle vorher vorhandenen Informationen löschen
	m_ListReceivedSessionKeys.DeleteAllItems();

	// Tabelle mit Informationen füllen...
	char number[5];
	OctetString *o;
	bool b;
	char hexstring[65];   // FIXME HK: BUFFER FOR UP TO 256 BIT AES KEYS 
	char boolstring[128]; // "sucessful" || "not sucessful"

	for(int i=0; i<bob->getNumberOfReceptions(); i++)
	{
		// Informationen holen
		o = bob->getFormerSessionKey(i);
		b = bob->getFormerResponse(i);
		
		// laufende Nummer ermitteln (_nicht_ 0-indiziert, daher i+1 anstatt i)
		itoa((i+1), number, 10);
		// Antworttext ermitteln
		if(b) LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_ANSWER_SUCCESS, boolstring, STR_LAENGE_STRING_TABLE);
		else LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_ANSWER_FAILURE, boolstring, STR_LAENGE_STRING_TABLE);
		// Hexstring ermitteln
		convertOctetStringToHexString(o, hexstring);
		// Zeile füllen
		m_ListReceivedSessionKeys.InsertItem(i, number);
		m_ListReceivedSessionKeys.SetItemText(i,1, boolstring);
		m_ListReceivedSessionKeys.SetItemText(i,2, hexstring);
	}

	UpdateData(false);
}

void CDlgSideChannelAttackVisualizationHEBob::OnOK()
{
	UpdateData(true);

	// store the keyword in the registry
	if(CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "SideChannelAttack" ) == ERROR_SUCCESS ) {
		if(keyword == "") 
			keyword.LoadStringA( IDS_SCA_KEYWORD );
		CT_WRITE_REGISTRY(keyword, "Keyword");
		CT_CLOSE_REGISTRY();
	}

	UpdateData(false);

	CDialog::OnOK();
}