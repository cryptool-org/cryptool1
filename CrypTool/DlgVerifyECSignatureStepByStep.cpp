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


// DlgSignVerifSteps.cpp: Implementierungsdatei
//
//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 2000
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgVerifyECSignatureStepByStep.h"
#include "CrypToolTools.h"
#include "FileTools.h"
#include "s_prng.h"
#include "s_ecconv.h"
#include "ECsecude.h"
#include "DialogeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgVerifyECSignatureStepByStep 


CDlgVerifyECSignatureStepByStep::CDlgVerifyECSignatureStepByStep(OctetString *msgOcts, bool msgFromFile, CString fname,\
									   EcDomParam_ac_ptr dp_ac,\
									   L_NUMBER *c_in, L_NUMBER *d_in, int signlength,\
									   char *sigalg_id, char *hashalg_id,\
									   CString UserKeyId, CString firstname, CString name,\
									   CString cID, CString cInfo,\
									   BOOL duration,\
									   CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVerifyECSignatureStepByStep::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVerifyECSignatureStepByStep)
	m_TextMessage = _T("");
	m_TextSign = _T("");
	m_DataDisplay = _T("");
	m_TextVerifSteps = _T("");
	m_MsgHexDump = _T("");
	m_SignHexDump = _T("");
	m_Step = _T("");
	//}}AFX_DATA_INIT

	messageOcts = msgOcts;
	messageFromFile = msgFromFile;
	filename = fname;
	DomParamAc = dp_ac;
	c = c_in;
	d = d_in;
	SignLength = signlength;
	SigAlg = sigalg_id;
	HashAlg = hashalg_id;

	UserKeyFile = UserKeyId;
	Firstname = firstname;
	Name = name;
	
	curveID = cID;
	curveInfo = cInfo;

	showDuration = duration;

	base = 10;
	hexdumpCols = 14;

	maxsteps = -1;

	inttoln(-1, NrVerifData.P.x);
	inttoln(-1, NrVerifData.P.y);
	inttoln(-1, NrVerifData.i);
	inttoln(-1, NrVerifData.f);
	NrVerifData.l = 0;
	inttoln(-1, NrVerifData.g);
	
	DsaVerifData.l = 0;
	inttoln(-1, DsaVerifData.f);
	inttoln(-1, DsaVerifData.h);
	inttoln(-1, DsaVerifData.h1);
	inttoln(-1, DsaVerifData.h2);
	inttoln(-1, DsaVerifData.P.x);
	inttoln(-1, DsaVerifData.P.y);
	inttoln(-1, DsaVerifData.i);
	inttoln(-1, DsaVerifData.c1);
}


void CDlgVerifyECSignatureStepByStep::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVerifyECSignatureStepByStep)
	DDX_Control(pDX, IDOK, m_OkButtonCtrl);
	DDX_Control(pDX, IDC_RADIO4, m_RadioOctets);
	DDX_Control(pDX, IDC_RADIO3, m_RadioHexadezimal);
	DDX_Control(pDX, IDC_RADIO2, m_RadioDezimal);
	DDX_Control(pDX, IDC_RADIO1, m_RadioOktal);
	DDX_Control(pDX, IDC_EDIT7, m_StepCtrl);
	DDX_Control(pDX, IDC_EDIT4, m_SignHexDumpCtrl);
	DDX_Control(pDX, IDC_EDIT2, m_MsgHexDumpCtrl);
	DDX_Control(pDX, IDC_EDIT5, m_TextVerifStepsCtrl);
	DDX_Control(pDX, IDC_EDIT6, m_DataDisplayCtrl);
	DDX_Control(pDX, IDC_EDIT3, m_TextSignCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_TextMessageCtrl);
	DDX_Control(pDX, IDC_BUTTON_CONTINUE, m_ContinueButtonCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_TextMessage);
	DDX_Text(pDX, IDC_EDIT3, m_TextSign);
	DDX_Text(pDX, IDC_EDIT6, m_DataDisplay);
	DDX_Text(pDX, IDC_EDIT5, m_TextVerifSteps);
	DDX_Text(pDX, IDC_EDIT2, m_MsgHexDump);
	DDX_Text(pDX, IDC_EDIT4, m_SignHexDump);
	DDX_Text(pDX, IDC_EDIT7, m_Step);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVerifyECSignatureStepByStep, CDialog)
	//{{AFX_MSG_MAP(CDlgVerifyECSignatureStepByStep)
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE, OnButtonContinue)
	ON_BN_CLICKED(IDC_RADIO1, OnRadioOktal)
	ON_BN_CLICKED(IDC_RADIO2, OnRadioDezimal)
	ON_BN_CLICKED(IDC_RADIO3, OnRadioHexadezimal)
	ON_BN_CLICKED(IDC_RADIO4, OnRadioOctets)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Eigene Member Funktionen

