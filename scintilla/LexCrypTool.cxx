/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

/*

	This file implements a simple lexer for Scintilla

	It grays out (style configurable) the characters, which 
	are not in the predefined "alphabet" (a set of characters, 
	configurable).

	- Alphabet characters are styled with style 0.
	- Non-alphabet characters are syle with the style defined in property 
	  cryptool.nonalphabetstyle (int).
	- The Alphabet is defined by property cryptool.alphabet (string).

	The name of the lexer is "CrypTool". Here is an example how to activate the lexer:
		SendMessage(SCI_SETPROPERTY, (WPARAM)_T("cryptool.nonalphabetstyle"), (LPARAM)2);
		SendMessage(SCI_SETPROPERTY, (WPARAM)_T("cryptool.alphabet"), (LPARAM)(LPCTSTR)"ABCDEFHIJKLMNOPQRSTUVWXY");
		SendMessage(SCI_SETLEXERLANGUAGE,0,(LPARAM)"CrypTool");

	The lexer can be built as an internal or external lexer.

	Internal lexer build:
	1. unpack sciteXXX.zip (scintillaXXX.zip will give an error in step 4)
	2. copy LexCrypTool.cxx to scintilla\src
	3. cd scintilla\src
	4. LexGen.py
	5. build scilexer.dll as described in the Scintilla documentation

	External lexer build:
	1. unpack and build sciteXXX.zip or scintillaXXX.zip
	2. Define BUILD_AS_EXTERNAL_LEXER in your makefile/project properties
	3. Compile LexCrypTool.cxx
	4. Create a file LexCrypTool.def with the following contents:
		LIBRARY	LexCrypTool
		EXPORTS
			GetLexerCount	@1
			GetLexerName	@2
			Lex				@3
			Fold			@4
	5. Link LexCrypTool.dll with the created Module Definition File 
	   (/DEF:LexCrypTool.def) and the following input files:
	   LexCrypTool.obj, 
	   WindowAccessor.obj PropSet.obj PlatWin.obj XPM.obj UniConversion.obj
	
*/
#include <string.h>
#include <stdlib.h>

#include "Platform.h"

#include "PropSet.h"
#include "Accessor.h"
#include "Scintilla.h"
#include "SciLexer.h"

#ifndef BUILD_AS_EXTERNAL_LEXER
#include <ctype.h>
#include "KeyWords.h"
#endif

static void CrypToolLex (
        unsigned int startPos, int length,
        int initStyle,
        WordList *keywordlists[],
        Accessor &styler);

static void CrypToolFold (
        unsigned int startPos, int length,
        int initStyle,
        WordList *keywordlists[],
        Accessor &styler);

#ifdef BUILD_AS_EXTERNAL_LEXER

#include "WindowAccessor.h"

#define EXT_LEXER_DECL __stdcall

int EXT_LEXER_DECL GetLexerCount()
{
	return 1;
}

void EXT_LEXER_DECL GetLexerName(unsigned int, char *name, int buflength)
{
	strncpy(name, "CrypTool", buflength);
	name[buflength - 1] = '\0';
}

static void InternalLexOrFold(int foldOrLex, unsigned int startPos, int length,
	int initStyle, char *words[], WindowID window, char *props);

void EXT_LEXER_DECL Lex(unsigned int, unsigned int startPos, int length,
	int initStyle, char *words[], WindowID window, char *props)
{
	InternalLexOrFold(0, startPos, length, initStyle, words, window, props);
}

void EXT_LEXER_DECL Fold(unsigned int, unsigned int startPos, int length,
	int initStyle, char *words[], WindowID window, char *props)
{
	// build expected data structures and do the Fold
	InternalLexOrFold(1, startPos, length, initStyle, words, window, props);
}

static void InternalLexOrFold(int foldOrLex, unsigned int startPos, int length,
	int initStyle, char *words[], WindowID window, char *props)
{
	// create and initialize a WindowAccessor (including contained PropSet)
	PropSet ps;
	ps.SetMultiple(props);
	WindowAccessor wa(window, ps);
	// create and initialize WordList(s)
	int nWL = 0;
	for (; words[nWL]; nWL++) ;	// count # of WordList PTRs needed
	WordList** wl = new WordList* [nWL + 1];// alloc WordList PTRs
	int i = 0;
	for (; i < nWL; i++) {
		wl[i] = new WordList();	// (works or THROWS bad_alloc EXCEPTION)
		wl[i]->Set(words[i]);
	}
	wl[i] = 0;
	// call our "internal" folder/lexer (... then do Flush!)
	if (foldOrLex)
		CrypToolFold(startPos, length, initStyle, wl, wa);
	else
		CrypToolLex(startPos, length, initStyle, wl, wa);
	wa.Flush();
	// clean up before leaving
	for (i = nWL - 1; i >= 0; i--)
		delete wl[i];
	delete [] wl;

}
#endif // BUILD_AS_EXTERNAL_LEXER

static void CrypToolLex(
        unsigned int startPos, int length,
        int /*initStyle*/,
        WordList * /*keywordlists*/ [],
        Accessor &styler)
{
	char *props = styler.GetProperties();
	PropSet ps;
	ps.SetMultiple(props);
	delete []props;
	SString alphastr = ps.Get("cryptool.alphabet");
	const char *alpha = alphastr.c_str();
	size_t alphalen = strlen(alpha);
	SString nonalphastylestr = ps.Get("cryptool.nonalphabetstyle");
	int nonalphastyle = atoi(nonalphastylestr.c_str());

	styler.StartAt(startPos);
	styler.StartSegment(startPos);
	
	for (unsigned int i = startPos; i < startPos + length; i++) {
		char ch = styler.SafeGetCharAt(i);
		int style = (alphalen == 0 || memchr(alpha,ch,alphalen)) ? 0 : nonalphastyle;
		styler.ColourTo(i,style);
	}
}

static void CrypToolFold(
        unsigned int, int,
        int,
        WordList *[],
        Accessor &)
{
}

#ifndef BUILD_AS_EXTERNAL_LEXER
static const char * const CrypToolWordListDesc[] = {
	0
};

LexerModule lmCrypTool(SCLEX_AUTOMATIC, CrypToolLex, "CrypTool", CrypToolFold, CrypToolWordListDesc);
#endif /* BUILD_AS_EXTERNAL_LEXER */
