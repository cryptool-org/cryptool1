// Homophone.cpp: Implementierung der Klasse Homophone.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "multipad.h"
#include "fileutil.h"
#include "secure.h"
#include "ChrTools.h"
#include <iostream.h>
#include "Math.h"
#include "assert.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "s_prng.h"
#include "Homophon.h"


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Homophone::Homophone(FILE *infp,FILE *outfp)
{
	int i,len;

	text.SetConverter(AppConv);
	for(i=0;i<alphsize;i++)
		do_not_round_me[i]=false;

	fseek(infp,0,SEEK_END);
	fsize=ftell(infp);
	fseek(infp,0,SEEK_SET);
	inbuf=(char *)malloc(fsize);
	if(!inbuf)
		return;
	out=outfp;
	fread(inbuf,1,fsize,infp);
	text.ReadString(inbuf,fsize);
	len = text.GetSize();

	NGram distr(text);
	
	alphsize=theApp.TextOptions.m_alphabet.GetLength();
	alphabet=theApp.TextOptions.m_alphabet.GetBuffer(0);

	for(i=0;i<alphsize;i++)
		float_value[i]=distr[i]*256;

	make_number();
	while(checksum()!=256)
	{
		if(checksum()<256)
			increase_number();
		else
			decrease_number();
	}
}

Homophone::~Homophone()
{
	if(inbuf)
		free(inbuf);
}

void Homophone::SetOutFp(FILE *f)
{
	out=f;
}

void Homophone::SetInput(char *in)
{
	int temp[256],i,j,k;
	char pas[256],t[256];

	i=0;
	j=0;
	while(in[j]!=0)
	{
		bool run;
		run=true;
		for(k=0;k<i;k++)
		{
			if(in[j]==t[k])
				run=false;
		}
		if(run)
			t[i++]=in[j];
		j++;
	}
	for(j=0;j<alphsize;j++)
	{
		bool run;
		run=true;
		for(k=0;k<i;k++)
		{
			if(t[k]==alphabet[j])
				run=false;
		}
		if(run)
			t[i++]=alphabet[j];
	}
	t[i]=0;
	memcpy(temp,number,256*sizeof(int));
	j=0;
	while(j<256)
	{
		for(k=0;k<alphsize;k++)
		{
			if(temp[k]>0)
			{
				temp[k]--;
				pas[j++]=alphabet[k];
			}
		}
	}
	for(j=0;j<alphsize;j++)
	{
		k=0;
		while(t[j]!=alphabet[k])
			k++;
		k=(3*k+2*alphsize-j)%256;
		for(i=0;i<256-k;i++)
			passphrase[255-k-i]=pas[i+k];
		for(i=256-k;i<256;i++)
			passphrase[i]=pas[i+k-256];
		strncpy(pas,passphrase,256);
	}
	passphrase[256]=0;
}

char *Homophone::GetPassphrase()
{
	return passphrase;
}

void Homophone::SetPassphrase(char *a)
{
	strcpy(passphrase,a);
}

int Homophone::checksum()		 // prüft, ob die Summe 100 ist
{
	int i,sum=0;
	for(i=0;i<alphsize;i++)
		sum+=number[i];
	return sum;
}

void Homophone::decrease_number() // wenn durch Rundung>100
{
	int i,index=0;
	double object=256;
	for(i=0;i<alphsize;i++)
		if(float_value[i]<object&&number[i]>1&&do_not_round_me[i]==false)
		{
			object=float_value[i];
			index=i;
		}
	number[index]--;
	do_not_round_me[index]=true;
}

void Homophone::increase_number() // wenn durch Rundung<100
{
	int i,index=0;
	double object=0;
	for(i=0;i<alphsize;i++)
		if(float_value[i]>object&&do_not_round_me[i]==false)
		{
			object=float_value[i];
			index=i;
		}
	number[index]++;
	do_not_round_me[index]=true;
}

void Homophone::make_number()  // erstellt ganze Zahlen aus Histogramm
{
	int i;
	for(i=0;i<alphsize;i++)
	{
		if(float_value[i]==0.0)
			number[i]=0;
		else
		{
			number[i]=int(round(float_value[i]));
			if(number[i]==0)
				number[i]=1;
			float_value[i]-=number[i];
		}
	}
}

void Homophone::print_number() // gibt die ganzen Zahlen aus
{
	int i;
	for(i=0;i<=25;i++)
		cout<<number[i]<<" ";
	cout<<endl<<endl;
}

double Homophone::round(double f) // erzwungen, weil kein round bei MFC vorhanden...
{
	if(f-floor(f)<0.5)
		return floor(f);
	return ceil(f);
}

void Homophone::do_it()           // wird als einzige Funktion von "homophone.main" aufgerufen
{
	//randomize_values();
	assert(checksum()==100);
	int i;
	for(i=0;i<=25;i++)
		assert(number[i]>=0);
	replace_letter_by_number();
	encrypt_text();
	print_crypt();
	print_encr_text();
}

void Homophone::replace_letter_by_number() // erzeugt zufällige Zahlen, mit denen ein plaintext-Buchstabe verschlüsselt werden kann
{
	srand((unsigned)time(NULL));
	int i,j;
	for(i=0;i<=25;i++)
	{
		for(j=0;j<number[i];j++)
		{
			crypt[i][j]=200;
			while(crypt[i][j]>=100||value_already_used(crypt[i][j])==true)
				crypt[i][j]=rand();
		}
	}
}

void Homophone::print_crypt() // gibt die Zahlen aus, die für A-Z stehen
{
	int i,j;
	for(i=0;i<=0;i++)
	{
		for(j=0;j<=99;j++)
		{
			if(crypt[20][j]>=0)
				cout<<crypt[20][j]<<" ";
		}
	}
	cout<<endl<<endl;
}

bool Homophone::value_already_used(int value) // prüft, ob eine Zahl nicht schon verwendet wird
{
	int i,j,counter=0;
	for(i=0;i<=25;i++)
	{
		for(j=0;j<=99;j++)
		{
			if(crypt[i][j]==value)
				counter++;
		}
	}
	if(counter>1)
		return true;
	return false;
}

void Homophone::randomize_values()  // simuliert ein Histogramm
{
	srand((unsigned)time(NULL));
	int i;
	double sum=0,product;
	for(i=0;i<=25;i++)
	{
		float_value[i]=double(rand())/100;
		sum+=float_value[i];
	}
	product=100/sum;
	for(i=0;i<=25;i++)
		float_value[i]*=product;
}

void Homophone::encrypt_text()  // verschlüsselt text nach encr_text
{
	srand((unsigned)time(NULL));
	int i,j,len;
	int value;

	len=text.GetSize();
	for(i=0;i<len;i++)
	{
		value=rand()&0xff;
		while(value>=number[text[i]])
			value=rand()&0xff;
		value++;
		j=0;
		while(value>0)
		{
			if(passphrase[j++]==alphabet[text[i]])
				value--;
		}
		j--;
		fputc(j,out);
	}
}

void Homophone::print_encr_text() // gibt verschlüsselten Text(also Zahlen) aus
{
	int i;
	for(i=0;i<=80;i++)
		if(encr_text[i]>=0)
			cout<<encr_text[i]<<" ";
}

void Homophone::decrypt_text()
{
	int i;

	for(i=0;i<fsize;i++)
		fputc(passphrase[(unsigned char)inbuf[i]],out);
}





