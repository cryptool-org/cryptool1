//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
#ifndef AFX_HILLEINGABE_H__218034DD_7572_11D2_8D2B_00C04F795E36__INCLUDED_
#define AFX_HILLEINGABE_H__218034DD_7572_11D2_8D2B_00C04F795E36__INCLUDED_

// HillEingabe.h : Header-Datei
//

#include "hill.h"
#include "crypt.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CHillEingabe 

class CHiEdit : public CEdit
{
protected:
	//{{AFX_MSG(CHiEdit)
	afx_msg void OnLButtonUp(UINT, CPoint);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
};

class CHillEingabe : public CDialog
{
	CBitmapButton m_Paste;

// Konstruktion
public:
	int		m_decrypt;
	square_matrix * mat;
	void UpdateFeld (CEdit*feld);
	void MatrixEinlesen(square_matrix& mat, int dim);
	void MatrixAnzeigen(square_matrix& mat);
	bool NaechsterEintrag(int& i, int& j) ;
	int AlleFelderKorrekt(int);
	void AnzeigeDimensionSetzen(int);
	int dim;
	int Display(hill *);
	class CHiEdit* m_pFelder[HILL_MAX_DIM][HILL_MAX_DIM];
	CHillEingabe(hill *hillkl, CWnd* pParent = NULL);   // Standardkonstruktor
	~CHillEingabe();

// Dialogfelddaten
	//{{AFX_DATA(CHillEingabe)
	enum { IDD = IDD_DIALOG_SCHLUESSEL_HILL_EINGABE };
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


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CHillEingabe)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	CFont cf;
	hill *hillklasse;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CHillEingabe)
	virtual void OnOK();
	virtual void OnDecrypt();
	virtual BOOL OnInitDialog();
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
	afx_msg void OnZufaelligerSchluessel();
	afx_msg void OnGroessereSchluessel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_HILLEINGABE_H__218034DD_7572_11D2_8D2B_00C04F795E36__INCLUDED_
