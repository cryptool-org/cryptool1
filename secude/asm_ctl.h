/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

#define _ASM

#include "asm_linkage.h"

#define PROLOGUE(x)  save %sp, -SA(MINFRAME+x), %sp

#define EPILOGUE ret     ; restore ;


#ifndef NAME
#define NAME(x) x
#endif

