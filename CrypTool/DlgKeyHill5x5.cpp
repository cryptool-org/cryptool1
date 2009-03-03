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

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHill5x5 


CDlgKeyHill5x5::CDlgKeyHill5x5(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyHill5x5::IDD, pParent)
	, m_pHillAlphInfo(_T(""))
{
	hillklasse = new CHillEncryption(theApp.TextOptions.getAlphabet().GetBuffer(0));;
	m_decrypt = 0;
	//{{AFX_DATA_INIT(CDlgKeyHill5x5)
	m_Verbose = FALSE;
	//}}AFX_DATA_INIT
}

CDlgKeyHill5x5::~CDlgKeyHill5x5()
{
	if(hillklasse) delete hillklasse;
	if(mat) delete mat;
}

void CDlgKeyHill5x5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyHill5x5)
	DDX_Check(pDX, IDC_CHECK1, m_Verbose);
	DDX_Control(pDX, IDC_EDIT1, m_FeldUnsichtbar);
	DDX_Control(pDX, IDC_EDIT11, m_Feld11);
	DDX_Control(pDX, IDC_EDIT12, m_Feld12);
	DDX_Control(pDX, IDC_EDIT13, m_Feld13);
	DDX_Control(pDX, IDC_EDIT14, m_Feld14);
	DDX_Control(pDX, IDC_EDIT15, m_Feld15);
	DDX_Control(pDX, IDC_EDIT21, m_Feld21);
	DDX_Control(pDX, IDC_EDIT22, m_Feld22);
	DDX_Control(pDX, IDC_EDIT23, m_Feld23);
	DDX_Control(pDX, IDC_EDIT24, m_Feld24);
	DDX_Control(pDX, IDC_EDIT25, m_Feld25);
	DDX_Control(pDX, IDC_EDIT31, m_Feld31);
	DDX_Control(pDX, IDC_EDIT32, m_Feld32);
	DDX_Control(pDX, IDC_EDIT33, m_Feld33);
	DDX_Control(pDX, IDC_EDIT34, m_Feld34);
	DDX_Control(pDX, IDC_EDIT35, m_Feld35);
	DDX_Control(pDX, IDC_EDIT41, m_Feld41);
	DDX_Control(pDX, IDC_EDIT42, m_Feld42);
	DDX_Control(pDX, IDC_EDIT43, m_Feld43);
	DDX_Control(pDX, IDC_EDIT44, m_Feld44);
	DDX_Control(pDX, IDC_EDIT45, m_Feld45);
	DDX_Control(pDX, IDC_EDIT51, m_Feld51);
	DDX_Control(pDX, IDC_EDIT52, m_Feld52);
	DDX_Control(pDX, IDC_EDIT53, m_Feld53);
	DDX_Control(pDX, IDC_EDIT54, m_Feld54);
	DDX_Control(pDX, IDC_EDIT55, m_Feld55);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT36, m_Feld36);
	DDX_Control(pDX, IDC_EDIT37, m_Feld37);
	DDX_Control(pDX, IDC_EDIT38, m_Feld38);
	DDX_Control(pDX, IDC_EDIT40, m_Feld40);
	DDX_Control(pDX, IDC_EDIT46, m_Feld46);
	DDX_Control(pDX, IDC_EDIT47, m_Feld47);
	DDX_Control(pDX, IDC_EDIT48, m_Feld48);
	DDX_Control(pDX, IDC_EDIT49, m_Feld49);
	DDX_Control(pDX, IDC_EDIT50, m_Feld50);
	DDX_Control(pDX, IDC_EDIT111, m_Feld111);
	DDX_Control(pDX, IDC_EDIT57, m_Feld57);
	DDX_Control(pDX, IDC_EDIT58, m_Feld58);
	DDX_Control(pDX, IDC_EDIT59, m_Feld59);
	DDX_Control(pDX, IDC_EDIT56, m_Feld56);
	DDX_Control(pDX, IDC_EDIT115, m_Feld115);
	DDX_Control(pDX, IDC_EDIT60, m_Feld60);
	DDX_Control(pDX, IDC_EDIT61, m_Feld61);
	DDX_Control(pDX, IDC_EDIT62, m_Feld62);
	DDX_Control(pDX, IDC_EDIT116, m_Feld116);
	DDX_Control(pDX, IDC_EDIT117, m_Feld117);
	DDX_Control(pDX, IDC_EDIT63, m_Feld63);
	DDX_Control(pDX, IDC_EDIT64, m_Feld64);
	DDX_Control(pDX, IDC_EDIT69, m_Feld69);
	DDX_Control(pDX, IDC_EDIT65, m_Feld65);
	DDX_Control(pDX, IDC_EDIT66, m_Feld66);
	DDX_Text(pDX, IDC_EDIT3, m_pHillAlphInfo);
}


