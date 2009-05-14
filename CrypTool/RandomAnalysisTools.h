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