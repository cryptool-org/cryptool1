//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
// HillEingabeGross.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "HillEingabe.h"
#include "HillEingabeGross.h"
#include "hill.h"
#include "ChrTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CHillEingabeGross 


CHillEingabeGross::CHillEingabeGross(hill *hillkl, CWnd* pParent /*=NULL*/)
	: CDialog(CHillEingabeGross::IDD, pParent)
{
	hillklasse = hillkl;
	m_decrypt = 0;
	//{{AFX_DATA_INIT(CHillEingabeGross)
	//}}AFX_DATA_INIT
}


CHillEingabeGross::~CHillEingabeGross()
{
	if (mat)
	{
		delete mat;
	}
}

void CHillEingabeGross::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHillEingabeGross)
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
}


BEGIN_MESSAGE_MAP(CHillEingabeGross, CDialog)
	//{{AFX_MSG_MAP(CHillEingabeGross)
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
	ON_BN_CLICKED(IDC_BUTTON3, OnZufaelligerSchluessel)
	ON_BN_CLICKED(IDC_BUTTON4, OnKleinereSchluessel)
	ON_BN_CLICKED(IDC_BUTTON5, OnDecrypt)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CHillEingabeGross 

void CHillEingabeGross::OnUpdateMat11() 
{
	// TODO: Wenn es sich hierbei um ein RICHEDIT-Steuerelement handelt, sendet es
	// sendet diese Benachrichtigung nur, wenn die Funktion CDialog::OnInitDialog()
	// überschrieben wird, um die EM_SETEVENTMASK-Nachricht an das Steuerelement
	// mit dem ENM_UPDATE-Attribut Ored in die Maske lParam zu senden.
	
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	UpdateFeld(m_pFelder[0][0]);
}
void CHillEingabeGross::OnUpdateMat12() 
{
	UpdateFeld(m_pFelder[0][1]);
}
void CHillEingabeGross::OnUpdateMat13()
{
	UpdateFeld(m_pFelder[0][2]);
}
void CHillEingabeGross::OnUpdateMat14()
{
	UpdateFeld(m_pFelder[0][3]);
}
void CHillEingabeGross::OnUpdateMat15()
{
	UpdateFeld(m_pFelder[0][4]);
}
void CHillEingabeGross::OnUpdateMat16()
{
	UpdateFeld(m_pFelder[0][5]);
}
void CHillEingabeGross::OnUpdateMat17()
{
	UpdateFeld(m_pFelder[0][6]);
}
void CHillEingabeGross::OnUpdateMat18()
{
	UpdateFeld(m_pFelder[0][7]);
}
void CHillEingabeGross::OnUpdateMat19()
{
	UpdateFeld(m_pFelder[0][8]);
}
void CHillEingabeGross::OnUpdateMat110()
{
	UpdateFeld(m_pFelder[0][9]);
}
void CHillEingabeGross::OnUpdateMat21()
{
	UpdateFeld(m_pFelder[1][0]);
}
void CHillEingabeGross::OnUpdateMat22()
{
	UpdateFeld(m_pFelder[1][1]);
}
void CHillEingabeGross::OnUpdateMat23()
{
	UpdateFeld(m_pFelder[1][2]);
}
void CHillEingabeGross::OnUpdateMat24()
{
	UpdateFeld(m_pFelder[1][3]);
}
void CHillEingabeGross::OnUpdateMat25()
{
	UpdateFeld(m_pFelder[1][4]);
}
void CHillEingabeGross::OnUpdateMat26()
{
	UpdateFeld(m_pFelder[1][5]);
}
void CHillEingabeGross::OnUpdateMat27()
{
	UpdateFeld(m_pFelder[1][6]);
}
void CHillEingabeGross::OnUpdateMat28()
{
	UpdateFeld(m_pFelder[1][7]);
}
void CHillEingabeGross::OnUpdateMat29()
{
	UpdateFeld(m_pFelder[1][8]);
}
void CHillEingabeGross::OnUpdateMat210()
{
	UpdateFeld(m_pFelder[1][9]);
}
void CHillEingabeGross::OnUpdateMat31()
{
	UpdateFeld(m_pFelder[2][0]);
}
void CHillEingabeGross::OnUpdateMat32()
{
	UpdateFeld(m_pFelder[2][1]);
}
void CHillEingabeGross::OnUpdateMat33()
{
	UpdateFeld(m_pFelder[2][2]);
}
void CHillEingabeGross::OnUpdateMat34()
{
	UpdateFeld(m_pFelder[2][3]);
}
void CHillEingabeGross::OnUpdateMat35()
{
	UpdateFeld(m_pFelder[2][4]);
}
void CHillEingabeGross::OnUpdateMat36()
{
	UpdateFeld(m_pFelder[2][5]);
}
void CHillEingabeGross::OnUpdateMat37()
{
	UpdateFeld(m_pFelder[2][6]);
}
void CHillEingabeGross::OnUpdateMat38()
{
	UpdateFeld(m_pFelder[2][7]);
}
void CHillEingabeGross::OnUpdateMat39()
{
	UpdateFeld(m_pFelder[2][8]);
}
void CHillEingabeGross::OnUpdateMat310()
{
	UpdateFeld(m_pFelder[2][9]);
}
void CHillEingabeGross::OnUpdateMat41()
{
	UpdateFeld(m_pFelder[3][0]);
}
void CHillEingabeGross::OnUpdateMat42()
{
	UpdateFeld(m_pFelder[3][1]);
}
void CHillEingabeGross::OnUpdateMat43()
{
	UpdateFeld(m_pFelder[3][2]);
}
void CHillEingabeGross::OnUpdateMat44()
{
	UpdateFeld(m_pFelder[3][3]);
}
void CHillEingabeGross::OnUpdateMat45()
{
	UpdateFeld(m_pFelder[3][4]);
}
void CHillEingabeGross::OnUpdateMat46()
{
	UpdateFeld(m_pFelder[3][5]);
}
void CHillEingabeGross::OnUpdateMat47()
{
	UpdateFeld(m_pFelder[3][6]);
}
void CHillEingabeGross::OnUpdateMat48()
{
	UpdateFeld(m_pFelder[3][7]);
}
void CHillEingabeGross::OnUpdateMat49()
{
	UpdateFeld(m_pFelder[3][8]);
}
void CHillEingabeGross::OnUpdateMat410()
{
	UpdateFeld(m_pFelder[3][9]);
}
void CHillEingabeGross::OnUpdateMat51()
{
	UpdateFeld(m_pFelder[4][0]);
}
void CHillEingabeGross::OnUpdateMat52()
{
	UpdateFeld(m_pFelder[4][1]);
}
void CHillEingabeGross::OnUpdateMat53()
{
	UpdateFeld(m_pFelder[4][2]);
}
void CHillEingabeGross::OnUpdateMat54()
{
	UpdateFeld(m_pFelder[4][3]);
}
void CHillEingabeGross::OnUpdateMat55()
{
	UpdateFeld(m_pFelder[4][4]);
}
void CHillEingabeGross::OnUpdateMat56()
{
	UpdateFeld(m_pFelder[4][5]);
}
void CHillEingabeGross::OnUpdateMat57()
{
	UpdateFeld(m_pFelder[4][6]);
}
void CHillEingabeGross::OnUpdateMat58()
{
	UpdateFeld(m_pFelder[4][7]);
}
void CHillEingabeGross::OnUpdateMat59()
{
	UpdateFeld(m_pFelder[4][8]);
}
void CHillEingabeGross::OnUpdateMat510()
{
	UpdateFeld(m_pFelder[4][9]);
}
void CHillEingabeGross::OnUpdateMat61()
{
	UpdateFeld(m_pFelder[5][0]);
}
void CHillEingabeGross::OnUpdateMat62()
{
	UpdateFeld(m_pFelder[5][1]);
}
void CHillEingabeGross::OnUpdateMat63()
{
	UpdateFeld(m_pFelder[5][2]);
}
void CHillEingabeGross::OnUpdateMat64()
{
	UpdateFeld(m_pFelder[5][3]);
}
void CHillEingabeGross::OnUpdateMat65()
{
	UpdateFeld(m_pFelder[5][4]);
}
void CHillEingabeGross::OnUpdateMat66()
{
	UpdateFeld(m_pFelder[5][5]);
}
void CHillEingabeGross::OnUpdateMat67()
{
	UpdateFeld(m_pFelder[5][6]);
}
void CHillEingabeGross::OnUpdateMat68()
{
	UpdateFeld(m_pFelder[5][7]);
}
void CHillEingabeGross::OnUpdateMat69()
{
	UpdateFeld(m_pFelder[5][8]);
}
void CHillEingabeGross::OnUpdateMat610()
{
	UpdateFeld(m_pFelder[5][9]);
}
void CHillEingabeGross::OnUpdateMat71()
{
	UpdateFeld(m_pFelder[6][0]);
}
void CHillEingabeGross::OnUpdateMat72()
{
	UpdateFeld(m_pFelder[6][1]);
}
void CHillEingabeGross::OnUpdateMat73()
{
	UpdateFeld(m_pFelder[6][2]);
}
void CHillEingabeGross::OnUpdateMat74()
{
	UpdateFeld(m_pFelder[6][3]);
}
void CHillEingabeGross::OnUpdateMat75()
{
	UpdateFeld(m_pFelder[6][4]);
}
void CHillEingabeGross::OnUpdateMat76()
{
	UpdateFeld(m_pFelder[6][5]);
}
void CHillEingabeGross::OnUpdateMat77()
{
	UpdateFeld(m_pFelder[6][6]);
}
void CHillEingabeGross::OnUpdateMat78()
{
	UpdateFeld(m_pFelder[6][7]);
}
void CHillEingabeGross::OnUpdateMat79()
{
	UpdateFeld(m_pFelder[6][8]);
}
void CHillEingabeGross::OnUpdateMat710()
{
	UpdateFeld(m_pFelder[6][9]);
}
void CHillEingabeGross::OnUpdateMat81()
{
	UpdateFeld(m_pFelder[7][0]);
}
void CHillEingabeGross::OnUpdateMat82()
{
	UpdateFeld(m_pFelder[7][1]);
}
void CHillEingabeGross::OnUpdateMat83()
{
	UpdateFeld(m_pFelder[7][2]);
}
void CHillEingabeGross::OnUpdateMat84()
{
	UpdateFeld(m_pFelder[7][3]);
}
void CHillEingabeGross::OnUpdateMat85()
{
	UpdateFeld(m_pFelder[7][4]);
}
void CHillEingabeGross::OnUpdateMat86()
{
	UpdateFeld(m_pFelder[7][5]);
}
void CHillEingabeGross::OnUpdateMat87()
{
	UpdateFeld(m_pFelder[7][6]);
}
void CHillEingabeGross::OnUpdateMat88()
{
	UpdateFeld(m_pFelder[7][7]);
}
void CHillEingabeGross::OnUpdateMat89()
{
	UpdateFeld(m_pFelder[7][8]);
}
void CHillEingabeGross::OnUpdateMat810()
{
	UpdateFeld(m_pFelder[7][9]);
}
void CHillEingabeGross::OnUpdateMat91()
{
	UpdateFeld(m_pFelder[8][0]);
}
void CHillEingabeGross::OnUpdateMat92()
{
	UpdateFeld(m_pFelder[8][1]);
}
void CHillEingabeGross::OnUpdateMat93()
{
	UpdateFeld(m_pFelder[8][2]);
}
void CHillEingabeGross::OnUpdateMat94()
{
	UpdateFeld(m_pFelder[8][3]);
}
void CHillEingabeGross::OnUpdateMat95()
{
	UpdateFeld(m_pFelder[8][4]);
}
void CHillEingabeGross::OnUpdateMat96()
{
	UpdateFeld(m_pFelder[8][5]);
}
void CHillEingabeGross::OnUpdateMat97()
{
	UpdateFeld(m_pFelder[8][6]);
}
void CHillEingabeGross::OnUpdateMat98()
{
	UpdateFeld(m_pFelder[8][7]);
}
void CHillEingabeGross::OnUpdateMat99()
{
	UpdateFeld(m_pFelder[8][8]);
}
void CHillEingabeGross::OnUpdateMat910()
{
	UpdateFeld(m_pFelder[8][9]);
}
void CHillEingabeGross::OnUpdateMat101()
{
	UpdateFeld(m_pFelder[9][0]);
}
void CHillEingabeGross::OnUpdateMat102()
{
	UpdateFeld(m_pFelder[9][1]);
}
void CHillEingabeGross::OnUpdateMat103()
{
	UpdateFeld(m_pFelder[9][2]);
}
void CHillEingabeGross::OnUpdateMat104()
{
	UpdateFeld(m_pFelder[9][3]);
}
void CHillEingabeGross::OnUpdateMat105()
{
	UpdateFeld(m_pFelder[9][4]);
}
void CHillEingabeGross::OnUpdateMat106()
{
	UpdateFeld(m_pFelder[9][5]);
}
void CHillEingabeGross::OnUpdateMat107()
{
	UpdateFeld(m_pFelder[9][6]);
}
void CHillEingabeGross::OnUpdateMat108()
{
	UpdateFeld(m_pFelder[9][7]);
}
void CHillEingabeGross::OnUpdateMat109()
{
	UpdateFeld(m_pFelder[9][8]);
}
void CHillEingabeGross::OnUpdateMat1010()
{
	UpdateFeld(m_pFelder[9][9]);
}


