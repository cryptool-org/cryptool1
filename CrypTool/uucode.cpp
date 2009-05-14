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

#define STREAM_IN_BLOCKLENGTH_ENC 4500  //Größe des Einlesebuffers beim Enkodieren
#define STREAM_OUT_BLOCKLENGTH_ENC (STREAM_IN_BLOCKLENGTH_ENC*4/3+STREAM_IN_BLOCKLENGTH_ENC/48*1)*2  //Größe des Auslesebuffers beim Enkodieren
#define STREAM_IN_BLOCKLENGTH_DEC 4096   //Größe des Einlesebuffers beim Dekodieren
#define STREAM_OUT_BLOCKLENGTH_DEC STREAM_IN_BLOCKLENGTH_DEC*3/4  //Größe des Auslesebuffers beim Dekodieren




#define HLIB_IN_HLIB 1
#include "uucode.h"

// Der Eingabebuffer ist fest definiert auf 4500 [ Vielfaches von 45(Der Eingabezeilenlänge)].
// Ausgabebuffer entsprechend angepasst.

ssize_t UUEncode(
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
	ssize_t leftChars=0;


	if(state)
	{
		acc=(*state)&0xffffU;
		ai=((*state)>>16)&0x3U;
		ci=((*state)>>18);
	}
	else
	{  
		acc=0;  ai=0;  ci=0; 
	}
	
	do
	{
		int up=0,lbyte=0;
		leftChars=inend-(unsigned char*)in;
		if(leftChars>=45)
		{
			lbyte=45;
			*(out++)=(char)(45+32);
		}
		else
		{	
			lbyte=leftChars;
	//		if(leftChars==0) *(out++)='`';
			if((leftChars!=0))  *(out++)=(char)(leftChars+32);
		}
		
			for(;in<inend && up<45;in++)
			{
				acc<<=8;
				acc|=(u_int32_t)(*in);
				++ai;
				up++;
				if(ai==3)
				{
					ASSERT(out + 4 <= outend);
					if((char)(((acc>>18) & 0x3fU)==0))
					{
						*(out++)='`';
					}
					else{
						*(out++)=(char)(((acc>>18) & 0x3fU)+32);
					}
						if((char)(((acc>>12) & 0x3fU)==0))
					{
						*(out++)='`';
					}
					else
					{
					*(out++)=(char)(((acc>>12) & 0x3fU)+32);
					}
					if((char)(((acc>>6) & 0x3fU)==0))
					{
						*(out++)='`';
					}
					else
					{
						*(out++)=(char)(((acc>>6) & 0x3fU)+32);
					}
					
					if((char)((acc & 0x3fU)==0))
					{
						*(out++)='`';
					}
					else
					{
						*(out++)=(char)((acc & 0x3fU)+32);
					}
					ai=0;
					acc=0U;
				}
		
					if(up==lbyte+ai){ *((char*)(out++))='\n';}
				}				
		leftChars=inend-(unsigned char*)in;
	
	}while(leftChars!=0);


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
				if((char)(((acc>>2) & 0x3fU))==0)
				{
					*(out++)='`';
				}
				else
				{
					*(out++)=(char)(((acc>>2) & 0x3fU)+32);
				}
			    if((char)(((acc<<4) & 0x3fU))==0)
				{
					*(out++)='`';
				}	
				else
				{
					*(out++)=(char)(((acc<<4) & 0x3fU)+32);
				}
				break;
			case 2:
				if((char)(((acc>>10) & 0x3fU))==0)
				{
					*(out++)='`';
				}	
				else
				{
					*(out++)=(char)(((acc>>10) & 0x3fU)+32);
				}
				if((char)(((acc>> 4) & 0x3fU))==0)
				{
					*(out++)='`';
				}	
				else
				{
					*(out++)=(char)(((acc>> 4) & 0x3fU)+32);
				}
				if((char)(((acc<< 2) & 0x3cU))==0)
				{
					*(out++)='`';
				}	
				else
				{
					*(out++)=(char)(((acc<< 2) & 0x3cU)+32);
				}
				break;
		}	
	}


    *outfill = out-(unsigned char*)_out;
	return(UU_CODE_NOERROR);
}

