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

#include "CrypToolTools.h"
#include "DialogeMessage.h"
#include "MakeNewName.h"
#include <stdlib.h>
#include <stdio.h>

#pragma warning(disable : 4996)


BOOL CheckAlphabet( int minSize )
{
	if (theApp.TextOptions.getAlphabet().GetLength() < minSize )
	{
		Message(IDS_STRING_MSG_ON_ALPHABET, MB_ICONEXCLAMATION, minSize);
		return FALSE;
	}
	return TRUE;
}


BOOL CheckTextSize( SymbolArray &text, int Threshold )
{
	if(text.GetSize() < Threshold ) 
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, Threshold);
		return FALSE;
	}
	return TRUE;
}


void LoadText( const char *infile, SymbolArray &text )
{
	CWaitCursor WCursor;
	text.Read(infile);
	WCursor.Restore();
}


void GetNewDocTitle(const char* keyStr, const char* OldTitle, 
					int IDS_STRING_ID, char* title, long titleLength, BOOL Decrypt, int KeyType)
{
	if(Decrypt)
		LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
	else
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
	

	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID,pc_str,STR_LAENGE_STRING_TABLE);
    MakeNewName3(title,titleLength,pc_str1,pc_str,OldTitle,keyStr);
}

void OpenNewDoc( const char *outfile, const char* keyStr, const char* OldTitle, int IDS_STRING_ID, 
				 BOOL Decrypt, int KeyType)
{
	char title[128];
	CAppDocument *NewDoc;
	NewDoc = theApp.OpenDocumentFileNoMRU( outfile, keyStr, KeyType );
    remove(outfile);
    if(NewDoc) 
	{
		GetNewDocTitle(keyStr, OldTitle, IDS_STRING_ID, title, 128, Decrypt, KeyType);
	    NewDoc->SetTitle(title);
	}
}

char* itoa_fmt(int i_num, char *c_buffer, int i_base )
{

	char c_tmp[33];
	itoa(i_num, c_tmp, i_base );

	int l = strlen(c_tmp);
	int set_pt = (!(l % 3)) ? 3 : l % 3; 

	int i_buffer_length = l+1+l/3;
	if ( !c_buffer) 
		c_buffer = new char[i_buffer_length];

	char strPT[128];
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PT,strPT,STR_LAENGE_STRING_TABLE);
	char c_pt = strPT[0];

	int i,j = 0;
	for (i = 0; i<l; )
	{
		c_buffer[j++] = c_tmp[i++];
		if ( i<l && i == set_pt ) { c_buffer[j++] = c_pt; set_pt += 3; }
	}
	c_buffer[j] = '\0';

	return c_buffer;
}

char* itoa_fmt(__int64 i_num, char *c_buffer, int i_base )
{
	char c_tmp[68];
	_i64toa(i_num, c_tmp, i_base );

	int l = strlen(c_tmp);
	int set_pt = (!(l % 3)) ? 3 : l % 3; 

	int i_buffer_length = l+1+l/3;
	if ( !c_buffer) 
		c_buffer = new char[i_buffer_length];

	char strPT[128];
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PT,strPT,STR_LAENGE_STRING_TABLE);
	char c_pt = strPT[0];

	int i,j = 0;
	for (i = 0; i<l; )
	{
		c_buffer[j++] = c_tmp[i++];
		if ( i<l && i == set_pt ) { c_buffer[j++] = c_pt; set_pt += 3; }
	}
	c_buffer[j] = '\0';

	return c_buffer;
}



char* double_fmt(double d_num, char *c_buffer, int prec )
{
	char c_tmp[60];
	if (abs(d_num) > (double)INT_MAX)
	{
		sprintf(c_tmp, "%f", d_num);
	}
	else
	{
		int i_num = (int)floor(d_num);
		itoa_fmt(i_num, c_tmp);
		if (prec > 9) prec = 9;
		char strPrec[10];
		d_num = abs(d_num);
		d_num = d_num - floor(d_num) +1.0;
		i_num = (int)(d_num*pow(10.0, prec));
		itoa(i_num, strPrec, 10);
		char commaStr[128];
		LoadString(AfxGetInstanceHandle(),IDS_STRING_COMMA,commaStr,STR_LAENGE_STRING_TABLE);
        strPrec[0] = commaStr[0];
		strcat(c_tmp, strPrec);
	}

	if ( !c_buffer ) c_buffer = new char[strlen(c_tmp)];
	strcpy(c_buffer, c_tmp);

	return c_buffer;
}



