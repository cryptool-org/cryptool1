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
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "FileTools.h"
#include "ChrTools.h"
#include "CrypToolApp.h"
#include <sys/stat.h>

#pragma warning(disable : 4996)

int cnt=0;

void GetTmpName( char *dest, const char *prefix, const char *ext )
{
    char *temp;
    FILE *f;

    temp = getenv("TEMP");
    if(!temp)
        temp = getenv("TMP");
    if(!temp)
        temp = ".";

    for(;cnt<10000;) {
		cnt++;
        sprintf(dest,"%s\\%s%d%s",temp,prefix,cnt,ext);
        f = fopen(dest,"r");
        if(!f) return;
        fclose(f);
    }
    dest[0]=0;
}

BOOL IsPrint(const unsigned char c)
{
	if(c < 32) return FALSE;
	if((0x07f <= c) && ( c <= 0x09f)) return FALSE;
	return TRUE;
}

BOOL IsText(const unsigned char c)
{
	if((('a'<=c)&&(c<='z')) || (('A'<=c)&&(c<='Z')) || (('0'<=c)&&(c<='9'))) return TRUE;
	if(c==0) return FALSE;
	// if(strchr(" .:,;-_<>|öÖäÄ#'üÜ+*~^°!\"§$%&/()=?`´ß\\{[]}\032",c)) return TRUE;
	if (strchr(" !\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~__,\"\"o__¤¥§¨©ª«­±²³//´µ·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýþÿ\032", c)) return TRUE;
	return FALSE;
}

BOOL IsHex(const unsigned char c)
{
	if(('0' <= c) && (c <= '9')) return TRUE;
	if(('A' <= c) && (c <= 'F')) return TRUE;
	if(('a' <= c) && (c <= 'f')) return TRUE;
	return FALSE;
}

int HexVal(const unsigned char c)
{
	if(('0' <= c) && (c <= '9')) return c-'0';
	if(('A' <= c) && (c <= 'F')) return c+10-'A';
	if(('a' <= c) && (c <= 'f')) return c+10-'a';
	return -1;
}



int HexDumpMem(char *Dest, int DestSize, unsigned char *Src, int SrcSize, const int len, long start)
{
	char *p;

    int i,j,k, linelen;
	int lines, rest;
	ASSERT(DestSize >= 0 && SrcSize >= 0 && len >= 0 && start >= 0);
	linelen = 11 + len * 4;
	lines = (SrcSize+len-1) / len;
	rest = SrcSize % len;
	k = lines * linelen - len + rest;

	if(k>DestSize) return 0;

	p = Dest;
    for(i=0;i<SrcSize;i+=len) {
        sprintf(p,"%5.05X  ",i+start); // = MAX_ADR_LEN Zeichen
		p += 7;
        for(j=i;j<i+len;j++) {
            if(j<SrcSize) sprintf(p,"%02.2X",Src[j]);
            else p[0] = p[1] = ' ';
			p[2] = ' '; // = HEX_SEP Zeichen
			p += 3;
		}
		p[0] = p[1] = ' '; // = ASC_SEP Zeichen
		p += 2;
        for(j=i;j<i+len;j++)
            if(j<SrcSize) {
                if(IsPrint(Src[j]))
					*p = Src[j];
                else
					*p = '.';
				p++;
            }
			if(j<=SrcSize) { // 2 Zeichen Zeilenende
			p[0] = '\r';
			p[1] = '\n';
			p += 2;
		}
	}
	*p = 0;
    return p - Dest;
}



