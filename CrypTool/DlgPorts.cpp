// DlgPorts.cpp : implementation file
//

#include "stdafx.h"
#include "DlgPorts.h"

#include <list>

// CDlgPorts dialog

IMPLEMENT_DYNAMIC(CDlgPorts, CDialog)

CDlgPorts::CDlgPorts(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPorts::IDD, pParent)
{

}

CDlgPorts::~CDlgPorts()
{
}

void CDlgPorts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORTS_INFORMATION, portsInformation);
}


BEGIN_MESSAGE_MAP(CDlgPorts, CDialog)
END_MESSAGE_MAP()

BOOL CDlgPorts::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// flomar, 03/29/2010
	// from now on we arrange the information about CrypTool ports in a single edit control; 
	// when there's a new port, all we have to do is extend this function and add some resources

	struct Port {
		CString heading;
		CString initialWork;
		CString furtherWork;
	};

	std::list<Port> listPorts;

	// Polish port
	Port portPolish;
	portPolish.heading.LoadString(IDS_STRING_PORTS_HEADING_POLISH);
	portPolish.initialWork.LoadString(IDS_STRING_PORTS_INITIAL_WORK_POLISH);
	portPolish.furtherWork.LoadString(IDS_STRING_PORTS_FURTHER_WORK_POLISH);
	listPorts.push_back(portPolish);

	// Serbian port
	Port portSerbian;
	portSerbian.heading.LoadString(IDS_STRING_PORTS_HEADING_SERBIAN);
	portSerbian.initialWork.LoadString(IDS_STRING_PORTS_INITIAL_WORK_SERBIAN);
	portSerbian.furtherWork.LoadString(IDS_STRING_PORTS_FURTHER_WORK_SERBIAN);
	listPorts.push_back(portSerbian);

	// Spanish port
	Port portSpanish;
	portSpanish.heading.LoadString(IDS_STRING_PORTS_HEADING_SPANISH);
	portSpanish.initialWork.LoadString(IDS_STRING_PORTS_INITIAL_WORK_SPANISH);
	portSpanish.furtherWork.LoadString(IDS_STRING_PORTS_FURTHER_WORK_SPANISH);
	listPorts.push_back(portSpanish);

	// now insert all ports into the text field
	for(std::list<Port>::iterator iter=listPorts.begin(); iter!=listPorts.end(); iter++) {
		CString heading = (*iter).heading;
		CString initialWork = (*iter).initialWork;
		CString furtherWork = (*iter).furtherWork;
		
		portsInformation.Append(heading);
		portsInformation.Append("\r\n");
		portsInformation.Append("\r\n");
		portsInformation.Append(initialWork);
		portsInformation.Append("\r\n");
		portsInformation.Append(furtherWork);
		portsInformation.Append("\r\n");
		portsInformation.Append("\r\n");
		portsInformation.Append("\r\n");
	}

	UpdateData(false);
	
	return TRUE;
}