//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_DLGFORTSCHRITT_H__386CD5D9_F7C7_11D2_888E_00C04F795E28__INCLUDED_
#define AFX_DLGFORTSCHRITT_H__386CD5D9_F7C7_11D2_888E_00C04F795E28__INCLUDED_

// DlgFortschritt.h : Header-Datei
//

#include <afxmt.h>

/////////////////////////////////////////////////////////////////////////////
// CProgressModel

class CProgressModel
{
public:
	CProgressModel() { }
	virtual double getProgress() = 0; // 0.0 <= result <= 1.0
};


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowProgress 

class CDlgShowProgress : public CDialog
{
// Konstruktion
public:
	CDlgShowProgress(CWnd* pParent = NULL);   // Standardkonstruktor
	void Display();
	void Display(const char *title);
	void cancel( void );
	int m_displayed;
	int m_canceled;
	
	// old interface
	int Set(int pos);
	int Set(int pos, CString format);
	int Set(int pos, CString caption, CString format);

	// new MV interface
	void setFormat(UINT format) { m_format.LoadString(format); }
	void setFormat(LPCTSTR format) { m_format = format; }
	void setTitle(UINT title) { m_title.LoadString(title); }
	void setTitle(LPCTSTR title) { m_title = title; }
	void setModel(CProgressModel *model);
	void setModelTitleFormat(CProgressModel *model,UINT title, UINT format);
	void setModelTitleFormat(CProgressModel *model,LPCTSTR title, UINT format);
	void setModelTitleFormat(CProgressModel *model,UINT title, LPCTSTR format);
	void setModelTitleFormat(CProgressModel *model,LPCTSTR title, LPCTSTR format);
	void startClock();
	CString m_days, m_years;
#ifdef debugprogress
	FILE *debug;
#endif
// Dialogfelddaten
	//{{AFX_DATA(CDlgShowProgress)
	enum { IDD = IDD_SHOW_PROGRESS };
	CStatic	m_text_ctl;
	CProgressCtrl	m_Progress;
	CString	m_text;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgShowProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CString m_format;
	CString m_title;
	// old interface
	int m_pos;
	// new MV interface
	CProgressModel *m_model;
	clock_t m_clock0;
	LONGLONG m_hres_clock0;
	LONGLONG m_hres_cps;
	CString duration(double progress) const;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgShowProgress)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_old_pos;
	CCriticalSection Lock;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGFORTSCHRITT_H__386CD5D9_F7C7_11D2_888E_00C04F795E28__INCLUDED_
