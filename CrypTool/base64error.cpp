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

#include "stdafx.h"
#include "CrypToolApp.h"
#include "base64.h"


void base64error(std::string text, char errchar,ssize_t errcode, ssize_t position, int chlb)
{
	char str[2]; 
	str[0] = errchar; str[1] = '\0';
	CString result="";

	switch(errcode)
	{	
		case -1:
			result.Format(IDS_BASE64_DECODE_PREMATURE_END, position, str);
			AfxMessageBox(result, MB_OK);
			break;
		case -2: 
			result.Format(IDS_BASE64_DECODE_ILLEGAL_CHARACTER, position, str);
			AfxMessageBox(result, MB_OK);
			break;
		case -3:
			result.Format(IDS_BASE64_DECODE_MISSING_CHARS, chlb,text);
			AfxMessageBox(result, MB_OK);
			break;
		case -4:		
			result.Format(IDS_BASE64_FILE_WRITE_ERROR,text);
			AfxMessageBox(result, MB_OK);
			break;
		case -5:
			result.Format(IDS_BASE64_FILE_OPEN_ERROR,text);
			AfxMessageBox(result, MB_OK);
			break;
	}
}