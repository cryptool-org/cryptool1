/*
 *   MIRACL Comba's method for ultimate speed modular multiplication
 *   mrcomba.c 
 *
 *   See "Exponentiation Cryptosystems on the IBM PC", IBM Systems
 *   Journal Vol. 29 No. 4 1990. Comba's method has been extended to 
 *   implement Montgomery reduction. 
 *
 *   Here the inner loops of the basic multiplication, squaring and 
 *   Montgomery's redc() functions are completely unravelled, and 
 *   reorganised for maximum possible speed. Implemented in assembly
 *   language. You really can't go much faster in software on an 8086/80286/
 *   80386. However for 80486/Pentium circumstances change. Branch prediction
 *   means that there is less advantage in unravelling loops, and furthermore
 *   the FP co-processor is a better bet for multiplication (1 cycle) than the
 *   integer multiplication instruction (10 cycles). See mr80x87.c for 
 *   details. For an alternative approach see mrkcm.c
 *
 *   This method would appear to be particularly useful for implementing 
 *   fast Elliptic Curve Cryptosystems
 *
 *   The #define MR_COMBA in mirdef.h determines the FIXED size of 
 *   modulus to be used. This *must* be determined at compile time. 
 *
 *   To take advantage of these programs:-
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
 *   (2) Before compiling the MIRACL library, specify MR_COMBA in 
 *       mirdef.h to your required size, e.g to 16 for fast 512 bit 
 *       exponentiation on a 32-bit computer. 
 *       Note that 1024 bit RSA decoding with two 512 bit primes, requires 
 *       512 bit exponentiation (using the Chinese Remainder Thereom).
 *
 *   (3) Use Montgomery representation when implementing your crypto-system
 *       e.g. use monty_powmod(). This will automatically call the 
 *       routines in this module.
 *
 *   Note that this module can generate a *lot* of code e.g. > 49kbytes for 
 *   MR_COMBA = 32 for an 80386. Compile using -B switch - you will need 
 *   the TASM macro-assembler. If out-of-memory, try using the TASMX /ml 
 *   version of the assembler.
 *
 *   Note that it is *VITAL* that arrays be aligned on 4-byte boundaries
 *   for maximum speed on a 386+. Borland C does *not* do this automatically, 
 *   when using the 16 bit compiler, so simply adding a static integer as 
 *   "padding" can nearly double the speed(!?)
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 */


#include <stdio.h>     
#include <miracl.h>    

#ifdef MR_COMBA
#if INLINE_ASM == 1    
#define N 2
#define POINTER WORD PTR  
#define PBP bp   
#define PBX bx   
#define PSI si   
#define PDI di   
#define DSI si   
#define DDI di   
#define DBP bp   
#define DAX ax   
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
#define DSI esi  
#define DDI edi  
#define DBP ebp  
#define DAX eax  
#define DCX ecx  
#define DDX edx  
#endif           
  
#if INLINE_ASM == 3    
#define N 4
#define POINTER DWORD PTR   
#define PBP ebp   
#define PBX ebx   
#define PSI esi   
#define PDI edi   
#define DSI esi  
#define DDI edi  
#define DBP ebp  
#define DAX eax  
#define DCX ecx  
#define DDX edx  
#endif           
  
#ifdef INLINE_ASM
#ifndef MR_LMM
                       /* not implemented for large data model 16 bits */

