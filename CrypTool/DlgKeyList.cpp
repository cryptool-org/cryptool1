// DlgKeyList.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DlgKeyList.h"
#include "DialogeMessage.h"


// CDlgKeyList-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgKeyList, CDialog)

CDlgKeyList::CDlgKeyList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyList::IDD, pParent)
{

}

CDlgKeyList::~CDlgKeyList()
{
}

BOOL CDlgKeyList::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateData(FALSE);
	m_ctrlHeader.SetWindowText( m_strHeader );

	m_ctrlKeyList.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	long index = 0, row = 0; 

	col_heading::iterator it_headline = m_keyList.headline.begin();
	while (it_headline != m_keyList.headline.end() )
	{
		m_ctrlKeyList.InsertColumn(index++, (*it_headline).str, LVCFMT_LEFT, (*it_headline).width);
		it_headline++;
	}

	deque<key_list_row>::iterator it_key = m_keyList.keys.begin();
	while ( it_key != m_keyList.keys.end() )
	{
		index = 0;
			key_list_row::iterator it =  (*it_key).begin();
		while ( it != (*it_key).end() ) 
		{
			if ( !index )
			{
				m_ctrlKeyList.InsertItem( row, *it );
			}
			else
				m_ctrlKeyList.SetItemText(row, index, *it);
			index++; it++;
		}
		row++; it_key++;
	}
	m_ctrlKeyList.SetItemState(1, LVIS_SELECTED, LVIS_SELECTED);
	UpdateData();

	return TRUE;
}

void CDlgKeyList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HEADER, m_ctrlHeader);
	DDX_Control(pDX, IDC_KEY_LIST, m_ctrlKeyList);
	DDX_Control(pDX, IDC_BUTTON_COPY_KEY, m_ctrl_copy_key);
}


BEGIN_MESSAGE_MAP(CDlgKeyList, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COPY_KEY, &CDlgKeyList::OnBnClickedButtonCopyKey)
END_MESSAGE_MAP()


// CDlgKeyList-Meldungshandler

void CDlgKeyList::OnBnClickedButtonCopyKey()
{
	POSITION pos = m_ctrlKeyList.GetFirstSelectedItemPosition();
	if ( pos )
		c_key_ptr->copy_key((long)pos-1);
	else
		Message(IDS_NOKEYSELECTED, MB_ICONINFORMATION);

}
