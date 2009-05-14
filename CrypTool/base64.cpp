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

/*
 * base64.c
 *
 * Implementation of base64 encoding/decoding algorithm. 
 *
 * Copyright (c) 2001--2002 by Wolfgang Wieser (wwieser@gmx.de)
 *
 * This file may be distributed and/or modified under the terms of the 
 * GNU General Public License version 2 as published by the Free Software 
 * Foundation. (See COPYING.GPL for details.)
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

//////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main	//
//////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CryptDoc.h"
#include "FileTools.h"
#include "Cryptography.h"
#include <ios>
#include <string>
#include <iostream>
#include <fstream>
#include "ScintillaDoc.h"
#include "ScintillaView.h"


#define STREAM_IN_BLOCKLENGTH_ENC 4080  //Größe des Einlesebuffers beim Enkodieren
#define STREAM_OUT_BLOCKLENGTH_ENC (STREAM_IN_BLOCKLENGTH_ENC*4/3+STREAM_IN_BLOCKLENGTH_ENC/48*1)  //Größe des Auslesebuffers beim Enkodieren
#define STREAM_IN_BLOCKLENGTH_DEC 4096   //Größe des Einlesebuffers beim Dekodieren
#define STREAM_OUT_BLOCKLENGTH_DEC STREAM_IN_BLOCKLENGTH_DEC*3/4  //Größe des Auslesebuffers beim Dekodieren




#define HLIB_IN_HLIB 1
#include "base64.h"

/* Maps the values in range 0...63 to base64 chars. */
static const unsigned char *_base64_encode=(unsigned char *)
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789+/";

ssize_t Base64Encode(
	const char *_in,size_t inlen,
	char *_out,size_t outlen,
	u_int32_t *state/*=NULL*/,int lwidth/*=0*/,ssize_t *outfill)
{
	unsigned char *in=(unsigned char *)_in;
	unsigned char *out=(unsigned char *)_out;
	unsigned char *inend=in+inlen;
	unsigned char *outend=out+outlen;
	u_int32_t acc;
	int ai,ci;

	if(state)
	{
		acc=(*state)&0xffffU;
		ai=((*state)>>16)&0x3U;
		ci=((*state)>>18);
	}

	else
	{  acc=0;  ai=0;  ci=0;  }
	
			for(;in<inend;in++)
	{
		acc<<=8;
		acc|=(u_int32_t)(*in);
		++ai;
		if(ai==3)
		{
			*(out++)=_base64_encode[(acc>>18) & 0x3fU];
			*(out++)=_base64_encode[(acc>>12) & 0x3fU];
			*(out++)=_base64_encode[(acc>> 6) & 0x3fU];
			*(out++)=_base64_encode[ acc      & 0x3fU];
			ai=0;
			acc=0U;
			if(lwidth)  if((++ci)==lwidth)
			{
				*((char*)(out++))='\n';
				ci=0;
			}
		}
	}

	if(state && inlen)
	{
		/* save carry in state (ai=0,1,2) */
		*state = 
			(((u_int32_t)ci)<<18) | 
			(((u_int32_t)ai)<<16) | 
			acc;
	}
	else
	{
			if(state)  *state=0;
	
		/* store rest of input in output */
		/* ai==3 never possible here.*/
		switch(ai)
		{
			case 0:
				break; //Wenn case 0 dann encoding vollständig.
			case 1:
				*(out++)=_base64_encode[(acc>>2) & 0x3fU];
				*(out++)=_base64_encode[(acc<<4) & 0x3fU];
				*((char*)(out++))='=';
				*((char*)(out++))='=';
				break;
			case 2:
				*(out++)=_base64_encode[(acc>>10) & 0x3fU];
				*(out++)=_base64_encode[(acc>> 4) & 0x3fU];
				*(out++)=_base64_encode[(acc<< 2) & 0x3fU];
				*((char*)(out++))='=';
				break;
		}	
	}
    *outfill = out-(unsigned char*)_out;
	return(B64_CODE_NOERROR);
}

static const unsigned char *_base64_decode=(const unsigned char *)
	"\xff\xff\xff\xff\xff\xff\xff\xff\xfe\xfe\xfe\xfe\xfe\xfe\xff\xff"
	"\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
	"\xfe\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x3e\xff\xff\xff\x3f"
	"\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\xff\xff\xff\xfd\xff\xff"
	"\xff\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e"
	"\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\xff\xfe\xff\xff\xff"
	"\xff\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28"
	"\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\xff\xff\xff\xff\xfe";

