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

// Wire.cpp: implementation of the Wire class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wire.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWire::CWire()
{
	
	setParameters(-1,-1,0,0,0,0,1,0, (CString)"", FALSE,FALSE);
	changeColor = FALSE;
}

CWire::~CWire()
{

}
			
void CWire::setParameters(int computer1, int computer2, int x1, int y1, int x2, int y2, int steps, int borderWidth, CString name, bool type, bool init_connected)
{
	setParametersSO(x1,y1,x2,y2,borderWidth);
	
	this->computer1=computer1;
	this->computer2=computer2;
	
	this->name=name;
	this->type=type;
	connected=init_connected;
	this->steps=steps;
	intervallX = (x2-x1)/steps;
	intervallY = (y2-y1)/steps;
}

void CWire::draw(CClientDC& dc)

{
	originalPen=dc.SelectObject(&blackPen);
	changeColor=TRUE; //wichtig, damit die Farben nicht wackeln
	if (visible){
		if (connected){
			if (type){
				dc.SelectObject(&redPen);
				dc.MoveTo(x1 ,y1);
				dc.LineTo(x2 ,y2);
				/*
				for(int i=0; i<steps;i++){
					if (changeColor == false){
						dc.SelectObject(&redPen);
						changeColor = true;
					}else{
						dc.SelectObject(&blackPen);
						changeColor = false;
					}
					dc.MoveTo(x1 + i*intervallX,y1 + i*intervallY);
					dc.LineTo(x1 + (i+1)*intervallX,y1 + (i+1)*intervallY);
				}
				*/
			}else{
				dc.SelectObject(&bluePen);
				dc.MoveTo(x1 ,y1);
				dc.LineTo(x2 ,y2);
				/*
				for(int i=0; i<steps;i++){
					if (changeColor == false){
						dc.SelectObject(&yellowPen);
						changeColor = true;
					}else{
						dc.SelectObject(&blackPen);
						changeColor = false;
					}
					dc.MoveTo(x1 + i*intervallX,y1 + i*intervallY);
					dc.LineTo(x1 + (i+1)*intervallX,y1 + (i+1)*intervallY);
				}
				*/
			}
		}else{
			if(type){
				dc.SelectObject(&whitePen);
				dc.MoveTo(x1 ,y1);
				dc.LineTo(x2 ,y2);
				/*
				for(int i=0; i<steps;i++){
					dc.MoveTo(x1 + i*intervallX,y1 + i*intervallY);
					dc.LineTo(x1 + (i+1)*intervallX,y1 + (i+1)*intervallY);
				}
				*/
			}else{
				for(int i=0; i<steps;i++){
					if (changeColor == false){
						dc.SelectObject(&whitePen);
						changeColor = true;
					}else{
						dc.SelectObject(&blackPen);
						changeColor = false;
					}
					dc.MoveTo(x1 + i*intervallX,y1 + i*intervallY);
					dc.LineTo(x1 + (i+1)*intervallX,y1 + (i+1)*intervallY);
				}
			}
		}
	}else{
		dc.SelectObject(&whitePen);	
		for(int i=0; i<steps;i++){
			dc.MoveTo(x1 + i*intervallX,y1 + i*intervallY);
			dc.LineTo(x1 + (i+1)*intervallX,y1 + (i+1)*intervallY);
		}
	}

	dc.SelectObject(&originalPen);
	
}

bool CWire::isMouseOverObject(CPoint& point)
{
	bool returnValue=FALSE;
	if (visible){
		for(int i=(point.x)-4;i<=(point.x)+4;i++){
			for(int j=(point.y)-4;j<=(point.y)+4;j++){
				if (isMouseOverObjectPoint(i,j)) returnValue=TRUE;
			}
		}
	}
	return returnValue;
}

bool CWire::isMouseOverObjectPoint(int x, int y)
{
	if ((connected)||(!type)){
		if ((isBetween(x1,x2,x))&&(isBetween(y1,y2,y))){
			
			if (((x2-x1)==0)&&((x-x1)==0)){
				return TRUE;
			}else if (((x2-x1)==0)||((x-x1)==0)){
				return FALSE;
			}else if(((y2-y1)/(x2-x1))==((y-y1)/(x-x1))){
				return TRUE;
			}else{
				return FALSE;
			}
		}else{
			return FALSE;	
		}
	}else{
		return FALSE;
	}
}

bool CWire::isBetween(int a1, int a2, int b)
{
	if ((a1<=a2)&&(a1<=b)&&(b<=a2)){
		return TRUE;
	}else if ((a2<a1)&&(a2<=b)&&(b<=a1)){
		return TRUE;
	}else{
		return FALSE;
	}
}



int CWire::getTargetComputer(int startComputer)
{
	int returnValue;
	if (computer1==startComputer){
		returnValue=computer2;
	}else if (computer2==startComputer){
		returnValue=computer1;
	}else{
		returnValue=-1;
	}
	return returnValue;
}



int CWire::getXForWireStep(int i, int lastComputer)
{
	if (lastComputer==computer1){
		return x1 + i*intervallX - intervallX/2;		
	}else{
		return x2 - i*intervallX + intervallX/2;
	}

}

int CWire::getYForWireStep(int i, int lastComputer)
{
	if (lastComputer==computer1){
		return y1 + i*intervallY - intervallY/2;	
	}else{
		return y2 - i*intervallY + intervallY/2;
	}
}
