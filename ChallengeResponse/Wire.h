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

// Wire.h: interface for the Wire class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_WIRE_H__D36C4943_6742_11D6_9FD1_E4F1A1F6DF7D__INCLUDED_)
#define AFX_WIRE_H__D36C4943_6742_11D6_9FD1_E4F1A1F6DF7D__INCLUDED_

#include "ScenarioObject.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWire : public CScenarioObject
{

public:
	int getYForWireStep(int i, int lastComputer);
	int getXForWireStep(int i, int lastComputer);
	// geerbete Varablen und Methoden
	//bool visible;
	void draw(CClientDC& dc);

	// eigene Variablen und Methoden
	bool connected;
	int getTargetComputer(int startComputer);
	bool isMouseOverObjectPoint(int x, int y);
	bool isMouseOverObject(CPoint& point);
	void setParameters(int computer1, int computer2, int x1, int y1, int x2, int y2, int steps, int borderwidth, CString caption, bool type, bool init_connected);
	CWire();
	virtual ~CWire();

private:
	bool isBetween(int a1, int a2, int b);
	int computer1, computer2;
	int steps, intervallX,intervallY;
	bool mark;
	bool type;
	bool changeColor;
	
	
	
};

#endif // !defined(AFX_WIRE_H__D36C4943_6742_11D6_9FD1_E4F1A1F6DF7D__INCLUDED_)
