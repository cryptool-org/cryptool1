==================================================================
         CrypTool, Version 1.3.03, August 2002
         (c) Deutsche Bank AG 1998-2002, Frankfurt/Main
         (c) University of Siegen and Karlsruhe
         $Id$
==================================================================


                       Contents

 1. .... Brief description
 1.1. .... How to start - An Introduction to CrypTool
 1.2. .... What do you get in the CrypTool package?
 1.3. .... Acknowledgements
 1.4. .... New maintainer in the future - Road Map
 2. .... Limitations and requirements
 2.1. .... Installation under Windows 95
 2.2. .... Interactive Online Help under Windows XP
 2.3. .... Support for different languages
 2.4. .... Restrictions in libraries used
 3. .... Installation
 4. .... List of files
 4.1. .... Checking the integrity of downloaded files
 5. .... What's new in CrypTool till 1.3.03
 5.1. .... Classical methods
 5.2. .... Symmetric methods
 5.3. .... Asymmetric methods
 5.4. .... Formatting / display / navigation
 5.5. .... Help / PDF script
 5.6. .... Miscellaneous
 5.7. .... Enhancements from version 1.3.00 to 1.3.03
 5.8. .... Planned enhancements after version 1.3.03
 6. .... Possible areas for further development
 6.1. .... Meaningful tasks to make the new maintainer familiar with
 7. .... Brief history of the released main versions of CrypTool
 8. .... Feedback on errors
 9. .... Contact addresses
10. .... References / Hints
10.1. .... Wirtschaftswoche special issue
10.2. .... c't 14/2001, pp 204-208
10.3. .... GISA citizen CD "Into the Internet - with Security"
10.4. .... Freeware project Crank, CAP, CryptAid, etc
11. .... Appendix
11.1. .... Hints for using CrypTool on Linux with Wine



1. Brief description
   -----------------
This README file is part of the free distribution of CrypTool,
a program by means of which cryptographic functions can be easily
demonstrated and known and unknown algorithms analyzed.

Every part of the program comes with extensive Online help, which
can be understood without deep knowledge in cryptography,
therefore no user manual on how to use CrypTool is provided.

CrypTool is completely available in English and German.

It is required that the user is able to use typical applications
under Windows.

The current version of CrypTool can be found at these addresses:
                http://www.CrypTool.com
                http://www.CrypTool.org
                http://www.CrypTool.de

The aim of CrypTool is to explain cryptographic mechanisms and to
demonstrate the use and the limitations of individual mechanisms.
CrypTool has implemented almost all state-of-the-art crypto
functions and allows you to learn about and use, modern and
classic cryptography within the same environment in a "playful"
manner.

CrypTool is used
- within companies to help raising the sensitivity for IT security
  (Awareness) and for educational purposes,
- within school lessons and
- within lectures at several universities.

Kindly note the terms of the license and the information regarding
liability for any damage arising from the use of CrypTool. These
conditions are described during the installation process and at
the introduction page of the Online help for CrypTool.


1.1. How to start - An Introduction to CrypTool
     ------------------------------------------
When you start up CrypTool, the CrypTool work area starts up
along with a small welcome screen which appears in the
foreground. If you press F1 here, the starting page of the Online
help comes up.
This starting page is a good starting point, to become aquainted
with all essential features of CrypTool (using the links on this
starting page).

Read the information and tips on the introductory help page
and then, in the CrypTool work area, open an unencrypted file
from the "examples" subdirectory.
You can now try out many of the CrypTool functions on this file.

To quickly get up to speed on CrypTool, we recommend that you
work through some of the examples (tutorials) provided within the
Online help facility (the examples are shown in the Help contents
overview under "Starting work with CrypTool").

We hope you enjoy trying out all the functionality within
CrypTool.


1.2. What do you get in the CrypTool package?
     ----------------------------------------
The CrypTool package includes the following four main parts:

