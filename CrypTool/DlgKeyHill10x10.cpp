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
// HillEingabeGross.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeyHill5x5.h"
#include "DlgKeyHill10x10.h"
#include "HillEncryption.h"
#include "ChrTools.h"
#include "KeyRepository.h"
#include ".\dlgkeyhill10x10.h"
#include "DlgHillOptions.h"
#include "CrypToolTools.h"
#include "assert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHill10x10 


CDlgKeyHill10x10::CDlgKeyHill10x10(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyHill10x10::IDD, pParent)
   , m_HillBase(0)
	, m_pHillAlphInfo(_T(""))
{
}


CDlgKeyHill10x10::~CDlgKeyHill10x10()
{
}

void CDlgKeyHill10x10::init( CKeyHillBase *Hillbase )
{
   assert( Hillbase && Hillbase->key_range >= 10 );
   m_HillBase = Hillbase;
}


void CDlgKeyHill10x10::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

   DDX_Control(pDX, IDC_EDIT11,  m_HillBase->HillAlphMat[0][0] );
	DDX_Control(pDX, IDC_EDIT12,  m_HillBase->HillAlphMat[0][1]);
	DDX_Control(pDX, IDC_EDIT13,  m_HillBase->HillAlphMat[0][2]);
	DDX_Control(pDX, IDC_EDIT14,  m_HillBase->HillAlphMat[0][3]);
	DDX_Control(pDX, IDC_EDIT15,  m_HillBase->HillAlphMat[0][4]);
	DDX_Control(pDX, IDC_EDIT16,  m_HillBase->HillAlphMat[0][5]);
	DDX_Control(pDX, IDC_EDIT17,  m_HillBase->HillAlphMat[0][6]);
	DDX_Control(pDX, IDC_EDIT18,  m_HillBase->HillAlphMat[0][7]);
	DDX_Control(pDX, IDC_EDIT19,  m_HillBase->HillAlphMat[0][8]);
	DDX_Control(pDX, IDC_EDIT110, m_HillBase->HillAlphMat[0][9]);
	DDX_Control(pDX, IDC_EDIT21,  m_HillBase->HillAlphMat[1][0]);
	DDX_Control(pDX, IDC_EDIT22,  m_HillBase->HillAlphMat[1][1]);
	DDX_Control(pDX, IDC_EDIT23,  m_HillBase->HillAlphMat[1][2]);
	DDX_Control(pDX, IDC_EDIT24,  m_HillBase->HillAlphMat[1][3]);
	DDX_Control(pDX, IDC_EDIT25,  m_HillBase->HillAlphMat[1][4]);
	DDX_Control(pDX, IDC_EDIT26,  m_HillBase->HillAlphMat[1][5]);
	DDX_Control(pDX, IDC_EDIT27,  m_HillBase->HillAlphMat[1][6]);
	DDX_Control(pDX, IDC_EDIT28,  m_HillBase->HillAlphMat[1][7]);
	DDX_Control(pDX, IDC_EDIT29,  m_HillBase->HillAlphMat[1][8]);
	DDX_Control(pDX, IDC_EDIT210, m_HillBase->HillAlphMat[1][9]);
	DDX_Control(pDX, IDC_EDIT31,  m_HillBase->HillAlphMat[2][0]);
	DDX_Control(pDX, IDC_EDIT32,  m_HillBase->HillAlphMat[2][1]);
	DDX_Control(pDX, IDC_EDIT33,  m_HillBase->HillAlphMat[2][2]);
	DDX_Control(pDX, IDC_EDIT34,  m_HillBase->HillAlphMat[2][3]);
	DDX_Control(pDX, IDC_EDIT35,  m_HillBase->HillAlphMat[2][4]);
	DDX_Control(pDX, IDC_EDIT36,  m_HillBase->HillAlphMat[2][5]);
	DDX_Control(pDX, IDC_EDIT37,  m_HillBase->HillAlphMat[2][6]);
	DDX_Control(pDX, IDC_EDIT38,  m_HillBase->HillAlphMat[2][7]);
	DDX_Control(pDX, IDC_EDIT39,  m_HillBase->HillAlphMat[2][8]);
	DDX_Control(pDX, IDC_EDIT310, m_HillBase->HillAlphMat[2][9]);
	DDX_Control(pDX, IDC_EDIT41,  m_HillBase->HillAlphMat[3][0]);
	DDX_Control(pDX, IDC_EDIT42,  m_HillBase->HillAlphMat[3][1]);
	DDX_Control(pDX, IDC_EDIT43,  m_HillBase->HillAlphMat[3][2]);
	DDX_Control(pDX, IDC_EDIT44,  m_HillBase->HillAlphMat[3][3]);
	DDX_Control(pDX, IDC_EDIT45,  m_HillBase->HillAlphMat[3][4]);
	DDX_Control(pDX, IDC_EDIT46,  m_HillBase->HillAlphMat[3][5]);
	DDX_Control(pDX, IDC_EDIT47,  m_HillBase->HillAlphMat[3][6]);
	DDX_Control(pDX, IDC_EDIT48,  m_HillBase->HillAlphMat[3][7]);
	DDX_Control(pDX, IDC_EDIT49,  m_HillBase->HillAlphMat[3][8]);
	DDX_Control(pDX, IDC_EDIT410, m_HillBase->HillAlphMat[3][9]);
	DDX_Control(pDX, IDC_EDIT51,  m_HillBase->HillAlphMat[4][0]);
	DDX_Control(pDX, IDC_EDIT52,  m_HillBase->HillAlphMat[4][1]);
	DDX_Control(pDX, IDC_EDIT53,  m_HillBase->HillAlphMat[4][2]);
	DDX_Control(pDX, IDC_EDIT54,  m_HillBase->HillAlphMat[4][3]);
	DDX_Control(pDX, IDC_EDIT55,  m_HillBase->HillAlphMat[4][4]);
	DDX_Control(pDX, IDC_EDIT56,  m_HillBase->HillAlphMat[4][5]);
	DDX_Control(pDX, IDC_EDIT57,  m_HillBase->HillAlphMat[4][6]);
	DDX_Control(pDX, IDC_EDIT58,  m_HillBase->HillAlphMat[4][7]);
	DDX_Control(pDX, IDC_EDIT59,  m_HillBase->HillAlphMat[4][8]);
	DDX_Control(pDX, IDC_EDIT510, m_HillBase->HillAlphMat[4][9]);
	DDX_Control(pDX, IDC_EDIT61,  m_HillBase->HillAlphMat[5][0]);
	DDX_Control(pDX, IDC_EDIT62,  m_HillBase->HillAlphMat[5][1]);
	DDX_Control(pDX, IDC_EDIT63,  m_HillBase->HillAlphMat[5][2]);
	DDX_Control(pDX, IDC_EDIT64,  m_HillBase->HillAlphMat[5][3]);
	DDX_Control(pDX, IDC_EDIT65,  m_HillBase->HillAlphMat[5][4]);
	DDX_Control(pDX, IDC_EDIT66,  m_HillBase->HillAlphMat[5][5]);
	DDX_Control(pDX, IDC_EDIT67,  m_HillBase->HillAlphMat[5][6]);
	DDX_Control(pDX, IDC_EDIT68,  m_HillBase->HillAlphMat[5][7]);
	DDX_Control(pDX, IDC_EDIT69,  m_HillBase->HillAlphMat[5][8]);
	DDX_Control(pDX, IDC_EDIT610, m_HillBase->HillAlphMat[5][9]);
	DDX_Control(pDX, IDC_EDIT71,  m_HillBase->HillAlphMat[6][0]);
	DDX_Control(pDX, IDC_EDIT72,  m_HillBase->HillAlphMat[6][1]);
	DDX_Control(pDX, IDC_EDIT73,  m_HillBase->HillAlphMat[6][2]);
	DDX_Control(pDX, IDC_EDIT74,  m_HillBase->HillAlphMat[6][3]);
	DDX_Control(pDX, IDC_EDIT75,  m_HillBase->HillAlphMat[6][4]);
	DDX_Control(pDX, IDC_EDIT76,  m_HillBase->HillAlphMat[6][5]);
	DDX_Control(pDX, IDC_EDIT77,  m_HillBase->HillAlphMat[6][6]);
	DDX_Control(pDX, IDC_EDIT78,  m_HillBase->HillAlphMat[6][7]);
	DDX_Control(pDX, IDC_EDIT79,  m_HillBase->HillAlphMat[6][8]);
	DDX_Control(pDX, IDC_EDIT710, m_HillBase->HillAlphMat[6][9]);
	DDX_Control(pDX, IDC_EDIT81,  m_HillBase->HillAlphMat[7][0]);
	DDX_Control(pDX, IDC_EDIT82,  m_HillBase->HillAlphMat[7][1]);
	DDX_Control(pDX, IDC_EDIT83,  m_HillBase->HillAlphMat[7][2]);
	DDX_Control(pDX, IDC_EDIT84,  m_HillBase->HillAlphMat[7][3]);
	DDX_Control(pDX, IDC_EDIT85,  m_HillBase->HillAlphMat[7][4]);
	DDX_Control(pDX, IDC_EDIT86,  m_HillBase->HillAlphMat[7][5]);
	DDX_Control(pDX, IDC_EDIT87,  m_HillBase->HillAlphMat[7][6]);
	DDX_Control(pDX, IDC_EDIT88,  m_HillBase->HillAlphMat[7][7]);
	DDX_Control(pDX, IDC_EDIT89,  m_HillBase->HillAlphMat[7][8]);
	DDX_Control(pDX, IDC_EDIT810, m_HillBase->HillAlphMat[7][9]);
	DDX_Control(pDX, IDC_EDIT91,  m_HillBase->HillAlphMat[8][0]);
	DDX_Control(pDX, IDC_EDIT92,  m_HillBase->HillAlphMat[8][1]);
	DDX_Control(pDX, IDC_EDIT93,  m_HillBase->HillAlphMat[8][2]);
	DDX_Control(pDX, IDC_EDIT94,  m_HillBase->HillAlphMat[8][3]);
	DDX_Control(pDX, IDC_EDIT95,  m_HillBase->HillAlphMat[8][4]);
	DDX_Control(pDX, IDC_EDIT96,  m_HillBase->HillAlphMat[8][5]);
	DDX_Control(pDX, IDC_EDIT97,  m_HillBase->HillAlphMat[8][6]);
	DDX_Control(pDX, IDC_EDIT98,  m_HillBase->HillAlphMat[8][7]);
	DDX_Control(pDX, IDC_EDIT99,  m_HillBase->HillAlphMat[8][8]);
	DDX_Control(pDX, IDC_EDIT910, m_HillBase->HillAlphMat[8][9]);
	DDX_Control(pDX, IDC_EDIT101, m_HillBase->HillAlphMat[9][0]);
	DDX_Control(pDX, IDC_EDIT102, m_HillBase->HillAlphMat[9][1]);
	DDX_Control(pDX, IDC_EDIT103, m_HillBase->HillAlphMat[9][2]);
	DDX_Control(pDX, IDC_EDIT104, m_HillBase->HillAlphMat[9][3]);
	DDX_Control(pDX, IDC_EDIT105, m_HillBase->HillAlphMat[9][4]);
	DDX_Control(pDX, IDC_EDIT106, m_HillBase->HillAlphMat[9][5]);
	DDX_Control(pDX, IDC_EDIT107, m_HillBase->HillAlphMat[9][6]);
	DDX_Control(pDX, IDC_EDIT108, m_HillBase->HillAlphMat[9][7]);
	DDX_Control(pDX, IDC_EDIT109, m_HillBase->HillAlphMat[9][8]);
	DDX_Control(pDX, IDC_EDIT1010,m_HillBase->HillAlphMat[9][9]);

	DDX_Control(pDX, IDC_EDIT40,  m_HillBase->HillNumMat[0][0] );
	DDX_Control(pDX, IDC_EDIT50,  m_HillBase->HillNumMat[0][1] );
	DDX_Control(pDX, IDC_EDIT20,  m_HillBase->HillNumMat[0][2] );
	DDX_Control(pDX, IDC_EDIT90,  m_HillBase->HillNumMat[0][3] );
	DDX_Control(pDX, IDC_EDIT100, m_HillBase->HillNumMat[0][4] );
	DDX_Control(pDX, IDC_EDIT117, m_HillBase->HillNumMat[0][5] );
	DDX_Control(pDX, IDC_EDIT118, m_HillBase->HillNumMat[0][6] );
	DDX_Control(pDX, IDC_EDIT119, m_HillBase->HillNumMat[0][7] );
	DDX_Control(pDX, IDC_EDIT60,  m_HillBase->HillNumMat[0][8] );
	DDX_Control(pDX, IDC_EDIT125, m_HillBase->HillNumMat[0][9] );
	DDX_Control(pDX, IDC_EDIT127, m_HillBase->HillNumMat[1][0] );
	DDX_Control(pDX, IDC_EDIT134, m_HillBase->HillNumMat[1][1] );
	DDX_Control(pDX, IDC_EDIT135, m_HillBase->HillNumMat[1][2] );
	DDX_Control(pDX, IDC_EDIT136, m_HillBase->HillNumMat[1][3] );
	DDX_Control(pDX, IDC_EDIT70,  m_HillBase->HillNumMat[1][4] );
	DDX_Control(pDX, IDC_EDIT137, m_HillBase->HillNumMat[1][5] );
	DDX_Control(pDX, IDC_EDIT138, m_HillBase->HillNumMat[1][6] );
	DDX_Control(pDX, IDC_EDIT139, m_HillBase->HillNumMat[1][7] );
	DDX_Control(pDX, IDC_EDIT80,  m_HillBase->HillNumMat[1][8] );
	DDX_Control(pDX, IDC_EDIT211, m_HillBase->HillNumMat[1][9] );
	DDX_Control(pDX, IDC_EDIT140, m_HillBase->HillNumMat[2][0] );
	DDX_Control(pDX, IDC_EDIT141, m_HillBase->HillNumMat[2][1] );
	DDX_Control(pDX, IDC_EDIT142, m_HillBase->HillNumMat[2][2] );
	DDX_Control(pDX, IDC_EDIT143, m_HillBase->HillNumMat[2][3] );
	DDX_Control(pDX, IDC_EDIT144, m_HillBase->HillNumMat[2][4] );
	DDX_Control(pDX, IDC_EDIT145, m_HillBase->HillNumMat[2][5] );
	DDX_Control(pDX, IDC_EDIT146, m_HillBase->HillNumMat[2][6] );
	DDX_Control(pDX, IDC_EDIT147, m_HillBase->HillNumMat[2][7] );
	DDX_Control(pDX, IDC_EDIT148, m_HillBase->HillNumMat[2][8] );
	DDX_Control(pDX, IDC_EDIT311, m_HillBase->HillNumMat[2][9] );
	DDX_Control(pDX, IDC_EDIT149, m_HillBase->HillNumMat[3][0] );
	DDX_Control(pDX, IDC_EDIT150, m_HillBase->HillNumMat[3][1] );
	DDX_Control(pDX, IDC_EDIT151, m_HillBase->HillNumMat[3][2] );
	DDX_Control(pDX, IDC_EDIT152, m_HillBase->HillNumMat[3][3] );
	DDX_Control(pDX, IDC_EDIT153, m_HillBase->HillNumMat[3][4] );
	DDX_Control(pDX, IDC_EDIT154, m_HillBase->HillNumMat[3][5] );
	DDX_Control(pDX, IDC_EDIT155, m_HillBase->HillNumMat[3][6] );
	DDX_Control(pDX, IDC_EDIT156, m_HillBase->HillNumMat[3][7] );
	DDX_Control(pDX, IDC_EDIT157, m_HillBase->HillNumMat[3][8] );
	DDX_Control(pDX, IDC_EDIT411, m_HillBase->HillNumMat[3][9] );
	DDX_Control(pDX, IDC_EDIT158, m_HillBase->HillNumMat[4][0] );
	DDX_Control(pDX, IDC_EDIT159, m_HillBase->HillNumMat[4][1] );
	DDX_Control(pDX, IDC_EDIT113, m_HillBase->HillNumMat[4][2] );
	DDX_Control(pDX, IDC_EDIT160, m_HillBase->HillNumMat[4][3] );
	DDX_Control(pDX, IDC_EDIT161, m_HillBase->HillNumMat[4][4] );
	DDX_Control(pDX, IDC_EDIT162, m_HillBase->HillNumMat[4][5] );
	DDX_Control(pDX, IDC_EDIT163, m_HillBase->HillNumMat[4][6] );
	DDX_Control(pDX, IDC_EDIT164, m_HillBase->HillNumMat[4][7] );
	DDX_Control(pDX, IDC_EDIT165, m_HillBase->HillNumMat[4][8] );
	DDX_Control(pDX, IDC_EDIT511, m_HillBase->HillNumMat[4][9] );
	DDX_Control(pDX, IDC_EDIT166, m_HillBase->HillNumMat[5][0] );
	DDX_Control(pDX, IDC_EDIT167, m_HillBase->HillNumMat[5][1] );
	DDX_Control(pDX, IDC_EDIT168, m_HillBase->HillNumMat[5][2] );
	DDX_Control(pDX, IDC_EDIT169, m_HillBase->HillNumMat[5][3] );
	DDX_Control(pDX, IDC_EDIT170, m_HillBase->HillNumMat[5][4] );
	DDX_Control(pDX, IDC_EDIT171, m_HillBase->HillNumMat[5][5] );
	DDX_Control(pDX, IDC_EDIT172, m_HillBase->HillNumMat[5][6] );
	DDX_Control(pDX, IDC_EDIT173, m_HillBase->HillNumMat[5][7] );
	DDX_Control(pDX, IDC_EDIT174, m_HillBase->HillNumMat[5][8] );
	DDX_Control(pDX, IDC_EDIT611, m_HillBase->HillNumMat[5][9] );
	DDX_Control(pDX, IDC_EDIT175, m_HillBase->HillNumMat[6][0] );
	DDX_Control(pDX, IDC_EDIT176, m_HillBase->HillNumMat[6][1] );
	DDX_Control(pDX, IDC_EDIT177, m_HillBase->HillNumMat[6][2] );
	DDX_Control(pDX, IDC_EDIT178, m_HillBase->HillNumMat[6][3] );
	DDX_Control(pDX, IDC_EDIT179, m_HillBase->HillNumMat[6][4] );
	DDX_Control(pDX, IDC_EDIT180, m_HillBase->HillNumMat[6][5] );
	DDX_Control(pDX, IDC_EDIT181, m_HillBase->HillNumMat[6][6] );
	DDX_Control(pDX, IDC_EDIT182, m_HillBase->HillNumMat[6][7] );
	DDX_Control(pDX, IDC_EDIT183, m_HillBase->HillNumMat[6][8] );
	DDX_Control(pDX, IDC_EDIT711, m_HillBase->HillNumMat[6][9] );
	DDX_Control(pDX, IDC_EDIT184, m_HillBase->HillNumMat[7][0] );
	DDX_Control(pDX, IDC_EDIT185, m_HillBase->HillNumMat[7][1] );
	DDX_Control(pDX, IDC_EDIT186, m_HillBase->HillNumMat[7][2] );
	DDX_Control(pDX, IDC_EDIT187, m_HillBase->HillNumMat[7][3] );
	DDX_Control(pDX, IDC_EDIT188, m_HillBase->HillNumMat[7][4] );
	DDX_Control(pDX, IDC_EDIT189, m_HillBase->HillNumMat[7][5] );
	DDX_Control(pDX, IDC_EDIT190, m_HillBase->HillNumMat[7][6] );
	DDX_Control(pDX, IDC_EDIT191, m_HillBase->HillNumMat[7][7] );
	DDX_Control(pDX, IDC_EDIT192, m_HillBase->HillNumMat[7][8] );
	DDX_Control(pDX, IDC_EDIT811, m_HillBase->HillNumMat[7][9] );
	DDX_Control(pDX, IDC_EDIT193, m_HillBase->HillNumMat[8][0] );
	DDX_Control(pDX, IDC_EDIT194, m_HillBase->HillNumMat[8][1] );
	DDX_Control(pDX, IDC_EDIT195, m_HillBase->HillNumMat[8][2] );
	DDX_Control(pDX, IDC_EDIT196, m_HillBase->HillNumMat[8][3] );
	DDX_Control(pDX, IDC_EDIT197, m_HillBase->HillNumMat[8][4] );
	DDX_Control(pDX, IDC_EDIT198, m_HillBase->HillNumMat[8][5] );
	DDX_Control(pDX, IDC_EDIT199, m_HillBase->HillNumMat[8][6] );
	DDX_Control(pDX, IDC_EDIT200, m_HillBase->HillNumMat[8][7] );
	DDX_Control(pDX, IDC_EDIT201, m_HillBase->HillNumMat[8][8] );
	DDX_Control(pDX, IDC_EDIT911, m_HillBase->HillNumMat[8][9] );
	DDX_Control(pDX, IDC_EDIT202, m_HillBase->HillNumMat[9][0] );
	DDX_Control(pDX, IDC_EDIT203, m_HillBase->HillNumMat[9][1] );
	DDX_Control(pDX, IDC_EDIT204, m_HillBase->HillNumMat[9][2] );
	DDX_Control(pDX, IDC_EDIT205, m_HillBase->HillNumMat[9][3] );
	DDX_Control(pDX, IDC_EDIT206, m_HillBase->HillNumMat[9][4] );
	DDX_Control(pDX, IDC_EDIT207, m_HillBase->HillNumMat[9][5] );
	DDX_Control(pDX, IDC_EDIT208, m_HillBase->HillNumMat[9][6] );
	DDX_Control(pDX, IDC_EDIT209, m_HillBase->HillNumMat[9][7] );
	DDX_Control(pDX, IDC_EDIT212, m_HillBase->HillNumMat[9][8] );
	DDX_Control(pDX, IDC_EDIT1011,m_HillBase->HillNumMat[9][9] );

   DDX_Check(pDX, IDC_CHECK1, m_HillBase->verbose);
	DDX_Text(pDX, IDC_EDIT3, m_pHillAlphInfo);
   DDX_Text(pDX, IDC_EDIT2, m_HillBase->HillOptions.m_offset );
   DDV_MinMaxInt(pDX, m_HillBase->HillOptions.m_offset, 0, 1);
}

