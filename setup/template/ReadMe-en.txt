==================================================================
              CrypTool, Version 1.3.01, April 2002
                  (c) Deutsche Bank AG 1998-2002
                  (c) University of Siegen and Karlsruhe
                         Frankfurt am Main
==================================================================



                       Contents

 1. .... Brief description
 1.1. .... What else comes with the program?
 1.2. .... Acknowledgements
 1.3. .... New maintainer in the future
 2. .... Limitations and requirements
 2.1. .... Installation under Windows 95
 2.2. .... Support for different languages
 2.3. .... Restrictions in libraries used
 3. .... Installation
 4. .... List of files
 4.1. .... Checking the integrity of downloaded files
 5. .... How to start
 6. .... What's new in CrypTool 1.3.00
 6.1. .... Classical methods
 6.2. .... Symmetric methods
 6.3. .... Asymmetric methods
 6.4. .... Formatting / display / navigation
 6.5. .... Help / PDF script
 6.6. .... Miscellaneous
 6.7. .... Enhancements from version 1.3.00 to 1.3.01
 6.8. .... Enhancements from version 1.3.01 to 1.3.02
 7. .... Possible areas for further development
 8. .... Brief history of the main versions of CrypTool
 9. .... Road map
10. .... Feedback on errors
11. .... Contact addresses
12. .... References
12.1. .... Wirtschaftswoche special issue
12.2. .... c't 14/2001, pp 204-208
12.3. .... GNU project crank
13. .... Appendix
13.1. .... Hints for using CrypTool on Linux with Wine



1. Brief description
   -----------------
This README file is part of the free distribution of CrypTool,
a program by means of which cryptographic functions can be easily
demonstrated and known and unknown algorithms analysed.

Every part of the program comes with extensive help.

It is required that the user is able to use typical applications
under Windows.

The current version of CrypTool can be found at these addresses:
                     http://www.CrypTool.com
                     http://www.CrypTool.org
                     http://www.CrypTool.de

The aim of CrypTool is to explain cryptographic mechanisms and to
demonstrate the use and the limitations of individual mechanisms.

Kindly note the terms of the licence and the information regarding
liability for any damage arising from the use of CrypTool. These
conditions are described during the installation process and at
the introduction page of the online Help for CrypTool. 

1.1. What else comes with the program?
     ---------------------------------
As well as the program itself, comprehensive documentation is
provided. This consists of four parts:
a) this README file
b) online Help (program-specific,
                with examples for you to work through)
c) script (on the subject of cryptography, attached as a PDF file)
d) demos (software modules which explain individual topics and
          principles).

CrypTool is not intended as an application to be used to encrypt
or otherwise protect real-world data. It is simply a
demonstration primarily used for training purposes.

- To this end, CrypTool contains an extensive collection of
  cryptographic algorithms which are extremely well-documented.
  In this way, CrypTool is very well suited for training and 
  teaching employees awareness of the importance of IT security.

