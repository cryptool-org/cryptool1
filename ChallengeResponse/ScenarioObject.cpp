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

// ScenarioObject.cpp: implementation of the CScenarioObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ScenarioObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScenarioObject::CScenarioObject()
{

}

CScenarioObject::~CScenarioObject()
{

}

void CScenarioObject::draw(CClientDC &dc)
{
	//abstrakt
}

bool CScenarioObject::isMouseOverObject(CPoint &point)
{
	return isMouseOverScenarioObject(point);
}

bool CScenarioObject::isMouseOverScenarioObject(CPoint &point)
{
	if ((x1<=point.x)&&(point.x<=x2)&&(y1<=point.y)&&(point.y<=y2)){
		return TRUE;
	}else{
		return FALSE;
	}
}
void CScenarioObject::setParametersSO(int x1, int y1, int x2, int y2, int borderWidth)
{
	this->x1=x1;
	this->x2=x2;
	this->y1=y1;
	this->y2=y2;
	this->borderWidth=borderWidth;
	setPens();
}

void CScenarioObject::setPens()
{

	black=RGB(0,0,0);
	red=RGB(255,0,0);
	white=RGB(255,255,255);
	yellow=RGB(255,255,0);
	blue=RGB(0,0,183);

	if ( !(HPEN) blackPen ) // FIXME without that code an assertion occurs
		blackPen.CreatePen(PS_SOLID,borderWidth,black);
	if ( !(HPEN) redPen ) // FIXME without that code an assertion occurs
		redPen.CreatePen(PS_SOLID,borderWidth,red);
	if ( !(HPEN) yellowPen ) // FIXME without that code an assertion occurs
		yellowPen.CreatePen(PS_SOLID,borderWidth,yellow);
	if ( !(HPEN) whitePen ) // FIXME without that code an assertion occurs
		whitePen.CreatePen(PS_SOLID,borderWidth,white);
	if ( !(HPEN) bluePen ) // FIXME without that code an assertion occurs
		bluePen.CreatePen(PS_SOLID,borderWidth,blue);
}
