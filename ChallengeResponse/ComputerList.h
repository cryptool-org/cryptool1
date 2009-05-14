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

// ComputerList.h: interface for the CComputerList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPUTERLIST_H__5A9ABDA2_6CD6_11D6_9FD1_F82875035D7B__INCLUDED_)
#define AFX_COMPUTERLIST_H__5A9ABDA2_6CD6_11D6_9FD1_F82875035D7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Computer.h"

class CComputerList  
{
public:
	CComputer& getComputer(int i);
	void addComputer(CComputer& computer);
	void clearList();
	CComputerList();
	virtual ~CComputerList();

private:
	CObList list;
};

#endif // !defined(AFX_COMPUTERLIST_H__5A9ABDA2_6CD6_11D6_9FD1_F82875035D7B__INCLUDED_)
