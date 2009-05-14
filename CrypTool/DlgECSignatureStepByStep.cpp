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

// DlgSignSteps.cpp: Implementierungsdatei
//
//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 2000
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgECSignatureStepByStep.h"
#include "DialogeMessage.h"

#include "FileTools.h"
#include "s_prng.h"
#include "s_ecconv.h"
#include "ECsecude.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgECSignatureStepByStep 


CDlgECSignatureStepByStep::CDlgECSignatureStepByStep(OctetString *msgOct, CString sig_id, CString hash_id,\
							 EcDomParam_ac_ptr dp_ac, EcDomParam_pc_ptr dp_pc,\
							 CString used_keyfile,\
							 CString name, CString firstname, CString curve_id,\
							 CWnd* pParent /*=NULL*/)\
		: CDialog(CDlgECSignatureStepByStep::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgECSignatureStepByStep)
	m_DataDisplay = _T("");
	m_TextMessage = _T("");
	m_MsgHexDump = _T("");
	m_TextSignSteps = _T("");
	m_Step = _T("");
	//}}AFX_DATA_INIT

	messageOcts = msgOct;

	DomParamAc = dp_ac; // The Domain Parameter (affine coordinates) of the selected elliptic Curve
	DomParamPc = dp_pc; // The Domain Parameter (projective coordinates) of the selected elliptic Curve

	SigAlg = sig_id; // Sign with algorithm sigalg
	HashAlg = hash_id; // use hash algorithm hashalg

	Name = name;
	Firstname = firstname;
	curveID = curve_id;

	UserKeyId = used_keyfile;

	base = 10;
	step = 0;
}


void CDlgECSignatureStepByStep::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgECSignatureStepByStep)
	DDX_Control(pDX, IDC_EDIT4, m_StepCtrl);
	DDX_Control(pDX, IDOK, m_FlushSignDataCtrl);
	DDX_Control(pDX, IDC_EDIT3, m_TextSignStepsCtrl);
	DDX_Control(pDX, IDC_BUTTON_CONTINUE, m_ContinueButtonCtrl);
	DDX_Control(pDX, IDC_EDIT2, m_MsgHexDumpCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_TextMessageCtrl);
	DDX_Control(pDX, IDC_EDIT_SHOW_STEPS, m_DataDisplayCtrl);
	DDX_Text(pDX, IDC_EDIT_SHOW_STEPS, m_DataDisplay);
	DDX_Text(pDX, IDC_EDIT1, m_TextMessage);
	DDX_Text(pDX, IDC_EDIT2, m_MsgHexDump);
	DDX_Text(pDX, IDC_EDIT3, m_TextSignSteps);
	DDX_Text(pDX, IDC_EDIT4, m_Step);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgECSignatureStepByStep, CDialog)
	//{{AFX_MSG_MAP(CDlgECSignatureStepByStep)
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE, OnButtonContinue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgECSignatureStepByStep 

