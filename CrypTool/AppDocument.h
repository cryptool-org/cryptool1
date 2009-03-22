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


#ifndef AFX_MYDOCUMENT_H__AD95E458_D56B_11D3_878E_00C04F795E36__INCLUDED_
#define AFX_MYDOCUMENT_H__AD95E458_D56B_11D3_878E_00C04F795E36__INCLUDED_

// MyDocument.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dokument CAppDocument 

class CAppDocument : public CDocument
{
protected:
	CAppDocument();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CAppDocument)

// Attribute
public:

// Operationen
public:
	virtual void SetData(int);
	void ClearPathName() { m_strPathName = ""; }
	BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace = TRUE);
// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CAppDocument)
	public:
	virtual void Serialize(CArchive& ar);   // Überschrieben für Dokument-Ein-/Ausgabe
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementierung
public:
	HWND hWndVaterFenster;
	CWnd* CWndVaterFenster;
	CString csSchluessel;
	int iSchluesselTyp;
	virtual ~CAppDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CAppDocument)
	afx_msg void OnUpdateGotoVater(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowKey(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int fontSize;
	CString fontFace;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_MYDOCUMENT_H__AD95E458_D56B_11D3_878E_00C04F795E36__INCLUDED_