- Most of the cryptographic basic algorithms used are from:
  - the industry-proven SECUDE library (version 5.4.15) 
    (www.secude.com) and from 
  - the Miracl library (version 4.4.3) 
    (http://indigo.ie/~mscott/).
  In this way, CrypTool is an outstanding reference
  implementation.

- The cryptoanalysis of most of the classical algorithms
  implemented is automated. The analysis of modern techniques
  is limited so that CrypTool cannot be used as a hacker's tool.

- CrypTool contains a special program for the creation of
  self-extracting executable files which can also be used
  independently. In this program a session key is generated
  from a password, and with this key any file contents are
  AES-encrypted.

1.2. Acknowledgements
     ----------------
A number of individuals have contributed to CrypTool, many of
them in their free time as well. We are extremely grateful to
them.

Dr. Carsten Elsner allowed us to include his story "The Dialogue
of the Sisters" (translated from the German by Klaus Esslinger). 
The author owns all rights at this story. The maintainer of 
CrypTool is allowed by author only to distribute this story 
together with the CrypTool package.


1.3. New maintainer in the future
     ----------------------------
CrypTool will get an academic home as planned. There the further
development as open source is co-ordinated.
The current sponsors of CrypTool have been Deutsche Bank,
Secude Ltd. and FZI Karlsruhe. 1.3.0x is the last version,
released by Deutsche Bank as maintainer.
From May 2002 the new maintainer is the chair "Security
in Information Technology", faculty computer science from
Mrs. Prof. Dr. Claudia Eckert at the technical university of
Darmstadt, Germany.

We would be glad, if not only the old developers but many new
ones help to enhance the functionality and usability of CrypTool. 
Homepage of CrypTool remains www.cryptool.com.



2. Limitations and requirements
   ----------------------------
CrypTool requires a Win32 environment, as provided under
Windows 95, Windows 98, Windows Me, Windows NT (from version 4.0),
Windows 2000 and Windows XP.

CrypTool also functions basically under FreeBSD/Linux with Wine
(with reservations on functionality and stability).
See appendix 13.1..


2.1. Installation under Windows 95
     -----------------------------
On older Windows 95 systems you may get an error message,
"Cannot find 'secude.dll'", when you attempt to start up CrypTool.
If this is the case, you will only be able to use CrypTool with
some restrictions.

When CrypTool is started up, the algorithms of the SECUDE library
are dynamically loaded with the aid of the library "msvcrt.dll".
Unfortunately, under Windows 95 not every version of "msvcrt.dll"
supports integration of the SECUDE library. A number of programs
are supplied with a more recent version of "msvcrt.dll" - copy
this file into your Windows directory or into the directory that
contains CrypTool.


2.2. Support for different languages
     -------------------------------
The program is designed to run in more than one language
(currently in English and German).
Similarly, the help facility and the documentation are available
in both German and English.

Changing the programming language is only automatic under
Windows NT, unfortunately not under Win9x.
For this reason, CrypTool is supplied in three different
installation variants (see chapter 4. List of files).


2.3. Restrictions in libraries used
     ------------------------------
The enclosed Secude-Lib is restricted through the ticket file to a 
key length of 768 bits for the asymmetric algorithms and smart 
card support is disabled. If you have a Secude-Lib license you 
will also be able to use longer key lengths with the asymmetric 
methods with the aid of your ticket file. Use of Secude-Lib
outside of the CrypTool program requires a license.

In order to demonstrate the RSA cryptosystem and to factorise 
integers CrypTool uses the long integer arithmetic of the Miracl 
library from Shamus Software Ltd. We restricted the integer bit 
length up to 1024.



3. Installation
   ------------
To install CrypTool on your PC, copy the CrypTool setup executable
to a suitable place in your file system and double-click on it.
The default installation directory is C:\Program Files\CrypTool.
The target directory can be altered in the installation routine.

If you already possess an earlier version of CrypTool, it is
recommended uninstalling the old version of CrypTool before
installing the new one, as otherwise it is possible that some
of the old files will not be overwritten. Please note:
- During deinstallation not all of the directories and files in
  the program directories (normally C:\Program Files\CrypTool)
  may be deleted. Delete these manually.
- De installation will delete all user generated asymmetric keys.
  If you intend to use those keys a newly installed version of
  CrypTool, then perform the following steps. Copy the
  entire pse\ directory in order to protect these keys. De install
  CrypTool and install the new version. Finally copy the saved 
  pse\ directory to the installation folder.
  Starting with version 1.3.00 you can alternatively export/import
  RSA and DSA PSEs using PKCS#12 format.

Please note that it might be necessary to adjust the access 
permissions if multiple users want to share one CrypTool 
installation. In that case set the access rights in the 
sub-trees "pse\" and "pse\pseca\" to full access for each user.

The "pse\" sub-tree should not be manually altered as, if the
structure becomes inconsistent, it may be necessary to reinstall
CrypTool.



4. List of files
   -------------
The package is distributed as compressed, self extracting archive
in two language versions:

SetupCrypTool_1_3_en.exe English language support only.
SetupCrypTool_1_3_de.exe German language support only.

The archives contain the following files:

ReadMe-de.txt..... Copy of these brief instructions (German)
ReadMe-en.txt..... Copy of these brief instructions (English)
CrypTool-en.cnt... Index list for the CrypTool help system
CrypTool-de.cnt... The German version of CrypTool-en.cnt
CrypTool.exe...... The executable program
aestool.exe....... A program which encrypts files into
                   self-extracting programs. To decrypt the files,
                   the correct password must be entered.
CrypTool-en.hlp... CrypTool help system with example scenarios.
CrypTool-de.hlp... The German version of CrypTool-en.hlp
EC-Param.ini...... Initialisation file for public key procedures
                   based on elliptic curves.
secude.dll........ Library of cryptographic functions provided by
                   SECUDE GmbH.
ticket............ License for the SECUDE library.
irunin.*.......... These files are necessary for installation and
                   deinstallation.

script-en.pdf..... A script on cryptography, prime numbers, 
                   number theory and the mathematics behind 
                   certain algorithms.
script-de.pdf..... The German version of script-en.pdf
DialogueSisters.pdf.... Fantasy story by Dr. Elsner describing a
                        variant of the RSA cryptosystem.

Referenztexte\.... This directory contains text files in the
                   languages German, English, French, Spanish and
                   Latin. These files are routinely used as
                   references for the analysis of encrypted
                   texts. These files are write-protected.

Referenztexte\deutsch.txt // Extract from the Value-Added Tax Law
             \english.txt // Extract from Agenda 21 [UN document]
             \genesis-de.txt  // book of Genesis in the
             \genesis-en.txt  // languages German, English
             \genesis-fr.txt  // French, Spanish and Latin
             \genesis-es.txt
             \genesis-lt.txt

Beispieldateien\.. This directory contains various sample files
                   which are used in the examples provided in the
                   program. Files ending with the suffix ".txt"
                   are text files. All other files are binary.
                   Files whose names are in the format 
		   "XX-enc-YY.*" are encrypted files. Please do 
		   not change these files as they are used in the
		   various examples provided in the program.

Beispieldateien\CrypTool.bmp
               \CrypTool-en.txt
               \CrypTool-de.txt
               \Playfair-enc-de.txt
               \probetext-de.txt
               \psion-enc.hex
               \vernam.txt

pse\.............. This directory and its subdirectory pseca\ are
                   used to store (asymmetric) keys and
                   certificates that have been generated. The
                   following files are necessary for
                   administration of the key database:

pse\pseca\calog
         \CA_exts
         \cert.dir
         \cert.pag
         \crls.dir
         \crls.pag
         \pseca
         \user.dir
         \user.pag

While CrypTool is running, the following files are generated and
managed:

CrypTool.GID...... The help system generates and manages this 
                   file.
cry*.*............ CrypTool writes temporary files to the Temp
                   directory which has a name beginning cry*.*.
CrypTool.ini...... This file is located in the Windows
                   directory and contains the file names of the
                   most recently processed files.



4.1. Checking the integrity of downloaded files
     ------------------------------------------
You can verify the integrity of files using hash values. 
Hash values are like fingerprints: if you newly calculate the
hash of a downloaded file and then compare it with the values
at the CrypTool homepage, you can see, whether you got a copy
of the original file or not. If the hash values are different
you should download the file again and eventually try to find
the reason, why you had a modified file at your computer.

a) Downloadable files
At the homepage of CrypTool www.cryptool.org/.com you can find
the hash values of all files, which could be directly downloaded 
from the English page, within the files md5sum.txt and 
sha1sum.txt.
Using the wide-spreaded tools MD5SUM and SHA1SUM you can check
the integrity of these files.

