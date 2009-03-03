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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHill10x10 


CDlgKeyHill10x10::CDlgKeyHill10x10(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyHill10x10::IDD, pParent)
	, m_pHillAlphInfo(_T(""))
{
	hillklasse = new CHillEncryption(theApp.TextOptions.getAlphabet().GetBuffer(0));;
	m_decrypt = 0;
	//{{AFX_DATA_INIT(CDlgKeyHill10x10)
	m_Verbose = FALSE;
	//}}AFX_DATA_INIT
}


CDlgKeyHill10x10::~CDlgKeyHill10x10()
{
	if(hillklasse) delete hillklasse;
	if(mat) delete mat;
}

void CDlgKeyHill10x10::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyHill10x10)
	DDX_Check(pDX, IDC_CHECK1, m_Verbose);
	DDX_Control(pDX, IDC_EDIT1, m_FeldUnsichtbar);
	DDX_Control(pDX, IDC_EDIT11, m_Feld11);
	DDX_Control(pDX, IDC_EDIT12, m_Feld12);
	DDX_Control(pDX, IDC_EDIT13, m_Feld13);
	DDX_Control(pDX, IDC_EDIT14, m_Feld14);
	DDX_Control(pDX, IDC_EDIT15, m_Feld15);
	DDX_Control(pDX, IDC_EDIT16, m_Feld16);
	DDX_Control(pDX, IDC_EDIT17, m_Feld17);
	DDX_Control(pDX, IDC_EDIT18, m_Feld18);
	DDX_Control(pDX, IDC_EDIT19, m_Feld19);
	DDX_Control(pDX, IDC_EDIT110, m_Feld110);
	DDX_Control(pDX, IDC_EDIT21, m_Feld21);
	DDX_Control(pDX, IDC_EDIT22, m_Feld22);
	DDX_Control(pDX, IDC_EDIT23, m_Feld23);
	DDX_Control(pDX, IDC_EDIT24, m_Feld24);
	DDX_Control(pDX, IDC_EDIT25, m_Feld25);
	DDX_Control(pDX, IDC_EDIT26, m_Feld26);
	DDX_Control(pDX, IDC_EDIT27, m_Feld27);
	DDX_Control(pDX, IDC_EDIT28, m_Feld28);
	DDX_Control(pDX, IDC_EDIT29, m_Feld29);
	DDX_Control(pDX, IDC_EDIT210, m_Feld210);
	DDX_Control(pDX, IDC_EDIT31, m_Feld31);
	DDX_Control(pDX, IDC_EDIT32, m_Feld32);
	DDX_Control(pDX, IDC_EDIT33, m_Feld33);
	DDX_Control(pDX, IDC_EDIT34, m_Feld34);
	DDX_Control(pDX, IDC_EDIT35, m_Feld35);
	DDX_Control(pDX, IDC_EDIT36, m_Feld36);
	DDX_Control(pDX, IDC_EDIT37, m_Feld37);
	DDX_Control(pDX, IDC_EDIT38, m_Feld38);
	DDX_Control(pDX, IDC_EDIT39, m_Feld39);
	DDX_Control(pDX, IDC_EDIT310, m_Feld310);
	DDX_Control(pDX, IDC_EDIT41, m_Feld41);
	DDX_Control(pDX, IDC_EDIT42, m_Feld42);
	DDX_Control(pDX, IDC_EDIT43, m_Feld43);
	DDX_Control(pDX, IDC_EDIT44, m_Feld44);
	DDX_Control(pDX, IDC_EDIT45, m_Feld45);
	DDX_Control(pDX, IDC_EDIT46, m_Feld46);
	DDX_Control(pDX, IDC_EDIT47, m_Feld47);
	DDX_Control(pDX, IDC_EDIT48, m_Feld48);
	DDX_Control(pDX, IDC_EDIT49, m_Feld49);
	DDX_Control(pDX, IDC_EDIT410, m_Feld410);
	DDX_Control(pDX, IDC_EDIT51, m_Feld51);
	DDX_Control(pDX, IDC_EDIT52, m_Feld52);
	DDX_Control(pDX, IDC_EDIT53, m_Feld53);
	DDX_Control(pDX, IDC_EDIT54, m_Feld54);
	DDX_Control(pDX, IDC_EDIT55, m_Feld55);
	DDX_Control(pDX, IDC_EDIT56, m_Feld56);
	DDX_Control(pDX, IDC_EDIT57, m_Feld57);
	DDX_Control(pDX, IDC_EDIT58, m_Feld58);
	DDX_Control(pDX, IDC_EDIT59, m_Feld59);
	DDX_Control(pDX, IDC_EDIT510, m_Feld510);
	DDX_Control(pDX, IDC_EDIT61, m_Feld61);
	DDX_Control(pDX, IDC_EDIT62, m_Feld62);
	DDX_Control(pDX, IDC_EDIT63, m_Feld63);
	DDX_Control(pDX, IDC_EDIT64, m_Feld64);
	DDX_Control(pDX, IDC_EDIT65, m_Feld65);
	DDX_Control(pDX, IDC_EDIT66, m_Feld66);
	DDX_Control(pDX, IDC_EDIT67, m_Feld67);
	DDX_Control(pDX, IDC_EDIT68, m_Feld68);
	DDX_Control(pDX, IDC_EDIT69, m_Feld69);
	DDX_Control(pDX, IDC_EDIT610, m_Feld610);
	DDX_Control(pDX, IDC_EDIT71, m_Feld71);
	DDX_Control(pDX, IDC_EDIT72, m_Feld72);
	DDX_Control(pDX, IDC_EDIT73, m_Feld73);
	DDX_Control(pDX, IDC_EDIT74, m_Feld74);
	DDX_Control(pDX, IDC_EDIT75, m_Feld75);
	DDX_Control(pDX, IDC_EDIT76, m_Feld76);
	DDX_Control(pDX, IDC_EDIT77, m_Feld77);
	DDX_Control(pDX, IDC_EDIT78, m_Feld78);
	DDX_Control(pDX, IDC_EDIT79, m_Feld79);
	DDX_Control(pDX, IDC_EDIT710, m_Feld710);
	DDX_Control(pDX, IDC_EDIT81, m_Feld81);
	DDX_Control(pDX, IDC_EDIT82, m_Feld82);
	DDX_Control(pDX, IDC_EDIT83, m_Feld83);
	DDX_Control(pDX, IDC_EDIT84, m_Feld84);
	DDX_Control(pDX, IDC_EDIT85, m_Feld85);
	DDX_Control(pDX, IDC_EDIT86, m_Feld86);
	DDX_Control(pDX, IDC_EDIT87, m_Feld87);
	DDX_Control(pDX, IDC_EDIT88, m_Feld88);
	DDX_Control(pDX, IDC_EDIT89, m_Feld89);
	DDX_Control(pDX, IDC_EDIT810, m_Feld810);
	DDX_Control(pDX, IDC_EDIT91, m_Feld91);
	DDX_Control(pDX, IDC_EDIT92, m_Feld92);
	DDX_Control(pDX, IDC_EDIT93, m_Feld93);
	DDX_Control(pDX, IDC_EDIT94, m_Feld94);
	DDX_Control(pDX, IDC_EDIT95, m_Feld95);
	DDX_Control(pDX, IDC_EDIT96, m_Feld96);
	DDX_Control(pDX, IDC_EDIT97, m_Feld97);
	DDX_Control(pDX, IDC_EDIT98, m_Feld98);
	DDX_Control(pDX, IDC_EDIT99, m_Feld99);
	DDX_Control(pDX, IDC_EDIT910, m_Feld910);
	DDX_Control(pDX, IDC_EDIT101, m_Feld101);
	DDX_Control(pDX, IDC_EDIT102, m_Feld102);
	DDX_Control(pDX, IDC_EDIT103, m_Feld103);
	DDX_Control(pDX, IDC_EDIT104, m_Feld104);
	DDX_Control(pDX, IDC_EDIT105, m_Feld105);
	DDX_Control(pDX, IDC_EDIT106, m_Feld106);
	DDX_Control(pDX, IDC_EDIT107, m_Feld107);
	DDX_Control(pDX, IDC_EDIT108, m_Feld108);
	DDX_Control(pDX, IDC_EDIT109, m_Feld109);
	DDX_Control(pDX, IDC_EDIT1010, m_Feld1010);
	//}}AFX_DATA_MAP


	DDX_Control(pDX, IDC_EDIT40, m_Feld40);
	DDX_Control(pDX, IDC_EDIT50, m_Feld50);
	DDX_Control(pDX, IDC_EDIT20, m_Feld20);
	DDX_Control(pDX, IDC_EDIT90, m_Feld90);
	DDX_Control(pDX, IDC_EDIT100, m_Feld100);
	DDX_Control(pDX, IDC_EDIT117, m_Feld117);
	DDX_Control(pDX, IDC_EDIT118, m_Feld118);
	DDX_Control(pDX, IDC_EDIT119, m_Feld119);
	DDX_Control(pDX, IDC_EDIT60, m_Feld60);
	DDX_Control(pDX, IDC_EDIT125, m_Feld125);
	DDX_Control(pDX, IDC_EDIT127, m_Feld127);
	DDX_Control(pDX, IDC_EDIT134, m_Feld134);
	DDX_Control(pDX, IDC_EDIT135, m_Feld135);
	DDX_Control(pDX, IDC_EDIT136, m_Feld136);
	DDX_Control(pDX, IDC_EDIT70, m_Feld70);
	DDX_Control(pDX, IDC_EDIT137, m_Feld137);
	DDX_Control(pDX, IDC_EDIT138, m_Feld138);
	DDX_Control(pDX, IDC_EDIT139, m_Feld139);
	DDX_Control(pDX, IDC_EDIT80, m_Feld80);
	DDX_Control(pDX, IDC_EDIT211, m_Feld211);
	DDX_Control(pDX, IDC_EDIT140, m_Feld140);
	DDX_Control(pDX, IDC_EDIT141, m_Feld141);
	DDX_Control(pDX, IDC_EDIT142, m_Feld142);
	DDX_Control(pDX, IDC_EDIT143, m_Feld143);
	DDX_Control(pDX, IDC_EDIT144, m_Feld144);
	DDX_Control(pDX, IDC_EDIT145, m_Feld145);
	DDX_Control(pDX, IDC_EDIT146, m_Feld146);
	DDX_Control(pDX, IDC_EDIT147, m_Feld147);
	DDX_Control(pDX, IDC_EDIT148, m_Feld148);
	DDX_Control(pDX, IDC_EDIT311, m_Feld311);
	DDX_Control(pDX, IDC_EDIT149, m_Feld149);
	DDX_Control(pDX, IDC_EDIT150, m_Feld150);
	DDX_Control(pDX, IDC_EDIT151, m_Feld151);
	DDX_Control(pDX, IDC_EDIT152, m_Feld152);
	DDX_Control(pDX, IDC_EDIT153, m_Feld153);
	DDX_Control(pDX, IDC_EDIT154, m_Feld154);
	DDX_Control(pDX, IDC_EDIT155, m_Feld155);
	DDX_Control(pDX, IDC_EDIT156, m_Feld156);
	DDX_Control(pDX, IDC_EDIT157, m_Feld157);
	DDX_Control(pDX, IDC_EDIT411, m_Feld411);
	DDX_Control(pDX, IDC_EDIT158, m_Feld158);
	DDX_Control(pDX, IDC_EDIT159, m_Feld159);
	DDX_Control(pDX, IDC_EDIT113, m_Feld113);
	DDX_Control(pDX, IDC_EDIT160, m_Feld160);
	DDX_Control(pDX, IDC_EDIT161, m_Feld161);
	DDX_Control(pDX, IDC_EDIT162, m_Feld162);
	DDX_Control(pDX, IDC_EDIT163, m_Feld163);
	DDX_Control(pDX, IDC_EDIT164, m_Feld164);
	DDX_Control(pDX, IDC_EDIT165, m_Feld165);
	DDX_Control(pDX, IDC_EDIT511, m_Feld511);
	DDX_Control(pDX, IDC_EDIT166, m_Feld166);
	DDX_Control(pDX, IDC_EDIT167, m_Feld167);
	DDX_Control(pDX, IDC_EDIT168, m_Feld168);
	DDX_Control(pDX, IDC_EDIT169, m_Feld169);
	DDX_Control(pDX, IDC_EDIT170, m_Feld170);
	DDX_Control(pDX, IDC_EDIT171, m_Feld171);
	DDX_Control(pDX, IDC_EDIT172, m_Feld172);
	DDX_Control(pDX, IDC_EDIT173, m_Feld173);
	DDX_Control(pDX, IDC_EDIT174, m_Feld174);
	DDX_Control(pDX, IDC_EDIT611, m_Feld611);
	DDX_Control(pDX, IDC_EDIT175, m_Feld175);
	DDX_Control(pDX, IDC_EDIT176, m_Feld176);
	DDX_Control(pDX, IDC_EDIT177, m_Feld177);
	DDX_Control(pDX, IDC_EDIT178, m_Feld178);
	DDX_Control(pDX, IDC_EDIT179, m_Feld179);
	DDX_Control(pDX, IDC_EDIT180, m_Feld180);
	DDX_Control(pDX, IDC_EDIT181, m_Feld181);
	DDX_Control(pDX, IDC_EDIT182, m_Feld182);
	DDX_Control(pDX, IDC_EDIT183, m_Feld183);
	DDX_Control(pDX, IDC_EDIT711, m_Feld711);
	DDX_Control(pDX, IDC_EDIT184, m_Feld184);
	DDX_Control(pDX, IDC_EDIT185, m_Feld185);
	DDX_Control(pDX, IDC_EDIT186, m_Feld186);
	DDX_Control(pDX, IDC_EDIT187, m_Feld187);
	DDX_Control(pDX, IDC_EDIT188, m_Feld188);
	DDX_Control(pDX, IDC_EDIT189, m_Feld189);
	DDX_Control(pDX, IDC_EDIT190, m_Feld190);
	DDX_Control(pDX, IDC_EDIT191, m_Feld191);
	DDX_Control(pDX, IDC_EDIT192, m_Feld192);
	DDX_Control(pDX, IDC_EDIT811, m_Feld811);
	DDX_Control(pDX, IDC_EDIT193, m_Feld193);
	DDX_Control(pDX, IDC_EDIT194, m_Feld194);
	DDX_Control(pDX, IDC_EDIT195, m_Feld195);
	DDX_Control(pDX, IDC_EDIT196, m_Feld196);
	DDX_Control(pDX, IDC_EDIT197, m_Feld197);
	DDX_Control(pDX, IDC_EDIT198, m_Feld198);
	DDX_Control(pDX, IDC_EDIT199, m_Feld199);
	DDX_Control(pDX, IDC_EDIT200, m_Feld200);
	DDX_Control(pDX, IDC_EDIT201, m_Feld201);
	DDX_Control(pDX, IDC_EDIT911, m_Feld911);
	DDX_Control(pDX, IDC_EDIT202, m_Feld202);
	DDX_Control(pDX, IDC_EDIT203, m_Feld203);
	DDX_Control(pDX, IDC_EDIT204, m_Feld204);
	DDX_Control(pDX, IDC_EDIT205, m_Feld205);
	DDX_Control(pDX, IDC_EDIT206, m_Feld206);
	DDX_Control(pDX, IDC_EDIT207, m_Feld207);
	DDX_Control(pDX, IDC_EDIT208, m_Feld208);
	DDX_Control(pDX, IDC_EDIT209, m_Feld209);
	DDX_Control(pDX, IDC_EDIT212, m_Feld212);
	DDX_Control(pDX, IDC_EDIT1011, m_Feld1011);

	DDX_Text(pDX, IDC_EDIT3, m_pHillAlphInfo);
}