ssize_t Base64Decode(
	const char *_in,size_t inlen,char *_out,size_t outlen
	,u_int32_t *state /*=NULL*/,ssize_t *outfill,ssize_t *indec, BOOL lastBlock,int *chlb)
{
	unsigned char *ib=(unsigned char*)_in;
	unsigned char *ib_end=ib+inlen;
	unsigned char *ob=(unsigned char*)_out;
	unsigned char *ob_end=ob+outlen;
	u_int32_t dec=0xfdU;   /* simulate end char in case inlen=0 */
	u_int32_t acc = state ? ((*state)&0xffffffU) : 0U;
	int       ai  = state ? ((*state)>>24) : 0;
	unsigned int zeichen=0;
	//CString result="";
	int count=0; //Zähler für Anzahl der "=".
	BOOL illegal_eq = FALSE;


	for(; ib<ib_end; ib++)
	{		
		zeichen++;

		if((*ib)>=128U)  
		{
			*indec=(char*)ib-_in;
			*outfill = (char*)ob-_out;
			return(B64_DECODE_ILLEGAL_CHARACTER);
		}
		dec=_base64_decode[(int)(*ib)];
		if(dec<64 || dec==253)
		{
			if(dec==253) //Behandlung der "=" am Ende
			{
				dec=0;	//dec wird auf Null gesetzt, da beim Codieren die "=" aus (eigentlich nicht vorhandenen) 0-Bit Blöcken entstanden sind
				count++; 
			}
			if (illegal_eq)
			{
				*indec=(char*)ib-_in;
				*outfill = (char*)ob-_out;
				return(B64_DECODE_ILLEGAL_CHARACTER);				
			}
			
			acc=(acc<<6)|dec;
			++ai;
			if(ai==4)  /* got 4 chars */
			{
				*(ob++)=(unsigned char)((acc>>16) & 0xffU);
				*(ob++)=(unsigned char)((acc>> 8) & 0xffU);
				*(ob++)=(unsigned char)( acc      & 0xffU);
				acc=0U;  ai=0;
			}
			*chlb=ai;
		}
		else switch(dec)
		{
			case 0xffU:  
					*indec=(char*)ib-_in;
					*outfill = ((char*)ob-_out)-count;
					return(B64_DECODE_ILLEGAL_CHARACTER);
					break;
			case 0xfdU:
					*indec=(char*)ib-_in;
					//ai=ai+1;
					if (!lastBlock)
					{
						*outfill = ((char*)ob-_out)-count;
						return(B64_DECODE_PREMATURE_END);
					}
					else
						illegal_eq = TRUE;
					break;
					
		}
		
	}
	
	// TO DO: Ignorieren von überflüssigen "=" Zeichen, also mehr als zwei.
	/* ai==4 not possible here. ai<4 here. */
	
	if(state && dec!=0xfdU)  /* state and no end char */
	{
		/* Save carry in state. */
		*state = (((u_int32_t)ai)<<24) | acc;
	}
	else
	{
		if(state)  *state=0U;
		/* Save the last bytes in the output buffer. */

		switch(ai)
		{
			case 3:  /* got 3 chars */
				if ( acc & 0x03 ) return (B64_DECODE_MISSING_CHAR); 
				*(ob++)=(unsigned char)((acc>>10) & 0xffU);
				*(ob++)=(unsigned char)((acc>> 2) & 0xffU);
				*outfill = ((char*)ob-_out)-count;
				return (B64_DECODE_MISSING_CHAR);
				break;
			case 2:  /* got 2 chars */
				if ( acc & 0x0f ) return (B64_DECODE_MISSING_CHAR);
				*(ob++)=(unsigned char)((acc>> 4) & 0xffU);
				*outfill = ((char*)ob-_out)-count;
				return (B64_DECODE_MISSING_CHAR);
				break;
			case 1: 
				return (B64_DECODE_MISSING_CHAR);
				break; 
				
			}
		}
	*outfill = ((char*)ob-_out)-count; //Die beim Codieren angefügten "==" müssen als Zeichen wieder entfernt werden.-> -count.
	return(B64_CODE_NOERROR);
}


