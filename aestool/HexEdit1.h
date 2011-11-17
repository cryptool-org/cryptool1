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


#if !defined(AFX_HEXEDIT1_H__04BE516C_E9FF_11D3_888D_0010A4F6E7D5__INCLUDED_)
#define AFX_HEXEDIT1_H__04BE516C_E9FF_11D3_888D_0010A4F6E7D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HexEdit1.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CHexEdit 

class CHexEdit : public CEdit
{
// Konstruktion
public:
	CHexEdit();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CHexEdit)
	//}}AFX_VIRTUAL

// Implementierung
public:
	int SetHex(char *data, int len);
	int SetAscii(CString);
	char * BinData;
	int BinLen;
	int HexVal(char c);
	virtual ~CHexEdit();
	void SetValidChars(LPCTSTR validchars) { m_validchars = validchars; }
	void SetFixedByteLength(int l);
	void SetFillChar(char c) { m_fillchar = c; }
	virtual bool isvalidchar(char);
	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CHexEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnUpdate();
	afx_msg LRESULT OnPaste(WPARAM wparam, LPARAM lparam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int active;
	int BinBuffLen;
	int m_fixedbytelength; // if >0 then the field is fixed length
	char m_fillchar; // if shorter it is filled up with this char
	int m_insert; // insert mode; default: 0 == overwrite mode
	LPCTSTR m_validchars; // default: "0123456789ABCDEF"
	void postproc( char *oldstring, int start, int end );
	void preproc( char **oldstring, int *start, int *end, char ch );
	int shrink(int val);
	int extend(int val, int max);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_HEXEDIT1_H__04BE516C_E9FF_11D3_888D_0010A4F6E7D5__INCLUDED_
