// DlgHomophonicSubstitution.cpp

#include "stdafx.h"
#include "CrypToolApp.h"
#include "Cryptography.h"
#include "CrypToolTools.h"
#include "DialogeMessage.h"

#include "DlgHomophonicSubstitution.h"

#define REGISTRY_STRING_HOMOPHONIC_SUBSTITUTION "HomophonicSubstitution"
#define REGISTRY_STRING_HOMOPHONIC_SUBSTITUTION_COUNT_HOMOPHONES "CountHomophones"

IMPLEMENT_DYNAMIC(CDlgHomophonicSubstitution, CDialog)

CDlgHomophonicSubstitution::CDlgHomophonicSubstitution(const CString &sourceFile, const CString &sourceTitle, CWnd *pParent) :
	CDialog(CDlgHomophonicSubstitution::IDD, pParent),
	m_homophonicSubstitution(sourceFile),
	m_sourceFile(sourceFile),
	m_sourceTitle(sourceTitle) {

}

CDlgHomophonicSubstitution::~CDlgHomophonicSubstitution() {

}

bool CDlgHomophonicSubstitution::executeEncryption(const CString &targetFile) const {
	return m_homophonicSubstitution.executeEncryption(m_sourceFile, targetFile);
}

bool CDlgHomophonicSubstitution::executeDecryption(const CString &targetFile) const {
	return m_homophonicSubstitution.executeDecryption(m_sourceFile, targetFile);
}

CString CDlgHomophonicSubstitution::getKeyAsString() const {
	return m_homophonicSubstitution.exportKeyAsString();
}

BOOL CDlgHomophonicSubstitution::OnInitDialog() {
	CDialog::OnInitDialog();
	checkInputFile();
	loadSettings();
	publishSettings();
	initializeToolTipButtons();
	updateToolTipButtons();
	initializeListHomophonesKeyTable();
	updateListHomophonesKeyTable();
	return TRUE;
}

BOOL CDlgHomophonicSubstitution::PreTranslateMessage(MSG *pMsg) {
	switch(pMsg->message) {
	case WM_KEYDOWN:
		// Whenever the focus is on m_editCountHomophones, pressing the "Enter" 
		// key will not trigger the element currently focused, but instead it 
		// will call "pressedEnterEditCountHomophones" and consider the event 
		// as being handled (thus returning "true").
		if(pMsg->wParam == VK_RETURN) {
			if(GetFocus() == &m_editCountHomophones) {
				pressedEnterEditCountHomophones();
				return true;
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgHomophonicSubstitution::DoDataExchange(CDataExchange *pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COUNT_HOMOPHONES, m_editCountHomophones);
	DDX_Control(pDX, IDC_BUTTON_UPDATE_COUNT_HOMOPHONES, m_buttonUpdateCountHomophones);
	DDX_Control(pDX, IDC_LIST_HOMOPHONES_KEY_TABLE, m_listHomophonesKeyTable);
	DDX_Control(pDX, IDC_BUTTON_ENCRYPT, m_buttonEncrypt);
	DDX_Control(pDX, IDC_BUTTON_DECRYPT, m_buttonDecrypt);
	DDX_Control(pDX, IDC_BUTTON_GENERATE_KEY, m_buttonGenerateKey);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_buttonCancel);
	DDX_Text(pDX, IDC_EDIT_COUNT_HOMOPHONES, m_countHomophones);
}

BEGIN_MESSAGE_MAP(CDlgHomophonicSubstitution, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_COUNT_HOMOPHONES, clickedButtonUpdateCountHomophones)
	ON_BN_CLICKED(IDC_BUTTON_COPY_KEY_TO_KEYSTORE, clickedButtonCopyKeyToKeystore)
	ON_BN_CLICKED(IDC_BUTTON_COPY_KEY_TO_CLIPBOARD, clickedButtonCopyKeyToClipboard)
	ON_BN_CLICKED(IDC_BUTTON_PASTE_KEY_FROM_KEYSTORE, clickedButtonPasteKeyFromKeystore)
	ON_BN_CLICKED(IDC_BUTTON_PASTE_KEY_FROM_CLIPBOARD, clickedButtonPasteKeyFromClipboard)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_HOMOPHONES_KEY_TABLE, doubleClickedListHomophonesKeyTable)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPT, clickedButtonEncrypt)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT, clickedButtonDecrypt)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE_KEY, clickedButtonGenerateKey)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, clickedButtonCancel)
