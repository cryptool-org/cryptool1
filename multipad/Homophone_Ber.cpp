// Homophone_Ber.cpp: Implementierung der Klasse Homophone_Ber.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Homophone_Ber.h"
#include "time.h"
#include <stdlib.h>
#include "assert.h"
#include "multipad.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Homophone_Ber::Homophone_Ber()
{
	Init_Data();
}

Homophone_Ber::~Homophone_Ber()
{

}

void Homophone_Ber::Make_enc_table()	

	// ordnet jedem plaintext-Zeichen "seine" Anzahl an ciphertext-Zeichen zu und f�llt enc_data,
	// so da� verschl�sselt werden kann

{
	int i,last=0;


	for(i=0;i<range;i++)
	{
		if(freq[i]>0.0)
		{
			enc_data[i][1]=int(floor(range*freq[i]));
// Eingef�gt 24. April 2001 -- Henrik Koy
			if ( (0==enc_data[i][1]) )
			{
				enc_data[i][1]=1;
				do_not_round_me[i]=true;
			}
		}
/*
		else
		{
			enc_data[i][1]=1;
			do_not_round_me[i]=true;
		}
*/
	}

/* 
	if(FALSE==theApp.TextOptions.m_Case)
	{
		for(i='A';i<='Z';i++)
		{
			for(j=0;j<=1;j++)
			{
				enc_data[i][j] += enc_data[i+'a'-'A'][j];
				freq[i]        += freq[i+'a'-'A'];
				freq[i+'a'-'A'] =-1;
			}
		}
	}
*/

	while(range!=Checksum())
	{
		if(Checksum()<range)
		{
			Increase_ciphers();
		}
		else
		{
			Decrease_ciphers();
		}
	}
	assert(range==Checksum());

	for(i=0;i<range;i++)
	{
		if(enc_data[i][1]>0)
		{
			enc_data[i][0]=last;
			last+=enc_data[i][1];
		}
	}
}


int Homophone_Ber::Checksum()

// pr�ft, ob die Summe der ciphertext-Zeichen gleich range ist

{
	int i,sum=0;

	for(i=0;i<range;i++)
	{
		if(enc_data[i][1]>=0)
		{
			sum+=enc_data[i][1];
		}
	}
	return(sum);
}

void Homophone_Ber::Increase_ciphers()

// erh�ht die Anzahl der ciphertext-Zeichen, wenn deren Summe kleiner als range ist

{
	int i,index=0;
	double value=0.01;

	for(i=0;i<range;i++)
	{
		if(freq[i]>0.0&&false==do_not_round_me[i]&&freq[i]*range/enc_data[i][1]>value)
		{
			value=freq[i]*range/enc_data[i][1];
			index=i;
		}
	}
	enc_data[index][1]++;
}

void Homophone_Ber::Decrease_ciphers()

// verringert die Anzahl der ciphertext-Zeichen, wenn deren Summe gr��er als range ist

{
	int i,index=0;
	double value=100;

	for(i=0;i<range;i++)
	{
		if(freq[i]>0.0&&false==do_not_round_me[i]&&freq[i]*range/enc_data[i][1]<value)
		{
			value=freq[i]*range/enc_data[i][1];
			index=i;
		}
	}
	enc_data[index][1]--;   
}

void Homophone_Ber::Generate_key()

// f�llt key mit den Zahlen von 0 bis range in zuf�lliger Reihenfolge auf

{
	int i;

	for(i=0;i<range;i++)
	{
		key[Get_free_position()]=i;
	}
	assert(true==Check_key());
}

int Homophone_Ber::Get_free_position()

// wird von Generate_key() aufgerufen und sucht f�r die Zahlen von 0 bis range einen freien Platz in key

{
	int index,value=0;

	while(-1!=value)
	{
		index=zz.zzgen4()%range;
		value=key[index];
	}
	return(index);
}

int Homophone_Ber::Get_random_number(int number)

// gibt eine Zufallszahl zwischen 0 und (number-1) zur�ck

{
	return(zz.zzgen4()%number);
}

bool Homophone_Ber::Check_key()		

// pr�ft, ob jede Zahl zwischen 0 und range genau einmal in key[] vorhanden ist

