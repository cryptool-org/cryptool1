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

// ChallengeResponseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "ChallengeResponseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern const int numWires;
extern CWire wires[];
extern const int numComputers;
extern CComputer computers[];
// extern const int numPackets;  //FIXME Linking-Error, if numPackets is bounded - for usage please look at onResetButton
extern CPacket packets[];

/////////////////////////////////////////////////////////////////////////////
// CChallengeResponseDlg dialog

CChallengeResponseDlg::CChallengeResponseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChallengeResponseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChallengeResponseDlg)
	m_modeText = _T("");
	m_mode = -1;
	m_action = -1;
	m_attackerMasked = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32	
}

void CChallengeResponseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChallengeResponseDlg)
	DDX_Control(pDX, IDC_CHECK_MASK, c_attackerMasked);
	DDX_Control(pDX, IDC_AUTHENTICATE_CLIENT_BUTTON, m_authenticateClient);
	DDX_Text(pDX, IDC_EDIT, m_modeText);
	DDX_Radio(pDX, IDC_START_RADIO, m_mode);
	DDX_Radio(pDX, IDC_ACTION_NOTHING_RADIO, m_action);
	DDX_Check(pDX, IDC_CHECK_MASK, m_attackerMasked);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChallengeResponseDlg, CDialog)
	//{{AFX_MSG_MAP(CChallengeResponseDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_EXIT_BUTTON, OnExitButton)
	ON_BN_CLICKED(IDC_START_RADIO, OnModeRadioButtons)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_ACTION_ATTACK_RADIO, OnChangeAction)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_AUTHENTICATE_CLIENT_BUTTON, OnAuthenticateClientButton)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_AUTHENTICATE_ATTACKER_BUTTON, OnAuthenticateAttackerButton)
	ON_BN_CLICKED(IDC_CHECK_MASK, OnCheckMask)
	ON_BN_CLICKED(IDC_SCENARIO_HELP_BUTTON, OnScenarioHelpButton)
	ON_BN_CLICKED(IDC_RESET_BUTTON, OnResetButton)
	ON_BN_CLICKED(IDC_HELP, OnHelp)
	ON_BN_CLICKED(IDC_EINFUEHRUNG_RADIO, OnModeRadioButtons)
	ON_BN_CLICKED(IDC_PASSWORT_RADIO, OnModeRadioButtons)
	ON_BN_CLICKED(IDC_EINMALPASSWOERTER, OnModeRadioButtons)
	ON_BN_CLICKED(IDC_CHALLENGERESPONSE1_RADIO, OnModeRadioButtons)
	ON_BN_CLICKED(IDC_CHALLENGERESPONSE2_RADIO, OnModeRadioButtons)
	ON_BN_CLICKED(IDC_WECHSELSEITIG_RADIO, OnModeRadioButtons)
	ON_BN_CLICKED(IDC_ACTION_CONNECT_RADIO, OnChangeAction)
	ON_BN_CLICKED(IDC_ACTION_DISCONNECT_RADIO, OnChangeAction)
	ON_BN_CLICKED(IDC_ACTION_NOTHING_RADIO, OnChangeAction)
	ON_BN_CLICKED(IDC_ACTION_REMOVE_ATTACK_RADIO, OnChangeAction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChallengeResponseDlg message handlers

BOOL CChallengeResponseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//"Start" aktivieren
	hCmark = AfxGetApp()->LoadStandardCursor(IDC_UPARROW);
	hCstandard = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); 
	ChangeMode(0);
	m_action=0;
	UpdateData(FALSE);
	
	// Add "About..." menu item to system menu.
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChallengeResponseDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//Inserted
		//Hintergrundfläche weiß
		CPaintDC dc(this);

		CBitmap bmp, *poldbmp;
		bmp.LoadBitmap(IDB_CR_BACKGROUND_BITMAP);

		CDC memdc;
		memdc.CreateCompatibleDC( &dc );
		poldbmp = memdc.SelectObject( &bmp );
		::StretchBlt(dc.m_hDC,135,10,635,380,memdc,0,0,520,370,SRCCOPY);
		::DeleteDC(memdc);
		::DeleteObject(bmp);
		
		CClientDC dc1(this);
		scenario.draw(dc1);

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChallengeResponseDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


int CChallengeResponseDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CChallengeResponseDlg::OnExitButton() 
{
	OnOK();
}

void CChallengeResponseDlg::ChangeMode(int mode)
{
	m_mode = mode;
	UpdateData(FALSE);
	ChangeScenario();
}

void CChallengeResponseDlg::ChangeScenario()
{
	KillTimer(1);
	UpdateData(TRUE);
	CClientDC dc(this);
	scenario.protocolRunning=FALSE;
	scenario.changeMode(m_mode,dc,m_modeText);
	UpdateData(FALSE);

}
void CChallengeResponseDlg::OnModeRadioButtons() 
{
	ChangeScenario();
}

void CChallengeResponseDlg::OnMouseMove(UINT nFlags, CPoint point) 
{

	
	//Debug: Koordinaten anzeigen
/*	CString a;
	char str1[10];
	char str2[10];
	UpdateData(TRUE);
	itoa(point.x,str1,10);
	itoa(point.y,str2,10);
	m_modeText=((CString)str1)+(CString)","+((CString)str2);
	UpdateData(FALSE);
*/	
	CClientDC dc(this);
	
	if (scenario.isMouseOverObject(m_action,point)){	
		
		::SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hCmark);
	}else{
		::SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)hCstandard);
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CChallengeResponseDlg::OnChangeAction() 
{
	UpdateData(TRUE);
	
}

void CChallengeResponseDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonDown(nFlags, point);
}

void CChallengeResponseDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	int error;
	error=scenario.mouseClick(m_action,point,dc);
	if (m_action==3){
		if (error==1){
			msg.LoadString(IDS_Message_ComputerToStrong);
			MessageBox(msg,"");
		}
		if (error==2){
			msg.LoadString(IDS_Message_NoConnectionToComputer);
			MessageBox(msg,"");
		}
	}
	
	// Maskierungsknopf überprüfen
	checkAttackerCanMask();
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CChallengeResponseDlg::OnAuthenticateClientButton() 
{
	authenticateAttacker = FALSE;
	startProtocol(authenticateAttacker);
}

void CChallengeResponseDlg::OnAuthenticateAttackerButton() 
{
	authenticateAttacker = TRUE;
	startProtocol(authenticateAttacker);	
}

void CChallengeResponseDlg::startProtocol(bool authenticateAttacker)
{
	int InstallResult;
	if (scenario.mode>0){
		if (scenario.protocolRunning){
			msg=(CString)"Protokoll läuft bereits!";
			MessageBox(msg,"");
		}else{
			scenario.protocolInitiated=FALSE;
			InstallResult=SetTimer(1,300,NULL);
			if (InstallResult==0){
				msg=(CString)"Timer kann nicht installiert werden!";
				MessageBox(msg,"");
			}else{
				scenario.initiateProtocol(authenticateAttacker);
				scenario.protocolInitiated=TRUE;
			}
		}
	}else{
		msg.LoadString(IDS_Message_NoScenarioChosen);
		MessageBox(msg,"");
	}

}

