//{{AFX_INCLUDES()
#include "Trapezeditor.h"
//}}AFX_INCLUDES
#if !defined(AFX_EDITORDIALOG_H__FDEB90C8_51BD_40C3_BA23_212689B85213__INCLUDED_)
#define AFX_EDITORDIALOG_H__FDEB90C8_51BD_40C3_BA23_212689B85213__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditorDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditorDialog dialog
class CVolumeRenderer;
 
class CEditorDialog : public CDialog
{
// Construction
public:
	void setColorTable256(unsigned char *);
	void setHistogram256(float *);
	void Create();
	CEditorDialog(CVolumeRenderer *pVolRen, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditorDialog)
	enum { IDD = IDD_EDITOR };
	CTrapezEditor	m_ctrlTFEditor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditorDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditorDialog)
	afx_msg void OnColorTableChanged();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CVolumeRenderer *m_pVolRen;
	short m_nMode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITORDIALOG_H__FDEB90C8_51BD_40C3_BA23_212689B85213__INCLUDED_)
