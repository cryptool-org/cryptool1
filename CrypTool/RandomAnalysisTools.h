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
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

// Header zu ZZahlAnalyse.cpp

#ifndef ZZAHLANALYSE
#define ZZAHLANALYSE

#define MAXINT 10000000000.0
#define VALUE_NONE 0
#define V_RESULT 1
#define V_MEAN 2
#define V_VARI 3
#define DEFAULTNAME "Analyse"
#define PA_MAXFOUND 100
#define PA_MAXPRINTLENGTH 20

class CRandomAnalysisTools {

public:
	int FindPeriod(int &i_periodenOffset);
	int FindPeriod();
	CRandomAnalysisTools(char *);
	CRandomAnalysisTools(int, char *);
	~CRandomAnalysisTools();

	void SetData(int);
	bool AnalyzeIt();
	void WriteAnalyse(char *,const char *);
	double *GetResult();
	double GetMean();
	double GetVariation();
	double CalcTriangle(unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long);

	char *data;
	int datalen,resultlen,origlen;
	double *result;
	int isValid;

	double mean,vari;

	struct s_periodResult
	{
		int offset, length, repeated;
		char str [PA_MAXPRINTLENGTH+1];
	};
	s_periodResult periodResults[PA_MAXFOUND];
	int cnt_periodResults;
};


#endif