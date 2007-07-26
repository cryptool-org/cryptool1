HOWTO Create a CrypTool Installer Package

1. Use MSDev to make a clean build of the release versions for all required languages.

2. Create the setup directories for all languagues:
	createsetupdirs.bat
for one language only:
	createsetupdir1lang.bat de

3. Create the installer executable for all language: 
	createsetupexes.bat
for one language only:
	createsetupexe1lang.bat de