BEGIN_MESSAGE_MAP(CDlgKeyHill10x10, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyHill10x10)
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

	ON_BN_CLICKED(IDC_RADIO21, OnDisableAlphCode)
	ON_BN_CLICKED(IDC_RADIO22, OnEnableAlphCode)
	ON_BN_CLICKED(IDC_RADIO23, OnRowVectorMatrix)
	ON_BN_CLICKED(IDC_RADIO24, OnMatrixColumnVector)

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


	ON_BN_CLICKED(IDC_BUTTON3, OnZufaelligerSchluessel)
	ON_BN_CLICKED(IDC_BUTTON4, OnKleinereSchluessel)
	ON_BN_CLICKED(IDC_BUTTON5, OnDecrypt)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)

	ON_BN_CLICKED(IDC_BUTTON_TEXTOPTIONS, OnTextOptions)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON69, OnBnClickedButton69)
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyHill10x10 

void CDlgKeyHill10x10::OnUpdateMat11() 
{
	// TODO: Wenn es sich hierbei um ein RICHEDIT-Steuerelement handelt, sendet es
	// sendet diese Benachrichtigung nur, wenn die Funktion CDialog::OnInitDialog()
	// überschrieben wird, um die EM_SETEVENTMASK-Nachricht an das Steuerelement
	// mit dem ENM_UPDATE-Attribut Ored in die Maske lParam zu senden.
	
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	UpdateFeld(m_pFelder[0][0]);
	setFeldAlphCode(m_pFelder[0][0],m_pAlphCode[0][0]);
}
void CDlgKeyHill10x10::OnUpdateMat12() 
{
	UpdateFeld(m_pFelder[0][1]);
	setFeldAlphCode(m_pFelder[0][1],m_pAlphCode[0][1]);
}
void CDlgKeyHill10x10::OnUpdateMat13()
{
	UpdateFeld(m_pFelder[0][2]);
	setFeldAlphCode(m_pFelder[0][2],m_pAlphCode[0][2]);
}
void CDlgKeyHill10x10::OnUpdateMat14()
{
	UpdateFeld(m_pFelder[0][3]);
	setFeldAlphCode(m_pFelder[0][3],m_pAlphCode[0][3]);
}
void CDlgKeyHill10x10::OnUpdateMat15()
{
	UpdateFeld(m_pFelder[0][4]);
	setFeldAlphCode(m_pFelder[0][4],m_pAlphCode[0][4]);
}
void CDlgKeyHill10x10::OnUpdateMat16()
{
	UpdateFeld(m_pFelder[0][5]);
	setFeldAlphCode(m_pFelder[0][5],m_pAlphCode[0][5]);
}
void CDlgKeyHill10x10::OnUpdateMat17()
{
	UpdateFeld(m_pFelder[0][6]);
	setFeldAlphCode(m_pFelder[0][6],m_pAlphCode[0][6]);
}
void CDlgKeyHill10x10::OnUpdateMat18()
{
	UpdateFeld(m_pFelder[0][7]);
	setFeldAlphCode(m_pFelder[0][7],m_pAlphCode[0][7]);
}
void CDlgKeyHill10x10::OnUpdateMat19()
{
	UpdateFeld(m_pFelder[0][8]);
	setFeldAlphCode(m_pFelder[0][8],m_pAlphCode[0][8]);
}
void CDlgKeyHill10x10::OnUpdateMat110()
{
	UpdateFeld(m_pFelder[0][9]);
	setFeldAlphCode(m_pFelder[0][9],m_pAlphCode[0][9]);
}
void CDlgKeyHill10x10::OnUpdateMat21()
{
	UpdateFeld(m_pFelder[1][0]);
	setFeldAlphCode(m_pFelder[1][0],m_pAlphCode[1][0]);
}
void CDlgKeyHill10x10::OnUpdateMat22()
{
	UpdateFeld(m_pFelder[1][1]);
	setFeldAlphCode(m_pFelder[1][1],m_pAlphCode[1][1]);
}
void CDlgKeyHill10x10::OnUpdateMat23()
{
	UpdateFeld(m_pFelder[1][2]);
	setFeldAlphCode(m_pFelder[1][2],m_pAlphCode[1][2]);
}
void CDlgKeyHill10x10::OnUpdateMat24()
{
	UpdateFeld(m_pFelder[1][3]);
	setFeldAlphCode(m_pFelder[1][3],m_pAlphCode[1][3]);
}
void CDlgKeyHill10x10::OnUpdateMat25()
{
	UpdateFeld(m_pFelder[1][4]);
	setFeldAlphCode(m_pFelder[1][4],m_pAlphCode[1][4]);
}
void CDlgKeyHill10x10::OnUpdateMat26()
{
	UpdateFeld(m_pFelder[1][5]);
	setFeldAlphCode(m_pFelder[1][5],m_pAlphCode[1][5]);
}
void CDlgKeyHill10x10::OnUpdateMat27()
{
	UpdateFeld(m_pFelder[1][6]);
	setFeldAlphCode(m_pFelder[1][6],m_pAlphCode[1][6]);
}
void CDlgKeyHill10x10::OnUpdateMat28()
{
	UpdateFeld(m_pFelder[1][7]);
	setFeldAlphCode(m_pFelder[1][7],m_pAlphCode[1][7]);
}
void CDlgKeyHill10x10::OnUpdateMat29()
{
	UpdateFeld(m_pFelder[1][8]);
	setFeldAlphCode(m_pFelder[1][8],m_pAlphCode[1][8]);
}
void CDlgKeyHill10x10::OnUpdateMat210()
{
	UpdateFeld(m_pFelder[1][9]);
	setFeldAlphCode(m_pFelder[1][9],m_pAlphCode[1][9]);
}
void CDlgKeyHill10x10::OnUpdateMat31()
{
	UpdateFeld(m_pFelder[2][0]);
	setFeldAlphCode(m_pFelder[2][0],m_pAlphCode[2][0]);
}
void CDlgKeyHill10x10::OnUpdateMat32()
{
	UpdateFeld(m_pFelder[2][1]);
	setFeldAlphCode(m_pFelder[2][1],m_pAlphCode[2][1]);
}
void CDlgKeyHill10x10::OnUpdateMat33()
{
	UpdateFeld(m_pFelder[2][2]);
	setFeldAlphCode(m_pFelder[2][2],m_pAlphCode[2][2]);
}
void CDlgKeyHill10x10::OnUpdateMat34()
{
	UpdateFeld(m_pFelder[2][3]);
	setFeldAlphCode(m_pFelder[2][3],m_pAlphCode[2][3]);
}
void CDlgKeyHill10x10::OnUpdateMat35()
{
	UpdateFeld(m_pFelder[2][4]);
	setFeldAlphCode(m_pFelder[2][4],m_pAlphCode[2][4]);
}
void CDlgKeyHill10x10::OnUpdateMat36()
{
	UpdateFeld(m_pFelder[2][5]);
	setFeldAlphCode(m_pFelder[2][5],m_pAlphCode[2][5]);
}
void CDlgKeyHill10x10::OnUpdateMat37()
{
	UpdateFeld(m_pFelder[2][6]);
	setFeldAlphCode(m_pFelder[2][6],m_pAlphCode[2][6]);
}
void CDlgKeyHill10x10::OnUpdateMat38()
{
	UpdateFeld(m_pFelder[2][7]);
	setFeldAlphCode(m_pFelder[2][7],m_pAlphCode[2][7]);
}
void CDlgKeyHill10x10::OnUpdateMat39()
{
	UpdateFeld(m_pFelder[2][8]);
	setFeldAlphCode(m_pFelder[2][8],m_pAlphCode[2][8]);
}
void CDlgKeyHill10x10::OnUpdateMat310()
{
	UpdateFeld(m_pFelder[2][9]);
	setFeldAlphCode(m_pFelder[2][9],m_pAlphCode[2][9]);
}
void CDlgKeyHill10x10::OnUpdateMat41()
{
	UpdateFeld(m_pFelder[3][0]);
	setFeldAlphCode(m_pFelder[3][0],m_pAlphCode[3][0]);
}
void CDlgKeyHill10x10::OnUpdateMat42()
{
	UpdateFeld(m_pFelder[3][1]);
	setFeldAlphCode(m_pFelder[3][1],m_pAlphCode[3][1]);
}
void CDlgKeyHill10x10::OnUpdateMat43()
{
	UpdateFeld(m_pFelder[3][2]);
	setFeldAlphCode(m_pFelder[3][2],m_pAlphCode[3][2]);
}
void CDlgKeyHill10x10::OnUpdateMat44()
{
	UpdateFeld(m_pFelder[3][3]);
	setFeldAlphCode(m_pFelder[3][3],m_pAlphCode[3][3]);
}
void CDlgKeyHill10x10::OnUpdateMat45()
{
	UpdateFeld(m_pFelder[3][4]);
	setFeldAlphCode(m_pFelder[3][4],m_pAlphCode[3][4]);
}
void CDlgKeyHill10x10::OnUpdateMat46()
{
	UpdateFeld(m_pFelder[3][5]);
	setFeldAlphCode(m_pFelder[3][5],m_pAlphCode[3][5]);
}
void CDlgKeyHill10x10::OnUpdateMat47()
{
	UpdateFeld(m_pFelder[3][6]);
	setFeldAlphCode(m_pFelder[3][6],m_pAlphCode[3][6]);
}
void CDlgKeyHill10x10::OnUpdateMat48()
{
	UpdateFeld(m_pFelder[3][7]);
	setFeldAlphCode(m_pFelder[3][7],m_pAlphCode[3][7]);
}
void CDlgKeyHill10x10::OnUpdateMat49()
{
	UpdateFeld(m_pFelder[3][8]);
	setFeldAlphCode(m_pFelder[3][8],m_pAlphCode[3][8]);
}
void CDlgKeyHill10x10::OnUpdateMat410()
{
	UpdateFeld(m_pFelder[3][9]);
	setFeldAlphCode(m_pFelder[3][9],m_pAlphCode[3][9]);
}
void CDlgKeyHill10x10::OnUpdateMat51()
{
	UpdateFeld(m_pFelder[4][0]);
	setFeldAlphCode(m_pFelder[4][0],m_pAlphCode[4][0]);
}
void CDlgKeyHill10x10::OnUpdateMat52()
{
	UpdateFeld(m_pFelder[4][1]);
	setFeldAlphCode(m_pFelder[4][1],m_pAlphCode[4][1]);
}
void CDlgKeyHill10x10::OnUpdateMat53()
{
	UpdateFeld(m_pFelder[4][2]);
	setFeldAlphCode(m_pFelder[4][2],m_pAlphCode[4][2]);
}
void CDlgKeyHill10x10::OnUpdateMat54()
{
	UpdateFeld(m_pFelder[4][3]);
	setFeldAlphCode(m_pFelder[4][3],m_pAlphCode[4][3]);
}
void CDlgKeyHill10x10::OnUpdateMat55()
{
	UpdateFeld(m_pFelder[4][4]);
	setFeldAlphCode(m_pFelder[4][4],m_pAlphCode[4][4]);
}
void CDlgKeyHill10x10::OnUpdateMat56()
{
	UpdateFeld(m_pFelder[4][5]);
	setFeldAlphCode(m_pFelder[4][5],m_pAlphCode[4][5]);
}
void CDlgKeyHill10x10::OnUpdateMat57()
{
	UpdateFeld(m_pFelder[4][6]);
	setFeldAlphCode(m_pFelder[4][6],m_pAlphCode[4][6]);
}
void CDlgKeyHill10x10::OnUpdateMat58()
{
	UpdateFeld(m_pFelder[4][7]);
	setFeldAlphCode(m_pFelder[4][7],m_pAlphCode[4][7]);
}
void CDlgKeyHill10x10::OnUpdateMat59()
{
	UpdateFeld(m_pFelder[4][8]);
	setFeldAlphCode(m_pFelder[4][8],m_pAlphCode[4][8]);
}
void CDlgKeyHill10x10::OnUpdateMat510()
{
	UpdateFeld(m_pFelder[4][9]);
	setFeldAlphCode(m_pFelder[4][9],m_pAlphCode[4][9]);
}
void CDlgKeyHill10x10::OnUpdateMat61()
{
	UpdateFeld(m_pFelder[5][0]);
	setFeldAlphCode(m_pFelder[5][0],m_pAlphCode[5][0]);
}
void CDlgKeyHill10x10::OnUpdateMat62()
{
	UpdateFeld(m_pFelder[5][1]);
	setFeldAlphCode(m_pFelder[5][1],m_pAlphCode[5][1]);
}
void CDlgKeyHill10x10::OnUpdateMat63()
{
	UpdateFeld(m_pFelder[5][2]);
	setFeldAlphCode(m_pFelder[5][2],m_pAlphCode[5][2]);
}
void CDlgKeyHill10x10::OnUpdateMat64()
{
	UpdateFeld(m_pFelder[5][3]);
	setFeldAlphCode(m_pFelder[5][3],m_pAlphCode[5][3]);
}
void CDlgKeyHill10x10::OnUpdateMat65()
{
	UpdateFeld(m_pFelder[5][4]);
	setFeldAlphCode(m_pFelder[5][4],m_pAlphCode[5][4]);
}
void CDlgKeyHill10x10::OnUpdateMat66()
{
	UpdateFeld(m_pFelder[5][5]);
	setFeldAlphCode(m_pFelder[5][5],m_pAlphCode[5][5]);
}
void CDlgKeyHill10x10::OnUpdateMat67()
{
	UpdateFeld(m_pFelder[5][6]);
	setFeldAlphCode(m_pFelder[5][6],m_pAlphCode[5][6]);
}
void CDlgKeyHill10x10::OnUpdateMat68()
{
	UpdateFeld(m_pFelder[5][7]);
	setFeldAlphCode(m_pFelder[5][7],m_pAlphCode[5][7]);
}
void CDlgKeyHill10x10::OnUpdateMat69()
{
	UpdateFeld(m_pFelder[5][8]);
	setFeldAlphCode(m_pFelder[5][8],m_pAlphCode[5][8]);
}
void CDlgKeyHill10x10::OnUpdateMat610()
{
	UpdateFeld(m_pFelder[5][9]);
	setFeldAlphCode(m_pFelder[5][9],m_pAlphCode[5][9]);
}
void CDlgKeyHill10x10::OnUpdateMat71()
{
	UpdateFeld(m_pFelder[6][0]);
	setFeldAlphCode(m_pFelder[6][0],m_pAlphCode[6][0]);
}
void CDlgKeyHill10x10::OnUpdateMat72()
{
	UpdateFeld(m_pFelder[6][1]);
	setFeldAlphCode(m_pFelder[6][1],m_pAlphCode[6][1]);
}
void CDlgKeyHill10x10::OnUpdateMat73()
{
	UpdateFeld(m_pFelder[6][2]);
	setFeldAlphCode(m_pFelder[6][2],m_pAlphCode[6][2]);
}
void CDlgKeyHill10x10::OnUpdateMat74()
{
	UpdateFeld(m_pFelder[6][3]);
	setFeldAlphCode(m_pFelder[6][3],m_pAlphCode[6][3]);
}
void CDlgKeyHill10x10::OnUpdateMat75()
{
	UpdateFeld(m_pFelder[6][4]);
	setFeldAlphCode(m_pFelder[6][4],m_pAlphCode[6][4]);
}
void CDlgKeyHill10x10::OnUpdateMat76()
{
	UpdateFeld(m_pFelder[6][5]);
	setFeldAlphCode(m_pFelder[6][5],m_pAlphCode[6][5]);
}
void CDlgKeyHill10x10::OnUpdateMat77()
{
	UpdateFeld(m_pFelder[6][6]);
	setFeldAlphCode(m_pFelder[6][6],m_pAlphCode[6][6]);
}
void CDlgKeyHill10x10::OnUpdateMat78()
{
	UpdateFeld(m_pFelder[6][7]);
	setFeldAlphCode(m_pFelder[6][7],m_pAlphCode[6][7]);
}
void CDlgKeyHill10x10::OnUpdateMat79()
{
	UpdateFeld(m_pFelder[6][8]);
	setFeldAlphCode(m_pFelder[6][8],m_pAlphCode[6][8]);
}
void CDlgKeyHill10x10::OnUpdateMat710()
{
	UpdateFeld(m_pFelder[6][9]);
	setFeldAlphCode(m_pFelder[6][9],m_pAlphCode[6][9]);
}
void CDlgKeyHill10x10::OnUpdateMat81()
{
	UpdateFeld(m_pFelder[7][0]);
	setFeldAlphCode(m_pFelder[7][0],m_pAlphCode[7][0]);
}
void CDlgKeyHill10x10::OnUpdateMat82()
{
	UpdateFeld(m_pFelder[7][1]);
	setFeldAlphCode(m_pFelder[7][1],m_pAlphCode[7][1]);
}
void CDlgKeyHill10x10::OnUpdateMat83()
{
	UpdateFeld(m_pFelder[7][2]);
	setFeldAlphCode(m_pFelder[7][2],m_pAlphCode[7][2]);
}
void CDlgKeyHill10x10::OnUpdateMat84()
{
	UpdateFeld(m_pFelder[7][3]);
	setFeldAlphCode(m_pFelder[7][3],m_pAlphCode[7][3]);
}
void CDlgKeyHill10x10::OnUpdateMat85()
{
	UpdateFeld(m_pFelder[7][4]);
	setFeldAlphCode(m_pFelder[7][4],m_pAlphCode[7][4]);
}
void CDlgKeyHill10x10::OnUpdateMat86()
{
	UpdateFeld(m_pFelder[7][5]);
	setFeldAlphCode(m_pFelder[7][5],m_pAlphCode[7][5]);
}
void CDlgKeyHill10x10::OnUpdateMat87()
{
	UpdateFeld(m_pFelder[7][6]);
	setFeldAlphCode(m_pFelder[7][6],m_pAlphCode[7][6]);
}
void CDlgKeyHill10x10::OnUpdateMat88()
{
	UpdateFeld(m_pFelder[7][7]);
	setFeldAlphCode(m_pFelder[7][7],m_pAlphCode[7][7]);
}
void CDlgKeyHill10x10::OnUpdateMat89()
{
	UpdateFeld(m_pFelder[7][8]);
	setFeldAlphCode(m_pFelder[7][8],m_pAlphCode[7][8]);
}
void CDlgKeyHill10x10::OnUpdateMat810()
{
	UpdateFeld(m_pFelder[7][9]);
	setFeldAlphCode(m_pFelder[7][9],m_pAlphCode[7][9]);
}
void CDlgKeyHill10x10::OnUpdateMat91()
{
	UpdateFeld(m_pFelder[8][0]);
	setFeldAlphCode(m_pFelder[8][0],m_pAlphCode[8][0]);
}
void CDlgKeyHill10x10::OnUpdateMat92()
{
	UpdateFeld(m_pFelder[8][1]);
	setFeldAlphCode(m_pFelder[8][1],m_pAlphCode[8][1]);
}
void CDlgKeyHill10x10::OnUpdateMat93()
{
	UpdateFeld(m_pFelder[8][2]);
	setFeldAlphCode(m_pFelder[8][2],m_pAlphCode[8][2]);
}
void CDlgKeyHill10x10::OnUpdateMat94()
{
	UpdateFeld(m_pFelder[8][3]);
	setFeldAlphCode(m_pFelder[8][3],m_pAlphCode[8][3]);
}
void CDlgKeyHill10x10::OnUpdateMat95()
{
	UpdateFeld(m_pFelder[8][4]);
	setFeldAlphCode(m_pFelder[8][4],m_pAlphCode[8][4]);
}
void CDlgKeyHill10x10::OnUpdateMat96()
{
	UpdateFeld(m_pFelder[8][5]);
	setFeldAlphCode(m_pFelder[8][5],m_pAlphCode[8][5]);
}
void CDlgKeyHill10x10::OnUpdateMat97()
{
	UpdateFeld(m_pFelder[8][6]);
	setFeldAlphCode(m_pFelder[8][6],m_pAlphCode[8][6]);
}
void CDlgKeyHill10x10::OnUpdateMat98()
{
	UpdateFeld(m_pFelder[8][7]);
	setFeldAlphCode(m_pFelder[8][7],m_pAlphCode[8][7]);
}
void CDlgKeyHill10x10::OnUpdateMat99()
{
	UpdateFeld(m_pFelder[8][8]);
	setFeldAlphCode(m_pFelder[8][8],m_pAlphCode[8][8]);
}
void CDlgKeyHill10x10::OnUpdateMat910()
{
	UpdateFeld(m_pFelder[8][9]);
	setFeldAlphCode(m_pFelder[8][9],m_pAlphCode[8][9]);
}
void CDlgKeyHill10x10::OnUpdateMat101()
{
	UpdateFeld(m_pFelder[9][0]);
	setFeldAlphCode(m_pFelder[9][0],m_pAlphCode[9][0]);
}
void CDlgKeyHill10x10::OnUpdateMat102()
{
	UpdateFeld(m_pFelder[9][1]);
	setFeldAlphCode(m_pFelder[9][1],m_pAlphCode[9][1]);
}
void CDlgKeyHill10x10::OnUpdateMat103()
{
	UpdateFeld(m_pFelder[9][2]);
	setFeldAlphCode(m_pFelder[9][2],m_pAlphCode[9][2]);
}
void CDlgKeyHill10x10::OnUpdateMat104()
{
	UpdateFeld(m_pFelder[9][3]);
	setFeldAlphCode(m_pFelder[9][3],m_pAlphCode[9][3]);
}
void CDlgKeyHill10x10::OnUpdateMat105()
{
	UpdateFeld(m_pFelder[9][4]);
	setFeldAlphCode(m_pFelder[9][4],m_pAlphCode[9][4]);
}
void CDlgKeyHill10x10::OnUpdateMat106()
{
	UpdateFeld(m_pFelder[9][5]);
	setFeldAlphCode(m_pFelder[9][5],m_pAlphCode[9][5]);
}
void CDlgKeyHill10x10::OnUpdateMat107()
{
	UpdateFeld(m_pFelder[9][6]);
	setFeldAlphCode(m_pFelder[9][6],m_pAlphCode[9][6]);
}
void CDlgKeyHill10x10::OnUpdateMat108()
{
	UpdateFeld(m_pFelder[9][7]);
	setFeldAlphCode(m_pFelder[9][7],m_pAlphCode[9][7]);
}
void CDlgKeyHill10x10::OnUpdateMat109()
{
	UpdateFeld(m_pFelder[9][8]);
	setFeldAlphCode(m_pFelder[9][8],m_pAlphCode[9][8]);
}
void CDlgKeyHill10x10::OnUpdateMat1010()
{
	UpdateFeld(m_pFelder[9][9]);
	setFeldAlphCode(m_pFelder[9][9],m_pAlphCode[9][9]);
}
////////////////////////////////
void CDlgKeyHill10x10::OnUpdateMat40()
{
	UpdateAlphCode(m_pAlphCode[0][0]);
	setFeldAlph(m_pFelder[0][0],m_pAlphCode[0][0]);
}
void CDlgKeyHill10x10::OnUpdateMat50()
{
	UpdateAlphCode(m_pAlphCode[0][1]);
	setFeldAlph(m_pFelder[0][1],m_pAlphCode[0][1]);
}
void CDlgKeyHill10x10::OnUpdateMat20()
{
	UpdateAlphCode(m_pAlphCode[0][2]);
	setFeldAlph(m_pFelder[0][2],m_pAlphCode[0][2]);
}
void CDlgKeyHill10x10::OnUpdateMat90()
{
	UpdateAlphCode(m_pAlphCode[0][3]);
	setFeldAlph(m_pFelder[0][3],m_pAlphCode[0][3]);
}
void CDlgKeyHill10x10::OnUpdateMat100()
{
	UpdateAlphCode(m_pAlphCode[0][4]);
	setFeldAlph(m_pFelder[0][4],m_pAlphCode[0][4]);
}
void CDlgKeyHill10x10::OnUpdateMat117()
{
	UpdateAlphCode(m_pAlphCode[0][5]);
	setFeldAlph(m_pFelder[0][5],m_pAlphCode[0][5]);
}
void CDlgKeyHill10x10::OnUpdateMat118()
{
	UpdateAlphCode(m_pAlphCode[0][6]);
	setFeldAlph(m_pFelder[0][6],m_pAlphCode[0][6]);
}
void CDlgKeyHill10x10::OnUpdateMat119()
{
	UpdateAlphCode(m_pAlphCode[0][7]);
	setFeldAlph(m_pFelder[0][7],m_pAlphCode[0][7]);
}
void CDlgKeyHill10x10::OnUpdateMat60()
{
	UpdateAlphCode(m_pAlphCode[0][8]);
	setFeldAlph(m_pFelder[0][8],m_pAlphCode[0][8]);
}
void CDlgKeyHill10x10::OnUpdateMat125()
{
	UpdateAlphCode(m_pAlphCode[0][9]);
	setFeldAlph(m_pFelder[0][9],m_pAlphCode[0][9]);
}
void CDlgKeyHill10x10::OnUpdateMat127()
{
	UpdateAlphCode(m_pAlphCode[1][0]);
	setFeldAlph(m_pFelder[1][0],m_pAlphCode[1][0]);
}
void CDlgKeyHill10x10::OnUpdateMat134()
{
	UpdateAlphCode(m_pAlphCode[1][1]);
	setFeldAlph(m_pFelder[1][1],m_pAlphCode[1][1]);
}
void CDlgKeyHill10x10::OnUpdateMat135()
{
	UpdateAlphCode(m_pAlphCode[1][2]);
	setFeldAlph(m_pFelder[1][2],m_pAlphCode[1][2]);
}
void CDlgKeyHill10x10::OnUpdateMat136()
{
	UpdateAlphCode(m_pAlphCode[1][3]);
	setFeldAlph(m_pFelder[1][3],m_pAlphCode[1][3]);
}
void CDlgKeyHill10x10::OnUpdateMat70()
{
	UpdateAlphCode(m_pAlphCode[1][4]);
	setFeldAlph(m_pFelder[1][4],m_pAlphCode[1][4]);
}
void CDlgKeyHill10x10::OnUpdateMat137()
{
	UpdateAlphCode(m_pAlphCode[1][5]);
	setFeldAlph(m_pFelder[1][5],m_pAlphCode[1][5]);
}
void CDlgKeyHill10x10::OnUpdateMat138()
{
	UpdateAlphCode(m_pAlphCode[1][6]);
	setFeldAlph(m_pFelder[1][6],m_pAlphCode[1][6]);
}
void CDlgKeyHill10x10::OnUpdateMat139()
{
	UpdateAlphCode(m_pAlphCode[1][7]);
	setFeldAlph(m_pFelder[1][7],m_pAlphCode[1][7]);
}
void CDlgKeyHill10x10::OnUpdateMat80()
{
	UpdateAlphCode(m_pAlphCode[1][8]);
	setFeldAlph(m_pFelder[1][8],m_pAlphCode[1][8]);
}
void CDlgKeyHill10x10::OnUpdateMat211()
{
	UpdateAlphCode(m_pAlphCode[1][9]);
	setFeldAlph(m_pFelder[1][9],m_pAlphCode[1][9]);
}
void CDlgKeyHill10x10::OnUpdateMat140()
{
	UpdateAlphCode(m_pAlphCode[2][0]);
	setFeldAlph(m_pFelder[2][0],m_pAlphCode[2][0]);
}
void CDlgKeyHill10x10::OnUpdateMat141()
{
	UpdateAlphCode(m_pAlphCode[2][1]);
	setFeldAlph(m_pFelder[2][1],m_pAlphCode[2][1]);
}
void CDlgKeyHill10x10::OnUpdateMat142()
{
	UpdateAlphCode(m_pAlphCode[2][2]);
	setFeldAlph(m_pFelder[2][2],m_pAlphCode[2][2]);
}
void CDlgKeyHill10x10::OnUpdateMat143()
{
	UpdateAlphCode(m_pAlphCode[2][3]);
	setFeldAlph(m_pFelder[2][3],m_pAlphCode[2][3]);
}
void CDlgKeyHill10x10::OnUpdateMat144()
{
	UpdateAlphCode(m_pAlphCode[2][4]);
	setFeldAlph(m_pFelder[2][4],m_pAlphCode[2][4]);
}
void CDlgKeyHill10x10::OnUpdateMat145()
{
	UpdateAlphCode(m_pAlphCode[2][5]);
	setFeldAlph(m_pFelder[2][5],m_pAlphCode[2][5]);
}
void CDlgKeyHill10x10::OnUpdateMat146()
{
	UpdateAlphCode(m_pAlphCode[2][6]);
	setFeldAlph(m_pFelder[2][6],m_pAlphCode[2][6]);
}
void CDlgKeyHill10x10::OnUpdateMat147()
{
	UpdateAlphCode(m_pAlphCode[2][7]);
	setFeldAlph(m_pFelder[2][7],m_pAlphCode[2][7]);
}
void CDlgKeyHill10x10::OnUpdateMat148()
{
	UpdateAlphCode(m_pAlphCode[2][8]);
	setFeldAlph(m_pFelder[2][8],m_pAlphCode[2][8]);
}
void CDlgKeyHill10x10::OnUpdateMat311()
{
	UpdateAlphCode(m_pAlphCode[2][9]);
	setFeldAlph(m_pFelder[2][9],m_pAlphCode[2][9]);
}
void CDlgKeyHill10x10::OnUpdateMat149()
{
	UpdateAlphCode(m_pAlphCode[3][0]);
	setFeldAlph(m_pFelder[3][0],m_pAlphCode[3][0]);
}
void CDlgKeyHill10x10::OnUpdateMat150()
{
	UpdateAlphCode(m_pAlphCode[3][1]);
	setFeldAlph(m_pFelder[3][1],m_pAlphCode[3][1]);
}
void CDlgKeyHill10x10::OnUpdateMat151()
{
	UpdateAlphCode(m_pAlphCode[3][2]);
	setFeldAlph(m_pFelder[3][2],m_pAlphCode[3][2]);
}
void CDlgKeyHill10x10::OnUpdateMat152()
{
	UpdateAlphCode(m_pAlphCode[3][3]);
	setFeldAlph(m_pFelder[3][3],m_pAlphCode[3][3]);
}
void CDlgKeyHill10x10::OnUpdateMat153()
{
	UpdateAlphCode(m_pAlphCode[3][4]);
	setFeldAlph(m_pFelder[3][4],m_pAlphCode[3][4]);
}
void CDlgKeyHill10x10::OnUpdateMat154()
{
	UpdateAlphCode(m_pAlphCode[3][5]);
	setFeldAlph(m_pFelder[3][5],m_pAlphCode[3][5]);
}
void CDlgKeyHill10x10::OnUpdateMat155()
{
	UpdateAlphCode(m_pAlphCode[3][6]);
	setFeldAlph(m_pFelder[3][6],m_pAlphCode[3][6]);
}
void CDlgKeyHill10x10::OnUpdateMat156()
{
	UpdateAlphCode(m_pAlphCode[3][7]);
	setFeldAlph(m_pFelder[3][7],m_pAlphCode[3][7]);
}
void CDlgKeyHill10x10::OnUpdateMat157()
{
	UpdateAlphCode(m_pAlphCode[3][8]);
	setFeldAlph(m_pFelder[3][8],m_pAlphCode[3][8]);
}
void CDlgKeyHill10x10::OnUpdateMat411()
{
	UpdateAlphCode(m_pAlphCode[3][9]);
	setFeldAlph(m_pFelder[3][9],m_pAlphCode[3][9]);
}
void CDlgKeyHill10x10::OnUpdateMat158()
{
	UpdateAlphCode(m_pAlphCode[4][0]);
	setFeldAlph(m_pFelder[4][0],m_pAlphCode[4][0]);
}
void CDlgKeyHill10x10::OnUpdateMat159()
{
	UpdateAlphCode(m_pAlphCode[4][1]);
	setFeldAlph(m_pFelder[4][1],m_pAlphCode[4][1]);
}
void CDlgKeyHill10x10::OnUpdateMat113()
{
	UpdateAlphCode(m_pAlphCode[4][2]);
	setFeldAlph(m_pFelder[4][2],m_pAlphCode[4][2]);
}
void CDlgKeyHill10x10::OnUpdateMat160()
{
	UpdateAlphCode(m_pAlphCode[4][3]);
	setFeldAlph(m_pFelder[4][3],m_pAlphCode[4][3]);
}
void CDlgKeyHill10x10::OnUpdateMat161()
{
	UpdateAlphCode(m_pAlphCode[4][4]);
	setFeldAlph(m_pFelder[4][4],m_pAlphCode[4][4]);
}
void CDlgKeyHill10x10::OnUpdateMat162()
{
	UpdateAlphCode(m_pAlphCode[4][5]);
	setFeldAlph(m_pFelder[4][5],m_pAlphCode[4][5]);
}
void CDlgKeyHill10x10::OnUpdateMat163()
{
	UpdateAlphCode(m_pAlphCode[4][6]);
	setFeldAlph(m_pFelder[4][6],m_pAlphCode[4][6]);
}
void CDlgKeyHill10x10::OnUpdateMat164()
{
	UpdateAlphCode(m_pAlphCode[4][7]);
	setFeldAlph(m_pFelder[4][7],m_pAlphCode[4][7]);
}
void CDlgKeyHill10x10::OnUpdateMat165()
{
	UpdateAlphCode(m_pAlphCode[4][8]);
	setFeldAlph(m_pFelder[4][8],m_pAlphCode[4][8]);
}
void CDlgKeyHill10x10::OnUpdateMat511()
{
	UpdateAlphCode(m_pAlphCode[4][9]);
	setFeldAlph(m_pFelder[4][9],m_pAlphCode[4][9]);
}
void CDlgKeyHill10x10::OnUpdateMat166()
{
	UpdateAlphCode(m_pAlphCode[5][0]);
	setFeldAlph(m_pFelder[5][0],m_pAlphCode[5][0]);
}
void CDlgKeyHill10x10::OnUpdateMat167()
{
	UpdateAlphCode(m_pAlphCode[5][1]);
	setFeldAlph(m_pFelder[5][1],m_pAlphCode[5][1]);
}
void CDlgKeyHill10x10::OnUpdateMat168()
{
	UpdateAlphCode(m_pAlphCode[5][2]);
	setFeldAlph(m_pFelder[5][2],m_pAlphCode[5][2]);
}
void CDlgKeyHill10x10::OnUpdateMat169()
{
	UpdateAlphCode(m_pAlphCode[5][3]);
	setFeldAlph(m_pFelder[5][3],m_pAlphCode[5][3]);
}
void CDlgKeyHill10x10::OnUpdateMat170()
{
	UpdateAlphCode(m_pAlphCode[5][4]);
	setFeldAlph(m_pFelder[5][4],m_pAlphCode[5][4]);
}
void CDlgKeyHill10x10::OnUpdateMat171()
{
	UpdateAlphCode(m_pAlphCode[5][5]);
	setFeldAlph(m_pFelder[5][5],m_pAlphCode[5][5]);
}
void CDlgKeyHill10x10::OnUpdateMat172()
{
	UpdateAlphCode(m_pAlphCode[5][6]);
	setFeldAlph(m_pFelder[5][6],m_pAlphCode[5][6]);
}
void CDlgKeyHill10x10::OnUpdateMat173()
{
	UpdateAlphCode(m_pAlphCode[5][7]);
	setFeldAlph(m_pFelder[5][7],m_pAlphCode[5][7]);
}
void CDlgKeyHill10x10::OnUpdateMat174()
{
	UpdateAlphCode(m_pAlphCode[5][8]);
	setFeldAlph(m_pFelder[5][8],m_pAlphCode[5][8]);
}
void CDlgKeyHill10x10::OnUpdateMat611()
{
	UpdateAlphCode(m_pAlphCode[5][9]);
	setFeldAlph(m_pFelder[5][9],m_pAlphCode[5][9]);
}
void CDlgKeyHill10x10::OnUpdateMat175()
{
	UpdateAlphCode(m_pAlphCode[6][0]);
	setFeldAlph(m_pFelder[6][0],m_pAlphCode[6][0]);
}
void CDlgKeyHill10x10::OnUpdateMat176()
{
	UpdateAlphCode(m_pAlphCode[6][1]);
	setFeldAlph(m_pFelder[6][1],m_pAlphCode[6][1]);
}
void CDlgKeyHill10x10::OnUpdateMat177()
{
	UpdateAlphCode(m_pAlphCode[6][2]);
	setFeldAlph(m_pFelder[6][2],m_pAlphCode[6][2]);
}
void CDlgKeyHill10x10::OnUpdateMat178()
{
	UpdateAlphCode(m_pAlphCode[6][3]);
	setFeldAlph(m_pFelder[6][3],m_pAlphCode[6][3]);
}
void CDlgKeyHill10x10::OnUpdateMat179()
{
	UpdateAlphCode(m_pAlphCode[6][4]);
	setFeldAlph(m_pFelder[6][4],m_pAlphCode[6][4]);
}
void CDlgKeyHill10x10::OnUpdateMat180()
{
	UpdateAlphCode(m_pAlphCode[6][5]);
	setFeldAlph(m_pFelder[6][5],m_pAlphCode[6][5]);
}
void CDlgKeyHill10x10::OnUpdateMat181()
{
	UpdateAlphCode(m_pAlphCode[6][6]);
	setFeldAlph(m_pFelder[6][6],m_pAlphCode[6][6]);
}
void CDlgKeyHill10x10::OnUpdateMat182()
{
	UpdateAlphCode(m_pAlphCode[6][7]);
	setFeldAlph(m_pFelder[6][7],m_pAlphCode[6][7]);
}
void CDlgKeyHill10x10::OnUpdateMat183()
{
	UpdateAlphCode(m_pAlphCode[6][8]);
	setFeldAlph(m_pFelder[6][8],m_pAlphCode[6][8]);
}
void CDlgKeyHill10x10::OnUpdateMat711()
{
	UpdateAlphCode(m_pAlphCode[6][9]);
	setFeldAlph(m_pFelder[6][9],m_pAlphCode[6][9]);
}
void CDlgKeyHill10x10::OnUpdateMat184()
{
	UpdateAlphCode(m_pAlphCode[7][0]);
	setFeldAlph(m_pFelder[7][0],m_pAlphCode[7][0]);
}
void CDlgKeyHill10x10::OnUpdateMat185()
{
	UpdateAlphCode(m_pAlphCode[7][1]);
	setFeldAlph(m_pFelder[7][1],m_pAlphCode[7][1]);
}
void CDlgKeyHill10x10::OnUpdateMat186()
{
	UpdateAlphCode(m_pAlphCode[7][2]);
	setFeldAlph(m_pFelder[7][2],m_pAlphCode[7][2]);
}
void CDlgKeyHill10x10::OnUpdateMat187()
{
	UpdateAlphCode(m_pAlphCode[7][3]);
	setFeldAlph(m_pFelder[7][3],m_pAlphCode[7][3]);
}
void CDlgKeyHill10x10::OnUpdateMat188()
{
	UpdateAlphCode(m_pAlphCode[7][4]);
	setFeldAlph(m_pFelder[7][4],m_pAlphCode[7][4]);
}
void CDlgKeyHill10x10::OnUpdateMat189()
{
	UpdateAlphCode(m_pAlphCode[7][5]);
	setFeldAlph(m_pFelder[7][5],m_pAlphCode[7][5]);
}
void CDlgKeyHill10x10::OnUpdateMat190()
{
	UpdateAlphCode(m_pAlphCode[7][6]);
	setFeldAlph(m_pFelder[7][6],m_pAlphCode[7][6]);
}
void CDlgKeyHill10x10::OnUpdateMat191()
{
	UpdateAlphCode(m_pAlphCode[7][7]);
	setFeldAlph(m_pFelder[7][7],m_pAlphCode[7][7]);
}
void CDlgKeyHill10x10::OnUpdateMat192()
{
	UpdateAlphCode(m_pAlphCode[7][8]);
	setFeldAlph(m_pFelder[7][8],m_pAlphCode[7][8]);
}
void CDlgKeyHill10x10::OnUpdateMat811()
{
	UpdateAlphCode(m_pAlphCode[7][9]);
	setFeldAlph(m_pFelder[7][9],m_pAlphCode[7][9]);
}
void CDlgKeyHill10x10::OnUpdateMat193()
{
	UpdateAlphCode(m_pAlphCode[8][0]);
	setFeldAlph(m_pFelder[8][0],m_pAlphCode[8][0]);
}
void CDlgKeyHill10x10::OnUpdateMat194()
{
	UpdateAlphCode(m_pAlphCode[8][1]);
	setFeldAlph(m_pFelder[8][1],m_pAlphCode[8][1]);
}
void CDlgKeyHill10x10::OnUpdateMat195()
{
	UpdateAlphCode(m_pAlphCode[8][2]);
	setFeldAlph(m_pFelder[8][2],m_pAlphCode[8][2]);
}
void CDlgKeyHill10x10::OnUpdateMat196()
{
	UpdateAlphCode(m_pAlphCode[8][3]);
	setFeldAlph(m_pFelder[8][3],m_pAlphCode[8][3]);
}
void CDlgKeyHill10x10::OnUpdateMat197()
{
	UpdateAlphCode(m_pAlphCode[8][4]);
	setFeldAlph(m_pFelder[8][4],m_pAlphCode[8][4]);
}
void CDlgKeyHill10x10::OnUpdateMat198()
{
	UpdateAlphCode(m_pAlphCode[8][5]);
	setFeldAlph(m_pFelder[8][5],m_pAlphCode[8][5]);
}
void CDlgKeyHill10x10::OnUpdateMat199()
{
	UpdateAlphCode(m_pAlphCode[8][6]);
	setFeldAlph(m_pFelder[8][6],m_pAlphCode[8][6]);
}
void CDlgKeyHill10x10::OnUpdateMat200()
{
	UpdateAlphCode(m_pAlphCode[8][7]);
	setFeldAlph(m_pFelder[8][7],m_pAlphCode[8][7]);
}
void CDlgKeyHill10x10::OnUpdateMat201()
{
	UpdateAlphCode(m_pAlphCode[8][8]);
	setFeldAlph(m_pFelder[8][8],m_pAlphCode[8][8]);
}
void CDlgKeyHill10x10::OnUpdateMat911()
{
	UpdateAlphCode(m_pAlphCode[8][9]);
	setFeldAlph(m_pFelder[8][9],m_pAlphCode[8][9]);
}
void CDlgKeyHill10x10::OnUpdateMat202()
{
	UpdateAlphCode(m_pAlphCode[9][0]);
	setFeldAlph(m_pFelder[9][0],m_pAlphCode[9][0]);
}
void CDlgKeyHill10x10::OnUpdateMat203()
{
	UpdateAlphCode(m_pAlphCode[9][1]);
	setFeldAlph(m_pFelder[9][1],m_pAlphCode[9][1]);
}
void CDlgKeyHill10x10::OnUpdateMat204()
{
	UpdateAlphCode(m_pAlphCode[9][2]);
	setFeldAlph(m_pFelder[9][2],m_pAlphCode[9][2]);
}
void CDlgKeyHill10x10::OnUpdateMat205()
{
	UpdateAlphCode(m_pAlphCode[9][3]);
	setFeldAlph(m_pFelder[9][3],m_pAlphCode[9][3]);
}
void CDlgKeyHill10x10::OnUpdateMat206()
{
	UpdateAlphCode(m_pAlphCode[9][4]);
	setFeldAlph(m_pFelder[9][4],m_pAlphCode[9][4]);
}
void CDlgKeyHill10x10::OnUpdateMat207()
{
	UpdateAlphCode(m_pAlphCode[9][5]);
	setFeldAlph(m_pFelder[9][5],m_pAlphCode[9][5]);
}
void CDlgKeyHill10x10::OnUpdateMat208()
{
	UpdateAlphCode(m_pAlphCode[9][6]);
	setFeldAlph(m_pFelder[9][6],m_pAlphCode[9][6]);
}
void CDlgKeyHill10x10::OnUpdateMat209()
{
	UpdateAlphCode(m_pAlphCode[9][7]);
	setFeldAlph(m_pFelder[9][7],m_pAlphCode[9][7]);
}
void CDlgKeyHill10x10::OnUpdateMat212()
{
	UpdateAlphCode(m_pAlphCode[9][8]);
	setFeldAlph(m_pFelder[9][8],m_pAlphCode[9][8]);
}
void CDlgKeyHill10x10::OnUpdateMat1011()
{
	UpdateAlphCode(m_pAlphCode[9][9]);
	setFeldAlph(m_pFelder[9][9],m_pAlphCode[9][9]);
}


