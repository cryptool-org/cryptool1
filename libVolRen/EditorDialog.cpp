// EditorDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EditorDialog.h"
#include "VolumeRenderer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditorDialog dialog


CEditorDialog::CEditorDialog(CVolumeRenderer *pVolRen, CWnd* pParent /*=NULL*/)
	: CDialog(CEditorDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditorDialog)
	//}}AFX_DATA_INIT

	ASSERT(pVolRen != NULL);
	m_pVolRen = pVolRen;

	
}


void CEditorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditorDialog)
	DDX_Control(pDX, IDC_GTTRAPEZEDITORCTRL1, m_ctrlTFEditor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditorDialog, CDialog)
	//{{AFX_MSG_MAP(CEditorDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorDialog message handlers

void CEditorDialog::Create()
{
	CDialog::Create(CEditorDialog::IDD);
	
	CDialog::ShowWindow(SW_SHOW);
}

BEGIN_EVENTSINK_MAP(CEditorDialog, CDialog)
    //{{AFX_EVENTSINK_MAP(CEditorDialog)
	ON_EVENT(CEditorDialog, IDC_GTTRAPEZEDITORCTRL1, 1 /* ColorTableChanged */, OnColorTableChanged, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/*void CEditorDialog::OnTransferFunctionChanged(LPUNKNOWN colortable) 
{
	// TODO: Add your control notification handler code here
	m_pVolRen->OnTransferFunctionChanged();
	
}*/

void CEditorDialog::setColorTable256(unsigned char *pColorTable)
{
	m_ctrlTFEditor.SetColortable((LPUNKNOWN) pColorTable);
	m_ctrlTFEditor.SetResolution(256);
}

void CEditorDialog::setHistogram256(float *pHistogram)
{
	m_ctrlTFEditor.SetHistogram((LPUNKNOWN) pHistogram);
	m_ctrlTFEditor.SetHistScale(25.0);
}

void CEditorDialog::OnColorTableChanged() 
{
	m_pVolRen->OnTransferFunctionChanged();
}
