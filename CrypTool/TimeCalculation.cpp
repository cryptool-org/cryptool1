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

	m_Years  = (__int64)(Seconds / _TC_YEARS);
	Seconds -= (m_Years * _TC_YEARS);

	m_Days   = (int)(Seconds / _TC_DAYS);
	Seconds -= (m_Days * _TC_DAYS);

	m_Hours  = (int)(Seconds / _TC_HOURS);
	Seconds -= (m_Hours * _TC_HOURS);
	
	m_Minutes= (int)Seconds / _TC_MINUTES;
	Seconds -= (m_Minutes * _TC_MINUTES);

	m_Seconds= Seconds;
}

TimeCalculation::~TimeCalculation()
{
	
}
