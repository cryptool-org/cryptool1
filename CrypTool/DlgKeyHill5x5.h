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

class CDlgKeyHill5x5 : public CDialog
{
	CBitmapButton m_Paste;

// Konstruktion
public:
	int		m_decrypt;
	unsigned long	alphCode;
	unsigned long firstPosNull;
	CSquareMatrixModN * mat;
	void UpdateFeld (CEdit*feld);
	void UpdateAlphCode(CEdit *feld);
	void MatrixEinlesen(CSquareMatrixModN& mat, int dim);
	void MatrixAnzeigen(CSquareMatrixModN& mat);
	bool NaechsterEintrag(int& i, int& j) ;
	int AlleFelderKorrekt(int);
	void AnzeigeDimensionSetzen(int);
	int dim;
	int Display();
	class CHiEdit* m_pFelder[HILL_MAX_DIM][HILL_MAX_DIM];

	class CHiEdit* m_pAlphCode[HILL_MAX_DIM][HILL_MAX_DIM];

	CString getAlphCode(CString alphChar);
	CString getAlphChar(CString alphPos);
	void setFeldAlph(CEdit *feld,CEdit *feldAlph);
	void setFeldAlphCode(CEdit *feld,CEdit *feldAlph);
	void setDoublePos(CEdit *feld);

	void OnHillOptions();
	BOOL getFirstPosNull();

	CString getDimMessage();

	CDlgKeyHill5x5(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgKeyHill5x5();

	CHillEncryption *getHillKlasse() { return hillklasse; };

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHill5x5)
	enum { IDD = IDD_KEY_HILL5X5 };
	BOOL	m_Verbose;
	CEdit	m_FeldUnsichtbar;
	class CHiEdit	m_Feld11;
	class CHiEdit	m_Feld12;
	class CHiEdit	m_Feld13;
	class CHiEdit	m_Feld14;
	class CHiEdit	m_Feld15;
	class CHiEdit	m_Feld21;
	class CHiEdit	m_Feld22;
	class CHiEdit	m_Feld23;
	class CHiEdit	m_Feld24;
	class CHiEdit	m_Feld25;
	class CHiEdit	m_Feld31;
	class CHiEdit	m_Feld32;
	class CHiEdit	m_Feld33;
	class CHiEdit	m_Feld34;
	class CHiEdit	m_Feld35;
	class CHiEdit	m_Feld41;
	class CHiEdit	m_Feld42;
	class CHiEdit	m_Feld43;
	class CHiEdit	m_Feld44;
	class CHiEdit	m_Feld45;
	class CHiEdit	m_Feld51;
	class CHiEdit	m_Feld52;
	class CHiEdit	m_Feld53;
	class CHiEdit	m_Feld54;
	class CHiEdit	m_Feld55;
	//}}AFX_DATA

	CHiEdit m_Feld36;
	CHiEdit m_Feld37;
	CHiEdit m_Feld38;
	CHiEdit m_Feld40;
	CHiEdit m_Feld46;
	CHiEdit m_Feld47;
	CHiEdit m_Feld48;
	CHiEdit m_Feld49;
	CHiEdit m_Feld50;
	CHiEdit m_Feld111;
	CHiEdit m_Feld57;
	CHiEdit m_Feld58;
	CHiEdit m_Feld59;
	CHiEdit m_Feld56;
	CHiEdit m_Feld115;
	CHiEdit m_Feld60;
	CHiEdit m_Feld61;
	CHiEdit m_Feld62;
	CHiEdit m_Feld116;
	CHiEdit m_Feld117;
	CHiEdit m_Feld63;
	CHiEdit m_Feld64;
	CHiEdit m_Feld69;
	CHiEdit m_Feld65;
	CHiEdit m_Feld66;


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyHill5x5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	CFont cf;
	CHillEncryption *hillklasse;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHill5x5)
	virtual void OnOK();
	virtual void OnDecrypt();
	virtual BOOL OnInitDialog();
	afx_msg void OnVerbose();
	afx_msg void OnPasteKey();
	afx_msg void OnDimension1();
	afx_msg void OnDimension2();
	afx_msg void OnDimension3();
	afx_msg void OnDimension4();
	afx_msg void OnDimension5();
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
	afx_msg void OnEnableAlphCode();
	afx_msg void OnDisableAlphCode();
	afx_msg void OnRowVectorMatrix();
	afx_msg void OnMatrixColumnVector();

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



	afx_msg void OnZufaelligerSchluessel();
	afx_msg void OnGroessereSchluessel();

	afx_msg void OnTextOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_pHillAlphInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_HILLEINGABE_H__218034DD_7572_11D2_8D2B_00C04F795E36__INCLUDED_