BEGIN_MESSAGE_MAP(CDlgKeyHill5x5, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyHill5x5)
	ON_BN_CLICKED(IDC_RADIO1, OnDimension1)
	ON_BN_CLICKED(IDC_RADIO2, OnDimension2)
	ON_BN_CLICKED(IDC_RADIO3, OnDimension3)
	ON_BN_CLICKED(IDC_RADIO4, OnDimension4)
	ON_BN_CLICKED(IDC_RADIO5, OnDimension5)
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

	ON_BN_CLICKED(IDC_RADIO6, OnDisableAlphCode)
	ON_BN_CLICKED(IDC_RADIO7, OnEnableAlphCode)

	ON_BN_CLICKED(IDC_RADIO8, OnRowVectorMatrix)
	ON_BN_CLICKED(IDC_RADIO9, OnMatrixColumnVector)
	
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


	ON_BN_CLICKED(IDC_BUTTON3, OnZufaelligerSchluessel)
	ON_BN_CLICKED(IDC_BUTTON4, OnGroessereSchluessel)
	ON_BN_CLICKED(IDC_BUTTON5, OnDecrypt)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)
	ON_BN_CLICKED(IDC_BUTTON1,	OnHillOptions)

	ON_BN_CLICKED(IDC_CHECK1, OnVerbose)

	ON_BN_CLICKED(IDC_BUTTON_TEXTOPTIONS, OnTextOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyHill5x5 


void CDlgKeyHill5x5::OnUpdateMat11() 
{
	// TODO: Wenn es sich hierbei um ein RICHEDIT-Steuerelement handelt, sendet es
	// sendet diese Benachrichtigung nur, wenn die Funktion CDialog::OnInitDialog()
	// überschrieben wird, um die EM_SETEVENTMASK-Nachricht an das Steuerelement
	// mit dem ENM_UPDATE-Attribut Ored in die Maske lParam zu senden.
	
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	UpdateFeld(m_pFelder[0][0]);
	setFeldAlphCode(m_pFelder[0][0],m_pAlphCode[0][0]);
}

void CDlgKeyHill5x5::OnUpdateMat12() 
{
	UpdateFeld(m_pFelder[0][1]);
	setFeldAlphCode(m_pFelder[0][1],m_pAlphCode[0][1]);
}

void CDlgKeyHill5x5::OnUpdateMat13() 
{
	UpdateFeld(m_pFelder[0][2]);
	setFeldAlphCode(m_pFelder[0][2],m_pAlphCode[0][2]);
}

void CDlgKeyHill5x5::OnUpdateMat14() 
{
	UpdateFeld(m_pFelder[0][3]);
	setFeldAlphCode(m_pFelder[0][3],m_pAlphCode[0][3]);
}

void CDlgKeyHill5x5::OnUpdateMat15() 
{
	UpdateFeld(m_pFelder[0][4]);
	setFeldAlphCode(m_pFelder[0][4],m_pAlphCode[0][4]);
}

void CDlgKeyHill5x5::OnUpdateMat21() 
{
	UpdateFeld(m_pFelder[1][0]);
	setFeldAlphCode(m_pFelder[1][0],m_pAlphCode[1][0]);
}

void CDlgKeyHill5x5::OnUpdateMat22() 
{
	UpdateFeld(m_pFelder[1][1]);
	setFeldAlphCode(m_pFelder[1][1],m_pAlphCode[1][1]);
}

void CDlgKeyHill5x5::OnUpdateMat23() 
{
	UpdateFeld(m_pFelder[1][2]);
	setFeldAlphCode(m_pFelder[1][2],m_pAlphCode[1][2]);
}

void CDlgKeyHill5x5::OnUpdateMat24() 
{
	UpdateFeld(m_pFelder[1][3]);
	setFeldAlphCode(m_pFelder[1][3],m_pAlphCode[1][3]);
}

void CDlgKeyHill5x5::OnUpdateMat25() 
{
	UpdateFeld(m_pFelder[1][4]);
	setFeldAlphCode(m_pFelder[1][4],m_pAlphCode[1][4]);
}

void CDlgKeyHill5x5::OnUpdateMat31() 
{
	UpdateFeld(m_pFelder[2][0]);
	setFeldAlphCode(m_pFelder[2][0],m_pAlphCode[2][0]);
}

void CDlgKeyHill5x5::OnUpdateMat32() 
{
	UpdateFeld(m_pFelder[2][1]);
	setFeldAlphCode(m_pFelder[2][1],m_pAlphCode[2][1]);
}

void CDlgKeyHill5x5::OnUpdateMat33() 
{
	UpdateFeld(m_pFelder[2][2]);
	setFeldAlphCode(m_pFelder[2][2],m_pAlphCode[2][2]);
}

void CDlgKeyHill5x5::OnUpdateMat34() 
{
	UpdateFeld(m_pFelder[2][3]);
	setFeldAlphCode(m_pFelder[2][3],m_pAlphCode[2][3]);
}

void CDlgKeyHill5x5::OnUpdateMat35() 
{
	UpdateFeld(m_pFelder[2][4]);
	setFeldAlphCode(m_pFelder[2][4],m_pAlphCode[2][4]);
}

void CDlgKeyHill5x5::OnUpdateMat41() 
{
	UpdateFeld(m_pFelder[3][0]);
	setFeldAlphCode(m_pFelder[3][0],m_pAlphCode[3][0]);
}

void CDlgKeyHill5x5::OnUpdateMat42() 
{
	UpdateFeld(m_pFelder[3][1]);
	setFeldAlphCode(m_pFelder[3][1],m_pAlphCode[3][1]);
}

void CDlgKeyHill5x5::OnUpdateMat43() 
{
	UpdateFeld(m_pFelder[3][2]);
	setFeldAlphCode(m_pFelder[3][2],m_pAlphCode[3][2]);
}

void CDlgKeyHill5x5::OnUpdateMat44() 
{
	UpdateFeld(m_pFelder[3][3]);
	setFeldAlphCode(m_pFelder[3][3],m_pAlphCode[3][3]);
}

void CDlgKeyHill5x5::OnUpdateMat45() 
{
	UpdateFeld(m_pFelder[3][4]);
	setFeldAlphCode(m_pFelder[3][4],m_pAlphCode[3][4]);
}

void CDlgKeyHill5x5::OnUpdateMat51() 
{
	UpdateFeld(m_pFelder[4][0]);
	setFeldAlphCode(m_pFelder[4][0],m_pAlphCode[4][0]);
}

void CDlgKeyHill5x5::OnUpdateMat52() 
{
	UpdateFeld(m_pFelder[4][1]);
	setFeldAlphCode(m_pFelder[4][1],m_pAlphCode[4][1]);
}

void CDlgKeyHill5x5::OnUpdateMat53() 
{
	UpdateFeld(m_pFelder[4][2]);
	setFeldAlphCode(m_pFelder[4][2],m_pAlphCode[4][2]);
}

void CDlgKeyHill5x5::OnUpdateMat54() 
{
	UpdateFeld(m_pFelder[4][3]);
	setFeldAlphCode(m_pFelder[4][3],m_pAlphCode[4][3]);
}

void CDlgKeyHill5x5::OnUpdateMat55() 
{
	UpdateFeld(m_pFelder[4][4]);
	setFeldAlphCode(m_pFelder[4][4],m_pAlphCode[4][4]);
}

void CDlgKeyHill5x5::OnUpdateMat36()
{
	UpdateAlphCode(m_pAlphCode[0][0]);
	setFeldAlph(m_pFelder[0][0],m_pAlphCode[0][0]);
}
void CDlgKeyHill5x5::OnUpdateMat37()
{
	UpdateAlphCode(m_pAlphCode[0][1]);
	setFeldAlph(m_pFelder[0][1],m_pAlphCode[0][1]);
}
void CDlgKeyHill5x5::OnUpdateMat38()
{
	UpdateAlphCode(m_pAlphCode[0][2]);
	setFeldAlph(m_pFelder[0][2],m_pAlphCode[0][2]);
}
void CDlgKeyHill5x5::OnUpdateMat40()
{
	UpdateAlphCode(m_pAlphCode[0][3]);
	setFeldAlph(m_pFelder[0][3],m_pAlphCode[0][3]);
}
void CDlgKeyHill5x5::OnUpdateMat46()
{
	UpdateAlphCode(m_pAlphCode[0][4]);
	setFeldAlph(m_pFelder[0][4],m_pAlphCode[0][4]);
}
void CDlgKeyHill5x5::OnUpdateMat47()
{
	UpdateAlphCode(m_pAlphCode[1][0]);
	setFeldAlph(m_pFelder[1][0],m_pAlphCode[1][0]);
}
void CDlgKeyHill5x5::OnUpdateMat48()
{
	UpdateAlphCode(m_pAlphCode[1][1]);
	setFeldAlph(m_pFelder[1][1],m_pAlphCode[1][1]);
}
void CDlgKeyHill5x5::OnUpdateMat49()
{
	UpdateAlphCode(m_pAlphCode[1][2]);
	setFeldAlph(m_pFelder[1][2],m_pAlphCode[1][2]);
}
void CDlgKeyHill5x5::OnUpdateMat50()
{
	UpdateAlphCode(m_pAlphCode[1][3]);
	setFeldAlph(m_pFelder[1][3],m_pAlphCode[1][3]);
}
void CDlgKeyHill5x5::OnUpdateMat111()
{
	UpdateAlphCode(m_pAlphCode[1][4]);
	setFeldAlph(m_pFelder[1][4],m_pAlphCode[1][4]);
}
void CDlgKeyHill5x5::OnUpdateMat57()
{
	UpdateAlphCode(m_pAlphCode[2][0]);
	setFeldAlph(m_pFelder[2][0],m_pAlphCode[2][0]);
}
void CDlgKeyHill5x5::OnUpdateMat58()
{
	UpdateAlphCode(m_pAlphCode[2][1]);
	setFeldAlph(m_pFelder[2][1],m_pAlphCode[2][1]);
}
void CDlgKeyHill5x5::OnUpdateMat59()
{
	UpdateAlphCode(m_pAlphCode[2][2]);
	setFeldAlph(m_pFelder[2][2],m_pAlphCode[2][2]);
}
void CDlgKeyHill5x5::OnUpdateMat56()
{
	UpdateAlphCode(m_pAlphCode[2][3]);
	setFeldAlph(m_pFelder[2][3],m_pAlphCode[2][3]);
}
void CDlgKeyHill5x5::OnUpdateMat115()
{
	UpdateAlphCode(m_pAlphCode[2][4]);
	setFeldAlph(m_pFelder[2][4],m_pAlphCode[2][4]);
}
void CDlgKeyHill5x5::OnUpdateMat60()
{
	UpdateAlphCode(m_pAlphCode[3][0]);
	setFeldAlph(m_pFelder[3][0],m_pAlphCode[3][0]);
}
void CDlgKeyHill5x5::OnUpdateMat61()
{
	UpdateAlphCode(m_pAlphCode[3][1]);
	setFeldAlph(m_pFelder[3][1],m_pAlphCode[3][1]);
}
void CDlgKeyHill5x5::OnUpdateMat62()
{
	UpdateAlphCode(m_pAlphCode[3][2]);
	setFeldAlph(m_pFelder[3][2],m_pAlphCode[3][2]);
}
void CDlgKeyHill5x5::OnUpdateMat116()
{
	UpdateAlphCode(m_pAlphCode[3][3]);
	setFeldAlph(m_pFelder[3][3],m_pAlphCode[3][3]);
}
void CDlgKeyHill5x5::OnUpdateMat117()
{
	UpdateAlphCode(m_pAlphCode[3][4]);
	setFeldAlph(m_pFelder[3][4],m_pAlphCode[3][4]);
}
void CDlgKeyHill5x5::OnUpdateMat63()
{
	UpdateAlphCode(m_pAlphCode[4][0]);
	setFeldAlph(m_pFelder[4][0],m_pAlphCode[4][0]);
}
void CDlgKeyHill5x5::OnUpdateMat64()
{
	UpdateAlphCode(m_pAlphCode[4][1]);
	setFeldAlph(m_pFelder[4][1],m_pAlphCode[4][1]);
}
void CDlgKeyHill5x5::OnUpdateMat69()
{
	UpdateAlphCode(m_pAlphCode[4][2]);
	setFeldAlph(m_pFelder[4][2],m_pAlphCode[4][2]);
}
void CDlgKeyHill5x5::OnUpdateMat65()
{
	UpdateAlphCode(m_pAlphCode[4][3]);
	setFeldAlph(m_pFelder[4][3],m_pAlphCode[4][3]);
}
void CDlgKeyHill5x5::OnUpdateMat66()
{
	UpdateAlphCode(m_pAlphCode[4][4]);
	setFeldAlph(m_pFelder[4][4],m_pAlphCode[4][4]);
}


void CDlgKeyHill5x5::OnExitMat36()
{
	setDoublePos(m_pAlphCode[0][0]);
}
void CDlgKeyHill5x5::OnExitMat37()
{
	setDoublePos(m_pAlphCode[0][1]);
}
void CDlgKeyHill5x5::OnExitMat38()
{
	setDoublePos(m_pAlphCode[0][2]);
}
void CDlgKeyHill5x5::OnExitMat40()
{
	setDoublePos(m_pAlphCode[0][3]);
}
void CDlgKeyHill5x5::OnExitMat46()
{
	setDoublePos(m_pAlphCode[0][4]);
}
void CDlgKeyHill5x5::OnExitMat47()
{
	setDoublePos(m_pAlphCode[1][0]);
}
void CDlgKeyHill5x5::OnExitMat48()
{
	setDoublePos(m_pAlphCode[1][1]);
}
void CDlgKeyHill5x5::OnExitMat49()
{
	setDoublePos(m_pAlphCode[1][2]);
}
void CDlgKeyHill5x5::OnExitMat50()
{
	setDoublePos(m_pAlphCode[1][3]);
}
void CDlgKeyHill5x5::OnExitMat111()
{
	setDoublePos(m_pAlphCode[1][4]);
}
void CDlgKeyHill5x5::OnExitMat57()
{
	setDoublePos(m_pAlphCode[2][0]);
}
void CDlgKeyHill5x5::OnExitMat58()
{
	setDoublePos(m_pAlphCode[2][1]);
}
void CDlgKeyHill5x5::OnExitMat59()
{
	setDoublePos(m_pAlphCode[2][2]);
}
void CDlgKeyHill5x5::OnExitMat56()
{
	setDoublePos(m_pAlphCode[2][3]);
}
void CDlgKeyHill5x5::OnExitMat115()
{
	setDoublePos(m_pAlphCode[2][4]);
}
void CDlgKeyHill5x5::OnExitMat60()
{
	setDoublePos(m_pAlphCode[3][0]);
}
void CDlgKeyHill5x5::OnExitMat61()
{
	setDoublePos(m_pAlphCode[3][1]);
}
void CDlgKeyHill5x5::OnExitMat62()
{
	setDoublePos(m_pAlphCode[3][2]);
}
void CDlgKeyHill5x5::OnExitMat116()
{
	setDoublePos(m_pAlphCode[3][3]);
}
void CDlgKeyHill5x5::OnExitMat117()
{
	setDoublePos(m_pAlphCode[3][4]);
}
void CDlgKeyHill5x5::OnExitMat63()
{
	setDoublePos(m_pAlphCode[4][0]);
}
void CDlgKeyHill5x5::OnExitMat64()
{
	setDoublePos(m_pAlphCode[4][1]);
}
void CDlgKeyHill5x5::OnExitMat69()
{
	setDoublePos(m_pAlphCode[4][2]);
}
void CDlgKeyHill5x5::OnExitMat65()
{
	setDoublePos(m_pAlphCode[4][3]);
}
void CDlgKeyHill5x5::OnExitMat66()
{
	setDoublePos(m_pAlphCode[4][4]);
}


void CDlgKeyHill5x5::UpdateFeld(CEdit *feld)
{
	if(!alphCode)
	{
	CString cs;
	feld->GetWindowText(cs);

	// QUICK FIX: if user supplied MORE THAN ON CHARACTER, for example by using 
	// the copy/paste mechanism, throw away all characters except the first one
	if(cs.GetLength() > 1) {
		cs.Delete(1, cs.GetLength() - 1);
	}

	if (cs.GetLength() == 1)
	{
		if ( hillklasse->ist_erlaubtes_zeichen(cs[0]) )
		{
			// zum naechsten Feld springen
			NextDlgCtrl();
		}
		else if ( (theApp.TextOptions.getIgnoreCase()) && (MyIsLower(cs[0])) && 
			     (hillklasse->ist_erlaubtes_zeichen(MyToUpper(cs[0]))) )
		{
			// Zeichen in Grossbuchstaben umwandeln und anzeigen
			char c;
			c = MyToUpper(cs[0]);
			cs.SetAt(0,c);
			feld->SetWindowText(cs);
			// Jetzt wird die Funktion UpdateFeld erneut aufgerufen, daher darf
			// kein Sprung ins naechste Feld gemacht werden,
			// da das Programm wieder in diese funktion, dieses Mal in den
			// ersten Fall kommt. 
			// // zum naechsten Feld springen
			// NextDlgCtrl();
		}
		else
		{
			// Zeichen loeschen und Cursor wieder auf Anfang positionieren.
			// (Cursorpositionierung vor erstes moegliches Eingabezeichen
			// erfolgt mit leerem String automatisch.)
			cs.Empty();
			feld->SetWindowText(cs);
		}
	}
	}
}
void CDlgKeyHill5x5::UpdateAlphCode(CEdit *feld)
{
	if(alphCode)
	{
	CString cs;
	feld->GetWindowText(cs);
	if(cs.GetLength() == 2)
	{
		if(_ttoi(cs) < 0 || _ttoi(cs) > theApp.TextOptions.getAlphabet().GetLength())
		{
			cs.Empty();
			feld->SetWindowText(cs);
		}
		else
		{
			NextDlgCtrl();
		}
	}
	}
}

int CDlgKeyHill5x5::Display()
{
	int res;

	res=DoModal();

	//	MakeBin(m_einstr, buffer);
	
	return res;
}

void CDlgKeyHill5x5::OnOK() 
{
	UpdateData(true);
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "Hill" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(unsigned long(firstPosNull), "OrdChrOffset");
		CT_WRITE_REGISTRY(unsigned long(alphCode), "EditKeyChrMatrix");
		CT_CLOSE_REGISTRY();
	}
	// Matrizen anlegen und Daten aus Eingabefenster auslesen
	CSquareMatrixModN mat1(dim,hillklasse->get_modul());

	// mat muss wieder freigegeben werden, wenn nicht mehr benoetigt !
	// Dies geschieht im Destruktor
	mat = new CSquareMatrixModN(dim,hillklasse->get_modul());

	// Ueberpruefen, ob alle Felder der Matrix gefuellt sind
	// Falls ein Fehler ausgetreten ist (mindestens eine Eingabe fehlt),
	// zu der ersten fehlenden Eingabe springen (und Funktion verlasssen).
	if (! AlleFelderKorrekt(dim))
	{
		return;
	}

	// Matrix mit den Werten aus der Eingabemaske fuellen
	MatrixEinlesen(*mat, dim);
	
	// Falls die Matrix nicht invertierbar ist, wieder ins Fenster zurueckspringen
	if ( ! mat->invert(&mat1))
	{
		char msg[1024];
		LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY_INV,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(msg,pc_str,getDimMessage(),theApp.TextOptions.getAlphabet().GetLength());
		MessageBox(msg, pc_str1, MB_ICONWARNING|MB_OK);

		if(!alphCode)
		{
			m_pFelder[0][0]->SetFocus();
			m_pFelder[0][0]->SetSel(0,-1);
		}
		else
		{
			m_pAlphCode[0][0]->SetFocus();
			m_pAlphCode[0][0]->SetSel(0,-1);
		}
		return;
	}
	else
	{
		m_decrypt = 0;
		CDialog::OnOK();
	}

}

