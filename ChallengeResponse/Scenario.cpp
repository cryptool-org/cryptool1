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

// Scenario.cpp: implementation of the CScenario class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Scenario.h"
#include "ScenarioObject.h"
#include "wire.h" 
#include "resource.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int numComputers=6;
const int numWires=6; // Falls Fehler bei Koordinatenerkennung auftreten 7 und wires[0] nicht besetzen.
const int numPackets=5;
const int wireSteps=5;
CComputer computers[numComputers];
CWire wires[numWires];
CPacket packets[numPackets];
//int cmatrix[numComputers][numComputers];
int routing[numComputers][numComputers];
//bool cmatrix_selected[numComputers][numComputers];
//int cmatrix_distance[numComputers][numComputers];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

	

CScenario::CScenario()
{
	protocolRunning=FALSE;

	client.Format(IDS_CR_CLIENT);
	router1.Format(IDS_CR_ROUTER,1);
	router2.Format(IDS_CR_ROUTER,2);
	server1.Format(IDS_CR_SERVER,1);
	server2.Format(IDS_CR_SERVER,2);
	attacker.Format(IDS_CR_ATTACKER);
	computers[0].setParameters(180,140,220,180,1,client,0,2,FALSE);
	computers[1].setParameters(300,140,340,180,1,router1,0,-1,FALSE);
	computers[2].setParameters(420,140,460,180,1,router2,0,-1,FALSE);
	computers[3].setParameters(540, 40,580, 80,1,server1,0,2,FALSE);
	computers[4].setParameters(540,240,580,280,1,server2,0,2,FALSE);
	computers[5].setParameters(300,240,340,280,1,attacker,1,2,TRUE);

	w_C_R1=(CString)"w_C_R1";
	w_R1_R2=(CString)"w_R1_R2";
	w_R2_S1=(CString)"w_R2_S1";
	w_R2_S2=(CString)"w_R2_S2";
	w_A_R1=(CString)"w_A_R1";
	w_A_R2=(CString)"w_A_R2";
	
	//Falls Fehler bei Koordinatenerkennung auftreten, wires[0] nicht besetzen
	wires[0].setParameters(getIndexOfComputer(client),getIndexOfComputer(router1),220,160,300,160, wireSteps, 3, w_C_R1, FALSE, TRUE);
	wires[1].setParameters(getIndexOfComputer(router1),getIndexOfComputer(router2),340,160,420,160, wireSteps, 3, w_R1_R2, FALSE, TRUE);
	wires[2].setParameters(getIndexOfComputer(router2),getIndexOfComputer(server1),460,140,540, 60, wireSteps, 2, w_R2_S1, FALSE, TRUE);
	wires[3].setParameters(getIndexOfComputer(router2),getIndexOfComputer(server2),460,180,540,260, wireSteps, 2, w_R2_S2, FALSE, TRUE);
	wires[4].setParameters(getIndexOfComputer(attacker),getIndexOfComputer(router1),320,240,320,180, wireSteps, 3, w_A_R1, TRUE, FALSE);
	wires[5].setParameters(getIndexOfComputer(attacker),getIndexOfComputer(router2),340,260,420,180, wireSteps, 2, w_A_R2, TRUE, FALSE);

	modeText_Start.LoadString(IDS_modeText_Start);
	modeText_Einfuehrung.LoadString(IDS_modeText_Einfuehrung); 
	modeText_Passwoerter.LoadString(IDS_modeText_Passwoerter);
	modeText_Einmalpasswoerter.LoadString(IDS_modeText_Einmalpasswoerter);
	modeText_ChallengeResponseSymmetrisch.LoadString(IDS_modeText_ChallengeResponseSymmetrisch);
	modeText_ChallengeResponseAsymmetrisch.LoadString(IDS_modeText_ChallengeResponseAsymmetrisch);
	modeText_WechselseitigeAuthentifikation.LoadString(IDS_modeText_WechselseitigeAuthentifikation);
	
	dataCaption_Passwort.LoadString(IDS_dataCaption_Passwort);
	dataCaption_Einmalpasswort.LoadString(IDS_dataCaption_Einmalpasswort);
	dataCaption_Schluessel.LoadString(IDS_dataCaption_Schluessel);
	dataCaption_geheimerSchluesselClient.LoadString(IDS_dataCaption_geheimerSchluesselClient);
	dataCaption_oeffentlicherSchluesselClient.LoadString(IDS_dataCaption_oeffentlicherSchluesselClient);
	dataCaption_geheimerSchluesselServer1.LoadString(IDS_dataCaption_geheimerSchluesselServer1);
	dataCaption_oeffentlicherSchluesselServer1.LoadString(IDS_dataCaption_oeffentlicherSchluesselServer1);
	dataCaption_ChallengeFromServer1.LoadString(IDS_dataCaption_ChallengeFromServer1);
	dataCaption_ResponseToServer1.LoadString(IDS_dataCaption_ResponseToServer1);
	dataCaption_ChallengeFromClient.LoadString(IDS_dataCaption_ChallengeFromClient);
	dataCaption_ResponseToClient.LoadString(IDS_dataCaption_ResponseToClient);

	dataValue_Passwort.Format(IDS_CR_PASSWORD);
	dataValue_Einmalpasswort=(CString)"123456";
	dataValue_Schluessel=(CString)"a3c2b1";
	dataValue_geheimerSchluesselClient=(CString)"her7sj"; //gleicher Schlüssel für interne Verarbeitung
	dataValue_oeffentlicherSchluesselClient=(CString)"her7sj";
	dataValue_geheimerSchluesselServer1=(CString)"98zwr3";
	dataValue_oeffentlicherSchluesselServer1=(CString)"2j658d";
	dataValue_ChallengeFromServer1=(CString)"a76zup";
	dataValue_ResponseToServer1=(CString)"jsd874";
	dataValue_ChallengeFromClient=(CString)"9cxn4f";
	dataValue_ResponseToClient=(CString)"98xf54";

	calculateShortestWays();
	
	int i;
	for(i=0;i<=numPackets-1;i++){
		packets[i].active=FALSE;
	}
}

