==================================================================
    CrypTool, Version 1.4.31 for Win32, May 2017
    
CrypTool v1 (CT1) is a free, international
e-learning program for cryptography and cryptanalysis.

    (c) Contributors
        including Deutsche Bank AG, Frankfurt/Main, and the Universities
        of Siegen, Darmstadt, Bochum, Duisburg-Essen, and Kassel.
        1998-2017
    Freeware and Open Source according to the Apache License 2.0
    www.cryptool.org
    Prof. Bernhard Esslinger
    $Id$
==================================================================

 1. ... Brief description of the CT1 package
 1.1. ... How to start using CT1 -- An introduction to CT1
 1.2. ... Components of the CT1 distribution
 1.3. ... Acknowledgments
 1.4. ... Maintainer and hosting
 2. ... What does CT1 offer in detail
 2.1. ... What can you do with CT1
 2.2. ... Where do you find the source code
 2.3. ... Where can you get another overview about CT1
 2.4. ... What's new in version 1.4.20 / 1.4.21
 2.5. ... What's new in version 1.4.30
 2.6. ... What's new in version 1.4.31
 3. ... Limitations and requirements
 3.1. ... Scope of this education, training and awareness software
 3.2. ... Win32 environment, rights for installation and usage, Java runtime
 3.3. ... Interactive online help under Windows XP
 3.4. ... Support for different languages
 3.5. ... Restrictions / features / hints & tips
 3.6. ... Using certificates and keys created with older CT1 versions
 4. ... Installation / de-installation / key usage / operating
 4.1. ... Installation
 4.2. ... De-installation of CT1
 4.3. ... Repeated usage of keys
 4.3.1. ... Keys of previous versions
 4.3.2. ... Keys stored in the files of the PSE directory
 4.4. ... Installation under multi-user operating systems
 4.5. ... Operating under multi-user operating systems
 4.6. ... Installation on a network drive --> Online help problem
 5. ... List of delivered files
 5.1. ... Checking the integrity of downloaded files
 6. ... Brief history of the released main versions of CT1
 7. ... Feedback and contact addresses
 8. ... References / hints / awards
 8.1. ... Articles about CrypTool
 8.2. ... Further references
 8.3. ... Further freeware projects (Crank, CAP, CryptoStudio, SageMath, etc)
 8.4. ... Awards
A. ... Appendix
A.1. .... Roadmap after CT 1.4.31
A.2. .... Successor projects using Java/Eclipse and C#/.NET
A.3. .... Possible areas for further development -- Future features, ideas
A.4. .... Using CT1 on Linux


Abbreviations used:
CT   CrypTool (for instance used to characterize the whole CT project)
CT1  CrypTool 1 = CrypTool version 1 (the version delivered with this readme)
CT2  CrypTool 2 = CrypTool version 2 (uses .NET; runs under Win32)
JCT  JCrypTool  = Java-CrypTool (runs under Win32, Linux and MacOS)


1. Brief description of the CT1 package
   ------------------------------------
This ReadMe file is part of the distribution of the program CrypTool 1 (CT1).
CrypTool is a free and open-source program by means of which cryptographic
functions can be easily learned and demonstrated, and known and unknown
algorithms can be analyzed.

Already in the ancient ages such methods have been used to assure the privacy
of messages. Current methods are based on modern mathematics and
offer besides encryption also to check integrity, to build digital
signatures, secure authentication and many more. CrypTool supports
both the execution and the analysis of such methods.

CT1 has been developed since 1998 in the CrypTool project. Currently more
than 70 persons world-wide are working voluntarily in the CrypTool project.

Every part of the program CT1 comes with extensive online help, which
can be understood without deep knowledge in cryptography.

CT1 is available in 7 languages (language abbreviations by ISO 639-1):
- English (EN),
- German (DE),
- French (FR),
- Greek (EL),
- Polish (PL),
- Serbian (SR), and
- Spanish (ES).

In all language versions the program has the same full functionality --
translated and localized are the GUI (menus, dialogs, etc.) of the programs
CrypTool, AES-Tool, and Number Shark, and the installer program (setup).

Here is a list of the remaining components of the CT1 package, which
could not be localized yet for all language versions:
                        DE     EN     EL    ES    FR    PL    SR
Online help (html)      yes    yes    no    no    no    no    no
Readme file (txt)       yes    yes    no    no    no    no    no
CT book (pdf)           yes    yes    no    no    no    no    no
CT presentation (pdf)   yes    yes    no    yes   no    no    no
Elsner stories (pdf)    yes    yes    no    no    no    no    no

In English and German the CT1 package is completely localized.
If a component isn't available for one of the other language versions,
then the according English component is attached.

Further language versions (Turkish, Russian, Ukrainian, ...)
are partly under development.

Currently the Greek version is not available as the compiler VS2008
does not support the Greek fonts (as UTF16) correctly.
However, for other reasons we have to stay with VS2008 for CT 1.4.31.
Nevertheless, from CT 1.5 we will use the newest MS compiler (VS 2017)
again. (xxx)

The current release version of CrypTool and the source code are
available at the following Internet addresses (without registration):
                https://www.CrypTool.org
                http://www.CrypTool.com
                http://www.CrypTool.de

Since beginning of 2010, the rate of CT1 packages downloaded per month is
ca. 6000 (more than 1/2 of the current downloads request the English version).

There are two successors of CT1, called CT2 and JCT.
Their download numbers are: (xxx)
               JCT: ca. 1000 / month
               CT2: ca. 4000 / month
The successor versions of CT1 offer a far broader functionality than CT1.

The aim of all CrypTool versions is to explain cryptographic mechanisms
and to demonstrate the use and the limitations of individual mechanisms.
CT1 has implemented almost all state-of-the-art crypto functions and
allows you to learn about, and use modern and classic cryptography
within the same environment in a "playful" manner.

CrypTool is used worldwide
- within companies to help raising the sensitivity for IT security
  (awareness) and for educational purposes,
- within school lessons, and
- within lectures at many universities.

Kindly note the terms of the license and the information regarding
non-liability for any damage arising from the use of CT1. These
conditions are described e.g. at the web page, during the installation
process and at the introduction page of the online help of CT1.

Previous users of CT1 may find interesting especially chapter 2.6
(What's new in version CT 1.4.31) and chapter A.1 (Roadmap after CT 1.4.31)
of this ReadMe.

We warmly welcome everybody willing to further develop CrypTool
or to give feedback. We are also glad about hints telling us about
papers (diploma, bachelor, master, or doctor thesis or seminar and
project works), which could be integrated into CrypTool.
Especially young developers should have the heart to participate -- as
proven in the past they'll learn a lot about professional software
development from the experienced developers.
Contacts: Please see chapter 7 below.


1.1. How to start using CrypTool -- An introduction to CT1
     -----------------------------------------------------
It is required that the user is able to use typical applications
under Windows.

When you start up CT1, the CrypTool work area starts up along with a
small welcome screen which appears in the foreground. If you press F1
in the welcome screen, the starting page of the online help comes up too.

This starting page of the online help is a good starting point to become
acquainted with all essential features of CrypTool (e.g. by following
the links on this starting page).
Please read the information and the hints on the introductory help page.

To quickly get up to speed on cryptography with CrypTool, we
recommend that you work through some of the examples (tutorials)
provided within the online help facility (the examples are shown
in the online help contents overview under "Start with CrypTool").

The easiest way to try out many of the CrypTool functions is with
the file "Startingexample-en.txt", which is open by default in the
CrypTool work area. But you also can open any unencrypted file from
the "examples" sub-directory or any other file.

If a menu item has no meaning to you or you don't know exactly what
to do within a dialog window, please press F1. If the according
online help isn't satisfactory please give us feedback.

You can find a 1-page overview (menu tree) of all menus in CT1 within
the CrypTool book, attached as PDF (see appendix A1 of this PDF file).

An overview about all functions in the different CrypTool programs can be
found on the CT Portal website (www.cryptool.org) under the menu
"Documentation --> CT Functions" or directly via:
   https://www.cryptool.org/en/ctp-documentation/ctp-functions

We hope you enjoy learning about cryptography and trying out all the
functionality within CrypTool.


1.2. Components of the CT1 distribution
     ----------------------------------
The CT1 package includes the following four main parts:

(1) The program CT1
-------------------
Main part of the CT1 package is the program CT1 itself:

- To this end, CrypTool contains an extensive collection of
  cryptographic algorithms and protocols which are well documented
  and partly visualized.
  In this way, CrypTool is very well suited for teaching, and for training
  employee's awareness about the importance of IT security.

- Most of the cryptographic basic algorithms used are taken from:
  - the Secude library (http://secude.com/),  (xxx)
  - the Miracl library from Miracl (former DCU/CertiVox, Shamus Software)
        (https://www.miracl.com),
  - the OpenSSL library (http://www.openssl.org/),
  - the NTL number theory library of Victor Shoup
        (http://www.shoup.net/ntl/),
  - the APFLOAT library of Mikko Tommila (http://www.apfloat.org/apfloat),
  - the MPIR library for arbitrary precision arithmetic (derived from GMP)
        (www.mpir.org), and
  - the cv act library of cv cryptovision Ltd (www.cryptovision.com). (xxx)

  The currently used version of the included libraries can be seen
  within the "About CrypTool" dialog (see help menu).

  In this way, CrypTool is also an outstanding reference
  implementation of cryptographic methods.

- The cryptanalysis of most of the classical algorithms
  implemented is automated.
  The analysis of modern techniques is limited so that CrypTool
  is not a hacker's tool.

CrypTool is not intended as an application to be used as a Certification
Authority (CA) [see chapter 3.1] or to encrypt or otherwise protect
real-world data.


(2) Documentation
-----------------
A comprehensive documentation is provided. This also consists of
four parts:
a) readme file (this file)
b) online help
   - context-specific help in order to use the program and further
     information about individual topics and principles,
   - demos and sample scenarios (here you can learn to know single
     procedures step-by-step).
c) book on the subject of cryptography (attached as a PDF file)
d) presentation, which shows at some slides the possibilities of
   CrypTool (also attached as PDF file).


(3) Self-contained programs
---------------------------
The following programs can be called from within CrypTool or directly
as a stand-alone program:

a) The program AES-Tool v 2.7 (developed within the CrypTool project):
   AES-Tool can create self-extracting executable files.
   AES-Tool encrypts the content of any file using a session key and
   the AES 128 bit cipher.
   This encryption tool can be called both as a Windows application
   and as a command line tool (e.g. called from within a batch file).
   The installation of CrypTool assigns the file extension "AES" with
   this program.

b) The educational game "Number Shark" v 1.2.4 (by the CrypTool project):
   This game helps pupils to get acquainted with divisors and prime
   factors.

c) The animation program Animal (see http://www.algoanim.net)
   (Version 2.4.9; September 5, 2016):
   Animal is a general-purpose animation tool with a current focus on algorithm
   animation. It contains a lot of animation generators (currently, there are
   more than 500.)
   This program is maintained by Dr. Roessling at the Technical
   University of Darmstadt. It allows to specify and model the single
   steps of algorithms or the components of data structures with as
   much detail as desired, and run these steps forwards, backwards, or
   automatically). It also can dynamically animate source code.
   Animations can be created with the Animal system using a GUI,
   a script language or a Java API.
   Further examples of animations can be found within the Animal repository
   at the website (www.algoanim.net/available-animations) or included within
   the Animal ControlCenter.
   To run Animal JRE 1.7 is required (see chapter 3.2).

d) As well as Animal the following programs are stand-alone Java applications
   (JAR files). To run them at least JRE 1.5 is required (see chapter 3.2).
   - ECC demonstration v 1.1.1
   - AES flow visualization
   - The Control Center of the S/MIME demonstration (according to given
     parameters it creates an XML file, which is used to control the called
     Flash animation).

e) The Flash applications:
   - Rijndael Animation (visualizes the AES encryption method),
   - Rijndael Inspector (visualizes the changes in the state matrix after
                         each step of each round of AES),
   - S/MIME Demonstration, and
   - Enigma (visualizes the WW2 crypto machine Enigma).

f) The Authorware application "NT" (Number Theory) introduces elementary
   number theory and visualizes many of the methods and concepts, which
   are the basis of modern public-key cryptography.
   Where appropriate, the mathematical formulas are shown.
   It allows to dynamically check out the mathematical methods with own
   number examples.
   Part of it is the program bc v1.06 by the Free Software Foundation (FSF),
   which allows to calculate with arbitrary precision from the command line.



(4) Stories (dealing with number theory and cryptography) and riddles
---------------------------------------------------------------------
a) There are two stories attached as PDF file.
   - In "The Dialogue of the Sisters" the two title-role sisters use a
     variant of the RSA algorithm, in order to communicate securely.
   - In "The Chinese Labyrinth" Marco Polo has to solve number theoretic
     problems to become a minister of the Great Khan.

b) Cipher Challenges / Cipher Riddles:
   Also enclosed are 13 files with encrypted texts, which we got by courtesy
   of Klaus Schmeh, the author of the book "Codebreaker and Codemaker":
   Klaus Schmeh: "Codeknacker gegen Codemacher. Die faszinierende Geschichte
                 der Verschluesselung", 2nd edition, December 2007, W3L

   These files contain some historically interesting (solved and unsolved)
   ciphertexts, which are appropriate as exercise or simply as pastime:
   1) Dorabella cipher (unsolved)
   2) D’Agapeyeff cipher (unsolved)
   3) Feynman ciphers (3 parts, two are still unsolved)
   4) Kryptos sculpture (4 parts, the last one is still unsolved)
   5) Double-Column-Transposition (Doppelwuerfel) (riddle created by Klaus
                   Schmeh, plaintext is English, solved)
   6) "The Adventure of the Dancing Men" ("Die tanzenden Maennchen") by
            Arthur Conan Doyle (Sherlock Holmes)(transliterated, solved)
   7) Harry-Potter cipher (riddle created by Klaus Schmeh, plaintext is
                           German, unsolved)
   8) "Mathias Sandorf" by Jules Verne (solved)

   More information about these files are available in the online help of
   CT1 (see index item "Crypto Competitions/Crypto Puzzles") and within
   the book of Klaus Schmeh.

   Many more riddles and challenges can be found
   - at the pages of CrypTool-Online and
   - at the pages of the crypto challenge "MysteryTwister C3":
     https://www.mysterytwisterc3.org

All the single files included in the package are listed within
chapter 5 (see below in this ReadMe file).



1.3. Acknowledgments
     ----------------
A big number of individuals (more than 300) have contributed to CT1,
normally complimentary in their free time (some are listed in the dialog
box you get after double clicking the "About" dialog box).
We are extremely grateful to these person.

I'd like to mention some outstanding software developers / architects
within the CT1 project. Their empowered and long-time dedication
and their brilliant expertise and persistence are the key for such
durable, agile and successful open source projects:
Joerg, Henrik, Florian, Peer.

I also want to thank some outstanding software developers / architects
within the successor projects CT2 and JCT. They showed great endurance
and expertise, necessary to overcome the difficulties of the brand new
development environments and software architectures:
- Arno, Nils, Philipp, Thomas, Sebastian, Martin, Timo, Soeren, ...
- Dominik, Simon, Matthias, Tobias, Amro, David, Michael, ...

And needless to say the many undisclosed ones, especially students and
interns who contributed a lot -- and thereby learned even a lot more by
the experts within the project.

Contributors are e.g. Deutsche Bank AG, the Technical University of Darmstadt
and the University of Duisburg-Essen.

Further on we want to mention some contributors who have special conditions
for their input:

- Dr. Carsten Elsner allowed us to include both his stories.
  The author owns all rights at these stories. The maintainer of
  CrypTool is allowed by the author only to distribute this story
  together with the CrypTool package.
  The German version of the story "The Dialogue of the Sisters"
  was first published in the computer magazine c't, 25/1999. While
  c't published a slightly shortened version you here get the original
  version.

- Dr. Guido Roessling allowed us to include and deliver his freeware
  Animal, a Java based animation software.