void CDlgKeyHill10x10::OnExitMat40()
{
	setDoublePos(m_pAlphCode[0][0]);
}
void CDlgKeyHill10x10::OnExitMat50()
{
	setDoublePos(m_pAlphCode[0][1]);
}
void CDlgKeyHill10x10::OnExitMat20()
{
	setDoublePos(m_pAlphCode[0][2]);
}
void CDlgKeyHill10x10::OnExitMat90()
{
	setDoublePos(m_pAlphCode[0][3]);
}
void CDlgKeyHill10x10::OnExitMat100()
{
	setDoublePos(m_pAlphCode[0][4]);
}
void CDlgKeyHill10x10::OnExitMat117()
{
	setDoublePos(m_pAlphCode[0][5]);
}
void CDlgKeyHill10x10::OnExitMat118()
{
	setDoublePos(m_pAlphCode[0][6]);
}
void CDlgKeyHill10x10::OnExitMat119()
{
	setDoublePos(m_pAlphCode[0][7]);
}
void CDlgKeyHill10x10::OnExitMat60()
{
	setDoublePos(m_pAlphCode[0][8]);
}
void CDlgKeyHill10x10::OnExitMat125()
{
	setDoublePos(m_pAlphCode[0][9]);
}
void CDlgKeyHill10x10::OnExitMat127()
{
	setDoublePos(m_pAlphCode[1][0]);
}
void CDlgKeyHill10x10::OnExitMat134()
{
	setDoublePos(m_pAlphCode[1][1]);
}
void CDlgKeyHill10x10::OnExitMat135()
{
	setDoublePos(m_pAlphCode[1][2]);
}
void CDlgKeyHill10x10::OnExitMat136()
{
	setDoublePos(m_pAlphCode[1][3]);
}
void CDlgKeyHill10x10::OnExitMat70()
{
	setDoublePos(m_pAlphCode[1][4]);
}
void CDlgKeyHill10x10::OnExitMat137()
{
	setDoublePos(m_pAlphCode[1][5]);
}
void CDlgKeyHill10x10::OnExitMat138()
{
	setDoublePos(m_pAlphCode[1][6]);
}
void CDlgKeyHill10x10::OnExitMat139()
{
	setDoublePos(m_pAlphCode[1][7]);
}
void CDlgKeyHill10x10::OnExitMat80()
{
	setDoublePos(m_pAlphCode[1][8]);
}
void CDlgKeyHill10x10::OnExitMat211()
{
	setDoublePos(m_pAlphCode[1][9]);
}
void CDlgKeyHill10x10::OnExitMat140()
{
	setDoublePos(m_pAlphCode[2][0]);
}
void CDlgKeyHill10x10::OnExitMat141()
{
	setDoublePos(m_pAlphCode[2][1]);
}
void CDlgKeyHill10x10::OnExitMat142()
{
	setDoublePos(m_pAlphCode[2][2]);
}
void CDlgKeyHill10x10::OnExitMat143()
{
	setDoublePos(m_pAlphCode[2][3]);
}
void CDlgKeyHill10x10::OnExitMat144()
{
	setDoublePos(m_pAlphCode[2][4]);
}
void CDlgKeyHill10x10::OnExitMat145()
{
	setDoublePos(m_pAlphCode[2][5]);
}
void CDlgKeyHill10x10::OnExitMat146()
{
	setDoublePos(m_pAlphCode[2][6]);
}
void CDlgKeyHill10x10::OnExitMat147()
{
	setDoublePos(m_pAlphCode[2][7]);
}
void CDlgKeyHill10x10::OnExitMat148()
{
	setDoublePos(m_pAlphCode[2][8]);
}
void CDlgKeyHill10x10::OnExitMat311()
{
	setDoublePos(m_pAlphCode[2][9]);
}
void CDlgKeyHill10x10::OnExitMat149()
{
	setDoublePos(m_pAlphCode[3][0]);
}
void CDlgKeyHill10x10::OnExitMat150()
{
	setDoublePos(m_pAlphCode[3][1]);
}
void CDlgKeyHill10x10::OnExitMat151()
{
	setDoublePos(m_pAlphCode[3][2]);
}
void CDlgKeyHill10x10::OnExitMat152()
{
	setDoublePos(m_pAlphCode[3][3]);
}
void CDlgKeyHill10x10::OnExitMat153()
{
	setDoublePos(m_pAlphCode[3][4]);
}
void CDlgKeyHill10x10::OnExitMat154()
{
	setDoublePos(m_pAlphCode[3][5]);
}
void CDlgKeyHill10x10::OnExitMat155()
{
	setDoublePos(m_pAlphCode[3][6]);
}
void CDlgKeyHill10x10::OnExitMat156()
{
	setDoublePos(m_pAlphCode[3][7]);
}
void CDlgKeyHill10x10::OnExitMat157()
{
	setDoublePos(m_pAlphCode[3][8]);
}
void CDlgKeyHill10x10::OnExitMat411()
{
	setDoublePos(m_pAlphCode[3][9]);
}
void CDlgKeyHill10x10::OnExitMat158()
{
	setDoublePos(m_pAlphCode[4][0]);
}
void CDlgKeyHill10x10::OnExitMat159()
{
	setDoublePos(m_pAlphCode[4][1]);
}
void CDlgKeyHill10x10::OnExitMat113()
{
	setDoublePos(m_pAlphCode[4][2]);
}
void CDlgKeyHill10x10::OnExitMat160()
{
	setDoublePos(m_pAlphCode[4][3]);
}
void CDlgKeyHill10x10::OnExitMat161()
{
	setDoublePos(m_pAlphCode[4][4]);
}
void CDlgKeyHill10x10::OnExitMat162()
{
	setDoublePos(m_pAlphCode[4][5]);
}
void CDlgKeyHill10x10::OnExitMat163()
{
	setDoublePos(m_pAlphCode[4][6]);
}
void CDlgKeyHill10x10::OnExitMat164()
{
	setDoublePos(m_pAlphCode[4][7]);
}
void CDlgKeyHill10x10::OnExitMat165()
{
	setDoublePos(m_pAlphCode[4][8]);
}
void CDlgKeyHill10x10::OnExitMat511()
{
	setDoublePos(m_pAlphCode[4][9]);
}
void CDlgKeyHill10x10::OnExitMat166()
{
	setDoublePos(m_pAlphCode[5][0]);
}
void CDlgKeyHill10x10::OnExitMat167()
{
	setDoublePos(m_pAlphCode[5][1]);
}
void CDlgKeyHill10x10::OnExitMat168()
{
	setDoublePos(m_pAlphCode[5][2]);
}
void CDlgKeyHill10x10::OnExitMat169()
{
	setDoublePos(m_pAlphCode[5][3]);
}
void CDlgKeyHill10x10::OnExitMat170()
{
	setDoublePos(m_pAlphCode[5][4]);
}
void CDlgKeyHill10x10::OnExitMat171()
{
	setDoublePos(m_pAlphCode[5][5]);
}
void CDlgKeyHill10x10::OnExitMat172()
{
	setDoublePos(m_pAlphCode[5][6]);
}
void CDlgKeyHill10x10::OnExitMat173()
{
	setDoublePos(m_pAlphCode[5][7]);
}
void CDlgKeyHill10x10::OnExitMat174()
{
	setDoublePos(m_pAlphCode[5][8]);
}
void CDlgKeyHill10x10::OnExitMat611()
{
	setDoublePos(m_pAlphCode[5][9]);
}
void CDlgKeyHill10x10::OnExitMat175()
{
	setDoublePos(m_pAlphCode[6][0]);
}
void CDlgKeyHill10x10::OnExitMat176()
{
	setDoublePos(m_pAlphCode[6][1]);
}
void CDlgKeyHill10x10::OnExitMat177()
{
	setDoublePos(m_pAlphCode[6][2]);
}
void CDlgKeyHill10x10::OnExitMat178()
{
	setDoublePos(m_pAlphCode[6][3]);
}
void CDlgKeyHill10x10::OnExitMat179()
{
	setDoublePos(m_pAlphCode[6][4]);
}
void CDlgKeyHill10x10::OnExitMat180()
{
	setDoublePos(m_pAlphCode[6][5]);
}
void CDlgKeyHill10x10::OnExitMat181()
{
	setDoublePos(m_pAlphCode[6][6]);
}
void CDlgKeyHill10x10::OnExitMat182()
{
	setDoublePos(m_pAlphCode[6][7]);
}
void CDlgKeyHill10x10::OnExitMat183()
{
	setDoublePos(m_pAlphCode[6][8]);
}
void CDlgKeyHill10x10::OnExitMat711()
{
	setDoublePos(m_pAlphCode[6][9]);
}
void CDlgKeyHill10x10::OnExitMat184()
{
	setDoublePos(m_pAlphCode[7][0]);
}
void CDlgKeyHill10x10::OnExitMat185()
{
	setDoublePos(m_pAlphCode[7][1]);
}
void CDlgKeyHill10x10::OnExitMat186()
{
	setDoublePos(m_pAlphCode[7][2]);
}
void CDlgKeyHill10x10::OnExitMat187()
{
	setDoublePos(m_pAlphCode[7][3]);
}
void CDlgKeyHill10x10::OnExitMat188()
{
	setDoublePos(m_pAlphCode[7][4]);
}
void CDlgKeyHill10x10::OnExitMat189()
{
	setDoublePos(m_pAlphCode[7][5]);
}
void CDlgKeyHill10x10::OnExitMat190()
{
	setDoublePos(m_pAlphCode[7][6]);
}
void CDlgKeyHill10x10::OnExitMat191()
{
	setDoublePos(m_pAlphCode[7][7]);
}
void CDlgKeyHill10x10::OnExitMat192()
{
	setDoublePos(m_pAlphCode[7][8]);
}
void CDlgKeyHill10x10::OnExitMat811()
{
	setDoublePos(m_pAlphCode[7][9]);
}
void CDlgKeyHill10x10::OnExitMat193()
{
	setDoublePos(m_pAlphCode[8][0]);
}
void CDlgKeyHill10x10::OnExitMat194()
{
	setDoublePos(m_pAlphCode[8][1]);
}
void CDlgKeyHill10x10::OnExitMat195()
{
	setDoublePos(m_pAlphCode[8][2]);
}
void CDlgKeyHill10x10::OnExitMat196()
{
	setDoublePos(m_pAlphCode[8][3]);
}
void CDlgKeyHill10x10::OnExitMat197()
{
	setDoublePos(m_pAlphCode[8][4]);
}
void CDlgKeyHill10x10::OnExitMat198()
{
	setDoublePos(m_pAlphCode[8][5]);
}
void CDlgKeyHill10x10::OnExitMat199()
{
	setDoublePos(m_pAlphCode[8][6]);
}
void CDlgKeyHill10x10::OnExitMat200()
{
	setDoublePos(m_pAlphCode[8][7]);
}
void CDlgKeyHill10x10::OnExitMat201()
{
	setDoublePos(m_pAlphCode[8][8]);
}
void CDlgKeyHill10x10::OnExitMat911()
{
	setDoublePos(m_pAlphCode[8][9]);
}
void CDlgKeyHill10x10::OnExitMat202()
{
	setDoublePos(m_pAlphCode[9][0]);
}
void CDlgKeyHill10x10::OnExitMat203()
{
	setDoublePos(m_pAlphCode[9][1]);
}
void CDlgKeyHill10x10::OnExitMat204()
{
	setDoublePos(m_pAlphCode[9][2]);
}
void CDlgKeyHill10x10::OnExitMat205()
{
	setDoublePos(m_pAlphCode[9][3]);
}
void CDlgKeyHill10x10::OnExitMat206()
{
	setDoublePos(m_pAlphCode[9][4]);
}
void CDlgKeyHill10x10::OnExitMat207()
{
	setDoublePos(m_pAlphCode[9][5]);
}
void CDlgKeyHill10x10::OnExitMat208()
{
	setDoublePos(m_pAlphCode[9][6]);
}
void CDlgKeyHill10x10::OnExitMat209()
{
	setDoublePos(m_pAlphCode[9][7]);
}
void CDlgKeyHill10x10::OnExitMat212()
{
	setDoublePos(m_pAlphCode[9][8]);
}
void CDlgKeyHill10x10::OnExitMat1011()
{
	setDoublePos(m_pAlphCode[9][9]);
}


