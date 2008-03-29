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


// TextAnalyse.cpp: Implementierung der Klasse TextAnalyse.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KeyParameterHomophone.h"
#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif
#include "CrypToolApp.h"
#include "assert.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

void CKeyParameterHomophone::Init(int _keyType = HOM_ENC_TXT)
{
	int i;
	for(i=0;i<range;i++)
	{
		count[i]=0;
		freq[i]=-1.0;
	}
	total_count=0;
	keyType = _keyType;
}

CKeyParameterHomophone::CKeyParameterHomophone()
{
	Init();
}

CKeyParameterHomophone::~CKeyParameterHomophone()
{

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

	if ( HOM_ENC_TXT == keyType )
	{
		if(FALSE==theApp.TextOptions.getDistinguishUpperLowerCase())
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
			for(j=0;j<theApp.TextOptions.getAlphabet().GetLength();j++)
			{
				if((unsigned short)theApp.TextOptions.getAlphabet().GetAt(j)==i)
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

void CKeyParameterHomophone::Analyse(const char *f_toAnalyse, int _keyType)
{
	char buffer[buffsize];
	int i,value;

	ifstream f(f_toAnalyse, ios::binary | ios::in );
	f.read(buffer,buffsize);

	Init(_keyType);

	while(f.gcount())
	{
		for(i=0;i<f.gcount();i++)
		{
			value=(unsigned char)buffer[i];
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

void CKeyParameterHomophone::Analyse(int _keyType)

// erstellt für die Referenzdatei das Histogramm

{
	char buffer[buffsize];
	int i,value;

	Init(_keyType);

	// check for reference file for statistical applications
	while(theApp.TextOptions.getReferenceFile().IsEmpty()) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STATISTICAL_REFERENCE_FILE_MISSING, pc_str, STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str, MB_ICONINFORMATION);

		// open text options dialog
		if(theApp.TextOptions.DoModal() != IDOK)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STATISTICAL_REFERENCE_FILE_STILL_MISSING, pc_str, STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str, MB_ICONINFORMATION);
			return;
		}
	}

	// at this point the reference file should be valid

	ifstream f(theApp.TextOptions.getReferenceFile(), ios::binary | ios::in );
	f.read(buffer,buffsize);

	while(f.gcount())
	{
		for(i=0;i<f.gcount();i++)
		{
			value=(unsigned char)buffer[i];
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