(1) The program CrypTool
------------------------
Main part of the CrypTool package is the program CrypTool itself.
CrypTool is not intended as an application to be used to encrypt
or otherwise protect real-world data. It is simply a
demonstration primarily used for training purposes.

- To this end, CrypTool contains an extensive collection of
  cryptographic algorithms which are very well-documented.
  In this way, CrypTool is very well suited for training and
  teaching employees awareness of the importance of IT security.

- Most of the cryptographic basic algorithms used are taken from:
  - the industry-proven Secude library (version 5.4.15)
    (www.secude.com) and from
  - the Miracl library (version 4.4.3)
    (http://indigo.ie/~mscott/).
  In this way, CrypTool is also an outstanding reference
  implementation.

- The cryptanalysis of most of the classical algorithms
  implemented is automated. The analysis of modern techniques
  is limited so that CrypTool cannot be used as a hacker's tool.

(2) Documentation
-----------------
A comprehensive documentation is provided. This consists of four
parts:
a) README file (this file)
b) Online Help
   - context-specific help in order to use the program and further
     information about individual topics and principles,
   - demos and sample scenarios (here you learn to know single
     procedures step-by-step).
c) script (on the subject of cryptography, attached as a PDF file)
d) presentation, which shows at some slides the possibilities of
   CrypTool (also attached as PDF file).

(3) The program AES-Tool
------------------------
CrypTool contains a special program for the creation of
self-extracting executable files which can also be used
independently. In this program a session key is generated
from a password, and with this key any file contents are
AES-encrypted.

(4) The story "The Dialogue of the Sisters" as PDF file
-------------------------------------------------------
The title-role sisters use a variant of the RSA algoritm, to
securely communicate.

All the single files included in the package are listed within
chapter 4 (see below in this README file).



1.3. Acknowledgements
     ----------------
A number of individuals have contributed to CrypTool, many of
them in their free time as well (some are listed in the dialog
box you get after double clicking the "About" dialog box).
We are extremely grateful to them.

Dr. Carsten Elsner allowed us to include his story "The Dialogue
of the Sisters" (translated from the German by Klaus Esslinger).
The German version of this story was published in the computer
magazine c't, 25/1999. While c't published a slidely shortened
version you here get the original version.
The author owns all rights at this story. The maintainer of
CrypTool is allowed by author only to distribute this story
together with the CrypTool package.


1.4. New maintainer in the future - Road Map
     ---------------------------------------
CrypTool will get an academic home as planned. There the further
development as open source is co-ordinated.

The current sponsors of CrypTool have been Deutsche Bank AG,
Secude Ltd. and FZI Karlsruhe. 1.3.0x is the last version,
released by Deutsche Bank as maintainer.

From September 2002 the new maintainer is the chair "Security
in Information Technology", faculty computer science from
Mrs. Prof. Dr. Claudia Eckert at the technical university of
Darmstadt, Germany.

Homepage of CrypTool remains www.cryptool.com.

When the new version 1.4 of CrypTool will come is up to the new
maintainer.

Then it is planned to make the source code of CrypTool
freely available as open source to the Internet community.

If you are interested to help developing CrypTool before it is
available as open source please do not hesitate to contact one
of the email addresses listed below.

We would be glad, if not only the old developers but many new
ones help to enhance the functionality and usability of CrypTool.



2. Limitations and requirements
   ----------------------------
CrypTool requires a Win32 environment, as provided under
Windows 95, Windows 98, Windows Me, Windows NT (from version 4.0),
Windows 2000 and Windows XP.

CrypTool also functions basically under FreeBSD/Linux with Wine
(with reservations on functionality and stability).
See appendix 11.1.


2.1. Installation under Windows 95
     -----------------------------
On older Windows 95 systems you may get an error message,
"Cannot find 'secude.dll'", when you attempt to start up CrypTool.
If this is the case, you will only be able to use CrypTool with
some restrictions.

When CrypTool is started up, the algorithms of the Secude library
are dynamically loaded with the aid of the library "msvcrt.dll".

