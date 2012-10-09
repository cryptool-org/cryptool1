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
// HillEingabe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeyHill5x5.h"
#include "HillEncryption.h"
#include "ChrTools.h"
#include "KeyRepository.h"
#include "DlgHillOptions.h"
#include "CrypToolTools.h"
#include "assert.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHill5x5 

CDlgKeyHill5x5::CDlgKeyHill5x5(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyHill5x5::IDD, pParent)
	, m_HillBase(0) // FIXME
	, m_pHillAlphInfo(_T(""))
{
}

CDlgKeyHill5x5::~CDlgKeyHill5x5()
{
}

void CDlgKeyHill5x5::init( CKeyHillBase *Hillbase )
{
   assert( Hillbase && Hillbase->key_range >= 5 );
   m_HillBase = Hillbase;
}

void CDlgKeyHill5x5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
// HillAlphMat
	DDX_Control(pDX, IDC_EDIT11, m_HillBase->HillAlphMat[0][0] );
	DDX_Control(pDX, IDC_EDIT12, m_HillBase->HillAlphMat[0][1] );
	DDX_Control(pDX, IDC_EDIT13, m_HillBase->HillAlphMat[0][2] );
	DDX_Control(pDX, IDC_EDIT14, m_HillBase->HillAlphMat[0][3] );
	DDX_Control(pDX, IDC_EDIT15, m_HillBase->HillAlphMat[0][4] );
	DDX_Control(pDX, IDC_EDIT21, m_HillBase->HillAlphMat[1][0] );
	DDX_Control(pDX, IDC_EDIT22, m_HillBase->HillAlphMat[1][1] );
	DDX_Control(pDX, IDC_EDIT23, m_HillBase->HillAlphMat[1][2] );
	DDX_Control(pDX, IDC_EDIT24, m_HillBase->HillAlphMat[1][3] );
	DDX_Control(pDX, IDC_EDIT25, m_HillBase->HillAlphMat[1][4] );
	DDX_Control(pDX, IDC_EDIT31, m_HillBase->HillAlphMat[2][0] );
	DDX_Control(pDX, IDC_EDIT32, m_HillBase->HillAlphMat[2][1] );
	DDX_Control(pDX, IDC_EDIT33, m_HillBase->HillAlphMat[2][2] );
	DDX_Control(pDX, IDC_EDIT34, m_HillBase->HillAlphMat[2][3] );
	DDX_Control(pDX, IDC_EDIT35, m_HillBase->HillAlphMat[2][4] );
	DDX_Control(pDX, IDC_EDIT41, m_HillBase->HillAlphMat[3][0] );
	DDX_Control(pDX, IDC_EDIT42, m_HillBase->HillAlphMat[3][1] );
	DDX_Control(pDX, IDC_EDIT43, m_HillBase->HillAlphMat[3][2] );
	DDX_Control(pDX, IDC_EDIT44, m_HillBase->HillAlphMat[3][3] );
	DDX_Control(pDX, IDC_EDIT45, m_HillBase->HillAlphMat[3][4] );
	DDX_Control(pDX, IDC_EDIT51, m_HillBase->HillAlphMat[4][0] );
	DDX_Control(pDX, IDC_EDIT52, m_HillBase->HillAlphMat[4][1] );
	DDX_Control(pDX, IDC_EDIT53, m_HillBase->HillAlphMat[4][2] );
	DDX_Control(pDX, IDC_EDIT54, m_HillBase->HillAlphMat[4][3] );
	DDX_Control(pDX, IDC_EDIT55, m_HillBase->HillAlphMat[4][4] );

