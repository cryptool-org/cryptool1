//////////////////////////////////////////////////////////////////
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Thomas Gauweiler 2001
//////////////////////////////////////////////////////////////////

// DialogPeriodeOutput.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "fileutil.h"
#include "DialogPeriodeOutput.h"
#include "zzahlanalyse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogPeriodeOutput 


CDialogPeriodeOutput::CDialogPeriodeOutput(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPeriodeOutput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogPeriodeOutput)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}

void CDialogPeriodeOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPeriodeOutput)
	DDX_Control(pDX, IDC_LIST_KEYS, m_listview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogPeriodeOutput, CDialog)
	//{{AFX_MSG_MAP(CDialogPeriodeOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDialogPeriodeOutput 

BOOL CDialogPeriodeOutput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	// m_listview in Report-Mode initialisieren

	int colWidth = 100;  // Spaltenbreite in Pixel

	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_NO,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 0, pc_str, LVCFMT_LEFT, colWidth-70 , 0); // Nr

	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_OFFSET,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, colWidth-60 , 1); // Offset

	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 2, pc_str, LVCFMT_LEFT, colWidth-55 , 2); // Länge

	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_PCNT,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 3, pc_str, LVCFMT_LEFT, colWidth-20 , 3); // Periodenzahl
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_TXT,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 4, pc_str, LVCFMT_LEFT, colWidth+40 , 4); // Perioden Inhalt Klartext
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_HEX,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 5, pc_str, LVCFMT_LEFT, colWidth+300 , 5); // Perioden Inhalt Hexdump

	for (int i=0; i<zahlenanalyse->cnt_periodResults; i++) { 
		sprintf(pc_str1,"%d", i+1);
		int j = m_listview.InsertItem (i, pc_str1);				// <- dafür muß es eine Alternative geben!
		sprintf(pc_str1,"%d", zahlenanalyse->periodResults[i].offset+1);
		m_listview.SetItemText (j, 1, pc_str1);
		sprintf(pc_str1,"%d", zahlenanalyse->periodResults[i].length);
		m_listview.SetItemText (j, 2, pc_str1);
		sprintf(pc_str1,"%d", zahlenanalyse->periodResults[i].repeated+1);
		m_listview.SetItemText (j, 3, pc_str1);

		pc_str1[0]='\0';
		char s [PA_MAXPRINTLENGTH*4+10]; s[0]='\0';
		int len = (zahlenanalyse->periodResults[i].length)<PA_MAXPRINTLENGTH ? zahlenanalyse->periodResults[i].length : PA_MAXPRINTLENGTH;
		for (int k=0; k<len; k++) {
			s[k] = IsText(zahlenanalyse->periodResults[i].str[k]) ? zahlenanalyse->periodResults[i].str[k] : '.';
			sprintf(pc_str1,"%s %02.2X", pc_str1, (unsigned char)zahlenanalyse->periodResults[i].str[k]);
		}
		s[len]='\0';

		m_listview.SetItemText (j, 4, s);
		m_listview.SetItemText (j, 5, pc_str1);
	}


	// m_listview.SortItems(
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
