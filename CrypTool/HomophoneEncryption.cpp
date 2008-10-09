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


// Homophone_Ber.cpp: Implementierung der Klasse Homophone_Ber.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "HomophoneEncryption.h"
#include "time.h"
#include <stdlib.h>
#include "assert.h"
#include "CrypToolApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 
BOOL HomophoneData::Init( const int Size )
{
	if ( !(key             = new int[Size]) )		return FALSE;
	if ( !(decryptionData  = new char[Size]) )		return FALSE;
	SizeHomophoneKey = Size;
	Init_Data();
	return TRUE;
}

void HomophoneData::Init_Data()
// setzt die Daten der Klasse auf vernünftige Eingangswerte
{
	int i;
	for(i=0;i<SizeHomophoneKey;i++)
	{
		decryptionData[i]	= 32;
		key[i]				= -1;
	}
	for ( i=0; i<range; i++ )
	{
		encryptionData1[i]	= -1;
		encryptionData0[i]	= -1;
		doNotRoundMe[i]		= false;
		frequency[i]		= 0.0;
	}
}

void HomophoneData::Release( )
{
	if ( key )             delete []key;        
	if ( decryptionData )  delete []decryptionData;
}

BOOL HomophoneData::Resize( const int Size )
{
	Release();
	return Init( Size );
}

//////////////////////////////////////////////////////////////////////
// constructor / destructor
CHomophoneEncryption::CHomophoneEncryption()
{
	data.Init( range );
	keyType = HOM_ENC_TXT;
}

CHomophoneEncryption::~CHomophoneEncryption()
{
	data.Release();
}
//////////////////////////////////////////////////////////////////////

void CHomophoneEncryption::Make_enc_table(const int _keyType )	
// ordnet jedem plaintext-Zeichen "seine" Anzahl an ciphertext-Zeichen zu und füllt enc_data,
// so daß verschlüsselt werden kann
{
	keyType = _keyType;
	int i,last=0;

	for(i=0;i<range;i++)
	{
		if ( HOM_ENC_TXT == keyType )
		{
			if ((i > 0) && (-1 != theApp.TextOptions.getAlphabet().Find(char(i))) )
			{
				data.encryptionData1[i]=max(int(floor(data.SizeHomophoneKey*data.frequency[i])), 0);
				// Eingefügt 24. April 2001 -- Henrik Koy
				if ( (0==data.encryptionData1[i]) )
				{
					data.encryptionData1[i]=1;
					data.doNotRoundMe[i]=true;
				}
			}
			else
			{
				data.encryptionData1[i]=-1;
			}
		}
		else 
		{
			data.encryptionData1[i]=max(int(floor(data.SizeHomophoneKey*data.frequency[i])), 0);
			if ( (0==data.encryptionData1[i]) )
			{
				data.encryptionData1[i]=1;
				data.doNotRoundMe[i]=true;
			}
		}
	}

	while(data.SizeHomophoneKey!=Checksum())
	{
		if(Checksum()<data.SizeHomophoneKey)
		{
			Increase_ciphers();
		}
		else
		{
			Decrease_ciphers();
		}
	}
	assert(data.SizeHomophoneKey==Checksum());

// build the index-list
	for(i=0;i<range;i++)
	{
		if(data.encryptionData1[i]>0)
		{
			data.encryptionData0[i]=last;
			last+=data.encryptionData1[i];
		}
	}
}


int CHomophoneEncryption::Checksum()
// prüft, ob die Summe der ciphertext-Zeichen gleich range ist
{
	int i,sum=0;

	for(i=0;i<range;i++)
	{
		if(data.encryptionData1[i]>=0)
		{
			sum+=data.encryptionData1[i];
		}
	}
	return(sum);
}

void CHomophoneEncryption::Increase_ciphers()
// erhöht die Anzahl der ciphertext-Zeichen, wenn deren Summe kleiner als range ist
{
	int i,index=0;
	double value=0.0001;

	for(i=0;i<range;i++)
	{
		if( data.frequency[i]>0.0  &&
			false==data.doNotRoundMe[i] &&
			data.frequency[i]*data.SizeHomophoneKey/data.encryptionData1[i]>value)
		{
			value=data.frequency[i]*data.SizeHomophoneKey/data.encryptionData1[i];
			index=i;
		}
	}
	data.encryptionData1[index]++;
}

