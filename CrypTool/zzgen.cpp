/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/


// zzgen.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "zzgen.h"
#include "FileTools.h"
#include "s_prng.h"



/*
Der Zufallsgenerator aus der SecudeLib.
Einzelne Bits weden zu einem Byte zusammengesetzt.
*/
unsigned char zzgen::zzgen4()
{
	unsigned char o;
	int i;

	o=0;
	for(i=0;i<8;i++)
		o|=(_rand_bit())<<i;

	return o;
}

/*
Blum Shub Generator seed^2 mod n.
Eigentlich muss für n ein RSA Modul benutzt werden.
*/
unsigned char zzgen::zzgen3(unsigned long *seed,unsigned long n)
{
	unsigned long i,l;
	int j;

	i=*seed;
	l=0;
	for(j=0;j<32;j++)
	{
		if(*seed&1<<j)
			l=(l+i)%n;
		i<<=1;
		i%=n;
	}
	*seed=i;

	return (unsigned char)(i&0xff);
}

/*
generiert ein Zufallsbyte durch (seed*a)+b mod c davon werden die unteren 8 Bit benutzt.
Die Parameter a,b,c sollten Primzahlen sein! 
*/
unsigned char zzgen::zzgen2(unsigned long *seed,unsigned long a,unsigned long b,unsigned long c)
{
	*seed=((*seed)*a+b)%c;

	return (unsigned char)((*seed)&0xff);
}

/*
Generiert ein Zufallsbyte durch Bitverschiebung des seeds nach links.
Das erste herausgeschobene Bit ist das LSB des Zufallsbytes. Das LSB des 
seeds wird mit mask aus dem alten seed generiert. zyk gibt die Anzahl der 
vom seed beutzten Bits fest (1..32)
*/
unsigned char zzgen::zzgen1(unsigned long *seed,unsigned long mask,int zyk)
{
	unsigned long i;
	unsigned char c;
	int j,k;
	bool r;

	c=0;
	for(j=0;j<8;j++)
	{
		c|=((*seed&(1<<zyk))?1:0)<<j;
		i=*seed&mask;
		r=0;
		for(k=0;k<32;k++)
			r^=(i&(1<<k))?1:0;
		*seed<<=1;
		*seed|=r?1:0;
	}

	return c;
}

unsigned long zzgen::multmodn(unsigned long a, unsigned long b,unsigned long n)
{
	unsigned long s,t,u;

	if(b<a)
	{
		t=b;
		u=a;
	}
	else
	{
		t=a;
		u=b;
	}
	s=0;
	while(t)
	{
		if(t&1)
			s=(s+u)%n;
		u=(u+u)%n;
		t>>=1;
	}
	return s;
}

unsigned long zzgen::powermod(unsigned long a,unsigned long x,unsigned long n)
{
	unsigned long s,t,u;
	
	s=1;
	t=a;
	u=x;
	
	while(u)
	{
		if(u&1)
			s=multmodn(s,t,n);
		u>>=1;
		t=multmodn(t,t,n);
	}
	return(s);
}


/*
Stellt über ein Sieb fest, ob p eine Primzahl ist.
Falls fp vorhanden ist, werden die einige davon nach fp geschrieben.
Falls last nicht Null wird dort die grösste Primzahl kleiner gleich 
p abgelegt.
*/
bool zzgen::isprime(unsigned int p,FILE* fp=0,unsigned int *last=NULL)
{
	unsigned int i,j,sqi,pro;
	char *buf;
	unsigned int n;

	if(fp)
		theApp.fs.Display("test");
	theApp.fs.Set(0);
	pro=0;

	if(!fp&&!last)
	{
		if (p<2)
			return false;
		sqi=(int)sqrt((double)p)+1;
	}
	else
		sqi=p;
	n=(sqi>>3)+1;
	if(n>primlen)
	{
		buf=(char *)calloc(n+2,1);
		if(primlen!=0)
		{
			memcpy(buf,prim,primlen-1);
			free(prim);
		}
		j=2;
		for(i=j;i<((primlen==0?1:primlen)-1)<<3;i++)
		{
			if(!(buf[i>>3]&(1<<(i&0x07))))
			{
				if(last)
					*last=i;
				if(fp&&i>sqi-100000)
					fprintf(fp,"%d\n",i);
				j=i;
				while(j<(primlen-1)<<3)
					j+=i;

				while(j<(n<<3))
				{
					buf[j>>3]|=(1<<(j&0x07));
					j+=i;
				}
				j=i+1;
			}
		}
		i=j;
		while(i<sqi)
		{
			if(i*100/sqi>pro)
			{
				theApp.fs.Set(pro);
				pro++;
				Sleep(0);
			}
			if(!(buf[i>>3]&(1<<(i&0x07))))
			{
				if(last)
					*last=i;
				if(theApp.fs.m_canceled)
				{
					free(buf);
					theApp.fs.cancel();
					return false;
				}
				j=2*i;
				while(j<(n<<3))
				{
					buf[j>>3]|=(1<<(j&0x07));
					j+=i;
				}
				if(fp&&i+100000>sqi)
					fprintf(fp,"%d\n",i);
			}
			i++;
		}
		prim=buf;
		primlen=n;
		if(last)
		{
			if(!(prim[sqi>>3]&(1<<(sqi&0x07))))
				*last=sqi;

		}
	}
	else
	{
		if(fp)
		{
			for(i=max(2,(int)p-100000);i<p;i++)
			{
				if(!(prim[i>>3]&(1<<(i&0x07))))
					fprintf(fp,"%d\n",i);
			}
		}
		if(last)
		{
			i=p;
			while(prim[i>>3]&(1<<(i&0x07)))
				i--;
			*last=i;
		}
	}
	theApp.fs.cancel();
	Sleep(100);
	if(!(prim[p>>3]&(1<<(p&0x07))))
		return true;
	else
		return false;
}