int HexUndumpMem(const char *inbuff, const int inlen, char *outbuff, int *state)
{
/*	Format of buffer:
		Adress (anything but space)
		1 space
		[1 Space 2 Hex digits]*
		2 Spaces
		rest ignored till \n char is read
		*/
		/* state = 0 scan for leading address 
		   state = 1 scan blank before Hexval
		   state = 2 scan High nibble
		   state = X3 scan low nibble (Highnibble is is X)
		   state = 4 discard ASCII display to end of line
		   state = 5 discard eol
		   return number of hex digits scanned, -1 on error */
	int i,j;
	char c;

	for(i=j=0;i<inlen;i++) {
		c = inbuff[i];
		process:
		switch (*state) {
		case (0): // adress and values are separated by 2 blanks 
			if(c==' ') *state = 1;
			break;
		case (1): // blank before value
			if(c!=' ')
				return -1; // format error 
			*state = 2;
			break;
		case (2): // high nibble
			if(c==' ') {
				*state = 4; // discard rest of line
				break;
			}
			if(!IsHex(c))
					return -2; // format error
			*state = (HexVal(c)<<4)+3;
			break;
		case (4): // discard rest of line
			//if(c=='\r') *state = 0;
			if(c=='\n' || c=='\r') *state = 5;
			break;
		case (5): // discard eol
			if (c!='\n' && c!='\r') {
				*state = 0; 
				goto process;
			}
			break;
		default: // low nibble
			if(!IsHex(c)) 
				return -3; // format error
			outbuff[j]=(*state & 0x0f0) + HexVal(c);
			j++;
			*state = 1;
			break;
		}
	}
	return j;
}

int HexDumpOct(OctetString& Dest, OctetString& Src, const int len, long start)
{

    unsigned i,j;
	int linelen, lines, rest;

	linelen = 11 + len * 4;
	lines = (Src.noctets+len-1) / len;
	rest = Src.noctets % len;
	Dest.noctets = lines * linelen - (rest? len - rest: 0);
	Dest.octets = new char[Dest.noctets+1];

	char* p = Dest.octets;
    for(i=0; i<Src.noctets; i+=len) {
        sprintf(p,"%5.05X  ",i+start); // = MAX_ADR_LEN Zeichen
		p += 7;
        for(j=i;j<i+len;j++) {
            if(j<Src.noctets) sprintf(p,"%02.2X",Src.octets[j]);
            else p[0] = p[1] = ' ';
			p[2] = ' '; // = HEX_SEP Zeichen
			p += 3;
		}
		p[0] = p[1] = ' '; // = ASC_SEP Zeichen
		p += 2;
        for(j=i;j<i+len;j++)
            if(j<Src.noctets) {
                if(IsPrint(Src.octets[j]))
					*p = Src.octets[j];
                else
					*p = '.';
				p++;
            }
			if(j<=Src.noctets) { // 2 Zeichen Zeilenende
			p[0] = '\r';
			p[1] = '\n';
			p += 2;
		}
	}
	*p = 0;
    return p - Dest.octets;
}

int ASCDump(const char *outfile, const char *infile, const int blocklen, const int numblocks, int maxsize)
{
    char buffer[800],c;
    FILE *f1, *f2;
    int l,i,j, maxj;
	int r;

    f1 = fopen(infile,"rt");
    if(!f1) return 0;

    f2 = fopen(outfile,"wt");
    if(!f2) return 0;
	maxj = ((int) maxsize / ((blocklen + 1) * numblocks + 3)) * (blocklen); 
	r = 1;
	j = 0;
    do {
        l = fread(buffer, 1, sizeof(buffer), f1);
        for(i=0;i<l;i++) {
            c = buffer[i];
            if(('a'<=c) && (c<='z')) c += 'A'-'a';
            if(('A'<=c) && (c<='Z')) {
                fprintf(f2,"%c",buffer[i]);
                j++;
                if((j%blocklen) == 0) {
					if((j%(blocklen*numblocks))==0) {
						fputc('\n',f2);
						if(j>= maxj) {
							r = 2;
							break;
						}
					}
	                else fputc(' ',f2);
                }
            }
        }
    } while (l>0);
    fclose(f1);
    fclose(f2);
    return TRUE;
}


