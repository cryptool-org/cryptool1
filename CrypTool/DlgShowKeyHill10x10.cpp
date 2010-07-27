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
   , m_HillBase(0)
   , m_pHillAlphInfo( _T("") )
{
}

CDlgShowKeyHill10x10::~CDlgShowKeyHill10x10()
{
}

void CDlgShowKeyHill10x10::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT11,  m_HillBase->HillAlphMat[0][0]);
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

	DDX_Control(pDX, IDC_EDIT40,  m_HillBase->HillNumMat[0][0]);
	DDX_Control(pDX, IDC_EDIT50,  m_HillBase->HillNumMat[0][1]);
	DDX_Control(pDX, IDC_EDIT20,  m_HillBase->HillNumMat[0][2]);
	DDX_Control(pDX, IDC_EDIT90,  m_HillBase->HillNumMat[0][3]);
	DDX_Control(pDX, IDC_EDIT100, m_HillBase->HillNumMat[0][4]);
	DDX_Control(pDX, IDC_EDIT117, m_HillBase->HillNumMat[0][5]);
	DDX_Control(pDX, IDC_EDIT118, m_HillBase->HillNumMat[0][6]);
	DDX_Control(pDX, IDC_EDIT119, m_HillBase->HillNumMat[0][7]);
	DDX_Control(pDX, IDC_EDIT60,  m_HillBase->HillNumMat[0][8]);
	DDX_Control(pDX, IDC_EDIT125, m_HillBase->HillNumMat[0][9]);
	DDX_Control(pDX, IDC_EDIT127, m_HillBase->HillNumMat[1][0]);
	DDX_Control(pDX, IDC_EDIT213, m_HillBase->HillNumMat[1][1]);
	DDX_Control(pDX, IDC_EDIT214, m_HillBase->HillNumMat[1][2]);
	DDX_Control(pDX, IDC_EDIT215, m_HillBase->HillNumMat[1][3]);
	DDX_Control(pDX, IDC_EDIT70,  m_HillBase->HillNumMat[1][4]);
	DDX_Control(pDX, IDC_EDIT216, m_HillBase->HillNumMat[1][5]);
	DDX_Control(pDX, IDC_EDIT217, m_HillBase->HillNumMat[1][6]);
	DDX_Control(pDX, IDC_EDIT218, m_HillBase->HillNumMat[1][7]);
	DDX_Control(pDX, IDC_EDIT80,  m_HillBase->HillNumMat[1][8]);
	DDX_Control(pDX, IDC_EDIT219, m_HillBase->HillNumMat[1][9]);
	DDX_Control(pDX, IDC_EDIT220, m_HillBase->HillNumMat[2][0]);
	DDX_Control(pDX, IDC_EDIT134, m_HillBase->HillNumMat[2][1]);
	DDX_Control(pDX, IDC_EDIT135, m_HillBase->HillNumMat[2][2]);
	DDX_Control(pDX, IDC_EDIT136, m_HillBase->HillNumMat[2][3]);
	DDX_Control(pDX, IDC_EDIT137, m_HillBase->HillNumMat[2][4]);
	DDX_Control(pDX, IDC_EDIT138, m_HillBase->HillNumMat[2][5]);
	DDX_Control(pDX, IDC_EDIT139, m_HillBase->HillNumMat[2][6]);
	DDX_Control(pDX, IDC_EDIT211, m_HillBase->HillNumMat[2][7]);
	DDX_Control(pDX, IDC_EDIT140, m_HillBase->HillNumMat[2][8]);
	DDX_Control(pDX, IDC_EDIT312, m_HillBase->HillNumMat[2][9]);
	DDX_Control(pDX, IDC_EDIT142, m_HillBase->HillNumMat[3][0]);
	DDX_Control(pDX, IDC_EDIT221, m_HillBase->HillNumMat[3][1]);
	DDX_Control(pDX, IDC_EDIT222, m_HillBase->HillNumMat[3][2]);
	DDX_Control(pDX, IDC_EDIT223, m_HillBase->HillNumMat[3][3]);
	DDX_Control(pDX, IDC_EDIT144, m_HillBase->HillNumMat[3][4]);
	DDX_Control(pDX, IDC_EDIT145, m_HillBase->HillNumMat[3][5]);
	DDX_Control(pDX, IDC_EDIT146, m_HillBase->HillNumMat[3][6]);
	DDX_Control(pDX, IDC_EDIT147, m_HillBase->HillNumMat[3][7]);
	DDX_Control(pDX, IDC_EDIT148, m_HillBase->HillNumMat[3][8]);
	DDX_Control(pDX, IDC_EDIT412, m_HillBase->HillNumMat[3][9]);
	DDX_Control(pDX, IDC_EDIT149, m_HillBase->HillNumMat[4][0]);
	DDX_Control(pDX, IDC_EDIT150, m_HillBase->HillNumMat[4][1]);
	DDX_Control(pDX, IDC_EDIT113, m_HillBase->HillNumMat[4][2]);
	DDX_Control(pDX, IDC_EDIT151, m_HillBase->HillNumMat[4][3]);
	DDX_Control(pDX, IDC_EDIT152, m_HillBase->HillNumMat[4][4]);
	DDX_Control(pDX, IDC_EDIT153, m_HillBase->HillNumMat[4][5]);
	DDX_Control(pDX, IDC_EDIT154, m_HillBase->HillNumMat[4][6]);
	DDX_Control(pDX, IDC_EDIT155, m_HillBase->HillNumMat[4][7]);
	DDX_Control(pDX, IDC_EDIT156, m_HillBase->HillNumMat[4][8]);
	DDX_Control(pDX, IDC_EDIT512, m_HillBase->HillNumMat[4][9]);
	DDX_Control(pDX, IDC_EDIT224, m_HillBase->HillNumMat[5][0]);
	DDX_Control(pDX, IDC_EDIT158, m_HillBase->HillNumMat[5][1]);
	DDX_Control(pDX, IDC_EDIT159, m_HillBase->HillNumMat[5][2]);
	DDX_Control(pDX, IDC_EDIT160, m_HillBase->HillNumMat[5][3]);
	DDX_Control(pDX, IDC_EDIT161, m_HillBase->HillNumMat[5][4]);
	DDX_Control(pDX, IDC_EDIT162, m_HillBase->HillNumMat[5][5]);
	DDX_Control(pDX, IDC_EDIT163, m_HillBase->HillNumMat[5][6]);
	DDX_Control(pDX, IDC_EDIT164, m_HillBase->HillNumMat[5][7]);
	DDX_Control(pDX, IDC_EDIT174, m_HillBase->HillNumMat[5][8]);
	DDX_Control(pDX, IDC_EDIT612, m_HillBase->HillNumMat[5][9]);
	DDX_Control(pDX, IDC_EDIT225, m_HillBase->HillNumMat[6][0]);
	DDX_Control(pDX, IDC_EDIT226, m_HillBase->HillNumMat[6][1]);
	DDX_Control(pDX, IDC_EDIT166, m_HillBase->HillNumMat[6][2]);
	DDX_Control(pDX, IDC_EDIT167, m_HillBase->HillNumMat[6][3]);
	DDX_Control(pDX, IDC_EDIT168, m_HillBase->HillNumMat[6][4]);
	DDX_Control(pDX, IDC_EDIT169, m_HillBase->HillNumMat[6][5]);
	DDX_Control(pDX, IDC_EDIT170, m_HillBase->HillNumMat[6][6]);
	DDX_Control(pDX, IDC_EDIT171, m_HillBase->HillNumMat[6][7]);
	DDX_Control(pDX, IDC_EDIT172, m_HillBase->HillNumMat[6][8]);
	DDX_Control(pDX, IDC_EDIT712, m_HillBase->HillNumMat[6][9]);
	DDX_Control(pDX, IDC_EDIT227, m_HillBase->HillNumMat[7][0]);
	DDX_Control(pDX, IDC_EDIT175, m_HillBase->HillNumMat[7][1]);
	DDX_Control(pDX, IDC_EDIT176, m_HillBase->HillNumMat[7][2]);
	DDX_Control(pDX, IDC_EDIT177, m_HillBase->HillNumMat[7][3]);
	DDX_Control(pDX, IDC_EDIT178, m_HillBase->HillNumMat[7][4]);
	DDX_Control(pDX, IDC_EDIT179, m_HillBase->HillNumMat[7][5]);
	DDX_Control(pDX, IDC_EDIT180, m_HillBase->HillNumMat[7][6]);
	DDX_Control(pDX, IDC_EDIT191, m_HillBase->HillNumMat[7][7]);
	DDX_Control(pDX, IDC_EDIT181, m_HillBase->HillNumMat[7][8]);
	DDX_Control(pDX, IDC_EDIT812, m_HillBase->HillNumMat[7][9]);
	DDX_Control(pDX, IDC_EDIT183, m_HillBase->HillNumMat[8][0]);
	DDX_Control(pDX, IDC_EDIT228, m_HillBase->HillNumMat[8][1]);
	DDX_Control(pDX, IDC_EDIT184, m_HillBase->HillNumMat[8][2]);
	DDX_Control(pDX, IDC_EDIT185, m_HillBase->HillNumMat[8][3]);
	DDX_Control(pDX, IDC_EDIT186, m_HillBase->HillNumMat[8][4]);
	DDX_Control(pDX, IDC_EDIT187, m_HillBase->HillNumMat[8][5]);
	DDX_Control(pDX, IDC_EDIT188, m_HillBase->HillNumMat[8][6]);
	DDX_Control(pDX, IDC_EDIT189, m_HillBase->HillNumMat[8][7]);
	DDX_Control(pDX, IDC_EDIT190, m_HillBase->HillNumMat[8][8]);
	DDX_Control(pDX, IDC_EDIT912, m_HillBase->HillNumMat[8][9]);
	DDX_Control(pDX, IDC_EDIT229, m_HillBase->HillNumMat[9][0]);
	DDX_Control(pDX, IDC_EDIT193, m_HillBase->HillNumMat[9][1]);
	DDX_Control(pDX, IDC_EDIT194, m_HillBase->HillNumMat[9][2]);
	DDX_Control(pDX, IDC_EDIT195, m_HillBase->HillNumMat[9][3]);
	DDX_Control(pDX, IDC_EDIT196, m_HillBase->HillNumMat[9][4]);
	DDX_Control(pDX, IDC_EDIT197, m_HillBase->HillNumMat[9][5]);
	DDX_Control(pDX, IDC_EDIT198, m_HillBase->HillNumMat[9][6]);
	DDX_Control(pDX, IDC_EDIT199, m_HillBase->HillNumMat[9][7]);
	DDX_Control(pDX, IDC_EDIT200, m_HillBase->HillNumMat[9][8]);
	DDX_Control(pDX, IDC_EDIT1012,m_HillBase->HillNumMat[9][9]);

   DDX_Text( pDX, IDC_EDIT2,  m_HillBase->HillOptions.m_offset );
	DDX_Text( pDX, IDC_EDIT3, m_pHillAlphInfo );
}


