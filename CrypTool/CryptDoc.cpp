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
// CryptDoc.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include <fstream.h>
#include "FileTools.h"
#include "CryptDoc.h"
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

extern char *CaPseDatei, *CaPseVerzeichnis, *Pfad, *PseVerzeichnis;


UINT AESBrute(PVOID p);

/////////////////////////////////////////////////////////////////////////////
// CCryptDoc




IMPLEMENT_DYNCREATE(CCryptDoc, CPadDoc)

CCryptDoc::CCryptDoc()
{
	ContentName[0] = 0;
	// PRESENTATION_NAME PresentationName[0] = 0;
}

BOOL CCryptDoc::OnNewDocument()
{
	FILE *f;

	if (!CPadDoc::OnNewDocument())
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
/*  PRESENTATION_NAME
    GetTmpName(PresentationName,"cry",".txt");
	f = fopen(PresentationName,"wb");
	if (!f)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_COULD_NOT_OPEN_TMP_FILE,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_NOTE,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	fclose(f);
*/
	return TRUE;
}

CCryptDoc::~CCryptDoc()
{
}


BEGIN_MESSAGE_MAP(CCryptDoc, CPadDoc)
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
	ON_COMMAND(ID_VERNAM_BIN, OnVernamBin)
	ON_COMMAND(ID_CRYPT_3DES_CBC, OnCrypt3desCbc)
	ON_COMMAND(ID_CRYPT_3DES_ECB, OnCrypt3desEcb)
	ON_COMMAND(ID_CRYPT_RC4, OnCryptRc4)
	ON_COMMAND(ID_CRYPT_DES_DESCBC, OnCryptDesDescbc)
	ON_COMMAND(ID_CAESAR_AUTO, OnCaesarAuto)
	ON_COMMAND(ID_VIGENERE_AUTO, OnVigenereAuto)
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
	ON_COMMAND(ID_TOTXT, OnToTxt) 
	ON_COMMAND(ID_TOHEX, OnToHex) 
	ON_COMMAND(ID_ANALYSE_VITANY, OnVitanyAnalyse)
	ON_COMMAND(ID_ANALYSE_PERIOD, OnPeriod)
	ON_COMMAND(ID_HOMOPHONE_HEX, OnHomophoneHex)
	ON_COMMAND(ID_HOMOPHONE_ASC, OnHomophone)
	ON_COMMAND(ID_ANALYSE_NGRAM, OnAnalyseNGram)
	ON_COMMAND(ID_ANALYSE_NGRAM_BIN, OnAnalyseNGramBin)
	ON_COMMAND(ID_PERMUTATION_ASC, OnPermutationAsc)
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
	ON_COMMAND(ID_PERMUTATION_ASC, OnPermutationAsc)
	ON_COMMAND(ID_SIGNATUR_ATTACK, OnSignaturAttack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCryptDoc diagnostics

#ifdef _DEBUG
void CCryptDoc::AssertValid() const
{
	CPadDoc::AssertValid();
}

void CCryptDoc::Dump(CDumpContext& dc) const
{
	CPadDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCryptDoc serialization

void CCryptDoc::Serialize(CArchive& ar)
{
    CPadDoc::Serialize( ar );
}

/////////////////////////////////////////////////////////////////////////////
// CCryptDoc commands

void CCryptDoc::OnCloseDocument() 
{
    char // PRESENTATION_NAME name1[128], 
		 name2[128];

    // PRESENTATION_NAME strncpy(name1,PresentationName,sizeof(name1));
    strncpy(name2,ContentName,sizeof(name2));
	CPadDoc::OnCloseDocument();
    // PRESENTATION_NAME remove(name1);
    remove(name2);
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
    int r = FileCpy(ContentName,lpszPathName, 0x0FFFFF);
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

/* PRESENTATION_NAME
    if(!FileCpy(ContentName,lpszPathName,-1)) {
        remove(ContentName);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_COULD_NOT_OPEN_TMP_FILE,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_NOTE,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK | MB_ICONWARNING);
		return FALSE;
    }
*/
/* PRESENTATION_NAME
	if(!present(ContentName, PresentationName)) {
        remove(ContentName);
	    remove(PresentationName);
		return FALSE;
	}
*/
	if (!CPadDoc::OnOpenDocument( ContentName /* PRESENTATION_NAME PresentationName */)) {
        remove(ContentName);
        // PRESENTATION_NAME remove(PresentationName);
		return FALSE;
    }

	SetPathName(lpszPathName);
	return TRUE;
}

BOOL CCryptDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	POSITION pos = GetFirstViewPosition();

    if(IsModified()) CPadDoc::OnSaveDocument(ContentName);
    CPadDoc::OnSaveDocument(lpszPathName);
 	GetNextView(pos)->Invalidate();
 	UpdateAllViews(NULL);
    return TRUE;
}

BOOL CCryptDoc::present(const char *in, char *out)
{
	int r;

    GetTmpName(out,"cry",".txt");
    r = FileCpy(out, in, 0x0FFFFF);
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

    GetTmpName(out,"cry",".asc");
//    r = ASCDump(out, in, 5, 8, 0x0FFFFF);
    r = FileCpy(out, in, 0x0FFFFF);
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
	Crypt(ContentName, GetTitle(),128,128,1,1);
}

void CCryptDoc::OnCryptRc2() 
{
	UpdateContent();
	Crypt(ContentName, GetTitle(),8,128,8,7);
}

void CCryptDoc::OnCryptDesDesecb() 
{
    UpdateContent();
	Crypt(ContentName, GetTitle(),64,64,1,2);
}

void CCryptDoc::OnCryptHashMd5() 
{
    UpdateContent();
	hash(ContentName, GetTitle(),3);	
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

void CCryptDoc::OnCryptHashRipemd160() 
{
    UpdateContent();
	hash(ContentName, GetTitle(),6);
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

BOOL CAscDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
    /* store modified file */
    CPadDoc::OnSaveDocument(ContentName);
//    CPadDoc::OnSaveDocument(PresentationName);

    /* create user-file */
    FileCpy(lpszPathName, ContentName, -1);

	return TRUE;
}

BOOL CHexDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
    /* store modified file */
    CPadDoc::OnSaveDocument(ContentName);

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

    FileCpy(lpszPathName, ContentName, -1);
	
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

		CPadDoc::OnSaveDocument(ContentName);

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
	Crypt(ContentName, GetTitle(),128,128,1,4);
}

void CCryptDoc::OnCrypt3desEcb() 
{
	UpdateContent();
	Crypt(ContentName, GetTitle(),128,128,1,5);
}

void CCryptDoc::OnCryptRc4() 
{
	UpdateContent();
	Crypt(ContentName, GetTitle(),8,128,8,6);
}

void CCryptDoc::OnCryptDesDescbc() 
{
	UpdateContent();
	Crypt(ContentName, GetTitle(),64,64,1,3);
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

void CCryptDoc::OnCRYPTDelPse() {}

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


	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = ContentName;
	para->OldTitle = GetTitle();
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( AnaSubst, ((void *) para) );

//	UpdateContent();
//	AnaSubst(ContentName, GetTitle());	
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
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->key = (char *) malloc(sizeof(int));
	*(int *)para->key = 3;
	para->keylenstep = 1; 
	para->keylenmin = para->keylenmax = 64;
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( Brute, ((void *) para) );

//	UpdateContent();
//	Brute(ContentName, GetTitle(),64,3);
}

void CCryptDoc::OnAnalyseDesecb() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->key = (char *) malloc(sizeof(int));
	*(int *)para->key = 2;
	para->keylenstep = 1; 
	para->keylenmin = para->keylenmax = 64;
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( Brute, ((void *) para) );

//  UpdateContent();
//	Brute(ContentName, GetTitle(),64,2);
}

