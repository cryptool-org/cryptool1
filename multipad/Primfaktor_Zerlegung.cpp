// Primfaktor_Zerlegung.cpp: Implementierung der Klasse Primfaktor_Zerlegung.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Primfaktor_Zerlegung.h"
#include "multipad.h"
#include "eval.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////



Primfaktor_Zerlegung::Primfaktor_Zerlegung()
{
	mip = &g_precision;
}

Primfaktor_Zerlegung::~Primfaktor_Zerlegung()
{
	mip = 0;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void Primfaktor_Zerlegung::marks(long start)
{
	
	// mark non-primes in this interval. Note    
    // that those < NEXT are dealt with already  

    int i,pr,j,k;
    for (j=1;j<=MULT/2;j+=2) plus[j]=minus[j]=TRUE;
    for (i=0;;i++)
    { // mark in both directions 
        pr=mip->PRIMES[i];
        if (pr<NEXT) continue;
        if ((long)pr*pr>start) break;
        k=pr-start%pr;
        for (j=k;j<=MULT/2;j+=pr)
            plus[j]=FALSE;
        k=start%pr;
        for (j=k;j<=MULT/2;j+=pr)
            minus[j]=FALSE;
    } 

}

void Primfaktor_Zerlegung::duplication(ZZn sum,ZZn diff,ZZn& x,ZZn& z)
{
	 // double a point on the curve P(x,z)=2.P(x1,z1) 
    ZZn t;
    t=sum*sum;
    z=diff*diff;
    x=z*t;        // x = sum^2.diff^2 
    t-=z;         // t = sum^2-diff^2 
    z+=ak*t;      // z = ak*t +diff^2 
    z*=t;
}

void Primfaktor_Zerlegung::addition(ZZn xd,ZZn zd,ZZn sm1,ZZn df1,ZZn sm2,ZZn df2,ZZn& x,ZZn& z)
{
	// add two points on the curve P(x,z)=P(x1,z1)+P(x2,z2) 
    // given their difference P(xd,zd)                      
    ZZn t;
    x=df2*sm1;
    z=df1*sm2;
    t=z+x;
    z-=x;
    x=t*t;
    x*=zd;   // x = zd.[df1.sm2+sm1.df2]^2 
    z*=z;
    z*=xd;   // z = xd.[df1.sm2-sm1.df2]^2 
}

void Primfaktor_Zerlegung::ellipse(ZZn x,ZZn z,int r,ZZn& x1,ZZn& z1,ZZn& x2,ZZn& z2)
{
	 // calculate point r.P(x,z) on curve 
    int k,rr;
    k=1;
    rr=r;
    x1=x;
    z1=z;
    duplication(x1+z1,x1-z1,x2,z2);  // generate 2.P 
    while ((rr/=2)>1) k*=2;
    while (k>0)
    { // use binary method 
        if ((r&k)==0)
        { // double P(x1,z1) mP to 2mP 
            addition(x,z,x1+z1,x1-z1,x2+z2,x2-z2,x2,z2);
            duplication(x1+z1,x1-z1,x1,z1);
        }
        else
        { // double P(x2,z2) (m+1)P to (2m+2)P 
            addition(x,z,x1+z1,x1-z1,x2+z2,x2-z2,x1,z1);
            duplication(x2+z2,x2-z2,x2,z2);
        }    
        k/=2;
    }
}

void Primfaktor_Zerlegung::next_phase()
{
	 // now change gear
    ZZn s1,d1,s2,d2;
    long interval;
    xt=x;
    zt=z;
    s2=x+z;
    d2=x-z;                    // P = (s2,d2) 
    duplication(s2,d2,x,z);
    s1=x+z;
    d1=x-z;                    // 2.P = (s1,d1) 
    fu[1]=x1/z1;
    addition(x1,z1,s1,d1,s2,d2,x2,z2);  // 3.P = (x2,z2) 
    for (int m=5;m<=MULT/2;m+=2)
    { // calculate m.P = (x,z) and store fu[m] = x/z 
        addition(x1,z1,x2+z2,x2-z2,s1,d1,x,z);
        x1=x2;
        z1=z2;
        x2=x;
        z2=z;
        if (!cp[m]) continue;
        fu[m]=x2/z2;        
    }
    ellipse(xt,zt,MULT,x,z,x2,z2);
    xt=x+z;
    zt=x-z;                           // MULT.P = (xt,zt) 
    iv=p/MULT;
    if (p%MULT>MULT/2) iv++;
    interval=(long)iv*MULT;
    p=interval+1;
    ellipse(x,z,iv,x1,z1,x2,z2);      // (x1,z1) = iv.MULT.P 
    fvw=x1/z1;
    marks(interval);
    q=fvw-fu[p%MULT];  
}

int Primfaktor_Zerlegung::giant_step()
{
	// increment giant step
    long interval;
    iv++;
    interval=(long)iv*MULT;
    p=interval+1;
    marks(interval);
    fvw=x2/z2;
    addition(x1,z1,x2+z2,x2-z2,xt,zt,x,z);
    x1=x2;
    z1=z2;
    x2=x;
    z2=z;
    return 1;   
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int Primfaktor_Zerlegung::lenstra_fakt(CString Eingabe)
{
	//  factoring program using Lenstras Elliptic Curve method 
	int index;
	int co_index;
    int phase,m,k,nc,pos,btch;
    long i,pa;
    Big n,t;
    ZZn tt,u,v;

    gprime(LIMIT1);
    for (m=1;m<=MULT/2;m+=2) 
        if (igcd(MULT,m)==1) cp[m]=TRUE;
        else                 cp[m]=FALSE;
//    cout << "input number to be factored\n";
//    cin >> n;

	index=0;
	co_index=0;

	char *str=Eingabe.GetBuffer(100);

	if (false==evaluateFormula::eval(temp, str)) 
	return -1;

	n=temp; 

    if (prime(n))
    {
		//this number is prime
		LoadString(AfxGetInstanceHandle(),IDS_STRING37110,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox(line);
        return 0;
    }

	// Roger
	exp2=0;
	while(0==n%2)
	{
		exp2++;
		n=n/2;
	}
	//

	if (n==1)
	{
		return 0;
	}
    modulo(n);                 // do all arithmetic mod n 
    for (nc=1,k=6;k<100;k++)
    { // try a new curve 
        u=k*k-5;
        v=4*k;
        x=u*u*u;
        z=v*v*v;

        ak=((v-u)*(v-u)*(v-u)*(3*u+v))/(16*u*u*u*v);

        phase=1;
        p=0;
        i=0;
        btch=50;
        //cout << "phase 1 - trying all primes less than " << LIMIT1;
        //cout << "\nprime= " << setw(8) << p;
        forever
        { // main loop 
            if (phase==1)
            {	
                p=mip->PRIMES[i];
                if (mip->PRIMES[i+1]==0)
                { // now change gear 
                    phase=2;
//                  cout << "\nphase 2 - trying last prime less than ";
//                    cout << LIMIT2 << "\nprime= " << setw(8) << p;
                    next_phase();
                    btch*=100;
                    i++;
                    continue;
                }
                pa=p;
                while ((LIMIT1/p) > pa) pa*=p;
                ellipse(x,z,(int)pa,x1,z1,x2,z2);
                x=x1;
                q=z=z1;
            }
            else
            { // looking for last large prime factor of (p+1+d) 
                p+=2;
                pos=p%MULT;
                if (pos>MULT/2) pos=giant_step();
                if (!cp[pos]) continue;
        // if neither interval +/- pos is prime, don't bother 
                if (!plus[pos] && !minus[pos]) continue;
                q*=(fvw-fu[pos]);        // batch gcds 
            }
            if (i++%btch==0)
            { // try for a solution
//                cout << "\b\b\b\b\b\b\b\b" << setw(8) << p << flush;
                t=gcd(q,n);
                if (t==1)
                {
                    if (p>LIMIT2) break;
                    else continue;
                }
                if (t==n)
                {
//					cout << "\ndegenerate case";
                    break;
                }
                if (prime(t)) 
				{
//					Ein primfactor ist
					PL.prime[index]=t;
					CFL.CoFaktor[co_index]=0;
					index++;
					//prim1=t;
					//coprim1=0;
				}
                else 
				{
//					composite factor 
					PL.prime[index]=0;
					CFL.CoFaktor[co_index]=t;
					co_index++;
					//coprim1=t;
					//prim1=0;
				}
                n/=t;
                if (prime(n)) 
				{
//					prime factor   
					PL.prime[index]=n;
					CFL.CoFaktor[co_index]=0;
					index++;
					//prim2=n;
					//coprim2=0;
				}
                else          
				{
//					composite factor 
					PL.prime[index]=0;
					CFL.CoFaktor[co_index]=n;
					co_index++;
					//coprim2=n;
					//prim2=0;
				}
				PL.lastprime=index;
				CFL.lastcofaktor=co_index;
                return 0;
            }
        }
        if (nc>NCURVES) break;
	
//        cout << "\ntrying a different curve " << nc << "\n";
    } 
//    cout << "\nfailed to factor\n";
	LoadString(AfxGetInstanceHandle(),IDS_STRING37111,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line,pc_str);
	AfxMessageBox(line);
    return 0;
}



// void Primfaktor_Zerlegung::SetIOBASE(int base)
// {
//	mip->IOBASE=base;
// }

// eigentlich Miracl precision(50,0);

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


int Primfaktor_Zerlegung::brent(CString Eingabe)
{
	/*  factoring program using Brents method */
	int index, co_index;
    long k,r,i,m,iter;
    Big n,z;
    ZZn x,y,q,ys;

//    cout << "input number to be factored\n";
//    cin >> n;
	index=0;
	co_index=0;

	char *str=Eingabe.GetBuffer(100);

	if (false==evaluateFormula::eval( temp, str)) 
	return -1;

	n=temp; 

    if (prime(n))
    {
        //this number is prime
		LoadString(AfxGetInstanceHandle(),IDS_STRING37110,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox(line);
        return 0;
    }
	
	// Roger
	exp2=0;
	while(0==n%2)
	{
		exp2++;
		n=n/2;
	}
	if (n==1)
	{
		return 0;
	}
	//

    m=10L;
    r=1L;
    iter=0L;
    z=0;
    do
    {
        modulo(n);    // ZZn arithmetic done mod n 
        y=z;          // convert back to ZZn (n has changed!) 
                      // note:- a change of modulus is tricky for
                      // for n-residue representation used in Montgomery
                      // arithmetic 

//        cout << "iterations=" << setw(5) << iter;

        q=1;
        do
        {
            x=y;
            for (i=1L;i<=r;i++) y=(y*y+3);
            k=0;
            do
            {
                iter++;

//              if (iter%10==0) cout << "\b\b\b\b\b" << setw(5) << iter << flush;

                ys=y;
                for (i=1L;i<=min(m,r-k);i++)
                {   
                    y=(y*y+3);
                    q=((y-x)*q);
                }
                z=gcd(q,n);
                k+=m;
            } while (k<r && z==1);
            r*=2;
        } while (z==1);
        if (z==n) do 
        { // back-track 
            ys=(ys*ys+3);
            z=gcd(ys-x,n);
        } while (z==1);
        if (!prime(z))
		{
             //cout << "\ncomposite factor ";
			 CFL.CoFaktor[co_index]=z;
			 co_index++;
		}
        else
		{
			//cout << "\nprime factor     ";
			PL.prime[index]=z;
			index++;
		}
        //cout << z << endl;
        if (z==n) 
		{
			PL.lastprime=index;
			CFL.lastcofaktor=co_index;
			return 0;
		}
        n/=z;
        z=y;          /* convert to Big */
    } while (!prime(n));      
    //cout << "prime factor     ";
    //cout << n << endl;
	PL.prime[index]=n;
	index++;
    
	PL.lastprime=index;
	CFL.lastcofaktor=co_index;
	return 0;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


int Primfaktor_Zerlegung::brute(CString Eingabe)
{
	int index, co_index;
	int n,p;
    Big x;
    
	gprime(LIMIT1); /* generate all primes < LIMIT */

	index=0;
	co_index=0;

	char *str=Eingabe.GetBuffer(100);

	if (false==evaluateFormula::eval(temp, str)) 
	return -1;

	x=temp; 
	
	if (prime(x))
    {
		//this number is prime
		LoadString(AfxGetInstanceHandle(),IDS_STRING37110,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox(line);
        return 0;
    }

	// Roger
	exp2=0;
	while(0==x%2)
	{
		exp2++;
		x=x/2;
	}
	//
	if (x==1)
	{
		return 0;
	}
	n=0;
	p=mip->PRIMES[0];
    forever
    { // try division by each prime 
        if (x%p==0)
        { // factor found 
            x/=p;
            PL.prime[index]=p;
			index++;
            if (x==1) 
			{
				PL.lastprime=index;
				CFL.lastcofaktor=co_index;
				return 0;
			}
            continue;
        }
        if ((x/p)<=p)
        { // must be prime 
            PL.prime[index]=x;
			index++;
			PL.lastprime=index;
			CFL.lastcofaktor=co_index;
            return 0;
        }
		p=mip->PRIMES[++n];
        if (p==0) break;
    }
    if (prime(x))
	{
		PL.prime[index]=x;
		index++;
	}
    else
	{
		CFL.CoFaktor[co_index]=x;
		co_index++;
	}

	if (index==0 && co_index<2)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING37111,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox(line);
	}
	PL.lastprime=index;
	CFL.lastcofaktor=co_index;
    return 0;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int Primfaktor_Zerlegung::Pollard(CString Eingabe)
{
	//  factoring program using Pollards (p-1) method 
	int index, co_index;
    int phase,m,pos,btch;
    long i,pa;
    Big n,t;
    gprime(LIMIT1);
    for (m=1;m<=MULT/2;m+=2)
        if (igcd(MULT,m)==1) cp[m]=TRUE;
        else                 cp[m]=FALSE;

	index=0;
	co_index=0;

	char *str=Eingabe.GetBuffer(100);

	if (false==evaluateFormula::eval(temp, str)) 
	return -1;

	n=temp; 

    if (prime(n))
    {
		//this number is prime
		LoadString(AfxGetInstanceHandle(),IDS_STRING37110,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox(line);
        return 0;
    }
	// Roger
	exp2=0;
	while(0==n%2)
	{
		exp2++;
		n=n/2;
	}
	//
	if (n==1)
	{
		return 0;
	}
    modulo(n);                    /* do all arithmetic mod n */
    phase=1;
    p=0;
    btch=50;
    i=0;
    b=2;
//    cout << "phase 1 - trying all primes less than " << LIMIT1;
//    cout << "\nprime= " << setw(8) << p;
    forever
    { /* main loop */
        if (phase==1)
        { /* looking for all factors of (p-1) < LIMIT1 */
            p=mip->PRIMES[i];
            if (mip->PRIMES[i+1]==0)
            {
                phase=2;
//                cout << "\nphase 2 - trying last prime less than ";
//                cout  << LIMIT3 << "\nprime= " << setw(8) << p;
                next_phase_pollard();
                btch*=100;
                i++;
                continue;
            }
            pa=p;
            while ((LIMIT1/p) > pa) pa*=p;
            b=pow(b,(int)pa);      /* b = b^pa mod n */
            qq=b-1;
        }
        else
        { /* looking for last prime factor of (p-1) < LIMIT3 */
            p+=2;
            pos=p%MULT;
            if (pos>MULT/2) pos=giant_step_pollard();

        /* if neither interval+/-pos is prime, don't bother */
                if (!plus[pos] && !minus[pos]) continue;
            if (!cp[pos]) continue;
            qq*=(bvw-bu[pos]);        /* batch gcd's in q */
        }
        if (i++%btch==0)
        { /* try for a solution */
//            cout << "\b\b\b\b\b\b\b\b" << setw(8) << p << flush;
            t=gcd((Big)qq,n);
            if (t==1)
            {
                if (p>LIMIT3) break;
                else continue;
            }
            if (t==n)
            {
//                cout << "\ndegenerate case";
                break;
            }
            if (prime(t))
			{
				PL.prime[index]=t;
				//CFL.CoFaktor[co_index]=0;
				index++;
			}
            else
			{
				//PL.prime[index]=0;
				CFL.CoFaktor[co_index]=t;
				co_index++;
			}
            n/=t;
            if (prime(n))
			{
				PL.prime[index]=n;
				//CFL.CoFaktor[co_index]=0;
				index++;
			}
            else
			{
				//PL.prime[index]=0;
				CFL.CoFaktor[co_index]=n;
				co_index++;
			}
			PL.lastprime=index;
			CFL.lastcofaktor=co_index;
            return 0;
        }
    } 
//    cout << "\nfailed to factor\n";
	LoadString(AfxGetInstanceHandle(),IDS_STRING37111,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line,pc_str);
	AfxMessageBox(line);
    return 0;
}


void Primfaktor_Zerlegung::next_phase_pollard()
{
	/* now changing gear */
    ZZn bp,t;
    long interval;
    bw=pow(b,8);
    t=1;
    bp=bu[1]=b;
    for (int m=3;m<=MULT/2;m+=2)
    { /* store bu[m] = b^(m*m) */
        t*=bw;
        bp*=t;
        if (cp[m]) bu[m]=bp;
    }
    t=pow(b,MULT);
    t=pow(t,MULT);
    bd=t*t;            /* bd = b^(2*MULT*MULT) */
    iv=p/MULT;
    if (p%MULT>MULT/2) iv++;
    interval=(long)iv*MULT;
    p=interval+1;
    marks_pollard(interval);
    bw=pow(t,(2*iv-1));
    bvw=pow(t,iv);
    bvw=pow(bvw,iv);   /* bvw = b^(MULT*MULT*iv*iv) */
    qq=bvw-bu[p%MULT];

}

int Primfaktor_Zerlegung::giant_step_pollard()
{
	 /* increment giant step */
    long interval;
    iv++;
    interval=(long)iv*MULT;
    p=interval+1;
    marks_pollard(interval);
    bw*=bd;
    bvw*=bw;
    return 1;

}

void Primfaktor_Zerlegung::marks_pollard(long start)
{
	/* mark non-primes in this interval. Note    *
   * that those < NEXT are dealt with already  */
    int i,pr,j,k;
    for (j=1;j<=MULT/2;j+=2) plus[j]=minus[j]=TRUE;
    for (i=0;;i++)
    { /* mark in both directions */
        pr=mip->PRIMES[i];
        if (pr<NEXT) continue;
        if ((long)pr*pr>start) break;
        k=pr-start%pr;
        for (j=k;j<=MULT/2;j+=pr)
            plus[j]=FALSE;
        k=start%pr;
        for (j=k;j<=MULT/2;j+=pr)
            minus[j]=FALSE;
    }        
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Primfaktor_Zerlegung::marks_williams(long start)
{
	/* mark non-primes in this interval. Note    *
   * that those < NEXT are dealt with already  */
    int i,pr,j,k;
    for (j=1;j<=MULT/2;j+=2) plus[j]=minus[j]=TRUE;
    for (i=0;;i++)
    { /* mark in both directions */
        pr=mip->PRIMES[i];
        if (pr<NEXT) continue;
        if ((long)pr*pr>start) break;
        k=pr-start%pr;
        for (j=k;j<=MULT/2;j+=pr)
            plus[j]=FALSE;
        k=start%pr;
        for (j=k;j<=MULT/2;j+=pr)
            minus[j]=FALSE;
    }    
}

void Primfaktor_Zerlegung::next_phase_williams()
{
	/* now change gear */
    ZZn t;
    long interval;
    fp=fu[1]=b;
    fd=b*b-2;
    fn=fd*b-b;
    for (int m=5;m<=MULT/2;m+=2)
    { /* store fu[m] = Vm(b) */
        t=fn*fd-fp;
        fp=fn;
        fn=t;
        if (!cp[m]) continue;
        fu[m]=t;
    }
    fd=luc(b,MULT);
    iv=p/MULT;
    if (p%MULT>MULT/2) iv++;
    interval=(long)iv*MULT;
    p=interval+1;
    marks_williams(interval);
    fvw=luc(fd,iv,&fp);
    q=fvw-fu[p%MULT];	
}

int Primfaktor_Zerlegung::giant_step_williams()
{
	/* increment giant step */
    long interval;
    ZZn t;
    iv++;
    interval=(long)iv*MULT;
    p=interval+1;
    marks_williams(interval);
    t=fvw;
    fvw=fvw*fd-fp;
    fp=t;
    return 1;
}

int Primfaktor_Zerlegung::Williams(CString Eingabe)
{
	/*  factoring program using Williams (p+1) method */
	int index, co_index;
    int k,phase,m,nt,pos,btch;
    long i,pa;
    Big n,t;
    gprime(LIMIT1);
    for (m=1;m<=MULT/2;m+=2)
        if (igcd(MULT,m)==1) cp[m]=TRUE;
        else                 cp[m]=FALSE;

	index=0;
	co_index=0;

	char *str=Eingabe.GetBuffer(100);

	if (false==evaluateFormula::eval(temp, str)) 
	return -1;

	n=temp; 

    if (prime(n))
    {
		//this number is prime
		LoadString(AfxGetInstanceHandle(),IDS_STRING37110,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox(line);
        return 0;

    }
	// Roger
	exp2=0;
	while(0==n%2)
	{
		exp2++;
		n=n/2;
	}
	if (n==1)
	{
		return 0;
	}
	//
    modulo(n);                     /* do all arithmetic mod n */
    for (nt=0,k=3;k<10;k++)
    { /* try more than once for p+1 condition (may be p-1) */
        b=k;                       /* try b=3,4,5..        */
        nt++;
        phase=1;
        p=0;
        btch=50;
        i=0;
//        cout << "phase 1 - trying all primes less than " << LIMIT1;
//        cout << "\nprime= " << setw(8) << p;
        forever
        { /* main loop */
            if (phase==1)
            { /* looking for all factors of p+1 < LIMIT1 */
                p=mip->PRIMES[i];
                if (mip->PRIMES[i+1]==0)
                { /* now change gear */
                    phase=2;
//                    cout << "\nphase 2 - trying last prime less than ";
//                    cout << LIMIT4 << "\nprime= " << setw(8) << p;
                    next_phase_williams();
                    btch*=100;
                    i++;
                    continue;
                }
                pa=p;
                while ((LIMIT1/p) > pa) pa*=p;
                q=luc(b,(int)pa);
                b=q;
                q-=2;
            }
            else
            { /* looking for last large prime factor of (p+1) */
                p+=2;
                pos=p%MULT;
                if (pos>MULT/2) pos=giant_step_williams();
                if (!cp[pos]) continue;

        /* if neither interval+/-pos is prime, don't bother */

                if (!plus[pos] && !minus[pos]) continue;
                q*=(fvw-fu[pos]);  /* batching gcds */
            }
            if (i++%btch==0)
            { /* try for a solution */
//                cout << "\b\b\b\b\b\b\b\b" << setw(8) << p << flush;
                t=gcd(q,n);
                if (t==1)
                {
                    if (p>LIMIT4) break;
                    else continue;
                }
                if (t==n)
                {
//                    cout << "\ndegenerate case";
                    break;
                }
                if (prime(t))
				{
					PL.prime[index]=t;
					//CFL.CoFaktor[co_index]=0;
					index++;
				}
                else 
				{
					//PL.prime[index]=0;
					CFL.CoFaktor[co_index]=t;
					co_index++;
				}
                n/=t;
                if (prime(n))
				{
					PL.prime[index]=n;
					//CFL.CoFaktor[co_index]=0;
					index++;
				}
                else
				{
					//PL.prime[index]=0;
					CFL.CoFaktor[co_index]=n;
					co_index++;
				}
				PL.lastprime=index;
				CFL.lastcofaktor=co_index;
                return 0;
            }
        } 
        if (nt>=NTRYS) break;
//        cout << "\ntrying again\n";
    }
//    cout << "\nfailed to factor\n";
	LoadString(AfxGetInstanceHandle(),IDS_STRING37111,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line,pc_str);
	AfxMessageBox(line);

    return 0;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int Primfaktor_Zerlegung::QSieve(CString Eingabe)
{
	/* factoring via quadratic sieve */
	int index;
	int co_index;
	int i; // i war zuerst unsigned int
    unsigned int j,a,*SV;
    unsigned char logpi;
    int S,r,s1,s2,NS,logm,ptr,threshold,epri;
    long M,la,lptr;
	
	index=0;
	co_index=0;

	char *str=Eingabe.GetBuffer(100);

	if (false==evaluateFormula::eval(temp, str)) 
		return -1;

	NN=temp;
    
	
	if (initv()<0) return 0;
    hmod=2*mlf+1;               /* set up hash table */
    TT=hmod;
    while (!prime(TT)) TT-=2;
    hmod=toint(TT);
    hmod2=hmod-2;
    for (i=0;i<hmod;i++) hash[i]=(-1);

    M=50*(long)mmm;
    NS=M/SSIZE;
    if (M%SSIZE!=0) NS++;
    M=SSIZE*(long)NS;
    logm=0;
    la=M;
    while ((la/=2)>0) logm++;   /* logm = log(M) */

    rp[0]=0;
	logp[0]=0;
    for (i=1;i<=mmm;i++)
    { /* find root mod each prime, and approx log of each prime */
        r=DD%epr[i];
        rp[i]=sqrmp(r,epr[i]);     /* = square root of r mod epr[i] */
        logp[i]=0;
        r=epr[i];
        while((r/=2)>0) logp[i]++;
    }
    r=DD%8;             /* take special care of 2  */
    if (r==5) logp[1]++;
    if (r==1) logp[1]+=2;
    threshold=logm-2*logp[mmm];
 
    jj=0;
    nlp=0;

    TT=RR;
    while ((TT/=2)>0) threshold++;   /*  add in number of bits in RR */
    DG=sqrt(DD*2);
    DG=sqrt(DG/M);
    if (DG%2==0) ++DG;
    if (DG%4==1) DG+=2;
    cout << "working...    0" << flush;
    forever
    { /* try a new polynomial  */

        new_poly();

        for (ptr=(-NS);ptr<NS;ptr++)
        { /* sieve over next period */
            la=(long)ptr*SSIZE;
            SV=(unsigned int *)sieve;
            for (i=0;i<SSIZE/sizeof(int);i++) *SV++=0;
            for (i=1;i<=mmm;i++)
            { /* sieving with each prime */
                epri=epr[i];
                logpi=logp[i];
                r=la%epri;
                s1=(r1[i]-r)%epri;
                if (s1<0) s1+=epri;
                s2=(r2[i]-r)%epri;
                if (s2<0) s2+=epri;
                for (j=s1;j<SSIZE;j+=epri) sieve[j]+=logpi;
                if (s1==s2) continue;
                for (j=s2;j<SSIZE;j+=epri) sieve[j]+=logpi;
            }

            for (a=0;a<SSIZE;a++)
            {  /* main loop - look for fully factored residues */
                if (sieve[a]<threshold) continue;
                lptr=la+a;
                S=0;
                TT=AA*lptr+BB;
                PP=(TT*IG)%DD;             /*  PP = (AAx + BB)/G */
                if (PP<0) PP+=DD;
                VV=(PP*PP)%DD;             /*  VV = PP^2 mod kN  */
                if (TT<0) TT=(-TT);
                if (TT<RR) S=1;            /*  check for -ve VV  */
                if (S==1) VV=DD-VV;
                e[0]=S;
                for (i=1;i<=mmm;i++) e[i]=0;
                if (!factored(lptr,VV)) continue;
                if (gotcha(NN,PP))
                { /* factors found! */
                    PP=gcd(PP,NN);
                    cout << "factors are";
                    if (prime(PP))
					{
						PL.prime[index]=PP;
						index++;
						//cout << "\nprime factor     " << PP;
					}
                    else
					{
						CFL.CoFaktor[co_index]=PP;
						co_index++;
						//cout << "\ncomposite factor " << PP;
					}
                    NN/=PP;
                    if (prime(NN))
					{
						PL.prime[index]=NN;
						index++;
						//cout << "\nprime factor     " << NN;
					}
                    else
					{
						CFL.CoFaktor[co_index]=NN;
						co_index++;
						//cout << "\ncomposite factor " << NN;
					}
                    PL.lastprime=index;
					CFL.lastcofaktor=co_index;
					return 0;
                }
            }
        }
    }
}

int Primfaktor_Zerlegung::initv()
{
	/* initialize */
    Big T;
    double dp;
    int i,k,digits,pak,maxp;
	//int j;
    nbts=8*sizeof(int);

    //cout << "input number to be factored N= \n";
    //cin >> NN;

	
    if (prime(NN))
    {
        
		//this number is prime
		LoadString(AfxGetInstanceHandle(),IDS_STRING37110,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox(line);
        return (-1);
    }


	// Roger
	exp2=0;
	while(0==NN%2)
	{
		exp2++;
		NN=NN/2;
	}
	//

    T=NN;
    digits=1;                   /* digits in N */
    while ((T/=10)>0) digits++;

    if (digits<10) mmm=digits;               
    else mmm=25;
    if (digits>20) mmm=(digits*digits*digits*digits)/4096;
    dp=(double)2*(mmm+100);          /* number of primes to generate */

    maxp=(int)(dp*(log(dp*log(dp)))); /* Rossers upper bound */
    gprime(maxp);

    epr=(int *)mr_alloc(mmm+1,sizeof(int));

    k=knuth(mmm,epr,NN,DD);

    RR=sqrt(DD);

    if (RR*RR==DD)
    {
        cout << k << "N is a perfect square!" << endl;
        cout << "factors are" << endl;
        if (prime(RR)) cout << "prime factor     ";
        else           cout << "composite factor ";
        cout << RR << endl;
        NN=NN/RR;
        if (prime(NN)) cout << "prime factor     ";
        else           cout << "composite factor ";
        cout << NN << endl;
        return (-1);
    }
    cout << "using multiplier k= " << k;
    cout << "\nand " << mmm << " small primes as factor base\n";
    gprime(0);   /* reclaim PRIMES space */

    mlf=2*mmm;    

    r1=(int *)mr_alloc((mmm+1),sizeof(int));
    r2=(int *)mr_alloc((mmm+1),sizeof(int));
    rp=(int *)mr_alloc((mmm+1),sizeof(int));
    bb=(int *)mr_alloc((mmm+1),sizeof(int));
	//bb=(unsigned int *) mr_alloc((mmm+1),sizeof(int));
    e=(int *)mr_alloc((mmm+1),sizeof(int));

    logp=(unsigned char *)mr_alloc(mmm+1,1);

    pr=(int *)mr_alloc((mlf+1),sizeof(int));
    hash=(int *)mr_alloc(2*mlf+1,sizeof(int));

    sieve=(unsigned char *)mr_alloc(SSIZE+1,1);

    xx=new Big[mmm+1];
    yy=new Big[mmm+1];
    zz=new Big[mlf+1];
    ww=new Big[mlf+1];

	EE=(unsigned int **)mr_alloc(mmm+1,sizeof(unsigned int *));
    G=(unsigned int **) mr_alloc(mlf+1,sizeof(unsigned int *));


    pak=1+mmm/(8*sizeof(int));

    for (i=0;i<=mmm;i++)
    { 
        xx[i]=0;
        yy[i]=0;
        bb[i]=(-1);
        EE[i]=(unsigned int *)mr_alloc(pak,sizeof(int)); //Roger
    }
    for (i=0;i<=mlf;i++)
    {
        zz[i]=0;
        ww[i]=0;
        G[i]=(unsigned int *)mr_alloc(pak,sizeof(int)); //Roger
    }

    return 1;
}

int Primfaktor_Zerlegung::knuth(int mmm, int *epr, Big& N, Big& D)
{
	/* Input number to be factored N, find best multiplier k  *
   * set D=k.N */
    Big T;
    double fks,dp,top;
    BOOL found;
    int i,j,bk,nk,kk,rem,p;
	static int pk[]={0,1,2,3,5,6,7,10,11,13,14,15,17,0};

    top=(-10.0e0);
    found=FALSE;
    nk=0;
    bk=0;
    epr[0]=1;
    epr[1]=2;

    do
    { /* search for best Knuth-Schroepel multiplier */
        kk=pk[++nk];
        if (kk==0)
        { /* finished */
            kk=pk[bk];
            found=TRUE;
        }
        D=kk*N;
        fks=log(2.0e0)/(2.0e0);
        rem=D%8;
        if (rem==1) fks*=(4.0e0);
        if (rem==5) fks*=(2.0e0);
        fks-=log((double)kk)/(2.0e0);
        i=0;
        j=1;
        while (j<mmm)
        { /* select small primes */
			p=mip->PRIMES[++i];
            rem=D%p;
            if (spmd(rem,(p-1)/2,p)<=1) /* x = spmd(a,b,c) = a^b mod c */
            { /* use only if Jacobi symbol = 0 or 1 */
                epr[++j]=p;
                dp=(double)p;
                if (kk%p==0) fks+=log(dp)/dp;
                else         fks+=2*log(dp)/(dp-1.0e0);
            }
        }
        if (fks>top)
        { /* find biggest fks */
            top=fks;
            bk=nk;
        }
    } while (!found);
    return kk;	
}

bool Primfaktor_Zerlegung::gotcha(Big& NN, Big& P)
{
	/* use new factorisation */
    Big XX,YY,T;
    int r,j,i,k,n,rb,had,hp;
    bool found;
    found=true;
    if (partial)
    { /* check partial factorisation for usefulness */
        had=lp%hmod;
        forever
        { /* hash search for matching large prime */
            hp=hash[had];
            if (hp<0)
            { /* failed to find match */
                found=false;
                break;
            }
            if (pr[hp]==lp) break; /* hash hit! */
            had=(had+(hmod2-lp%hmod2))%hmod;
        }
        if (!found && nlp>=mlf) return false;
    }
    XX=P;
    YY=1;
    for (k=1;k<=mmm;k++)
    { /* build up square part in YY  *
       * reducing e[k] to 0s and 1s */
        if (e[k]<2) continue;
        r=e[k]/2;
        e[k]%=2;
        T=epr[k];
        YY*=pow(T,r);
    }
    if (partial)
    { /* factored with large prime */
        if (!found)
        { /* store new partial factorization   */
            hash[had]=nlp;
            pr[nlp]=lp;
            zz[nlp]=XX;
            ww[nlp]=YY;
            for (n=0,rb=0,j=0;j<=mmm;j++)
            {
                G[nlp][n]|=((e[j]&1)<<rb); //roger
                if (++rb==nbts) n++,rb=0;
            }
            nlp++;         
        }
        if (found)
        { /* match found so use as factorization  */
            cout << "\b\b\b\b\b*";
            XX=(XX*zz[hp])%NN;
            YY=(YY*ww[hp])%NN;
            for (n=0,rb=0,j=0;j<=mmm;j++)
            {
                e[j]+=((G[hp][n]>>rb)&1);
                if (e[j]==2)
                {
                    YY=(YY*epr[j])%NN;
                    e[j]=0;
                }
                if (++rb==nbts) n++,rb=0;
            }
            YY=(YY*lp)%NN; 
        }
    }
    else cout << "\b\b\b\b\b " << flush;
    if (found)
    {
        for (k=mmm;k>=0;k--)
        { /* use new factorization in search for solution */
            if (e[k]%2==0) continue;
            if (bb[k]<0)
            { /* no solution this time */
                found=false;
                break;
            }
            i=bb[k];
            YY=(YY*yy[i])%NN;    /* There must be a better way! */
			XX=(XX*xx[i])%NN;    /* This is very inefficient -  */
            //YY=(YY*yy[i])%NN;    /* There must be a better way! */
            for (n=0,rb=0,j=0;j<=mmm;j++)
            { /* Gaussian elimination */
                e[j]+=((EE[i][n]>>rb)&1);//roger
                if (++rb==nbts) n++,rb=0;
            }
        }
        for (j=0;j<=mmm;j++)
        { /* update YY */
            if (e[j]<2) continue;
            T=epr[j];
            YY=(YY*pow(T,e[j]/2,NN))%NN;  /* x = pow(a,b,c) = a^b mod c */
        }
        if (!found)
        { /* store details in EE, x and y for later  */
            bb[k]=jj;
            xx[jj]=XX;
            yy[jj]=YY;
            for (n=0,rb=0,j=0;j<=mmm;j++)
            {
                EE[jj][n]|=((e[j]&1)<<rb);//roger
                if (++rb==nbts) n++,rb=0;
            }
            jj++;
            cout << setw(4) << jj; 
        }
    }
    if (found)
    { /* check for false alarm */
        P=XX+YY;
        cout << "\ntrying...\n";
        if (XX==YY || P==NN) found=false;
        if (!found) cout << "working... " << setw(4) << jj << flush;
    }
    return found;
}

bool Primfaktor_Zerlegung::factored(long lptr, Big& T)
{
	/* factor quadratic residue T */
    bool facted;
    int i,j,r,st;  
    partial=false;
    facted=false;
    for (j=1;j<=mmm;j++)
    { /* now attempt complete factorisation of T */
        r=lptr%epr[j];
        if (r<0) r+=epr[j];
        if (r!=r1[j] && r!=r2[j]) continue;
        while (T%epr[j]==0)
        { /* cast out epr[j] */
            e[j]++;
            T/=epr[j];
        }
        st=toint(T);      /*  st = T as an int; st=TOOBIG if too big */
        if (st==1)
        {
           facted=true;
           break;
        }
        if ((T/epr[j])<=epr[j])
        { /* st is prime < epr[mmm]^2 */
            if (st==MR_TOOBIG || (st/epr[mmm])>(1+mlf/50)) break;
            if (st<=epr[mmm])
                for (i=j;i<=mmm;i++)
                if (st==epr[i])
                {
                    e[i]++;
                    facted=true;
                    break;
                }
            if (facted) break;
            lp=st;  /* factored with large prime */
            partial=true;
            facted=true;
            break;
        }
    }
    return facted;
}

void Primfaktor_Zerlegung::new_poly()
{
	/* form the next polynomial */
    int i,r,s,s1,s2;

    r=mip->NTRY;        /* MR_NTRY is global - number of trys at proving */
    mip->NTRY=1;        /* a probable prime  */
    do
    { /* looking for suitable prime DG = 3 mod 4 */
        do DG+=4; while(!prime(DG));
        TT=(DG-1)/2;
        TT=pow(DD,TT,DG);  /*  check DD is quad residue */
    } while (TT!=1);
    mip->NTRY=r;
    TT=(DG+1)/4;
    BB=pow(DD,TT,DG);
    TT=(DD-BB*BB)/DG;
    AA=inverse(2*BB,DG);
    AA=(AA*TT)%DG;
    BB=AA*DG+BB;       /* BB^2 = DD mod DG^2  */
    AA=DG*DG;
    IG=inverse(DG,DD); /*  IG = 1/DG mod DD  */ 
    r1[0]=r2[0]=0;
    for (i=1;i<=mmm;i++) 
    { /* find roots of quadratic mod each prime */
        s=BB%epr[i];
        r=AA%epr[i];
        r=invers(r,epr[i]);      /* r = 1/AA mod p */
        s1=(-s+rp[i]);
        s2=(-s-rp[i]);
        r1[i]=smul(s1,r,epr[i]);  /* s1 = s1*r mod epr[i] */
        r2[i]=smul(s2,r,epr[i]);  
    }
}
