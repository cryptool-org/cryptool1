#if !defined(AFX_3DRENDERBOX_H__60040607_3E15_4E7A_8745_B5B7C8B94002__INCLUDED_)
#define AFX_3DRENDERBOX_H__60040607_3E15_4E7A_8745_B5B7C8B94002__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DRenderBox.h : Header-Datei
//

#include "VolumeRenderer.h"

/////////////////////////////////////////////////////////////////////////////
// Fenster C3DRenderBox 

class C3DRenderBox : public CWnd
{
// Konstruktion
	CVolumeRenderer *m_pVolumeRenderer;

public:
	C3DRenderBox();
	setVolumeRenderer( CVolumeRenderer *m_pVolRen ) 
	{ m_pVolumeRenderer = m_pVolRen; }

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(C3DRenderBox)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~C3DRenderBox();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(C3DRenderBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_3DRENDERBOX_H__60040607_3E15_4E7A_8745_B5B7C8B94002__INCLUDED_
