README for the Optimized C Implementation Directory

Algorithm:	MARS
Submitter:	IBM (represented by Nevenko Zunic)
---------------------------------------------

Contents:

    Readme.txt       - this file
    aes.h            - the (modified) NIST C API header
    mars-opt.c       - the optimized MARS code
    tests.c          - code for doing the KAT/IVT/MCT tests
    makefile.bcc     - makefile for use with the Borland compiler
    makefile.visualc - makefile for use with the Visual C compiler
    makefile.gcc     - makefiel for use with GCC-based compilers

Compiling:

    To compile MARS and the tests with Borland C++ 5.0 (in a DOS window):

        bcc32 -Oi -6 -v -A -a4 -O2 -DKAT tests.c mars-ref.c

    -DKAT turns on the KAT tests. Similarly, -DMCT and -DIVT
    turn on their respective tests.  Note that -DIVT adds code to
    the MARS encryption and decryption code, and thus impacts speed.

    To compile MARS and the tests with DJGPP (in a DOS window):

       gcc -Wall -pedantic -O6 -fomit-frame-pointer -mcpu=pentiumpro
          -o tests -DKAT tests.c mars-ref.c

    The same -DMCT and DIVT apply.
    The same -DMCT and DIVT apply.
    The same -DMCT and DIVT apply.