- We also got the allowance to integrate enhanced versions of:
  - the two Flash animations for AES by Enrique Zabala,
  - the Flash animation for Enigma by Dr. Frank Spiess,
  - the number theory e-learning program by Martin Ramberger.
  All rights for a usage outside the context of the free CrypTool
  application remain with the appropriate owners/authors.

- The companies (see chapter 1.2)
  - Secude IT Security Ltd, (xxx)
  - Shamus Software Ltd, and
  - cv cryptovision Ltd (xxx)
  allowed us gratefully to use their cryptographic libraries.
  These libraries distributed with CT1 are not allowed to be
  used in another context than CrypTool without contacting the
  mentioned companies and asking for their current terms of license.

Also we want to cordially thank the open source developers, who
encouraged us with their code or who build code we can use, e.g.
- the libraries OpenSSL, GMP/MPIR, APFLOAT and NTL,
- the installation software NSIS (http://nsis.sourceforge.net/Main_Page),
- the text editor software Scintilla (http://scintilla.sourceforge.net),
- the Hex Control (www.codeguru.com/Cpp/controls/controls/article.php/c5287),
- the rendering engine from OpenQVis (http://openqvis.sourceforge.net/).

I also want to thank
- Dr. Bartosz Sawicki from the University of Warsaw, who did with his team
  the first Polish version.
- Dr. Gonzalo Alvarez from the University of Madrid, who did with his
  colleagues the first Spanish version.
- Bojan Dimitrovski from the University of Belgrade, who did with his
  colleagues the first Serbian version.
- Prof. Ioannis Mavridis and Dr. Theodoros Mastoras for the first
  Greek version of CT1.
- Alain Stephan for the first French version of CT1.
And several people (like Pawel, Vasilios, and Vesna) who helped to continue
the translations for new versions of CT1.

Potential further translations:
- Turkish (xxx): Interests, but not started yet.
- Russian (xxx): Requests, but not started yet.



1.4. Maintainer and hosting
     ----------------------
CrypTool was never bound only to a single person or a single faculty.
Also the hosting changed. After Siegen and Darmstadt there were:
From April 2008 the chair "Division for distributed systems", Engineering
department of Prof. Dr. Torben Weis at the University of Duisburg-Essen,
Germany hosted CT.
Since April 2014 the chair for Applied Information Security of Prof. Dr.
Arno Wacker at the University Kassel hosts
- the web pages of the whole CrypTool project,
- the Subversion repository system for the program sources of CT1, and
- the Subversion repository system for the program sources of the successor
  CrypTool 2.
Webserver and build server are currently running virtually in a Proxmox
environment with 24 Intel Xeon E5-2640 a 2.5GHz and 128 Gigabyte RAM.

The CrypTool developer group around Prof. Bernhard Esslinger continues
to act as maintainer of CT1: This means they take care about the source
code, they publish CrypTool as open source and freeware, and they
co-ordinate the further development. Current steps of the roadmap
are published in chapter A.1 of this readme and at the web page.

Homepage of CrypTool: www.cryptool.org

We would be very glad about every new developer, who joins to help
enhancing the functionality and usability of CrypTool.
Ideas for further development can be found in chapter A.3.

Also very welcome are ideas and information, how CrypTool is used in
lectures, at schools and in education, so that we can help to share this
information. A tool to foster such an information exchange in this area
is with the cryptology portal for teachers (www.cryptoportal.org) which
currently is only available in German.



2. What does CT1 offer in detail
   -----------------------------

2.1. What can you do with CT1
     ------------------------
The general properties and functions of CT1 are:

- E-learning program around the topic cryptography and cryptanalysis.

- Everything in one program package and controlled by one common
  graphical user interface.

- Many classic encryption methods, and for them either a manual
  cryptanalysis or an automatic analysis is offered (known-plaintext
  or ciphertext-only attack).

- Codes like Base64 and UU-Encode.

- Almost all modern symmetric encryption methods, accompanied by brute-force
  analysis
  (The brute-force attack on symmetric algorithms allows to define
   joker characters and the expected elapsed time is displayed.
   Additionally you can customize the width of the entropy field
   used for this kind of analysis within the analysis options; and you can
   specify which alphabet you expect the plaintext is build from).

- Modern (asymmetric) crypto methods and protocols (hash, RSA, ECC, digital
  signature, hybrid encryption, PKCS#5, shared secret, ...) and partly
  attacks against it (birthday attack, side-channel attack,
  lattice-base reduction).

- Demonstration of the RSA cryptosystem (and some variants) and some
  number theoretic algorithms behind:
  - Generate and test primes (including the deterministic method AKS).
  - Factorize numbers (step-by-step) with different methods
    (the different methods run in parallel threads).
  - Make the RSA cryptosystem understandable and use it:
     - Generate RSA keys (also with primes of your own choice).
     - Encrypt/decrypt with RSA.
     - Generate RSA signatures and validate these.
     - Attack the RSA cryptosystem.

- Three attacks against RSA, based on lattice reduction. They work,
  if special preconditions are given:
  * either a part of one of the two factors of N is known
    ("Factoring with a Hint"),
  * or a part of the plaintext of an eavesdropped encrypted message
    is known and e is small ("Attack on Stereotyped Messages"),
  * or if d is too small compared to N, N can be factorized
    ("Attack on Small Secret Keys (according to Bloemer/May)").
  This implementation was done within a thesis, which can be delivered
  via email (this thesis only exists in the German language).

- Visualization / Animation / Demonstration
  - demo of the sensitivity of hash algorithms.
  - visualization via flow process charts (e.g. the Diffie-Hellman
    key exchange protocol or the challenge response demonstration).
  - Animations
     - with Animal: for the ciphers Caesar, Vigenère, Nihilist, and DES,
     - with Flash:  for AES, Enigma, and S/MIME,
     - with Java/SWT: - addition of points on an elliptic curve
                        (either on a discrete or on a real curve),
                      - flow visualization of AES,
                      - control center of the S/MIME demonstration.

- Demonstration for different ways of authentication in the net
  (Visualization of challenge response methods):
  * from UID/PW and one-time password
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

- Calculate hash values and demonstrate its sensitivity.

- Implementation of HMACs (combination of hashes and symmetric methods
  to authenticate messages).
  Hashes are also used in CrypTool within PKCS#5 or digital signatures.

- The Shared Secret method from Shamir has been implemented with
  many options.

- Random numbers:
  - Generators and statistical analysis for (random) data (e.g. FIPS-140-1).
  - The Secude cryptographic random number generator allows to gather
    entropy by mouse moves and keyboard entries.
    This is the default, when calling it the first time, because it shows,
    that you need a random source in order to get good random data. (xxx)
  - 3-D visualization of big sets of random numbers with the rendering
    engine from OpenQVis.

- Export and import RSA and DSA PSEs with the keys stored in there
  via PKCS#12.

- The modern methods are implemented according to international
  standards (reference implementation).

- The last adjustment for a method (parameter, key or alphabet) is
  stored within the program. A stored key can be retrieved via an
  insert-key-icon for any single key, which make the handling of testing
  and probing easier.

- For each window you now can call a dialog which shows all relevant
  properties of the document.

- In all classic algorithms where the alphabets of the text documents play
  a role, the used alphabet is the one handled in the common dialog
  "Text Options". So the transparency and usability are clearly improved:
  When entering a key, you now can see at once which method is adapted,
  because each according key-entry dialog contains the additional button
  "Text options", which directly leads to the dialog "Text Options"
  (Users found, that the most needed place to use text options was within
  the key-entry dialog. So from here it's no more necessary to first close
  the key-entry dialog again and then call the text options via the main menu).
  This call via a click at the button "Text options" is implemented for
  instance within the key-entry dialogs for Caesar, mono-alphabetic
  substitution, Vigenère, Scytale, permutation and homophones.

- CrypTool can be used without having administrator access rights.
  Different users at the same PC can have different settings.
  See chapters 3.2 and 4.4 for details.

- The same menu structure is permanently visible: Items which cannot
  be clicked for special document types are dynamically made gray.

- The self-contained program AES-Tool can create self-extracting
  programs. So you can encrypt any file with the AES algorithm,
  protected by a password (the password can be entered in ascii or
  directly as a hexadecimal key).
  Full functionality also when calling from the command line.
  A self-extracting archive may not be bigger as 4 GB. But if you one
  create the encrypted AES file the original file maybe significantly
  larger than 4 GB.

- The self-contained e-learning program "NT" about the mathematics behind
  the asymmetric cryptography presents exhaustively and interactively the
  elementary number theory.

- Three applications based on the Chinese remainder theorem:
  * Solving a system of linear modular congruences using the solar
    system as an example.
  * Showing how you can calculate (add, subtract or multiply) with
    modular remainders (residues) instead of the (bigger) actual numbers.
  * Showing the shared secret method (this is an electronic equivalent
    to the vault mechanism where e.g. at least 3 key-owners must
    cooperate to open it, but 5 different keys are there).

- With the dialog "Compute Mersenne Numbers" you can create in less than a
  minute the biggest primes found in the GIMPS project (they are several
  million digits long).

- With the Password Quality Meter (PQM) dialog you can check the resistance
  of a password with different methods and by defining minimum requirements.

- With the Password Entropy dialog you can generate passwords, which achieve
  a similar security as a randomly created binary key for symmetric ciphers
  with a given bit length. You can also customize the alphabet to be used
  for the password.

- The educational game "The Number Shark" helps pupils to
  get an easy understanding of divisors and primes.

- Download website https://www.cryptool.org/en/ct1-downloads
  This web page contains the hash values of all downloadable CrypTool files:
  So you can check the integrity of the files of the CrypTool package
  stored on your computer.

- Exhaustive documentation (online help, book).
  The online help has HTML format.
  The online help contains explanations about the handling and about all
  the cryptographic methods, a historic overview and the integration into
  further scientific and organizational topics plus how cryptography should
  be used.

- CrypTool is used world-wide in schools, universities, agencies and
  companies.



2.2. Where do you find the source code
     ---------------------------------
- The sources of the release version (Tag "CrypTool_1_4_31") and the current
  developer sources are available directly from the subversion repository.
  Everybody has read access without a password to this repository via:
  svn checkout https://www.cryptool.org/svn/CrypTool/trunk/ --username anonymous


- Snapshot about the number of files and the number of lines of code

  To get an impression of the size of the CT1 project here is a statistics
  created in October 2016 using the files of version 1.4.31 Prefinal beta 06d:(xxx)

    FILE SUMMARY (number of files according to file extension)
    ------------
              4 .rc files
             36 .c files
            325 .cpp files
            379 .h files
             36 .java files
             14 .pl files
           1152 .html files
             46 .txt files
             47 .tex files
              4 .sage files
          2,043 TOTAL


    LINES OF CODE (LoC) SUMMARY
    ---------------------------
         84,772 MFC resource code (rc)
        285,633 C/C++ source code (c cpp h)
          9,795 Java source code (java)
          2,257 Perl code (pl)
         66,267 HTML code (html hpp)
          8,109 Text files (txt)
         61,401 LaTeX code (tex)
            825 Sage code (sage)
        519,059 TOTAL

    TOTAL: 519,059 lines of code (plus of 18 % from 437,772 with CT 1.4.30)
    - Here only code written within the CrypTool project or explicitly
      dedicated to the CrypTool project is counted. Any sources used
      within the CrypTool project coming from other open source projects
      like OpenSSL, NTL, Scintilla, Animal, ... are not counted here.
      Also any automatically created files or word lists are not counted.


- Details about compilation, linking and about a consistent development
  can be found in the sources in the file "readme-source.txt".

- The sources have been compiled with the Microsoft development environment
  Visual Studio 2008 Standard Edition.
  Note about the versions of the MS development environment:
  - The Express Edition of VS2008 is not sufficient, because this does not
    support the old MFC library (in contrast to the Standard Edition) for
    the GUI, which is still used in CT 1.4.
  - The compilation itself worked well when using a more modern Microsoft
    development environment like Visual Studio 2010 Standard Edition
    (VC++ v9.0), VS2013, or VS2015. However, many graphics then appeared
    distorted or too small at UHD monitors (in the opposite to executables
    built with VS2008).
    --> We found no hint, how to get rid of this adaption in the newer
        development environments, without newly creating all graphics ;-)
        The adaption is probably caused by the GUI settings where users
        can change the "size of texts, apps and other elements" to a value
        different of 100 %.

- Compiling all versions (7 languages, each in debug and release mode)
  lasts about 2 h on a modern PC. (xxx)



2.3. Where can you get another overview about CrypTool
     -------------------------------------------------
You can get a good overview of what CrypTool offers
- within the online help (see "starting page"),
- at the attached PDF presentation (title: "Cryptology with CrypTool") and
- using the menu tree in appendix A.1 within the attached CrypTool book,
- at the website of the CrypTool portal under
          "Documentation" -> "CT Function",
          https://www.cryptool.org/en/ctp-documentation/ctp-functions
- at the website of CT1 (https://www.cryptool.org/en/cryptool1) under
          - "Documentation" -> "Features of CrypTool 1.4.3x", and
          - "Screenshots" -> "Screenshots".



2.4. What's new in version 1.4.20 / 1.4.21
     -------------------------------------
This chapter lists the enhancements and bug fixes in CrypTool 1.4.20 and
1.4.21, which have been added since CrypTool 1.4.10.

a) Developer-relevant changes (more technically oriented):

- Clearance of source code, better re-usage.

- Update to OpenSSL 0.9.8g, Animal 2.3.14 and NSIS 2.37.

- Automated consistency check within the online help (link to menus,
  dialogs, pictures, mutual links).

- Safeguarding entry fields against fuzzy input via clipboard, to avoid
  provoked program crashes.


b) Changes within the user documentation:

- Online help: enhanced.

- Within the book: minor bug-fixes, menu tree within appendix A.1 adapted
                   to the new version of CrypTool.

- Updated and enhanced presentation (more than 100 pages now).

- New CrypTool website using Joomla since April 2008.


c) New functionality:

- Bug fixes:
  - Many small improvements in the masks (user interface):
    user guidance; refresh; cursor correctly set again after dialog change;
    DH, Hill and side-channel-attack dialogs consistently offer a checkmark
    to show detail dialogs or to create log files.
  - Corrected the AML file for the DES animation with Animal (in the matrix
    K[1] a bit was set to 1 instead to 0). Thanks to attentive users!
  - The installer now handles previously installed versions better.

- The installer links the file extension AES to the AES-Tool; and optionally
  includes AES-Tool into the context menu "Open with ..." within the
  Windows Explorer.

- The menu "Help" within the CrypTool application now also contains the
  item for the CrypTool presentation.

- Within the text option dialog there now is a check mark for German Umlauts
  in order to build the used alphabet by clicking.

- A text file now can be shown in any given fixed block length:
  e.g. formats xxx xxx xxx  or  xxxxx xxxxx xxxxx ...
  Also you can convert everything into small or capital letters.

- The editors are enhanced:
  * Hex editor / Hex control / HexView:
     - Search and replace (including hex nulls) also in the hex area.
     - Undo / Redo.
  * Text editor:
     - Search and replace can be done with synchronized ascii and hex strings
     - Redo.

- The ADFGVX cipher now can deal with variable alphabets for the
  transposition password defined by the text options dialog (not
  only the 26 capital letters).

- Enhancement of the brute-force analysis for symmetric ciphers (Henk --
  thanks for the practical and educational suggestions):
  - Define the alphabet of the expected plaintext in order to limit the
    search of a possible correct key.
  - Showing a choice of the 50 plaintexts with the lowest entropy values.

- The AES-Tool in version 2.5 is faster when handling large files.
  The files extension AES is linked to this application during the
  installation process.

- The educational program/game "Number Shark" in version 1.1.5 was corrected
  a little bit and the online help was enhanced.

- SHA2 family (SHA-256, SHA-512) added for calculating the hash value of
  the shown document or of a file
  http://csrc.nist.gov/publications/fips/fips180-2/fips180-2.pdf

- Improving of the password-quality-meter: In addition to the known PQM
  methods from KeyPass and PGP an own component was added. This new method
  rates the password by making realistic assumptions about the attacker's
  knowledge coming from dictionary attacks:
  - Recognition of series and patterns (the entropy is calculated no more
    only from single independent characters).
  - All methods are normalized: 100 % means 128 bit entropy.
    If 100 % is achieved, further entries in the password field are ignored.
  - Restrictions in this version:
    - In the password field no blanks can be entered (all ascii codes <= 32
      are ignored).
    - The new PQM method rates at most 32 characters of the entered password.

- The password entropy dialog offers to create random passwords which offer
  a similar high security as randomly generated binary keys for symmetric
  ciphers using a given bit length.
  Additionally you can specify the alphabet used for the password.



2.5. What's new in version 1.4.30
     ----------------------------
This chapter lists the enhancements and bug fixes in CrypTool 1.4.30,
which have been added since CrypTool 1.4.21.

Version 1.4.30 was released simultaneously in 5 languages (English, German,
Polish, Serbian, and Spanish).

a) Developer-relevant changes (more technically oriented):