CScenario::~CScenario()
{

}

void CScenario::draw(CClientDC &dc)
{
	//wichtig: erst Drähte, dann Computer
	int i;
	for(i=0;i<=numWires-1;i++){
		wires[i].draw(dc);
	}

	for(i=0;i<=numComputers-1;i++){
		computers[i].draw(dc);
	}

	for(i=0;i<=numPackets-1;i++){
		packets[i].draw(dc);
	}
}

void CScenario::changeMode(int Mode,CClientDC& dc, CString& label)
{
	mode = Mode;
	clearComputerData(dc);
	switch (mode)
	{
	case 0:	
		modeText=modeText_Start;
		showBaseControls(FALSE);
		break;
	case 1:
		modeText=modeText_Einfuehrung;
		showBaseControls(TRUE);
		break;
	case 2:
		modeText=modeText_Passwoerter;
		showBaseControls(TRUE);
		setComputerDataPasswort();
		break;
	case 3:
		modeText=modeText_Einmalpasswoerter;
		showBaseControls(TRUE);
		setComputerDataEinmalpasswoerter();
		break;
	case 4:
		modeText=modeText_ChallengeResponseSymmetrisch;
		showBaseControls(TRUE);
		setComputerDataChallengeResponseSymmetrisch();
		break;
	case 5:
		modeText=modeText_ChallengeResponseAsymmetrisch;
		showBaseControls(TRUE);
		setComputerDataChallengeResponseAsymmetrisch();
		break;
	case 6:
		modeText=modeText_WechselseitigeAuthentifikation;
		showBaseControls(TRUE);
		setComputerDataChallengeResponseWechselseitig();
		break;
	}
	
	label=modeText;
	draw(dc);
}

void CScenario::showBaseControls(bool visible)
{
	int i;
	for(i=0;i<=numComputers-1;i++){
		computers[i].visible=visible;
	}
	
	for(i=0;i<=numWires-1;i++){
		wires[i].visible=visible;
	}
}

bool CScenario::isMouseOverObject(int action,CPoint& point)
{
	bool returnValue=FALSE;
	int i;
	switch(action){
	case 0:
		break;
	case 1:
	case 2:
		for(i=0;i<=numWires-1;i++){
			if (wires[i].isMouseOverObject(point)) returnValue=TRUE;
		}
		if (computers[getIndexOfComputer(router1)].isMouseOverObject(point)) returnValue=TRUE;
		if (computers[getIndexOfComputer(router2)].isMouseOverObject(point)) returnValue=TRUE;
		break;
	case 3:
	case 4:
		if (computers[getIndexOfComputer(client)].isMouseOverObject(point)) returnValue=TRUE;
		if (computers[getIndexOfComputer(server1)].isMouseOverObject(point)) returnValue=TRUE;
		if (computers[getIndexOfComputer(server2)].isMouseOverObject(point)) returnValue=TRUE;
		if (computers[getIndexOfComputer(router1)].isMouseOverObject(point)) returnValue=TRUE;
		if (computers[getIndexOfComputer(router2)].isMouseOverObject(point)) returnValue=TRUE;
		break;
	default:
		break;
	}
	return returnValue;
}

