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

// OpenGLView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "OpenGLView.h"
#include "OpenGLDoc.h"
#include "CrypToolVolRen.h"
#include "3DVisOpt.h"

#include "OpenGL.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include ".\openglview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// DONT KNOW WHAT IAM DOING

unsigned char threeto8[8] =
{
	0, 0111>>1, 0222>>1, 0333>>1, 0444>>1, 0555>>1, 0666>>1, 0377
};

unsigned char twoto8[4] =
{
	0, 0x55, 0xaa, 0xff
};

unsigned char oneto8[2] =
{
	0, 255
};

static int defaultOverride[13] =
{
	0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91
};

static PALETTEENTRY defaultPalEntry[20] =
{
	{ 0,   0,   0,    0 },
	{ 0x80,0,   0,    0 },
	{ 0,   0x80,0,    0 },
	{ 0x80,0x80,0,    0 },
	{ 0,   0,   0x80, 0 },
	{ 0x80,0,   0x80, 0 },
	{ 0,   0x80,0x80, 0 },
	{ 0xC0,0xC0,0xC0, 0 },

	{ 192, 220, 192,  0 },
	{ 166, 202, 240,  0 },
	{ 255, 251, 240,  0 },
	{ 160, 160, 164,  0 },

	{ 0x80,0x80,0x80, 0 },
	{ 0xFF,0,   0,    0 },
	{ 0,   0xFF,0,    0 },
	{ 0xFF,0xFF,0,    0 },
	{ 0,   0,   0xFF, 0 },
	{ 0xFF,0,   0xFF, 0 },
	{ 0,   0xFF,0xFF, 0 },
	{ 0xFF,0xFF,0xFF, 0 }
};

// DONT KNOW WHAT IAM DOING


/////////////////////////////////////////////////////////////////////////////
// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

COpenGLView::COpenGLView()
{
	m_pVolumeRenderer = NULL;
	m_pDC = NULL;
	m_pOldPalette = NULL;
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
	ON_WM_DESTROY()
	ON_COMMAND(ID_POPUP_OPENGL_EIGENSCHAFTEN, OnPopupOpenglEigenschaften)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung COpenGLView 

void COpenGLView::OnDraw(CDC* pDC)
{
	static BOOL busy = FALSE;
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
	if ( busy )
		return;
	busy = TRUE;

	if ( wglMakeCurrent(m_pDC->GetSafeHdc(), m_hOpenGLContext))
	{
		glDrawBuffer(GL_BACK); 

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // IN

		glClearDepth(1.0f);
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_pVolumeRenderer->renderScene();

		glFinish();
		SwapBuffers(wglGetCurrentDC());
	}
	busy = FALSE;
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

	Init();

	return 0;
}

int COpenGLView::Init()
{
	PIXELFORMATDESCRIPTOR pfd;
	int		n;
	
	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != NULL);

	if (!bSetupPixelFormat())
		return 0;

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

	CreateRGBPalette(); // DONT KNOW WHAT IAM DOING

    // Createan  OpenGL rendering context
	m_hOpenGLContext = wglCreateContext(m_pDC->GetSafeHdc());
	ASSERT(m_hOpenGLContext != NULL);
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hOpenGLContext);
	glEnable(GL_DEPTH_TEST);

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
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	if( !CView::PreCreateWindow(cs) )
		return FALSE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

BOOL COpenGLView::OnCommand(WPARAM wParam, LPARAM lParam)
{
    switch (LOWORD(wParam))
    {
    case CM_OPENGL_PROPERTIES:
			OnPopupOpenglEigenschaften();
			return TRUE;
    case CM_OPENGL_TOGGLE_BORDER_LINES:
			OnPopupOpenglShowBox();
			return TRUE;
    default:
			return CView::OnCommand(wParam, lParam);
    }
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
	// we're MANUALLY building the context menu here, because static resources 
	// don't allow dynamic menu content (more precisely: I don't know how to do it...)

	CMenu menu;
	menu.CreatePopupMenu();
	CString menuText;

	// first menu entry
	menuText.LoadString(IDS_CONTEXT_MENU_OPENGL_PROPERTIES);
	menu.InsertMenu(0, MF_BYPOSITION, CM_OPENGL_PROPERTIES, menuText);

	// second menu entry (depending on the "isBoundingBoxVisible" function)
	if(m_pVolumeRenderer) {
		if(m_pVolumeRenderer->isBoundingBoxVisible()) {
			menuText.LoadString(IDS_CONTEXT_MENU_OPENGL_DISABLE_BORDER_LINES);
		}
		else {
			menuText.LoadString(IDS_CONTEXT_MENU_OPENGL_ENABLE_BORDER_LINES);
		}
		menu.InsertMenu(1, MF_BYPOSITION, CM_OPENGL_TOGGLE_BORDER_LINES, menuText);
	}

	// build the context menu
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, this);
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

