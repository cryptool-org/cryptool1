#if !defined(AFX_OPENGLVIEW_H__DD034059_50A5_46C7_9058_920B9EE74184__INCLUDED_)
#define AFX_OPENGLVIEW_H__DD034059_50A5_46C7_9058_920B9EE74184__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenGLView.h : Header-Datei
//

#include "VolumeRenderer.h"


/////////////////////////////////////////////////////////////////////////////
// Ansicht COpenGLView 

class COpenGLView : public CView
{

protected:
	COpenGLView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(COpenGLView)

// Attribute
public:

// Operationen
public:
	int Init(HDC hdc);

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COpenGLView)
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_OPENGLVIEW_H__DD034059_50A5_46C7_9058_920B9EE74184__INCLUDED_