int CScenario::mouseClick(int action,CPoint& point, CClientDC& dc)
{
	int returnValue=0;
	int i;
	switch(action){
	case 0:
		break;
	case 1:
		if (wires[getIndexOfWire(w_C_R1)].isMouseOverObject(point)) wires[getIndexOfWire(w_C_R1)].connected=TRUE;
		if (wires[getIndexOfWire(w_R1_R2)].isMouseOverObject(point)) wires[getIndexOfWire(w_R1_R2)].connected=TRUE;
		if (wires[getIndexOfWire(w_R2_S1)].isMouseOverObject(point)) wires[getIndexOfWire(w_R2_S1)].connected=TRUE;
		if (wires[getIndexOfWire(w_R2_S2)].isMouseOverObject(point)) wires[getIndexOfWire(w_R2_S2)].connected=TRUE;
		if (computers[getIndexOfComputer(router1)].isMouseOverObject(point)) wires[getIndexOfWire(w_A_R1)].connected=TRUE;
		if (computers[getIndexOfComputer(router2)].isMouseOverObject(point)) wires[getIndexOfWire(w_A_R2)].connected=TRUE;
		break;		
	case 2:
		for(i=0;i<=numWires-1;i++){
			if (wires[i].isMouseOverObject(point)) wires[i].connected=FALSE;
		}
		if (computers[getIndexOfComputer(router1)].isMouseOverObject(point)) wires[getIndexOfWire(w_A_R1)].connected=FALSE;
		if (computers[getIndexOfComputer(router2)].isMouseOverObject(point)) wires[getIndexOfWire(w_A_R2)].connected=FALSE;
		//nachdem calculateShortestWays aufgerufen wurde (s.u.), müssen evtl. angegriffene Rechner mögl wieder frei gegeben werden.
		break;
	case 3:
		if (computers[getIndexOfComputer(client)].isMouseOverObject(point)) returnValue=1;
		if (computers[getIndexOfComputer(server1)].isMouseOverObject(point)) returnValue=1;
		if (computers[getIndexOfComputer(server2)].isMouseOverObject(point)){
			if ((((wires[getIndexOfWire(w_A_R1)].connected)&&(wires[getIndexOfWire(w_R1_R2)].connected))||(wires[getIndexOfWire(w_A_R2)].connected))&&(wires[getIndexOfWire(w_R2_S2)].connected)){
				computers[getIndexOfComputer(server2)].underAttack=TRUE;
				if (mode==4){ //"Challenge Response Symmetrisch"
					computers[getIndexOfComputer(attacker)].data.changeValue(dataCaption_Schluessel,dataValue_Schluessel);
				}
			}else{
				returnValue=2;
			}
		}
		if (computers[getIndexOfComputer(router1)].isMouseOverObject(point)){
			if ((wires[getIndexOfWire(w_A_R1)].connected)||((wires[getIndexOfWire(w_A_R2)].connected)&&(wires[getIndexOfWire(w_R1_R2)].connected))){
				computers[getIndexOfComputer(router1)].underAttack=TRUE;
			}else{
				returnValue=2;
			}
		}
		if (computers[getIndexOfComputer(router2)].isMouseOverObject(point)){
			if (((wires[getIndexOfWire(w_A_R1)].connected)&&(wires[getIndexOfWire(w_R1_R2)].connected))||(wires[getIndexOfWire(w_A_R2)].connected)){
				computers[getIndexOfComputer(router2)].underAttack=TRUE;
			}else{
				returnValue=2;
			}
		}		
		break;
	case 4:
		if (computers[getIndexOfComputer(server2)].isMouseOverObject(point)){
			if ((((wires[getIndexOfWire(w_A_R1)].connected)&&(wires[getIndexOfWire(w_R1_R2)].connected))||(wires[getIndexOfWire(w_A_R2)].connected))&&(wires[getIndexOfWire(w_R2_S2)].connected)){
				computers[getIndexOfComputer(server2)].underAttack=FALSE;
			}else{
				returnValue=2;
			}
		}
		if (computers[getIndexOfComputer(router1)].isMouseOverObject(point)){
			if ((wires[getIndexOfWire(w_A_R1)].connected)||((wires[getIndexOfWire(w_A_R2)].connected)&&(wires[getIndexOfWire(w_R1_R2)].connected))){
				computers[getIndexOfComputer(router1)].underAttack=FALSE;
			}else{
				returnValue=2;
			}
		}
		if (computers[getIndexOfComputer(router2)].isMouseOverObject(point)){
			if (((wires[getIndexOfWire(w_A_R1)].connected)&&(wires[getIndexOfWire(w_R1_R2)].connected))||(wires[getIndexOfWire(w_A_R2)].connected)){
				computers[getIndexOfComputer(router2)].underAttack=FALSE;
			}else{
				returnValue=2;
			}
		}
		break;
	default:
		break;
	}
	
	calculateShortestWays();
	//ggf. angegriffene Rechner freigeben, zu denen keine Verbindung mehr besteht.
	if (action==2){
		for(int i=0;i<=numComputers-1;i++){
			if ((computers[i].underAttack)&&(routing[getIndexOfComputer(attacker)][i]==-1)){
				computers[i].underAttack=FALSE;
			}
		}
	}
	draw(dc);
	return returnValue;
}

bool CScenario::attackerCanMask()
{
	if (!wires[getIndexOfWire(w_R1_R2)].connected && wires[getIndexOfWire(w_A_R1)].connected && wires[getIndexOfWire(w_A_R2)].connected){
		return TRUE;
	}else{
		return FALSE;
	}
}


void CScenario::clearComputerData(CClientDC& dc)
{
	newData.clearLists();
	for(int i=0;i<=numComputers-1;i++){
		computers[i].eraseDataText(dc);
		computers[i].data.clearLists();
	}
}

void CScenario::setComputerDataPasswort()
{
	newData.addLabel(dataCaption_Passwort);
	newData.changeValue(dataCaption_Passwort,dataValue_Passwort);
	computers[getIndexOfComputer(attacker)].data.copy(newData,FALSE);
	computers[getIndexOfComputer(server1)].data.copy(newData,TRUE);
	computers[getIndexOfComputer(client)].data.copy(newData,TRUE);
}

void CScenario::setComputerDataEinmalpasswoerter()
{
	newData.addLabel(dataCaption_Einmalpasswort);
	newData.changeValue(dataCaption_Einmalpasswort,dataValue_Einmalpasswort);
	computers[getIndexOfComputer(attacker)].data.copy(newData,FALSE);
	computers[getIndexOfComputer(server1)].data.copy(newData,TRUE);
	computers[getIndexOfComputer(client)].data.copy(newData,TRUE);
}

