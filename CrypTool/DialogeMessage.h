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

#ifndef __DIALOG_MESSAGE_H
#define __DIALOG_MESSAGE_H

#include "stdafx.h"
#include "CrypToolApp.h"

//////////////////////////////////////////////////////////////////
//
//
//

#define IDS_STRINGLENGTH 1024
int Message(int IDS_STRING_ID, int FLAGS, int No1 = 0, int No2 = 0);
int Message(int IDS_STRING_ID, int FLAGS, int No, const char * str, bool transpose = false);
int Message(int IDS_STRING_ID, int FLAGS, const char* str1, const char* str2 = NULL);


#endif
