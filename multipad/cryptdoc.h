//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// CryptDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCryptDoc document

class CCryptDoc : public CPadDoc
{
protected:
	char ContentName[128];
	virtual BOOL present(const char *in, char *out);
	char PresentationName[128];
	CCryptDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCryptDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCryptDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void OnCloseDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
// for rich text edit 
	void SetModifiedFlag( BOOL bModified = TRUE );
	BOOL IsModified();
// 
	virtual ~CCryptDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCryptDoc)
	afx_msg void OnAddBin();
	afx_msg void OnPlayfairBin();
	afx_msg void OnPlayfairAnalyse();
	afx_msg void OnCaesarAsc();
	afx_msg void OnVigenereAsc();
	afx_msg void OnXorBin();
	afx_msg void OnAuto();
	afx_msg void OnEntropy();
	afx_msg void OnHistogram();
	afx_msg void OnCryptIdea();
	afx_msg void OnCryptRc2();
	afx_msg void OnCryptDesDesecb();
	afx_msg void OnCryptHashMd5();
	afx_msg void OnCryptHashMd2();
	afx_msg void OnCryptHashMd4();
	afx_msg void OnCryptHashRipemd160();
	afx_msg void OnCryptHashSha();
	afx_msg void OnCryptHashSha1();
	afx_msg void OnVernamBin();
	afx_msg void OnCrypt3desCbc();
	afx_msg void OnCrypt3desEcb();
	afx_msg void OnCryptRc4();
	afx_msg void OnCryptDesDescbc();
	afx_msg void OnCaesarAuto();
	afx_msg void OnVigenereAuto();
	afx_msg void OnHillPlain();
	afx_msg void OnAddAuto();
	afx_msg void OnXorAuto();
	afx_msg void OnHill();
	afx_msg void OnZip();
	afx_msg void OnUnzip();
	afx_msg void OnCRYPTDelPse();
	afx_msg void OnCRYPTRsaDec();
	afx_msg void OnCRYPTRsaEnc();
	afx_msg void OnCryptMono();
	afx_msg void OnCryptSign();
	afx_msg void OnCryptVerify();
	afx_msg void OnCryptExtract();
	afx_msg void OnAnalyzeSubst();
	afx_msg void OnFloating();
	afx_msg void OnUpdateNeedSecude(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNeedSecudeTicket(CCmdUI* pCmdUI);
	afx_msg void OnAnalyseDescbc();
	afx_msg void OnAnalyseDesecb();
	afx_msg void OnAnalyseIdea();
	afx_msg void OnAnalyseRc2();
	afx_msg void OnAnalyseRc4();
	afx_msg void OnAnalyseTripledescbc();
	afx_msg void OnAnalyseTripledesecb();
	afx_msg void OnCryptAesMars();
	afx_msg void OnCryptAesRc6();
	afx_msg void OnCryptAesRijndael();
	afx_msg void OnCryptAesSerpent();
	afx_msg void OnCryptAesTwofish();
	afx_msg void OnAnalyseAesMars();
	afx_msg void OnAnalyseAesRc6();
	afx_msg void OnAnalyseAesRijndael();
	afx_msg void OnAnalyseAesSerpent();
	afx_msg void OnAnalyseAesTwofish();
	afx_msg void OnToTxt(); 
	afx_msg void OnToHex();
	afx_msg void OnVitanyAnalyse();
	afx_msg void OnPeriod();
	afx_msg void OnHomophon();
	afx_msg void OnHomophoneHex();
	afx_msg void OnZZGen();
	afx_msg void OnNotAvail();
	afx_msg void OnHomophone();
    afx_msg void OnAnalyseNGram();
	afx_msg void OnAnalyseNGramBin();
    afx_msg void OnPermutationAsc();
	// afx_msg void OnAnalyseZufallstestsFrequencytest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL UpdateContent( void );
};


/////////////////////////////////////////////////////////////////////////////
// CHexDoc document

class CHexDoc : public CCryptDoc
{
protected:
	CHexDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHexDoc)

// Attributes
public:
BOOL CHexDoc::UpdateContent( void );

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexDoc)
	public:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHexDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHexDoc)
	afx_msg void OnUpdateFALSE(CCmdUI* pCmdUI);
	afx_msg void OnEntropy();
	afx_msg void OnHistogram();
	afx_msg void OnAuto();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAscDoc document

class CAscDoc : public CCryptDoc
{
protected:
	virtual BOOL present(const char *in, char *out);
	CAscDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAscDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAscDoc)
	public:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAscDoc();
	virtual void Serialize(CArchive& ar);
	virtual void SetData(int);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	int m_blocklen;

	// Generated message map functions
protected:
	//{{AFX_MSG(CAscDoc)
	afx_msg void OnUpdateFALSE(CCmdUI* pCmdUI);
	afx_msg void OnEntropy();
	afx_msg void OnHistogram();
	afx_msg void OnAuto();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL UpdateContent( void );
};
