// Zufallsgenerator_Tests_Alles.cpp: Implementierung der Klasse Zufallsgenerator_Tests.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "fileutil.h"
#include "Zufallsgenerator_Tests_Alles.h"
#include <fstream>
#include <cstdlib>




#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Zufallsgenerator_Tests::Zufallsgenerator_Tests()
{
	alpha=0.05f;
	bestanden=FALSE;
	x1=0;
}

Zufallsgenerator_Tests::~Zufallsgenerator_Tests()
{
}

void Zufallsgenerator_Tests::vergleiche_x1()
{
	// Mora se implemetirati ALPHA i uzimati parametar iz glavnog arraya!!!
	if(Get_x1() <= 3.8415) Set_result(TRUE);
}

//////////////////////////////////////////////////////////////////////
// Freq_Test Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Freq_Test::Freq_Test()
{
}

Freq_Test::~Freq_Test()
{
}

void Freq_Test::test()
{
	unsigned char ch;
	int num, null=0, eins=0,i,n=0;
//	GetTmpName(infile,"rnd",".hex");
	ifstream citaj(infile, ios::in);


	if (citaj)
	{
		while(citaj >> ch)
		{
			n++;
			num = (unsigned int) ch;
			for(i=1;i<=8;i++)
			{
				if ( num % 2 ) eins++;
				else null++;
				num /= 2;
			}
		}
	}
	Set_x1((pow(null - eins,2)/n));
	vergleiche_x1();
}