void CChallengeResponseDlg::OnDestroy() 
{
	KillTimer(1);
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CChallengeResponseDlg::OnTimer(UINT nIDEvent) 
{
	bool packetsLeft;
	CClientDC dc(this);
	if(scenario.protocolInitiated){
		scenario.drin=FALSE;
		packetsLeft=scenario.onTick(dc);
		if (packetsLeft==FALSE){
			KillTimer(1);
			if(scenario.protocolRunning==TRUE){
				scenario.protocolRunning=FALSE;
				msg.LoadString(IDS_Message_ProtocolInterrupted);
				MessageBox(msg,"");
			}else{
				if(scenario.authenticationFailed){
					msg.LoadString(IDS_Message_AuthenticationFailed);
					MessageBox(msg,"");
				}else{
					if (authenticateAttacker){
						msg.LoadString(IDS_Message_AuthenticationOfAttackerSuccessfull);
						MessageBox(msg,"");
					}else{
						if ((m_attackerMasked)&&(scenario.mode<6)){
							msg.LoadString(IDS_Message_ManInTheMiddleSuccessful);
							MessageBox(msg,"");
						}else{
							msg.LoadString(IDS_Message_AuthenticationOfClientSuccessful);
							MessageBox(msg,"");
						}
					}
				}
			}
		}
	}
	scenario.draw(dc);
	CDialog::OnTimer(nIDEvent);
}


void CChallengeResponseDlg::checkAttackerCanMask()
{
	//Maskierungsknopf an-/abschalten
	if(!scenario.attackerCanMask() && m_attackerMasked){
		msg.LoadString(IDS_Message_CannotMaskConnectionsMisconfiguration);
		MessageBox(msg,"");
		m_attackerMasked=FALSE;
		UpdateData(FALSE);
	}else{
		UpdateData(TRUE);
	}
}

void CChallengeResponseDlg::OnCheckMask() 
{
	if (scenario.protocolRunning){
		if (m_attackerMasked){
			m_attackerMasked=FALSE; // == UpdateData(TRUE);
		}else{
			m_attackerMasked=FALSE;
			UpdateData(FALSE);
			msg.LoadString(IDS_Message_MaskBeforeProtocolStart);
			MessageBox(msg,"");
		}
	}else{
		if(scenario.attackerCanMask()){
			m_attackerMasked=TRUE; // == UpdateData(TRUE);
		}else{
			m_attackerMasked=FALSE;
			UpdateData(FALSE);
			msg.LoadString(IDS_Message_CannotMaskConnectionsMisconfiguration);
			MessageBox(msg,"");
		}
	}
}



void CChallengeResponseDlg::OnScenarioHelpButton() 
{
	DWORD HelpID;
	switch(scenario.mode){
	case 0:
		HelpID = ID_CR_OVERVIEW+0x10000;		
		break;
	case 1:
		HelpID = ID_CR_USAGE+0x10000;
		break;
	case 2:
		HelpID = ID_CR_SZ_PASSWORDS+0x10000;
		break;
	case 3:
		HelpID = ID_CR_SZ_ONETIMEPASSWORDS+0x10000;
		break;
	case 4:
		HelpID = ID_CR_SZ_CRSYMMETRIC+0x10000;
		break;
	case 5:
		HelpID = ID_CR_SZ_CRASYMMETRIC+0x10000;
		break;
	case 6:
		HelpID = ID_CR_SZ_MUTUALAUTHENTICATION+0x10000;
		break;
	}		
	#if !defined(_MSC_VER) || _MSC_VER <= 1200		// HTML Help for VC++ 6.0
	theApp.WinHelp(HelpID, HELP_CONTEXT);
	#else											// HTML Help for VC++ .NET
	theApp.WinHelpInternal(HelpID, HELP_CONTEXT);	
	#endif
}


void CChallengeResponseDlg::OnResetButton() 
{
	
	int i;
	CClientDC dc(this);

	// load initial state of the scenarios
	if (scenario.mode!=0)
	{
		for(i=0;i<6;i++) // in place of i<6 it might be i<numPackets 
		{
			packets[i].visible=FALSE; // blend all packets
		}
		for(i=0;i<4;i++)
		{
			wires[i].connected=TRUE; // declare all connections, expect these to the attacker, as connected
		}
		for(i=4;i<6;i++)
		{
			wires[i].connected=FALSE; // do not display outgoing connections from the attacker 
		}
		for(i=0;i<5;i++)
		{
			computers[i].underAttack=FALSE; // display all stations black, expect the attacker´s computer
		}
		computers[5].underAttack=TRUE; // display attacker´s computer red
	}

	// redraw depending on the scenario
	switch(scenario.mode){
	case 0:		
		break;
	case 1:		
		scenario.draw(dc); // draw scenario
		ChangeMode(1);     // load labelling
		break;
	case 2:
		scenario.draw(dc);
		ChangeMode(2);
		break;
	case 3:
		scenario.draw(dc);
		ChangeMode(3);
		break;
	case 4:
		scenario.draw(dc);
		ChangeMode(4);
		break;
	case 5:
		scenario.draw(dc);
		ChangeMode(5);
		break;
	case 6:
		scenario.draw(dc);
		ChangeMode(6);
		break;
	}

	if (c_attackerMasked.GetCheck()==1) //If masking is activated, reset
	{
		c_attackerMasked.SetCheck(0);
		m_attackerMasked=FALSE;
	}
}


