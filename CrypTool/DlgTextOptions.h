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

#ifndef _DLGTEXTOPTIONS_H_
#define _DLGTEXTOPTIONS_H_

class CDlgTextOptions : public CDialog
{
	enum { IDD = IDD_TEXT_OPTIONS };

public:
	// construction
	CDlgTextOptions(CWnd *pParent = NULL);

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
	CString &refAlphabet(); 
	void getAlphabetWithOptions(CString &AlphabetWithOptions);
	CString getSeparator() { return separator; }
	BOOL getSeparateLetters() { return separateLetters; };
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
	int	upperCase;
	int lowerCase;
	int punctuation;
	int digits;
	int umlauts;
};

#endif