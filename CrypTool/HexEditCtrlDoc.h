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

// This file was originally written by Christian Kuendig. It was 
// obtained from www.codeguru.com in May 2005 and modified as necessary.


/////////////////////////////////////////////////////////////////////////////
// HexEditCtrlDoc.h : interface of the CHexEditCtrlDoc class
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_HEXEDITCTRLDOC_H__5BB7F667_959E_4E56_9A8B_4726E4407CC2__INCLUDED_)
#define AFX_HEXEDITCTRLDOC_H__5BB7F667_959E_4E56_9A8B_4726E4407CC2__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CryptDoc.h"

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// class CHexEditCtrlDoc
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class CHexEditCtrlDoc : public CCryptDoc
{
protected:

	//{{AFX_VIRTUAL(CHexEditCtrlDoc)
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CHexEditCtrlDoc)
	afx_msg void OnTotxt();
	//}}AFX_MSG

	DECLARE_DYNCREATE(CHexEditCtrlDoc)
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_HEXEDITCTRLDOC_H__5BB7F667_959E_4E56_9A8B_4726E4407CC2__INCLUDED_)
