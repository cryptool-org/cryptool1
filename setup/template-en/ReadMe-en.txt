==================================================================
    CrypTool, Version 1.4.00 for Win32, July 2006
    (c) Deutsche Bank AG, Frankfurt/Main
    (c) University of Siegen and Darmstadt
    (c) 1998-2006
    Bernhard Esslinger
    $Id$
==================================================================

                       Contents

 1. .... Brief description of the CrypTool package
 1.1. .... How to start - An introduction to CrypTool
 1.2. .... What do you get in the CrypTool package?
 1.3. .... Acknowledgements
 1.4. .... New maintainer in the future - Roadmap
 2. .... Limitations and requirements
 2.1. .... Education, training and awareness software
 2.2. .... Win32 environment
 2.3. .... Installation under Windows 95
 2.4. .... Interactive online help under Windows XP
 2.5. .... Support for different languages
 2.6. .... Restrictions in libraries used
 2.7. .... Using certificates created with older CrypTool versions
 3. .... Installation / de-installation / operating
 3.1. .... Installation and further usage of keys of previous versions
 3.2. .... Installation under multi-user operating systems
 3.3. .... De-installation of CrypTool
 3.4. .... Operating under multi-user operating systems
 4. .... List of delivered files
 4.1. .... Checking the integrity of downloaded files
 5. .... What's new in CrypTool 1.4.00
 5.1. .... What does CrypTool offer in general
 5.2. .... What's new in version 1.4.00
 6. .... Possible areas for further development -- ideas, requests
 6.1. .... Functionality: Algorithms / methods
 6.2. .... Functionality: Analysis
 6.3. .... Internal interfaces / editors
 6.4. .... User interface / visualizations
 6.5. .... Adding number theoretic functions
 6.6. .... Porting to Linux, Java and VS2005/WPF
 6.7. .... Meaningful tasks to make the new maintainer familiar with
 7. .... Brief history of the released main versions of CrypTool
 8. .... Feedback on errors
 9. .... Contact addresses
10. .... References / hints
10.1. .... Articles about CrypTool
10.2. .... Further references
10.3. .... Further freeware projects (Crank, CAP, CryptoStudio, etc)
10.4. .... Awards
11. .... Appendix
11.1. .... Hints for using CrypTool on Linux with Wine



1. Brief description of the CrypTool package
   -----------------------------------------
This ReadMe file is part of the free distribution of CrypTool,
a program by means of which cryptographic functions can be easily
demonstrated and known and unknown algorithms can be analyzed.

Every part of the program comes with extensive online help, which
can be understood without deep knowledge in cryptography,
therefore no user manual on how to use CrypTool is provided.

CrypTool is completely available in English and German.

It is required that the user is able to use typical applications
under Windows.

The current version of CrypTool can be found at these addresses:
                http://www.CrypTool.org
                http://www.CrypTool.com
                http://www.CrypTool.de

Since beginning of 2006 the average download number of the CrypTool
package is about 2000 packages per month -- with a growing trend
(more than 1/3 of the current downloads request the English version).

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
non-liability for any damage arising from the use of CrypTool. These
conditions are described e.g. at the web page, during the installation
process and at the introduction page of the online help for CrypTool.

Previous users of CrypTool may find especially chapter 5 (What's new)
and chapter 6 (Further development) of this ReadMe interesting.

We welcome very much everybody willing to further develop CrypTool
or to give feedback. We are also glad about hints telling us about
papers (diploma or doctor thesis or seminar home works), which could
be integrated into CrypTool. 
Contacts: Please see chapter 8 and 9 below.


1.1. How to start - An introduction to CrypTool
     ------------------------------------------
When you start up CrypTool, the CrypTool work area starts up
along with a small welcome screen which appears in the
foreground. If you press F1 in the welcome screen, the starting page
of the online help comes up too.

This starting page is a good starting point, to become acquainted
with all essential features of CrypTool (using the links on this
starting page). Please read the information and the hints on the
introductory help page.

To quickly get up to speed on CrypTool, we recommend that you
work through some of the examples (tutorials) provided within the
online help facility (the examples are shown in the online help 
contents overview under "Starting work with CrypTool").

The easiest way to try out many of the CrypTool functions is with
the file "Startingexample-en.txt", which is open by default in the
CrypTool work area. But you also can open any unencrypted file from the
"examples" subdirectory or any other file.

If a menu item has no meaning to you or you don't know exactly what
to do within a dialog window, please press F1. If the according
online help isn't satisfactory please give us feedback.

You can find a 1-page overview over all menus in CrypTool (menu tree)
within the included PDF script (appendix A1).

We hope you enjoy learning about cryptography and trying out all the
functionality within CrypTool.


1.2. What do you get in the CrypTool package?
     ----------------------------------------
The CrypTool package includes the following four main parts:

(1) The program CrypTool
------------------------
Main part of the CrypTool package is the program CrypTool itself.
CrypTool is a demonstration primarily used for training purposes:

- To this end, CrypTool contains an extensive collection of
  cryptographic algorithms and protocols which are well documented
  and partly visualized.
  In this way, CrypTool is very well suited for training and
  teaching employees awareness of the importance of IT security.

- Most of the cryptographic basic algorithms used are taken from:
  - the industry-proven Secude library (http://www.secude.com/),
  - the Miracl library (http://indigo.ie/~mscott/),
  - the OpenSSL library (http://www.openssl.org/),
  - the NTL number theory library of Victor Shoup
    (http://www.shoup.net/ntl/) and
  - the GMP library for arbitrary precision arithmetic
    (http://www.swox.com/gmp/).

  The currently used version of the included libraries can be seen
  within the "About CrypTool" dialog (see help menu).

  In this way, CrypTool is also an outstanding reference
  implementation.

- The cryptanalysis of most of the classical algorithms
  implemented is automated. 
  The analysis of modern techniques is limited so that CrypTool
  is not a hacker's tool.

CrypTool is not intended as an application to be used as a 
Certification Authority (CA) or to encrypt or otherwise protect 
real-world data.


(2) Documentation
-----------------
A comprehensive documentation is provided. This also consists of 
four parts:
a) ReadMe file (this file)
b) online help
   - context-specific help in order to use the program and further
     information about individual topics and principles,
   - demos and sample scenarios (here you learn to know single
     procedures step-by-step).
c) script on the subject of cryptography (attached as a PDF file)
d) presentation, which shows at some slides the possibilities of
   CrypTool (also attached as PDF file).


(3) Self-contained programs
---------------------------
All these programs can be called from within CrypTool or directly as
a stand-alone program.
a) The program AES-Tool (developed within the CrypTool project)
   CrypTool contains a special program for the creation of self-
   extracting executable files which can also be used independently.
   In this program a session key is generated from a password, and with
   this key any file's content can be AES-encrypted.
   This encryption tool can be called both as a Windows application
   and as a command line tool (e.g. called from within a batch file).
b) The educational game "Number Shark" (by the CrypTool project)
   This game helps pupils to get acquainted with divisors and prime
   factors.
