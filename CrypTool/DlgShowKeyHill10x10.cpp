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
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
// HillSchluesselAusgabeGross.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowKeyHill10x10.h"
#include "SquareMatrixModN.h"
#include "KeyRepository.h"
#include "HillEncryption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKeyHill10x10 


CDlgShowKeyHill10x10::CDlgShowKeyHill10x10(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowKeyHill10x10::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShowKeyHill10x10)
	m_Feld11 = _T("");
	m_Feld12 = _T("");
	m_Feld13 = _T("");
	m_Feld14 = _T("");
	m_Feld15 = _T("");
	m_Feld16 = _T("");
	m_Feld17 = _T("");
	m_Feld18 = _T("");
	m_Feld19 = _T("");
	m_Feld110 = _T("");
	m_Feld21 = _T("");
	m_Feld22 = _T("");
	m_Feld23 = _T("");
	m_Feld24 = _T("");
	m_Feld25 = _T("");
	m_Feld26 = _T("");
	m_Feld27 = _T("");
	m_Feld28 = _T("");
	m_Feld29 = _T("");
	m_Feld210 = _T("");
	m_Feld31 = _T("");
	m_Feld32 = _T("");
	m_Feld33 = _T("");
	m_Feld34 = _T("");
	m_Feld35 = _T("");
	m_Feld36 = _T("");
	m_Feld37 = _T("");
	m_Feld38 = _T("");
	m_Feld39 = _T("");
	m_Feld310 = _T("");
	m_Feld41 = _T("");
	m_Feld42 = _T("");
	m_Feld43 = _T("");
	m_Feld44 = _T("");
	m_Feld45 = _T("");
	m_Feld46 = _T("");
	m_Feld47 = _T("");
	m_Feld48 = _T("");
	m_Feld49 = _T("");
	m_Feld410 = _T("");
	m_Feld51 = _T("");
	m_Feld52 = _T("");
	m_Feld53 = _T("");
	m_Feld54 = _T("");
	m_Feld55 = _T("");
	m_Feld56 = _T("");
	m_Feld57 = _T("");
	m_Feld58 = _T("");
	m_Feld59 = _T("");
	m_Feld510 = _T("");
	m_Feld61 = _T("");
	m_Feld62 = _T("");
	m_Feld63 = _T("");
	m_Feld64 = _T("");
	m_Feld65 = _T("");
	m_Feld66 = _T("");
	m_Feld67 = _T("");
	m_Feld68 = _T("");
	m_Feld69 = _T("");
	m_Feld610 = _T("");
	m_Feld71 = _T("");
	m_Feld72 = _T("");
	m_Feld73 = _T("");
	m_Feld74 = _T("");
	m_Feld75 = _T("");
	m_Feld76 = _T("");
	m_Feld77 = _T("");
	m_Feld78 = _T("");
	m_Feld79 = _T("");
	m_Feld710 = _T("");
	m_Feld81 = _T("");
	m_Feld82 = _T("");
	m_Feld83 = _T("");
	m_Feld84 = _T("");
	m_Feld85 = _T("");
	m_Feld86 = _T("");
	m_Feld87 = _T("");
	m_Feld88 = _T("");
	m_Feld89 = _T("");
	m_Feld810 = _T("");
	m_Feld91 = _T("");
	m_Feld92 = _T("");
	m_Feld93 = _T("");
	m_Feld94 = _T("");
	m_Feld95 = _T("");
	m_Feld96 = _T("");
	m_Feld97 = _T("");
	m_Feld98 = _T("");
	m_Feld99 = _T("");
	m_Feld910 = _T("");
	m_Feld101 = _T("");
	m_Feld102 = _T("");
	m_Feld103 = _T("");
	m_Feld104 = _T("");
	m_Feld105 = _T("");
	m_Feld106 = _T("");
	m_Feld107 = _T("");
	m_Feld108 = _T("");
	m_Feld109 = _T("");
	m_Feld1010 = _T("");
	m_decrypt = 0;
	//}}AFX_DATA_INIT

	decrypt_vorher = m_decrypt;

	m_pFelder[0][0] = &m_Feld11;
	m_pFelder[0][1] = &m_Feld12;
	m_pFelder[0][2] = &m_Feld13;
	m_pFelder[0][3] = &m_Feld14;
	m_pFelder[0][4] = &m_Feld15;
	m_pFelder[0][5] = &m_Feld16;
	m_pFelder[0][6] = &m_Feld17;
	m_pFelder[0][7] = &m_Feld18;
	m_pFelder[0][8] = &m_Feld19;
	m_pFelder[0][9] = &m_Feld110;
	m_pFelder[1][0] = &m_Feld21;
	m_pFelder[1][1] = &m_Feld22;
	m_pFelder[1][2] = &m_Feld23;
	m_pFelder[1][3] = &m_Feld24;
	m_pFelder[1][4] = &m_Feld25;
	m_pFelder[1][5] = &m_Feld26;
	m_pFelder[1][6] = &m_Feld27;
	m_pFelder[1][7] = &m_Feld28;
	m_pFelder[1][8] = &m_Feld29;
	m_pFelder[1][9] = &m_Feld210;
	m_pFelder[2][0] = &m_Feld31;
	m_pFelder[2][1] = &m_Feld32;
	m_pFelder[2][2] = &m_Feld33;
	m_pFelder[2][3] = &m_Feld34;
	m_pFelder[2][4] = &m_Feld35;
	m_pFelder[2][5] = &m_Feld36;
	m_pFelder[2][6] = &m_Feld37;
	m_pFelder[2][7] = &m_Feld38;
	m_pFelder[2][8] = &m_Feld39;
	m_pFelder[2][9] = &m_Feld310;
	m_pFelder[3][0] = &m_Feld41;
	m_pFelder[3][1] = &m_Feld42;
	m_pFelder[3][2] = &m_Feld43;
	m_pFelder[3][3] = &m_Feld44;
	m_pFelder[3][4] = &m_Feld45;
	m_pFelder[3][5] = &m_Feld46;
	m_pFelder[3][6] = &m_Feld47;
	m_pFelder[3][7] = &m_Feld48;
	m_pFelder[3][8] = &m_Feld49;
	m_pFelder[3][9] = &m_Feld410;
	m_pFelder[4][0] = &m_Feld51;
	m_pFelder[4][1] = &m_Feld52;
	m_pFelder[4][2] = &m_Feld53;
	m_pFelder[4][3] = &m_Feld54;
	m_pFelder[4][4] = &m_Feld55;
	m_pFelder[4][5] = &m_Feld56;
	m_pFelder[4][6] = &m_Feld57;
	m_pFelder[4][7] = &m_Feld58;
	m_pFelder[4][8] = &m_Feld59;
	m_pFelder[4][9] = &m_Feld510;
	m_pFelder[5][0] = &m_Feld61;
	m_pFelder[5][1] = &m_Feld62;
	m_pFelder[5][2] = &m_Feld63;
	m_pFelder[5][3] = &m_Feld64;
	m_pFelder[5][4] = &m_Feld65;
	m_pFelder[5][5] = &m_Feld66;
	m_pFelder[5][6] = &m_Feld67;
	m_pFelder[5][7] = &m_Feld68;
	m_pFelder[5][8] = &m_Feld69;
	m_pFelder[5][9] = &m_Feld610;
	m_pFelder[6][0] = &m_Feld71;
	m_pFelder[6][1] = &m_Feld72;
	m_pFelder[6][2] = &m_Feld73;
	m_pFelder[6][3] = &m_Feld74;
	m_pFelder[6][4] = &m_Feld75;
	m_pFelder[6][5] = &m_Feld76;
	m_pFelder[6][6] = &m_Feld77;
	m_pFelder[6][7] = &m_Feld78;
	m_pFelder[6][8] = &m_Feld79;
	m_pFelder[6][9] = &m_Feld710;
	m_pFelder[7][0] = &m_Feld81;
	m_pFelder[7][1] = &m_Feld82;
	m_pFelder[7][2] = &m_Feld83;
	m_pFelder[7][3] = &m_Feld84;
	m_pFelder[7][4] = &m_Feld85;
	m_pFelder[7][5] = &m_Feld86;
	m_pFelder[7][6] = &m_Feld87;
	m_pFelder[7][7] = &m_Feld88;
	m_pFelder[7][8] = &m_Feld89;
	m_pFelder[7][9] = &m_Feld810;
	m_pFelder[8][0] = &m_Feld91;
	m_pFelder[8][1] = &m_Feld92;
	m_pFelder[8][2] = &m_Feld93;
	m_pFelder[8][3] = &m_Feld94;
	m_pFelder[8][4] = &m_Feld95;
	m_pFelder[8][5] = &m_Feld96;
	m_pFelder[8][6] = &m_Feld97;
	m_pFelder[8][7] = &m_Feld98;
	m_pFelder[8][8] = &m_Feld99;
	m_pFelder[8][9] = &m_Feld910;
	m_pFelder[9][0] = &m_Feld101;
	m_pFelder[9][1] = &m_Feld102;
	m_pFelder[9][2] = &m_Feld103;
	m_pFelder[9][3] = &m_Feld104;
	m_pFelder[9][4] = &m_Feld105;
	m_pFelder[9][5] = &m_Feld106;
	m_pFelder[9][6] = &m_Feld107;
	m_pFelder[9][7] = &m_Feld108;
	m_pFelder[9][8] = &m_Feld109;
	m_pFelder[9][9] = &m_Feld1010;
}