The file "msvcrt.dll" ships with Windows 98, Windows NT etc but
not with Windows 95.
A number of application programs are supplied with a (not always
recent enough) version of "msvcrt.dll" - copy this file into your
Windows directory or into the directory that contains CrypTool.
Alternatively you can download a self extracting executable that
contains "msvcrt.dll" from:
    ftp://ftp.microsoft.com/softlib/mslfiles/msvcrt.exe
Save the file in a temporary directory and double click on it to
extract the files. Follow the instructions in the ReadMe.txt file
contained in the package in order to install the missing file.


2.2. Interactive Online Help under Windows XP
     ----------------------------------------
Using Windows XP there is a special case where it is not
possible to get the Online help via F1: Only menu entries with
sub-menu are affected. The Problem only occurs while the sub-menu
is displayed. In this case pressing F1 has no effect.

Usually you can also get help in CrypTool for menu items which
itself have sub menus, if they are selected.
Under Windows XP you only get the Online help, if the submenu
is not popped up.
With other versions of Windows this doesn't matter - there it is
only important, that the menu has the focus.

Workaround with example: Indiv. Procedures / RSA Demonstration
If the sub menu of "RSA Demonstration" pops up, but you want to
get help for the menu item "RSA Demonstration" itself, only
under Windows XP you have to close the sub menu of
"RSA-Demonstration" using the Esc or the arrow key, and then
press F1.


2.3. Support for different languages
     -------------------------------
Program,  help facility and the documentation are designed to run
in more than one language (currently in English and German).

For each supported language we deliver an extra setup (we gave up
our try, to deliver only one executable containing all languages,
because the automatic adjustment to the language which is set at
the user's PC did only work correctly under Windows NT 4.0, but
unfortunately not under Win9x).


2.4. Restrictions in libraries used
     ------------------------------
The enclosed Secude-Lib is restricted through the ticket file to
a key length of 768 bits for the asymmetric algorithms and smart
card support is disabled. If you have a Secude-Lib license you
will also be able to use longer key lengths with the asymmetric
methods with the aid of your ticket file. Use of Secude-Lib
outside of the CrypTool program requires a license.

In order to demonstrate the RSA cryptosystem and to factorize
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
  Starting with version 1.3.00 you alternatively can export/import
  RSA and DSA PSEs using the PKCS#12 format.

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

SetupCrypTool_1-3-02_en.exe   English language support only.
SetupCrypTool_1-3-02_de.exe   German language support only.

The archives contain the following files:

ReadMe-de.txt..... Copy of these brief instructions (German).
ReadMe-en.txt..... Copy of these brief instructions (English).
CrypTool-en.cnt... Index list for the CrypTool help system.
CrypTool-de.cnt... The German version of CrypTool-en.cnt.
CrypTool.exe...... The executable program.
aestool.exe....... A program which encrypts files into
                   self-extracting programs. To decrypt the files,
                   the correct password must be entered.
CrypTool-en.hlp... CrypTool help system with example scenarios.
CrypTool-de.hlp... The German version of CrypTool-en.hlp
EC-Param.ini...... Initialization file for public key procedures
                   based on elliptic curves.
secude.dll........ Library of cryptographic functions provided by
                   Secude GmbH.
ticket............ License for the Secude library.
irunin.*.......... These files are necessary for installation and
                   deinstallation.

script-en.pdf..... A script on cryptography, prime numbers,
                   number theory and the mathematics behind
                   certain algorithms.
script-de.pdf..... The German version of script-en.pdf.
CrypToolPresentation_1_3_02_en.pdf.. Slides presentation
CrypToolPresentation_1_3_02_de.pdf.. German version of presentation.
DialogueSisters.pdf.... Fantasy story by Dr. Elsner describing a
                        variant of the RSA cryptosystem.
DialogSchwestern.pdf... German version of DialogueSisters.pdf.

references\....... This directory contains text files in the
                   languages German, English, French, Spanish and
                   Latin. These files are routinely used as
                   references for the analysis of encrypted
                   texts. These files are write-protected.