void dobase64enc(const char *infile, const char *OldTitle)
{
	char outfile[CRYPTOOL_PATH_LENGTH], title[256];
    CAppDocument *NewDoc;

    GetTmpName(outfile,"cry",".tmp");

	int lwidth=16; //(gewünschte Zeilenlänge/4)=lwidth
	ssize_t rv;
	int count;
	char buffer[STREAM_IN_BLOCKLENGTH_ENC];
	char ob[STREAM_OUT_BLOCKLENGTH_ENC];
	unsigned int state=0;
	ssize_t outchars=0;
	bool lf= false;

	std::fstream filein(infile, std::ios_base::in|std::ios_base::binary);
	if (!filein.is_open())
	{
		base64error( outfile,NULL,B64_FILE_OPEN_ERROR,NULL,NULL);
		return;
	}
	std::fstream fileout(outfile, std::ios_base::out|std::ios_base::binary);
	
	if (!fileout.is_open())
	{
		base64error(outfile,NULL,B64_FILE_OPEN_ERROR,NULL,NULL);
		return;
	}																						

	do
	{
		filein.read(buffer, STREAM_IN_BLOCKLENGTH_ENC);
		count = filein.gcount();
		rv=Base64Encode(buffer,count,ob,STREAM_OUT_BLOCKLENGTH_ENC,&state,lwidth, &outchars);    
			
		if(rv>=0)
		{			
		
			if(outchars)
				lf=(ob[outchars-1]=='\n') ? true : false;

			fileout.write(ob,outchars);
			if (!fileout.good())
			{
				base64error(outfile,NULL,B64_FILE_WRITE_ERROR,NULL,NULL);		
				return;
			}
		}		
	}
	while (count);

	if (lf==false)
	{
		ob[0]='\n';
		fileout.write(ob,1);
	}

	filein.close();
	fileout.close();


    NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
    remove(outfile);
    if(NewDoc) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_BASE64ENC_OF,pc_str,STR_LAENGE_STRING_TABLE);
        MakeNewName(title,sizeof(title),pc_str,OldTitle);
        NewDoc->SetTitle(title);

		CView* CView_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive()->GetActiveView();
		((CScintillaView*)CView_hilf)->OnViewFontCourier10();
    }

}

void dobase64dec(const char *infile, const char *OldTitle)
{
	char outfile[CRYPTOOL_PATH_LENGTH], title[256];
    CAppDocument *NewDoc;

    GetTmpName(outfile,"cry",".txt");
	ssize_t rv;
	int count;
	char buffer[STREAM_IN_BLOCKLENGTH_DEC];
	char ob[STREAM_OUT_BLOCKLENGTH_DEC];
	unsigned int state=0;
	ssize_t outchars=0;
	ssize_t inchars=0;
	int zeichen=0;
	int ai=0;

	std::fstream filein(infile, std::ios_base::in|std::ios_base::binary);
	if (!filein.is_open())
	{
		base64error(infile,NULL,B64_FILE_OPEN_ERROR,NULL,NULL);
		return;
	}
	
	std::fstream fileout(outfile, std::ios_base::out|std::ios_base::binary);
	if (!fileout.is_open())
	{
		base64error( outfile,buffer[inchars],B64_FILE_OPEN_ERROR,inchars,NULL);
		return;
	}																							

	do
	{
		filein.read(buffer, STREAM_IN_BLOCKLENGTH_DEC);
		count = filein.gcount();
	
		rv=Base64Decode(buffer,count,ob,STREAM_OUT_BLOCKLENGTH_DEC,&state, &outchars, &inchars, filein.eof(),&ai);
			
		if(rv<0)
		{
			base64error( "",buffer[inchars],rv,inchars+zeichen, ai);	
			count=0;
		}
		if(outchars>0 && rv!=B64_DECODE_MISSING_CHAR)
		{
			fileout.write(ob,outchars);
			if (!fileout.good())
			{
				base64error(outfile,NULL,B64_FILE_WRITE_ERROR,NULL,NULL);		
				return;
			}
		}
		zeichen=zeichen+4096;
	}
	while (count);

	filein.close();
	fileout.close();
	
    NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
    remove(outfile);
    if(NewDoc) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_BASE64DEC_OF,pc_str,STR_LAENGE_STRING_TABLE);
        MakeNewName(title,sizeof(title),pc_str,OldTitle);
        NewDoc->SetTitle(title);
    }
	
} 