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

//////////////////////////////////////////////////////////////////
// C++ class for symmentric encryption/decryption with
// DESL, DESX and DESXL.
//
// Coded 2007 by Markus Diett (markus@diett-it.de)
// Communication Security Group 
// at the Ruhr-University Bochum  (http://www.crypto.rub.de)
//////////////////////////////////////////////////////////////////

#include ".\DESXL.h"

DESXL::DESXL(void)
{
}
DESXL::~DESXL(void)
{
}
void DESXL::PC1(unsigned char *in,unsigned char *out) 
{
	out[0]= BITNUM(in,56,7) | BITNUM(in,48,6) | BITNUM(in,40,5) | BITNUM(in,32,4) | BITNUM(in,24,3) | BITNUM(in,16,2) | BITNUM(in,8,1) | BITNUM(in,0,0); 
	out[1]= BITNUM(in,57,7) | BITNUM(in,49,6) | BITNUM(in,41,5) | BITNUM(in,33,4) | BITNUM(in,25,3) | BITNUM(in,17,2) | BITNUM(in,9,1) | BITNUM(in,1,0); 
	out[2]= BITNUM(in,58,7) | BITNUM(in,50,6) | BITNUM(in,42,5) | BITNUM(in,34,4) | BITNUM(in,26,3) | BITNUM(in,18,2) | BITNUM(in,10,1) | BITNUM(in,2,0); 
	out[3]= BITNUM(in,59,7) | BITNUM(in,51,6) | BITNUM(in,43,5) | BITNUM(in,35,4) | BITNUM(in,62,3) | BITNUM(in,54,2) | BITNUM(in,46,1) | BITNUM(in,38,0); 
	out[4]= BITNUM(in,30,7) | BITNUM(in,22,6) | BITNUM(in,14,5) | BITNUM(in,6,4) | BITNUM(in,61,3) | BITNUM(in,53,2) | BITNUM(in,45,1) | BITNUM(in,37,0); 
	out[5]= BITNUM(in,29,7) | BITNUM(in,21,6) | BITNUM(in,13,5) | BITNUM(in,5,4) | BITNUM(in,60,3) | BITNUM(in,52,2) | BITNUM(in,44,1) | BITNUM(in,36,0); 
	out[6]= BITNUM(in,28,7) | BITNUM(in,20,6) | BITNUM(in,12,5) | BITNUM(in,4,4) | BITNUM(in,27,3) | BITNUM(in,19,2) | BITNUM(in,11,1) | BITNUM(in,3,0); 
}

void DESXL::PC2(unsigned char *in,unsigned char *out) 
{
	out[0]= BITNUM(in,13,7) | BITNUM(in,16,6) | BITNUM(in,10,5) | BITNUM(in,23,4) | BITNUM(in,0,3) | BITNUM(in,4,2) | BITNUM(in,2,1) | BITNUM(in,27,0); 
	out[1]= BITNUM(in,14,7) | BITNUM(in,5,6) | BITNUM(in,20,5) | BITNUM(in,9,4) | BITNUM(in,22,3) | BITNUM(in,18,2) | BITNUM(in,11,1) | BITNUM(in,3,0); 
	out[2]= BITNUM(in,25,7) | BITNUM(in,7,6) | BITNUM(in,15,5) | BITNUM(in,6,4) | BITNUM(in,26,3) | BITNUM(in,19,2) | BITNUM(in,12,1) | BITNUM(in,1,0); 
	out[3]= BITNUM(in,40,7) | BITNUM(in,51,6) | BITNUM(in,30,5) | BITNUM(in,36,4) | BITNUM(in,46,3) | BITNUM(in,54,2) | BITNUM(in,29,1) | BITNUM(in,39,0); 
	out[4]= BITNUM(in,50,7) | BITNUM(in,44,6) | BITNUM(in,32,5) | BITNUM(in,47,4) | BITNUM(in,43,3) | BITNUM(in,48,2) | BITNUM(in,38,1) | BITNUM(in,55,0); 
	out[5]= BITNUM(in,33,7) | BITNUM(in,52,6) | BITNUM(in,45,5) | BITNUM(in,41,4) | BITNUM(in,49,3) | BITNUM(in,35,2) | BITNUM(in,28,1) | BITNUM(in,31,0); 
}