c) The animation program ANIMAL (see http://www.animal.ahrgr.de)
   This program is maintained by Dr. Roessling at the Technical
   University of Darmstadt. It allows to specify and model the single
   steps of algorithms or the components of data structures with as
   much detail as desired, and run these steps forwards, backwards, or 
   automatically). Animations can be created with the Animal system 
   using a GUI, a script language or a Java API.


(4) Stories dealing with number theory and cryptography 
-------------------------------------------------------
There are two stories attached as PDF file.
- In "The Dialogue of the Sisters" the title-role sisters use a 
  variant of the RSA algorithm, in order to communicate securely.
- In "The Chinese Labyrinth" Marco Polo has to solve number theoretic
  problems to become a minister of the Great Khan.

All the single files included in the package are listed within
chapter 4 (see below in this ReadMe file).



1.3. Acknowledgements
     ----------------
A big number of individuals have contributed to CrypTool, many of
them in their free time as well (some are listed in the dialog
box you get after double clicking the "About" dialog box).
We are extremely grateful to them.

Sponsors are e.g. Deutsche Bank AG and the Technical University
of Darmstadt.

Dr. Carsten Elsner allowed us to include both his stories.
The author owns all rights at these stories. The maintainer of
CrypTool is allowed by the author only to distribute this story
together with the CrypTool package.
The German version of the story "The Dialogue of the Sisters"
was first published in the computer magazine c't, 25/1999. While 
c't published a slightly shortened version you here get the original
version.

The companies Secude IT Security GmbH and Shamus Software Ltd. (see
above) allowed us gratefully to use their cryptographic libraries.
These libraries distributed with CrypTool are not allowed to be
used in another context than CrypTool without contacting the
mentioned companies and asking for their current terms of licence.

Also we want to thank the open source developers, who delivered code
(e.g. the libraries OpenSSL und NTL) or whose code encouraged us.


1.4. Maintainer, Hosting and Roadmap
     -------------------------------
CrypTool got an academic home as planned:
From October 2002 the chair "Security in Information Technology", 
faculty computer science from Mrs. Prof. Dr. Claudia Eckert at the
Technical University of Darmstadt, Germany hosts the English and 
German web page of CrypTool and the Subversion repository system
for the program sources.

The CrypTool developer group around Bernhard Esslinger stay in being
the maintainer: This means they take care about the source code, 
they publish CrypTool as open source and freeware, and they
co-ordinate the further development. Current steps of the roadmap
will be published at the web page.

Homepage of CrypTool remains www.cryptool.com (www.cryptool.org).

We would be very glad, if not only the present developers but many new
ones help to enhance the functionality and usability of CrypTool.
Ideas for further development can be found in chapter 6.

Also very welcome are ideas and information, how CrypTool is used in
lectures, school and education, so that we can help to share this
information.



2. Limitations and requirements
   ----------------------------

2.1. Education, training and awareness software
     ------------------------------------------
CrypTool is a demonstration primarily for training and awareness
purposes, which is intended to be used at once without any previous
configuration work.

Therefore the development goal of CrypTool was not to be used
productively for encryption or as a Certification Authority (CA) --
despite the functions are correctly implemented in CrypTool.

For instance - contrary to productive CA applications - the CA key pair
is contained directly within the software (source and binary) and
it is protected with a very simple PIN for the CA-PSE (personal 
security environment).

The root key of the CA built in CrypTool 1.4.00 has a length of 2048
bit and it is valid for 20 years (July 6th, 2006 - July 6th, 2026).
Certificates issued with the root key of older CrypTool versions 
(1.3.05 and older) cannot be imported in version 1.4.00.

Please notice when creating user certificates with CrypTool, that each
CrypTool program contains a root CA with the same key pair. 
This means that everybody (!), who uses CrypTool, can sign user 
certificates with this built-in CA.

Professional PKI software like the OpenXPKI, Entrust, the Secude CA or
the Microsoft CA additionally manage the whole certificate life-cycle,
offer CRL handling, take care for unique serial numbers and use
defined registration processes.

Nevertheless all the algorithms implemented in CrypTool are according
to international standards and are working as "well" as in productive 
applications.


2.2. Win32 environment
     -----------------
CrypTool requires a Win32 environment, as provided under
Windows 95, Windows 98, Windows Me, Windows NT (from version 4.0),
Windows 2000 and Windows XP.

Since version 1.4.00 CrypTool doesn't need administrator access 
rights - neither for the installation nor for the usage. Persistent
data is written only into the CrypTool directory, into the Windows 
directory for temporary files (TEMP directory) or into the user 
specific part of the Windows registry (Details see chapter 3).

Remark: Where the TEMP directory of Windows is, can be seen by
entering %TEMP% in the Windows Explorer. The value can also be seen
and adjusted under Windows XP via "System --> System properties 
--> Tab Enhanced --> Environment variables".

CrypTool also works basically under FreeBSD/Linux with Wine
(with reservations on functionality and stability).
See appendix 11.1.

To port CrypTool to Linux or redesign it with Java or prepare it for
Windows Vista/Avalon are future goals (see chapter 6).


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
extract the files. Follow the instructions in the readme.txt file
contained there in the package in order to install the missing file.


2.4. Interactive online help under Windows XP
     ----------------------------------------
Using Windows XP there is a special case where it is not
possible to get the online help via F1: Only menu entries with
submenus are affected. The problem only occurs while the submenu
is displayed. In this case pressing F1 has no effect.

Usually you can also help in CrypTool also for selected menu items
which itself have submenus -- independent of whether the submenu 
is popped up or not.
Under Windows XP you only get the online help, if the submenu
is not popped up.
With other versions of Windows this doesn't matter - there it is
only important, that the menu has the focus.

Workaround with example: 
Select the menu item "Indiv. Procedures \ RSA Cryptosystem":
If the submenu of "RSA Cryptosystem" pops up, but you want to
get help for the menu item "RSA Cryptosystem" itself, only
under Windows XP you have to close the submenu of
"RSA Cryptosystem" using the Esc or the left arrow key, and then
press F1.


2.5. Support for different languages
     -------------------------------
Program, help facility and the documentation are designed to run
in more than one language (currently in English and German).

For each supported language we deliver an extra setup (we gave up
our try, to deliver only one executable containing all languages,
because the automatic adjustment to the language which is set at
the user's PC did only work correctly under Windows NT 4.0, but
unfortunately not under Win9x).


2.6. Restrictions
     ------------
- In order to demonstrate the RSA cryptosystem and to factorize
  integers CrypTool uses the long integer arithmetic of the Miracl
  library from Shamus Software Ltd. We restricted the integer bit
  length up to 8192.

- From binary files "only" the first almost 2 GB can be loaded into
  the hex editor (< 0x7ffff000 = 2.147.479.552 Bytes).
 
- Text files can be loaded in unlimited size by the text editor
  (if you got enough resources on your pc).

- For performance reasons it was decided that CrypTool limits the
  document size when performing n-gram analysis:
   - for binary data up to 64 kByte and
   - for text data up to 256 kByte.
  Files opened, which are longer, are truncated -- only in this
  special analysis -- to the maximal length.

- Hash values of external files, which are not loaded into the internal
  editor, can be calculated for files of any size. 

