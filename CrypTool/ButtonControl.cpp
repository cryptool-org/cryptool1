// ButtonControl.cpp

#include "ButtonControl.h"

// Klasse BitmapButton
// ===========================================================================================================
BitmapButton::BitmapButton()
{
	this->bIsActionPerformed = false;
	this->bIsActive = false;
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
// ===========================================================================================================



// Klasse BitmapButtonControl
// ===========================================================================================================
BitmapButtonControl::BitmapButtonControl()
{

}

BitmapButtonControl::~BitmapButtonControl()
{

}
// ===========================================================================================================

// Klasse MyBitmapButtonControl
// ===========================================================================================================
MyBitmapButtonControl::MyBitmapButtonControl()
{
	
}

MyBitmapButtonControl::MyBitmapButtonControl(CWnd *parent)
{
	// Anzahl der Buttons bestimmen
	NumberOfButtons = 0;
	while ( BitmapResources[NumberOfButtons++].BitmapName[0][0] );
	
	NumberOfButtons--;
	
	AllButtons = new BitmapButton[NumberOfButtons];
	// Einzelen Buttons laden
	for ( int i=0; i<NumberOfButtons; i++ )
	{
		AllButtons[i].Init( BitmapResources[i], parent );
	}

	this->Update();
}

MyBitmapButtonControl::~MyBitmapButtonControl()
{
	delete[] AllButtons;
}

// ===========================================================================================================