b) Additionally you can check the files WITHIN the 
downloaded setup-package.
In order to do this check for these files, you can find the
hash values of them here within the readme:

XXXXXXXXXX             RIPEMD-160     SHA-1       MD5
Directory cryptool:
aestool.exe
CrypTool-en.cnt
CrypTool-en.hlp
CrypTool.exe
deutsch.txt
DialogueSisters.pdf
EC-Param.ini
english.txt
irunin.dat
irunin.ini
irunin.lng
ReadMe-en.txt
script-en.pdf
secude.dll
TEST-Param.ini
ticket

Directory cryptool\Beispieldateien:
CrypTool-de.txt
CrypTool-en.txt
CrypTool.bmp
Playfair-enc-de.txt
probetext-de.txt
psion-enc.hex
vernam.txt

Directory cryptool\pse\pseca:
calog
CA_exts
cert.dir
cert.pag
crls.dir
crls.pag
pseca
user.dir
user.pag

Directory cryptool\Referenzdateien:
genesis-eng.txt
genesis-esp.txt
genesis-fra.txt
genesis-ger.txt
genesis-lat.txt

In order to do the check you can use the tools mentioned
in part (a) or you can use the program CrypTool itself.

From version 1.3.01 you can calculate the hash values of
"external" files, without loading them into CrypTool:
- menu Indiv. Procedures / Hash / Hash value of a file...
- open the regarding file
- compare the shown hash value with the value within this
  Readme file (using the same hash algorthm!).