BEGIN_MESSAGE_MAP(CDlgKeyHill10x10, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyHill10x10)

	ON_EN_UPDATE(IDC_EDIT11, OnUpdateMat11)
	ON_EN_UPDATE(IDC_EDIT12, OnUpdateMat12)
	ON_EN_UPDATE(IDC_EDIT13, OnUpdateMat13)
	ON_EN_UPDATE(IDC_EDIT14, OnUpdateMat14)
	ON_EN_UPDATE(IDC_EDIT15, OnUpdateMat15)
	ON_EN_UPDATE(IDC_EDIT16, OnUpdateMat16)
	ON_EN_UPDATE(IDC_EDIT17, OnUpdateMat17)
	ON_EN_UPDATE(IDC_EDIT18, OnUpdateMat18)
	ON_EN_UPDATE(IDC_EDIT19, OnUpdateMat19)
	ON_EN_UPDATE(IDC_EDIT110, OnUpdateMat110)
	ON_EN_UPDATE(IDC_EDIT21, OnUpdateMat21)
	ON_EN_UPDATE(IDC_EDIT22, OnUpdateMat22)
	ON_EN_UPDATE(IDC_EDIT23, OnUpdateMat23)
	ON_EN_UPDATE(IDC_EDIT24, OnUpdateMat24)
	ON_EN_UPDATE(IDC_EDIT25, OnUpdateMat25)
	ON_EN_UPDATE(IDC_EDIT26, OnUpdateMat26)
	ON_EN_UPDATE(IDC_EDIT27, OnUpdateMat27)
	ON_EN_UPDATE(IDC_EDIT28, OnUpdateMat28)
	ON_EN_UPDATE(IDC_EDIT29, OnUpdateMat29)
	ON_EN_UPDATE(IDC_EDIT210, OnUpdateMat210)
	ON_EN_UPDATE(IDC_EDIT31, OnUpdateMat31)
	ON_EN_UPDATE(IDC_EDIT32, OnUpdateMat32)
	ON_EN_UPDATE(IDC_EDIT33, OnUpdateMat33)
	ON_EN_UPDATE(IDC_EDIT34, OnUpdateMat34)
	ON_EN_UPDATE(IDC_EDIT35, OnUpdateMat35)
	ON_EN_UPDATE(IDC_EDIT36, OnUpdateMat36)
	ON_EN_UPDATE(IDC_EDIT37, OnUpdateMat37)
	ON_EN_UPDATE(IDC_EDIT38, OnUpdateMat38)
	ON_EN_UPDATE(IDC_EDIT39, OnUpdateMat39)
	ON_EN_UPDATE(IDC_EDIT310, OnUpdateMat310)
	ON_EN_UPDATE(IDC_EDIT41, OnUpdateMat41)
	ON_EN_UPDATE(IDC_EDIT42, OnUpdateMat42)
	ON_EN_UPDATE(IDC_EDIT43, OnUpdateMat43)
	ON_EN_UPDATE(IDC_EDIT44, OnUpdateMat44)
	ON_EN_UPDATE(IDC_EDIT45, OnUpdateMat45)
	ON_EN_UPDATE(IDC_EDIT46, OnUpdateMat46)
	ON_EN_UPDATE(IDC_EDIT47, OnUpdateMat47)
	ON_EN_UPDATE(IDC_EDIT48, OnUpdateMat48)
	ON_EN_UPDATE(IDC_EDIT49, OnUpdateMat49)
	ON_EN_UPDATE(IDC_EDIT410, OnUpdateMat410)
	ON_EN_UPDATE(IDC_EDIT51, OnUpdateMat51)
	ON_EN_UPDATE(IDC_EDIT52, OnUpdateMat52)
	ON_EN_UPDATE(IDC_EDIT53, OnUpdateMat53)
	ON_EN_UPDATE(IDC_EDIT54, OnUpdateMat54)
	ON_EN_UPDATE(IDC_EDIT55, OnUpdateMat55)
	ON_EN_UPDATE(IDC_EDIT56, OnUpdateMat56)
	ON_EN_UPDATE(IDC_EDIT57, OnUpdateMat57)
	ON_EN_UPDATE(IDC_EDIT58, OnUpdateMat58)
	ON_EN_UPDATE(IDC_EDIT59, OnUpdateMat59)
	ON_EN_UPDATE(IDC_EDIT510, OnUpdateMat510)
	ON_EN_UPDATE(IDC_EDIT61, OnUpdateMat61)
	ON_EN_UPDATE(IDC_EDIT62, OnUpdateMat62)
	ON_EN_UPDATE(IDC_EDIT63, OnUpdateMat63)
	ON_EN_UPDATE(IDC_EDIT64, OnUpdateMat64)
	ON_EN_UPDATE(IDC_EDIT65, OnUpdateMat65)
	ON_EN_UPDATE(IDC_EDIT66, OnUpdateMat66)
	ON_EN_UPDATE(IDC_EDIT67, OnUpdateMat67)
	ON_EN_UPDATE(IDC_EDIT68, OnUpdateMat68)
	ON_EN_UPDATE(IDC_EDIT69, OnUpdateMat69)
	ON_EN_UPDATE(IDC_EDIT610, OnUpdateMat610)
	ON_EN_UPDATE(IDC_EDIT71, OnUpdateMat71)
	ON_EN_UPDATE(IDC_EDIT72, OnUpdateMat72)
	ON_EN_UPDATE(IDC_EDIT73, OnUpdateMat73)
	ON_EN_UPDATE(IDC_EDIT74, OnUpdateMat74)
	ON_EN_UPDATE(IDC_EDIT75, OnUpdateMat75)
	ON_EN_UPDATE(IDC_EDIT76, OnUpdateMat76)
	ON_EN_UPDATE(IDC_EDIT77, OnUpdateMat77)
	ON_EN_UPDATE(IDC_EDIT78, OnUpdateMat78)
	ON_EN_UPDATE(IDC_EDIT79, OnUpdateMat79)
	ON_EN_UPDATE(IDC_EDIT710, OnUpdateMat710)
	ON_EN_UPDATE(IDC_EDIT81, OnUpdateMat81)
	ON_EN_UPDATE(IDC_EDIT82, OnUpdateMat82)
	ON_EN_UPDATE(IDC_EDIT83, OnUpdateMat83)
	ON_EN_UPDATE(IDC_EDIT84, OnUpdateMat84)
	ON_EN_UPDATE(IDC_EDIT85, OnUpdateMat85)
	ON_EN_UPDATE(IDC_EDIT86, OnUpdateMat86)
	ON_EN_UPDATE(IDC_EDIT87, OnUpdateMat87)
	ON_EN_UPDATE(IDC_EDIT88, OnUpdateMat88)
	ON_EN_UPDATE(IDC_EDIT89, OnUpdateMat89)
	ON_EN_UPDATE(IDC_EDIT810, OnUpdateMat810)
	ON_EN_UPDATE(IDC_EDIT91, OnUpdateMat91)
	ON_EN_UPDATE(IDC_EDIT92, OnUpdateMat92)
	ON_EN_UPDATE(IDC_EDIT93, OnUpdateMat93)
	ON_EN_UPDATE(IDC_EDIT94, OnUpdateMat94)
	ON_EN_UPDATE(IDC_EDIT95, OnUpdateMat95)
	ON_EN_UPDATE(IDC_EDIT96, OnUpdateMat96)
	ON_EN_UPDATE(IDC_EDIT97, OnUpdateMat97)
	ON_EN_UPDATE(IDC_EDIT98, OnUpdateMat98)
	ON_EN_UPDATE(IDC_EDIT99, OnUpdateMat99)
	ON_EN_UPDATE(IDC_EDIT910, OnUpdateMat910)
	ON_EN_UPDATE(IDC_EDIT101, OnUpdateMat101)
	ON_EN_UPDATE(IDC_EDIT102, OnUpdateMat102)
	ON_EN_UPDATE(IDC_EDIT103, OnUpdateMat103)
	ON_EN_UPDATE(IDC_EDIT104, OnUpdateMat104)
	ON_EN_UPDATE(IDC_EDIT105, OnUpdateMat105)
	ON_EN_UPDATE(IDC_EDIT106, OnUpdateMat106)
	ON_EN_UPDATE(IDC_EDIT107, OnUpdateMat107)
	ON_EN_UPDATE(IDC_EDIT108, OnUpdateMat108)
	ON_EN_UPDATE(IDC_EDIT109, OnUpdateMat109)
	ON_EN_UPDATE(IDC_EDIT1010, OnUpdateMat1010)

	ON_EN_UPDATE(IDC_EDIT40, OnUpdateMat40)
	ON_EN_UPDATE(IDC_EDIT50, OnUpdateMat50)
	ON_EN_UPDATE(IDC_EDIT20, OnUpdateMat20)
	ON_EN_UPDATE(IDC_EDIT90, OnUpdateMat90)
	ON_EN_UPDATE(IDC_EDIT100, OnUpdateMat100)
	ON_EN_UPDATE(IDC_EDIT117, OnUpdateMat117)
	ON_EN_UPDATE(IDC_EDIT118, OnUpdateMat118)
	ON_EN_UPDATE(IDC_EDIT119, OnUpdateMat119)
	ON_EN_UPDATE(IDC_EDIT60, OnUpdateMat60)
	ON_EN_UPDATE(IDC_EDIT125, OnUpdateMat125)
	ON_EN_UPDATE(IDC_EDIT127, OnUpdateMat127)
	ON_EN_UPDATE(IDC_EDIT134, OnUpdateMat134)
	ON_EN_UPDATE(IDC_EDIT135, OnUpdateMat135)
	ON_EN_UPDATE(IDC_EDIT136, OnUpdateMat136)
	ON_EN_UPDATE(IDC_EDIT70, OnUpdateMat70)
	ON_EN_UPDATE(IDC_EDIT137, OnUpdateMat137)
	ON_EN_UPDATE(IDC_EDIT138, OnUpdateMat138)
	ON_EN_UPDATE(IDC_EDIT139, OnUpdateMat139)
	ON_EN_UPDATE(IDC_EDIT80, OnUpdateMat80)
	ON_EN_UPDATE(IDC_EDIT211, OnUpdateMat211)
	ON_EN_UPDATE(IDC_EDIT140, OnUpdateMat140)
	ON_EN_UPDATE(IDC_EDIT141, OnUpdateMat141)
	ON_EN_UPDATE(IDC_EDIT142, OnUpdateMat142)
	ON_EN_UPDATE(IDC_EDIT143, OnUpdateMat143)
	ON_EN_UPDATE(IDC_EDIT144, OnUpdateMat144)
	ON_EN_UPDATE(IDC_EDIT145, OnUpdateMat145)
	ON_EN_UPDATE(IDC_EDIT146, OnUpdateMat146)
	ON_EN_UPDATE(IDC_EDIT147, OnUpdateMat147)
	ON_EN_UPDATE(IDC_EDIT148, OnUpdateMat148)
	ON_EN_UPDATE(IDC_EDIT311, OnUpdateMat311)
	ON_EN_UPDATE(IDC_EDIT149, OnUpdateMat149)
	ON_EN_UPDATE(IDC_EDIT150, OnUpdateMat150)
	ON_EN_UPDATE(IDC_EDIT151, OnUpdateMat151)
	ON_EN_UPDATE(IDC_EDIT152, OnUpdateMat152)
	ON_EN_UPDATE(IDC_EDIT153, OnUpdateMat153)
	ON_EN_UPDATE(IDC_EDIT154, OnUpdateMat154)
	ON_EN_UPDATE(IDC_EDIT155, OnUpdateMat155)
	ON_EN_UPDATE(IDC_EDIT156, OnUpdateMat156)
	ON_EN_UPDATE(IDC_EDIT157, OnUpdateMat157)
	ON_EN_UPDATE(IDC_EDIT411, OnUpdateMat411)
	ON_EN_UPDATE(IDC_EDIT158, OnUpdateMat158)
	ON_EN_UPDATE(IDC_EDIT159, OnUpdateMat159)
	ON_EN_UPDATE(IDC_EDIT113, OnUpdateMat113)
	ON_EN_UPDATE(IDC_EDIT160, OnUpdateMat160)
	ON_EN_UPDATE(IDC_EDIT161, OnUpdateMat161)
	ON_EN_UPDATE(IDC_EDIT162, OnUpdateMat162)
	ON_EN_UPDATE(IDC_EDIT163, OnUpdateMat163)
	ON_EN_UPDATE(IDC_EDIT164, OnUpdateMat164)
	ON_EN_UPDATE(IDC_EDIT165, OnUpdateMat165)
	ON_EN_UPDATE(IDC_EDIT511, OnUpdateMat511)
	ON_EN_UPDATE(IDC_EDIT166, OnUpdateMat166)
	ON_EN_UPDATE(IDC_EDIT167, OnUpdateMat167)
	ON_EN_UPDATE(IDC_EDIT168, OnUpdateMat168)
	ON_EN_UPDATE(IDC_EDIT169, OnUpdateMat169)
	ON_EN_UPDATE(IDC_EDIT170, OnUpdateMat170)
	ON_EN_UPDATE(IDC_EDIT171, OnUpdateMat171)
	ON_EN_UPDATE(IDC_EDIT172, OnUpdateMat172)
	ON_EN_UPDATE(IDC_EDIT173, OnUpdateMat173)
	ON_EN_UPDATE(IDC_EDIT174, OnUpdateMat174)
	ON_EN_UPDATE(IDC_EDIT611, OnUpdateMat611)
	ON_EN_UPDATE(IDC_EDIT175, OnUpdateMat175)
	ON_EN_UPDATE(IDC_EDIT176, OnUpdateMat176)
	ON_EN_UPDATE(IDC_EDIT177, OnUpdateMat177)
	ON_EN_UPDATE(IDC_EDIT178, OnUpdateMat178)
	ON_EN_UPDATE(IDC_EDIT179, OnUpdateMat179)
	ON_EN_UPDATE(IDC_EDIT180, OnUpdateMat180)
	ON_EN_UPDATE(IDC_EDIT181, OnUpdateMat181)
	ON_EN_UPDATE(IDC_EDIT182, OnUpdateMat182)
	ON_EN_UPDATE(IDC_EDIT183, OnUpdateMat183)
	ON_EN_UPDATE(IDC_EDIT711, OnUpdateMat711)
	ON_EN_UPDATE(IDC_EDIT184, OnUpdateMat184)
	ON_EN_UPDATE(IDC_EDIT185, OnUpdateMat185)
	ON_EN_UPDATE(IDC_EDIT186, OnUpdateMat186)
	ON_EN_UPDATE(IDC_EDIT187, OnUpdateMat187)
	ON_EN_UPDATE(IDC_EDIT188, OnUpdateMat188)
	ON_EN_UPDATE(IDC_EDIT189, OnUpdateMat189)
	ON_EN_UPDATE(IDC_EDIT190, OnUpdateMat190)
	ON_EN_UPDATE(IDC_EDIT191, OnUpdateMat191)
	ON_EN_UPDATE(IDC_EDIT192, OnUpdateMat192)
	ON_EN_UPDATE(IDC_EDIT811, OnUpdateMat811)
	ON_EN_UPDATE(IDC_EDIT193, OnUpdateMat193)
	ON_EN_UPDATE(IDC_EDIT194, OnUpdateMat194)
	ON_EN_UPDATE(IDC_EDIT195, OnUpdateMat195)
	ON_EN_UPDATE(IDC_EDIT196, OnUpdateMat196)
	ON_EN_UPDATE(IDC_EDIT197, OnUpdateMat197)
	ON_EN_UPDATE(IDC_EDIT198, OnUpdateMat198)
	ON_EN_UPDATE(IDC_EDIT199, OnUpdateMat199)
	ON_EN_UPDATE(IDC_EDIT200, OnUpdateMat200)
	ON_EN_UPDATE(IDC_EDIT201, OnUpdateMat201)
	ON_EN_UPDATE(IDC_EDIT911, OnUpdateMat911)
	ON_EN_UPDATE(IDC_EDIT202, OnUpdateMat202)
	ON_EN_UPDATE(IDC_EDIT203, OnUpdateMat203)
	ON_EN_UPDATE(IDC_EDIT204, OnUpdateMat204)
	ON_EN_UPDATE(IDC_EDIT205, OnUpdateMat205)
	ON_EN_UPDATE(IDC_EDIT206, OnUpdateMat206)
	ON_EN_UPDATE(IDC_EDIT207, OnUpdateMat207)
	ON_EN_UPDATE(IDC_EDIT208, OnUpdateMat208)
	ON_EN_UPDATE(IDC_EDIT209, OnUpdateMat209)
	ON_EN_UPDATE(IDC_EDIT212, OnUpdateMat212)
	ON_EN_UPDATE(IDC_EDIT1011, OnUpdateMat1011)

	ON_EN_KILLFOCUS(IDC_EDIT40, OnExitMat40)
	ON_EN_KILLFOCUS(IDC_EDIT50, OnExitMat50)
	ON_EN_KILLFOCUS(IDC_EDIT20, OnExitMat20)
	ON_EN_KILLFOCUS(IDC_EDIT90, OnExitMat90)
	ON_EN_KILLFOCUS(IDC_EDIT100, OnExitMat100)
	ON_EN_KILLFOCUS(IDC_EDIT117, OnExitMat117)
	ON_EN_KILLFOCUS(IDC_EDIT118, OnExitMat118)
	ON_EN_KILLFOCUS(IDC_EDIT119, OnExitMat119)
	ON_EN_KILLFOCUS(IDC_EDIT60, OnExitMat60)
	ON_EN_KILLFOCUS(IDC_EDIT125, OnExitMat125)
	ON_EN_KILLFOCUS(IDC_EDIT127, OnExitMat127)
	ON_EN_KILLFOCUS(IDC_EDIT134, OnExitMat134)
	ON_EN_KILLFOCUS(IDC_EDIT135, OnExitMat135)
	ON_EN_KILLFOCUS(IDC_EDIT136, OnExitMat136)
	ON_EN_KILLFOCUS(IDC_EDIT70, OnExitMat70)
	ON_EN_KILLFOCUS(IDC_EDIT137, OnExitMat137)
	ON_EN_KILLFOCUS(IDC_EDIT138, OnExitMat138)
	ON_EN_KILLFOCUS(IDC_EDIT139, OnExitMat139)
	ON_EN_KILLFOCUS(IDC_EDIT80, OnExitMat80)
	ON_EN_KILLFOCUS(IDC_EDIT211, OnExitMat211)
	ON_EN_KILLFOCUS(IDC_EDIT140, OnExitMat140)
	ON_EN_KILLFOCUS(IDC_EDIT141, OnExitMat141)
	ON_EN_KILLFOCUS(IDC_EDIT142, OnExitMat142)
	ON_EN_KILLFOCUS(IDC_EDIT143, OnExitMat143)
	ON_EN_KILLFOCUS(IDC_EDIT144, OnExitMat144)
	ON_EN_KILLFOCUS(IDC_EDIT145, OnExitMat145)
	ON_EN_KILLFOCUS(IDC_EDIT146, OnExitMat146)
	ON_EN_KILLFOCUS(IDC_EDIT147, OnExitMat147)
	ON_EN_KILLFOCUS(IDC_EDIT148, OnExitMat148)
	ON_EN_KILLFOCUS(IDC_EDIT311, OnExitMat311)
	ON_EN_KILLFOCUS(IDC_EDIT149, OnExitMat149)
	ON_EN_KILLFOCUS(IDC_EDIT150, OnExitMat150)
	ON_EN_KILLFOCUS(IDC_EDIT151, OnExitMat151)
	ON_EN_KILLFOCUS(IDC_EDIT152, OnExitMat152)
	ON_EN_KILLFOCUS(IDC_EDIT153, OnExitMat153)
	ON_EN_KILLFOCUS(IDC_EDIT154, OnExitMat154)
	ON_EN_KILLFOCUS(IDC_EDIT155, OnExitMat155)
	ON_EN_KILLFOCUS(IDC_EDIT156, OnExitMat156)
	ON_EN_KILLFOCUS(IDC_EDIT157, OnExitMat157)
	ON_EN_KILLFOCUS(IDC_EDIT411, OnExitMat411)
	ON_EN_KILLFOCUS(IDC_EDIT158, OnExitMat158)
	ON_EN_KILLFOCUS(IDC_EDIT159, OnExitMat159)
	ON_EN_KILLFOCUS(IDC_EDIT113, OnExitMat113)
	ON_EN_KILLFOCUS(IDC_EDIT160, OnExitMat160)
	ON_EN_KILLFOCUS(IDC_EDIT161, OnExitMat161)
	ON_EN_KILLFOCUS(IDC_EDIT162, OnExitMat162)
	ON_EN_KILLFOCUS(IDC_EDIT163, OnExitMat163)
	ON_EN_KILLFOCUS(IDC_EDIT164, OnExitMat164)
	ON_EN_KILLFOCUS(IDC_EDIT165, OnExitMat165)
	ON_EN_KILLFOCUS(IDC_EDIT511, OnExitMat511)
	ON_EN_KILLFOCUS(IDC_EDIT166, OnExitMat166)
	ON_EN_KILLFOCUS(IDC_EDIT167, OnExitMat167)
	ON_EN_KILLFOCUS(IDC_EDIT168, OnExitMat168)
	ON_EN_KILLFOCUS(IDC_EDIT169, OnExitMat169)
	ON_EN_KILLFOCUS(IDC_EDIT170, OnExitMat170)
	ON_EN_KILLFOCUS(IDC_EDIT171, OnExitMat171)
	ON_EN_KILLFOCUS(IDC_EDIT172, OnExitMat172)
	ON_EN_KILLFOCUS(IDC_EDIT173, OnExitMat173)
	ON_EN_KILLFOCUS(IDC_EDIT174, OnExitMat174)
	ON_EN_KILLFOCUS(IDC_EDIT611, OnExitMat611)
	ON_EN_KILLFOCUS(IDC_EDIT175, OnExitMat175)
	ON_EN_KILLFOCUS(IDC_EDIT176, OnExitMat176)
	ON_EN_KILLFOCUS(IDC_EDIT177, OnExitMat177)
	ON_EN_KILLFOCUS(IDC_EDIT178, OnExitMat178)
	ON_EN_KILLFOCUS(IDC_EDIT179, OnExitMat179)
	ON_EN_KILLFOCUS(IDC_EDIT180, OnExitMat180)
	ON_EN_KILLFOCUS(IDC_EDIT181, OnExitMat181)
	ON_EN_KILLFOCUS(IDC_EDIT182, OnExitMat182)
	ON_EN_KILLFOCUS(IDC_EDIT183, OnExitMat183)
	ON_EN_KILLFOCUS(IDC_EDIT711, OnExitMat711)
	ON_EN_KILLFOCUS(IDC_EDIT184, OnExitMat184)
	ON_EN_KILLFOCUS(IDC_EDIT185, OnExitMat185)
	ON_EN_KILLFOCUS(IDC_EDIT186, OnExitMat186)
	ON_EN_KILLFOCUS(IDC_EDIT187, OnExitMat187)
	ON_EN_KILLFOCUS(IDC_EDIT188, OnExitMat188)
	ON_EN_KILLFOCUS(IDC_EDIT189, OnExitMat189)
	ON_EN_KILLFOCUS(IDC_EDIT190, OnExitMat190)
	ON_EN_KILLFOCUS(IDC_EDIT191, OnExitMat191)
	ON_EN_KILLFOCUS(IDC_EDIT192, OnExitMat192)
	ON_EN_KILLFOCUS(IDC_EDIT811, OnExitMat811)
	ON_EN_KILLFOCUS(IDC_EDIT193, OnExitMat193)
	ON_EN_KILLFOCUS(IDC_EDIT194, OnExitMat194)
	ON_EN_KILLFOCUS(IDC_EDIT195, OnExitMat195)
	ON_EN_KILLFOCUS(IDC_EDIT196, OnExitMat196)
	ON_EN_KILLFOCUS(IDC_EDIT197, OnExitMat197)
	ON_EN_KILLFOCUS(IDC_EDIT198, OnExitMat198)
	ON_EN_KILLFOCUS(IDC_EDIT199, OnExitMat199)
	ON_EN_KILLFOCUS(IDC_EDIT200, OnExitMat200)
	ON_EN_KILLFOCUS(IDC_EDIT201, OnExitMat201)
	ON_EN_KILLFOCUS(IDC_EDIT911, OnExitMat911)
	ON_EN_KILLFOCUS(IDC_EDIT202, OnExitMat202)
	ON_EN_KILLFOCUS(IDC_EDIT203, OnExitMat203)
	ON_EN_KILLFOCUS(IDC_EDIT204, OnExitMat204)
	ON_EN_KILLFOCUS(IDC_EDIT205, OnExitMat205)
	ON_EN_KILLFOCUS(IDC_EDIT206, OnExitMat206)
	ON_EN_KILLFOCUS(IDC_EDIT207, OnExitMat207)
	ON_EN_KILLFOCUS(IDC_EDIT208, OnExitMat208)
	ON_EN_KILLFOCUS(IDC_EDIT209, OnExitMat209)
	ON_EN_KILLFOCUS(IDC_EDIT212, OnExitMat212)
	ON_EN_KILLFOCUS(IDC_EDIT1011, OnExitMat1011)

	ON_BN_CLICKED(IDC_RADIO1, OnDimension1)
	ON_BN_CLICKED(IDC_RADIO2, OnDimension2)
	ON_BN_CLICKED(IDC_RADIO3, OnDimension3)
	ON_BN_CLICKED(IDC_RADIO4, OnDimension4)
	ON_BN_CLICKED(IDC_RADIO5, OnDimension5)
	ON_BN_CLICKED(IDC_RADIO6, OnDimension6)
	ON_BN_CLICKED(IDC_RADIO7, OnDimension7)
	ON_BN_CLICKED(IDC_RADIO8, OnDimension8)
	ON_BN_CLICKED(IDC_RADIO9, OnDimension9)
	ON_BN_CLICKED(IDC_RADIO10, OnDimension10)

	ON_BN_CLICKED(IDC_RADIO21, OnEnableAlphCode)
	ON_BN_CLICKED(IDC_RADIO22, OnDisableAlphCode)
	ON_BN_CLICKED(IDC_RADIO23, OnRowVectorMatrix)
	ON_BN_CLICKED(IDC_RADIO24, OnMatrixColumnVector)

	ON_BN_CLICKED(IDC_BUTTON3, OnZufaelligerSchluessel)
	ON_BN_CLICKED(IDC_BUTTON_RESETKEY, OnResetKey)
	ON_BN_CLICKED(IDC_BUTTON4, OnKleinereSchluessel)
	ON_BN_CLICKED(IDC_BUTTON5, OnDecrypt)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)

	ON_BN_CLICKED(IDC_BUTTON_TEXTOPTIONS, OnTextOptions)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON69, OnHillOptions)
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyHill10x10 

