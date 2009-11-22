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
// HillSchluesselAusgabeGross.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "SquareMatrixModN.h"
#include "CrypToolApp.h"
#include "DlgShowKeyHill10x10.h"
#include "KeyRepository.h"
#include "HillEncryption.h"
#include "Cryptography.h"
#include "assert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKeyHill10x10 


CDlgShowKeyHill10x10::CDlgShowKeyHill10x10(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowKeyHill10x10::IDD, pParent)
	, i_multDirection(0)
	, m_alphabetOffset(0)
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


	m_AlphFeld40 = _T("");
	m_AlphFeld50 = _T("");
	m_AlphFeld20 = _T("");
	m_AlphFeld90 = _T("");
	m_AlphFeld100 = _T("");
	m_AlphFeld117 = _T("");
	m_AlphFeld118 = _T("");
	m_AlphFeld119 = _T("");
	m_AlphFeld60 = _T("");
	m_AlphFeld125 = _T("");
	m_AlphFeld127 = _T("");
	m_AlphFeld213 = _T("");
	m_AlphFeld214 = _T("");
	m_AlphFeld215 = _T("");
	m_AlphFeld70 = _T("");
	m_AlphFeld216 = _T("");
	m_AlphFeld217 = _T("");
	m_AlphFeld218 = _T("");
	m_AlphFeld80 = _T("");
	m_AlphFeld219 = _T("");
	m_AlphFeld220 = _T("");
	m_AlphFeld134 = _T("");
	m_AlphFeld135 = _T("");
	m_AlphFeld136 = _T("");
	m_AlphFeld137 = _T("");
	m_AlphFeld138 = _T("");
	m_AlphFeld139 = _T("");
	m_AlphFeld211 = _T("");
	m_AlphFeld140 = _T("");
	m_AlphFeld312 = _T("");
	m_AlphFeld142 = _T("");
	m_AlphFeld221 = _T("");
	m_AlphFeld222 = _T("");
	m_AlphFeld223 = _T("");
	m_AlphFeld144 = _T("");
	m_AlphFeld145 = _T("");
	m_AlphFeld146 = _T("");
	m_AlphFeld147 = _T("");
	m_AlphFeld148 = _T("");
	m_AlphFeld412 = _T("");
	m_AlphFeld149 = _T("");
	m_AlphFeld150 = _T("");
	m_AlphFeld113 = _T("");
	m_AlphFeld151 = _T("");
	m_AlphFeld152 = _T("");
	m_AlphFeld153 = _T("");
	m_AlphFeld154 = _T("");
	m_AlphFeld155 = _T("");
	m_AlphFeld156 = _T("");
	m_AlphFeld512 = _T("");
	m_AlphFeld224 = _T("");
	m_AlphFeld158 = _T("");
	m_AlphFeld159 = _T("");
	m_AlphFeld160 = _T("");
	m_AlphFeld161 = _T("");
	m_AlphFeld162 = _T("");
	m_AlphFeld163 = _T("");
	m_AlphFeld164 = _T("");
	m_AlphFeld174 = _T("");
	m_AlphFeld612 = _T("");
	m_AlphFeld225 = _T("");
	m_AlphFeld226 = _T("");
	m_AlphFeld166 = _T("");
	m_AlphFeld167 = _T("");
	m_AlphFeld168 = _T("");
	m_AlphFeld169 = _T("");
	m_AlphFeld170 = _T("");
	m_AlphFeld171 = _T("");
	m_AlphFeld172 = _T("");
	m_AlphFeld712 = _T("");
	m_AlphFeld227 = _T("");
	m_AlphFeld175 = _T("");
	m_AlphFeld176 = _T("");
	m_AlphFeld177 = _T("");
	m_AlphFeld178 = _T("");
	m_AlphFeld179 = _T("");
	m_AlphFeld180 = _T("");
	m_AlphFeld191 = _T("");
	m_AlphFeld181 = _T("");
	m_AlphFeld812 = _T("");
	m_AlphFeld183 = _T("");
	m_AlphFeld228 = _T("");
	m_AlphFeld184 = _T("");
	m_AlphFeld185 = _T("");
	m_AlphFeld186 = _T("");
	m_AlphFeld187 = _T("");
	m_AlphFeld188 = _T("");
	m_AlphFeld189 = _T("");
	m_AlphFeld190 = _T("");
	m_AlphFeld912 = _T("");
	m_AlphFeld229 = _T("");
	m_AlphFeld193 = _T("");
	m_AlphFeld194 = _T("");
	m_AlphFeld195 = _T("");
	m_AlphFeld196 = _T("");
	m_AlphFeld197 = _T("");
	m_AlphFeld198 = _T("");
	m_AlphFeld199 = _T("");
	m_AlphFeld200 = _T("");
	m_AlphFeld1012 = _T("");

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

	m_pAlphFelder[0][0] = &m_AlphFeld40;
	m_pAlphFelder[0][1] = &m_AlphFeld50;
	m_pAlphFelder[0][2] = &m_AlphFeld20;
	m_pAlphFelder[0][3] = &m_AlphFeld90;
	m_pAlphFelder[0][4] = &m_AlphFeld100;
	m_pAlphFelder[0][5] = &m_AlphFeld117;
	m_pAlphFelder[0][6] = &m_AlphFeld118;
	m_pAlphFelder[0][7] = &m_AlphFeld119;
	m_pAlphFelder[0][8] = &m_AlphFeld60;
	m_pAlphFelder[0][9] = &m_AlphFeld125;
	m_pAlphFelder[1][0] = &m_AlphFeld127;
	m_pAlphFelder[1][1] = &m_AlphFeld213;
	m_pAlphFelder[1][2] = &m_AlphFeld214;
	m_pAlphFelder[1][3] = &m_AlphFeld215;
	m_pAlphFelder[1][4] = &m_AlphFeld70;
	m_pAlphFelder[1][5] = &m_AlphFeld216;
	m_pAlphFelder[1][6] = &m_AlphFeld217;
	m_pAlphFelder[1][7] = &m_AlphFeld218;
	m_pAlphFelder[1][8] = &m_AlphFeld80;
	m_pAlphFelder[1][9] = &m_AlphFeld219;
	m_pAlphFelder[2][0] = &m_AlphFeld220;
	m_pAlphFelder[2][1] = &m_AlphFeld134;
	m_pAlphFelder[2][2] = &m_AlphFeld135;
	m_pAlphFelder[2][3] = &m_AlphFeld136;
	m_pAlphFelder[2][4] = &m_AlphFeld137;
	m_pAlphFelder[2][5] = &m_AlphFeld138;
	m_pAlphFelder[2][6] = &m_AlphFeld139;
	m_pAlphFelder[2][7] = &m_AlphFeld211;
	m_pAlphFelder[2][8] = &m_AlphFeld140;
	m_pAlphFelder[2][9] = &m_AlphFeld312;
	m_pAlphFelder[3][0] = &m_AlphFeld142;
	m_pAlphFelder[3][1] = &m_AlphFeld221;
	m_pAlphFelder[3][2] = &m_AlphFeld222;
	m_pAlphFelder[3][3] = &m_AlphFeld223;
	m_pAlphFelder[3][4] = &m_AlphFeld144;
	m_pAlphFelder[3][5] = &m_AlphFeld145;
	m_pAlphFelder[3][6] = &m_AlphFeld146;
	m_pAlphFelder[3][7] = &m_AlphFeld147;
	m_pAlphFelder[3][8] = &m_AlphFeld148;
	m_pAlphFelder[3][9] = &m_AlphFeld412;
	m_pAlphFelder[4][0] = &m_AlphFeld149;
	m_pAlphFelder[4][1] = &m_AlphFeld150;
	m_pAlphFelder[4][2] = &m_AlphFeld113;
	m_pAlphFelder[4][3] = &m_AlphFeld151;
	m_pAlphFelder[4][4] = &m_AlphFeld152;
	m_pAlphFelder[4][5] = &m_AlphFeld153;
	m_pAlphFelder[4][6] = &m_AlphFeld154;
	m_pAlphFelder[4][7] = &m_AlphFeld155;
	m_pAlphFelder[4][8] = &m_AlphFeld156;
	m_pAlphFelder[4][9] = &m_AlphFeld512;
	m_pAlphFelder[5][0] = &m_AlphFeld224;
	m_pAlphFelder[5][1] = &m_AlphFeld158;
	m_pAlphFelder[5][2] = &m_AlphFeld159;
	m_pAlphFelder[5][3] = &m_AlphFeld160;
	m_pAlphFelder[5][4] = &m_AlphFeld161;
	m_pAlphFelder[5][5] = &m_AlphFeld162;
	m_pAlphFelder[5][6] = &m_AlphFeld163;
	m_pAlphFelder[5][7] = &m_AlphFeld164;
	m_pAlphFelder[5][8] = &m_AlphFeld174;
	m_pAlphFelder[5][9] = &m_AlphFeld612;
	m_pAlphFelder[6][0] = &m_AlphFeld225;
	m_pAlphFelder[6][1] = &m_AlphFeld226;
	m_pAlphFelder[6][2] = &m_AlphFeld166;
	m_pAlphFelder[6][3] = &m_AlphFeld167;
	m_pAlphFelder[6][4] = &m_AlphFeld168;
	m_pAlphFelder[6][5] = &m_AlphFeld169;
	m_pAlphFelder[6][6] = &m_AlphFeld170;
	m_pAlphFelder[6][7] = &m_AlphFeld171;
	m_pAlphFelder[6][8] = &m_AlphFeld172;
	m_pAlphFelder[6][9] = &m_AlphFeld712;
	m_pAlphFelder[7][0] = &m_AlphFeld227;
	m_pAlphFelder[7][1] = &m_AlphFeld175;
	m_pAlphFelder[7][2] = &m_AlphFeld176;
	m_pAlphFelder[7][3] = &m_AlphFeld177;
	m_pAlphFelder[7][4] = &m_AlphFeld178;
	m_pAlphFelder[7][5] = &m_AlphFeld179;
	m_pAlphFelder[7][6] = &m_AlphFeld180;
	m_pAlphFelder[7][7] = &m_AlphFeld191;
	m_pAlphFelder[7][8] = &m_AlphFeld181;
	m_pAlphFelder[7][9] = &m_AlphFeld812;
	m_pAlphFelder[8][0] = &m_AlphFeld183;
	m_pAlphFelder[8][1] = &m_AlphFeld228;
	m_pAlphFelder[8][2] = &m_AlphFeld184;
	m_pAlphFelder[8][3] = &m_AlphFeld185;
	m_pAlphFelder[8][4] = &m_AlphFeld186;
	m_pAlphFelder[8][5] = &m_AlphFeld187;
	m_pAlphFelder[8][6] = &m_AlphFeld188;
	m_pAlphFelder[8][7] = &m_AlphFeld189;
	m_pAlphFelder[8][8] = &m_AlphFeld190;
	m_pAlphFelder[8][9] = &m_AlphFeld912;
	m_pAlphFelder[9][0] = &m_AlphFeld229;
	m_pAlphFelder[9][1] = &m_AlphFeld193;
	m_pAlphFelder[9][2] = &m_AlphFeld194;
	m_pAlphFelder[9][3] = &m_AlphFeld195;
	m_pAlphFelder[9][4] = &m_AlphFeld196;
	m_pAlphFelder[9][5] = &m_AlphFeld197;
	m_pAlphFelder[9][6] = &m_AlphFeld198;
	m_pAlphFelder[9][7] = &m_AlphFeld199;
	m_pAlphFelder[9][8] = &m_AlphFeld200;
	m_pAlphFelder[9][9] = &m_AlphFeld1012;
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

	DDX_Text(pDX, IDC_EDIT40, m_AlphFeld40);
	DDX_Text(pDX, IDC_EDIT50, m_AlphFeld50);
	DDX_Text(pDX, IDC_EDIT20, m_AlphFeld20);
	DDX_Text(pDX, IDC_EDIT90, m_AlphFeld90);
	DDX_Text(pDX, IDC_EDIT100, m_AlphFeld100);
	DDX_Text(pDX, IDC_EDIT117, m_AlphFeld117);
	DDX_Text(pDX, IDC_EDIT118, m_AlphFeld118);
	DDX_Text(pDX, IDC_EDIT119, m_AlphFeld119);
	DDX_Text(pDX, IDC_EDIT60, m_AlphFeld60);
	DDX_Text(pDX, IDC_EDIT125, m_AlphFeld125);
	DDX_Text(pDX, IDC_EDIT127, m_AlphFeld127);
	DDX_Text(pDX, IDC_EDIT213, m_AlphFeld213);
	DDX_Text(pDX, IDC_EDIT214, m_AlphFeld214);
	DDX_Text(pDX, IDC_EDIT215, m_AlphFeld215);
	DDX_Text(pDX, IDC_EDIT70, m_AlphFeld70);
	DDX_Text(pDX, IDC_EDIT216, m_AlphFeld216);
	DDX_Text(pDX, IDC_EDIT217, m_AlphFeld217);
	DDX_Text(pDX, IDC_EDIT218, m_AlphFeld218);
	DDX_Text(pDX, IDC_EDIT80, m_AlphFeld80);
	DDX_Text(pDX, IDC_EDIT219, m_AlphFeld219);
	DDX_Text(pDX, IDC_EDIT220, m_AlphFeld220);
	DDX_Text(pDX, IDC_EDIT134, m_AlphFeld134);
	DDX_Text(pDX, IDC_EDIT135, m_AlphFeld135);
	DDX_Text(pDX, IDC_EDIT136, m_AlphFeld136);
	DDX_Text(pDX, IDC_EDIT137, m_AlphFeld137);
	DDX_Text(pDX, IDC_EDIT138, m_AlphFeld138);
	DDX_Text(pDX, IDC_EDIT139, m_AlphFeld139);
	DDX_Text(pDX, IDC_EDIT211, m_AlphFeld211);
	DDX_Text(pDX, IDC_EDIT140, m_AlphFeld140);
	DDX_Text(pDX, IDC_EDIT312, m_AlphFeld312);
	DDX_Text(pDX, IDC_EDIT142, m_AlphFeld142);
	DDX_Text(pDX, IDC_EDIT221, m_AlphFeld221);
	DDX_Text(pDX, IDC_EDIT222, m_AlphFeld222);
	DDX_Text(pDX, IDC_EDIT223, m_AlphFeld223);
	DDX_Text(pDX, IDC_EDIT144, m_AlphFeld144);
	DDX_Text(pDX, IDC_EDIT145, m_AlphFeld145);
	DDX_Text(pDX, IDC_EDIT146, m_AlphFeld146);
	DDX_Text(pDX, IDC_EDIT147, m_AlphFeld147);
	DDX_Text(pDX, IDC_EDIT148, m_AlphFeld148);
	DDX_Text(pDX, IDC_EDIT412, m_AlphFeld412);
	DDX_Text(pDX, IDC_EDIT149, m_AlphFeld149);
	DDX_Text(pDX, IDC_EDIT150, m_AlphFeld150);
	DDX_Text(pDX, IDC_EDIT113, m_AlphFeld113);
	DDX_Text(pDX, IDC_EDIT151, m_AlphFeld151);
	DDX_Text(pDX, IDC_EDIT152, m_AlphFeld152);
	DDX_Text(pDX, IDC_EDIT153, m_AlphFeld153);
	DDX_Text(pDX, IDC_EDIT154, m_AlphFeld154);
	DDX_Text(pDX, IDC_EDIT155, m_AlphFeld155);
	DDX_Text(pDX, IDC_EDIT156, m_AlphFeld156);
	DDX_Text(pDX, IDC_EDIT512, m_AlphFeld512);
	DDX_Text(pDX, IDC_EDIT224, m_AlphFeld224);
	DDX_Text(pDX, IDC_EDIT158, m_AlphFeld158);
	DDX_Text(pDX, IDC_EDIT159, m_AlphFeld159);
	DDX_Text(pDX, IDC_EDIT160, m_AlphFeld160);
	DDX_Text(pDX, IDC_EDIT161, m_AlphFeld161);
	DDX_Text(pDX, IDC_EDIT162, m_AlphFeld162);
	DDX_Text(pDX, IDC_EDIT163, m_AlphFeld163);
	DDX_Text(pDX, IDC_EDIT164, m_AlphFeld164);
	DDX_Text(pDX, IDC_EDIT174, m_AlphFeld174);
	DDX_Text(pDX, IDC_EDIT612, m_AlphFeld612);
	DDX_Text(pDX, IDC_EDIT225, m_AlphFeld225);
	DDX_Text(pDX, IDC_EDIT226, m_AlphFeld226);
	DDX_Text(pDX, IDC_EDIT166, m_AlphFeld166);
	DDX_Text(pDX, IDC_EDIT167, m_AlphFeld167);
	DDX_Text(pDX, IDC_EDIT168, m_AlphFeld168);
	DDX_Text(pDX, IDC_EDIT169, m_AlphFeld169);
	DDX_Text(pDX, IDC_EDIT170, m_AlphFeld170);
	DDX_Text(pDX, IDC_EDIT171, m_AlphFeld171);
	DDX_Text(pDX, IDC_EDIT172, m_AlphFeld172);
	DDX_Text(pDX, IDC_EDIT712, m_AlphFeld712);
	DDX_Text(pDX, IDC_EDIT227, m_AlphFeld227);
	DDX_Text(pDX, IDC_EDIT175, m_AlphFeld175);
	DDX_Text(pDX, IDC_EDIT176, m_AlphFeld176);
	DDX_Text(pDX, IDC_EDIT177, m_AlphFeld177);
	DDX_Text(pDX, IDC_EDIT178, m_AlphFeld178);
	DDX_Text(pDX, IDC_EDIT179, m_AlphFeld179);
	DDX_Text(pDX, IDC_EDIT180, m_AlphFeld180);
	DDX_Text(pDX, IDC_EDIT191, m_AlphFeld191);
	DDX_Text(pDX, IDC_EDIT181, m_AlphFeld181);
	DDX_Text(pDX, IDC_EDIT812, m_AlphFeld812);
	DDX_Text(pDX, IDC_EDIT183, m_AlphFeld183);
	DDX_Text(pDX, IDC_EDIT228, m_AlphFeld228);
	DDX_Text(pDX, IDC_EDIT184, m_AlphFeld184);
	DDX_Text(pDX, IDC_EDIT185, m_AlphFeld185);
	DDX_Text(pDX, IDC_EDIT186, m_AlphFeld186);
	DDX_Text(pDX, IDC_EDIT187, m_AlphFeld187);
	DDX_Text(pDX, IDC_EDIT188, m_AlphFeld188);
	DDX_Text(pDX, IDC_EDIT189, m_AlphFeld189);
	DDX_Text(pDX, IDC_EDIT190, m_AlphFeld190);
	DDX_Text(pDX, IDC_EDIT912, m_AlphFeld912);
	DDX_Text(pDX, IDC_EDIT229, m_AlphFeld229);
	DDX_Text(pDX, IDC_EDIT193, m_AlphFeld193);
	DDX_Text(pDX, IDC_EDIT194, m_AlphFeld194);
	DDX_Text(pDX, IDC_EDIT195, m_AlphFeld195);
	DDX_Text(pDX, IDC_EDIT196, m_AlphFeld196);
	DDX_Text(pDX, IDC_EDIT197, m_AlphFeld197);
	DDX_Text(pDX, IDC_EDIT198, m_AlphFeld198);
	DDX_Text(pDX, IDC_EDIT199, m_AlphFeld199);
	DDX_Text(pDX, IDC_EDIT200, m_AlphFeld200);
	DDX_Text(pDX, IDC_EDIT1012, m_AlphFeld1012);

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

	DDX_Control(pDX, IDC_EDIT40, m_ControlAlphFeld40);
	DDX_Control(pDX, IDC_EDIT50, m_ControlAlphFeld50);
	DDX_Control(pDX, IDC_EDIT20, m_ControlAlphFeld20);
	DDX_Control(pDX, IDC_EDIT90, m_ControlAlphFeld90);
	DDX_Control(pDX, IDC_EDIT100, m_ControlAlphFeld100);
	DDX_Control(pDX, IDC_EDIT117, m_ControlAlphFeld117);
	DDX_Control(pDX, IDC_EDIT118, m_ControlAlphFeld118);
	DDX_Control(pDX, IDC_EDIT119, m_ControlAlphFeld119);
	DDX_Control(pDX, IDC_EDIT60, m_ControlAlphFeld60);
	DDX_Control(pDX, IDC_EDIT125, m_ControlAlphFeld125);
	DDX_Control(pDX, IDC_EDIT127, m_ControlAlphFeld127);
	DDX_Control(pDX, IDC_EDIT213, m_ControlAlphFeld213);
	DDX_Control(pDX, IDC_EDIT214, m_ControlAlphFeld214);
	DDX_Control(pDX, IDC_EDIT215, m_ControlAlphFeld215);
	DDX_Control(pDX, IDC_EDIT70, m_ControlAlphFeld70);
	DDX_Control(pDX, IDC_EDIT216, m_ControlAlphFeld216);
	DDX_Control(pDX, IDC_EDIT217, m_ControlAlphFeld217);
	DDX_Control(pDX, IDC_EDIT218, m_ControlAlphFeld218);
	DDX_Control(pDX, IDC_EDIT80, m_ControlAlphFeld80);
	DDX_Control(pDX, IDC_EDIT219, m_ControlAlphFeld219);
	DDX_Control(pDX, IDC_EDIT220, m_ControlAlphFeld220);
	DDX_Control(pDX, IDC_EDIT134, m_ControlAlphFeld134);
	DDX_Control(pDX, IDC_EDIT135, m_ControlAlphFeld135);
	DDX_Control(pDX, IDC_EDIT136, m_ControlAlphFeld136);
	DDX_Control(pDX, IDC_EDIT137, m_ControlAlphFeld137);
	DDX_Control(pDX, IDC_EDIT138, m_ControlAlphFeld138);
	DDX_Control(pDX, IDC_EDIT139, m_ControlAlphFeld139);
	DDX_Control(pDX, IDC_EDIT211, m_ControlAlphFeld211);
	DDX_Control(pDX, IDC_EDIT140, m_ControlAlphFeld140);
	DDX_Control(pDX, IDC_EDIT312, m_ControlAlphFeld312);
	DDX_Control(pDX, IDC_EDIT142, m_ControlAlphFeld142);
	DDX_Control(pDX, IDC_EDIT221, m_ControlAlphFeld221);
	DDX_Control(pDX, IDC_EDIT222, m_ControlAlphFeld222);
	DDX_Control(pDX, IDC_EDIT223, m_ControlAlphFeld223);
	DDX_Control(pDX, IDC_EDIT144, m_ControlAlphFeld144);
	DDX_Control(pDX, IDC_EDIT145, m_ControlAlphFeld145);
	DDX_Control(pDX, IDC_EDIT146, m_ControlAlphFeld146);
	DDX_Control(pDX, IDC_EDIT147, m_ControlAlphFeld147);
	DDX_Control(pDX, IDC_EDIT148, m_ControlAlphFeld148);
	DDX_Control(pDX, IDC_EDIT412, m_ControlAlphFeld412);
	DDX_Control(pDX, IDC_EDIT149, m_ControlAlphFeld149);
	DDX_Control(pDX, IDC_EDIT150, m_ControlAlphFeld150);
	DDX_Control(pDX, IDC_EDIT113, m_ControlAlphFeld113);
	DDX_Control(pDX, IDC_EDIT151, m_ControlAlphFeld151);
	DDX_Control(pDX, IDC_EDIT152, m_ControlAlphFeld152);
	DDX_Control(pDX, IDC_EDIT153, m_ControlAlphFeld153);
	DDX_Control(pDX, IDC_EDIT154, m_ControlAlphFeld154);
	DDX_Control(pDX, IDC_EDIT155, m_ControlAlphFeld155);
	DDX_Control(pDX, IDC_EDIT156, m_ControlAlphFeld156);
	DDX_Control(pDX, IDC_EDIT512, m_ControlAlphFeld512);
	DDX_Control(pDX, IDC_EDIT224, m_ControlAlphFeld224);
	DDX_Control(pDX, IDC_EDIT158, m_ControlAlphFeld158);
	DDX_Control(pDX, IDC_EDIT159, m_ControlAlphFeld159);
	DDX_Control(pDX, IDC_EDIT160, m_ControlAlphFeld160);
	DDX_Control(pDX, IDC_EDIT161, m_ControlAlphFeld161);
	DDX_Control(pDX, IDC_EDIT162, m_ControlAlphFeld162);
	DDX_Control(pDX, IDC_EDIT163, m_ControlAlphFeld163);
	DDX_Control(pDX, IDC_EDIT164, m_ControlAlphFeld164);
	DDX_Control(pDX, IDC_EDIT174, m_ControlAlphFeld174);
	DDX_Control(pDX, IDC_EDIT612, m_ControlAlphFeld612);
	DDX_Control(pDX, IDC_EDIT225, m_ControlAlphFeld225);
	DDX_Control(pDX, IDC_EDIT226, m_ControlAlphFeld226);
	DDX_Control(pDX, IDC_EDIT166, m_ControlAlphFeld166);
	DDX_Control(pDX, IDC_EDIT167, m_ControlAlphFeld167);
	DDX_Control(pDX, IDC_EDIT168, m_ControlAlphFeld168);
	DDX_Control(pDX, IDC_EDIT169, m_ControlAlphFeld169);
	DDX_Control(pDX, IDC_EDIT170, m_ControlAlphFeld170);
	DDX_Control(pDX, IDC_EDIT171, m_ControlAlphFeld171);
	DDX_Control(pDX, IDC_EDIT172, m_ControlAlphFeld172);
	DDX_Control(pDX, IDC_EDIT712, m_ControlAlphFeld712);
	DDX_Control(pDX, IDC_EDIT227, m_ControlAlphFeld227);
	DDX_Control(pDX, IDC_EDIT175, m_ControlAlphFeld175);
	DDX_Control(pDX, IDC_EDIT176, m_ControlAlphFeld176);
	DDX_Control(pDX, IDC_EDIT177, m_ControlAlphFeld177);
	DDX_Control(pDX, IDC_EDIT178, m_ControlAlphFeld178);
	DDX_Control(pDX, IDC_EDIT179, m_ControlAlphFeld179);
	DDX_Control(pDX, IDC_EDIT180, m_ControlAlphFeld180);
	DDX_Control(pDX, IDC_EDIT191, m_ControlAlphFeld191);
	DDX_Control(pDX, IDC_EDIT181, m_ControlAlphFeld181);
	DDX_Control(pDX, IDC_EDIT812, m_ControlAlphFeld812);
	DDX_Control(pDX, IDC_EDIT183, m_ControlAlphFeld183);
	DDX_Control(pDX, IDC_EDIT228, m_ControlAlphFeld228);
	DDX_Control(pDX, IDC_EDIT184, m_ControlAlphFeld184);
	DDX_Control(pDX, IDC_EDIT185, m_ControlAlphFeld185);
	DDX_Control(pDX, IDC_EDIT186, m_ControlAlphFeld186);
	DDX_Control(pDX, IDC_EDIT187, m_ControlAlphFeld187);
	DDX_Control(pDX, IDC_EDIT188, m_ControlAlphFeld188);
	DDX_Control(pDX, IDC_EDIT189, m_ControlAlphFeld189);
	DDX_Control(pDX, IDC_EDIT190, m_ControlAlphFeld190);
	DDX_Control(pDX, IDC_EDIT912, m_ControlAlphFeld912);
	DDX_Control(pDX, IDC_EDIT229, m_ControlAlphFeld229);
	DDX_Control(pDX, IDC_EDIT193, m_ControlAlphFeld193);
	DDX_Control(pDX, IDC_EDIT194, m_ControlAlphFeld194);
	DDX_Control(pDX, IDC_EDIT195, m_ControlAlphFeld195);
	DDX_Control(pDX, IDC_EDIT196, m_ControlAlphFeld196);
	DDX_Control(pDX, IDC_EDIT197, m_ControlAlphFeld197);
	DDX_Control(pDX, IDC_EDIT198, m_ControlAlphFeld198);
	DDX_Control(pDX, IDC_EDIT199, m_ControlAlphFeld199);
	DDX_Control(pDX, IDC_EDIT200, m_ControlAlphFeld200);
	DDX_Control(pDX, IDC_EDIT1012, m_ControlAlphFeld1012);
	DDX_Radio  (pDX, IDC_RADIO1,   m_decrypt);
	DDX_Text   (pDX, IDC_EDIT2,    m_alphabetOffset);
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
		CHillEncryption hillklasse(theApp.TextOptions.refAlphabet().GetBuffer(0));
		
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


	m_pControlAlphFelder[0][0] = &m_ControlAlphFeld40;
	m_pControlAlphFelder[0][1] = &m_ControlAlphFeld50;
	m_pControlAlphFelder[0][2] = &m_ControlAlphFeld20;
	m_pControlAlphFelder[0][3] = &m_ControlAlphFeld90;
	m_pControlAlphFelder[0][4] = &m_ControlAlphFeld100;
	m_pControlAlphFelder[0][5] = &m_ControlAlphFeld117;
	m_pControlAlphFelder[0][6] = &m_ControlAlphFeld118;
	m_pControlAlphFelder[0][7] = &m_ControlAlphFeld119;
	m_pControlAlphFelder[0][8] = &m_ControlAlphFeld60;
	m_pControlAlphFelder[0][9] = &m_ControlAlphFeld125;
	m_pControlAlphFelder[1][0] = &m_ControlAlphFeld127;
	m_pControlAlphFelder[1][1] = &m_ControlAlphFeld213;
	m_pControlAlphFelder[1][2] = &m_ControlAlphFeld214;
	m_pControlAlphFelder[1][3] = &m_ControlAlphFeld215;
	m_pControlAlphFelder[1][4] = &m_ControlAlphFeld70;
	m_pControlAlphFelder[1][5] = &m_ControlAlphFeld216;
	m_pControlAlphFelder[1][6] = &m_ControlAlphFeld217;
	m_pControlAlphFelder[1][7] = &m_ControlAlphFeld218;
	m_pControlAlphFelder[1][8] = &m_ControlAlphFeld80;
	m_pControlAlphFelder[1][9] = &m_ControlAlphFeld219;
	m_pControlAlphFelder[2][0] = &m_ControlAlphFeld220;
	m_pControlAlphFelder[2][1] = &m_ControlAlphFeld134;
	m_pControlAlphFelder[2][2] = &m_ControlAlphFeld135;
	m_pControlAlphFelder[2][3] = &m_ControlAlphFeld136;
	m_pControlAlphFelder[2][4] = &m_ControlAlphFeld137;
	m_pControlAlphFelder[2][5] = &m_ControlAlphFeld138;
	m_pControlAlphFelder[2][6] = &m_ControlAlphFeld139;
	m_pControlAlphFelder[2][7] = &m_ControlAlphFeld211;
	m_pControlAlphFelder[2][8] = &m_ControlAlphFeld140;
	m_pControlAlphFelder[2][9] = &m_ControlAlphFeld312;
	m_pControlAlphFelder[3][0] = &m_ControlAlphFeld142;
	m_pControlAlphFelder[3][1] = &m_ControlAlphFeld221;
	m_pControlAlphFelder[3][2] = &m_ControlAlphFeld222;
	m_pControlAlphFelder[3][3] = &m_ControlAlphFeld223;
	m_pControlAlphFelder[3][4] = &m_ControlAlphFeld144;
	m_pControlAlphFelder[3][5] = &m_ControlAlphFeld145;
	m_pControlAlphFelder[3][6] = &m_ControlAlphFeld146;
	m_pControlAlphFelder[3][7] = &m_ControlAlphFeld147;
	m_pControlAlphFelder[3][8] = &m_ControlAlphFeld148;
	m_pControlAlphFelder[3][9] = &m_ControlAlphFeld412;
	m_pControlAlphFelder[4][0] = &m_ControlAlphFeld149;
	m_pControlAlphFelder[4][1] = &m_ControlAlphFeld150;
	m_pControlAlphFelder[4][2] = &m_ControlAlphFeld113;
	m_pControlAlphFelder[4][3] = &m_ControlAlphFeld151;
	m_pControlAlphFelder[4][4] = &m_ControlAlphFeld152;
	m_pControlAlphFelder[4][5] = &m_ControlAlphFeld153;
	m_pControlAlphFelder[4][6] = &m_ControlAlphFeld154;
	m_pControlAlphFelder[4][7] = &m_ControlAlphFeld155;
	m_pControlAlphFelder[4][8] = &m_ControlAlphFeld156;
	m_pControlAlphFelder[4][9] = &m_ControlAlphFeld512;
	m_pControlAlphFelder[5][0] = &m_ControlAlphFeld224;
	m_pControlAlphFelder[5][1] = &m_ControlAlphFeld158;
	m_pControlAlphFelder[5][2] = &m_ControlAlphFeld159;
	m_pControlAlphFelder[5][3] = &m_ControlAlphFeld160;
	m_pControlAlphFelder[5][4] = &m_ControlAlphFeld161;
	m_pControlAlphFelder[5][5] = &m_ControlAlphFeld162;
	m_pControlAlphFelder[5][6] = &m_ControlAlphFeld163;
	m_pControlAlphFelder[5][7] = &m_ControlAlphFeld164;
	m_pControlAlphFelder[5][8] = &m_ControlAlphFeld174;
	m_pControlAlphFelder[5][9] = &m_ControlAlphFeld612;
	m_pControlAlphFelder[6][0] = &m_ControlAlphFeld225;
	m_pControlAlphFelder[6][1] = &m_ControlAlphFeld226;
	m_pControlAlphFelder[6][2] = &m_ControlAlphFeld166;
	m_pControlAlphFelder[6][3] = &m_ControlAlphFeld167;
	m_pControlAlphFelder[6][4] = &m_ControlAlphFeld168;
	m_pControlAlphFelder[6][5] = &m_ControlAlphFeld169;
	m_pControlAlphFelder[6][6] = &m_ControlAlphFeld170;
	m_pControlAlphFelder[6][7] = &m_ControlAlphFeld171;
	m_pControlAlphFelder[6][8] = &m_ControlAlphFeld172;
	m_pControlAlphFelder[6][9] = &m_ControlAlphFeld712;
	m_pControlAlphFelder[7][0] = &m_ControlAlphFeld227;
	m_pControlAlphFelder[7][1] = &m_ControlAlphFeld175;
	m_pControlAlphFelder[7][2] = &m_ControlAlphFeld176;
	m_pControlAlphFelder[7][3] = &m_ControlAlphFeld177;
	m_pControlAlphFelder[7][4] = &m_ControlAlphFeld178;
	m_pControlAlphFelder[7][5] = &m_ControlAlphFeld179;
	m_pControlAlphFelder[7][6] = &m_ControlAlphFeld180;
	m_pControlAlphFelder[7][7] = &m_ControlAlphFeld191;
	m_pControlAlphFelder[7][8] = &m_ControlAlphFeld181;
	m_pControlAlphFelder[7][9] = &m_ControlAlphFeld812;
	m_pControlAlphFelder[8][0] = &m_ControlAlphFeld183;
	m_pControlAlphFelder[8][1] = &m_ControlAlphFeld228;
	m_pControlAlphFelder[8][2] = &m_ControlAlphFeld184;
	m_pControlAlphFelder[8][3] = &m_ControlAlphFeld185;
	m_pControlAlphFelder[8][4] = &m_ControlAlphFeld186;
	m_pControlAlphFelder[8][5] = &m_ControlAlphFeld187;
	m_pControlAlphFelder[8][6] = &m_ControlAlphFeld188;
	m_pControlAlphFelder[8][7] = &m_ControlAlphFeld189;
	m_pControlAlphFelder[8][8] = &m_ControlAlphFeld190;
	m_pControlAlphFelder[8][9] = &m_ControlAlphFeld912;
	m_pControlAlphFelder[9][0] = &m_ControlAlphFeld229;
	m_pControlAlphFelder[9][1] = &m_ControlAlphFeld193;
	m_pControlAlphFelder[9][2] = &m_ControlAlphFeld194;
	m_pControlAlphFelder[9][3] = &m_ControlAlphFeld195;
	m_pControlAlphFelder[9][4] = &m_ControlAlphFeld196;
	m_pControlAlphFelder[9][5] = &m_ControlAlphFeld197;
	m_pControlAlphFelder[9][6] = &m_ControlAlphFeld198;
	m_pControlAlphFelder[9][7] = &m_ControlAlphFeld199;
	m_pControlAlphFelder[9][8] = &m_ControlAlphFeld200;
	m_pControlAlphFelder[9][9] = &m_ControlAlphFeld1012;
	
	// Font mit fester Breite erstellen und fuer alle Schluesselfelder setzen
	cf.CreatePointFont(80,"Courier");
	for (int i=0; i<HILL_MAX_DIM_GROSS; i++)
	{
		for (int j=0; j<HILL_MAX_DIM_GROSS; j++)
		{
			m_pControlFelder[i][j]->SetFont(&cf);
			m_pControlAlphFelder[i][j]->SetFont(&cf);
		}
	}
	
	CString str;
	for(int i=0;i<HILL_MAX_DIM_GROSS;i++)
	{
		for(int j=0;j<HILL_MAX_DIM_GROSS;j++)
		{
			m_pControlFelder[i][j]->GetWindowText(str);
			m_pControlAlphFelder[i][j]->SetWindowText(getAlphCode(str));
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
	i_multDirection  = (iHillMultiplicationType) ? 0 : 1;
	m_alphabetOffset = (hillklasse.firstPosNull) ? 0 : 1;
}


void CDlgShowKeyHill10x10::OnVerschluesseln() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	OnDecrypt();

	CString str;
	for(int i=0;i<HILL_MAX_DIM_GROSS;i++)
	{
		for(int j=0;j<HILL_MAX_DIM_GROSS;j++)
		{
			m_pControlFelder[i][j]->GetWindowText(str);
			m_pControlAlphFelder[i][j]->SetWindowText(getAlphCode(str));
		}
	}
}

