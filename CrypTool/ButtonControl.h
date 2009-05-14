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

// ButtonControl.h

#ifndef _BUTTONCONTROL_
#define _BUTTONCONTROL_

#include "stdafx.h"
#include "resource.h"

// Über dieses Struct werden den einzelnen Buttons die Ressourcen zugewiesen!
// Member:	Ressource:	Ressourcen-ID des Buttons, dem die Bitmap-Ressourcen beigefügt werden sollen
//			BitmapName:	Alle Bitmaps des Buttons (4x rot, 4x grün), jeweils UP, DOWN, FOCUS, INACTIVE
// Anmerkung:			Das ENDE der Aufreihung ist speziell gekennzeichnet, Hinweis beachten!
typedef struct ResourceStructure
{
	int Resource;
	char *BitmapName[8];
} ButtonResourceStruct;

// Diese Klasse enthält mehrere Variablen, die das Zustandsverhalten eines jeden Buttons steuern
class BitmapButton
{
private:
	// Verknüpfung zur Button-Ressource
	int ResourceID;
	// Fenster, mit dem der Button "verknüpft" ist	
	CWnd *pParent;
	// Ressourcen-Bitmaps des Buttons (MFC-Stil)
	LPCTSTR StatusGUP, StatusGDOWN, StatusGFOCUS, StatusGDISABLED;
	LPCTSTR StatusRUP, StatusRDOWN, StatusRFOCUS, StatusRDISABLED;
	// Zustände des Buttons	
	bool bIsActionPerformed;
	bool bIsActive;

	bool bStatusChanged;

public:
	// Der "eigentliche" Button
	CBitmapButton Button;
	
	BitmapButton();
	virtual ~BitmapButton();
   
	// Initialisiert die Bitmap-Ressourcen des Buttons und sein zugeordnetes Parent-Window
	void Init(const ButtonResourceStruct, CWnd*);

	bool IsActionPerformed() { return bIsActionPerformed; };
	void PerformAction() { bStatusChanged = bStatusChanged | !bIsActionPerformed; 
	                       bIsActionPerformed = true; };
	void CancelAction()  { bStatusChanged = bStatusChanged |  bIsActionPerformed; 
	                       bIsActionPerformed = false; };

	bool IsActive() { return bIsActive; };
	void SetActive(bool a) { bStatusChanged = bStatusChanged | ( a != bIsActive ); 
	                         bIsActive = a; };

	void ShowBitmaps();

	bool StatusChanged() { return bStatusChanged; }
	void ResetStatusChanged() { bStatusChanged = false; }
};

class BitmapButtonControl
{
protected:
	// Anzahl der Buttons in der Kontrollstruktur
	int NumberOfButtons;

	BitmapButtonControl();

public:
	virtual ~BitmapButtonControl();

	// Alle Buttons der Klasse in einem Array zusammengefasst
	BitmapButton *AllButtons;
	
	// Diese Funktion steuert das Zustandsverhalten der Buttons (aktiviert bzw. deaktiviert sie)
	virtual void Update() = 0;
	virtual void PerformAction(const int) = 0;
};

#endif