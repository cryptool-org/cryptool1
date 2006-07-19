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


#include "stdafx.h"
#include "CrypToolApp.h"
#include "uucode.h"


void uucodeerror(std::string text, char errchar,ssize_t errcode, ssize_t position, int chlb, int lines)
{
	char str[2]; 
	str[0] = errchar; str[1] = '\0';
	CString result="";

	switch(errcode)
	{	
		case -1:
			result.Format(IDS_UU_DECODE_MISSING_BEGIN);
			AfxMessageBox(result, MB_OK);
			break;
		case -2: 
			result.Format(IDS_UU_DECODE_ILLEGAL_CHARACTER, position, str);
			AfxMessageBox(result, MB_OK);
			break;
		case -3:
			result.Format(IDS_UU_DECODE_MISSING_CHAR, chlb,text);
			AfxMessageBox(result, MB_OK);
			break;
		case -4:		
			result.Format(IDS_UU_FILE_WRITE_ERROR,text);
			AfxMessageBox(result, MB_OK);
			break;
		case -5:
			result.Format(IDS_UU_FILE_OPEN_ERROR);
			AfxMessageBox(result, MB_OK);
			break;
		case -6:
			result.Format(IDS_UU_DECODE_LB_DIFFERS_TOSHORT, lines);
			AfxMessageBox(result, MB_OK);
			break;
		case -7:
			result.Format(IDS_UU_DECODE_LB_DIFFERS_TOLONG, lines);
			AfxMessageBox(result, MB_OK);
			break;
		case -8:
			result.Format(IDS_UU_DECODE_MISSING_FN);
			AfxMessageBox(result, MB_OK);
			break;
		case -9:
			result.Format(IDS_UU_DECODE_MISSING_END);
			AfxMessageBox(result, MB_OK);
			break;
		case -10:
			result.Format(IDS_UU_DECODE_MISSING_NL_BEFORE_END);
			AfxMessageBox(result, MB_OK);
			break;
		case -11:
			result.Format(IDS_UU_DECODE_MISSING_NL_AFTER_END);
			AfxMessageBox(result, MB_OK);
			break;
	}
}