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
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Thomas Gauweiler 2001
//////////////////////////////////////////////////////////////////

// DialogPeriodeOutput.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "FileTools.h"
#include "DlgPeriodicityAnalysis.h"
#include "RandomAnalysisTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgPeriodicityAnalysis 


CDlgPeriodicityAnalysis::CDlgPeriodicityAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPeriodicityAnalysis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPeriodicityAnalysis)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	OldTitle = 0;
}

CDlgPeriodicityAnalysis::~CDlgPeriodicityAnalysis()
{
	if ( OldTitle )
		free(OldTitle);
}

void CDlgPeriodicityAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPeriodicityAnalysis)
	DDX_Control(pDX, IDC_LIST_KEYS, m_listview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPeriodicityAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgPeriodicityAnalysis)
	ON_BN_CLICKED(IDOK, OnSaveList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgPeriodicityAnalysis 

BOOL CDlgPeriodicityAnalysis::OnInitDialog() 
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

	for (int i=zahlenanalyse->cnt_periodResults-1; i>=0; i--)
	{ 
		sprintf(pc_str1,"%d", zahlenanalyse->cnt_periodResults-i);
		int j = m_listview.InsertItem (zahlenanalyse->cnt_periodResults-i-1, pc_str1);
		sprintf(pc_str1,"%d", zahlenanalyse->periodResults[i].offset+1);
		m_listview.SetItemText (j, 1, pc_str1);
		sprintf(pc_str1,"%d", zahlenanalyse->periodResults[i].length);
		m_listview.SetItemText (j, 2, pc_str1);
		sprintf(pc_str1,"%d", zahlenanalyse->periodResults[i].repeated+1);
		m_listview.SetItemText (j, 3, pc_str1);

		pc_str1[0]='\0';
		char s [PA_MAXPRINTLENGTH*4+10]; s[0]='\0';
		int len = (zahlenanalyse->periodResults[i].length)<PA_MAXPRINTLENGTH ? zahlenanalyse->periodResults[i].length : PA_MAXPRINTLENGTH;
		for (int k=0; k<len; k++)
		{
			s[k] = IsText(zahlenanalyse->periodResults[i].str[k]) ? zahlenanalyse->periodResults[i].str[k] : '.';
			sprintf(pc_str1,"%s %02.2X", pc_str1, (unsigned char)zahlenanalyse->periodResults[i].str[k]);
		}
		s[len]='\0';

		m_listview.SetItemText (j, 4, s);
		m_listview.SetItemText (j, 5, pc_str1);
	}
/*
	for (int i = 0; i < zahlenanalyse->cnt_periodResults; i ++)
	{ 
		sprintf(pc_str1,"%d", zahlenanalyse->cnt_periodResults-i);
		int j = m_listview.InsertItem (zahlenanalyse->cnt_periodResults-i-1, pc_str1);
		sprintf(pc_str1,"%d", zahlenanalyse->periodResults[i].offset+1);
		m_listview.SetItemText (j, 1, pc_str1);
		sprintf(pc_str1,"%d", zahlenanalyse->periodResults[i].length);
		m_listview.SetItemText (j, 2, pc_str1);
		sprintf(pc_str1,"%d", zahlenanalyse->periodResults[i].repeated+1);
		m_listview.SetItemText (j, 3, pc_str1);

		pc_str1[0]='\0';
		char s [PA_MAXPRINTLENGTH*4+10]; s[0]='\0';
		int len = (zahlenanalyse->periodResults[i].length)<PA_MAXPRINTLENGTH ? zahlenanalyse->periodResults[i].length : PA_MAXPRINTLENGTH;
		for (int k=0; k<len; k++)
		{
			s[k] = IsText(zahlenanalyse->periodResults[i].str[k]) ? zahlenanalyse->periodResults[i].str[k] : '.';
			sprintf(pc_str1,"%s %02.2X", pc_str1, (unsigned char)zahlenanalyse->periodResults[i].str[k]);
		}
		s[len]='\0';

		m_listview.SetItemText (j, 4, s);
		m_listview.SetItemText (j, 5, pc_str1);
	}*/


	// m_listview.SortItems(
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgPeriodicityAnalysis::OnSaveList() 
{
	char line[1024], header[256];
	UpdateData(TRUE);
	SHOW_HOUR_GLASS
	// b_SaveFactorList = true;
	
	GetTmpName(outfile,"cry",".tmp");
	ofstream f_details(outfile);

	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_TITLE,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(header, pc_str, OldTitle);
	f_details << header << "\n";
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_HEADER,pc_str,STR_LAENGE_STRING_TABLE);
	f_details << pc_str;

	int maxtxtlen = (zahlenanalyse->periodResults[zahlenanalyse->cnt_periodResults-1].length<PA_MAXPRINTLENGTH) ? 
		             zahlenanalyse->periodResults[zahlenanalyse->cnt_periodResults-1].length : PA_MAXPRINTLENGTH;
	for (int i=zahlenanalyse->cnt_periodResults-1; i>=0; i--) {
		line[0] = '\0';
		f_details << zahlenanalyse->cnt_periodResults-i << "\t";
		f_details << zahlenanalyse->periodResults[i].offset+1 << "\t";
		f_details << zahlenanalyse->periodResults[i].length << "\t";
		f_details << zahlenanalyse->periodResults[i].repeated+1 << "\t\t";

		pc_str1[0]='\0';
		char s [PA_MAXPRINTLENGTH*4+10]; s[0]='\0';
		int len = (zahlenanalyse->periodResults[i].length)<PA_MAXPRINTLENGTH ? 
			       zahlenanalyse->periodResults[i].length : PA_MAXPRINTLENGTH;
		for (int k=0; k<len; k++) {
			s[k] = IsText(zahlenanalyse->periodResults[i].str[k]) ? 
				    zahlenanalyse->periodResults[i].str[k] : '.';
			sprintf(pc_str1,"%s %02.2X", pc_str1, (unsigned char)zahlenanalyse->periodResults[i].str[k]);
		}
		s[len]='\0';
		f_details << s << "\t";
		for (int j= (maxtxtlen - zahlenanalyse->periodResults[i].length+7) / 8; j>0; j--) 
			f_details << "\t";
		f_details << pc_str1 << "\n";
	}

	f_details.close();
	{
		theApp.ThreadOpenDocumentFileNoMRU(outfile, header);
		remove(outfile);
	}
	CDialog::OnOK();	
}