Security reasons recommend to do the comparision for binary 
files (EXE, DLL, PDF, ...), if you are not quite sure, that
your computer is untouched.





5. How to start
   ------------
When you start up CrypTool, the CrypTool work area starts up
along with a small welcome screen which appears in the
foreground, from which you can branch off immediately to the
first page of help if you wish.
Read the information and tips on the introductory page of help
and then, in the CrypTool work area, open an unencrypted file
from the "Beispieldateien" subdirectory.
You can now try out many of the CrypTool functions on this file.

To quickly get up to speed on CrypTool, we recommend that you
work through some of the examples provided within the help
facility (the examples are shown in the Help contents directory
under "Starting work with CrypTool").

We hope you enjoy trying out all the functionality within
CrypTool.



6. What's new in CrypTool 1.3.00
   -----------------------------
The following enhancements and bug fixes have been added since
CrypTool version 1.202 (Dec 2000).
- CrypTool is now fully available in both German and English
  language versions.
- All dialogue has been reviewed for consistency and clarity.
- The restrictions (maximum data volume 64 Kb) which previously
  applied to Windows versions Win95 and Win98 are no longer
  applicable.
- The most recent configuration relating to an algorithm (such
  as the key or alphabet chosen) is stored internally within the
  program.

6.1. Classical methods
     -----------------
+ Homophone encryption is new
+ Permutation encryption new
+ Generation of random numbers
  The following pseudo random number generators are available:
  - The random number generator provided by SECUDE lib
  - A  "x^2 mod N" random number generator configured through
    parameter N
  - Linear congruence generator
  - Inverse linear congruence generator
+ Statistical analyses for random data (e.g. FIPS-140-1)
+ Improved periodicity analysis
+ N-gram analysis expanded (with the option of saving the results)
  The N-gram analysis is restricted for binary files to 64 kB and
  for text files to 256 kB (longer inputs are truncated to the
  maximum input length).
+ Errors in Vigenere and Caesar algorithms have been eliminated
  (any text files)
+ Improved Playfair analysis

6.2. Symmetric methods
     -----------------
+ A separate program generates self-extracting programs.
  This means that any file can be encrypted password-protected
  with AES (by entering a hexadecimal key).
+ It is possible to see how a key is generated from a password
  in accordance with PKCS#5 [a hexadecimal key is generated which
  is resistant against dictionary attacks from the text input
  (password). Parameters: output key length, seed for the random
  number generator, number of hash iterations, hash procedure
  (MD2, MD5, SHA-1)].

6.3. Asymmetric methods
     ------------------
+ Demo on number theory and RSA method:
   - prime number generation
   - factorisation of numbers (in stages) and using several
     different methods
   - transparent use of the RSA cryptosystem (including for
     self-selected prime numbers) (this means that the
     "Dialogue of sisters" from c't 25/1999 magazine can also be
     implemented)

6.4. Formatting / display / navigation
     ---------------------------------
+ Internally the keys and characteristics of all the methods are
  stored separately. Storage and recall of the keys entered are
  achieved via two buttons. Classical methods such as Playfair
  use very specific formats, so that this makes reuse a lot
  simpler.
+ Switching from hex displays to text displays is no longer
  possible for non-text files
+ When the display changes, the parent window is retained.
+ Hot keys added for moving around within the PDF script

6.5. Help / PDF script
     -----------------
+ Script extended to include an introduction to elementary number
  theory with a lot of examples

6.6. Miscellaneous
     -------------
+ PKCS#12 export and import of RSA- and DSA-PSEs including the
  keys stored within these PSEs.
+ New web site
   - Additional information: presentation in German and English.


6.7. Enhancements from version 1.3.00 to 1.3.01
     ------------------------------------------
Source:
+ Revision of the source code for the transmission to the new
  maintainer.
+ Further automation the process of generating the setup package.
Web page:
+ It now contains the hash values of the downloadable files.
  So you can verify whether the integrity of the files on your
  computer is ok.
Dokumentation:
+ Single CrypTool praesentation for version 1.3.01
  (no separation in features of 1.2.xx and new within 1.3.0x).
+ The online Help got further improvement and enhancements (e.g.
  for the new Functions, addition of a time table).
Functionality:
+ Clicking F1 now also leads you to the regarding text in the
  online Help, even if the active menu item has a submenu.
