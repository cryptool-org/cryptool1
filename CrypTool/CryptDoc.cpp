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

// CryptDoc.cpp : implementation file
//

#include "stdafx.h"
#include <io.h>
#include <process.h>
#include "CrypToolApp.h"
#include <fstream>
#include "FileTools.h"
#include "base64.h"
#include "CryptDoc.h"
#include "CrypToolTools.h"
#include "uucode.h"

#include "DlgShowKeyHill5x5.h"
#include "DlgShowKeyHill10x10.h"

#include "DlgVigenereAnalysisSchroedel.h"

#include "Cryptography.h"
#include "AutomaticAnalysis.h"
#include "SecudeCryptography.h"
#include "MakeZip.h"
#include "AsymmetricEncryption.h"
#include "DlgAbout.h"
#include "RandomAnalysisTools.h"
#include "DlgKeyHomophone.h"
#include "DlgNGramAnalysis.h"
#include "DlgExtractSignature.h" // für OnCryptExtract
#include "DlgStatRandTests.h"
#include "DlgHybridEncryptionDemo.h"
#include "DlgHybridDecryptionDemo.h"
#include <sys\stat.h>
#include "DialogeMessage.h"
#include "ASN1Decoder.h"
#include "DlgDiffieHellmanVisualization.h"
#include "DlgASN1PSEPINPrompt.h"
#include "DlgSigAttModificDemo.h"
#include "DlgSignatureAttack.h"
#include "DlgSideChannelAttackVisualizationHE.h"
#include "DlgFileProperties.h"
#include "DlgADFGVX.h"
#include "DlgAdfgvxManual.h"
#include "MonoSubstCracker.h"
#include "DlgRot13Caesar.h"
#include "DlgShowKey.h"
#include "DlgSolitaire.h"
#include "DlgSolitaireAnalyse.h"
#include "ECIESMain.h"
#include "bruteforceheap.h"
#include "DlgFormatTextDocument.h"
#include "DlgSimpleTranspositions.h"
#include "DlgAutomatedPermAnalysis.h"

extern char *CaPseDatei, *CaPseVerzeichnis, *Pfad, *PseVerzeichnis;

extern UINT singleThreadVigenereAnalysisSchroedel(PVOID argument);

/////////////////////////////////////////////////////////////////////////////
// CCryptDoc



IMPLEMENT_DYNCREATE(CCryptDoc, CRichEditDoc)

CCryptDoc::CCryptDoc()
{
	ContentName[0] = 0;
	// PRESENTATION_NAME PresentationName[0] = 0;
}

BOOL CCryptDoc::OnNewDocument()
{
	FILE *f;

	if (!CAppDocument::OnNewDocument())
		return FALSE;
    GetTmpName(ContentName,"cry",".org");
	f = fopen(ContentName,"wb");
// Überprüfen ob neues Dokument angelegt werden kann
	if (!f)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_COULD_NOT_OPEN_TMP_FILE,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_NOTE,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	fclose(f);

	return TRUE;
}

CCryptDoc::~CCryptDoc()
{
}


void CCryptDoc::SymCryptBruteForce( int AlgID, cryptProvider provider, int keylen_min, int keylen_max, int keylen_step )
{
	algorithm_info *info;
	info = (algorithm_info*)malloc(sizeof(algorithm_info));
	info->AlgId = AlgID;
	info->provider = provider;

	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->key = (char*)info;
	para->keylenstep = keylen_step; 
	para->keylenmin = keylen_min;
	para->keylenmax = keylen_max;
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	para->result = NULL;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( SymmetricBruteForce, ((void *) para) );
}


