==================================================================
    CrypTool, Version 1.3.04, June 2003
    (c) Deutsche Bank AG 1998-2003, Frankfurt/Main
    (c) University of Siegen and Darmstadt
    Bernhard Esslinger
    $Id$
==================================================================

                       Contents

 1. .... Brief description of the CrypTool package
 1.1. .... How to start - An Introduction to CrypTool
 1.2. .... What do you get in the CrypTool package?
 1.3. .... Acknowledgements
 1.4. .... New maintainer in the future - Road Map
 2. .... Limitations and requirements
 2.1. .... Education, training and awareness software
 2.2. .... Win32 environment
 2.3. .... Installation under Windows 95
 2.4. .... Interactive Online Help under Windows XP
 2.5. .... Support for different languages
 2.6. .... Restrictions in libraries used
 3. .... Installation / deinstallation / operating
 3.1. .... Installation under multi-user operating systems
 3.2. .... Operating under multi-user operating systems
 4. .... List of files
 4.1. .... Checking the integrity of downloaded files
 5. .... What's new in CrypTool till 1.3.04
 5.1. .... Enhancements from version 1.2.02 to 1.3.00
 5.1.1. .... Classical methods
 5.1.2. .... Symmetric methods
 5.1.3. .... Asymmetric methods
 5.1.4. .... Formatting / display / navigation
 5.1.5. .... Help / PDF script
 5.1.6. .... Miscellaneous
 5.2. .... Enhancements from version 1.3.00 to 1.3.04
 5.3. .... Planned enhancements after version 1.3.04
 6. .... Possible areas for further development -- ideas, requests
 6.1. .... Analysis
 6.2. .... Algorithms / methods
 6.3. .... Internal interfaces
 6.4. .... User interfaces / visualizations
 6.5. .... Adding number theoretic functions
 6.6. .... Porting to Linux
 6.7. .... Meaningful tasks to make the new maintainer familiar with
 7. .... Brief history of the released main versions of CrypTool
 8. .... Feedback on errors
 9. .... Contact addresses
10. .... References / hints
10.1. .... Articles
10.1.1. .... c't 14/2001, pp 204-208
10.1.2. .... DuD October 2002
10.1.3. .... KES 2/2003 (May 2003)
10.1.4. .... 8th German IT-Security Congress of GISA (May 2003)
10.2. .... Et cetera
10.2.1. .... Wirtschaftswoche special issue
10.2.2. .... GISA citizen CD "Into the Internet - with Security"
10.2.3. .... Freeware projects Crank, CAP, CryptAid, etc
11. .... Appendix
11.1. .... Hints for using CrypTool on Linux with Wine



1. Brief description of the CrypTool package
   -----------------------------------------
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

Since beginning of 2003 the average download number of the CrypTool
package is about 1000 pieces per month -- with a growing trend.

The aim of CrypTool is to explain cryptographic mechanisms and to
demonstrate the use and the limitations of individual mechanisms.
CrypTool has implemented almost all state-of-the-art crypto
functions and allows you to learn about and use, modern and
classic cryptography within the same environment in a "playful"
manner.

CrypTool is used
- within companies to help raising the sensitivity for IT security
  (awareness) and for educational purposes,
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
This starting page is a good starting point, to become acquainted
with all essential features of CrypTool (using the links on this
starting page).

Please read the information and tips on the introductory help page
and then, in the CrypTool work area, open an unencrypted file
from the "examples" subdirectory.
You can now try out many of the CrypTool functions on this file.

To quickly get up to speed on CrypTool, we recommend that you
work through some of the examples (tutorials) provided within the
Online help facility (the examples are shown in the Help contents
overview under "Starting work with CrypTool").

If a menu item has no meaning to you or you don't know exactly what
to do within a dialogue window, please press F1. If the according
Online help isn't satisfactory please give us feedback.

We hope you enjoy trying out all the functionality within
CrypTool.


1.2. What do you get in the CrypTool package?
     ----------------------------------------
The CrypTool package includes the following four main parts:

(1) The program CrypTool
------------------------
Main part of the CrypTool package is the program CrypTool itself.
CrypTool is not intended as an application to be used as a 
Certification Authority (CA) or to encrypt or otherwise protect 
real-world data. It is a demonstration primarily used for 
training purposes:

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
  implemented is automated. 
  The analysis of modern techniques is limited so that CrypTool
  cannot be used as a hacker's tool.

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
from a password, and with this key any file content is
AES-encrypted.
This encryption tool can be called either as a Windows application
and as a command line tool (e.g. called from within a batch file).

