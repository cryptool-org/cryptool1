Rijndael
Joan Daemen

Optimized ANSI C v2.0
-----------------------------------------------------------

This archive contains the following files:

Makefile.bcc:	    makefile for use with Borland compiler.
Makefile.gcc:	    makefile for use with GCC-based compilers.
Makefile.Visualc:   makefile for use with Visual C compiler.
Makefile.org:       original makefile from submitter.
README: 	    This file.
boxes-fst.dat:	Tables that are needed by the reference implementation.
		The tables implement the S-box and its inverse, and also
		some temporary tables needed for multiplying in the finite
		field GF(2^8).
rijndael-alg-fst.c:
rijndael-alg-fst.h:
		Algorithm implementation.
rijndael-api-fst.c:
rijndael-api-fst.h:
		Interface to the C API.
rijndaeltest-fst.c:
		Implementation of the KAT and MCT.
table.128:
table.192:
table.256:
		Files needed for the KAT (for the Table Known Answer Test).



Instructions for the KAT and MCT software:

1) Compile the C code and put the executable in the same directory as the
   table.??? files.
2) Run the executable. It generates all the tables in the NIST format.
3) Compare the generated tables with the original provided tables, e.g.
   in Unix, with `diff'. 
4) The code is independent of the ENDIANness of the machine.
   However, the code casts char pointers to int pointers.
   On some platforms, this casting can cause problems. 
   This will cause malfunctioning of the CBC Monte Carlo tests.
   In this case, the compile parameter STRICT_ALIGN should be set to 1. 
   (Of course this results in slower code.) 


Changes with respect to v1.0 (= round 1 submission)
---------------------------------------------------

1) Removed the parameter blockLen from makeKey() and cipherInit().
   The parameter is still present in the structures keyInstance and
   cipherInstance.
2) Removed some calls to sscan().
3) Corrected the CBC decryption Monte Carlo test code.
4) Provided code for platforms with pointer alignment problems.
4) Provided code for platforms with pointer alignment problems.
4) Provided code for platforms with pointer alignment problems.