void CDlgShowKeyHill10x10::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowKeyHill10x10)
	DDX_Control(pDX, IDC_EDIT1, m_FeldUnsichtbar);
	DDX_Text(pDX, IDC_EDIT11, m_Feld11);
	DDX_Text(pDX, IDC_EDIT12, m_Feld12);
	DDX_Text(pDX, IDC_EDIT13, m_Feld13);
	DDX_Text(pDX, IDC_EDIT14, m_Feld14);
	DDX_Text(pDX, IDC_EDIT15, m_Feld15);
	DDX_Text(pDX, IDC_EDIT16, m_Feld16);
	DDX_Text(pDX, IDC_EDIT17, m_Feld17);
	DDX_Text(pDX, IDC_EDIT18, m_Feld18);
	DDX_Text(pDX, IDC_EDIT19, m_Feld19);
	DDX_Text(pDX, IDC_EDIT110, m_Feld110);
	DDX_Text(pDX, IDC_EDIT21, m_Feld21);
	DDX_Text(pDX, IDC_EDIT22, m_Feld22);
	DDX_Text(pDX, IDC_EDIT23, m_Feld23);
	DDX_Text(pDX, IDC_EDIT24, m_Feld24);
	DDX_Text(pDX, IDC_EDIT25, m_Feld25);
	DDX_Text(pDX, IDC_EDIT26, m_Feld26);
	DDX_Text(pDX, IDC_EDIT27, m_Feld27);
	DDX_Text(pDX, IDC_EDIT28, m_Feld28);
	DDX_Text(pDX, IDC_EDIT29, m_Feld29);
	DDX_Text(pDX, IDC_EDIT210, m_Feld210);
	DDX_Text(pDX, IDC_EDIT31, m_Feld31);
	DDX_Text(pDX, IDC_EDIT32, m_Feld32);
	DDX_Text(pDX, IDC_EDIT33, m_Feld33);
	DDX_Text(pDX, IDC_EDIT34, m_Feld34);
	DDX_Text(pDX, IDC_EDIT35, m_Feld35);
	DDX_Text(pDX, IDC_EDIT36, m_Feld36);
	DDX_Text(pDX, IDC_EDIT37, m_Feld37);
	DDX_Text(pDX, IDC_EDIT38, m_Feld38);
	DDX_Text(pDX, IDC_EDIT39, m_Feld39);
	DDX_Text(pDX, IDC_EDIT310, m_Feld310);
	DDX_Text(pDX, IDC_EDIT41, m_Feld41);
	DDX_Text(pDX, IDC_EDIT42, m_Feld42);
	DDX_Text(pDX, IDC_EDIT43, m_Feld43);
	DDX_Text(pDX, IDC_EDIT44, m_Feld44);
	DDX_Text(pDX, IDC_EDIT45, m_Feld45);
	DDX_Text(pDX, IDC_EDIT46, m_Feld46);
	DDX_Text(pDX, IDC_EDIT47, m_Feld47);
	DDX_Text(pDX, IDC_EDIT48, m_Feld48);
	DDX_Text(pDX, IDC_EDIT49, m_Feld49);
	DDX_Text(pDX, IDC_EDIT410, m_Feld410);
	DDX_Text(pDX, IDC_EDIT51, m_Feld51);
	DDX_Text(pDX, IDC_EDIT52, m_Feld52);
	DDX_Text(pDX, IDC_EDIT53, m_Feld53);
	DDX_Text(pDX, IDC_EDIT54, m_Feld54);
	DDX_Text(pDX, IDC_EDIT55, m_Feld55);
	DDX_Text(pDX, IDC_EDIT56, m_Feld56);
	DDX_Text(pDX, IDC_EDIT57, m_Feld57);
	DDX_Text(pDX, IDC_EDIT58, m_Feld58);
	DDX_Text(pDX, IDC_EDIT59, m_Feld59);
	DDX_Text(pDX, IDC_EDIT510, m_Feld510);
	DDX_Text(pDX, IDC_EDIT61, m_Feld61);
	DDX_Text(pDX, IDC_EDIT62, m_Feld62);
	DDX_Text(pDX, IDC_EDIT63, m_Feld63);
	DDX_Text(pDX, IDC_EDIT64, m_Feld64);
	DDX_Text(pDX, IDC_EDIT65, m_Feld65);
	DDX_Text(pDX, IDC_EDIT66, m_Feld66);
	DDX_Text(pDX, IDC_EDIT67, m_Feld67);
	DDX_Text(pDX, IDC_EDIT68, m_Feld68);
	DDX_Text(pDX, IDC_EDIT69, m_Feld69);
	DDX_Text(pDX, IDC_EDIT610, m_Feld610);
	DDX_Text(pDX, IDC_EDIT71, m_Feld71);
	DDX_Text(pDX, IDC_EDIT72, m_Feld72);
	DDX_Text(pDX, IDC_EDIT73, m_Feld73);
	DDX_Text(pDX, IDC_EDIT74, m_Feld74);
	DDX_Text(pDX, IDC_EDIT75, m_Feld75);
	DDX_Text(pDX, IDC_EDIT76, m_Feld76);
	DDX_Text(pDX, IDC_EDIT77, m_Feld77);
	DDX_Text(pDX, IDC_EDIT78, m_Feld78);
	DDX_Text(pDX, IDC_EDIT79, m_Feld79);
	DDX_Text(pDX, IDC_EDIT710, m_Feld710);
	DDX_Text(pDX, IDC_EDIT81, m_Feld81);
	DDX_Text(pDX, IDC_EDIT82, m_Feld82);
	DDX_Text(pDX, IDC_EDIT83, m_Feld83);
	DDX_Text(pDX, IDC_EDIT84, m_Feld84);
	DDX_Text(pDX, IDC_EDIT85, m_Feld85);
	DDX_Text(pDX, IDC_EDIT86, m_Feld86);
	DDX_Text(pDX, IDC_EDIT87, m_Feld87);
	DDX_Text(pDX, IDC_EDIT88, m_Feld88);
	DDX_Text(pDX, IDC_EDIT89, m_Feld89);
	DDX_Text(pDX, IDC_EDIT810, m_Feld810);
	DDX_Text(pDX, IDC_EDIT91, m_Feld91);
	DDX_Text(pDX, IDC_EDIT92, m_Feld92);
	DDX_Text(pDX, IDC_EDIT93, m_Feld93);
	DDX_Text(pDX, IDC_EDIT94, m_Feld94);
	DDX_Text(pDX, IDC_EDIT95, m_Feld95);
	DDX_Text(pDX, IDC_EDIT96, m_Feld96);
	DDX_Text(pDX, IDC_EDIT97, m_Feld97);
	DDX_Text(pDX, IDC_EDIT98, m_Feld98);
	DDX_Text(pDX, IDC_EDIT99, m_Feld99);
	DDX_Text(pDX, IDC_EDIT910, m_Feld910);
	DDX_Text(pDX, IDC_EDIT101, m_Feld101);
	DDX_Text(pDX, IDC_EDIT102, m_Feld102);
	DDX_Text(pDX, IDC_EDIT103, m_Feld103);
	DDX_Text(pDX, IDC_EDIT104, m_Feld104);
	DDX_Text(pDX, IDC_EDIT105, m_Feld105);
	DDX_Text(pDX, IDC_EDIT106, m_Feld106);
	DDX_Text(pDX, IDC_EDIT107, m_Feld107);
	DDX_Text(pDX, IDC_EDIT108, m_Feld108);
	DDX_Text(pDX, IDC_EDIT109, m_Feld109);
	DDX_Text(pDX, IDC_EDIT1010, m_Feld1010);
	DDX_Control(pDX, IDC_EDIT11, m_ControlFeld11);
	DDX_Control(pDX, IDC_EDIT12, m_ControlFeld12);
	DDX_Control(pDX, IDC_EDIT13, m_ControlFeld13);
	DDX_Control(pDX, IDC_EDIT14, m_ControlFeld14);
	DDX_Control(pDX, IDC_EDIT15, m_ControlFeld15);
	DDX_Control(pDX, IDC_EDIT16, m_ControlFeld16);
	DDX_Control(pDX, IDC_EDIT17, m_ControlFeld17);
	DDX_Control(pDX, IDC_EDIT18, m_ControlFeld18);
	DDX_Control(pDX, IDC_EDIT19, m_ControlFeld19);
	DDX_Control(pDX, IDC_EDIT110, m_ControlFeld110);
	DDX_Control(pDX, IDC_EDIT21, m_ControlFeld21);
	DDX_Control(pDX, IDC_EDIT22, m_ControlFeld22);
	DDX_Control(pDX, IDC_EDIT23, m_ControlFeld23);
	DDX_Control(pDX, IDC_EDIT24, m_ControlFeld24);
	DDX_Control(pDX, IDC_EDIT25, m_ControlFeld25);
	DDX_Control(pDX, IDC_EDIT26, m_ControlFeld26);
	DDX_Control(pDX, IDC_EDIT27, m_ControlFeld27);
	DDX_Control(pDX, IDC_EDIT28, m_ControlFeld28);
	DDX_Control(pDX, IDC_EDIT29, m_ControlFeld29);
	DDX_Control(pDX, IDC_EDIT210, m_ControlFeld210);
	DDX_Control(pDX, IDC_EDIT31, m_ControlFeld31);
	DDX_Control(pDX, IDC_EDIT32, m_ControlFeld32);
	DDX_Control(pDX, IDC_EDIT33, m_ControlFeld33);
	DDX_Control(pDX, IDC_EDIT34, m_ControlFeld34);
	DDX_Control(pDX, IDC_EDIT35, m_ControlFeld35);
	DDX_Control(pDX, IDC_EDIT36, m_ControlFeld36);
	DDX_Control(pDX, IDC_EDIT37, m_ControlFeld37);
	DDX_Control(pDX, IDC_EDIT38, m_ControlFeld38);
	DDX_Control(pDX, IDC_EDIT39, m_ControlFeld39);
	DDX_Control(pDX, IDC_EDIT310, m_ControlFeld310);
	DDX_Control(pDX, IDC_EDIT41, m_ControlFeld41);
	DDX_Control(pDX, IDC_EDIT42, m_ControlFeld42);
	DDX_Control(pDX, IDC_EDIT43, m_ControlFeld43);
	DDX_Control(pDX, IDC_EDIT44, m_ControlFeld44);
	DDX_Control(pDX, IDC_EDIT45, m_ControlFeld45);
	DDX_Control(pDX, IDC_EDIT46, m_ControlFeld46);
	DDX_Control(pDX, IDC_EDIT47, m_ControlFeld47);
	DDX_Control(pDX, IDC_EDIT48, m_ControlFeld48);
	DDX_Control(pDX, IDC_EDIT49, m_ControlFeld49);
	DDX_Control(pDX, IDC_EDIT410, m_ControlFeld410);
	DDX_Control(pDX, IDC_EDIT51, m_ControlFeld51);
	DDX_Control(pDX, IDC_EDIT52, m_ControlFeld52);
	DDX_Control(pDX, IDC_EDIT53, m_ControlFeld53);
	DDX_Control(pDX, IDC_EDIT54, m_ControlFeld54);
	DDX_Control(pDX, IDC_EDIT55, m_ControlFeld55);
	DDX_Control(pDX, IDC_EDIT56, m_ControlFeld56);
	DDX_Control(pDX, IDC_EDIT57, m_ControlFeld57);
	DDX_Control(pDX, IDC_EDIT58, m_ControlFeld58);
	DDX_Control(pDX, IDC_EDIT59, m_ControlFeld59);
	DDX_Control(pDX, IDC_EDIT510, m_ControlFeld510);
	DDX_Control(pDX, IDC_EDIT61, m_ControlFeld61);
	DDX_Control(pDX, IDC_EDIT62, m_ControlFeld62);
	DDX_Control(pDX, IDC_EDIT63, m_ControlFeld63);
	DDX_Control(pDX, IDC_EDIT64, m_ControlFeld64);
	DDX_Control(pDX, IDC_EDIT65, m_ControlFeld65);
	DDX_Control(pDX, IDC_EDIT66, m_ControlFeld66);
	DDX_Control(pDX, IDC_EDIT67, m_ControlFeld67);
	DDX_Control(pDX, IDC_EDIT68, m_ControlFeld68);
	DDX_Control(pDX, IDC_EDIT69, m_ControlFeld69);
	DDX_Control(pDX, IDC_EDIT610, m_ControlFeld610);
	DDX_Control(pDX, IDC_EDIT71, m_ControlFeld71);
	DDX_Control(pDX, IDC_EDIT72, m_ControlFeld72);
	DDX_Control(pDX, IDC_EDIT73, m_ControlFeld73);
	DDX_Control(pDX, IDC_EDIT74, m_ControlFeld74);
	DDX_Control(pDX, IDC_EDIT75, m_ControlFeld75);
	DDX_Control(pDX, IDC_EDIT76, m_ControlFeld76);
	DDX_Control(pDX, IDC_EDIT77, m_ControlFeld77);
	DDX_Control(pDX, IDC_EDIT78, m_ControlFeld78);
	DDX_Control(pDX, IDC_EDIT79, m_ControlFeld79);
	DDX_Control(pDX, IDC_EDIT710, m_ControlFeld710);
	DDX_Control(pDX, IDC_EDIT81, m_ControlFeld81);
	DDX_Control(pDX, IDC_EDIT82, m_ControlFeld82);
	DDX_Control(pDX, IDC_EDIT83, m_ControlFeld83);
	DDX_Control(pDX, IDC_EDIT84, m_ControlFeld84);
	DDX_Control(pDX, IDC_EDIT85, m_ControlFeld85);
	DDX_Control(pDX, IDC_EDIT86, m_ControlFeld86);
	DDX_Control(pDX, IDC_EDIT87, m_ControlFeld87);
	DDX_Control(pDX, IDC_EDIT88, m_ControlFeld88);
	DDX_Control(pDX, IDC_EDIT89, m_ControlFeld89);
	DDX_Control(pDX, IDC_EDIT810, m_ControlFeld810);
	DDX_Control(pDX, IDC_EDIT91, m_ControlFeld91);
	DDX_Control(pDX, IDC_EDIT92, m_ControlFeld92);
	DDX_Control(pDX, IDC_EDIT93, m_ControlFeld93);
	DDX_Control(pDX, IDC_EDIT94, m_ControlFeld94);
	DDX_Control(pDX, IDC_EDIT95, m_ControlFeld95);
	DDX_Control(pDX, IDC_EDIT96, m_ControlFeld96);
	DDX_Control(pDX, IDC_EDIT97, m_ControlFeld97);
	DDX_Control(pDX, IDC_EDIT98, m_ControlFeld98);
	DDX_Control(pDX, IDC_EDIT99, m_ControlFeld99);
	DDX_Control(pDX, IDC_EDIT910, m_ControlFeld910);
	DDX_Control(pDX, IDC_EDIT101, m_ControlFeld101);
	DDX_Control(pDX, IDC_EDIT102, m_ControlFeld102);
	DDX_Control(pDX, IDC_EDIT103, m_ControlFeld103);
	DDX_Control(pDX, IDC_EDIT104, m_ControlFeld104);
	DDX_Control(pDX, IDC_EDIT105, m_ControlFeld105);
	DDX_Control(pDX, IDC_EDIT106, m_ControlFeld106);
	DDX_Control(pDX, IDC_EDIT107, m_ControlFeld107);
	DDX_Control(pDX, IDC_EDIT108, m_ControlFeld108);
	DDX_Control(pDX, IDC_EDIT109, m_ControlFeld109);
	DDX_Control(pDX, IDC_EDIT1010, m_ControlFeld1010);
	DDX_Radio(pDX, IDC_RADIO1, m_decrypt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowKeyHill10x10, CDialog)
	//{{AFX_MSG_MAP(CDlgShowKeyHill10x10)
	ON_BN_CLICKED(IDC_DECRYPT, OnDecrypt)
	ON_BN_CLICKED(IDC_RADIO1, OnVerschluesseln)
	ON_BN_CLICKED(IDC_RADIO2, OnEntschluesseln)
	ON_BN_CLICKED(IDC_BUTTON1, OnKopieren)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowKeyHill10x10 