void DESXL::IP(unsigned char *block)
{
  unsigned char tmp[8];
  tmp[0] = BITNUM(block,57,7) | BITNUM(block,49,6) | BITNUM(block,41,5) | BITNUM(block,33,4) | BITNUM(block,25,3) | BITNUM(block,17,2) | BITNUM(block,9,1) | BITNUM(block,1,0); 
  tmp[1] = BITNUM(block,59,7) | BITNUM(block,51,6) | BITNUM(block,43,5) | BITNUM(block,35,4) | BITNUM(block,27,3) | BITNUM(block,19,2) | BITNUM(block,11,1) | BITNUM(block,3,0);
  tmp[2] = BITNUM(block,61,7) | BITNUM(block,53,6) | BITNUM(block,45,5) | BITNUM(block,37,4) | BITNUM(block,29,3) | BITNUM(block,21,2) | BITNUM(block,13,1) | BITNUM(block,5,0);
  tmp[3] = BITNUM(block,63,7) | BITNUM(block,55,6) | BITNUM(block,47,5) | BITNUM(block,39,4) | BITNUM(block,31,3) | BITNUM(block,23,2) | BITNUM(block,15,1) | BITNUM(block,7,0); 
  tmp[4] = BITNUM(block,56,7) | BITNUM(block,48,6) | BITNUM(block,40,5) | BITNUM(block,32,4) | BITNUM(block,24,3) | BITNUM(block,16,2) | BITNUM(block,8,1) | BITNUM(block,0,0);
  tmp[5] = BITNUM(block,58,7) | BITNUM(block,50,6) | BITNUM(block,42,5) | BITNUM(block,34,4) | BITNUM(block,26,3) | BITNUM(block,18,2) | BITNUM(block,10,1) | BITNUM(block,2,0);
  tmp[6] = BITNUM(block,60,7) | BITNUM(block,52,6) | BITNUM(block,44,5) | BITNUM(block,36,4) | BITNUM(block,28,3) | BITNUM(block,20,2) | BITNUM(block,12,1) | BITNUM(block,4,0);
  tmp[7] = BITNUM(block,62,7) | BITNUM(block,54,6) | BITNUM(block,46,5) | BITNUM(block,38,4) | BITNUM(block,30,3) | BITNUM(block,22,2) | BITNUM(block,14,1) | BITNUM(block,6,0);
  block[0]=tmp[0];
  block[1]=tmp[1];
  block[2]=tmp[2];
  block[3]=tmp[3];
  block[4]=tmp[4];
  block[5]=tmp[5];
  block[6]=tmp[6];
  block[7]=tmp[7];
}