BOOL CDlgECSignatureStepByStep::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	int fret;

	m_FlushSignDataCtrl.EnableWindow(FALSE);

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
	m_TextSignStepsCtrl.SetFont(&m_Font);
	m_StepCtrl.SetFont(&m_Font);
	LogFont.lfWeight = defaultFontWeight; // Auf default Wert zurückstellen
	strncpy(LogFont.lfFaceName, "Courier", 32); // Auf Courier umstellen	
	m_Font2.CreateFontIndirect( &LogFont ); // Font2 initialisieren
	//strncpy(LogFont.lfFaceName, DefaultFontStyle, 32);

	m_MsgHexDumpCtrl.SetFont(&m_Font2);
	m_DataDisplayCtrl.SetFont(&m_Font2);

	/*
	if (messagefromfile == true)
	{
		// Die signierte Nachricht ist zu gross und passt nicht komplett
		// in ein CEdit Feld. Es wird lediglich ein erster Teil der Nachricht dargestellt
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNED_MESSAGE_FIRST_PART,pc_str,STR_LAENGE_STRING_TABLE);
		m_TextMsg = (CString) pc_str;
	}
	*/

	LoadString(AfxGetInstanceHandle(),IDS_STRING_MESSAGE_TO_SIGN,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextMessage = (CString) pc_str; // Zu signierende Nachricht M:

	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_STEP_BY_STEP,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextSignSteps = (CString) pc_str; // Schrittweise Signatur Erzeugung:
	UpdateData(FALSE);

	if (messageOcts->noctets != 0)
	{
		int cols = 14;
		int srcSize = messageOcts->noctets;
		int destSize = ((srcSize+cols-1)/cols)*(11+cols*4)-cols+(srcSize%cols)+1;
		char *msgdata = (char *) malloc(destSize+1);
		fret = HexDumpMem(msgdata, destSize, (unsigned char *) messageOcts->octets, srcSize, cols);
		if (fret == 0)
		{
			// Fehler
			//EndDialog(-1);
			return TRUE;
		}
		m_MsgHexDump = (CString) msgdata;
		free (msgdata);
	}

	UpdateData(FALSE);

	// Umwandeln von CString nach char*
	LPTSTR string_tmp = new TCHAR[SigAlg.GetLength()+1];
	_tcscpy(string_tmp, SigAlg);
	char *sign_primitiv_id=string_tmp;

	LPTSTR string_tmp2 = new TCHAR[HashAlg.GetLength()+1];
	_tcscpy(string_tmp2, HashAlg);
	char *hash_id=string_tmp2;

	fret = ecssa_sign_gen_op_ac(c, d, messageOcts, DomParamAc, sign_primitiv_id , hash_id);
	if (fret)
	{
		//
	}

	delete string_tmp;
	delete string_tmp2;

	UpdateDataDisplay();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


int CDlgECSignatureStepByStep::DsaDataStructToDsaDataStringStruct()
{
	int err = 0;
	char *ustr;
	char *Vxstr;
	char *Vystr;
	char *istr;
	char *cstr;
	char *dstr;

	err = ln_to_string ( DsaSignData.u, &ustr, base );
	DsaSignDataStrings.u = (CString) ustr;
	free (ustr);

	if (DsaSignData.V.infinity == 0)
	{
		err += ln_to_string (DsaSignData.V.x, &Vxstr, base);
		DsaSignDataStrings.Vx = (CString) Vxstr;
		free (Vxstr);

		err += ln_to_string (DsaSignData.V.y, &Vystr, base);
		DsaSignDataStrings.Vy = (CString) Vystr;
		free (Vystr);
	}
	else 
	{
		DsaSignDataStrings.Vx = (CString) "inf";
		DsaSignDataStrings.Vy = (CString) "inf";
	}

	err += ln_to_string (DsaSignData.i, &istr, base);
	DsaSignDataStrings.i = (CString) istr;
	free (istr);

	err += ln_to_string (DsaSignData.c, &cstr, base);
	DsaSignDataStrings.c = (CString) cstr;
	free (cstr);

	err += ln_to_string (DsaSignData.d, &dstr, base);
	DsaSignDataStrings.d = (CString) dstr;
	free (dstr);

	return err;
}

int CDlgECSignatureStepByStep::NrDataStructToNrDataStringStruct()
{
	int err = 0;
	char *ustr;
	char *Vxstr;
	char *Vystr;
	char *istr;
	char *cstr;
	char *dstr;

	err = ln_to_string ( NrSignData.u, &ustr, base );
	NrSignDataStrings.u = (CString) ustr;
	free (ustr);

	if (NrSignData.V.infinity == 0)
	{
		err += ln_to_string (NrSignData.V.x, &Vxstr, base);
		NrSignDataStrings.Vx = (CString) Vxstr;
		free (Vxstr);

		err += ln_to_string (NrSignData.V.y, &Vystr, base);
		NrSignDataStrings.Vy = (CString) Vystr;
		free (Vystr);
	}
	else 
	{
		NrSignDataStrings.Vx = (CString) "inf";
		NrSignDataStrings.Vy = (CString) "inf";
	}

	err += ln_to_string (NrSignData.i, &istr, base);
	NrSignDataStrings.i = (CString) istr;
	free (istr);

	err += ln_to_string (NrSignData.c, &cstr, base);
	NrSignDataStrings.c = (CString) cstr;
	free (cstr);

	err += ln_to_string (NrSignData.d, &dstr, base);
	NrSignDataStrings.d = (CString) dstr;
	free (dstr);

	return err;
}

int CDlgECSignatureStepByStep::UpdateDataDisplay()
{
	CString sp1 = (CString)" ";
	CString sp2 = (CString)"  ";
	CString nl = (CString)"\r\n";

	int err;

	LoadString(AfxGetInstanceHandle(),IDS_STRING_CONTINUE,pc_str,STR_LAENGE_STRING_TABLE);
	CString cont = (CString) pc_str; // cont == "weiter ..."

	int maxsteps = 6;

	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_DISPLAY_STEPS,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str1, pc_str, step, maxsteps);
	m_Step = (CString) pc_str1;

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

		// geheimer Schlüssel
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_SECRET_KEY,pc_str,STR_LAENGE_STRING_TABLE);
		m_DataDisplay += ( ((CString)pc_str) + nl + nl); // geheimer Schlüssel
		m_DataDisplay += ( sp2 + ((CString)"s  = ") + DomParamAcString.privKey + nl + nl );

		// Signaturverfahren und Hashfunktion
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SEL_SIGNATURE_HASH_FUNCTION,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, SigAlg, HashAlg);
		m_DataDisplay += ( ((CString)pc_str1) + nl + nl);

		// Länge der zu signierenden Nachricht in Byte
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_MESSAGE_SIZE,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, messageOcts->noctets);
		m_DataDisplay += ( ((CString)pc_str1) + nl + nl);

		m_DataDisplay += ( cont + nl + nl);

		nFirstVisibleLine = 0;
	}
	if (step == 1)
	{
		char *fstr;
		// message Representative f
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_HASHING,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, HashAlg);
		m_DataDisplay += ( ((CString)pc_str1) + nl + nl);
		err = ln_to_string (MsgRepData.f, &fstr, base);
		if (err > 0)
		{
			// Fehler. Umwandlung von L_NUMBER in String nicht möglich.
			Message(IDS_STRING_ERR_TRANSFORMATION_LNUMBER_TO_CSTRING,MB_ICONSTOP);
			m_DataDisplayCtrl.LineScroll( nFirstVisibleLine );
			return -1;
		}
		m_DataDisplay += ( sp2 + ((CString)"f  = ") + ((CString)fstr) + nl + nl );
		m_DataDisplay += ( cont + nl + nl);
		free (fstr);
	}
	
	if (SigAlg == "ECSP-DSA")
	{
		if (step == 0)
		{
			err = DsaDataStructToDsaDataStringStruct();
			if (err > 0)
			{
				// Fehler. Umwandlung von L_NUMBER in String nicht möglich.
				Message(IDS_STRING_ERR_TRANSFORMATION_LNUMBER_TO_CSTRING,MB_ICONSTOP);
				return -1;
			}
		}

		if (step == 2)
		{
			// one-time key pair
			LoadString(AfxGetInstanceHandle(),IDS_STRING_CREATE_RANDOM_ASYMKEY,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(pc_str1, pc_str, curveID);
			m_DataDisplay += ( ((CString)pc_str1) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"u  = ") + DsaSignDataStrings.u + nl);
			m_DataDisplay += ( sp2 + ((CString)"Vx  = ") + DsaSignDataStrings.Vx + nl);
			m_DataDisplay += ( sp2 + ((CString)"Vy  = ") + DsaSignDataStrings.Vy + nl + nl);

			m_DataDisplay += ( cont + nl + nl);			
		}
		if (step == 3)
		{
			// umwandeln von Vx nach integer i
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_CONVERSION,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"i  = ") + DsaSignDataStrings.i + nl + nl);

			m_DataDisplay += ( cont + nl + nl);		
		}
		if (step == 4)
		{
			// Berechne c = i mod r, wobei c != 0
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_DIV_REMAINDER,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"c  = ") + DsaSignDataStrings.c + nl + nl);

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 5)
		{
			// Berechne d = u^(-1)(f+s*c) mod r, wobei d != 0
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_EVAL_RSA_PRIVATE_KEY,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);
			m_DataDisplay += ( sp2 + ((CString)"d  = ") + DsaSignDataStrings.d + nl + nl);

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 6)
		{
			// Signaturerzeugung beendet
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE_COMPLETE,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl);
			m_ContinueButtonCtrl.EnableWindow(FALSE);
			m_FlushSignDataCtrl.EnableWindow(TRUE);
			m_FlushSignDataCtrl.SetFocus();
		}
	}
	else if (SigAlg == "ECSP-NR")
	{
		if (step == 0)
		{
			err = NrDataStructToNrDataStringStruct();
			if (err > 0)
			{
				// Fehler. Umwandlung von L_NUMBER in String nicht möglich.
				Message(IDS_STRING_ERR_TRANSFORMATION_LNUMBER_TO_CSTRING,MB_ICONSTOP);
				return -1;
			}
		}

		if (step == 2)
		{
			// one-time key pair
			LoadString(AfxGetInstanceHandle(),IDS_STRING_CREATE_RANDOM_ASYMKEY,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(pc_str1, pc_str, curveID);
			m_DataDisplay += ( ((CString)pc_str1) + nl + nl);

			m_DataDisplay += ( sp2 + ((CString)"u  = ") + NrSignDataStrings.u + nl);
			m_DataDisplay += ( sp2 + ((CString)"Vx  = ") + NrSignDataStrings.Vx + nl);
			m_DataDisplay += ( sp2 + ((CString)"Vy  = ") + NrSignDataStrings.Vy + nl + nl);

			m_DataDisplay += ( cont + nl + nl);			
		}
		if (step == 3)
		{
			// umwandeln von Vx nach integer i
			LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_CONVERSION,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);

			m_DataDisplay += ( sp2 + ((CString)"i  = ") + NrSignDataStrings.i + nl + nl);

			m_DataDisplay += ( cont + nl + nl);		
		}
		if (step == 4)
		{
			// Berechne c = i+f mod r, wobei c != 0
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_DIV_REMAINDER_2,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);

			m_DataDisplay += ( sp2 + ((CString)"c  = ") + NrSignDataStrings.c + nl + nl);

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 5)
		{
			// Berechne d = u-s*c mod r, wobei d != 0
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_EVAL_RSA_PRIVATE_KEY_2,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl + nl);

			m_DataDisplay += ( sp2 + ((CString)"d  = ") + NrSignDataStrings.d + nl + nl);

			m_DataDisplay += ( cont + nl + nl);
		}
		if (step == 6)
		{
			// Signaturerzeugung beendet
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE_COMPLETE,pc_str,STR_LAENGE_STRING_TABLE);
			m_DataDisplay += ( ((CString)pc_str) + nl);
			m_ContinueButtonCtrl.EnableWindow(FALSE);
			m_FlushSignDataCtrl.EnableWindow(TRUE);
			m_FlushSignDataCtrl.SetFocus();
		}
	}
	UpdateData(FALSE);

	m_DataDisplayCtrl.LineScroll( step ? m_DataDisplayCtrl.GetLineCount() : 0 /* nFirstVisibleLine */ );
	UpdateData(TRUE);

	return 0;
}