{									
	int i,j,sum;

	for(i=0;i<range;i++)
	{
		sum=0;
		for(j=0;j<range;j++)
		{
			if(key[j]==i)
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

void Homophone_Ber::Init_Data()

// setzt die Daten der Klasse auf vern�nftige Eingangswerte

{
	int i,j;

	for(i=0;i<range;i++)
	{
		dec_data[i]=32;
		do_not_round_me[i]=false;
		freq[i]=0.0;
		key[i]=-1;
		for(j=0;j<=1;j++)
		{
			enc_data[i][j]=-1;
		}
	}
}

int Homophone_Ber::Encrypt(int value)

// liefert zu dem ASCII-Wert eines plaintext-Zeichens (value) zuf�llig ein ciphertext-Zeichen zur�ck

{
	if (FALSE == theApp.TextOptions.m_Case && (value >= 'a' && value<='z'))	
	{
		value += 'A'-'a';
	}
	if(enc_data[value][1]>0)
	{
		return(key[enc_data[value][0]+Get_random_number(enc_data[value][1])]);
	}
	return(-1);
}

void Homophone_Ber::Make_dec_table()

// f�llt dec_data, so da� entschl�sselt werden kann

{
	int i;

	for(i=0;i<range;i++)
	{
		dec_data[i]=Get_index(i);
	}
}

int Homophone_Ber::Get_index(int value)

// liefert zu dem ASCII-Wert eines ciphertext-Zeichens dessen Position in key zur�ck

{
	int i,index;

	for(i=0;i<range;i++)
	{
		if(value==key[i])
		{
			index=i;
		}
	}
	for(i=range-1;i>=0;i--)
	{
		if(enc_data[i][1]>0&&enc_data[i][0]<=index)
		{
			return(i);
		}
	}
	return(0);
}

const char* Homophone_Ber::GetKeyStr()
{
	char *keyStr = new char[6*range]; // ACHTUNG NOCH ABZU�NDERN
	long k, l, i, j = 0;
	for ( i=0; i<range; i++ )
	{
		if(enc_data[i][1]>0)
		{
			char hexStr[10];
			sprintf(hexStr, "%X", i);
			for ( k=0; hexStr[k]!=0; k) keyStr[j++] = hexStr[k++];
			keyStr[j++] = ':';
			for ( l=0; l<enc_data[i][1]; l++)
			{
				sprintf(hexStr, "%X", key[enc_data[i][0]+l]);
				for ( k=0; hexStr[k]!=0; k) keyStr[j++] = hexStr[k++];
				if (l+1<enc_data[i][1]) keyStr[j++] = ',';
			}
			keyStr[j++] = ' ';
		}
	}
	keyStr[j] = 0;
	return keyStr;
}

void Homophone_Ber::load_enc_table(const char *keyStr)
{
	Init_Data();
	long k, l, i, j = 0, Cnt = 0, Index;
	bool LoadError = false;
	while (keyStr[j] != 0)
	{
		Index = 0;
		while (keyStr[j] == ' ') j++;
		while (keyStr[j] != ':') {
			Index *= 16;
			if ( keyStr[j] >= '0' && keyStr[j] <= '9' ) Index += keyStr[j]-'0';
			else
				if ( keyStr[j] >= 'A' && keyStr[j] <= 'F' ) Index += keyStr[j]-'A'+10;
				else { LoadError= true; break; }
			if (Index>range) { LoadError=true; break; }
			j++;
		}
		if (keyStr[j] == 0) 
			LoadError=true;;
		if (LoadError) break;
		j++;
		enc_data[Index][0]=Cnt;
		l = 0;
		while (1) {
			k = 0;
			while (keyStr[j] != ',' && keyStr[j] != ' ' && keyStr[j] != 0) {
				k *= 16;
				if ( keyStr[j] >= '0' && keyStr[j] <= '9' ) k += keyStr[j]-'0';
				else
					if ( keyStr[j] >= 'A' && keyStr[j] <= 'F' ) k += keyStr[j]-'A'+10;
					else { LoadError= true; break; }
				if (k>range) { LoadError=true; break; }
				j++;
			}
			if (LoadError) break;
			l++;
			key[Cnt++]=k;
			if (keyStr[j] == 0) 
				break;
			if (keyStr[j] == ' ') 
				break;
			j++;
		}
		enc_data[Index][1] = l;
		if (LoadError) break;
	}
}