- Clearance of source code, better re-usage, many warnings eliminated.
  E.g. the Hill encryption including the GUI was written completely new.
  Doing so around 6000 lines of C++ code could be saved, nevertheless
  functionality and performance were improved!

- The welcome screen was created newly, so that the texts of different
  languages can be combined with the background more easily.

- Now compiled with VS2008.

- Update of used libraries and other software to the following versions:
  - Scintilla 1.7.7
  - cv act library v. 1.4.6 (supporting Windows Vista too)
  - OpenSSL 0.9.8k
  - MPIR 1.3.1 (derived from GMP version 4.2.1) instead of GMP 4.1
  - APFLOAT 2.41
  - Animal 2.3.21.

- Source code and application of CT1 are now subject to the Apache
  license 2.0 (see http://www.apache.org/licenses/LICENSE-2.0).


b) Changes within the user documentation / on the websites:

- Online help: well enhanced (e.g. modi and padding variants used for block
               ciphers now are described explicitly).

- CrypTool book: Extensive revision:
                 - extensions and update to status quo,
                 - inclusion of many SageMath code samples,
                   delivery of the SageMath code as files,
                 - minor bug-fixes,
                 - menu tree within appendix A.1 adapted to the new version
                   of CrypTool,
                 - new cover.

- Updated and enhanced presentation (more than 110 pages now).

- From the CrypTool website links are set to the sites of the successor
  versions JCT and CT2, which already offer their current and stable
  betas for download.

- The following additional websites also belonging to the CrypTool family
  of website went life:
  - www.cryptool-online.org  "CrypTool-Online" runs various crypto functions
                              directly within a browser.
  - www.m.cryptool.org       "CrypTool-Mobil" runs various crypto functions
                              directly within a smartphone.
                              This maybe helpful for geocaching.
  - www.cryptoportal.org     A teacher's portal with material for the lessons
                              and links (currently only in German)
  - https://www.mysterytwisterc3.org  An international crypto challenge contest
                                      with tasks of different levels.

- A short video with CrypTool is on YouTube:
   - German:  http://www.youtube.com/watch?v=of0C9Lx0vGs
   - English: http://www.youtube.com/watch?v=bLJKuW4UOuE
   - Spanish: http://www.youtube.com/watch?v=pTFdklPQiL4

- At the CrypTool website, section presentations, now there is an interactive
  introduction into the basics of RSA (as PPT and as Flash):
  https://www.cryptool.org/en/ctp-documentation/ctp-presentations


c) New functionality / Usability:

- Bug fixes --> Thanks to the many attentive users!
   - Bug fixed in AKS which appeared with the numbers 2^8+1 and 2^16+1.
     The corrected version of AKS is slower.
   - Bug fixed in AKS which broke CT when calculating the estimated time for
     very big numbers. Fixed by using MPIR instead of an older Windows version
     of the GMP library.
   - Bug fixed in further primality tests which appeared when the tested
     number had prime factors < 39.
   - In the dialog "Key generation from password (according to PKSC #5)"
     now hash values with leading zeros are presented correctly.
   - The ECC-AES hybrid encryption and decryption now also runs under
     Windows Vista (thanks to a new cv act lib from cryptovision).
     Additionally, now a correct error message pops up, if one tries to
     decrypt an unencrypted text.
   - DH Demonstration: In earlier versions a crash happened when a digits
     (e.g. 2) were appended to an automatically created generator.
     This is fixed now.
   - Side-channel attack on the hybrid encryption protocol "Textbook RSA":
     In earlier versions a crash happened when a RSA modulus was used
     longer than 1024 bits when starting the attack cycle.
     This is fixed now.
   - The Secret Sharing application using the CRT now disallows, that
     n=k (so all share holders are necessary) in order to avoid that the
     algorithm then would make the whole secret evident to the first
     share holder.
   - RSA demonstration: Keep the entered parameter e after calling options.
   - Fix for the ECC demonstration:
     - The old version calculated under special circumstances a point outside
       the curve when adding points over the discrete group over F(p).
     - The coordinates dynamically shown at the points near the mouse cursor
       are now completely visible also at the right border.
     - The point in infinity is now added in the overall number of points.
     - The log window now is amodal, resizable and the content is more
       well-arranged.
     - The sliders are broader now, so its easier to adjust the parameters.
     - The version number now is 1.1.1 and it is shown in the title.
   - Fix for DESX/DESXL: Now the effective bit length is displayed in
     encryption and brute force dialogs.
   - Fix for DESX/DESXL brute force analysis, which skipped keys when
     searching in the last 128 bit of the key (brute-force analysis ignores
     correctly the parity bit of the DES key for performance reasons;
     this can be done so only for the DES key part of the whole key).
   - The result of the attack on the hash value of the electronic signature
     previously showed a wrong number of steps (always ca. 4.x*10^18).
   - Fixed a crash which happened when first defining within the text options
     as alphabet the capital letters plus the small umlauts, and then calling
     the Caesar cipher.
   - Fixed a bug when entering hex strings from the clipboard (now its
     inserted only at the marked places).
   - Switching between text and hex view does not lose the font selected for
     the text view of a document.
   - Conflicts with the certificate serial numbers: So far serial numbers have
     been generated consecutively, and the serial number was not checked when
     a cert was imported into the key store.
     This could involve using the wrong certificate when validating a message.
     Both are fixed: The serial numbers are now generated randomly and if a new
     certificate is to be imported, first it is checked whether its number is
     already generated. If so its rejected.
   - The ciphertext-only analysis of XOR ciphertexts calculated a wrong
     key length despite the shown autocorrelation was correct.
     Now the correct key length is shown and used.
   - Correction of quite a few typos within the CrypTool online help, the
     resource files of  CrypTool, AES-Tool, and Number Shark, and the Animal
     AML files.


- CrypTool now remembers its main window position and size and uses
  this when it is restarted.

- User convenience: Especially helpful for new users who did not use online
  help and asked about the meaning of the icon the icon used to paste keys
  from the internal key store into several modal dialogs now carries a tool
  tip ("Paste key").

- Many small improvements in the masks (user interface), e.g. elapsed-time
  dialog for the AKS test; text in about box can be marked and copied; time
  and number of found factors are shown at once in the factorization dialog;
  menu "XOR" in analysis of ciphertext-only changed to "XOR / Vernam".

- Contributors and translating organizations are now listed in own dialogs
  (which can be called from the new About dialog).

- Extensive enhancements of the online help.

- External PDFs on the Internet now can be opened directly within the online
  help.

- The XOR/Psion tutorial in the presentation used an encrypted file (created
  from a German plaintext). Now there is also a file with an encrypted English
  plaintext: psion-en-enc.hex

- For all DES based methods now the dialogs show both the effectively used
  key length and the key length which the user has to enter.

- All available 8 hash methods offered in the dialogs for:
  - Key generation from password (according to PKSC #5),
  - Generation of a hashed Message Authentication Code (HMAC),
  - Generation of the hash value of a file, and in the
  - Hash demonstration.

- The HMAC dialog was newly designed.

- Within the HMAC dialog the names are related to the literature and the
  according online help contains the corresponding references.
  Variant 5 of the HMAC sample constructions now exactly follows RFC 2104.
  Details:
  CrypTool contains five HMAC variants
  (H = hash function, k = key, m = message):
  1.  H ( k, m )
  2.  H ( m, k )
  3.  H ( k, m, k )
  4.  H ( k, m, k' )
  5.  H ( k , H (k, m) )
  Only variant 5 is specified by a standard (RFC 2104, FIPS PUB 198).
  This HMAC is calculated via: H ( k XOR opad, H(k XOR ipad, m) )
  where ipad = 64 bytes each 0x36, opad = 64 bytes each 0x5C.
  If the key k is longer than the block length of the hash function, then k
  will be substituted by H(k).
  All this functions are implemented using OpenSSL.

- Within the PKCS #5 dialog now at most 100,000 iterations can be calculated.
  Additionally more hash methods are supported than described in the original
  standard.

- Enhancement of the brute-force analysis for symmetric ciphers:
  Another column was added to also show the key which goes with the
  current columns of entropy of plaintext, plaintext and ciphertext.


- If the result in the dialog primality testing says, that the given number
  is NOT prime, then you can directly (via a new button) call the
  factorization dialog.

- Until 1.4.21 the dialog "Generate Primes" created two randomly
  selected primes within a given range.
  Now all primes within a given range can be generated (generation of
  prime sets).

- Diffie-Hellman now creates the primes and the generator according
  to standards for secure generators.

- New is the fast calculation of integer powers.
  This uses the library APFLOAT and it can be used to calculate and store
  all digits of the current prime number records (Mersenne numbers).
  In this dialog for the input of integers the thousands separators used
  in digit grouping (commas) are set automatically. This is more user friendly
  for eventually very big exponents.


- Added the classic transposition ciphers Scytale and rail fence (combined
  in one dialog) including the view and insertion of the key via icon.

- Solitaire encryption: Dialogs are improved, display of "A" and "B" for the
  jokers instead of "53" and "54" (as in the original description),
  message is no longer limited to 64 kB, the key streams created can be stored.
  Solitaire's manual analysis (reconstruction of the initial deck) is improved.

- The permutation cipher now can be applied to hex files too.

- The way, how a permutation is created from a key word, is now the same with
  all methods (double column transposition, ADFGVX).

- The Hill cipher supports further options, and all key parameters and all
  according options are saved in the key store (registry).

- Playfair encryption offers further options (pre-formatting; differentiate
  whether to insert separators only between pairs of double characters or
  always when double characters follow each other in the plaintext).
  This makes a difference when dealing with words like "BALLOON".

- All specific options are now within the dialogs of the according methods.
  So we could get rid of the menu item "Further Options".

- The checkbox "Special characters" within the dialog "Text Options" now
  offers some more characters by default. Maximum are 98 characters for
  the classic ciphers.

- The alphabet set in the dialog "Text Options" now affects almost all
  classic ciphers: Therefore all adapted methods now have a button to
  directly call the Text Options dialog from the Key Entry dialog.

  The "Text options" button is enabled at
  - the classic substitution methods (Caesar, Vigenère,
        mono-alphabetic substitution, Hill) and at
  - the classic transposition methods (Scytale, transposition part of ADFGVX).

  The "Text options" button is intentionally not available in the key entry
  dialogs for the following ciphers:
  - Substitution part of ADFGVX (algorithm requires fixed alphabet)
  - Playfair (the algorithm determines via the matrix the alphabet)
  - Permutation (all data is permutated; pre-format the document if wished
                 by yourself via the menu "View \ Format Text Document")
  - Solitaire (algorithm requires fixed alphabet; turning all letter into
               the 26 upper-case letters and deletes all other characters).

  This enhancement came especially because of many requests to offer more
  characters for the mono-alphabetic substitution.


- A visualization for secure e-mail was added: The user can enter dynamically
  data which is signed or encrypted using the S/MIME protocol.

- Another visualization for the AES algorithm was added: flow visualization,
  showing how the bits are changed round-by-round (compiled with Java 1.5).


- The educational program/game "Number Shark" (in version 1.2.1) was
  corrected and the online help was updated and enhanced.
  Showing the optional solutions:
  - Until now optimal results could be shown in two ways:
    - Until n=158 they have been stored.
    - For any number they could be calculated in a very slow brute-force
      algorithm.
  - Now they can be calculated much faster using a back-tracking algorithm
    (39 numbers within around 1 minute; 40 numbers within around 5 minutes).
  - Even much more faster are heuristic algorithms, like the ones implemented
    in JCT. They normally don't find an optimal result, but a very good one.
    Best known results up to n=404 are delivered with the game now.
    All known values can be shown in a table.
  - If the Number Shark calculates optional results (which can last very long),
    then you now can restart using stored pre-calculations.
  - Further background pictures have been added.

- The educational program "Number Theory" got some few corrections and is
  now included in the version from 2010-06-19.


- For the simple column transposition now a known-plaintext analysis
  is added to calculate the transposition key.
  This known-plaintext analysis is now better integrated -- together with the
  previous known-plaintext analysis for the Hill cipher.
  All keys found by the transposition analysis are now shown in a table.

- Further ciphertext-only analysis for Vigenère (according to Schroedel):
  This is effective for very short cryptograms if the password comes from
  a dictionary.



2.6. What's new in version 1.4.31
     ----------------------------
This chapter lists the enhancements and the bug fixes in CrypTool 1.4.31,
which have been added since CrypTool 1.4.30.

Version 1.4.31 is released simultaneously in 6 of 7 languages.
Greek will follow.

a) Developer-relevant changes (more technically oriented):

- Update of used libraries and other software to the following versions:
  - Scintilla (3.7.0 postponed to CT 1.5; still using modified 1.7.7)
  - compiler-dependent: cv act library 1.4.6 with VS2008, 1.4.18 with VS2010
  - OpenSSL 1.0.1 (xxx)
  - MPIR 1.3.1 (derived from GMP version 4.2.1) instead of GMP 4.1 (xxx)
      ???????  2.5.1 (postponed to CT 1.5) (xxx)
  - Miracl 4.4.3  -->  5.5.4  (postponed to CT 1.5) (xxx)
  - NTL 5.5.2  --> 10.3 (thread-safe and with exception handling, needs
                        a C++11 compiler)   (postponed to CT 1.5) (xxx)
  - Animal 2.4.9
  - Substitution of the Secude library (as we encountered problems after
    compiling with VS2010 (not with VS2008) postponed to CT 1.5.) (xxx)

- The CT1 installer now is signed with a certificate issued by a CA which
  is contained in the Windows keystore. This avoids that Windows shows
  users unnecessary warnings about unsigned software.

- Installer fills the publisher field so the Windows overview of installed
  software shows now "CrypTool Team".
  
- The release of CT 1.4.31 is still compiled with VS2008 (see above).
  From CT 1.5 VS 2017 will be used for compilation, or QCT substitutes CT1.


b) Changes within the user documentation / on the websites:

- Online help: updated some topics.

- CrypTool book: - Edition 12 is a major update, many corrections and additions
                 - Additional chapters about bitblock and bitstream
                   encryption, and with a Survey on Current Academic Results
                   for Solving Discrete Logarithms And Factoring
                 - Inclusion of further SageMath code samples
                   (for primitive roots and RSA fix points)
                 - Appendices with function overviews also for CT2 and JCT
                   (xxx)
                 - Added the menu paths of CT2 and JCT in the foot notes.

- Presentation about CT1 updated in March 2017.
  The description of the overall CrypTool project, and the information about
  the two other CT projects (CT2, JCT) are now in self-contained presentations.

- At January 18th, 2012 the new CrypTool website (CTP) was released. It
  describes the 5 sub projects of the CT project in an equivalent way.
  This contains CT1.


c) New functionality / Usability / Corrections of errors:

