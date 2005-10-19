// OpenGLDoc.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "OpenGLDoc.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGLDoc

IMPLEMENT_DYNCREATE(COpenGLDoc, CDocument)

COpenGLDoc::COpenGLDoc()
{
//	m_pVolumeRenderer = NULL;
	volume = NULL;
}

BOOL COpenGLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

COpenGLDoc::~COpenGLDoc()
{
}


BEGIN_MESSAGE_MAP(COpenGLDoc, CDocument)
	//{{AFX_MSG_MAP(COpenGLDoc)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose COpenGLDoc

#ifdef _DEBUG
void COpenGLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COpenGLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Serialisierung COpenGLDoc 

void COpenGLDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Code zum Speichern hier einfügen
	}
	else
	{
		// ZU ERLEDIGEN: Code zum Laden hier einfügen

		if ( volume == NULL ) {
			nResolution[0] = 128;
			nResolution[1] = 128;
			nResolution[2] = 128;
			dVoxelSize[0] = 1;
			dVoxelSize[1] = 1;
			dVoxelSize[2] = 1;
			wordlen = 4;
			unsigned int numVals = nResolution[0] * nResolution[1] * nResolution[2];

			if (volume != NULL)
				delete volume;
			volume = new StreamToVolume (nResolution[0], nResolution[1], nResolution[2]);

			if (volume->getVolume() != NULL) 
			{
				char name[1024];
				strcpy(name, ar.m_strFileName);
				ifstream f;
				f.open(name);
				if (!f.is_open())
				{
					// FIXME Error
				}
				else
				{
					char sMagic[128];
					char sFile[1024];
					f.getline(sMagic, 128);
					f.getline(sFile, 1024);

					if ( strncmp(sMagic,"OPENGL", 6) )
					{
						// FIXME: ERROR
					}
					else
					{
						volume->setWordLen(wordlen);
						volume->analyzeFile(sFile);
					}
				}
			}
		}

	}
}

/////////////////////////////////////////////////////////////////////////////
// Befehle COpenGLDoc 
