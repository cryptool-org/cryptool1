// CrypToolVolRen.h: Schnittstelle f�r die Klasse CCrypToolVolRen.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTOOLVOLREN_H__988E8BF5_2746_4B47_9D60_8382257946E8__INCLUDED_)
#define AFX_CRYPTOOLVOLREN_H__988E8BF5_2746_4B47_9D60_8382257946E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// class CArcBall;
// class CVolume;

#include "Volume.h"
#include "ArcBall.h"
#include "CVector.h"
#include "CPosition.h"
#include "resource.h"

class CCrypToolVolRen  
{
public:
	CCrypToolVolRen(CView *pParent);
	virtual ~CCrypToolVolRen();

public:

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
	virtual void setSize(int nWidth, int nHeight, BOOL f_Force = FALSE);

	virtual bool OnLButtonDown(UINT nFlags, CPoint point);
	virtual bool OnLButtonUp(UINT nFlags, CPoint point);
	virtual bool OnMouseMove(UINT nFlags, CPoint point);
	virtual bool OnRButtonDown(UINT nFlags, CPoint point);
	virtual bool OnRButtonUp(UINT nFlags, CPoint point);
	void setParent( CWnd *p ) { m_pParent = p; }

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
	CWnd *m_pParent;
	CView *m_pParentV;
};

#endif // !defined(AFX_CRYPTOOLVOLREN_H__988E8BF5_2746_4B47_9D60_8382257946E8__INCLUDED_)
