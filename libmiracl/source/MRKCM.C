/*
 *   MIRACL Karatsuba method for multiprecision multiplication combined with 
 *   Comba's method for high speed assembly language multiplication
 *   and Montgomery's method for modular muliplication - the KCM Method - 
 *   together yield near optimal speed for exponentiation cryptosystems.
 *
 *   mrkcm.c 
 *
 *   The #define MR_KCM in mirdef.h affects the size of modulus that can
 *   be used. This *must* be determined at compile time. Then any modulus
 *   of size in words = MR_KCM*2^n can be used. For example if MR_KCM=8 
 *   a modulus of size 8,16,32,64 etc can be used. So if MR_KCM = 8 on a
 *   32 bit computer, then the modulus may be 256, 512, 1024, 2048 etc.
 *   bits in length 
 *
 *   To take advantage of this code:-
 *
 *   for the C code, include #define MR_KCM 4 in mirdef.h. Also ensure
 *   that MR_NOASM is defined, as is a double-length type mr_dltype.
 *
 *   For assembly language versions:-
 *
 *   (1) Only implemented for 8086/80386 processor, using Borland compiler.
 *       However only simple instructions used (mov, add, adc, mul ...)
 *       so it shouldn't be too difficult to implement on other processors
 *       (that support unsigned MUL).
 *
 *       For example an implementation of the STEP macro below
 *       on a SPARC processor, might look something like:-
 *
 *       ld     [%01+4*i],%03
 *       ld     [%02+4*j],%04
 *       umul   %03,%04,%03
 *       rd     %y,%04
 *       addcc  %05,%03,%05
 *       addxcc %06,%04,%06
 *       addx   %07,0,%07
 *
 *       Note - this hasn't been tried!
 *
 *   (2) Before compiling the MIRACL library, specify MR_KCM in 
 *       mirdef.h to your required size. A size of 8 is recommended  
 *       for popular modulus sizes on the Pentium processor. A size of 16 
 *       appears to be optimal on the Pentium Pro. For other 
 *       processors you will have to experiment to determine the optimal.
 *       Generally speaking the slower the speed of the MUL relative to
 *       the ADD, the smaller MR_KCM.
 *
 *       Note that 1024 bit RSA decoding with two 512 bit primes, requires 
 *       512 bit exponentiation (using the Chinese Remainder Thereom).
 *
 *   (3) Use Montgomery representation when implementing your crypto-system
 *       e.g. use powmod(). This will automatically call the 
 *       routines in this module if the modulus is one of the supported 
 *       lengths.
 *
 *   Note that this module can generate a *lot* of code for larger values of 
 *   MR_KCM. Compile using -B switch - you will need 
 *   the TASM macro-assembler. If out-of-memory, try using the TASMX /ml 
 *   version of the assembler.
 *
 *   Note that it is *VITAL* that arrays be aligned on 4-byte boundaries
 *   for maximum speed on a 386+. Borland C does *not* do this automatically, 
 *   when using the 16 bit compiler, so simply adding a static integer as 
 *   "padding" can nearly double the speed(!?)
 *
 *   Inspiration from Wei Dai is acknowledged
 *
 *
 *   Copyright (c) 1988-1999 Shamus Software Ltd.
 */

#include <stdio.h>
#include <miracl.h>

#ifdef MR_KCM
  
#if INLINE_ASM == 1    
#define N 2
#define POINTER WORD PTR  
#define PBP bp   
#define PBX bx 
#define PCX cx  
#define PSI si   
#define PDI di   
#define DSI si   
#define DDI di   
#define DBP bp   
#define DAX ax   
#define DBX bx
#define DCX cx   
#define DDX dx   
#endif   
 
#if INLINE_ASM == 2    
#define N 4
#define POINTER DWORD PTR   
#define PBP bp   
#define PBX bx   
#define PSI si   
#define PDI di   
#define PCX cx
#define DSI esi  
#define DDI edi  
#define DBP ebp  
#define DAX eax
#define DBX ebx  
#define DCX ecx  
#define DDX edx  
#endif           
  
#if INLINE_ASM == 3    
#define N 4
#define POINTER DWORD PTR   
#define PBP ebp   
#define PBX ebx
#define PCX ecx   
#define PSI esi   
#define PDI edi   
#define DSI esi  
#define DDI edi  
#define DBP ebp  
#define DAX eax
#define DBX ebx  
#define DCX ecx  
#define DDX edx  
#endif           
  
