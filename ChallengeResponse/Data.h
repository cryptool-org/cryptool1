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

// Data.h: interface for the CData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATA_H__064E9A01_6BDC_11D6_9FD1_E9F62E3D370B__INCLUDED_)
#define AFX_DATA_H__064E9A01_6BDC_11D6_9FD1_E9F62E3D370B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CData  
{
public:
	CString getValueByLabel(CString label);
	CString getValueHidden(int i);
	CString getValue(int i);
	CString getLabel(int i);
	void copy(CData& orgData, bool copyValues);
	CString getLine(int i, bool isAttacker);
	int getNumberOfLines();
	void changeValue(CString label, CString value);
	void addLabel(CString label);
	void clearLists();
	CData();
	virtual ~CData();
	CStringList labels;
	CStringList values;
};

#endif // !defined(AFX_DATA_H__064E9A01_6BDC_11D6_9FD1_E9F62E3D370B__INCLUDED_)
