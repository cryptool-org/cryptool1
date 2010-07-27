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


#pragma once

#include "Solitaire.h"
#include "afxwin.h"
#include "ToolTipButton.h"

// CDlgSolitaire-Dialogfeld

#define NUMBER_OF_CARDS		"NUMBER_OF_CARDS: "
#define SORT_METHOD			"SORT_METHOD: "
#define KEY_WORD			"KEY_WORD: "
#define MANUAL				"MANUAL: "
#define INITIAL_DECK		"INITIAL_DECK: "
#define MAPPED_DECK			"MAPPED_DECK: "



class CDlgSolitaire : public CDialog
{
	DECLARE_DYNAMIC(CDlgSolitaire)
	bool load_infile();

public:
	CDlgSolitaire(const char* _infile, CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgSolitaire();
	c_solitaire		deck;
	int				sel_card_count;
	char          *infile;
	unsigned char *in_buffer, *key_stream;	
	long           in_buffer_size, key_stream_size;
	solitaire_action sol_action;

// Dialogfelddaten
	enum { IDD = IDD_SOLITAIRE, IDH = IDR_HTML_DLGSOLITAIRE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	void    DoCard( int k, CButton &button );
	void    ChangeConfiguration();
	void    init();
	void    saveDeck( CString &str_deck, const char *def_fname );

	DECLARE_MESSAGE_MAP()
//	DECLARE_DHTML_EVENT_MAP()
public:
	void enableVorgabe(bool art);
	void initdrei();
	long get_no_of_cards() { return deck.get_no_of_cards(); }
	afx_msg void OnCbnSelchangeKartenanzahl();
	afx_msg void OnCbnSelchangeCombo2();
	CString InitialDeck;
	afx_msg void OnBnClickedButton61();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedCryptStep1();
	afx_msg void OnBnClickedCryptStep2();
	afx_msg void OnBnClickedCryptStep3();
	afx_msg void OnBnClickedCryptStep4();
	afx_msg void OnBnClickedCryptStep5();
	afx_msg void OnBnClickedDoCrypt();
	afx_msg void OnBnClickedDoCryptSteps();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton26();
	afx_msg void OnBnClickedButton27();
	afx_msg void OnBnClickedButton28();
	afx_msg void OnBnClickedButton29();
	afx_msg void OnBnClickedButton30();
	afx_msg void OnBnClickedButton31();
	afx_msg void OnBnClickedButton32();
	afx_msg void OnBnClickedButton33();
	afx_msg void OnBnClickedButton34();
	afx_msg void OnBnClickedButton35();
	afx_msg void OnBnClickedButton36();
	afx_msg void OnBnClickedButton37();
	afx_msg void OnBnClickedButton38();
	afx_msg void OnBnClickedButton39();
	afx_msg void OnBnClickedButton40();
	afx_msg void OnBnClickedButton41();
	afx_msg void OnBnClickedButton42();
	afx_msg void OnBnClickedButton43();
	afx_msg void OnBnClickedButton44();
	afx_msg void OnBnClickedButton45();
	afx_msg void OnBnClickedButton46();
	afx_msg void OnBnClickedButton47();
	afx_msg void OnBnClickedButton48();
	afx_msg void OnBnClickedButton49();
	afx_msg void OnBnClickedButton50();
	afx_msg void OnBnClickedButton51();
	afx_msg void OnBnClickedButton52();
	afx_msg void OnBnClickedButton53();
	afx_msg void OnBnClickedButton54();
	afx_msg void OnBnClickedButton55();
	afx_msg void OnBnClickedButton56();
	afx_msg void OnBnClickedButton57();
	afx_msg void OnBnClickedButton58();
	afx_msg void OnBnClickedButton59();
	afx_msg void OnBnClickedButton60();
	afx_msg void OnBnClickedButton62();
	afx_msg void OnResetCardSettings();
	afx_msg void OnEnChangePassword();
	CEdit m_passwort;
	CString m_passwort1;
	afx_msg void OnBnClickedModifyDeckByPassword();
	CButton m_passwort_button;
	CButton m_reset_button;
	CButton m_auto_button;
	CButton m_manuell_button;
	CButton m_schritt1;
	CButton m_schritt2;
	CButton m_schritt3;
	CButton m_schritt4;
	CButton m_schritt5;
	CString endDeck;
	CString key_edit;
	afx_msg void OnBnClickedSaveDeck();
	afx_msg void OnBnClickedSaveFinalDeck();
	CButton m_inispeichern;
	CButton m_abschlussspeichern;
	afx_msg void OnBnCancel();
	afx_msg void OnEncrypt();
	afx_msg void OnDecrypt();
	afx_msg void OnPasteKey();
	CButton verschl;
	CButton entschl;
	CToolTipButton m_Paste;

	int edit_zaehler_value;
	CButton m_rest_generate;
	afx_msg void OnBnFinishCrypt();
	CEdit m_edit_rest_generate;
	afx_msg void OnBnReInit();
	CButton m_anderemischung;
	afx_msg void OnBnNewShuffle();
	int edit_schl_zeichen;
	CEdit m_edit_schl;
	afx_msg void OnBnSaveKeyStream();
	CButton m_keystream_save_button;
	CComboBox m_ctrlComboSelCards;
	CComboBox m_ctrlSelKartenanzahl;

   CButton *vorgabe_p;
};
