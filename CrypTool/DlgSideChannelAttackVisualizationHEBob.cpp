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


// DlgSideChannelAttackVisualizationHEBob.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSideChannelAttackVisualizationHEBob.h"

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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSideChannelAttackVisualizationHEBob, CDialog)
	//{{AFX_MSG_MAP(CDlgSideChannelAttackVisualizationHEBob)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgSideChannelAttackVisualizationHEBob 

BOOL CDlgSideChannelAttackVisualizationHEBob::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// ** TODO **		

	// Anzeige aktualisieren
	updateDisplay();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

// Diese Funktion aktualisiert die angezeigten Daten unter R�cksichtnahme
// des internen Status des Objekts 
void CDlgSideChannelAttackVisualizationHEBob::updateDisplay()
{
	// inits
	char temp[STR_LAENGE_STRING_TABLE+20];
	m_ControlTasks.ResetContent();
		
	// AKTUELLEN Zeiger auf entsprechendes SCA-Objekt holen
	SCA_Server *bob = (SCA_Server*)((CDlgSideChannelAttackVisualizationHE*)parent)->getSCAServer();
	
	// *** TASK-TABELLE MIT INFOS F�LLEN ***
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
		// ** (oder: wie viele Nachrichten konnte Bob erfolgreich entschl�sseln ? **
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

	// *** SESSION KEY TABELLE F�LLEN ***
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

	// alle vorher vorhandenen Informationen l�schen
	m_ListReceivedSessionKeys.DeleteAllItems();

	// Tabelle mit Informationen f�llen...
	char number[5];
	OctetString *o;
	bool b;
	char hexstring[1000];
	char boolstring[1000];

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
		// Zeile f�llen
		m_ListReceivedSessionKeys.InsertItem(i, number);
		m_ListReceivedSessionKeys.SetItemText(i,1, boolstring);
		m_ListReceivedSessionKeys.SetItemText(i,2, hexstring);
	}

	UpdateData(false);
}