#ifdef INLINE_ASM
#ifndef MR_LMM
        /* not implemented for large data models in 16 bits - sorry! */
#ifndef MR_NOASM

static void mr_comba_mul(big x,big y,big z)
{ /* multiply two arrays of length MR_KCM */ 
    ASM  
    { /* first define some macros.... */
     STEP MACRO i,j  
       mov DAX,[PBX+N*i] 
       mul POINTER [PSI+N*j] 
       add DBP,DAX 
       adc DDI,DDX 
       adc cl,ch   
     ENDM         

     MFIN MACRO k 
       mov DDX,DDI   
       pop PDI       
       mov [PDI+N*k],DBP 
       push PDI     
       mov DBP,DDX  
       mov DDI,DCX  
       xor cl,cl    
     ENDM          

     DIAG MACRO ns,ne  
       CNT1=ns         
       CNT2=ne         
       WHILE CNT1 LE ne 
           STEP CNT1,CNT2 
           CNT1=CNT1+1   
           CNT2=CNT2-1   
       ENDM    
     ENDM 

     MULTUP MACRO
        CNT=0
        WHILE CNT LT MR_KCM
            DIAG 0,CNT
            MFIN CNT
            CNT=CNT+1
        ENDM
     ENDM

     MULTDOWN MACRO
        SCNT=0
        CNT=MR_KCM
        WHILE SCNT LT (MR_KCM-1)
            SCNT=SCNT+1
            DIAG SCNT,(MR_KCM-1)
            MFIN CNT
            CNT=CNT+1
        ENDM
        pop PDI
        mov [PDI+N*CNT],DBP
     ENDM
    }      

    ASM    push PBP   
    ASM    push DDI
    ASM    push DSI
      /* bx -> x, si -> y, di-> z */   
    ASM    mov PBX,x  
    ASM    mov PSI,y  
    ASM    mov PDI,z 

    ASM    push PDI    
    ASM    xor DCX,DCX 
    ASM    xor DDI,DDI 
    ASM    xor DBP,DBP 
   
    ASM    MULTUP
    ASM    MULTDOWN

    ASM    pop DSI
    ASM    pop DDI
    ASM    pop PBP

}   

static void mr_comba_halfm(big x,big y,big z)
{ /* multiply two arrays, but only return lower half */

    ASM    push PBP   
    ASM    push DDI
    ASM    push DSI
      /* bx -> x, si -> y, di-> z */   
    ASM    mov PBX,x  
    ASM    mov PSI,y  
    ASM    mov PDI,z 

    ASM    push PDI    
    ASM    xor DCX,DCX 
    ASM    xor DDI,DDI 
    ASM    xor DBP,DBP 
   
    ASM    MULTUP

    ASM    pop PDI
    ASM    pop DSI
    ASM    pop DDI
    ASM    pop PBP
}

static void mr_comba_sqr(big x,big z)
{ /* square an array of length MR_KCM */
    ASM  
    { /* first define some macros.... */
     DSTEP MACRO i,j  
       mov DAX,[PBX+N*i]  
       mul POINTER [PBX+N*j] 
       add DBP,DAX 
       adc DDI,DDX 
       adc cl,ch   
       add DBP,DAX 
       adc DDI,DDX 
       adc cl,ch   
     ENDM          

     SELF MACRO k 
       mov DAX,[PBX+N*k] 
       mul DAX      
       add DBP,DAX 
       adc DDI,DDX 
       adc cl,ch   
     ENDM          

     SFIN MACRO k  
       mov [PSI+N*k],DBP 
       mov DBP,DDI  
       mov DDI,DCX  
       xor cl,cl    
     ENDM 

     SDIAG MACRO ns,ne  
        CNT1=ns  
        CNT2=ne  
        WHILE CNT1 LT CNT2  
            DSTEP CNT1,CNT2 
            CNT1=CNT1+1     
            CNT2=CNT2-1     
        ENDM 
     ENDM 

     SQUARE MACRO
        CNT=0
        WHILE CNT LT MR_KCM
            SDIAG 0,CNT
            IF (CNT MOD 2) EQ 0
                SELF CNT/2
            ENDIF
            SFIN CNT
            CNT=CNT+1
        ENDM
        SCNT=0
        WHILE SCNT LT (MR_KCM-1)
            SCNT=SCNT+1
            SDIAG SCNT,(MR_KCM-1)
            IF (CNT MOD 2) EQ 0
                SELF CNT/2
            ENDIF
            SFIN CNT
            CNT=CNT+1
        ENDM
        mov [PSI+N*CNT],DBP
     ENDM
    }      

    ASM          
    {            
        push PBP   
        push DDI
        push DSI
      /* bx -> x, si -> z */   
        mov PBX,x  
        mov PSI,z   
   
        xor DCX,DCX 
        xor DDI,DDI 
        xor DBP,DBP 
   
        SQUARE

        pop DSI
        pop DDI
        pop PBP     
    }  
}

