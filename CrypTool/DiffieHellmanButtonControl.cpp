// DiffieHellmanButtonControl.cpp

#include "stdafx.h"

#include "DiffieHellmanButtonControl.h"

DiffieHellmanBitmapButtonControl::DiffieHellmanBitmapButtonControl()
{
	
}

DiffieHellmanBitmapButtonControl::DiffieHellmanBitmapButtonControl(CWnd *parent)
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

DiffieHellmanBitmapButtonControl::~DiffieHellmanBitmapButtonControl()
{
	delete[] AllButtons;
}