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

// 3DVisOpt.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "3DVisOpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld C3DVisOpt 

#if 0
C3DVisOpt::C3DVisOpt(CWnd* pParent /*=NULL*/)
	: CDialog(C3DVisOpt::IDD, pParent)
{
	//{{AFX_DATA_INIT(C3DVisOpt)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	resolution = 128;
	density = 127;
	shift = 50;
	wordsize = 4;
}
#endif

C3DVisOpt::C3DVisOpt(CWnd* pParent, 
		unsigned short arg_res, 
		unsigned short arg_dens, 
		unsigned short arg_shift, 
		unsigned short arg_wordsize)
		: CDialog(C3DVisOpt::IDD, pParent)
{
	default_resolution = arg_res;
	default_density = arg_dens;
	default_shift = arg_shift;
	default_wordsize = arg_wordsize;	
	this->resetToDefaults();
}


void C3DVisOpt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3DVisOpt)
	DDX_Control(pDX, IDC_BUTTON_RESET, m_ButtonReset);
	DDX_Control(pDX, IDC_EDIT_SHIFT, m_editShift);
	DDX_Control(pDX, IDC_EDIT_RESOLUTION, m_editResolution);
	DDX_Control(pDX, IDC_EDIT_DENSITY, m_editDensity);
	DDX_Control(pDX, IDC_RADIO_WORDSIZE_1, m_CtrlButtonWordSize);
	DDX_Control(pDX, IDC_SLIDER_SHIFT, m_CtrlSliderShift);
	DDX_Control(pDX, IDC_SLIDER_DENSITY, m_CtrlSliderDensity);
	DDX_Control(pDX, IDC_SLIDER_RESOLUTION, m_CtrlSliderResolution);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3DVisOpt, CDialog)
	//{{AFX_MSG_MAP(C3DVisOpt)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_RESOLUTION, OnReleasedcaptureSliderResolution)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_DENSITY, OnReleasedcaptureSliderDensity)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SHIFT, OnReleasedcaptureSliderShift)
	ON_BN_CLICKED(IDC_RADIO_WORDSIZE_1, OnRadioWordsize1)
	ON_BN_CLICKED(IDC_RADIO_WORDSIZE_2, OnRadioWordsize2)
	ON_BN_CLICKED(IDC_RADIO_WORDSIZE_4, OnRadioWordsize4)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten C3DVisOpt 

void C3DVisOpt::resetToDefaults()
{
	resolution = default_resolution;
	density = default_density;
	shift = default_shift;
	wordsize = default_wordsize;	
}


void C3DVisOpt::updateControls()
{
	char buffer[10];
	buffer[9] = 0;
	
	_snprintf(buffer, 9, "%d", resolution);
	m_editResolution.SetSel(0, -1);
	m_editResolution.ReplaceSel(buffer, false);

	_snprintf(buffer, 9, "%d", density);
	m_editDensity.SetSel(0, -1);
	m_editDensity.ReplaceSel(buffer, false);

	_snprintf(buffer, 9, "%d", shift);
	m_editShift.SetSel(0, -1);
	m_editShift.ReplaceSel(buffer, false);

	switch(wordsize)
	{
		case 1:
			CheckRadioButton(IDC_RADIO_WORDSIZE_1, IDC_RADIO_WORDSIZE_4, IDC_RADIO_WORDSIZE_1);
			break;
			;;
		case 2:
			CheckRadioButton(IDC_RADIO_WORDSIZE_1, IDC_RADIO_WORDSIZE_4, IDC_RADIO_WORDSIZE_2);
			break;
			;;
		default:
			CheckRadioButton(IDC_RADIO_WORDSIZE_1, IDC_RADIO_WORDSIZE_4, IDC_RADIO_WORDSIZE_4);
			wordsize = 4;
	}

	m_CtrlSliderResolution.SetPos(resolution);
	m_CtrlSliderDensity.SetPos(density);
	m_CtrlSliderShift.SetPos(shift);

}


BOOL C3DVisOpt::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	m_CtrlSliderResolution.SetRange(64, 255);
	m_CtrlSliderDensity.SetRange(1, 255);
	m_CtrlSliderShift.SetRange(0, 50);

	this->updateControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void C3DVisOpt::OnReleasedcaptureSliderResolution(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	*pResult = 0;
	resolution = m_CtrlSliderResolution.GetPos();
	this->updateControls();
}

void C3DVisOpt::OnReleasedcaptureSliderDensity(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	*pResult = 0;
	density = m_CtrlSliderDensity.GetPos();
	this->updateControls();
}

void C3DVisOpt::OnReleasedcaptureSliderShift(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	*pResult = 0;
	shift = m_CtrlSliderShift.GetPos();
	this->updateControls();
}

void C3DVisOpt::OnRadioWordsize1() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	wordsize = 1;
	
}

void C3DVisOpt::OnRadioWordsize2() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	wordsize = 2;
}

void C3DVisOpt::OnRadioWordsize4() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	wordsize = 4;
}

void C3DVisOpt::OnButtonReset() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	this->resetToDefaults();
	this->updateControls();
}