void DESXL::invIP(unsigned char *block)
{
  unsigned char tmp[8]; 
  tmp[0] = BITNUM(block,39,7) | BITNUM(block,7,6) | BITNUM(block,47,5) | BITNUM(block,15,4) | BITNUM(block,55,3) | BITNUM(block,23,2) | BITNUM(block,63,1) | BITNUM(block,31,0);
  tmp[1] = BITNUM(block,38,7) | BITNUM(block,6,6) | BITNUM(block,46,5) | BITNUM(block,14,4) | BITNUM(block,54,3) | BITNUM(block,22,2) | BITNUM(block,62,1) | BITNUM(block,30,0);
  tmp[2] = BITNUM(block,37,7) | BITNUM(block,5,6) | BITNUM(block,45,5) | BITNUM(block,13,4) | BITNUM(block,53,3) | BITNUM(block,21,2) | BITNUM(block,61,1) | BITNUM(block,29,0);
  tmp[3] = BITNUM(block,36,7) | BITNUM(block,4,6) | BITNUM(block,44,5) | BITNUM(block,12,4) | BITNUM(block,52,3) | BITNUM(block,20,2) | BITNUM(block,60,1) | BITNUM(block,28,0);
  tmp[4] = BITNUM(block,35,7) | BITNUM(block,3,6) | BITNUM(block,43,5) | BITNUM(block,11,4) | BITNUM(block,51,3) | BITNUM(block,19,2) | BITNUM(block,59,1) | BITNUM(block,27,0);
  tmp[5] = BITNUM(block,34,7) | BITNUM(block,2,6) | BITNUM(block,42,5) | BITNUM(block,10,4) | BITNUM(block,50,3) | BITNUM(block,18,2) | BITNUM(block,58,1) | BITNUM(block,26,0);
  tmp[6] = BITNUM(block,33,7) | BITNUM(block,1,6) | BITNUM(block,41,5) | BITNUM(block,9,4) | BITNUM(block,49,3) | BITNUM(block,17,2) | BITNUM(block,57,1) | BITNUM(block,25,0);
  tmp[7] = BITNUM(block,32,7) | BITNUM(block,0,6) | BITNUM(block,40,5) | BITNUM(block,8,4) | BITNUM(block,48,3) | BITNUM(block,16,2) | BITNUM(block,56,1) | BITNUM(block,24,0);
  block[0]=tmp[0];
  block[1]=tmp[1];
  block[2]=tmp[2];
  block[3]=tmp[3];
  block[4]=tmp[4];
  block[5]=tmp[5];
  block[6]=tmp[6];
  block[7]=tmp[7];
}

