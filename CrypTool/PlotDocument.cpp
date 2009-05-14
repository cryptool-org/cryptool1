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
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// PlotDoc.cpp : implementation of the CPlotDocument class
//

//#include <stdlib.h>
//#include <string.h>

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DialogeMessage.h"
#include "CPlotDocument.h"

/////////////////////////////////////////////////////////////////////////////
// CPlotDocument

IMPLEMENT_DYNCREATE(CPlotDocument, CAppDocument)

BEGIN_MESSAGE_MAP(CPlotDocument, CAppDocument)
	//{{AFX_MSG_MAP(CPlotDocument)
	ON_COMMAND(ID_PLOTBAR, OnPlotbar)
	ON_UPDATE_COMMAND_UI(ID_PLOTBAR, OnUpdatePlotbar)
	ON_COMMAND(ID_BARWIDTH, OnBarwidth)
	ON_UPDATE_COMMAND_UI(ID_GOTO_VATER, OnUpdateGotoVater)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlotDocument construction/destruction

CPlotDocument::CPlotDocument()
{
	m_bar_width = theApp.PlotOptions.m_bar_width;
	m_curve_width = theApp.PlotOptions.m_curve;
	m_nulllinie = theApp.PlotOptions.m_nulllinie;
	m_relativ = theApp.PlotOptions.m_relativ;
}

CPlotDocument::~CPlotDocument()
{
}

void CPlotDocument::Load_Values(CArchive& ar){
	char Buff1[255];
	char* pch1, * pch2;
	
	ValueType *aValue;
	int cnt;

	cnt=0;
	while( ar.ReadString(Buff1,80) != NULL){//jeweils die nächste Zeile lesen
		aValue = new ValueType;
		aValue->aString = NULL;

		aValue->x = strtod(Buff1, &pch1);
		aValue->y = strtod(pch1, &pch2);
		if(pch1==pch2) {
			aValue->y = aValue->x;
			aValue->x = ++cnt;
		}
		m_ValueList.AddItem(aValue);

		memset(Buff1,0,255);
	}
}	

/////////////////////////////////////////////////////////////////////////////
// CPlotDocument AxisInfo
// reads the details for axis labeling from an extra temp file
void  CPlotDocument::x_axis_add(double x){
		ValueType *anItem1, *anItem2, *anItem3;
		char buffer[255];
		int len;

		anItem1 = new ValueType;
		anItem1->aString = NULL;
		anItem2 = new ValueType;
		anItem2->aString = NULL;
		anItem3 = new ValueType;
		anItem3->aString = NULL;

		anItem1->aPoint.x = anItem2->aPoint.x = (long)(x * m_xfactor) - m_xa;
		anItem1->x = anItem2->x = anItem1->aPoint.x;
		anItem1->aPoint.y = Y_BOTTOM - PIN_LEN;
		anItem1->y = Y_BOTTOM;

		anItem2->aPoint.y = LOG_DISPL_DIM_Y - Y_TOP + PIN_LEN;
		anItem2->y = LOG_DISPL_DIM_Y - Y_TOP;

		m_AxisList.AddItem(anItem1);	
		m_AxisList.AddItem(anItem2);	

		anItem3->aPoint.y = Y_BOTTOM - TEXT_DIST;
		anItem3->aPoint.x = anItem1->aPoint.x;

		if(m_xchar == '0') sprintf(buffer, "%d", (int) x); // print figures
		else sprintf(buffer, "%c", theApp.TextOptions.getAlphabet()[(int)x-1] /*m_xchar + (int) x*/); // print capital letters 

		anItem3->x = len = strlen(buffer);

		anItem3->aString=new char[len];
		strncpy(anItem3->aString, buffer,len);
		anItem3->y = 0;

		m_TextList.AddItem(anItem3);
}

