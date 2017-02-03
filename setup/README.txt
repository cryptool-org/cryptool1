HOWTO Create a CrypTool Installer Package

0. Make a clean subversion checkout of CrypTool

1. Use MSDev to make a clean build of the release versions for all required languages.

2. Create the setup directories for all languagues:
	createsetupdirs.bat
for one language only:
	createsetupdir1lang.bat de

3. Create the installer executable for all language: 
	createsetupexes.bat
for one language only:
	createsetupexe1lang.bat de

4. Create a subversion tag:
	cd trunk
	svn copy . https://www.cryptool.org/svn/CrypTool/tags/CrypTool_1_4_30_beta_07

NOTE:
1. After every last minute update of the readme a build is required to update the 
   readme in the online help.
2. Make sure to update files in setup/template* including 
   CT-Book-*.pdf and 
   CrypToolPresentation-*.pdf