void CHillEingabeGross::UpdateFeld(CEdit *feld)
{
	CString cs;
	feld->GetWindowText(cs);

	if  (cs.GetLength() == 1)
	{
		if( hillklasse->ist_erlaubtes_zeichen(cs[0]) )
		{
			// zum naechsten Feld springen
			NextDlgCtrl();
		}
		else if ( (theApp.TextOptions.m_IgnoreCase) && (MyIsLower(cs[0])) && 
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


int CHillEingabeGross::Display(hill *hillklasse)
{
	int res;

	res=DoModal();

	//	MakeBin(m_einstr, buffer);
	
	return res;
}

void CHillEingabeGross::OnOK() 
{
	// Matrizen anlegen und Daten aus Eingabefenster auslesen
	square_matrix mat1(dim,hillklasse->get_modul());

	// mat muss wieder freigegeben werden, wenn nicht mehr benoetigt !
	// Dies geschieht im Destruktor
	mat = new square_matrix(dim,hillklasse->get_modul());

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
		LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY_INV,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, pc_str1, MB_ICONWARNING|MB_OK);
		m_pFelder[0][0]->SetFocus();
		m_pFelder[0][0]->SetSel(0,-1);
		return;
	}
	else
	{
		m_decrypt = 0;
		CDialog::OnOK();
	}
}

void CHillEingabeGross::OnDecrypt()
{
	// Matrizen anlegen und Daten aus Eingabefenster auslesen
	square_matrix mat1(dim,hillklasse->get_modul());

	// mat muss wieder freigegeben werden, wenn nicht mehr benoetigt !
	// Dies geschieht im Destruktor
	mat = new square_matrix(dim,hillklasse->get_modul());

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
		LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY_INV,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, pc_str1, MB_ICONWARNING|MB_OK);
		m_pFelder[0][0]->SetFocus();
		m_pFelder[0][0]->SetSel(0,-1);
		return;
	}
	else
	{
		m_decrypt = 1;
		CDialog::OnOK();
	}

}

