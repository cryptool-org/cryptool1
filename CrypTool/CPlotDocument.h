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
