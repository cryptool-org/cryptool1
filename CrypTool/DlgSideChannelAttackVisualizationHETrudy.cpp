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

// DlgSideChannelAttackVisualizationHETrudy.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSideChannelAttackVisualizationHETrudy.h"
#include "CrypToolTools.h"
#include ".\dlgsidechannelattackvisualizationhetrudy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSideChannelAttackVisualizationHETrudy 


CDlgSideChannelAttackVisualizationHETrudy::CDlgSideChannelAttackVisualizationHETrudy(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSideChannelAttackVisualizationHETrudy::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSideChannelAttackVisualizationHETrudy)
	m_DeterminedSessionKey = _T("");
	m_InterceptedEncryptedSessionKey = _T("");
	m_ComputedMessage = _T("");
	//}}AFX_DATA_INIT

	// Beziehung zu Vaterdialog herstellen
	this->parent = pParent;

	// die signifikante Bitzahl ermitteln
	// DEFAULT-WERT: 128 Bit
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "SideChannelAttack" ) == ERROR_SUCCESS )
	{
		unsigned long u_significantBits = 128;
		CT_READ_REGISTRY_DEFAULT(u_significantBits, "BitlengthSecret", u_significantBits);
		significantBits = u_significantBits;
		if(!significantBits) throw SCA_Error(E_SCA_INTERNAL_ERROR);
		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}
}


void CDlgSideChannelAttackVisualizationHETrudy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSideChannelAttackVisualizationHETrudy)
	DDX_Control(pDX, IDC_LIST_TASKS, m_ControlTasks);
	DDX_Control(pDX, IDC_LIST_MODIFIEDSESSIONKEYS, m_ListModifiedSessionKeys);
	DDX_Text(pDX, IDC_EDIT_DETERMINEDSESSIONKEY, m_DeterminedSessionKey);
	DDX_Text(pDX, IDC_EDIT_INTERCEPTEDENCRYPTEDSESSIONKEY, m_InterceptedEncryptedSessionKey);
	DDX_Text(pDX, IDC_EDIT_COMPUTEDMESSAGE, m_ComputedMessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSideChannelAttackVisualizationHETrudy, CDialog)
	//{{AFX_MSG_MAP(CDlgSideChannelAttackVisualizationHETrudy)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSideChannelAttackVisualizationHETrudy 

BOOL CDlgSideChannelAttackVisualizationHETrudy::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// ** TODO **
	
	updateDisplay();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