void CDlgShowKeyHill10x10::OnDecrypt() 
{
	UpdateData(TRUE);

	if (m_decrypt != decrypt_vorher)
	{
		SHOW_HOUR_GLASS

		decrypt_vorher = m_decrypt;

		// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
		int i,
			j;
		
		// Alle Eintraege aus dem Fenster auslesen
		char Zeichen[HILL_MAX_DIM_GROSS][HILL_MAX_DIM_GROSS];
		
		int dim = 1;
		
		for (i=0; i<HILL_MAX_DIM_GROSS; i++)
		{
			for (j=0; j<HILL_MAX_DIM_GROSS; j++)
			{
				CString cs;
				m_pControlFelder[i][j]->GetWindowText(cs);
				
				if (cs.GetLength() == 1)
				{
					Zeichen[i][j] = cs[0];
					
					// Die Variable dim erhaelt am Ende der Schleife die Dimension der angezeigten Matrix,
					// da die letzte Zuweisung passiert, wenn das letzte Ausgabefeld (rechts unten) 
					// angesprochen wird. Dieses befindet sich in der letzten Zeile der Matrix. 
					dim = j+1;
				}
			}
		}
		
		// Anhand der Eintraege wurde die Groesse der Matrix bestimmt (dim)
		// Nun sind die Werte in eine CSquareMatrixModN einzulesen

		// nur fuer Funktion my_char_to_int
		CHillEncryption hillklasse(theApp.TextOptions.m_alphabet.GetBuffer(0));
		
		CSquareMatrixModN mat(dim,hillklasse.get_modul());

		for (i=0; i<dim; i++)
		{
			for (j=0; j<dim; j++)
			{
				CString cs;
				m_pControlFelder[i][j]->GetWindowText(cs);
				
				mat(i,j) = hillklasse.my_char_to_int(cs[0]);
			}
		}
		
		// Matrix invertieren
		CSquareMatrixModN inv_mat(dim,hillklasse.get_modul());
		BOOL b = mat.invert(&inv_mat);
		ASSERT(b);
		
		
		// Werte anzeigen
		for (i=0; i<dim; i++)
		{
			for (j=0; j<dim; j++)
			{
				CString cs;
				cs = hillklasse.my_int_to_char(inv_mat(i,j));
				
				ASSERT( (cs.GetLength() == 1) && (hillklasse.ist_erlaubtes_zeichen(cs[0])));
				m_pControlFelder[i][j]->SetWindowText(cs);
			}
		}

		HIDE_HOUR_GLASS
	}
}