// HillNumMat
	DDX_Control(pDX, IDC_EDIT36,  m_HillBase->HillNumMat[0][0] );
	DDX_Control(pDX, IDC_EDIT37,  m_HillBase->HillNumMat[0][1] );
	DDX_Control(pDX, IDC_EDIT38,  m_HillBase->HillNumMat[0][2] );
	DDX_Control(pDX, IDC_EDIT40,  m_HillBase->HillNumMat[0][3] );
	DDX_Control(pDX, IDC_EDIT46,  m_HillBase->HillNumMat[0][4] );
	DDX_Control(pDX, IDC_EDIT47,  m_HillBase->HillNumMat[1][0] );
	DDX_Control(pDX, IDC_EDIT48,  m_HillBase->HillNumMat[1][1] );
	DDX_Control(pDX, IDC_EDIT49,  m_HillBase->HillNumMat[1][2] );
	DDX_Control(pDX, IDC_EDIT50,  m_HillBase->HillNumMat[1][3] );
	DDX_Control(pDX, IDC_EDIT111, m_HillBase->HillNumMat[1][4] );
	DDX_Control(pDX, IDC_EDIT57,  m_HillBase->HillNumMat[2][0] );
	DDX_Control(pDX, IDC_EDIT58,  m_HillBase->HillNumMat[2][1] );
	DDX_Control(pDX, IDC_EDIT59,  m_HillBase->HillNumMat[2][2] );
	DDX_Control(pDX, IDC_EDIT56,  m_HillBase->HillNumMat[2][3] );
	DDX_Control(pDX, IDC_EDIT115, m_HillBase->HillNumMat[2][4] );
	DDX_Control(pDX, IDC_EDIT60,  m_HillBase->HillNumMat[3][0] );
	DDX_Control(pDX, IDC_EDIT61,  m_HillBase->HillNumMat[3][1] );
	DDX_Control(pDX, IDC_EDIT62,  m_HillBase->HillNumMat[3][2] );
	DDX_Control(pDX, IDC_EDIT116, m_HillBase->HillNumMat[3][3] );
	DDX_Control(pDX, IDC_EDIT117, m_HillBase->HillNumMat[3][4] );
	DDX_Control(pDX, IDC_EDIT63,  m_HillBase->HillNumMat[4][0] );
	DDX_Control(pDX, IDC_EDIT64,  m_HillBase->HillNumMat[4][1] );
	DDX_Control(pDX, IDC_EDIT69,  m_HillBase->HillNumMat[4][2] );
	DDX_Control(pDX, IDC_EDIT65,  m_HillBase->HillNumMat[4][3] );
	DDX_Control(pDX, IDC_EDIT66,  m_HillBase->HillNumMat[4][4] );

   DDX_Check(pDX, IDC_CHECK1, m_HillBase->verbose);
	DDX_Text(pDX, IDC_EDIT3, m_pHillAlphInfo);
   DDX_Text(pDX, IDC_EDIT2, m_HillBase->HillOptions.m_offset );
   DDV_MinMaxInt(pDX, m_HillBase->HillOptions.m_offset, 0, 1);
}


BEGIN_MESSAGE_MAP(CDlgKeyHill5x5, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyHill5x5)

// HillAlphMat
	ON_EN_UPDATE(IDC_EDIT11, OnUpdateMat11)
	ON_EN_UPDATE(IDC_EDIT12, OnUpdateMat12)
	ON_EN_UPDATE(IDC_EDIT13, OnUpdateMat13)
	ON_EN_UPDATE(IDC_EDIT14, OnUpdateMat14)
	ON_EN_UPDATE(IDC_EDIT15, OnUpdateMat15)
	ON_EN_UPDATE(IDC_EDIT21, OnUpdateMat21)
	ON_EN_UPDATE(IDC_EDIT22, OnUpdateMat22)
	ON_EN_UPDATE(IDC_EDIT23, OnUpdateMat23)
	ON_EN_UPDATE(IDC_EDIT24, OnUpdateMat24)
	ON_EN_UPDATE(IDC_EDIT25, OnUpdateMat25)
	ON_EN_UPDATE(IDC_EDIT31, OnUpdateMat31)
	ON_EN_UPDATE(IDC_EDIT32, OnUpdateMat32)
	ON_EN_UPDATE(IDC_EDIT33, OnUpdateMat33)
	ON_EN_UPDATE(IDC_EDIT34, OnUpdateMat34)
	ON_EN_UPDATE(IDC_EDIT35, OnUpdateMat35)
	ON_EN_UPDATE(IDC_EDIT41, OnUpdateMat41)
	ON_EN_UPDATE(IDC_EDIT42, OnUpdateMat42)
	ON_EN_UPDATE(IDC_EDIT43, OnUpdateMat43)
	ON_EN_UPDATE(IDC_EDIT44, OnUpdateMat44)
	ON_EN_UPDATE(IDC_EDIT45, OnUpdateMat45)
	ON_EN_UPDATE(IDC_EDIT51, OnUpdateMat51)
	ON_EN_UPDATE(IDC_EDIT52, OnUpdateMat52)
	ON_EN_UPDATE(IDC_EDIT53, OnUpdateMat53)
	ON_EN_UPDATE(IDC_EDIT54, OnUpdateMat54)
	ON_EN_UPDATE(IDC_EDIT55, OnUpdateMat55)
