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

// ScenarioObject.h: interface for the CScenarioObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENARIOOBJECT_H__7EE1C7C2_EB61_11D7_9FD1_ED1DDA3A9E7B__INCLUDED_)
#define AFX_SCENARIOOBJECT_H__7EE1C7C2_EB61_11D7_9FD1_ED1DDA3A9E7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScenarioObject : public CObject 
{
public:
	void setPens();
	//eigene Variablen und Methoden
	bool visible;
	void draw(CClientDC &dc);
	void setParametersSO(int x1, int y1, int x2, int y2, int borderWidth);
	bool isMouseOverScenarioObject(CPoint& point);
	bool isMouseOverObject(CPoint& point);
	CString name;

	//Konstruktor & Dekonstruktor
	CScenarioObject();
	virtual ~CScenarioObject();

protected:
	//eigene Variablen
	int  x1,y1,x2,y2;
	int  borderWidth;

	CPen blackPen, redPen, whitePen, yellowPen, bluePen;
	CPen* originalPen;
	CFont captionFont, dataFont;
	COLORREF black, red, white, yellow, blue;
	CFont* originalFont;

};

#endif // !defined(AFX_SCENARIOOBJECT_H__7EE1C7C2_EB61_11D7_9FD1_ED1DDA3A9E7B__INCLUDED_)
