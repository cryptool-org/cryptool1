=================================================
Abstract
=================================================

   This directory contains a custom build of version 1.4.6 of the cv act library/pc.

   Copyright: (c) 2008 cv cryptovision gmbh, all rights reserved.
   Licence:   The conditions for the use of this software are regulated in the cv act library licence agreement.



=================================================
Content of directories
=================================================

   ./include/*                               > cv act library/pc interfaces

   ./lib_vc_net2008/actvcmt.lib              > cv act library/pc for WIN32 multithreaded applications
   ./lib_vc_net2008/actvcmtd.lib             > cv act library/pc for WIN32 multithreaded debug applications
   ./lib_vc_net2008/actvcmti.lib             > cv act library/pc for WIN32 multithreaded DLL applications
   ./lib_vc_net2008/actvcmtid.lib            > cv act library/pc for WIN32 multithreaded DLL debug applications



   IMPORTANT NOTES for '*_vc_net2008' binaries:
   --------------------------------------------
	
   1. All libraries have been built with MS VC90 (Micrsoft Visual C++ 2008) using
      the following solution platform:
         
         WIN32

   2. All libraries have been built with the following preprocessor defines:

         _SECURE_SCL=0
         _CRT_SECURE_NO_DEPRECATE
         NO_SMARTCARD

   3. The libraries do not include the SecureToken and the PKCS15 module.



======================================================
Change history version 1.4.6 compared to version 1.4.5
======================================================

   Minor bug fixes, no changes of the functionality.



======================================================
Change history version 1.4.5 compared to version 1.4.4
======================================================

   Added ECDSA SHA-2 algorithm OIDs for certificate verification.



======================================================
Change history version 1.4.4 compared to version 1.4.3
======================================================

   1. CRC-16/32 function added (actTools).

   2. Added conversion function for PKCS#3 DH Keys (actTools).



======================================================
Change history version 1.4.3 compared to version 1.4.2
======================================================

   Minor bug fixes, no changes of the functionality.



======================================================
Change history version 1.4.2 compared to version 1.4.1
======================================================

   1. New password based key derivation functions 'PBKDF1' and 'PBKDF2' according to PKCS#5.
      -  The PBKDF2 function is now used by default for password based key derivation
         in all symmetric key objects (e.g. BlockCipher key objects).

 

======================================================
Change history version 1.4.1 compared to version 1.4.0
======================================================

   1. New key derivation function 'X963KDF' according to ANSI X9.63-2001, Section 5.6.3.
      -  As example, X963KDF may be used in (EC-)DH schemes to derive keys of arbitrary length.

   2. (EC-)IES asymmetric encryption and decryption modifed according to ANSI X9.63-2001, Section 5.8.
      -  The modified (EC-)IES key object may be used to encrypt input data of arbitrary length.
      -  PLEASE NOTE: Not backwards compatible to version 1.4.0 and earlier.

   3. New block cipher operation modes according to NIST Special Publication 800-38A:
      -  'OFB' (Output Feedback Mode)
      -  'CTR' (Counter Mode)