static void mr_cpy(big x,big z,int n)
{ /* copy an array of length n*MR_KCM */
  /* first some macros */
    ASM
    {
        COPYP MACRO i
            mov DAX,[PSI+N*i]
            mov [PBX+N*i],DAX
        ENDM

        COPYCODE MACRO
            CNT=0
            WHILE CNT LT MR_KCM
                COPYP CNT
                CNT=CNT+1
            ENDM
        ENDM
    }
    ASM push PSI

    ASM mov PSI,x
    ASM mov PBX,z
    ASM mov PCX,n

 cp1: 
    ASM COPYCODE

    ASM dec PCX
    ASM je cp2
    ASM lea PSI,[PSI+N*MR_KCM]
    ASM lea PBX,[PBX+N*MR_KCM]        
    ASM jmp cp1
cp2:
    ASM pop PSI
    return;
}

static int mr_addn(big x,big y,big z,int n)
{ /* add two arrays of length n*MR_KCM */
  /* first some macros */
    ASM
    {
        ADDP MACRO i
            mov DAX,[PSI+N*i]
            adc DAX,[PDI+N*i]
            mov [PBX+N*i],DAX
        ENDM

        ADDCODE MACRO
            CNT=0
            WHILE CNT LT MR_KCM
                ADDP CNT
                CNT=CNT+1
            ENDM
        ENDM
    }
    ASM push PSI
    ASM push PDI

    ASM mov PSI,x
    ASM mov PDI,y
    ASM mov PBX,z
    ASM mov PCX,n
    ASM xor DAX,DAX  /* clear carry */

 an1: 
    ASM ADDCODE
                      /* important to preserve carry flag */
    ASM dec PCX
    ASM je an2
    ASM lea PSI,[PSI+N*MR_KCM]
    ASM lea PDI,[PDI+N*MR_KCM]
    ASM lea PBX,[PBX+N*MR_KCM]        
    ASM jmp an1
an2:
    ASM pop PDI
    ASM pop PSI

    ASM jb an3
    return 0;
an3:
    return 1;
}

static int mr_incn(big y,big z,int n)
{ /* add to an array of length n*MR_KCM */
  /* first some macros */

/* Probably fastest on most 80x86 */
    ASM
    {
        INCP MACRO i
            mov DAX,[PSI+N*i]
            adc [PDI+N*i],DAX
        ENDM

        INCCODE MACRO
            CNT=0
            WHILE CNT LT MR_KCM
                INCP CNT
                CNT=CNT+1
            ENDM
        ENDM
    }  

    ASM push PSI
    ASM push PDI

    ASM mov PSI,y
    ASM mov PDI,z
    ASM mov PCX,n
    ASM xor DAX,DAX   /* clear carry */
 in1: 
    ASM INCCODE
                      /* important to preserve carry flag */
    ASM dec PCX
    ASM je in2
    ASM lea PSI,[PSI+N*MR_KCM]
    ASM lea PDI,[PDI+N*MR_KCM]
    ASM jmp in1
in2:
    ASM pop PDI
    ASM pop PSI

    ASM jb in3
    return 0;
in3:
    return 1;
}