BEGIN_MESSAGE_MAP(CCryptDoc, CAppDocument)
	//{{AFX_MSG_MAP(CCryptDoc)
	ON_COMMAND(ID_ADD_BIN, OnAddBin)
	ON_COMMAND(ID_PLAYFAIR_BIN, OnPlayfairBin)
	ON_COMMAND(ID_PLAYFAIR_ANALYSE, OnPlayfairAnalyse)
	ON_COMMAND(ID_CAESAR_ASC, OnCaesarAsc)
	ON_COMMAND(ID_VIGENERE_ASC, OnVigenereAsc)
	ON_COMMAND(ID_XOR_BIN, OnXorBin)
	ON_COMMAND(ID_AUTO, OnAuto)
	ON_COMMAND(ID_ENTROPY, OnEntropy)
	ON_COMMAND(ID_HISTOGRAM, OnHistogram)
	ON_COMMAND(ID_CRYPT_IDEA, OnCryptIdea)
	ON_COMMAND(ID_CRYPT_RC2, OnCryptRc2)
	ON_COMMAND(ID_CRYPT_DES_DESECB, OnCryptDesDesecb)
	ON_COMMAND(ID_CRYPT_HASH_MD5, OnCryptHashMd5)
	ON_COMMAND(ID_CRYPT_HASH_MD2, OnCryptHashMd2)
	ON_COMMAND(ID_CRYPT_HASH_MD4, OnCryptHashMd4)
	ON_COMMAND(ID_CRYPT_HASH_RIPEMD160, OnCryptHashRipemd160)
	ON_COMMAND(ID_CRYPT_HASH_SHA, OnCryptHashSha)
	ON_COMMAND(ID_CRYPT_HASH_SHA1, OnCryptHashSha1)
	ON_COMMAND(ID_CRYPT_HASH_SHA256, OnCryptHashSha256)
	ON_COMMAND(ID_CRYPT_HASH_SHA512, OnCryptHashSha512)
	ON_COMMAND(ID_VERNAM_BIN, OnVernamBin)
	ON_COMMAND(ID_CRYPT_3DES_CBC, OnCrypt3desCbc)
	ON_COMMAND(ID_CRYPT_3DES_ECB, OnCrypt3desEcb)
	ON_COMMAND(ID_CRYPT_RC4, OnCryptRc4)
	ON_COMMAND(ID_CRYPT_DES_DESCBC, OnCryptDesDescbc)
	ON_COMMAND(ID_CAESAR_AUTO, OnCaesarAuto)
	ON_COMMAND(ID_VIGENERE_AUTO, OnVigenereAuto)
	ON_COMMAND(ID_ANALYSIS_VIGENERE_SCHROEDEL, OnVigenereAnalysisSchroedel)
	ON_COMMAND(ID_HILL_AUTO, OnHillPlain)
	ON_COMMAND(ID_ADD_AUTO, OnAddAuto)
	ON_COMMAND(ID_XOR_AUTO, OnXorAuto)
	ON_COMMAND(ID_HILL, OnHill)
	ON_COMMAND(ID_ZIP, OnZip)
	ON_COMMAND(ID_UNZIP, OnUnzip)
	ON_COMMAND(ID_CRYPT_RsaDec, OnCRYPTRsaDec)
	ON_COMMAND(ID_CRYPT_RsaEnc, OnCRYPTRsaEnc)
	ON_COMMAND(ID_CryptMono, OnCryptMono)
	ON_COMMAND(ID_CRYPT_SIGN, OnCryptSign)
	ON_COMMAND(ID_CRYPT_VERIFY, OnCryptVerify)
	ON_COMMAND(ID_CRYPT_EXTRACT, OnCryptExtract)
	ON_COMMAND(ID_ANALYZE_SUBST, OnAnalyzeSubst)
	ON_COMMAND(ID_FLOATING, OnFloating)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_3DES_CBC, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_EXTRACT, OnUpdateNeedSecudeTicket)
	ON_COMMAND(ID_ANALYSE_DESCBC, OnAnalyseDescbc)
	ON_COMMAND(ID_ANALYSE_DESECB, OnAnalyseDesecb)
	ON_COMMAND(ID_ANALYSE_IDEA, OnAnalyseIdea)
	ON_COMMAND(ID_ANALYSE_RC2, OnAnalyseRc2)
	ON_COMMAND(ID_ANALYSE_RC4, OnAnalyseRc4)
	ON_COMMAND(ID_ANALYSE_TRIPLEDESCBC, OnAnalyseTripledescbc)
	ON_COMMAND(ID_ANALYSE_TRIPLEDESECB, OnAnalyseTripledesecb)
	ON_COMMAND(ID_CRYPT_AES_MARS, OnCryptAesMars)
	ON_COMMAND(ID_CRYPT_AES_RC6, OnCryptAesRc6)
	ON_COMMAND(ID_CRYPT_AES_RIJNDAEL, OnCryptAesRijndael)
	ON_COMMAND(ID_CRYPT_AES_SERPENT, OnCryptAesSerpent)
	ON_COMMAND(ID_CRYPT_AES_TWOFISH, OnCryptAesTwofish)
	ON_COMMAND(ID_ANALYSE_AES_MARS, OnAnalyseAesMars)
	ON_COMMAND(ID_ANALYSE_AES_RC6, OnAnalyseAesRc6)
	ON_COMMAND(ID_ANALYSE_AES_RIJNDAEL, OnAnalyseAesRijndael)
	ON_COMMAND(ID_ANALYSE_AES_SERPENT, OnAnalyseAesSerpent)
	ON_COMMAND(ID_ANALYSE_AES_TWOFISH, OnAnalyseAesTwofish)
	ON_COMMAND(ID_ANALYSE_VITANY, OnVitanyAnalyse)
	ON_COMMAND(ID_ANALYSE_PERIOD, OnPeriod)
	ON_COMMAND(ID_HOMOPHONE_ASC, OnHomophone)
	ON_COMMAND(ID_ANALYSE_NGRAM, OnAnalyseNGram)
	ON_COMMAND(ID_ANALYSE_NGRAM_BIN, OnAnalyseNGramBin)
	ON_COMMAND(ID_PERMUTATION, OnPermutation)
	ON_COMMAND(ID_AES_SELFEXTRACT, OnAesSelfextract)
	ON_UPDATE_COMMAND_UI(ID_AES_SELFEXTRACT, OnUpdateAesSelfextract)
	ON_COMMAND(ID_ANALYSE_ZUFALLSTESTS_FREQUENCYTEST, OnAnalyseZufallstestsFrequencytest)
	ON_COMMAND(ID_ANALYSE_ZUFALLSTESTS_SERIALTEST, OnAnalyseZufallstestsSerialtest)
	ON_COMMAND(ID_ANALYSE_ZUFALLSTESTS_RUNS, OnAnalyseZufallstestsRuns)
	ON_COMMAND(ID_ANALYSE_ZUFALLSTESTS_POKERTEST, OnAnalyseZufallstestsPokertest)
	ON_COMMAND(ID_ANALYSE_ZUFALLSTESTS_FIPSPUB1401, OnAnalyseZufallstestsFipspub1401)
	ON_COMMAND(ID_EINZELVERFAHREN_HASHWERTE_HASHDEMO, OnEinzelverfahrenHashwerteHashdemo)
	ON_COMMAND(ID_VERENTSCHLSSELN_HYBRIDVERFAHREN_HYBRIDVERSCHLSSELUNG, OnEinzelverfahrenHybridverfahrenHybridverschlsselung)
	ON_COMMAND(ID_EINZELVERFAHREN_SIGN_DOC, OnEinzelverfahrenSignDoc)
	ON_COMMAND(ID_VERENTSCHLSSELN_HYBRIDVERFAHREN_HYBRIDENTSCHLSSELUNG, OnEinzelverfahrenHybridverfahrenHybridentschlsselung)
	ON_COMMAND(ID_EINZELVERFAHREN_ASN1DECODIEREN, OnEinzelverfahrenAsn1decodieren)
	ON_COMMAND(ID_SIGATTMODIFICDEMO, OnSigattmodificdemo)
	ON_COMMAND(ID_SIGNATUR_ATTACK, OnSignaturAttack)
	ON_COMMAND(ID_EINZELVERFAHREN_SIDECHANNELATTACK_ON_HYBRIDENCRYPTION, OnEinzelverfahrenSidechannelattackOnHybridencryption)
	ON_COMMAND(ID_FILEPROPERTIES, OnFileProperties)
	ON_COMMAND(ID_GENERATE_MACS, OnMessageauthenticationcode)
	ON_COMMAND(ID_ENCRYPT_ADFGVX, OnEncryptAdfgvx)
	ON_COMMAND(ID_ANALYSE_SYMMCLASSIC_ADFGVX, OnAnalyseSymmclassicAdfgvx)
	ON_COMMAND(ID_CIPHERTEXT_ONLY_SUBSTITUTION, OnCiphertextOnlySubstitution)
	ON_COMMAND(ID_SHOW_KEY, OnShowKey)
	ON_COMMAND(ID_GOTO_VATER, OnGotoVater)
	ON_COMMAND(ID_ANALYSIS_RANDOM_3D_VISUALIZATION, OnAnalysisRandom3dVisualization)
	ON_COMMAND(ID_SYMCLASSIC_SOLITAIRE, OnSymclassicSolitaire)
	ON_COMMAND(ID_ENCRYPTION_SIMPLE_TRANSPOSITIONS, OnEncryptionSimpleTranspositions)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_3DES_ECB, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_DES_DESCBC, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_DES_DESECB, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_HASH_MD2, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_HASH_MD4, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_HASH_MD5, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_HASH_RIPEMD160, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_HASH_SHA, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_HASH_SHA1, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_IDEA, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_RC4, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_RC2, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_RsaDec, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_RsaEnc, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_SIGN, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_VERIFY, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_ANALYSE_DESCBC, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_ANALYSE_DESECB, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_ANALYSE_IDEA, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_ANALYSE_RC2, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_ANALYSE_RC4, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_ANALYSE_TRIPLEDESCBC, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_ANALYSE_TRIPLEDESECB, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_VERENTSCHLSSELN_HYBRIDVERFAHREN_HYBRIDVERSCHLSSELUNG, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_VERENTSCHLSSELN_HYBRIDVERFAHREN_HYBRIDENTSCHLSSELUNG, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_EINZELVERFAHREN_SIGN_DOC, OnUpdateNeedSecude)
	ON_UPDATE_COMMAND_UI(ID_EINZELVERFAHREN_HASHWERTE_HASHDEMO, OnUpdateNeedSecude)
	ON_COMMAND(ID_CIPHERTEXT_ONLY_SUBSTITUTION, OnCiphertextOnlySubstitution)
	ON_COMMAND(ID_ROT13CAESAR_ASC, OnRot13caesarAsc)
	ON_COMMAND(ID_ANALYSE_SYMMCLASSIC_CIPHERTEXTOLY_SOLITAIRE, OnAnalyseSymmclassicCiphertextolySolitaire)
	ON_COMMAND(ID_ENCODE_BASE64, OnIndivproceduresBase64Encode)
	ON_COMMAND(ID_DECODE_BASE64, OnIndivproceduresBase64Decode)
	ON_COMMAND(ID_ENCODE_UU, OnEncodeUu)
	ON_COMMAND(ID_DECODE_UU, OnDecodeUu)
	ON_COMMAND(ID_CRYPT_DESL, OnCryptDESL)
	ON_COMMAND(ID_CRYPT_DESX, OnCryptDESX)
	ON_COMMAND(ID_CRYPT_DESXL, OnCryptDESXL)
	ON_COMMAND(ID_ANALYSE_DESL, OnAnalyseDESL)
	ON_COMMAND(ID_ANALYSE_DESX, OnAnalyseDESX)
	ON_COMMAND(ID_ANALYSE_DESXL, OnAnalyseDESXL)
	ON_COMMAND(ID_FORMAT_TEXT_DOCUMENT, OnFormatTextDocument)
	//}}AFX_MSG_MAP

	ON_COMMAND(ID_HYBRID_ECCENC, OnHybridEccEnc)
	ON_COMMAND(ID_HYBRID_ECCDEC, OnHybridEccDec)
	ON_COMMAND(ID_EDIT_REPEAT, OnEditRepeat)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REPEAT, OnUpdateEditRepeat)
	ON_COMMAND(ID_KNOWN_ANALYSIS_SINGLE_PERMUTATION, &CCryptDoc::OnKnownAnalysisSinglePermutation)
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCryptDoc diagnostics

