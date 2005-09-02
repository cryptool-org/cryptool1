// ScintillaDoc.h : Schnittstelle der Klasse CScintillaDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ScintillaDoc_H__B0181E56_C987_4057_BB38_3453D7B6776E__INCLUDED_)
#define AFX_ScintillaDoc_H__B0181E56_C987_4057_BB38_3453D7B6776E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//class CScintillaDoc : public CDocument
//HACK:
#include "CryptDoc.h"
class CScintillaDoc : public CCryptDoc
{
protected: // Nur aus Serialisierung erzeugen
	CScintillaDoc();
	DECLARE_DYNCREATE(CScintillaDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CScintillaDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
#if 0
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
#endif
// Implementierung
public:
	virtual ~CScintillaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CScintillaDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ScintillaDoc_H__B0181E56_C987_4057_BB38_3453D7B6776E__INCLUDED_)
