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