+ Calculate hash values of external files without loading them
+ Show/Visualize 
  - the single steps / dependencies of 
    hybrid encryption and decryption,
+ Step-by-step verification of a signature is now possible too
  (here the already existing masks are reused - similiar as at
  the visualization of the hybrid decryption)
+ Improving the factorization of compound intergers:
    - edit the details of each found factor
    - check, if the quadratic sieve method needs more storage
      for the given integer than available.
+ Enhancing the RSA cryptosystem dialogue
  - inter active usage of factorisation if only the public
    parameters are known
  - it's now possible to use hex values as input too.
+ Improvements at the AES-Tool.
+ Hill cipher: enable to switch (XXXXXXXX) the key matrix 
+ Hill cipher: allow not only letters but also integers as
  input for the key matrix
+ Update the Miracl lib from version 4.4.3 to XXXXXX
+ Enclose the complete "Dialogue of the sisters" in German and
  English (within this story a special case of the RSA encryption
  is described which is implemented within the RSA demo) --
  many thanks to the author Dr. Carsten Elsner.


6.8. Enhancements from version 1.3.01 to 1.3.02
     ------------------------------------------
Functionality:
+ Show/Visualize 
  - the single steps / dependencies of
    creation and verification of an electronic signature.
  - how changes to a document change the hash value
    (sensitivity of hash algorithms).

7. Possible areas for further development
   --------------------------------------
+ Additional algorithms on every aspect of encryption or analysis,
  e.g. ADFGVX as a classic procedure, 
  the RC5 and Ghost as symmetric procedures or
  Rabin for the public key methods.
+ whereever algorithms can be customized: option to set
  e.g. initial vector, number of rounds, key length, word size
  or the kind of padding. This then must be part of description
  for the internal key storage of this special algorithm
  (e.g. for the RC5-Algorithm - see RFC2040).
+ Use dictionary for all attacks, not just for substitution
+ Implementation of standardized pattern searching
+ Analysis new
  - of homophone encryption
  - for asymmetric cryptomethods
+ Analysis improvement (not sophisticated enough yet)
  - of the monoalphabetic substitution
  - the Playfair encryption
+ Summary of all display modules in a logical class tree
+ Rearrange the source to facilitate a separation of cryptographic
  functions and user interface (make ports and debugging easier)
+ New magnification function in the display for graphics and/or
  display of co-ordinates of the current mouse pointer position
+ Facilities for correcting individual characters in the analysis
  of XOR, ADD, Vigenere.
+ Display of second-, third-, etc. -best hit in XOR/ADD analysis
  (this could lead to a shorter key length).
+ Autocorrelation: execute more operations (XOR, ADD, ...) in the
  blocks prior to super imposition, if appropriate
+ Make it possible to edit the homophone key (especially
  necessary for analysis of homophone encryption)
+ Floating entropy: automatic display of relevant places with
  high entropy
+ Porting to Linux (SECUDE or Miracl library available).
+ Porting to Java (a SECUDE library is available for this).
+ Visualization of Diffie-Hellman key exchange.
+ Generate cryptographically strong elliptic curves and use these
  to implement a cryptosystem based on elliptic curves.
  Here, one could take the cryptosystem developed by Menezes and
  Vanstone that was proposed by the authors in 1993:
  A. Menezes and S. Vanstone,
  "Elliptic curve cryptosystems and their implementation",
  Journal of Cryptology, 6 (1993), pp 209-224.
+ Because cryptographic structures and formats are often ASN.1 
  encoded: integration of an ASN.1 decoding tool. 
+ Attack on hash methods based on the "birthday paradoxon".
+ In general visualization of dependancies and workflows in
  protocolls (not only "simple" algorithms).
+ Add the German standards for validation of random numbers.
+ Implements further standards and refer to all places, where
  they are used, from a menu and from the online Help (main
  task here is User Interface and documentation).
+ Enhance CrypTool as a frontend for number theoretic functions
  and values.



7.1 Meaningful tasks to make the new maintainer familiar
     ---------------------------------------------------
+ Integrate the RC5 algorithmu as described above, in order to
  see all places where to enhance the sources.
+ offer all kind of transpositions for the content of text windows
  in an easy-to-use dialogue window.
