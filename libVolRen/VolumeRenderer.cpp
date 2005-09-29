// VolumeRenderer.cpp: implementation of the CVolumeRenderer class.
//
//////////////////////////////////////////////////////////////////////

#include <Afxwin.h>
#include <GL/gl.h>
#include <math.h>
#include "ArcBall.h"
#include "Volume.H"
#include "VolumeRenderer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DEG2RAD(a) ((a)/57.295)

#define ZOOM_MIN (0.05)
#define ZOOM_MAX (10.0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVolumeRenderer::CVolumeRenderer(CWnd *pParent)
{
	ASSERT(NULL != pParent);
	m_pParent = pParent;
	m_dFieldOfView = 45.0;
	m_pArcBall = new CArcBall();

	m_bDragging   = false;
	m_bZooming    = false;
	m_dZoom       = 1.0;
	m_dTranslateX = 0.0; 
	m_dTranslateY = 0.0;
	m_nWidth      = 0;
	m_nHeight     = 0;
	m_bInitialized = false;
	m_pVolume = NULL;
	m_pEditor = NULL;
	m_nPosX = 0;
	m_nPosY = 0;
}

CVolumeRenderer::~CVolumeRenderer()
{
	if (NULL != m_pArcBall) delete m_pArcBall;
	if (NULL != m_pVolume) delete m_pVolume;
	if (NULL != m_pEditor) delete m_pEditor;
}

void CVolumeRenderer::setVolume(int nResolution[3], double dVoxelSize[3], unsigned char *pBuffer) {
	
	m_dVolumeDimension[0] = dVoxelSize[0] * double(nResolution[0]);
	m_dVolumeDimension[1] = dVoxelSize[1] * double(nResolution[1]);
	m_dVolumeDimension[2] = dVoxelSize[2] * double(nResolution[2]);

	if (NULL != m_pVolume) {
		if (NULL != m_pEditor) {
			m_pEditor->setColorTable256(NULL);
			m_pEditor->setHistogram256(NULL);
		}
		delete [] m_pVolume;
	}

	m_pVolume = new CVolume(nResolution,dVoxelSize,pBuffer);

	if (NULL != m_pEditor) {
		m_pEditor->setColorTable256(m_pVolume->getColorTable());
		m_pEditor->setHistogram256(m_pVolume->getHistogram());
	}
	

}

