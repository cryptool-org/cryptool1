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

// Computer.cpp: implementation of the CComputer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Computer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComputer::CComputer()
{
	setParameters(0,0,0,0,0,(CString)"",0,-1,FALSE);
	underAttack=FALSE;
	captionTextSize=14;
	dataTextSize=12;	

	//captionFont.CreateFont(captionTextSize,0,0,0,400,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Arial");
	captionFont.CreateFont(15,0,0,0,FW_BOLD,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"ArialBold");
	dataFont.CreateFont(dataTextSize,0,0,0,400,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Arial");
}

CComputer::~CComputer()
{

}

bool CComputer::isMouseOverObject(CPoint &point)
{
	return isMouseOverScenarioObject(point);
}


void CComputer::setParameters(int x1, int y1, int x2, int y2, int borderWidth, CString &name, int textPosition, int dataPosition, bool isAttacker)
{
	setParametersSO(x1,y1,x2,y2,borderWidth);
	this->name=name;
	this->textPosition=textPosition;
	this->dataPosition=dataPosition;
	this->isAttacker=isAttacker;
}

void CComputer::draw(CClientDC &dc)
{
	if (visible){
		if ((isAttacker)||(underAttack)){
			originalPen = dc.SelectObject(&redPen);
			dc.SetTextColor(red);
		}else{
			originalPen = dc.SelectObject(&bluePen);
			dc.SetTextColor(black);
		}
	}else{
		originalPen = dc.SelectObject(&whitePen);
		dc.SetTextColor(white);
	}


	originalFont = dc.SelectObject(&captionFont);
	dc.SetBkMode(TRANSPARENT);
	
	dc.Rectangle(x1,y1,x2,y2);
	if (textPosition == 0){//oben
		dc.TextOut(x1-4*borderWidth,y1-(borderWidth+captionTextSize),name);
	}else{//rechts unten
		dc.TextOut(x2+3*borderWidth,y2+borderWidth-captionTextSize,name);
	}
	
	drawDataText(dc);

	dc.SelectObject(&originalFont);
	dc.SelectObject(&originalPen);
}

void CComputer::drawDataText(CClientDC &dc)
{
	dc.SelectObject(&dataFont);
	int x,y;
	x=1;//nicht auf 0 setzen, sonst Crash
	y=1;//nicht auf 0 setzen, sonst Crash
	for(int i=0; i<data.getNumberOfLines(); i++){
		if (dataPosition == 1){ //rechts
			x=x2+2*borderWidth;
			y=y1+i*dataTextSize;		
		}else if (dataPosition == 2){ //unten
			x=x1-borderWidth;
			y=y2+2*borderWidth+i*dataTextSize;
		}
		dc.TextOut(x,y,data.getLine(i,isAttacker));
	}
}


void CComputer::eraseDataText(CClientDC &dc)
{
	dc.SetTextColor(white);
	originalFont = dc.SelectObject(&dataFont);
	drawDataText(dc);
	dc.SelectObject(&originalFont);
}

int CComputer::getX1()
{
	return x1;
}

int CComputer::getY1()
{
	return y1;
}

int CComputer::getX2()
{
	return x2;
}

int CComputer::getY2()
{
	return y2;
}

int CComputer::getBorderWidth()
{
	return borderWidth;
}
