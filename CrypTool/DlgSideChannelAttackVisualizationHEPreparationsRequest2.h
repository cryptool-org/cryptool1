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


#ifndef _DLGSIDECHANNELATTACKVISUALIZATIONHEPREPARATIONSREQUEST2_H_
#define _DLGSIDECHANNELATTACKVISUALIZATIONHEPREPARATIONSREQUEST2_H_

// CDlgSideChannelAttackVisualizationHEPreparationsRequest2 dialog

class CDlgSideChannelAttackVisualizationHEPreparationsRequest2 : public CDialog
{
	DECLARE_DYNCREATE(CDlgSideChannelAttackVisualizationHEPreparationsRequest2)

public:
	CDlgSideChannelAttackVisualizationHEPreparationsRequest2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSideChannelAttackVisualizationHEPreparationsRequest2();

// Dialog Data
	enum { IDD = IDD_SIDECHANNELATTACKVISUALIZATION_HE_PREPARATIONS_REQUEST_2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	bool radioChoice1;
	bool radioChoice2;
	bool radioChoice3;
	afx_msg void OnBnClickedRadioChoice1();
	afx_msg void OnBnClickedRadioChoice2();
	afx_msg void OnBnClickedRadioChoice3();
};

#endif