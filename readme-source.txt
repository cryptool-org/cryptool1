
CrypTool 1.4.31  (August 2015)
~~~~~~~~~~~~~~~


Readme for developers of CrypTool v1 (CT1)
------------------------------------------


Content:
========
A) How to build CT1 from the current C++ sources?

B) What to deliver back, if you make enhancements to CT1?




A) Readme for developers who want to build CT1 from the current C++ sources
===========================================================================

1. Files you need
   ~~~~~~~~~~~~~~
readme-source.txt 	This readme
CrypTool\source\ ...	Directory tree with the source code for building CrypTool.
			Files can be downloaded from subversion repository via Internet.


2. Tools you need
   ~~~~~~~~~~~~~~
For building CT1 completely you need:
a) Microsoft C++ Compiler:
    - Visual Studio 2008.
    - Older compilers like Visual Studio 2005 are no longer supported and will not work 
      with the current solution and project files (*.sln, *.proj).
    - The *free* Visual C++ 2008 Express Edition cannot be used, because it lacks MFC support.
b) Perl (>= Version 5.00)
c) NullSoft NSIS for building the setup/installer (see http://nsis.sourceforge.net/).


3. The programs (CrypTool.exe and AES-Tool.exe)
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Remark:
The following paragraphs always tell the German and English names of the menu items.

The project files, which can be opened with MS-Visual C, are located at
- VS.net 2008:     CrypTool\CrypTool.sln 
To open the project file please double click it or 
with MS-VC choose Datei[File] -> Arbeitsbereich öffnen[open project/solution].

Before compiling you should make sure to include Perl correctly:
Please adjust/check at:
Menü[Menu] -> Extras[Tools] -> Optionen[Options]: 
- At the choice box "Verzeichnisse Anzeigen für[Show directories for]" pick  
  "Ausführbare Dateien[Executable files]" 
- Declare the path for Perl (preset is "C:\Programme\perl\bin\")

Building CrypTool and AES-Tool:
At Menü[Menu] Erstellen[Build] -> Aktive Konfiguration festlegen[choose configuration] 
the following configurations are defined:
- CrypTool Win32 (Debug_{de|en})     // depending on the favoured language (German or English)
- CrypTool Win32 Release_{de|en}     // depending on the favoured language (German or English)
- aestool Win32 (Debug_{de|en})      // depending on the favoured language (German or English)	
- aestool Win32 Release_aes_{de|en}  // depending on the favoured language (German or English)

Online help:
Files of the online help can be found at
CrypTool\source\CrypTool\CrypTool\hlp_[de|en].
Building the online help takes some time, but you can prevent that
by adding a file called "makehelp.no" to the help directories. 


4. The installer
   ~~~~~~~~~~~~~
How to build the CT1 installer (SetupCrypTool*.exe) is described in 
setup\README.txt


5. Adding your own developments to CT1
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Everyone is encouraged to enhance the possibilities CrypTool already has.
Please contact the CrypTool team or see the CrypTool homepage (www.cryptool.org),
how to move your enhancements into the sources of the major release version.

5.1 Expanding the online help
   ~~~~~~~~~~~~~~~~~~~~~~~~~~
When you extend CT1 you also will have to expand the online help. 
There are four cases that can appear:

a) Adding new source code, which gets a new ID, like terminal dialogs, menu
   entries, ... That ID is added automatically to CrypTool_helpIDs.h
   - New source code, where the appropriate help already exists:
     To handle that situation, please edit "CrypTool_Alias.h" by adding a 
     new line taking notice of the alphabetical order.
     Pattern: H<new ID> = <target html file> 
     Example: new ID: "ID_TEST" should point at existing "main_index.html" -> 
              new line: HID_TEST = main_index.html
   - New source code, where the appropriate help must be created:
     Create a new html file by using the template (hlp_[de|en]\template.html)
     Name that file according to the new ID: 
     Pattern: H<new ID>.html 
     Example: new ID: <ID_TEST> -> name of the new html file: <HID_TEST.html>
     Copy that file to the appropriate folder ("hlp_de" or "hlp_en"). 
     Add the new html file to the HTML Help project CrypTool.hhp) using one of
     the following two methods:
     a) Open the CrypTool.hhp with the HTML Help Workshop and add the new 
        html file via "Add/Remove topic files".
     b) Open the CrypTool.hhp with an editor and add a new line with the 
        filename of the new html file to the [Files]-section.
        Please take notice of the alphabetical order.

b) Adding new source code, which gets no ID but an Alink, like menus, or sub-
   menus
   - New menu:
     When creating a new menu (e.g. "Test"), a new help topic will be needed.
     So create a new html file (e.g. menu_test.html) and add that file to the 
     HTML Help project, like described at 5.1a. 
     For creating a new Alink please edit CrypToolPopupMenuIDs.txt: like described
     there, add the new "pmenuid" in your new html file at the ALink-object.
     More information for editing the Alink-object can be found in the template
     (hlp_[de|en]\template.html).
   - New sub-menu:
     When creating a new sub-menu, there already will be an appropriate html 
     file for the super menu. For creating the new Alink please edit 
     CrypToolPopupMenuIDs.txt, like described there. 
     Then add to the existing html file of the super menu an Alink-object 
     (which can be found in the template) and add your help text.
     Finally add the new "pmenuid" to the ALink-object. 
     More information for editing the Alink-object can be found in the template.