int CDlgECSignatureStepByStep::ecssa_sign_gen_op_ac(/*out*/ L_NUMBER *c, L_NUMBER *d,
		        /*in  */ OctetString *M,
			   EcDomParam_ac_ptr Key,
			   char *sign_primitiv_id, /* "ECSP-DSA" or "ECSP-NR" */
			   char *hash_id) /* select hash_id for emsa1: "SHA-1" or "RIPEMD-160" */
{   
	unsigned int l;
	L_NUMBER f[MAXLGTH];

	/* select signature primitiv */

	if (strcmp(sign_primitiv_id, "ECSP-NR") == 0){
		l = SECUDE(lngtouse)(Key->r); /* l = (length of r in bits)-1 */
	}

	if (strcmp(sign_primitiv_id, "ECSP-DSA") == 0){
		l = SECUDE(lngtouse)(Key->r)+1; /* l = (length of r in bits) */
	}

	MsgRepData.l = l; // Zwischenergebnis speichern

	int fret = emsa1_encoding_operation(f, M, l, hash_id);

	if (fret) return (-1); /* error */

	trans(f, MsgRepData.f); // Zwischenergebnis speichern

	if (strcmp(sign_primitiv_id, "ECSP-NR") == 0){
		return ecFp_ecsp_nr_ac(c, d, Key->privKey, Key->E, Key->G, Key->r, f);
	}

	if (strcmp(sign_primitiv_id, "ECSP-DSA") == 0){
		return ecFp_ecsp_dsa_ac(c, d, Key->privKey, Key->E, Key->G, Key->r, f);
	}

	return (-5); /* error: function doesn't anything */
}

