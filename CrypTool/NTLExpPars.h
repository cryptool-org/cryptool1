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

// NTLExpPars.h: Schnittstelle für die Klasse NTLExpPars.
//
//////////////////////////////////////////////////////////////////////
#define NOMINMAX
#include "NTL/ZZ.h"
#include "afx.h"
using namespace NTL;
#if !defined(AFX_NTLEXPPARS_H__6DF4E263_4879_4A94_9CD0_5E85B8AC0053__INCLUDED_)
#define AFX_NTLEXPPARS_H__6DF4E263_4879_4A94_9CD0_5E85B8AC0053__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NTL_OP_END 0
#define NTL_OP_PLUS 1
#define NTL_OP_MINUS 2
#define NTL_OP_TIMES 3
#define NTL_OP_DIV 4
#define NTL_OP_POWER 5
#define NTL_OP_OPENPAR 6
#define NTL_OP_CLOSEPAR 7
#define NTL_OP_NUMBER 8
#define NTL_OP_ERROR 255



class NTLExpPars  
{
public:
	CString verbose;
	ZZ parseExp(CString ex);
	NTLExpPars();
	virtual ~NTLExpPars();

private:
	int lastToken;
	bool lowPrecedence(int a, int b);
	ZZ calc(ZZ a, ZZ b, int op);
	int nextToken(CString& ex, ZZ& v);
};

#endif // !defined(AFX_NTLEXPPARS_H__6DF4E263_4879_4A94_9CD0_5E85B8AC0053__INCLUDED_)
