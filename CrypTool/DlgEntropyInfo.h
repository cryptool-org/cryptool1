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

#if !defined(AFX_DLGENTROPYINFO_H__624CBB55_6E59_11D6_93AA_00B0D0161C45__INCLUDED_)
#define AFX_DLGENTROPYINFO_H__624CBB55_6E59_11D6_93AA_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEntropyInfo.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgEntropyInfo 

class CDlgEntropyInfo : public CDialog
{
// Konstruktion
public:
	CDlgEntropyInfo(CWnd* pParent = NULL);   // Standardkonstruktor

	CString m_oldtitle;
	// Dialogfelddaten
	//{{AFX_DATA(CDlgEntropyInfo)
	enum { IDD = IDD_ENTROPY_INFO };
	CStatic	m_ctrl_entropy_info;
	CStatic	m_ctrl_alphabet_info;
	CString	m_alphabet_info;
	CString	m_entropy_info;
	//}}AFX_DATA

	int    i_countAlphabet, i_characters;
	double d_maxEntropy, d_entropy;
	void   SetParameter( const char *oldtitle, 
						 int countAlphabet, int Characters,
		                 double maxEntropy, double Entropy )
	{
		m_oldtitle = oldtitle;
		i_countAlphabet = countAlphabet; i_characters = Characters;
		d_maxEntropy    = maxEntropy;    d_entropy    = Entropy;
	}
 
// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgEntropyInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgEntropyInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGENTROPYINFO_H__624CBB55_6E59_11D6_93AA_00B0D0161C45__INCLUDED_
