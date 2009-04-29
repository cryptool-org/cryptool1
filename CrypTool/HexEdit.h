/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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
