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

#ifndef _DLGPASSWORDENTROPY_
#define _DLGPASSWORDENTROPY_

class CDlgPasswordEntropy : public CDialog
{
public:
	CDlgPasswordEntropy(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgPasswordEntropy();

// Dialogfelddaten
	enum { IDD = IDD_PASSWORDENTROPY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	virtual void EditPasswordBitLengthChanged();
	virtual void EditPasswordAlphabetChanged();

	virtual void CheckBoxesAlphabetChanged();

	void updatePasswordLength();

	afx_msg void OnBnClickedGeneratepassword();
	afx_msg void OnBnClickedTextoptions();
	afx_msg void OnBnClickedMeasurepasswordquality();

	void updateGUI();

	DECLARE_MESSAGE_MAP()

	CEdit editControlPasswordBitLength;
	CEdit editControlPasswordAlphabet;

	CString stringPasswordBitLength;
	CString stringPasswordAlphabet;
	CString stringPasswordLength;
	CString stringPasswordExample;

	BOOL useCrypToolAlphabet;
	BOOL useNonConfusableCharactersWrittenTransmission;
	BOOL useNonConfusableCharactersTelephonicTransmission;
	BOOL useWLANAlphabet;

	CString computeAlphabetUnionSet(const CString alphabetOne, const CString alphabetTwo);	
};

#endif