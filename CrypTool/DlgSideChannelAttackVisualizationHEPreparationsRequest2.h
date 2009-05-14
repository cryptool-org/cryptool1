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