- With the AES-Tool you can encrypt and archive files with a
  maximum size of 4 GB (as long as compiled with VS2003).

  Please keep in mind, that the output of the stand-alone AES-Tool
  is not identical with the output you get within CrypTool, using
  the menu item sequence "Crypt/Decrypt \ Symmetric (modern) \ 
  Rijndael (AES)"  (even if you create a file with has the extension
  "aes"). CrypTool itself currently uses a fixed IV (0), which is
  not stored. AES-Tool uses a random IV, which is appended together 
  with the file name to the end of the encrypted data.


2.7. Using certificates created with older CrypTool versions
     -------------------------------------------------------
If you want to keep on using certificates, created with older versions
of CrypTool, you can do so:
  a) for RSA and DSA keys:
     Export the PSEs with the old CrypTool into a PKCS#12 format and
     load these files into the new CrypTool.
  b) for ECC keys:
     Here it is enough, to copy the according files
     (e.g. [da][db][EC-prime239v1][1131039030][d] )
     from the old CrypTool\pse directory into the new one.



3. Installation / de-installation / operating
   -----------------------------------------

3.1. Installation and further usage of keys of previous versions
     -----------------------------------------------------------
To install CrypTool on your PC, copy the CrypTool setup executable
to a suitable place in the file system and double-click on it.
The default target directory is "C:\Program Files\CrypTool".
The target directory can be altered in the installation routine.

If you already possess an earlier version of CrypTool, it is
recommended uninstalling the old version of CrypTool before
installing the new one, as otherwise it is possible that some
of the old files will not be overwritten. Please note:
- During de-installation not all of the directories and files in
  the program directories (normally "C:\Program Files\CrypTool")
  may be deleted. If so, delete these manually.
- De-installation will delete all user generated asymmetric keys.
  If you intend to further use those keys also in the newly installed 
  version of CrypTool, then perform the following steps. Copy the
  entire pse\ directory in order to protect these keys. De-install
  CrypTool and install the new version. Finally copy the saved
  pse\ directory to the installation folder. Also see chapter 2.7.
  Alternatively you can export/import RSA and DSA PSEs using the 
  PKCS#12 format.

Please note that it might be necessary to adjust the access
permissions if multiple users want to share one CrypTool
installation. In that case set the access rights in the
sub-trees "pse\" and "pse\pseca\" to full access for each user.

The "pse\" sub-tree should not be manually altered as, if the
structure becomes inconsistent, it may be necessary to completely
reinstall CrypTool in order to use the certificate based methods.


3.2. Installation under multi-user operating systems
     -----------------------------------------------
In multi-user systems like Windows XP the administrator has full
access to the whole file system; the other users are normally
restricted.

If a normal user installs CrypTool he needs write access for the 
directory in which CrypTool should be installed:
- e.g. for the directory %ProgramFiles% (normally C:\Program Files),
  if the sub-directory "CrypTool" does not already exist; or
- for the directory  %ProgramFiles%\CrypTool (C:\Program Files\CrypTool),
  if this already exists.
If he does not have these rights, the installation program stops.

Therefore as a normal user without admin access rights, you should specify
as target directory a so called "local directory" (instead of "C:\Programme").
"Local" and accessible for any user could be e.g.: %ALLUSERSPROFILE%
(The default of the English Windows XP is: 
"C:\Documents and Settings\All Users").

If you install CrypTool without administrator rights and you also have no
write access to %ALLUSERSPROFILE%\Start Menu, then the CrypTool specific
entries are missing in the start menu of WXP ("Start \ All Programms").
But every user can add these entries manually.

Remark: In the same way as with %TEMP%, you can see, where these directories
are on your disk by entering in the Windows Explorer %ALLUSERSPROFILE% or
%userprofile%.


3.3. De-installation of CrypTool
     ---------------------------
To de-install use the "Start" menu entry in the windows task bar.
Go for "All programs" \ "CrypTool".
Click "Uninstall CrypTool".


3.4. Operating under multi-user operating systems
     --------------------------------------------
From Version 1.4.00 all user-specific parameters are stored in the 
local registry (e.g. the files lastly opened): So no ini-file in the
Windows directory is needed any more and operating for multi-users
is supported. 

If the user wants to create (or change) files from within CrypTool in
multi-user systems like Windows XP, then he needs writing access for
the appropriate target directory (or for the appropriate files). 
If this does not work, the user normally gets a warning.
Writing access is explicitly necessary for only two directories:
- the default Windows directory for temporary files (TEMP) for the
  cry*.* files,
- the sub-directory "CrypTool\pse", where the created asymmetric keys
  and certificates are stored in (see chapter 3 above).



4. List of delivered files
   -----------------------
The package is distributed as a compressed, self extracting archive
in two different language versions:

SetupCrypTool_1_4_00_en.exe   English language support only.
SetupCrypTool_1_4_00_de.exe   German language support only.

The archives contain the following files:

ReadMe-en.txt .... This brief instruction (English).
ReadMe-de.txt .... This brief instruction (German).

md5sum.txt ....... File which contains the MD5 hash values of all files
                   within the CrypTool package.
sha1sum.txt ...... SHA-1 hash values of all these files.

CrypTool.exe ..... The executable e-learning program (English and German).
aestool.exe ...... A program which encrypts files into
                   self-extracting programs. To decrypt the files,
                   the correct password must be entered.
CrypTool-en.chm .. HTML help archive containing the CrypTool online help
                   system in English.
CrypTool-de.chm .. The German version of "CrypTool-en.chm".

EC-Param.ini ..... Initialisation file for public key procedures
                   based on elliptic curves.
secude.dll ....... Library of cryptographic functions provided by
                   Secude IT Security GmbH.
ticket ........... License for the Secude library.
libxml2.dll ...... Is used by the secude.dll.
secidea.dll ...... Is used by the secude.dll for IDEA encryption.
srndmskb.dll ..... Used by secude.dll for collecting entropy when
                   initializing the Secude random number generator.
db.dll ........... Is used by the secude.dll.
libeay32.dll ..... Library from OpenSSL.
SciLexer.dll ..... Library with the routines for the Scintilla text
                   editor.
TEST-Param.ini ... Initialisation file for random number tests. 
irunin.* ......... These files are necessary for installation and
                   de-installation.

NumberShark.exe .. The executable program of the educational game "NumberShark".
Zahlenhai.exe .... The German version of "NumberShark.exe".
NumberShark_en.chm HTML help archive for tne NumberShark online help (English).
NumberShark_de.chm The German version of "NumberShark_en.chm".
GameData.txt ..... First high-scores for the NumberShark game.

script-en.pdf .... A script on cryptography, prime numbers,
                   elementary number theory and the mathematics
                   behind certain algorithms.
script-de.pdf .... The German version of script-en.pdf.

CrypToolPresentation_1_4_00_en.pdf .. Slides presentation
CrypToolPresentation_1_4_00_de.pdf .. German version of presentation.

DialogueSisters.pdf ... Fantasy story by Dr. Elsner describing a
                        variant of the RSA cryptosystem.
DialogSchwestern.pdf .. German version of DialogueSisters.pdf.
ChinLab-en.pdf.pdf .. Story by Dr. Elsner about basic number theory
                      problems assigned to Marco Polo by the Great
                      Khan.
ChinLab-de.pdf.pdf .. German version of ChinLab-en.pdf.


