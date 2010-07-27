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

//#if !defined(AFX_DLGROT13CAESAR_H__F55065A9_4E94_4628_8094_05713C56FF7C__INCLUDED_)
//#define AFX_DLGROT13CAESAR_H__F55065A9_4E94_4628_8094_05713C56FF7C__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
// DlgRot13Caesar.h : Header-Datei
//

#ifndef DIA1_H
#define DIA1_H
// dia1.h : header file
//

#include "afxwin.h"
#include "KeyRepository.h"

#define MAX_VIGENERE	1024
#define MAX_DISPLAY		40
#define MAX_EXTRA		3
#define FILL_CHAR		'.'
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRot13Caesar 

#include "DlgTextOptions.h"
#include "ToolTipButton.h"

// this struct implements the "new" Caesar key with the added key offset
struct CaesarKey {
	char key;
	unsigned int offset;

	CaesarKey() {
		key = 0;
		offset = 0;
	};
};

class CDlgRot13Caesar : public CDialog
{
public:
	//{{AFX_DATA(CDlgRot13Caesar)
	enum { IDD = IDD_ROT13_CAESAR };
	//}}AFX_DATA

public:
	// default constructor
	CDlgRot13Caesar(CWnd* pParent = NULL);

	// this function returns the key that was chosen by the user (including the key offset)
	CString GetTheKey() {
		CString theKey = alphabeticKey;
		if(keyOffsetZero) theKey.Append(", KEY OFFSET: 0");
		else theKey.Append(", KEY OFFSET: 1");
		return theKey; 
	};
	// this function indicates whether we are in encryption or decryption mode
    bool GetModeDecryption() { return modeDecryption; };
	// this function returns the encryption type (here, this is either Casear or ROT13)
	unsigned int GetTypeEncryption() { return typeEncryption; };
	// this function indicates the key offset (here, the key offset is either zero or one)
	bool IsKeyOffsetZero() { return keyOffsetZero; };

protected:
	//{{AFX_VIRTUAL(CDlgRot13Caesar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDlgRot13Caesar)
	virtual BOOL OnInitDialog();
	afx_msg void OnPasteKey();
	afx_msg void OnEncrypt();
	afx_msg void OnDecrypt();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
	
private:
	// edit field for álphabetic key input
	CEdit controlEditAlphabeticKey;
	// edit field for numeric key input
	CEdit controlEditNumericKey;
	// edit field for the Caesar distance
	CEdit controlEditDistance;
	// edit field for the source alphabet
	CEdit controlEditSourceAlphabet;
	// edit field for the target alphabet (the "new" alphabet)
	CEdit controlEditTargetAlphabet;
	// edit field for ROT13-related messages
	CEdit controlEditMessageROT13;
	// edit field for displaying information regarding the alphabet size
	CEdit controlEditShowAlphabetSizeAndMapping;
	// tool tip button for pasting keys from the key store
	CToolTipButton controlBitmapButtonPaste;
	// radio button to change to Caesar mode
	CButton controlRadioButtonCaesar;
	// radio button to change to ROT13 mode
	CButton controlRadioButtonROT13;
	// radio button to activate alphabetic key input
	CButton controlRadioButtonAlphabetic;
	// radio button to activate numeric key input
	CButton controlRadioButtonNumeric;
	// radio button to use zero as key offset
	CButton controlRadioButtonKeyOffsetZero;
	// radio button to use one as key offset
	CButton controlRadioButtonKeyOffsetOne;
	// button to start the encryption
	CButton controlButtonEncryption;
	// button to start the decryption
	CButton controlButtonDecryption;
	// a monospace font object used to display certain text fields
	CFont font;

	// this is the main GUI update function which is called whenever the state of the dialog changes
	void onUpdateGUI();

	// this function returns the number of digits used to display the alphabet length
	int getDigitsOfAlphabetLength();
	// this function checks if there's a valid key in the key store
	CaesarKey checkPasteKeyVariant(int SID);
	// this function is called when the user clicks on the text options button
	void onTextOptions();

	// this function calculates the numeric key (i.e. 2) for the given alphabetic key (i.e. B)
	CString calculateNumericKeyFromAlphabeticKey(CString alphabeticKey);
	// this function calculates the alphabetic key (i.e. C) for the given numeric key (i.e. 3)
	CString calculateAlphabeticKeyFromNumericKey(CString numericKey);

	// this variable indicates which mode we're in (Caesar or ROT13)
	bool modeCaesar;
	// this variable indicates which mode we're in (decryption or encryption)
	bool modeDecryption;
	// this variable indicates how the key is chosen (alphabetic or numeric)
	bool alphabeticKeyInput;
	// this variable indicates which key offset we're using (zero or one)
	bool keyOffsetZero;

	// this variable holds the encryption type (either IDS_STRING_CAESAR or IDS_STRING_ROT13)
	unsigned int typeEncryption;

	// the alphabetic key
	CString alphabeticKey;
	// the numeric key
	CString numericKey;
	// the alphabet
	CString alphabet;
	// the target alphabet
	CString targetAlphabet;	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGROT13CAESAR_H__F55065A9_4E94_4628_8094_05713C56FF7C__INCLUDED_