void CDlgKeyHill10x10::UpdateFeld(CEdit *feld)
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

	if  (cs.GetLength() == 1)
	{
		if( hillklasse->ist_erlaubtes_zeichen(cs[0]) )
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
}void CDlgKeyHill10x10::UpdateAlphCode(CEdit *feld)
{
	if(alphCode)
	{
	CString cs;
	feld->GetWindowText(cs);
	if(cs.GetLength() == 2)
	{
		if(_ttoi(cs) < 1 || _ttoi(cs) > theApp.TextOptions.getAlphabet().GetLength())
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

int CDlgKeyHill10x10::Display()
{
	int res;

	res=DoModal();

	//	MakeBin(m_einstr, buffer);
	
	return res;
}

void CDlgKeyHill10x10::OnOK() 
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

void CDlgKeyHill10x10::OnDecrypt()
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
		m_decrypt = 1;
		CDialog::OnOK();
	}

}

BOOL CDlgKeyHill10x10::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_Verbose = bGlobVerbose;

	CheckRadioButton(IDC_RADIO21,IDC_RADIO22,IDC_RADIO21);
	
	if(iHillMultiplicationType)
		CheckRadioButton(IDC_RADIO23,IDC_RADIO24,IDC_RADIO23);
	else
		CheckRadioButton(IDC_RADIO23,IDC_RADIO24,IDC_RADIO24);
	
	//// TODO: Zusätzliche Initialisierung hier einfügen
	int len = theApp.TextOptions.getAlphabet().GetLength();

	LoadString(AfxGetInstanceHandle(),IDS_HILL_CASE,pc_str,STR_LAENGE_STRING_TABLE);
	char l_str[1024];
	sprintf(l_str,pc_str,len);
	//
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
		CheckRadioButton(IDC_RADIO21, IDC_RADIO22, IDC_RADIO21);
	else
		CheckRadioButton(IDC_RADIO21, IDC_RADIO22, IDC_RADIO22);


	m_pHillAlphInfo = theApp.TextOptions.getAlphabet();

	UpdateData(FALSE);

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

	m_pAlphCode[0][0] = &m_Feld40;
	m_pAlphCode[0][1] = &m_Feld50;
	m_pAlphCode[0][2] = &m_Feld20;
	m_pAlphCode[0][3] = &m_Feld90;
	m_pAlphCode[0][4] = &m_Feld100;
	m_pAlphCode[0][5] = &m_Feld117;
	m_pAlphCode[0][6] = &m_Feld118;
	m_pAlphCode[0][7] = &m_Feld119;
	m_pAlphCode[0][8] = &m_Feld60;
	m_pAlphCode[0][9] = &m_Feld125;
	m_pAlphCode[1][0] = &m_Feld127;
	m_pAlphCode[1][1] = &m_Feld134;
	m_pAlphCode[1][2] = &m_Feld135;
	m_pAlphCode[1][3] = &m_Feld136;
	m_pAlphCode[1][4] = &m_Feld70;
	m_pAlphCode[1][5] = &m_Feld137;
	m_pAlphCode[1][6] = &m_Feld138;
	m_pAlphCode[1][7] = &m_Feld139;
	m_pAlphCode[1][8] = &m_Feld80;
	m_pAlphCode[1][9] = &m_Feld211;
	m_pAlphCode[2][0] = &m_Feld140;
	m_pAlphCode[2][1] = &m_Feld141;
	m_pAlphCode[2][2] = &m_Feld142;
	m_pAlphCode[2][3] = &m_Feld143;
	m_pAlphCode[2][4] = &m_Feld144;
	m_pAlphCode[2][5] = &m_Feld145;
	m_pAlphCode[2][6] = &m_Feld146;
	m_pAlphCode[2][7] = &m_Feld147;
	m_pAlphCode[2][8] = &m_Feld148;
	m_pAlphCode[2][9] = &m_Feld311;
	m_pAlphCode[3][0] = &m_Feld149;
	m_pAlphCode[3][1] = &m_Feld150;
	m_pAlphCode[3][2] = &m_Feld151;
	m_pAlphCode[3][3] = &m_Feld152;
	m_pAlphCode[3][4] = &m_Feld153;
	m_pAlphCode[3][5] = &m_Feld154;
	m_pAlphCode[3][6] = &m_Feld155;
	m_pAlphCode[3][7] = &m_Feld156;
	m_pAlphCode[3][8] = &m_Feld157;
	m_pAlphCode[3][9] = &m_Feld411;
	m_pAlphCode[4][0] = &m_Feld158;
	m_pAlphCode[4][1] = &m_Feld159;
	m_pAlphCode[4][2] = &m_Feld113;
	m_pAlphCode[4][3] = &m_Feld160;
	m_pAlphCode[4][4] = &m_Feld161;
	m_pAlphCode[4][5] = &m_Feld162;
	m_pAlphCode[4][6] = &m_Feld163;
	m_pAlphCode[4][7] = &m_Feld164;
	m_pAlphCode[4][8] = &m_Feld165;
	m_pAlphCode[4][9] = &m_Feld511;
	m_pAlphCode[5][0] = &m_Feld166;
	m_pAlphCode[5][1] = &m_Feld167;
	m_pAlphCode[5][2] = &m_Feld168;
	m_pAlphCode[5][3] = &m_Feld169;
	m_pAlphCode[5][4] = &m_Feld170;
	m_pAlphCode[5][5] = &m_Feld171;
	m_pAlphCode[5][6] = &m_Feld172;
	m_pAlphCode[5][7] = &m_Feld173;
	m_pAlphCode[5][8] = &m_Feld174;
	m_pAlphCode[5][9] = &m_Feld611;
	m_pAlphCode[6][0] = &m_Feld175;
	m_pAlphCode[6][1] = &m_Feld176;
	m_pAlphCode[6][2] = &m_Feld177;
	m_pAlphCode[6][3] = &m_Feld178;
	m_pAlphCode[6][4] = &m_Feld179;
	m_pAlphCode[6][5] = &m_Feld180;
	m_pAlphCode[6][6] = &m_Feld181;
	m_pAlphCode[6][7] = &m_Feld182;
	m_pAlphCode[6][8] = &m_Feld183;
	m_pAlphCode[6][9] = &m_Feld711;
	m_pAlphCode[7][0] = &m_Feld184;
	m_pAlphCode[7][1] = &m_Feld185;
	m_pAlphCode[7][2] = &m_Feld186;
	m_pAlphCode[7][3] = &m_Feld187;
	m_pAlphCode[7][4] = &m_Feld188;
	m_pAlphCode[7][5] = &m_Feld189;
	m_pAlphCode[7][6] = &m_Feld190;
	m_pAlphCode[7][7] = &m_Feld191;
	m_pAlphCode[7][8] = &m_Feld192;
	m_pAlphCode[7][9] = &m_Feld811;
	m_pAlphCode[8][0] = &m_Feld193;
	m_pAlphCode[8][1] = &m_Feld194;
	m_pAlphCode[8][2] = &m_Feld195;
	m_pAlphCode[8][3] = &m_Feld196;
	m_pAlphCode[8][4] = &m_Feld197;
	m_pAlphCode[8][5] = &m_Feld198;
	m_pAlphCode[8][6] = &m_Feld199;
	m_pAlphCode[8][7] = &m_Feld200;
	m_pAlphCode[8][8] = &m_Feld201;
	m_pAlphCode[8][9] = &m_Feld911;
	m_pAlphCode[9][0] = &m_Feld202;
	m_pAlphCode[9][1] = &m_Feld203;
	m_pAlphCode[9][2] = &m_Feld204;
	m_pAlphCode[9][3] = &m_Feld205;
	m_pAlphCode[9][4] = &m_Feld206;
	m_pAlphCode[9][5] = &m_Feld207;
	m_pAlphCode[9][6] = &m_Feld208;
	m_pAlphCode[9][7] = &m_Feld209;
	m_pAlphCode[9][8] = &m_Feld212;
	m_pAlphCode[9][9] = &m_Feld1011;

	
	// Font mit fester Breite erstellen und fuer alle Schluesselfelder setzen
	cf.CreatePointFont(80,"Courier");
	for (int i=0; i<HILL_MAX_DIM_GROSS; i++)
	{
		for (int j=0; j<HILL_MAX_DIM_GROSS; j++)
		{
			m_pFelder[i][j]->SetFont(&cf);
			m_pAlphCode[i][j]->SetFont(&cf);
		}
	}

	ASSERT ((0 <= iHillSchluesselDim) && (iHillSchluesselDim <= HILL_MAX_DIM_GROSS));
	dim = iHillSchluesselDim;

	switch (iHillSchluesselDim)
	{
	case 1:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO1);
		break;
	case 2:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO2);
		break;
	case 3:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO3);
		break;
	case 4:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO4);
		break;
	case 5:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO5);
		break;
	case 6:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO6);
		break;
	case 7:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO7);
		break;
	case 8:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO8);
		break;
	case 9:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO9);
		break;
	case 10:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO10);
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

	//read matrix entries from hill5x5
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
void CDlgKeyHill10x10::OnEnableAlphCode()
{
	alphCode = 1;
	AnzeigeDimensionSetzen(dim);
}
void CDlgKeyHill10x10::OnDisableAlphCode()
{
	alphCode = 0;
	AnzeigeDimensionSetzen(dim);
}
void CDlgKeyHill10x10::OnDimension1() 
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

