// Homophone_Ber.cpp: Implementierung der Klasse Homophone_Ber.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Homophone_Ber.h"
#include "time.h"
#include <stdlib.h>

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
	for(int i=0;i<=25;i++)
	{
		Set_freq(i,double(range)/26);
		Set_cipher(i,-1);
		Set_do_not_round_me(i,false);
	}
}

Homophone_Ber::~Homophone_Ber()
{

}

int Homophone_Ber::Get_cipher(int index)
{
	return(ciphers[index]);
}

void Homophone_Ber::Calculate_ciphers()
{
	int i;
	for(i=0;i<=25;i++)
	{
		if(0.0==Get_freq(i))
		{
			Set_cipher(i,0);
		}
		else
		{
			Set_cipher(i,round(Get_freq(i)));
			if(0==Get_cipher(i))
			{
				Set_cipher(i,1);
			}
			Set_freq(i,Get_freq(i)-Get_cipher(i));
		}
	}	

	while(range!=checksum())
	{
		if(checksum()<range)
		{
			increase_ciphers();
		}
		else
		{
			decrease_ciphers();
		}
	}
}

void Homophone_Ber::Set_freq(int index, double value)
{
	freq[index]=value;
}

void Homophone_Ber::Set_cipher(int index, int value)
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

int Homophone_Ber::checksum()
{
	int sum=0;
	for(int i=0;i<=25;i++)
	{
		sum+=Get_cipher(i);
	}
	return(sum);
}

void Homophone_Ber::increase_ciphers()
{
	int i,index=0;
	double object=0;
	for(i=0;i<=25;i++)
	{
		if(Get_freq(i)>object&&false==Get_do_not_round_me(i))
		{
			object=Get_freq(i);
			index=i;
		}
	}
	Set_cipher(index,Get_cipher(index)+1);
	do_not_round_me[index]=true;
}

void Homophone_Ber::decrease_ciphers()
{
	int i,index=0;
	double object=100;
	for(i=0;i<=25;i++)
	{
		if(Get_freq(i)<object&&Get_cipher(i)>1&&false==Get_do_not_round_me(i))
		{
			object=Get_freq(i);
			index=i;
		}
	}
	Set_cipher(index,Get_cipher(index)-1);
	do_not_round_me[index]=true;
}

void Homophone_Ber::Set_do_not_round_me(int index, bool value)
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

void Homophone_Ber::Set_key(int index, int value)
{
	key[index]=value;
}

void Homophone_Ber::Generate_key()
{
	for(int i=0;i<=255;i++)
	{
		Set_key(i,-1);
	}

	for(i=0;i<=255;i++)
	{
		Set_key(Get_free_position(),i);
	}
}

int Homophone_Ber::Get_free_position()
{
	int index,value=0;
	while(-1!=value)
	{
		index=zz.zzgen4();
		value=Get_key(index);
	}
	return(index);
}
