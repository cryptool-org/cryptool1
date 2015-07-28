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

#ifndef _DLGLENGTHOFANUMBER_
#define _DLGLENGTHOFANUMBER_

class CDlgLengthOfANumber : public CDialog
{
public:
	CDlgLengthOfANumber(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgLengthOfANumber();

// Dialogfelddaten
	enum { IDD = IDD_LENGTHOFANUMBER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnClickedRadioButtonNumberRepresentation();
	afx_msg void OnChangedNumber();
private:
	int numberRepresentation;
	CString stringNumber;
private:
	void convertNumberToRepresentation(const int _base);
	void updateNumberLengths();
	int calculateNumberLength(const int _base);

	DECLARE_MESSAGE_MAP()
};

#endif