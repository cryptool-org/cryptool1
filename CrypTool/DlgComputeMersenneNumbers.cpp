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

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgComputeMersenneNumbers.h"

// include apfloat and utility headers
#include "../apfloat241/ap.h"
#include "../apfloat241/apint.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgComputeMersenneNumbers dialog

IMPLEMENT_DYNAMIC(CDlgComputeMersenneNumbers, CDialog)

CDlgComputeMersenneNumbers::CDlgComputeMersenneNumbers(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgComputeMersenneNumbers::IDD, pParent)
{

}

CDlgComputeMersenneNumbers::~CDlgComputeMersenneNumbers()
{
}

void CDlgComputeMersenneNumbers::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgComputeMersenneNumbers, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COMPUTE, &CDlgComputeMersenneNumbers::OnBnClickedButtonCompute)
END_MESSAGE_MAP()


// CDlgComputeMersenneNumbers message handlers

void CDlgComputeMersenneNumbers::OnBnClickedButtonCompute()
{
	// ...
	// flomar, 06/29/2010
	// for now, this is just a dummy implementation
	// ...

	apbase(10);

	apint base = 2;
	unsigned long exponent = 10;
  
	time_t b = time(0);
	apint mersenneNumber = pow(base, exponent);
	double timeNeeded = difftime(time(0), b);

	// convert apint to something readable
	std::ostringstream outbuffer;
	std::string buffer;

	outbuffer << mersenneNumber;
	buffer = outbuffer.str();
}
