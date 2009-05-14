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
#ifndef AFX_HILLEINGABEGROSS_H__EB1BC795_A3CB_11D3_877D_00C04F795E36__INCLUDED_
#define AFX_HILLEINGABEGROSS_H__EB1BC795_A3CB_11D3_877D_00C04F795E36__INCLUDED_

// HillEingabeGross.h : Header-Datei
//

#include "HillEncryption.h"
#include "Cryptography.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHill10x10 

class CDlgKeyHill10x10 : public CDialog
{
	CBitmapButton m_Paste;
// Konstruktion
public:
	int		m_decrypt;
	unsigned long alphCode;
	unsigned long firstPosNull;
	CSquareMatrixModN * mat;
	void UpdateFeld (CEdit*feld);
	void UpdateAlphCode(CEdit*feld);
	void MatrixEinlesen(CSquareMatrixModN& mat, int dim);
	void MatrixAnzeigen(CSquareMatrixModN& mat);
	bool NaechsterEintrag(int& i, int& j) ;
	int AlleFelderKorrekt(int);
	void AnzeigeDimensionSetzen(int);
	int dim;
	int Display();
	CHiEdit* m_pFelder[HILL_MAX_DIM_GROSS][HILL_MAX_DIM_GROSS];
	CHiEdit* m_pAlphCode[HILL_MAX_DIM_GROSS][HILL_MAX_DIM_GROSS];

	CString getAlphCode(CString alphChar);
	CString getAlphChar(CString alphPos);
	void setFeldAlph(CEdit *feld,CEdit *feldAlph);
	void setFeldAlphCode(CEdit *feld,CEdit *feldAlph);
	void setDoublePos(CEdit *feld);

	CString getDimMessage();

	CDlgKeyHill10x10(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgKeyHill10x10();

	CHillEncryption *getHillKlasse() { return hillklasse; };

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHill10x10)
	enum { IDD = IDD_KEY_HILL_10X10 };
	BOOL	m_Verbose;
	CEdit	m_FeldUnsichtbar;
	class CHiEdit	m_Feld11;
	class CHiEdit	m_Feld12;
	class CHiEdit	m_Feld13;
	class CHiEdit	m_Feld14;
	class CHiEdit	m_Feld15;
	class CHiEdit	m_Feld16;
	class CHiEdit	m_Feld17;
	class CHiEdit	m_Feld18;
	class CHiEdit	m_Feld19;
	class CHiEdit	m_Feld110;
	class CHiEdit	m_Feld21;
	class CHiEdit	m_Feld22;
	class CHiEdit	m_Feld23;
	class CHiEdit	m_Feld24;
	class CHiEdit	m_Feld25;
	class CHiEdit	m_Feld26;
	class CHiEdit	m_Feld27;
	class CHiEdit	m_Feld28;
	class CHiEdit	m_Feld29;
	class CHiEdit	m_Feld210;
	class CHiEdit	m_Feld31;
	class CHiEdit	m_Feld32;
	class CHiEdit	m_Feld33;
	class CHiEdit	m_Feld34;
	class CHiEdit	m_Feld35;
	class CHiEdit	m_Feld36;
	class CHiEdit	m_Feld37;
	class CHiEdit	m_Feld38;
	class CHiEdit	m_Feld39;
	class CHiEdit	m_Feld310;
	class CHiEdit	m_Feld41;
	class CHiEdit	m_Feld42;
	class CHiEdit	m_Feld43;
	class CHiEdit	m_Feld44;
	class CHiEdit	m_Feld45;
	class CHiEdit	m_Feld46;
	class CHiEdit	m_Feld47;
	class CHiEdit	m_Feld48;
	class CHiEdit	m_Feld49;
	class CHiEdit	m_Feld410;
	class CHiEdit	m_Feld51;
	class CHiEdit	m_Feld52;
	class CHiEdit	m_Feld53;
	class CHiEdit	m_Feld54;
	class CHiEdit	m_Feld55;
	class CHiEdit	m_Feld56;
	class CHiEdit	m_Feld57;
	class CHiEdit	m_Feld58;
	class CHiEdit	m_Feld59;
	class CHiEdit	m_Feld510;
	class CHiEdit	m_Feld61;
	class CHiEdit	m_Feld62;
	class CHiEdit	m_Feld63;
	class CHiEdit	m_Feld64;
	class CHiEdit	m_Feld65;
	class CHiEdit	m_Feld66;
	class CHiEdit	m_Feld67;
	class CHiEdit	m_Feld68;
	class CHiEdit	m_Feld69;
	class CHiEdit	m_Feld610;
	class CHiEdit	m_Feld71;
	class CHiEdit	m_Feld72;
	class CHiEdit	m_Feld73;
	class CHiEdit	m_Feld74;
	class CHiEdit	m_Feld75;
	class CHiEdit	m_Feld76;
	class CHiEdit	m_Feld77;
	class CHiEdit	m_Feld78;
	class CHiEdit	m_Feld79;
	class CHiEdit	m_Feld710;
	class CHiEdit	m_Feld81;
	class CHiEdit	m_Feld82;
	class CHiEdit	m_Feld83;
	class CHiEdit	m_Feld84;
	class CHiEdit	m_Feld85;
	class CHiEdit	m_Feld86;
	class CHiEdit	m_Feld87;
	class CHiEdit	m_Feld88;
	class CHiEdit	m_Feld89;
	class CHiEdit	m_Feld810;
	class CHiEdit	m_Feld91;
	class CHiEdit	m_Feld92;
	class CHiEdit	m_Feld93;
	class CHiEdit	m_Feld94;
	class CHiEdit	m_Feld95;
	class CHiEdit	m_Feld96;
	class CHiEdit	m_Feld97;
	class CHiEdit	m_Feld98;
	class CHiEdit	m_Feld99;
	class CHiEdit	m_Feld910;
	class CHiEdit	m_Feld101;
	class CHiEdit	m_Feld102;
	class CHiEdit	m_Feld103;
	class CHiEdit	m_Feld104;
	class CHiEdit	m_Feld105;
	class CHiEdit	m_Feld106;
	class CHiEdit	m_Feld107;
	class CHiEdit	m_Feld108;
	class CHiEdit	m_Feld109;
	class CHiEdit	m_Feld1010;
	//}}AFX_DATA