void CDlgKeyHill5x5::OnDecrypt()
{
	// Matrizen anlegen und Daten aus Eingabefenster auslesen
	CSquareMatrixModN mat1(dim,hillklasse->get_modul());

	// mat muss wieder freigegeben werden, wenn nicht mehr benoetigt !
	// Dies geschieht im Destruktor
	mat = new CSquareMatrixModN(dim,hillklasse->get_modul());

	// Ueberpruefen, ob alle Felder der Matrix gefuellt sind
	// Falls ein Fehler ausgetreten ist (mindestens eine Eingabe fehlt),
	// zu der ersten fehlenden Eingabe springen (und Funktion verlasssen).
	if (! AlleFelderKorrekt(dim))
	{
		return;
	}

	// Matrix mit den Werten aus der Eingabemaske fuellen
	MatrixEinlesen(*mat, dim);
	
	// Falls die Matrix nicht invertierbar ist, wieder ins Fenster zurueckspringen
	if ( ! mat->invert(&mat1))
	{
		char msg[1024];
		LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY_INV,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(msg,pc_str,getDimMessage(),theApp.TextOptions.getAlphabet().GetLength());
		MessageBox(msg, pc_str1, MB_ICONWARNING|MB_OK);
	
		if(!alphCode)
		{
			m_pFelder[0][0]->SetFocus();
			m_pFelder[0][0]->SetSel(0,-1);
		}
		else
		{
			m_pAlphCode[0][0]->SetFocus();
			m_pAlphCode[0][0]->SetSel(0,-1);
		}
		return;
	}
	else
	{
		m_decrypt = 1;
		CDialog::OnOK();
	}
}

