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
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
#ifndef AFX_HILLEINGABE_H__218034DD_7572_11D2_8D2B_00C04F795E36__INCLUDED_
#define AFX_HILLEINGABE_H__218034DD_7572_11D2_8D2B_00C04F795E36__INCLUDED_

// HillEingabe.h : Header-Datei
//

#include "HillEncryption.h"
#include "Cryptography.h"
#include "afxwin.h"

#define DIM_DLG_HILL_5x5	5

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHill5x5 

class CHiEdit : public CEdit
{
protected:
	//{{AFX_MSG(CHiEdit)
	afx_msg void OnLButtonUp(UINT, CPoint);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
};

enum HillEditType { HILL_CHAR_MATRIX, HILL_NUM_MATRIX };
enum HillMultType { VECTOR_MATRIX, MATRIX_VECTOR };


class CDlgKeyHillBaseFunctions {
    CHiEdit           **HillNumMat;
	CEdit             **HillAlphMat;
	CSquareMatrixModN  *HillMat;

	// HILL parameter
	unsigned long   alphabetOffset;
	unsigned long   max_dim, dim;
	HillEditType    matType;
	HillMultType    multType; 
	unsigned long   cryptMode;

	friend class CDlgKeyHill5x5;
	friend class CDlgKeyHill10x10;

	// Select Matrix
	void setMatFont();
	void activateMatrix     ( CEdit **mat );
	void deactivateMatrix   ( CEdit **mat ); 
	void selectActMatrix    ( );
	void selectHillDimension( unsigned long new_dim );
	void selectMatType      ( HillEditType new_type );
	void selectMultType     ( HillMultType new_type );

	void syncNumAlph ( unsigned long i, unsigned long j );
	void syncAlphNum ( unsigned long i, unsigned long j );
	void formatNum   ( unsigned long i, unsigned long j );

	int  validEntries();
	int  isInvertable();

	void pasteKey();
	void copyKey();
	void readRegistry();
	void writeRegistry();
	void randomKey();
	void SetHillMatrix ( CSquareMatrixModN *mat );
	void loadHillMatrix( CSquareMatrixModN& mat );

public:
	int ord( const char ch );
	CDlgKeyHillBaseFunctions(unsigned long p_keyRange);
	~CDlgKeyHillBaseFunctions();
};


class CDlgKeyHill5x5 : public CDialog
{
	CDlgKeyHillBaseFunctions *m_HillBase;
	CBitmapButton             m_Paste;
	BOOL	m_Verbose;
	CEdit	m_FeldUnsichtbar;
	CString m_pHillAlphInfo;
	unsigned long m_alphabetOffset;

// Konstruktion
public:
	CDlgKeyHill5x5(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgKeyHill5x5();

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHill5x5)
	enum { IDD = IDD_KEY_HILL5X5 };
	//{{AFX_VIRTUAL(CDlgKeyHill5x5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// helper functions
	void radioSetMultType( unsigned long ID );
	void radioSetHillDim ( unsigned long ID );
	void radioSetMatType ( unsigned long ID );
	void displayAlphabet();

	CFont cf;
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHill5x5)
	afx_msg void OnUpdateMat11();
	afx_msg void OnUpdateMat12();
	afx_msg void OnUpdateMat13();
	afx_msg void OnUpdateMat14();
	afx_msg void OnUpdateMat15();
	afx_msg void OnUpdateMat21();
	afx_msg void OnUpdateMat22();
	afx_msg void OnUpdateMat23();
	afx_msg void OnUpdateMat24();
	afx_msg void OnUpdateMat25();
	afx_msg void OnUpdateMat31();
	afx_msg void OnUpdateMat32();
	afx_msg void OnUpdateMat33();
	afx_msg void OnUpdateMat34();
	afx_msg void OnUpdateMat35();
	afx_msg void OnUpdateMat41();
	afx_msg void OnUpdateMat42();
	afx_msg void OnUpdateMat43();
	afx_msg void OnUpdateMat44();
	afx_msg void OnUpdateMat45();
	afx_msg void OnUpdateMat51();
	afx_msg void OnUpdateMat52();
	afx_msg void OnUpdateMat53();
	afx_msg void OnUpdateMat54();
	afx_msg void OnUpdateMat55();

	afx_msg void OnUpdateMat36();
	afx_msg void OnUpdateMat37();
	afx_msg void OnUpdateMat38();
	afx_msg void OnUpdateMat40();
	afx_msg void OnUpdateMat46();
	afx_msg void OnUpdateMat47();
	afx_msg void OnUpdateMat48();
	afx_msg void OnUpdateMat49();
	afx_msg void OnUpdateMat50();
	afx_msg void OnUpdateMat111();
	afx_msg void OnUpdateMat57();
	afx_msg void OnUpdateMat58();
	afx_msg void OnUpdateMat59();
	afx_msg void OnUpdateMat56();
	afx_msg void OnUpdateMat115();
	afx_msg void OnUpdateMat60();
	afx_msg void OnUpdateMat61();
	afx_msg void OnUpdateMat62();
	afx_msg void OnUpdateMat116();
	afx_msg void OnUpdateMat117();
	afx_msg void OnUpdateMat63();
	afx_msg void OnUpdateMat64();
	afx_msg void OnUpdateMat69();
	afx_msg void OnUpdateMat65();
	afx_msg void OnUpdateMat66();

	afx_msg void OnExitMat36();
	afx_msg void OnExitMat37();
	afx_msg void OnExitMat38();
	afx_msg void OnExitMat40();
	afx_msg void OnExitMat46();
	afx_msg void OnExitMat47();
	afx_msg void OnExitMat48();
	afx_msg void OnExitMat49();
	afx_msg void OnExitMat50();
	afx_msg void OnExitMat111();
	afx_msg void OnExitMat57();
	afx_msg void OnExitMat58();
	afx_msg void OnExitMat59();
	afx_msg void OnExitMat56();
	afx_msg void OnExitMat115();
	afx_msg void OnExitMat60();
	afx_msg void OnExitMat61();
	afx_msg void OnExitMat62();
	afx_msg void OnExitMat116();
	afx_msg void OnExitMat117();
	afx_msg void OnExitMat63();
	afx_msg void OnExitMat64();
	afx_msg void OnExitMat69();
	afx_msg void OnExitMat65();
	afx_msg void OnExitMat66();

	void SetDimension( unsigned long d );
	afx_msg void OnDimension1();
	afx_msg void OnDimension2();
	afx_msg void OnDimension3();
	afx_msg void OnDimension4();
	afx_msg void OnDimension5();	

	afx_msg void OnEnableAlphCode();
	afx_msg void OnDisableAlphCode();

	afx_msg void OnRowVectorMatrix();
	afx_msg void OnMatrixColumnVector();

	void         DoCrypt( unsigned long mode );
	virtual void OnOK();
	virtual void OnDecrypt();

	virtual BOOL OnInitDialog();
	afx_msg void OnVerbose();
	afx_msg void OnPasteKey();
	afx_msg void OnZufaelligerSchluessel();
	afx_msg void OnGroessereSchluessel();
	afx_msg void OnTextOptions();
	afx_msg void OnHillOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_HILLEINGABE_H__218034DD_7572_11D2_8D2B_00C04F795E36__INCLUDED_
