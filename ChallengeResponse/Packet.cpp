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

// Packet.cpp: implementation of the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Packet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPacket::CPacket()
{

}

CPacket::~CPacket()
{

}

void CPacket::draw(CClientDC &dc)
{
	if (visible||active){
		originalPen = dc.SelectObject(&blackPen);
	}else{
		originalPen = dc.SelectObject(&whitePen);
	}
	dc.Rectangle(x1,y1,x2,y2);
	
	dc.MoveTo(x1+1,y1+1);
	dc.LineTo(x2-1,y2-1);
	dc.MoveTo(x1+1,y2-1);
	dc.LineTo(x2-1,y1+1);

	dc.SelectObject(&originalPen);
}

void CPacket::erase(CClientDC &dc)
{
	originalPen = dc.SelectObject(&whitePen);
	
	dc.Rectangle(x1,y1,x2,y2);
	
	dc.MoveTo(x1,y1);
	dc.LineTo(x2,y2);
	dc.MoveTo(x1,y2);
	dc.LineTo(x2,y1);

	dc.SelectObject(&originalPen);
}


void CPacket::activate(CString contentCaption, CString contentValue, int startComputer, int lastComputer, int targetComputer, bool attackerCopy)
{
	active=TRUE;
	onWire=FALSE;
	actualWireStep=0; //eigentlich 1, hier 0 damit Fehler auffallen.
	data.clearLists();
	data.addLabel(contentCaption);
	data.changeValue(contentCaption,contentValue);
	this->startComputer=startComputer;
	this->lastComputer=lastComputer;
	this->targetComputer=targetComputer;
	this->attackerCopy=attackerCopy;

}


void CPacket::setParameters(int x1, int y1, int x2, int y2, int borderWidth)
{
	setParametersSO(x1, y1, x2, y2, borderWidth);
	visible=FALSE;
}


void CPacket::addMoreData(CString contentCaption, CString contentValue)
{
	data.addLabel(contentCaption);
	data.changeValue(contentCaption,contentValue);
}