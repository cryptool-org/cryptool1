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

#if !defined(AFX_3DVISOPT_H__15C59C13_FFA8_4BC3_930C_4F19DDCD0199__INCLUDED_)
#define AFX_3DVISOPT_H__15C59C13_FFA8_4BC3_930C_4F19DDCD0199__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DVisOpt.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld C3DVisOpt 

class C3DVisOpt : public CDialog
{
// Konstruktion
public:
	unsigned short resolution, default_resolution;
	unsigned short density,    default_density;
	unsigned short shift,      default_shift;
	unsigned short wordsize,   default_wordsize;

	//C3DVisOpt(CWnd* pParent = NULL);   // Standardkonstruktor
	C3DVisOpt(CWnd* pParent, 
		unsigned short arg_res, 
		unsigned short arg_dens, 
		unsigned short arg_shift, 
		unsigned short arg_wordsize);

// Dialogfelddaten
	//{{AFX_DATA(C3DVisOpt)
	enum { IDD = IDD_SET_VISOPT };
	CButton	m_ButtonReset;
	CEdit	m_editShift;
	CEdit	m_editResolution;
	CEdit	m_editDensity;
	CButton	m_CtrlButtonWordSize;
	CSliderCtrl	m_CtrlSliderShift;
	CSliderCtrl	m_CtrlSliderDensity;
	CSliderCtrl	m_CtrlSliderResolution;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(C3DVisOpt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	void updateControls(void);
	void resetToDefaults(void);

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(C3DVisOpt)
	virtual BOOL OnInitDialog();
	afx_msg void OnReleasedcaptureSliderResolution(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderDensity(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderShift(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioWordsize1();
	afx_msg void OnRadioWordsize2();
	afx_msg void OnRadioWordsize4();
	afx_msg void OnButtonReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_3DVISOPT_H__15C59C13_FFA8_4BC3_930C_4F19DDCD0199__INCLUDED_