void CDlgKeyHill10x10::OnDimension2() 
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

void CDlgKeyHill10x10::OnDimension3() 
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

void CDlgKeyHill10x10::OnDimension4() 
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

void CDlgKeyHill10x10::OnDimension5() 
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

void CDlgKeyHill10x10::OnDimension6() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	dim = 6;
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

void CDlgKeyHill10x10::OnDimension7() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	dim = 7;
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

void CDlgKeyHill10x10::OnDimension8() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	dim = 8;
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

void CDlgKeyHill10x10::OnDimension9() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	dim = 9;
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

void CDlgKeyHill10x10::OnDimension10() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	dim = 10;
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

void CDlgKeyHill10x10::AnzeigeDimensionSetzen(int dim)
{
	for(int i=0;i<HILL_MAX_DIM_GROSS;i++)
		{
			for(int j=0;j<HILL_MAX_DIM_GROSS;j++)
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


	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM_GROSS));

	BOOL mybool;

	for (int i=0; i<HILL_MAX_DIM_GROSS; i++)
	{
		for (int j=0; j<HILL_MAX_DIM_GROSS; j++)
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

int CDlgKeyHill10x10::AlleFelderKorrekt(int dim)
{
	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM_GROSS));

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

void CDlgKeyHill10x10::MatrixEinlesen(CSquareMatrixModN& mat, int dim)
{
	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM_GROSS));

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