void DESXL::cryptBlock(unsigned char *block,char mode,char variant)
{
	register int regl,*regr;
	int *l,*r;
	int *tmpint;
	register int saver;
	int x,keystart,keyfaktor;
	register unsigned char b32[4];
	if ((variant == VAR_DESX)||(variant == VAR_DESXL)) {
		if (mode==ENCRYPT) x=0; else x=1;
		for (int i=0;i<8;i++) block[i]=block[i]^desxkey[x][i];
	}
	if ((variant != VAR_DESL)&&(variant != VAR_DESXL)) IP(block);
	l=(int *)block;
	r=(int *)(block+4);
	saver=*r;
	regr=(int*)b32;
	*regr=*r;
	regl=*l;

	for (int i=1;i<=16;i++) {
        if (mode==ENCRYPT)
		{ 
			keyfaktor=1;keystart=-1;
		}
		else
		{
			keyfaktor=-1;keystart=16;
		}
		
		if ((variant==VAR_DESL)||(variant == VAR_DESXL)) {
			*regr = DESLSBox[0][(((b32[3]&0x01)<<5) | ((b32[0]>>3)&0x1f))  ^  ((roundkey[keyfaktor*i+keystart][0]>>2)&0x3f)]
			    ^DESLSBox[1][(((b32[0]&0x1f)<<1) | ((b32[1]>>7)&0x01))  ^  (((roundkey[keyfaktor*i+keystart][0]&0x03)<<4) | ((roundkey[keyfaktor*i+keystart][1]>>4)&0x0f))]
  			    ^DESLSBox[2][(((b32[0]&0x01)<<5) | ((b32[1]>>3)&0x1f))  ^  (((roundkey[keyfaktor*i+keystart][1]&0x0f)<<2) | ((roundkey[keyfaktor*i+keystart][2]>>6)&0x03))]
  			    ^DESLSBox[3][(((b32[1]&0x1f)<<1) | ((b32[2]>>7)&0x01))  ^  (roundkey[keyfaktor*i+keystart][2]&0x3f)]

			    ^DESLSBox[4][(((b32[1]&0x01)<<5) | ((b32[2]>>3)&0x1f))  ^  ((roundkey[keyfaktor*i+keystart][3]>>2)&0x3f)]
			    ^DESLSBox[5][(((b32[2]&0x1f)<<1) | ((b32[3]>>7)&0x01))  ^  (((roundkey[keyfaktor*i+keystart][3]&0x03)<<4) | ((roundkey[keyfaktor*i+keystart][4]>>4)&0x0f))]
  			    ^DESLSBox[6][(((b32[2]&0x01)<<5) | ((b32[3]>>3)&0x1f))  ^  (((roundkey[keyfaktor*i+keystart][4]&0x0f)<<2) | ((roundkey[keyfaktor*i+keystart][5]>>6)&0x03))]
  			    ^DESLSBox[7][(((b32[3]&0x1f)<<1) | ((b32[0]>>7)&0x01))  ^  (roundkey[keyfaktor*i+keystart][5]&0x3f)];		
		} else {
			*regr = SBox[0][(((b32[3]&0x01)<<5) | ((b32[0]>>3)&0x1f))  ^  ((roundkey[keyfaktor*i+keystart][0]>>2)&0x3f)]
			    ^SBox[1][(((b32[0]&0x1f)<<1) | ((b32[1]>>7)&0x01))  ^  (((roundkey[keyfaktor*i+keystart][0]&0x03)<<4) | ((roundkey[keyfaktor*i+keystart][1]>>4)&0x0f))]
  			    ^SBox[2][(((b32[0]&0x01)<<5) | ((b32[1]>>3)&0x1f))  ^  (((roundkey[keyfaktor*i+keystart][1]&0x0f)<<2) | ((roundkey[keyfaktor*i+keystart][2]>>6)&0x03))]
  			    ^SBox[3][(((b32[1]&0x1f)<<1) | ((b32[2]>>7)&0x01))  ^  (roundkey[keyfaktor*i+keystart][2]&0x3f)]

			    ^SBox[4][(((b32[1]&0x01)<<5) | ((b32[2]>>3)&0x1f))  ^  ((roundkey[keyfaktor*i+keystart][3]>>2)&0x3f)]
			    ^SBox[5][(((b32[2]&0x1f)<<1) | ((b32[3]>>7)&0x01))  ^  (((roundkey[keyfaktor*i+keystart][3]&0x03)<<4) | ((roundkey[keyfaktor*i+keystart][4]>>4)&0x0f))]
  			    ^SBox[6][(((b32[2]&0x01)<<5) | ((b32[3]>>3)&0x1f))  ^  (((roundkey[keyfaktor*i+keystart][4]&0x0f)<<2) | ((roundkey[keyfaktor*i+keystart][5]>>6)&0x03))]
  			    ^SBox[7][(((b32[3]&0x1f)<<1) | ((b32[0]>>7)&0x01))  ^  (roundkey[keyfaktor*i+keystart][5]&0x3f)];

		}
		*regr^=regl;
		regl=saver;
		saver=*regr;
	}
    *regr=regl;
	regl=saver;
    
	tmpint=(int*)block;
	*tmpint=regl;
	tmpint=(int*)(block+4);
	*tmpint=*regr;
	if ((variant != VAR_DESL)&&(variant != VAR_DESXL)) invIP(block);
	if ((variant == VAR_DESX)||(variant == VAR_DESXL)) {
		if (mode==ENCRYPT) x=1; else x=0;
        for (int i=0;i<8;i++) block[i]=block[i]^desxkey[x][i];
	}

}


