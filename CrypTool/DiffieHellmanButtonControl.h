// DiffieHellmanButtonControl.h

#include "ButtonControl.h"

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
		AllButtons[11].SetActive(AllButtons[9].IsActionPerformed() && AllButtons[10].IsActionPerformed() );
			
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