static int mr_decn(big y,big z,int n)
{ /* subtract from an array of length n*MR_KCM */
  /* first some macros */

/* Probably fastest on most 80x86 */
    ASM
    {
        DECP MACRO i
            mov DAX,[PSI+N*i]
            sbb [PDI+N*i],DAX
        ENDM

        DECCODE MACRO
            CNT=0
            WHILE CNT LT MR_KCM
                DECP CNT
                CNT=CNT+1
            ENDM
        ENDM
    } 
           
    ASM push PSI
    ASM push PDI

    ASM mov PSI,y
    ASM mov PDI,z
    ASM mov PCX,n
    ASM xor DAX,DAX    /* clear carry */

dn1: 
    ASM DECCODE
                      /* important to preserve carry flag */
    ASM dec PCX
    ASM je dn2
    ASM lea PSI,[PSI+N*MR_KCM]
    ASM lea PDI,[PDI+N*MR_KCM]
    ASM jmp dn1
dn2:
    ASM pop PDI
    ASM pop PSI

    ASM jb dn3
    return 0;
dn3:
    return 1;
}
#endif
#endif
#endif

#ifdef MR_NOASM

static void mr_comba_mul(big x,big y,big z)
{ /* unwound Comba code for 4x4 multiply */
    mr_small extra;
    mr_large dig,carry;

/* going up the pyramid of partial products.... */

    carry=(mr_large)x[0]*y[0];
    z[0]=(mr_small)carry;
    carry=MR_TOP(carry);

    extra=0;
    carry+=(mr_large)x[1]*y[0];
    dig=(mr_large)x[0]*y[1];
    carry+=dig;
    if (carry<dig) extra=1;
    z[1]=(mr_small)carry;
    carry=MR_TOP(carry);
    MR_TOP(carry)=extra;     

    extra=0;
    carry+=(mr_large)x[2]*y[0];  /* never overflows! */
    dig=(mr_large)x[1]*y[1];
    carry+=dig;
    if (carry<dig) extra=1;
    dig=(mr_large)x[0]*y[2];
    carry+=dig;
    if (carry<dig) extra++;
    z[2]=(mr_small)carry;
    carry=MR_TOP(carry);
    MR_TOP(carry)=extra;     
    
    extra=0;
    dig=(mr_large)x[3]*y[0];
    carry+=dig;
    if (carry<dig) extra=1;
    dig=(mr_large)x[2]*y[1];
    carry+=dig;
    if (carry<dig) extra++;
    dig=(mr_large)x[1]*y[2];
    carry+=dig;
    if (carry<dig) extra++;
    dig=(mr_large)x[0]*y[3];
    carry+=dig;
    if (carry<dig) extra++;
    z[3]=(mr_small)carry;
    carry=MR_TOP(carry);
    MR_TOP(carry)=extra;     

    extra=0;
    dig=(mr_large)x[3]*y[1];
    carry+=dig;
    if (carry<dig) extra=1;
    dig=(mr_large)x[2]*y[2];
    carry+=dig;
    if (carry<dig) extra++;
    dig=(mr_large)x[1]*y[3];
    carry+=dig;
    if (carry<dig) extra++;
    z[4]=(mr_small)carry;
    carry=MR_TOP(carry);
    MR_TOP(carry)=extra;     

    extra=0;
    dig=(mr_large)x[3]*y[2];
    carry+=dig;
    if (carry<dig) extra=1;
    dig=(mr_large)x[2]*y[3];
    carry+=dig;
    if (carry<dig) extra++;
    z[5]=(mr_small)carry;
    carry=MR_TOP(carry);
    MR_TOP(carry)=extra;     

    dig=(mr_large)x[3]*y[3];
    carry+=dig;
    z[6]=(mr_small)carry;
    z[7]=MR_TOP(carry);

    return;
}

static void mr_comba_halfm(big x,big y,big z) 
{
    mr_small extra;
    mr_large dig,carry;

    carry=(mr_large)x[0]*y[0];
    z[0]=(mr_small)carry;
    carry=MR_TOP(carry);

    extra=0;
    carry=(mr_large)x[1]*y[0]+carry;
    dig=(mr_large)x[0]*y[1];
    carry+=dig;
    if (carry<dig) extra=1;
    z[1]=(mr_small)carry;
    carry=MR_TOP(carry);
    MR_TOP(carry)=extra;     

    extra=0;
    carry+=(mr_large)x[2]*y[0];
    dig=(mr_large)x[1]*y[1];
    carry+=dig;
    if (carry<dig) extra=1;
    dig=(mr_large)x[0]*y[2];
    carry+=dig;
    if (carry<dig) extra++;
    z[2]=(mr_small)carry;
    carry=MR_TOP(carry);
    MR_TOP(carry)=extra;     

    extra=0;
    dig=(mr_large)x[3]*y[0];
    carry+=dig;
    dig=(mr_large)x[2]*y[1];
    carry+=dig;
    dig=(mr_large)x[1]*y[2];
    carry+=dig;
    dig=(mr_large)x[0]*y[3];
    carry+=dig;
    z[3]=(mr_small)carry;
    return;
}