void  CPlotDocument::y_axis_add(double y, double y_inc){
	ValueType *anItem1, *anItem2, *anItem3;
	char buffer[255];
	int len, prec;

		for(prec=0;prec<8;prec++) {
			if(y_inc == floor(y_inc)) break;
			y_inc *= 10.0;
		}

		anItem1 = new ValueType;
		anItem1->aString = NULL;
		anItem2 = new ValueType;
		anItem2->aString = NULL;
		anItem3 = new ValueType;
		anItem3->aString = NULL;

		anItem1->aPoint.y = anItem2->aPoint.y = (long)(y * m_yfactor) - m_ya;
		anItem1->y = anItem2->y = anItem1->aPoint.y;
		anItem1->aPoint.x = X_LEFT - PIN_LEN;
		anItem1->x = X_LEFT - PIN_LEN/3 ;

		anItem2->aPoint.x = LOG_DISPL_DIM_X - X_RIGHT + PIN_LEN;
		anItem2->x = LOG_DISPL_DIM_X - X_RIGHT + PIN_LEN/3 ;

		m_AxisList.AddItem(anItem1);	
		m_AxisList.AddItem(anItem2);	

		anItem3->aPoint.x = X_LEFT - TEXT_DIST;
		anItem3->aPoint.y = anItem1->aPoint.y;
		sprintf(buffer, "%.*f", prec, y);
		anItem3->x = len = strlen(buffer);
		anItem3->aString=new char[len];
		strncpy(anItem3->aString, buffer,len);
		anItem3->y = 1;

		m_TextList.AddItem(anItem3);
}



void CPlotDocument::Load_AxisInfo(){
	double x_0, x_1, x_inc, t;
	double y_0, y_1, y_inc, s;
	int x_n, y_n, k, l, j;

	int deltas[]={1,2,5,10,20,25,50,100,200,250,500,1000,2000,2500,5000,10000,20000,25000,50000,100000,200000,250000,500000,1000000,2000000,2500000,5000000};

	for(j=0;j<27;j++) if ((m_xmax+1)/deltas[j]<12) break;

	x_0 = m_xmin;
	t = (int) ceil((x_0 + ((deltas[j]+1)/2)) / deltas[j]);
	x_1 = t*deltas[j];
	x_inc = deltas[j];
	x_n = ((int)(m_xmax - x_1)) / deltas[j] + 1;
//	x_n = (int)(m_xmax + 1 - deltas[j] / 2) / deltas[j] + 1;// letzte  +1 ist von Doberenz

	j = (int) log10(m_ymax-m_ymin)-1;
	s = pow((double)10,(double)j);
	for(j=0; j<12; j++) if ((m_ymax - m_ymin)/(s*deltas[j])<12) break;
	k = (int) (m_ymin/(s*deltas[j]));
	l = (int) (m_ymax/(s*deltas[j])+1);

	y_inc = s * deltas[j];
	if ( y_inc < 1.0 ) y_inc = 1.0;  // ACHTUNG !!! y-Skalierung kleiner 1 unterdrücken

	if ((int)(m_ymin*10/y_inc)!=0)
		t = (int)(m_ymin/y_inc + 1);
	else
		t = 0;
	y_0 = t*y_inc;
	y_1 = y_0+y_inc;
	y_n = ((int)((m_ymax - y_1) / y_inc)) + 1;
//	y_0 = s * deltas[j] * k; //m_ymin;
//	y_1 = s * deltas[j] * (k+1);
//	y_inc = s * deltas[j];
//	y_n = l - k - 1; // -1 ist von Doberenz

	//m_continuous = 0;

//I) All the stuff for the X Axis

	if(m_xchar!='0') {
		x_0=1;
		x_1=3;
		x_inc=2;
		x_n=(theApp.TextOptions.getAlphabet().GetLength() - 1)/ 2;
	}

	x_axis_add(x_0);

	int i;
	for (i=0; i<x_n; i++){
		x_axis_add(x_1);
		x_1 += x_inc;
	}
		
//II) All the stuff for the Y Axis and other right aligned text


	y_axis_add(y_0, y_inc);

	for (i=0; i<y_n; i++){
		y_axis_add(y_1, y_inc);
		y_1+=y_inc;
	}

}


