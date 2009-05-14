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
#include "cryptoolapp.h"


/////////////////////////////////////////////////////////////////////////////
// Dokument COpenGLDoc 

class COpenGLDoc : public CAppDocument
{
protected:
	COpenGLDoc();           // Dynamische Erstellung verwendet geschützten Konstruktor
	COpenGLDoc(int arg_resolution, int arg_density, int arg_shift, int arg_wordlen);

	DECLARE_DYNCREATE(COpenGLDoc)

// Attribute
private:
// Operationen
	int				 resolution;
	int				 density;
	double			 voxelsize;
	int				 wordlen;
	int				 shift;
	char             sFile[1024];

public:
//	unsigned char   *m_pCharBuffer;
	int				 nResolution[3];
	double			 dVoxelSize[3];

	StreamToVolume  *volume;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COpenGLDoc)
	public:
	virtual void Serialize(CArchive& ar);   // Überschrieben für Dokument-Ein-/Ausgabe
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
	virtual void setResolution(int arg);
	virtual void setDensity(int arg);
	virtual void setShift(int arg);
	virtual void setVoxelSize(double arg);
	virtual void setWordLen(int arg);

	virtual int getResolution();
	virtual int getDensity();
	virtual int getShift();
	virtual double getVoxelSize();
	virtual int getWordLen();

	virtual bool createVolumeData();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(COpenGLDoc)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_OPENGLDOC_H__9396FCDE_475D_4938_A3AC_95354BFC4C7B__INCLUDED_