references\deutsch.txt    // Extract from the Value-Added Tax law
          \english.txt    // Extract from Agenda 21 [UN document]
          \genesis-de.txt  // book of Genesis in the
          \genesis-en.txt  // languages German, English
          \genesis-es.txt  // French, Spanish and Latin
          \genesis-fr.txt  // The 2-letter codes are according
          \genesis-la.txt  // to the ISO 639 language codes.

examples\......... This directory contains various sample files
                   which are used in the examples provided in the
                   program. Files ending with the suffix ".txt"
                   are text files. All other files are binary.
                   Files whose names are in the format
		   "XX-enc-YY.*" are encrypted files. Please do
		   not change these files as they are used in the
		   various examples provided in the program.

examples\CrypTool.bmp
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
                   directory which has a name beginning cry*.*
                   (extensions: asc, hex, org, plt, tmp, txt).
CrypTool.ini...... This file is located in the Windows
                   directory and contains the setting for 
                   showing/not showing the welcome screen and
                   the file names of the most recently opened 
                   files.



4.1. Checking the integrity of downloaded files
     ------------------------------------------
You can verify the integrity of files using hash values.
Hash values are like fingerprints: if you newly calculate the
hash of a downloaded file and then compare it with the values
at the CrypTool homepage, you can see, whether you got a unchanged
copy of the original file or not.
If the hash values are different you should download the file
again and eventually try to find the reason, why you had a
modified file at your computer.

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
hash values of them here within the README file:

MD5 hash value                    Name
XXXmd5sumXXX

SHA1 hash value                          Name
XXXsha1sumXXX

In order to do the check you can use the tools mentioned
in part (a) or you can use the program CrypTool itself.

From version 1.3.01 you can calculate the hash values of
"external" files, without loading them into CrypTool:
- menu Indiv. Procedures / Hash / Hash value of a file...
  (using MD5 or SHA1 as hash algorithm!)
- open the regarding file
- compare the shown hash value with the value within this
  README file.

Security reasons recommend to do the comparison for binary
files (EXE, DLL, PDF, ...), if you are not quite sure, that
your computer is untouched.



5. What's new in CrypTool till 1.3.03
   ----------------------------------
The following enhancements and bug fixes (listed till 5.6) have been
added for version 1.3.00 since CrypTool version 1.202 (Dec 2000).
- CrypTool is now fully available in both German and English
  language versions.
- All dialogues has been reviewed for consistency and clarity.
- The restrictions (maximum data volume 64 Kb) which previously
  applied to Windows versions Win95 and Win98 are no longer
  applicable.
- The most recent configuration relating to an algorithm (such
  as the key or alphabet chosen) is stored internally within the
  program.

5.1. Classical methods
     -----------------
+ Homophone encryption is new
+ Permutation encryption new
+ Generation of random numbers
  The following pseudo random number generators are available:
  - The random number generator provided by Secude lib
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
+ Improved Playfair analysis.

5.2. Symmetric methods
     -----------------
+ The separate program AES-Tool generates self-extracting
  programs.
  This means that any file can be encrypted password-protected
  with AES (by entering a hexadecimal key).
+ It is possible to see how a key is generated from a password
  in accordance with PKCS#5 [a hexadecimal key is generated which
  is resistant against dictionary attacks from the text input
  (password). Parameters: output key length, seed for the random
  number generator, number of hash iterations, hash procedure
  (MD2, MD5, SHA-1)].

5.3. Asymmetric methods
     ------------------
+ Demo on number theory and RSA method:
  - prime number generation
  - factorization of numbers (in stages) and using several
    different methods
  - transparent use of the RSA cryptosystem (including for
    self-selected prime numbers).
    This means that you can e.g. duplicate "The Dialogue of 
    the Sisters".

5.4. Formatting / display / navigation
     ---------------------------------
+ Internally the keys and characteristics of all the methods are
  stored separately. Storage and recall of the keys entered are
  achieved via two buttons. Classical methods such as Playfair
  use very specific formats, so that this makes reuse a lot
  simpler.