unsigned long zzgen::getrnd(unsigned long i)
{
	unsigned long x;
	int j,k;
	
	k=31;
	while((i&(1<<k))==0)
		k--;
	do
	{
		x=0;
		for(j=0;j<=k;j++)
			x|=_rand_bit()<<(j);
	}
	while(x>=i||x==0);

	return x;
}

unsigned long zzgen::ggt(unsigned long x,unsigned long y)
{
	unsigned long g;

	g=y;
	while (x>0)
	{
		g=x;
		x=y%x;
		y=g;
	}
	return g;
}

long zzgen::jacobi(long a,long n)
{/*
	unsigned long g;
	
	if (a>=b)
		a%=b;// Regel 4 
	if (a==0)
		return 0;        // Definition 2 
	if (a==1)
		return 1;  // Regel 1 
	
	if (a<0)
	{
		if (((b-1)/2)%2 == 0)
			return jacobi(-a,b);
	}
	else
		return -jacobi(-a,b);
		
	if (a%2==0)                    // a ist gerade 
	{
		if (((b*b-1)/8)%2==0)
			return jacobi(a/2,b);
	}
	else
		return -jacobi(a/2,b);// Nach den Regeln 3 und 2 
 
	
	g=ggt(a,b);
			
	if (g==a)                    // a geht in b auf 
		return 0;                    // nach Regel 5 
	else
	{
		if (g!=1)
			return jacobi(g,b)*jacobi(a/g,b);     // nach Regel 2 
		else
		{
			if ((((a-1)*b-1)/4)%2==0)
				return jacobi(b,a);                   // nach Regel 6a 
			else
				return -jacobi(b,a);                  // nach Regel 6b 
		}
	}*/
	long a1,e,n1,s;

	if(0==a)
	{
		return(0);
	}
	if(1==a)
	{
		return(1);
	}
	for(e=0,a1=a;a1%2==0;e++)
	{
		a1/=2;
	}
	if(0==e%2)
	{
		s=1;
	}
	else
	{
		if((1==n%8)||(7==n%8))
		{
			s=1;
		}
		else
		{
			s=-1;
		}
	}
	if((3==n%4)&&(3==a1%4))
	{
		s=-s;
	}
	n1=n%a1;
	if(1==a1)
	{
		return(s);
	}
	return(s*jacobi(n1,a1));
}

bool zzgen::isprimefast (unsigned long p)
{
	int i,t;
	unsigned long a,j,jac;
	
	if(p==2||p==3)
		return true;
	if((p&1)==0)
		return false;
	t=100;
	/* Die Schleife wird t=i - mal wiederholt */
	for (i=t; i>=0; i--)
	{
		/* a ist eine Zufallszahl kleiner p */
		a=getrnd(p);
		
		if (ggt(a,p)!=1)
			return false;
		j=powermod(a,(p-1)/2,p);
		
		/* Das Jacobi-Symbol von a und p wird berechnet */
		jac=(unsigned long)jacobi((long)a,(long)p);
		
		/* Wenn j ungleich jac ist p definitiv nicht prim */
		if (j!=jac)
			return false;
	}
	/* p hat alle Testdurchläuufe bestanden 
	und ist wahrscheinlich prim */
	return true;
}

bool zzgen::isprimefast2 (unsigned long p)
{
	unsigned long k,y,b,m,j,z,sich;
	unsigned long a[10001];
	bool run;
	
	if(p==2||p==3)
		return true;
	if((p&1)==0)
		return false;
	b=0;
	m=p-1;
	while ((m&1)==0)
	{
		m>>=1;
		b++;
	}

	sich=min((unsigned long)10001,(p-1)/2);
	for (k=0;k<sich;k++)
	{
		a[k]=getrnd(p-2);
		y=0;
		while (y<k)
		{
			if (a[k]==a[y]) //Gibt's die Zahl schon?
			{
				a[k]=getrnd(p-2);  //Erzeuge neue Zahl
				y=0; //Beginne Vergleich von vorne
			} else
				y++; //Setze Vergleich fort
		}
		
		//Schritt 2
		j=0;
		z=powermod(a[k],m,p);
		
		//Schritt 3
		if (z==1 || z==p-1)
			continue;
		
		//Schritt 4
		run=true;
		while(run)
		{
			if (j>0 && z==1)
				return false;
			
			//Schritt 5
			j++;
			if (j<b && z!=p-1)
			{
				z=powermod(z,2,p);
				run=true;
			}
			else
				run=false;
		}
		
		//Schritt 6
		if (j==b && z!=p-1)
			return false;
	}
	return true;
}

