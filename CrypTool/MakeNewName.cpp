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

#include "MakeNewName.h"
#include "string.h"
#include "stdio.h"

#pragma warning(disable : 4996)


/* Die folgende Funktionen generieren aus dem Namen des Fensters mit den zu bearbeitenden
   Daten einen Namen für das Fenster, in dem die Ausgabe dargestellt wird		*/

void MakeNewName(char *dest, unsigned int len, const char *format, const char *old)
{
    if(strlen(format)+strlen(old)<(size_t)len)
        sprintf(dest,format,old);
    else
	{
		int lenRemain = (size_t)len - (strlen(format) +4);
		if (lenRemain > 0)
		{
			char *tmp_str;
			tmp_str = new char[lenRemain+4];
			memcpy(tmp_str, old, lenRemain);
			memcpy(tmp_str+lenRemain, "...", 3);
			tmp_str[lenRemain+3] = '\0';
			sprintf(dest, format, tmp_str);
			delete []tmp_str;
		}
		else
			sprintf(dest,format,"...");
	}
}

void MakeNewName2(char *dest, int len, const char *format, const char *old, const char *alg)
{
    if(strlen(format)+strlen(old)+strlen(alg)<(size_t)len)
        sprintf(dest,format,alg,old);
    else
	{
		int lenRemain = (size_t)len - (strlen(format) + strlen(alg) +4);
		if (lenRemain > 0)
		{
			char *tmp_str;
			tmp_str = new char[lenRemain+4];
			memcpy(tmp_str, old, lenRemain);
			memcpy(tmp_str+lenRemain, "...", 3);
			tmp_str[lenRemain+3] = '\0';
			sprintf(dest, format, alg, tmp_str);
			delete []tmp_str;
		}
		else
			sprintf(dest,format,alg,"...");
	}
}

void MakeNewName3(char *dest, unsigned int len, const char *format, const char *alg, const char *old, const char *key)
{
    if(strlen(format)+strlen(alg)+strlen(old)+strlen(key)<(size_t)len)
        sprintf(dest,format,alg,old,key);
    else {
	    if(strlen(format)+strlen(alg)+3+strlen(old)<(size_t)len)
		{
			int lenRemain = (size_t)len - (strlen(format) + strlen(alg) +strlen(old) +4);
			if (lenRemain > 0)
			{
				char *tmp_str;
				tmp_str = new char[lenRemain+4];
				memcpy(tmp_str, key, lenRemain);
				memcpy(tmp_str+lenRemain, "...", 3);
				tmp_str[lenRemain+3] = '\0';
				sprintf(dest, format, alg, old, tmp_str);
				delete []tmp_str;
			}
			else
				sprintf(dest,format,alg,"...",key);
		}
		else
		{
			int lenRemain = (size_t)len - (strlen(format) + strlen(alg) +3 +4);
			if (lenRemain > 0)
			{
				char *tmp_str;
				tmp_str = new char[lenRemain+4];
				memcpy(tmp_str, old, lenRemain);
				memcpy(tmp_str+lenRemain, "...", 3);
				tmp_str[lenRemain+3] = '\0';
				sprintf(dest, format, alg, tmp_str, "...");
				delete []tmp_str;
			}
			else
				sprintf(dest,format,alg,"...","...");
		}
	}
}