+ Switching from hex display to text display is no longer
  possible for non-text files
+ When the display changes, the parent window is retained.
+ Hot keys added for moving around within the PDF script

5.5. Help / PDF script
     -----------------
+ Script extended to include an introduction to elementary number
  theory with a lot of examples

5.6. Miscellaneous
     -------------
+ PKCS#12 export and import of RSA- and DSA-PSEs including the
  keys stored within these PSEs.
+ New web site
  - Additional information: presentation in German and English.


5.7. Enhancements from version 1.3.00 to 1.3.03
     ------------------------------------------
The following topics have been improved:
Source code:
+ Revision of the source code for the transmission to the new
  maintainer.
+ Further automation the process of generating the setup package.
Web page:
+ It now contains the hash values of the downloadable files.
  So you can verify whether the integrity of the files on your
  computer is ok.
Documentation:
+ Script:
  - The article "Introduction to elementary number theory"
    (chapter 3) was enhanced with
    - an appendix about the example calls using the software
      package for computer-aided number theory PARI-GP (now you
      can duplicate the examples not only with Mathematica but
      also with a free mathematical package) and with
    - chapter 3.11: information about the current discussion
      about the security of the RSA algorithm (see Bernstein).
  - new chapters 5.1 and 5.2 about special signatures.
  - new in chapter 6: information about the motivation and
    interoperability of elliptic curves.
+ Single CrypTool presentation for version 1.3.0x
  (no separation in features of 1.2.xx and new within 1.3.0x).
+ The Online help got further improvement and enhancements (e.g.
  for the new functions and addition of a time table about
  cryptography).
Functionality:
+ Clicking F1 now also leads you to the regarding text in the
  Online help, even if the active menu item has a submenu.
+ Calculate hash values of external files without loading them
+ Improving the factorization of compound integers:
  - edit the details of each found factor
  - check, if the quadratic sieve method needs more storage
    for the given integer than available.
+ Enhancing the RSA cryptosystem dialogue:
  - inter active usage of factorization if only the public
    parameters are known
  - it's now possible to use hex values as input too.
+ Improvements at the AES-Tool  
  (the version of the AES-Tool delivered with 1.3.03 was partly
  rewritten and is no more comatible with its predecessors):
  - AES-Tool now offers complete functionality also when called
    from the commandline.
  - There is a customization suggesting the file type (exe or aes).
+ With the Hill cipher you can write the details of the used
  key matrix into a text file:
  - the currently used alphabet (choosen with Options/Textoptions)
  - the Hill key matrix, also coded in numbers
  - a sample encryption/decryption calculated in detail.
+ With the manual analysis of the substitution encryption it is
  now possible to move backward and forward between the last
  changes via button click.
  Additionally, you can temporarily store the key, which was the
  result of your manual analysis, and use in later on.
+ Enclose the complete "Dialogue of the Sisters" in German and
  English (within this story a special case of the RSA encryption
  is described which is implemented within the RSA demo).
+ More details shown when calculating the entropy.
+ When showing the content of the certificate, the public key is
  shown too.
+ Show/Visualize the single steps / dependencies of
    -> the creation of an electronic signature,
    -> the hybrid encryption and decryption,
    -> how changes to a document change the hash value
       (sensitivity of hash algorithms).
+ The flow charts used for visualization show you, which steps
  can be taken in which order. If you click a step, where the
  prerequisites are not there, then a popup explains this in
  detail.
+ Step-by-step verification of an RSA-signature is now possible
  too (here the already existing masks are reused - similar as at
  the visualization of the hybrid decryption).


5.8. Planned enhancements after version 1.3.03
     -----------------------------------------
Functionality:
+ Show/Visualize the birthday paradoxon and attack hash methods
  based on this.
+ A pure commandline version of AES-Tool to be also available for
  the operating systems OS/2 and Linux (aestool-os2; aestool-linux).