(4) The story "The Dialogue of the Sisters" as PDF file
-------------------------------------------------------
The title-role sisters use a variant of the RSA algorithm, to
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
magazine c't, 25/1999. While c't published a slightly shortened
version you here get the original version.
The author owns all rights at this story. The maintainer of
CrypTool is allowed by the author only to distribute this story
together with the CrypTool package.

The companies Secude Ltd. and Shamus Software Ltd. (see above)
allowed us gratefully to use their cryptographic libraries.
These libraries distributed with CrypTool are not allowed to be
used in another context than CrypTool without contacting the
mentioned companies and asking for their current terms of licence.



1.4. New maintainer in the future - Road Map
     ---------------------------------------
CrypTool got an academic home as planned. There the further
development as open source is co-ordinated.

The current sponsors of CrypTool have been Deutsche Bank AG,
Secude Ltd. and FZI Karlsruhe. 1.3.04 is probably the last version,
released by Deutsche Bank as maintainer.

From October 2002 the rights on CrypTool moved to the chair 
"Security in Information Technology", faculty computer science
from Mrs. Prof. Dr. Claudia Eckert at the technical university of
Darmstadt, Germany.
They make the source code of CrypTool freely available to the 
Internet community as open source.

Homepage of CrypTool remains www.cryptool.com.

We would be very glad, if not only the old developers but many new
ones help to enhance the functionality and usability of CrypTool.
Ideas for further development can be found in chapter 5.3 and 6.



2. Limitations and requirements
   ----------------------------

2.1. Education, training and awareness software
     ------------------------------------------
As said above the development goal of CrypTool was not to be used
productively as a Certification Authority (CA).
It is a demonstration primarily for training and awareness purposes,
which can be used at once without any previous configuration work.

Therefore - in the opposite to productive CA applications - the 
CA key pair is contained directly within the software (source and
binary) and it is the same one in all the CrypTool versions right now.
Intentionally the PIN, protecting the CA-PSE (personal security
environment) is also very simple.
So by will the CA built in within CrypTool has not a key length adequate
for productive CAs (e.g. RSA with 1024 or 1536 bit), but only 512 bit.
The built in CA key is defined to be valid till 2010.

Please notice when creating user certificates with CrypTool, that each
CrypTool program contains a root CA with the same key pair. 
This means that everybody (!), who uses CrypTool, can sign user certificates
with this built-in CA.

Nevertheless all the algorithms implemented are according to international
standards and are working as "well" as in productive applications.


2.2. Win32 environment
     -----------------
CrypTool requires a Win32 environment, as provided under
Windows 95, Windows 98, Windows Me, Windows NT (from version 4.0),
Windows 2000 and Windows XP.

CrypTool also functions basically under FreeBSD/Linux with Wine
(with reservations on functionality and stability).
See appendix 11.1.


2.3. Installation under Windows 95
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


2.4. Interactive Online Help under Windows XP
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

Workaround with example: Indiv. Procedures \ RSA Demonstration
If the sub menu of "RSA Demonstration" pops up, but you want to
get help for the menu item "RSA Demonstration" itself, only
under Windows XP you have to close the sub menu of
"RSA-Demonstration" using the Esc or the arrow key, and then
press F1.


2.5. Support for different languages
     -------------------------------
Program,  help facility and the documentation are designed to run
in more than one language (currently in English and German).

For each supported language we deliver an extra setup (we gave up
our try, to deliver only one executable containing all languages,
because the automatic adjustment to the language which is set at
the user's PC did only work correctly under Windows NT 4.0, but
unfortunately not under Win9x).


2.6. Restrictions in libraries used
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



3. Installation / deinstallation / operating
   -----------------------------------------
To install CrypTool on your PC, copy the CrypTool setup executable
to a suitable place in your file system and double-click on it.
The default installation directory is "C:\Program Files\CrypTool".
The target directory can be altered in the installation routine.

If you already possess an earlier version of CrypTool, it is
recommended uninstalling the old version of CrypTool before
installing the new one, as otherwise it is possible that some
of the old files will not be overwritten. Please note:
- During de-installation not all of the directories and files in
  the program directories (normally "C:\Program Files\CrypTool")
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