ssize_t UUDecode(
	const char *_in,size_t inlen,char *_out,size_t outlen
	,u_int32_t *state /*=NULL*/,ssize_t *outfill,ssize_t *indec,int *lines)
{
	unsigned char *ib=(unsigned char*)_in;
	unsigned char *ib_end=ib+inlen;
	unsigned char *ob=(unsigned char*)_out;
	unsigned char *ob_end=ob+outlen;
	u_int32_t dec=0xfdU;   /* simulate end char in case inlen=0 */
	u_int32_t acc = state ? ((*state)&0x3ffffU) : 0U;
	int       ai  = state ? ((*state)>>18)& 0x3 : 0;
	int		codecharsleft = state ? ((*state)>>20 &0x7f): 0; // codechars = uuchars
	bool lfexpected= state ? (((*state)>>27)& 0x1) : 0;
	int lbyte=0;
	int zeichen=0;
	int lns=0;

	for(; ib<ib_end; ib++)
	{			
		zeichen++;
		if (codecharsleft==0)
			{
				if(!lfexpected)
				{
					if((*ib)==96) //Wenn '`' gefunden, verarbeiten restlicher Zeichen aus state
					{
						switch(ai)
						{
							case 3:  /* got 3 chars */
								*(ob++)=(unsigned char)((acc>>10) & 0xffU);
								*(ob++)=(unsigned char)((acc>> 2) & 0xffU);
								break;
							case 2:  /* got 2 chars */
								*(ob++)=(unsigned char)((acc>> 4) & 0xffU);
								break;
							case 1: 
								return (UU_DECODE_MISSING_CHAR);
								break; 
								
						}
						
						*indec=(char*)ib-_in;
						*outfill = ((char*)ob-_out);
						return(UU_CODE_NOERROR);
					}	

					else if((*ib)>96U || (*ib)<32U)
					{
						*indec=(char*)ib-_in;
						*outfill = (char*)ob-_out;
						return(UU_DECODE_ILLEGAL_CHARACTER);
					}

					else
					{
						lbyte=((int)(*ib)-32);
						codecharsleft=(lbyte*4+2)/3;					
						lfexpected=1;
					}
				}
				else //lfexpected=1
				{
					switch(ai)
					{
						case 3:  /* got 3 chars */
							*(ob++)=(unsigned char)((acc>>10) & 0xffU);
							*(ob++)=(unsigned char)((acc>> 2) & 0xffU);
							break;
						case 2:  /* got 2 chars */
							*(ob++)=(unsigned char)((acc>> 4) & 0xffU);
							break;
						case 1: 
							return (UU_DECODE_MISSING_CHAR);
							break; 		
					}
					ai=0;
					acc=0;

					if(*ib=='\n')
					{
						lfexpected=0;
						lns++;
						*lines=lns;
					}
					else
					{
						*indec=(char*)ib-_in;
						*outfill = (char*)ob-_out;
						return(UU_DECODE_LB_DIFFERS_TOLONG);
					}
				}
			}
		
			else // codecharsleft>0
			{
				ASSERT(lfexpected);
			//	ASSERT(codecharsleft>0);
				

				if(*ib=='\n')
				{	
					*indec=(char*)ib-_in;
					*outfill = ((char*)ob-_out);
					return(UU_DECODE_LB_DIFFERS_TOSHORT);
				}


				else if((*ib)>96U || (*ib)<32U)  
				{
					*indec=(char*)ib-_in;
					*outfill = (char*)ob-_out;
					return(UU_DECODE_ILLEGAL_CHARACTER);
				}
				else if((*ib)==96)
				{
					dec=0;
				}
				


				else
				{
					dec=((int)(*ib)-32);
				}

				acc=(acc<<6)|dec;
				codecharsleft=codecharsleft-1;
				++ai;
				if(ai==4)  /* got 4 chars */
				{
					*(ob++)=(unsigned char)((acc>>16) & 0xffU);
					*(ob++)=(unsigned char)((acc>> 8) & 0xffU);
					*(ob++)=(unsigned char)( acc      & 0xffU);
					acc=0U;  ai=0;
				}	
		
			}
	}
	
	/* ai==4 not possible here. ai<4 here. */
	
	if(state)
	{
		/* Save carry in state. */
		ASSERT((acc >> 18) == 0);
		ASSERT(0 <= ai && ai <= 3);
		ASSERT(0 <= codecharsleft && codecharsleft < 87);
		*state = (((u_int32_t)lfexpected) << 27) | (((u_int32_t)codecharsleft)<<20) | (((u_int32_t)ai)<<18) 

| acc ;

	}
	*indec=(char*)ib-_in;
	*outfill = ((char*)ob-_out);
	return(UU_CODE_NOERROR);
}


void douuenc(const char *infile, const char *OldTitle)
{
	char outfile[CRYPTOOL_PATH_LENGTH], title[256];
    CAppDocument *NewDoc;

    GetTmpName(outfile,"cry",".tmp");


	char drive[1024],dir[1024], fname[128], ext[128];
	_splitpath( infile, drive, dir, fname, ext);

	strcat(fname, ext);
   
	int lwidth=16; //gewünschte Zeilenlänge/4=lwidth
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
		uucodeerror( outfile,NULL,UU_FILE_OPEN_ERROR,NULL,NULL,NULL);
		return;
	}
	std::fstream fileout(outfile, std::ios_base::out|std::ios_base::binary);
	
	if (!fileout.is_open())
	{
		uucodeerror(outfile,NULL,UU_FILE_OPEN_ERROR,NULL,NULL,NULL);
		return;
	}														

								

	
	CString header = CString("begin 644 ") + CString(fname) + CString("\n");
	fileout.write(header, header.GetLength());	
	do
	{
		
		
		
		filein.read(buffer, STREAM_IN_BLOCKLENGTH_ENC);
		count = filein.gcount();

		rv=UUEncode(buffer,count,ob,STREAM_OUT_BLOCKLENGTH_ENC,&state,lwidth, &outchars);    

		
		if(rv>=0)
		{			
			

			if(outchars)
				lf=(ob[outchars-1]=='\n') ? true : false;
		//	if(outchars==0  && count==0){lf=true;}
			fileout.write(ob,outchars);
			if (!fileout.good())
			{
				uucodeerror(outfile,NULL,UU_FILE_WRITE_ERROR,NULL,NULL,NULL);		
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
	fileout.write("`\nend\n", sizeof("`\nend\n")-1);

	

	filein.close();
	fileout.close();


    NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
    remove(outfile);
    if(NewDoc) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_UUENC_OF,pc_str,STR_LAENGE_STRING_TABLE);
        MakeNewName(title,sizeof(title),pc_str,OldTitle);
        NewDoc->SetTitle(title);
    }

	CView* CView_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive()->GetActiveView();
	((CScintillaView*)CView_hilf)->OnViewFontCourier10();
	
}