void CCryptDoc::OnAnalyseIdea() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->key = (char *) malloc(sizeof(int));
	*(int *)para->key = 1;
	para->keylenstep = 1; 
	para->keylenmin = para->keylenmax = 128;
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( Brute, ((void *) para) );

//  UpdateContent();
//	Brute(ContentName, GetTitle(),128,1);
}

void CCryptDoc::OnAnalyseRc2() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->key = (char *) malloc(sizeof(int));
	*(int *)para->key = 7;
	para->keylenstep = 8; 
	para->keylenmin = 8; 
	para->keylenmax = 128;
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( Brute, ((void *) para) );

//	UpdateContent();
//	Brute(ContentName, GetTitle(),128,7);
}

void CCryptDoc::OnAnalyseRc4() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->key = (char *) malloc(sizeof(int));
	*(int *)para->key = 6;
	para->keylenstep = 8; 
	para->keylenmin = 8; 
	para->keylenmax = 128;
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( Brute, ((void *) para) );

//	UpdateContent();
//	Brute(ContentName, GetTitle(),128,6);
}

void CCryptDoc::OnAnalyseTripledescbc() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->key = (char *) malloc(sizeof(int));
	*(int *)para->key = 4;
	para->keylenstep = 1; 
	para->keylenmin = para->keylenmax = 128;
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( Brute, ((void *) para) );

