//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
// Modifiziert von Matej Matejicek 2001
// Nur für die Cryptool Datei "TEST-Param.ini"
// Deutsche Bank AG Frankfurt - IT Security
//////////////////////////////////////////////////////////////////

#include <afxtempl.h>

class CReadIniFile2 : public CStdioFile
{

public:
	typedef CList <CString,CString&> CStringList; // A List which will contain CString entries

private:
	CString keyword_prefix1;
	CString keyword_prefix2;
	CString keyword_prefix3;
	CString keyword_suffix;
	CString keyword;
	CString start_block;
	CString end_block;
	CString Line;
	CString inputfile;

	CStdioFile IniDataFile; //"TEST-Param.ini" Datei

public:
	// Methoden
	int GetAlphaList(CStringList& AlphaList);			//Alpha-Liste
	int GetDefaultAlpha(CString& curveID);				//Default-Alpha
	double GetAlphaParam(CString alpha, UINT def_id);	//Parameter von Alpha, def_id ist 
														//die Freiheitsgrad v
};