BEGIN_MESSAGE_MAP(CDlgShowKeyHill10x10, CDialog)
	//{{AFX_MSG_MAP(CDlgShowKeyHill10x10)
	ON_BN_CLICKED(IDC_RADIO1,  OnKey)
	ON_BN_CLICKED(IDC_RADIO2,  OnInvKey)
	ON_BN_CLICKED(IDC_RADIO27,  OnOfs0)
	ON_BN_CLICKED(IDC_RADIO28,  OnOfs1)
	ON_BN_CLICKED(IDC_BUTTON1, OnCopyKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowKeyHill10x10 

BOOL CDlgShowKeyHill10x10::OnInitDialog() 
{
   CDialog::OnInitDialog();

   m_HillBase->setMatFont();
   m_HillBase->SetHillMatrix();
   m_HillBase->matType = HILL_NUM_MATRIX;

   if ( m_HillBase->multType == MATRIX_VECTOR ) 
      CheckRadioButton( IDC_RADIO25, IDC_RADIO26, IDC_RADIO25 );
   else
      CheckRadioButton( IDC_RADIO25, IDC_RADIO26, IDC_RADIO26 );

   if ( m_HillBase->HillOptions.m_offset )
      CheckRadioButton( IDC_RADIO27, IDC_RADIO28, IDC_RADIO28 );
   else
      CheckRadioButton( IDC_RADIO27, IDC_RADIO28, IDC_RADIO27 );

   GetDlgItem( IDC_RADIO8 )->EnableWindow( FALSE );
   GetDlgItem( IDC_RADIO9 )->EnableWindow( FALSE );

   m_ShowInvKey = FALSE;
   CheckRadioButton( IDC_RADIO1, IDC_RADIO2, IDC_RADIO1 );
   displayAlphabet();
   m_pHillAlphInfo = theApp.TextOptions.getAlphabet();
   UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgShowKeyHill10x10::init( CKeyHillBase *Hillbase )
{
   assert( Hillbase && Hillbase->key_range >= 5 );
   m_HillBase = Hillbase;
}


void CDlgShowKeyHill10x10::displayAlphabet() 
{ 
	CString sc;
	sc.Format( IDS_HILL_CASE, theApp.TextOptions.getAlphabet().GetLength() );
	GetDlgItem(IDC_STATIC_HILL_ALPH)->SetWindowText(sc);
	UpdateData( FALSE );
}


void CDlgShowKeyHill10x10::OnCopyKey() 
{
   m_HillBase->copyKey();
}

void CDlgShowKeyHill10x10::OnKey()
{
   if ( m_ShowInvKey )
   {
      if ( m_HillBase->invertMatrix() )
         m_ShowInvKey = FALSE;
      else
      {
         // FIXME 
      }
   }
}

void CDlgShowKeyHill10x10::OnInvKey()
{
   if ( !m_ShowInvKey )
   {
      if ( m_HillBase->invertMatrix() )
         m_ShowInvKey = TRUE;
      else
      {
         // FIXME 
      }
   }
}

void CDlgShowKeyHill10x10::OnOfs0()
{
   m_HillBase->HillOptions.m_offset = 0;
   m_HillBase->syncNumAlph();
   UpdateData( FALSE );
}

void CDlgShowKeyHill10x10::OnOfs1()
{
   m_HillBase->HillOptions.m_offset = 1;
   m_HillBase->syncNumAlph();
   UpdateData( FALSE );
}