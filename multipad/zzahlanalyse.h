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
#define PA_MAXFOUND 10

class zzahlanalyse {

public:
	int FindPeriod(int &i_periodenOffset);
	int FindPeriod();
//	zzahlanalyse();
	zzahlanalyse(char *);
	zzahlanalyse(int, char *);
	~zzahlanalyse();

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

	struct s_periodResult {
		int offset, length, repeated;
	};
	s_periodResult periodResults[PA_MAXFOUND];
	int cnt_periodResults;
};


#endif