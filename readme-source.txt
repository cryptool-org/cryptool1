CrypTool 1.3.06 b1  (2004-07-29)
~~~~~~~~~~~~~~~

Readme for building CrypTool out of the sources. 


Files

readme.txt 				This Readme
SetupCrypTool_1_3_02_{de|en}.exe	CrypTool Setup
CrypTool\source\ ...			Source code for building CrypTool

1. Requirements
   ~~~~~~~~~~~~
For building you need
- Microsoft C++ Compiler:
  + Visual Studion C++ 6.0 
  + VS.net 2003 (at the moment it is possible to compile CrypTool with VS.net
    2003, but certain runtime errors will appear)
  + Visual C++ Toolkit 2003 (please see
    http://msdn.microsoft.com/visualc/vctoolkit2003/)
    ATTENTION!!! at the moment this compiler cannot be used yet!
- Perl (Version 5.XX)
- HTML Help Workshop (please see 
  http://msdn.microsoft.com/library/default.asp?url=/library/en-
  us/htmlhelp/html/hwMicrosoftHTMLHelpDownloads.asp - 
  please install both Htmlhelp.exe and Hhupd.exe)

2. The programs CrypTool.exe aestool.exe
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The project files, which can be opened with MS-Visual C, are located at
Visual Studio 6: ..\CrypTool\CrypTool.dsw 
VS.net 2003:     ..\CrypTool\CrypTool.sln 
(to open please double click or with MSVC choose Datei[File] -> Arbeitsbereich öffnen[open project/solution])

Before compiling you should notice to include Perl and HTML Help Workshop correctly:
Please adjust/check at 

Menü[Menu] -> Extras[Tools] -> Optionen[Options]: 
- At the choice box "Verzeichnisse Anzeigen für[Show directories for]" pick  
  "Ausführbare Dateien[executable files]" 
- Declare the path for perl (preset is "C:\Programme\perl\bin\") and for HTML
  Help compiler (hhc.exe) (preset is "C:\Programme\HTML Help Workshop")
  Also add/readapt the following settings: Projekt[Project] -> 
  Einstellungen[Settings] (project settings only for CrypTool)
- tab: Linker -> Kategorie[Category]: Allgemein[General] -> at "Objekt-
  /Bibliothek-Module[Object-/library-modules]" add htmlhelp.lib 
- tab: Linker -> Kategorie[Category]: Eingabe[Input] -> "Zusätzlicher
  Bibliothekpfad:[additional library directories]" add your 
  path to htmlhelp.lib 
- tab: C/C++ -> Kategorie[Category] -> Präprozessor[Preprocessor] -> 
  "Zusätzliche Include-Verzeichnisse:[additional include directories]" add your
  path to htmlhelp.h here

Building CrypTool:
At Menü:[Menu:] Erstellen[Build] -> Aktive Konfiguration festlegen[choose configuration] the following configurations are defined:
- CrypTool Win32 (Debug) 
- CrypTool Win32 Release_{de|en}	// depending on the favoured language
- aestool Win32 (Debug)	
- aestool Win32 Release_aes_{de|en}	// depending on the favoured language

Online-help:
Files of the online-help can be found at
CrypTool\source\CrypTool\CrypTool\hlp_[de|en]

Building the online help takes some time, but you can prevent that by adding a file called "makehelp.no" to the help directories. 

Possible problems:
Maybe the MFC was not compiled yet.
The according readme can be found at C:\Program Files\Microsoft Visual Studio\VC98\MFC\SRC or your similar directory.
Before compiling the MFC you have to call the batch file VCVARS32.BAT for setting the environment.

To compile the MFC call the following commands (according to the readme)

	Debug Build:   $> NMAKE DEBUG=1 CODEVIEW=1 BROWSE=1
	Release Build: $> NMAKE DEBUG=0

3. Further development of CrypTool
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

3.1 Expanding the online help
When you extend CrypTool you also will have to expand the online help. There are four cases that can appear:

      Adding new source code, which gets a new ID, like terminal dialogs, menu
      entries, ... That ID is added automatically to CrypTool_helpIDs.h
	- New source code, where the appropriate help exists already:
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
	  Copy that file to the appropriate folder ("hlp_de" or "hlp_en"). Add the
          new html file to the HTML Help project CrypTool.hhp) using one of the 
          following methods:
		a) Open the CrypTool.hhp with the HTML Help Workshop and add the new 
               html file via "Add/Remove topic files".
		b) Open the CrypTool.hhp with an editor an add a new line with the 
               filename of the new html file to the [Files]-section. Please take
               notice of the alphabetical order.
      Adding new source code, which gets no ID but an Alink, like menus, or sub-
      menus
	- New menu:
	  When creating a new menu (e.g. Test), a new help topic will be needed.
          So creat a new html file(e.g. menu_test.html) an add that file to the 
          HTML Help project, like described at 3.1 . For creating a new Alink
          please edit CrypToolPopupMenuIDs.txt, like described there and add the 
          new "pmenuid" in your new html file at the ALink-object. More 
          information for editing the Alink-object can be found in the template
          (hlp_[de|en]\template.html).
	- New sub-menu:
	  When creating a new sub-menu, there already will be an appropriate html 
          file for the supermenu. For creating the new Alink please edit 
          CrypToolPopupMenuIDs.txt, like described there. Then add to the existing 
          html file of the supermenu an Alink-object (which can be found in the 
          template) and add your help text. Finally add the new "pmenuid" to the
          ALink-object. More information for editing the Alink-object can be found 
          in the template.