6. Possible areas for further development
   --------------------------------------
+ Additional algorithms on every aspect of encryption or analysis,
  e.g.
  - ADFGVX as a classic procedure,
  - the RC5 and Ghost as symmetric procedures or
  - Rabin for the public key methods.
+ Customization wherever possible:
  option to set e.g. initial vector, number of rounds, key length,
  word size or the kind of padding (e.g. for the RC5-Algorithm
  see RFC2040).
  Then these additional customazations must become part of the
  format for the internal key storage.
+ Use dictionary for all attacks, not just for substitution.
+ Implementation of standardized pattern searching.
+ Analysis newly to implement for
  - homophone encryption.
+ Analysis improvement (not sophisticated enough yet) of
  - monoalphabetic substitution,
  - Playfair encryption,
  - asymmetric cryptomethods.
+ Summary of all display modules in a logical class tree.
+ Rearrange the source to facilitate a separation of cryptographic
  functions and user interface (make ports and debugging easier).
+ New magnification function in the display for graphics and/or
  display of co-ordinates of the current mouse pointer position.
+ Facilities for correcting individual characters in the analysis
  of XOR, ADD, Vigenere.
+ Display of second-, third-, etc. -best hit in XOR/ADD analysis
  (this could lead to a shorter key length).
+ Autocorrelation: execute more operations (XOR, ADD, ...) in the
  blocks prior to super imposition, if appropriate
+ Make it possible to edit the homophone key (necessary for
  analysis of homophone encryption)
+ Floating entropy: automatic display of relevant places with
  high entropy
+ Hill cipher: enable to transpose the key matrix .
+ Hill cipher: allow not only letters but also integers as
  input for the key matrix.
+ Update the Miracl lib to a newer version than 4.4.3., if this
  improves the performance.
+ Porting to Linux (Secude or Miracl library available) - here
  a great demand is noticed.
+ Porting to Java (a Secude library is available for this).
+ Generate cryptographically strong elliptic curves and use these
  to implement a cryptosystem based on elliptic curves.
  Here, one could take the cryptosystem developed by Menezes and
  Vanstone that was proposed by the authors in 1993:
  A. Menezes and S. Vanstone,
  "Elliptic curve cryptosystems and their implementation",
  Journal of Cryptology, 6 (1993), pp 209-224.
+ Because cryptographic structures and formats are often ASN.1
  encoded: integration of an ASN.1 decoding tool.
+ Visualization of Diffie-Hellman key exchange.
+ In general visualization of dependencies and workflows in
  protocols (not only "simple" algorithms).