int CDlgVerifyECSignatureStepByStep::ecssa_sign_verif_op_ac( /* in */ L_NUMBER *c,
			      L_NUMBER *d,
			      OctetString *M,
			      EcDomParam_ac_ptr Key,
			      char *sign_primitiv_id, /* "ECSP-DSA" or "ECSP-NR" */
			      char *hash_id) /* select hash_id for emsa1: "SHA-1" or "RIPEMD-160" */
{
	unsigned int l;
	L_NUMBER f[MAXLGTH];

	/*if (validate_pub_key_dompar_ac(Key)) return 1;*/ /* validation of public key and its associated set of domain
											parameters failed! */

	if (strcmp(sign_primitiv_id, "ECSP-NR") == 0){
		if (ecFp_ecvp_nr_ac(c, d, Key->pubKey, Key->E, Key->G, Key->r, f)) return -3; /* error */
		l = SECUDE(lngtouse)(Key->r); /* l = (length of r in bits)-1 */

		NrVerifData.l = l; // Zwischenwert speichern

		return emsa1_verfication_operation(f,M,l,hash_id);
	}

	if (strcmp(sign_primitiv_id, "ECSP-DSA") == 0){
		l = SECUDE(lngtouse)(Key->r)+1; /* l = (length of r in bits) */

		DsaVerifData.l = l; // Zwischenwert speichern

		int fret = emsa1_encoding_operation(f, M, l, hash_id);

		if (fret) return -4; // calculate f
		
		trans(f, DsaVerifData.f); // Zwischenwert speichern

		return ecFp_ecvp_dsa_ac(c, d, Key->pubKey, Key->E, Key->G, Key->r, f);
	}

	return (-5); /* error: function doesn't anything */
}

int CDlgVerifyECSignatureStepByStep::emsa1_encoding_operation(/*out*/ L_NUMBER *f,
		             /*in   */ OctetString *M,
		                         unsigned int l,
		                         char *hash_id) /* "SHA-1" or "RIPEMD-160" */
{	
	/* I do not check if the length of M is greater than the length
	   limitation: 2^(61)-1 octets for SHA-1 or RIPEMD-160. I assume 
	   that the length of M is not that big.
	*/
	
	int n;
	int higher_bits;
	unsigned char bitmask = 255;
	
	BitString bitstr_hash;
	
	OctetString hash;
	hash.noctets = 0;
		
	hash.octets = (char*)malloc(20+1); /* 160-bits (20 bytes) */
	if (!hash.octets) return (-1); /* error: memory allocation failed */ 

	if (strcmp(hash_id, "SHA-1") == 0)
	{
		SECUDE(sec_hash_all)(M, &hash, SECUDE_DATA_PTR(sha1_aid), NULL);
	}
	else if (strcmp(hash_id, "RIPEMD-160") == 0)
	{
		SECUDE(sec_hash_all)(M, &hash, SECUDE_DATA_PTR(ripemd160_aid), NULL);
	}
	else 
	{
		free (hash.octets);
		return (-2); /* error: the selected Hash Algorithm is not supported */
	}
		
	if (l < (8*hash.noctets))
	{
		bitstr_hash = *(SECUDE(aux_OString2BString)(&hash));

		/* The 160-bits (20 bytes) representing Hash(M) are stored in the char-field:
		   bitstr_hash.bits[0], bitstr_hash.bits[0], ..., bitstr_hash.bits[20]
		   where bitstr_hash.bits[20] = NULL is the string-termination.
		   bitstr_hash.bits[0] is the char containing the most significant byte */
		
		/* Keep the l most significant bits (MSB) of Hash(M) = hash */

		n = (int) ceil(l/8.0); /* the first n char's of bitstr_bits* contain the l MSB's */
		bitstr_hash.bits[n] = (char) NULL; /* cut off the rest */

		/* if n < 20 :
		   I don't free the memory occupied by bitstr_hash.bits[n+1] ... bitstr_hash.bits[20] */

		higher_bits = l%8; /* keep the (l mod 8) higher bits of bitstr_hash.bits[n-1], that means:       */
		if (higher_bits)   /* set the 8-(l mod 8) less significant bits in bitstr_hash.bits[n-1] to zero */
			(bitstr_hash.bits[n-1] = bitstr_hash.bits[n-1] & (bitmask << ((unsigned char) 8-(higher_bits))));
		bitstr_hash.nbits = l; /* bitstr_hash contains now l bits */

		SECUDE(aux_BitString2LN2)(f, &bitstr_hash); /* f is the message representative */
		return 0;
	}
	else
	{
		/* convert the octet hash into the L_NUMBER f */

		//if (string_to_ln(strcat("0", hash.octets), f)) return (-2); /* if error then return -2 */
		SECUDE(aux_OctetString2LN2)(f, &hash); /* f is the message representative */
		return 0;
	}
}