void CScenario::setComputerDataChallengeResponseSymmetrisch()
{
	newData.addLabel(dataCaption_Schluessel);
	newData.changeValue(dataCaption_Schluessel,dataValue_Schluessel);
	newData.addLabel(dataCaption_ChallengeFromServer1);
	newData.addLabel(dataCaption_ResponseToServer1);
	computers[getIndexOfComputer(attacker)].data.copy(newData,FALSE);
	computers[getIndexOfComputer(server1)].data.copy(newData,TRUE);
	computers[getIndexOfComputer(server2)].data.copy(newData,TRUE);
	computers[getIndexOfComputer(client)].data.copy(newData,TRUE);
}

void CScenario::setComputerDataChallengeResponseAsymmetrisch()
{
	newData.addLabel(dataCaption_geheimerSchluesselClient);
	newData.addLabel(dataCaption_oeffentlicherSchluesselClient);
	newData.changeValue(dataCaption_oeffentlicherSchluesselClient,dataValue_oeffentlicherSchluesselClient);
	newData.addLabel(dataCaption_ChallengeFromServer1);
	newData.addLabel(dataCaption_ResponseToServer1);
	computers[getIndexOfComputer(attacker)].data.copy(newData,TRUE);
	computers[getIndexOfComputer(server1)].data.copy(newData,TRUE);
	computers[getIndexOfComputer(server2)].data.copy(newData,TRUE);
	newData.changeValue(dataCaption_geheimerSchluesselClient,dataValue_geheimerSchluesselClient);
	computers[getIndexOfComputer(client)].data.copy(newData,TRUE);
}

void CScenario::setComputerDataChallengeResponseWechselseitig()
{
	newData.addLabel(dataCaption_geheimerSchluesselClient);
	newData.addLabel(dataCaption_oeffentlicherSchluesselClient);
	newData.changeValue(dataCaption_oeffentlicherSchluesselClient,dataValue_oeffentlicherSchluesselClient);
	
	newData.addLabel(dataCaption_geheimerSchluesselServer1);
	newData.addLabel(dataCaption_oeffentlicherSchluesselServer1);
	newData.changeValue(dataCaption_oeffentlicherSchluesselServer1,dataValue_oeffentlicherSchluesselServer1);
	newData.addLabel(dataCaption_ChallengeFromServer1);
	newData.addLabel(dataCaption_ResponseToServer1);
	newData.addLabel(dataCaption_ChallengeFromClient);
	newData.addLabel(dataCaption_ResponseToClient);
	computers[getIndexOfComputer(attacker)].data.copy(newData,TRUE);
	computers[getIndexOfComputer(server2)].data.copy(newData,TRUE);
	newData.changeValue(dataCaption_geheimerSchluesselClient,dataValue_geheimerSchluesselClient);
	computers[getIndexOfComputer(client)].data.copy(newData,TRUE);
	newData.changeValue(dataCaption_geheimerSchluesselClient,(CString)"");
	newData.changeValue(dataCaption_geheimerSchluesselServer1,dataValue_geheimerSchluesselServer1);
	computers[getIndexOfComputer(server1)].data.copy(newData,TRUE);


}

int CScenario::getIndexOfComputer(CString name)
{
	int returnValue=-1;
	for(int i=0;i<=numComputers-1;i++){
		if (computers[i].name==name) returnValue=i;
	}
	return returnValue;
}

int CScenario::getIndexOfWire(CString name)
{
	int returnValue=-1;
	for(int i=0;i<=numWires-1;i++){
		if (wires[i].name==name) returnValue=i;
	}
	return returnValue;
}


