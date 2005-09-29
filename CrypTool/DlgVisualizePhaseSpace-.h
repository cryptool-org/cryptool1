#if !defined(AFX_DLGVISUALIZEPHASESPACE_H__45DEAC0B_B737_4282_B832_F5FB35FB17FD__INCLUDED_)
#define AFX_DLGVISUALIZEPHASESPACE_H__45DEAC0B_B737_4282_B832_F5FB35FB17FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVisualizePhaseSpace.h : Header-Datei
//

// #include "OpenGL.h"
#include "3DRenderBox.h"
#include "StreamToVolume.h"
#include "VolumeRenderer.h"
#include "VolumeUtilities.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgVisualizePhaseSpace 

class CDlgVisualizePhaseSpace : public CDialog
{
	C3DRenderBox *m_pDisplay;

	CVolumeRenderer *m_pVolumeRenderer;
	unsigned char *m_pCharBuffer;

	StreamToVolume* volume;
	
	// Konstruktion
public:
	virtual ~CDlgVisualizePhaseSpace();
	BOOL LoadData();
	CDlgVisualizePhaseSpace(CWnd* pParent = NULL);   // Standardkonstruktor
	char Filename[1024];

// Dialogfelddaten
	//{{AFX_DATA(CDlgVisualizePhaseSpace)
	enum { IDD = IDD_VISUALIZE_PHASE_SPACE };
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente ein
	//}}AFX_DATA

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgVisualizePhaseSpace)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgVisualizePhaseSpace)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGVISUALIZEPHASESPACE_H__45DEAC0B_B737_4282_B832_F5FB35FB17FD__INCLUDED_
