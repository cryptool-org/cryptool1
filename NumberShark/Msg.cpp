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

//
//  Copyright (C) 2005 Serge Wautier - appTranslator
//  
//  appTranslator - The ultimate localization tool for your Visual C++ applications
//                  http://www.apptranslator.com
//
//  This source code is provided 'as-is', without any express or implied
//  warranty. In no event will the author be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this source code must not be misrepresented; you must not
//    claim that you wrote the original source code. If you use this source code
//    in a product, an acknowledgment in the product documentation and in the
//    About box is required, mentioning appTranslator and http://www.apptranslator.com
//
//  2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original source code.
//
//  3. This notice may not be removed or altered from any source distribution
//

//
// Msg.cpp: Implementation of the CMsg and CFMsg classes
//
//   CMsg : Wrapper around LoadString(). CString that takes a resource string index in its c'tor
//
//   CFMsg : Wrapper around the API FormatMessage().
//

#include "stdafx.h"
#include "Msg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//
// CMsg : CString-derived class used to load strings form the resource string table
//        The index in the string table is passed to the c'tor.
//        Since CMsg derives from CString, it has an LPCTSTR operator, hence can replace a string literal.
//        e.g.: SetWindowText(CMsg(IDS_TITLE)); // Weather Forecast.
//

CMsg::CMsg(UINT nID) // nID = resource ID of string (in string table)
{
  if (!LoadString(nID))
  { // Error : string not found !
    TRACE(_T("Unknown resource string id : %d\n"),nID);
    ASSERT(false);
    CString::operator=(_T("???")); // In case of error, set string contents to ???. Compatible with VC6 and VC7.
  }
}

//
//   CFMsg: Creates a formatted message. Wrapper around the API FormatMessage(). Kind of super-printf().
//          Since CFMsg derives from CString, it has an LPCTSTR operator, hence can replace a string literal.
//          e.g.: AfxMessageBox( CFMsg(IDS_AGE, szName, nAge), MB_ICONINFORMATION ); 
//                                     // IDS_AGE : %1 is %2!d! years old.
//                                     // Message : Jane is 27 years old.
//

CFMsg::CFMsg(UINT nFormatID,...) // nFormatID = resource string containing text to format
{                               // uses FormatMessage() arguments notation : %1 %2 ...
	
  // Get format string from string table
	CString strFormat;
	if (!strFormat.LoadString(nFormatID))
  { // Format string not found -> Load error string : ???
    TRACE(_T("Unknown resource string id : %d\n"),nFormatID);
    ASSERT(false);
    CString::operator=(_T("???")); // In case of error, set string contents to ???. Compatible with VC6 and VC7.
  }
  else
  { // OK, format string was loaded successfully

	  // Format message into temporary buffer lpszTemp
	  va_list argList;
	  va_start(argList, nFormatID);
	  LPTSTR lpszTemp;
	  if (::FormatMessage(FORMAT_MESSAGE_FROM_STRING|FORMAT_MESSAGE_ALLOCATE_BUFFER,
		                    strFormat, 0, 0, (LPTSTR)&lpszTemp, 0, &argList) == 0 ||
		    lpszTemp == NULL)
	  {
		  AfxThrowMemoryException();
	  }

	  // Copy lpszTemp into the result string
	  CString::operator=(lpszTemp); // Compatible with VC6 and VC7.

    // Clean-up
	  LocalFree(lpszTemp);
	  va_end(argList);
  }
}

CFMsg::CFMsg(LPCTSTR lpszFormat,...)
{
	// Format message into temporary buffer lpszTemp
	va_list argList;
	va_start(argList, lpszFormat);
	LPTSTR lpszTemp;
	if (::FormatMessage(FORMAT_MESSAGE_FROM_STRING|FORMAT_MESSAGE_ALLOCATE_BUFFER,
		lpszFormat, 0, 0, (LPTSTR)&lpszTemp, 0, &argList) == 0 ||
		lpszTemp == NULL)
	{
		AfxThrowMemoryException();
	}

	// Copy lpszTemp into the result string
	CString::operator=(lpszTemp); // Compatible with VC6 and VC7.

  // Clean-up
	LocalFree(lpszTemp);
	va_end(argList);
}