END_MESSAGE_MAP()

void CDlgHomophonicSubstitution::checkInputFile() {
	CFile infile;
	if(!infile.Open(m_sourceFile, CFile::modeRead | CFile::typeBinary)) {
		Message(IDS_HOMOPHONIC_SUBSTITUTION_EMPTY_DOCUMENT, MB_ICONINFORMATION);
		EndDialog(IDCANCEL);
	}
	if(infile.GetLength() == 0) {
		infile.Close();
		Message(IDS_HOMOPHONIC_SUBSTITUTION_EMPTY_DOCUMENT, MB_ICONINFORMATION);
		EndDialog(IDCANCEL);
	}
}

void CDlgHomophonicSubstitution::loadSettings() {
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_READ, IDS_REGISTRY_SETTINGS, REGISTRY_STRING_HOMOPHONIC_SUBSTITUTION) == ERROR_SUCCESS) {
		unsigned long countHomophones = (unsigned long)(m_homophonicSubstitution.getCountHomophonesMax());
		CT_READ_REGISTRY(countHomophones, REGISTRY_STRING_HOMOPHONIC_SUBSTITUTION_COUNT_HOMOPHONES);
		m_homophonicSubstitution.setCountHomophones((unsigned int)(countHomophones));
		m_countHomophones = m_homophonicSubstitution.getCountHomophones();
	}
}

void CDlgHomophonicSubstitution::saveSettings() {
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_WRITE, IDS_REGISTRY_SETTINGS, REGISTRY_STRING_HOMOPHONIC_SUBSTITUTION) == ERROR_SUCCESS) {
		CT_WRITE_REGISTRY((unsigned long)(m_homophonicSubstitution.getCountHomophones()), REGISTRY_STRING_HOMOPHONIC_SUBSTITUTION_COUNT_HOMOPHONES);
		CT_CLOSE_REGISTRY();
	}
}

void CDlgHomophonicSubstitution::publishSettings() {
	m_countHomophones = m_homophonicSubstitution.getCountHomophones();
	UpdateData(false);
}

void CDlgHomophonicSubstitution::initializeToolTipButtons() {
	// Copy key to keystore.
	VERIFY(m_buttonCopyKeyToKeystore.AutoLoad(IDC_BUTTON_COPY_KEY_TO_KEYSTORE, this));
	CString textButtonCopyKeyToKeystore;
	textButtonCopyKeyToKeystore.LoadString(IDS_STRING_COPY_KEY_TO_KEY_STORE);
	m_buttonCopyKeyToKeystore.SetToolTipText(&textButtonCopyKeyToKeystore);
	// Copy key to clipboard.
	VERIFY(m_buttonCopyKeyToClipboard.AutoLoad(IDC_BUTTON_COPY_KEY_TO_CLIPBOARD, this));
	CString textButtonCopyKeyToClipboard;
	textButtonCopyKeyToClipboard.LoadString(IDS_STRING_COPY_KEY_TO_CLIPBOARD);
	m_buttonCopyKeyToClipboard.SetToolTipText(&textButtonCopyKeyToClipboard);
	// Paste key from keystore.
	VERIFY(m_buttonPasteKeyFromKeystore.AutoLoad(IDC_BUTTON_PASTE_KEY_FROM_KEYSTORE, this));
	CString textButtonPasteKeyFromKeystore;
	textButtonPasteKeyFromKeystore.LoadString(IDS_STRING_PASTE_KEY_FROM_KEY_STORE);
	m_buttonPasteKeyFromKeystore.SetToolTipText(&textButtonPasteKeyFromKeystore);
	// Paste key from clipboard.
	VERIFY(m_buttonPasteKeyFromClipboard.AutoLoad(IDC_BUTTON_PASTE_KEY_FROM_CLIPBOARD, this));
	CString textButtonPasteKeyFromClipboard;
	textButtonPasteKeyFromClipboard.LoadString(IDS_STRING_PASTE_KEY_FROM_CLIPBOARD);
	m_buttonPasteKeyFromClipboard.SetToolTipText(&textButtonPasteKeyFromClipboard);
}

