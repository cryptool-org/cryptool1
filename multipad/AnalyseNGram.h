#if !defined(AFX_ANALYSENGRAM_H__93B8AE31_1461_11D5_92DF_00B0D0161C45__INCLUDED_)
#define AFX_ANALYSENGRAM_H__93B8AE31_1461_11D5_92DF_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnalyseNGram.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld AnalyseNGram 

class AnalyseNGram : public CDialog
{
// Konstruktion
public:
	bool b_saveNGramList();
	char outfile[128];
	~AnalyseNGram();
	int GetN();
	void LoadText(SymbolArray &, BOOL BinaryFile = FALSE );
	BOOL OnInitDialog();
	AnalyseNGram(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(AnalyseNGram)
	enum { IDD = IDD_DIALOG_ANALYSE_NGRAM };
		CListCtrl m_ListView;
		int       m_N_NGram;
	long	m_ShowCntNGram;
	long	m_NrNGram;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(AnalyseNGram)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(AnalyseNGram)
	afx_msg void OnEvalNGram();
	afx_msg void OnSaveNGramList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool b_SaveNGramList;
	long l_N;
	void SetupListBox( int N = 1 );
	SymbolArray *textRef;
    BOOL isBinary;

// NGramm-Daten
	long				 l_DispNGrams;
	NGram				*toAnalyze;
	SortedArray<double> *SA;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ANALYSENGRAM_H__93B8AE31_1461_11D5_92DF_00B0D0161C45__INCLUDED_
