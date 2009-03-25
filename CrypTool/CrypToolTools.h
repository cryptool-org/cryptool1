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

char* itoa_fmt(int i_num, char *c_buffer = NULL, int i_base = 10 );
char* itoa_fmt(__int64 i_num, char *c_buffer = NULL, int i_base = 10 );
char* double_fmt(double d_num, char *c_buffer, int prec = 2);

unsigned long CT_OPEN_REGISTRY_SETTINGS	(unsigned long MODE_ACCESS, int ID_REGISTRY_PATH, const char *SUB_FOLDER = 0);
void CT_CLOSE_REGISTRY();
BOOL CT_READ_REGISTRY			(unsigned long &value,		const char *ID);
BOOL CT_READ_REGISTRY			(char *value,		const char *ID,		unsigned long &length);
BOOL CT_READ_REGISTRY_DEFAULT	(unsigned long &value,		const char *ID, const unsigned long default_value);
BOOL CT_READ_REGISTRY_DEFAULT	(char *value,				const char *ID, const char *default_value,	unsigned long &length);
BOOL CT_WRITE_REGISTRY			(const unsigned long value, const char *ID);
BOOL CT_WRITE_REGISTRY			(const char *value,			const char *ID);

#endif


