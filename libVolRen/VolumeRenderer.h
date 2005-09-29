// VolumeRenderer.h: interface for the CVolumeRenderer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOLUMERENDERER_H__5A2FCA7C_3F4C_4ADB_8770_8753E4109858__INCLUDED_)
#define AFX_VOLUMERENDERER_H__5A2FCA7C_3F4C_4ADB_8770_8753E4109858__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CArcBall;
class CVolume;

#include "CVector.h"
#include "CPosition.h"
#include "resource.h"
#include "EditorDialog.h"

#ifdef VOLREN_EXPORTS
#define VOLREN_API __declspec(dllexport)
#else
#define VOLREN_API __declspec(dllimport)
#endif

class VOLREN_API CVolumeRenderer  
{
public:
	CVolumeRenderer(CWnd *pParent);
	virtual ~CVolumeRenderer();

	void setVolume(int nResolution[3], double dVoxelSize[3], unsigned char *pBuffer);
	void OnTransferFunctionChanged();
	void showVolumeEditor();
	void displayBoundingBox(bool on);
	bool isBoundingBoxVisible();
	void setSampling(double d);
	double getSampling();

	virtual void renderScene();
	virtual void viewAll();
	virtual void setOrigin(int nX, int nY);
	virtual void setSize(int nWidth, int nHeight);

	virtual bool OnLButtonDown(UINT nFlags, CPoint point);
	virtual bool OnLButtonUp(UINT nFlags, CPoint point);
	virtual bool OnMouseMove(UINT nFlags, CPoint point);
	virtual bool OnRButtonDown(UINT nFlags, CPoint point);
	virtual bool OnRButtonUp(UINT nFlags, CPoint point);

protected:

	void init();
	CArcBall *m_pArcBall;
	double m_dFieldOfView;
	
	CVector m_vecCameraPosition;
	CPosition m_vecMouseDown;

	bool m_bDragging;
	bool m_bZooming;
	double m_dZoom;
	double m_dTranslateX, m_dTranslateY;
	double  m_dCenter, m_dRadius;

	int m_nPosX, m_nPosY;
	int m_nWidth, m_nHeight;

	bool   m_bInitialized;
	double m_dAspectRatio;

	CVolume *m_pVolume;
	double  m_dVolumeDimension[3];
	CEditorDialog *m_pEditor;
	CWnd *m_pParent;
};

#endif // !defined(AFX_VOLUMERENDERER_H__5A2FCA7C_3F4C_4ADB_8770_8753E4109858__INCLUDED_)
