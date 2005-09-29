// 3DRenderBox.cpp: Implementierungsdatei
//

#include "stdafx.h"
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


//****************************************************************************************************************************
int SetPixelFormat(HDC hdc)
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
		MessageBox(NULL, "ChoosePixelFormat Failed", NULL, MB_OK);
		return 0;
	}
	 
	// make that match the device context's current pixel format 
	if(SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
	{
		MessageBox(NULL, "SetPixelFormat Failed", NULL, MB_OK);
		return 0;
	}


	return 1;
}



/////////////////////////////////////////////////////////////////////////////
// C3DRenderBox

C3DRenderBox::C3DRenderBox()
{
	m_pVolumeRenderer = NULL;
}

C3DRenderBox::~C3DRenderBox()
{
}


BEGIN_MESSAGE_MAP(C3DRenderBox, CWnd)
	//{{AFX_MSG_MAP(C3DRenderBox)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten C3DRenderBox 

int C3DRenderBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Speziellen Erstellungscode hier einfügen
	SetPixelFormat(::GetDC(m_hWnd));
	
	return 0;
}

void C3DRenderBox::OnPaint() 
{
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
			
			m_pVolumeRenderer->renderScene();

			glFinish();
			if (FALSE == SwapBuffers(hdc)) {
				AfxMessageBox(_T("ERROR: unable to swap buffers!"));
			}
			
        } 
    }  

	wglMakeCurrent(NULL, NULL) ; 
	::ReleaseDC (m_hWnd, hdc) ; 
	wglDeleteContext(hglrc); 

	// Do not call CWnd::OnPaint() for painting messages	
	// Kein Aufruf von CWnd::OnPaint() für Zeichnungsnachrichten
}

void C3DRenderBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	if (NULL != m_pVolumeRenderer) {
		m_pVolumeRenderer->OnLButtonDown(nFlags,point);
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void C3DRenderBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	if (NULL != m_pVolumeRenderer) {
		m_pVolumeRenderer->OnLButtonUp(nFlags,point);
	}
	CWnd::OnLButtonUp(nFlags, point);
}

void C3DRenderBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	if (NULL != m_pVolumeRenderer) {
		m_pVolumeRenderer->OnMouseMove(nFlags,point);
	}	
	CWnd::OnMouseMove(nFlags, point);
}

void C3DRenderBox::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	if (NULL != m_pVolumeRenderer) {
		m_pVolumeRenderer->setSize(cx, cy);
	}	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
}

BOOL C3DRenderBox::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen

	if( !CWnd::PreCreateWindow(cs) )
		return FALSE;

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}