+ Add the German standards for validation of random numbers.
+ Implement further standards and refer to all places, where
  they (e.g. PKCS#5) are used, from a menu and from the Online
  help (main task here is user interface and documentation).
+ Enhance CrypTool as a front-end for number theoretic functions
  and values.



6.1. Meaningful tasks to make the new maintainer familiar with
     ---------------------------------------------------------
+ Integrate the RC5 algorithms as described above, in order to
  see all places where to enhance the sources.
+ offer all kind of transpositions and superpositions for the
  content of text windows in an easy-to-use dialogue window.
+ Create test suite with examples and solutions, in order to
  automate testing and to make sure, that program changes do not
  negatively influence old and running functionality:
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



7. Brief history of the released main versions of CrypTool
   -------------------------------------------------------

			Windows-Setup in MB
Version   Date		English		German
1.0.01    Oct. 1999	-		1,3
1.1.01    May  2000	-		2,3
1.2.00    Aug. 2000	-		2,8
1.2.02    Dec. 2000	-		3,2
1.3.00    Jan. 2002	4,7		4,9
1.3.02    June 2002	6,4		6,9
1.3.03    Aug. 2002	xxx		xxx

Remark about the current versions:
1.3.02    many new functions compared to 1.3.00
1.3.03    many minor bug fixes and documentation compared to 1.3.02



8. Feedback on errors (bugs)
   -------------------------
If you have any problems or find any errors, please send a
description of the problem by e-mail to
- joerg-cornelius.schneider@db.com  or
- bernhard.esslinger@db.com / besslinger@web.de

We would be very grateful for suggestions of any kind regarding
CrypTool and we'll be helpful whenever out time allows.

We would also be interested to hear how and where you use
CrypTool.



9. Contact addresses
   -----------------
- joerg-cornelius.schneider@db.com
- bernhard.esslinger@db.com
- besslinger@web.de
- henrik.koy@db.com
- peer.wichmann@fzi.de



10. References / Hints
    ------------------
10.1. Wirtschaftswoche special issue
      ------------------------
In the special issue "Cryptography" of the magazibe Wirtschaftswoche
(Sept. 2000) there was a competition entitled "Crack the text!". 
Please see http://www.wiwo.de/wiwowwwangebot/fn/ww/sfn/buildww/cn/
cn_artikel/id/62633!100301/SH/0/depot/0/bt/1/index.html
If you followed the tips provided, you could be able to crack the
task using CrypTool in a few mouse clicks.

10.2. c't 14/2001, pp 204-208
      -----------------------
A 5-page article on CrypTool was published in July 2001 in this
renowned and widely circulated German computer magazine.

10.3. GISA citizen CD "Into the Internet - with Security"
      ---------------------------------------------------
The German Information Security Agency (GISA) and the German
ministry for internal affairs published in spring 2002 a CD
in order to inform citizens how to use computers and Internet
and how one can securely use the Internet.
CrypTool is included on this CD to raise the knowledge about
cryptographic security functions.
More than 600,000 copies of this CD have been produced.

10.4. Freeware project Crank, CAP, CryptAid, etc
      ------------------------------------------
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
classical cryptanalysis.

The only "useful" programs known to us, which combine cryptography
and crypanalysis (under a graphical user interface) are:
- CAP from Dr. Richard Spillman
  http://www.cs.plu.edu/courses/privacy/index.htm
- CryptAid from David Lovelock
  (probably development stop 1997)
  http://archives.math.utk.edu/software/msdos/miscellaneous/cryptaid/.html

If we are missing something here, please feel free to inform us,
so that we can complete the list.

We explicitely want to state, that we would welcome if all the
efforts made for these single programs could be combined into one
new program.




11. Appendix
    --------

11.1. Hints for using CrypTool on Linux with Wine
11.1.1. ... Installing CrypTool
11.1.2. ... Wine configuration
11.1.3. ... Running CrypTool


11.1. Hints for using CrypTool on Linux with Wine
      -------------------------------------------
These hints are based on tests with Wine 2001-11-29.

11.1.1. Installing CrypTool
        -------------------
In the last step of the installation wizard the user has the
option to start CrypTool. This does not work under Wine. Please
start CrypTool as described below.


11.1.2. Wine configuration
        ------------------
CrypTool does not work with the version of riched32.dll built into
Wine. Try to open a file. It will show up empty if the wrong
version of riched32.dll is used. The problem will probably not
occur if Wine is configured to use an existing Windows partition.
If you use Wine without Windows perform the following steps to fix
the problem:
 - Install CrypTool.
 - Get hold of riched32.dll (we are using version 5.0.1458.47)
   and copy it in the CrypTool installation directory.
   Possibly you have to perform the same procedure with other DLLs
   used by riched32.dll.
   Their names are listed in Wine's error output.
 - Configure Wine to use it.
   In the standard configuration this works.
   If it does not add the following line in the [DllOverrides]
   section of the Wine configuration file:
   "riched32" = "native,builtin"


11.1.3. Running CrypTool
        ----------------

11.1.3.1. Starting
          --------
To start CrypTool change to the directory where it was installed
and start it with:

$ wine CrypTool

If you do not change to the installation directory CrypTool will
not find some important files.


11.1.3.2. Bugs and workarounds
          --------------------
* The Online help cannot be invoked with F1.
  Use the following line to display the Online help:

  $ wine winhlp32 CrypTool.hlp