BOOL CDlgKeyHill5x5::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_Verbose = bGlobVerbose;
	
	CheckRadioButton(IDC_RADIO6,IDC_RADIO7,IDC_RADIO6);

	if(iHillMultiplicationType)
		CheckRadioButton(IDC_RADIO8,IDC_RADIO9,IDC_RADIO8);
	else
		CheckRadioButton(IDC_RADIO8,IDC_RADIO9,IDC_RADIO9);

	// TODO: Zusätzliche Initialisierung hier einfügen
	int len = theApp.TextOptions.getAlphabet().GetLength();

	LoadString(AfxGetInstanceHandle(),IDS_HILL_CASE,pc_str,STR_LAENGE_STRING_TABLE);
	char l_str[1024];
	sprintf(l_str,pc_str,len);
	
	GetDlgItem(IDC_STATIC_HILL_ALPH)->SetWindowText(l_str);


	alphCode = 0;
	firstPosNull = 1;
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "Hill") == ERROR_SUCCESS)
	{
		
		CT_READ_REGISTRY_DEFAULT(firstPosNull, "OrdChrOffset", firstPosNull);
		CT_READ_REGISTRY_DEFAULT(alphCode,"EditKeyChrMatrix",alphCode);
		
		UpdateData(false);

		CT_CLOSE_REGISTRY();
	}

	if(!alphCode)
	{
		CheckRadioButton(IDC_RADIO6, IDC_RADIO7, IDC_RADIO6);
	}
	else
	{
		CheckRadioButton(IDC_RADIO6, IDC_RADIO7, IDC_RADIO7);
	}



	m_pHillAlphInfo = theApp.TextOptions.getAlphabet();

	UpdateData(FALSE);

	m_pFelder[0][0] = &m_Feld11;
	m_pFelder[0][1] = &m_Feld12;
	m_pFelder[0][2] = &m_Feld13;
	m_pFelder[0][3] = &m_Feld14;
	m_pFelder[0][4] = &m_Feld15;
	m_pFelder[1][0] = &m_Feld21;
	m_pFelder[1][1] = &m_Feld22;
	m_pFelder[1][2] = &m_Feld23;
	m_pFelder[1][3] = &m_Feld24;
	m_pFelder[1][4] = &m_Feld25;
	m_pFelder[2][0] = &m_Feld31;
	m_pFelder[2][1] = &m_Feld32;
	m_pFelder[2][2] = &m_Feld33;
	m_pFelder[2][3] = &m_Feld34;
	m_pFelder[2][4] = &m_Feld35;
	m_pFelder[3][0] = &m_Feld41;
	m_pFelder[3][1] = &m_Feld42;
	m_pFelder[3][2] = &m_Feld43;
	m_pFelder[3][3] = &m_Feld44;
	m_pFelder[3][4] = &m_Feld45;
	m_pFelder[4][0] = &m_Feld51;
	m_pFelder[4][1] = &m_Feld52;
	m_pFelder[4][2] = &m_Feld53;
	m_pFelder[4][3] = &m_Feld54;
	m_pFelder[4][4] = &m_Feld55;

	m_pAlphCode[0][0] = &m_Feld36;
	m_pAlphCode[0][1] = &m_Feld37;
	m_pAlphCode[0][2] = &m_Feld38;
	m_pAlphCode[0][3] = &m_Feld40;
	m_pAlphCode[0][4] = &m_Feld46;
	m_pAlphCode[1][0] = &m_Feld47;
	m_pAlphCode[1][1] = &m_Feld48;
	m_pAlphCode[1][2] = &m_Feld49;
	m_pAlphCode[1][3] = &m_Feld50;
	m_pAlphCode[1][4] = &m_Feld111;
	m_pAlphCode[2][0] = &m_Feld57;
	m_pAlphCode[2][1] = &m_Feld58;
	m_pAlphCode[2][2] = &m_Feld59;
	m_pAlphCode[2][3] = &m_Feld56;
	m_pAlphCode[2][4] = &m_Feld115;
	m_pAlphCode[3][0] = &m_Feld60;
	m_pAlphCode[3][1] = &m_Feld61;
	m_pAlphCode[3][2] = &m_Feld62;
	m_pAlphCode[3][3] = &m_Feld116;
	m_pAlphCode[3][4] = &m_Feld117;
	m_pAlphCode[4][0] = &m_Feld63;
	m_pAlphCode[4][1] = &m_Feld64;
	m_pAlphCode[4][2] = &m_Feld69;
	m_pAlphCode[4][3] = &m_Feld65;
	m_pAlphCode[4][4] = &m_Feld66;


	
	// Font mit fester Breite erstellen und fuer alle Schluesselfelder setzen
	cf.CreatePointFont(80,"Courier");
	for (int i=0; i<HILL_MAX_DIM; i++)
	{
		for (int j=0; j<HILL_MAX_DIM; j++)
		{
			m_pFelder[i][j]->SetFont(&cf);
			m_pAlphCode[i][j]->SetFont(&cf);
		}
	}

	if (iHillSchluesselDim > HILL_MAX_DIM)
	{
		iHillSchluesselDim = HILL_MAX_DIM;
	}

	ASSERT ((0 <= iHillSchluesselDim) && (iHillSchluesselDim <= HILL_MAX_DIM));
	dim = iHillSchluesselDim;

	switch (iHillSchluesselDim)
	{
	case 1:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO1);
		break;
	case 2:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO2);
		break;
	case 3:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO3);
		break;
	case 4:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO4);
		break;
	case 5:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO5);
		break;
	default:
		// Default Dimension = 2
		dim = 2;
		iHillSchluesselDim = dim;
		CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO2);
		break;
	}

	// Default: Verschlüsseln
	CheckRadioButton(IDC_RADIO15, IDC_RADIO16, IDC_RADIO15);

	AnzeigeDimensionSetzen(dim);



	//Read the matrix entries from hill10x10
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
			m_pFelder[i][j]->SetWindowText(sHillGlobalKey[i][j]);
		}
	}

	// Die Matrix enthaelt am Ende die Daten der Eingabemaske
	// Sie wird in der Nachrichtenbehandlungsfunktion "OnOK" angelegt und 
	// im Destruktor wieder freigegeben.
	mat = 0;

	CString Title;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_HILL,pc_str,STR_LAENGE_STRING_TABLE);
	Title = pc_str;
	VERIFY(m_Paste.AutoLoad(IDC_BUTTON2,this));
	if ( IsKeyEmpty( Title ))
	{
		m_Paste.EnableWindow(TRUE);
	}
	else
	{
		m_Paste.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
void CDlgKeyHill5x5::OnEnableAlphCode()
{
	alphCode = 1;
	AnzeigeDimensionSetzen(dim);
}
void CDlgKeyHill5x5::OnDisableAlphCode()
{
	alphCode = 0;
	AnzeigeDimensionSetzen(dim);
}
void CDlgKeyHill5x5::OnDimension1() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	dim = 1;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	if(!alphCode)
	{
		m_pFelder[0][0]->SetFocus();
		m_pFelder[0][0]->SetSel(0,-1);
	}
	else
	{
		m_pAlphCode[0][0]->SetFocus();
		m_pAlphCode[0][0]->SetSel(0,-1);
	}
}

