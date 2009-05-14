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

#if !defined(AFX_ANALYSENGRAM_H__93B8AE31_1461_11D5_92DF_00B0D0161C45__INCLUDED_)
#define AFX_ANALYSENGRAM_H__93B8AE31_1461_11D5_92DF_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnalyseNGram.h : Header-Datei
//

#define NGRAM_NMAX 16 // maximal erlaubtes N für die N-Gramm analyse


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgNGramAnaylsis 

class CNGram;


class CDlgNGramAnaylsis : public CDialog
{
// Konstruktion
	CNGram *NGramPtr;
	bool	b_SaveNGramList;
	long	l_N;
    BOOL	isBinary;
	long	l_DispNGrams;
	char   *bufferRef;
	unsigned long bufferSize;
	void	SetupListBox( int N = 1 );
	BOOL    NGramActualized;
	char    Title[256];

public:
	void Register( int N );
	bool b_saveNGramList();
	char outfile[CRYPTOOL_PATH_LENGTH];
	int  GetN();
	void LoadText( char *buffer, const unsigned long Size, const char *OldTitle, 
		           BOOL BinaryFile = FALSE );
	BOOL OnInitDialog();
	     CDlgNGramAnaylsis(CWnd* pParent = NULL);   // Standardkonstruktor
    	~CDlgNGramAnaylsis();

// Dialogfelddaten
	//{{AFX_DATA(CDlgNGramAnaylsis)
	enum { IDD = IDD_NGRAM_ANALYSIS };
	CEdit	m_ShowCntNGramCtrl;
	CEdit	  m_NrNGramCtrl;
	CListCtrl m_ListView;
	int       m_N_NGram;
	unsigned long  	  m_ShowCntNGram;
	unsigned long  	  m_NrNGram;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgNGramAnaylsis)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgNGramAnaylsis)
	afx_msg void OnEvalNGram();
	afx_msg void OnSaveNGramList();
	afx_msg void OnTextOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};




class CNGram  
{	
	CNGram();
	unsigned long  Size;
	unsigned long  hashed;
	unsigned long  HashTableSize;
	unsigned short N;
	unsigned short AlphabetSize;
	char          *NGramHashTable;
	unsigned long  individuals;
	unsigned long  iterator;
	int  preSort( int tSize, int cnt );

public:
	CNGram( const unsigned long  fileSize, 
		    const unsigned short _N, 
			const unsigned short alphabetSize = 256 );
	virtual ~CNGram();
	void add( const char * substring );
	void sort();
	void get( char *SubStr, unsigned long &cnt, double &rel );
	void resetIterator() { iterator = 0; }	
	unsigned long getIndividuals() { return individuals; }
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ANALYSENGRAM_H__93B8AE31_1461_11D5_92DF_00B0D0161C45__INCLUDED_
