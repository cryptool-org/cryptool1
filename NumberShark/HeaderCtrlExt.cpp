// HeaderCtrlEx1.cpp : implementation file
//

#include "stdafx.h"
//#include "HeaderCtrlEx.h"
#include "HeaderCtrlExt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx

CHeaderCtrlEx::CHeaderCtrlEx()
{
}

CHeaderCtrlEx::~CHeaderCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CHeaderCtrlEx, CHeaderCtrl)
	//{{AFX_MSG_MAP(CHeaderCtrlEx)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx message handlers



void CHeaderCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

   ASSERT(lpDrawItemStruct->CtlType == ODT_HEADER);

   HDITEM hdi;
   TCHAR  lpBuffer[256];

   hdi.mask = HDI_TEXT;
   hdi.pszText = lpBuffer;
   hdi.cchTextMax = 256;

   GetItem(lpDrawItemStruct->itemID, &hdi);

   	
	CDC* pDC;
	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	//THIS FONT IS ONLY FOR DRAWING AS LONG AS WE DON'T DO A SetFont(...)
	pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
   // Draw the button frame.
   ::DrawFrameControl(lpDrawItemStruct->hDC, 
      &lpDrawItemStruct->rcItem, DFC_BUTTON, DFCS_BUTTONPUSH);


	UINT uFormat = DT_CENTER;
	//DRAW THE TEXT
   ::DrawText(lpDrawItemStruct->hDC, lpBuffer, (int)strlen(lpBuffer), 
      &lpDrawItemStruct->rcItem, uFormat);

   pDC->SelectStockObject(SYSTEM_FONT);

}