5.2 Further things to consider to make a new development fit into CT1
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
These claims guarantee a high level of quality and a consistent user interface.

a) CT1 has for each menu item a longer text string explaining it. This text
   appears in the status line at the lower border of the main window.
   Within the properties dialog of a new menu item (within Visual Studio) please
   fill the field for the text in the status bar.
    
b) Use consistent capitalization: 
   - For menu entries (German), button texts, dialog titles and online help headings: 
     Use the same capitalization as in a sentence: Capital first letter, the following words 
     are only capitalized when required by the language (e.g. German nouns, english proper 
     names etc.)
   - For English menu entries:
     Use the capitalization as in a english heading

c) Usage of the icons "Show key" ("Schlüssel anzeigen") and "Insert key" ("Schlüssel einfügen"):
   After encrypting a document, you can click on the "Show key" icon within the
   icon bar (below the menu bar). Then the used key for this method is shown and
   can be copied to an internal, method-specific key-clipboard.
   So take care to activate this "show key" icon after showing your encrypted document.
   In all dialogues, where you enter a key, there has to be an "Insert key" icon
   (this could be in the encryption dialogue or in the analysis dialog).
   This icon is active, if for this method there has already be a key copied into
   the internal, method-specific key-clipboard.
   Please have a look at the source code, how it is implemented for other encryption
   methods.

d) More complex methods which require several different input values like the
   RSA crypto system or the Diffie-Hellman key exchange should offer at the end:
   - to show the achieved result in an extra dialog mask.
   - to create a log file.

e) The online help for CT1 is in HTML format. To build it, use your HTML editor
   of choice.

   Help texts have to be exhaustive and easy to understand.
   There must be a version in both English AND German (if you can do it only in
   one language please contact the CrypTool mailing list, and we translate it
   into the other language).
   Each help page has to be within an own HTML file (with a self-explaining name).

   There have to be different help pages one gets when pressing F1 and
   - if a menu item is marked:
     Title has to contain the method name and the menu path.
     Then the method has to be described in general, references be named, ... .
   or
   - if a dialog is visible:
     This help page explains how to operate the dialogue.
     Here you should inform about restrictions within your implementation.

   Please make sure, that complex methods always have these 2 pages separated and
   that these 2 pages are cross-linked.
   If it is very complex you can even have a third or more page explaining only the maths.
   If the method is simple, then the 2 pages could be merged to one.

   This separation exists e.g. for:
   - the menu item "Ver-/Entschlüsselung \ Hybrid-Demo \ Hybridverschlüsselung"
     ["Crypt \ Hybrid Demonstration \ Hybrid Encryption"].
     Here within the first chapter there is a link to the dialog
     "Visualisierung der Hybridverschlüsselung" ["Visualising hybrid encryption"].
   - the menu item "Ver-/Entschlüsselung \ Klassisch \ Playfair"
     ["Crypt \ Classical \ Playfair"].
     Here within the second chapter there is a link to the dialog
     "Schlüsseleingabe Playfair" ["Playfair key entry"].

   - Another thing in the online help is:
     - to offer a links to a scientific source for deeper information.
     - to describe the according RFC, PKCS, ... standard if there is any.

f) If you implement a method please make sure that your method reflects the options
   within the menu "Optionen \ Textoptionen" [Options \ Text Options] and reacts
   properly to changes made there.
   If the options within the options dialogs (like the alphabet used, the way to deal with
   formats, ...) are not enough, you also can make enhancements within the options dialogs.

g) When developing new code, try to separate different functionalities: so please act
   according to the MVC-principle (model-view-controller).


6. Additional hints
   ~~~~~~~~~~~~~~~~

- We want to encourage you, to first have a look at the different features implemented in
  the CT1 program (run it), and then look into the source code, look for according examples
  and re-use the existing methods.

- If you come to a problem do not hesitate to paste a mail to the CrypTool team
  (see www.cryptool.org).

- There is an old presentation about how to compile CT1 and how to add own
  methods (CrypTool-MFC-Kurs-VC7.ppt in the same directory as this file). 
  The most important recommendations are:
  - First develop your program as a pure console application to make your functionality clear.
  - Then integrate your program into CT1 and design the GUI.
  Acting in this way means to have 2 separated steps: this helps to clearly divide up the
  crypto functionality and the application/presentation layer.
  
- Among others, there is the Perl script "CheckHelp.pl" (located in "trunk/CrypTool") supporting 
  developers in maintaining the CT1 online help. It is very useful because it runs various 
  consistency checks regarding the online help. A simple way to run this script is "perl CheckHelp.pl 
  ENGLISH hlp_de" from the CT1 root directory ("trunk/CrypTool"). There are more languages 
  supported, and you can get detailed output information if the "$debug" switch is set. For more 
  information, take a look at the documented source file "CheckHelp.pl"
  