- Two more languages added: Greek and French.
- Installation and usage without administrator privileges: Now not only the
  program doesn't need administrator rights any more, but also the installer
  can be executed by a normal user.
- Within the number-theoretic functions the special case of generic t-adic
  NAF key generators was added. The b-adic window was made broader.
  Rewriting of the generator as its pattern caused some anti-virus products
  to produce by mistake false-positive warnings about the beta setups.
- Text windows now have a context menu entry to switch to hex view, and
  vice versa.
- Many small improvements in the dialog window layouts, like in "Attack on
  Stereotyped Messages". 
- The layout of the RSA demonstration dialog was improved according to some
  didactical feedback we received. (xxx)  
- Transposition Encryption: The key entry dialog now also contains a text
  options dialog.
  This button was also added with the analysis of the maS.
- Mono-alphabetic substitution (maS): The key entry dialog features a new
  parameter to define the starting position (offset) of the password. In the
  past the password was always positioned at the beginning of the ciphertext
  alphabet.
- The analysis of the substitution cipher offers two variants. The second
  variant uses a list of frequent words, which were not revealed and changeable
  by the user in former versions. Both is possible now. (xxx)
- To determine the substitution matrix the ADFGVX analysis now also uses the
  frequency distribution of the reference text selected in the text options
  dialog.
  Additionally you can determine whether digits are also used for the frequency
  distribution (case sensitivity and special characters are not allowed
  with the ADFGVX cipher). The introduction dialog of the analysis was
  adapted accordingly.
- The fields to present hash values for a file now can display values of
  256 bit length without the need of scrolling.
- Number Shark 1.2.4:
  - Some of the hot key functionalities now also have a button.
  - Updated online help (especially some outdated links).
- AES Tool 2.7:
  - Fixed a bug which appeared when entering too long hexadecimal keys.
  - Now you can enter the key as normal ASCII characters too, and securely
    delete the original file after encrypting.

- If the registry contains positions or sizes laying the CT window outside
  of the screen, CT now recognizes this at start time and adjusts its position
  within the visible area. The "disappearance" of the windows happened several
  times under Win 7 with CT 1.4.30, especially after updates of the operating
  system or after changing the monitor resolution.
- DES-Animal animation: In the steps 357-424 and especially in the
  pre-output matrix (64 bit) some mistakes have been fixed.
  Thanks to Vasilis. Additionally the online help has been enhanced.
- Dialog to enter hex keys: Before entering via Ctrl-V worked correctly,
  via context menu -> Paste it didn't. Now both work ok.
- At SHA256 / SHA512 the wrong function was called yet.
  This also effected the dialog window "Generation of HMACs".
- Calling bc from within the number theory tutorial now also works under
  Windows [Bsp: 3*5 // 5+3^2 // a=10; a+2; b=a; b+7 // sqrt(4.5) //
   define d (n) { return (2*n); }; d(5) // l(100)/l(10) # Natural log // quit //
  faktbas(4) is 4*3*2*1 // Sample of a sum function via a for loop:
  sum=0; for(i=16;i>=0;i--)sum+=32*(256^i); sum].
  Make own enhancements like http://x-bc.sourceforge.net/extensions_bc.html 
- Playfair with a 6*6 matrix now doesn't wrongly transform J to I any more.
- Scilexer.dll again greys out non-alphabet characters correctly.
  See e.g. menu View --> Alphabet or the Hill analyzer.
- Fixed small issue with wrong index shown initially in the homophones dialog.
- Making the dialog "Attack on Stereotyped Messages" more robust, and
  fixed some smaller mistakes in layout. 

- Thanks to the many attentive users, who pointed us to bugs and
  inconsistencies.





3. Limitations and requirements
   ----------------------------

3.1. Scope of this education, training and awareness software
     --------------------------------------------------------
CrypTool is a demonstration primarily for training and awareness
purposes, which is intended to be used at once without any previous
configuration work.

Therefore, the development goal of CrypTool 1 was not to be used
productively for encryption or as a Certification Authority (CA) --
despite the functions are correctly implemented in CrypTool.

For instance -- contrary to productive CA applications -- the CA key pair
is contained directly within the software (source and binary) and
it is protected by will only with a very simple PIN for the CA-PSE
(personal security environment).

The root key of the CA built in CrypTool 1.4.31 has a length of 2048
bit and it is valid for 20 years (July 6th, 2006 - July 6th, 2026).
Certificates issued with the root key of older CrypTool versions
(1.3.05 and older) cannot be imported in version 1.4.31.

Please notice when creating user certificates with CrypTool, that each
CrypTool program contains a root CA with the same key pair.
This means that everybody (!), who uses CrypTool, can sign user
certificates with this built-in CA.

Professional PKI software like the OpenXPKI, the Entrust CA, or the
Microsoft CA additionally manage the whole certificate life-cycle,
offer CRL handling, take care for unique serial numbers and use
defined registration processes.

JCT contains a plugin which visualizes the processes of a PKI.

Nevertheless, all the modern crypto algorithms in CrypTool 1 are
implemented according to international standards and are working
as "well" as in productive applications.


3.2. Win32 environment, rights for installation and usage, Java runtime
     ------------------------------------------------------------------
CT1 v1.4.31 was written to run under the operating system Windows 8 and 10.
CT1 requires a Win32 environment, which is also available in 64-bit Windows.

Some functions like Animal, ECC demonstration, ... [see chapter 1.2, part (3)]
require an installed Java Runtime Environment JRE (version >= 1.7).

The computer equipment should have at least a 300 MHz CPU, 256 MByte RAM,
and 200 MByte free space on the hard drive (low requirements).

Different language versions (localizations) of CT1 can be used in
parallel at one computer, if installed in different directories.

Different users using the same PC can have different settings (because these
settings are stored in the user-specific area of the Windows registry).

Usage of CT1:
 - CT1 can be run without having administrator access rights.
 - Explanation:
   When using the CrypTool application you need write access for:
    - files within the CrypTool directory PSE (for the PKI key management),
    - files within the user-specific TEMP directory
      (for storing temporary files),
    - the user-specific area of the Windows registry (to store user settings).

Installation of CT1:
 - Also the installation can be done without having administrator access rights.
 - Explanation:
   During the installation process persistent data is stored at the following
   places, so the installing person needs to have write access for:
    - the CrypTool directory,
    - the user-specific area in the Windows registry.


Remark 1 -- Details concerning access rights:
a) Program Directory:
   For a successful installation the installation directory selected by the
   user must be writable during installation.
   Two sub-directories of the installation directory ("pse" and "examples")
   will be enabled for writing for everybody who is in the group "Users".

b) Windows Registry:
   To enable the registration of the file extension ".aes" for AES-Tool,
   the following part of the registry needs to be writable during installation:
   HKEY_CLASSES_ROOT
   HKEY_CLASSES_ROOT\Applications

   CT1 will only be listed as installed application in the control panel
   (System -> Software) if the following registry key is writable:
   HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Uninstall

c) Start menu:
   CT1 is installed in the Start Menu for all users if the following
   directory is writable during installation:
   %allusersprofile%\Start Menu\Programs
   If this directory is not writable CT1 will be installed in:
   %userprofile%\Start Menu\Programs.


Remark 2:
Event: The CT1 application stops execution with "Could not create
       temporary file".

When CT1 creates a new temporary file it tries to write the file in one
of the following directories: 
 1. the one of the local variable TEMP 
 2. if TEMP is not set: the one of the local variable TMP 
 3. if both variables, TEMP and TMP, are not set: CT1 tries to write the file
    in the folder which is actually set.

Please check the access rights for the directories of the local variables.
In case %TEMP% and %TMP% are not set, please set these environment variables
to an appropriate path. In case they are set please verify if you have access
rights to create files and folders. 


Remark 3:
Where the TEMP directory of Windows is, can be seen by entering %TEMP%
in the Windows Explorer. The value can also be seen and adjusted
via "System Information" --> "Software Environment" --> 
"Environment Variables". Or by setting a value at the commandline.



3.3. Interactive online help under Windows XP
     ----------------------------------------
In CT1 you can get help for each selected menu item via pressing F1.

- For end menu items this always works directly.

- For menu items which itself have submenus this works only if the submenu
  is not popped up (before WinXP it was independent of whether the submenu
  was popped up or not).

  Workaround to suppress a popped-up submenu (with example):
  Select the menu item "Indiv. Procedures \ RSA Cryptosystem":
  If the submenu of "RSA Cryptosystem" pops up, but you want to get help
  for the menu item "RSA Cryptosystem" itself, close the submenu of
  "RSA Cryptosystem" using the Esc or the left arrow key, and then
  press F1.


3.4. Support for different languages
     -------------------------------
Program, help facility and the documentation are designed to run
in more than one language.

For each supported language CrypTool 1.4.31 comes with an extra installation
program (setup).


3.5. Restrictions / features / hints & tips
     --------------------------------------
- In order to demonstrate the RSA cryptosystem and to factorize
  integers CrypTool uses the long integer arithmetic of the Miracl
  library. We restricted the integer bit length for RSA to 8192.

- From binary files "only" the first almost 2 GB can be loaded into
  the hex editor (< 0x7ffff000 = 2.147.479.552 Bytes).

  In contrast, text files can be loaded in unlimited size by the text
  editor (if you got enough resources on your pc).

- Reading and saving text files always use the two characters CR/NL
  (as usual under Windows) to characterize the begin of a new line.
  This means that documents you get from Unix, where a new line is
  characterized only with the character LF) are getting longer [LF
  is changed into CR/NL]. So the validation of a signature could fail.

- Text boxes within dialogs are built with one of two different editor
  controls. They handle pressing the enter key at the key board differently:
  a) Scintilla: Enter adds CR/NL and moves the cursor to the next line.
  b) Standard MFC editor: Pressing Enter moves the focus away from
                          the text editor and tries to trigger the
                          OK button.

- Display of special mathematical characters within the HTML help:
  Microsoft's HTML-Help calls the predefined Microsoft Internet Explorer
  (IE). Version IE 6 sometimes has problems, to display mathematical
  characters like the Gauss bracket.
  If your computer has IE7 as predefined Microsoft browser, this works ok.
  The basic HTML files, which are aggregated within the CHM file are
  displayed correct with IE7 and Firefox 1.5 or higher.
  Within the online help chapter about the modulo operator the Gauss
  bracket is used to describe the next lower integer.

- For performance reasons it was decided that CrypTool limits the
  document size when performing n-gram analysis:
   - for binary data up to 64 kByte and
   - for text data up to 256 kByte.
  Files opened, which are longer, are truncated -- only in this
  special analysis -- to this maximal length.

- Hash values of external files can be calculated for files of any size.
  Remark: Loading a file, which is longer than the maximum size of the internal
  editor, then the calculated hash values are not the same, as the document
  shown in the editor was truncated.

- SMIME Flash Video bug
  > Error description:
    Flash videos of the type ".flv" are opened with the CrypTool
    player for flash animations after CrypTool was started and
    a flash animation (like  S/MIME or Rijndael) was opened.
  > Solution:
    Manual definition of the correct player. Therefore right-click
    on a ".flv" file and choose "Open with ...". Now select the
    desired player using the shown list and set the checkbox at
    the bottom ("Always use the selected program to open this kind
    of file"). Afterwards click "OK" and from now on ".flv" files
    will be opened with the correct player.

- AES-Tool:
  - To store a file in an encrypted manner as an self-extracting archive
    the file may not be bigger than 4 GB.
  - But if just create the purely encrypted AES file without self-extracting
    code then the original file maybe significantly larger than 4 GB.

  Please keep in mind, that the output of the stand-alone AES-Tool
  is not identical with the output you get within CrypTool, using
  the menu item sequence "Crypt/Decrypt \ Symmetric (modern) \
  Rijndael (AES)"  (even if you create a file with has the extension
  "aes"). CrypTool itself currently uses a fixed IV (0), which is
  not stored. AES-Tool uses a random IV, which is appended together
  with the file name to the end of the encrypted data.


3.6. Using certificates and keys created with older CrypTool versions
     ----------------------------------------------------------------
Please see chapter 4.3, describing this when doing the installation.



4. Installation / de-installation / key usage / operating
   ------------------------------------------------------

4.1. Installation
     ------------
To install CrypTool on your PC, copy the CrypTool setup executable
to a suitable place in the file system and double-click on it.
The default target directory is  "C:\Program Files\CrypTool".
The target directory can be altered in the installation routine.
You need access rights for the target directory.

If you install it as administrator in "C:\Program Files\CrypTool"
then you still can run CrypTool later as a normal user.

If you change the name of the target directory "CrypTool" e.g. in
"CrypTool-1.4.31-Final-en", then the entry in the start menu of the
Windows task bar will adapted accordingly.

After creating the setups they have been scanned locally with the
antivirus products from Symantec and Avira, and remotely at virustotal.com:
There only 2/50 scanners wrote complaints. These came from two exotic products
called Bkav (HW32.Packed.B5F3) and Qihoo-360 (HEUR/QVM20.1.0000.Malware.Gen).
We consider these two warnings as false-positives.


4.2. De-installation of CrypTool
     ---------------------------
To de-install CrypTool v1 there are several ways. These are the easiest ones:
1) Use the "Start" menu entry in the Windows task bar.
   Go for "All programs" \ "CrypTool".
   Click in de CT menu at "Uninstall CrypTool".
2) Use the Windows window "Properties" and search for "installing and removing
   programs". There you get a list of installed programs and click on CrypTool.

Sometimes the JAR files cannot be deleted because Windows and the JRE
report that the file is still in use despite CrypTool and all its stand-alone
programs are closed.
After rebooting the system the JAR file and the whole directory can be
deleted.


4.3. Repeated usage of keys
     ----------------------

4.3.1. Keys of previous versions
       -----------------------------------------------------------
If you already possess an earlier version of CrypTool, the installation
program tries to de-install the old version of CrypTool before
installing the new one.
Please note:
- If during de-installation not all of the directories and files in
  the program directories (normally "C:\Program Files\CrypTool")
  will be deleted, delete these manually.
- De-installation will delete all user generated asymmetric keys and
  certificates.

If you intend to further use these keys and certificates also in the
newly installed version of CrypTool, then there are two alternatives:
a) Import from a CrypTool version older than version 1.4.00:
   - For RSA and DSA keys:
     You can export these RSA and DSA PSEs with the old CrypTool into
     the PKCS#12 format; and import these files with the new CrypTool.
   - For ECC keys:
     Here it is enough to copy the according files
     (e.g. [da][db][EC-prime239v1][1131039030][d] )
     from the old CrypTool\pse directory into the new one.
b) Import from CrypTool version 1.4.00:
   Copy the entire pse\ directory into another directory BEFORE doing
   the uninstallation. After the installation of the new version copy
   the saved pse\ directory to the installation folder.

Please note that it might be necessary to adjust the access
permissions if multiple users want to share one CrypTool
installation. In that case set the access rights in the
sub-trees "pse\" and "pse\pseca\" to full access for each user.

The "pse\" sub-tree should not be  altered manually -- because if the
structure becomes inconsistent, it may be necessary to completely
reinstall CrypTool in order to use the certificate-based methods.


4.3.2. Keys stored in the files of the PSE directory
       ---------------------------------------------
The RSA and ECC key created in the menu "PKI" are stored in the directory
PSE (the keys of the classical cipher methods are not permanently stored).
From version 1.4.20 a user-specific directory is used as PSE directory
(not the actual installation directory any more), to avoid access problems
in multi-user environments.
So CrypTool accesses its asymmetric keys and certificates by default from
the user-application directory. When a user calls CrypTool the first time,
it determines this directory using the environment variable APPDATA, and
then the CrypTool program directory pse\ is copied completely into the
user-application directory. These user-individual keys have the following
benefits:
- There is no need any more for write access to parts of the program directory,
- Most (all) read and write problems in multi-user environments should be
  solved so [see chapter 4.5.b)], and
- When a new installation is done, the user-individual keys are not overwritten.