void CDlgHomophonicSubstitution::updateToolTipButtons() {
	// Enable copy buttons by default (we always have a valid key).
	m_buttonCopyKeyToKeystore.EnableWindow(true);
	m_buttonCopyKeyToClipboard.EnableWindow(true);
	// Conditionally enable/disable paste from keystore button.
	m_buttonPasteKeyFromKeystore.EnableWindow(canKeyBePastedFromKeystore());
	m_buttonPasteKeyFromClipboard.EnableWindow(canKeyBePastedFromClipboard());
}

bool CDlgHomophonicSubstitution::canKeyBePastedFromKeystore() const {
	CString key;
	return pasteKeyFromKeystore(IDS_CRYPT_HOMOPHONIC_SUBSTITUTION, key);
}

bool CDlgHomophonicSubstitution::canKeyBePastedFromClipboard() const {
	CString key;
	return pasteKeyFromClipboard(IDS_CRYPT_HOMOPHONIC_SUBSTITUTION, key);
}

void CDlgHomophonicSubstitution::initializeListHomophonesKeyTable() {
	m_listHomophonesKeyTable.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	CString columnHeader;
	columnHeader.Format(IDS_STRING_HOMOPHONIC_SUBSTITUTION_COLUMN_HEADER_CODE);
	m_listHomophonesKeyTable.InsertColumn(0, columnHeader, LVCFMT_LEFT, 50);
	columnHeader.Format(IDS_STRING_HOMOPHONIC_SUBSTITUTION_COLUMN_HEADER_CHARACTER);
	m_listHomophonesKeyTable.InsertColumn(1, columnHeader, LVCFMT_LEFT, 75);
	columnHeader.Format(IDS_STRING_HOMOPHONIC_SUBSTITUTION_COLUMN_HEADER_FREQUENCY);
	m_listHomophonesKeyTable.InsertColumn(2, columnHeader, LVCFMT_LEFT, 75);
	columnHeader.Format(IDS_STRING_HOMOPHONIC_SUBSTITUTION_COLUMN_HEADER_COUNT);
	m_listHomophonesKeyTable.InsertColumn(3, columnHeader, LVCFMT_LEFT, 75);
	columnHeader.Format(IDS_STRING_HOMOPHONIC_SUBSTITUTION_COLUMN_HEADER_HOMOPHONES);
	m_listHomophonesKeyTable.InsertColumn(4, columnHeader, LVCFMT_LEFT, 400);
}

void CDlgHomophonicSubstitution::updateListHomophonesKeyTable() {
	m_listHomophonesKeyTable.DeleteAllItems();
	CString stringCode;
	CString stringCharacter;
	CString stringFrequency;
	CString stringCountHomophones;
	CString stringHomophones;
	CString stringHomophone;
	const std::vector<HomophonicSubstitution::KeyEntry> keyEntries = m_homophonicSubstitution.getKeyEntries();
	for(int indexKeyEntry=0; indexKeyEntry<keyEntries.size(); indexKeyEntry++) {
		HomophonicSubstitution::KeyEntry keyEntry = keyEntries[indexKeyEntry];
		m_listHomophonesKeyTable.InsertItem(indexKeyEntry, "KeyEntry");
		stringCode.Empty();
		stringCode.Format("%02x", keyEntry.code);
		stringCode = stringCode.MakeUpper();
		m_listHomophonesKeyTable.SetItemText(indexKeyEntry, 0, stringCode);
		stringCharacter.Empty();
		stringCharacter.AppendChar(keyEntry.character);
		m_listHomophonesKeyTable.SetItemText(indexKeyEntry, 1, stringCharacter);
		stringFrequency.Empty();
		stringFrequency.Format("%f", keyEntry.frequency);
		m_listHomophonesKeyTable.SetItemText(indexKeyEntry, 2, stringFrequency);
		stringCountHomophones.Empty();
		stringCountHomophones.Format("%d", keyEntry.countHomophones);
		m_listHomophonesKeyTable.SetItemText(indexKeyEntry, 3, stringCountHomophones);
		stringHomophones.Empty();
		for(int indexHomophone=0; indexHomophone<keyEntry.homophones.size(); indexHomophone++) {
			stringHomophone.Empty();
			stringHomophone.Format("%02x", keyEntry.homophones[indexHomophone]);
			stringHomophone = stringHomophone.MakeUpper();
			stringHomophones.Append(stringHomophone);
			if(indexHomophone + 1 < keyEntry.homophones.size()) {
				stringHomophones.Append(", ");
			}
		}
		m_listHomophonesKeyTable.SetItemText(indexKeyEntry, 4, stringHomophones);
	}
}