// DONT KNOW WHAT IAM DOING

void COpenGLView::CreateRGBPalette()
{
	PIXELFORMATDESCRIPTOR pfd;
	LOGPALETTE *pPal;
	int n, i;
	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

	if (pfd.dwFlags & PFD_NEED_PALETTE)
	{
		n = 1 << pfd.cColorBits;
		pPal = (PLOGPALETTE) new char[sizeof(LOGPALETTE) + n * sizeof(PALETTEENTRY)];

		ASSERT(pPal != NULL);

		pPal->palVersion = 0x300;
		pPal->palNumEntries = n;
		for (i=0; i<n; i++)
		{
			pPal->palPalEntry[i].peRed =
					ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
			pPal->palPalEntry[i].peGreen =
					ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
			pPal->palPalEntry[i].peBlue =
					ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
			pPal->palPalEntry[i].peFlags = 0;
		}

		/* fix up the palette to include the default GDI palette */
		if ((pfd.cColorBits == 8)                           &&
			(pfd.cRedBits   == 3) && (pfd.cRedShift   == 0) &&
			(pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
			(pfd.cBlueBits  == 2) && (pfd.cBlueShift  == 6)
		   )
		{
			for (i = 1 ; i <= 12 ; i++)
				pPal->palPalEntry[defaultOverride[i]] = defaultPalEntry[i];
		}

		m_cPalette.CreatePalette(pPal);
		delete pPal;

		m_pOldPalette = m_pDC->SelectPalette(&m_cPalette, FALSE);
		m_pDC->RealizePalette();
	}
}

unsigned char COpenGLView::ComponentFromIndex(int i, UINT nbits, UINT shift)
{
	unsigned char val;

	val = (unsigned char) (i >> shift);
	switch (nbits)
	{

	case 1:
		val &= 0x1;
		return oneto8[val];
	case 2:
		val &= 0x3;
		return twoto8[val];
	case 3:
		val &= 0x7;
		return threeto8[val];

	default:
		return 0;
	}
}

// DONT KNOW WHAT IAM DOING

void COpenGLView::OnDestroy() 
{
	HGLRC   hrc;
	hrc = ::wglGetCurrentContext();

	::wglMakeCurrent(NULL,  NULL);

	if (hrc)
		::wglDeleteContext(hrc);

	if (m_pOldPalette)
		m_pDC->SelectPalette(m_pOldPalette, FALSE);

	if (m_pDC)
		delete m_pDC;

	CView::OnDestroy();
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
}

BOOL COpenGLView::bSetupPixelFormat(void)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		  PFD_SUPPORT_OPENGL |          // support OpenGL
		  PFD_DOUBLEBUFFER,             // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 32-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int pixelformat;

	if ( (pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0 )
	{
		MessageBox("ChoosePixelFormat failed");
		return FALSE;
	}

	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		MessageBox("SetPixelFormat failed");
		return FALSE;
	}

	return TRUE;
}

void COpenGLView::OnPopupOpenglEigenschaften() 
{
	// INITIALISATIONS Dlg.Memberfunction/variable
	COpenGLDoc* pDoc = GetDocument();

	int currentResolution = pDoc->getResolution();
	int currentDensity    = pDoc->getDensity();
	int currentShift      = pDoc->getShift();
	int currentWordLen    = pDoc->getWordLen();

	C3DVisOpt Dlg(NULL, currentResolution, currentDensity, currentShift, currentWordLen);

	
	if ( IDOK == Dlg.DoModal() )
	{
		if ((currentResolution != Dlg.resolution) ||
			(currentDensity != Dlg.density) || 
			(currentShift != Dlg.shift) ||
			(currentWordLen != Dlg.wordsize)) {

			// change rendering settings
			pDoc->setResolution(Dlg.resolution);
			pDoc->setDensity(Dlg.density);
			pDoc->setShift(Dlg.shift);
			pDoc->setWordLen(Dlg.wordsize);

			// recompute cube data
			pDoc->createVolumeData();

			if ( pDoc->volume )
				m_pVolumeRenderer->setVolume(pDoc->nResolution, pDoc->dVoxelSize, pDoc->volume->getVolume());

			// redraw
			RECT l_rect;
			this->GetWindowRect(&l_rect);
			m_pVolumeRenderer->setSize(l_rect.right-l_rect.left, l_rect.bottom -l_rect.top, TRUE);

			this->OnDraw(NULL);
	
		}
		
	}
}

void COpenGLView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	if (NULL != m_pVolumeRenderer) {
		m_pVolumeRenderer->OnRButtonDown(nFlags,point);
	}
		
	CView::OnRButtonDown(nFlags, point);
}

void COpenGLView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	if (NULL != m_pVolumeRenderer) {
		m_pVolumeRenderer->OnRButtonUp(nFlags,point);
	}
	
	CView::OnRButtonUp(nFlags, point);
}