examples\ ........ This directory contains various sample files
                   which are used in the scenarios provided in the
                   program. Files ending with the suffix ".txt"
                   are text files. All other files are binary.
                   Files whose names are in the format
		   "XX-enc-YY.*" are encrypted files. Please do
		   not change these files.

examples\CrypTool.bmp
        \CrypTool-en.txt
        \CrypTool-de.txt
        \CrypTool.bmp
        \Playfair-enc-de.txt
        \Probetext-de.txt
        \psion-enc.hex
        \vernam.txt
        \Startingexample-en.txt
        \Startbeispiel-de.txt
        \original.txt ..... "Harmless" sample for the hash collision
                            demonstration.
        \Original.txt ..... German version of original.txt
        \fake.txt ......... "Dangerous" sample for the hash collision
                            demonstration.
        \Faelschung.txt ... German version of fake.txt
        \letterFromAliceToBob-DECRYPTED-en.txt .. Sample files for the
        \letterFromAliceToBob-DECRYPTED-de.txt .. demonstration of the
        \letterFromAliceToBob-ENCRYPTED-en.hex .. side-channel attack on
        \letterFromAliceToBob-ENCRYPTED-de.hex .. hybrid encryption.


references\ ...... This directory contains text files in the
                   languages German, English, French, Spanish and
                   Latin. These files are routinely used as
                   references for the analysis of encrypted
                   texts. These files are write-protected.

references\deutsch.txt   // Extract from the German value-added tax law
          \english.txt   // Extract from Agenda 21 [UN document]
          \genesis-de.txt  // Book of Genesis in the
          \genesis-en.txt  // languages German, English
          \genesis-es.txt  // French, Spanish and Latin.
          \genesis-fr.txt  // The 2-letter codes are according
          \genesis-la.txt  // to the ISO 639 language codes.


animal\ .......... This directory contains files, necessary for the
                   animation program ANIMAL.

animal\Animal-2.0.2.jar
      \animal.bat
      \animal.properties
      \AnimalResources
      \AnimalResources.de
      \AnimalResources.de_DE
      \AnimalResources.en
      \AnimalResources.en_US
      \AnimalResources.es
      \AnimalResources.es_SP
      \animList.txt
      \anmTypes.dat
      \default.properties
      \Editors.dat
      \elementDefinitions
      \exporters.dat
      \figTypes.dat
      \handlers.dat
      \imgTypes.dat
      \importers.dat
      \languages.dat
      \languages.default
      \parser.config
      \txtTypes.dat
      \types.dat

animal\anims ..... This directory contains AML files. 
                   Each AML file contains the description of an
                   animation for an encryption method.

animal\anims\caesar_de.aml
            \caesar_en.aml
            \des_de.aml
            \des_en.aml
            \nihilist_de.aml
            \nihilist_en.aml
            \vigenere_de.aml
            \vigenere_en.aml


pse\ ............. This directory and its subdirectory pseca\ are
                   used to store (asymmetric) keys and
                   certificates that have been generated.

pse\[SideChannelAttack][Bob][RSA-512][1152179494][PIN=1234].pse

pse\pseca\calog    These files are necessary for the administration of 
         \CA_exts  the key database:
         \cert.dir
         \cert.pag
         \CRL_exts
         \crls.dir
         \crls.pag
         \user.dir
         \user.pag


While CrypTool is running, the following files are generated and
managed:
cry*.* ........... CrypTool writes temporary files to the \temp
                   directory (file names begin with cry*.*).
                   There are the following file extensions:
                   txt -> text file view
                   hex -> hexadecimal (binary) view
                   plt -> diagram/plot view (histogram, autocorrelation)
                   ogl -> OpenGL graphics view
                   org -> copy of an original file after file open
                   tmp -> temporary file for intermediate results



4.1. Checking the integrity of downloaded files
     ------------------------------------------
The integrity of files can be verified using hash values.
Hash values are like fingerprints -- with a small information base you
are able to identify a much larger object.

There are two ways how files from the CrypTool project can get on your
computer: via direct download or by unpacking a downloaded file:
a) Downloadable files:
   At the homepage of CrypTool www.cryptool.org you can find the
   hash values of all files directly downloadable from the English
   Web page within the files md5sum.txt and sha1sum.txt.
   If you newly calculate the hash of a downloaded file and then
   compare it with the values at the CrypTool homepage, you can see, 
   whether you got an unchanged copy of the original file or not.
   If the hash values are different you should download the file
   again and eventually try to find the reason, why you had a
   modified file at your computer.
b) Additionally you can check the files WITHIN the downloaded setup
   package:
   The hash values of these files are also within the files md5sum.txt
   and sha1sum.txt.

In order to do the integrity check of the downloaded or unpacked files
you can use the wide-spread tools MD5SUM and SHA1SUM.

Alternatively you can use the program CrypTool itself:
  The hash values of "external" files can be calculated, even
  without loading them into CrypTool:
  - click the menu "Indiv. Procedures \ Hash \ Hash Value of a File",
  - open the regarding file,
  - choose MD5 or SHA1 as hash algorithm,
  - compare the shown hash value with the value within md5sum.txt or
    sha1sum.txt.

Security reasons recommend to do the comparison for binary
files (EXE, DLL, PDF, ...), if you are not quite sure, that
your computer is untouched.



5. What's new in CrypTool 1.4.00
   -----------------------------

Chapter 5 lists the enhancements and bug fixes in CrypTool 1.4.00,
which have been added since CrypTool 1.3.05.

5.1. What does CrypTool offer in general
     -----------------------------------
Here first of all the general properties of CrypTool:
- E-learning program around the topic cryptography and cryptanalysis.
- Cryptography and cryptanalysis under a common graphical user 
  interface.
- CrypTool is fully available in both English and German.
- Classical encryption methods, and for them either the manual
  cryptanalysis is supported or an automatic analysis is offered.
- Modern symmetric encryption methods, accompanied by brute-force
  analysis
  (The brute-force attack on symmetric algorithms allows to define
   joker characters and the expected elapsed time is displayed. 
   Additionally you can customize the width of the entropy field
   used for this kind of analysis within the analysis options).
- Modern crypto methods and protocols (hash, RSA, ECC, digital
  signature, hybrid encryption, PKCS#5, shared secret, ...) and partly
  attacks against it (birthday attack, side-channel attack, 
  lattice-base reduction).
- Calculate hash values and demonstrate its sensitivity.
- Random number generators and statistical analysis for (random)
  data (e.g. FIPS-140-1).
- Demonstration concerning number theory and the RSA cryptosystem:
  - Generate and test primes.
  - Factorize numbers (step-by-step) with different methods
    (the different methods run in parallel threads).
  - Make the RSA cryptosystem understandable and use it:
     - Generate RSA keys (also with primes of your own choice).
     - Encrypt/decrypt with RSA.
     - Generate RSA signatures and validate these.
     - Attack the RSA cryptosystem.
- Export and import RSA and DSA-PSEs with the keys stored in there
  via PKCS#12.
- Visualization via flow process charts (e.g. the Diffie-Hellman
  key exchange) or with ANIMAL.
- The modern methods are implemented according to international
  standards (reference implementation).
- The self-contained program AES-Tool can create self-extracting
  programs. So you can encrypt any file <4 GB with the AES algorithm,
  protected by a password (entered as a hexadecimal key).
  Full functionality also when calling from the command line.
- The last adjustment for a method (parameter, key or alphabet) is
  stored within the program. A stored key can be retrieved via an
  insert-icon for any single key.
- Exhaustive documentation (online help, script).
- Web page with the hash values of all downloadable CrypTool files:
  So you can check the integrity of the files of the CrypTool package
  stored on your computer.
- CrypTool is used world-wide in schools, universities, agencies and
  companies.

You can get a good overview of what CrypTool offers
- at the attached Powerpoint presentation
   (title: "Cryptography with CrypTool") and
- at the web site of CrypTool 
   (use the item "CT Introduction" within the left frame).


5.2. What's new in version 1.4.00
     ----------------------------

a) Developer-relevant changes (more technically oriented):