//	UpdateContent();
//	Brute(ContentName, GetTitle(),128,4);
}

void CCryptDoc::OnAnalyseTripledesecb() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->key = (char *) malloc(sizeof(int));
	*(int *)para->key = 5;
	para->keylenstep = 1; 
	para->keylenmin = para->keylenmax = 128;
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( Brute, ((void *) para) );

//	UpdateContent();
//	Brute(ContentName, GetTitle(),128,5);
}

void CCryptDoc::OnCryptAesMars() 
{
	UpdateContent();
	AESCrypt(ContentName, GetTitle(),1);
}

void CCryptDoc::OnCryptAesRc6() 
{
	UpdateContent();
	AESCrypt(ContentName, GetTitle(),2);
}

void CCryptDoc::OnCryptAesRijndael() 
{
	UpdateContent();
	AESCrypt(ContentName, GetTitle(),3);
}

void CCryptDoc::OnCryptAesSerpent() 
{
	UpdateContent();
	AESCrypt(ContentName, GetTitle(),4);
}

void CCryptDoc::OnCryptAesTwofish() 
{
	UpdateContent();
	AESCrypt(ContentName, GetTitle(),5);
}

void CCryptDoc::OnAnalyseAesMars() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->key = (char *) malloc(sizeof(int));
	*(int *)para->key = 1;
	para->keylenstep = 64; 
	para->keylenmin = 128;
	para->keylenmax = 256;
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( AESBrute, ((void *) para) );
}

void CCryptDoc::OnAnalyseAesRc6() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->key = (char *) malloc(sizeof(int));
	*(int *)para->key = 2;
	para->keylenstep = 64; 
	para->keylenmin = 128;
	para->keylenmax = 256;
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( AESBrute, ((void *) para) );
}

void CCryptDoc::OnAnalyseAesRijndael() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->key = (char *) malloc(sizeof(int));
	*(int *)para->key = 3;
	para->keylenstep = 64; 
	para->keylenmin = 128;
	para->keylenmax = 256;
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( AESBrute, ((void *) para) );
}

void CCryptDoc::OnAnalyseAesSerpent() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->key = (char *) malloc(sizeof(int));
	*(int *)para->key = 4;
	para->keylenstep = 64; 
	para->keylenmin = 128;
	para->keylenmax = 256;
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( AESBrute, ((void *) para) );
}

void CCryptDoc::OnAnalyseAesTwofish() 
{
	CryptPar *para;

	para = (CryptPar *) malloc(sizeof(CryptPar));
    UpdateContent();
	memset(para,0,sizeof(CryptPar));
	para->infile = strdup(ContentName);
	para->OldTitle = strdup(GetTitle());
	para->key = (char *) malloc(sizeof(int));
	*(int *)para->key = 5;
	para->keylenstep = 64; 
	para->keylenmin = 128;
	para->keylenmax = 256;
	para->flags = CRYPT_DO_WAIT_CURSOR | CRYPT_DISPLAY_BG | CRYPT_DO_PROGRESS | CRYPT_FREE_MEM;
	theApp.OpenBGFlag = 1;
    AfxBeginThread( AESBrute, ((void *) para) );
}

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
	char outfile[128], c;
	BOOL Modified;
	WINDOWPLACEMENT place;
	FILE *in;

	GetTmpName(outfile,"cry",".txt");
	
	CWnd* CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
	CWnd_hilf->GetWindowPlacement( &place );
	Modified = IsModified();
	OnSaveDocument(outfile);

	// Test auf abschließende Nullzeichen
	in = fopen(outfile,"rb");
	fseek(in, -1, SEEK_END);
	fread(&c, 1, 1, in);
	fclose(in);
	if(c==0) { // abschließende Null gefunden --> Benutzer warnen
		if(IDYES != AfxMessageBox (IDS_STRING_CUT_NULLS, MB_YESNO | MB_ICONQUESTION))
			return;
	}

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