BOOL CHillEingabeGross::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

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

	
	// Font mit fester Breite erstellen und fuer alle Schluesselfelder setzen
	cf.CreatePointFont(80,"Courier");
	for (int i=0; i<HILL_MAX_DIM_GROSS; i++)
	{
		for (int j=0; j<HILL_MAX_DIM_GROSS; j++)
		{
			m_pFelder[i][j]->SetFont(&cf);
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

void CHillEingabeGross::OnDimension1() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	dim = 1;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CHillEingabeGross::OnDimension2() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	dim = 2;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CHillEingabeGross::OnDimension3() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	dim = 3;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CHillEingabeGross::OnDimension4() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	dim = 4;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CHillEingabeGross::OnDimension5() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	dim = 5;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CHillEingabeGross::OnDimension6() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	dim = 6;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CHillEingabeGross::OnDimension7() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	dim = 7;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CHillEingabeGross::OnDimension8() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	dim = 8;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CHillEingabeGross::OnDimension9() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	dim = 9;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CHillEingabeGross::OnDimension10() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	dim = 10;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CHillEingabeGross::AnzeigeDimensionSetzen(int dim)
{
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
			m_pFelder[i][j]->EnableWindow(mybool);
		}
	}
}

int CHillEingabeGross::AlleFelderKorrekt(int dim)
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
				m_pFelder[i][j]->SetFocus();
				m_pFelder[i][j]->SetSel(0,-1);
				return FALSE;
			}
		}
	}

	return TRUE;
}

