// TextAnalyse.cpp: Implementierung der Klasse TextAnalyse.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KeyParameterHomophone.h"
#include <iostream.h>
#include "CrypToolApp.h"
#include "assert.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

void CKeyParameterHomophone::Init()
{
	int i;

	for(i=0;i<range;i++)
	{
		count[i]=0;
		freq[i]=-1.0;
	}
	total_count=0;
}

CKeyParameterHomophone::CKeyParameterHomophone()
{
	Init();
}

CKeyParameterHomophone::~CKeyParameterHomophone()
{

}

void CKeyParameterHomophone::Analyse()

// erstellt für die Referenzdatei das Histogramm

{
	char buffer[buffsize];
	int i,value;

	Init();

	ifstream f(theApp.TextOptions.m_StrRefFile, ios::binary | ios::in );
	f.read(buffer,buffsize);

	while(f.gcount())
	{
		for(i=0;i<f.gcount();i++)
		{
			value=buffer[i];
			if(0<=value&&value<range)
			{
				count[value]++;
				total_count++;
			}
		}
		f.read(buffer,buffsize);
	}
	f.close();
	Correct_count_table();
	Make_freq_table();
	assert(true==Checksum());
}

void CKeyParameterHomophone::Make_freq_table()

// setzt freq, d.h. die relative Häufigkeit aller Zeichen

{
	int i;

	for(i=0;i<range;i++)
	{
		freq[i]=double(count[i])/total_count;
	}
}

void CKeyParameterHomophone::Correct_count_table()

// korrigiert count:

//		1.	wenn "Groß/Kleinschreibung beachten" ausgeschaltet ist, werden die Häufigkeiten der
//			Kleinbuchstaben zu denen der Großbuchstaben addiert

//		2.	die Häufigkeiten von den Zeichen, die nicht im Alphabet enthalten sind, werden auf 0 gesetzt
//			und von total_count subtrahiert

{
	bool char_in_alpha;
	int i,j;

	if(FALSE==theApp.TextOptions.m_Case)
	{
		for(i=65;i<=90;i++)
		{
			count[i]+=count[i+32];
			count[i+32]=0;
		}
	}
	for(i=0;i<range;i++)
	{
		char_in_alpha=false;
		for(j=0;j<theApp.TextOptions.m_alphabet.GetLength();j++)
		{
			if(theApp.TextOptions.m_alphabet.GetAt(j)==i)
			{
				char_in_alpha=true;
			}
		}
		if(false==char_in_alpha)
		{
			total_count-=count[i];
			count[i]=0;
		}
	}
}

bool CKeyParameterHomophone::Checksum()

// prüft, ob die Summe der Häufigkeiten aller Zeichen gleich total_count ist

{
	int i;
	long sum=0;

	for(i=0;i<range;i++)
	{
		sum+=count[i];
	}
	if(sum==total_count)
	{
		return(true);
	}
	return(false);
}

void CKeyParameterHomophone::Analyse(const char *f_toAnalyse)
{
	char buffer[buffsize];
	int i,value;

	ifstream f(f_toAnalyse, ios::binary | ios::in );
	f.read(buffer,buffsize);

	Init();

	while(f.gcount())
	{
		for(i=0;i<f.gcount();i++)
		{
			value=buffer[i];
			if(0<=value&&value<range)
			{
				count[value]++;
				total_count++;
			}
		}
		f.read(buffer,buffsize);
	}
	f.close();
	Correct_count_table();
	Make_freq_table();
	assert(true==Checksum());
}
