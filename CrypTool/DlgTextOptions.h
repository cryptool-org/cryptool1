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

#include <vector>

class CDlgTextOptions : public CDialog {
	enum { IDD = IDD_TEXT_OPTIONS };
public:
	// Dialog construction and destruction.
	CDlgTextOptions(CWnd *pParent = NULL);
	virtual ~CDlgTextOptions();
public:
	// This function is invoked as soon as the path variable ("Pfad") 
	// has been set, it initializes the default options including the 
	// reference files (for which the path variable is required).
	void initialize();
public:
	// Returns a const reference to the alphabet.
	const CString &getAlphabet() const;
	// Returns a non-const reference to the alphabet.
	CString &getAlphabetReference();
	// Returns an alphabet based on the internal alphabet, but 
	// with the currently selected options applied.
	CString getAlphabetWithOptions() const;
	// Sets the new alphabet. Returns false if the new alphabet contains 
	// invalid characters (in which case the internal alphabet will not 
	// be changed), and returns true otherwise.
	bool setAlphabet(const CString &_alphabet);
	// Returns the full path of the language reference file.
	CString getReferenceFilePath() const;
	// Returns the name of the language reference file without any 
	// information about the path, compare "getReferenceFilePath".
	CString getReferenceFileName() const;
public:
	BOOL getKeepCharactersNotPresentInAlphabetUnchanged() const { return options.keepCharactersNotPresentInAlphabetUnchanged == 1; };
	BOOL getKeepUpperLowerCaseInformation() const { return options.keepUpperLowerCaseInformation == 1; };
	BOOL getDistinguishUpperLowerCase() const { return options.distinguishUpperLowerCase == 1; };
	BOOL getIgnoreCase() const { return options.distinguishUpperLowerCase == 0; };
public:
	CString getAllowedCharacters() const;
	CString getUpperCaseCharacters() const;
	CString getLowerCaseCharacters() const;
	CString getSpecialCharacters() const;
	CString getDigitCharacters() const;
	CString getUpperCaseUmlautCharacters() const;
	CString getLowerCaseUmlautCharacters() const;
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange *pDX);
	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnCheckKeepCharactersNotPresentInAlphabetUnchanged();
	afx_msg void OnCheckKeepUpperLowerCaseInformation();
	afx_msg void OnCheckDistinguishUpperLowerCase();
	afx_msg void OnCheckUpperCase();
	afx_msg void OnCheckLowerCase();
	afx_msg void OnCheckSpace();
	afx_msg void OnCheckSpecial();
	afx_msg void OnCheckDigits();
	afx_msg void OnCheckUmlauts();
protected:
	afx_msg void OnUpdateEditAlphabet();
	afx_msg void OnButtonSearchReferenceFile();
	afx_msg void OnComboSelectReferenceFile();
protected:
	afx_msg void OnButtonOK();
	afx_msg void OnButtonRestoreStandard();
	afx_msg void OnButtonCancel();
protected:
	CStatic	controlEditAlphabetHeading;
	CEdit controlEditAlphabet;
	CEdit controlEditReferenceFile;
	CComboBox controlComboBoxSelectReferenceFile;
private:
	// This function is called upon construction of the dialog, it initializes 
	// both the current and the old options to the same default values.
	void restoreDefaultOptions();
	// This function is invoked whenever the alphabet is changed to 
	// reflect the updated alphabet length towards the user.
	void updateEditAlphabetHeading();
	// This function is invoked to dynamically update tri-state controls 
	// based on the currently configured alphabet.
	void updateCheckState();
	// This function is invoked to dynamically enable/disable the OK 
	// button based on whether there is a valid reference file selected.
	void updateButtonOK();
private:
	// This struct is used for handling language reference files.
	struct ReferenceFile {
		CString name;
		CString path;
	};
	// This struct contains the options which can be manipulated through the 
	// user interface. Note that, besides a lot of configuration flags, it also 
	// contains all the reference files which the user can choose from.
	struct Options {
		Options() :
			keepCharactersNotPresentInAlphabetUnchanged(0),
			keepUpperLowerCaseInformation(0),
			distinguishUpperLowerCase(0),
			alphabetUpperCase(0),
			alphabetLowerCase(0),
			alphabetSpace(0),
			alphabetSpecial(0),
			alphabetDigits(0),
			alphabetUmlauts(0),
			alphabet(""),
			referenceFiles(std::vector<ReferenceFile>()),
			referenceFileIndex(0),
			referenceFile("") { }
		int keepCharactersNotPresentInAlphabetUnchanged;
		int keepUpperLowerCaseInformation;
		int distinguishUpperLowerCase;
		int alphabetUpperCase;
		int alphabetLowerCase;
		int alphabetSpace;
		int alphabetSpecial;
		int alphabetDigits;
		int alphabetUmlauts;
		CString alphabet;
		std::vector<ReferenceFile> referenceFiles;
		int referenceFileIndex;
		CString referenceFile;
	};
	// This function initializes the reference files for the specified options. 
	// This function should only be invoked once in the "initialize" function.
	void initializeReferenceFiles(Options &_options);
	// This function updates the user interface w/r/t the reference files, in 
	// other words both the file name for the currently selected reference file 
	// as well as the combo box are updated. Note that this function should 
	// not be called before "OnInitDialog" hasn't been called.
	void updateReferenceFiles(const Options &_options);
	// This function copies one set of options onto another.
	void copyOptions(const Options &_optionsSource, Options &_optionsTarget);
	// This variable contains the current options.
	Options options;
	// This variable contains the old options.
	Options optionsOld;
};

#endif