+ Create test suite with examples and solutions, in order to
  automate testing and to make sure, that program changes do not
  negatively nfluence old functionality:
  a) interface, to load test cases manually into the dialog boxes
  b) create interface, to load test cases from a file into the
     different dialog boxes.
     Maybe build a script language to control all dialogues or
     use automated test tools off-the-shelf.
  c) create commandline interface (best after within the source
     pure crypto functionality is separated from user-interaction)
     so test cases can be read from a file without using
     dialog boxes (without user interface), solved and the result
     again written to a file:
     -> automatic comparison of the solution possible
     -> new version can be tested easier.



8. Brief history of the main versions of CrypTool
   ----------------------------------------------

Version		Date
1.0.01		Oct. 1999
1.1.01		May 2000
1.2.00		Aug. 2000
1.2.02		Dec. 2000
1.3.00		Jan. 2002
1.3.01		Apr. 2002



9. Road map
   -------
When a new version 1.4 of CrypTool will come is up to the new
maintainer.

Then it is planned to make the source code of CrypTool
freely available as open source to the Internet community.



10. Feedback on errors (bugs)
    -------------------------
If you have any problems or find any errors, please send a
description of the problem by e-mail to
- joerg-cornelius.schneider@db.com  or
- bernhard.esslinger@db.com / besslinger@web.de

We would be very grateful for suggestions of any kind regarding
CrypTool.
We would also be interested to hear how and where you use
CrypTool.



11. Contact addresses
    -----------------
- joerg-cornelius.schneider@db.com
- bernhard.esslinger@db.com
- besslinger@web.de
- henrik.koy@db.com
- peer.wichmann@fzi.de



12. References
    ----------
12.1. Wirtschaftswoche special issue
      ------------------------
In the special "Cryptography" issue of Wirtschaftswoche there is
a competition entitled "Crack the text!". Further details
regarding the competition can be obtained from
http://wiwo.de/WirtschaftsWoche/Wiwo_CDA/0,1702,12723_47642,00.html
If you follow the tips provided, you will be able to crack the
task using CrypTool in a few mouse clicks.

12.2. c't 14/2001, pp 204-208
      -----------------------
A 5-page article on CrypTool was published in July 2001 in this
well-known, widely circulated German computer magazine.
The fantasy story, "The Dialogue of sisters", was also
published in c't, 25/1999. The variant of RSA used in this story
can be duplicated with CrypTool version 1.3.00.

12.3. GNU project crank
      -----------------
http://freshmeat.net/projects/crank/

Crank was initiated in January 2001 by Matthew Russell and is
released under the GNU general public license, the GPL.
In the Crank project the idea is that a program with a graphical
user interface will be created under Linux which will enable
classical crypto algorithms to be broken almost entirely
automatically.
Initially the focus is on the analysis of monoalphabetic
substitution ciphers and the development of generic and flexible
analysis tools.
On this page there are also some very interesting links on
classical cryptoanalysis.




13. Appendix
    --------

13.1. Hints for using CrypTool on Linux with Wine
13.1.1. ......... Installing CrypTool
13.1.2. ......... Wine configuration
13.1.3. ......... Running CrypTool


13.1. Hints for using CrypTool on Linux with Wine
      -------------------------------------------

This file is based on tests with wine 2001-11-29.

13.1.1 Installing CrypTool
       -------------------
In the last step of the installation wizard the user has the
option to start CrypTool. This does not work under wine. Please
start CrypTool as described below.


13.1.2 Wine configuration
       ------------------
CrypTool does not work with the version of riched32.dll built into
wine. Try to open a file. It will show up empty if the wrong
version of riched32.dll is used. The problem will probably not
occur if wine is configured to use an existing Windows partition.
If you use wine without Windows perform the following steps to fix
the problem:
 - install CrypTool.
 - get hold of riched32.dll (we are using version 5.0.1458.47)
   and copy it in the CrypTool installation directory. 
   Possibly you have perform the same procedure with other DLLs
   used by riched32.dll.
   Their names are listed in Wine's error output.
 - configure wine to use it. In the standard configuration it
   does. If it does not put the following line in the
   [DllOverrides] section of the wine configuration file:
   "riched32" = "native,builtin"


13.1.3 Running CrypTool
       ----------------

13.1.3.1 Starting
         --------
To start CrypTool change to the directory where it was installed
and start it with:

$ wine CrypTool

If you do not change to the installation directory CrypTool will
not find some important files.


13.1.3.2 Bugs and work arounds
         ---------------------
* The online help cannot be invoked with F1.
  Use the following line to display the online help:

  $ wine winhlp32 CrypTool.hlp