void CDlgKeyHill10x10::MatrixAnzeigen(CSquareMatrixModN& mat)
{
	int dimension = mat.get_dim();

	ASSERT ((1 <= dimension) && (dimension <= HILL_MAX_DIM_GROSS));

	CString cs;

	for (int i=0; i<dimension; i++)
	{
		for (int j=0; j<dimension; j++)
		{
			cs = hillklasse->my_int_to_char(mat(i,j));
			m_pFelder[i][j]->SetWindowText(cs);
			m_pFelder[i][j]->SetSel(0,0);
		}
	}
}


// Die Position fuer den naechsten Eintrag in der Schluesselmatrix wird berechnet.
// Falls kein weiterer Eintrag mehr zur Verfuegung steht, wird FALSE zurueckgegeben,
// im anderen Fall TRUE.
bool CDlgKeyHill10x10::NaechsterEintrag(int &i, int &j) 
{
	bool rc = true;

	j++;
	if (j == HILL_MAX_DIM_GROSS)
	{
		// Wir starten in der naechsten Zeile wieder vorne, ...
		i++;
		j = 0;
		// ... sofern es noch eine weitere gibt.
		if (i == HILL_MAX_DIM_GROSS)
		{
			// Es gibt keine weitere Zeile
			rc = false;
		}
	}

	return rc;
}