void CCryptDoc::OnNotAvail() 
{
	Message(IDS_STRING_EC_MSG_TODO_FOR_CRYPTOOL, MB_ICONINFORMATION);
}

void CCryptDoc::OnHomophone() 
{
    UpdateContent();
    HomophoneAsc(ContentName, GetTitle());
}

void CCryptDoc::OnHomophoneHex()
{
    UpdateContent();
    HomophoneHex(ContentName, GetTitle());
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

// rich text edit
BOOL CCryptDoc::IsModified()
{
	return ((CAppEditView*)m_viewList.GetHead())->GetRichEditCtrl().GetModify();
}

void CCryptDoc::SetModifiedFlag(BOOL bModified)
{
	((CAppEditView*)m_viewList.GetHead())->GetRichEditCtrl().SetModify(bModified);
}
//

void CCryptDoc::OnPermutationAsc() 
{
    UpdateContent();
    PermutationAsc(ContentName, GetTitle());
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
		sprintf(FREQT.tmpStr, "Frequency Test");
		LoadString(AfxGetInstanceHandle(), IDS_STRING_CAPTATION_FREQUENCY_TEST, pc_str, STR_LAENGE_STRING_TABLE);
		char tmpstr[127];
		sprintf(tmpstr, pc_str, GetTitle());

		FREQT.SetAlternativeWindowText( tmpstr );
		if ( FREQT.LoadAlphaList() )
			FREQT.DoModal();
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
		sprintf(SERT.tmpStr, "Serial Test");

		LoadString(AfxGetInstanceHandle(), IDS_STRING_CAPTATION_SERIAL_TEST, pc_str, STR_LAENGE_STRING_TABLE);
		char tmpstr[127];
		sprintf(tmpstr, pc_str, GetTitle());
		SERT.SetAlternativeWindowText(tmpstr);
		if ( SERT.LoadAlphaList() )
			SERT.DoModal();
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
		char tmpstr[127];
		sprintf(tmpstr, pc_str, GetTitle());

		LRT.SetAlternativeWindowText( tmpstr );
		if ( LRT.LoadAlphaList() )
			LRT.DoModal();
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
		sprintf(POKT.tmpStr, "Poker Test");

		LoadString(AfxGetInstanceHandle(),IDS_STRING_CAPTATION_POKER_TEST,pc_str,STR_LAENGE_STRING_TABLE);
		char tmpStr[256];
		sprintf( tmpStr, pc_str, GetTitle());
		
		POKT.SetAlternativeWindowText(tmpStr);
		if ( POKT.LoadAlphaList() )
			POKT.DoModal();
	}
	HIDE_HOUR_GLASS
}


void CCryptDoc::OnAnalyseZufallstestsFipspub1401() 
{
	CStdioFile file;
	SHOW_HOUR_GLASS
	UpdateContent();
	file.Open(ContentName, CFile::modeRead);
	if(file.GetLength() < 2500) 
	{
		Message(IDS_STRING_TEST_FIPS_KLEINE_DATEI_2, MB_ICONINFORMATION,
			    file.GetLength(), ContentName, true);
		file.Close();
	}
	else
	{
		if (file.GetLength() > 2500)
		{
			Message(IDS_STRING_TEST_FIPS_KLEINE_DATEI, MB_ICONINFORMATION, 
				    file.GetLength(), ContentName, true);
		}
		file.Close();
		CDlgFIPSTest140_1 FIPS;
		FIPS.init(ContentName, GetTitle());

		LoadString(AfxGetInstanceHandle(),IDS_STRING_CAPTATION_FIPS_PUB,pc_str,STR_LAENGE_STRING_TABLE);
		char tmpStr[256];
		sprintf( tmpStr, pc_str, GetTitle());
		FIPS.SetAlternativeWindowText(tmpStr);

		FIPS.DoModal();
	}
}

void CCryptDoc::OnAesSelfextract() 
{
    UpdateContent();
	_spawnl(_P_NOWAIT, theApp.m_Selfextract_EXE, theApp.m_Selfextract_EXE,
		ContentName, NULL);
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
