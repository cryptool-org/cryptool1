// OpenGLView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "OpenGLView.h"
#include "OpenGLDoc.h"
#include "CrypToolVolRen.h"

#include "OpenGL.h"
#include <gl/gl.h>
#include <gl/glu.h>

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
	m_pVolumeRenderer = NULL;
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
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_POPUP_OPENGL_SHOW_BOX, OnPopupOpenglShowBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung COpenGLView 

void COpenGLView::OnDraw(CDC* pDC)
{
	static BOOL sema = TRUE;
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
	if ( !sema )
		return;
	sema = FALSE;

	CPaintDC dc(this); // device context for painting
    if(wglMakeCurrent(dc.m_hDC, m_hOpenGLContext))
	{
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
		if (FALSE == SwapBuffers(dc.m_hDC)) {
			AfxMessageBox(_T("ERROR: unable to swap buffers!"));
		}
    } 
	sema = TRUE;
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

	::ReleaseDC(m_hWnd, hdc);

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

    // Createan  OpenGL rendering context
	m_hOpenGLContext = wglCreateContext(hdc);
	if(m_hOpenGLContext == NULL)
	{
		// AfxMessageBox(_T("ERROR: creating OpenGL context failed"));
		return false;
	}

	return 1;
}

void COpenGLView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	if (NULL != m_pVolumeRenderer) {
		m_pVolumeRenderer->OnMouseMove(nFlags,point);
	}


	CView::OnMouseMove(nFlags, point);
}

void COpenGLView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	if (NULL != m_pVolumeRenderer) {
		m_pVolumeRenderer->OnLButtonDown(nFlags,point);
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void COpenGLView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	if (NULL != m_pVolumeRenderer) {
		m_pVolumeRenderer->OnLButtonUp(nFlags,point);
	}	

	CView::OnLButtonUp(nFlags, point);
}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if( !CView::PreCreateWindow(cs) )
		return FALSE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}





#ifdef _DEBUG

COpenGLDoc* COpenGLView::GetDocument()
{
	return STATIC_DOWNCAST(COpenGLDoc, m_pDocument);
}

#endif //_DEBUG

void COpenGLView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	COpenGLDoc *pDoc = GetDocument();


	m_pVolumeRenderer = new CCrypToolVolRen(this);


	if ( m_pVolumeRenderer )
	{
  		if ( pDoc->volume )
			m_pVolumeRenderer->setVolume(pDoc->nResolution, pDoc->dVoxelSize, pDoc->volume->getVolume());
		RECT l_rect;
		this->GetWindowRect(&l_rect);
		m_pVolumeRenderer->setSize(l_rect.right-l_rect.left, l_rect.bottom -l_rect.top);	
	}
	
}

void COpenGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if ( m_pVolumeRenderer )
	{
		m_pVolumeRenderer->setSize(cx, cy);	
	}
}

void COpenGLView::OnContextMenu(CWnd* pWnd, CPoint point) 
{

   CPoint local = point;
   ScreenToClient(&local);

      CMenu menu;
      if (menu.LoadMenu(IDR_CONTEXT_MENU_OPENGL))
      {
         CMenu* pPopup = menu.GetSubMenu(0);
         ASSERT(pPopup != NULL);

         pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            AfxGetMainWnd()); // Verwenden Sie das Hauptfenster für die Befehle
      }
	
}

void COpenGLView::OnPopupOpenglShowBox() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	if ( m_pVolumeRenderer )
	{
		if ( m_pVolumeRenderer->isBoundingBoxVisible() )
			m_pVolumeRenderer->displayBoundingBox(false);
		else
			m_pVolumeRenderer->displayBoundingBox(true);
	}
}
