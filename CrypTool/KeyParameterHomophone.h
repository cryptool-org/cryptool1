/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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


// TextAnalyse.h: Schnittstelle f�r die Klasse TextAnalyse.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTANALYSE_H__83C7F3B3_0C82_11D5_8102_000629C93170__INCLUDED_)
#define AFX_TEXTANALYSE_H__83C7F3B3_0C82_11D5_8102_000629C93170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define range		256
#define buffsize	4096

class CKeyParameterHomophone  
{
public:
	void Analyse( const char * f_toAnalyse );
	double freq[range];
	long count[range];
	void Analyse();
	CKeyParameterHomophone();
	virtual ~CKeyParameterHomophone();

private:
	bool Checksum();
	void Correct_count_table();
	void Make_freq_table();
	long total_count;
	void Init();
};

#endif // !defined(AFX_TEXTANALYSE_H__83C7F3B3_0C82_11D5_8102_000629C93170__INCLUDED_)