void CScenario::calculateShortestWays()
{
	int i;
	int nextToClient, nextToServer1,nextToServer2;
	
	nextToClient=-1;
	nextToServer1=-1;
	nextToServer2=-1;

	if (wires[getIndexOfWire(w_C_R1)].connected){ //Client -> *
		nextToClient=getIndexOfWire(w_C_R1);
	}
	if (wires[getIndexOfWire(w_R2_S1)].connected){ //Server1 -> *
		nextToServer1=getIndexOfWire(w_R2_S1);
	}
	if (wires[getIndexOfWire(w_R2_S2)].connected){ //Server2 -> *
		nextToServer2=getIndexOfWire(w_R2_S2);
	}
	
	for(i=0;i<=numComputers-1;i++){
		routing[getIndexOfComputer(client)][i]=nextToClient;
		routing[getIndexOfComputer(server1)][i]=nextToServer1;
		routing[getIndexOfComputer(server2)][i]=nextToServer2;
	}
	
	routing[getIndexOfComputer(router1)][getIndexOfComputer(client)]=nextToClient;
	routing[getIndexOfComputer(router2)][getIndexOfComputer(server1)]=nextToServer1;
	routing[getIndexOfComputer(router2)][getIndexOfComputer(server2)]=nextToServer2;

	
	//Korrektur für (i,i)!!
	for(i=0;i<=numComputers-1;i++){
		routing[i][i]=-1;
		routing[i][i]=-1;
		routing[i][i]=-1;
	}
	
	
	if (wires[getIndexOfWire(w_R1_R2)].connected){
		routing[getIndexOfComputer(router1)][getIndexOfComputer(router2)]=getIndexOfWire(w_R1_R2);
		routing[getIndexOfComputer(router1)][getIndexOfComputer(server1)]=getIndexOfWire(w_R1_R2);
		routing[getIndexOfComputer(router1)][getIndexOfComputer(server2)]=getIndexOfWire(w_R1_R2);
		routing[getIndexOfComputer(router2)][getIndexOfComputer(client)]=getIndexOfWire(w_R1_R2);
		routing[getIndexOfComputer(router2)][getIndexOfComputer(router1)]=getIndexOfWire(w_R1_R2);
		if ((wires[getIndexOfWire(w_A_R1)].connected)&&(wires[getIndexOfWire(w_A_R2)].connected)){
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(client)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router1)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router2)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server1)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server2)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(router1)][getIndexOfComputer(attacker)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(router2)][getIndexOfComputer(attacker)]=getIndexOfWire(w_A_R2);
		}else if ((wires[getIndexOfWire(w_A_R1)].connected)&&(!wires[getIndexOfWire(w_A_R2)].connected)){
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(client)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router1)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router2)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server1)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server2)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(router1)][getIndexOfComputer(attacker)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(router2)][getIndexOfComputer(attacker)]=getIndexOfWire(w_R1_R2);
		}else if ((!wires[getIndexOfWire(w_A_R1)].connected)&&(wires[getIndexOfWire(w_A_R2)].connected)){
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(client)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router1)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router2)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server1)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server2)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(router1)][getIndexOfComputer(attacker)]=getIndexOfWire(w_R1_R2);
			routing[getIndexOfComputer(router2)][getIndexOfComputer(attacker)]=getIndexOfWire(w_A_R2);
		}else if ((!wires[getIndexOfWire(w_A_R1)].connected)&&(!wires[getIndexOfWire(w_A_R2)].connected)){
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(client)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router1)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router2)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server1)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server2)]=-1;
			routing[getIndexOfComputer(router1)][getIndexOfComputer(attacker)]=-1;
			routing[getIndexOfComputer(router2)][getIndexOfComputer(attacker)]=-1;
		}
	}else{
		if ((wires[getIndexOfWire(w_A_R1)].connected)&&(wires[getIndexOfWire(w_A_R2)].connected)){
			routing[getIndexOfComputer(router1)][getIndexOfComputer(router2)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(router1)][getIndexOfComputer(server1)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(router1)][getIndexOfComputer(server2)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(router2)][getIndexOfComputer(client)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(router2)][getIndexOfComputer(router1)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(client)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router1)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router2)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server1)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server2)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(router1)][getIndexOfComputer(attacker)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(router2)][getIndexOfComputer(attacker)]=getIndexOfWire(w_A_R2);
		}else if ((wires[getIndexOfWire(w_A_R1)].connected)&&(!wires[getIndexOfWire(w_A_R2)].connected)){
			routing[getIndexOfComputer(router1)][getIndexOfComputer(router2)]=-1;
			routing[getIndexOfComputer(router1)][getIndexOfComputer(server1)]=-1;
			routing[getIndexOfComputer(router1)][getIndexOfComputer(server2)]=-1;
			routing[getIndexOfComputer(router2)][getIndexOfComputer(client)]=-1;
			routing[getIndexOfComputer(router2)][getIndexOfComputer(router1)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(client)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router1)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router2)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server1)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server2)]=-1;
			routing[getIndexOfComputer(router1)][getIndexOfComputer(attacker)]=getIndexOfWire(w_A_R1);
			routing[getIndexOfComputer(router2)][getIndexOfComputer(attacker)]=-1;
		}else if ((!wires[getIndexOfWire(w_A_R1)].connected)&&(wires[getIndexOfWire(w_A_R2)].connected)){
			routing[getIndexOfComputer(router1)][getIndexOfComputer(router2)]=-1;
			routing[getIndexOfComputer(router1)][getIndexOfComputer(server1)]=-1;
			routing[getIndexOfComputer(router1)][getIndexOfComputer(server2)]=-1;
			routing[getIndexOfComputer(router2)][getIndexOfComputer(client)]=-1;
			routing[getIndexOfComputer(router2)][getIndexOfComputer(router1)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(client)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router1)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router2)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server1)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server2)]=getIndexOfWire(w_A_R2);
			routing[getIndexOfComputer(router1)][getIndexOfComputer(attacker)]=-1;
			routing[getIndexOfComputer(router2)][getIndexOfComputer(attacker)]=getIndexOfWire(w_A_R2);
		}else if ((!wires[getIndexOfWire(w_A_R1)].connected)&&(!wires[getIndexOfWire(w_A_R2)].connected)){
			routing[getIndexOfComputer(router1)][getIndexOfComputer(router2)]=-1;
			routing[getIndexOfComputer(router1)][getIndexOfComputer(server1)]=-1;
			routing[getIndexOfComputer(router1)][getIndexOfComputer(server2)]=-1;
			routing[getIndexOfComputer(router2)][getIndexOfComputer(client)]=-1;
			routing[getIndexOfComputer(router2)][getIndexOfComputer(router1)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(client)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router1)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(router2)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server1)]=-1;
			routing[getIndexOfComputer(attacker)][getIndexOfComputer(server2)]=-1;
			routing[getIndexOfComputer(router1)][getIndexOfComputer(attacker)]=-1;
			routing[getIndexOfComputer(router2)][getIndexOfComputer(attacker)]=-1;
		}
	}
}