void CDlgKeyHill10x10::OnPasteKey() 
{
	CString cs, hilf;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_HILL,pc_str,STR_LAENGE_STRING_TABLE);
	if ( PasteKey(pc_str,cs) )
	{

 		int i=0, // Zeile des naechsten Eintrages in die Schluesselmatrix
 			j=-1, // Spalte des naechsten Eintrages in die Schluesselmatrix 
 			l=0, // Laufvariable fuer den Text aus der Zwischenablage
 			laenge = cs.GetLength(); // Laenge des Textes der Zwischenablage
		int keyDim = 0;
		
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
				if (i == HILL_MAX_DIM_GROSS)
				{
 					// Es gibt keine weitere Zeile
 					l = laenge;
				}
 			}
 
 			l++;
 		}

		ASSERT ((0 <= keyDim) && (keyDim <= HILL_MAX_DIM_GROSS));
		dim = keyDim;
		iHillSchluesselDim = dim;

		switch (iHillSchluesselDim)
		{
		case 1:	
			CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO1);
			OnDimension1();
			break;
		case 2:	
			CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO2);
			OnDimension2();
			break;
		case 3:	
			CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO3);
			OnDimension3();
			break;
		case 4:	
			CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO4);
			OnDimension4();
			break;
		case 5:	
			CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO5);
			OnDimension5();
			break;
		case 6:	
			CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO6);
			OnDimension6();
			break;
		case 7:	
			CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO7);
			OnDimension7();
			break;
		case 8:	
			CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO8);
			OnDimension8();
			break;
		case 9:	
			CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO9);
			OnDimension9();
			break;
		case 10:	
			CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO10);
			OnDimension10();
			break;
		default:
			// Default Dimension = 2
			dim = 2;
			iHillSchluesselDim = dim;
			CheckRadioButton(IDC_RADIO1, IDC_RADIO10, IDC_RADIO2);
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
}

