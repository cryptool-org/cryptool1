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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#include "CryptDocTemplate.h"
#include "FileTools.h"
#include "ChrTools.h"

CCryptDocTemplate::CCryptDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass)
		: CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass)
{
}


CDocTemplate::Confidence CCryptDocTemplate::MatchDocType(LPCTSTR lpszPathName,
	CDocument*& rpDocMatch)
{
	/* ok = 0 noAttempt
	        1 maybeAttemptForeign,
			2 maybeAttemptNative,
			3 yesAttemptForeign,
			4 yesAttemptNative,
			5 yesAlreadyOpen
	*/
	Confidence conf = noAttempt;

	ASSERT(lpszPathName != NULL);

	// see what the original routine finds ...

	conf = CDocTemplate::MatchDocType(lpszPathName, rpDocMatch);

	if((conf==yesAlreadyOpen)||(conf==yesAttemptNative)) return conf;

	// otherwise we will try to identify the content

	CString strType;
	// get the file type and return if none available
	if (!GetDocString(strType, CDocTemplate::regFileTypeName) || strType.IsEmpty())
		return maybeAttemptForeign;
	if(strType=="HEX File Type") 
		return maybeAttemptForeign;

	if(strType=="Plot File Type") 
		return noAttempt;


	// read file

	FILE *fi;
	unsigned char buffer[4096];
	signed char c;
	int l,i;
	int ok;

	fi = fopen(lpszPathName, "rb");
	if(!fi) return maybeAttemptForeign;
	int curlinelen=0;

	if(strType=="TEXT File Type") {
		ok=2;
		do {
	      l = fread(buffer, 1, sizeof(buffer), fi);
		    for(i=0;i<l;i++) {
				if(curlinelen++ > 256) {
					ok=min(ok,1);
				}
				c=buffer[i];
				if(c=='\n')	curlinelen=0;
				if((c==9) || (c==13) || (c==10) || (c<0)) continue;
				if(IsText(c)) continue;
				ok=0;
				break;
			}
			if(!ok) break;
		} while (l>0);
	}

	if(strType=="ASCII File Type") {
		ok = 3;
		do {
	      l = fread(buffer, 1, sizeof(buffer), fi);
		    for(i=0;i<l;i++) {
				if(MyIsLower(buffer[i])) ok=min(ok,2);
				if(MyIsAlpha((unsigned char)buffer[i])) continue;
				ok=0;
				break;
			}
			if(!ok) break;
		} while (l>0);
	}

	if(strType=="OpenGL File Type") {
		ok = 4;
		l = fread(buffer, 1, 6, fi);
		if (strncmp((char*)buffer, "OPENGL",5)) ok = 0;
	}

	fclose(fi);
	switch(ok) {
	case(1): return maybeAttemptForeign;
	case(2): return maybeAttemptNative;
	case(3): return yesAttemptForeign;
	case(4): return yesAttemptNative;
	}

	return noAttempt;
}

CCryptDocTemplate::~CCryptDocTemplate()
{
}

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

IMPLEMENT_DYNAMIC(CCryptDocTemplate, CMultiDocTemplate) 