3.1. Installation under multi-user operating systems
     -----------------------------------------------
In multi-user systems like Windows XP the administrator has full
access to the whole file system; the other users are normally
restricted.
If a normal user installs CrypTool he needs writing access for the 
directory in which CrypTool should be installed (e.g. for "C:\Program Files"),
if the sub-directory "CrypTool" does not already exist; or for the
directory "C:\Program Files\CrypTool", if this already exists. 
If he does not have these rights, the installation program stops.


3.2. Operating under multi-user operating systems
     --------------------------------------------
If the user wants to create (or change) files from within CrypTool in
multi-user systems like Windows XP, then he needs writing access for
the appropriate target directory (or for the appropriate files). 
If this does not work, the user normally gets a warning.
Writing access is explicitely necessary for:
- the default Windows directory for temporary files (for the *.cry files),
- the sub-directory "CrypTool\pse", where the created asymmetric keys
  and certificates are stored in, and
- the file CrypTool.ini, where the CrypTool program stores settings or
  adjustments, surviving the actual program session (persistence).
  CrypTool.ini is normally created within the Windows directory
  (e.g. C:\Windows) when the program CrypTool is started the first time.
  Please consider that, 
   - the adjustments can only be stored persistently, if the user
     has writing access for this file. 
   - even in multi-user systems like Windows XP only one (!) 
     CrypTool.ini file exists yet. 
  To achieve a higher flexibility with persistent adjustments a future
  version of CrypTool could
   - user-specifically write the persistent adjustments under Windows into 
     the registry instead of using an ini file.
   - offer another option for the user, whether the adjustment should be
     made for the current program session only or whether it should be
     persistent.



4. List of files
   -------------
The package is distributed as compressed, self extracting archive
in two language versions:

SetupCrypTool_1-3-04_en.exe   English language support only.
SetupCrypTool_1-3-04_de.exe   German language support only.

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
EC-Param.ini...... Initialisation file for public key procedures
                   based on elliptic curves.
secude.dll........ Library of cryptographic functions provided by
                   Secude GmbH.
ticket............ License for the Secude library.
libeay32.dll...... Library from OpenSSL 0.96.
irunin.*.......... These files are necessary for installation and
                   de-installation.

script-en.pdf..... A script on cryptography, prime numbers,
                   number theory and the mathematics behind
                   certain algorithms.
script-de.pdf..... The German version of script-en.pdf.
CrypToolPresentation_1_3_04_en.pdf.. Slides presentation
CrypToolPresentation_1_3_04_de.pdf.. German version of presentation.
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
        \Probetext-de.txt
        \psion-enc.hex
        \vernam.txt
        \Startbeispiel-de.txt
        \Startingexample-en.txt


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
Using the wide-spread tools MD5SUM and SHA1SUM you can check
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

You can calculate the hash values of "external" files, even
without loading them into CrypTool:
- menu Indiv. Procedures \ Hash \ Hash value of a file...
  (using MD5 or SHA1 as hash algorithm!)
- open the regarding file
- compare the shown hash value with the value within this
  README file.

Security reasons recommend to do the comparison for binary
files (EXE, DLL, PDF, ...), if you are not quite sure, that
your computer is untouched.



5. What's new in CrypTool till 1.3.04
   ----------------------------------

5.1. Enhancements from version 1.2.02 to 1.3.00
     ------------------------------------------
The following enhancements and bug fixes (listed till 5.1.6) have
been added for version 1.3.00 since CrypTool version 1.202:
- CrypTool is now fully available in both English and German
  language versions.
- All dialogues has been reviewed for consistency and clarity.
- The restrictions (maximum data volume 64 KB) which previously
  applied to Windows versions Win95 and Win98 are no longer
  applicable.
  Because of performance reasons CrypTool is customized in a way, that
  - from text files only 4 MB and
  - from binary files only 1 MB can be loaded.
  Using the AES tool files of any size can be encrypted.  
- The most recent configuration relating to an algorithm (such
  as the key or alphabet chosen) is stored internally within the
  program.

5.1.1. Classical methods
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

5.1.2. Symmetric methods
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

5.1.3. Asymmetric methods
       ------------------
