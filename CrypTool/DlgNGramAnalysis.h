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
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
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
