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