You can enforce the old behavior if you set the registry entry
HKEY_CURRENT_USER\Software\CrypTool\Settings\UserKeyStore\UseUserKeyStore
to the value ‘0’ (this registry variable is visible after the first call of
CrypTool).


4.4. Installation under multi-user operating systems
     -----------------------------------------------
In multi-user systems the administrator has full access to the whole file
system; the other users are normally restricted.

If a normal user installs CrypTool he needs write access for the
directory in which CrypTool should be installed:
- e.g. for the directory %ProgramFiles% (normally C:\Program Files),
  if the sub-directory "CrypTool" does not already exist;
- or for the directory  %ProgramFiles%\CrypTool (C:\Program Files\CrypTool),
  if this already exists.
If he does not have these access rights, the installation program stops.

Therefore, as a normal user without admin access rights, you should specify as
target directory a so called "local directory" (instead of "C:\Program Files").
"Local" and accessible for any user could be e.g.: %ALLUSERSPROFILE%
(Default is: "C:\ProgramData").

If you install CrypTool without administrator rights and you also have no
write access to %ALLUSERSPROFILE%\Start Menu, then the CrypTool specific
entries are missing in the start menu of WinXP ("Start \ All Programs").
But every user can add these entries manually.

Remark: In the same way as with %TEMP%, you can see, where these directories
are on your disk by entering in the Windows Explorer %ALLUSERSPROFILE% or
%userprofile%.


4.5. Operating under multi-user operating systems
     --------------------------------------------
a) All user-specific parameters are stored in the local user-specific registry
   (including the files lastly opened or the algorithm options you changed):

b) If the user wants to create (or change) files from within CrypTool in
   multi-user systems, then he needs write access for the appropriate target
   directory (or for the appropriate files).
   If this does not work, the user normally gets a warning.
   Write access is explicitly necessary only for two directories:
   - the default Windows directory for temporary files (TEMP) for the
     cry*.* files,
   - the sub-directory "CrypTool\pse", where the created asymmetric keys
     and certificates are stored in.


4.6. Installation on a network drive --> Online help problem
     -------------------------------------------------------
   Especially in courses at schools educational software is installed only
   at the central machine like a Windows network server; the client PCs
   are calling the program from there.

   This works with the program CrypTool itself. But if the online help is
   called from a client PC, then it will not be displayed according to the
   default settings of Windows. This is no problem specific for CrypTool,
   but for all Windows online help files.
   The HTML-help program then normally only shows the content overview of
   the index, but not the content of single help pages.

   Online help under Windows normally comes from a CHM file, which bundles
   all single HTML help files. Within the Microsoft HTML-help program the
   Internet Explorer is used to display the HTML help files bundled in the
   CHM file.

   Early XP versions allowed a client PC to display help files on a server.
   To close a security gap the Windows XP update (KB896358) was distributed.
   Unfortunately this patch also causes that the Microsoft HTML help
   doesn't display the actual help page (but the meta information like
   content, index or search words are displayed correctly), if you want
   to access from a client help files stored at a server.

   WORKAROUND:
   Because de-installing a patch is no good idea and because in this scenario
   it is not wanted to store the CHM files locally, you can change or add
   a special registry entry:

   We assume that the CHM files are stored at "X:\program\CrypTool"
   where "X"  is a server partition with the UNC path "\\server\user".
   Therefore, the full UNC path to the CHM files would be:
   "\\server\user\program\CrypTool".

   Open the Registry Editor (Start > Run... > "regedit") and navigate
   to "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x".
   Create a new key "ItssRestrictions", and in this key create a new string
   with the name "UrlAllowList" and the value
   "\\server\user\program\CrypTool;file://\\server\user\program\CrypTool;
    X:\program\CrypTool;file://X:\program\CrypTool".

   By adding these entries in the registry of all client PCs all clients
   have access to the server partition.

   ATTENTION:
   Changing the registry can cause Windows to stop working. You are
   solely responsible for such changes.
   To change the client's registry you probably need administrator rights.

   Further information:
   - http://support.microsoft.com/kb/896054
   - http://www.robo-forum.de/cgi-bin/ultimatebb.cgi?ubb=get_topic;f=10;t=000065




5. List of delivered files
   -----------------------
The package is distributed as a compressed, self extracting archive
in currently seven different language versions.

The self-extracting archive in English language
           SetupCrypTool_1_4_31_en.exe
contains the following files:

ReadMe-en.txt .... This brief instruction (English).

md5sum.txt ....... MD5 hash values of all files within the CrypTool package.
sha1sum.txt ...... SHA-1 hash values of all these files.
authors.txt ...... Information about the authors of CT1.

CrypTool.exe ..... The executable e-learning program.
aestool.exe ...... The program AES-Tool which encrypts files into
                   self-extracting programs. To decrypt the files, the
                   correct password must be entered.

CrypTool-en.chm .. HTML help archive containing the CrypTool online help
                   system (in English).
rijndael-poster-a4.pdf ... Procedures of the AES algorithm (German)

msvcr90.dll ...... Necessary for CrypTool.exe.
EC-Param.ini ..... Initialization file for public-key procedures
                   based on elliptic curves.
TEST-Param.ini ... Initialization file for random number tests.
secude.dll ....... Library of cryptographic functions provided by
                   Secude IT Security Ltd. (xxx)
ticket ........... License for the Secude library. (xxx)
libxml2.dll ...... Is used by the secude.dll. (xxx)
secidea.dll ...... Is used by the secude.dll for IDEA encryption. (xxx)
srndmskb.dll ..... Used by secude.dll for collecting entropy when
                   initializing the Secude random number generator. (xxx)
db.dll ........... Is used by the secude.dll. (xxx)
secude.xml ....... Is used by the secude.dll. (xxx)
libeay32.dll ..... Library from OpenSSL.
SciLexer.dll ..... Library of the Scintilla text editor.
cracklib_Win32.dll .. Supports PQM tests.

Rijndael-Animation.exe .. Animation (Flash) of the AES algorithm.
Rijndael-Inspector.exe .. Animation (Flash) of the changes within the
                          data block when processing the AES algorithm.
AES_Flussvisualisierung.jar .. Visualization of data changes in AES.

Enigma_en.exe .... Animation (Flash) of the 3-rotor Enigma machine.
Enigma-Help_en.html .. HTML online help of "Enigma_en.exe" (English).
enigma_screenshot1.png .. Screenshot used by the Enigma help file.

eccdemo.jar ...... Demonstration (Java) of adding points on elliptic curves.

NT.exe ........... Educational program (Authorware) of number theory.
TextNumberConverter.exe .. Auxiliary program of "NT.exe".
ToolBarWrapper.dll .. Necessary for the Authorware program NT.exe

NumberShark.exe .. The educational game "Number Shark".
NumberShark_en.chm HTML help archive for the Number Shark online help.
GameData.txt ..... First high-scores for the Number Shark game.

CT-Book-en.pdf ... A book (manual) on cryptography, prime numbers,
                   elementary number theory and the mathematics
                   behind certain algorithms.

CrypTool1-Presentation-en.pdf .. Slides presentation (English)

DialogueSisters.pdf .. Fantasy story by Dr. Elsner describing a
                       variant of the RSA cryptosystem.
ChinLab-en.pdf ... Story by Dr. Elsner about basic number theory
                   problems assigned to Marco Polo by the Great
                   Khan.

Uninstall.exe .... Part of the NSIS installer.
license-en.rtf ... Used from the installer.


examples\ ........ This directory contains various sample files
                   which are used in the scenarios provided in the
                   program. Files ending with the suffix ".txt"
                   are text files. All other files are binary.
                   Files whose names are in the format
		   "XX-enc-YY.*" are encrypted files. Please do
		   not change these files.

examples\CrypTool-en.txt
        \CrypTool-de.txt
        \CrypTool.bmp
        \Startingexample-en.txt
        \Startbeispiel-de.txt
        \Startingexample-pl.txt

        \Playfair-enc-de.txt
        \probetext-de.txt
        \psion-en-enc.hex ... Encrypted file from the tutorial English
        \psion-de-enc.hex ... Encrypted file from the tutorial German
        \vernam.txt

        \original.txt ..... "Harmless" sample for the hash collision
                            demonstration.
        \fake.txt ......... "Dangerous" sample for the hash collision
                            demonstration.

        \letterFromAliceToBob-DECRYPTED-en.txt .. Sample files for the
        \letterFromAliceToBob-ENCRYPTED-en.hex .. demonstration of the
                              side-channel attack on hybrid encryption.

        \state2.hex ....... Un-encrypted sample data of ...
        \state2-enc.hex ... Encrypted sample data of "Rijndael-Animation.exe",
                            used and created with "CrypTool.exe".


cryptochallenges\ ... This directory contains files with ciphertext.
                      Most of them are historically interesting, some are
                      still unsolved.
                      Two special challenges are also included: the
                      Doppelwuerfel (double column transposition)
                      cipher (see www.mysterytwisterc3.org) and the
                      HarryPotter cipher.

cryptochallenges\Schmeh01-Dorabella-enc.txt
                 Schmeh02-Agapeyeff-enc.txt
                 Schmeh03a-Feynman-enc.txt
                 Schmeh03b-Feynman-enc.txt
                 Schmeh03c-Feynman-enc.txt
                 Schmeh04a-Kryptos-enc.txt
                 Schmeh04b-Kryptos-enc.txt
                 Schmeh04c-Kryptos-enc.txt
                 Schmeh04d-Kryptos-enc.txt
                 Schmeh05-Doppelwuerfel-enc.txt
                 Schmeh06-SherlockHolmes-enc.txt
                 Schmeh07-HarryPotter-enc.txt
                 Schmeh08-MathiasSandorf-enc.txt


reference\ ...... This directory contains text files in the languages
                  German, English, French, Greek, Spanish, Polish, Serbian,
                  and Latin. These files are routinely used as
                  references for the analysis of encrypted
                  texts. These files are write-protected.

reference\deutsch.txt   // Extract from the German value-added tax law
         \english.txt   // Extract from Agenda 21 [UN document]
         \homer-el.txt  // Extract from Homer's Ilias
         \genesis-de.txt  // Book of Genesis in the
         \genesis-en.txt  // languages German, English,French, 
         \genesis-es.txt  // Polish, Serbian, Spanish, and Latin.
         \genesis-fr.txt  // The 2-letter codes (en, de, ...) are
         \genesis-pl.txt  // according to the ISO 639 language codes.
         \genesis-sr.txt  // 
         \genesis-la.txt  // 


words\ ........... This directory contains the files used to perform
                   the tests and analyses.

words\cracklib-words        // For test on password patterns
      cracklib_dict.hwm     //
      cracklib_dict.pwd     //
      cracklib_dict.pwi     //
      VigenereAnalysisSchroedelDictionary.txt   // For the Vigenère analysis
      VigenereAnalysisSchroedelDigrams.txt      // (according to Schroedel)
      VigenereAnalysisSchroedelTrigrams.txt     // Language-dependent
      SubstitutionAnalysisMethod2-de.txt   // For variant 2 of the mono- 
      SubstitutionAnalysisMethod2-en.txt   // alphabetic substitution analysis


sage\ ........... This directory contains the source code of the example
                  calculations in the book CT-Book-en.pdf using the
                  computer algebra system SageMath. (xxx)

sage\SAGE-Samples-in-Chap01.sage
     SAGE-Samples-in-Chap02.sage
     SAGE-Samples-in-Chap03.sage
     SAGE-Samples-in-Chap04.sage


pse\ ............. This directory and its sub-directory pseca\
                   are used to store (asymmetric) keys and
                   certificates that have been generated.

pse\[SideChannelAttack][Bob][RSA-512][1152179494][PIN=1234].pse
    [HybridEncryption][Bob][EC-prime239v1][1178702474][PIN=1234]
    [HybridEncryption][Bob][EC-prime239v1][1178702474][PIN=1234].pse

pse\pseca\calog        These files are necessary for the administration
         \capse.cse    of the key database.
         \CA_exts
         \cert.dir
         \cert.pag
         \crls.dir
         \crls.pag
         \CRL_exts
         \user.dir
         \user.pag


animal\ .......... This directory contains files, necessary for the
                   animation program Animal.

animal\animal-2_4_9.jar
      \animal.bat
      \animal.properties
      \AnimalResources
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

animal\anims\caesar_en.aml
            \des_en.aml
            \nihilist_en.aml
            \vigenere_en.aml


Bc\ .............. This directory and the ones below contain the utility
                   BC for calculations with arbitrary precision. It belongs
                   to "NT.exe", from where it can be started directly.
                   Only bc.exe and bc.1.txt are part of the original
                   distribution; the remaining BC files are from the "NT.exe"
                   author and contain scripts with number theoretic functions.

Bc\bc.1.txt
  \bc.deutsch.txt ... German translation of bc.1.txt
  \Bc.exe
  \BCmax.bat ........ Called via F3 from within NT.exe to start BC Calculator
  \BCmin.bat
  \bruch.txt
  \calc.txt
  \dislog.txt
  \ECM.TXT
  \pi.txt
  \polynom.txt
  \Prims.txt
  \quadRest.txt
  \res.txt
  \RSA.txt
  \seed
  \sieb.txt
  \testBruch.bat
  \testPi.bat
  \testPolynom.bat
  \testRSA.bat
  \testSieb.bat

Bc\contrib\Authors
          \bc-1.06.README
          \ChangeLog
          \COPYING
          \COPYING.LIB
          \FAQ
          \INSTALL
          \install-sh
          \News
          \README

Bc\manifest\bc-1.06-bin.mft
           \bc-1.06-bin.ver


xtras\ ............ Files needed by Authorware, used to build "NT.exe"

xtras\BMPVIEW.X32
     \MIX32.X32
     \VIEWSVC.X32


smimedemo\ ............ Files needed by the Flash/Java animation of an
                        S/MIME e-mail.

smimedemo\anim.swf
         \lock2.gif
         \smime.ini
         \SMIME_Animation.exe   [creates temporarily params.xml]
         \start-en.bat
         \swt-awt-win32-3235.dll
         \swt-gdip-win32-3235.dll
         \swt-wgl-win32-3235.dll
         \swt-win32-3235.dll

smimedemo\font\Mathematica7.ttf
              \Mathematica7b.ttf
              \Mathematica7m.ttf
              \Mathematica7mb.ttf

smimedemo\images\encrypt.png
                \sign.png

smimedemo\krypto\CertInfoDialog.class
                \KeyStoreUtils.class
                \KryptoService.class

smimedemo\lib\bcmail-jdk16-141.jar
             \bcprov-jdk16-141.jar
             \commons-codec-1.3.jar
             \mail.jar
             \swt.jar

smimedemo\mail\Mail.class
              \MailService.class
              \SignedDataProcessor.class
              \SignedMultiPart.class

smimedemo\main\Config.class
              \Programm.class
              \Resetable.class

smimedemo\texte\ITexte.class
               \TranslationText.class

smimedemo\userinterface\AliasDialog$1.class
                       \AliasDialog.class
                       \GUI$1.class
                       \GUI$10.class
                       \GUI$11.class
                       \GUI$12.class
                       \GUI$13.class
                       \GUI$14.class
                       \GUI$15.class
                       \GUI$2.class
                       \GUI$3.class
                       \GUI$4.class
                       \GUI$5.class
                       \GUI$6.class
                       \GUI$7.class
                       \GUI$8.class
                       \GUI$9.class
                       \GUI.class
                       \MyInputDialogData.class
                       \PasswordDialog$1.class
                       \PasswordDialog.class

smimedemo\utils\Tools.class
               \Utils$FixedRand.class
               \Utils.class
               \Version.class


tadicnafkeys\ ..... Files belonging to the generic t-adic NAF key generator.

tadicnafkeys\k1.txt
            \t-adicNAF.exe
            \t-adicNAF.hta
            \t-adicNAF.pdf