int CDlgVerifyECSignatureStepByStep::emsa1_verfication_operation(/* in */ L_NUMBER *f,
			           OctetString *M,
			           unsigned int l,
			           char *hash_id) /* "SHA-1" or "RIPEMD-160" */
{
	L_NUMBER g[MAXLGTH];

	if (emsa1_encoding_operation(g, M, l, hash_id)) return (-1); /* error executing emsa1_encoding_operation */
	
	trans(g, NrVerifData.g); // Zwischenwert speichern

	if (SECUDE(comp)(g, f) == 0) return 0; /* f is a correct representative of M */
	return -2; /* f is an invalid representative of M */

}

/**********************************************************************************************************************
/* ECVP-DSA (IEEE 1363, 7.2.8)	for prime fields			ecFp_ecvp_dsa_ac()
/**********************************************************************************************************************/
int CDlgVerifyECSignatureStepByStep::ecFp_ecvp_dsa_ac( L_NUMBER *c, L_NUMBER *d, ecFp_point_ac_srcptr W, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G, L_NUMBER *r,L_NUMBER *f)
{
	L_NUMBER h[MAXLGTH],h1[MAXLGTH],h2[MAXLGTH];
	ecFp_point_ac_destptr P, temp_point;

	DsaVerifData.rangecheckfailed = 1; // Zwischenschritt speichern

	if (c[0]== 0) return (-1); /*signature verification failed*/
	if (d[0]== 0) return (-1); /*signature verification failed*/
	if ( SECUDE(comp)(c,r) >= 0) return(-1); /*signature verification failed*/
	if ( SECUDE(comp)(d,r) >= 0) return (-1); /*signature verification failed*/

	DsaVerifData.rangecheckfailed = 0; // Zwischenschritt speichern

	P=ecFp_point_init_ac;
	if (P==NULL) return (-2); /*point allocation error*/
	temp_point=ecFp_point_init_ac;
	if (temp_point==NULL){
		ecFp_point_clear_ac(P);
		return (-2); /*point allocation error*/
	}
	inttoln(1,h1);
	SECUDE(mdiv)(h1,d,h,r);  /* h=1/d */

	trans (h, DsaVerifData.h); // Zwischenschritt speichern

	SECUDE(mmult)(h,f,h1,r); /* h1=fh mod r */

	trans (h1, DsaVerifData.h1); // Zwischenschritt speichern

	SECUDE(mmult)(h,c,h2,r); /* h2=ch mod r */

	trans (h2, DsaVerifData.h2); // Zwischenschritt speichern

	ecFp_mult_ac(P,  E,  h1,  G);
	ecFp_mult_ac(temp_point,  E,  h2,  W);
	ecFp_add_ac(P, E, P, temp_point);

	trans(P->x, DsaVerifData.P.x); // Zwischenwert speichern
	trans(P->y, DsaVerifData.P.y); // Zwischenwert speichern
	DsaVerifData.P.infinity = P->infinity; // Zwischenwert speichern

	trans(P->x, DsaVerifData.i); // Zwischenwert speichern

	if ((P->infinity)!=0){
		ecFp_point_clear_ac(P);
		ecFp_point_clear_ac(temp_point);
		return (-1); /*signature verification failed*/
	}
	SECUDE(div)(P->x,r,h1,h); /* h = P->x (mod r) */

	trans(h, DsaVerifData.c1); // Zwischenwert speichern

	ecFp_point_clear_ac(P);
	ecFp_point_clear_ac(temp_point);
	if ( (SECUDE(comp)(c,h)) != 0 ) return (-1); /*signature verification failed*/
	else return 0;	/*signature verification successful*/
}

/*********************************************************************************************************************
/* ECVP-NR (IEEE 1363, 7.2.6) for prime fields		(affine coordinates)			ecFp_ecvp_nr_ac()
/**********************************************************************************************************************/