void CDlgKeyHill5x5::OnDimension2() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	dim = 2;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	if(!alphCode)
	{
		m_pFelder[0][0]->SetFocus();
		m_pFelder[0][0]->SetSel(0,-1);
	}
	else
	{
		m_pAlphCode[0][0]->SetFocus();
		m_pAlphCode[0][0]->SetSel(0,-1);
	}
}

void CDlgKeyHill5x5::OnDimension3() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	dim = 3;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	if(!alphCode)
	{
		m_pFelder[0][0]->SetFocus();
		m_pFelder[0][0]->SetSel(0,-1);
	}
	else
	{
		m_pAlphCode[0][0]->SetFocus();
		m_pAlphCode[0][0]->SetSel(0,-1);
	}
}

void CDlgKeyHill5x5::OnDimension4() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	dim = 4;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	if(!alphCode)
	{
		m_pFelder[0][0]->SetFocus();
		m_pFelder[0][0]->SetSel(0,-1);
	}
	else
	{
		m_pAlphCode[0][0]->SetFocus();
		m_pAlphCode[0][0]->SetSel(0,-1);
	}
}

void CDlgKeyHill5x5::OnDimension5() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	dim = 5;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	if(!alphCode)
	{
		m_pFelder[0][0]->SetFocus();
		m_pFelder[0][0]->SetSel(0,-1);
	}
	else
	{
		m_pAlphCode[0][0]->SetFocus();
		m_pAlphCode[0][0]->SetSel(0,-1);
	}
}

