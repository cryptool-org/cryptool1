// CArcBall.h: interface for the CArcBall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CArcBall_H__INCLUDED_)
#define _CArcBall_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CPosition.h"
#include "CVector.h"
#include "CMatrix.h"
#include "CQuaternion.h"

class CArcBall  
{
public:
	void reset();
	CArcBall();
	virtual ~CArcBall();

	/* Public routines */
	void place(CPosition &vecPos, double dRadius);
	void setMouse(CPosition &vecNow);
	void startDragging();
	void finishDragging();
	CMatrix getRotatonMatrix();
private:
	CVector convertMouseToSphere(CPosition vec2Mouse);
	CQuaternion getQuaternion(CVector vec3From, CVector vec3To);
	
    double        m_dRadius;

    CPosition     m_vec2Center;
    CPosition     m_vec2Now, m_vec2Down;
    CVector       m_vec3To,  m_vec3From;
    CQuaternion   m_quatNow, m_quatDown, m_quatDrag;

    bool m_bDragging;
};

#endif // !defined(_CArcBall_H__INCLUDED_)