int CDlgVerifyECSignatureStepByStep::ecFp_ecvp_nr_ac(L_NUMBER *c, L_NUMBER *d, ecFp_point_ac_srcptr W, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G,L_NUMBER *r, L_NUMBER *f)
{
	L_NUMBER h[MAXLGTH];
	ecFp_point_ac_destptr P,temp_point;
	L_NUMBER one[MAXLGTH];
	L_NUMBER zero[MAXLGTH];
	inttoln(1,one);
	inttoln(0,zero);

	NrVerifData.rangecheckfailed = 1; // Zwischenschritt speichern

	if (c[0]==0) return 1; /*invalid signature*/
	if (d[0]==0) return 1; /*invalid signature*/
	if ( (SECUDE(comp)(c,one)) < 0 ) return 1; /*invalid signature*/
	if ( (SECUDE(comp)(c,r)) >= 0) return 1; /*invalid signature*/
	if ( (SECUDE(comp)(d,zero)) < 0 ) return 1; /*invalid signature*/
	if ( (SECUDE(comp)(d,r)) >= 0) return 1; /*invalid signature*/

	NrVerifData.rangecheckfailed = 0; // Zwischenschritt speichern

	P=ecFp_point_init_ac;
	if (P==NULL) return (-1);/*point allocation error*/
	temp_point=ecFp_point_init_ac;
	if (temp_point==NULL)
	{
		ecFp_point_clear_ac(P);
		return -1; /*point allocation error*/
	}

	P->infinity = 0;
	temp_point->infinity = 0;

	ecFp_mult_ac(P,  E,  d,  G);
	ecFp_mult_ac(temp_point,  E,  c,  W);
	ecFp_add_ac(P, E, P, temp_point);

	trans(P->x, NrVerifData.P.x); // Zwischenwert speichern
	trans(P->y, NrVerifData.P.y); // Zwischenwert speichern
	NrVerifData.P.infinity = P->infinity; // Zwischenwert speichern

	if ((P->infinity)!=0){
		ecFp_point_clear_ac(P);
		ecFp_point_clear_ac(temp_point);
		return 1; /*invalid signature*/
	}

	trans(P->x,h);

	trans(P->x, NrVerifData.i); // Zwischenwert speichern

	SECUDE(msub)(c,h,f,r);

	trans(f, NrVerifData.f); // Zwischenwert speichern

	ecFp_point_clear_ac(P);
	ecFp_point_clear_ac(temp_point);
	return 0;  
	/* compare f to the hash value of the message to find out if
	   the signature is valid*/
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgVerifyECSignatureStepByStep 

BOOL CDlgVerifyECSignatureStepByStep::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	LOGFONT LogFont;
	char DefaultFontName[32];
	LONG defaultFontWeight;
	CFont *defaultFont = m_ContinueButtonCtrl.GetFont();
	defaultFont->GetLogFont( &LogFont ); // Default Systemschrift ermitteln
	strncpy(DefaultFontName, LogFont.lfFaceName, 32); // Default Wert sichern
	defaultFontWeight = LogFont.lfWeight; // Default Wert sichern
	LogFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	m_Font.CreateFontIndirect( &LogFont ); // Font initialisieren
	m_TextMessageCtrl.SetFont(&m_Font);
	m_TextSignCtrl.SetFont(&m_Font);
	m_TextVerifStepsCtrl.SetFont(&m_Font);
	m_StepCtrl.SetFont(&m_Font);
	LogFont.lfWeight = defaultFontWeight; // Auf default Wert zurückstellen
	strncpy(LogFont.lfFaceName, "Courier", 32); // Auf Courier umstellen	
	m_Font2.CreateFontIndirect( &LogFont ); // Font2 initialisieren
	//strncpy(LogFont.lfFaceName, DefaultFontStyle, 32);

	m_MsgHexDumpCtrl.SetFont(&m_Font2);
	m_SignHexDumpCtrl.SetFont(&m_Font2);
	m_DataDisplayCtrl.SetFont(&m_Font2);

	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNED_MESSAGE,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextMessage = (CString) pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextSign = (CString) pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE_VERIFICATION_STEP_BY_STEP,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextVerifSteps = (CString) pc_str;

	UpdateData(FALSE);

	/*
	if (messageFromFile == true)
	{
		// Die signierte Nachricht ist zu gross und passt nicht komplett
		// in ein CEdit Feld. Es wird lediglich ein erster Teil der Nachricht dargestellt
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNED_MESSAGE_FIRST_PART,pc_str,STR_LAENGE_STRING_TABLE);
		m_TextMsg = (CString) pc_str;
	}
	*/

	int srcSize;
	int destSize;
	int err;

	// Signierte Nachricht ausgeben
	if (messageOcts->noctets != 0)
	{
		// Nachricht ist kein leerer String
		srcSize = messageOcts->noctets;
		destSize = ((srcSize+hexdumpCols-1)/hexdumpCols)*(11+hexdumpCols*4)-hexdumpCols+(srcSize%hexdumpCols)+1;

		char *msgdata = (char *) malloc(destSize+1);

		err = HexDumpMem(msgdata, destSize, (unsigned char *) messageOcts->octets, srcSize, hexdumpCols);
		if (err == 0)
		{
			// Fehler
			return TRUE;
		}
		CString mData(msgdata);
		m_MsgHexDump = mData;
		free(msgdata);
	}
	UpdateData(FALSE);

	CheckRadioButton (IDC_RADIO1, IDC_RADIO4, IDC_RADIO2);
	UpdateData(TRUE);
	base = 10; // Signatur als Dezimalzahlen darstellen

	UpdateSigEditBox();

	int fret = ecssa_sign_verif_op_ac( c, d, messageOcts, DomParamAc, SigAlg, HashAlg);
	if (fret)
	{
		// sig fehlerhaft
	}

	step = 0;
	UpdateDataDisplay();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

int CDlgVerifyECSignatureStepByStep::UpdateSigEditBox()
{
	int err;

	char *strC;
	char *strD;

	int srcSize;
	int destSize;

	if ( (base == 8) || (base == 10) || (base == 16) )
	{
		// wandele c und d (beides L_NUMBERs) nach Zahlen in Basis "base"

		err = ln_to_string (c, &strC, base); // Dezimalsystem
		if (err)
		{
			// Fehler.
			return -1;
		}
		err = ln_to_string (d, &strD, base); // Dezimalsystem
		if (err)
		{
			// Fehler.
			free(strC);
			return -1;
		}

		m_SignHexDump = ((CString)"\r\nc = ")+((CString)strC)+((CString)" ");
		m_SignHexDump = m_SignHexDump+((CString)"\r\n\r\nd = ")+((CString)strD)+((CString)" ");
		UpdateData(FALSE);

		free(strC);
		free(strD);
	}
	else
	{
		// Signatur als Octets darstellen

		OctetString *cOcts = theApp.SecudeLib.aux_LN2OctetString(c, (theApp.SecudeLib.lngtouse(c)+7)/8);
		if (cOcts == NULL)
		{
			// Fehler
			return -2;
		}
		OctetString *dOcts = theApp.SecudeLib.aux_LN2OctetString(d, (theApp.SecudeLib.lngtouse(d)+7)/8);
		if (dOcts == NULL)
		{
			// Fehler
			theApp.SecudeLib.aux_free_OctetString(&cOcts);
			return -2;
		}

		m_SignHexDump = ((CString)"c:\r\n"); UpdateData(FALSE);

		// cOcts als Hexdump ausgeben
		srcSize = cOcts->noctets;
		destSize = ((srcSize+hexdumpCols-1)/hexdumpCols)*(11+hexdumpCols*4)-hexdumpCols+(srcSize%hexdumpCols)+1;

		char *cData = (char *) malloc(destSize+1);

		err = HexDumpMem(cData, destSize, (unsigned char *) cOcts->octets, srcSize, hexdumpCols);
		if (err == 0)
		{
			// Fehler
			theApp.SecudeLib.aux_free_OctetString(&cOcts);
			theApp.SecudeLib.aux_free_OctetString(&dOcts);
			free(cData);
			return -3;
		}
		m_SignHexDump = m_SignHexDump + ((CString)cData) + ((CString)"\r\n\r\n"); UpdateData(FALSE);
		theApp.SecudeLib.aux_free_OctetString(&cOcts);

		m_SignHexDump = m_SignHexDump + ((CString)"d:\r\n"); UpdateData(FALSE);

		// dOcts als Hexdump ausgeben
		srcSize = dOcts->noctets;
		destSize = ((srcSize+hexdumpCols-1)/hexdumpCols)*(11+hexdumpCols*4)-hexdumpCols+(srcSize%hexdumpCols)+1;

		char *dData = (char *) malloc(destSize+1);

		err = HexDumpMem(dData, destSize, (unsigned char *) dOcts->octets, srcSize, hexdumpCols);
		if (err == 0)
		{
			// Fehler
			theApp.SecudeLib.aux_free_OctetString(&dOcts);
			free(cData);
			free(dData);
			return -3;
		}
		m_SignHexDump = m_SignHexDump + ((CString)dData);
		UpdateData(FALSE);
		theApp.SecudeLib.aux_free_OctetString(&dOcts);
		free(cData);
		free(dData);
	}
	return 0;
}


int CDlgVerifyECSignatureStepByStep::DsaDataStructToDsaDataStringStruct()
{
	int err = 0;
	char *fstr;
	char *hstr;
	char *h1str;
	char *h2str;
	char *Pxstr;
	char *Pystr;
	char *istr;
	char *c1str;

	err = ln_to_string ( DsaVerifData.f, &fstr, base );
	DsaVerifDataStrings.f = (CString) fstr;
	free (fstr);

	err += ln_to_string ( DsaVerifData.h, &hstr, base );
	DsaVerifDataStrings.h = (CString) hstr;
	free (hstr);

	err += ln_to_string ( DsaVerifData.h1, &h1str, base );
	DsaVerifDataStrings.h1 = (CString) h1str;
	free (h1str);

	err += ln_to_string ( DsaVerifData.h2, &h2str, base );
	DsaVerifDataStrings.h2 = (CString) h2str;
	free (h2str);

	if (DsaVerifData.P.infinity == 0)
	{
		err += ln_to_string (DsaVerifData.P.x, &Pxstr, base);
		DsaVerifDataStrings.Px = (CString) Pxstr;
		free (Pxstr);

		err += ln_to_string (DsaVerifData.P.y, &Pystr, base);
		DsaVerifDataStrings.Py = (CString) Pystr;
		free (Pystr);
	}
	else 
	{
		DsaVerifDataStrings.Px = (CString) "inf";
		DsaVerifDataStrings.Py = (CString) "inf";
	}

	err += ln_to_string (DsaVerifData.i, &istr, base);
	DsaVerifDataStrings.i = (CString) istr;
	free (istr);

	err += ln_to_string (DsaVerifData.c1, &c1str, base);
	DsaVerifDataStrings.c1 = (CString) c1str;
	free (c1str);

	return err;
}

int CDlgVerifyECSignatureStepByStep::NrDataStructToNrDataStringStruct()
{
	int err = 0;
	char *Pxstr;
	char *Pystr;
	char *istr;
	char *fstr;
	char *gstr;

	if (NrVerifData.P.infinity == 0)
	{
		err += ln_to_string (NrVerifData.P.x, &Pxstr, base);
		NrVerifDataStrings.Px = (CString) Pxstr;
		free (Pxstr);

		err += ln_to_string (NrVerifData.P.y, &Pystr, base);
		NrVerifDataStrings.Py = (CString) Pystr;
		free (Pystr);
	}
	else 
	{
		NrVerifDataStrings.Px = (CString) "inf";
		NrVerifDataStrings.Py = (CString) "inf";
	}

	err += ln_to_string (NrVerifData.i, &istr, base);
	NrVerifDataStrings.i = (CString) istr;
	free (istr);

	err += ln_to_string (NrVerifData.f, &fstr, base);
	NrVerifDataStrings.f = (CString) fstr;
	free (fstr);

	err += ln_to_string (NrVerifData.g, &gstr, base);
	NrVerifDataStrings.g = (CString) gstr;
	free (gstr);

	return err;
}

int CDlgVerifyECSignatureStepByStep::UpdateDataDisplay()
{
	CString sp1 = (CString)" ";
	CString sp2 = (CString)"  ";
	CString nl = (CString)"\r\n";

	int err;

	LoadString(AfxGetInstanceHandle(),IDS_STRING_CONTINUE,pc_str,STR_LAENGE_STRING_TABLE);
	CString cont = (CString) pc_str; // cont == "weiter ..."

	if (step == 0)
	{
		// benutzter Schlüsselbezeichner:
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_CREATOR,pc_str,STR_LAENGE_STRING_TABLE);
		m_DataDisplay = (CString)pc_str+sp2+Firstname+sp1+Name+nl+nl;

		// Domain Parameter des Signaturerzeugers ausgeben
		
		err = EcDomParamAcToString(&DomParamAcString, DomParamAc, base);
		if (err > 0)
		{
			// Fehler. Umwandlung der Domain Parameter in String nicht möglich.
			Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM,MB_ICONSTOP);
			return -1;
		}
		LoadString(AfxGetInstanceHandle(),IDS_STRING_DOMAIN_PARAMETER_TO_USE,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, curveID);
		m_DataDisplay += (CString) pc_str1 + nl + nl;
		m_DataDisplay += ( sp2 + ((CString)"a  = ") + DomParamAcString.a + nl );
		m_DataDisplay += ( sp2 + ((CString)"b  = ") + DomParamAcString.b + nl );
		m_DataDisplay += ( sp2 + ((CString)"Gx = ") + DomParamAcString.G_xcoord + nl );
		m_DataDisplay += ( sp2 + ((CString)"Gy = ") + DomParamAcString.G_ycoord + nl );
		m_DataDisplay += ( sp2 + ((CString)"k  = ") + DomParamAcString.k + nl );
		m_DataDisplay += ( sp2 + ((CString)"r  = ") + DomParamAcString.r + nl + nl );

		// öffentlicher Schlüssel
		LoadString(AfxGetInstanceHandle(),IDS_STRING_PUBLIC_EC_KEY,pc_str,STR_LAENGE_STRING_TABLE);
		m_DataDisplay += ( ((CString)pc_str) + nl + nl); // öffentlicher Schlüssel
		m_DataDisplay += ( sp2 + ((CString)"Wx  = ") + DomParamAcString.pubKey_xcoord + nl );
		m_DataDisplay += ( sp2 + ((CString)"Wy  = ") + DomParamAcString.pubKey_ycoord + nl + nl );

		// Signaturverfahren und Hashfunktion
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SEL_SIGNATURE_HASH_FUNCTION,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, SigAlg, HashAlg);
		m_DataDisplay += ( ((CString)pc_str1) + nl + nl);

		// Länge der signierenten Nachricht in Byte
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_MESSAGE_SIZE_2,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, messageOcts->noctets);
		m_DataDisplay += ( ((CString)pc_str1) + nl + nl);

		// Länge der Signatur in Bit
		LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_BITLENGTH_CD,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, SignLength);
		m_DataDisplay += ( ((CString)pc_str1) + nl + nl);
		m_DataDisplay += ( cont + nl + nl);

		nFirstVisibleLine = 0;
	}

	if ( strcmp(SigAlg,"ECSP-DSA") == 0 )
	{
		if (step == 0)
		{
			err = DsaDataStructToDsaDataStringStruct();
			if (err > 0)
			{
				// Fehler. Umwandlung von L_NUMBER in String nicht möglich.
				Message(IDS_STRING_ERR_TRANSFORMATION_LNUMBER_TO_CSTRING,MB_ICONSTOP);
				UpdateData(FALSE);
				return -1;
			}
			maxsteps = 10;
		}

		LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_DISPLAY_STEPS,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, step, maxsteps);
		m_Step = (CString) pc_str1;
	
		if (step == 1)
		{
			// message Representative f
			LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_HASHING,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(pc_str1, pc_str, HashAlg);
			m_DataDisplay += ( ((CString)pc_str1) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"f  = ") + DsaVerifDataStrings.f + nl + nl );

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 2)
		{
			// Überprüfe ob c und d aus [1, r-1] sind
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_SIGNATURE_VALIDITY_TEST,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl );

			if (DsaVerifData.rangecheckfailed == 1)
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_C_D_ERROR,pc_str,STR_LAENGE_STRING_TABLE);
				m_DataDisplay += ( sp2 + ((CString)pc_str) + nl );
				UpdateData(FALSE);
				m_DataDisplayCtrl.LineScroll( nFirstVisibleLine );
				SignatureInvalid();
				return 1;
			}
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_C_D_CORRECT,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( sp2 + ((CString)pc_str) + nl + nl );

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 3)
		{
			// h = d^(-1) mod r
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_INVERT_D,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"h  = ") + DsaVerifDataStrings.h + nl + nl );

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 4)
		{
			// h1 = f*h mod r
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_H1,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"h1 = ") + DsaVerifDataStrings.h1 + nl + nl );

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 5)
		{
			// h2 = c*h mod r
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_H2,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"h2 = ") + DsaVerifDataStrings.h2 + nl + nl );

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 6)
		{
			//  P = h1 G + h2 W
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_CHECK_SIGNATURE,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"Px = ") + DsaVerifDataStrings.Px + nl );
			m_DataDisplay += ( sp2 + ((CString)"Py = ") + DsaVerifDataStrings.Py + nl + nl );

			if (DsaVerifData.P.infinity != 0)
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_SIGNATURE_INCORRECT,pc_str,STR_LAENGE_STRING_TABLE);
				m_DataDisplay += ( sp2 + ((CString)pc_str) + nl );
				UpdateData(FALSE);
				m_DataDisplayCtrl.LineScroll( nFirstVisibleLine );
				SignatureInvalid();
				return 2;
			}

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 7)
		{
			// Px to i
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_MULT_CONVERT,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"i  = ") + DsaVerifDataStrings.i + nl + nl );

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 8)
		{
			// c' = i mod r
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_DIV_REMAINDER,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"c' = ") + DsaVerifDataStrings.c1 + nl + nl );

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 9)
		{
			// c' = c  ?
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_COMPARE,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);
		}
		if (step == 10)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_MSG_COMPARE_C_CPRIME,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( sp2 + ((CString)pc_str) + nl );
			UpdateData(FALSE);
			m_DataDisplayCtrl.LineScroll( nFirstVisibleLine );
			UpdateData(TRUE);
			if ( (SECUDE(comp)(c,DsaVerifData.c1)) != 0 ) SignatureInvalid(); //signature verification failed
			else SignatureValid();
		}
	}
	else if ( strcmp(SigAlg,"ECSP-NR") == 0 )
	{
		if (step == 0)
		{
			err = NrDataStructToNrDataStringStruct();
			if (err > 0)
			{
				// Fehler. Umwandlung von L_NUMBER in String nicht möglich.
				Message(IDS_STRING_ERR_TRANSFORMATION_LNUMBER_TO_CSTRING,MB_ICONSTOP);
				UpdateData(FALSE);
				return -1;
			}
			maxsteps = 7;
		}

		LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_DISPLAY_STEPS,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, step, maxsteps);
		m_Step = (CString) pc_str1;

		if (step == 1)
		{
			// Überprüfe ob c und d aus [1, r-1] sind
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_SIGNATURE_VALIDITY_TEST,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl );

			if (NrVerifData.rangecheckfailed == 1)
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_C_D_ERROR,pc_str,STR_LAENGE_STRING_TABLE);
				m_DataDisplay += ( sp2 + ((CString)pc_str) + nl );
				UpdateData(FALSE);
				m_DataDisplayCtrl.LineScroll( nFirstVisibleLine );
				SignatureInvalid();
				return 1;
			}
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_C_D_CORRECT,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( sp2 + ((CString)pc_str) + nl + nl );

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 2)
		{
			//  P = h1 G + h2 W
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_CALC_P,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"Px = ") + NrVerifDataStrings.Px + nl );
			m_DataDisplay += ( sp2 + ((CString)"Py = ") + NrVerifDataStrings.Py + nl + nl );

			if (NrVerifData.P.infinity != 0)
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_SIGNATURE_INCORRECT,pc_str,STR_LAENGE_STRING_TABLE);
				m_DataDisplay += ( sp2 + ((CString)pc_str) + nl );
				UpdateData(FALSE);
				m_DataDisplayCtrl.LineScroll( nFirstVisibleLine );
				SignatureInvalid();
				return 2;
			}

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 3)
		{
			// Px to i
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_MULT_CONVERT,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"i  = ") + NrVerifDataStrings.i + nl + nl );

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 4)
		{
			// f = c - i mod r
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_CALC_MESSAGE_REPRESENTATIVE,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"f  = ") + NrVerifDataStrings.f + nl + nl );

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 5)
		{
			// g
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_CALC_HASHFUNCTION,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(pc_str1, pc_str, HashAlg);
			m_DataDisplay += ( ((CString)pc_str1) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"g  = ") + NrVerifDataStrings.g + nl + nl );

			m_DataDisplay += ( cont + nl + nl);

		}
		if (step == 6)
		{
			// f = g ?
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_COMPARE_F_G,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);

		}
		if (step == 7)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_MSG_COMPARE_F_G,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( sp2 + ((CString)pc_str) + nl );
			UpdateData(FALSE);
			m_DataDisplayCtrl.LineScroll( nFirstVisibleLine );
			UpdateData(TRUE);
			if ( (SECUDE(comp)(NrVerifData.f,NrVerifData.g)) != 0 ) SignatureInvalid(); //signature verification failed
			else SignatureValid();
		}
	}

	UpdateData(FALSE);

	m_DataDisplayCtrl.LineScroll( step ? m_DataDisplayCtrl.GetLineCount() : 0 /* nFirstVisibleLine */ );

	UpdateData(TRUE);

	return 0;
}

