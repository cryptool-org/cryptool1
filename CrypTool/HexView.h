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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_HEXVIEW_H__0EFC0691_5F70_11D3_8772_00C04F795E36__INCLUDED_
#define AFX_HEXVIEW_H__0EFC0691_5F70_11D3_8772_00C04F795E36__INCLUDED_

// HexView.h : Header-Datei
//

#include "AppEditView.h"

/////////////////////////////////////////////////////////////////////////////
// Ansicht CHexView 

class CHexView : public CAppEditView
{
protected:
	CHexView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CHexView)

// Attribute
public:

// Operationen
public:
	int m_NoPrintChars;
	int m_TrailBlanks;
	HRESULT QueryAcceptData(LPDATAOBJECT lpdataobj, CLIPFORMAT *lpcfFormat, DWORD dwReco, 
		                    BOOL bReally, HGLOBAL hMetaFile);
	virtual void SerializeRaw(CArchive& ar);
	CSize CharSize;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CHexView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CHexView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	int m_NewSize;
	BOOL m_SizeActive;
	int AdjustCursor(int direction);
	int m_curlen;
	int m_totlen;
	int m_lineoffset;
	int m_curline;
	int m_hexwidth;
	int m_charoffset;
	int m_lineindex;
	char m_line[1024];
	bool m_EOF; // indicates the attempt to attach a character at the end of file
	CFont m_Font;
	//{{AFX_MSG(CHexView)
	afx_msg void OnUpdateFalse(CCmdUI* pCmdUI);
	afx_msg void OnEmpty();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdateTotxt(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char GetCharAt(int offset);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_HEXVIEW_H__0EFC0691_5F70_11D3_8772_00C04F795E36__INCLUDED_