void CDlgKeyHill10x10::OnUpdateMat11()    { m_HillBase->syncAlphNum(0,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat12()    { m_HillBase->syncAlphNum(0,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat13()    { m_HillBase->syncAlphNum(0,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat14()    { m_HillBase->syncAlphNum(0,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat15()    { m_HillBase->syncAlphNum(0,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat16()    { m_HillBase->syncAlphNum(0,5); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat17()    { m_HillBase->syncAlphNum(0,6); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat18()    { m_HillBase->syncAlphNum(0,7); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat19()    { m_HillBase->syncAlphNum(0,8); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat110()   { m_HillBase->syncAlphNum(0,9); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat21()    { m_HillBase->syncAlphNum(1,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat22()    { m_HillBase->syncAlphNum(1,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat23()    { m_HillBase->syncAlphNum(1,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat24()    { m_HillBase->syncAlphNum(1,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat25()    { m_HillBase->syncAlphNum(1,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat26()    { m_HillBase->syncAlphNum(1,5); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat27()    { m_HillBase->syncAlphNum(1,6); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat28()    { m_HillBase->syncAlphNum(1,7); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat29()    { m_HillBase->syncAlphNum(1,8); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat210()   { m_HillBase->syncAlphNum(1,9); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat31()    { m_HillBase->syncAlphNum(2,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat32()    { m_HillBase->syncAlphNum(2,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat33()    { m_HillBase->syncAlphNum(2,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat34()    { m_HillBase->syncAlphNum(2,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat35()    { m_HillBase->syncAlphNum(2,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat36()    { m_HillBase->syncAlphNum(2,5); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat37()    { m_HillBase->syncAlphNum(2,6); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat38()    { m_HillBase->syncAlphNum(2,7); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat39()    { m_HillBase->syncAlphNum(2,8); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat310()   { m_HillBase->syncAlphNum(2,9); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat41()    { m_HillBase->syncAlphNum(3,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat42()    { m_HillBase->syncAlphNum(3,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat43()    { m_HillBase->syncAlphNum(3,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat44()    { m_HillBase->syncAlphNum(3,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat45()    { m_HillBase->syncAlphNum(3,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat46()    { m_HillBase->syncAlphNum(3,5); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat47()    { m_HillBase->syncAlphNum(3,6); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat48()    { m_HillBase->syncAlphNum(3,7); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat49()    { m_HillBase->syncAlphNum(3,8); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat410()   { m_HillBase->syncAlphNum(3,9); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat51()    { m_HillBase->syncAlphNum(4,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat52()    { m_HillBase->syncAlphNum(4,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat53()    { m_HillBase->syncAlphNum(4,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat54()    { m_HillBase->syncAlphNum(4,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat55()    { m_HillBase->syncAlphNum(4,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat56()    { m_HillBase->syncAlphNum(4,5); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat57()    { m_HillBase->syncAlphNum(4,6); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat58()    { m_HillBase->syncAlphNum(4,7); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat59()    { m_HillBase->syncAlphNum(4,8); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat510()   { m_HillBase->syncAlphNum(4,9); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat61()    { m_HillBase->syncAlphNum(5,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat62()    { m_HillBase->syncAlphNum(5,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat63()    { m_HillBase->syncAlphNum(5,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat64()    { m_HillBase->syncAlphNum(5,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat65()    { m_HillBase->syncAlphNum(5,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat66()    { m_HillBase->syncAlphNum(5,5); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat67()    { m_HillBase->syncAlphNum(5,6); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat68()    { m_HillBase->syncAlphNum(5,7); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat69()    { m_HillBase->syncAlphNum(5,8); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat610()   { m_HillBase->syncAlphNum(5,9); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat71()    { m_HillBase->syncAlphNum(6,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat72()    { m_HillBase->syncAlphNum(6,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat73()    { m_HillBase->syncAlphNum(6,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat74()    { m_HillBase->syncAlphNum(6,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat75()    { m_HillBase->syncAlphNum(6,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat76()    { m_HillBase->syncAlphNum(6,5); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat77()    { m_HillBase->syncAlphNum(6,6); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat78()    { m_HillBase->syncAlphNum(6,7); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat79()    { m_HillBase->syncAlphNum(6,8); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat710()   { m_HillBase->syncAlphNum(6,9); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat81()    { m_HillBase->syncAlphNum(7,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat82()    { m_HillBase->syncAlphNum(7,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat83()    { m_HillBase->syncAlphNum(7,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat84()    { m_HillBase->syncAlphNum(7,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat85()    { m_HillBase->syncAlphNum(7,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat86()    { m_HillBase->syncAlphNum(7,5); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat87()    { m_HillBase->syncAlphNum(7,6); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat88()    { m_HillBase->syncAlphNum(7,7); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat89()    { m_HillBase->syncAlphNum(7,8); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat810()   { m_HillBase->syncAlphNum(7,9); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat91()    { m_HillBase->syncAlphNum(8,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat92()    { m_HillBase->syncAlphNum(8,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat93()    { m_HillBase->syncAlphNum(8,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat94()    { m_HillBase->syncAlphNum(8,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat95()    { m_HillBase->syncAlphNum(8,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat96()    { m_HillBase->syncAlphNum(8,5); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat97()    { m_HillBase->syncAlphNum(8,6); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat98()    { m_HillBase->syncAlphNum(8,7); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat99()    { m_HillBase->syncAlphNum(8,8); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat910()   { m_HillBase->syncAlphNum(8,9); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat101()   { m_HillBase->syncAlphNum(9,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat102()   { m_HillBase->syncAlphNum(9,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat103()   { m_HillBase->syncAlphNum(9,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat104()   { m_HillBase->syncAlphNum(9,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat105()   { m_HillBase->syncAlphNum(9,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat106()   { m_HillBase->syncAlphNum(9,5); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat107()   { m_HillBase->syncAlphNum(9,6); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat108()   { m_HillBase->syncAlphNum(9,7); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat109()   { m_HillBase->syncAlphNum(9,8); checkForInvalidCharacterInput(); }
void CDlgKeyHill10x10::OnUpdateMat1010()  { m_HillBase->syncAlphNum(9,9); checkForInvalidCharacterInput(); }


////////////////////////////////
void CDlgKeyHill10x10::OnUpdateMat40()  { m_HillBase->syncNumAlph(0,0); }
void CDlgKeyHill10x10::OnUpdateMat50()  { m_HillBase->syncNumAlph(0,1); }
void CDlgKeyHill10x10::OnUpdateMat20()  { m_HillBase->syncNumAlph(0,2); }
void CDlgKeyHill10x10::OnUpdateMat90()  { m_HillBase->syncNumAlph(0,3); }
void CDlgKeyHill10x10::OnUpdateMat100() { m_HillBase->syncNumAlph(0,4); }
void CDlgKeyHill10x10::OnUpdateMat117() { m_HillBase->syncNumAlph(0,5); }
void CDlgKeyHill10x10::OnUpdateMat118() { m_HillBase->syncNumAlph(0,6); }
void CDlgKeyHill10x10::OnUpdateMat119() { m_HillBase->syncNumAlph(0,7); }
void CDlgKeyHill10x10::OnUpdateMat60()  { m_HillBase->syncNumAlph(0,8); }
void CDlgKeyHill10x10::OnUpdateMat125() { m_HillBase->syncNumAlph(0,9); }
void CDlgKeyHill10x10::OnUpdateMat127() { m_HillBase->syncNumAlph(1,0); }
void CDlgKeyHill10x10::OnUpdateMat134() { m_HillBase->syncNumAlph(1,1); }
void CDlgKeyHill10x10::OnUpdateMat135() { m_HillBase->syncNumAlph(1,2); }
void CDlgKeyHill10x10::OnUpdateMat136() { m_HillBase->syncNumAlph(1,3); }
void CDlgKeyHill10x10::OnUpdateMat70()  { m_HillBase->syncNumAlph(1,4); }
void CDlgKeyHill10x10::OnUpdateMat137() { m_HillBase->syncNumAlph(1,5); }
void CDlgKeyHill10x10::OnUpdateMat138() { m_HillBase->syncNumAlph(1,6); }
void CDlgKeyHill10x10::OnUpdateMat139() { m_HillBase->syncNumAlph(1,7); }
void CDlgKeyHill10x10::OnUpdateMat80()  { m_HillBase->syncNumAlph(1,8); }
void CDlgKeyHill10x10::OnUpdateMat211() { m_HillBase->syncNumAlph(1,9); }
void CDlgKeyHill10x10::OnUpdateMat140() { m_HillBase->syncNumAlph(2,0); }
void CDlgKeyHill10x10::OnUpdateMat141() { m_HillBase->syncNumAlph(2,1); }
void CDlgKeyHill10x10::OnUpdateMat142() { m_HillBase->syncNumAlph(2,2); }
void CDlgKeyHill10x10::OnUpdateMat143() { m_HillBase->syncNumAlph(2,3); }
void CDlgKeyHill10x10::OnUpdateMat144() { m_HillBase->syncNumAlph(2,4); }
void CDlgKeyHill10x10::OnUpdateMat145() { m_HillBase->syncNumAlph(2,5); }
void CDlgKeyHill10x10::OnUpdateMat146() { m_HillBase->syncNumAlph(2,6); }
void CDlgKeyHill10x10::OnUpdateMat147() { m_HillBase->syncNumAlph(2,7); }
void CDlgKeyHill10x10::OnUpdateMat148() { m_HillBase->syncNumAlph(2,8); }
void CDlgKeyHill10x10::OnUpdateMat311() { m_HillBase->syncNumAlph(2,9); }
void CDlgKeyHill10x10::OnUpdateMat149() { m_HillBase->syncNumAlph(3,0); }
void CDlgKeyHill10x10::OnUpdateMat150() { m_HillBase->syncNumAlph(3,1); }
void CDlgKeyHill10x10::OnUpdateMat151() { m_HillBase->syncNumAlph(3,2); }
void CDlgKeyHill10x10::OnUpdateMat152() { m_HillBase->syncNumAlph(3,3); }
void CDlgKeyHill10x10::OnUpdateMat153() { m_HillBase->syncNumAlph(3,4); }
void CDlgKeyHill10x10::OnUpdateMat154() { m_HillBase->syncNumAlph(3,5); }
void CDlgKeyHill10x10::OnUpdateMat155() { m_HillBase->syncNumAlph(3,6); }
void CDlgKeyHill10x10::OnUpdateMat156() { m_HillBase->syncNumAlph(3,7); }
void CDlgKeyHill10x10::OnUpdateMat157() { m_HillBase->syncNumAlph(3,8); }
void CDlgKeyHill10x10::OnUpdateMat411() { m_HillBase->syncNumAlph(3,9); }
void CDlgKeyHill10x10::OnUpdateMat158() { m_HillBase->syncNumAlph(4,0); }
void CDlgKeyHill10x10::OnUpdateMat159() { m_HillBase->syncNumAlph(4,1); }
void CDlgKeyHill10x10::OnUpdateMat113() { m_HillBase->syncNumAlph(4,2); }
void CDlgKeyHill10x10::OnUpdateMat160() { m_HillBase->syncNumAlph(4,3); }
void CDlgKeyHill10x10::OnUpdateMat161() { m_HillBase->syncNumAlph(4,4); }
void CDlgKeyHill10x10::OnUpdateMat162() { m_HillBase->syncNumAlph(4,5); }
void CDlgKeyHill10x10::OnUpdateMat163() { m_HillBase->syncNumAlph(4,6); }
void CDlgKeyHill10x10::OnUpdateMat164() { m_HillBase->syncNumAlph(4,7); }
void CDlgKeyHill10x10::OnUpdateMat165() { m_HillBase->syncNumAlph(4,8); }
void CDlgKeyHill10x10::OnUpdateMat511() { m_HillBase->syncNumAlph(4,9); }
void CDlgKeyHill10x10::OnUpdateMat166() { m_HillBase->syncNumAlph(5,0); }
void CDlgKeyHill10x10::OnUpdateMat167() { m_HillBase->syncNumAlph(5,1); }
void CDlgKeyHill10x10::OnUpdateMat168() { m_HillBase->syncNumAlph(5,2); }
void CDlgKeyHill10x10::OnUpdateMat169() { m_HillBase->syncNumAlph(5,3); }
void CDlgKeyHill10x10::OnUpdateMat170() { m_HillBase->syncNumAlph(5,4); }
void CDlgKeyHill10x10::OnUpdateMat171() { m_HillBase->syncNumAlph(5,5); }
void CDlgKeyHill10x10::OnUpdateMat172() { m_HillBase->syncNumAlph(5,6); }
void CDlgKeyHill10x10::OnUpdateMat173() { m_HillBase->syncNumAlph(5,7); }
void CDlgKeyHill10x10::OnUpdateMat174() { m_HillBase->syncNumAlph(5,8); }
void CDlgKeyHill10x10::OnUpdateMat611() { m_HillBase->syncNumAlph(5,9); }
void CDlgKeyHill10x10::OnUpdateMat175() { m_HillBase->syncNumAlph(6,0); }
void CDlgKeyHill10x10::OnUpdateMat176() { m_HillBase->syncNumAlph(6,1); }
void CDlgKeyHill10x10::OnUpdateMat177() { m_HillBase->syncNumAlph(6,2); }
void CDlgKeyHill10x10::OnUpdateMat178() { m_HillBase->syncNumAlph(6,3); }
void CDlgKeyHill10x10::OnUpdateMat179() { m_HillBase->syncNumAlph(6,4); }
void CDlgKeyHill10x10::OnUpdateMat180() { m_HillBase->syncNumAlph(6,5); }
void CDlgKeyHill10x10::OnUpdateMat181() { m_HillBase->syncNumAlph(6,6); }
void CDlgKeyHill10x10::OnUpdateMat182() { m_HillBase->syncNumAlph(6,7); }
void CDlgKeyHill10x10::OnUpdateMat183() { m_HillBase->syncNumAlph(6,8); }
void CDlgKeyHill10x10::OnUpdateMat711() { m_HillBase->syncNumAlph(6,9); }
void CDlgKeyHill10x10::OnUpdateMat184() { m_HillBase->syncNumAlph(6,0); }
void CDlgKeyHill10x10::OnUpdateMat185() { m_HillBase->syncNumAlph(7,1); }
void CDlgKeyHill10x10::OnUpdateMat186() { m_HillBase->syncNumAlph(7,2); }
void CDlgKeyHill10x10::OnUpdateMat187() { m_HillBase->syncNumAlph(7,3); }
void CDlgKeyHill10x10::OnUpdateMat188() { m_HillBase->syncNumAlph(7,4); }
void CDlgKeyHill10x10::OnUpdateMat189() { m_HillBase->syncNumAlph(7,5); }
void CDlgKeyHill10x10::OnUpdateMat190() { m_HillBase->syncNumAlph(7,6); }
void CDlgKeyHill10x10::OnUpdateMat191() { m_HillBase->syncNumAlph(7,7); }
void CDlgKeyHill10x10::OnUpdateMat192() { m_HillBase->syncNumAlph(7,8); }
void CDlgKeyHill10x10::OnUpdateMat811() { m_HillBase->syncNumAlph(7,9); }
void CDlgKeyHill10x10::OnUpdateMat193() { m_HillBase->syncNumAlph(8,0); }
void CDlgKeyHill10x10::OnUpdateMat194() { m_HillBase->syncNumAlph(8,1); }
void CDlgKeyHill10x10::OnUpdateMat195() { m_HillBase->syncNumAlph(8,2); }
void CDlgKeyHill10x10::OnUpdateMat196() { m_HillBase->syncNumAlph(8,3); }
void CDlgKeyHill10x10::OnUpdateMat197() { m_HillBase->syncNumAlph(8,4); }
void CDlgKeyHill10x10::OnUpdateMat198() { m_HillBase->syncNumAlph(8,5); }
void CDlgKeyHill10x10::OnUpdateMat199() { m_HillBase->syncNumAlph(8,6); }
void CDlgKeyHill10x10::OnUpdateMat200() { m_HillBase->syncNumAlph(8,7); }
void CDlgKeyHill10x10::OnUpdateMat201() { m_HillBase->syncNumAlph(8,8); }
void CDlgKeyHill10x10::OnUpdateMat911() { m_HillBase->syncNumAlph(8,9); }
void CDlgKeyHill10x10::OnUpdateMat202() { m_HillBase->syncNumAlph(9,0); }
void CDlgKeyHill10x10::OnUpdateMat203() { m_HillBase->syncNumAlph(9,1); }
void CDlgKeyHill10x10::OnUpdateMat204() { m_HillBase->syncNumAlph(9,2); }
void CDlgKeyHill10x10::OnUpdateMat205() { m_HillBase->syncNumAlph(9,3); }
void CDlgKeyHill10x10::OnUpdateMat206() { m_HillBase->syncNumAlph(9,4); }
void CDlgKeyHill10x10::OnUpdateMat207() { m_HillBase->syncNumAlph(9,5); }
void CDlgKeyHill10x10::OnUpdateMat208() { m_HillBase->syncNumAlph(9,6); }
void CDlgKeyHill10x10::OnUpdateMat209() { m_HillBase->syncNumAlph(9,7); }
void CDlgKeyHill10x10::OnUpdateMat212() { m_HillBase->syncNumAlph(9,8); }
void CDlgKeyHill10x10::OnUpdateMat1011(){ m_HillBase->syncNumAlph(9,9); }

void CDlgKeyHill10x10::OnExitMat40()  { m_HillBase->formatNum(0,0); }
void CDlgKeyHill10x10::OnExitMat50()  { m_HillBase->formatNum(0,1); }
void CDlgKeyHill10x10::OnExitMat20()  { m_HillBase->formatNum(0,2); }
void CDlgKeyHill10x10::OnExitMat90()  { m_HillBase->formatNum(0,3); }
void CDlgKeyHill10x10::OnExitMat100() { m_HillBase->formatNum(0,4); }
void CDlgKeyHill10x10::OnExitMat117() { m_HillBase->formatNum(0,5); }
void CDlgKeyHill10x10::OnExitMat118() { m_HillBase->formatNum(0,6); }
void CDlgKeyHill10x10::OnExitMat119() { m_HillBase->formatNum(0,7); }
void CDlgKeyHill10x10::OnExitMat60()  { m_HillBase->formatNum(0,8); }
void CDlgKeyHill10x10::OnExitMat125() { m_HillBase->formatNum(0,9); }
void CDlgKeyHill10x10::OnExitMat127() { m_HillBase->formatNum(1,0); }
void CDlgKeyHill10x10::OnExitMat134() { m_HillBase->formatNum(1,1); }
void CDlgKeyHill10x10::OnExitMat135() { m_HillBase->formatNum(1,2); }
void CDlgKeyHill10x10::OnExitMat136() { m_HillBase->formatNum(1,3); }
void CDlgKeyHill10x10::OnExitMat70()  { m_HillBase->formatNum(1,4); }
void CDlgKeyHill10x10::OnExitMat137() { m_HillBase->formatNum(1,5); }
void CDlgKeyHill10x10::OnExitMat138() { m_HillBase->formatNum(1,6); }
void CDlgKeyHill10x10::OnExitMat139() { m_HillBase->formatNum(1,7); }
void CDlgKeyHill10x10::OnExitMat80()  { m_HillBase->formatNum(1,8); }
void CDlgKeyHill10x10::OnExitMat211() { m_HillBase->formatNum(1,9); }
void CDlgKeyHill10x10::OnExitMat140() { m_HillBase->formatNum(2,0); }
void CDlgKeyHill10x10::OnExitMat141() { m_HillBase->formatNum(2,1); }
void CDlgKeyHill10x10::OnExitMat142() { m_HillBase->formatNum(2,2); }
void CDlgKeyHill10x10::OnExitMat143() { m_HillBase->formatNum(2,3); }
void CDlgKeyHill10x10::OnExitMat144() { m_HillBase->formatNum(2,4); }
void CDlgKeyHill10x10::OnExitMat145() { m_HillBase->formatNum(2,5); }
void CDlgKeyHill10x10::OnExitMat146() { m_HillBase->formatNum(2,6); }
void CDlgKeyHill10x10::OnExitMat147() { m_HillBase->formatNum(2,7); }
void CDlgKeyHill10x10::OnExitMat148() { m_HillBase->formatNum(2,8); }
void CDlgKeyHill10x10::OnExitMat311() { m_HillBase->formatNum(2,9); }
void CDlgKeyHill10x10::OnExitMat149() { m_HillBase->formatNum(3,0); }
void CDlgKeyHill10x10::OnExitMat150() { m_HillBase->formatNum(3,1); }
void CDlgKeyHill10x10::OnExitMat151() { m_HillBase->formatNum(3,2); }
void CDlgKeyHill10x10::OnExitMat152() { m_HillBase->formatNum(3,3); }
void CDlgKeyHill10x10::OnExitMat153() { m_HillBase->formatNum(3,4); }
void CDlgKeyHill10x10::OnExitMat154() { m_HillBase->formatNum(3,5); }
void CDlgKeyHill10x10::OnExitMat155() { m_HillBase->formatNum(3,6); }
void CDlgKeyHill10x10::OnExitMat156() { m_HillBase->formatNum(3,7); }
void CDlgKeyHill10x10::OnExitMat157() { m_HillBase->formatNum(3,8); }
void CDlgKeyHill10x10::OnExitMat411() { m_HillBase->formatNum(3,9); }
void CDlgKeyHill10x10::OnExitMat158() { m_HillBase->formatNum(4,0); }
void CDlgKeyHill10x10::OnExitMat159() { m_HillBase->formatNum(4,1); }
void CDlgKeyHill10x10::OnExitMat113() { m_HillBase->formatNum(4,2); }
void CDlgKeyHill10x10::OnExitMat160() { m_HillBase->formatNum(4,3); }
void CDlgKeyHill10x10::OnExitMat161() { m_HillBase->formatNum(4,4); }
void CDlgKeyHill10x10::OnExitMat162() { m_HillBase->formatNum(4,5); }
void CDlgKeyHill10x10::OnExitMat163() { m_HillBase->formatNum(4,6); }
void CDlgKeyHill10x10::OnExitMat164() { m_HillBase->formatNum(4,7); }
void CDlgKeyHill10x10::OnExitMat165() { m_HillBase->formatNum(4,8); }
void CDlgKeyHill10x10::OnExitMat511() { m_HillBase->formatNum(4,9); }
void CDlgKeyHill10x10::OnExitMat166() { m_HillBase->formatNum(5,0); }
void CDlgKeyHill10x10::OnExitMat167() { m_HillBase->formatNum(5,1); }
void CDlgKeyHill10x10::OnExitMat168() { m_HillBase->formatNum(5,2); }
void CDlgKeyHill10x10::OnExitMat169() { m_HillBase->formatNum(5,3); }
void CDlgKeyHill10x10::OnExitMat170() { m_HillBase->formatNum(5,4); }
void CDlgKeyHill10x10::OnExitMat171() { m_HillBase->formatNum(5,5); }
void CDlgKeyHill10x10::OnExitMat172() { m_HillBase->formatNum(5,6); }
void CDlgKeyHill10x10::OnExitMat173() { m_HillBase->formatNum(5,7); }
void CDlgKeyHill10x10::OnExitMat174() { m_HillBase->formatNum(5,8); }
void CDlgKeyHill10x10::OnExitMat611() { m_HillBase->formatNum(5,9); }
void CDlgKeyHill10x10::OnExitMat175() { m_HillBase->formatNum(6,0); }
void CDlgKeyHill10x10::OnExitMat176() { m_HillBase->formatNum(6,1); }
void CDlgKeyHill10x10::OnExitMat177() { m_HillBase->formatNum(6,2); }
void CDlgKeyHill10x10::OnExitMat178() { m_HillBase->formatNum(6,3); }
void CDlgKeyHill10x10::OnExitMat179() { m_HillBase->formatNum(6,4); }
void CDlgKeyHill10x10::OnExitMat180() { m_HillBase->formatNum(6,5); }
void CDlgKeyHill10x10::OnExitMat181() { m_HillBase->formatNum(6,6); }
void CDlgKeyHill10x10::OnExitMat182() { m_HillBase->formatNum(6,7); }
void CDlgKeyHill10x10::OnExitMat183() { m_HillBase->formatNum(6,8); }
void CDlgKeyHill10x10::OnExitMat711() { m_HillBase->formatNum(6,9); }
void CDlgKeyHill10x10::OnExitMat184() { m_HillBase->formatNum(6,0); }
void CDlgKeyHill10x10::OnExitMat185() { m_HillBase->formatNum(7,1); }
void CDlgKeyHill10x10::OnExitMat186() { m_HillBase->formatNum(7,2); }
void CDlgKeyHill10x10::OnExitMat187() { m_HillBase->formatNum(7,3); }
void CDlgKeyHill10x10::OnExitMat188() { m_HillBase->formatNum(7,4); }
void CDlgKeyHill10x10::OnExitMat189() { m_HillBase->formatNum(7,5); }
void CDlgKeyHill10x10::OnExitMat190() { m_HillBase->formatNum(7,6); }
void CDlgKeyHill10x10::OnExitMat191() { m_HillBase->formatNum(7,7); }
void CDlgKeyHill10x10::OnExitMat192() { m_HillBase->formatNum(7,8); }
void CDlgKeyHill10x10::OnExitMat811() { m_HillBase->formatNum(7,9); }
void CDlgKeyHill10x10::OnExitMat193() { m_HillBase->formatNum(8,0); }
void CDlgKeyHill10x10::OnExitMat194() { m_HillBase->formatNum(8,1); }
void CDlgKeyHill10x10::OnExitMat195() { m_HillBase->formatNum(8,2); }
void CDlgKeyHill10x10::OnExitMat196() { m_HillBase->formatNum(8,3); }
void CDlgKeyHill10x10::OnExitMat197() { m_HillBase->formatNum(8,4); }
void CDlgKeyHill10x10::OnExitMat198() { m_HillBase->formatNum(8,5); }
void CDlgKeyHill10x10::OnExitMat199() { m_HillBase->formatNum(8,6); }
void CDlgKeyHill10x10::OnExitMat200() { m_HillBase->formatNum(8,7); }
void CDlgKeyHill10x10::OnExitMat201() { m_HillBase->formatNum(8,8); }
void CDlgKeyHill10x10::OnExitMat911() { m_HillBase->formatNum(8,9); }
void CDlgKeyHill10x10::OnExitMat202() { m_HillBase->formatNum(9,0); }
void CDlgKeyHill10x10::OnExitMat203() { m_HillBase->formatNum(9,1); }
void CDlgKeyHill10x10::OnExitMat204() { m_HillBase->formatNum(9,2); }
void CDlgKeyHill10x10::OnExitMat205() { m_HillBase->formatNum(9,3); }
void CDlgKeyHill10x10::OnExitMat206() { m_HillBase->formatNum(9,4); }
void CDlgKeyHill10x10::OnExitMat207() { m_HillBase->formatNum(9,5); }
void CDlgKeyHill10x10::OnExitMat208() { m_HillBase->formatNum(9,6); }
void CDlgKeyHill10x10::OnExitMat209() { m_HillBase->formatNum(9,7); }
void CDlgKeyHill10x10::OnExitMat212() { m_HillBase->formatNum(9,8); }
void CDlgKeyHill10x10::OnExitMat1011(){ m_HillBase->formatNum(9,9); }

// HILL parameter
void CDlgKeyHill10x10::SetDimension( unsigned long d )
{
	const unsigned long HillDimID[] = 
   { 0, IDC_RADIO1, IDC_RADIO2, IDC_RADIO3, IDC_RADIO4, IDC_RADIO5,
        IDC_RADIO6, IDC_RADIO7, IDC_RADIO8, IDC_RADIO9, IDC_RADIO10 };
	m_HillBase->selectHillDimension( d ); radioSetHillDim(HillDimID[d]);
}
void CDlgKeyHill10x10::OnDimension1()  { SetDimension(1); }
void CDlgKeyHill10x10::OnDimension2()  { SetDimension(2); }
void CDlgKeyHill10x10::OnDimension3()  { SetDimension(3); }
void CDlgKeyHill10x10::OnDimension4()  { SetDimension(4); }
void CDlgKeyHill10x10::OnDimension5()  { SetDimension(5); }
void CDlgKeyHill10x10::OnDimension6()  { SetDimension(6); }
void CDlgKeyHill10x10::OnDimension7()  { SetDimension(7); }
void CDlgKeyHill10x10::OnDimension8()  { SetDimension(8); }
void CDlgKeyHill10x10::OnDimension9()  { SetDimension(9); }
void CDlgKeyHill10x10::OnDimension10() { SetDimension(10); }

void CDlgKeyHill10x10::OnEnableAlphCode()     { m_HillBase->selectMatType ( HILL_CHAR_MATRIX ); }
void CDlgKeyHill10x10::OnDisableAlphCode()    { m_HillBase->selectMatType ( HILL_NUM_MATRIX ); }
void CDlgKeyHill10x10::OnRowVectorMatrix()    { m_HillBase->selectMultType( MATRIX_VECTOR ); radioSetMultType( IDC_RADIO23 ); }
void CDlgKeyHill10x10::OnMatrixColumnVector() { m_HillBase->selectMultType( VECTOR_MATRIX ); radioSetMultType( IDC_RADIO24 ); }

// helper functions
void CDlgKeyHill10x10::radioSetMultType( unsigned long ID ) {	CheckRadioButton(IDC_RADIO23,IDC_RADIO24, ID); }
void CDlgKeyHill10x10::radioSetHillDim ( unsigned long ID ) {	CheckRadioButton(IDC_RADIO1, IDC_RADIO10, ID); }
void CDlgKeyHill10x10::radioSetMatType ( unsigned long ID ) {	CheckRadioButton(IDC_RADIO21,IDC_RADIO22, ID); }
void CDlgKeyHill10x10::displayAlphabet() 
{ 
	CString sc;
	sc.Format( IDS_HILL_CASE, theApp.TextOptions.getAlphabet().GetLength() );
	GetDlgItem(IDC_STATIC_HILL_ALPH)->SetWindowText(sc);
	m_pHillAlphInfo = theApp.TextOptions.getAlphabet();
	UpdateData( FALSE );
}

BOOL CDlgKeyHill10x10::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_HillBase->setMatFont();

   if ( m_HillBase->multType == MATRIX_VECTOR ) 
   	radioSetMultType( IDC_RADIO23 );
   else
   	radioSetMultType( IDC_RADIO24 );

   if ( m_HillBase->matType == HILL_CHAR_MATRIX )
	   radioSetMatType ( IDC_RADIO21 );
   else
	   radioSetMatType ( IDC_RADIO22 );

	displayAlphabet();
   SetDimension( m_HillBase->dim );

   if ( m_HillBase->HillMat->is_initialized() )
      m_HillBase->SetHillMatrix();

	CString cs;
	cs.LoadStringA(IDS_CRYPT_HILL);
	VERIFY(m_Paste.AutoLoad(IDC_BUTTON2,this));
	m_Paste.EnableWindow( IsKeyEmpty(cs) );

	// add tool tip to the paste button
	CString buttonPasteText;
	buttonPasteText.LoadString(IDS_STRING_PASTE_KEY_FROM_KEY_STORE);
	m_Paste.SetToolTipText(&buttonPasteText);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgKeyHill10x10::DoCrypt( unsigned long mode )
{
	UpdateData(true);
	if ( !m_HillBase->isInvertable() )
	{
		// FIXME: Set FOCUS
		return;
	}

   if ( mode == 1 ) // Decrypt
   {
      m_HillBase->invertMatrix();
   }
	m_HillBase->cryptMode = mode;
   m_HillBase->GetHillMatrix();
   m_HillBase->currDlg = 0;
	CDialog::OnOK();
}

void CDlgKeyHill10x10::OnOK()		  { DoCrypt(0); }
void CDlgKeyHill10x10::OnDecrypt() { DoCrypt(1); }
void CDlgKeyHill10x10::OnPasteKey() 
{	
	m_HillBase->pasteKey(); 
   SetDimension( m_HillBase->dim );
   UpdateData(FALSE);
}

void CDlgKeyHill10x10::OnZufaelligerSchluessel() 
{
	m_HillBase->randomKey();
   GetDlgItem(IDOK)->SetFocus();
}

void CDlgKeyHill10x10::OnResetKey()
{
	m_HillBase->Clear();
}

void CDlgKeyHill10x10::OnKleinereSchluessel() 
{
	m_HillBase->currDlg = DLG_HILL_5x5; 
   m_HillBase->max_dim = DIM_DLG_HILL_5x5;
   m_HillBase->GetHillMatrix();
   CDialog::OnOK();	
}

void CDlgKeyHill10x10::OnHillOptions()
{
   m_HillBase->SetHillOptions();
   UpdateData(FALSE);
}

void CDlgKeyHill10x10::OnTextOptions()
{
   if ( m_HillBase->SetTextOptions() )
	   displayAlphabet();
}

void CDlgKeyHill10x10::checkForInvalidCharacterInput() {
	// get the current alphabet
	CString alphabet = theApp.TextOptions.getAlphabet();
	// as soon as this variables turns true, we leave the loop below
	bool error = false;
	// go through all elements of the matrix
	for(int x=0; x<10 && !error; x++) {
		for(int y=0; y<10 && !error; y++) {
			// get the input for the current matrix cell
			CString input;
			m_HillBase->HillAlphMat[x][y].GetWindowText(input);
			// empty cells DON'T result in an error, we just skip 'em
			if(input.GetLength() > 0) {
				// discard anything but the very first character
				char character = input[0];
				// now check if the character is valid
				if(alphabet.Find(character) == -1) {
					m_HillBase->HillAlphMat[x][y].SetSel(0, -1);
					error = true;
				}
			}
		}
	}
	// dump an error message for the user
	if(error) {
		CString title;
		CString message;
		title.LoadString(IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED);
		message.Format(IDS_HILL_BAD_KEY_NONVALID_CHAR, 0, theApp.TextOptions.getAlphabet().GetLength()-1, theApp.TextOptions.getAlphabet().GetLength());
		MessageBox(message, title, MB_ICONWARNING|MB_OK);
	}
}
