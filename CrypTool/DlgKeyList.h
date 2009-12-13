#pragma once
#include "afxwin.h"
#include "resource.h"
#include <deque>
#define deque std::deque
#include <assert.h>

struct column_item {
	CString str;
	long width;

	column_item( long ID, long w ) {
		str.LoadString( ID ); width = w; }
};

typedef deque<column_item> col_heading;
typedef deque<CString>     key_list_row;

class base_copy_key {
public:
	virtual bool copy_key(long ndx) = 0;
};

class key_list {
	col_heading          headline;
	deque<key_list_row>  keys;

	friend class CDlgKeyList;
public:
	void append_hl( long ID, long w )    { headline.push_back(column_item(ID, w)); }
	void append_key( key_list_row &key ) { keys.push_back(key); }
};

// CDlgKeyList-Dialogfeld

class CDlgKeyList : public CDialog
{
	DECLARE_DYNAMIC(CDlgKeyList)
	base_copy_key *c_key_ptr;

public:
	CDlgKeyList(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgKeyList();

// Dialogfelddaten
	enum { IDD = IDD_KEYS_LIST };

	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CString   m_strHeader;
	CEdit     m_ctrlHeader;
	CListCtrl m_ctrlKeyList;
	CButton   m_ctrl_copy_key;
	afx_msg void OnBnClickedButtonCopyKey();
	key_list m_keyList;
	void set_copy_key_class( base_copy_key *key_ptr ) { c_key_ptr = key_ptr; }
};
