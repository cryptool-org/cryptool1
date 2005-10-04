#if !defined(AFX_OPENGLDOC_H__9396FCDE_475D_4938_A3AC_95354BFC4C7B__INCLUDED_)
#define AFX_OPENGLDOC_H__9396FCDE_475D_4938_A3AC_95354BFC4C7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenGLDoc.h : Header-Datei
//

#include "VolumeRenderer.h"
#include "VolumeUtilities.h"
#include "StreamToVolume.h"


/////////////////////////////////////////////////////////////////////////////
// Dokument COpenGLDoc 

class COpenGLDoc : public CAppDocument
{
protected:
	COpenGLDoc();           // Dynamische Erstellung verwendet gesch�tzten Konstruktor
	DECLARE_DYNCREATE(COpenGLDoc)

// Attribute
public:

// Operationen
public:
	CVolumeRenderer *m_pVolumeRenderer;
	unsigned char   *m_pCharBuffer;
	StreamToVolume  *volume;

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(COpenGLDoc)
	public:
	virtual void Serialize(CArchive& ar);   // �berschrieben f�r Dokument-Ein-/Ausgabe
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~COpenGLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(COpenGLDoc)
		// HINWEIS - Der Klassen-Assistent f�gt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_OPENGLDOC_H__9396FCDE_475D_4938_A3AC_95354BFC4C7B__INCLUDED_
