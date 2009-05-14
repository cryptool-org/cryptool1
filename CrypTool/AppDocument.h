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

#ifndef AFX_MYDOCUMENT_H__AD95E458_D56B_11D3_878E_00C04F795E36__INCLUDED_
#define AFX_MYDOCUMENT_H__AD95E458_D56B_11D3_878E_00C04F795E36__INCLUDED_

// MyDocument.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dokument CAppDocument 

class CAppDocument : public CDocument
{
protected:
	CAppDocument();           // Dynamische Erstellung verwendet gesch�tzten Konstruktor
	DECLARE_DYNCREATE(CAppDocument)

// Attribute
public:

// Operationen
public:
	virtual void SetData(int);
	void ClearPathName() { m_strPathName = ""; }
	BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace = TRUE);
// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CAppDocument)
	public:
	virtual void Serialize(CArchive& ar);   // �berschrieben f�r Dokument-Ein-/Ausgabe
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
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_MYDOCUMENT_H__AD95E458_D56B_11D3_878E_00C04F795E36__INCLUDED_
