/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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