#ifdef _DEBUG
void CCryptDoc::AssertValid() const
{
	CAppDocument::AssertValid();
}

void CCryptDoc::Dump(CDumpContext& dc) const
{
	CAppDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCryptDoc serialization

void CCryptDoc::Serialize(CArchive& ar)
{
    CAppDocument::Serialize( ar );
}

/////////////////////////////////////////////////////////////////////////////
// CCryptDoc commands

void CCryptDoc::OnCloseDocument() 
{
    char name2[128];

    strncpy(name2,ContentName,sizeof(name2));
	CAppDocument::OnCloseDocument();
    remove(name2);

// Remove Elements From List
	bool found = false;
	deque<void*>::iterator it = theApp.m_fileList.begin();
	while ( it != theApp.m_fileList.end() )
	{
		if ( this == (CCryptDoc*)*it )
		{
			found = true;
			break;
		}
		it++;
	}
	if ( found )
		theApp.m_fileList.erase(it);
}

BOOL CCryptDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
    GetTmpName(ContentName,"cry",".org");
	if ( -1 == _access( lpszPathName, 0 ) )
	{
        remove(ContentName);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FILEOPENERROR ,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERROR,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	// ADD_PRESENTATION_NAME
	int r = FileCpy(ContentName, lpszPathName);
    if( !r ) {
        remove(ContentName);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_COULD_NOT_OPEN_TMP_FILE,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_NOTE,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK | MB_ICONWARNING);
		return FALSE;
    }
	if(r==2) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_CHOSEN_TEXT_TO_LARGE,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_NOTE,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK | MB_ICONWARNING);
	}
	// ADD_PRESENTATION_NAME

	if (!CAppDocument::OnOpenDocument( ContentName /* PRESENTATION_NAME PresentationName */)) {
        remove(ContentName);
        // PRESENTATION_NAME remove(PresentationName);
		return FALSE;
    }

	SetPathName(lpszPathName);


// 	theApp.m_fileList.push_back( fileItem( CString(lpszPathName), m_strTitle) );

	return TRUE;
}

BOOL CCryptDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	POSITION pos = GetFirstViewPosition();

    if(IsModified()) CAppDocument::OnSaveDocument(ContentName);
    CAppDocument::OnSaveDocument(lpszPathName);
 	GetNextView(pos)->Invalidate();
 	UpdateAllViews(NULL);
    return TRUE;
}

BOOL CCryptDoc::present(const char *in, char *out)
{
	int r;

    GetTmpName(out,"cry",".txt");
    r = FileCpy(out, in);
	if(r==0) return FALSE;
	if(r==2) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_CHOSEN_TEXT_TO_LARGE,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_NOTE,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK | MB_ICONWARNING);
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CHexDoc

IMPLEMENT_DYNCREATE(CHexDoc, CCryptDoc)

CHexDoc::CHexDoc()
{
}

CHexDoc::~CHexDoc()
{
}


BEGIN_MESSAGE_MAP(CHexDoc, CCryptDoc)
	//{{AFX_MSG_MAP(CHexDoc)
	ON_COMMAND(ID_ENTROPY, OnEntropy)
	ON_COMMAND(ID_HISTOGRAM, OnHistogram)
	ON_COMMAND(ID_AUTO, OnAuto)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexDoc diagnostics

#ifdef _DEBUG
void CHexDoc::AssertValid() const
{
	CCryptDoc::AssertValid();
}

void CHexDoc::Dump(CDumpContext& dc) const
{
	CCryptDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAscDoc

IMPLEMENT_DYNCREATE(CAscDoc, CCryptDoc)

CAscDoc::CAscDoc()
{
	m_blocklen=5;
}

CAscDoc::~CAscDoc()
{
}

void CAscDoc::SetData(int i)
{
	m_blocklen = i;
	UpdateAllViews(NULL);
}

void CAscDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		char name[128];
		CFile f;

		strcpy(name, ar.m_strFileName);
		name[strlen(name)-4]=0x0;
		if( f.Open( name, CFile::modeRead ) )
		{
			CArchive tmp( &f, CArchive::load);	
			tmp >> m_blocklen;	
			tmp.Close(); f.Close();	
		}
	}
	CCryptDoc::Serialize(ar);
}

BEGIN_MESSAGE_MAP(CAscDoc, CCryptDoc)
	//{{AFX_MSG_MAP(CAscDoc)
	ON_COMMAND(ID_ENTROPY, OnEntropy)
	ON_COMMAND(ID_HISTOGRAM, OnHistogram)
	ON_COMMAND(ID_AUTO, OnAuto)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAscDoc diagnostics

#ifdef _DEBUG
void CAscDoc::AssertValid() const
{
	CCryptDoc::AssertValid();
}

void CAscDoc::Dump(CDumpContext& dc) const
{
	CCryptDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAscDoc commands

BOOL CAscDoc::present(const char *in, char *out)
{
	int r;

    GetTmpName(out,"cry",".txt");
//    r = ASCDump(out, in, 5, 8, 0x0FFFFF);
    r = FileCpy(out, in);
	if(r==0) return FALSE;
	if(r==2) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_CHOSEN_TEXT_TO_LARGE,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_NOTE,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK | MB_ICONWARNING);
	}
	return TRUE;
}

void CCryptDoc::OnAddBin() 
{
    UpdateContent();
    AddBin(ContentName, GetTitle());
}

void CCryptDoc::OnCaesarAsc() 
{
    UpdateContent();
    CaesarAsc(ContentName, GetTitle());
}

void CCryptDoc::OnVigenereAsc() 
{
    UpdateContent();
    VigenereAsc(ContentName, GetTitle());
}

void CCryptDoc::OnXorBin() 
{
    UpdateContent();
    XorBin(ContentName, GetTitle());
}

void CCryptDoc::OnVernamBin() 
{
    UpdateContent();
	VernamBin(ContentName, GetTitle());
}

void CHexDoc::OnUpdateFALSE(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(FALSE);
}

void CAscDoc::OnUpdateFALSE(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(FALSE);
}

void CCryptDoc::OnAuto() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM | CRYPT_ASCII;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( Autocorr, ((void *) para) );
}

void CCryptDoc::OnEntropy() 
{
    UpdateContent();
    EntropyASCII(ContentName, GetTitle());	
}

void CAscDoc::OnEntropy() 
{
    UpdateContent();
    EntropyASCII(ContentName, GetTitle());	
}

void CHexDoc::OnEntropy() 
{
    EntropyBin(ContentName, GetTitle());	
}

void CCryptDoc::OnHistogram() 
{
    UpdateContent();
    HistogramASCII(ContentName, GetTitle());	
}

void CAscDoc::OnHistogram() 
{
    UpdateContent();
    HistogramASCII(ContentName, GetTitle());	
}

void CHexDoc::OnHistogram() 
{
    HistogramBin(ContentName, GetTitle());	
}

