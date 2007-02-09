/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/
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
