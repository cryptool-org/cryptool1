/*
 *   Example program demonstrates 1024 bit Diffie-Hellman, El Gamal and RSA
 *   and 168 bit Elliptic Curve Diffie-Hellman 
 *
 *   Requires: crt.cpp big.cpp elliptic.cpp
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */

#include <iostream.h>
#include <elliptic.h>
#include <big.h>
#include <crt.h>
#include <time.h>

/* large 1024 bit prime p for which (p-1)/2 is also prime */
char *primetext=
"155315526351482395991155996351231807220169644828378937433223838972232518351958838087073321845624756550146945246003790108045940383194773439496051917019892370102341378990113959561895891019716873290512815434724157588460613638202017020672756091067223336194394910765309830876066246480156617492164140095427773547319";

/* Use elliptic curve of the form y^2=x^3-3x+B */

/* 168 bit elliptic curve prime 2#168-2#8-1 */

char *ecp="374144419156711147060143317175368453031918731001599";

/* elliptic curve parameter B */

char *ecb="47118247490432258461368463772056856484209695203684";

/* elliptic curve - point of prime order (x,y) */

char *ecx="2";
char *ecy="254723918246166988633045009882478694134109920361326";

char *text="MIRACL - Fastest multi-precision library in the World!\n";

Miracl precision(120,0);

int main()
{
    int ia,ib;
    long seed;
    Big a,b,p,q,n,phi,pa,pb,key,e,d,m,c,x,y,k;
    Big primes[2],pm[2];
    ECn g,ea,eb;
    miracl *mip=&precision;

    time(&seed);
    irand(seed);   /* change parameter for different values */

    cout << "First Diffie-Hellman Key exchange .... " << endl;

    p=primetext;

/* offline calculations could be done quicker using Brickell's idea
   - See brick.cpp. Note use of "truncated exponent" of 160 bits - 
   could be output from hash function SHA (see mrshs.c)             */

    cout << "\nAlice's offline calculation" << endl;        
    a=rand(160,2);

/* 3 generates the prime sub-group of size (p-1)/2 */

    pa=pow(3,a,p);             // pa =3^a mod p

    cout << "Bob's offline calculation" << endl;        
    b=rand(160,2);
    pb=pow(3,b,p);

    cout << "Alice calculates Key=" << endl;
    key=pow(pb,a,p);
    cout << key << endl;

    cout << "Bob calculates Key=" << endl;
    key=pow(pa,b,p);
    cout << key << endl;

    cout << "Alice and Bob's keys should be the same!" << endl;

/* 
   Now Elliptic Curve version of the above.
   Curve is y^2=x^3+Ax+B mod p, where A=-3, B and p as above 
   "Primitive root" is the point (x,y) above, which is of large prime order q. 
   In this case actually
   q= 374144419156711147060143278790910180887907558063267
 
*/
    cout << "\nLets try that again using elliptic curves...." << endl;
    a=-3;
    b=ecb;
    p=ecp;
    ecurve(a,b,p,MR_PROJECTIVE);
    x=ecx;
    y=ecy;
    g=ECn(x,y);
    ea=eb=g;

    cout << "Alice's offline calculation" << endl;        
    a=rand(160,2);
    ea*=a;
    ia=ea.get(pa); /* <ia,pa> is compressed form of public key */

    cout << "Bob's offline calculation" << endl;        
    b=rand(160,2);
    eb*=b;
    ib=eb.get(pb); /* <ib,pb> is compressed form of public key */

    cout << "Alice calculates Key=" << endl;
    eb=ECn(pb,ib);  /* decompress eb */
    eb*=a;
    eb.get(key);
    cout << key << endl;

    cout << "Bob calculates Key=" << endl;
    ea=ECn(pa,ia); /* decompress ea */
    ea*=b;
    ea.get(key);
    cout << key << endl;

    cout << "Alice and Bob's keys should be the same! (but much smaller)" << endl;


/* El Gamal's Method */

    cout << "\nTesting El Gamal's public key method" << endl;
    p=primetext;
    x=rand(160,2);
    y=pow(3,x,p);
    do 
    {
        k=rand(160,2);
    } while (gcd(p-1,k)!=1);  

    mip->IOBASE=256;  
    a=pow(3,k,p);
    b=modmult(pow(y,k,p),(Big)text,p);
    mip->IOBASE=10;
    cout << "Ciphertext= \n" << a << "\n" << b << endl;

    m=modmult(b,pow(a,p-1-x,p),p);
    mip->IOBASE=256;
    cout << "Plaintext= \n" << m << endl;
    mip->IOBASE=10;

/* RSA. Generate primes p & q. Use e=65537, and find d=1/e mod (p-1)(q-1) */

    cout << "\nNow generating 512-bit random primes p and q" << endl;
    for(;;) 
    {
        p=rand(512,2);        // random 512 bit number
        if (p%2==0) p+=1;
        while (!prime(p)) p+=2;

        q=rand(512,2);
        if (q%2==0) q+=1;
        while (!prime(q)) q+=2;

        n=p*q;

        e=65537L;
        phi=(p-1)*(q-1);
        if (gcd(e,phi)!=1) continue;
        d=inverse(e,phi);
        break;
    }
    cout << p << endl;
    cout << q << endl;
    cout << "n = p.q = \n";
    cout << n << endl;

/* set up for chinese remainder thereom */

    primes[0]=p;
    primes[1]=q;

    Crt chinese(2,primes);

    mip->IOBASE=256;
  
    cout << "Encrypting test string" << endl;
    c=pow((Big)text,e,n);         // c=m^e mod n
    mip->IOBASE=10;
    cout << "Ciphertext= \n";
    cout << c << endl;

    cout << "Decrypting test string" << endl;

    
    pm[0]=pow(c%p,d%(p-1),p);    /* get result mod p */
    pm[1]=pow(c%q,d%(q-1),q);    /* get result mod q */
    m=chinese.eval(pm);    /* combine them using CRT */

    mip->IOBASE=256;
    cout << "Plaintext= \n";
    cout << m << endl;
    return 0;
}
 

