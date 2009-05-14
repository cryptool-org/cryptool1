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

// Computer.h: interface for the CComputer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPUTER_H__5F1B51C3_6B2B_11D6_9FD1_E041629BF17B__INCLUDED_)
#define AFX_COMPUTER_H__5F1B51C3_6B2B_11D6_9FD1_E041629BF17B__INCLUDED_

#include "Data.h"	// Added by ClassView
#include "ScenarioObject.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CComputer : CScenarioObject
{
public:
	int getBorderWidth();
	int getY2();
	int getX2();
	int getY1();
	int getX1();
	// geerbte Variablen & Methoden


	void draw(CClientDC& dc);
	void setParameters(int x1,int y1, int x2, int y2, int borderwidth, CString& name, int textposition, int dataposition, bool isAttacker);
	bool isMouseOverObject(CPoint &point);

	// eigene Variablen & Methoden
	CData data;
	bool visible;		// eigentlich in ScenarioObject, eingefügt wg. Compilerfehler
	CString name;		// eigentlich in ScenarioObject, eingefügt wg. Compilerfehler
	bool underAttack;
	void eraseDataText(CClientDC &dc);
	void drawDataText(CClientDC &dc);
	
	//Konstruktor & Dekonstruktor
	CComputer();
	virtual ~CComputer();

	
private:
	// eigene Variablen
	bool isAttacker;
	int captionTextSize;
	int dataTextSize;	
	int textPosition;
	int dataPosition;
};

#endif // !defined(AFX_COMPUTER_H__5F1B51C3_6B2B_11D6_9FD1_E041629BF17B__INCLUDED_)
