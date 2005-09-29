// CArcBall.cpp: implementation of the CArcBall class.
//
//////////////////////////////////////////////////////////////////////

#include "ArcBall.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArcBall::CArcBall() :
m_bDragging(false),
m_dRadius(1.0),
m_vec2Center(0.0,0.0),
m_vec2Down(0.0,0.0),
m_vec2Now(0.0,0.0),
m_vec3From(0.0, 0.0, 0.0),
m_vec3To(0.0, 0.0, 0.0),
m_quatDown(0.0, 0.0, 0.0, 1.0),
m_quatDrag(0.0, 0.0, 0.0, 1.0),
m_quatNow(0.0, 0.0, 0.0, 1.0)
{
	
	
}

CArcBall::~CArcBall()
{
	
}

void CArcBall::place(CPosition &vec2Center, double dRadius)
{
	m_vec2Center = vec2Center;
	m_dRadius = dRadius;
}

void CArcBall::setMouse(CPosition &vec2Now)
{
	m_vec2Now = vec2Now;
}


/* Begin drag sequence. */
void CArcBall::startDragging()
{
    m_bDragging = true;
    m_vec2Down   = m_vec2Now;
}


/* Stop drag sequence. */
void CArcBall::finishDragging()
{
    m_bDragging = false;
    m_quatDown  = m_quatNow;
}

/* Return rotation matrix defined by controller use. */
CMatrix CArcBall::getRotatonMatrix() 
{  
	
	m_vec3From = convertMouseToSphere(m_vec2Down);
    m_vec3To   = convertMouseToSphere(m_vec2Now);

    if (m_bDragging) {

		m_quatDrag = getQuaternion(m_vec3From, m_vec3To);
		m_quatNow  = m_quatDrag * m_quatDown;
    } 
	
	return m_quatNow.getMatrix4x4().getTransposed();

}


/* Convert 2D window coordinates to coordinates on the 3D unit sphere. */
CVector CArcBall::convertMouseToSphere(CPosition vec2Mouse)
{
	CPosition vec2UnitMouse = (vec2Mouse - m_vec2Center) / m_dRadius;
    double dDragRadius = vec2UnitMouse * vec2UnitMouse;

    CVector vec3BallMouse(vec2UnitMouse[0], vec2UnitMouse[1], 0.0, 1.0);

    if (dDragRadius > 1.0) {
		// the mouse position was outside the sphere
		// -> map the mouse position to the circle
		vec3BallMouse /= sqrt(dDragRadius);
		vec3BallMouse[2] = 0.0;
    } else {
		// compute the z-value of the unit sphere
		vec3BallMouse[2] = sqrt(1.0 - dDragRadius);
    }
	//vec3BallMouse.normalize();
    return (vec3BallMouse);
}


/* Construct a unit quaternion from two points on unit sphere */
CQuaternion 
CArcBall::getQuaternion(CVector vecFrom, CVector vecTo)
{
	return CQuaternion(
		vecFrom[1] * vecTo[2] - vecFrom[2]*vecTo[1],
		vecFrom[2] * vecTo[0] - vecFrom[0]*vecTo[2],
		vecFrom[0] * vecTo[1] - vecFrom[1]*vecTo[0],
		vecFrom[0] * vecTo[0] + vecFrom[1]*vecTo[1] + vecFrom[2]*vecTo[2]);
}


void CArcBall::reset()
{
	m_bDragging = false;
    m_quatDown.set(0.0, 0.0, 0.0, 1.0);
    m_quatNow.set(0.0, 0.0, 0.0, 1.0);
	m_vec2Now  = m_vec2Center;
	m_vec2Down = m_vec2Center;

}