While CrypTool is running, the following files are generated and
managed:
cry*.* ........... CrypTool writes temporary files to the \temp
                   directory (file names begin with cry*.*).
       These files have the following file extensions:
                  txt -> text file view
                  hex -> hexadecimal (binary) view
                  plt -> diagram/plot view (histogram, autocorrelation)
                  ogl -> OpenGL graphics view
                  org -> copy of an original file after file open
                  tmp -> temporary file for intermediate results




5.1. Checking the integrity of downloaded files
     ------------------------------------------
The integrity of files can be verified using hash values.
Hash values are like fingerprints -- with a small information base you
are able to identify a much larger object.

The files of the CrypTool project normally get onto your computer by
downloading the archive (setup file) and unpacking the archive:
a) Downloadable files:
   At the homepage of CrypTool www.cryptool.org you can find the
   hash values of all files directly downloadable from the English
   Web page within the files md5sum.txt and sha1sum.txt there.
   If you newly calculate the hash of a downloaded file and then
   compare it with the values at the CrypTool homepage, you can see,
   whether you got an unchanged copy of the original file or not.
   If the hash values are different you should download the file
   again and eventually try to find the reason, why you had a
   modified file at your computer.
b) Additionally you can check the files WITHIN the downloaded setup
   archive:
   The hash values of these files are within the files md5sum.txt
   and sha1sum.txt, which will be unpacked as part of the archive.

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



6. Brief history of the released main versions of CT1
   --------------------------------------------------

Release   Date		Size of Windows Setup  Disc space   Released
Version                 English      German    needed EN     by
1.0.01    Oct. 1999      -            1.3 MB    -            DB
1.1.01    May  2000      -            2.3 MB    -            DB
1.2.00    Aug. 2000      -            2.8 MB    -            DB
1.2.02    Dec. 2000      -            3.2 MB    -            DB
1.3.00    Jan. 2002      4.7 MB       4.9 MB    -            DB
1.3.02    June 2002      6.4 MB       6.9 MB    -            DB
1.3.03    Sep. 2002      6.5 MB       6.9 MB    -            DB
1.3.04    July 2003      8.1 MB       8.6 MB    -            DB
1.3.05    Aug. 2003      8.2 MB       8.6 MB    -            DB
1.4.00    July 2006     18.2 MB      18.4 MB    -            DB
1.4.10    July 2007     26.7 MB      27.5 MB    47 MB        DB
1.4.20    July 2008     36.1 MB      37.1 MB    73 MB        DB
1.4.21    July 2008     36.1 MB      37.1 MB    73 MB        DB
1.4.30    Aug. 2010     51.5 MB      52.1 MB    94 MB        DB
1.4.31    May  2017     69.9 MB      70.7 MB   112 MB        CT (xxxok)

Remarks about the (intermediate) versions:
1.3.02  Many new functions compared to 1.3.00
1.3.03  Many minor bug fixes and documentation improvements
1.3.04  Some new functionality, some minor bug fixes, and major
        documentation improvements and enhancements (online help, book)
1.3.05  Some minor bug fixes
1.4.00 Beta10  Dec. 2005  First public beta of version 1.4.00
1.4.00 Beta12  Mar. 2006  Second public beta of version 1.4.00
1.4.00 Beta14  July 2006  Third public beta of version 1.4.00
1.4.00   Many new functions compared to 1.3.05
1.4.10 Beta04  May  2007  First public beta of version 1.4.10
1.4.10 Beta06  July 2007  Second public beta of version 1.4.10
1.4.10  Set of functions and online help heavily enhanced compared to 1.4.00
1.4.20-Beta03  May  2008  First public beta of version 1.4.20
1.4.20  Set of functions and online help enhanced compared to 1.4.10;
        Mostly fine tuning and code stabilization (quality release).
1.4.21  Patch containing also MSVCR71.dll. This DLL is used by the current
        OpenSSL library, but not available by default on blank Windows systems.
1.4.30-Beta03  Mar. 2009  First public beta of version 1.4.30
1.4.30-Beta04  Sep. 2009  Second public beta of version 1.4.30
1.4.30-Beta05  Jan. 2010  Third public beta of version 1.4.30
1.4.30-Beta06  Feb. 2010  Forth public beta of version 1.4.30
1.4.30-Beta07  June 2010  Fifth public beta of version 1.4.30
1.4.30-Beta08  July 2010  Fifth public beta of version 1.4.30
1.4.30  Many bug fixes and enhanced functionality compared to CT 1.4.21
        Disc space needed for the different language versions of CT 1.4.30:
        EN:  93.7 MB
        DE:  94.7 MB
        PL: 100.0 MB
        SR:  93,7 MB
        ES:  94.4 MB
1.4.31-Beta05  July 2012  First public beta of CT 1.4.31
1.4.31-Beta06  Feb. 2013  Second public beta of CT 1.4.31
1.4.31-Beta06a June 2013  Third public beta of CT 1.4.31
                          (first one with a Greek language version)
1.4.31-Beta06a July 2013  Fourth public beta of CT 1.4.31
1.4.31-Beta06b Oct. 2013  Fifth public beta of CT 1.4.31
1.4.31-Beta06c 2015       Further beta of CT 1.4.31
1.4.31-Beta06d 2016       Further beta of CT 1.4.31
1.4.31  Many bug fixes and enhanced functionality compared to 1.4.30.
                          (first one with a French language version)



7. Feedback and contact addresses
   ------------------------------
If you have any problems or find any errors, please do not hesitate to
send an exhaustive description of the problem (and some screenshots)
via e-mail to one of the persons mentioned below.

We would be very grateful for suggestions of any kind regarding
CrypTool and we'll be helpful whenever our time allows.

We would also be interested to hear how and where you use CrypTool.

Contact addresses:
- bernhard.esslinger@uni-siegen.de
- esslinger@cryptool.org
- joerg-cornelius.schneider@db.com
- henrik.koy@db.com




8. References / hints / awards
   ---------------------------

See also:
- https://www.cryptool.org/en/ctp-links
- https://www.cryptool.org/en/ctp-education/ctp-awards


8.1. Articles about CrypTool
     -----------------------
8.1.1. c't 14/2001, pp 204-208
       -----------------------
A 5-page article on CrypTool was published in July 2001 in this
renowned and widely circulated German computer magazine.

8.1.2. DuD October 2002
       ----------------
A 4-page article on CrypTool was published under the title
"CrypTool - spielerischer Einstieg in klassische und moderne
Kryptographie. Neue Version - fundierte Awareness in Deutsch
und Englisch" in the German technical journal "DuD Datenschutz
und Datensicherheit" (Privacy and Data Protection) in the
issue 10/2002.

8.1.3. KES 2/2003 (May 2003)
       ---------------------
A 6-page article on CrypTool was published under the title
"(Ver)Schlüsselerlebnisse - CrypTool unterstützt Verständnis für
die Grundlagen der Internetsicherheit" in the German technical
journal "KES - Zeitschrift für Informations-Sicherheit" (journal
for information security) in the issue 2/2003.
[The Title means "Experience cryptography -- CrypTool improves the
understanding of information security"].

8.1.4. Proceedings 8th German IT-Security Congress of GISA (May 2003)
       --------------------------------------------------------------
The presentation "Awareness in der Informationsgesellschaft: CrypTool
- Kryptographie spielerisch verstehen" was given by Mr Koy at the GISA
(German Information Security Agency) congress 2003 in Bonn.
The article for the congress is within the proceedings, "IT-Sicherheit
im verteilten Chaos", at page 485 - 500.

8.1.5. Datenschutz PRAXIS (June 2005)
       ------------------------------
A 2-page article on CrypTool was published under the title
"Spielend verschlüsseln lernen mit dem kostenlosen CrypTool" by
Dr. Rainer W. Gerling,  in the German journal "Datenschutz PRAXIS",
in the issue June 2005
[The Title means "Learn playfully how to encrypt with the free software
CrypTool"].

8.1.6. Report Touch Briefing Information Security (October 2006)
       ---------------------------------------------------------
The "Touch Briefing Information Security" report 2006 contains the article
"The CrypTool Project -- Improving Awareness and Education for Cryptology".
Accessible via: http://www.touchbriefings.com/pdf/2259/esslinger.pdf
Using the search keywords "awareness cryptology" both google.de and
google.com afterwards listed this article at the top ranking.

8.1.7. DFN-News, Edition 73 (April 2008)
       ---------------------------------------------------------
This edition of the German Research Net organization (DFN) contains the
4-page article "CrypTool -- An e-learning programme for cryptology".

8.1.8. KES 3/2008 (July 2008)
       ----------------------
A 3 1/3-page article on CrypTool was published under the title
"(Ver)Schlüsselerlebnisse NG" in the German technical
journal "KES - Zeitschrift für Informations-Sicherheit" (journal
for information security) in the issue 3/2008.
[The Title means "Experience cryptography Next Generation"].
It deals with the 10th anniversary of CrypTool and the upcoming new
versions.

8.1.9. Telepolis 8/2008 (August 2008)
       ------------------------------
An article by Klaus Schmeh about CrypTool was published under the title
"Werkzeugkasten für Codeknacker" in the German online magazine Telepolis.
[The title means "Tool box for code analysts"].
http://www.heise.de/tp/r4/artikel/28/28389/1.html

8.1.10. Eclipse Magazin 4/2008 (October 2008)
        --------------------------------------
An article by Dominik Schadow about JCrypTool was published under the title
"JCrypTool: Kryptisch gesagt..." in the German "Eclipse" magazine.
This article is available as reprint via the direct download link:
http://www.trivadis.com/fileadmin/user_upload/PDFs/Trivadis_in_der_Presse/EclipseMagazin_Kryptisch_gesagt_Schadow.pdf

8.1.11. ep-Elektropraktiker January 2009
        --------------------------------
A 2-page article on CrypTool was published under the title
"CrypTool - sichere Kommunikation" in the German technical journal
"ep-Elektropraktiker" (Practical Electronics) in the issue 1/2009 by H. Moebus.
http://www.elektropraktiker.de/download/luk-2009-1-06-46867.html

8.1.12. DuD March 2009
        --------------
A 6-page article on CrypTool was published under the title
"CrypTool - an open source project in practice. Lessons learned from a
 successful open source project" in the German technical journal
"DuD Datenschutz und Datensicherheit" (Privacy and Data Protection) in the
issue 3/2009.


Further articles can be found on the following website:
https://www.cryptool.org/en/ctp-education/ctportal-awards/270-ctp-printmedia



8.2. Further references
     ------------------
8.2.1. Wirtschaftswoche special issue
       ------------------------------
In the special issue "Cryptography" of the magazine Wirtschaftswoche
(Sept. 2000) there was a competition entitled "Crack the text!".
Please see http://www.wiwo.de/wiwowwwangebot/fn/ww/sfn/buildww/cn/
cn_artikel/id/62633!100301/SH/0/depot/0/bt/1/index.html.
If you followed the hints provided, you could be able to crack the
task using CrypTool in a few mouse clicks.
The article is no more available at the website.

8.2.2. GISA citizen CD "Into the Internet - with Security"
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

8.2.3. GISA Software Suite BOSS 2.0 (Jan. 2007)
       ---------------------------------------------
The German Information Security Agency (GISA) delivered CrypTool 1.4.00
as part of the software suite "BSI OSS Security Suite 2.0 (BOSS)".
The BOSS-Live CD was replaced by OpenVAS.


8.2.4. Usage in further education / courses (examples)
       -----------------------------------------------
- CISSP, T.I.S.P. - TeleTrusT Information Security Professional, ...

- https://www.tisp.de/
  http://www.logicalsecurity.com/education
  http://www.careeracademy.com
  https://www.cccure.com

- http://www.cdachyd.in/cnss/cnss_ebrochure.htm   (Dec. 2008)
  A 20 week Course on Networking & System Security (CNSS) offered by C-DAC
  Hyderabad, India where CrypTool is used for educational purposes.
  The Centre for Development of Advanced Computing (C-DAC) is primarily an
  R & D institution for Information Technology (IT) based solutions.



8.2.5. Mentions on different web sites
       -------------------------------

a) When writing "The Code Book" Simon Singh collected on his web site
   http://www.simonsingh.net/ a lot of material about cryptography, its
   history and its education.

   Within his newsletter #13 from Feb 11, 2004 he recommends CrypTool as one
   of four worldwide crypto tutorials:
   - www.simonsingh.net/The_Black_Chamber/home.html
   - www.cryptoclub.math.uic.edu/indexmain.html
   - www.antilles.k12.vi.us/math/cryptotut/home.htm
   - www.cryptool.com
   See http://simonsingh.net/2004/02/royal-institution-and-more-mind-games/


b) The Professional Security Testers Warehouse (PST) had a submission by
   Jaganmohan Kataru (CISSP, MCSE) in the Security News Dashboard at Sep
   21, 2005 with the post subject: "eLearning Program for Cryptology":
   http://www.professionalsecuritytesters.org/modules.php?name=Forums&
   file=viewtopic&t=34

   Similar post was at the "CISSP, SSCP, CISM, CISA, ISSPCS, and SANS
   GIAC GCFW Open Study Guides Web site" for Cryptography
   http://www.cccure.org/modules.php?name=News&new_topic=51  with the
   title "CrypTool A great tool to learn more about cryptography",
   posted on Thursday, September 22, 2005.


c) Wikipedia:
   - English:
     - https://en.wikipedia.org/wiki/CrypTool
     - http://en.wikipedia.org/wiki/Cryptography
     - http://en.wikipedia.org/wiki/Topics_in_Cryptography
   - German:
     - https://de.wikipedia.org/wiki/CrypTool
     - http://de.wikipedia.org/wiki/Kryptographie
     - http://de.wikipedia.org/wiki/Wikipedia:WikiProjekt_Kryptologie
   - Polish:
     - http://pl.wikipedia.org/wiki/CrypTool
     - http://pl.wikipedia.org/wiki/Kryptografia
   - Spanish:
     - http://es.wikipedia.org/wiki/CrypTool
   - Serbian:
     - http://sr.wikipedia.org/sr/CrypTool
   - French:
     - http://fr.wikipedia.org/wiki/CrypTool
   - Thai:
     - http://th.wikipedia.org/wiki/CrypTool
   - Italian:
     - http://it.wikipedia.org/wiki/CrypTool
   - Greek:
     - http://el.wikipedia.org/wiki/CrypTool
   - Russian: (xxx)
   - Turkish: (xxx)
   - Chinese: (xxx)


d) A small selection of further pages mentioning CrypTool:
   https://www.a-i3.org/content/view/415/28/
   http://www.fh-lueneburg.de/mathe-lehramt/krypto/krypto.htm
   http://www.kryptographiespielplatz.de/
   http://www.tinohempel.de/info/info/kryptografie/index.htm
   http://www.edoeb.admin.ch/themen/00794/00928/00930/00953/index.html?lang=en
       (see link under "Freeware program with which you can use
                        cryptographic procedures")
   http://www.roehri.ch/~sr/links/crypto.html
   http://www.freebyte.com/security/, http://www.freebyte.com/education/
       (Last updated on April 03, 2015)
   http://nlp.stanford.edu/projects/nmt/data/wmt14.en-de/vocab.50K.de
       [text for Neural Machine Translation :-)]
   http://williamstallings.com/Cryptography/Crypto7e-Student/
        (resource site for the book "Cryptography and Network Security",
         7th edition by William Stallings)
   http://www.garykessler.net/library/crypto.html
   http://blog.learningtree.com/an-introduction-to-using-cryptool-to-show-how-ciphers-work
   ...



8.3. Further freeware projects (Crank, CAP, CryptoStudio, SageMath, etc)
     -------------------------------------------------------------------

a) Available with complete source code are:

- http://freshmeat.net/projects/crank/
  http://freecode.com/projects/crank
  Crank was initiated in January 2001 by Matthew Russell and is
  released under the GNU general public license (GPL).
  In the Crank project the idea was to create a program with a graphical
  user interface under Linux which will allow to automatically break
  classical crypto algorithms.
  The focus was on the analysis of mono-alphabetic substitution ciphers
  and the development of generic and flexible analysis tools.
  The current version 0.2.1 was released in August 2001. Since then
  no further development took place.
  On the project web page there are also some interesting links
  on classical cryptanalysis.

