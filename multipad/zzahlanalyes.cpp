// Implementierung des Dreieckeverfahrens um
// die Qualit�t von Zufallszahlen zu testen

#include "stdafx.h"
#include "commdlg.h"
#include "multipad.h"
#include "fileutil.h"
#include "crypt.h"
#include <iostream.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zzahlanalyse.h"

double zzahlanalyse::CalcTriangle(unsigned long ax,unsigned long ay,unsigned long bx,unsigned long by,unsigned long cx,unsigned long cy)
{
	double i,j,k,l,m,n;

	i=(double)bx-(double)ax;
	j=(double)by+(double)ay;
	k=(double)cx-(double)bx;
	l=(double)by+(double)cy;
	m=(double)cx-(double)ax;
	n=(double)cy+(double)ay;

	return fabs((i*j)+(k*l)-(m*n));
}

bool zzahlanalyse::AnalyzeIt(void)
{
	int i,j,k,l,p,step,ldl;
	double min;
	unsigned long *ld;

	min=(unsigned long)0xffffffff;
	min=min*min;

	if (isValid==V_MEAN||isValid==V_VARI||isValid==V_RESULT)
		return true;

	LoadString(AfxGetInstanceHandle(),IDS_STRING61407,pc_str,STR_LAENGE_STRING_TABLE);
	theApp.fs.Set(0,pc_str);

	p=0;
	step=datalen/256;
	ldl=datalen/4;
	ld=(unsigned long *)data;

	for (i=4,l=0;i<ldl;i+=2,l++)
	{
		if (p<=0)
		{
			if(theApp.fs.m_canceled) {
				theApp.fs.cancel();
				return false;
			}
			theApp.fs.Set((i*i*100)/(ldl*ldl));
			p=step;
		}
		else
			p--;
		for (j=2;j<i;j+=2)
		{
			for (k=0;k<j;k+=2)
			{
				double t;
				t=CalcTriangle(ld[i],ld[i+1],ld[j],ld[j+1],ld[k],ld[k+1]);
				if (t < min)
					min=t;
				if (min < 0.0001 )
					ldl=i;
			}
		}
		result[l]=min*i*i*i/(unsigned long)0xffffffff/(unsigned long)0xffffffff*0.5;
	}
	datalen=ldl*4;
	resultlen=l;
	isValid=V_RESULT;
	theApp.fs.cancel();
	return true;
}

double zzahlanalyse::GetMean()
{
	int i;
	double m;

	if (isValid==V_MEAN||isValid==V_VARI)
		return mean;
	else
		AnalyzeIt();

	for (i=resultlen/10,m=0.;i<resultlen;i++)
		m+=result[i];
	
	isValid=V_MEAN;

	return mean=m/(resultlen*0.9);
}

double zzahlanalyse::GetVariation()
{
	int i;
	double v,t;

	if (isValid==V_VARI)
		return vari;
	else
		GetMean();

	v=0;
	for (i=resultlen/10,v=0.;i<resultlen;i++)
	{
		t=result[i]-mean;
		v+=(t*t);
	}
	
	isValid=V_VARI;

	return vari=sqrt(v/(resultlen*0.9));
}

void zzahlanalyse::WriteAnalyse(char *name,const char *titel)
{
	char name2[128],line[128];
	FILE *fo;
	int i;
	double var,mea;
	CFile f;

	if(!AnalyzeIt())
		return;
	mea=GetMean();
	var=GetVariation();
	GetTmpName(name,"cry",".plt");
	fo = fopen(name,"wt");
	
	for(i=resultlen/10;i<resultlen;i++)
		fprintf(fo,"%lf\n",(result[i]/mea));
	fclose(fo);

	strcpy(name2, name);
	name2[strlen(name)-4] = 0x0;
	
	if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) )
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING61416,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,mea,var/mea);
		CArchive ar( &f, CArchive::store);
		CString s1 = line;
		LoadString(AfxGetInstanceHandle(),IDS_STRING61418,pc_str,STR_LAENGE_STRING_TABLE);
		CString s2 = pc_str;
		LoadString(AfxGetInstanceHandle(),IDS_STRING61417,pc_str,STR_LAENGE_STRING_TABLE);
		CString s3 = pc_str;
		
		ar << s1 << s2 << s3;
		
		// CONTINUOUS  X_CHAR  Y_CHAR
		ar << (int)1 << '0' << '0';
		
		ar.Close(); f.Close();
		
	}
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING61405,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName(line,sizeof(line),pc_str,titel);

	theApp.ThreadOpenDocumentFileNoMRU(name,line);
}

