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


// DiffieHellmanButtonControl.h

#ifndef _DIFFIEHELLMANBUTTONCONTROL_
#define _DIFFIEHELLMANBUTTONCONTROL_

#include "ButtonControl.h"

// DIFFIE-HELLMAN-VISUALISIERUNG
const ButtonResourceStruct DH_BitmapResources[] = 
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

class DiffieHellmanBitmapButtonControl : public BitmapButtonControl 
{
private:
	/*****************************************************************************************************/
	// Diese Funktion steuert die Abhängigkeit der Buttons untereinander, d.h....
	// Die Funktion
	//						void SetActive( bool )
	//
	// bestimmt, ob ein entsprechender Button aktiviert oder deaktiviert wird.
	//
	// Um dabei die Abhängigkeit von anderen Buttons zu implementieren, wird ein boolscher
	// Wert übergeben, der den Zustand des jeweils anderen Buttons widerspiegelt.

	void Update()
	{
		AllButtons[0].SetActive(true);
		AllButtons[1].SetActive( AllButtons[0].IsActionPerformed() );
		AllButtons[2].SetActive( AllButtons[5].IsActionPerformed() || AllButtons[6].IsActionPerformed() );
		AllButtons[3].SetActive( AllButtons[7].IsActionPerformed() && AllButtons[8].IsActionPerformed() );
		AllButtons[4].SetActive( AllButtons[3].IsActionPerformed() );
		AllButtons[5].SetActive( AllButtons[1].IsActionPerformed() );
		AllButtons[6].SetActive( AllButtons[1].IsActionPerformed() );
		AllButtons[7].SetActive( AllButtons[5].IsActionPerformed() && AllButtons[2].IsActionPerformed() );
		AllButtons[8].SetActive( AllButtons[6].IsActionPerformed() && AllButtons[2].IsActionPerformed() );
		AllButtons[9].SetActive( AllButtons[4].IsActionPerformed() );
		AllButtons[10].SetActive(AllButtons[4].IsActionPerformed() );
		AllButtons[11].SetActive(AllButtons[9].IsActionPerformed() && AllButtons[10].IsActionPerformed() );
			

		//Die entsprechenden Bitmaps laden
		for(int i=0; i<NumberOfButtons;i++)
			if ( AllButtons[i].StatusChanged() )
			{
				if( AllButtons[i].IsActive() ) AllButtons[i].Button.EnableWindow( true );
				else AllButtons[i].Button.EnableWindow( false );

				AllButtons[i].ShowBitmaps();
				AllButtons[i].ResetStatusChanged();
			}
    };
	/*****************************************************************************************************/

public:
	DiffieHellmanBitmapButtonControl();
	DiffieHellmanBitmapButtonControl(CWnd*);
	virtual ~DiffieHellmanBitmapButtonControl();
	
	
	// Diese Funktion beeinflusst (neben der Funktion: void Update) das Zustandsverhalten der einzelnen Buttons
	// Je nach dem, welcher Button gerade gedrückt wurde (siehe Parameter), so werden die entsprechenden
	// "abhängigen" Buttons alle zurückgesetzt.
	void PerformAction(const int b)
	{
		// Entsprechenden Button "drücken" bzw. Aktion ausführen
		this->AllButtons[b].PerformAction();

		if(b == 0)
		{
			AllButtons[1].CancelAction();
			AllButtons[2].CancelAction();
			AllButtons[3].CancelAction();
			AllButtons[4].CancelAction();
			AllButtons[5].CancelAction();
			AllButtons[6].CancelAction();
			AllButtons[7].CancelAction();
			AllButtons[8].CancelAction();
			AllButtons[9].CancelAction();
			AllButtons[10].CancelAction();
		}
		if(b == 1)
		{
			AllButtons[2].CancelAction();
			AllButtons[3].CancelAction();
			AllButtons[4].CancelAction();
			AllButtons[5].CancelAction();
			AllButtons[6].CancelAction();
			AllButtons[7].CancelAction();
			AllButtons[8].CancelAction();
			AllButtons[9].CancelAction();
			AllButtons[10].CancelAction();
		}
		if(b == 2)
		{
			AllButtons[3].CancelAction();
			AllButtons[4].CancelAction();
			AllButtons[7].CancelAction();
			AllButtons[8].CancelAction();
			AllButtons[9].CancelAction();
			AllButtons[10].CancelAction();
		}
		if(b == 3)
		{
			AllButtons[4].CancelAction();
			AllButtons[9].CancelAction();
			AllButtons[10].CancelAction();
		}
		if(b == 4)
		{
			AllButtons[9].CancelAction();
			AllButtons[10].CancelAction();
		}
		if(b == 5)
		{
			AllButtons[3].CancelAction();
			AllButtons[4].CancelAction();
			AllButtons[7].CancelAction();
			AllButtons[9].CancelAction();
			AllButtons[10].CancelAction();
		}
		if(b == 6)
		{
			AllButtons[3].CancelAction();
			AllButtons[4].CancelAction();
			AllButtons[8].CancelAction();
			AllButtons[9].CancelAction();
			AllButtons[10].CancelAction();
		}
		if(b == 7 || b == 8)
		{
			AllButtons[3].CancelAction();
			AllButtons[4].CancelAction();
			AllButtons[9].CancelAction();
			AllButtons[10].CancelAction();
		}
		if(b == 9)
		{

		}
		if(b == 10)
		{

		}

		this->Update();
	};

};

#endif