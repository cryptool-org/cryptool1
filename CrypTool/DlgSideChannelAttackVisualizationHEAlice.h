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


#if !defined(AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEALICE_H__FDB140A3_568B_41A2_B227_55A36A2EF6A3__INCLUDED_)
#define AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEALICE_H__FDB140A3_568B_41A2_B227_55A36A2EF6A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSideChannelAttackVisualizationHEAlice.h : Header-Datei
//

#include "DlgSideChannelAttackVisualizationHE.h"
#include "SideChannelAttack.h"
#include "PictureEx.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSideChannelAttackVisualizationHEAlice 

class CDlgSideChannelAttackVisualizationHEAlice : public CDialog
{
private:
	CWnd* parent;
// Konstruktion
public:
	void updateDisplay();
	CDlgSideChannelAttackVisualizationHEAlice(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSideChannelAttackVisualizationHEAlice)
	enum { IDD = IDD_SIDECHANNELATTACKVISUALIZATION_HE_ALICE };
	CListBox	m_ControlTasks;
	CListCtrl	m_SessionKeyReceptionsList;
	CString	m_OriginalSessionKey;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSideChannelAttackVisualizationHEAlice)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSideChannelAttackVisualizationHEAlice)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEALICE_H__FDB140A3_568B_41A2_B227_55A36A2EF6A3__INCLUDED_