static void mr_comba_sqr(big x,big z)
{ /* square an array of length MR_KCM */
    mr_small extra;
    mr_large dig,carry;

/* going up the pyramid of partial products.... */

    carry=(mr_large)x[0]*x[0];
    z[0]=(mr_small)carry;
    carry=MR_TOP(carry);

    extra=0;
    dig=(mr_large)x[0]*x[1];
    carry+=dig;
    carry+=dig;
    if (carry<dig) extra=1;
    z[1]=(mr_small)carry;
    carry=MR_TOP(carry);
    MR_TOP(carry)=extra;     

    extra=0;
    dig=(mr_large)x[2]*x[0];
    carry+=dig;
    carry+=dig;
    if (carry<dig) extra=1;
    dig=(mr_large)x[1]*x[1];
    carry+=dig;
    if (carry<dig) extra++;
    z[2]=(mr_small)carry;
    carry=MR_TOP(carry);
    MR_TOP(carry)=extra;     

    extra=0;
    dig=(mr_large)x[3]*x[0];
    carry+=dig;
    if (carry<dig) extra=1;
    carry+=dig;
    if (carry<dig) extra++;
    dig=(mr_large)x[2]*x[1];
    carry+=dig;
    if (carry<dig) extra++;
    carry+=dig;
    if (carry<dig) extra++;
    z[3]=(mr_small)carry;
    carry=MR_TOP(carry);
    MR_TOP(carry)=extra;     

    extra=0;
    dig=(mr_large)x[3]*x[1];
    carry+=dig;
    if (carry<dig) extra=1;
    carry+=dig;
    if (carry<dig) extra++;
    dig=(mr_large)x[2]*x[2];
    carry+=dig;
    if (carry<dig) extra++;
    z[4]=(mr_small)carry;
    carry=MR_TOP(carry);
    MR_TOP(carry)=extra;     

    extra=0;
    dig=(mr_large)x[3]*x[2];
    carry+=dig;
    if (carry<dig) extra=1;
    carry+=dig;
    if (carry<dig) extra++;
    z[5]=(mr_small)carry;
    carry=MR_TOP(carry);
    MR_TOP(carry)=extra;     

    dig=(mr_large)x[3]*x[3];
    carry+=dig;
    z[6]=(mr_small)carry;
    z[7]=MR_TOP(carry);

    return;
}

static void mr_cpy(big x,big z,int n)
{ /* copy an array of length n*4 */
    int m;
    for (m=0;m<4*n;m+=4)
    {
       z[m]=x[m];
       z[m+1]=x[m+1];
       z[m+2]=x[m+2];
       z[m+3]=x[m+3];
    }
}

static int mr_addn(big x,big y,big z,int n)
{ /* add two arrays of length n*4 */
    int m;
    mr_small carry=0;
    mr_large u;

    for (m=0;m<4*n;m+=4)
    { /* unroll the loops 4 times and hope to God for a decent compiler.... */
        u=(mr_large)carry+x[m]+y[m];
        z[m]=(mr_small)u;
        carry=MR_TOP(u);
        u=(mr_large)carry+x[m+1]+y[m+1];
        z[m+1]=(mr_small)u;
        carry=MR_TOP(u);
        u=(mr_large)carry+x[m+2]+y[m+2];
        z[m+2]=(mr_small)u;
        carry=MR_TOP(u);
        u=(mr_large)carry+x[m+3]+y[m+3];
        z[m+3]=(mr_small)u;
        carry=MR_TOP(u);
    } 
    return carry;
}