- http://freshmeat.net/projects/griffon/
  http://freecode.com/projects/griffon
  Griffon was started in 2000 by Adrian Mulvaney and is
  released under the GNU general public license (GPL).
  Griffon is a GTK+ GUI cryptanalysis package for pre-digital ciphers.
  Mono-alphabetic transposition, substitution and Playfair are covered.
  The program includes a customizable frequency count.
  The current version 1.0 was released in November 2000. Since then
  no further development took place.

- http://www.kryptosproject.org/          (old)
  http://kryptosproject.sourceforge.net/  (new)
  Kryptos is an open source project begun at the George Mason University.
  Kryptos is educational software for teaching cryptography with a
  static GUI, but many modern algorithms, which can origin from
  different dynamically selectable crypto libraries.
  It has no cryptanalysis functions.
  The current version Kryptos 3.01 was released in December 2006
  and requires .NET Framework 2.0.

- http://cryptostudio.sourceforge.net/
  CryptoStudio from Prof. Marco Russo
  The current version 1.0 was releases in June 2005 and is available
  in English and Italian.
  It is a GUI (looking like Microsoft's Visual Studio) offering
  functions of the general purpose cryptographic open source library
  OpenSSL and using its command line tools. So the web page states:
  "Many of the CryptoStudio functionality are a mere GUI wrapper of
  OpenSSL tools, intended to make those tools available also to
  uninitiated users".
  Users can also find utilities for file encryption, basic s/mime mail
  management etc., but no cryptanalysis.

- http://gcipher.sourceforge.net/
  GCipher is a small encryption tool for Unix, without online help and
  without cryptanalysis, written in Python.
  The three classic ciphers can be performed via the GUI as well as via command
  line and via network proxy.
  The current version 1.0 was published in June 2003 by Shannon -jj Behrens.

- http://www.nku.edu/~cryptography/doku.php?id=downloads:downloads
  (from http://www.nku.edu/~christensen)
  The Java program CryptoHelper.JAR of the "Math and Computer Science Club"
  at NKU is very complete concerning classical ciphers.
  Last update: Gary Watson, Aug 2005.

- http://www.cs.unc.edu/~stotts/145/homes/crypt/
  Cypher, written in C and FLTK (for Windows and Unix), is a toolkit
  designed to aid in the decryption of historical ciphers by providing
  statistical data and algorithmic analysis on encrypted messages.
  It was developed in a university project by 6 (?) students in 2000.
  The Website contains the source files, but not the executables.

- http://silenteye.v1kings.io/
  https://github.com/achorein/silenteye/tree/0.4/vagrant
  SilentEye is a cross-platform application designed for an easy use of
  steganography. It hides messages in pictures or sounds. It has a nice
  GUI and an easy integration of new steganography algorithms.
  And it can be run from the commandline. It's free under GNU GPL v3.
  Last update: Version 0.4.3, Feb 2013.

- The open-source computer-algebra system "SageMath" has also implemented
  some algorithms from the area of cryptography:
    Ciphers
    Classical Ciphers
    Simplified DES
    Mini-AES
    Blum-Goldwasser Probabilistic Encryption
    Stream Ciphers
    Linear feedback shift register (LFSR) sequence commands
    Boolean functions
    Small Scale Variants of the AES (SR) Polynomial System Generator
    Multivariate Polynomial Systems
    S-Boxes and Their Algebraic Representations
    Hard Lattice Generator
  http://www.sagemath.org/doc/reference/index.html
  SAGE is also used for some examples in the CrypTool book.

- The website of the American Cryptogram Association (ACA), a non-profit
  organization "dedicated to promoting the hobby and art of cryptanalysis".
  This site contains a wealth of code and information for paper&pencil and
  classical ciphers and their cryptanalysis.
  http://www.cryptogram.org/



b) The only other useful programs known to us, which usefully combine
   cryptography and cryptanalysis (under a graphical user interface),
   are such, where the source code is not public:

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
  (single statistical functions and classical encryption methods; was
  available from December 2002 at http://phoenix.goucher.edu/~jtrafton/Crypto,
  link is dead now).

- The Java application "CipherClerk" by Wilhelm M. Plotz
  (encryption and decryption with many classic algorithms;
  last update in 2003)
  http://members.aon.at/cipherclerk/

- CryptoBench - GUI around parts of Wei Dai's Crypto++ library
  Compact and clearly arranged GUI implemented around Wei Dai's
  Crypto++ library (no cryptanalysis).
  The current version 1.0.1 of the CryptoBench exists since 2004.
  Wei Dai's Crypto++ library is open source, the GUI of CryptoBench is
  freeware, but not open source.
  http://www.addario.org/cryptobench/

- "Cryptanalysis Tools" by Steven Kohns
  The program was designed for the Cryptology class at NKU (Northern Kentucky
  University) in Spring of 2004. It is designed to help create and break
  simple ciphers.
  To work under Windows XP the "Windows 2000 compatibility mode" has to be
  enabled.
  Last update: May 02, 2004 - Uploaded Cryptanalysis Project
               Nov 27, 2004 - Version 0.17 (as per splash screen)
                            - Version 0.37 (as per help file)
  http://studenthome.nku.edu/~kohuss/content/crypt.html

- "Cryptography Tools" by Don Spickler
  The Java program was developed at the Henson School of Science & Technology,
  Salisbury University "to help users understand the workings of and the
  cryptanalysis of several classical ciphers".
  There are executable files (no sources) available for Windows, Linux and Mac.
  Last update: Sep 24, 2009 -- Version 1.2.1
  http://facultyfp.salisbury.edu/despickler/personal/CryptTools.asp

- "CryptoCrack" by Phil Pilcrow
  The Windows program CryptoCrack is designed for solving classical ciphers:
  "CryptoCrack can solve over 50 different classical cipher types and in many
  cases without knowing any plaintext or the key length" (cited from 23.10.16).
  So it doesn’t include routines for solving machine based or modern, computer
  based types such as Enigma, AES, DES, Blowfish etc. (see FAQ).
  This tool solves many classical ciphers very fast and very well.
  Initial release: May 29, 2011, ongoing active development.  
  Last update: Mar 2017 -- Version 0.7 beta (version 0.7.6279.17017))
  https://sites.google.com/site/cryptocrackprogram/home

- "CryptoMake" by Phil Pilcrow
  Very exhaustive program to create classical ciphers.
  Initial release: March 5, 2014, ongoing active development.
  Last update: Feb 2016 -- Version 0.2 beta (0.2.5901.21555)
  https://sites.google.com/site/cryptomake/


If we are missing something here or if something is incorrect, please feel
free to inform us, so that we can complete or correct the list.

We explicitly want to state, that we would welcome very much if the
efforts made for these single programs could be combined into one
merged new program. We are very keen about any co-operation!!



8.4. Awards
     ------
In general the biggest award for us is, if CrypTool is broadly used in
education and training. Additionally we have been very glad about the many
positive feedback we got so far. We try to respond quickly also in the future
to any request you have.

CrypTool was honored with the following "official" awards (see web page):

- TeleTrusT Special Award
  The TeleTrusT Special Award for education about cryptography and
  promoting acceptance, awareness and understanding of cryptographic
  methods was conferred at the ISSE conference.

- European Information Security Award 2004
  The CrypTool project was a finalist in the European Information
  Security Award (EISA 2004) in the category education and training,
  hosted by the RSA conference Europe.

- IT Security Award NRW 2004
  CrypTool received the IT Security Award NRW in the category education
  (e-learning / knowledge transfer about cryptology).

- Selected Landmark in the Land of Ideas 2008
  The event series 365 Landmarks in the Land of Ideas is a project of
  Germany "Land of Ideas", a joint nation-branding initiative by Germany’s
  federal government and the private sector. CrypTool was selected in the
  category science and technology.
  The project was presented at a big public event at the University
  of Siegen on July, 22nd, 2008.

Also see
https://www.cryptool.org/en/ctp-education/ctp-awards/259-ctp-awards



A. Appendix
   --------

A.1. .... Roadmap after CT 1.4.31
A.2. .... Successor projects using Java/Eclipse and C#/.NET
A.2.1. .... Design of the successor projects CT2 and JCT
A.2.2. .... Features of the successor projects CT2 and JCT
A.3. .... Possible areas for further development -- Future features, ideas
A.3.1. .... Functionality: Algorithms / Methods
A.3.2. .... Functionality: Analysis
A.3.3. .... Internal interfaces / Editors
A.3.4. .... User interface / Visualizations
A.4. .... Using CT1 on Linux
A.4.1. .... Running CT1 on Linux with Wine
A.4.2. .... Porting draft of CT1 to Linux with Qt


All functions available in CT1, CT2, JCT and CT-Online can be found in an
interactive list of at:
   https://www.cryptool.org/en/ctp-documentation/ctp-functions



A.1. Roadmap after CT 1.4.31
     -----------------------
In general, all bigger new developments from the CT project will go directly to
the two existing successor projects CT2 and JCT (see chapter A.2).

The CrypTool team will continue to fix bugs within CT1.

For those who prefer to keep on developing in C/C++, there will also be
a successor: QCrypTool (QCT).
Here, CT1 is further developed using Qt 5:
- The GUI will be completely written with Qt (instead of MFC) which
  enables platform independence.
- Like JCT, QCT will run on Linux, MacOS, and Windows.
- With Qt, several languages can be combined in one setup and in one
  executable. So within QCT, you can switch the language without a restart.
- A possible further development could be the integration of a fork of
  OpenSSL which implements the set of the Chinese Crypto Standards (which
  is comparable to the NIST standards and even got more attention after
  Edward Snowden's confirmation of the doubts which had been only rumors
  before).
- See https://github.com/flomar/QCrypTool



A.2. Successor projects using Java/Eclipse and C#/.NET
     -------------------------------------------------
The successors of CT1 use state-of-the-art development technology,
current layout techniques and modern software architectures.

A.2.1. Design of the successor projects CT2 and JCT
       --------------------------------------------
a) General wish list according to the user feedback about CT1
   This is the basis for both successor projects, Java-CrypTool and CrypTool 2:
   - Modern pure-plugin architecture
   - All languages supported by one program, one setup
   - More modern layout, less move between different dialogs
   - Standard compatibility in the user interface
   - More user interaction
   - Dynamic change between languages
   - Dynamic change between crypto providers
   - Automatic updates via the Internet (keep opened files after new start)
   - Implementing all functions as threads (parallel, interruptible)
   - Functions use all cores is available
   - Easier handling of cascades using the existing building blocks
   - More customizing opportunities concerning alphabets of classic ciphers
   - Offer a recorder for user interactions (action history)
   - Handle all files as stream to be able to operate very big files
   - Control of all functionality also from the command line

b)  Java-CrypTool (JCrypTool, JCT):
   - Completely new designed CrypTool in Java using Eclipse/RCP
   - Platform independent --> Support for Windows, MacOS, and Linux
   - Usage of SWT for the GUI
   - Strictly using the standards of Eclipse
   - Bouncy Castle (BC) and FlexiProvider (FP) are used as crypto providers.
     FP will become part of BC.
     Offer JCT as a dynamic graphical frontend for BC.
   - XML Security (demonstrator for XML signatures)
   - Cooperation with the chair of Prof. Buchmann, TU Darmstadt for the
     integration of FP
   - For newbies, but also for experts
   - Using of Github with Git for source code management:
     https://github.com/jcryptool/
     https://github.com/jcryptool/core
     https://github.com/jcryptool/core/wiki
     https://github.com/jcryptool/crypto
     https://github.com/jcryptool/doc

c) CrypTool 2 (CT2)
   - Completely new designed CrypTool in C# using the .NET framework and WPF
   - Strictly using the standards from Microsoft .NET (looks like Office 2007)
   - Usage of Windows Presentation Foundation (WPF) to create multi media
     GUIs using vector graphics
   - The whole project can be build with the respective most current, free
     Visual Studio Express-Edition for C#.
   - Available as crypto providers are:
     - the .NET crypto provider,
     - libraries like GMP/MPIR, Crypto++ via wrappers, and
     - BouncyCastle for C#.
   - Steep learning curve for newbies by visual programming
   - Close cooperation with the chairs of Prof. Weis in Duisburg-Essen and
     Prof. Wacker in Kassel
   - Usage of Subversion for source code management.



A.2.2. Features for the successor projects CT2 and JCT
       -----------------------------------------------
The new versions are (see chapter A.2.1):
- CT2: CrypTool 2.x   and
- JCT: JCrypTool 1.x



Some (not all) features of the release versions of the successor projects:

-------------------------------------------------------
- CT2  Visual programming (composition of protocols and workflows)
- CT2  Tutorial: Prime number visualizations
- CT2  Tutorial: Bleichenbacher attack, enhancements by Kuehn
- CT2  Tutorial: Lattice-based cryptography
- CT2  WEP encryption and analysis of WEP encrypted messages (attack
       on the WEP protocol)
- CT2  DH-Key Exchange
- CT2  Visualization of Quantum Key Agreement, BB84 protocol
- CT2  Steganography methods
- CT2  Smartcard plugin (it sends commands to a smartcard using
                         the PC/SC interface in Windows)
- CT2  Cube attack on symmetric ciphers (I. Dinur and A. Shamir)
- CT2  SAT Solver
- CT2  Homomorphic encryption (Paillier)
- CT2  Quadratic sieve (significantly faster than in CT1)
       For time measures compare:
       - https://www.cryptoportal.org/details_links.php?PHPSESSID=1a3ea85bebc01e983a852682cecc48b3&link_id=69
       - http://bscw.schule.de/pub/bscw.cgi/d864899/Schulz_Witten_Zeit-Experimente.pdf  (this article is in German only)
