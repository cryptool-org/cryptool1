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


public:
	// Der "eigentliche" Button
	CBitmapButton Button;
	
	BitmapButton();
	virtual ~BitmapButton();
   
	// Initialisiert die Bitmap-Ressourcen des Buttons und sein zugeordnetes Parent-Window
	void Init(const ButtonResourceStruct, CWnd*);

	bool IsActionPerformed() { return bIsActionPerformed; };
	void PerformAction() { bIsActionPerformed = true; };
	void CancelAction() { bIsActionPerformed = false; };

	bool IsActive() { return bIsActive; };
	void SetActive(bool a) { bIsActive = a; };

	void ShowBitmaps();
};

class BitmapButtonControl
{
protected:
	// Anzahl der Buttons in der Kontrollstruktur
	int NumberOfButtons;

public:
	BitmapButtonControl();
	virtual ~BitmapButtonControl();

	// Alle Buttons der Klasse in einem Array zusammengefasst
	BitmapButton *AllButtons;
	
	// Diese Funktion steuert das Zustandsverhalten der Buttons (aktiviert bzw. deaktiviert sie)
	virtual void Update() = 0;
	virtual void PerformAction(const int) = 0;
};

class MyBitmapButtonControl : public BitmapButtonControl 
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
		// Die Button-Abhängigkeiten
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
		
		// Alle Buttons parsen und entsprechend aktivieren oder deaktivieren
		for(int i=0; i<NumberOfButtons; i++)
		{
			if(!AllButtons[i].IsActive()) AllButtons[i].Button.EnableWindow(false);
			else AllButtons[i].Button.EnableWindow(true);
		}

		// Die entsprechenden Bitmaps laden
		for(i=0; i<NumberOfButtons;i++)
		{
			AllButtons[i].ShowBitmaps();
		}
    };
	/*****************************************************************************************************/

public:
	MyBitmapButtonControl();
	MyBitmapButtonControl(CWnd*);
	virtual ~MyBitmapButtonControl();
	
	
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