- The sources of CrypTool 1.4.00 can be downloaded also from the
  web page without registration.

- Details about compilation, linking and about a consistent development
  can be found in the sources in the file "readme-source".

- The sources now can be compiled with Microsoft development 
  environment Visual Studio 2003 (VC++ v7.1).
  The support of VC++ v6.0 was stopped (besides some incompatibilities
  between the compilers the main problem was, that the GMP library
  could not be compiled with it).

  There is already a source branch in our Subversion system, which can
  be compiled with VS2005 (VC++ v8.0). This will be officially 
  supported after 1.4.00.

- After so far including the libraries from Secude and Miracl,
  now also the libraries of OpenSSL, NTL and GMP are used.

- The old editors for text and binary data have been replaced by
  open-source editors with better functionality and their code was
  at some places enhanced: So loading is faster, the used storage
  is smaller and bigger files can be loaded.

  * Hex editor / Hex control / HexView:
    Link: http://www.codeguru.com/Cpp/controls/controls/article.php/c5287
    -> Added: Insertion, simultaneous marking of chars in hex and ASCII.

  * Text editor:
    Link: http://scintilla.sourceforge.net/ScintillaDownload.html

  Now you also can view files, which have non-printable characters,
  in text mode.

  With the menu item "View" \ "Font" you can adjust in a fast way
  meaningful sizes and the font type (mono-space or proportional).
  So "Courier 10" e.g. is good, to have a look at the output of the
  ADFGVX cipher.

  Search and Replace in the text editor has been enhanced with regular
  expressions.
  In the hexadecimal editor currently no search is available.

- The menu structure is arranged more clearly and contains more
  entries.

  The menu structure now is permanently visible: Items which cannot
  be clicked for special document types are dynamically made grey,
  but they are no more taken away (this was a frequent request from
  users).

- For each window you now can call a dialog which shows all relevant
  properties of the document.

- The online help now is HTML format (instead as in Winhelp format).

- All persistent data is now stored within the user local part of
  the registry (no more INI file): So CrypTool can be used without
  administrator access rights and different users at the same pc can
  have different settings.

- With the ANIMAL software system workflows can be visualized:
  - Link: http://www.animal.ahrgr.de
  - Further examples within the ANIMAL repository: 
    http://www.animal.ahrgr.de/animations.php3?tool=Animal&lang=en


b) Changes within the user documentation:

- The Online help is improved and enhanced.

- Within the script: minor bug-fixes, new chapter about paper&pencil
  methods, information about movies and fiction, where cryptography
  is used, and many updates.

- Another fantasy story by Dr. Carsten Elsner: Within "The Chinese
  Labyrinth" Marco Polo has to solve number theoretic problems.

- Updated and enhanced presentation (almost 90 pages now).



c) New functionality:

- The dialogs for key entry for Caesar and mono-alphabetic substitution
  are more detailed and contain as option the special cases ROT13 and
  Atbash.

- Solitaire as an example for a solid paper&pencil encryption method
  plus an analysis of it.

- Implementation and analysis of ADFGVX as an example of a cascading
  cipher.
  Here you also have the option to enter the password of the substitution
  matrix as a string.

- A improved analysis for mono-alphabetic substitution.

- Implementation of the base64- and the uu-encoding.

- Within the hash demo, which shows the sensitivity of hash algorithms
  now hash functions available in CrypTool can be used (before the
  dialog offered only MD2, MD5 und SHA-1).

- Demonstration for different ways of authentication in the net
  (Visualisation of challenge response methods):
  * from UID/PW and One-Time-Password
  * over (unidirectional) challenge response (symmetric + asymmetric)
  * to asymmetric mutual authentication.
  * The user interactively can control, what a attacker could do
    (get the computer under control, create or separate connections,
     eavesdrop).
  * Experience: only the mutual asymmetric authentication is secure
    against man-in-the-middle attacks.

- Demonstration for a side-channel attack against a typical hybrid
  encryption protocol: If the implementation is not comprehensive,
  but formally correct, as happened in reality, the attacker can very
  efficiently calculate the used session key of an eavesdropped message
  by sending protocol-appropriate requests to the server.

- Three attacks against RSA, based on lattice reduction. They work,
  if special preconditions are given:
  * either a part of one of the two factors of N is known 
    ("Factoring with a Hint"),
  * or a part of the cleartext of an eavesdropped encrypted message
    is known and e is small ("Attack on Stereotyped Messages"),
  * or if d is too small compared to N, N can be factorized 
    ("Attack on Small Secret Keys").
  This implementation was done within a thesis, which can be delivered
  via email (this thesis only exists in the German language).

- Implementation of MACs (combination of hashes and symmetric methods
  to authenticate messages). 
  Hashes have been already used in CrypTool within PKCS#5 or digital
  signatures.

- Three applications based on the Chinese remainder theorem:
  * Solving a system of linear modular congruencies using the solar
    system as an example.
  * Showing how you can calculate (add, subtract or multiply) with
    modular remainders (residues) instead of the (bigger) actual
    numbers.
  * Showing the shared secret method (this is an electronic equivalent
    to the vault mechanism where e.g. at least 3 key-owners must 
    cooperate to open it, but 5 different keys are there).

- Visualize algorithms (Caesar, Vigenère, Nihilist and DES) using the
  animation software ANIMAL 2.0 (Java application: allows one to
  specify and model the single steps of algorithms or the components
  of data structures with as much detail as desired, and run these
  steps forwards, backwards, or automatically). Animations can be
  created with the Animal system using a GUI, a script language or a
  Java API.

