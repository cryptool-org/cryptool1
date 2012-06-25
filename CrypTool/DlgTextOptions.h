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

#ifndef _DLGTEXTOPTIONS_H_
#define _DLGTEXTOPTIONS_H_

#include <list>

class CDlgTextOptions : public CDialog
{
	enum { IDD = IDD_TEXT_OPTIONS };

public:
	// construction
	CDlgTextOptions(CWnd *pParent = NULL);
	void         SetDefaultOptions();

protected:
	// initialization
	virtual BOOL OnInitDialog();
	// data exchange
	virtual void DoDataExchange(CDataExchange *pDX);
	// functions associated with standard buttons
	afx_msg void OnOK();
	afx_msg void OnCancel();
	// functions associated with check boxes
	afx_msg void OnCheckKeepUpperLowerCaseInformation();
	afx_msg void OnCheckDistinguishUpperLowerCase();
	afx_msg void OnCheckUpperCase();
	afx_msg void OnCheckPunctuation();
	afx_msg void OnCheckSpace();
	afx_msg void OnCheckLowerCase();
	afx_msg void OnCheckDigits();
	afx_msg void OnCheckUmlauts();
	afx_msg void OnCheckPlayfair();
	// misc functions
	afx_msg void OnUpdateEditAlphabet();
	afx_msg void OnUpdateEditSeparator();
	afx_msg void OnButtonRestoreStandard();
	afx_msg void OnButtonSearchReferenceFile();
	void updateAlphabetHeading();
	void updateCheckState();

	DECLARE_MESSAGE_MAP()

public:
	// access methods
	CString getTitle() { return title; }
	CString getReferenceFile() { return referenceFile; }
	const CString &getAlphabet(); 
   int            setAlphabet( CString &new_alphabet );
	CString &refAlphabet(); 
	void getAlphabetWithOptions(CString &AlphabetWithOptions);
	BOOL getDistinguishUpperLowerCase() { return distinguishUpperLowerCase; };
	BOOL getKeepCharactersNotPresentInAlphabetUnchanged() { return keepCharactersNotPresentInAlphabetUnchanged; };
	BOOL getKeepUpperLowerCaseInformation() { return keepUpperLowerCaseInformation; };
	BOOL getIgnoreCase() { return ignoreCase; };

private:
	// variables associated with the dialog resource
	CStatic	informationAlphabetSize;
	CEdit controlEditReferenceFile;
	CEdit controlEditAlphabet;
	// misc variables
	CString title;
	CString	separator;
	CString	alphabet;
	CString oldAlphabet;
	CString referenceFile;
	CString oldReferenceFile;
	// boolean variables
	BOOL keepCharactersNotPresentInAlphabetUnchanged;
	BOOL oldKeepCharactersNotPresentInAlphabetUnchanged;
	BOOL keepUpperLowerCaseInformation;
	BOOL oldKeepUpperLowerCaseInformation;
	BOOL distinguishUpperLowerCase;
	BOOL oldDistinguishUpperLowerCase;
	BOOL space;
	BOOL separateLetters;
	BOOL ignoreCase;
	// tri-state variables associated with the check boxes
	int upperCase;
	int lowerCase;
	int punctuation;
	int digits;
	int umlauts;
private:
	struct LanguageReferenceFile {
		// the name of the language
		CString language;
		// the path to the reference file associated with the language
		CString referenceFile;
	};
	std::list<LanguageReferenceFile> listLanguageReferenceFiles;
protected:
	CComboBox	controlComboBoxSelectReferenceFile;
	afx_msg void OnSelendokComboSelectReferenceFile();
	int selectedLanguageReferenceFile;
	int oldSelectedLanguageReferenceFile;
};

#endif