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


#include "stdafx.h"
#include "CrypToolApp.h"
#include "base64.h"


void base64error(std::string text, char errchar,ssize_t errcode, ssize_t position)
{
	char str[2]; 
	str[0] = errchar; str[1] = '\0';
	CString result="";

	switch(errcode)
	{	
		case -1:
			result.Format(IDS_BASE64_DECODE_PREMATURE_END, position, str);
			AfxMessageBox(result, MB_OK);
			break;
		case -2: 
			result.Format(IDS_BASE64_DECODE_ILLEGAL_CHARACTER, position, str);
			AfxMessageBox(result, MB_OK);
			break;
		case -3:
			result.Format(IDS_BASE64_DECODE_MISSING_CHARS,text);
			AfxMessageBox(result, MB_OK);
			break;
		case -4:		
			result.Format(IDS_BASE64_FILE_WRITE_ERROR,text);
			AfxMessageBox(result, MB_OK);
			break;
		case -5:
			result.Format(IDS_BASE64_FILE_OPEN_ERROR,text);
			AfxMessageBox(result, MB_OK);
			break;
	}
}