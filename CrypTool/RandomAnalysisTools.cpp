//////////////////////////////////////////////////////////////////
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

// Implementierung des Dreieckeverfahrens um
// die Qualität von Zufallszahlen zu testen

#include "stdafx.h"
#include "commdlg.h"
#include "CrypToolApp.h"
#include "FileTools.h"
#include "Cryptography.h"
#include <iostream.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RandomAnalysisTools.h"

double CRandomAnalysisTools::CalcTriangle(unsigned long ax,unsigned long ay,unsigned long bx,unsigned long by,unsigned long cx,unsigned long cy)
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

bool CRandomAnalysisTools::AnalyzeIt(void)
{
	int i,j,k,l,p,step,ldl;
	double min;
	unsigned long *ld;

	min=(unsigned long)0xffffffff;
	min=min*min;

	if (isValid==V_MEAN||isValid==V_VARI||isValid==V_RESULT)
	{
		return true;
	}

	LoadString(AfxGetInstanceHandle(),IDS_STRING_END_ANALYZE_VITANY,pc_str,STR_LAENGE_STRING_TABLE);
	theApp.fs.Set(0,pc_str);

	p=0;
	step=datalen/256;
	ldl=datalen/4;
	ld=(unsigned long *)data;

	for (i=4,l=0;i<ldl;i+=2,l++)
	{
		if (p<=0)
		{
			if(theApp.fs.m_canceled)
			{
				theApp.fs.cancel();
				return false;
			}
			theApp.fs.Set((i*i*100)/(ldl*ldl));
			p=step;
		}
		else
		{
			p--;
		}

		for (j=2;j<i;j+=2)
		{
			for (k=0;k<j;k+=2)
			{
				double t;
				t=CalcTriangle(ld[i],ld[i+1],ld[j],ld[j+1],ld[k],ld[k+1]);
				if (t < min)
				{
					min=t;
				}
				if (min < 0.0001 )
				{
					ldl=i;
				}
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

double CRandomAnalysisTools::GetMean()
{
	int i;
	double m;

	if (isValid==V_MEAN||isValid==V_VARI)
	{
		return mean;
	}
	else
	{
		AnalyzeIt();
	}

	for (i=resultlen/10,m=0.;i<resultlen;i++)
	{
		m+=result[i];
	}
	
	isValid=V_MEAN;

	return mean=m/(resultlen*0.9);
}

double CRandomAnalysisTools::GetVariation()
{
	int i;
	double v,t;

	if (isValid==V_VARI)
	{
		return vari;
	}
	else
	{
		GetMean();
	}

	v=0;
	for (i=resultlen/10,v=0.;i<resultlen;i++)
	{
		t=result[i]-mean;
		v+=(t*t);
	}
	
	isValid=V_VARI;

	return vari=sqrt(v/(resultlen*0.9));
}

void CRandomAnalysisTools::WriteAnalyse(char *name,const char *titel)
{
	char name2[128],line[128];
	FILE *fo;
	int i;
	double var,mea;
	CFile f;

	if(!AnalyzeIt())
	{
		return;
	}
	mea=GetMean();
	var=GetVariation();
	GetTmpName(name,"cry",".plt");
	fo = fopen(name,"wt");
	
	for(i=resultlen/10; i<resultlen; i++)
	{
		fprintf(fo,"%lf\n",(result[i]/mea));
	}
	fclose(fo);

	strcpy(name2, name);
	name2[strlen(name)-4] = 0x0;
	
	if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) )
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_AVERAGE_VARIATION,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,mea,var/mea);
		CArchive ar( &f, CArchive::store);
		CString s1 = line;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_VERTICES,pc_str,STR_LAENGE_STRING_TABLE);
		CString s2 = pc_str;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_VARIANCE,pc_str,STR_LAENGE_STRING_TABLE);
		CString s3 = pc_str;
		
		ar << s1 << s2 << s3;
		
		// CONTINUOUS  X_CHAR  Y_CHAR
		ar << (int)1 << '0' << '0';
		
		ar.Close(); f.Close();
		
	}
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING_DIAGRAM_VITANY,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName(line,sizeof(line),pc_str,titel);

	theApp.ThreadOpenDocumentFileNoMRU(name,line);
}

void CRandomAnalysisTools::SetData(int len)
{
	origlen=len;
	len=(len>8192) ? 8192 : len;
	datalen=(len-1)&(~7);
	resultlen=(datalen/4)-2;
    if ( resultlen < 1 )
	{
		resultlen = 1;
	}
	result=(double *)malloc(resultlen*sizeof(double));
	isValid=VALUE_NONE;
}

CRandomAnalysisTools::CRandomAnalysisTools(int len, char *d)
{
	cnt_periodResults=0;

	SetData(len);
	data=(char *)malloc(origlen);
	memcpy(data,d,origlen); // len -> origlen, damit auch die ganzen Daten in das Feld geschrieben werden. [TG]
}

CRandomAnalysisTools::CRandomAnalysisTools(char *infile)
{
	int len;
	FILE *fp;

	cnt_periodResults=0;
	len=filesize(infile);
	if(fp=fopen(infile,"rb"))
	{
		data=(char *)malloc(len);
		fread(data,1,len,fp);
		fclose(fp);
		SetData(len);
	}
}