- CT2  GNFS (using YAFU and msieve)
- CT2  Solitaire encryption and analysis
- CT2  Decimalization methods (Visa, Modulo, Multiplication, IBM)
- CT2  Mathematical tools like Berlekamp-Massey
- CT2  Encryption of and distributed analysis against Vigenère autokey
- CT2  Powerful analyzers against classical ciphers (including Enigma)
- CT2  Search for word patters using norms (i.e. "together" = 12341546)
- CT2  LFSR, NLFSR
- CT2  Symmetric encryption methods by Ecrypt (SOSEMANUK, ...)
- CT2  Encryption with Enigma, Purple, T310/50, M209, M-138
- CT2  Encryption with DES, AES, PRESENT, Twofish, ...
- CT2  Encrypt plaintext with AES by using an ASCII password (which is
       converted to an AES-key by using PKCS#5). The result is base64-encoded
       for easy copy&paste e.g. to an email. Linkage with the smartphone app
       CrypDroid.
- CT2  Evaluation of the password strength

-------------------------------------------------------
- JCT  Adaptive navigation pane, optionally as tree or palette, with filtering
- JCT  Vigenère autokey encryption
- JCT  Visualization of classic (analysis) methods
- JCT  Adjusting of all detail parameters of modern algorithms
       in the FlexiProvider perspective (especially Post-Quantum algorithms)
- JCT  Dragon cipher & LFSR
- JCT  Analysis methods for entropy, Friedman, frequency 
- JCT  Detailed visualization of the inner states of DES (round keys, fixed
       points, avalanche effekt within the S-box)
- JCT  Visualization of calculations on elliptic curves over R, F(p), and F(2^m)
- JCT  Visualization of Kleptography algorithms (four malicious methods against
       RSA key generation incl. SETUP attack)
- JCT  Multi-partite key exchange
- JCT  Homomorphic encryption (RSA, Paillier, Gentry&Halevi)
- JCT  PQC signature schemes (WOTS, MSS, XMSS-MT)
- JCT  Analysis of transposition ciphers using the ACO algorithm
- JCT  Visualization of zero-knowledge proofs
- JCT  Running-key encryption and its automatic analysis (Viterbi)
- JCT  Verifiable Secret Sharing
- JCT  Games: Number Shark (incl. heuristic solvers) and Sudoku solvers
- JCT  Powerful action history and cascading possibility
- JCT  Various customizing opportunities concerning the alphabets
       of classic ciphers and a command line interface
- JCT  Visualization and explanation of Android's unlock pattern (AUP)



A.3 Possible areas for further development -- Future features, ideas
    ----------------------------------------------------------------

The developer wikis of CT2 and JCT each contain a list with development tasks
for further features requested by users:
- CT2: https://www.cryptool.org/trac/CrypTool2/wiki/StudentTasksProposals
- JCT: https://github.com/jcryptool/core/wiki/project-Ideas

Below are further possible topics for enhancements which have been requested
or discussed already by users of CT1.
Topics already planned in CT2 or JCT are marked accordingly.


A.3.1. Functionality: Algorithms / Methods
       -----------------------------------
- Offer an interface, so that the offline programs JCT and CT2 can be called
  via web browsers

- Implement additional algorithms on each topic:
    * Codes:
       - T9 (http://en.wikipedia.org/wiki/T9_%28predictive_text%29) etc.
    * Encryption:
       - Classic procedures (incl. analysis): e.g.
           - Sigaba
           - Further rotor ciphers, Hagelin, Lorenz machine
           - JCT: Extend the alphabets of the classic ciphers to 256 characters
       - Symmetric procedures:
           Camellia (RFC3713), RC5 and Gost (http://vipul.net/gost),
           Radio Gatun, SOSEMANUK, VSH, ...
       - Public-key methods: McEliece, Rabin, NTRU
       - Demonstration of visual cryptography
       - Integrate new methods developed at Ecrypt (Network of Excellence
         in Cryptology). See http://www.ecrypt.eu.org
    * Hashes:
        - CT2: Tiger (http://www.cs.technion.ac.il/~biham/Reports/Tiger)
        - All SHA-3 candidates
          (http://csrc.nist.gov/groups/ST/hash/sha-3/index.html)
    * Protocols / weaknesses in protocols:
       - Visualization of man-in-the-middle attacks
       - Visualization of SSL
       - Blind signatures
       - Electronic voting
       - CT2 Virtual Credit Card Numbers (VCC) and check sums
       - JCT Visualization of the KEGVER protocol and further kleptographic
             methods (http://www.cryptovirology.com)

- Offer fast selection between different encryption methods using a
  dialog box instead of using menus (and making all parameters of these
  algorithms customizable) (see CryptoBench)

- Generation of all hash values using a regular expression as password
  pattern (Hartmann)

- Generate cryptographically strong elliptic curves and use these
  to implement a cryptosystem based on elliptic curves.
  Here, one could take the cryptosystem developed by Menezes and
  Vanstone that was proposed by the authors in 1993:
  A. Menezes and S. Vanstone,
  "Elliptic curve cryptosystems and their implementation",
  Journal of Cryptology, 6 (1993), pp 209-224,
  or by Dan Bernstein.

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
  - Usage of the already integrated 3-D visualization of random numbers
    in order to emphasize weaknesses of random number generators
    (like with LCG) by showing the hyper planes you can see when turning
    the cube.
  - Additional randomness tests (from the Spanish version?)
  - CT2  NIST Random number test suite

- Implement further standards and refer to all places, where
  they (e.g. PKCS#5) are used, from a menu and from the online
  help (main task here is user interface and documentation).

- JCT  PGP-S/MIME interoperability

- Reveal the link between CrypTool (PKCS#12) and PGP by enabling the
  use of PGP keys within CrypTool.
    Idea: Open private-key ring via a given password, analyze its
    structure, get the private key (PGP sources are available) and
    use this key, to decrypt PGP files with the algorithms implemented
    in CrypTool. This shows, that PGP also uses the standard algorithms
    used e.g. in S/MIME.

- Create a test suite with examples and solutions, in order to
  automate testing and to make sure, that program changes do not
  negatively influence old and running functionality:
  a) interface, to load test cases manually into the dialog boxes
  b) interface, to load test cases from a file into the different
     dialog boxes.
     Maybe build a script language to control all dialogs or
     use automated test tools off-the-shelf.
  c) create command line interface, so test cases can be read from a
     file without using dialog boxes (no user interface), solved
     and the result again written to a file:
     -> automatic comparison of the solution possible
     -> new version can be tested easier.



A.3.2. Functionality: Analysis
       -----------------------
- Usage of distributed computing for cryptanalysis
- Offer a cryptanalysis framework to have a toolbox for fast code breaking
- CT2  Framework for distributing cryptanalytic calculations
- CT2  Toolbox for creating and analyzing stream ciphers
- CT2  Framework to create and analyze LFSR stream ciphers
- CT2  Framework to analyze side-channel attacks

- Especially desirable is cryptanalysis in all forms and if its
  visualization could be enhanced.

- Offering a (good) analysis for ALL implemented encryption methods (which
  is at least for the classic methods better than brute-force). E.g. for
   - Nihilist
   - Turning grille (Fleissner)

- Attack on symmetric encryption methods, where you have the flexibility
  to reduce the parameters of the encryption method.

- Differential cryptanalysis on symmetric ciphers (DES, ...).

- Enhance the brute-force possibilities: use knowledge about
  - parts of the plaintext,
  - parts of the key.

- Demonstration, how long an exhaustive key search lasts (depending
  on the key length).

- Analysis to be newly implemented for:
   * homophone encryption
   * permutations/transpositions
     - Known-plaintext analysis of the double column transposition,
     - Ciphertext-only analysis of the double-column transposition.
   * Playfair encryption
      - C sources from Gunnar-Andresson are available.

- Analysis to be improved for:
   * mono-alphabetic substitution
      - explicitly show mutually inverted digrams like "th"/"ht" and
        double-characters like "tt".
      - CT1: Show the characters which have been substituted not only
        capitalized but also in red to enhance readability.
   * illustrate the Vigenère analysis more deeply:
      - Enable to enter not only a fixed value for the key length,
        but also a range of values (e.g. "2-9"). Then show in the next
        dialog for each length the statistically most appropriate
        key. Potentially show the top-10 most likely keys for a given length.
      - Clicking at one of the displayed key proceeds the according
        decryption. Clicking an additional button performs the
        decryption for all displayed keys.
      - The analysis option "Show base ciphers" currently shows for
        each "column Caesar" the graphics correlation and histogram.
        Additionally the text for each column Caesar could be
        displayed.

- Use word lists (dictionary) for all attacks, not only for substitution.

- Usage of algorithms from the area of AI (artificial intelligence) and
  GP/GA (Genetic Programming/Algorithms) in order to automatically analyze
  (classical) encryption ciphers.

- CT2: Mass pattern search: Implementation of an enhanced high performance
  pattern search for pre-given standardized and regular patterns of any
  size (e.g. in order to find multiple patterns in one file which are
  also there in another file), or which searches for unknown but
  repeated patterns in a document.
  The search could be enhanced by additionally offering replacing.

- Facilities for correcting individual characters in the analysis
  of XOR, ADD, Vigenère. Ignorance of non-encrypted areas.

- Display of second-, third-, etc. best hit in XOR/ADD analysis
  (this could lead to a shorter key length).

- Autocorrelation: Execute further operations (XOR, ADD, ...) in the
  blocks prior to super imposition, if appropriate.

- Make it possible to edit the homophone key (necessary for the
  analysis of homophone encryption)

- Floating entropy: automatic search for places in a document with high
  entropy

- Extend existing limitations of the N-Gram analysis concerning
  the file size (maybe give user feedback and allow to stop calculation,
  if a high amount of time is necessary).

- Timing Attack on RSA / Advantages of blinding

- Visualize current hash attacks (e.g. create postscript documents according
  to Lucks or PDF documents according to BSI with the same hash value)
  and explain the  scenarios.

- Usage of Rainbow tables

- Implement and/or visualize further attacks against concrete protocols
  in order to improve future concepts.



A.3.3. Internal interfaces / Editors
       -----------------------------
- Store all used keys in a container.
  Enable showing all keys for the different encryption methods in a dialog.
  Enable to store them permanently as a file in a format common for all
  CrypTool versions.

- In the successor projects of CT1: Make sure a separation of cryptographic
  functions from the user interface (this makes ports and debugging easier).

- Enable customization wherever possible:
  Offer an option to set e.g. initial vector, number of rounds, key
  length, word size or the kind of padding (e.g. for the RC5 algorithm,
  see RFC2040).
  Then these additional customizations must also become part of the
  format for the internal key storage.

- Libraries for arbitrary length numbers and cryptography:
   - Support further libraries (FLINT/C, Wei Dai's Crypto++, ...)

- JCT  Commandline functionality (for users and for test-automation)



A.3.4. User interface / Visualizations
       -------------------------------
The following suggestions are mostly related to CT1. However, similar
requirements are there for all crypto programs wit a GUI.

- There are several dialogs within CT1 where special input fields
  expect a special number format (decimal, hexadecimal, ...).
  The dialog "The RSA Cryptosystem" e.g. allows to enter the message
  as text (with an alphabet defined by you) or as a number (with 4
  different base numbers); compared with that the primes here can
  only be entered as decimal numbers or as terms of decimal numbers.
  Alternatively an a-modal window for interchanging the bases could
  be used.

- It would be useful if a calculator can be called from within
  CrypTool as an a-modal window: it should accept terms with numbers
  of any basis as input and it should show the result in several
  fields in parallel with different number bases.
  The right output number representation could be transferred into
  the clipboard via button, or the mouse could drag the field content
  directly into the entry field in the CrypTool dialog box.

- An interactive interface for calling the CAS system SageMath would be
  interesting (http://www.sagemath.org/).

- Visualize generally the according mathematical basics, e.g.:
  - using a text book
  - using Sage notebooks like the ones for ECC introduction by
    Maike Massierer at:
      - http://web.maths.unsw.edu.au/~maikemassierer/ecc-notebook
        (Version 1.3, January 2011) (xxx)
    Part 0, the cover page contains no calculations, but the links to the
    remaining parts; in order to execute the calculations within the
    remaining parts you have to make copies as Sage user.
  - like PascGalois Software (Group Calculator)
      - http://www.pascgalois.org/software.html
  - see also http://www.martindalecenter.com/Calculators2_6_NZ.html
  - http://world.std.com/~reinhold/BigNumCalc.html
  - http://mathforum.org/library/resource_types/calculators/?keyid=28652723&start_at=301&num_to_see=50
  - http://www.hbmeyer.de/pythagen.htm (Pythagorean Triples)

- CT1: Offer a customizing feature to the user, so that he can choose
  that all new windows appear within the main windows (as right now)
  or as "free" (modal or a-modal) windows outside the main window.
  E.g. show single dialog windows in an a-modal way (e.g. N-gram
  analysis, manual analysis, hybrid encryption demonstration).
  This allows that one can switch between the main window and
  the dialog window without closing the dialog window first
  (the burden is a more complex control mechanism, handling of
  multiple calls to the same dialog, update after change of
  window focus or after changing the underlying original data
  within the main window, ...).

- AES-Tool -- enhancement as standalone tool:
  - Integrate the PKCS#5 dialog to let the user enter letters in
    his used way: then set random values for salt and iteration
    counter and ask the user, to remember the generated hex value
    or store it securely.
  - Also encryption of complete directories.
  Generally within CrypTool the keys of modern encryption methods
  intentionally must be typed in using the hex format.
  We pedagogically did it by will, that everybody sees what type of
  key the different methods expect: classical methods expect a key
  built from the used alphabet, modern symmetric methods expect
  binary data of key length 56 bit till 256 bit.
  On the other hand people normally are used to type their input using
  all ASCII keyboard buttons. Within a productive application the key
  should NOT be built of ASCII letters. If it is wished to use a ASCII
  password then it is better to generate a good key from the password.
  Within CrypTool both requirements (key input via ASCII and showing,
  that good hex keys are necessary) could be combined in the
  following way:
  Within the hexadecimal key input dialogs a button should be added,
  calling the dialog "Indiv. Procedures \ Hash \ Key Generation from
  Password (PKCS#5)".
  The called dialog then is already customized with the right key length
  and after pushing "Back" the generated key will be used as hex
  input for the encryption method. AES-256 needs SHA-256.
  CT1: From AES-Tool 2.6 (deployed with CT 1.4.31) you can enter the key
  in ASCII form. The ASCII characters are then transformed via PKCS#5. 

- Make it customizable by the user, how big the part of text and binary
  files can be, which CrypTool will load.

- New magnification function in the display for graphics and/or
  display of the coordinates of the current mouse pointer position.

- CT1: Make all dialogs thread-safe, so the user can cancel long-running
  transactions, without stopping the whole program via the Task Manager.
  This is already implemented in the factorization dialog.
  This is especially meaningful for cryptanalysis (it would be necessary
  for the known-plaintext analysis of the single-column transposition):
  If the upper bound of the permutation length is not limited, it takes
  a felt eternity if the upper bound is >900. Here we limited the length of
  the permutation to 100 for consistency reasons, because our implementation
  of the permutation cipher does not allow longer permutation lengths.

- Visualization:
   - Visualization of dependencies and workflows in protocols
     (not only "simple" algorithms) is a meaningful enhancement.
   - Attacks on weak RSA keys are described in the online help of CT1
     at Help \ Scenarios \ RSA cryptosystem (demonstration),
     under the topic "3. Attack on the RSA algorithm", which explains
     that factorization of the module can break the method.
     This is implemented, but not visualized.
   - Attacks on other asymmetric methods are not implemented in
     CrypTool yet. To attack Diffie-Hellman, DSA, or EC-DSA, one
     has to calculate "discrete logarithms". After implementing
     this it also could be visualized.
   - Show the avalanche effect at hash or encryption methods.



A.4. Using CT1 on Linux
     ------------------

A.4.1. Running CT1 on Linux with Wine
       ------------------------------
In a short test under MINT 17.3 with Wine 1.8.0 in October 2016 the setup of
CrypTool 1.4.31 Prefinal (compiled with VS2008) worked fine.

Most functions in CT1 itself (like encryption methods and RSA key generation)
work well under Wine. Wine is much more stable than 6 years ago.
- ok: Calling most dialogs (incl. RSA-AES hybrid encryption demo),
      performing the calculations, clicking F1 for context-sensitive help
- ok: Warning dialog, if Java isn't installed in Wine
- ok: Showing the readme file in IE (called from CT1 via menu Help)
- nok: Calling from CT1 via menu Help a PDF (book, presentation):
       Wine unsuccessfully searches Acrobat Reader (even if Okular and
       Acrobat are there).
- ok: In the online help: Call of inner links within the online help
- nok: In the online help:
       - Calling external programs from the help (readme.txt in notepad, PDFs)
       - Navigation via the back and forth buttons
- nok: Some malfunctions within the Macromedia application NT

Generally we do not make extra efforts to support Wine.
Instead of that, please try the platform-independent version JCT which also
runs under Linux (see chapter 3.5).


A.4.2. Porting of CT1 to Linux with Qt
       -------------------------------
A first project to port CrypTool 1.x to Linux using GCC 4.x and Qt 4.x
was started outside of the actual CrypTool project by single persons,
but unfortunately not finished because lack of time.
- The libraries from Miracl, NTL, OpenSSL and GMP/MPIR are available.
- Dividing the complete task in meaningful parts is recommended:
       - graphical user interface: This is the main task.
       - functionality implemented in pure C/C++: ok
       - online help in HTML: ok.
- The first beta was released in November 2007.
  The second beta ("still no full functional version", 11 % of the
  planned tasks) was published mid December 2008.
- http://www.cryptoolinux.net/

With QCrypTool (QCT), the CT core team will build a successor of CT1
using Qt 5 (see A.1).

################################################################

Please also try out the new versions CT2 and JCT.
You can find them at  www.cryptool.org  too.

Entry in Wikipedia: https://en.wikipedia.org/wiki/CrypTool

