// DlgHomophonicSubstitution.h

#ifndef _DLGHOMOPHONICSUBSTITUTION_H_
#define _DLGHOMOPHONICSUBSTITUTION_H_

#include <afxwin.h>
#include "KeyRepository.h"
#include "ToolTipButton.h"
#include "HomophonicSubstitution.h"

class CDlgHomophonicSubstitution : public CDialog {
	DECLARE_DYNAMIC(CDlgHomophonicSubstitution)
	enum { IDD = IDD_HOMOPHONIC_SUBSTITUTION };
public:
	CDlgHomophonicSubstitution(const CString &sourceFile, const CString &sourceTitle, CWnd *pParent = NULL);
	virtual ~CDlgHomophonicSubstitution();
public:
	bool executeEncryption(const CString &targetFile) const;
	bool executeDecryption(const CString &targetFile) const;
public:
	CString getKeyAsString() const;
protected:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	virtual void DoDataExchange(CDataExchange *pDX);
	DECLARE_MESSAGE_MAP()
private:
	void checkInputFile();
private:
	void loadSettings();
	void saveSettings();
	void publishSettings();
private:
	void initializeToolTipButtons();
	void updateToolTipButtons();
private:
	bool canKeyBePastedFromKeystore() const;
	bool canKeyBePastedFromClipboard() const;
private:
	void initializeListHomophonesKeyTable();
	void updateListHomophonesKeyTable();
private:
	void pressedEnterEditCountHomophones();
	void clickedButtonUpdateCountHomophones();
	void clickedButtonCopyKeyToKeystore();
	void clickedButtonCopyKeyToClipboard();
	void clickedButtonPasteKeyFromKeystore();
	void clickedButtonPasteKeyFromClipboard();
	void doubleClickedListHomophonesKeyTable(NMHDR *pNMHDR, LRESULT *pResult);
	void clickedButtonEncrypt();
	void clickedButtonDecrypt();
	void clickedButtonGenerateKey();
	void clickedButtonCancel();
private:
	HomophonicSubstitution m_homophonicSubstitution;
private:
	const CString m_sourceFile;
	const CString m_sourceTitle;
private:
	CEdit m_editCountHomophones;
	CButton m_buttonUpdateCountHomophones;
	CToolTipButton m_buttonCopyKeyToKeystore;
	CToolTipButton m_buttonCopyKeyToClipboard;
	CToolTipButton m_buttonPasteKeyFromKeystore;
	CToolTipButton m_buttonPasteKeyFromClipboard;
	CListCtrl m_listHomophonesKeyTable;
	CButton m_buttonEncrypt;
	CButton m_buttonDecrypt;
	CButton m_buttonGenerateKey;
	CButton m_buttonCancel;
private:
	unsigned int m_countHomophones;
};

class CDlgHomophoneSubstitutionKeyEntryDetails : public CDialog {
	DECLARE_DYNAMIC(CDlgHomophoneSubstitutionKeyEntryDetails)
	enum { IDD = IDD_HOMOPHONIC_SUBSTITUTION_KEY_ENTRY_DETAILS };
public:
	CDlgHomophoneSubstitutionKeyEntryDetails(const CString &code, const CString &character, const CString &frequency, const CString &count, const CString &homophones, CWnd *pParent = NULL);
	virtual ~CDlgHomophoneSubstitutionKeyEntryDetails();
protected:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	virtual void DoDataExchange(CDataExchange *pDX);
	DECLARE_MESSAGE_MAP()
private:
	void clickedButtonClose();
private:
	CEdit m_editCode;
	CEdit m_editCharacter;
	CEdit m_editFrequency;
	CEdit m_editCount;
	CEdit m_editHomophones;
private:
	CString m_code;
	CString m_character;
	CString m_frequency;
	CString m_count;
	CString m_homophones;
};

#endif
