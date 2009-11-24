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

#ifndef _CRYPTDOC_H_
#define _CRYPTDOC_H_

#include "symEncBase.h"
#include "CrypToolApp.h"

//////////////////////////////////////////////////////////////////
// CryptDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCryptDoc document

class CCryptDoc : public CAppDocument
{

protected:
	virtual BOOL present(const char *in, char *out);
	// PRESENTATION_NAME char PresentationName[128];
	CCryptDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCryptDoc)

// Attributes
public:
	char ContentName[CRYPTOOL_PATH_LENGTH];

// Operations
public:
	virtual BOOL UpdateContent( void );

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
#if 0
// for rich text edit 
	void SetModifiedFlag( BOOL bModified = TRUE );
	BOOL IsModified();
#endif
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
	afx_msg void OnCryptHashSha256();
	afx_msg void OnCryptHashSha512();
	afx_msg void OnVernamBin();
	afx_msg void OnCrypt3desCbc();
	afx_msg void OnCrypt3desEcb();
	afx_msg void OnCryptRc4();
	afx_msg void OnCryptDesDescbc();
	afx_msg void OnCaesarAuto();
	afx_msg void OnVigenereAuto();
	afx_msg void OnVigenereAnalysisSchroedel();
	afx_msg void OnHillPlain();
	afx_msg void OnAddAuto();
	afx_msg void OnXorAuto();
	afx_msg void OnHill();
	afx_msg void OnZip();
	afx_msg void OnUnzip();
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
	afx_msg void OnVitanyAnalyse();
	afx_msg void OnPeriod();
	afx_msg void OnHomophone();
    afx_msg void OnAnalyseNGram();
	afx_msg void OnAnalyseNGramBin();
    afx_msg void OnPermutation();
	afx_msg void OnAesSelfextract();
	afx_msg void OnUpdateAesSelfextract(CCmdUI* pCmdUI);
	afx_msg void OnAnalyseZufallstestsFrequencytest();
	afx_msg void OnAnalyseZufallstestsSerialtest();
	afx_msg void OnAnalyseZufallstestsRuns();
	afx_msg void OnAnalyseZufallstestsPokertest();
	afx_msg void OnAnalyseZufallstestsFipspub1401();
	afx_msg void OnEinzelverfahrenHashwerteHashdemo();
	afx_msg void OnEinzelverfahrenHybridverfahrenHybridverschlsselung();
	afx_msg void OnEinzelverfahrenSignDoc();
	afx_msg void OnEinzelverfahrenHybridverfahrenHybridentschlsselung();
	afx_msg void OnEinzelverfahrenAsn1decodieren();
	afx_msg void OnSigattmodificdemo();
	afx_msg void OnSignaturAttack();
	afx_msg void OnEinzelverfahrenSidechannelattackOnHybridencryption();
	afx_msg void OnFileProperties();
	afx_msg void OnMessageauthenticationcode();
	afx_msg void OnEncryptAdfgvx();
	afx_msg void OnAnalyseSymmclassicAdfgvx();
	afx_msg void OnCiphertextOnlySubstitution();
	afx_msg void OnRot13caesarAsc();
	afx_msg void OnShowKey();
	afx_msg void OnGotoVater();
	afx_msg void OnAnalysisRandom3dVisualization();
	afx_msg void OnSymclassicSolitaire();
	afx_msg void OnEncryptionSimpleTranspositions();
	afx_msg void OnAnalyseSymmclassicCiphertextolySolitaire();
	afx_msg void OnIndivproceduresBase64Encode();
	afx_msg void OnIndivproceduresBase64Decode();
    afx_msg void OnCryptDESL();
	afx_msg void OnCryptDESX();
	afx_msg void OnCryptDESXL();
	afx_msg void OnAnalyseDESL();
	afx_msg void OnAnalyseDESX();
	afx_msg void OnAnalyseDESXL();
	afx_msg void OnFormatTextDocument();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SymCryptBruteForce( int AlgID, cryptProvider provider, int keylen_min, int keylen_max, int keylen_step = 1 );

public:
	afx_msg void OnDecodeUu();
	afx_msg void OnEncodeUu();
	afx_msg void OnHybridEccEnc();
	afx_msg void OnHybridEccDec();
	afx_msg void OnEditRepeat();
	afx_msg void OnUpdateEditRepeat(CCmdUI *pCmdUI);
	afx_msg void OnKnownAnalysisSinglePermutation();
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
	afx_msg void OnUpdateTotxt(CCmdUI* pCmdUI);
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

#endif