void CScenario::initiateProtocol(bool authenticateAttacker)
{
	protocolRunning=TRUE;
	authenticationFailed=FALSE;
	checkAuthenticationFailed=FALSE;
	step=0;
	if (authenticateAttacker){
		authenticator=attacker;
	}else{
		authenticator=client;
	}
	for(int i=0;i<=numPackets-1;i++){
		packets[i].visible=FALSE;
	}
	protocolStep();
}

void CScenario::protocolStep()
{
	if (mode==1){ //"Einführung"
		switch(step){
		case 0: // 1. Paket abschicken
			packets[0].activate(dataCaption_Passwort,computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_Passwort), getIndexOfComputer(server1), getIndexOfComputer(server1), getIndexOfComputer(authenticator), FALSE);
			break;
		case 1: // 2. Paket abschicken
			packets[0].activate(dataCaption_Passwort,computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_Passwort), getIndexOfComputer(authenticator), getIndexOfComputer(authenticator), getIndexOfComputer(server1), FALSE);
			break;
		case 2:
			packets[0].active=FALSE;
			protocolRunning=FALSE;
			break;
		}
	}
	if (mode==2){ //"Passwort"
		switch(step){
		case 0: //Passwort abschicken
			checkAuthenticationFailed=TRUE;
			packets[0].activate(dataCaption_Passwort,computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_Passwort), getIndexOfComputer(authenticator), getIndexOfComputer(authenticator), getIndexOfComputer(server1), FALSE);
			break;
		case 1: //Server prüft Antwort
			// "OK"
			packets[0].active=FALSE;
			protocolRunning=FALSE;
			break;
		}
	}

	if (mode==3){ //"Einmalpasswörter"
		switch(step){
		case 0: //Einmalpasswort abschicken
			checkAuthenticationFailed=TRUE;
			packets[0].activate(dataCaption_Einmalpasswort,computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_Einmalpasswort), getIndexOfComputer(authenticator), getIndexOfComputer(authenticator), getIndexOfComputer(server1), FALSE);
			break;
		case 1: //Server prüft Antwort
			// "OK"
			
			// neues Einmalpasswort bestimmen
			CString newPassword;
			newPassword=computers[getIndexOfComputer(client)].data.getValueByLabel(dataCaption_Einmalpasswort);
			newPassword=newPassword.Mid(1) + (CString)newPassword.GetAt(0);
			computers[getIndexOfComputer(client)].data.changeValue(dataCaption_Einmalpasswort, newPassword);
			computers[getIndexOfComputer(server1)].data.changeValue(dataCaption_Einmalpasswort, newPassword);
			packets[0].active=FALSE;
			protocolRunning=FALSE;
			break;
		}
	}
	
	if (mode==4){ //"Challenge Response Symmetrisch"
		CString newResponse;
		CString newChallenge;
		switch(step){
		case 0: //Challenge
			
			//Challenge neu erzeugen
			newChallenge=dataValue_ChallengeFromServer1;
			newChallenge=newChallenge.Mid(1) + (CString)newChallenge.GetAt(0);
			dataValue_ChallengeFromServer1=newChallenge;
			computers[getIndexOfComputer(server1)].data.changeValue(dataCaption_ChallengeFromServer1, newChallenge);
			
			//Response bestimmen
			newResponse=(CString)computers[getIndexOfComputer(server1)].data.getValueByLabel(dataCaption_Schluessel).GetAt(0)+computers[getIndexOfComputer(server1)].data.getValueByLabel(dataCaption_ChallengeFromServer1);
			computers[getIndexOfComputer(server1)].data.changeValue(dataCaption_ResponseToServer1, newResponse);

			//Challenge abschicken
			packets[0].activate(dataCaption_ChallengeFromServer1,computers[getIndexOfComputer(server1)].data.getValueByLabel(dataCaption_ChallengeFromServer1), getIndexOfComputer(server1), getIndexOfComputer(server1), getIndexOfComputer(authenticator), FALSE);
			break;
		
		case 1: //Response
			checkAuthenticationFailed=TRUE;
			//Response bestimmen
			
			newResponse=(CString)computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_Schluessel).GetAt(0)+computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_ChallengeFromServer1);
			computers[getIndexOfComputer(authenticator)].data.changeValue(dataCaption_ResponseToServer1, newResponse);
			
			//Response abschicken
			packets[0].activate(dataCaption_ResponseToServer1,computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_ResponseToServer1), getIndexOfComputer(authenticator), getIndexOfComputer(authenticator), getIndexOfComputer(server1), FALSE);
			break;
		case 2: //Response prüfen
			// "OK"
			packets[0].active=FALSE;
			protocolRunning=FALSE;
			break;
		}
	}

	if (mode==5){ //"Challenge Response Asymmetrisch"
		CString newResponse;
		CString newChallenge;
		switch(step){
		case 0: //Challenge
			
			//Challenge neu erzeugen
			newChallenge=dataValue_ChallengeFromServer1;
			newChallenge=newChallenge.Mid(1) + (CString)newChallenge.GetAt(0);
			dataValue_ChallengeFromServer1=newChallenge;
			computers[getIndexOfComputer(server1)].data.changeValue(dataCaption_ChallengeFromServer1, newChallenge);

			//Response bestimmen
			newResponse=(CString)computers[getIndexOfComputer(server1)].data.getValueByLabel(dataCaption_oeffentlicherSchluesselClient).GetAt(0)+computers[getIndexOfComputer(server1)].data.getValueByLabel(dataCaption_ChallengeFromServer1);
			computers[getIndexOfComputer(server1)].data.changeValue(dataCaption_ResponseToServer1, newResponse);

			//Challenge abschicken
			packets[0].activate(dataCaption_ChallengeFromServer1,computers[getIndexOfComputer(server1)].data.getValueByLabel(dataCaption_ChallengeFromServer1), getIndexOfComputer(server1), getIndexOfComputer(server1), getIndexOfComputer(authenticator), FALSE);
			break;
		
		case 1: //Response
			checkAuthenticationFailed=TRUE;
			
			//Response bestimmen
			if (authenticator==client){
				newResponse=(CString)computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_geheimerSchluesselClient).GetAt(0)+computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_ChallengeFromServer1);
			}else{
				newResponse=computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_ResponseToServer1);
			}
				
			computers[getIndexOfComputer(authenticator)].data.changeValue(dataCaption_ResponseToServer1, newResponse);
			
			//Response abschicken
			packets[0].activate(dataCaption_ResponseToServer1,computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_ResponseToServer1), getIndexOfComputer(authenticator), getIndexOfComputer(authenticator), getIndexOfComputer(server1), FALSE);
			break;
		case 2: //Response prüfen
			// "OK"
			packets[0].active=FALSE;
			protocolRunning=FALSE;
			break;
		}
	}

	if (mode==6){ //"Wechselseitige Authentifikation"
		CString newResponse;
		CString verification;
		CString newChallenge;
		switch(step){
		case 0: //Challenge von Server1
			
			//Challenge von Server1 neu erzeugen
			newChallenge=dataValue_ChallengeFromServer1;
			newChallenge=newChallenge.Mid(1) + (CString)newChallenge.GetAt(0);
			dataValue_ChallengeFromServer1=newChallenge;
			computers[getIndexOfComputer(server1)].data.changeValue(dataCaption_ChallengeFromServer1, newChallenge);

			//Challenge abschicken
			packets[0].activate(dataCaption_ChallengeFromServer1,computers[getIndexOfComputer(server1)].data.getValueByLabel(dataCaption_ChallengeFromServer1), getIndexOfComputer(server1), getIndexOfComputer(server1), getIndexOfComputer(authenticator), FALSE);
			break;
		
		case 1: //Response und Challenge von Client
			//checkAuthenticationFailed=TRUE;
			
			//Challenge von Client neu erzeugen
			newChallenge=dataValue_ChallengeFromClient;
			newChallenge=newChallenge.Mid(1) + (CString)newChallenge.GetAt(0);
			dataValue_ChallengeFromClient=newChallenge;
			computers[getIndexOfComputer(authenticator)].data.changeValue(dataCaption_ChallengeFromClient, newChallenge);

			//Challenges signieren als Response an Server1
			if (authenticator==client){
				newResponse=(CString)computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_geheimerSchluesselClient).GetAt(0) + computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_ChallengeFromServer1) + computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_ChallengeFromClient);
			}else{
				newResponse=computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_ResponseToServer1);
			}
			computers[getIndexOfComputer(authenticator)].data.changeValue(dataCaption_ResponseToServer1, newResponse);
			
			//Response abschicken
			
			packets[0].activate(dataCaption_ResponseToServer1,computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_ResponseToServer1), getIndexOfComputer(authenticator), getIndexOfComputer(authenticator), getIndexOfComputer(server1), FALSE);
			packets[0].addMoreData(dataCaption_ChallengeFromClient,computers[getIndexOfComputer(authenticator)].data.getValueByLabel(dataCaption_ChallengeFromClient));
			break;

		case 2: //Response von Client prüfen, Response an Client erzeugen
			//checkAuthenticationFailed=TRUE;

			//Response von Client prüfen
			//1. Signatur umkehren
			verification=(CString)computers[getIndexOfComputer(server1)].data.getValueByLabel(dataCaption_ResponseToServer1);
			verification=(CString)verification.Right(verification.GetLength()-1);
			//2. Inhalt prüfen
			if (!((verification.Left(computers[getIndexOfComputer(server1)].data.getValueByLabel(dataCaption_ChallengeFromServer1).GetLength())==(CString)computers[getIndexOfComputer(server1)].data.getValueByLabel(dataCaption_ChallengeFromServer1))
			  && (verification.Right(computers[getIndexOfComputer(server1)].data.getValueByLabel(dataCaption_ChallengeFromClient).GetLength())==(CString)computers[getIndexOfComputer(server1)].data.getValueByLabel(dataCaption_ChallengeFromClient)))){

				authenticationFailed=TRUE;
				packets[0].active=FALSE;
				protocolRunning=FALSE;
				break;
			}
			//Challenges signieren als Response an Client
			newResponse=(CString) dataValue_geheimerSchluesselServer1.GetAt(0) + dataValue_ChallengeFromClient + dataValue_ChallengeFromServer1;
			computers[getIndexOfComputer(server1)].data.changeValue(dataCaption_ResponseToClient, newResponse);
			
			//Response abschicken
			packets[0].activate(dataCaption_ResponseToClient,computers[getIndexOfComputer(server1)].data.getValueByLabel(dataCaption_ResponseToClient), getIndexOfComputer(server1), getIndexOfComputer(server1), getIndexOfComputer(authenticator), FALSE);
	
			break;
		
		case 3:
			// "OK"
			packets[0].active=FALSE;
			protocolRunning=FALSE;
			break;

		}

	}

}

