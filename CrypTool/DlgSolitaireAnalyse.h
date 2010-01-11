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


#pragma once

#include "Solitaire.h"
#include "afxwin.h"

// CDlgSolitaireAnalyse-Dialogfeld

class CDlgSolitaireAnalyse : public CDialog
{
	DECLARE_DYNAMIC(CDlgSolitaireAnalyse)

public:
	CDlgSolitaireAnalyse(char* infile, CString oldTitle,CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgSolitaireAnalyse();
	Deck* myD;
	int zaehler;
	CString vorgabe;
	char* infile;
	CString oldTitle;

// Dialogfelddaten
	enum { IDD = IDD_SOLITAIRE_ANALYSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	void    DoCard( int k, CButton &button );
	DECLARE_MESSAGE_MAP()
public:
	int kartenanzahl;
	int kartenanzahlneu;
	int vorgaben;
	CString deckart;
	CString gefundenesDeck;
	
	void enablebut(bool art);
	void vorgabesetzen();

	afx_msg void OnCbnSelchangeKartenanzahl();
	//afx_msg void OnCbnSelchangeCombo2();

	CButton but1;
	CButton but2;
	CButton but3;
	CButton but4;
	CButton but5;
	CButton but6;
	CButton but7;
	CButton but8;
	CButton but9;
	CButton but10;
	CButton but11;
	CButton but12;
	CButton but13;
	CButton but14;
	CButton but15;
	CButton but16;
	CButton but17;
	CButton but18;
	CButton but19;
	CButton but20;
	CButton but21;
	CButton but22;
	CButton but23;
	CButton but24;
	CButton but25;
	CButton but26;
	CButton but27;
	CButton but28;
	CButton but29;
	CButton but30;
	CButton but31;
	CButton but32;
	CButton but33;
	CButton but34;
	CButton but35;
	CButton but36;
	CButton but37;
	CButton but38;
	CButton but39;
	CButton but40;
	CButton but41;
	CButton but42;
	CButton but43;
	CButton but44;
	CButton but45;
	CButton but46;
	CButton but47;
	CButton but48;
	CButton but49;
	CButton but50;
	CButton but51;
	CButton but52;
	CButton but53;
	CButton but4054;
	afx_msg void OnBnClickedButton9();	
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton26();
	afx_msg void OnBnClickedButton27();
	afx_msg void OnBnClickedButton28();
	afx_msg void OnBnClickedButton29();
	afx_msg void OnBnClickedButton30();
	afx_msg void OnBnClickedButton31();
	afx_msg void OnBnClickedButton32();
	afx_msg void OnBnClickedButton33();
	afx_msg void OnBnClickedButton34();
	afx_msg void OnBnClickedButton35();
	afx_msg void OnBnClickedButton36();
	afx_msg void OnBnClickedButton37();
	afx_msg void OnBnClickedButton38();
	afx_msg void OnBnClickedButton39();
	afx_msg void OnBnClickedButton40();
	afx_msg void OnBnClickedButton41();
	afx_msg void OnBnClickedButton42();
	afx_msg void OnBnClickedButton43();
	afx_msg void OnBnClickedButton44();
	afx_msg void OnBnClickedButton45();
	afx_msg void OnBnClickedButton46();
	afx_msg void OnBnClickedButton47();
	afx_msg void OnBnClickedButton48();
	afx_msg void OnBnClickedButton49();
	afx_msg void OnBnClickedButton50();
	afx_msg void OnBnClickedButton51();
	afx_msg void OnBnClickedButton52();
	afx_msg void OnBnClickedButton53();
	afx_msg void OnBnClickedButton54();
	afx_msg void OnBnClickedButton55();
	afx_msg void OnBnClickedButton56();
	afx_msg void OnBnClickedButton57();
	afx_msg void OnBnClickedButton58();
	afx_msg void OnBnClickedButton59();
	afx_msg void OnBnClickedButton60();
	afx_msg void OnBnClickedButton61();
	afx_msg void OnBnClickedButton62();
	CButton m_Reset;
	afx_msg void OnBnClickedButton63();
	CButton vorne;
	CButton hinten;
	CButton waehlen;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CString zwischendeck;
	CString Initialdeck;
	//CButton starten;
	//CButton man_hinten;
	//afx_msg void OnBnClickedButton4();
	//afx_msg void OnBnClickedButton5();
	afx_msg void OnEnChangeEdit132();
	CButton schluesselerzeugen;
	afx_msg void OnBnClickedButton4();
	CEdit schluessel;
	CString schluesselstrom;
	afx_msg void OnBnClickedOk();
	CButton entschluesseln;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	CComboBox m_kartenanzahl;
};
