#ifndef __CRYPTOOL_TOOLS_H
#define __CRYPTOOL_TOOLS_H

#include "stdafx.h"
#include "CrypToolApp.h"

BOOL CheckAlphabet (int minSize = 1);
BOOL CheckTextSize (SymbolArray &text, int Threshold = 1);
void LoadText      (const char *infile, SymbolArray &text);
void GetNewDocTitle(const char* keyStr, const char* OldTitle, 
					int IDS_STRING_ID, char* title, long titleLength, BOOL Decrypt = FALSE, 
					int KeyType = SCHLUESSEL_LINEAR );

void OpenNewDoc    (const char *outfile, const char* keyStr, const char* OldTitle, 
					int IDS_STRING_ID, BOOL Decrypt = FALSE, int KeyType = SCHLUESSEL_LINEAR );


#endif