bool CScenario::onTick(CClientDC &dc)
{
	
	bool packetsLeft=FALSE;
		
	for(int i=0;i<=numPackets-1;i++){
		if (packets[i].active==TRUE){
			packetsLeft=TRUE;
			
			//altes Paket löschen
			packets[i].erase(dc);

			//Paket ist auf Draht
			if(packets[i].onWire){
				
				//Paketkoordinaten berechnen
				packets[i].setParameters(wires[packets[i].actualWire].getXForWireStep(packets[i].actualWireStep,packets[i].lastComputer)-5, wires[packets[i].actualWire].getYForWireStep(packets[i].actualWireStep,packets[i].lastComputer)-5, wires[packets[i].actualWire].getXForWireStep(packets[i].actualWireStep,packets[i].lastComputer)+5, wires[packets[i].actualWire].getYForWireStep(packets[i].actualWireStep,packets[i].lastComputer)+5, 1);

				//weiteres Vorgehen bestimmen
				if ((packets[i].actualWireStep>0)&&(packets[i].actualWireStep<wireSteps)){
					//Paket im nächsten Schritt weiter auf Draht
					packets[i].actualWireStep++;
				}else if (packets[i].actualWireStep==wireSteps){
					//Paket im nächsten Schritt auf Computer
					packets[i].onWire=FALSE;
					packets[i].lastComputer=wires[packets[i].actualWire].getTargetComputer(packets[i].lastComputer);
				}

			//Paket ist auf Rechner
			}else{
				//alte Schrift löschen
				for(int c=0;c<=numComputers-1;c++){
					computers[c].eraseDataText(dc);
				}
				
				//Paketkoordinaten berechnen
				packets[i].setParameters((computers[packets[i].lastComputer].getX1()+10),computers[packets[i].lastComputer].getY1()+10,computers[packets[i].lastComputer].getX2()-10,computers[packets[i].lastComputer].getY2()-10,1);
				
				//weiteres Vorgehen bestimmen
				
				//Paket hat Ziel erreicht
				if(packets[i].lastComputer==packets[i].targetComputer){
					//Paket trotz Deaktivierung zeichnen
					packets[i].visible=TRUE;
					//ggf. Inhalt des Pakets auf Richtigkeit überprüfen
					if ((checkAuthenticationFailed)&&(packets[i].targetComputer!=getIndexOfComputer(attacker))){
						if(computers[packets[i].targetComputer].data.getValueByLabel(packets[i].data.getLabel(0))!=packets[i].data.getValue(0)){
							authenticationFailed=TRUE;
						}	
					//Neuen Wert kopieren
					}else{
						for(int j=0;j<packets[i].data.getNumberOfLines();j++){
							computers[packets[i].targetComputer].data.changeValue(packets[i].data.getLabel(j),packets[i].data.getValue(j));
						}
					}
					//ggf. mit Protokoll fortfahren
					if(packets[i].attackerCopy==FALSE){
						step++;
						protocolStep();
					}else{
						packets[i].active=FALSE;
					}
					
				//Paket muss auf neuen Draht
				}else{
					packets[i].actualWire=routing[packets[i].lastComputer][packets[i].targetComputer];
					if (routing[getIndexOfComputer(router1)][getIndexOfComputer(attacker)]==getIndexOfWire(w_A_R2)) drin=TRUE;
					packets[i].onWire=TRUE;
					packets[i].actualWireStep=1;
					if (packets[i].actualWire==-1){
						packets[i].active=FALSE;
					}
				}

				//Rechner ist Angreiferrechner
				if ((packets[i].lastComputer)==getIndexOfComputer(attacker)){
					//computers[getIndexOfComputer(attacker)].data.changeValue(packets[i].data.getLabel(0),packets[i].data.getValue(0)); //Neuen Wert kopieren
					for(int j=0;j<packets[i].data.getNumberOfLines();j++){
							computers[getIndexOfComputer(attacker)].data.changeValue(packets[i].data.getLabel(j),packets[i].data.getValue(j));
					}
				}

				//Rechner ist angegriffen
				if (computers[packets[i].lastComputer].underAttack==TRUE){
					//Paket ist nicht ohnehin schon Angreiferkopie
					if(packets[i].attackerCopy==FALSE){
						
						//suche freie Paketnummer
						int newPacket=-1;
						for(int np=numPackets-1;np>=0;np--){
							if (packets[np].active==FALSE){
								newPacket=np;
							}
						}
						if (newPacket > -1){
							packets[newPacket].activate(packets[i].data.getLabel(0),packets[i].data.getValue(0),packets[i].lastComputer,packets[i].lastComputer,getIndexOfComputer(attacker),TRUE);
						}
						//packets[2].activate(packets[i].data.getLabel(0),packets[i].data.getValue(0),packets[i].lastComputer,packets[i].lastComputer,getIndexOfComputer(attacker),TRUE);
					}
				}
				
			}
						
		}

	}
	return packetsLeft;
}