void CDlgHomophonicSubstitution::pressedEnterEditCountHomophones() {
	m_buttonUpdateCountHomophones.SetFocus();
}

void CDlgHomophonicSubstitution::clickedButtonUpdateCountHomophones() {
	UpdateData(true);
	const int countHomophonesOld = m_countHomophones;
	m_homophonicSubstitution.setCountHomophones(m_countHomophones);
	m_countHomophones = m_homophonicSubstitution.getCountHomophones();
	updateListHomophonesKeyTable();
	UpdateData(false);
	if(m_countHomophones != countHomophonesOld) {
		Message(IDS_HOMOPHONIC_SUBSTITUTION_ADJUSTED_NUMBER_OF_HOMOPHONES, MB_ICONINFORMATION);
	}
}

void CDlgHomophonicSubstitution::clickedButtonCopyKeyToKeystore() {
	copyKeyToKeystore(IDS_CRYPT_HOMOPHONIC_SUBSTITUTION, m_homophonicSubstitution.exportKeyAsString());
	updateToolTipButtons();
}

void CDlgHomophonicSubstitution::clickedButtonCopyKeyToClipboard() {
	copyKeyToClipboard(IDS_CRYPT_HOMOPHONIC_SUBSTITUTION, m_homophonicSubstitution.exportKeyAsString());
	updateToolTipButtons();
}

void CDlgHomophonicSubstitution::clickedButtonPasteKeyFromKeystore() {
	CString key;
	if(pasteKeyFromKeystore(IDS_CRYPT_HOMOPHONIC_SUBSTITUTION, key)) {
		m_homophonicSubstitution.importKeyAsString(key);
		m_countHomophones = m_homophonicSubstitution.getCountHomophones();
		updateListHomophonesKeyTable();
		UpdateData(false);
	}
}

void CDlgHomophonicSubstitution::clickedButtonPasteKeyFromClipboard() {
	CString key;
	if(pasteKeyFromClipboard(IDS_CRYPT_HOMOPHONIC_SUBSTITUTION, key)) {
		m_homophonicSubstitution.importKeyAsString(key);
		m_countHomophones = m_homophonicSubstitution.getCountHomophones();
		updateListHomophonesKeyTable();
		UpdateData(false);
	}
}

void CDlgHomophonicSubstitution::doubleClickedListHomophonesKeyTable(NMHDR *pNMHDR, LRESULT *pResult) {
	const int index = m_listHomophonesKeyTable.GetNextItem(-1, LVNI_SELECTED);
	const HomophonicSubstitution::KeyEntry keyEntry = m_homophonicSubstitution.getKeyEntries()[index];
	CString stringCode;
	stringCode.Format("%02x", keyEntry.code);
	stringCode = stringCode.MakeUpper();
	CString stringCharacter;
	stringCharacter.AppendChar(keyEntry.character);
	CString stringFrequency;
	stringFrequency.Format("%f", keyEntry.frequency);
	CString stringCount;
	stringCount.Format("%d", keyEntry.homophones.size());
	CString stringHomophones;
	CString stringHomophone;
	for(int indexHomophone=0; indexHomophone<keyEntry.homophones.size(); indexHomophone++) {
		stringHomophone.Empty();
		stringHomophone.Format("%02x", keyEntry.homophones[indexHomophone]);
		stringHomophone = stringHomophone.MakeUpper();
		stringHomophones.Append(stringHomophone);
		if(indexHomophone + 1 < keyEntry.homophones.size()) {
			stringHomophones.Append(", ");
		}
	}
	CDlgHomophoneSubstitutionKeyEntryDetails dlg(stringCode, stringCharacter, stringFrequency, stringCount,stringHomophones);
	dlg.DoModal();
}

