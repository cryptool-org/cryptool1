How to update the Scintilla library distributed with CrypTool
=============================================================

1. Download and Build Scintilla

Follow the instructions in LexCrypTool.cxx regarding "Internal lexer build:"
After unpacking sciteXXX.zip change into the unpacked directory "scintilla" 
and apply the patch:
	patch -p1 < ...\scintilla-wordwrap-ignore-style.diff
Then continue to build Scintilla as described in LexCrypTool.cxx.

2. Update the CrypTool source
Copy the SciLexer.dll from the Scintilla build directory scintilla\bin to
the setup\template directory in the CrypTool source tree.
	
Copy the following files from the Scintilla source directory to the scintilla
directory in the CrypTool source tree:
	License.txt
	README
	version.txt

3. Build CrypTool

4. Run CrypTool and verify that "Edit\Alphabet" works for text files and that 
"Help\About" shows the new Scintilla version.

