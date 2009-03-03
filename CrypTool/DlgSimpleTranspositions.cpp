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

// DlgSimpleTranspositions.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSimpleTranspositions.h"
#include "Cryptography.h"
#include "CrypToolTools.h"

IMPLEMENT_DYNAMIC(CDlgSimpleTranspositions, CDialog)

CDlgSimpleTranspositions::CDlgSimpleTranspositions(char* infile, CString oldTitle, CWnd* pParent)
	: CDialog(CDlgSimpleTranspositions::IDD, pParent)
	, key(0)
{
	fileName = infile;
	fileNameTitle = oldTitle;

	// the type is Scytale by default
	type = 0;
	// the default key is 2
	key = 2;
	// the default offset is 0
	offset = 0;

	// init the bitmaps
	bitmapScytale.LoadBitmapA(IDB_SIMPLE_TRANSPOSITION_SCYTALE);
	bitmapRailFence.LoadBitmapA(IDB_SIMPLE_TRANSPOSITION_RAIL_FENCE);
}

CDlgSimpleTranspositions::~CDlgSimpleTranspositions()
{

}

void CDlgSimpleTranspositions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RADIO_SCYTALE, type);
	DDX_Control(pDX, IDC_SIMPLE_TRANSPOSITION_IMAGE, controlImage);
	DDX_Text(pDX, IDC_EDIT_KEY, key);
	DDX_Text(pDX, IDC_EDIT_OFFSET, offset);
}


BEGIN_MESSAGE_MAP(CDlgSimpleTranspositions, CDialog)
	ON_BN_CLICKED(ID_ENCRYPT, &CDlgSimpleTranspositions::OnBnClickedEncrypt)
	ON_BN_CLICKED(ID_DECRYPT, &CDlgSimpleTranspositions::OnBnClickedDecrypt)
	ON_BN_CLICKED(IDC_RADIO_SCYTALE, OnRadioScytale)
	ON_BN_CLICKED(IDC_RADIO_RAIL_FENCE, OnRadioRailFence)
END_MESSAGE_MAP()

BOOL CDlgSimpleTranspositions::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// load stored settings (key and offset)
	loadSettings();

	UpdateData(false);

	// update the GUI
	updateGUI();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

// CDlgSimpleTranspositions message handlers

void CDlgSimpleTranspositions::OnBnClickedEncrypt()
{
	UpdateData(true);

	// check if the key is valid
	if(key < 1) {
		LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_KEY_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
		return;
	}

	// check if the offset is valid
	if(offset < 0) {
		LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_OFFSET_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
		return;
	}

	// now, do the actual encryption
	if(type == 0) { // SCYTALE
		int result = ScytaleEncryption(fileName.GetBuffer(), fileNameTitle.GetBuffer(), key, true);
		if(result == -1) {
			LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_KEY_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);	
			return;
		}
	}
	if(type == 1) { // RAIL FENCE
		int result = RailFenceEncryption(fileName.GetBuffer(), fileNameTitle.GetBuffer(), key, offset, true);
		if(result == -1) {
			LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_KEY_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);	
			return;
		}
	}
	
	// store settings (key and offset)
	saveSettings();

	EndDialog(IDOK);
}

void CDlgSimpleTranspositions::OnBnClickedDecrypt()
{
	UpdateData(true);

	// check if the key is valid
	if(key < 1) {
		LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_KEY_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
		return;
	}

	// check if the offset is valid
	if(offset < 0) {
		LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_OFFSET_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
		return;
	}

	// now, do the actual encryption
	if(type == 0) // SCYTALE
		ScytaleEncryption(fileName.GetBuffer(), fileNameTitle.GetBuffer(), key, offset, false);
	if(type == 1) // RAIL FENCE
		RailFenceEncryption(fileName.GetBuffer(), fileNameTitle.GetBuffer(), key, offset, false);

	// store settings (key and offset)
	saveSettings();

	EndDialog(IDOK);
}

void CDlgSimpleTranspositions::OnRadioScytale()
{
	// we want to update the GUI depending on the state we're in
	updateGUI();
}

void CDlgSimpleTranspositions::OnRadioRailFence()
{
	// we want to update the GUI depending on the state we're in
	updateGUI();
}

void CDlgSimpleTranspositions::updateGUI() 
{
	UpdateData(true);

	// the first thing we want to do is find out which mode we're running in
	if(type == 0) {				// SCYTALE
		// update the key description
		CWnd *windowKeyDescription = GetDlgItem(IDC_SIMPLE_TRANSPOSITION_KEY);
		if(windowKeyDescription) {
			LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_KEY_DESCRIPTION_SCYTALE, pc_str, STR_LAENGE_STRING_TABLE);
			windowKeyDescription->SetWindowTextA(pc_str); 
		}
		// update the image
		controlImage.SetBitmap(bitmapScytale);

	}
	if(type == 1) {				// RAIL FENCE
		// update the key description
		CWnd *windowKeyDescription = GetDlgItem(IDC_SIMPLE_TRANSPOSITION_KEY);
		if(windowKeyDescription) {
			LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_KEY_DESCRIPTION_RAIL_FENCE, pc_str, STR_LAENGE_STRING_TABLE);
			windowKeyDescription->SetWindowTextA(pc_str);
		}
		// update the image
		controlImage.SetBitmap(bitmapRailFence);
	}

	UpdateData(false);
}

void CDlgSimpleTranspositions::loadSettings() {
	// try to load settings (key and offset) from windows registry
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_READ, IDS_REGISTRY_SETTINGS, "SimpleTranspositions") == ERROR_SUCCESS) {		
		unsigned long ulType = type;
		unsigned long ulKey = key;
		unsigned long ulOffset = offset;
		CT_READ_REGISTRY(ulType, "Type");
		CT_READ_REGISTRY(ulKey, "Key");
		CT_READ_REGISTRY(ulOffset, "Offset");
		CT_CLOSE_REGISTRY();
		type = ulType;
		key = ulKey;
		offset = ulOffset;
	}
}

void CDlgSimpleTranspositions::saveSettings() {
	// try to write settings (key and offset) to windows registry
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_WRITE, IDS_REGISTRY_SETTINGS, "SimpleTranspositions") == ERROR_SUCCESS) {
		CT_WRITE_REGISTRY((unsigned long)type, "Type");
		CT_WRITE_REGISTRY((unsigned long)key, "Key");
		CT_WRITE_REGISTRY((unsigned long)offset, "Offset");
		CT_CLOSE_REGISTRY();
	}
}