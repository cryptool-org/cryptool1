// RSA_Berechnungen.cpp: Implementierung der Klasse RSA_Berechnungen.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "RSA_Berechnungen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

RSA_Berechnungen::RSA_Berechnungen() : precision3(25)
{
	s=new char[100];
}

RSA_Berechnungen::~RSA_Berechnungen()
{

}
	

Big RSA_Berechnungen::extended_euclidian_algorithm(Big n, Big e)
{
	Big ausgabe;
	if (e==0)
	{
	
		ausgabe=-1;
		return ausgabe;// 0 besitzt keine Inverse modulo n
	}

	Big n0=n;
	Big e0=e;
	Big t0=0;
	Big t=1;
	Big q= (n0 / e0);
	Big r=n0-q*e0;
	while (r>0)
	{
		Big temp= t0 -q*t;
		if (temp>=0)
		{
			temp=temp%n;
		}
		if (temp<0) 
		{
			temp = n -((-temp) % n);
		}
		t0=t;
		t=temp;
		n0=e0;
		e0=r;
		q=n0/e0;
		r=n0 - q*e0;
	}
	if (e0!=1)
	{// e hat keine Inverse
	
		ausgabe=-1;
		return ausgabe;
	}
	ausgabe=t%n;
	return ausgabe;
}

Big RSA_Berechnungen::square_und_multiply(Big x, Big b, Big n)
{//BERECHNET X^B MOD N
	long i;
	Big z=1;
	Big *b_i;
	
	//b_i=(Big *) calloc(1700,sizeof(Big)); 
	b_i = new Big[1700];	
	//In b_i[0] sollte die Länge des Vektors gespeichert werden. 

	long temp=Bitlaenge(b,b_i);
	
	for (i=temp;i>=0;i--)
	{
		z =(z*z)%n;
		if (b_i[i]==1)
		{
			z=(z*x)%n;
		}
	}
	//b_i[0]=temp-1;
	return z;

}

long RSA_Berechnungen::Bitlaenge(Big x,Big *bi)
{
	Big temp=0;
		
	if (x==0)
	{
		bi[0]=temp;
		return 0;
	//	bi[1]=temp;
	}
	if (x<0) 
	{
		x=-x;
		return 0; //noch bearbeiten
	}
	
	//Vorsicht : es fehlte noch die binäre Dartstellung von negative Zahlen.
	long l=0;
	//bi[0]=0;
	//bi[1]=1;
	while (x!=1)
	{
		bi[l]=x%2;
		x=x/2;
		l=l+1;
	}
	//bi[0]=temp+1;
	bi[l]=temp+1;
	return l;

}

Big RSA_Berechnungen::random_with_limits(Big upper)
{
	Big ausgabe;
	ausgabe=1;
	// erzeugt eine Zufallszahl rand_val, wobei gilt: 1< rand_val < upper
	irand(123456789); // Einstellbar!
	ausgabe=rand(upper);
	return ausgabe;

}


Big RSA_Berechnungen::erzeuge_oeffentliche_Schluessel_e(Big phi_pq)
{
	Big eingabe;
	eingabe=phi_pq;
	Big z;
	CString schwer;
	schwer= konvertiere_Big_CString(eingabe);
	Big ausgabe;
	if (eingabe >2)
	{
		z=random_with_limits(eingabe);
		schwer= konvertiere_Big_CString(z);
		while (1!=ggT(z,eingabe))
		{
			z=random_with_limits(eingabe);
			schwer= konvertiere_Big_CString(z);
		}
		ausgabe=z;
		return ausgabe;
	}
	else 
	{
		ausgabe=-1;
		return ausgabe; //keine solche Zahl existiert!		
	}
}


Big RSA_Berechnungen::ggT(Big a, Big b)
{
	Big temp;

	if (a==0) return b;
	else if (b==0) return a;
	else if (a==b) return a;
	else if (a<b) 
	{
		while (b!=0)
		{
			temp=a;
			a=b;
			b=temp%b;
		}
		return a;
	}
	else
	{
		while (a!=0)
		{
			temp=b;
			b=a;
			a=temp%a;
		}
		return b;
	}
}


long RSA_Berechnungen::RSA_BlockLaengeBerechnung(Big x, long a)
{
	//x ist der RSA-Modul x=p*q; a ist die Anzahl der benutzten Zeichen.
	if (x==0)
	{
		//???
	}
	if (x<0) 
	{
		x=-x;
	}
	
	//Vorsicht : es fehlte noch die a-adische Dartstellung von negative Zahlen.
	long l=1;

//	Big a_big;
//	lgconv(a,a_big);

	while (x>a)
	{
		x=x/a;
		l=l+1;
	}

	return (l);
}

Big RSA_Berechnungen::potenz(Big x, Big n)
{
	Big z=1;

	if (x==0 && n==0) return z;
	if (x==0 && n!=0) return (z-1);
	if (x!=0 && n==0) return z;
	do 
	{
		z=z*x;
		n=n-1;
	}
	while (n!=0);
	return z;
}