void CDlgKeyHill5x5::AnzeigeDimensionSetzen(int dim)
{

		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				if(alphCode)
				{
					m_pFelder[i][j]->EnableWindow(FALSE);
					m_pAlphCode[i][j]->EnableWindow(TRUE);
				}
				if(!alphCode)
				{
					m_pAlphCode[i][j]->EnableWindow(FALSE);
					m_pFelder[i][j]->EnableWindow(TRUE);
				}
			}
		}





	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM));

	BOOL mybool;

	for (int i=0; i<HILL_MAX_DIM; i++)
	{
		for (int j=0; j<HILL_MAX_DIM; j++)
		{
			if (i<dim && j<dim)
			{
				// Eine Eingabe in die Felder muss moeglich sein
				mybool = TRUE;
			}
			else
			{
				// Eine Eingabe in die Felder darf nicht moeglich sein
				mybool = FALSE;
			}
			if(!alphCode)
				m_pFelder[i][j]->EnableWindow(mybool);
			if(alphCode)
				m_pAlphCode[i][j]->EnableWindow(mybool);
		}
	}

	if(!alphCode)
	{
		m_pFelder[0][0]->SetFocus();
		m_pFelder[0][0]->SetSel(0,-1);
	}
	else
	{
		m_pAlphCode[0][0]->SetFocus();
		m_pAlphCode[0][0]->SetSel(0,-1);
	}
}

