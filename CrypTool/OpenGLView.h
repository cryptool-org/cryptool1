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

#if !defined(AFX_OPENGLVIEW_H__DD034059_50A5_46C7_9058_920B9EE74184__INCLUDED_)
#define AFX_OPENGLVIEW_H__DD034059_50A5_46C7_9058_920B9EE74184__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenGLView.h : Header-Datei
//

#include "CrypToolVolRen.h"
#include "OpenGLDoc.h"
#include "cryptoolapp.h"

// we need those defines for our dynamic context menu
#define CM_OPENGL_PROPERTIES						7777
#define CM_OPENGL_TOGGLE_BORDER_LINES		7778

/////////////////////////////////////////////////////////////////////////////
// Ansicht COpenGLView 

class COpenGLView : public CView
{

protected:
	COpenGLView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(COpenGLView)

// Attribute
public:

	CPalette    m_cPalette;
	CPalette    *m_pOldPalette;
//	CRect       m_oldRect;
//	float       m_fRadius;
	CClientDC   *m_pDC;
	CView       *tmpView;
	CWnd		tmpWnd;


	CCrypToolVolRen *m_pVolumeRenderer;
	unsigned char   *m_pCharBuffer;
	HGLRC			 m_hOpenGLContext;

// Operationen
public:
	unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift);
	void CreateRGBPalette();
	COpenGLDoc* GetDocument();
	int Init();

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COpenGLView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(COpenGLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPopupOpenglShowBox();
	afx_msg void OnDestroy();
	afx_msg void OnPopupOpenglEigenschaften();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL bSetupPixelFormat(void);
};

#ifndef _DEBUG  // debug version in cubeview.cpp
inline COpenGLDoc* COpenGLView::GetDocument()
   { return (COpenGLDoc*)m_pDocument; }
#endif


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_OPENGLVIEW_H__DD034059_50A5_46C7_9058_920B9EE74184__INCLUDED_
