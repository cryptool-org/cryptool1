// TimeCalculation.cpp: Implementierung der Klasse TimeCalculation.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TimeCalculation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

TimeCalculation::TimeCalculation(double Seconds)
{
	if (Seconds < 0)
	{
		m_Years = m_Days = m_Hours = m_Minutes = -1;
		return;
	}

	m_Years = Seconds / _TC_YEARS;
	Seconds -= (m_Years * _TC_YEARS);

	m_Days = Seconds / _TC_DAYS;
	Seconds -= (m_Days * _TC_DAYS);

	m_Hours = Seconds / _TC_HOURS;
	Seconds -= (m_Hours * _TC_HOURS);
	
	m_Minutes = Seconds / _TC_MINUTES;
	Seconds -= (m_Minutes * _TC_MINUTES);

	m_Seconds = Seconds;
}

TimeCalculation::~TimeCalculation()
{
	
}
