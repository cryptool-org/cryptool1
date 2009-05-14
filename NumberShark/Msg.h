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
// Msg.h: Declaration of the CMsg and CFMsg classes
//

#pragma once

//
//   CMsg : Wrapper around LoadString().
//          The index in the string table is passed to the c'tor.
//          Since CMsg derives from CString, it has an LPCTSTR operator, hence can replace a string literal.
//
//          e.g.: AfxMessageBox(CMsg(IDS_ERROR), MB_ICONERROR); // Error. Login Failed.
//

class CMsg : public CString  
{
public :
  CMsg(UINT nID); // c'tor loads a string from the resource string table
};

//
//   CFMsg: Creates a formatted message. Wrapper around the API FormatMessage(). Kind of super-printf().
//          Since CFMsg derives from CString, it has an LPCTSTR operator, hence can replace a string literal.
//
//          e.g.: AfxMessageBox( CFMsg(IDS_AGE, szName, nAge), MB_ICONINFORMATION ); 
//                                     // IDS_AGE : %1 is %2!d! years old.
//                                     // Message : Jane is 27 years old.
//

class CFMsg : public CString 
{                            
public:
  CFMsg(LPCTSTR pszFormat,...); // Format string can be a string literal...
  CFMsg(UINT nFormatID,...);    // ... or a string stored in the string table.
};

