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

#include"stdafx.h"
#include "DynTabCtrl.h"

/*
Autor Jens Weller aka phlox81
(C) 05/2004
Für Anregungen und Verbesserungen
bitte Mail an jensweller@gmx.de,
oder http://www.phlox81.de

  DynTabCtrl.cpp

*/

DynTabCtrl::DynTabCtrl(bool deltab):delete_tab(deltab)
{
	m_aktuellepos =0;
}

 DynTabCtrl::~DynTabCtrl()
{
	if(!m_tabs.empty())
	{
		for(unsigned int i =0; i < m_tabs.size(); i++)//vector freigeben
		{
			if(!m_tabs[i]->DestroyWindow())
				MessageBox("Freigeben des Tabsheets fehlgeschlagen");
			delete m_tabs[i];
		}
		m_tabs.clear();//vector leeren
	}
}

BEGIN_MESSAGE_MAP(DynTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CMyTab)
		ON_WM_LBUTTONDOWN()
		ON_WM_RBUTTONDOWN()
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
Korrekter Aufruf:
m_tab.InsertItem(new MyDlg(),"titel", IDD_MYDLG);
Klasse verwaltet die Pointer, und Löscht sie bei DeleteItem/Destruktor
*/
int DynTabCtrl::InsertItem(CDialog * dlg, CString titel, UINT ID)
{
	if(!dlg->Create(ID,this))
	{
		MessageBox("Create von " + titel +" Fehlgeschlagen");
		delete dlg;
		dlg =NULL;
		return FALSE;
	}
	if(m_tabs.empty())
	{
		dlg->ShowWindow(SW_SHOW);
	}
	else
		dlg->ShowWindow(SW_HIDE);
	m_tabs.push_back(dlg);
	m_titel.push_back(titel);
	SetRec();
	return (int)CTabCtrl::InsertItem(m_tabs.size()-1,titel);
}

CDialog* DynTabCtrl::GetTab(int itab)
{
	if((int)m_tabs.size() > itab && itab > -1)
		return m_tabs[itab];
	return NULL;
}


void DynTabCtrl::SetRec()
{
	CRect tabRec, itemRec;
	int nX, nY, nXz, nYz;
	GetClientRect(&tabRec);
	GetItemRect(0, &itemRec);
	nX=itemRec.left;
	nY=itemRec.bottom+1;
	nXz=tabRec.right-itemRec.left-1;
	nYz=tabRec.bottom-nY-1;
	if(!m_tabs.empty())
	{
		vector<CDialog*>::iterator itablist = m_tabs.begin();
		(*itablist)->SetWindowPos(&wndTop, nX, nY, nXz, nYz, SWP_SHOWWINDOW);
		if(m_tabs.size() > 1)
		{
			itablist++;
			for(; itablist != m_tabs.end(); itablist++)
			{
				(*itablist)->SetWindowPos(&wndTop, nX, nY, nXz, nYz, SWP_HIDEWINDOW);
			}
		}
	}
}

void DynTabCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CTabCtrl::OnLButtonDown(nFlags, point);
    if(m_aktuellepos != GetCurFocus())
    {
            m_tabs[m_aktuellepos]->ShowWindow(SW_HIDE);
            m_aktuellepos=GetCurFocus();
            m_tabs[m_aktuellepos]->ShowWindow(SW_SHOW);
            m_tabs[m_aktuellepos]->SetFocus();
    }
}

BOOL DynTabCtrl::DeleteItem(int nItem)
{
	if(nItem > -1 && nItem < (int)m_tabs.size())
	{
		if(CTabCtrl::DeleteItem(nItem))
		{
			// delete m_tabs[nItem];
			m_tabs.erase( m_tabs.begin() + nItem /* &m_tabs[nItem] */);
			m_titel.erase( m_titel.begin() + nItem /* &m_titel[nItem] */);
			delete m_tabs[nItem];
			if(!m_tabs.empty())
			{
				SetCurFocus(0);
				m_aktuellepos = 0;
				m_tabs[0]->ShowWindow(SW_SHOW);
				m_tabs[0]->SetFocus();
				m_tabs[0]->Invalidate();
			return TRUE;
			}
		}
	}
	return FALSE;
}

void DynTabCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(delete_tab)
	{
		CRect c;
		GetItemRect(GetCurFocus(),&c);
		if(c.PtInRect(point))
		{
			CMenu m;
			ClientToScreen(&point);
			m.CreatePopupMenu();
			m.InsertMenu(0,MF_BYPOSITION,55555,"löschen");
			m.TrackPopupMenu(TPM_LEFTALIGN + TPM_LEFTBUTTON,point.x, point.y, this, NULL);
		}
	}
}

BOOL DynTabCtrl::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen

	if(wParam == 55555 && delete_tab)
	{
		DeleteItem(GetCurFocus());
	}
	return CTabCtrl::OnCommand(wParam, lParam);
}

void DynTabCtrl::SetDeleteTab(bool deltab)
{
	delete_tab = deltab;
}

bool DynTabCtrl::GetDeleteTab()
{
	return delete_tab;
}
