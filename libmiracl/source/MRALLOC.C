/*
 *   MIRACL memory allocation routines 
 *   mralloc.c
 *
 *   Copyright (c) 1988-1997 Shamus Software Ltd.
 *
 *   MIRACL C Memory allocation/deallocation
 *   Can be replaced with special user-defined routines
 *   Default is to standard system routines
 *
 *   NOTE: uses calloc() which initialises memory to Zero, so make sure
 *   any substituted routine does the same!
 */

#include <stdio.h>
#include "miracl.h" // Roger 17.04.2001
#include <stdlib.h>

void mr_set_align(_MIPD_ int n)
{ /* ad-hoc method to force alignment to n byte boundary. */
  /* Use with care - if at all */
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    mr_mip->alignment=n;
}

void *mr_alloc(_MIPD_ int num,int size)
{
    char *p; 
    int gap;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif

    if (mr_mip==NULL) 
    {
        p=calloc(num,size);
        return (void *)p;
    }
    if (mr_mip->ERNUM) return NULL;
    if (!mr_mip->alignment) 
    {
        p=calloc(num,size);
        if (p==NULL) mr_berror(_MIPP_ MR_ERR_OUT_OF_MEMORY);
        return (void *)p;
    }
    p=calloc(num*size+mr_mip->alignment,1);       /* Allocate a bit more */
    if (p==NULL) 
    {         
        mr_berror(_MIPP_ MR_ERR_OUT_OF_MEMORY);
        return NULL;
    }
    gap=mr_mip->alignment-((unsigned long)p)%mr_mip->alignment;   
                                                  /* Move pointer forward */
    p+=gap;                                       /* to alignment boundary */
    *(p-1)=(unsigned char)gap;                    /* Remember increment */
    return (void *)p;
}

void mr_free(_MIPD_ void *addr)
{
    char *p;
    int gap;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (addr==NULL) return;
    if (mr_mip==NULL)
    {
        free(addr);
        return;
    }
    if (!mr_mip->alignment) 
    {
        free(addr);
        return;
    }
    p=(char *)addr;
    gap=*(p-1);                    /* recall increment */
    p-=gap;                        /* step back to original address */
    free((void*)p);
}