int CDlgECSignatureStepByStep::emsa1_encoding_operation(/*out*/ L_NUMBER *f,
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

/**********************************************************************************************************************
/*    Function to generate a key pair (private key, public key)	ecFp_generate_key_ac()
/**********************************************************************************************************************/
void CDlgECSignatureStepByStep::ecFp_generate_key_ac(L_NUMBER *private_key, ecFp_point_ac_destptr public_key, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G,L_NUMBER *r) 
{	
	private_key[0]=0;
	while (private_key[0]==0){
		_rand_int(private_key, r);
	}
	ecFp_mult_ac(public_key,  E,  private_key,  G);
}

/**********************************************************************************************************************
/* ECSP-DSA (IEEE 1363, 7.2.7) for prime fields				ecFp_ecsp_dsa_ac()
/**********************************************************************************************************************/
int CDlgECSignatureStepByStep::ecFp_ecsp_dsa_ac(L_NUMBER *c, L_NUMBER *d, L_NUMBER *s, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G, L_NUMBER *r, L_NUMBER *f)
{
	L_NUMBER  u[MAXLGTH],i[MAXLGTH], temp[MAXLGTH];
	ecFp_point_ac_t V;
	int no_result=1;
	unsigned int k;

	V=ecFp_point_init_ac;
	if (V==NULL) return (-1); /*point allocation error*/
	while (no_result)
	{
		ecFp_generate_key_ac(u, V, E, G, r);
		trans(V->x, i); 
		SECUDE(div)(i,r,temp,c); /*c=i mod r*/
		if ( c[0]!=0 ) no_result=0;
		if ( !(no_result) ){
			SECUDE(mmult)(s,c,d,r);
			SECUDE(madd)(d,f,d,r);
			inttoln(1,temp);
			SECUDE(mdiv)(temp,u,temp,r); /* temp = 1/u (mod r)*/
			SECUDE(mmult)(d,temp,d,r); /*=u^(-1)(f+sc) mod r*/
			if ( d[0]!=0) no_result=0;
			else no_result=1;
		}
	}

	trans(u, DsaSignData.u); // Zwischenergebnis speichern
	trans(V->x, DsaSignData.V.x); // Zwischenergebnis speichern
	trans(V->y, DsaSignData.V.y); // Zwischenergebnis speichern
	DsaSignData.V.infinity = V->infinity; // Zwischenergebnis speichern
	trans(i, DsaSignData.i); // Zwischenergebnis speichern
	trans(c, DsaSignData.c); // Zwischenergebnis speichern
	trans(d, DsaSignData.d); // Zwischenergebnis speichern

	for (k=1; k<=u[0]; u[k]=0,k++);  /*delete any trace of (u,V)*/
	u[0]=0;
	for (k=1; k<=V->x[0]; V->x[0]=0, k++);
	V->x[0]=0;
	for (k=1; k<=V->y[0]; V->y[0]=0, k++);
	V->y[0]=0;
	ecFp_point_clear_ac(V);
	return 0;
}

/**********************************************************************************************************************
/* ECSP-NR(IEEE 1363, 7.2.5) for prime fields	(affine coordinates)				ecFp_ecsp_nr_ac()
/**********************************************************************************************************************/
int CDlgECSignatureStepByStep::ecFp_ecsp_nr_ac(L_NUMBER *c, L_NUMBER *d, L_NUMBER *s, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G, L_NUMBER *r, L_NUMBER *f)
{
	int not_sufficient=1;
	L_NUMBER u[MAXLGTH], i[MAXLGTH];
	ecFp_point_ac_t V;
	unsigned int k;

	V=ecFp_point_init_ac;
	if (V==NULL) return (-1); /*point allocation error*/
	V->infinity = 0; /* OK ? */

	while (not_sufficient){	
		ecFp_generate_key_ac(u, V, E, G, r);
		trans(V->x, i);
		SECUDE(madd)(i,f,c,r);
		if (c[0]!= 0) not_sufficient=0;
	}
	SECUDE(mmult)(s,c,d,r);
	SECUDE(msub)(u,d,d,r);

	trans(u, NrSignData.u); // Zwischenergebnis speichern
	trans(V->x, NrSignData.V.x); // Zwischenergebnis speichern
	trans(V->y, NrSignData.V.y); // Zwischenergebnis speichern
	NrSignData.V.infinity = V->infinity; // Zwischenergebnis speichern
	trans(i, NrSignData.i); // Zwischenergebnis speichern
	trans(c, NrSignData.c); // Zwischenergebnis speichern
	trans(d, NrSignData.d); // Zwischenergebnis speichern

	for (k=1; k<=u[0]; u[k]=0,k++);  /*delete any trace of (u,V)*/
	u[0]=0;
	for (k=1; k<=V->x[0]; V->x[0]=0, k++);
	V->x[0]=0;
	for (k=1; k<=V->y[0]; V->y[0]=0, k++);
	V->y[0]=0;	
	ecFp_point_clear_ac(V);
	return 0;
}


void CDlgECSignatureStepByStep::OnButtonContinue() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	//LoadString(AfxGetInstanceHandle(),IDS_STRING_MESSAGE_TO_SIGN,pc_str1,STR_LAENGE_STRING_TABLE);
	//sprintf(pc_str, pc_str1,((CString)keyType)+kInfo,((CString)creattime));
	//m_KeyInfo = (CString) pc_str; // Benutzter Schlüssel:

	nFirstVisibleLine = m_DataDisplayCtrl.GetFirstVisibleLine();
	step++;
	UpdateDataDisplay();
}

void CDlgECSignatureStepByStep::GetSignature(L_NUMBER *c_out, L_NUMBER *d_out)
{
	trans(c, c_out);
	trans(d, d_out);
}
