// TextAnalyse.h: Schnittstelle für die Klasse TextAnalyse.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTANALYSE_H__83C7F3B3_0C82_11D5_8102_000629C93170__INCLUDED_)
#define AFX_TEXTANALYSE_H__83C7F3B3_0C82_11D5_8102_000629C93170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define range		256
#define buffsize	4096

class TextAnalyse  
{
public:
	double freq[range];
	long count[range];
	void Analyse();
	TextAnalyse();
	virtual ~TextAnalyse();

private:
	bool Checksum();
	void Correct_count_table();
	void Make_freq_table();
	long total_count;
};

#endif // !defined(AFX_TEXTANALYSE_H__83C7F3B3_0C82_11D5_8102_000629C93170__INCLUDED_)