// Diese Funktion aktualisiert die angezeigten Daten unter Rücksichtnahme
// des internen Status des Objekts 
void CDlgSideChannelAttackVisualizationHETrudy::updateDisplay()
{
	// inits
	char temp[STR_LAENGE_STRING_TABLE+20];
	m_ControlTasks.ResetContent();
		
	// AKTUELLEN Zeiger auf entsprechendes SCA-Objekt holen
	const SCA_Attacker *trudy = ((CDlgSideChannelAttackVisualizationHE*)parent)->getSCAAttacker();

	// *** TASK-TABELLE MIT INFOS FÜLLEN ***
	if(trudy->hasInterceptedHybridEncryptedFile())
	{
		// hat Trudy schon die Nachricht von A->B abgefangen?
		LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_MESSAGEINTERCEPTED,temp,STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(temp);
		// Trudy hat den Session Key aus der Nachricht "extrahiert"
		LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_HASEXTRACTEDDENCSESSIONKEY,temp,STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(temp);

		if(trudy->getNumberOfModifications())
		{
			// ** Wie viele modifizierte Sessionkeys hat Trudy bisher erstellt? **
			// Unterscheidung zwischen Singular und Plural
			// IDS_SCA_ATTACKER_MODIFICATIONSMADE_S:
			//		"Trudy hat 1 modifizierten Sessionkey erstellt"
			//	IDS_SCA_ATTACKER_MODIFICATIONSMADE
			//		"Trudy hat n modfizierte Sessionkeys erstellt.
			if(trudy->getNumberOfModifications() == 1)
			{
				LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_MODIFICATIONSMADE_S, pc_str, STR_LAENGE_STRING_TABLE);
				m_ControlTasks.AddString(pc_str);
			}
			else
			{
				LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_MODIFICATIONSMADE, pc_str, STR_LAENGE_STRING_TABLE);
				sprintf(temp, pc_str, trudy->getNumberOfModifications());
				m_ControlTasks.AddString(temp);
			}
	
			// ** Wie viele SUCCESS-Antworten hat Trudy von Bobs Server erhalten? ** 
			// Unterscheidung zwischen Singular und Plural (s.o.)
			if(	trudy->getNumberOfModifications() == 1 &&trudy->getNumberOfPositiveResponses() == 1)
			{
				LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_SUCCESSRESPONSE_TRUE, pc_str, STR_LAENGE_STRING_TABLE);
				m_ControlTasks.AddString(pc_str);
			}
			else if(trudy->getNumberOfModifications() == 1 && trudy->getNumberOfPositiveResponses() == 0)
			{
				LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_SUCCESSRESPONSE_FALSE, pc_str, STR_LAENGE_STRING_TABLE);
				m_ControlTasks.AddString(pc_str);
			}
			else
			{
				LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_SUCCESSRESPONSES, pc_str, STR_LAENGE_STRING_TABLE);
				sprintf(temp, pc_str, trudy->getNumberOfPositiveResponses(), trudy->getNumberOfModifications());
				m_ControlTasks.AddString(temp);
			}
		}
		else
		{
			// Trudy hat noch KEINE modifizierten Session Keys erstellt
			LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_NOMODIFICATIONSYET, temp ,STR_LAENGE_STRING_TABLE);
			m_ControlTasks.AddString(temp);
		}
	}
	else
	{
		// Trudy hat bisher KEINE Nachricht abgefangen
		LoadString(AfxGetInstanceHandle(),IDS_SCA_ATTACKER_MESSAGENOTINTERCEPTEDYET,temp,STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(temp);
	}

	// *** MODIFIZIERTE SESSION KEYS TABELLE FÜLLEN ***
	// m_listview in Report-Mode initialisieren!!!
	m_ListModifiedSessionKeys.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	// *** Beschriftung der Tabelle ***
	// vom Angreifer modifizierter Session Key
	LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_MODIFIEDSESSIONKEY, temp, STR_LAENGE_STRING_TABLE);
	m_ListModifiedSessionKeys.InsertColumn(0, temp, LVCFMT_LEFT, 520, 0);
	// alle vorher vorhandenen Informationen löschen
	m_ListModifiedSessionKeys.DeleteAllItems();
	// Tabelle mit Informationen füllen...
	OctetString o;
	char hexstring[SCA_MAX_LENGTH_OCTETSTRING+1];

	for(int i=0; i<trudy->getNumberOfModifications(); i++)
	{
		// Informationen holen
		o = trudy->getModifiedChallenge(i);
		// Hexstring ermitteln
		convertOctetStringToHexString(&o, hexstring);
		// Zeile füllen
		m_ListModifiedSessionKeys.InsertItem(i, hexstring);
	}

	// *** VERSCHLÜSSELTER SESSION KEY (ORIGINAL) ***
	if(trudy->hasInterceptedHybridEncryptedFile())
	{
		o = trudy->getInterceptedSessionKey();
		char hexout[SCA_MAX_LENGTH_OCTETSTRING+1];
		convertOctetStringToHexString(&o, hexout);

		this->m_InterceptedEncryptedSessionKey = hexout;

	}
	else
	{
		LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_SESSIONKEYNOTINTERCEPTEDYET, temp, STR_LAENGE_STRING_TABLE);
		this->m_InterceptedEncryptedSessionKey = temp;
	}

	// *** DURCH ANGRIFF ERMITTELTER SESSION KEY ***
	if(trudy->isDone())
	{
		Big s = (char*)trudy->getComputedSecret().c_str();
		OctetString o;
		char hexout[SCA_MAX_LENGTH_OCTETSTRING+1];
		convertBigNumberToOctetString(s,&o,significantBits/8);
		convertOctetStringToHexString(&o, hexout);
		this->m_DeterminedSessionKey = hexout;

		// Ursprünglich von Alice verschlüsselte Nachricht entschlüsseln und anzeigen
		// AKTUELLEN Zeiger auf entsprechendes SCA-Objekt holen
		SCA_Client *alice = ((CDlgSideChannelAttackVisualizationHE*)parent)->getSCAClient();
		// Ursprungstext ermitteln
		OctetString originalCipherText = alice->getHybEncFile().cipherText;
		// Text entschlüsseln
		OctetString clearText;
		// dynamisch Speicher für entschlüsselten Text allokieren
		clearText.octets = new char[originalCipherText.noctets + 256];
		clearText.noctets = 0;
		decryptMessageAES(&originalCipherText, &o, &clearText, significantBits);
		// Anzeige aktualisieren
		char *tempBuffer = new char[clearText.noctets+1];
		memset(tempBuffer, 0, clearText.noctets+1);
		memcpy(tempBuffer, clearText.octets, clearText.noctets);
		m_ComputedMessage = tempBuffer;
		delete tempBuffer;
      delete []o.octets;
      delete []clearText.octets;
	}
	else
	{
		LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_SESSIONKEYNOTDETERMINEDYET, temp, STR_LAENGE_STRING_TABLE);
		this->m_DeterminedSessionKey = temp;
	}

	UpdateData(false);
}

void CDlgSideChannelAttackVisualizationHETrudy::OnBnClickedOk()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	OnOK();
}
