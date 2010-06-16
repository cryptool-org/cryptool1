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
// HillSchluesselAusgabe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "SquareMatrixModN.h"
#include "CrypToolApp.h"
#include "DlgShowKeyHill5x5.h"
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
// Dialogfeld CDlgShowKeyHill5x5 


CDlgShowKeyHill5x5::CDlgShowKeyHill5x5(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowKeyHill5x5::IDD, pParent)
   , m_HillBase(0)
{
}

CDlgShowKeyHill5x5::~CDlgShowKeyHill5x5()
{
}

void CDlgShowKeyHill5x5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

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

   DDX_Text( pDX, IDC_EDIT2,  m_HillBase->HillOptions.m_alphabetOffset );
}


BEGIN_MESSAGE_MAP(CDlgShowKeyHill5x5, CDialog)
	//{{AFX_MSG_MAP(CDlgShowKeyHill5x5)
	ON_BN_CLICKED(IDC_RADIO1,  OnKey)
	ON_BN_CLICKED(IDC_RADIO2,  OnInvKey)
	ON_BN_CLICKED(IDC_BUTTON1, OnCopyKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgShowKeyHill5x5 


BOOL CDlgShowKeyHill5x5::OnInitDialog() 
{
   CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

void CDlgShowKeyHill5x5::OnCopyKey() 
{
}

void CDlgShowKeyHill5x5::OnKey()
{
}

void CDlgShowKeyHill5x5::OnInvKey()
{
}

