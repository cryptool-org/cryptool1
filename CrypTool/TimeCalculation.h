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

// TimeCalculation.h: Schnittstelle für die Klasse TimeCalculation.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMECALCULATION_H__2F8E6511_D9C0_11D6_9DF3_000629718A52__INCLUDED_)
#define AFX_TIMECALCULATION_H__2F8E6511_D9C0_11D6_9DF3_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _TC_MINUTES		60
#define _TC_HOURS		(_TC_MINUTES * 60)
#define _TC_DAYS		(_TC_HOURS * 24)
#define _TC_YEARS		(_TC_DAYS * 365)

class TimeCalculation  
{
public:
	TimeCalculation(double Seconds);
	virtual ~TimeCalculation();
	__int64 GetYears() const	{ return m_Years; }
	int GetDays() const			{ return m_Days; }
	int GetHours() const		{ return m_Hours; }
	int GetMinutes() const		{ return m_Minutes; }
	double GetSeconds() const		{ return m_Seconds; }

private:
	__int64 m_Years;
	int m_Days;
	int m_Hours;
	int m_Minutes;
	double m_Seconds;
};

#endif // !defined(AFX_TIMECALCULATION_H__2F8E6511_D9C0_11D6_9DF3_000629718A52__INCLUDED_)