// HillNumMat
	ON_EN_UPDATE(IDC_EDIT36, OnUpdateMat36)
	ON_EN_UPDATE(IDC_EDIT37, OnUpdateMat37)
	ON_EN_UPDATE(IDC_EDIT38, OnUpdateMat38)
	ON_EN_UPDATE(IDC_EDIT40, OnUpdateMat40)
	ON_EN_UPDATE(IDC_EDIT46, OnUpdateMat46)
	ON_EN_UPDATE(IDC_EDIT47, OnUpdateMat47)
	ON_EN_UPDATE(IDC_EDIT48, OnUpdateMat48)
	ON_EN_UPDATE(IDC_EDIT49, OnUpdateMat49)
	ON_EN_UPDATE(IDC_EDIT50, OnUpdateMat50)
	ON_EN_UPDATE(IDC_EDIT111, OnUpdateMat111)
	ON_EN_UPDATE(IDC_EDIT57, OnUpdateMat57)
	ON_EN_UPDATE(IDC_EDIT58, OnUpdateMat58)
	ON_EN_UPDATE(IDC_EDIT59, OnUpdateMat59)
	ON_EN_UPDATE(IDC_EDIT56, OnUpdateMat56)
	ON_EN_UPDATE(IDC_EDIT115, OnUpdateMat115)
	ON_EN_UPDATE(IDC_EDIT60, OnUpdateMat60)
	ON_EN_UPDATE(IDC_EDIT61, OnUpdateMat61)
	ON_EN_UPDATE(IDC_EDIT62, OnUpdateMat62)
	ON_EN_UPDATE(IDC_EDIT116, OnUpdateMat116)
	ON_EN_UPDATE(IDC_EDIT117, OnUpdateMat117)
	ON_EN_UPDATE(IDC_EDIT63, OnUpdateMat63)
	ON_EN_UPDATE(IDC_EDIT64, OnUpdateMat64)
	ON_EN_UPDATE(IDC_EDIT69, OnUpdateMat69)
	ON_EN_UPDATE(IDC_EDIT65, OnUpdateMat65)
	ON_EN_UPDATE(IDC_EDIT66, OnUpdateMat66)
	
	ON_EN_KILLFOCUS(IDC_EDIT36, OnExitMat36)
	ON_EN_KILLFOCUS(IDC_EDIT37, OnExitMat37)
	ON_EN_KILLFOCUS(IDC_EDIT38, OnExitMat38)
	ON_EN_KILLFOCUS(IDC_EDIT40, OnExitMat40)
	ON_EN_KILLFOCUS(IDC_EDIT46, OnExitMat46)
	ON_EN_KILLFOCUS(IDC_EDIT47, OnExitMat47)
	ON_EN_KILLFOCUS(IDC_EDIT48, OnExitMat48)
	ON_EN_KILLFOCUS(IDC_EDIT49, OnExitMat49)
	ON_EN_KILLFOCUS(IDC_EDIT50, OnExitMat50)
	ON_EN_KILLFOCUS(IDC_EDIT111, OnExitMat111)
	ON_EN_KILLFOCUS(IDC_EDIT57, OnExitMat57)
	ON_EN_KILLFOCUS(IDC_EDIT58, OnExitMat58)
	ON_EN_KILLFOCUS(IDC_EDIT59, OnExitMat59)
	ON_EN_KILLFOCUS(IDC_EDIT56, OnExitMat56)
	ON_EN_KILLFOCUS(IDC_EDIT115, OnExitMat115)
	ON_EN_KILLFOCUS(IDC_EDIT60, OnExitMat60)
	ON_EN_KILLFOCUS(IDC_EDIT61, OnExitMat61)
	ON_EN_KILLFOCUS(IDC_EDIT62, OnExitMat62)
	ON_EN_KILLFOCUS(IDC_EDIT116, OnExitMat116)
	ON_EN_KILLFOCUS(IDC_EDIT117, OnExitMat117)
	ON_EN_KILLFOCUS(IDC_EDIT63, OnExitMat63)
	ON_EN_KILLFOCUS(IDC_EDIT64, OnExitMat64)
	ON_EN_KILLFOCUS(IDC_EDIT69, OnExitMat69)
	ON_EN_KILLFOCUS(IDC_EDIT65, OnExitMat65)
	ON_EN_KILLFOCUS(IDC_EDIT66, OnExitMat66)