void CCryptDoc::OnCryptIdea() 
{
    UpdateContent();
	SymmetricEncryption(IDS_CRYPT_IDEA, SECUDE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnCryptRc2() 
{
	UpdateContent();
	SymmetricEncryption(IDS_CRYPT_RC2, SECUDE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnCryptDesDesecb() 
{
    UpdateContent();
	SymmetricEncryption(IDS_CRYPT_DES_ECB, SECUDE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnCryptHashMd2() 
{
    UpdateContent();
	hash(ContentName, GetTitle(),1);
}

void CCryptDoc::OnCryptHashMd4() 
{
    UpdateContent();
	hash(ContentName, GetTitle(),2);
}

void CCryptDoc::OnCryptHashMd5() 
{
    UpdateContent();
	hash(ContentName, GetTitle(),3);	
}

void CCryptDoc::OnCryptHashSha() 
{
    UpdateContent();
	hash(ContentName, GetTitle(),4);
}

void CCryptDoc::OnCryptHashSha1() 
{
    UpdateContent();
	hash(ContentName, GetTitle(),5);
}

void CCryptDoc::OnCryptHashRipemd160() 
{
    UpdateContent();
	hash(ContentName, GetTitle(),6);
}

void CCryptDoc::OnCryptHashSha256()
{
	UpdateContent();
	hash(ContentName, GetTitle(), 7);
}

void CCryptDoc::OnCryptHashSha512()
{
	UpdateContent();
	hash(ContentName, GetTitle(), 8);
}

BOOL CAscDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
    /* store modified file */
    CAppDocument::OnSaveDocument(ContentName);
//    CAppDocument::OnSaveDocument(PresentationName);

    /* create user-file */
    FileCpy(lpszPathName, ContentName);

	return TRUE;
}

BOOL CHexDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
    /* store modified file */
    CAppDocument::OnSaveDocument(ContentName);

/* Do Hex undump */
/*  f1 = fopen(PresentationName,"rt");
    f2 = fopen(ContentName,"wb");
    if((!f1) || (!f2)) return FALSE;
	state = 0; // in scan mode scan adress first

    do {
        l = fread(buffer, 1, sizeof(buffer), f1);
		i = HexUndumpMem(buffer, l, buffer, &state);
		if(i<0) {
			sprintf(line,"Internal error %d! within HexUndumpMem",-i);
			MessageBox(NULL,line,"Error",MB_OK);
		}
		else
			fwrite(buffer, 1, i, f2);
    } while (l>0);
    fclose(f1);
    fclose(f2);*/

    FileCpy(lpszPathName, ContentName);
	
	return TRUE;
}

BOOL CCryptDoc::UpdateContent( void )
{
    const char *oldname;
	CString title;

	{
		CWaitCursor WCursor;

		if(!IsModified()) return TRUE;

		oldname = GetPathName();
		title = GetTitle();

		CAppDocument::OnSaveDocument(ContentName);

	    if(oldname[0]) SetPathName(oldname,FALSE);
		SetTitle(title);
		SetModifiedFlag(TRUE);

	    return TRUE;
	}
}

BOOL CHexDoc::UpdateContent( void )
{
    const char *oldname;
	CString title;

	{
		CWaitCursor WCursor;

	    if(!IsModified()) return TRUE;

	    oldname = GetPathName();
		title = GetTitle();

	    CHexDoc::OnSaveDocument(ContentName);

	    if(oldname[0]) SetPathName(oldname,FALSE);
		SetTitle(title);
	    SetModifiedFlag(TRUE);

		return TRUE;
	}
}

BOOL CAscDoc::UpdateContent( void )
{
    const char *oldname;
	CString title;

	{
		CWaitCursor WCursor;

	    if(!IsModified()) return TRUE;

		oldname = GetPathName();
		title = GetTitle();

		/* store modified file */
	    // PRESENTATION_NAME CAscDoc::OnSaveDocument(PresentationName);
		CAscDoc::OnSaveDocument(ContentName);

	    if(oldname[0]) SetPathName(oldname,FALSE);
		SetTitle(title);
	    SetModifiedFlag(TRUE);

		return TRUE;
	}
}

void CCryptDoc::OnCrypt3desCbc() 
{
	UpdateContent();
	SymmetricEncryption(IDS_CRYPT_TRIPLE_DES_CBC, SECUDE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnCrypt3desEcb() 
{
	UpdateContent();
	SymmetricEncryption(IDS_CRYPT_TRIPLE_DES_ECB, SECUDE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnCryptRc4() 
{
	UpdateContent();
	SymmetricEncryption(IDS_CRYPT_RC4, SECUDE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnCryptDesDescbc() 
{
	UpdateContent();
	SymmetricEncryption(IDS_CRYPT_DES_CBC, SECUDE_PROVIDER, ContentName, GetTitle());
}


void CCryptDoc::OnCaesarAuto() 
{
    UpdateContent();
    CaesarAuto(ContentName, GetTitle());
}

void CCryptDoc::OnVigenereAuto() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = ContentName;
	para->OldTitle = GetTitle();
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( VigenereAuto, ((void *) para) );
}

void CCryptDoc::OnVigenereAnalysisSchroedel()
{
	UpdateContent();
	// create the analysis dialog
	CDlgVigenereAnalysisSchroedel dlg(ContentName, GetTitle());
	// show the analysis dialog
	dlg.DoModal();
}

void CCryptDoc::OnHillPlain() 
{
    UpdateContent();
    HillPlain(ContentName, GetTitle());
}

void CCryptDoc::OnAddAuto() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = ContentName;
	para->OldTitle = GetTitle();
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( AddAuto, ((void *) para) );
}

void CCryptDoc::OnXorAuto() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = ContentName;
	para->OldTitle = GetTitle();
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( XorAuto, ((void *) para) );
}

void CCryptDoc::OnHill() 
{
    UpdateContent();
	Hill(ContentName, GetTitle());	
}

void CCryptDoc::OnZip() 
{
    UpdateContent();
    dozip(ContentName, GetTitle());
	
}

void CCryptDoc::OnUnzip() 
{
    UpdateContent();
    dounzip(ContentName, GetTitle());
}

// void CCryptDoc::OnCRYPTDelPse() {}

void CCryptDoc::OnCRYPTRsaDec() 
{
	UpdateContent();
	RsaDec(ContentName, GetTitle());
}

void CCryptDoc::OnCRYPTRsaEnc() 
{
	UpdateContent();
	RsaEnc(ContentName, GetTitle());
}

void CCryptDoc::OnCryptMono() 
{
	UpdateContent();
	Mono(ContentName, GetTitle());
}

void CCryptDoc::OnCryptSign() 
{
	UpdateContent();
	Sign(ContentName, GetTitle());
}

void CCryptDoc::OnCryptVerify() 
{
	UpdateContent();
	Verify(ContentName, GetTitle());
}

void CCryptDoc::OnCryptExtract() 
{
	UpdateContent();
//	extract(ContentName, GetTitle());

	SHOW_HOUR_GLASS
	CDlgExtractSignature dlgSigExt(ContentName, GetTitle());
	HIDE_HOUR_GLASS
	dlgSigExt.DoModal();
}

void CCryptDoc::OnAnalyzeSubst() 
{
    UpdateContent();
	// Überprüfung, ob Eingabedatei mindestens ein Zeichen enthält. 
	CFile datei(ContentName, CFile::modeRead);
	bool laenge_groesser_0 = FALSE;
	char c;
	while(datei.Read(&c,1) && ! laenge_groesser_0)
	{
		if ( (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) )
		{
			laenge_groesser_0 = TRUE;
		}
	}
	datei.Close();
	if (! laenge_groesser_0)
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		return;
	}
    UpdateContent();
	AnalyseMonoManual(ContentName, GetTitle());	
}

void CAscDoc::OnAuto() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM | CRYPT_ASCII;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( Autocorr, ((void *) para) );
}

void CHexDoc::OnAuto() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
//    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( Autocorr, ((void *) para) );
}

void CCryptDoc::OnFloating() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM | CRYPT_ASCII;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( FloatingEntropy, ((void *) para) );
}

void CCryptDoc::OnUpdateNeedSecude(CCmdUI* pCmdUI) 
{
    if(theApp.SecudeStatus == 2) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);
}

void CCryptDoc::OnUpdateNeedSecudeTicket(CCmdUI* pCmdUI) 
{
    if(theApp.SecudeStatus == 2) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);
}

void CCryptDoc::OnAnalyseDescbc() 
{
	SymCryptBruteForce( IDS_CRYPT_DES_CBC, SECUDE_PROVIDER, 64, 64 );
}

void CCryptDoc::OnAnalyseDesecb() 
{
	SymCryptBruteForce( IDS_CRYPT_DES_ECB, SECUDE_PROVIDER, 64, 64 );
}

void CCryptDoc::OnAnalyseIdea() 
{
	SymCryptBruteForce( IDS_CRYPT_IDEA, SECUDE_PROVIDER, 128, 128 );
}

void CCryptDoc::OnAnalyseRc2() 
{
	SymCryptBruteForce( IDS_CRYPT_RC2, SECUDE_PROVIDER, 8, 128, 8 );
}

void CCryptDoc::OnAnalyseRc4() 
{
	SymCryptBruteForce( IDS_CRYPT_RC4, SECUDE_PROVIDER, 8, 128, 8 );
}

void CCryptDoc::OnAnalyseTripledescbc() 
{
	SymCryptBruteForce( IDS_CRYPT_TRIPLE_DES_CBC, SECUDE_PROVIDER, 128, 128 );
}

void CCryptDoc::OnAnalyseTripledesecb() 
{
	SymCryptBruteForce( IDS_CRYPT_TRIPLE_DES_ECB, SECUDE_PROVIDER, 128, 128 );
}

void CCryptDoc::OnCryptAesMars() 
{
	UpdateContent();
	SymmetricEncryption(IDS_CRYPT_MARS, CORE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnCryptAesRc6() 
{
	UpdateContent();
	SymmetricEncryption(IDS_CRYPT_RC6, CORE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnCryptAesRijndael() 
{
	UpdateContent();
	SymmetricEncryption(IDS_CRYPT_RIJNDAEL, CORE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnCryptAesSerpent() 
{
	UpdateContent();
	SymmetricEncryption(IDS_CRYPT_SERPENT, CORE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnCryptAesTwofish() 
{
	UpdateContent();
	SymmetricEncryption(IDS_CRYPT_TWOFISH, CORE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnAnalyseAesMars() 
{
	SymCryptBruteForce( IDS_CRYPT_MARS, CORE_PROVIDER, 128, 256, 64 );
}

void CCryptDoc::OnAnalyseAesRc6() 
{
	SymCryptBruteForce( IDS_CRYPT_RC6, CORE_PROVIDER, 128, 256, 64 );
}

void CCryptDoc::OnAnalyseAesRijndael() 
{
	SymCryptBruteForce( IDS_CRYPT_RIJNDAEL, CORE_PROVIDER, 128, 256, 64 );
}

void CCryptDoc::OnAnalyseAesSerpent() 
{
	SymCryptBruteForce( IDS_CRYPT_SERPENT, CORE_PROVIDER, 128, 256, 64 );
}

void CCryptDoc::OnAnalyseAesTwofish() 
{
	SymCryptBruteForce( IDS_CRYPT_TWOFISH, CORE_PROVIDER, 128, 256, 64 );
}

#if 0
void CCryptDoc::OnToHex() 
{
	CAppDocument *NewDoc;
	char outfile[128];
	BOOL Modified;
	WINDOWPLACEMENT place;

	GetTmpName(outfile,"cry",".hex");

	CWnd* CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
	CWnd_hilf->GetWindowPlacement( &place );
	Modified = IsModified();
	OnSaveDocument(outfile);
	NewDoc = theApp.OpenDocumentFileNoMRU(outfile,csSchluessel);
	CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
	CWnd_hilf->SetWindowPlacement( &place );
	remove(outfile);
	NewDoc->SetTitle(GetTitle());
	NewDoc->CWndVaterFenster = CWndVaterFenster;
	NewDoc->hWndVaterFenster = hWndVaterFenster;
	NewDoc->SetModifiedFlag(Modified);
	OnCloseDocument();
}


void CCryptDoc::OnToTxt() 
 {
 	CAppDocument *NewDoc;
 	char outfile[128];
 	BOOL Modified;
 	WINDOWPLACEMENT place;
 	 
 	GetTmpName(outfile,"cry",".txt");
 	
 	CWnd* CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
 	CWnd_hilf->GetWindowPlacement( &place );
 	Modified = IsModified();
 	OnSaveDocument(outfile);
 
 	NewDoc = theApp.OpenDocumentFileNoMRU(outfile,csSchluessel);
 	CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
 	CWnd_hilf->SetWindowPlacement( &place );
 	remove(outfile);
 	NewDoc->SetTitle(GetTitle());
 	NewDoc->CWndVaterFenster = CWndVaterFenster;
 	NewDoc->hWndVaterFenster = hWndVaterFenster;
 	NewDoc->SetModifiedFlag(Modified);
 	OnCloseDocument();
}
#endif

void CCryptDoc::OnPlayfairBin()
{
    UpdateContent();
    PlayfairBin(ContentName, GetTitle());
}

void CCryptDoc::OnPlayfairAnalyse()
{
    UpdateContent();
    PlayfairAnalyse(ContentName, GetTitle());
}

void CCryptDoc::OnVitanyAnalyse()
{
	{
		struct stat *obj;
		obj = new (struct stat);
		obj->st_size;
		stat((const char*)ContentName,obj);
		int error = 0;
		if ( 500 > obj->st_size )
		{
			Message( IDS_VITANY_ERR_FILESIZE, MB_ICONSTOP );
			error = 1;
		}
		delete obj;
		if ( error )
			return;
	}

	CryptPar *para;
	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM | CRYPT_ASCII;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( Vitanycorr, ((void *) para) );
}

void CCryptDoc::OnPeriod()
{
    CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM | CRYPT_ASCII;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( Periode, ((void *) para) );

/*
	UpdateContent();
	class CRandomAnalysisTools ana(ContentName);
	ana.FindPeriod();
*/
  }

// void CCryptDoc::OnNotAvail() ??
// {
//	Message(IDS_STRING_EC_MSG_TODO_FOR_CRYPTOOL, MB_ICONINFORMATION);
// }

void CCryptDoc::OnHomophone() 
{
    UpdateContent();
    HomophoneAsc(ContentName, GetTitle());
}

void CCryptDoc::OnAnalyseNGram()
{
	UpdateContent();
	NGramAsc( ContentName, GetTitle());
}

void CCryptDoc::OnAnalyseNGramBin() 
{
	UpdateContent();
	NGramBin( ContentName, GetTitle());
}

void CCryptDoc::OnPermutation() 
{
    UpdateContent();
	Permutation(ContentName, GetTitle(), TRUE);
}

void CCryptDoc::OnAnalyseZufallstestsFrequencytest() 
{
	CStdioFile file;
	SHOW_HOUR_GLASS
	UpdateContent();
	file.Open(ContentName, CFile::modeRead);
	if(file.GetLength() < 16) 
	{
		file.Close();
		Message(IDS_STRING_TEST_KLEINE_DATEI, MB_ICONEXCLAMATION);
	}
	else
	{
		if ((file.GetLength()*8) < 10000) 
		{
			Message(IDS_STRING_TESTS_EMPFHAELUNG_FREQ_TEST, MB_ICONINFORMATION);
		}
		file.Close();
		Freq_Test test;
		CDlgFreqTest FREQT;
		FREQT.SetCurrentTest( &test );
		FREQT.init(ContentName, GetTitle());
		//sprintf(FREQT.tmpStr, "Frequency Test");
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TEST_FREQ, FREQT.tmpStr, STR_LAENGE_STRING_TABLE);	
		LoadString(AfxGetInstanceHandle(), IDS_STRING_CAPTATION_FREQUENCY_TEST, pc_str, STR_LAENGE_STRING_TABLE);
		int tempStringLength = strlen(pc_str) + strlen(GetTitle()) + 1;
		char *tempString = new char[tempStringLength];
		memset(tempString, 0, tempStringLength);
        sprintf(tempString, pc_str, GetTitle());
        FREQT.SetAlternativeWindowText(tempString);
		if ( FREQT.LoadAlphaList() )
			FREQT.DoModal();
		delete tempString;
	}
	HIDE_HOUR_GLASS
}

void CCryptDoc::OnAnalyseZufallstestsSerialtest() 
{
	CStdioFile file;
	SHOW_HOUR_GLASS
	UpdateContent();
	file.Open(ContentName, CFile::modeRead);

	if(file.GetLength() < 16) 
	{
		file.Close();
		Message(IDS_STRING_TEST_KLEINE_DATEI, MB_ICONEXCLAMATION);
	}
	else
	{
		file.Close();
		Serial_Test test;
		CDlgFreqTest SERT;
		SERT.SetCurrentTest( &test );
		SERT.init(ContentName, GetTitle());
		//sprintf(SERT.tmpStr, "Serial Test");
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TEST_SERIAL,SERT.tmpStr, STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(), IDS_STRING_CAPTATION_SERIAL_TEST, pc_str, STR_LAENGE_STRING_TABLE);
		int tempStringLength = strlen(pc_str) + strlen(GetTitle()) + 1;
		char *tempString = new char[tempStringLength];
		memset(tempString, 0, tempStringLength);
		sprintf(tempString, pc_str, GetTitle());
		SERT.SetAlternativeWindowText(tempString);
		if ( SERT.LoadAlphaList() )
			SERT.DoModal();
		delete tempString;
	}
	HIDE_HOUR_GLASS
}

void CCryptDoc::OnAnalyseZufallstestsRuns() 
{
	SHOW_HOUR_GLASS
	UpdateContent();
	CStdioFile file;
	file.Open(ContentName, CFile::modeRead);
	if(file.GetLength() < 16) 
	{
		file.Close();
		Message(IDS_STRING_TEST_KLEINE_DATEI, MB_ICONEXCLAMATION);
	}
	else
	{
		file.Close();
		CDlgRunsTest LRT;
		LRT.init(ContentName, GetTitle());

		LoadString(AfxGetInstanceHandle(), IDS_STRING_CAPTATION_RUNS_TESTS, pc_str, STR_LAENGE_STRING_TABLE);
		int tempStringLength = strlen(pc_str) + strlen(GetTitle()) + 1;
		char *tempString = new char[tempStringLength];
		memset(tempString, 0, tempStringLength);
		sprintf(tempString, pc_str, GetTitle());

		LRT.SetAlternativeWindowText( tempString );
		if ( LRT.LoadAlphaList() )
			LRT.DoModal();
		delete tempString;
	}
	HIDE_HOUR_GLASS
}

void CCryptDoc::OnAnalyseZufallstestsPokertest() 
{
	CStdioFile file;
	SHOW_HOUR_GLASS
	UpdateContent();
	file.Open(ContentName, CFile::modeRead);
	if(file.GetLength() < 16) 
	{
		file.Close();
		Message(IDS_STRING_TEST_KLEINE_DATEI, MB_ICONEXCLAMATION);
	}
	else
	{
		file.Close();
		Poker_Test test;
		CDlgFreqTest POKT;
		POKT.Set_Poker_Flag( TRUE );
		POKT.SetCurrentTest( &test );
		POKT.init(ContentName, GetTitle());
	//	sprintf(POKT.tmpStr, "Poker-Test");
		LoadString(AfxGetInstanceHandle(),IDS_STRING_TEST_POKER,POKT.tmpStr,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_CAPTATION_POKER_TEST,pc_str,STR_LAENGE_STRING_TABLE);
		int tempStringLength = strlen(pc_str) + strlen(GetTitle()) + 1;
		char *tempString = new char[tempStringLength];
		memset(tempString, 0, tempStringLength);
		sprintf(tempString, pc_str, GetTitle());
		
		POKT.SetAlternativeWindowText(tempString);
		if ( POKT.LoadAlphaList() )
			POKT.DoModal();
		delete tempString;
	}
	HIDE_HOUR_GLASS
}


void CCryptDoc::OnAnalyseZufallstestsFipspub1401() 
{
	CStdioFile file;
	char *str_size_fmt;

	SHOW_HOUR_GLASS
	UpdateContent();
	file.Open(ContentName, CFile::modeRead);
	if(file.GetLength() < 2500) 
	{
		str_size_fmt = itoa_fmt((__int64)file.GetLength());
		Message(IDS_STRING_TEST_FIPS_KLEINE_DATEI_2, MB_ICONEXCLAMATION, str_size_fmt);
		delete []str_size_fmt;
		file.Close();
	}
	else
	{
		if (file.GetLength() > 2500)
		{
			str_size_fmt = itoa_fmt((int)file.GetLength());
			Message(IDS_STRING_TEST_FIPS_KLEINE_DATEI, MB_ICONINFORMATION, str_size_fmt);
			delete []str_size_fmt;
		}
		file.Close();
		CDlgFIPSTest140_1 FIPS;
		FIPS.init(ContentName, GetTitle());

		LoadString(AfxGetInstanceHandle(),IDS_STRING_CAPTATION_FIPS_PUB,pc_str,STR_LAENGE_STRING_TABLE);
		int tempStringLength = strlen(pc_str) + strlen(GetTitle()) + 1;
		char *tempString = new char[tempStringLength];
		memset(tempString, 0, tempStringLength);
		sprintf(tempString, pc_str, GetTitle());
		FIPS.SetAlternativeWindowText(tempString);
		FIPS.DoModal();
		delete tempString;
	}
}


void CCryptDoc::OnAesSelfextract() 
{
    UpdateContent();
	CString str_m_Selfextract_EXE_Quoted = CString("\"") + CString(theApp.m_Selfextract_EXE) + CString("\"");
	_spawnl(_P_NOWAIT, theApp.m_Selfextract_EXE, str_m_Selfextract_EXE_Quoted, ContentName, NULL); 
	// FIXME: Interpret return value of _spawnl
}


void CCryptDoc::OnUpdateAesSelfextract(CCmdUI* pCmdUI) 
{
	if(theApp.m_Selfextract_EXE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}



void CCryptDoc::OnEinzelverfahrenHashwerteHashdemo() 
{
	UpdateContent();

	//ContentName ist eine globale Variable, die den Dateinamen der Temp-Datei enthält
	//GetTitle Titelüberschrift des aktuellen Dlgs (Bsp. "Unbenannt1")
	Hashdemo(ContentName,GetTitle());
}

void CCryptDoc::OnEinzelverfahrenHybridverfahrenHybridverschlsselung() 
{
	CDlgHybridEncryptionDemo hyb;
	UpdateContent();
	hyb.m_strBuffTitle = GetTitle();
	hyb.m_strPathSelDoc = ContentName;
	hyb.DoModal();
}


void CCryptDoc::OnEinzelverfahrenSignDoc() 
{
	UpdateContent();
	SignatureTutorial ( ContentName, GetTitle());
}


void CCryptDoc::OnEinzelverfahrenHybridverfahrenHybridentschlsselung() 
{
	UpdateContent();
	DecHyb( ContentName, GetTitle() );
}


// Diese Funktion wird aufgerufen, wenn der Benutzer ein bereits gegebenes Dokument asn1-decodieren will.
// Wird das Format erkannt, so wird sowohl ein asn1-dump als auch eine formatspezifische Ausgabe angezeigt.
// Wird das Format nicht erkannt, bleibt es bei der Ausgabe des asn1-dumps
void CCryptDoc::OnEinzelverfahrenAsn1decodieren() 
{
	// Dokumentinhalt aktualisieren
	UpdateContent();

	try
	{
		ASN1Decoder asndec( ContentName );
		
		// GÜLTIGE ASN1-STRUKTUR
		if(asndec.IsASN1Structure())
		{			
			// ASN1-DUMP
			char *filename = new char[CRYPTOOL_PATH_LENGTH];
			GetTmpName(filename, "cry", ".txt");
			asndec.StoreASN1Dump(filename);
			LoadString(AfxGetInstanceHandle(), IDS_ASN1_VALID_ASN1_FILE, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(NULL, pc_str, "CrypTool", MB_ICONINFORMATION);
			CAppDocument *NewDoc = theApp.OpenDocumentFileNoMRU(filename);
			
			// ZERTIFIKAT
			if(asndec.IsCertificate())
			{
				std::string pin = "NULL";
				GetTmpName(filename, "cry", ".txt");

				if(asndec.IsCertProtected())
				{
					CDlgASN1PSEPINPrompt dlg;
					if( dlg.DoModal() == IDOK ) pin = dlg.m_PIN;
					else return;
				}

				asndec.StoreCertDump(filename,pin);

				LoadString(AfxGetInstanceHandle(), IDS_ASN1_READY_TO_PRINT_CERTIFICATE, pc_str, STR_LAENGE_STRING_TABLE);
				MessageBox(NULL, pc_str, "CrypTool", MB_ICONINFORMATION);
							
				CAppDocument *NewDoc = theApp.OpenDocumentFileNoMRU(filename);
			}

			// FORMAT NICHT ERKANNT (UNBEKANNTE BZW NICHT IMPLEMENTIERTE ASN1-STRUKTUR)
			else
			{
				LoadString(AfxGetInstanceHandle(), IDS_ASN1_NOT_PROPERLY_RECOGNIZED, pc_str, STR_LAENGE_STRING_TABLE);
				MessageBox(NULL, pc_str, "CrypTool", MB_ICONWARNING);
				return;
			}
	
		}
		// KEINE GÜLTIGE ASN1-STRUKTUR
		else
		{
			LoadString(AfxGetInstanceHandle(), IDS_ASN1_NO_VALID_ASN1_FILE, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(NULL, pc_str, "CrypTool", MB_ICONWARNING);
			return;
		}
	}
	// *** FEHLERBEHANDLUNG ***
	catch(ASN1Error e)
	{
		if(e.GetErrorCode() == E_INVALID_FILENAME)
		{
			LoadString(AfxGetInstanceHandle(), IDS_ASN1_INVALID_FILENAME, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(NULL, pc_str, "CrypTool", MB_ICONWARNING);
			return;
		}

		if(e.GetErrorCode() == E_NO_VALID_CERTIFICATE_STRUCTURE)
		{
			LoadString(AfxGetInstanceHandle(), IDS_ASN1_INVALID_CERTIFICATE_STRUCTURE, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(NULL, pc_str, "CrypTool", MB_ICONWARNING);
			return;
		}

		if(e.GetErrorCode() == E_FILE_NOT_EXISTING)
		{
			LoadString(AfxGetInstanceHandle(), IDS_ASN1_FILE_NOT_EXISTING, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(NULL, pc_str, "CrypTool", MB_ICONWARNING);
			return;
		}

		if(e.GetErrorCode() == E_CERT_WRONG_PIN)
		{
			LoadString(AfxGetInstanceHandle(), IDS_ASN1_NO_VALID_PIN, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(NULL, pc_str, "CrypTool", MB_ICONWARNING);
			return;
		}
		
		if(e.GetErrorCode() == E_NO_VALID_ASN1_STRUCTURE || e.GetErrorCode() == E_IO_ERROR)
		{
			LoadString(AfxGetInstanceHandle(), IDS_ASN1_INTERNAL_ERROR, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(NULL, pc_str, "CrypTool", MB_ICONWARNING);
			return;
		}
		else
		{
			LoadString(AfxGetInstanceHandle(), IDS_ASN1_INTERNAL_ERROR, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(NULL, pc_str, "CrypTool", MB_ICONWARNING);
			return;
		}
	}
}

void CCryptDoc::OnSigattmodificdemo() 
{
	UpdateContent();

	CDlgSigAttModificDemo SAMD;
	SAMD.SetData(ContentName, GetTitle());
	SAMD.DoModal();
}

void CCryptDoc::OnSignaturAttack() 
{
	CDlgSignatureAttack S_A;
	S_A.DoModal();
}

// Den Dialog "Visualisierung eines Seitenkanalangriffs auf das
// Hybridverschlüsselungsverfahren" erstellen und anzeigen
void CCryptDoc::OnEinzelverfahrenSidechannelattackOnHybridencryption() 
{
	UpdateContent();

	CDlgSideChannelAttackVisualizationHE dlg;
	dlg.setEncryptedFile(ContentName);
	dlg.setInitFileTitle(GetTitle());
		
	dlg.DoModal();
}

void CCryptDoc::OnFileProperties() 
{
	UpdateContent();

	CString strView;
	this->GetDocTemplate()->GetDocString(strView, CDocTemplate::filterName);

	CDlgFileProperties DlgFileProperties;
	CString fName;
	fName = this->GetPathName();
	DlgFileProperties.copyFileInfos( ContentName, fName, 
									((CAppDocument*)this)->GetTitle(),
									((CAppDocument*)this)->csSchluessel, 
									((CAppDocument*)this)->iSchluesselTyp,
									strView);
	DlgFileProperties.DoModal();
}


void CCryptDoc::OnMessageauthenticationcode() 
{
	UpdateContent();
	CreateMac(ContentName, GetTitle());
}

void CCryptDoc::OnEncryptAdfgvx() 
{
	UpdateContent();
	class CDlgADFGVX dlg(ContentName, GetTitle());
	dlg.DoModal();
}

void CCryptDoc::OnAnalyseSymmclassicAdfgvx() 
{
	UpdateContent();
	//CDlgAdfgvxManual dlg = new CDlgAdfgvxManual(ContentName);
	class CDlgAdfgvxManual dlg(ContentName, GetTitle(), NULL);
	dlg.DoModal();
}

void CCryptDoc::OnCiphertextOnlySubstitution() 
{
    UpdateContent();

	// Überprüfung, ob Eingabedatei mindestens ein Zeichen enthält. 
	CFile datei(ContentName, CFile::modeRead);
	bool laenge_groesser_0 = FALSE;
	char c;
	while(datei.Read(&c,1) && ! laenge_groesser_0)
	{
		if ( (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) )
		{
			laenge_groesser_0 = TRUE;
		}
	}
	datei.Close();
	if (! laenge_groesser_0)
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		return;
	}


	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = ContentName;
	para->OldTitle = GetTitle();
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( AutoAnaSubst, ((void *) para) );	
}

void CCryptDoc::OnRot13caesarAsc() 
{
	UpdateContent();
	CDlgRot13Caesar Dlg;
	if ( Dlg.DoModal() != IDOK)
	{
		return;
	}
	SymbolArray text(AppConv);
	if ( 0 <= Rot13CaesarAscStart( text, ContentName ) ) // (0 <= ..) --> empty Ciphertext possible
		Rot13CaesarAscFinish(text, ContentName, Dlg.GetTheKey().GetBuffer(), Dlg.GetModeDecryption(), GetTitle(), Dlg.GetTypeEncryption(), Dlg.IsKeyOffsetZero());	
	else
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
}


void CCryptDoc::OnAnalysisRandom3dVisualization() 
{
    UpdateContent();

	char name[1024], title[1024];
	CFile f;

	GetTmpName(name,"cry",".ogl");
	f.Open(name, CFile::modeCreate | CFile::modeWrite );
	f.Write("OPENGL\n", 7);
	f.Write(ContentName, strlen(ContentName));
	f.Close();

	LoadString(AfxGetInstanceHandle(), IDS_TITLE_3D_VISUALISATION, pc_str, STR_LAENGE_STRING_TABLE);
	sprintf(title, pc_str, GetTitle());
    theApp.ThreadOpenDocumentFileNoMRU(name,title);
}


void CCryptDoc::OnGotoVater() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen

	// Sprung zum Fenster, sofern es noch geöffnet ist
	// if ( IsWindow(((CAppDocument*)m_pDocument)->hWndVaterFenster) )		// Hack for debug mode
	if ( IsWindow(((CAppDocument*)this)->hWndVaterFenster) )
	{
		((CMDIFrameWnd*)theApp.m_pMainWnd)->
			MDIActivate(((CAppDocument*)this)->CWndVaterFenster);
	//		MDIActivate(((CAppDocument*)m_pDocument)->CWndVaterFenster);	// Hack for debug mode
	}
}

void CCryptDoc::OnShowKey() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen

	CString Key = ((CAppDocument*)this)->csSchluessel;
	
	CString Title;
	Title=((CAppDocument*)this)->GetTitle();

	if ( Key.GetLength() >0 )
	{
		if ( ((CAppDocument*)this)->iSchluesselTyp == SCHLUESSEL_LINEAR )
		{
			CDlgShowKey AusgabeFenster;
			char CryptMethod[KEYDATA_HASHSTRING_LENGTH+1];
			if ( ExtractStrKeyType( CryptMethod, Title ) )
			{
				strcpy( AusgabeFenster.strTitle, CryptMethod );
				AusgabeFenster.m_Key = Key;
				AusgabeFenster.DoModal();
			}
			else
			{
				// ToDo: passende Fehlermeldung
			}
		}
		else if ( ((CAppDocument*)this)->iSchluesselTyp == SCHLUESSEL_QUADRATISCH )
		{
			// Hill Verfahren: 
			// Format des Schluessels: Zeilenweise, durch jeweils ein Leerzeichen getrennt
			// HILL_MAX_DIM=5: 5x5 hat also 25+4=29 Zeichen
			int p_keyend = Key.Find(HILLSTR_ALPHABETOFFSET);
			ASSERT(p_keyend > 0);
			if (p_keyend <= HILL_MAX_DIM*HILL_MAX_DIM+(HILL_MAX_DIM-1))
			{
				CDlgShowKeyHill5x5 AusgabeFenster;
				AusgabeFenster.SchluesselAnzeigen(Key);				
				// Es wird immer der Schluessel zum Verschluesseln angezeigt
				AusgabeFenster.m_decrypt = FALSE;
				AusgabeFenster.DoModal();
			}
			else
			{
				CDlgShowKeyHill10x10 AusgabeFenster;
				AusgabeFenster.SchluesselAnzeigen(Key);				
				// Es wird immer der Schluessel zum Verschluesseln angezeigt
				AusgabeFenster.m_decrypt = FALSE;
				AusgabeFenster.DoModal();
			}
		}
		else
		{
			ASSERT(false);
		}
	}
}

void CCryptDoc::OnSymclassicSolitaire() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	
	UpdateContent();
	CDlgSolitaire mySol(ContentName, NULL);
	mySol.DoModal();	
}

void CCryptDoc::OnEncryptionSimpleTranspositions()
{
	UpdateContent();
	CDlgSimpleTranspositions dlg(ContentName, GetTitle(), NULL);
	dlg.DoModal();
}

void CCryptDoc::OnAnalyseSymmclassicCiphertextolySolitaire() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	UpdateContent();
	CDlgSolitaireAnalyse mySolAnal(ContentName, GetTitle(), NULL);
	mySolAnal.DoModal();
}

void CCryptDoc::OnIndivproceduresBase64Encode()
{
    UpdateContent();
    dobase64enc(ContentName, GetTitle());
}

void CCryptDoc::OnIndivproceduresBase64Decode()
{
    UpdateContent();
    dobase64dec(ContentName, GetTitle());
}

void CCryptDoc::OnEncodeUu()
{
    UpdateContent();
	douuenc(ContentName, GetTitle());

}

void CCryptDoc::OnDecodeUu()
{
    UpdateContent();
	douudec(ContentName, GetTitle());
}

void CCryptDoc::OnHybridEccEnc()
{
    UpdateContent();
    ECCEnc(ContentName, GetTitle());
}

void CCryptDoc::OnHybridEccDec()
{
    UpdateContent();
    ECCDec(ContentName, GetTitle());
}

void CCryptDoc::OnCryptDESL()
{
	UpdateContent();
	SymmetricEncryption(IDS_CRYPT_DESL, CORE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnCryptDESX()
{
	UpdateContent();
	SymmetricEncryption(IDS_CRYPT_DESX, CORE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnCryptDESXL()
{
	UpdateContent();
	SymmetricEncryption(IDS_CRYPT_DESXL, CORE_PROVIDER, ContentName, GetTitle());
}

void CCryptDoc::OnAnalyseDESL() 
{
	SymCryptBruteForce( IDS_CRYPT_DESL, CORE_PROVIDER, 64, 64 );
}

void CCryptDoc::OnAnalyseDESX() 
{
	SymCryptBruteForce( IDS_CRYPT_DESX, CORE_PROVIDER, 192, 192 );
}

void CCryptDoc::OnAnalyseDESXL() 
{
	SymCryptBruteForce( IDS_CRYPT_DESXL, CORE_PROVIDER, 192, 192 );
}

void CCryptDoc::OnFormatTextDocument()
{
	CDlgFormatTextDocument dlg;
	if(dlg.DoModal() == IDOK) {
		// format the contents of the current document as desired 
		// and display the result in a new document
		UpdateContent();
		CString newDocumentText = dlg.format(ContentName);
		GetTmpName(ContentName, "cry", ".org");
		CFile outfile(ContentName, CFile::modeCreate|CFile::modeWrite);
		outfile.Write(newDocumentText.GetBuffer(), newDocumentText.GetLength());
		outfile.Close();
		theApp.OpenDocumentFileNoMRU(ContentName);
	}
}

void CCryptDoc::OnEditRepeat()
{
	theApp.findAndReplaceDialog.OnBnClickedButtonFind();
}

void CCryptDoc::OnUpdateEditRepeat(CCmdUI *pCmdUI)
{
	BOOL enable = theApp.findAndReplaceDialog.m_hWnd != 0 && theApp.findAndReplaceDialog.textFind.GetLength() != 0;
	pCmdUI->Enable(enable);
}

void CCryptDoc::OnKnownAnalysisSinglePermutation()
{
	CDlgAutomatedPermAnalysis dlg;
	UpdateContent();

	if ( dlg.setSourceFilename(ContentName) )
	{
		Message( IDS_PA_EMPTYREFFILE, MB_ICONSTOP );
		return;
	}
	if (IDOK == dlg.DoModal())
	{
		// DO SOMETHING???		
	}
}