void CDlgKeyHill10x10::OnZufaelligerSchluessel() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	// Zuerst eine zufaellige Matrix erzeugen und im Anschluss
	// in die Maske schreiben
	CSquareMatrixModN mat1(dim, hillklasse->get_modul());
	mat1.zufaellige_invertierbare_matrix();
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
	for(int i=0;i<HILL_MAX_DIM_GROSS;i++)
	{
		for(int j=0;j<HILL_MAX_DIM_GROSS;j++)
		{
			m_pFelder[i][j]->GetWindowText(str);
			m_pAlphCode[i][j]->SetWindowText(getAlphCode(str));
		}
	}
}


void CDlgKeyHill10x10::OnKleinereSchluessel() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(true);
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "Hill" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(unsigned long(firstPosNull), "OrdChrOffset");
		CT_WRITE_REGISTRY(unsigned long(alphCode), "EditKeyChrMatrix");
		CT_CLOSE_REGISTRY();
	}

	iHillSchluesselFensterGroesse = HILL_SCHLUESSEL_KLEIN;
	bGlobVerbose = bool(m_Verbose);

	//save matrix entries for hill5x5
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
			m_pFelder[i][j]->GetWindowText(sHillGlobalKey[i][j]);
		}
	}

	CDialog::OnOK();
}
CString CDlgKeyHill10x10::getAlphCode(CString alphChar)
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
CString CDlgKeyHill10x10::getAlphChar(CString alphPos)
{
		int pos = _ttoi(alphPos);
		pos--;
		if(pos < 0 || pos > theApp.TextOptions.getAlphabet().GetLength())
			return "";
		else
			return theApp.TextOptions.getAlphabet().Mid(pos,1);
}
void CDlgKeyHill10x10::setFeldAlphCode(CEdit *feld,CEdit *feldAlph)
{
	if(!alphCode)
	{
		CString str;
		feld->GetWindowText(str);
		feldAlph->SetWindowText(getAlphCode(str));
	}
}
void CDlgKeyHill10x10::setFeldAlph(CEdit *feld,CEdit *feldAlph)
{
    if(alphCode)
	{
		CString str;
		feldAlph->GetWindowText(str);
		if(str.GetLength() == 2)
			feld->SetWindowText(getAlphChar(str));
	}
}
void CDlgKeyHill10x10::setDoublePos(CEdit *feld)
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
void CDlgKeyHill10x10::OnRowVectorMatrix()
{
	iHillMultiplicationType = 1;
}
void CDlgKeyHill10x10::OnMatrixColumnVector()
{
	iHillMultiplicationType = 0;
}
void CDlgKeyHill10x10::OnBnClickedButton69()
{
	DlgHillOptions hillOpt;
	hillOpt.DoModal();
}
CString CDlgKeyHill10x10::getDimMessage()
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
		case 6:	
			return "6*6";
		case 7:	
			return "7*7";
		case 8:	
			return "8*8";
		case 9:	
			return "9*9";
		case 10:	
			return "10*10";
		default:
			return "2*2";
	}
}

void CDlgKeyHill10x10::OnTextOptions()
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