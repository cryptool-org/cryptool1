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

#if !defined(AFX_DLG_PARAM_H__91FFB993_588B_11D4_A054_002035F23D41__INCLUDED_)
#define AFX_DLG_PARAM_H__91FFB993_588B_11D4_A054_002035F23D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLG_param.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKeyParameter 

struct param
{
	char titel[10];
	L_NUMBER data[MAXLGTH];
};

class CDlgShowKeyParameter : public CDialog
{
// Konstruktion
public:
	CString m_Title;
	bool disableOkButton;
	CDlgShowKeyParameter(CWnd* pParent = NULL);   // Standardkonstruktor

	// flomar, 02/14/2012: new interface for setting modul and exponent
	CString m_modul;
	CString m_exponent;
	void setModul(L_NUMBER *_modul) {
		memcpy(m_data[0].data,_modul,MAXLGTH*sizeof(L_NUMBER));
	}
	void setExponent(L_NUMBER *_exponent) {
		memcpy(m_data[1].data,_exponent,MAXLGTH*sizeof(L_NUMBER));
	}

	struct param m_data[10];
	void settitel(char *);

// Dialogfelddaten
	//{{AFX_DATA(CDlgShowKeyParameter)
	enum { IDD = IDD_SHOW_KEY_PARAMETER };
	CButton	m_ctrlOK;
	int		m_radio;
	CString	m_titel;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgShowKeyParameter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgShowKeyParameter)
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_PARAM_H__91FFB993_588B_11D4_A054_002035F23D41__INCLUDED_