/////////////////////////////////////////////////////////////////////////////
// CPlotDocument value convertion
// converts given values for x and y into logical coordinates 

void CPlotDocument::Convert_Values(){

//I) find the min and max of x and y
	ValueType *anItem;

	m_ValueList.SetFirstItem();

	if(m_ValueList.GetNextItem(&anItem)){
		m_xmin = m_xmax = anItem->x;
		m_ymin = m_ymax = anItem->y;
			
		while(m_ValueList.GetNextItem(&anItem)){
			m_xmax = max(m_xmax, anItem->x);
			m_ymax = max(m_ymax, anItem->y);
			m_xmin = min(m_xmin, anItem->x);
			m_ymin = min(m_ymin, anItem->y);
		}
	}
	if (m_nulllinie)
		m_ymin=0;
	/* kleiner unschöner Hack um das binäre Histogram verarbeiten zu können ... den 
		wertebereich von 1 bis 256 auf 0 bis 255 verschieben */
	if((m_xmin==1) && (m_xmax==256)) {
		m_xmin=0;
		m_xmax=255;
	}
	if (m_ymin >= m_ymax)
	{
		m_ymax = m_ymin +1.0;
		if ( m_ymin >= 1.0 ) m_ymin -= 1.0;
		else if ( m_ymin > 0 ) m_ymin = 0.0;
	}

//II) compute some factors
	/*
	real x values 
	              /   delta_x_real   \
	|------------|--------------------|----------------
	0          x_real_min          x_real_max


	logical x values
	 /           delta_x_log           \
    |-----------------------------------|----------------
	0 (x_log_min)                    x_log_max

	 x_log = (x_real - x_real_min) * delta_x_log / delta_x_real
	
	e.g. m_xfactor  equals  delta_x_log / delta_x_real
		 m_xa  equals  x_real_min * delta_x_log / delta_x_real
	
	*/

	m_xfactor = (LOG_DISPL_DIM_X - X_LEFT - X_RIGHT) / ((m_xmax - m_xmin)*(X_PADDING/50.00 + 1));
	m_yfactor = (LOG_DISPL_DIM_Y - Y_BOTTOM - Y_TOP) / ((m_ymax - m_ymin)*(Y_PADDING/50.00 + 1));

	m_xa = (long) ((m_xmin - ((m_xmax - m_xmin) * X_PADDING/100))* m_xfactor) - X_LEFT;
	m_ya = (long) ((m_ymin - ((m_ymax - m_ymin) * Y_PADDING/100))* m_yfactor) - Y_BOTTOM;

//III) compute the logical values for each pair of x and y
	m_ValueList.SetFirstItem();

	while(m_ValueList.GetNextItem(&anItem)){
		anItem->aPoint.x = (long)(anItem->x * m_xfactor) - m_xa;
		anItem->aPoint.y = (long)(anItem->y * m_yfactor) - m_ya;
	}
}

	
	
/////////////////////////////////////////////////////////////////////////////
// CPlotDocument serialization


void CPlotDocument::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		char name[128];
		CFile f;

		Load_Values(ar); // read them from the file into a list
		Convert_Values(); // convert the values into logical display coordinates
		strcpy(name, ar.m_strFileName);
		name[strlen(name)-4]=0x0;
		if( !f.Open( name, CFile::modeRead ) )
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_HISTOGRAM_XLABEL,pc_str,STR_LAENGE_STRING_TABLE);
			m_xlabel = pc_str;
			LoadString(AfxGetInstanceHandle(),IDS_STRING_HISTOGRAM_YLABEL,pc_str,STR_LAENGE_STRING_TABLE);
			m_ylabel = pc_str;
			LoadString(AfxGetInstanceHandle(),IDS_STRING_HISTOGRAM_HEADING,pc_str,STR_LAENGE_STRING_TABLE);
			m_headline = pc_str;
			m_continuous = 0;
			m_ychar = 0x30;
			m_xchar = 0x40;
		}
		else
		{
// Read values from a tmp file
			CArchive tmp( &f, CArchive::load);	
			tmp >> m_headline >> m_xlabel >> m_ylabel;	
			tmp >> m_continuous >> m_xchar >> m_ychar;
			tmp.Close(); f.Close();	
		}
		Load_AxisInfo();
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPlotDocument diagnostics