void zzahlanalyse::SetData(int len,char *d)
{
	origlen=len;
	len=(len>8192) ? 8192 : len;
	datalen=(len-1)&(~7);
	data=(char *)malloc(origlen);
	memcpy(data,d,len);
	resultlen=(datalen/4)-2;
    if ( resultlen < 1 ) 
		resultlen = 1;
	result=(double *)malloc(resultlen*sizeof(double));
	isValid=V_NONE;
}


zzahlanalyse::zzahlanalyse(int len, char *d)
{
	SetData(len,d);
}

zzahlanalyse::zzahlanalyse(char *infile)
{
	int len;
	char *d;
	FILE *fp;

	len=filesize(infile);
	if(fp=fopen(infile,"rb"))
	{
		d=(char *)malloc(len);
		fread(d,1,len,fp);
		fclose(fp);
		SetData(len,d);
		free(d);
	}
}

zzahlanalyse::~zzahlanalyse()
{
	free(data);
	free(result);
}


int zzahlanalyse::FindPeriod()
{
	int i,j,len,s,p;

	if (origlen<4)
		return -1; // return;
	// LoadString(AfxGetInstanceHandle(),IDS_STRING61434,pc_str,STR_LAENGE_STRING_TABLE);
	// theApp.fs.Set(0,pc_str);
	p=0;
	for (s=0;s<origlen;s++)
	{
		if(p<s*100/origlen)
		{
			if(theApp.fs.m_canceled) {
				theApp.fs.cancel();
				return 0; // return;
			}
			theApp.fs.Set(p);
			p++;
		}
		len=origlen-s;
		for (i=2;i<len;i++)
		{
			j=0;
			while(data[s+i+j]==data[s+j]&&j<len-i)
				j++;
			if (i+j==len&&j>=i)
			{
				theApp.fs.cancel();
				// LoadString(AfxGetInstanceHandle(),IDS_STRING61432,pc_str1,STR_LAENGE_STRING_TABLE);
				// sprintf(pc_str,pc_str1,i,s);
				// AfxMessageBox(pc_str);
				// return;
				return i;
			}
		}
		len--;
	}
	// LoadString(AfxGetInstanceHandle(),IDS_STRING61433,pc_str,STR_LAENGE_STRING_TABLE);
	// AfxMessageBox(pc_str);
	return 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Spezifikation der Periodenanalyse (Henrik Koy 23. Nov. 2000)
// ------------------------------------------------------------
// Eine Periode ist die Wiederholung einer bestimmten Zeichenfolge der
// L�nge k (k >= 1) ab einer bestimmten Position (den Offset = Variablenname
// i_periodenOffset). Die Periode mu� sich bis zum Ende des Dokuments 
// durchziehen.
// Ausgegeben wird Die Periode mit kleinsten Offset (h�chste Priorit�t) und 
// kleinster L�nge Bsp.:
// "bbbbaaaa" hat Periodenoffset 4 und die Periodenl�nge 1.
// Die PeriodenAnalyse wird nur dann ausgef�hrt, wenn die L�nge des Dokuments
// gr��er als 3 Byte ist.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int zzahlanalyse::FindPeriod(int &i_periodenOffset)
{
	int PeriodeGefundenFlag = 0, i_periodenLaenge = 0;
	int i_periodenSuche;

	if (origlen<4)
		return -1;

	int p=0;
	i_periodenOffset=0;

	for (i_periodenSuche=0;i_periodenSuche<origlen-1;i_periodenSuche++)
	{
		// Fortschrittsanzeige...
		if(p<i_periodenSuche*100/origlen)
		{
			if(theApp.fs.m_canceled)
			{
				theApp.fs.cancel();
				i_periodenLaenge = -1;
				break;
			}
			theApp.fs.Set(p);
			p++;
		}
		int i_remainderText = origlen-i_periodenSuche;
		for (int len = 1; len <= i_remainderText/2; len++ )
		{
			if (!PeriodeGefundenFlag && (0 == i_remainderText % len))
			{
				int j = len;
				while ( j < i_remainderText )
				{
					if (data[i_periodenSuche+j] != data[i_periodenSuche + (j % len)])
						break;
					j++;
				}
				if ( j >= i_remainderText)
				{
					i_periodenOffset = i_periodenSuche;
					i_periodenLaenge = len;
					PeriodeGefundenFlag = 1;
				}
			}
		}
		/* Alte Version Peter
		if (!PeriodeGefundenFlag) for (i=1;i<=len;i++)
		{
			j=;
			while(data[i_periodenSuche+i+j]==data[i_periodenSuche+j]&&j<len-i)
				j++;
			if (i+j==len&&j>=i)
			{
				i_periodenOffset = i_periodenSuche;
				i_periodenLaenge = i;
				PeriodeGefundenFlag = 1;
			}
		}
		len++;
		*/
	}
	return i_periodenLaenge;
}
