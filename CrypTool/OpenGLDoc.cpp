// OpenGLDoc.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "OpenGLDoc.h"

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
	m_pVolumeRenderer = NULL;
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
		if (NULL == m_pVolumeRenderer)
		{
			int nResolution[3] = {30, 30, 30};
			double dVoxelSize[3] = {1, 1, 1};
			int wordlen = 4;
			unsigned int numVals = nResolution[0] * nResolution[1] * nResolution[2];

			if (volume != NULL)
				delete volume;
			volume = new StreamToVolume (nResolution[0], nResolution[1], nResolution[2]);

			if (volume->getVolume() != NULL) {
				volume->setWordLen(wordlen);
				volume->analyzeFile("C:\Programme\bin\Winscp3.exe", mode_AutoDensity);

				POSITION pos = GetFirstViewPosition();
				CWnd *hWnd  = this->GetNextView(pos)->GetForegroundWindow();
				m_pVolumeRenderer = new CVolumeRenderer( hWnd );

				if ( NULL != m_pVolumeRenderer ) {
					m_pVolumeRenderer->setVolume(nResolution, dVoxelSize, volume->getVolume());

					if (NULL != m_pVolumeRenderer) {
//						m_pVolumeRenderer->displayBoundingBox(1);
//						m_pVolumeRenderer->setSize(400, 400);
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// Befehle COpenGLDoc 