#ifdef _DEBUG
void CPlotDocument::AssertValid() const
{
	CAppDocument::AssertValid();
}

void CPlotDocument::Dump(CDumpContext& dc) const
{
	CAppDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPlotDocument commands

BOOL CPlotDocument::OnNewDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//return CAppDocument::OnNewDocument();
	return FALSE;
}

void CPlotDocument::OnPlotbar() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	m_continuous = (m_continuous + 1 ) % 2;
	UpdateAllViews(NULL);

}

void CPlotDocument::OnUpdatePlotbar(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen
		pCmdUI->SetCheck(m_continuous==0);

}
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld plot_opt_dlg 


plot_opt_dlg::plot_opt_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(plot_opt_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(plot_opt_dlg)
	m_bar_width = 1;
	m_curve = 1;
	m_nulllinie = FALSE;
	m_relativ = FALSE;
	//}}AFX_DATA_INIT
}

void plot_opt_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(plot_opt_dlg)
	DDX_Text(pDX, IDC_EDIT1, m_bar_width);
	DDV_MinMaxInt(pDX, m_bar_width, 0, 99);
	DDX_Text(pDX, IDC_EDIT2, m_curve);
	DDV_MinMaxInt(pDX, m_curve, 0, 99);
	DDX_Check(pDX, IDC_CHECK1, m_nulllinie);
	DDX_Check(pDX, IDC_CHECK2, m_relativ);
	//}}AFX_DATA_MAP

}

BEGIN_MESSAGE_MAP(plot_opt_dlg, CDialog)
	//{{AFX_MSG_MAP(plot_opt_dlg)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnChangeEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnChangeEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten plot_opt_dlg 


void CPlotDocument::OnBarwidth() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen

	plot_opt_dlg dlg;

	dlg.m_bar_width = m_bar_width;
	dlg.m_curve = m_curve_width;
	dlg.m_nulllinie = m_nulllinie;
	dlg.m_relativ = m_relativ;
	if(dlg.DoModal()==IDOK)
	{
		m_bar_width = dlg.m_bar_width;
		m_curve_width = dlg.m_curve;
		m_nulllinie = dlg.m_nulllinie;
		m_relativ = dlg.m_relativ;
	}
	Convert_Values();
	m_TextList.DelAll();
	m_AxisList.DelAll();
	Load_AxisInfo();
	UpdateAllViews(NULL);
}


void CPlotDocument::OnUpdateGotoVater(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen

	if(IsWindow(hWndVaterFenster))
	{
        pCmdUI->Enable(TRUE);
	}
	else
	{
        pCmdUI->Enable(FALSE);
	}
}

void plot_opt_dlg::OnChangeEdit2() 
{
	UpdateData(TRUE);
	if(m_curve>10)
	{
		Message(IDS_STRING_UPPERBOUND_GRAPHWIDTH,MB_ICONEXCLAMATION|MB_OK);
		m_curve=10;
	}
	else if (m_curve<1)
	{
		Message(IDS_STRING_LOWERBOUND_GRAPHWIDTH,MB_ICONEXCLAMATION|MB_OK);
		m_curve=1;
	}
	UpdateData(FALSE);
}

void plot_opt_dlg::OnChangeEdit1() 
{
	UpdateData(TRUE);
	if(m_bar_width>10)
	{
		Message(IDS_STRING_UPPER_BOUND_LINEWIDTH,MB_ICONEXCLAMATION|MB_OK);
		m_bar_width=10;
	}
	else if (m_bar_width<1)
	{
		Message(IDS_STRING_LOWER_BOUND_LINEWIDTH,MB_ICONEXCLAMATION|MB_OK);
		m_bar_width=1;
	}
	UpdateData(FALSE);

}