void comba_mult(_MIPD_ big x,big y,big z) 
{ /* comba multiplier */
    big w0;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    w0=mr_mip->w0; 
    zero(w0); 
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

     SELF MACRO k 
       mov DAX,[PBX+N*k] 
       mul DAX      
       add DBP,DAX 
       adc DDI,DDX 
       adc cl,ch   
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

     MULTIPLY MACRO
        CNT=0
        WHILE CNT LT MR_COMBA
            DIAG 0,CNT
            MFIN CNT
            CNT=CNT+1
        ENDM
        SCNT=0
        WHILE SCNT LT (MR_COMBA-1)
            SCNT=SCNT+1
            DIAG SCNT,(MR_COMBA-1)
            MFIN CNT
            CNT=CNT+1
        ENDM
        pop PDI
        mov [PDI+N*CNT],DBP
     ENDM

    }      
    ASM          
    {            
        push PBP   
        push DDI
        push DSI
      /* bx -> x, si -> y, di-> z */   
        mov PBX,x  
        mov PSI,y  
        mov PDI,w0   
        mov DAX,2*MR_COMBA 
        mov [PDI],DAX    
   
        mov PBP,N   
        add PBX,PBP 
        add PSI,PBP 
        add PDI,PBP 
        push PDI    
        xor DCX,DCX 
        xor DDI,DDI 
        xor DBP,DBP 
   
        MULTIPLY

        pop DSI
        pop DDI
        pop PBP     
    }  
    copy (w0,z); 
}   
 
void comba_square(_MIPD_ big x,big z)  
{ /* super comba squarer */
    big w0;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    w0=mr_mip->w0;       
    zero(w0); 
    ASM
    {  
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
        WHILE CNT LT MR_COMBA
            SDIAG 0,CNT
            IF (CNT MOD 2) EQ 0
                SELF CNT/2
            ENDIF
            SFIN CNT
            CNT=CNT+1
        ENDM
        SCNT=0
        WHILE SCNT LT (MR_COMBA-1)
            SCNT=SCNT+1
            SDIAG SCNT,(MR_COMBA-1)
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
    /* bx -> x, si-> z */ 
        mov PBX,x   
        mov PSI,w0  
        mov DAX,2*MR_COMBA 
        mov [PSI],DAX   
  
        mov PBP,N    
        add PBX,PBP  
        add PSI,PBP  
        xor DCX,DCX  
        xor DDI,DDI  
        xor DBP,DBP  
 
        SQUARE  

        pop DSI
        pop DDI
        pop PBP      
     }                    
     copy (w0,z);      
}                        
                         
void comba_redc(_MIPD_ big t,big w)     
{  /* super comba Montgomery redc() function */                      
    mr_small ndash;
    int rn,reg;
    big w0,modulus;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    ndash=mr_mip->ndash;
    w0=mr_mip->w0;
    modulus=mr_mip->modulus;          
    rn=modulus[0];    
    copy(t,w0);       
    ASM
    {

     RFINU MACRO k  
       mov DAX,DBP

       pop DDX
       push DDX  
       mul DDX 

       mov [PBX+N*k],DAX   
       mul POINTER [PSI]  
       add DBP,DAX 
       adc DDI,DDX 
       adc cl,ch   

       mov DBP,DDI   
       mov DDI,DCX   
       xor DCX,DCX   
       add DBP,[PBX+N*(k+1)]  
       adc DDI,DCX   
     ENDM           

     RFIND MACRO k  
       mov [PBX+N*k],DBP 
       mov DBP,DDI   
       mov DDI,DCX   
       xor DCX,DCX   
       add DBP,[PBX+N*(k+1)] 
       adc DDI,DCX   
     ENDM           

     RDIAGU MACRO ns,ne 
        CNT1=ns  
        CNT2=ne  
        WHILE CNT1 LT ne   
            STEP CNT1,CNT2 
            CNT1=CNT1+1    
            CNT2=CNT2-1    
        ENDM 
     ENDM
 
     REDC MACRO
        CNT=0
        WHILE CNT LT MR_COMBA
            RDIAGU 0,CNT
            RFINU CNT
            CNT=CNT+1
        ENDM
        SCNT=0
        WHILE SCNT LT (MR_COMBA-1)
            SCNT=SCNT+1
            DIAG SCNT,(MR_COMBA-1)
            RFIND CNT
            CNT=CNT+1
        ENDM
        mov [PBX+N*CNT],DBP
        CNT=CNT+1
        mov [PBX+N*CNT],DDI
     ENDM

    }
    ASM 
    {                    
        push PBP     
        push DDI
        push DSI
    /* bx -> t, si -> modulus */  
        mov PBX,w0 
        mov PSI,modulus 
    /* this is a bit tricky. I push "ndash" onto the top of the stack
       from where it can be accessed by RFINU */ 
        mov DDX,ndash
        push DDX   
        mov DAX,2*MR_COMBA+1     
        mov [PBX],DAX         
  
        mov PBP,N     
        add PBX,PBP   
        add PSI,PBP   
  
        xor DDI,DDI   
        xor DCX,DCX   
        mov DBP,[PBX] 
  
        REDC
 
        pop DDX
        pop DSI
        pop DDI
        pop PBP 
    } 
    mr_shift(_MIPP_ w0,(-rn),w0);   
    mr_lzero(w0);               
    if (compare(w0,modulus)>=0) mr_psub(_MIPP_ w0,modulus,w); 
    else copy(w0,w);         
} 

