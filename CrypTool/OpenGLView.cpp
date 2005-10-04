// OpenGLView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "OpenGLView.h"
#include "OpenGLDoc.h"

#include "OpenGL.h"
#include <gl/gl.h>
#include <gl/glu.h>

#include "cryptoolapp.h"
#include "3DRenderBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

COpenGLView::COpenGLView()
{
}

COpenGLView::~COpenGLView()
{
}


BEGIN_MESSAGE_MAP(COpenGLView, CView)
	//{{AFX_MSG_MAP(COpenGLView)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung COpenGLView 

void COpenGLView::OnDraw(CDC* pDC)
{
	CDocument *pDoc = GetDocument();
//	((COpenGLDoc*)pDoc)->m_pVolumeRenderer->setParent(this);


	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	HDC hdc = ::GetDC(m_hWnd);
	HGLRC hglrc;

	// TODO: Add your message handler code here
	glClearColor(0,0,0,0);
	glColor3f(1, 1, 1);

	if (hglrc = wglCreateContext(hdc))
	{ 
        // try to make it the thread's current rendering context 

        if(wglMakeCurrent(hdc, hglrc))
		{
 			/*
			//render here
			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_TRIANGLES);
			glColor3f(1, 0, 0);
			glVertex3f(.5, 0, 0);
			glColor3f(0, 1, 0);
			glVertex3f(0, .5, 0);
			glColor3f(0, 0, 1);
			glVertex3f(-.5, 0, 0);
			glEnd();
			SwapBuffers(hdc);
			*/

			glDrawBuffer(GL_BACK); 

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glShadeModel(GL_SMOOTH);
			glEnable(GL_DEPTH_TEST);
			//glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

			glClearDepth(1.0f);
			glClearColor(0.0f,0.0f,0.0f,1.0f);
			//glClearColor(0.2f,0.2f,0.5f,1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			RECT l_rect;
			this->GetWindowRect(&l_rect);
			((COpenGLDoc*)pDoc)->m_pVolumeRenderer->setSize(l_rect.right-l_rect.left, l_rect.bottom -l_rect.top);

			((COpenGLDoc*)pDoc)->m_pVolumeRenderer->renderScene();
//			((COpenGLDoc*)pDoc)->m_pVolumeRenderer->displayBoundingBox(1);

			glFinish();
			if (FALSE == SwapBuffers(hdc)) {
				AfxMessageBox(_T("ERROR: unable to swap buffers!"));
			}
			
        } 
    }  

	wglMakeCurrent(NULL, NULL) ; 
	::ReleaseDC (m_hWnd, hdc) ; 
	wglDeleteContext(hglrc); 

}

/////////////////////////////////////////////////////////////////////////////
// Diagnose COpenGLView

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COpenGLView 

int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	HDC hdc = ::GetDC(this->m_hWnd);
	Init(hdc);

//	CDocument *pDoc = GetDocument();
//	this->m_hWnd = this->GetWindow()->m_hWnd;
//	((COpenGLDoc*)pDoc)->m_pVolumeRenderer->setParent(this);
	

	return 0;
}

int COpenGLView::Init(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd 
	    1,                                // version number 
	    PFD_DRAW_TO_WINDOW |              // support window 
	    PFD_SUPPORT_OPENGL |              // support OpenGL 
	    PFD_DOUBLEBUFFER,                 // double buffered 
	    PFD_TYPE_RGBA,                    // RGBA type 
	    24,                               // 24-bit color depth 
	    0, 0, 0, 0, 0, 0,                 // color bits ignored 
	    8,                                // no alpha buffer 
	    0,                                // shift bit ignored 
	    0,                                // no accumulation buffer 
	    0, 0, 0, 0,                       // accum bits ignored 
	    32,                               // 32-bit z-buffer     
	    0,                                // no stencil buffer 
	    0,                                // no auxiliary buffer 
	    PFD_MAIN_PLANE,                   // main layer 
	    0,                                // reserved 
	    0, 0, 0                           // layer masks ignored 
	}; 

	
	int  iPixelFormat; 
 
	// get the device context's best, available pixel format match 
	if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
	{
		// MessageBox(NULL, "ChoosePixelFormat Failed", NULL, MB_OK);
		return 0;
	}
	 
	// make that match the device context's current pixel format 
	if(SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
	{
		// MessageBox(NULL, "SetPixelFormat Failed", NULL, MB_OK);
		return 0;
	}


	return 1;
}

void COpenGLView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CDocument *pDoc = GetDocument();
	if (NULL != ((COpenGLDoc*)pDoc)->m_pVolumeRenderer) {
		((COpenGLDoc*)pDoc)->m_pVolumeRenderer->OnMouseMove(nFlags,point);
	}

	CView::OnMouseMove(nFlags, point);
}

void COpenGLView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CDocument *pDoc = GetDocument();
	if (NULL != ((COpenGLDoc*)pDoc)->m_pVolumeRenderer) {
		((COpenGLDoc*)pDoc)->m_pVolumeRenderer->OnLButtonDown(nFlags,point);
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void COpenGLView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CDocument *pDoc = GetDocument();
	if (NULL != ((COpenGLDoc*)pDoc)->m_pVolumeRenderer) {
		((COpenGLDoc*)pDoc)->m_pVolumeRenderer->OnLButtonUp(nFlags,point);
	}	

	CView::OnLButtonUp(nFlags, point);
}
