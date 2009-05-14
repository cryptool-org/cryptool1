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


// SecudeLib.cpp: Implementierung der Klasse CSecudeLib.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "afxdll_.h"
#include "CrypToolApp.h"
#include "SecudeLib.h"
#include "DialogeMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DYNAMICSECUDE
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CSecudeLib::CSecudeLib()
{
	Status = 0;
	OpenSecudeLib();
}

CSecudeLib::~CSecudeLib()
{
	if(Status != 0) CloseSecudeLib();
}

int CSecudeLib::OpenSecudeLib()
{
	int r, errcnt;
	char *line;

	if(Status == 0) {
#ifdef DYNAMICSECUDE

		hDLL = LoadLibrary("SECUDE.DLL");

		if(hDLL == NULL) {
			Message(IDS_SECUDE_COULD_NOT_BE_LOADED, MB_ICONEXCLAMATION);
			// MessageBox(NULL,"SECUDE Lib konnte nicht gefunden werden!","Test", MB_OK);
			Status = 0;
			return Status;
		}
#endif
	// Laden der Funktionen
#undef DoOneFn
#undef SEC_PROTOTYPE_0
#undef SEC_PROTOTYPE_1
#undef SEC_PROTOTYPE_2
#undef SEC_PROTOTYPE_3
#undef SEC_PROTOTYPE_4
#undef SEC_PROTOTYPE_5
#undef SEC_PROTOTYPE_6
#undef SEC_PROTOTYPE_10
#define SEC_PROTOTYPE_0()	"@0"
#define SEC_PROTOTYPE_1(a,b)	"@4"
#define SEC_PROTOTYPE_2(a,b,c,d)	"@8"
#define SEC_PROTOTYPE_3(a,b,c,d,e,f)	"@12"
#define SEC_PROTOTYPE_4(a,b,c,d,e,f,g,h)	"@16"
#define SEC_PROTOTYPE_5(a,b,c,d,e,f,g,h,i,j)	"@20"
#define SEC_PROTOTYPE_6(a,b,c,d,e,f,g,h,i,j,k,l)	"@24"
#define SEC_PROTOTYPE_10(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t)	"@40"
#ifdef DYNAMICSECUDE
#define DoOneFn( a, b, c ,d)	c = (c##_t) GetProcAddress(hDLL,"_"###c##d); if(c==NULL) errcnt++;
#define DoOneData(a, b) b = (a *) GetProcAddress(hDLL, #b); if(b==NULL) errcnt++;
#else
#define DoOneFn(a,b,c,d) c=(c##_t) ::c;
#define DoOneData(a,b) b=(a *) &::b;
#endif
		errcnt = 0;
		DoAll;
#undef DoOneFn
#undef DoOneData

#ifdef DYNAMICSECUDE
		if(errcnt > 0) {
			// MessageBox(NULL,"SECUDE Lib konnte nicht geladen werden!","Test", MB_OK);
			Message(IDS_SECUDE_COULD_NOT_BE_LOADED, MB_ICONEXCLAMATION);
			CloseSecudeLib();
			Status = 0;
			return Status;
		}
#endif
	}

	r = SECUDE_HasValidTicket(&line);
	if(r<0) {
//		MessageBox(NULL,"Es konnte kein gültiges Ticket gefunden werden!","Test", MB_OK);
		Status = 1;
	}
	else {
//		MessageBox(NULL,"SECUDE ordnungsgemäß geladen!","Test", MB_OK);
		Status = 2;
	}
	if((MaxBits=light_version())==0)
		//MaxBits=MAX_ASYM_KEYSIZE; // the Secude definition of MAX_ASYM_KEYSIZE (16384) does not work:
			// in CDlgKeyAsymGeneration::CreateAsymKeys the key generation works, but the generation of 
			// the prototype certificate (af_create_Certificate) fails
			// Workaround: reduce to 8K
		MaxBits=8192;
	return Status;
}

int CSecudeLib::CloseSecudeLib()
{
#ifdef DYNAMICSECUDE
	FreeLibrary(hDLL);
#endif
	hDLL = NULL;
	Status = 0;
	return Status;
}

void CSecudeLib::ErrorMessage( UINT resid, PSE pse_handle)
{
	char *serror = theApp.SecudeLib.aux_sprint_error(pse_handle, NULL, 1);
	aux_free_error();
	CString msg;
	msg.Format(resid, serror);
	if (serror)
		aux_free_String(&serror);
	AfxMessageBox((LPCSTR)msg, MB_ICONSTOP);
}
