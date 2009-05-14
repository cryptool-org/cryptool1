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

#ifndef DynTabCtrl_h
#define DynTabCtrl_h

#include <vector>
using namespace std;

/*
Autor Jens Weller aka phlox81
(C) 05/2004
Für Anregungen und Verbesserungen
bitte Mail an jensweller@gmx.de,
oder http://www.phlox81.de

  DynTabCtrl.h

*/

class DynTabCtrl : public CTabCtrl
{
	vector<CString> m_titel;
	vector<CDialog*> m_tabs;
	int m_aktuellepos;
	bool delete_tab;
public:
	bool GetDeleteTab();
	void SetDeleteTab(bool deltab);
	BOOL DeleteItem(int nItem);
	DynTabCtrl(bool deltab=false);
	virtual  ~DynTabCtrl();
	int InsertItem(CDialog * dlg, CString titel,UINT ID);
	CDialog* GetTab(int itab);
protected:
	// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CShowEdit)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	void SetRec();
	//{{AFX_MSG(CMyTab)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

#endif