void CDlgShowKeyHill10x10::OnEntschluesseln() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	OnDecrypt();

	CString str;
	for(int i=0;i<HILL_MAX_DIM_GROSS;i++)
	{
		for(int j=0;j<HILL_MAX_DIM_GROSS;j++)
		{
			m_pControlFelder[i][j]->GetWindowText(str);
			m_pControlAlphFelder[i][j]->SetWindowText(getAlphCode(str));
		}
	}
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
	cs += HILLSTR_ALPHABETOFFSET;
	cs += ' ';
	cs += char('0' + m_alphabetOffset);
	cs += ' ';
	cs += HILLSTR_MULTVARIANT;
	cs += ' ';
	cs += char('0' + i_multDirection);
	cs += " \0";

    LoadString(AfxGetInstanceHandle(),IDS_CRYPT_HILL,pc_str,STR_LAENGE_STRING_TABLE);
	CopyKey(pc_str, cs); 
	m_FeldUnsichtbar.SetWindowText(cs);
	m_FeldUnsichtbar.SetSel(0,-1);  // Alles markieren
	m_FeldUnsichtbar.Copy();

	CDialog::OnOK();
}


void CDlgShowKeyHill10x10::SchluesselAnzeigen(CString Key)
{
	int pos = Key.Find(HILLSTR_ALPHABETOFFSET);
	int iLaenge = pos, iDimension = 1;
	pos += strlen(HILLSTR_ALPHABETOFFSET) +1;
	assert(pos > 0);
	m_alphabetOffset = (Key.GetAt(pos) == '0') ? 0 : 1;
	pos = Key.Find(HILLSTR_MULTVARIANT);
	assert(pos > 0);
	pos += strlen(HILLSTR_MULTVARIANT) +1;
	i_multDirection = (Key.GetAt(pos) == '0') ? 0 : 1;

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
CString CDlgShowKeyHill10x10::getAlphCode(CString alphChar)
{
	CString str;
	for(int i=0;i<theApp.TextOptions.getAlphabet().GetLength();i++)
	{
		if(theApp.TextOptions.getAlphabet()[i] == alphChar)
		{
			str.Format("%d",i+1);
			
			if(str.GetLength() == 1)
				str.Insert(0,"0");
			return str;
		}
	}
	return "";
}
