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

#include "DialogeMessage.h"

//////////////////////////////////////////////////////////////////////////////
//
// Message Box Handling
//

int Message( int IDS_STRING_ID, int FLAGS, int No1, int No2 )
{
	char line[IDS_STRINGLENGTH];

	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID, pc_str,STR_LAENGE_STRING_TABLE);
	sprintf( line, pc_str, No1, No2);
	return AfxMessageBox(line, FLAGS);
}

int Message(int IDS_STRING_ID, int FLAGS, int No, const char * str, bool transpose)
{
	char line[IDS_STRINGLENGTH];

	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID, pc_str,STR_LAENGE_STRING_TABLE);
	if ( transpose )
	{
		sprintf( line, pc_str, str, No );
	}
	else
	{
		sprintf( line, pc_str, No, str );
	}
	return AfxMessageBox (line, FLAGS);
}

int Message(int IDS_STRING_ID, int FLAGS, const char* str1, const char* str2)
{
	char line[IDS_STRINGLENGTH];

	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID, pc_str,STR_LAENGE_STRING_TABLE);
	if ( NULL == str2 )
	{
		sprintf( line, pc_str, str1 );
	}
	else
	{
		sprintf( line, pc_str, str1, str2 );
	}
	return AfxMessageBox (line, FLAGS);
}



