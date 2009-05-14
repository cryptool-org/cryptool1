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
#include "uucode.h"


void uucodeerror(std::string text, char errchar,ssize_t errcode, ssize_t position, int chlb, int lines)
{
	char str[2]; 
	str[0] = errchar; str[1] = '\0';
	CString result="";

	switch(errcode)
	{	
		case -1:
			result.Format(IDS_UU_DECODE_MISSING_BEGIN);
			AfxMessageBox(result, MB_OK);
			break;
		case -2: 
			result.Format(IDS_UU_DECODE_ILLEGAL_CHARACTER, position, str);
			AfxMessageBox(result, MB_OK);
			break;
		case -3:
			result.Format(IDS_UU_DECODE_MISSING_CHAR, chlb,text);
			AfxMessageBox(result, MB_OK);
			break;
		case -4:		
			result.Format(IDS_UU_FILE_WRITE_ERROR,text);
			AfxMessageBox(result, MB_OK);
			break;
		case -5:
			result.Format(IDS_UU_FILE_OPEN_ERROR);
			AfxMessageBox(result, MB_OK);
			break;
		case -6:
			result.Format(IDS_UU_DECODE_LB_DIFFERS_TOSHORT, lines);
			AfxMessageBox(result, MB_OK);
			break;
		case -7:
			result.Format(IDS_UU_DECODE_LB_DIFFERS_TOLONG, lines);
			AfxMessageBox(result, MB_OK);
			break;
		case -8:
			result.Format(IDS_UU_DECODE_MISSING_FN);
			AfxMessageBox(result, MB_OK);
			break;
		case -9:
			result.Format(IDS_UU_DECODE_MISSING_END);
			AfxMessageBox(result, MB_OK);
			break;
		case -10:
			result.Format(IDS_UU_DECODE_MISSING_NL_BEFORE_END);
			AfxMessageBox(result, MB_OK);
			break;
		case -11:
			result.Format(IDS_UU_DECODE_MISSING_NL_AFTER_END);
			AfxMessageBox(result, MB_OK);
			break;
	}
}