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

#if !defined(MONO_SUBST_CRACKER)
#define MONO_SUBST_CRACKER

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#include "CrypToolApp.h"
#include "Cryptography.h"
#include "DlgOptionsAutoSubstitutionAnalysis.h"
#include "DlgAutoSubstitutionAnalysisAlgorithmChoice.h"
#include "DlgAutoSubstitutionAnalysis.h"
#include "DlgManualSubstAnalysis.h"
#include "FileTools.h"


/*************************
 Definitions
 *************************/

#define DEBUG

// return codes
#define OK	0
#define FILE_OPENING_ERROR	-10
#define FILE_CONTENT_ERROR	-11
#define LANGUAGE_UNKNOWN_ERROR	-20

// available languages
#define EN	1
#define DE	2

// global vars 
extern int	*MaxPermu[26];	// required for manual analysis dialog
extern char	*Eingabedatei;	// required for manual analysis dialog
extern char	*Pfad;			// directory path of the main programm

// assumed (guessed) language of the text
static int	lang = EN;
static bool space_in_alphabet = false;

// parameter structure
struct MonoSubstCrackerParameters
{
	int			language;
	bool		space_in_alphabet;
	bool		nogui;
	char		*data;
	CDlgAutoSubstitutionAnalysis	*Dialog;
};


/*************************
 Func declarations.
 *************************/
UINT	AutoAnaSubst(PVOID p);
void	ManualAnaSubst(char* infile, const char* title, const char* key);
float	computeError (float *matrix, float *standard);
int		createInitialKey(char *key, float *stats);
int		createStatistics(char *text, float *single, float *digram);
void	encryptText (char *key, char *plain, char *cipher);
int		getAlphabetSize ();
int		createStatistics(char *text, float *single, float *digram);
char*	getSortedLetters ();
int		guessLanguage(char *);
int		initializeStandardDMatrix(float *stats, MonoSubstCrackerParameters *parameters);
int		invertKey(char *source, char *target);
bool	isInAlphabet(char c);
UINT	monoSubstCrackerThread(PVOID p);
void	prepareText(char *text);
int		transformDMatrix (float *source, int index1, int index2, float *target);


#endif