void CDlgVerifyECSignatureStepByStep::SignatureInvalid()
{
	verifFinish = clock();
	duration = (double)(verifFinish - verifStart) / CLOCKS_PER_SEC;

	m_ContinueButtonCtrl.EnableWindow(FALSE);
	m_OkButtonCtrl.SetFocus();

	if (showDuration==TRUE)
	{
		char temp[200];
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE_VERIFICATION_TIME,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_BAD_SIGNATURE,temp,STR_LAENGE_STRING_TABLE);
		char strDuration[20];
		double_fmt( duration, strDuration, 3 );
		sprintf(pc_str1, pc_str, strDuration);
		sprintf(pc_str, temp, pc_str1);
		AfxMessageBox (pc_str, MB_ICONEXCLAMATION);
	}
	else
	{
		Message(IDS_STRING_ASYMKEY_MSG_SIGNATURE_FAIL, MB_ICONEXCLAMATION);
	}
	
	return;
}


void CDlgVerifyECSignatureStepByStep::SignatureValid()
{
	verifFinish = clock();
	duration = (double)(verifFinish - verifStart) / CLOCKS_PER_SEC;

	m_ContinueButtonCtrl.EnableWindow(FALSE);
	m_OkButtonCtrl.SetFocus();

	if (showDuration==TRUE)
	{
		char temp[200];
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE_VERIFICATION_TIME,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_CORRECT_SIGNATURE,temp,STR_LAENGE_STRING_TABLE);
		char strDuration[20];
		double_fmt( duration, strDuration, 3 );
		sprintf(pc_str1, pc_str, strDuration);
		sprintf(pc_str, temp, pc_str1);
		AfxMessageBox (pc_str, MB_ICONINFORMATION);
	}
	else
	{
		Message(IDS_STRING_ASYMKEY_MSG_SIGNATURE_CORRECT, MB_ICONINFORMATION);
	}

	return;
}