void CVolumeRenderer::renderScene() {

	if (NULL == m_pVolume) return;

	if (false == m_bInitialized) init();

	GLfloat fTop, fRight, fNear, fFar;

	fNear   = float(m_dCenter - m_dRadius);
	fFar    = float(m_dCenter + m_dRadius);
	
	if (m_dAspectRatio > 1.0) {
		fRight = fNear * float(tan(DEG2RAD(m_dFieldOfView)/2.0) /m_dZoom);
		fTop   = fRight * float(m_dAspectRatio);
		
	} else {
		fTop   = fNear * float(tan(DEG2RAD(m_dFieldOfView)/2.0) /m_dZoom);
		fRight = fTop / float(m_dAspectRatio);
	} 

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum( -fTop, fTop, -fRight, fRight, fNear, fFar);
	glTranslated(m_dTranslateX * m_dRadius/m_dZoom, m_dTranslateY*m_dRadius/m_dZoom, -m_dCenter);

	glViewport(m_nPosX, m_nPosY, m_nWidth, m_nHeight );

	CMatrix matModel = m_pArcBall->getRotatonMatrix().getInverse();

	double matrix[16];
	matModel.get(matrix[ 0], matrix[ 4], matrix[ 8], matrix[12],
				 matrix[ 1], matrix[ 5], matrix[ 9], matrix[13],
				 matrix[ 2], matrix[ 6], matrix[10], matrix[14],
				 matrix[ 3], matrix[ 7], matrix[11], matrix[15]);

	glMatrixMode(GL_MODELVIEW);

	glPushAttrib(GL_LIGHTING_BIT | GL_ENABLE_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLoadIdentity();
	//glLoadMatrixd(m_pMatrixModelView);
//#define ENABLE_HEADLIGHT
#ifdef ENABLE_HEADLIGHT
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat light_ambient[]  = {0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse[]  = {0.5, 0.5, 0.5, 1.0};
	GLfloat light_specular[] = {1.0, 0.0, 0.0, 1.0};
	GLfloat light_position[] = {0.0, 0.0, -1.0, 0.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
#endif
	//glScaled(m_dZoom,m_dZoom,m_dZoom);
	glMultMatrixd(matrix);
	//glPushMatrix();
	glTranslated(m_vecCameraPosition[0], m_vecCameraPosition[1], m_vecCameraPosition[2]);

	if (NULL != m_pVolume)
		m_pVolume->render();

	//glPopMatrix();
	glPopAttrib();
}


void CVolumeRenderer::viewAll()
{
	
	
	
	m_dRadius              = 0.5f * sqrt( 
		m_dVolumeDimension[0] * m_dVolumeDimension[0] +
		m_dVolumeDimension[1] * m_dVolumeDimension[1]+
		m_dVolumeDimension[2] * m_dVolumeDimension[2]);

	m_vecCameraPosition.set(0.0, 0.0, 0.0,1.0);
				
	m_dCenter = m_dRadius/ sin(DEG2RAD(m_dFieldOfView)/2.0);
	
	m_dZoom = 1.0;
	m_dTranslateX = 0.0;
	m_dTranslateY = 0.0;
	
}

void CVolumeRenderer::init() {
	viewAll();
	m_bInitialized = true;

}


bool CVolumeRenderer::OnLButtonDown(UINT nFlags, CPoint point) {
// TODO: Add your message handler code here and/or call default
	
	m_pArcBall->setMouse(CPosition(point.x, m_nHeight- point.y));
	m_pArcBall->startDragging();
	return false;
}
bool CVolumeRenderer::OnLButtonUp(UINT nFlags, CPoint point) {
	m_pArcBall->finishDragging();
	return false;
}
bool CVolumeRenderer::OnMouseMove(UINT nFlags, CPoint point){

	CPosition pos(double(point.x)/double(m_nWidth),double(point.y)/double(m_nHeight));

	CPosition drag = pos-m_vecMouseDown;

	if (nFlags & MK_LBUTTON) {
		m_pArcBall->setMouse(CPosition(point.x, m_nHeight- point.y));
		m_pParent->Invalidate();
		return true;

	} else if ((m_bDragging) && (nFlags & MK_RBUTTON)) {
		
		m_dTranslateX +=  2.0 * drag[0];
		m_dTranslateY += -2.0  * drag[1];

		if (m_dTranslateX >  m_dZoom) m_dTranslateX =  m_dZoom;
		if (m_dTranslateX < -m_dZoom) m_dTranslateX = -m_dZoom;
		if (m_dTranslateY >  m_dZoom) m_dTranslateY =  m_dZoom;
		if (m_dTranslateY < -m_dZoom) m_dTranslateY = -m_dZoom;
		m_vecMouseDown = pos;
		m_pParent->Invalidate();
		return true;
	} else if ((m_bZooming) && (nFlags & (MK_RBUTTON|MK_CONTROL))) {
			
		double dZoom = 10.0*drag[0]; 
		m_dZoom += dZoom;
		if (m_dZoom < ZOOM_MIN) m_dZoom = ZOOM_MIN;
		if (m_dZoom > ZOOM_MAX) m_dZoom = ZOOM_MAX;
		if (m_dTranslateX >  m_dZoom) m_dTranslateX =  m_dZoom;
		if (m_dTranslateX < -m_dZoom) m_dTranslateX = -m_dZoom;
		if (m_dTranslateY >  m_dZoom) m_dTranslateY =  m_dZoom;
		if (m_dTranslateY < -m_dZoom) m_dTranslateY = -m_dZoom;
		m_vecMouseDown = pos;
		
		
		m_pParent->Invalidate();
		return true;
	}

	return false;
}


bool CVolumeRenderer::OnRButtonDown(UINT nFlags, CPoint point) {

	
	m_vecMouseDown.set(double(point.x)/double(m_nWidth),double(point.y)/double(m_nHeight));

	if (nFlags & MK_CONTROL) {
		// start zooming
		m_bZooming = true;

	} else {
	// start dragging
		m_bDragging = true;
	}
	return false;

}
bool CVolumeRenderer::OnRButtonUp(UINT nFlags, CPoint point) {
	m_bDragging = false;
	m_bZooming  = false;
	return false;

}

void CVolumeRenderer::setOrigin(int nX, int nY) {
	m_nPosX = nX;
	m_nPosY = nY;
	m_bInitialized = false;
}

void CVolumeRenderer::setSize(int nWidth, int nHeight) {
	
	if ((nWidth == m_nWidth) && (nHeight == m_nHeight)) return;

	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_dAspectRatio = double(m_nWidth)/double(m_nHeight);
	m_bInitialized = false;

	m_pArcBall->place(CPosition(nWidth/2, nHeight/2), 
			0.5 * sqrt((double)(nWidth * nWidth + nHeight * nHeight)));
	// m_pParent->Invalidate();
}

void CVolumeRenderer::showVolumeEditor()
{	
	if (NULL == m_pEditor) {
		m_pEditor = new CEditorDialog(this);
	}

	if (m_pEditor->GetSafeHwnd() == 0) {
		m_pEditor->Create();
	}
	if (m_pVolume != NULL) {
		m_pEditor->setColorTable256(m_pVolume->getColorTable());
		m_pEditor->setHistogram256(m_pVolume->getHistogram());
	}
	
	m_pEditor->ShowWindow(SW_SHOW);

	
}

void CVolumeRenderer::OnTransferFunctionChanged()
{
	if (NULL != m_pVolume) {
		m_pVolume->applyTransferFunction();
		m_pParent->Invalidate();
	}

}

void CVolumeRenderer::setSampling(double d) {
	if (NULL != m_pVolume) {
		m_pVolume->setSampling(d);
		// FIXME m_pParent->Invalidate();
	}
}

double CVolumeRenderer::getSampling() {
	if (NULL != m_pVolume) {
		return m_pVolume->getSampling();
	} 

	return 1.0;
}
void CVolumeRenderer::displayBoundingBox(bool on) {
	if (NULL != m_pVolume) {
		m_pVolume->displayBoundingBox(on);
		m_pParent->Invalidate();
	}
}

bool CVolumeRenderer::isBoundingBoxVisible(){
	if (NULL != m_pVolume) {
		return m_pVolume->isBoundingBoxVisible();
	}
	return false;
}