+ Demo on number theory and RSA method:
  - prime number generation
  - factorization of numbers (in stages) and using several
    different methods
  - transparent use of the RSA cryptosystem (including for
    self-selected prime numbers).
    This means that you can e.g. duplicate "The Dialogue of
    the Sisters".

5.1.4. Formatting / display / navigation
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

5.1.5. Help / PDF script
       -----------------
+ Script extended to include an introduction to elementary number
  theory with a lot of examples

5.1.6. Miscellaneous
       -------------
+ PKCS#12 export and import of RSA- and DSA-PSEs including the
  keys stored within these PSEs.
+ New web site
  - Additional information: presentation in German and English.


5.2. Enhancements from version 1.3.00 to 1.3.04
     ------------------------------------------
The following topics have been improved/enhanced:

Source code:
============
+ Revision of the source code for the transmission to the new
  maintainer.
+ Further automation the process of generating the setup package.

Web page:
=========
+ It now contains the hash values of the downloadable files.
  So you can verify whether the integrity of the files on your
  computer is ok.
+ Added for 1.3.04:
  + Frame item, which points to a page with Web links
  + Frame item, which directly leads to the CrypTool presentation.


Documentation:
==============
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
  - new in 1.3.04: 
    current status of cryptanalysis of AES and RC5 and current
    proceedings regarding factorization (TWIRL) and
    number theory ("Primes in P") added.
+ Single CrypTool presentation for version 1.3.0x
  (no separation in features of 1.2.xx and new within 1.3.0x).
+ The Online help got further improvement and enhancements (e.g.
  for the new functions and addition of a time table about
  cryptography).
  In 1.3.04 e.g. topical information about PGP / GnuPP added.


Functionality:
==============
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
  rewritten and is no more compatible with its predecessors):
  - AES-Tool now offers complete functionality also when called
    from the command line.
    AES-Tool can be called by itself or within CrypTool via the menu
    item Crypt \ Symmetric \ AES (self extracting).
  - There is a customisation suggesting the file type (exe or aes).
  - Please note, that the output of the AES-Tool (even with file type
    "aes") is not completely identical with the output you get via the
    menu item Crypt \ Symmetric \ Rijndael (AES).
+ With the Hill cipher you can write the details of the used
  key matrix into a text file:
  - the currently used alphabet (chosen with Options \ Text Options)
  - the Hill key matrix, also coded in numbers
  - a sample encryption/decryption calculated in detail.
+ With the permutation cipher (double column transposition) now the
  inverse permutation key is also calculated and shown.
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
    -> how changes to a document change the hash value (hash
       demonstration) (sensitivity of hash algorithms).
+ The flow charts used for visualization show you, which steps
  can be taken in which order. If you click a step, where the
  prerequisites are not there, then a popup explains this in
  detail.
+ Step-by-step verification of an RSA-signature is now possible
  too (here the already existing masks are reused - similar as at
  the visualization of the hybrid decryption).
+ New menu item Starting Options.
+ Structure of Analysis became clearer.
+ When the user saves the window content to a file now a fitting
  file name is suggested:  Cry-<Method>-<Sourcefilename>.*
  For intentionally saved documents the window title contains
  the filename (instead of the description).

Completely new in 1.3.04 are:
-----------------------------
+ The CrypTool menu within the Windows Start\Program menu now
  also contains a hint to the readme file.
+ Within the dialogues for visualization the background was improved
  in order to be clearly visible even with new templates used with
  Windows XP.
+ Brute-force attacks at symmetric algorithms now allow to use
  more than 5 joker characters (20 bits)and the expected time 
  is presented.  Additionally the length of the here used entropy
  window can now be customized via analysis options.
+ Implementation of a high-performance search for hash collisions
  using the birthday paradox. This practically allows to show for
  concrete files how such an attack on hash or signature methods works.
+ Show/Visualize the Diffie-Hellman key exchange method.



5.3. Planned enhancements after version 1.3.04
     -----------------------------------------
Functionality:
+ A high performance pattern search to find either multiple patterns of
  any length within one file or to find any patterns in one file which
  also appear in another given file (mass search).
+ A pure command line version of AES-Tool to be also available for
  the operating systems OS/2 and Linux (aestool-os2; aestool-linux).
+ Visualize of challenge response methods.
+ Visualize of man-in-the-middle attacks.



6. Possible areas for further development -- ideas, requests
   ---------------------------------------------------------

6.1. Analysis
     --------