	class CHiEdit m_Feld40;
	class CHiEdit m_Feld50;
	class CHiEdit m_Feld20;
	class CHiEdit m_Feld90;
	class CHiEdit m_Feld100;
	class CHiEdit m_Feld117;
	class CHiEdit m_Feld118;
	class CHiEdit m_Feld119;
	class CHiEdit m_Feld60;
	class CHiEdit m_Feld125;
	class CHiEdit m_Feld127;
	class CHiEdit m_Feld134;
	class CHiEdit m_Feld135;
	class CHiEdit m_Feld136;
	class CHiEdit m_Feld70;
	class CHiEdit m_Feld137;
	class CHiEdit m_Feld138;
	class CHiEdit m_Feld139;
	class CHiEdit m_Feld80;
	class CHiEdit m_Feld211;
	class CHiEdit m_Feld140;
	class CHiEdit m_Feld141;
	class CHiEdit m_Feld142;
	class CHiEdit m_Feld143;
	class CHiEdit m_Feld144;
	class CHiEdit m_Feld145;
	class CHiEdit m_Feld146;
	class CHiEdit m_Feld147;
	class CHiEdit m_Feld148;
	class CHiEdit m_Feld311;
	class CHiEdit m_Feld149;
	class CHiEdit m_Feld150;
	class CHiEdit m_Feld151;
	class CHiEdit m_Feld152;
	class CHiEdit m_Feld153;
	class CHiEdit m_Feld154;
	class CHiEdit m_Feld155;
	class CHiEdit m_Feld156;
	class CHiEdit m_Feld157;
	class CHiEdit m_Feld411;
	class CHiEdit m_Feld158;
	class CHiEdit m_Feld159;
	class CHiEdit m_Feld113;
	class CHiEdit m_Feld160;
	class CHiEdit m_Feld161;
	class CHiEdit m_Feld162;
	class CHiEdit m_Feld163;
	class CHiEdit m_Feld164;
	class CHiEdit m_Feld165;
	class CHiEdit m_Feld511;
	class CHiEdit m_Feld166;
	class CHiEdit m_Feld167;
	class CHiEdit m_Feld168;
	class CHiEdit m_Feld169;
	class CHiEdit m_Feld170;
	class CHiEdit m_Feld171;
	class CHiEdit m_Feld172;
	class CHiEdit m_Feld173;
	class CHiEdit m_Feld174;
	class CHiEdit m_Feld611;
	class CHiEdit m_Feld175;
	class CHiEdit m_Feld176;
	class CHiEdit m_Feld177;
	class CHiEdit m_Feld178;
	class CHiEdit m_Feld179;
	class CHiEdit m_Feld180;
	class CHiEdit m_Feld181;
	class CHiEdit m_Feld182;
	class CHiEdit m_Feld183;
	class CHiEdit m_Feld711;
	class CHiEdit m_Feld184;
	class CHiEdit m_Feld185;
	class CHiEdit m_Feld186;
	class CHiEdit m_Feld187;
	class CHiEdit m_Feld188;
	class CHiEdit m_Feld189;
	class CHiEdit m_Feld190;
	class CHiEdit m_Feld191;
	class CHiEdit m_Feld192;
	class CHiEdit m_Feld811;
	class CHiEdit m_Feld193;
	class CHiEdit m_Feld194;
	class CHiEdit m_Feld195;
	class CHiEdit m_Feld196;
	class CHiEdit m_Feld197;
	class CHiEdit m_Feld198;
	class CHiEdit m_Feld199;
	class CHiEdit m_Feld200;
	class CHiEdit m_Feld201;
	class CHiEdit m_Feld911;
	class CHiEdit m_Feld202;
	class CHiEdit m_Feld203;
	class CHiEdit m_Feld204;
	class CHiEdit m_Feld205;
	class CHiEdit m_Feld206;
	class CHiEdit m_Feld207;
	class CHiEdit m_Feld208;
	class CHiEdit m_Feld209;
	class CHiEdit m_Feld212;
	class CHiEdit m_Feld1011;




// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyHill10x10)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	CFont cf;
	CHillEncryption *hillklasse;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHill10x10)
	virtual void OnOK();
	virtual void OnDecrypt();
	afx_msg void OnPasteKey();
	virtual BOOL OnInitDialog();
	afx_msg void OnDimension1();
	afx_msg void OnDimension2();
	afx_msg void OnDimension3();
	afx_msg void OnDimension4();
	afx_msg void OnDimension5();
	afx_msg void OnDimension6();
	afx_msg void OnDimension7();
	afx_msg void OnDimension8();
	afx_msg void OnDimension9();
	afx_msg void OnDimension10();
	afx_msg	void OnUpdateMat11();
	afx_msg	void OnUpdateMat12();
	afx_msg	void OnUpdateMat13();
	afx_msg	void OnUpdateMat14();
	afx_msg	void OnUpdateMat15();
	afx_msg	void OnUpdateMat16();
	afx_msg	void OnUpdateMat17();
	afx_msg	void OnUpdateMat18();
	afx_msg	void OnUpdateMat19();
	afx_msg	void OnUpdateMat110();
	afx_msg	void OnUpdateMat21();
	afx_msg	void OnUpdateMat22();
	afx_msg	void OnUpdateMat23();
	afx_msg	void OnUpdateMat24();
	afx_msg	void OnUpdateMat25();
	afx_msg	void OnUpdateMat26();
	afx_msg	void OnUpdateMat27();
	afx_msg	void OnUpdateMat28();
	afx_msg	void OnUpdateMat29();
	afx_msg	void OnUpdateMat210();
	afx_msg	void OnUpdateMat31();
	afx_msg	void OnUpdateMat32();
	afx_msg	void OnUpdateMat33();
	afx_msg	void OnUpdateMat34();
	afx_msg	void OnUpdateMat35();
	afx_msg	void OnUpdateMat36();
	afx_msg	void OnUpdateMat37();
	afx_msg	void OnUpdateMat38();
	afx_msg	void OnUpdateMat39();
	afx_msg	void OnUpdateMat310();
	afx_msg	void OnUpdateMat41();
	afx_msg	void OnUpdateMat42();
	afx_msg	void OnUpdateMat43();
	afx_msg	void OnUpdateMat44();
	afx_msg	void OnUpdateMat45();
	afx_msg	void OnUpdateMat46();
	afx_msg	void OnUpdateMat47();
	afx_msg	void OnUpdateMat48();
	afx_msg	void OnUpdateMat49();
	afx_msg	void OnUpdateMat410();
	afx_msg	void OnUpdateMat51();
	afx_msg	void OnUpdateMat52();
	afx_msg	void OnUpdateMat53();
	afx_msg	void OnUpdateMat54();
	afx_msg	void OnUpdateMat55();
	afx_msg	void OnUpdateMat56();
	afx_msg	void OnUpdateMat57();
	afx_msg	void OnUpdateMat58();
	afx_msg	void OnUpdateMat59();
	afx_msg	void OnUpdateMat510();
	afx_msg	void OnUpdateMat61();
	afx_msg	void OnUpdateMat62();
	afx_msg	void OnUpdateMat63();
	afx_msg	void OnUpdateMat64();
	afx_msg	void OnUpdateMat65();
	afx_msg	void OnUpdateMat66();
	afx_msg	void OnUpdateMat67();
	afx_msg	void OnUpdateMat68();
	afx_msg	void OnUpdateMat69();
	afx_msg	void OnUpdateMat610();
	afx_msg	void OnUpdateMat71();
	afx_msg	void OnUpdateMat72();
	afx_msg	void OnUpdateMat73();
	afx_msg	void OnUpdateMat74();
	afx_msg	void OnUpdateMat75();
	afx_msg	void OnUpdateMat76();
	afx_msg	void OnUpdateMat77();
	afx_msg	void OnUpdateMat78();
	afx_msg	void OnUpdateMat79();
	afx_msg	void OnUpdateMat710();
	afx_msg	void OnUpdateMat81();
	afx_msg	void OnUpdateMat82();
	afx_msg	void OnUpdateMat83();
	afx_msg	void OnUpdateMat84();
	afx_msg	void OnUpdateMat85();
	afx_msg	void OnUpdateMat86();
	afx_msg	void OnUpdateMat87();
	afx_msg	void OnUpdateMat88();
	afx_msg	void OnUpdateMat89();
	afx_msg	void OnUpdateMat810();
	afx_msg	void OnUpdateMat91();
	afx_msg	void OnUpdateMat92();
	afx_msg	void OnUpdateMat93();
	afx_msg	void OnUpdateMat94();
	afx_msg	void OnUpdateMat95();
	afx_msg	void OnUpdateMat96();
	afx_msg	void OnUpdateMat97();
	afx_msg	void OnUpdateMat98();
	afx_msg	void OnUpdateMat99();
	afx_msg	void OnUpdateMat910();
	afx_msg	void OnUpdateMat101();
	afx_msg	void OnUpdateMat102();
	afx_msg	void OnUpdateMat103();
	afx_msg	void OnUpdateMat104();
	afx_msg	void OnUpdateMat105();
	afx_msg	void OnUpdateMat106();
	afx_msg	void OnUpdateMat107();
	afx_msg	void OnUpdateMat108();
	afx_msg	void OnUpdateMat109();
	afx_msg	void OnUpdateMat1010();
	afx_msg void OnZufaelligerSchluessel();
	afx_msg void OnKleinereSchluessel();
	afx_msg void OnRowVectorMatrix();
	afx_msg void OnMatrixColumnVector();

	afx_msg	void OnUpdateMat40();
	afx_msg	void OnUpdateMat50();
	afx_msg	void OnUpdateMat20();
	afx_msg	void OnUpdateMat90();
	afx_msg	void OnUpdateMat100();
	afx_msg	void OnUpdateMat117();
	afx_msg	void OnUpdateMat118();
	afx_msg	void OnUpdateMat119();
	afx_msg	void OnUpdateMat60();
	afx_msg	void OnUpdateMat125();
	afx_msg	void OnUpdateMat127();
	afx_msg	void OnUpdateMat134();
	afx_msg	void OnUpdateMat135();
	afx_msg	void OnUpdateMat136();
	afx_msg	void OnUpdateMat70();
	afx_msg	void OnUpdateMat137();
	afx_msg	void OnUpdateMat138();
	afx_msg	void OnUpdateMat139();
	afx_msg	void OnUpdateMat80();
	afx_msg	void OnUpdateMat211();
	afx_msg	void OnUpdateMat140();
	afx_msg	void OnUpdateMat141();
	afx_msg	void OnUpdateMat142();
	afx_msg	void OnUpdateMat143();
	afx_msg	void OnUpdateMat144();
	afx_msg	void OnUpdateMat145();
	afx_msg	void OnUpdateMat146();
	afx_msg	void OnUpdateMat147();
	afx_msg	void OnUpdateMat148();
	afx_msg	void OnUpdateMat311();
	afx_msg	void OnUpdateMat149();
	afx_msg	void OnUpdateMat150();
	afx_msg	void OnUpdateMat151();
	afx_msg	void OnUpdateMat152();
	afx_msg	void OnUpdateMat153();
	afx_msg	void OnUpdateMat154();
	afx_msg	void OnUpdateMat155();
	afx_msg	void OnUpdateMat156();
	afx_msg	void OnUpdateMat157();
	afx_msg	void OnUpdateMat411();
	afx_msg	void OnUpdateMat158();
	afx_msg	void OnUpdateMat159();
	afx_msg	void OnUpdateMat113();
	afx_msg	void OnUpdateMat160();
	afx_msg	void OnUpdateMat161();
	afx_msg	void OnUpdateMat162();
	afx_msg	void OnUpdateMat163();
	afx_msg	void OnUpdateMat164();
	afx_msg	void OnUpdateMat165();
	afx_msg	void OnUpdateMat511();
	afx_msg	void OnUpdateMat166();
	afx_msg	void OnUpdateMat167();
	afx_msg	void OnUpdateMat168();
	afx_msg	void OnUpdateMat169();
	afx_msg	void OnUpdateMat170();
	afx_msg	void OnUpdateMat171();
	afx_msg	void OnUpdateMat172();
	afx_msg	void OnUpdateMat173();
	afx_msg	void OnUpdateMat174();
	afx_msg	void OnUpdateMat611();
	afx_msg	void OnUpdateMat175();
	afx_msg	void OnUpdateMat176();
	afx_msg	void OnUpdateMat177();
	afx_msg	void OnUpdateMat178();
	afx_msg	void OnUpdateMat179();
	afx_msg	void OnUpdateMat180();
	afx_msg	void OnUpdateMat181();
	afx_msg	void OnUpdateMat182();
	afx_msg	void OnUpdateMat183();
	afx_msg	void OnUpdateMat711();
	afx_msg	void OnUpdateMat184();
	afx_msg	void OnUpdateMat185();
	afx_msg	void OnUpdateMat186();
	afx_msg	void OnUpdateMat187();
	afx_msg	void OnUpdateMat188();
	afx_msg	void OnUpdateMat189();
	afx_msg	void OnUpdateMat190();
	afx_msg	void OnUpdateMat191();
	afx_msg	void OnUpdateMat192();
	afx_msg	void OnUpdateMat811();
	afx_msg	void OnUpdateMat193();
	afx_msg	void OnUpdateMat194();
	afx_msg	void OnUpdateMat195();
	afx_msg	void OnUpdateMat196();
	afx_msg	void OnUpdateMat197();
	afx_msg	void OnUpdateMat198();
	afx_msg	void OnUpdateMat199();
	afx_msg	void OnUpdateMat200();
	afx_msg	void OnUpdateMat201();
	afx_msg	void OnUpdateMat911();
	afx_msg	void OnUpdateMat202();
	afx_msg	void OnUpdateMat203();
	afx_msg	void OnUpdateMat204();
	afx_msg	void OnUpdateMat205();
	afx_msg	void OnUpdateMat206();
	afx_msg	void OnUpdateMat207();
	afx_msg	void OnUpdateMat208();
	afx_msg	void OnUpdateMat209();
	afx_msg	void OnUpdateMat212();
	afx_msg	void OnUpdateMat1011();

	afx_msg void OnEnableAlphCode();
	afx_msg void OnDisableAlphCode();


	afx_msg void OnExitMat40();
	afx_msg void OnExitMat50();
	afx_msg void OnExitMat20();
	afx_msg void OnExitMat90();
	afx_msg void OnExitMat100();
	afx_msg void OnExitMat117();
	afx_msg void OnExitMat118();
	afx_msg void OnExitMat119();
	afx_msg void OnExitMat60();
	afx_msg void OnExitMat125();
	afx_msg void OnExitMat127();
	afx_msg void OnExitMat134();
	afx_msg void OnExitMat135();
	afx_msg void OnExitMat136();
	afx_msg void OnExitMat70();
	afx_msg void OnExitMat137();
	afx_msg void OnExitMat138();
	afx_msg void OnExitMat139();
	afx_msg void OnExitMat80();
	afx_msg void OnExitMat211();
	afx_msg void OnExitMat140();
	afx_msg void OnExitMat141();
	afx_msg void OnExitMat142();
	afx_msg void OnExitMat143();
	afx_msg void OnExitMat144();
	afx_msg void OnExitMat145();
	afx_msg void OnExitMat146();
	afx_msg void OnExitMat147();
	afx_msg void OnExitMat148();
	afx_msg void OnExitMat311();
	afx_msg void OnExitMat149();
	afx_msg void OnExitMat150();
	afx_msg void OnExitMat151();
	afx_msg void OnExitMat152();
	afx_msg void OnExitMat153();
	afx_msg void OnExitMat154();
	afx_msg void OnExitMat155();
	afx_msg void OnExitMat156();
	afx_msg void OnExitMat157();
	afx_msg void OnExitMat411();
	afx_msg void OnExitMat158();
	afx_msg void OnExitMat159();
	afx_msg void OnExitMat113();
	afx_msg void OnExitMat160();
	afx_msg void OnExitMat161();
	afx_msg void OnExitMat162();
	afx_msg void OnExitMat163();
	afx_msg void OnExitMat164();
	afx_msg void OnExitMat165();
	afx_msg void OnExitMat511();
	afx_msg void OnExitMat166();
	afx_msg void OnExitMat167();
	afx_msg void OnExitMat168();
	afx_msg void OnExitMat169();
	afx_msg void OnExitMat170();
	afx_msg void OnExitMat171();
	afx_msg void OnExitMat172();
	afx_msg void OnExitMat173();
	afx_msg void OnExitMat174();
	afx_msg void OnExitMat611();
	afx_msg void OnExitMat175();
	afx_msg void OnExitMat176();
	afx_msg void OnExitMat177();
	afx_msg void OnExitMat178();
	afx_msg void OnExitMat179();
	afx_msg void OnExitMat180();
	afx_msg void OnExitMat181();
	afx_msg void OnExitMat182();
	afx_msg void OnExitMat183();
	afx_msg void OnExitMat711();
	afx_msg void OnExitMat184();
	afx_msg void OnExitMat185();
	afx_msg void OnExitMat186();
	afx_msg void OnExitMat187();
	afx_msg void OnExitMat188();
	afx_msg void OnExitMat189();
	afx_msg void OnExitMat190();
	afx_msg void OnExitMat191();
	afx_msg void OnExitMat192();
	afx_msg void OnExitMat811();
	afx_msg void OnExitMat193();
	afx_msg void OnExitMat194();
	afx_msg void OnExitMat195();
	afx_msg void OnExitMat196();
	afx_msg void OnExitMat197();
	afx_msg void OnExitMat198();
	afx_msg void OnExitMat199();
	afx_msg void OnExitMat200();
	afx_msg void OnExitMat201();
	afx_msg void OnExitMat911();
	afx_msg void OnExitMat202();
	afx_msg void OnExitMat203();
	afx_msg void OnExitMat204();
	afx_msg void OnExitMat205();
	afx_msg void OnExitMat206();
	afx_msg void OnExitMat207();
	afx_msg void OnExitMat208();
	afx_msg void OnExitMat209();
	afx_msg void OnExitMat212();
	afx_msg void OnExitMat1011();

	afx_msg void OnTextOptions();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_pHillAlphInfo;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton69();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_HILLEINGABEGROSS_H__EB1BC795_A3CB_11D3_877D_00C04F795E36__INCLUDED_