void CHillEingabeGross::MatrixEinlesen(square_matrix& mat, int dim)
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

void CHillEingabeGross::MatrixAnzeigen(square_matrix& mat)
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
bool CHillEingabeGross::NaechsterEintrag(int &i, int &j) 
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


void CHillEingabeGross::OnPasteKey() 
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
 				i++;
				if (keyDim == 0) keyDim = j+1;
				else if ( j+1 != keyDim ) {
					/* ToDo: Fehler Meldung */
					return; 
				}

 				j = -1;
 				// ... sofern es noch eine weitere gibt.
 				if (i == HILL_MAX_DIM_GROSS)
 				{
 					// Es gibt keine weitere Zeile
					j = 0;
 					l = laenge;
 				}
 			}
 
 			l++;
 		}

		ASSERT ((0 <= keyDim) && (keyDim <= HILL_MAX_DIM));
		dim = keyDim;
		iHillSchluesselDim = dim;

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
		AnzeigeDimensionSetzen(i);
		// Cursor in Feld links oben setzen
 		m_pFelder[0][0]->SetFocus();
 		m_pFelder[0][0]->SetSel(0,-1);
	}
}

void CHillEingabeGross::OnZufaelligerSchluessel() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	// Zuerst eine zufaellige Matrix erzeugen und im Anschluss
	// in die Maske schreiben
	square_matrix mat1(dim, hillklasse->get_modul());
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
}


void CHillEingabeGross::OnKleinereSchluessel() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	iHillSchluesselFensterGroesse = HILL_SCHLUESSEL_KLEIN;

	CDialog::OnOK();
}
