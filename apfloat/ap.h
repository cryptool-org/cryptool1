#include <cstddef>
#include <iostream>
#include <fstream>


#if !defined(__AP_H)
#define __AP_H


// Uncomment if you are _sure_ that no memory allocation or file I/O will fail
// #define NDEBUG

#include <cassert>


// Assembler optimizations
// ASM should be defined in the makefile

#if defined (ASM)
#define USEASM
#endif


// Symbolic constants
const double MAX_PRECISE_DOUBLE = 9e15;     // Maximum double that can be presented exactly (approximately)


// Global variables

extern size_t Ramsize;
extern size_t CacheL1size;
extern size_t CacheL2size;
extern size_t Cacheburst;
extern size_t Cachetreshold;
extern size_t Cacheburstblocksize;
extern size_t Cachemaxblocksize;
extern size_t Cacheblocksize;
extern size_t Maxblocksize;
extern size_t Memorytreshold;
extern size_t Blocksize;
extern size_t NProcessors;

extern int Basedigits;

extern int fno;


// These use stuff declared until now
#include "modint.h"
#include "bigint.h"
#include "baseint.h"


extern rawtype Base;
extern rawtype Basedigit;
extern rawtype Basefactors[];
extern int NBasefactors;

extern rawtype primetable[];
extern rawtype moduli[3];
extern rawtype primitiveroots[3];
extern rawtype wftamoduli[3];
extern rawtype wftaprimitiveroots[3];

extern rawtype *workspace;
extern int workspaceused;


// Variables for WFTA

#if defined (WFTA)

extern modint *w_0[];
extern modint *iw_0[];
extern modint *w_1[];
extern modint *iw_1[];
extern modint *w_2[];
extern modint *iw_2[];
extern int n[];
extern int *s[];
extern int m[];
extern int *ms[];
extern int *p[];
extern int *ip[];

#endif  // WFTA


// Truncate function may be a standard function or not

extern "C"
{
    int truncate (const char *filename, long size);
}


// Functions in init.cpp

bool apinit (void);
void apdeinit (void);
void setmodulus (rawtype m);
void clearmodulus (void);


// Functions in prime.cpp

bool isprime (rawtype n);
rawtype nextprime (rawtype n);
rawtype getprime (rawtype n, rawtype u = MAXMODULUS);
size_t factor (rawtype f[], rawtype n);
modint primitiveroot (void);
void initmoduli (rawtype n);
void apbase (int digit);

// Functions in crt.cpp

void crt (rawtype *r, rawtype *m, size_t n);


// Functions in move.cpp

#if defined (USEASM)
extern "C"
{
#endif

void moveraw (void *d, void *s, size_t n);
void swapraw (void *d, void *s, size_t n);

#if defined (USEASM)
}
#endif


// Functions in file.cpp

const char *filename (int fno);


// Functions in scramble.cpp

size_t permute (size_t n, size_t nn);
void scramble (modint data[], size_t nn);
void initscrambletable (size_t ptable[], size_t nn);
void tablescramble (modint data[], size_t ptable[]);


// Functions in transpos.cpp

void transposesquare (modint data[], size_t n1, size_t n2);
void transpose (modint data[], size_t n1, size_t n2);


// Functions in fnt.cpp

void fnt (modint data[], modint pr, int isign, size_t nn, int s = 1);
void ifnt (modint data[], modint pr, int isign, size_t nn, int s = 1);


// Functions in tablefnt.cpp

#if defined (USEASM)
extern "C"
{
#endif

void tablefnt (modint data[], modint wtable[], size_t ptable[], size_t nn, int s = 1);
void itablefnt (modint data[], modint wtable[], size_t ptable[], size_t nn, int s = 1);

#if defined (USEASM)
}
#endif


// Functions in fourstep.cpp

void fourstepfnt (modint data[], modint pr, int isign, size_t nn);
void ifourstepfnt (modint data[], modint pr, int isign, size_t nn);


// Functions in tablefou.cpp

void tablefourstepfnt (modint data[], modint pr, int isign, size_t nn);
void itablefourstepfnt (modint data[], modint pr, int isign, size_t nn);


// Functions in sixstep.cpp

void sixstepfnt (modint data[], modint pr, int isign, size_t nn);
void isixstepfnt (modint data[], modint pr, int isign, size_t nn);


// Functions in tablesix.cpp

void tablesixstepfnt (modint data[], modint pr, int isign, size_t nn, int t = 3);
void itablesixstepfnt (modint data[], modint pr, int isign, size_t nn, int t = 3);


// Functions in tablesit.cpp

void tablesixstepfnttrans (modint data[], modint pr, int isign, size_t nn);
void tablesixstepfnttrans2 (modint data[], modint pr, int isign, size_t nn);
void itablesixstepfnttrans (modint data[], modint pr, int isign, size_t nn);
void itablesixstepfnttrans2 (modint data[], modint pr, int isign, size_t nn, size_t e = 1);


// Functions in wfta.cpp

void createpermutetables (void);
void createwtables (modint pr, modint *wt[], modint *iwt[], modint *w[], modint *iw[]);
void wfta (modint x[], modint *w[], int nn);


// Functions in sixwftat.cpp

void sixstepwftatrans (modint data[], modint *w[], modint pr, int isign, int n1, int n2);
void isixstepwftatrans (modint data[], modint *w[], modint pr, int isign, int n1, int n2);


// Functions in tabletwo.cpp

void tabletwopassfnt (std::fstream &in, modint pr, int isign, size_t nn);
void itabletwopassfnt (std::fstream &in, modint pr, int isign, size_t nn);


// Functions in tabletwt.cpp

void tabletwopassfnttrans (std::fstream &in, modint pr, int isign, size_t nn);
void tabletwopassfnttrans2 (std::fstream &in, modint pr, int isign, size_t nn, size_t o = 0);
void itabletwopassfnttrans (std::fstream &in, modint pr, int isign, size_t nn);
void itabletwopassfnttrans2 (std::fstream &in, modint pr, int isign, size_t nn, size_t o = 0, size_t e = 1);


// This uses stuff declared until now
#include "apfloat.h"


// Misc. functions

rawtype ap2rawtype (apstruct *a);

// Functions in carrycrt.cpp

int carrycrt (apstruct *ds1, apstruct *s2, apstruct *s3, size_t rsize);


// Functions in convolut.cpp

void multiplyinplace (apstruct *ds1, apstruct *s2);
void squareinplace (apstruct *ds);
apstruct *convolution (apstruct *s1, apstruct *s2, size_t rsize, size_t s1size, size_t s2size, size_t n, int *i);
apstruct *autoconvolution (apstruct *s, size_t rsize, size_t ssize, size_t n, int *i);


#endif  // __AP_H