+ Offer a (good) analysis method for all encryption algorithms
  (at least for the classical one better than brute-force).
+ Implement analysis newly for
  - homophone encryption.
+ Analysis improvement (not sophisticated enough yet) of
  - monoalphabetic substitution (plus display of inverted digram
                                pairs and double characters),
  - Playfair encryption.
    Playfair: Pure C sources (Gunnar-Andresson) are available. 
              Because of restricted time these are not yet
              integrated into CrypTool.
+ Facilities for correcting individual characters in the analysis
  of XOR, ADD, Vigenere.
+ Display of second-, third-, etc. -best hit in XOR/ADD analysis
  (this could lead to a shorter key length).
+ Autocorrelation: execute more operations (XOR, ADD, ...) in the
  blocks prior to super imposition, if appropriate.
+ Make it possible to edit the homophone key (necessary for
  analysis of homophone encryption).
+ Floating entropy: automatic display of relevant places with
  high entropy.
+ Illustrate the Vigenere analysis more deeply:
  - enable to enter not only a fixed value for the key length,
    but also a range of values (e.g. "2-9"). Then show in the next
    dialog for each length the statistically most appropriate
    key. Clicking at the displayed key proceeds the according
    decryption. Clicking an additional button performs the
    decryptions for all displayed keys.
  - the Analysis Option "Show base ciphers" currently shows for
    each "column Caesar" the graphics correlation and histogram.
    Additionally the text for each column Caesar could be
    displayed.
+ Substitution analysis: the replaced letters in the dialog box
  are currently shown in capital letters: additionally display
  them in red to enhance readability.
+ Offer a view for any text files to show them in any given
  fixed block length: e.g. xxx xxx xxx  or  xxxxx xxxxx xxxxx ...
+ Attacking RSA encryption if the exponent is too small.
  RSA attack: Pure C++ sources and a diploma thesis in number
              theory (German) are available.


6.2. Algorithms / methods
     --------------------
