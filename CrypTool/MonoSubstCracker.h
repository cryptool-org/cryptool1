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
