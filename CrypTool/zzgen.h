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


#if !defined(AFX_ZZGEN_H__B511ADE2_6131_11D4_A05B_002035F23D41__INCLUDED_)
#define AFX_ZZGEN_H__B511ADE2_6131_11D4_A05B_002035F23D41__INCLUDED_

#include "HexEdit.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// zzgen.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld zzgen 

class zzgen 
{
// Konstruktion
public:
	//virtual ~zzgen();   // Standardkonstruktor
	char *prim;
	unsigned int primlen;
	int pblen;
	bool isprime(unsigned int,FILE *,unsigned int *);
	unsigned long getrnd(unsigned long);
	unsigned long ggt(unsigned long,unsigned long);
	long jacobi(long,long);
	bool isprimefast (unsigned long);
	bool isprimefast2 (unsigned long);

	unsigned char zzgen1(unsigned long *,unsigned long,int);
	unsigned char zzgen2(unsigned long *,unsigned long,unsigned long,unsigned long);
	unsigned char zzgen3(unsigned long *,unsigned long);
	unsigned char zzgen4();
	unsigned long multmodn(unsigned long,unsigned long,unsigned long);
	unsigned long powermod(unsigned long,unsigned long,unsigned long);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ZZGEN_H__B511ADE2_6131_11D4_A05B_002035F23D41__INCLUDED_
