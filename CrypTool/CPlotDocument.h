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
// PlotDoc.h : interface of the CPlotDocument class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef PLOTDOC_H
#define PLOTDOC_H

#include "ValueList.h"
#include "AppDocument.h"

// all following values are logical coordinates
#define LOG_DISPL_DIM_X 1280
#define LOG_DISPL_DIM_Y 1280

#define X_LEFT 200		// distances of the diagram area from the Top, Bottom, ... 
#define Y_BOTTOM 200
#define X_RIGHT 50
#define Y_TOP 200		

#define PIN_LEN 10		// length of the AXIS pins
#define TEXT_DIST 40	// distance between the AXIS and the labeling numbers
#define X_PADDING 5		// the max and min values have a distance of 5 % to the diagram boarder
#define Y_PADDING 5

class CPlotDocument : public CAppDocument
{
protected: // create from serialization only
	CPlotDocument();
	DECLARE_DYNCREATE(CPlotDocument)

// Attributes
public:
	CValueList m_ValueList;
	CValueList m_AxisList;
	CValueList m_TextList;
	
	CString m_xlabel, m_ylabel, m_headline;
	double m_xfactor, m_yfactor;
	long m_xa, m_ya;
	double m_xmax, m_xmin, m_ymax, m_ymin;
	char m_xchar, m_ychar;
	int m_continuous;
	BOOL m_relativ,m_nulllinie;
	int m_bar_width, m_curve_width;
// Operations
public:
	void Load_Values(CArchive& ar);
	void Load_AxisInfo();
	void Convert_Values();
	void  x_axis_add(double);
	void  y_axis_add(double, double);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlotDocument)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL
	

// Implementation
public:
	virtual ~CPlotDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPlotDocument)
	afx_msg void OnPlotbar();
	afx_msg void OnUpdatePlotbar(CCmdUI* pCmdUI);
	afx_msg void OnBarwidth();
	afx_msg void OnUpdateGotoVater(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld plot_opt_dlg 

class plot_opt_dlg : public CDialog
{
// Konstruktion
public:
	plot_opt_dlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(plot_opt_dlg)
	enum { IDD = IDD_DIALOG_PLOT_PARAM };
	int		m_bar_width;
	int		m_curve;
	BOOL	m_nulllinie;
	BOOL	m_relativ;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(plot_opt_dlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(plot_opt_dlg)
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif /* PLOTDOC_H */