int ASCUndumpMem(const char *inbuff, const int inlen, char *outbuff, char SepChar)
{
	int i,j;

	for(i=j=0; i<inlen; i++)
		if((inbuff[i] != SepChar) && (inbuff[i] != '\r') && (inbuff[i] != '\n')) outbuff[j++] = inbuff[i];

	return j;
}

int ASCDumpMem(char *Dest, int DestLen, const char *Src, int SrcLen, int blocklen, const int numblocks, char *SepChar)
{
	int LineLen, NumLines;
    int i,j;
	int rest, restlen;
	const char *SepChars=" -_.~";

	if(*SepChar == 0) {
		*SepChar = ' ';
		for(i=0;i<sizeof(SepChars);i++) {
			if(theApp.TextOptions.getAlphabet().Find(SepChars[i]) == -1) {
				*SepChar = SepChars[i];
				break;
			}
		}
	}

	LineLen = (blocklen+1)*numblocks+1;
	NumLines = (SrcLen-1) / (blocklen*numblocks);
	rest = SrcLen - NumLines * blocklen*numblocks;
	restlen = rest + (rest-1)/blocklen;

	if(NumLines * LineLen +restlen > DestLen) return 0;

	for(i=j=0;i<SrcLen;) {
		Dest[j++] = Src[i++];
//		if(i==SrcLen) break;
		if(i%blocklen == 0) {
			if(i%(blocklen*numblocks) == 0) { // Zeilenende
				Dest[j++]='\r';
				Dest[j++]='\n';
			}
			else { // Blockende
				Dest[j++]= *SepChar;
			}
		}
	}
	return j;
}

int FileCpy(const char *outfile, const char *infile)
{
	FILE *f1,*f2;
	char buffer[4096];
    int i;
	int l1, l2, r;

	if(0 == stricmp(outfile,infile)) return 1; // Dateien identisch
    f1 = fopen(infile,"rb");
    if(!f1) return 0;
	fseek(f1,0,SEEK_END);
	l1 = ftell(f1);
	fseek(f1,0,SEEK_SET);

	f2 = fopen(outfile,"wb");
    if(!f2) return 0;
	l2=l1;

	r = 1;

    do {
        i = fread(buffer, 1, sizeof(buffer), f1);
		i = min(i,l2);
		l2 -= i;
        fwrite(buffer, 1, i, f2);
    } while(i>0);
    fclose(f1);
    fclose(f2);

    return r;
}


BOOL Reformat(const char *reffile, const char *newfile, BOOL FixedAlphabet)
{
	if(!theApp.TextOptions.getKeepCharactersNotPresentInAlphabetUnchanged()) return TRUE;
	else return ForceReformat( reffile, newfile, FixedAlphabet);
}

BOOL ForceReformat(const char *reffile, const char *newfile, BOOL FixedAlphabet)
{
	FILE *fr, *fn;
	int lr, ln, i,p;
	char *bufr, *bufn;

	fr = fopen(reffile,"rb");
	fseek(fr, 0, SEEK_END);
	lr=ftell(fr);
	fseek(fr, 0, SEEK_SET);
	bufr = (char *) malloc(lr);
	fread(bufr, 1, lr, fr);
	fclose(fr);

	fn = fopen(newfile,"rb");
	fseek(fn, 0, SEEK_END);
	ln=ftell(fn);
	fseek(fn, 0, SEEK_SET);
	bufn = (char *) malloc(ln);
	fread(bufn, 1, ln, fn);
	fclose(fn);

	if(FixedAlphabet) { // use standard CPlayfairAlphabet
		for(i=p=0;i<lr;i++) {
			if(MyIsAlpha(bufr[i])) {
				if(MyIsLower(bufr[i]))
					bufr[i] = MyToLower(bufn[p]);
				else
					bufr[i] = bufn[p];
				p++;
				if(p>=ln) break;
			}
		}
	}
	else { // use custom CPlayfairAlphabet
		if(theApp.TextOptions.getKeepUpperLowerCaseInformation()) { // case insensitive
			for(i=p=0;i<lr;i++) {
				if(AppConv.IsInAlphabet(bufr[i])) {
					if(MyIsLower(bufr[i]))
						bufr[i] = MyToLower(bufn[p]);
					else
						bufr[i] = bufn[p];
					p++;
					if(p>=ln) break;
				}
			}
		}
		else { // case sensitive
			for(i=p=0;i<lr;i++) {
				if(AppConv.IsInAlphabet(bufr[i])) {
					bufr[i] = bufn[p];
					p++;
					if(p>=ln) break;
				}
			}
		}
	}

	fn = fopen(newfile,"wb");
	fwrite(bufr, 1, lr, fn);
   if ( p < ln )
      fwrite( &bufn[p], 1, ln -p, fn ); 
	fclose(fn);
	free(bufr);
	free(bufn);

	return TRUE;
} 

