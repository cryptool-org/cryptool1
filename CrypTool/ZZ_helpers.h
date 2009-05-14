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

#include <NTL/ZZX.h>
#include <afx.h>

using namespace NTL;

CString toString(ZZ zTmp, int base, int groupBy);
CString toString(ZZ zTmp, int base, int groupBy, int groupOffset, int minLength);
ZZ setToStringValue(CString value, int base);
ZZ evalF(ZZX f, ZZ x);
CString readable(ZZX t1);
ZZX differentiate(ZZX f);
ZZX power(ZZX a, int e);
 