BOOL CDlgShowKeyHill10x10::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	
	m_pControlFelder[0][0] = &m_ControlFeld11;
	m_pControlFelder[0][1] = &m_ControlFeld12;
	m_pControlFelder[0][2] = &m_ControlFeld13;
	m_pControlFelder[0][3] = &m_ControlFeld14;
	m_pControlFelder[0][4] = &m_ControlFeld15;
	m_pControlFelder[0][5] = &m_ControlFeld16;
	m_pControlFelder[0][6] = &m_ControlFeld17;
	m_pControlFelder[0][7] = &m_ControlFeld18;
	m_pControlFelder[0][8] = &m_ControlFeld19;
	m_pControlFelder[0][9] = &m_ControlFeld110;
	m_pControlFelder[1][0] = &m_ControlFeld21;
	m_pControlFelder[1][1] = &m_ControlFeld22;
	m_pControlFelder[1][2] = &m_ControlFeld23;
	m_pControlFelder[1][3] = &m_ControlFeld24;
	m_pControlFelder[1][4] = &m_ControlFeld25;
	m_pControlFelder[1][5] = &m_ControlFeld26;
	m_pControlFelder[1][6] = &m_ControlFeld27;
	m_pControlFelder[1][7] = &m_ControlFeld28;
	m_pControlFelder[1][8] = &m_ControlFeld29;
	m_pControlFelder[1][9] = &m_ControlFeld210;
	m_pControlFelder[2][0] = &m_ControlFeld31;
	m_pControlFelder[2][1] = &m_ControlFeld32;
	m_pControlFelder[2][2] = &m_ControlFeld33;
	m_pControlFelder[2][3] = &m_ControlFeld34;
	m_pControlFelder[2][4] = &m_ControlFeld35;
	m_pControlFelder[2][5] = &m_ControlFeld36;
	m_pControlFelder[2][6] = &m_ControlFeld37;
	m_pControlFelder[2][7] = &m_ControlFeld38;
	m_pControlFelder[2][8] = &m_ControlFeld39;
	m_pControlFelder[2][9] = &m_ControlFeld310;
	m_pControlFelder[3][0] = &m_ControlFeld41;
	m_pControlFelder[3][1] = &m_ControlFeld42;
	m_pControlFelder[3][2] = &m_ControlFeld43;
	m_pControlFelder[3][3] = &m_ControlFeld44;
	m_pControlFelder[3][4] = &m_ControlFeld45;
	m_pControlFelder[3][5] = &m_ControlFeld46;
	m_pControlFelder[3][6] = &m_ControlFeld47;
	m_pControlFelder[3][7] = &m_ControlFeld48;
	m_pControlFelder[3][8] = &m_ControlFeld49;
	m_pControlFelder[3][9] = &m_ControlFeld410;
	m_pControlFelder[4][0] = &m_ControlFeld51;
	m_pControlFelder[4][1] = &m_ControlFeld52;
	m_pControlFelder[4][2] = &m_ControlFeld53;
	m_pControlFelder[4][3] = &m_ControlFeld54;
	m_pControlFelder[4][4] = &m_ControlFeld55;
	m_pControlFelder[4][5] = &m_ControlFeld56;
	m_pControlFelder[4][6] = &m_ControlFeld57;
	m_pControlFelder[4][7] = &m_ControlFeld58;
	m_pControlFelder[4][8] = &m_ControlFeld59;
	m_pControlFelder[4][9] = &m_ControlFeld510;
	m_pControlFelder[5][0] = &m_ControlFeld61;
	m_pControlFelder[5][1] = &m_ControlFeld62;
	m_pControlFelder[5][2] = &m_ControlFeld63;
	m_pControlFelder[5][3] = &m_ControlFeld64;
	m_pControlFelder[5][4] = &m_ControlFeld65;
	m_pControlFelder[5][5] = &m_ControlFeld66;
	m_pControlFelder[5][6] = &m_ControlFeld67;
	m_pControlFelder[5][7] = &m_ControlFeld68;
	m_pControlFelder[5][8] = &m_ControlFeld69;
	m_pControlFelder[5][9] = &m_ControlFeld610;
	m_pControlFelder[6][0] = &m_ControlFeld71;
	m_pControlFelder[6][1] = &m_ControlFeld72;
	m_pControlFelder[6][2] = &m_ControlFeld73;
	m_pControlFelder[6][3] = &m_ControlFeld74;
	m_pControlFelder[6][4] = &m_ControlFeld75;
	m_pControlFelder[6][5] = &m_ControlFeld76;
	m_pControlFelder[6][6] = &m_ControlFeld77;
	m_pControlFelder[6][7] = &m_ControlFeld78;
	m_pControlFelder[6][8] = &m_ControlFeld79;
	m_pControlFelder[6][9] = &m_ControlFeld710;
	m_pControlFelder[7][0] = &m_ControlFeld81;
	m_pControlFelder[7][1] = &m_ControlFeld82;
	m_pControlFelder[7][2] = &m_ControlFeld83;
	m_pControlFelder[7][3] = &m_ControlFeld84;
	m_pControlFelder[7][4] = &m_ControlFeld85;
	m_pControlFelder[7][5] = &m_ControlFeld86;
	m_pControlFelder[7][6] = &m_ControlFeld87;
	m_pControlFelder[7][7] = &m_ControlFeld88;
	m_pControlFelder[7][8] = &m_ControlFeld89;
	m_pControlFelder[7][9] = &m_ControlFeld810;
	m_pControlFelder[8][0] = &m_ControlFeld91;
	m_pControlFelder[8][1] = &m_ControlFeld92;
	m_pControlFelder[8][2] = &m_ControlFeld93;
	m_pControlFelder[8][3] = &m_ControlFeld94;
	m_pControlFelder[8][4] = &m_ControlFeld95;
	m_pControlFelder[8][5] = &m_ControlFeld96;
	m_pControlFelder[8][6] = &m_ControlFeld97;
	m_pControlFelder[8][7] = &m_ControlFeld98;
	m_pControlFelder[8][8] = &m_ControlFeld99;
	m_pControlFelder[8][9] = &m_ControlFeld910;
	m_pControlFelder[9][0] = &m_ControlFeld101;
	m_pControlFelder[9][1] = &m_ControlFeld102;
	m_pControlFelder[9][2] = &m_ControlFeld103;
	m_pControlFelder[9][3] = &m_ControlFeld104;
	m_pControlFelder[9][4] = &m_ControlFeld105;
	m_pControlFelder[9][5] = &m_ControlFeld106;
	m_pControlFelder[9][6] = &m_ControlFeld107;
	m_pControlFelder[9][7] = &m_ControlFeld108;
	m_pControlFelder[9][8] = &m_ControlFeld109;
	m_pControlFelder[9][9] = &m_ControlFeld1010;

	
	// Font mit fester Breite erstellen und fuer alle Schluesselfelder setzen
	cf.CreatePointFont(80,"Courier");
	for (int i=0; i<HILL_MAX_DIM_GROSS; i++)
	{
		for (int j=0; j<HILL_MAX_DIM_GROSS; j++)
		{
			m_pControlFelder[i][j]->SetFont(&cf);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgShowKeyHill10x10::MatrixAnzeigen(CSquareMatrixModN& mat, int dim, CHillEncryption& hillklasse)
{
	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM_GROSS));

	CString cs;

	for (int i=0; i<HILL_MAX_DIM_GROSS; i++)
	{
		for (int j=0; j<HILL_MAX_DIM_GROSS; j++)
		{
			if (i<dim && j<dim)
			{
				// Wert anzeigen
				cs = hillklasse.my_int_to_char(mat(i,j));
			}
			else
			{
				// Feld leeren
				cs.Empty();
			}
			(*m_pFelder[i][j]) = cs;
		}
	}
}


