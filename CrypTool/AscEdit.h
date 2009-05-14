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

#if !defined(AFX_ASCEDIT_H__2B17B659_F65C_430E_BDB5_9181C5B3C75F__INCLUDED_)
#define AFX_ASCEDIT_H__2B17B659_F65C_430E_BDB5_9181C5B3C75F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AscEdit.h : Header-Datei
//

#define MAX_PERM_LENGTH 100

/////////////////////////////////////////////////////////////////////////////
// Fenster CAscEdit 

class CAscEdit : public CEdit
{
// Konstruktion
public:
	CAscEdit();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CAscEdit)
	//}}AFX_VIRTUAL

// Implementierung
public:
	int busy;
	virtual ~CAscEdit();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CAscEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	int m_mode;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ASCEDIT_H__2B17B659_F65C_430E_BDB5_9181C5B3C75F__INCLUDED_
