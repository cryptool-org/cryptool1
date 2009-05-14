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

// ButtonControl.cpp

#include "ButtonControl.h"

// Klasse BitmapButton
BitmapButton::BitmapButton()
{
	this->bIsActionPerformed = false;
	this->bIsActive = false;
	this->bStatusChanged = true;
}

BitmapButton::~BitmapButton()
{

}

void BitmapButton::Init(const ButtonResourceStruct res, CWnd *parent)
{
	this->ResourceID = res.Resource;

	// ROTE Ressourcen zuweisen...
	this->StatusRUP = res.BitmapName[0];
	this->StatusRDOWN = res.BitmapName[1];
	this->StatusRFOCUS = res.BitmapName[2];
	this->StatusRDISABLED = res.BitmapName[3];
	// GRÜNE Ressourcen zuweisen...
	this->StatusGUP = res.BitmapName[4];
	this->StatusGDOWN = res.BitmapName[5];
	this->StatusGFOCUS = res.BitmapName[6];
	this->StatusGDISABLED = res.BitmapName[7];
	
	this->pParent = parent;
	
	this->Button.AutoLoad(this->ResourceID, this->pParent);
}

void BitmapButton::ShowBitmaps()
{
	// Je nach internem Zustand (ausgeführt oder nicht) grüne oder rote Bitmaps laden
	IsActionPerformed() ? this->Button.LoadBitmaps(StatusGUP, StatusGDOWN, StatusGFOCUS, StatusGDISABLED) : this->Button.LoadBitmaps(StatusRUP, StatusRDOWN, StatusRFOCUS, StatusRDISABLED);
	
	this->Button.ShowWindow(SW_HIDE);
	this->Button.ShowWindow(SW_SHOW);
}

// Klasse BitmapButtonControl
BitmapButtonControl::BitmapButtonControl()
{

}

BitmapButtonControl::~BitmapButtonControl()
{

}
