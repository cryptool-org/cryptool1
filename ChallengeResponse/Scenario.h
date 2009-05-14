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

// Scenario.h: interface for the CScenario class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENARIO_H__4396F5C1_6B54_11D6_9FD1_C2C4B9AE477B__INCLUDED_)
#define AFX_SCENARIO_H__4396F5C1_6B54_11D6_9FD1_C2C4B9AE477B__INCLUDED_

#include "Computer.h"	// Added by ClassView
#include "Data.h"	// Added by ClassView
#include "Packet.h"	// Added by ClassView
#include "ScenarioObject.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CScenario  
{
public:
	bool attackerCanMask();
	bool checkAuthenticationFailed;
	bool authenticationFailed;
	bool drin;
	int mode;
	bool protocolInitiated;
	bool onTick(CClientDC &dc);
	int step;
	void initiateProtocol(bool authenticateAttacker);
	void protocolStep();
	bool protocolRunning;
	void calculateShortestWays();
	int getIndexOfWire(CString name);
	int getIndexOfComputer(CString name);
	void setComputerDataChallengeResponseWechselseitig();
	void setComputerDataChallengeResponseAsymmetrisch();
	void setComputerDataChallengeResponseSymmetrisch();
	void setComputerDataEinmalpasswoerter();
	void setComputerDataPasswort();
	void clearComputerData(CClientDC& dc);
	
	int mouseClick(int action,CPoint& point, CClientDC& dc);
	bool isMouseOverObject(int action,CPoint& point);
	void changeMode(int mode,CClientDC& dc, CString& label);
	void draw(CClientDC& dc);
	CScenario();
	virtual ~CScenario();

	CString client, server1, server2, router1, router2, attacker, authenticator;
	CString w_C_R1, w_R1_R2, w_R2_S1,w_R2_S2,w_A_R1,w_A_R2;
	
	
private:
	bool isBorderEmpty(int c1);
	CData newData;
	
	void showBaseControls(bool visible);

	
	CString modeText;
	CString modeText_Start;
	CString modeText_Einfuehrung;
	CString modeText_Passwoerter;
	CString modeText_Einmalpasswoerter;
	CString modeText_ChallengeResponseSymmetrisch;
	CString modeText_ChallengeResponseAsymmetrisch;
	CString modeText_WechselseitigeAuthentifikation;

	CString dataCaption_Passwort;
	CString dataCaption_Einmalpasswort;
	CString dataCaption_Schluessel;
	CString dataCaption_geheimerSchluesselClient;
	CString dataCaption_oeffentlicherSchluesselClient;
	CString dataCaption_geheimerSchluesselServer1;
	CString dataCaption_oeffentlicherSchluesselServer1;
	CString dataCaption_ChallengeFromServer1;
	CString dataCaption_ResponseToServer1;
	CString dataCaption_ChallengeFromClient;
	CString dataCaption_ResponseToClient;

	CString dataValue_Passwort;
	CString dataValue_Einmalpasswort;
	CString dataValue_Schluessel;
	CString dataValue_geheimerSchluesselClient;
	CString dataValue_oeffentlicherSchluesselClient;
	CString dataValue_geheimerSchluesselServer1;
	CString dataValue_oeffentlicherSchluesselServer1;
	CString dataValue_ChallengeFromServer1;
	CString dataValue_ResponseToServer1;
	CString dataValue_ChallengeFromClient;
	CString dataValue_ResponseToClient;




};

#endif // !defined(AFX_SCENARIO_H__4396F5C1_6B54_11D6_9FD1_C2C4B9AE477B__INCLUDED_)
