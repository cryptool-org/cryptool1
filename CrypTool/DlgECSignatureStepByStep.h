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
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 2000
//////////////////////////////////////////////////////////////////

#ifndef AFX_DLGSIGNSTEPS_H__820B119D_FBFD_11D3_879B_00C04F795E36__INCLUDED_
#define AFX_DLGSIGNSTEPS_H__820B119D_FBFD_11D3_879B_00C04F795E36__INCLUDED_

// DlgSignSteps.h : Header-Datei
//

#include "s_ecFp.h"
#include "AsymmetricEncryption.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgECSignatureStepByStep 

class CDlgECSignatureStepByStep : public CDialog
{
// Konstruktion
public:
	CDlgECSignatureStepByStep(OctetString *msgOct, CString sig_id, CString hash_id,\
							 EcDomParam_ac_ptr dp_ac, EcDomParam_pc_ptr dp_pc,\
							 CString used_keyfile,\
							 CString name, CString firstname, CString curve_id,\
							 CWnd* pParent = NULL);   // Standardkonstruktor

	void GetSignature(L_NUMBER *c, L_NUMBER *d);

// Dialogfelddaten
	//{{AFX_DATA(CDlgECSignatureStepByStep)
	enum { IDD = IDD_ECSIGNATRURE_STEPBYSTEP };
	CEdit	m_StepCtrl;
	CButton	m_FlushSignDataCtrl;
	CEdit	m_TextSignStepsCtrl;
	CButton	m_ContinueButtonCtrl;
	CEdit	m_MsgHexDumpCtrl;
	CEdit	m_TextMessageCtrl;
	CEdit	m_DataDisplayCtrl;
	CString	m_DataDisplay;
	CString	m_TextMessage;
	CString	m_MsgHexDump;
	CString	m_TextSignSteps;
	CString	m_Step;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgECSignatureStepByStep)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	CFont m_Font;
	CFont m_Font2;

	OctetString *messageOcts;

	L_NUMBER c[MAXLGTH];
	L_NUMBER d[MAXLGTH];

	EcDomParam_ac_ptr DomParamAc; // The Domain Parameter (affine coordinates) of the selected elliptic Curve
	EcDomParam_pc_ptr DomParamPc; // The Domain Parameter (projective coordinates) of the selected elliptic Curve

	EcDomParamAcAsString DomParamAcString;
	int base;
	int step;
	int nFirstVisibleLine;

	CString SigAlg; // Sign with algorithm sigalg
	CString HashAlg; // use hash algorithm hashalg

	CString Name;
	CString Firstname;
	CString curveID;

	CString UserKeyId;

	typedef struct{
		L_NUMBER u[MAXLGTH]; // one-time key pair (u,V) 
		__PointAc_struct V; // one-time key pair (u,V) ; V = (x,y); 
		L_NUMBER i[MAXLGTH];
		L_NUMBER c[MAXLGTH];
		L_NUMBER d[MAXLGTH];
	} ecsp_dsa_data_struct;

	ecsp_dsa_data_struct DsaSignData;

	typedef struct{
		L_NUMBER u[MAXLGTH]; // one-time key pair (u,V) 
		__PointAc_struct V; // one-time key pair (u,V) ; V = (x,y); 
		L_NUMBER i[MAXLGTH];
		L_NUMBER c[MAXLGTH];
		L_NUMBER d[MAXLGTH];
	} ecsp_nr_data_struct;

	ecsp_nr_data_struct NrSignData;

	typedef struct{
		unsigned int l;
		L_NUMBER f[MAXLGTH]; // message representative (max l bit long)
	} ecssa_sign_gen_op_ac_data_struct;

	ecssa_sign_gen_op_ac_data_struct MsgRepData;

	typedef struct{
		CString u;
		CString Vx;
		CString Vy;
		CString i;
		CString c;
		CString d;
	} DsaSignDataStringStruct;

	DsaSignDataStringStruct DsaSignDataStrings;

	typedef struct{
		CString u;
		CString Vx;
		CString Vy;
		CString i;
		CString c;
		CString d;
	} NrSignDataStringStruct;

	NrSignDataStringStruct NrSignDataStrings;

	int UpdateDataDisplay();

	int ecssa_sign_gen_op_ac(/*out*/ L_NUMBER *c, L_NUMBER *d,
		        /*in  */ OctetString *M,
			   EcDomParam_ac_ptr Key,
			   char *sign_primitiv_id, /* "ECSP-DSA" or "ECSP-NR" */
			   char *hash_id); /* select hash_id for emsa1: "SHA-1" or "RIPEMD-160" */

	int emsa1_encoding_operation(/*out*/ L_NUMBER *f,
		             /*in   */ OctetString *M,
		                         unsigned int l,
		                         char *hash_id); /* "SHA-1" or "RIPEMD-160" */

	void ecFp_generate_key_ac(L_NUMBER *private_key, ecFp_point_ac_destptr public_key, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G,L_NUMBER *r);

	int ecFp_ecsp_dsa_ac(L_NUMBER *c, L_NUMBER *d, L_NUMBER *s, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G, L_NUMBER *r, L_NUMBER *f);

	int ecFp_ecsp_nr_ac(L_NUMBER *c, L_NUMBER *d, L_NUMBER *s, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G, L_NUMBER *r, L_NUMBER *f);

	int DsaDataStructToDsaDataStringStruct();
	int NrDataStructToNrDataStringStruct();

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgECSignatureStepByStep)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonContinue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGSIGNSTEPS_H__820B119D_FBFD_11D3_879B_00C04F795E36__INCLUDED_