static int mr_incn(big y,big z,int n)
{ /* add to an array of length n*4 */
    int m;
    mr_small carry=0;
    mr_large u;
    for (m=0;m<4*n;m+=4)
    {
        u=(mr_large)carry+z[m]+y[m];
        z[m]=(mr_small)u;
        carry=MR_TOP(u); 
        u=(mr_large)carry+z[m+1]+y[m+1];
        z[m+1]=(mr_small)u;
        carry=MR_TOP(u); 
        u=(mr_large)carry+z[m+2]+y[m+2];
        z[m+2]=(mr_small)u;
        carry=MR_TOP(u); 
        u=(mr_large)carry+z[m+3]+y[m+3];
        z[m+3]=(mr_small)u;
        carry=MR_TOP(u); 
    }
    return carry;
}

static int mr_decn(big y,big z,int n)
{ /* subtract from an array of length n*4 */
    int m;
    mr_small borrow=0;
    mr_large u;
    for (m=0;m<4*n;m+=4)
    {
        u=(mr_large)z[m]-y[m]-borrow;
        z[m]=(mr_small)u;
        borrow=0-MR_TOP(u);
        u=(mr_large)z[m+1]-y[m+1]-borrow;
        z[m+1]=(mr_small)u;
        borrow=0-MR_TOP(u);
        u=(mr_large)z[m+2]-y[m+2]-borrow;
        z[m+2]=(mr_small)u;
        borrow=0-MR_TOP(u);
        u=(mr_large)z[m+3]-y[m+3]-borrow;
        z[m+3]=(mr_small)u;
        borrow=0-MR_TOP(u);
    } 
    return borrow; 
}

#endif

static void mr_karmul(int n,big t,big x,big y,big z)
{ /* full multiplication z=x*y */
    int i,nd2,m,md2;
    mr_small c1,c2,c=0;
    if (n==MR_KCM)
    { /* reached the bottom... */
        mr_comba_mul(x,y,z);
        return;
    }
    nd2=n/2;
    m=n/MR_KCM;
    md2=m/2;
 
    c1=mr_addn(x,&x[nd2],z,md2);
    c2=mr_addn(y,&y[nd2],&z[nd2],md2);
    mr_karmul(nd2,&t[n],z,&z[nd2],t);
    if (c1) c+=mr_incn(&z[nd2],&t[nd2],md2);
    if (c2) c+=mr_incn(z,&t[nd2],md2);
    if (c1&c2) c++;    /* form (a0+a1).(b0+b1), carry in c */
    mr_karmul(nd2,&t[n],x,y,z);
    c-=mr_decn(z,t,m);           /* subtract a0.b0 */
    mr_karmul(nd2,&t[n],&x[nd2],&y[nd2],&z[n]);
    c-=mr_decn(&z[n],t,m);       /* subtract a1.b1 */
    c+=mr_incn(t,&z[nd2],m);    /* combine results */

    i=n+nd2;
    z[i]+=c;
    if (z[i]<c)
    { /* propagate carries - very rare */
        do 
        {
            i++;
            z[i]++;
        } while (z[i]==0);
    }
}

static void mr_karsqr(int n,big t,big x,big z)
{ /* Squaring z=x*x */
    int i,nd2,m;
    mr_small c;
    if (n==MR_KCM)
    {
        mr_comba_sqr(x,z);
        return;
    }
    nd2=n/2;
    m=n/MR_KCM;
  
    mr_karsqr(nd2,&t[n],x,z);
    mr_karsqr(nd2,&t[n],&x[nd2],&z[n]);
    mr_karmul(nd2,&t[n],x,&x[nd2],t);

    c=mr_incn(t,&z[nd2],m);
    c+=mr_incn(t,&z[nd2],m);

    i=n+nd2;
    z[i]+=c;
    if (z[i]<c)
    { /* propagate carries - very rare */
        do 
        {
            i++;
            z[i]++;
        } while (z[i]==0);
    }
}

static void mr_karmul_lower(int n,big t,big x,big y,big z)
{ /* Calculates Least Significant bottom half of x*y */
    int nd2,m,md2;
    if (n==MR_KCM)
    { /* only calculate bottom half of product */
        mr_comba_halfm(x,y,z);
        return;
    }
    nd2=n/2;
    m=n/MR_KCM;
    md2=m/2;

    mr_karmul(nd2,&t[n],x,y,z);
    mr_karmul_lower(nd2,&t[n],&x[nd2],y,t); 
    mr_incn(t,&z[nd2],md2);
    mr_karmul_lower(nd2,&t[n],x,&y[nd2],t); 
    mr_incn(t,&z[nd2],md2);
}

