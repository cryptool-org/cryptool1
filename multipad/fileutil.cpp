//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "fileutil.h"
#include "multipad.h"

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
	if(strchr(" .:,;-_<>|����#'��+*~^�!\"�$%&/()=?`��\\{[]}\032",c)) return TRUE;
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



int HexDumpMem(char *Dest, int DestSize, unsigned char *Src, int SrcSize, const int len)
{
	char *p;

    int i,j,k, linelen;
	int lines, rest;

	linelen = 11 + len * 4;
	lines = (SrcSize+len-1) / len;
	rest = SrcSize % len;
	k = lines * linelen - len + rest;

	if(k>DestSize) return 0;

	p = Dest;
    for(i=0;i<SrcSize;i+=len) {
        sprintf(p,"%5.05X  ",i);
		p += 7;
        for(j=i;j<i+len;j++) {
            if(j<SrcSize) sprintf(p,"%02.2X",Src[j]);
            else p[0] = p[1] = ' ';
			p[2] = ' ';
			p += 3;
		}
		p[0] = p[1] = ' ';
		p += 2;
        for(j=i;j<i+len;j++)
            if(j<SrcSize) {
                if(IsPrint(Src[j]))
					*p = Src[j];
                else
					*p = '.';
				p++;
            }
		if(j<SrcSize) {
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
		   return number of hex digits scanned, -1 on error */
	int i,j;
	char c;

	for(i=j=0;i<inlen;i++) {
		c = inbuff[i];
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
			if(c=='\n') *state = 0;
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
			if(theApp.TextOptions.m_alphabet.Find(SepChars[i]) == -1) {
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
		if(i==SrcLen) break;
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

int FileCpy(const char *outfile, const char *infile, int maxsize)
{
    FILE *f1,*f2;
    char buffer[1024];
    int i;
	int l1, l2, r;

	if(0 == stricmp(outfile,infile)) return 1; // Dateien identisch
    f1 = fopen(infile,"rb");
    if(!f1) return 0;
	fseek(f1,0,SEEK_END);
	l1 = ftell(f1);
	fseek(f1,0,SEEK_SET);

	if((maxsize > 0) && (l1 > maxsize)) {
		r=2;
		l1=maxsize;
	}
	else {
		r=1;
	}

    f2 = fopen(outfile,"wb");
    if(!f2) return 0;
	l2=l1;

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
	if(!theApp.TextOptions.m_Format) return TRUE;
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

	if(FixedAlphabet) { // use standard alphabet
		for(i=p=0;i<lr;i++) {
			if(isalpha(bufr[i])) {
				if(islower(bufr[i]))
					bufr[i] = tolower(bufn[p]);
				else
					bufr[i] = bufn[p];
				p++;
				if(p>=ln) break;
			}
		}
	}
	else { // use custom alphabet
		if(theApp.TextOptions.m_ConvertCase) { // case insensitive
			for(i=p=0;i<lr;i++) {
				if(AppConv.IsInAlphabet(bufr[i])) {
					if(islower(bufr[i]))
						bufr[i] = tolower(bufn[p]);
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
	fclose(fn);
	free(bufr);
	free(bufn);

	return TRUE;
} 

int filesize( const char *name )
{
	FILE *f;
	int l;

	f = fopen(name,"rb");
	if(!f) return 0;

	fseek(f, 0, SEEK_END);
	l = ftell(f);
	fclose(f);
	return l;
}