B) What to deliver back, if you make enhancements to CT1
========================================================

This describes, what the CT1 developer team expects, if 
someone develops new features and starts to work with a copy
of a CT1 version.
Here we describe, what is the best way, to deliver the results
of one's project back to the CT1 mainstream source code.


English:
========

E1. Information about your project
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  - Name of the project/feature, 
  - Date of last source-change, 
  - Your contact data, 
  - Version number, 
  - Other contributing persons, 
  - Description/goal of your project
  - ... 


E2. Implementation details
   ~~~~~~~~~~~~~~~~~~~~~~~
E2.1. Resources
    - Which menus are used to get to your project
    - Do you work on HEX or ASCII
    - Name of the menu IDs
    - Name of the dialog IDDs
    - New bitmaps used?
    - ...

E2.2. Files 
    - Which existing files are changed?
      (which functions/global variables are new, most likely with line numbers or as diff)
       am besten mit Zeilenangaben)
    - Which new files created?

E2.3. Hints about implementation
    - Compiler version?
    - Which DLLs / libs (plus versions number) are used?
    - Which additional programs are used?
    - Do you need a Java runtime environment (which version)?
    - Important implementation details
    - Restrictions of your project
    - Test data.

E3. Usage / Online Help
   ~~~~~~~~~~~~~~~~~~~~
   - Which pages of the online help have been changed?
   - Which pages of the online help have been created newly?
   - Additional hints for usage/usability 
     (e.g. whether programs are called via links within the online help)
   - ...

E4. TODO/Further enhancements
   ~~~~~~~~~~~~~~~~~~~~~~~~~~
   - open issues (not yet implemented, but reasonable)
   - Possibilities for enhancement
   - ...

E5. What do we expect to get back?
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
If your project is in a status, that it can be integrated
into the CT1 release version, please send us
a) one zip file with the following content:
   - all files changed or created within your project
   - Your project file (content see above B-E-1 till B-E-4)
   - Your seminar workout, thesis or other documentation
   - eventually other relevant files
b) another zip file with:
   - all sources (your whole project directory, in order we can build the executable too)
   - your last executable (release and debug version).



German:
=======

G1. Informationen zu Ihrem Projekt
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  - Name des Projektes, 
  - Datum der Erstellung, 
  - Kontaktdaten, 
  - Version, 
  - Beteiligte Personen, 
  - Zweck des Projektes
  - ... 


G2. Implementierungsdetails
   ~~~~~~~~~~~~~~~~~~~~~~~
G2.1. Ressourcen
    - Über welches Menü erfolgt der Einstieg?
    - Arbeiten Sie mit HEX oder ASCII?
    - Name der Menü-IDs
    - Name der Dialog-IDDs
    - neue Bitmaps
    - ...

G2.2. Dateien 
    - Welche bestehende Dateien wurden geändert?
      (welche Funktionen/globale Variablen sind hinzu gekommen, am besten mit Zeilenangaben oder per diff)
    - Welche neuen Dateien wurden erstellt?

G2.3. Hinweise zur Implementierung
    - Compilerversion?
    - Welche DLLs / Libs (plus Versionsnummer) werden genutzt?
    - Werden zusätzliche Programme eingebunden?
    - Wird die Java runtime environment benötigt (welche Version)?
    - Wichtige Implementierungsdetails?
    - Grenzen/Limits Ihres Projekts?
    - Testdaten.

G3. Bedienung / Online Hilfe
   ~~~~~~~~~~~~~~~~~~~~~~~~
   - Welche Seiten der Online-Hilfe wurden geändert?
   - Welche Seiten zur Online-Hilfe wurden neu erstellt?
   - zusätzliche Hinweise zur Bedienung/Nutzung 
     (z.B. werden über Links in der Online-Hilfe Programme aufgerufen)
   - ...

G4. TODO/Ausblick
   ~~~~~~~~~~~~~
   - offene Punkte (noch nicht implementiert, aber sinnvoll)
   - Erweiterungsmöglichkeiten
   - ...

G5. Was soll zurückgeschickt werden?
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Wenn Ihr Projekt in einem Status ist, dass es in die 
CT1-Releaseversion integriert werden kann/soll, senden Sie uns bitte:
a) eine Zip-Datei mit folgendem Inhalt:
   - alle im CT1-Projekt neuen / geänderten Dateien
   - Ihre Projektdatei (Inhalt siehe oben Punkte B-G-1 bis B-G-4)
   - die Seminar-/Diplomarbeit und evtl. weitere Doku
   - ggf. weitere relevante Dateien
b) eine weitere Zip-Datei mit:
   - allen Sourcen (Ihr ganzes Projekt-Verzeichnis, damit auch wir daraus das Executable bauen können)
   - Ihr letztes Executable (Release- und Debug-Version).

