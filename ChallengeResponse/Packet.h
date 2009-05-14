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

// Packet.h: interface for the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKET_H__D1B4CB61_6D7B_11D6_9FD1_DD9275F6D937__INCLUDED_)
#define AFX_PACKET_H__D1B4CB61_6D7B_11D6_9FD1_DD9275F6D937__INCLUDED_

#include "ScenarioObject.h"
#include "Data.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPacket : CScenarioObject
{
public:
	void addMoreData(CString contentCaption, CString contentValue);
	bool visible;
	int actualWireStep;
	void erase(CClientDC &dc);
	void setParameters(int x1, int y1, int x2, int y2, int borderWidth);
	bool attackerCopy;
	int actualWire;
	bool onWire;
	
	
	
	//geerbte Variablen und Methoden
	void draw(CClientDC& dc);
	
	//eigene Variablen und Methoden
	int targetComputer;
	int lastComputer;
	int startComputer;
	CData data;
	bool active;
	void activate(CString contentCaption, CString contentValue, int startComputer, int lastComputer, int targetComputer, bool attackerCopy);

	//Konstruktor & Dekonstruktor
	CPacket();
	virtual ~CPacket();
};

#endif // !defined(AFX_PACKET_H__D1B4CB61_6D7B_11D6_9FD1_DD9275F6D937__INCLUDED_)