void CDlgHomophonicSubstitution::clickedButtonEncrypt() {
	saveSettings();
	EndDialog(IDENCRYPT);
}

void CDlgHomophonicSubstitution::clickedButtonDecrypt() {
	saveSettings();
	EndDialog(IDDECRYPT);
}

void CDlgHomophonicSubstitution::clickedButtonGenerateKey() {
	m_homophonicSubstitution.generateKey();
	updateListHomophonesKeyTable();
	UpdateData(false);
}

void CDlgHomophonicSubstitution::clickedButtonCancel() {
	EndDialog(IDCANCEL);
}

IMPLEMENT_DYNAMIC(CDlgHomophoneSubstitutionKeyEntryDetails, CDialog)

CDlgHomophoneSubstitutionKeyEntryDetails::CDlgHomophoneSubstitutionKeyEntryDetails(const CString &code, const CString &character, const CString &frequency, const CString &count, const CString &homophones, CWnd *pParent) :
	CDialog(CDlgHomophoneSubstitutionKeyEntryDetails::IDD, pParent),
	m_code(code),
	m_character(character),
	m_frequency(frequency),
	m_count(count),
	m_homophones(homophones) {

}

CDlgHomophoneSubstitutionKeyEntryDetails::~CDlgHomophoneSubstitutionKeyEntryDetails() {

}

BOOL CDlgHomophoneSubstitutionKeyEntryDetails::OnInitDialog() {
	CDialog::OnInitDialog();
	UpdateData(false);
	return TRUE;
}

BOOL CDlgHomophoneSubstitutionKeyEntryDetails::PreTranslateMessage(MSG *pMsg) {
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 'A' && GetKeyState(VK_CONTROL) < 0) {
		CWnd *focus = GetFocus();
		std::vector<CEdit*> edits;
		edits.push_back(&m_editCode);
		edits.push_back(&m_editCharacter);
		edits.push_back(&m_editFrequency);
		edits.push_back(&m_editCount);
		edits.push_back(&m_editHomophones);
		for(int indexEdit=0; indexEdit<edits.size(); indexEdit++) {
			CEdit *edit = edits[indexEdit];
			if(edit == focus) {
				edit->SetSel(0, -1);
				return true;
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgHomophoneSubstitutionKeyEntryDetails::DoDataExchange(CDataExchange *pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CODE, m_editCode);
	DDX_Control(pDX, IDC_EDIT_CHARACTER, m_editCharacter);
	DDX_Control(pDX, IDC_EDIT_FREQUENCY, m_editFrequency);
	DDX_Control(pDX, IDC_EDIT_COUNT, m_editCount);
	DDX_Control(pDX, IDC_EDIT_HOMOPHONES, m_editHomophones);
	DDX_Text(pDX, IDC_EDIT_CODE, m_code);
	DDX_Text(pDX, IDC_EDIT_CHARACTER, m_character);
	DDX_Text(pDX, IDC_EDIT_FREQUENCY, m_frequency);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_count);
	DDX_Text(pDX, IDC_EDIT_HOMOPHONES, m_homophones);
}

BEGIN_MESSAGE_MAP(CDlgHomophoneSubstitutionKeyEntryDetails, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, clickedButtonClose)
END_MESSAGE_MAP()

void CDlgHomophoneSubstitutionKeyEntryDetails::clickedButtonClose() {
	EndDialog(IDCLOSE);
}