void comba_add(_MIPD_ big x,big y,big w)
{ /* fast modular addition */
    big modulus;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    modulus=mr_mip->modulus;
    if (w!=x && w!=y) zero(w);
    ASM
    {
        ADDP MACRO i
            mov DAX,[PSI+N*i]
            adc DAX,[PBX+N*i]
            mov [PDI+N*i],DAX
        ENDM

        ADDCODE MACRO
            CNT=1
            WHILE CNT LE MR_COMBA
                ADDP CNT
                CNT=CNT+1
            ENDM
        ENDM

        DECP MACRO i
            mov DAX,[PBX+N*i]
            sbb [PDI+N*i],DAX
        ENDM

        DECCODE MACRO
            CNT=1
            WHILE CNT LE MR_COMBA
                DECP CNT
                CNT=CNT+1
            ENDM
        ENDM

        ACOMP MACRO i
            mov DAX,[PDI+N*i]
            cmp [PBX+N*i],DAX
            ja cma0
            jb cma1
        ENDM

        ACOMPCODE MACRO
            CNT=MR_COMBA
            WHILE CNT GT 0
                ACOMP CNT
                CNT=CNT-1
            ENDM
        ENDM
            

    }
    ASM push PSI
    ASM push PDI

    ASM mov PSI,x
    ASM mov PBX,y
    ASM mov PDI,w
    ASM xor DAX,DAX  /* clear carry */

    ASM ADDCODE
                     /* important to remember carry flag */
    ASM mov PBX,modulus
    ASM jc cma1:
    ASM ACOMPCODE    /* compare sum with modulus */


    ASM jmp cma1
  cma0: 
    ASM jmp cma2

  cma1:              /* here if sum>=modulus */
    ASM xor DAX,DAX
    ASM DECCODE      /* subtract modulus */
  cma2:
    ASM pop PDI
    ASM pop PSI

    w[0]=MR_COMBA;
    mr_lzero(w);   
}

void comba_sub(_MIPD_ big x,big y,big w)
{ /* fast modular subtraction */
    big modulus;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    modulus=mr_mip->modulus;
    if (x!=w && y!=w) zero(w);

    ASM
    {
        SUBP MACRO i
            mov DAX,[PSI+N*i]
            sbb DAX,[PBX+N*i]
            mov [PDI+N*i],DAX
        ENDM

        SUBCODE MACRO
            CNT=1
            WHILE CNT LE MR_COMBA
                SUBP CNT
                CNT=CNT+1
            ENDM
        ENDM

        INCP MACRO i
            mov DAX,[PSI+N*i]
            adc [PDI+N*i],DAX
        ENDM

        INCCODE MACRO
            CNT=1
            WHILE CNT LE MR_COMBA
                INCP CNT
                CNT=CNT+1
            ENDM
        ENDM

    }
    ASM push PSI
    ASM push PDI

    ASM mov PSI,x
    ASM mov PBX,y
    ASM mov PDI,w
    ASM xor DAX,DAX

    ASM SUBCODE
    
    ASM jnc cms1

    ASM xor DAX,DAX
    ASM mov PSI,modulus

    ASM INCCODE          /* oops - negative result - add in modulus */

  cms1:
    ASM pop PDI
    ASM pop PSI

    w[0]=MR_COMBA;
    mr_lzero(w); 
}

#endif
#endif
#endif

