// Homophone_Ber.cpp: Implementierung der Klasse Homophone_Ber.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Homophone_Ber.h"
#include "time.h"
#include <stdlib.h>
#include "assert.h"

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

int Homophone_Ber::Get_cipher(int index)
{
	return(ciphers[index]);
}

void Homophone_Ber::Calculate_ciphers(int chars)
{
	int i;

	for(i=0;i<chars;i++)
	{
		Set_cipher(i,int(floor(Get_freq(i))));
		if(0==Get_cipher(i))
		{
			Set_cipher(i,1);
			Set_do_not_round_me(i,true);
		}
	}

	while(range!=checksum(chars))
	{
		if(checksum(chars)<range)
		{
			increase_ciphers(chars);
		}
		else
		{
			decrease_ciphers(chars);
		}
	}
	assert(range==checksum(chars));
}

void Homophone_Ber::Set_freq(int index,double value)
{
	freq[index]=value*range;
}

void Homophone_Ber::Set_cipher(int index,int value)
{
	ciphers[index]=value;
}

double Homophone_Ber::Get_freq(int index)
{
	return(freq[index]);
}

int Homophone_Ber::round(double value)
{
	if(value-floor(value)<0.5)
	{
		return(int(floor(value)));
	}
	return(int(ceil(value)));
}

int Homophone_Ber::checksum(int chars)
{
	int i,sum=0;

	for(i=0;i<chars;i++)
	{
		sum+=Get_cipher(i);
	}
	return(sum);
}

void Homophone_Ber::increase_ciphers(int chars)
{
	int i,index=0;
	double value=0.01;

	for(i=0;i<chars;i++)
	{
		if(false==Get_do_not_round_me(i)&&Get_freq(i)/Get_cipher(i)>value)
		{
			value=Get_freq(i)/Get_cipher(i);
			index=i;
		}
	}
	Set_cipher(index,Get_cipher(index)+1);
}

void Homophone_Ber::decrease_ciphers(int chars)
{
	int i,index=0;
	double value=100;

	for(i=0;i<chars;i++)
	{
		if(false==Get_do_not_round_me(i)&&Get_freq(i)/Get_cipher(i)<value)
		{
			value=Get_freq(i)/Get_cipher(i);
			index=i;
		}
	}
	Set_cipher(index,Get_cipher(index)-1);
}

void Homophone_Ber::Set_do_not_round_me(int index,bool value)
{
	do_not_round_me[index]=value;
}

bool Homophone_Ber::Get_do_not_round_me(int index)
{
	return(do_not_round_me[index]);
}

int Homophone_Ber::Get_key(int index)
{
	return(key[index]);
}

void Homophone_Ber::Set_key(int index,int value)
{
	key[index]=value;
}

void Homophone_Ber::Generate_key()
{
	int i;

	for(i=0;i<range;i++)
	{
		Set_key(i,-1);
	}

	for(i=0;i<range;i++)
	{
		Set_key(i/*Get_free_position()*/,i);
	}
	assert(true==Check_key());
}

int Homophone_Ber::Get_free_position()
{
	int index,value=0;

	while(-1!=value)
	{
		index=zz.zzgen4()%range;
		value=Get_key(index);
	}
	return(index);
}

int Homophone_Ber::Get_random_number(int index)
{
	int i,sum=0,value;

	for(i=0;i<index;i++)
	{
		sum+=Get_cipher(i);
	}
	value=Get_key(sum+(zz.zzgen4()%Get_cipher(index)));
	assert(0<=value&&value<range);
	return(value);
}

bool Homophone_Ber::Check_key()		// prüft, ob jede Zahl zwischen 0 und range 
{									// genau einmal in key[] vorhanden ist
	int i,j,sum;
	for(i=0;i<range;i++)
	{
		sum=0;
		for(j=0;j<range;j++)
		{
			if(Get_key(j)==i)
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
{
	int i;

	for(i=0;i<range;i++)
	{
		Set_cipher(i,-1);
		Set_do_not_round_me(i,false);
		Set_freq(i,0.0);
		Set_key(i,-1);
	}
}
