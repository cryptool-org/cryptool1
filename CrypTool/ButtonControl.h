/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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

const ButtonResourceStruct BitmapResources[] = 
{
	{	IDC_SETPUBLICPARAMETERS,	"IDB_DH_BUTTON1_R_U",	"IDB_DH_BUTTON1_R_D",	"IDB_DH_BUTTON1_R_F",	"IDB_DH_BUTTON1_R_X",	"IDB_DH_BUTTON1_G_U",	"IDB_DH_BUTTON1_G_D",	"IDB_DH_BUTTON1_G_F",	"IDB_DH_BUTTON1_G_X" },
	{	IDC_SETSECRETS,				"IDB_DH_BUTTON2_R_U",	"IDB_DH_BUTTON2_R_D",	"IDB_DH_BUTTON2_R_F",	"IDB_DH_BUTTON2_R_X",	"IDB_DH_BUTTON2_G_U",	"IDB_DH_BUTTON2_G_D",	"IDB_DH_BUTTON2_G_F",	"IDB_DH_BUTTON2_G_X" },
	{	IDC_CREATESHAREDKEY,		"IDB_DH_BUTTON3_R_U",	"IDB_DH_BUTTON3_R_D",	"IDB_DH_BUTTON3_R_F",	"IDB_DH_BUTTON3_R_X",	"IDB_DH_BUTTON3_G_U",	"IDB_DH_BUTTON3_G_D",	"IDB_DH_BUTTON3_G_F",	"IDB_DH_BUTTON3_G_X" },
	{	IDC_EXCHANGESHAREDKEYS,		"IDB_DH_BUTTON4_R_U",	"IDB_DH_BUTTON4_R_D",	"IDB_DH_BUTTON4_R_F",	"IDB_DH_BUTTON4_R_X",	"IDB_DH_BUTTON4_G_U",	"IDB_DH_BUTTON4_G_D",	"IDB_DH_BUTTON4_G_F",	"IDB_DH_BUTTON4_G_X" },
	{	IDC_GENERATEFINALKEY,		"IDB_DH_BUTTON5_R_U",	"IDB_DH_BUTTON5_R_D",	"IDB_DH_BUTTON5_R_F",	"IDB_DH_BUTTON5_R_X",	"IDB_DH_BUTTON5_G_U",	"IDB_DH_BUTTON5_G_D",	"IDB_DH_BUTTON5_G_F",	"IDB_DH_BUTTON5_G_X" },
	{	IDC_BUTTONALICE1,			"IDB_DH_SECRET_R_U",	"IDB_DH_SECRET_R_D",	"IDB_DH_SECRET_R_F",	"IDB_DH_SECRET_R_X",	"IDB_DH_SECRET_G_U",	"IDB_DH_SECRET_G_D",	"IDB_DH_SECRET_G_F",	"IDB_DH_SECRET_G_X"  },
	{	IDC_BUTTONBOB1,				"IDB_DH_SECRET_R_U",	"IDB_DH_SECRET_R_D",	"IDB_DH_SECRET_R_F",	"IDB_DH_SECRET_R_X",	"IDB_DH_SECRET_G_U",	"IDB_DH_SECRET_G_D",	"IDB_DH_SECRET_G_F",	"IDB_DH_SECRET_G_X"  },
	{	IDC_BUTTONALICE2,			"IDB_DH_CALCULATE_R_U",	"IDB_DH_CALCULATE_R_D",	"IDB_DH_CALCULATE_R_F",	"IDB_DH_CALCULATE_R_X",	"IDB_DH_CALCULATE_G_U",	"IDB_DH_CALCULATE_G_D",	"IDB_DH_CALCULATE_G_F",	"IDB_DH_CALCULATE_G_X" },
	{	IDC_BUTTONBOB2,				"IDB_DH_CALCULATE_R_U",	"IDB_DH_CALCULATE_R_D",	"IDB_DH_CALCULATE_R_F",	"IDB_DH_CALCULATE_R_X",	"IDB_DH_CALCULATE_G_U",	"IDB_DH_CALCULATE_G_D",	"IDB_DH_CALCULATE_G_F",	"IDB_DH_CALCULATE_G_X" },
	{	IDC_BUTTONALICE3,			"IDB_DH_CALCULATE_R_U",	"IDB_DH_CALCULATE_R_D",	"IDB_DH_CALCULATE_R_F",	"IDB_DH_CALCULATE_R_X", "IDB_DH_CALCULATE_G_U",	"IDB_DH_CALCULATE_G_D",	"IDB_DH_CALCULATE_G_F",	"IDB_DH_CALCULATE_G_X" },
	{	IDC_BUTTONBOB3,				"IDB_DH_CALCULATE_R_U",	"IDB_DH_CALCULATE_R_D",	"IDB_DH_CALCULATE_R_F",	"IDB_DH_CALCULATE_R_X", "IDB_DH_CALCULATE_G_U",	"IDB_DH_CALCULATE_G_D",	"IDB_DH_CALCULATE_G_F",	"IDB_DH_CALCULATE_G_X" },
	{	IDC_KEY,					"IDB_DH_KEY_U",			"IDB_DH_KEY_D",			"IDB_DH_KEY_F",			"IDB_DH_KEY_X",			"IDB_DH_KEY_U",			"IDB_DH_KEY_D",			"IDB_DH_KEY_F",			"IDB_DH_KEY_X" },
	
	// KENNZEICHNUNG DES STRUKTUR-ENDES, _NICHT_ MODIFIZIEREN!!!!
	{0, "", "", "", "", "", "", "", "" }
};

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