int filesize( const char *name )
{
   struct _stat buf;
   int result;

   /* Get data associated with "stat.c": */
   result = _stat( name, &buf );
   /* Check if statistics are valid: */
   if( result != 0 )
      return -1;
   else
	  return buf.st_size;

}

int getFileSize(const char *filename, __int64 &size)
{
	FILE *stream;
	if ( (stream = fopen(filename, "rb")) )
	{
		_fseeki64(stream, (__int64)0, SEEK_END);
		size = _ftelli64(stream);
		fclose(stream);
		return 1;
	}
	size = (__int64)-1;
	return 0;
}

void Add2OString(OctetString*	osTarget, 
				 const char*	Source,
				 const int		Length)
{
	char* Buffer = new char[osTarget->noctets+Length];
	for(unsigned u=0; u<osTarget->noctets; u++) Buffer[u] = osTarget->octets[u];
	for(int i=0; i<Length; i++) Buffer[osTarget->noctets+i] = Source[i];
	delete[] osTarget->octets;
	osTarget->octets = Buffer;
	osTarget->noctets += Length;
}

int readSource(const char* infile, char *&mSrc, int &lSrc, BOOL TEXTMODE )
{
	__int64 m_fileSize;
	if ( !getFileSize(infile, m_fileSize ) )
		return -1; // FIXME: ERROR could not determine file size
	if ( m_fileSize >= (__int64)INT_MAX )
		return -2; // FIXME: ERROR file too large (> 2 GB)
	
	FILE *fstrm;
	if ( fstrm = fopen(infile, "rb") )
	{
		lSrc = (int)m_fileSize;
		mSrc = (char*)malloc( lSrc+1 );
		fread(mSrc, sizeof(char), (size_t)m_fileSize, fstrm );
		mSrc[lSrc] = '\0';
		fclose(fstrm);
	}
	else
		return -3; // FIXME: ...

	if ( TEXTMODE )
	{
		BOOL ignoreCase = theApp.TextOptions.getIgnoreCase();
		int l = lSrc, i;
		
		for(lSrc=i=0; i<l; i++) {
			char c = mSrc[i];
			if(ignoreCase && 'a'<=c && c<='z')
				c += 'A' - 'a';
			if (0 <= theApp.TextOptions.getAlphabet().Find(c))
				mSrc[lSrc++] = c;
		}
		mSrc[lSrc]='\0';
	}

	return 0;
}

int writeDest (const char* pData, int lData, char *&outFileName, BOOL TEXTMODE, const char *refFileName )
{
	char outfile[1024];
	GetTmpName(outfile,"cry",".tmp");

	outFileName = new char[strlen(outfile)+1];
	strcpy(outFileName, outfile);

	FILE *fstrm;
	if ( fstrm = fopen(outFileName, "wb" ) )
	{
		fwrite(pData, sizeof(char), lData, fstrm);
		fclose(fstrm);
	}
	else
	{
		return -1; // FIXME: could not open tmp file
	}
	if ( TEXTMODE ) 
		Reformat(refFileName,outFileName, FALSE);
	return 0;
}