unsigned long CT_OPEN_REGISTRY_SETTINGS	(unsigned long MODE_ACCESS, int ID_REGISTRY_PATH, const char *SUB_FOLDER )
{
	char registryPath[1024];
	LoadString(AfxGetInstanceHandle(),ID_REGISTRY_PATH,registryPath,STR_LAENGE_STRING_TABLE);

	if ( 0 == SUB_FOLDER )
	{
		return theApp.localRegistry.Open(HKEY_CURRENT_USER, registryPath, MODE_ACCESS);
	}
	else
	{
		char *path = new char[strlen(registryPath)+strlen(SUB_FOLDER)+2];
		strcpy(path, registryPath);
		strcat(path, "\\");
		strcat(path, SUB_FOLDER);
		unsigned long ret_value = theApp.localRegistry.Create(HKEY_CURRENT_USER, path, REG_NONE, REG_OPTION_NON_VOLATILE, MODE_ACCESS);
		delete []path;
		return ret_value;
	}
}

void CT_CLOSE_REGISTRY()
{
	theApp.localRegistry.Close();
}

BOOL CT_READ_REGISTRY			(unsigned long &value, const char *ID)
{
	unsigned long u_value;
	// 
	if (ERROR_SUCCESS != theApp.localRegistry.QueryValue(u_value, ID))
		return FALSE;
	value = u_value;
	return TRUE;
}

BOOL CT_READ_REGISTRY			(char *value, const char *ID, unsigned long &length)
{
	if (ERROR_SUCCESS != theApp.localRegistry.QueryValue(value, ID, &length))
		return FALSE;

	return TRUE;
}

BOOL CT_READ_REGISTRY_DEFAULT	(unsigned long &value, const char *ID, const unsigned long default_value)
{
	unsigned long u_value;
	// 
	if (ERROR_SUCCESS != theApp.localRegistry.QueryValue(u_value, ID))
	{
		u_value = (unsigned long)default_value;
		if (ERROR_SUCCESS != theApp.localRegistry.SetValue(u_value, ID))
			return FALSE;
	}	
	value = u_value;
	return TRUE;	
}

BOOL CT_READ_REGISTRY_DEFAULT	(char *value, const char *ID, const char *default_value, unsigned long &length)
{
	if (ERROR_SUCCESS != theApp.localRegistry.QueryValue(value, ID, &length))
	{
		strncpy(value, default_value, length-1);
		value[length-1]='\0';
		if (ERROR_SUCCESS != theApp.localRegistry.SetValue(value, ID))
			return FALSE;
	}	
	return TRUE;	
}

BOOL CT_WRITE_REGISTRY			(const unsigned long value, const char *ID)
{
	if (ERROR_SUCCESS != theApp.localRegistry.SetValue(value, ID))
		return FALSE;
	return TRUE;
}


BOOL CT_WRITE_REGISTRY			(const char *value,	const char *ID)
{
	if (ERROR_SUCCESS != theApp.localRegistry.SetValue(value, ID))
		return FALSE;
	return TRUE;
}

// This function expects a string of KEY/VALUE pairs as follows:
// "key0: value0, key1: value1, key2: value2..."
// Taking a key as argument, the function returns the respective value 
// (if successful) or an empty string (if unsuccessful).
// ***CAUTION***: Of course you should not use this function if
// keys or values might contain separators (here: ":" or ",")
CString extractValueFromStringByKey(CString _key, CString _string) {
	CString result;
	int startKey = _string.Find(_key);
	if(startKey >= 0) {
		// determine where the value begins
		// (don't forget ":" and " ", thus the "+2")
		int startValue = startKey + _key.GetLength() + 2;
		// determine where the value ends
		// (either on a "," or it's the end of the string)
		int endValue = _string.Find(",", startValue);
		if(endValue >= 0) {
			// obviously we've separated our value successfully
			CString value = _string;
			value.Delete(endValue, _string.GetLength() - endValue);
			value.Delete(0, startValue);
			result = value;
		}
		else {
			CString value = _string;
			value.Delete(0, startValue);
			result = value;
		}
	}
	return result;
}