void CHomophoneEncryption::Decrease_ciphers()
// verringert die Anzahl der ciphertext-Zeichen, wenn deren Summe größer als range ist
{
	int i,index=0;
	double value=100;

	for(i=0;i<range;i++)
	{
		if( data.frequency[i]>0.0 && 
			false==data.doNotRoundMe[i] && 
			data.encryptionData1[i] > 1 && 
			data.frequency[i]*data.SizeHomophoneKey/data.encryptionData1[i] < value)
		{
			value=data.frequency[i]*data.SizeHomophoneKey/data.encryptionData1[i];
			index=i;
		}
	}
	data.encryptionData1[index]--;   
}

void CHomophoneEncryption::Generate_key()
// füllt key mit den Zahlen von 0 bis range in zufälliger Reihenfolge auf
{
	int i;

	for(i=0;i<data.SizeHomophoneKey;i++)
	{
		data.key[Get_free_position()]=i;
	}
	assert(true==Check_key());
}

int CHomophoneEncryption::Get_free_position()
// wird von Generate_key() aufgerufen und sucht für die Zahlen von 0 bis range einen freien Platz in key
{
	int index,value=0;

	while(-1!=value)
	{	
		char *p_index = (char*)&index;
		index = rand() % 2147483648;
		index=index % data.SizeHomophoneKey;
		value=data.key[index];
	}
	return(index);
}

int CHomophoneEncryption::Get_random_number(int number)
// gibt eine Zufallszahl zwischen 0 und (number-1) zurück
{
	// return(zz.zzgen4()%number);
	int r = rand() % number;
	if ( r < 0 ) r = -r;
	return r;
}

bool CHomophoneEncryption::Check_key()		
// prüft, ob jede Zahl zwischen 0 und data.SizeHomophoneKey genau einmal in key[] vorhanden ist
{									
	int i,j,sum;

	for(i=0;i<data.SizeHomophoneKey;i++)
	{
		sum=0;
		for(j=0;j<data.SizeHomophoneKey;j++)
		{
			if(data.key[j]==i)
			{
				sum++;
			}
		}
		if(1!=sum)
		{
			return(false);
		}
	}
	return(true);
}

int CHomophoneEncryption::Encrypt(int value)
// liefert zu dem ASCII-Wert eines plaintext-Zeichens (value) zufällig ein ciphertext-Zeichen zurück
{
	if ((HOM_ENC_TXT == keyType) && (FALSE == theApp.TextOptions.getDistinguishUpperLowerCase() && (value >= 'a' && value<='z')) )	
	{
		value += 'A'-'a';
	}
	if(data.encryptionData1[value]>0)
	{
		return(data.key[data.encryptionData0[value] + Get_random_number(data.encryptionData1[value])]);
	}
	return(-1);
}

char	CHomophoneEncryption::Decrypt( const int i)
{
	return data.decryptionData[i];
}

void CHomophoneEncryption::Make_dec_table()
// füllt data.decryptionData, so daß entschlüsselt werden kann
{
	for(int i=0;i<data.SizeHomophoneKey;i++)
	{
		data.decryptionData[i]=GetIndex(i);
	}
}

char CHomophoneEncryption::GetIndex(const int value)
// liefert zu dem ASCII-Wert eines ciphertext-Zeichens dessen Position in key zurück
{
	int index;

	int i;
	for(i=0;i<data.SizeHomophoneKey;i++)
	{
		if(value==data.key[i])
		{
			index=i;
		}
	}
	for(i=range-1;i>=0;i--)
	{
		if( data.encryptionData1[i]>0 && data.encryptionData0[i]<=index ) 
		{
			return(i);
		}
	}
	return(0);
}