CRandomAnalysisTools::~CRandomAnalysisTools()
{
	free(data);
	free(result);
}

int CRandomAnalysisTools::FindPeriod()
// jetzt die Version von Peer Wichmann (Algorithmus) und Thomas Gauweiler (Algorithmus, Implementierung)
// Idee:
// Man beginnt von hinten mit zwei Zeigern zu suchen.
// Man hat ferner drei Zustände zu beachten: keine Periode, Periodenverdacht und Periode bestätigt.
// Initialzustand ist 'keine Periode', beide Zeiger auf das Ende gesetzt.
// Der suchende Zeiger tastet sich vor und sucht dasselbe Zeichen, das der folgende Zeiger hat.
// Trifft dies zu kommen wir zum Periodenverdacht. Jetzt folgt der folgende Zeiger im gleichbleibendem
// Abstand. Überquert der folgende Zeiger den Offset, den der suchende Zeiger zu Beginn des
// Periodenverdacht hatte, ist die Periode bestätigt. Dann wird nur noch nach dem Beginn der Periode
// gesucht. Sobald zwischen beiden Zeigern wieder ungleiche Werte entstehen, ist der Periodenanfang
// gefunden. Der Status wechselt wieder zu 'keine Periode', der folgende Zeiger springt wieder ans
// Ende und es wird eine übergeordnete Periode gesucht.
{
	int p=0;
	int search, follow=origlen-1;

	for (search=origlen-2; search>=0; search--)
	{
		// Fortschrittsanzeige... - aber nur wenn's auch etwas mehr zu tun gibt.
		if ((origlen > 1000))
		{
			if(p<(origlen-search)/(origlen/100))
			{
				if(theApp.fs.m_canceled)
				{
					theApp.fs.cancel();
					break;
				}
				p=(origlen-search)/(origlen/100);
				theApp.fs.Set(p);
			}
		}

		if (data[follow] == data[search])
		{ // wohl innerhalb einer Periode
			follow--;
		}
		else if (follow < origlen-1)	// wenn follow nicht am Ende ist...
		{ // zumindest im Periodenverdacht
			if (origlen-1 - follow >= follow-search)
			{ // mindestens eine volle Periode
				if (PA_MAXFOUND <= cnt_periodResults)
				{
					return cnt_periodResults;
				}
				periodResults[cnt_periodResults].offset  = search+1;
				periodResults[cnt_periodResults].length  = follow-search;
				periodResults[cnt_periodResults].repeated= (origlen-1 - follow) / (follow-search);
				int l=(PA_MAXPRINTLENGTH < (follow-search)) ? PA_MAXPRINTLENGTH : (follow-search);
				for (int j=0; j<l; j++)
				{
					periodResults[cnt_periodResults].str[j] = data[search+1+j];
				}
				periodResults[cnt_periodResults].str[l] = '\0';
				cnt_periodResults++;

				// Jan Blumenstein (JB) Bugfix 08-08-02 Beginn
				// war notwendig, da z.B. in "zezrzrzzezrzrz" die Periode "zezrzrz" nicht erkannt wurde
				
				search = follow;

				// search wird auf Position von follow zurückgesetzt, wenn eine Periode gefunden wurde
			}				
			
			else	// hier kommt man hin, wenn bei search zwar eine gleiche Zeichenfolge wie am Ende
					// gefunden wurde, diese aber nicht bis search durchgehend auftritt und damit ausscheidet
			{
				search += (origlen - 1 - follow);
							
				// auf diese Weise gehen die letzten (origlen-1-follow) Zeichen, rechts von der aktuellen
				// search-Position, nicht "verloren" - sie könnten schließlich der Anfang einer langen
				// Periode sein
			}
			// JB Bugfix Ende

			follow = origlen-1;
		}
	}
	// falls nur Perioden vorliegen (z.B. "ababab"), dann gibt es noch die übergeordnete einzutragen
	if (follow < origlen-1)
	{// zumindest im Periodenverdacht
		if (origlen-1 - follow >= follow-search)
		{ // mindestens eine volle Periode
			if (PA_MAXFOUND <= cnt_periodResults)
			{
				return cnt_periodResults;
			}
			periodResults[cnt_periodResults].offset  = search+1;
			periodResults[cnt_periodResults].length  = follow-search;
			periodResults[cnt_periodResults].repeated= (origlen-1 - follow) / (follow-search);
            int l=(PA_MAXPRINTLENGTH < (follow-search)) ? PA_MAXPRINTLENGTH : (follow-search);
            for (int j=0; j<l; j++)
			{
				periodResults[cnt_periodResults].str[j] = data[search+1+j];
			}
			periodResults[cnt_periodResults].str[l] = '\0';
			cnt_periodResults++;
		}
	}

	return cnt_periodResults;
}

int CRandomAnalysisTools::FindPeriod(int &i_periodenOffset)
// nur um den Schein der alten Schnittstelle zu wahren
{
	int ret=FindPeriod();
	if (ret<=0)
	{
		return (ret);
	}
	i_periodenOffset = periodResults[cnt_periodResults-1].offset;
	return (periodResults[cnt_periodResults-1].length);
}