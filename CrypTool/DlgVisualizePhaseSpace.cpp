// DlgVisualizePhaseSpace.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "DlgVisualizePhaseSpace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgVisualizePhaseSpace 


CDlgVisualizePhaseSpace::CDlgVisualizePhaseSpace(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVisualizePhaseSpace::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVisualizePhaseSpace)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	volume = NULL;
	m_pVolumeRenderer = NULL;
	m_pDisplay = new C3DRenderBox();

}

CDlgVisualizePhaseSpace::~CDlgVisualizePhaseSpace()
{
	if (m_pDisplay)
		delete m_pDisplay;

	if (m_pVolumeRenderer)
		delete m_pVolumeRenderer;

	if (volume)
		delete volume;
}

void CDlgVisualizePhaseSpace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVisualizePhaseSpace)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVisualizePhaseSpace, CDialog)
	//{{AFX_MSG_MAP(CDlgVisualizePhaseSpace)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgVisualizePhaseSpace 

BOOL CDlgVisualizePhaseSpace::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
#if 0
	m_pVolumeRenderer = new CVolumeRenderer(this);
	m_pDisplay->setVolumeRenderer(m_pVolumeRenderer);

	CRect rect(7, 7, 600, 400);
	m_pDisplay->Create( NULL,   //CWnd default
						NULL,   //has no name
						WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_VISIBLE,
						rect,
						this,   //this is the parent
						0);     //this should really be a different number... check resource.h
#endif


	CRect rect(7, 7, 400, 400);
	m_pDisplay->Create( NULL,   //CWnd default
						NULL,   //has no name
						WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_VISIBLE,
						rect,
						this,   //this is the parent
						0);     //this should really be a different number... check resource.h
	
	m_pVolumeRenderer = new CVolumeRenderer(m_pDisplay);
	m_pDisplay->setVolumeRenderer(m_pVolumeRenderer);

	if (NULL != m_pVolumeRenderer) {
		m_pVolumeRenderer->displayBoundingBox(1);
	}

	LoadData();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

BOOL CDlgVisualizePhaseSpace::LoadData()
{
	//int nResolution[3] = {256, 256, 256};
	// int nResolution[3] = {128, 128, 128};
	int nResolution[3] = {30, 30, 30};
	double dVoxelSize[3] = {1, 1, 1};
	int wordlen = 4;
	unsigned int numVals = nResolution[0] * nResolution[1] * nResolution[2];

	if (volume != NULL)
		delete volume;
	volume = new StreamToVolume (nResolution[0], nResolution[1], nResolution[2]);

	volume->setWordLen(wordlen);
	volume->analyzeFile(Filename, mode_AutoDensity);

	if (volume->getVolume() != NULL) {
		m_pVolumeRenderer->setVolume(nResolution, dVoxelSize, volume->getVolume());
		// m_pVolumeRenderer->setSampling(1.0);
	}
// #if 0
	if (NULL != m_pVolumeRenderer) {
		m_pVolumeRenderer->setSize(400, 400);
	}
// #endif

	this->Invalidate(FALSE);
	return TRUE;
}

void CDlgVisualizePhaseSpace::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
#if 0
	if (NULL != m_pVolumeRenderer) {
		m_pVolumeRenderer->setSize(250, 250);
	}
#endif

	
}