// Select Matrix Dimension
	ON_BN_CLICKED(IDC_RADIO1, OnDimension1)
	ON_BN_CLICKED(IDC_RADIO2, OnDimension2)
	ON_BN_CLICKED(IDC_RADIO3, OnDimension3)
	ON_BN_CLICKED(IDC_RADIO4, OnDimension4)
	ON_BN_CLICKED(IDC_RADIO5, OnDimension5)

	ON_BN_CLICKED(IDC_RADIO6, OnEnableAlphCode)
	ON_BN_CLICKED(IDC_RADIO7, OnDisableAlphCode)
   ON_BN_CLICKED(IDC_RADIO8, OnRowVectorMatrix)
	ON_BN_CLICKED(IDC_RADIO9, OnMatrixColumnVector)

	ON_BN_CLICKED(IDC_BUTTON3, OnZufaelligerSchluessel)
	ON_BN_CLICKED(IDC_BUTTON_RESETKEY, OnResetKey)
	ON_BN_CLICKED(IDC_BUTTON4, OnGroessereSchluessel)
	ON_BN_CLICKED(IDC_BUTTON5, OnDecrypt)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)
	ON_BN_CLICKED(IDC_BUTTON1, OnHillOptions)
	ON_BN_CLICKED(IDC_BUTTON_TEXTOPTIONS, OnTextOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyHill5x5 


// HillAlphMat
void CDlgKeyHill5x5::OnUpdateMat11() { m_HillBase->syncAlphNum(0,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat12() { m_HillBase->syncAlphNum(0,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat13() { m_HillBase->syncAlphNum(0,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat14() { m_HillBase->syncAlphNum(0,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat15() { m_HillBase->syncAlphNum(0,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat21() { m_HillBase->syncAlphNum(1,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat22() { m_HillBase->syncAlphNum(1,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat23() { m_HillBase->syncAlphNum(1,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat24() { m_HillBase->syncAlphNum(1,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat25() { m_HillBase->syncAlphNum(1,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat31() { m_HillBase->syncAlphNum(2,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat32() { m_HillBase->syncAlphNum(2,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat33() { m_HillBase->syncAlphNum(2,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat34() { m_HillBase->syncAlphNum(2,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat35() { m_HillBase->syncAlphNum(2,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat41() { m_HillBase->syncAlphNum(3,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat42() { m_HillBase->syncAlphNum(3,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat43() { m_HillBase->syncAlphNum(3,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat44() { m_HillBase->syncAlphNum(3,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat45() { m_HillBase->syncAlphNum(3,4); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat51() { m_HillBase->syncAlphNum(4,0); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat52() { m_HillBase->syncAlphNum(4,1); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat53() { m_HillBase->syncAlphNum(4,2); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat54() { m_HillBase->syncAlphNum(4,3); checkForInvalidCharacterInput(); }
void CDlgKeyHill5x5::OnUpdateMat55() { m_HillBase->syncAlphNum(4,4); checkForInvalidCharacterInput(); }

// HillNumMat
void CDlgKeyHill5x5::OnUpdateMat36()  { m_HillBase->syncNumAlph(0,0); }
void CDlgKeyHill5x5::OnUpdateMat37()  { m_HillBase->syncNumAlph(0,1); }
void CDlgKeyHill5x5::OnUpdateMat38()  { m_HillBase->syncNumAlph(0,2); }
void CDlgKeyHill5x5::OnUpdateMat40()  { m_HillBase->syncNumAlph(0,3); }
void CDlgKeyHill5x5::OnUpdateMat46()  { m_HillBase->syncNumAlph(0,4); }
void CDlgKeyHill5x5::OnUpdateMat47()  { m_HillBase->syncNumAlph(1,0); }
void CDlgKeyHill5x5::OnUpdateMat48()  { m_HillBase->syncNumAlph(1,1); }
void CDlgKeyHill5x5::OnUpdateMat49()  { m_HillBase->syncNumAlph(1,2); }
void CDlgKeyHill5x5::OnUpdateMat50()  { m_HillBase->syncNumAlph(1,3); }
void CDlgKeyHill5x5::OnUpdateMat111() { m_HillBase->syncNumAlph(1,4); }
void CDlgKeyHill5x5::OnUpdateMat57()  { m_HillBase->syncNumAlph(2,0); }
void CDlgKeyHill5x5::OnUpdateMat58()  { m_HillBase->syncNumAlph(2,1); }
void CDlgKeyHill5x5::OnUpdateMat59()  { m_HillBase->syncNumAlph(2,2); }
void CDlgKeyHill5x5::OnUpdateMat56()  { m_HillBase->syncNumAlph(2,3); }
void CDlgKeyHill5x5::OnUpdateMat115() { m_HillBase->syncNumAlph(2,4); }
void CDlgKeyHill5x5::OnUpdateMat60()  { m_HillBase->syncNumAlph(3,0); }
void CDlgKeyHill5x5::OnUpdateMat61()  { m_HillBase->syncNumAlph(3,1); }
void CDlgKeyHill5x5::OnUpdateMat62()  { m_HillBase->syncNumAlph(3,2); }
void CDlgKeyHill5x5::OnUpdateMat116() { m_HillBase->syncNumAlph(3,3); }
void CDlgKeyHill5x5::OnUpdateMat117() { m_HillBase->syncNumAlph(3,4); }
void CDlgKeyHill5x5::OnUpdateMat63()  { m_HillBase->syncNumAlph(4,0); }
void CDlgKeyHill5x5::OnUpdateMat64()  { m_HillBase->syncNumAlph(4,1); }
void CDlgKeyHill5x5::OnUpdateMat69()  { m_HillBase->syncNumAlph(4,2); }
void CDlgKeyHill5x5::OnUpdateMat65()  { m_HillBase->syncNumAlph(4,3); }
void CDlgKeyHill5x5::OnUpdateMat66()  { m_HillBase->syncNumAlph(4,4); }

void CDlgKeyHill5x5::OnExitMat36()  { m_HillBase->formatNum(0,0); }
void CDlgKeyHill5x5::OnExitMat37()  { m_HillBase->formatNum(0,1); }
void CDlgKeyHill5x5::OnExitMat38()  { m_HillBase->formatNum(0,2); }
void CDlgKeyHill5x5::OnExitMat40()  { m_HillBase->formatNum(0,3); }
void CDlgKeyHill5x5::OnExitMat46()  { m_HillBase->formatNum(0,4); }
void CDlgKeyHill5x5::OnExitMat47()  { m_HillBase->formatNum(1,0); }
void CDlgKeyHill5x5::OnExitMat48()  { m_HillBase->formatNum(1,1); }
void CDlgKeyHill5x5::OnExitMat49()  { m_HillBase->formatNum(1,2); }
void CDlgKeyHill5x5::OnExitMat50()  { m_HillBase->formatNum(1,3); }
void CDlgKeyHill5x5::OnExitMat111() { m_HillBase->formatNum(1,4); }
void CDlgKeyHill5x5::OnExitMat57()  { m_HillBase->formatNum(2,0); }
void CDlgKeyHill5x5::OnExitMat58()  { m_HillBase->formatNum(2,1); }
void CDlgKeyHill5x5::OnExitMat59()  { m_HillBase->formatNum(2,2); }
void CDlgKeyHill5x5::OnExitMat56()  { m_HillBase->formatNum(2,3); }
void CDlgKeyHill5x5::OnExitMat115() { m_HillBase->formatNum(2,4); }
void CDlgKeyHill5x5::OnExitMat60()  { m_HillBase->formatNum(3,0); }
void CDlgKeyHill5x5::OnExitMat61()  { m_HillBase->formatNum(3,1); }
void CDlgKeyHill5x5::OnExitMat62()  { m_HillBase->formatNum(3,2); }
void CDlgKeyHill5x5::OnExitMat116() { m_HillBase->formatNum(3,3); }
void CDlgKeyHill5x5::OnExitMat117() { m_HillBase->formatNum(3,4); }
void CDlgKeyHill5x5::OnExitMat63()  { m_HillBase->formatNum(4,0); }
void CDlgKeyHill5x5::OnExitMat64()  { m_HillBase->formatNum(4,1); }
void CDlgKeyHill5x5::OnExitMat69()  { m_HillBase->formatNum(4,2); }
void CDlgKeyHill5x5::OnExitMat65()  { m_HillBase->formatNum(4,3); }
void CDlgKeyHill5x5::OnExitMat66()  { m_HillBase->formatNum(4,4); }

// HILL parameter
void CDlgKeyHill5x5::SetDimension( unsigned long d )
{
	const unsigned long HillDimID[] = { 0, IDC_RADIO1, IDC_RADIO2, IDC_RADIO3, IDC_RADIO4, IDC_RADIO5 };
	m_HillBase->selectHillDimension( d ); radioSetHillDim(HillDimID[d]);
}
void CDlgKeyHill5x5::OnDimension1() { SetDimension(1); }
void CDlgKeyHill5x5::OnDimension2() { SetDimension(2); }
void CDlgKeyHill5x5::OnDimension3() { SetDimension(3); }
void CDlgKeyHill5x5::OnDimension4() { SetDimension(4); }
void CDlgKeyHill5x5::OnDimension5() { SetDimension(5); }

void CDlgKeyHill5x5::OnEnableAlphCode()     { m_HillBase->selectMatType ( HILL_CHAR_MATRIX ); }
void CDlgKeyHill5x5::OnDisableAlphCode()    { m_HillBase->selectMatType ( HILL_NUM_MATRIX ); }
void CDlgKeyHill5x5::OnRowVectorMatrix()    { m_HillBase->selectMultType( MATRIX_VECTOR ); radioSetMultType( IDC_RADIO8 ); }
void CDlgKeyHill5x5::OnMatrixColumnVector() { m_HillBase->selectMultType( VECTOR_MATRIX ); radioSetMultType( IDC_RADIO9 ); }

// helper functions
void CDlgKeyHill5x5::radioSetMultType( unsigned long ID ) {	CheckRadioButton(IDC_RADIO8,IDC_RADIO9, ID); }
void CDlgKeyHill5x5::radioSetHillDim ( unsigned long ID ) {	CheckRadioButton(IDC_RADIO1,IDC_RADIO5, ID); }
void CDlgKeyHill5x5::radioSetMatType ( unsigned long ID ) {	CheckRadioButton(IDC_RADIO6,IDC_RADIO7, ID); }
void CDlgKeyHill5x5::displayAlphabet() 
{ 
	CString sc;
	sc.Format( IDS_HILL_CASE, theApp.TextOptions.getAlphabet().GetLength() );
	GetDlgItem(IDC_STATIC_HILL_ALPH)->SetWindowText(sc);
	m_pHillAlphInfo = theApp.TextOptions.getAlphabet();
	UpdateData( FALSE );
}

BOOL CDlgKeyHill5x5::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_HillBase->setMatFont();

   if ( m_HillBase->multType == MATRIX_VECTOR ) 
   	radioSetMultType( IDC_RADIO8 );
   else
   	radioSetMultType( IDC_RADIO9 );

   if ( m_HillBase->matType == HILL_CHAR_MATRIX )
	   radioSetMatType ( IDC_RADIO6 );
   else
	   radioSetMatType ( IDC_RADIO7 );

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

void CDlgKeyHill5x5::DoCrypt( unsigned long mode )
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

void CDlgKeyHill5x5::OnOK()		 
{ 
   DoCrypt(0); 
}

void CDlgKeyHill5x5::OnDecrypt()  
{ 
   DoCrypt(1); 
}

void CDlgKeyHill5x5::OnPasteKey() 
{	
   m_HillBase->pasteKey(); 
   SetDimension( m_HillBase->dim );
   UpdateData(FALSE);
}

void CDlgKeyHill5x5::OnZufaelligerSchluessel() 
{
	m_HillBase->randomKey();
   GetDlgItem(IDOK)->SetFocus();
}

void CDlgKeyHill5x5::OnResetKey()
{
	m_HillBase->Clear();
}

void CDlgKeyHill5x5::OnGroessereSchluessel() 
{
   m_HillBase->currDlg = DLG_HILL_10x10; 
   m_HillBase->max_dim = DIM_DLG_HILL_10x10;
   m_HillBase->GetHillMatrix();
   CDialog::OnOK();	
}

void CDlgKeyHill5x5::OnHillOptions()
{
   m_HillBase->SetHillOptions();
   UpdateData(FALSE);
}

void CDlgKeyHill5x5::OnTextOptions()
{
   if ( m_HillBase->SetTextOptions() )
	   displayAlphabet();
}

void CDlgKeyHill5x5::checkForInvalidCharacterInput() {
	// get the current alphabet
	CString alphabet = theApp.TextOptions.getAlphabet();
	// as soon as this variables turns true, we leave the loop below
	bool error = false;
	// go through all elements of the matrix
	for(int x=0; x<5 && !error; x++) {
		for(int y=0; y<5 && !error; y++) {
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