int CDlgKeyHill5x5::AlleFelderKorrekt(int dim)
{
	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM));

	CString cs;

	for (int i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
		{
			m_pFelder[i][j]->GetWindowText(cs);

			// Kleinbuchstaben wurden schon zu Grossbuchstaben konvertiert, sofern erforderlich;
			// deshalb muss dies hier nicht mehr abgefragt werden.
			if ( (cs.GetLength() == 0) || (! hillklasse->ist_erlaubtes_zeichen(cs[0])) )
			{
				LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY_NONVALID_CHAR,pc_str,STR_LAENGE_STRING_TABLE);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str, pc_str1, MB_ICONWARNING|MB_OK);
				
				if(!alphCode)
				{
					m_pFelder[0][0]->SetFocus();
					m_pFelder[0][0]->SetSel(0,-1);
				}
				else
				{
					m_pAlphCode[0][0]->SetFocus();
					m_pAlphCode[0][0]->SetSel(0,-1);
				}
				return FALSE;
			}
		}
	}

	return TRUE;
}

void CDlgKeyHill5x5::MatrixEinlesen(CSquareMatrixModN& mat, int dim)
{
	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM));

	CString cs;

	for (int i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
		{
			m_pFelder[i][j]->GetWindowText(cs);

			// Kleinbuchstaben wurden schon zu Grossbuchstaben konvertiert, sofern erforderlich;
			// deshalb muss dies hier nicht mehr beruecksichtigt werden.
			ASSERT(hillklasse->ist_erlaubtes_zeichen(cs[0]));
			mat(i,j) = hillklasse->my_char_to_int(cs[0]);
		}
	}
}

void CDlgKeyHill5x5::MatrixAnzeigen(CSquareMatrixModN& mat)
{
	int dimension = mat.get_dim();

	ASSERT ((1 <= dimension) && (dimension <= HILL_MAX_DIM));

	CString cs;

	for (int i=0; i<dimension; i++)
	{
		for (int j=0; j<dimension; j++)
		{
			cs = hillklasse->my_int_to_char(mat(i,j));
			m_pFelder[i][j]->SetWindowText(cs);
		}
	}
}


// Die Position fuer den naechsten Eintrag in der Schluesselmatrix wird berechnet.
// Falls kein weiterer Eintrag mehr zur Verfuegung steht, wird FALSE zurueckgegeben,
// im anderen Fall TRUE.
bool CDlgKeyHill5x5::NaechsterEintrag(int &i, int &j) 
{
	bool rc = true;

	j++;
	if (j == HILL_MAX_DIM)
	{
		// Wir starten in der naechsten Zeile wieder vorne, ...
		i++;
		j = 0;
		// ... sofern es noch eine weitere gibt.
		if (i == HILL_MAX_DIM)
		{
			// Es gibt keine weitere Zeile
			rc = false;
		}
	}

	return rc;
}


void CDlgKeyHill5x5::OnPasteKey() 
{
	CString cs, hilf;

	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_HILL,pc_str,STR_LAENGE_STRING_TABLE);
	if ( PasteKey(pc_str,cs) )
	{

 		int i=0,          // Zeile des naechsten Eintrages in die Schluesselmatrix
 			j=-1,         // Spalte des naechsten Eintrages in die Schluesselmatrix 
 			l=0,          // Laufvariable fuer den Text aus der Zwischenablage
 			laenge = cs.GetLength(); // Laenge des Textes der Zwischenablage
		int keyDim = 0;
		while (l<laenge) {
			hilf = cs[l++];
			if (hillklasse->ist_erlaubtes_zeichen(hilf[0])) i++;
		}
		
		if ( i <= HILL_MAX_DIM*HILL_MAX_DIM )
		{	
			i = l = 0;
 			while (l < laenge)
 			{
 				hilf = cs[l];
 
				// Kleinbuchstaben wurden schon zu Grossbuchstaben konvertiert, sofern erforderlich;
				// deshalb muss dies hier nicht mehr abgefragt werden.
				if (hillklasse->ist_erlaubtes_zeichen(hilf[0]))
				{
 					// Naechsten Eintrag berechnen
 					if (NaechsterEintrag(i,j))
 					{
 						// Wert einfach uebernehmen
						m_pFelder[i][j]->SetWindowText(hilf);
 					}
 					else
 					{
 						// Es gibt keine weitere Zeile
 						l = laenge;
 					}
 				}
 				else if (hilf[0] == '\n')
 				{
 					// Wir starten in der naechsten Zeile wieder vorne,
 					// sofern wir nicht schon am Anfang einer Zeile stehen...
					if (keyDim == 0) keyDim = j+1;
					else if ( j >= 0 && j+1 != keyDim ) {
						/* ToDo: Fehler Meldung */
						return; 
					}
 					i++;
 					j = -1;
 					// ... sofern es noch eine weitere gibt.
 					if (i == HILL_MAX_DIM)
 					{
 						// Es gibt keine weitere Zeile
 						l = laenge;
 					}
 				}
 
 				l++;
 			}

			// if ( j < 0 ) i--;
			ASSERT ((0 <= keyDim) && (keyDim <= HILL_MAX_DIM));
			dim = keyDim;
			iHillSchluesselDim = dim;

			switch (iHillSchluesselDim)
			{
			case 1:	
				CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO1);
				OnDimension1();
				break;
			case 2:	
				CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO2);
				OnDimension2();
				break;
			case 3:	
				CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO3);
				OnDimension3();
				break;
			case 4:	
				CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO4);
				OnDimension4();
				break;
			case 5:	
				CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO5);
				OnDimension5();
				break;
			default:
				// Default Dimension = 2
				dim = 2;
				iHillSchluesselDim = dim;
				CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO2);
				OnDimension2();
				break;
			}
			AnzeigeDimensionSetzen(dim);


			CString str;
			for(int i=0;i<5;i++)
			{
				for(int j=0;j<5;j++)
				{
					m_pFelder[i][j]->GetWindowText(str);
					m_pAlphCode[i][j]->SetWindowText(getAlphCode(str));
				}
			}
			
			// Cursor in Feld links oben setzen

			if(!alphCode)
			{
				m_pFelder[0][0]->SetFocus();
				m_pFelder[0][0]->SetSel(0,-1);
			}
			else
			{
				m_pAlphCode[0][0]->SetFocus();
				m_pAlphCode[0][0]->SetSel(0,-1);
			}
		}
 		else
		{  
			// Message ... the stored Hill Key ...
		}
	}
}


