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

#ifndef _DLG_SIMPLE_TRANSPOSITIONS_H_
#define _DLG_SIMPLE_TRANSPOSITIONS_H_

#include "afxwin.h"
#include "KeyRepository.h"
#include "ToolTipButton.h"

// this struct implements the "new" Caesar key with the added key offset
struct SimpleTranspositionKey {
	int type;
	int key;
	int offset;

	SimpleTranspositionKey() {
		type = 0;
		key = 0;
		offset = 0;
	};
};

class CDlgSimpleTranspositions : public CDialog
{
	DECLARE_DYNAMIC(CDlgSimpleTranspositions)

public:
	CDlgSimpleTranspositions(char* infile, CString oldTitle, CWnd* pParent = NULL);
	virtual ~CDlgSimpleTranspositions();

// Dialog Data
	enum { IDD = IDD_SIMPLE_TRANSPOSITIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	// load/save settings from/to windows registry (key and offset)
	void loadSettings();
	void saveSettings();

public:
	afx_msg void OnBnClickedEncrypt();
	afx_msg void OnBnClickedDecrypt();
	afx_msg void OnBnClickedTextoptions();
	afx_msg void OnPasteKey();

	afx_msg void OnRadioScytale();
	afx_msg void OnRadioRailFence();

protected:
	// file name of the file to be encrypted/decrypted
	CString fileName;
	// title of the file to be encrypted/decrypted
	CString fileNameTitle;

	// internal function to update the GUI
	void updateGUI();

	// the control for the image
	CStatic controlImage;

	// bitmaps for scytale and rail fence
	CBitmap bitmapScytale;
	CBitmap bitmapRailFence;

	// bitmap button for pasting keys from the key store
	CToolTipButton controlBitmapButtonPaste;
	// this function checks if there's a valid key in the key store
	SimpleTranspositionKey checkPasteKeyVariant(int SID);

	int type;
	int key;
	int offset;
};

#endif