- 3-D visualisation of big sets of random numbers with the rendering
  engine from OpenQVis (http://openqvis.sourceforge.net/).

- Addendum to the Secude cryptographic random number generator which now
  also allows to gather entropy by mouse moves and keyboard entries.
  This is the default now, because it shows, that you need a random
  source in order to get good random data.

- The AES-Tool now can encrypt and decrypt files till 5 GB (the old
  limit was 256 MB).

- The Shared Secret method from Shamir has been implemented with
  many options.

- You can generate asymmetric keys (for RSA and DSA) now with a bit
  length till 8192 bits (CT 1.3.05 supported only 1024 bit).

- Another prime number test was added: the deterministic method AKS.

- Integration of an educational game for pupils, which helps them to
  get an easy understanding of divisors and primes ("The Number Shark").



6. Possible areas for further development -- ideas, requests
   ---------------------------------------------------------

6.1. Functionality: Algorithms / methods
     -----------------------------------
- Implement additional algorithms on each topic:
    * Encryption:
       - Turning grille (Fleissner) as classic procedure.
       - Symmetric procedures:
         Camellia (RFC3713), RC5 and Gost (http://vipul.net/gost).
       - Public key methods: McEliece and Rabin.
       - Implementation of the NTRU encryption system.
       - Demonstration of visual cryptography.
    * Hashes:
       - SHA-256, SHA-384, SHA-512
         http://csrc.nist.gov/publications/fips/fips180-2/fips180-2.pdf
       - Tiger (http://www.cs.technion.ac.il/~biham/Reports/Tiger/)
    * Protocols / weaknesses in protocols:
       - Visualisation of man-in-the-middle attacks.
       - Blind Signatures.
       - Electronic Voting.

- Offer fast selection between different encryption methods using a
  dialog box instead of using menus (and making all parameters of these
  algorithms customizable).

- Generate cryptographically strong elliptic curves and use these
  to implement a cryptosystem based on elliptic curves.
  Here, one could take the cryptosystem developed by Menezes and
  Vanstone that was proposed by the authors in 1993:
  A. Menezes and S. Vanstone,
  "Elliptic curve cryptosystems and their implementation",
  Journal of Cryptology, 6 (1993), pp 209-224.
  Desirable could be:
    * A ECC demo, which shows how points on a elliptic curve can be
      added or multiplied in discrete and in real fields (as java 
      application).
    * The implementation of the ECC-AES hybrid encryption (in C++) using
      the crypto library of cryptovision.

- Hill cipher
   - enable to transpose the key matrix
   - allow not only letters but also integers as input for the 
     key matrix.

- Because cryptographic structures and formats are often ASN.1
  encoded: Integration of an ASN.1 decoding tool.

- Random numbers:
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

- Implement further standards and refer to all places, where
  they (e.g. PKCS#5) are used, from a menu and from the online
  help (main task here is user interface and documentation).

- Reveal the link between CrypTool (PKCS#12) and PGP by enabling the
  use of PGP keys within CrypTool.
    Idea: Open private key ring via a given password, analyse its 
    structure, get the private key (PGP sources are available) and 
    use this key, to decrypt PGP files with the algorithms implemented
    in CrypTool. This shows, that PGP also only uses standard algorithms.

- Usage of CrypTool as a demonstrator for XML signatures.

- Visualize the password quality with a password quality meter.

- Build a command line version of the AES-Tool (also for other
  operating systems).


6.2. Functionality: Analysis
     -----------------------
- It would be especially desirable if analysis and its visualization
  could be enhanced.

- Offering a (good) analysis for all encryption methods (which is at
  least for the classic methods better than brute-force). 

- Visualize current hash attacks (create postscript documents according
  to Lucks or PDF documents according to BSI with the same hash value)
  and explain the  scenarios.

- Analysis to be newly implemented for:
   * homophone encryption
   * permutations/transpositions
   * Playfair encryption
      - pure C sources from Gunnar-Andresson are available. 

- Analysis to be improved for:
   * mono-alphabetic substitution
      - explicitly show mutually inverted digrams like "th"/"ht" and
        double-characters like "tt".
      - Show the characters which have been substituted not only 
        capitalized but also in red to enhance readability.
   * Use world lists (dictionary) for all attacks, not only for the
     substitution.

- Mass pattern search: Implementation of an enhanced high performance
  pattern search for pre-given standardized and regular patterns of any
  size (e.g. in order to find multiple patterns in one file which are 
  also there in another file), or which searches for unknown but
  repeated patterns in a document.
  The search could be enhanced by additionally offering replacing.

- Search for patters using norms (i.e. "together" = 12341546).
  C sources are available.

- Facilities for correcting individual characters in the analysis
  of XOR, ADD, Vigenère. Ignorance of non-encrypted areas.

- Display of second-, third-, etc. -best hit in XOR/ADD analysis
  (this could lead to a shorter key length).

- Autocorrelation: Execute further operations (XOR, ADD, ...) in the
  blocks prior to super imposition, if appropriate.

- Make it possible to edit the homophone key (necessary for the
  analysis of homophone encryption).

- Floating entropy: automatic display of relevant places with
  high entropy.

- Illustrate the Vigenère analysis more deeply:
  - Enable to enter not only a fixed value for the key length,
    but also a range of values (e.g. "2-9"). Then show in the next
    dialog for each length the statistically most appropriate
    key. Eventually show the top-10 most likely keys for a given length.
    Clicking at the displayed key proceeds the according
    decryption. Clicking an additional button performs the
    decryptions for all displayed keys.
  - The analysis option "Show base ciphers" currently shows for
    each "column Caesar" the graphics correlation and histogram.
    Additionally the text for each column Caesar could be
    displayed.

- Timing Attack on RSA / Advantages of blinding.

- Attack on the WEP protocol.

- Attack on symmetric encryption methods, where you have the flexibility
  to reduce the parameters.


6.3. Internal interfaces / editors
     -----------------------------
- Summary of all display modules in a logical class tree.

- Offer a view for any text file to show them in any given fixed
  block length: e.g. formats xxx xxx xxx  or  xxxxx xxxxx xxxxx ...

- Rearrange the source to facilitate a separation of cryptographic
  functions from the user interface (make ports and debugging easier).

- Enable customisation wherever possible:
  Offer an option to set e.g. initial vector, number of rounds, key
  length, word size or the kind of padding (e.g. for the RC5 algorithm,
  see RFC2040).
  Then these additional customisations must become part of the
  format for the internal key storage.

- Libraries:
   - Support further libraries (LiDIA, FLINT/C, Wei Dai's Crypto++, ...)

- Extend existing limitations of the N-Gram analysis concerning
  the file size (evtl. give user feedback, that a high amount of time
  is necessary)(see 5.2.a above).


6.4. User interface / visualizations
     -------------------------------
- There are several dialogs within CrypTool where special input fields
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

- Offer a customizing feature to the user, so that he can choose that
  all new windows appear within the main windows (as right now) or
  as "free" (modal or a-modal) windows outside the main window.
  E.g. show single dialogue windows in an a-modal way (e.g. N-gram
  analysis, manual analysis, hybrid encryption demonstration).
  This allows that one can switch between the main window and
  the dialogue window without closing the dialogue window first
  (the burden is a more complex control mechanism, handling of
  multiple calls to the same dialogue, update after change of
  window focus or after changing the underlying original data
  within the main window, ...).

- AES-Tool:
  - Porting it to Linux, ...
  - Integrate the PKCS#5 dialog to let the user enter letters in
    his used way: then set random values for salt and iteration
    counter and ask the user, to remember the generated hex value
    or store it securely. 
  Generally within CrypTool the keys of modern encryption methods
  intentionally must be typed in using the hex format. 
  We pedagogically did it by will, that everybody sees what type of
  key the different methods expect: classical methods expect a key
  built from the used alphabet, modern symmetric methods expect 
  binary data of key length 56 bit till 256 bit.
  On the other hand people normally are used to type their input using
  all ASCII keyboard buttons. Within a productive application the key
  should NOT be built of ASCII-letters. If it is wished to use a ASCII
  password then it is better to generate a good key from the password. 
  Within CrypTool both requirements (key input via ASCII and showing,
  that good hex-keys are necessary) could be combined in the
  following way:
  Within the hexadecimal key input dialogs a button should be added,
  calling the dialog "Indiv. Procedures \ Hash \ Key Generation from
  Password (PKCS#5)". 
  The called dialog then is already customized with the right key length
  and after pushing "Back" the generated key will be used as hex 
  input for the encryption method. In order to make this also work
  for AES-256, the hash function SHA-256 must be added to the 
  "Key Generation from Password"-dialog.

- Make customizable by the user how big the part of text and binary
  files can be which CrypTool will load.

- New magnification function in the display for graphics and/or
  display of co-ordinates of the current mouse pointer position.

- Visualization:
   - Visualization of dependencies and workflows in protocols 
     (not only "simple" algorithms) is a meaningful enhancement.
   - Attacks on weak RSA keys are described in CrypTool's 
     online help at Help \ Scenarios \ RSA cryptosystem (demonstration),
     under  "3.) Attack on the RSA algorithm":  saying
     factorisation of the modules can break the method.
     This is implemented, but not visualized.
   - Attacks on other asymmetric methods are not implemented in
     CrypTool yet. To attack Diffie-Hellman, DSA or EC-DSA, one 
     has to calculate "discrete logarithms". After implementing
     this it also could be visualized.


6.5. Adding number theoretic functions
     ---------------------------------
- Enhance CrypTool as a front-end for number theoretic functions
  and values.


6.6. Porting to Linux, Java and VS2005/WPF
     -------------------------------------
- Porting to Linux using GCC 4.x and Qt 4.x.
   - The libraries from Secude, Miracl, NTL, OpenSSL and GMP are
     available.
   - Divide the complete task in meaningful parts:
       - graphical user interface: This is the main task.
       - functionality implemented in pure C/C++: ok
       - online help in HTML: ok.

- Completely new designed CrypTool in Java (JCrypTool):
   - A major sub project, which does the port
   - A Secude library and Bouncy Castle are available.
   - Usage of Eclipe, SWT and Jigloo for development.
   - Plug-in based architecture.
   - Further developers for this project are very welcome
     (The current developers use a wiki for their communication and
     Subversion for source code version management).

- Porting to Windows Vista using Visual Studio 2005 and .NET.
  Usage of the new GUI API Windows Presentation Foundation (WPF)
  to create multi media GUIs.
   - Usage of the .NET framework (no MFC any more).
   - Usage of VS2005 (no longer VS2003 and no more VC++6.0),
     if the whole project can be built with the free-of-charge
     express edition for C++.



6.7. Meaningful tasks to make the new maintainer familiar with
     ---------------------------------------------------------
- Integrate the RC5 algorithms as described above, in order to
  see all places where to enhance the sources (function itself,
  options, menus + status line info, online help, ...).

- Offer all kind of transpositions and superpositions for the
  content of text windows in an easy-to-use dialogue window.

- Pattern matching dialogs.

- Create a test suite with examples and solutions, in order to
  automate testing and to make sure, that program changes do not
  negatively influence old and running functionality:
  a) interface, to load test cases manually into the dialog boxes
  b) interface, to load test cases from a file into the different
     dialog boxes.
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

Version   Date		Size of Windows Setup		Released by
			English	    	German
1.0.01    Oct. 1999	 -		 1.3 MB 	DB
1.1.01    May  2000	 -		 2.3 MB		DB
1.2.00    Aug. 2000	 -		 2.8 MB		DB
1.2.02    Dec. 2000	 -		 3.2 MB		DB
1.3.00    Jan. 2002	 4.7 MB		 4.9 MB		DB
1.3.02    June 2002	 6.4 MB		 6.9 MB		DB
1.3.03    Sep. 2002	 6.5 MB		 6.9 MB		DB
1.3.04    July 2003	 8.6 MB		 8,1 MB		DB
1.3.05    Aug. 2003	 8.6 MB		 8,1 MB		DB
1.4.00    July 2006	18,2 MB		18,4 MB		DB

Remarks about the versions:
1.3.02    Many new functions compared to 1.3.00.
1.3.03    Many minor bug fixes and documentation improvements.
1.3.04    Some new functionality, some minor bug fixes (crash in 
          analysis of Playfair, N-gram, RSA), and major documentation
          improvements and enhancements (online help, script).
1.3.05    Some minor bug fixes.
1.4.00 Beta10  Dec. 2005  First public beta of version 1.4.00.
1.4.00 Beta12  Mar. 2006  Second public beta of version 1.4.00.
1.4.00 Beta14  July 2006  Third public beta of version 1.4.00.
1.4.00    Many new functions compared to 1.3.05.



8. Feedback on errors (bugs)
   -------------------------
If you have any problems or find any errors, please do not hesitate to
send a description of the problem by e-mail to one of the persons or
to the mailing list (see chapter 9 below).

We would be very grateful for suggestions of any kind regarding
CrypTool and we'll be helpful whenever our time allows.

We would also be interested to hear how and where you use
CrypTool.



9. Contact addresses
   -----------------
- joerg-cornelius.schneider@db.com
- esslinger@fb5.uni-siegen.de
- henrik.koy@db.com
- cryptool-list@sec.informatik.tu-darmstadt.de



10. References / Hints / Awards
    ---------------------------

10.1. Articles about CrypTool
      -----------------------
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
[The Title means "Experience cryptography -- CrypTool improves the
understanding of information security].

10.1.4. Proceedings 8th German IT-Security Congress of GISA (May 2003)
        --------------------------------------------------------------
The presentation "Awareness in der Informationsgesellschaft: CrypTool
- Kryptographie spielerisch verstehen" was given by Mr Koy at the GISA
(German Information Security Agency) congress 2003 in Bonn.
The article for the congress is within the proceedings, "IT-Sicherheit
im verteilten Chaos", at page 485 - 500.


10.2. Further references
      ------------------
10.2.1. Wirtschaftswoche special issue
        ------------------------------
In the special issue "Cryptography" of the magazine Wirtschaftswoche
(Sept. 2000) there was a competition entitled "Crack the text!".
Please see http://www.wiwo.de/wiwowwwangebot/fn/ww/sfn/buildww/cn/
cn_artikel/id/62633!100301/SH/0/depot/0/bt/1/index.html.
If you followed the hints provided, you could be able to crack the
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



10.2.3. Mentions on different web sites
        -------------------------------

a) After writing "The Code Book" Simon Singh collected on his web site
   http://www.simonsingh.net/ a lot of material about cryptography, its
   history and its education.

   Within his newsletter (http://www.simonsingh.net/Newsletter_13.html) 
   from Feb 11, 2004 he recommends CrypTool as one of four worldwide
   crypto tutorials:
   - www.simonsingh.net/The_Black_Chamber/home.html
   - www.cryptoclub.math.uic.edu/indexmain.html
   - www.antilles.k12.vi.us/math/cryptotut/home.htm
   - www.cryptool.com


b) The Professional Security Testers Warehouse (PST) had a submission by
   Jaganmohan Kataru (CISSP, MCSE) in the Security News Dashboard at Sep
   21, 2005 with the post subject: "eLearning Program for Cryptology":
   http://www.professionalsecuritytesters.org/modules.php?name=Forums&
   file=viewtopic&t=34

   Similar post was at the "CISSP, SSCP, CISM, CISA, ISSPCS, and SANS
   GIAC GCFW Open Study Guides Web site" for Cryptography
   http://www.cccure.org/modules.php?name=News&new_topic=51  with the
   title "Cryptool A great tool to learn more about cryptography",
   posted on Thursday, September 22, 2005.


c) Wikipedia:
   - English:
     - http://en.wikipedia.org/wiki/Cryptool
     - http://en.wikipedia.org/wiki/Cryptography
     - http://en.wikipedia.org/wiki/Topics_in_Cryptography
   - German:
     - http://de.wikipedia.org/wiki/CrypTool
     - http://de.wikipedia.org/wiki/Kryptographie
     - http://de.wikipedia.org/wiki/Wikipedia:WikiProjekt_Kryptologie
  - French:
     - fr.wikipedia.org/wiki/Cryptool

d) A small selection of further pages:
   http://www.pki-page.org/
   http://www.bsi-fuer-buerger.de/toolbox/tb08.htm
   http://www.itejas.com/index.php/2005/09/22/learn_cryptography_with_cryptool
   http://www.privacycom.net/pwatch/viewArticle.php?article=48
   https://www.a-i3.org/content/view/415/28/
   http://www.fh-lueneburg.de/mathe-lehramt/krypto/krypto.htm
   http://www.kryptographiespielplatz.de/
   http://www.tinohempel.de/info/info/kryptografie/index.htm
   http://www.edsb.ch/e/themen/sicherheit/tipps/kap4.htm
   http://www.roehri.ch/~sr/links/crypto.html
   ...



10.3. Further freeware projects (Crank, CAP, CryptoStudio, etc)
      ---------------------------------------------------------

Available with complete source code are:

- http://freshmeat.net/projects/crank/
  Crank was initiated in January 2001 by Matthew Russell and is
  released under the GNU general public license, the GPL.
  In the Crank project the idea is that a program with a graphical
  user interface will be created under Linux which will enable
  classical crypto algorithms to be broken almost entirely
  automatically.
  Initially the focus is on the analysis of mono-alphabetic
  substitution ciphers and the development of generic and flexible
  analysis tools.
  The current version 0.2.1 was released in August 2001.
  On the project web page there are also some very interesting links
  on classical cryptanalysis.

- http://freshmeat.net/projects/griffon/
  Griffon was started in 2000 by Adrian Mulvaney and is
  released under the GNU general public license, the GPL.
  Griffon is a GTK+ GUI cryptanalysis package for pre-digital ciphers.
  Mono-alphabetic transposition and substitution ciphers and Playfair
  are covered. The program includes a customizable frequency count.
  The current version 1.0 was released in November 2000.

- http://www.kryptosproject.org/
  Kryptos is educational software for teaching cryptography with a
  static GUI, but many modern algorithms. It is build within an open
  source project at the George Mason University.
  It has no cryptanalysis functions.
  The current version Kryptos 2.0 was released in April 2005.

- http://cryptostudio.sourceforge.net/
  CryptoStudio from Prof. Marco Russo
  The current version 1.0 was releases in June 2005 and is available
  in English and Italian.
  It is a GUI (looking like Microsoft's Visual Studio) offering 
  functions of the general purpose cryptographic open source library
  OpenSSL and using its command line tools. So the web page states: 
  "Many of the CryptoStudio functionalities are a mere GUI wrapper of
  OpenSSL tools, intended to make those tools available also to 
  uninitiated users".
  Users can also find utilities for file encryption, basic s/mime mail
  management etc., but no cryptanalysis.


The only other programs known to us, which usefully combine
cryptography and cryptanalysis (under a graphical user interface),
but where the source code is probably not public, are:

- CAP from Dr. Richard Spillman
  The current version 4.1 was released in 2004 for download.
  This software exists in English only.
  From the programs we know, CAP and CrypTool have the most
  exhaustive functions for cryptanalysis.
  http://www.cs.plu.edu/courses/privacy/index.htm

- CryptAid from David Lovelock
  (development probably stopped already in 1997)
  http://archives.math.utk.edu/software/msdos/miscellaneous/cryptaid/.html

- The Visual Basic program "Cryptological Mathematics" from 
  Prof. R.E. Lewand (vivid presentation of some number theoretic 
  functions, functions for encryption and encryption; no functions
  for cryptanalysis; software to accompany his book; probably from the
  year 2001)
  http://faculty.goucher.edu/blewand/cryptomath/companion_software.htm

- John Trafton's student cryptography project in Java:
  (single statistical functions and classical encryption methods;
  available since December 2002)
  http://phoenix.goucher.edu/~jtrafton/Crypto.

- Wilhelm M. Plotz' Java application "CipherClerk"
  (encryption and decryption with many classic algorithms;
  last update in 2003)
  http://members.aon.at/cipherclerk/

- CryptoBench - GUI around Wei Dai's Crypto++ library
  Compact and clearly arranged GUI implemented around Wei Dai's 
  Crypto++ library (no cryptanalysis).
  The current version 1.0.1 of the CryptoBench exists since 2004.
  Wei Dai's Crypto++ library is open source, the GUI of CryptoBench is 
  freeware, but not open source.
  http://www.addario.org/cryptobench/


If we are missing something here or are incorrect anyhow, please feel
free to inform us, so that we can complete or correct the list.

We explicitly want to state, that we would welcome very much if the
efforts made for these single programs could be combined into one
merged new program. We are very keen about any co-operation!!


10.4. Awards
      ------
In general the biggest award for us is, if CrypTool is broadly used in
education and training. Additinally we are glad getting many positive
feedback.

CrypTool was honored with the following awards (see web page):

- TeleTrusT Special Award
  The TeleTrusT Special Award for education about cryptography and 
  promoting acceptance, awareness and understanding of cryptographic 
  methods was conferred at the ISSE conference.

- European Information Security Award 2004
  The CrypTool project was a finalist in the European Information
  Security Award (EISA 2004) in the category education and training,
  hosted by the RSA conference Europe.

- IT Security Award NRW 2004
  CrypTool and the Institute of Information Systems (University of
  Siegen) received the IT Security Award NRW in the category education
  (eLearning / knowledge transfer about cryptology).





11. Appendix
    --------

11.1. Hints for using CrypTool on Linux with Wine
11.1.1. ... Installing CrypTool
11.1.2. ... Wine configuration
11.1.3. ... Running CrypTool


11.1. Hints for using CrypTool on Linux with Wine
      -------------------------------------------
These hints are based on tests with Wine 0.9.9.

We do not recommend to use CrypTool under Wine, because too many things
there only work partly. A full featured CrypTool version for Linux can
be expected if the port using GCC and Qt4 is successful (see chapter
6.6). Any developers who can contribute to this sub project are most 
welcome.

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
* The online help cannot be invoked with F1.
  Use the following line to display the online help:

  $ wine winhlp32 CrypTool.hlp