const char* CHomophoneEncryption::GetKeyStr()
{
	char *keyStr = new char[data.SizeHomophoneKey*(3+LogKeySize(16)*2)+80 + range*6]; 
	int k, l, j = 0;
	char hexStr[10];

	sprintf(hexStr, "%X %X", data.SizeHomophoneKey, GetKeyType());
	for ( k=0; hexStr[k]!=0; ) keyStr[j++] = hexStr[k++];
	keyStr[j++] = '#';
	keyStr[j++] = '#';
	keyStr[j++] = '#';

	for (int i=0; i<range; i++ )
	{
		if(data.encryptionData1[i]>0)
		{
			sprintf(hexStr, "%X", i);
			for ( k=0; hexStr[k]!=0; ) keyStr[j++] = hexStr[k++];
			keyStr[j++] = ':';
			for ( l=0; l<data.encryptionData1[i]; l++)
			{
				sprintf(hexStr, "%X", data.key[data.encryptionData0[i]+l]);
				for ( k=0; hexStr[k]!=0; ) keyStr[j++] = hexStr[k++];
				if (l+1<data.encryptionData1[i]) keyStr[j++] = ',';
			}
			keyStr[j++] = ' ';
			keyStr[j++] = '#';
			keyStr[j++] = ' ';
		}
	}
	keyStr[j] = 0;
	return keyStr;
}

void CHomophoneEncryption::load_enc_table(const char *keyStr)
{
	Init_Data();
	long k, l, j = 0, Cnt = 0, Index;
	bool LoadError = false;
	
// == Die Groesse des Schluessels laden ....
	Index = 0;
	while (keyStr[j] != ' ') {
		Index *= 16;
		if ( keyStr[j] >= '0' && keyStr[j] <= '9' ) Index += keyStr[j]-'0';
		else
			if ( keyStr[j] >= 'A' && keyStr[j] <= 'F' ) Index += keyStr[j]-'A'+10;
			else { LoadError= true; break; }
		if (j++ > 8) 
		{ 
			LoadError = true;
			break;
		}
	}
	if ( LoadError ) 
		return;

	while (keyStr[j] == ' ') j++;
	if		(keyStr[j] == '0') keyType = 0;
	else if (keyStr[j] == '1') keyType = 1;
	else {
		LoadError = true;
		return;
	}
	j++;
	
	if ( Index != data.SizeHomophoneKey )
		Resize( Index );

	while (keyStr[j] != 0)
	{
		Index = 0;
		while (keyStr[j] == ' ' || keyStr[j] == '#') j++;
		while (keyStr[j] != ':') {
			Index *= 16;
			if ( keyStr[j] >= '0' && keyStr[j] <= '9' ) Index += keyStr[j]-'0';
			else
				if ( keyStr[j] >= 'A' && keyStr[j] <= 'F' ) Index += keyStr[j]-'A'+10;
				else { LoadError= true; break; }
			if (Index>range || Index<0) 
			{ 
				LoadError=true; 
				break; 
			}
			j++;
		}
		if (keyStr[j] == 0) 
			LoadError=true;;
		if (LoadError) break;
		j++;
		data.encryptionData0[Index]=Cnt;

		l = 0;
		while (1) {
			k = 0;
			while (keyStr[j] != ',' && keyStr[j] != ' ' && keyStr[j] != 0) {
				k *= 16;
				if ( keyStr[j] >= '0' && keyStr[j] <= '9' ) k += keyStr[j]-'0';
				else
					if ( keyStr[j] >= 'A' && keyStr[j] <= 'F' ) k += keyStr[j]-'A'+10;
					else { LoadError= true; break; }
				if (k>data.SizeHomophoneKey) { LoadError=true; break; }
				j++;
			}
			if (LoadError) break;
			l++;
			data.key[Cnt++]=k;
			if (keyStr[j] == 0) 
				break;
			if (keyStr[j] == ' ') 
				break;
			j++;
		}
		data.encryptionData1[Index] = l;
		data.frequency[Index] = (double)l/data.SizeHomophoneKey; // CHECKME
		if (LoadError) break;
	}
}
