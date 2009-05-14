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


#ifndef _CRYPTOOLVIEW_H_
#define _CRYPTOOLVIEW_H_

class CCrypToolView : public CView
{
protected:
	CCrypToolView();
	DECLARE_DYNCREATE(CCrypToolView)

// Attribute
public:

// Operationen
public:
// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CCrypToolView)
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CCrypToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	CFont font;
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//{{AFX_MSG(CCrypToolView)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
#if 0
	afx_msg void OnViewEndOfLine();
	afx_msg void OnUpdateViewEndOfLine(CCmdUI* pCmdUI);
	afx_msg void OnViewLineWrap();
	afx_msg void OnUpdateViewLineWrap(CCmdUI* pCmdUI);
	afx_msg void OnViewWhitespace();
	afx_msg void OnUpdateViewWhitespace(CCmdUI* pCmdUI);
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	// flomar
	void find();
	void findAndReplace();
	void findAndReplaceAll();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_MYEDITVIEW_H__AD95E45B_D56B_11D3_878E_00C04F795E36__INCLUDED_