static void mr_karmul_upper(int n,big t,big x,big y,big z)
{ /* Calculates Most Significant upper half of x*y, given lower part */
    int i,nd2,m,md2;
    mr_small c1,c2,c=0;
    if (n==MR_KCM)
    {
        mr_comba_mul(x,y,z);
        return;
    }
    nd2=n/2;
    m=n/MR_KCM;
    md2=m/2;
    c1=mr_addn(x,&x[nd2],&z[n],md2);
    c2=mr_addn(y,&y[nd2],&z[n+nd2],md2);
    mr_karmul(nd2,&t[n],&z[n],&z[n+nd2],t);
    if (c1) c+=mr_incn(&z[n+nd2],&t[nd2],md2);
    if (c2) c+=mr_incn(&z[n],&t[nd2],md2);
    if (c1&c2) c++;        /* form (a0+a1)(b0+b1), carry in c */

    mr_karmul(nd2,&t[n],&x[nd2],&y[nd2],&z[n]);
    c-=mr_decn(&z[n],t,m);  /* subtract a1.b1 */
                           /* recreate a0.b0 in z */
    mr_incn(z,&z[nd2],md2);
    mr_decn(t,&z[nd2],md2);
    c-=mr_decn(z,t,m);       /* subtract a0.b0 */
    c+=mr_incn(t,&z[nd2],m);

    i=n+nd2;
    z[i]+=c;
    if (z[i]<c)
    { /* propagate carries - very rare */
        do 
        {
            i++;
            z[i]++;
        } while (z[i]==0);
    }
}

void kcm_mul(_MIPD_ big x,big y,big z)
{ /* fast karatsuba multiplication */ 
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    int ml=(int)mr_mip->modulus[0];
    zero(mr_mip->w0);
    mr_karmul(ml,&mr_mip->w7[1],&x[1],&y[1],&mr_mip->w0[1]);
    mr_mip->w0[0]=mr_mip->w7[0]=2*ml;
    copy(mr_mip->w0,z);
}

void kcm_multiply(_MIPD_ int n,big x,big y,big z)
{ /* n *must* be MR_KCM*2^m for m>=0 */   
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    zero(mr_mip->w0);
    mr_karmul(n,&mr_mip->w7[1],&x[1],&y[1],&mr_mip->w0[1]);
    mr_mip->w0[0]=mr_mip->w7[0]=2*n;
    copy(mr_mip->w0,z);
}

void kcm_sqr(_MIPD_ big x,big z)
{ /* fast karatsuba squaring */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    int ml=(int)mr_mip->modulus[0];
    zero(mr_mip->w0);
    mr_karsqr(ml,&mr_mip->w7[1],&x[1],&mr_mip->w0[1]);
    mr_mip->w0[0]=mr_mip->w7[0]=2*ml;
    copy(mr_mip->w0,z);
}

void kcm_square(_MIPD_ int n,big x,big z)
{ /* n *must* be MR_KCM*2^m for m>=0 */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    zero(mr_mip->w0);
    mr_karsqr(n,&mr_mip->w7[1],&x[1],&mr_mip->w0[1]);
    mr_mip->w0[0]=mr_mip->w7[0]=2*n;
    copy(mr_mip->w0,z);
}

void kcm_redc(_MIPD_ big z,big w)
{ /* fast karatsuba Montgomery reduction */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    int m,ml=(int)mr_mip->modulus[0];
    m=ml/MR_KCM;
    copy(z,mr_mip->w0);

    mr_cpy(&mr_mip->w0[ml+1],&w[1],m);

    mr_karmul_lower(ml,&mr_mip->w7[1],&mr_mip->w0[1],&mr_mip->big_ndash[1],&mr_mip->ws[1]);
    mr_mip->ws[0]=w[0]=ml;

    mr_karmul_upper(ml,&mr_mip->w7[1],&mr_mip->ws[1],&mr_mip->modulus[1],&mr_mip->w0[1]);
    mr_mip->w0[0]=mr_mip->w7[0]=2*ml;

    if (mr_decn(&mr_mip->w0[ml+1],&w[1],m))
        mr_incn(&mr_mip->modulus[1],&w[1],m);

}

#endif