void CDlgVerifyECSignatureStepByStep::OnButtonContinue() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	nFirstVisibleLine = m_DataDisplayCtrl.GetFirstVisibleLine();
	step++;
	if (step == 1) verifStart = clock();
	UpdateDataDisplay();

}

void CDlgVerifyECSignatureStepByStep::OnRadioOktal() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	nFirstVisibleLine = m_DataDisplayCtrl.GetFirstVisibleLine();
	UpdateData(TRUE);
	base = 8;
	UpdateSigEditBox();
	m_DataDisplayCtrl.LineScroll( nFirstVisibleLine );
	UpdateData(TRUE);
}

void CDlgVerifyECSignatureStepByStep::OnRadioDezimal() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	nFirstVisibleLine = m_DataDisplayCtrl.GetFirstVisibleLine();
	UpdateData(TRUE);
	base = 10;
	UpdateSigEditBox();
	m_DataDisplayCtrl.LineScroll( nFirstVisibleLine );
	UpdateData(TRUE);
}

void CDlgVerifyECSignatureStepByStep::OnRadioHexadezimal() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	nFirstVisibleLine = m_DataDisplayCtrl.GetFirstVisibleLine();
	UpdateData(TRUE);
	base = 16;
	UpdateSigEditBox();
	m_DataDisplayCtrl.LineScroll( nFirstVisibleLine );
	UpdateData(TRUE);
}

void CDlgVerifyECSignatureStepByStep::OnRadioOctets() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	nFirstVisibleLine = m_DataDisplayCtrl.GetFirstVisibleLine();
	UpdateData(TRUE);
	base = -1;
	UpdateSigEditBox();
	m_DataDisplayCtrl.LineScroll( nFirstVisibleLine );
	UpdateData(TRUE);
}