void RSA_Berechnungen::encrypt_block(Big *Block, long blocklaenge,long anzahl_buchstaben, Big ausgabe,Big n, Big e)
{
	// n =pq ist das RSA-Modul
	// e ist RSA öffentliche Schluessel
	long i;
	long j;
	ausgabe=0;
	Big anzahl_buchstaben_big;
//	lgconv(anzahl_buchstaben, anzahl_buchstaben_big);
	// Block als Zahl (ausgabe) < RSA-Modul darstellen:
	for (i=blocklaenge-1;i>=0;i--)
	{
		ausgabe=ausgabe+Block[i]*potenz(anzahl_buchstaben,blocklaenge-1-i);
	}

	char ausgabe_char[100];
	ausgabe_char<<ausgabe;
	//Ergebnis-Zahl verschluesseln: ausgabe^e mod n=ausgabe
	ausgabe=square_und_multiply(ausgabe, e,n);
	
	ausgabe_char<<ausgabe;
	// Ergebnis-Zahl ausgabe wieder als Block darstellen
	i=blocklaenge-1;
	Big temp;
	do
	{
		temp=ausgabe;
		Block[i]=ausgabe%anzahl_buchstaben;
		ausgabe_char<<Block[i];
		ausgabe=ausgabe/anzahl_buchstaben;
		i=i-1;
	}while (ausgabe>=anzahl_buchstaben);
	if (i!=0)
	{
		Block[i]=ausgabe;
		ausgabe_char<<Block[i];
		for (j=i-1;j>=0;j--)
		{
			Block[j]=0;
			ausgabe_char<<Block[i];
		}
	}
	Block[0]=ausgabe;
	ausgabe_char<<Block[0];
}




void eval_product(Big &oldn, Big &n, char op)
{
	switch (op)
        {
        case TIMES:
                n*=oldn; 
                break;
        case '/':
                n=oldn/n;
                break;
        case '%':
                n=oldn%n;
        }
}


void RSA_Berechnungen::eval_power(Big &oldn, Big &n, char op)
{
	if (op) n=pow(oldn,toint(n));    // power(oldn,size(n),n,n);
}

void RSA_Berechnungen::eval_sum(Big &oldn, Big &n, char op)
{
	switch (op)
        {
        case '+':
                n+=oldn;
                break;
        case '-':
                n=oldn-n;
        }
}

bool RSA_Berechnungen::eval()
{
	mip3=&precision3;
	Big oldn[3];
        Big n;
        int i;
        char oldop[3];
        char op;
        char minus;
        for (i=0;i<3;i++)
        {
            oldop[i]=0;
        }
LOOP:
        while (*s==' ')
			s++;
        if (*s=='-')    /* Unary minus */
			{
			s++;
			minus=1;
			}
        else
	        minus=0;
        while (*s==' ')
		    s++;
        if (*s=='(' || *s=='[' || *s=='{')    /* Number is subexpression */
			{
			s++;
			eval ();
			n=t;
			}
        else            /* Number is decimal value */
        {
		
        for (i=0;s[i]>='0' && s[i]<='9';i++)
               ;
			if (!i)         /* No digits found */
			{
//					Error - invalid number
//					LoadString(AfxGetInstanceHandle(),IDS_STRING37101,pc_str,STR_LAENGE_STRING_TABLE);
//					sprintf(line,pc_str);
//					AfxMessageBox(line);
					return(false);
			}
			op=s[i];
			s[i]=0;
			n=s;

			s+=i;
			*s=op;
		}
        if (minus) n=-n;
			char z[100];
			mip3->IOBASE=10;
			z << n;
        do
			op=*s++;
			while (op==' ');
        if (op==0 || op==')' || op==']' || op=='}')
			{
			eval_power (oldn[2],n,oldop[2]);
			eval_product (oldn[1],n,oldop[1]);
			eval_sum (oldn[0],n,oldop[0]);
			t=n;
			char z[100];
			mip3->IOBASE=10;
			z << t;
			return(true);
			}
        else
        {
			if (op==RAISE)
				{
						eval_power (oldn[2],n,oldop[2]);
						oldn[2]=n;
						oldop[2]=RAISE;
				}
			else
			{
					if (op==TIMES || op=='/' || op=='%')
					{
					eval_power (oldn[2],n,oldop[2]);
					oldop[2]=0;
					eval_product (oldn[1],n,oldop[1]);
					oldn[1]=n;
					oldop[1]=op;
					}
					else
						{
						if (op=='+' || op=='-')
							{
									eval_power (oldn[2],n,oldop[2]);
									oldop[2]=0;
									eval_product (oldn[1],n,oldop[1]);
									oldop[1]=0;
									eval_sum (oldn[0],n,oldop[0]);
									oldn[0]=n;
									oldop[0]=op;
							}
						else    /* Error - invalid operator */
							{
//									Error - invalid operator
//									LoadString(AfxGetInstanceHandle(),IDS_STRING37109,pc_str,STR_LAENGE_STRING_TABLE);
//									sprintf(line,pc_str);
//									AfxMessageBox(line);
									return(false);
							}
						}
			}
		}
	goto LOOP;
}

Big RSA_Berechnungen::konvertiere_CString_Big(CString Eingabe)
{

//	mip3=&precision3;
	Big ausgabe;
	s=Eingabe.GetBuffer(500);

	//t=0;
	//eval();
	//if (false==eval()) 
	//	return -1;
	ausgabe=t;
	//mip3->IOBASE=10
	ausgabe=s;
   
	return ausgabe;
}

CString RSA_Berechnungen::konvertiere_Big_CString(Big Eingabe)
{
	//mip3=&precision3;
	CString ausgabe;
	
	//mip3->IOBASE=10;
	
	ausgabe.GetBuffer(500) << Eingabe;
	
	return ausgabe;
}