void CDlgKeyHill5x5::OnZufaelligerSchluessel() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	// Zuerst eine zufaellige Matrix erzeugen und im Anschluss
	// in die Maske schreiben
	CSquareMatrixModN mat1(dim, hillklasse->get_modul());
	if (mat1.zufaellige_invertierbare_matrix())
	{
		MatrixAnzeigen(mat1);
		m_pFelder[0][0]->SetFocus();
	}
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ON_WRONG_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, NULL, MB_ICONERROR|MB_OK);

	}

	CString str;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			m_pFelder[i][j]->GetWindowText(str);
			m_pAlphCode[i][j]->SetWindowText(getAlphCode(str));
		}
	}
}


void CDlgKeyHill5x5::OnGroessereSchluessel() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	UpdateData(true);
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "Hill" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(unsigned long(firstPosNull), "OrdChrOffset");
		CT_WRITE_REGISTRY(unsigned long(alphCode), "EditKeyChrMatrix");
		CT_CLOSE_REGISTRY();
	}

	iHillSchluesselFensterGroesse = HILL_SCHLUESSEL_GROSS;
	bGlobVerbose = bool(m_Verbose);


	//save matrix entries for hill10x10
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
			m_pFelder[i][j]->GetWindowText(sHillGlobalKey[i][j]);
		}
	}
	CDialog::OnOK();	
}

BEGIN_MESSAGE_MAP(CHiEdit, CEdit)
	//{{AFX_MSG_MAP(CHiEdit)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CHiEdit::OnLButtonUp(UINT nFlags, CPoint point )
{
	CEdit::OnLButtonUp(nFlags,point);
	SetSel(0, -1);
} 
CString CDlgKeyHill5x5::getAlphCode(CString alphChar)
{
	CString str;
	for(int i=0;i<theApp.TextOptions.getAlphabet().GetLength();i++)
	{
		if(theApp.TextOptions.getAlphabet()[i] == alphChar)
		{
			if(getFirstPosNull())
				str.Format("%d",i);
			else
				str.Format("%d",i+1);
			
			if(str.GetLength() == 1)
				str.Insert(0,"0");
			return str;
		}
	}
	return "";
}
CString CDlgKeyHill5x5::getAlphChar(CString alphPos)
{
		int pos = _ttoi(alphPos);

		if(!getFirstPosNull())
			pos--;
		
		if(pos < 0 || pos > theApp.TextOptions.getAlphabet().GetLength())
			return "";
		else
			return theApp.TextOptions.getAlphabet().Mid(pos, 1);
}
void CDlgKeyHill5x5::setFeldAlphCode(CEdit *feld,CEdit *feldAlph)
{
	if(!alphCode)
	{
		CString str;
		feld->GetWindowText(str);
		feldAlph->SetWindowText(getAlphCode(str));
	}
}
void CDlgKeyHill5x5::setFeldAlph(CEdit *feld,CEdit *feldAlph)
{
    if(alphCode)
	{
		CString str;
		feldAlph->GetWindowText(str);
		if(str.GetLength() == 2)
			feld->SetWindowText(getAlphChar(str));
	}
}
void CDlgKeyHill5x5::setDoublePos(CEdit *feld)
{
	CString cs;
	feld->GetWindowText(cs);

	if(cs.GetLength() == 1)
	{
		if(_ttoi(cs) < 1 || _ttoi(cs) > theApp.TextOptions.getAlphabet().GetLength())
		{
			cs.Empty();
			feld->SetWindowText(cs);
		}
		else
		{
			cs.Insert(0,"0");
			feld->SetWindowText(cs);
		}
		PrevDlgCtrl(); //because Tab and UpdateFeld makes both NextDlgCtrl
	}
}
void CDlgKeyHill5x5::OnRowVectorMatrix()
{
	iHillMultiplicationType = 1;
}
void CDlgKeyHill5x5::OnMatrixColumnVector()
{
	iHillMultiplicationType = 0;
}
void CDlgKeyHill5x5::OnHillOptions()
{
	DlgHillOptions hillOpt;
	hillOpt.DoModal();
	
	CString str;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			m_pFelder[i][j]->GetWindowText(str);
			m_pAlphCode[i][j]->SetWindowText(getAlphCode(str));
		}
	}

}
BOOL CDlgKeyHill5x5::getFirstPosNull()
{
	unsigned long firstPosNull;

	firstPosNull = 1;
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "Hill") == ERROR_SUCCESS)
	{		
		CT_READ_REGISTRY_DEFAULT(firstPosNull, "OrdChrOffset", firstPosNull);
		
		UpdateData(false);

		CT_CLOSE_REGISTRY();
	}
	return firstPosNull;
}
CString CDlgKeyHill5x5::getDimMessage()
{
	int iHillKeyDim = dim;

	switch (iHillKeyDim)
	{
		case 1:	
			return "1*1";
		case 2:	
			return "2*2";
		case 3:	
			return "3*3";
		case 4:	
			return "4*4";
		case 5:	
			return "5*5";
		default:
			return "2*2";
	}
}
void CDlgKeyHill5x5::OnVerbose()
{
	CButton* pCheck = (CButton*)GetDlgItem(IDC_CHECK1);
	m_Verbose = pCheck->GetCheck();
}

void CDlgKeyHill5x5::OnTextOptions()
{
	if(theApp.TextOptions.DoModal() != IDOK) return;

	//if(hillklasse) delete hillklasse;
	hillklasse = new CHillEncryption(theApp.TextOptions.getAlphabet().GetBuffer(0));
	
	int len = theApp.TextOptions.getAlphabet().GetLength();
	LoadString(AfxGetInstanceHandle(),IDS_HILL_CASE,pc_str,STR_LAENGE_STRING_TABLE);
	char l_str[1024];
	sprintf(l_str,pc_str,len);
	GetDlgItem(IDC_STATIC_HILL_ALPH)->SetWindowText(l_str);

	m_pHillAlphInfo = theApp.TextOptions.getAlphabet();
	
	UpdateData(false);
}