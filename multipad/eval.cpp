// eval.cpp: Implementierung der Klasse eval.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "eval.h"
#include "multipad.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

static char *s;
static Big  temp;


BOOL evaluateFormula::eval( Big& value, const char * Str )
{
    s = (char*)Str;
	if ( eval() ) {
		value = temp;
		return TRUE;
	}
	value = 0;
	return FALSE;
}

void evaluateFormula::eval_power(Big &oldn, Big &n, char op)
{
	if (op) n=pow(oldn,toint(n));    // power(oldn,size(n),n,n);
}

void evaluateFormula::eval_sum(Big &oldn, Big &n, char op)
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

void evaluateFormula::eval_product(Big &oldn, Big &n, char op)
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

BOOL evaluateFormula::eval()
{
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
		n=temp;
		}
    else            /* Number is decimal value */
    {
	
    for (i=0;s[i]>='0' && s[i]<='9';i++)
           ;
		if (!i)         /* No digits found */
		{
//				Error - invalid number
				char line[256];
				LoadString(AfxGetInstanceHandle(),IDS_STRING37101,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
				return(false);
		}
		op=s[i];
		s[i]=0;
		n=s;

		s+=i;
		*s=op;
	}
    if (minus) n=-n;
    do
		op=*s++;
		while (op==' ');
    if (op==0 || op==')' || op==']' || op=='}')
		{
		eval_power (oldn[2],n,oldop[2]);
		eval_product (oldn[1],n,oldop[1]);
		eval_sum (oldn[0],n,oldop[0]);
		temp=n;
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
//								Error - invalid operator
								char line[256];
								LoadString(AfxGetInstanceHandle(),IDS_STRING37109,pc_str,STR_LAENGE_STRING_TABLE);
								sprintf(line,pc_str);
								AfxMessageBox(line);
								return(false);;
						}
					}
		}
	}
	goto LOOP;

}