void DESXL::createKey(char *userinput,int keyLen,char variant)
{
  unsigned char tmp[24];
  for (int i=0;i<=(keyLen-1)/8;i++) {
     if ((userinput[i*2] >= '0') && (userinput[i*2] <= '9')) tmp[i] = (userinput[i*2] - '0') << 4;
		else if ((userinput[i*2] >= 'a') && (userinput[i*2] <= 'f')) tmp[i] = (userinput[i*2] - 'a' + 10) << 4; 
		else if ((userinput[i*2] >= 'A') && (userinput[i*2] <= 'F')) tmp[i] = (userinput[i*2] - 'A' + 10) << 4;
     if ((userinput[i*2+1] >= '0') && (userinput[i*2+1] <= '9')) tmp[i] = tmp[i]|(userinput[i*2+1] - '0');
		else if ((userinput[i*2+1] >= 'a') && (userinput[i*2+1] <= 'f')) tmp[i] =tmp[i]| (userinput[i*2+1] - 'a' + 10); 
		else if ((userinput[i*2+1] >= 'A') && (userinput[i*2+1] <= 'F')) tmp[i] =tmp[i]| (userinput[i*2+1] - 'A' + 10);
     userkey[i]=tmp[i];
  }
  unsigned char redKey[7];
  if ((variant == VAR_DESX)||(variant == VAR_DESXL)) {
    for (int i=0;i<8;i++) desxkey[0][i]=tmp[8+i];
	for (int i=0;i<8;i++) desxkey[1][i]=tmp[16+i];
  }
  PC1(tmp,redKey);
  int c,d;
  c=(redKey[0]<<20)|(redKey[1]<<12)|(redKey[2]<<4)|(redKey[3]>>4);
  d=((redKey[3]&0xf)<<24)|(redKey[4]<<16)|(redKey[5]<<8)|(redKey[6]);
  int x;
  for (int i=1; i<=16; i++) {
	  if ((i==1) || (i==2) ||(i==9) ||(i==16)) {
	    x=(c>>27)&1;
		c=((c<<1)|x)&0xfffffff;
	    x=(d>>27)&1;
		d=((d<<1)|x)&0xfffffff;
	  } else {
	    x=(c>>26)&3;
		c=((c<<2)|x)&0xfffffff;
	    x=(d>>26)&3;
		d=((d<<2)|x)&0xfffffff;
	  }
	  redKey[0]=(c>>20)&0xff;
	  redKey[1]=(c>>12)&0xff;
	  redKey[2]=(c>>4)&0xff;
	  redKey[3]=((c<<4)&0xf0) |((d>>24)&0x0f);
	  redKey[4]=(d>>16)&0xff;
	  redKey[5]=(d>>8)&0xff;
	  redKey[6]=(d)&0xff;
	  PC2(redKey,roundkey[i-1]);
  }
}


void DESXL::encrypt(unsigned char *input, int inputLen, unsigned char *outBuffer,char variant)
{
   	unsigned char b[8];
	int *l,*r,xorl,xorr;
    xorl=0;xorr=0;
	l=(int *)b;
    r=(int *)(b+4);
	for (int i=0;i<(inputLen-1)/8;i+=8) {
	  b[0]=input[i+0];
	  b[1]=input[i+1];
	  b[2]=input[i+2];
	  b[3]=input[i+3];
	  b[4]=input[i+4];
	  b[5]=input[i+5];
	  b[6]=input[i+6];
	  b[7]=input[i+7];
	  *l^=xorl;
	  *r^=xorr;
	  cryptBlock(b,ENCRYPT,variant);      
	  xorl=*l;
	  xorr=*r;
	  outBuffer[i+0]=b[0];
	  outBuffer[i+1]=b[1];
	  outBuffer[i+2]=b[2];
	  outBuffer[i+3]=b[3];
      outBuffer[i+4]=b[4];
	  outBuffer[i+5]=b[5];
	  outBuffer[i+6]=b[6];
	  outBuffer[i+7]=b[7];
	}

}

void DESXL::decrypt(unsigned char *input, int inputLen, unsigned char *outBuffer,char variant)
{
	unsigned char b[8];
	int *l,*r,xorl,xorr,tmpr,tmpl;
    xorl=0;xorr=0;tmpl=0;tmpr=0;
	l=(int *)b;
    r=(int *)(b+4);
	for (int i=0;i<(inputLen-1)/8;i+=8) {
	  b[0]=input[i+0];
	  b[1]=input[i+1];
	  b[2]=input[i+2];
	  b[3]=input[i+3];
	  b[4]=input[i+4];
	  b[5]=input[i+5];
	  b[6]=input[i+6];
	  b[7]=input[i+7];
	  tmpl=*l;
	  tmpr=*r;
	  cryptBlock(b,DECRYPT,variant);
      *l^=xorl;
	  *r^=xorr;
	  xorl=tmpl;
	  xorr=tmpr;
	  outBuffer[i+0]=b[0];
	  outBuffer[i+1]=b[1];
	  outBuffer[i+2]=b[2];
	  outBuffer[i+3]=b[3];
      outBuffer[i+4]=b[4];
	  outBuffer[i+5]=b[5];
	  outBuffer[i+6]=b[6];
	  outBuffer[i+7]=b[7];
	}

}

