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

#include "MakeNewName.h"
#include "string.h"
#include "stdio.h"

#pragma warning(disable : 4996)


/* Die folgende Funktionen generieren aus dem Namen des Fensters mit den zu bearbeitenden
   Daten einen Namen für das Fenster, in dem die Ausgabe dargestellt wird		*/

void MakeNewName(char *dest, unsigned int len, const char *format, const char *old)
{	
	if(strlen(format)+strlen(old)<(size_t)len) {
		sprintf(dest,format,old);
	}
  else {
		int lenRemain = (size_t)len - (strlen(format) +4);
		if (lenRemain > 0) {
			char *tmp_str;
			tmp_str = new char[lenRemain+4];
			memcpy(tmp_str, old, lenRemain);
			memcpy(tmp_str+lenRemain, "...", 3);
			tmp_str[lenRemain+3] = '\0';
			sprintf(dest, format, tmp_str);
			delete []tmp_str;
		}
		else {
			sprintf(dest,format,"...");
		}
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

// this function is very similar to "MakeNewName"; the only difference is that you can specify
// the name of the receiver (see last argument) that is added to the resulting document title
void MakeNewNameIncludingReceiver(char *dest, unsigned int len, const char *format, const char *old, const char *receiver) {
	if(strlen(format) + strlen(old) + strlen(receiver) < (size_t)len) {
		sprintf(dest, format, old, receiver);
	}
  else {
		// those seven extra characters consist of two "..." sequences and a binary null
		size_t lenRemain = (size_t)len - (strlen(format) + 7);
		// if we do have space left, try to add the receiver name first
		if(lenRemain > strlen(receiver)) {
			lenRemain -= strlen(receiver);
			// if there is still space left, try to add the old document title
			if(lenRemain > 0) {
				char *tmp_str;
				tmp_str = new char[lenRemain+4];
				memcpy(tmp_str, old, lenRemain);
				memcpy(tmp_str+lenRemain, "...", 3);
				tmp_str[lenRemain+3] = '\0';
				sprintf(dest, format, tmp_str, receiver);
				delete []tmp_str;
			}
		}
		// if there is no space left, go with two "..." sequences
		else {
			sprintf(dest, format, "...", "...");
		}
	}
}