void douudec(const char *infile, const char *OldTitle)
{
	char outfile[CRYPTOOL_PATH_LENGTH], title[256];
    CAppDocument *NewDoc;

    GetTmpName(outfile,"cry",".txt");
	ssize_t rv = 0;
	int count;
	char buffer[STREAM_IN_BLOCKLENGTH_DEC];
	char ob[STREAM_OUT_BLOCKLENGTH_DEC];
	unsigned int state=0;
	ssize_t outchars=0;
	ssize_t inchars=0;
	int zeichen=0;
	int ai=0, lines=0,linesold=0;
	int fnameindex=0;
	int cntspace=0;

	CString fname, test;

	std::ifstream filein(infile);
	if (!filein.is_open())
	{
		uucodeerror(infile,NULL,UU_FILE_OPEN_ERROR,NULL,NULL,NULL);
		return;
	}
	
	std::fstream fileout(outfile, std::ios_base::out|std::ios_base::binary);
	if (!fileout.is_open())
	{
		uucodeerror( outfile,buffer[inchars],UU_FILE_OPEN_ERROR,inchars,NULL,NULL);
		return;
	}				
	int offset=0;

	filein.read(buffer,STREAM_IN_BLOCKLENGTH_DEC);
	count = filein.gcount();
	
	if(0!=strncmp(buffer,"begin ",6))
	{
		uucodeerror("",NULL,UU_DECODE_MISSING_BEGIN,NULL, NULL,NULL);
		return;

	}
	else
	{
		while(offset<count && buffer[offset]!='\n' && cntspace<3)
		{	
			
			if(buffer[offset]==' ' && cntspace<3)
			{
				cntspace++;
				fnameindex=offset+1;
			}	
			offset++;
		}
	
		buffer[offset++]='\0';
		fname=buffer+fnameindex;
		
		if(offset==count || fname=="")
		{
			uucodeerror("", NULL,UU_DECODE_MISSING_FN, NULL, NULL,NULL );
			return;
		}

		
	}
	int unprocessed=offset;
	while(count-offset && rv>=0)
	{
		
		rv=UUDecode(buffer+offset,count-offset,ob,STREAM_OUT_BLOCKLENGTH_DEC,&state, &outchars, &inchars, 

&lines);
			linesold=linesold+lines;
			unprocessed=offset+inchars;
			offset=0;
		
			
		if(rv<0)
		{
			uucodeerror( "",buffer[unprocessed],rv,zeichen+unprocessed, ai, linesold);	
			count=0;
		}
		if(outchars>0 && rv!=UU_DECODE_MISSING_CHAR)
		{
			fileout.write(ob,outchars);
			if (!fileout.good())
			{
				uucodeerror(outfile,NULL,UU_FILE_WRITE_ERROR,NULL,NULL, NULL);		
				return;
			}
		}
		
		filein.read(buffer, STREAM_IN_BLOCKLENGTH_DEC);
		count = filein.gcount();
		zeichen=zeichen+unprocessed;
		
	}
	if(rv>=0)
	{
		if(0!=strncmp(buffer+unprocessed+1,"\n",1))
		{
			uucodeerror(outfile, NULL, UU_DECODE_MISSING_NL_BEFORE_END,NULL,NULL, NULL);
		}
		else if(0!=strncmp(buffer+unprocessed+2,"end",3))
		{
			uucodeerror(outfile, NULL, UU_DECODE_MISSING_END,NULL,NULL, NULL);
		}
		else if(0!=strncmp(buffer+unprocessed+5,"\n",1))
		{
			uucodeerror(outfile, NULL, UU_DECODE_MISSING_NL_AFTER_END,NULL,NULL, NULL);
		}

	}
	filein.close();
	fileout.close();
	
    NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
    remove(outfile);
    if(NewDoc) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_UUDEC_OF,pc_str,STR_LAENGE_STRING_TABLE);
        MakeNewName(title,sizeof(title),pc_str,OldTitle);
        NewDoc->SetTitle(title);
    }
	
} 