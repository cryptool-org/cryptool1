README
         An optimized ANSI C implementation of Serpent

Algorithm:	Serpent
Submitter:	Ross Anderson, Eli Biham, Lars Knudsen

==============================================

This directory contains the following files:

Readme.txt	: This file

makefile.bcc	: makefile for use with the Borland compiler
makefile.visualc: makefile for use with the Visual C compiler
makefile.gcc	: makefiel for use with GCC-based compilers
Makefile.org	: explains how to test the C files (from the submitter)

serpent.h	: NIST API header file for Serpent
aes.h		: Symbolic link to serpent.h

serpent.c	: Serpent code, conforming to the NIST C API
serpentsboxes.h	: header file with macros (for serpent.c only)

test.c		: test file with Serpent selftest

Source codes for KAT tests: 

ecb_vk.c
ecb_vt.c

Source codes for MCT tests: 

ecb_e_m.c
ecb_d_m.c
cbc_e_m.c
cbc_d_m.c
cbc_d_m.c
cbc_d_m.c