void CDlgShowKeyHill10x10::OnVerschluesseln() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	OnDecrypt();	
}

void CDlgShowKeyHill10x10::OnEntschluesseln() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	OnDecrypt();
}

void CDlgShowKeyHill10x10::OnKopieren() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	// Zuerst in cs die Matrix der Schlüssel aufbauen,
	// danach in das unsichtbare Feld schreiben und
	// schliesslich in diesem Feld alles markieren und in die Zwischenablage speichern

	CString cs, hilf;

	for (int i=0; i<HILL_MAX_DIM_GROSS; i++)
	{
		for (int j=0; j<HILL_MAX_DIM_GROSS; j++)
		{
			m_pControlFelder[i][j]->GetWindowText(hilf);
			if (hilf.GetLength() == 1)
			{
				cs += hilf;
			}
			else
			{
				cs += ' ';
			}
		}
		if ( i+1 < HILL_MAX_DIM_GROSS ) cs += '\n';
	}
    LoadString(AfxGetInstanceHandle(),IDS_CRYPT_HILL,pc_str,STR_LAENGE_STRING_TABLE);
	CopyKey(pc_str, cs); 
	m_FeldUnsichtbar.SetWindowText(cs);
	m_FeldUnsichtbar.SetSel(0,-1);  // Alles markieren
	m_FeldUnsichtbar.Copy();

	CDialog::OnOK();
}


void CDlgShowKeyHill10x10::SchluesselAnzeigen(CString Key)
{
	int iLaenge = Key.GetLength(),
		iDimension = 1;

	// Format: Zeilenweise Apspeicherung des Schluessel, jeweils durch ein Leerzeichen getrennt
	// iLaenge muss gleich i^2+(i-1) sein, 1 <= i <= HILL_MAX_DIM
	while ( ((iDimension*iDimension+(iDimension-1)) < iLaenge) && (iDimension <= HILL_MAX_DIM_GROSS))
	{
		iDimension++;
	}

	ASSERT( (1 <= iDimension) && (iDimension <= HILL_MAX_DIM_GROSS) );
	ASSERT( (iDimension*iDimension+(iDimension-1)) == iLaenge);

	CString hilf;
	for (int i=0; i<iDimension; i++)
	{
		for (int j=0; j<iDimension; j++)
		{
			hilf = Key[i*(iDimension+1)+j];
			(*m_pFelder[i][j]) = hilf;
		}
	}
}
