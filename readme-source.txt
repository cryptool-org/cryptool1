CrypTool 1.3.06 Beta 2  (2004-11-22)
~~~~~~~~~~~~~~~

Readme for building CrypTool from the current sources. 

Remarks: 
- The current release version 1.3.05 was built with Visual C++ 6.0.
- The current beta can also be compiled with VS.net 2003, but certain
  runtime errors will appear yet.
- Compared to the release version 1.3.05 the current beta contains the following additions:
    - Online-Help files in HTML format instead in Winhelp format
    - Demo of side-channel attack
    - Demo of challenge response and client-server authentication.



1. Files you need
   ~~~~~~~~~~~~~~
readme-source.txt 			This Readme
CrypTool\source\ ...			Directory tree with the source code for building CrypTool.
					File can be downloaded via Internet.


2. Tools you need
   ~~~~~~~~~~~~~~
For building you need:
- A Microsoft C++ Compiler:
    - Visual Studion C++ 6.0 
    or
    - VS.net 2003
- Perl (>= Version 5.00)
- HTML Help Workshop (please see 
  http://msdn.microsoft.com/library/default.asp?url=/library/en-
  us/htmlhelp/html/hwMicrosoftHTMLHelpDownloads.asp - 
  please install both Htmlhelp.exe and Hhupd.exe)

Remark:
The free Visual C++ Toolkit 2003 (http://msdn.microsoft.com/visualc/vctoolkit2003/)
cannot be used as compiler for CrypTool because it is not complete enough to do so!



3. The programs (CrypTool.exe and AES-Tool.exe)
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The project files, which can be opened with MS-Visual C, are located at
- Visual Studio 6: ..\CrypTool\CrypTool.dsw 
- VS.net 2003:     ..\CrypTool\CrypTool.sln 
To open the project file please double click or with MS-VC choose Datei[File] -> Arbeitsbereich öffnen[open project/solution].

Before compiling you should notice to include Perl and HTML Help Workshop correctly:
Please adjust/check at:
Menü[Menu] -> Extras[Tools] -> Optionen[Options]: 
- At the choice box "Verzeichnisse Anzeigen für[Show directories for]" pick  
  "Ausführbare Dateien[Executable files]" 
- Declare the path for Perl (preset is "C:\Programme\perl\bin\") and for
  for HTML Help compiler (hhc.exe) (preset is "C:\Programme\HTML Help Workshop").

Also add/readapt the following settings: Projekt[Project] -> 
Einstellungen[Settings] (project settings only for CrypTool, not for AES-Tool)
- tab: Linker -> Kategorie[Category]: Allgemein[General] -> at "Objekt-
  /Bibliothek-Module[Object-/library-modules]" add htmlhelp.lib 
- tab: Linker -> Kategorie[Category]: Eingabe[Input] -> "Zusätzlicher
  Bibliothekpfad[additional library directories]": add your 
  path to htmlhelp.lib 
- tab: C/C++ -> Kategorie[Category] -> Präprozessor[Preprocessor] -> 
  "Zusätzliche Include-Verzeichnisse[additional include directories]": add your
  path to htmlhelp.h here

Building CrypTool and AES-Tool:
At Menü:[Menu:] Erstellen[Build] -> Aktive Konfiguration festlegen[choose configuration] the following configurations are defined:
- CrypTool Win32 (Debug) 
- CrypTool Win32 Release_{de|en}	// depending on the favoured language (German or English)
- aestool Win32 (Debug)	
- aestool Win32 Release_aes_{de|en}	// depending on the favoured language (German or English)

Online help:
Files of the online help can be found at
CrypTool\source\CrypTool\CrypTool\hlp_[de|en]
Building the online help takes some time, but you can prevent that by adding a file called "makehelp.no" to the help directories. 

Possible problem (only saw with C++ 6.0 standard edition):
- Maybe the Microsoft library MFC was not compiled yet.
  The according readme can be found at 
  C:\Program Files\Microsoft Visual Studio\VC98\MFC\SRC or your similar directory.
  Before compiling the MFC you have to call the batch file VCVARS32.BAT for setting the environment.
  To compile the MFC call the following commands (according to the readme):
  Debug Build:   $> NMAKE DEBUG=1 CODEVIEW=1 BROWSE=1
  Release Build: $> NMAKE DEBUG=0



4. Adding your own developments to CrypTool
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Everyone is encouraged to enhance the possibilities CrypTool has.
Please contact the mailing list or see the CrypTool homepage (www.cryptool.org),
how to move your enhancements into the sources of the major release CVS.

4.1 Expanding the online help
   ~~~~~~~~~~~~~~~~~~~~~~~~~~
When you extend CrypTool you also will have to expand the online help. 
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
     HTML Help project, like described at 4.1a. 
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


4.2 Further things to consider to make a new development fit into CrypTool
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
These claims guarantee a high level of quality and a consistent user interface.

a) CrypTool has for each menu item a longer text string explaining it. This text
   appears in the status line at the lower border of the main window.
   Within the properties dialog of a new menu item (within Visual Studio) please
   fill the field for the text in the status bar.
    

b) Usage of the icon "Show key" and "Insert key":
   After encrypting a document, you can click on the "Show key" icon within the
   icon bar (below the menu bar). Then the used key for this method is shown and
   can be copied to an internal, method-specific key-clipboard.
   So take care to activate this "show key" icon after showing your encrypted document.
   In all dialogues, where you enter a key, there has to be an "Insert key" icon.
   This icon is active, if for this method there has already be a key copied into
   the internal, method-specific key-clipboard.
   Please have a look at the source code, how it is implemented for other encryption
   methods.

c) More complex methods which require several different input values like the
   RSA crypto system or the Diffie-Hellman key exchange should offer to create
   a log file at the end.

d) The online help for CrypTool is in HTML format. To build it, use your HTML editor
   of choice.

   Help texts have to be exhaustive and easy to understand.
   There must be a version in English and in German (if you can do it only in one
   language please contact the CrypTool mailing list).
   Each help page has to be within an own HTML file (with a self-explaining name).

   There has to be different help pages one gets when pressing F1 and
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

e) If you implement a method please make sure that your method reflects the options
   within the menu "Optionen \ Textoptionen" [Options \ Text Options] and reacts
   properly to changes made there.
   If the options within the options dialogs (like the alphabet used, the way to deal with
   formats, ...) are not enough, you also can make enhancements within the options dialogs.



5. Additional hints
   ~~~~~~~~~~~~~~~~

- We want to encourage you, to first have a look at the different methods implemented in
  CrypTool (running it) and then look into the source code, look for according examples
  and re-use them.

- If you come to a problem do not hesitate to paste a mail to the CrypTool mailings list
  (see www.cryptool.org).

- There exits an additional presentation about how to compile CrypTool and how to add own
  methods. The most important recommendations are:
  - First develop your program as a pure console application to make your functionality clear.
  - Then integrate your program into CrypTool and design the GUI.
  Acting in this way means to have 2 separated steps: this helps to clearly divide up the
  crypto functionality and the application/presentation layer.
  