+ Implement additional algorithms on each topic:
    - Encryption
       - ADFGVX as a classic procedure,
       - the RC5 and Ghost as symmetric procedures or
       - Rabin for the public key methods.
    - Hashes
       - SHA-xxx (http://csrc.nist.gov/publications/fips/fips180-2/fips180-2.pdf)
       - Tiger (http://www.cs.technion.ac.il/~biham/Reports/Tiger/)
    - Protocols / weaknesses in protocols.
  Remark: 
  ADFGVX: Sources in Basic including a user interface are available.
          Because of restricted time these are not yet transferred
          in C and integrated into CrypTool.
+ Implementation of an enhanced pattern search (with pre-given
  standardized and regular patterns and unknown but repeated
  patterns in a document, ...) by enhancing the dialogue used for
  mass comparison with known patterns from another file.
  The search could be enhanced by replacing.
+ Hill cipher
   - enable to transpose the key matrix
   - allow not only letters but also integers as input for the key matrix.
+ Generate cryptographically strong elliptic curves and use these
  to implement a cryptosystem based on elliptic curves.
  Here, one could take the cryptosystem developed by Menezes and
  Vanstone that was proposed by the authors in 1993:
  A. Menezes and S. Vanstone,
  "Elliptic curve cryptosystems and their implementation",
  Journal of Cryptology, 6 (1993), pp 209-224.
+ Because cryptographic structures and formats are often ASN.1
  encoded: integration of an ASN.1 decoding tool.
+ Random numbers:
  - Till now CrypTool concentrates on cryptographically strong
    pseudo number generators. Only the integrated Secude generator
    involves a "pure" random source. 
    Adding further "pure" random sources e.g. via mouse moves
    would be a good enhancement for CrypTool (Yarrow, PGP, ...). 
  - In Germany evaluations of deterministic random number generators
    are based on AIS 20 (since December 1999; AIS = Application
    Notes and Interpretation of the Scheme) and evaluations of 
    physical random number generators are based on AIS 31 (since
    September 2001). Especially AIS 31 has achieved great interest
    outside of Germany: this scheme evaluates not only the quality
    of the output like FIPS-140, but also the design of the generator
    itself !
    The documents AIS 20 and AIS 31 are both in English and German
    available at the web page of the German GISA:
    http://www.bsi.bund.de/zertifiz/zert/interpr/ais20e.pdf   
    http://www.bsi.bund.de/zertifiz/zert/interpr/ais31e.pdf   
    http://www.bsi.bund.de/zertifiz/zert/interpr/trngk31e.pdf 
    It would be a meaningful enhancement of CrypTool, to implement
    these requirements on evaluating random number generators 
    and also to visualize them.
+ Implement further standards and refer to all places, where
  they (e.g. PKCS#5) are used, from a menu and from the Online
  help (main task here is user interface and documentation).
+ Similar as CrypTool generates good keys from passwords (via PKCS#5)
  there should be a DOCUMENTED way on different methods how to
  generate good passwords.
+ Link to PGP:
  - Use PGP key within CrypTool:
    Idea: Open private key ring via password, analyse its structure,
    get the private key (PGP sources are available) and use this key,
    to decrypt PGP files with the algorithms implemented in CrypTool.
    This shows, that PGP only uses standard algorithms.


6.3. Internal interfaces
     -------------------
+ Summary of all display modules in a logical class tree.
+ According the default MFC procedure for different window types
  there are different menu trees in CrypTool for text and binary
  files. Because these 2 types are not very different, one could
  consider this only as a view of the same file and use the
  according functions for all window types (e.g. when encrypting
  a non-text file with Playfair one could ignore all letters 
  outside the alphabet) or one could dynamically enable/disable
  the menu items within a common menu structure. 
+ Rearrange the source to facilitate a separation of cryptographic
  functions and user interface (make ports and debugging easier).
+ Customisation wherever possible:
  option to set e.g. initial vector, number of rounds, key length,
  word size or the kind of padding (e.g. for the RC5-Algorithm
  see RFC2040).
  Then these additional customisations must become part of the
  format for the internal key storage.
+ Use a dictionary for all attacks, not just for substitution.
+ Libraries:
   - Support further libraries (Gnu, LiDIA, FLINT/C, ...)
   - Update the Miracl library to a newer version than 4.4.3., 
     if this improves the performance.
   - Update the Secude library to a newer version than 5.4.15C,
     if this improves the performance or if further methods are
     needed.
+  Write user-specific persistent information in the Windows registry
   instead of CrypTool.ini (see chapter 3.2. above).



6.4. User interfaces / visualizations
     --------------------------------
+ There are several dialogs within CrypTool where special input fields
  expect a special number format (decimal, hexadecimal, ...).
  The dialog "The RSA Cryptosystem" e.g. allows to enter the message
  as text (with an alphabet defined by you) or as a number (with 4
  different base numbers); compared with that the primes here can 
  only be entered as decimal numbers or as terms of decimal numbers.
  It would be useful if a calculator can be called from within 
  CrypTool as an a-modal window: it should accept terms with numbers 
  of any basis as input and it should show the result in several
  fields in parallel with different number bases. 
  The right output number representation could be transferred into
  the clipboard via button, or the mouse could drag the field content
  directly into the entry field in the CrypTool dialog box.
+ Offer a customizing feature to user, so that he can choose that
  all new windows appear within the main windows (as right now) or
  as "free" windows outside the main window.
  E.g. show single dialogue windows in an a-modal way (e.g. N-gram
  analysis, manual analysis, hybrid encryption demonstration).
  This allows that one can switch between the main window and
  the dialogue window without closing the dialogue window first
  (the burden is a more complex control mechanism, handling of
  multiple calls to the same dialogue, update after change of
  window focus or after changing the underlying original data
  within the main window, ...).
+ AES-Tool:
  - Porting it to Linux, ...
  - Integrate the PKCS#5 dialog to let the user enter letters in
    his used way: then set random values for salt and iteration
    counter and ask the user, to remember the generated hex value
    or store it securely. 
  Generally within CrypTool the keys of modern encryption methods
  intentionally must be typed in using the hex format. 
  We pedagogically did it by will, that everybody sees what type of
  key the different methods expect: classical methods expect a key
  built from the used alphabet, modern methods expect binary data of
  key length 56 bit till 256 bit.
  On the other hand people normally are used to type their input using
  all ASCII-keyboard-buttons. Within a productive application the key
  should NOT be built of ASCII-letters. If it is wished to use a ASCII
  password then it is better to generate a good key from the password. 
  Within CrypTool both requirements (key input via ASCII and showing,
  that good hex-keys are necessary) could be combined in the
  following way:
  Within the hexadecimal key input dialogs a button is added, calling
  the dialog "Indiv. Procedures \ Key Generation from Password". 
  The called dialog is already customized with the right key length
  and after pushing "Back" the generated key will be used as hex 
  input for the encryption method. In order to make this also work
  for AES-256, the hash function SHA-256 must be added to the 
  "Key Generation from Password"-dialog.
  Analog könnte man das AES-Tool so erweitern, dass der PKCS#5-Dialog
  eingebunden wird. Dadurch wäre die allgemeine Nutzung bequemer.
  Dann z.B. zufällige Werte für Salz und Iterationszahl bei jedem Aufruf,
  der nur eine ASCII-Passwort eingibt, voreinstellen, und den User
  auffordern, sich den Hexwert zu merken und/oder sicher aufzubewahren.
+ Make customizable by user how big the text and binary files can
  be loaded by CrypTool.
+ New magnification function in the display for graphics and/or
  display of co-ordinates of the current mouse pointer position.
+ Visualization:
  - Visualization of dependencies and workflows in protocols 
    (not only "simple" algorithms) is a meaningful enhancement.
  - Attacks on weak RSA keys are described in CrypTool's 
    online help at Help \ Szenarios \ RSA cryptosystem (demonstration), 
    under  "3.) Attack on the RSA algorithm":  saying
    factorisation of the moduls can break the method.
    This is implemented, but not visualized.
  - Attacks on other asymmetric methods are not implemented in
    CrypTool yet. To attack Diffie-Hellman, DSA or EC-DSA, one 
    has to calculate "discrete logarithms". After implementing
    this also could be visualized.


6.5. Adding number theoretic functions
     ---------------------------------
+ Enhance CrypTool as a front-end for number theoretic functions
  and values.


6.6. Porting to Linux
     ----------------
+ Porting to Linux - here a great demand is noticed.
   - a Secude and Miracl library is available.
   - Divide the complete task in meaningful parts:
       - graphical user interface
       - functionality implemented in pure C/C++
       - online help from Winhelp to HTML.
+ Porting to Java (a Secude library is available for this).


6.7. Meaningful tasks to make the new maintainer familiar with
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
  c) create command line interface (best after within the source
     pure crypto functionality is separated from user-interaction)
     so test cases can be read from a file without using
     dialog boxes (without user interface), solved and the result
     again written to a file:
     -> automatic comparison of the solution possible
     -> new version can be tested easier.



7. Brief history of the released main versions of CrypTool
   -------------------------------------------------------

Version   Date		Size of Windows-Setup	Released by
			English	    German
1.0.01    Oct. 1999	-	    1.3 MB	DB
1.1.01    May  2000	-	    2.3 MB	DB
1.2.00    Aug. 2000	-	    2.8 MB	DB
1.2.02    Dec. 2000	-	    3.2 MB	DB
1.3.00    Jan. 2002	4.7 MB	    4.9 MB	DB
1.3.02    June 2002	6.4 MB	    6.9 MB	DB
1.3.03    Sep. 2002	6.5 MB	    6.9 MB	DB
1.3.04    June 2003	7.6 MB	    8,1 MB	DB

Remark about the current versions:
1.3.02    Many new functions compared to 1.3.00
1.3.03    Many minor bug fixes and documentation improvements.
1.3.04    Some new functionality (see chap. 5.2), some minor bug
          fixes (crash in analysis of Playfair, N-gram, RSA), and
          major documentation improvements and enhancements.



8. Feedback on errors (bugs)
   -------------------------
If you have any problems or find any errors, please send a
description of the problem by e-mail to
- joerg-cornelius.schneider@db.com  or
- bernhard.esslinger@db.com / besslinger@web.de or
- the mailing list: cryptool-list@sec.informatik.tu-darmstadt.de

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
- cryptool-list@sec.informatik.tu-darmstadt.de
- peer.wichmann@web.de



10. References / hints
    ------------------

10.1. Articles
      --------
10.1.1. c't 14/2001, pp 204-208
        -----------------------
A 5-page article on CrypTool was published in July 2001 in this
renowned and widely circulated German computer magazine.

10.1.2. DuD October 2002
        ----------------
A 4-page article on CrypTool was published under the title
"CrypTool - spielerischer Einstieg in klassische und moderne
Kryptographie. Neue Version - fundierte Awareness in Deutsch
und Englisch" in the German technical journal "DuD Datenschutz
und Datensicherheit" (Privacy and Data Protection) in the
issue 10/2002.

10.1.3. KES 2/2003 (May 2003)
        ---------------------
A 6-page article on CrypTool was published under the title
"(Ver)Schlüsselerlebnisse - CrypTool unterstützt Verständnis für
die Grundlagen der Internetsicherheit" in the German technical
journal "KES - Zeitschrift für Informations-Sicherheit" (journal
for information security) in the issue 2/2003.
We plan to publish an English version too.

10.1.4. Proceedings 8th German IT-Security Congress of GISA (May 2003)
        --------------------------------------------------------------
The presentation "Awareness in der Informationsgesellschaft: CrypTool
- Kryptographie spielerisch verstehen" was given by Mr Koy at the GISA
(German Information Security Agency) congress 2003 in Bonn.
The article for the congress is within the proceedings, "IT-Sicherheit
im verteilten Chaos", at page 485 - 500.


10.2. Et cetera
      ---------
10.2.1. Wirtschaftswoche special issue
        ------------------------------
In the special issue "Cryptography" of the magazine Wirtschaftswoche
(Sept. 2000) there was a competition entitled "Crack the text!".
Please see http://www.wiwo.de/wiwowwwangebot/fn/ww/sfn/buildww/cn/
cn_artikel/id/62633!100301/SH/0/depot/0/bt/1/index.html.
If you followed the tips provided, you could be able to crack the
task using CrypTool in a few mouse clicks.

10.2.2. GISA citizen CD "Into the Internet - with Security"
        ---------------------------------------------------
The German Information Security Agency (GISA) and the German
ministry for internal affairs published in spring 2002 a CD
in order to inform citizens how to use computers and Internet
and how one can securely use the Internet.
CrypTool is included on this CD to raise the knowledge about
cryptographic security functions.
More than 600,000 copies of this CD have been produced.
The content of this CD is the basic for the GISA security portal
"for inexperienced Internet users" (http://www.bsi-fuer-buerger.de).

10.2.3. Freeware projects Crank, Griffon, CAP, CryptAid, etc
        ----------------------------------------------------
Available with source code are:
- http://freshmeat.net/projects/crank/
  Crank was initiated in January 2001 by Matthew Russell and is
  released under the GNU general public license, the GPL.
  In the Crank project the idea is that a program with a graphical
  user interface will be created under Linux which will enable
  classical crypto algorithms to be broken almost entirely
  automatically.
  Initially the focus is on the analysis of monoalphabetic
  substitution ciphers and the development of generic and flexible
  analysis tools.
  The current version 0.2.1 was released in August 2001.
  On the project web page there are also some very interesting links
  on classical cryptanalysis.

- http://freshmeat.net/projects/griffon/
  Griffon was started in 2000 by Adrian Mulvaney and is
  released under the GNU general public license, the GPL.
  Griffon is a GTK+ GUI cryptanalysis package for pre-digital ciphers.
  Monoalphabetic transposition and substitution ciphers and Playfair
  are covered. The program includes a customizable frequency count.
  The current version 1.0 was released in November 2000.

The only other "useful" programs known to us, which combine
cryptography and cryptanalysis (under a graphical user interface) but
where the source code is probably not public, are:
- CAP from Dr. Richard Spillman
  The current version 4 was released in November(?) 2002.
  http://www.cs.plu.edu/courses/privacy/index.htm
- CryptAid from David Lovelock
  (development probably stopped already in 1997)
  http://archives.math.utk.edu/software/msdos/miscellaneous/cryptaid/.html
- the Visual Basic program "Cryptological Mathematics" from Prof. R.E. Lewand
  (vivid presentation of some number theoretic functions, functions for
  encryption and encryption; no functions for cryptanalysis; software to
  accompany his book)
  http://faculty.goucher.edu/blewand/cryptomath/companion_software.htm
- John Trafton's student cryptography project in Java:
  (single statistical functions and classical encryption methods;
  available since December 2002)
  http://phoenix.goucher.edu/~jtrafton/Crypto.


If we are missing something here or are incorrect anyhow, please feel
free to inform us, so that we can complete or correct the list.

We explicitly want to state, that we would welcome very much if the
efforts made for these single programs could be combined into one
merged new program. We are very keen about any co-operation!!




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

