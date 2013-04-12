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
#include "DlgTranslations.h"

#include <list>

// CDlgTranslations dialog

IMPLEMENT_DYNAMIC(CDlgTranslations, CDialog)

CDlgTranslations::CDlgTranslations(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTranslations::IDD, pParent)
{

}

CDlgTranslations::~CDlgTranslations()
{
}

void CDlgTranslations::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TRANSLATIONS_INFORMATION, translationsInformation);
}


BEGIN_MESSAGE_MAP(CDlgTranslations, CDialog)
END_MESSAGE_MAP()

BOOL CDlgTranslations::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// flomar, 03/29/2010
	// from now on we arrange the information about CrypTool translations in a single edit control; 
	// when there's a new translation, all we have to do is extend this function and add some resources

	struct Translation {
		CString heading;
		CString initialWork;
		CString furtherWork;
	};

	std::list<Translation> listTranslations;
	
	// Greek translation
	Translation translationGreek;
	translationGreek.heading.LoadString(IDS_STRING_TRANSLATIONS_HEADING_GREEK);
	translationGreek.initialWork.LoadString(IDS_STRING_TRANSLATIONS_INITIAL_WORK_GREEK);
	translationGreek.furtherWork.LoadString(IDS_STRING_TRANSLATIONS_FURTHER_WORK_GREEK);
	listTranslations.push_back(translationGreek);

	// Polish translation
	Translation translationPolish;
	translationPolish.heading.LoadString(IDS_STRING_TRANSLATIONS_HEADING_POLISH);
	translationPolish.initialWork.LoadString(IDS_STRING_TRANSLATIONS_INITIAL_WORK_POLISH);
	translationPolish.furtherWork.LoadString(IDS_STRING_TRANSLATIONS_FURTHER_WORK_POLISH);
	listTranslations.push_back(translationPolish);

	// Serbian translation
	Translation translationSerbian;
	translationSerbian.heading.LoadString(IDS_STRING_TRANSLATIONS_HEADING_SERBIAN);
	translationSerbian.initialWork.LoadString(IDS_STRING_TRANSLATIONS_INITIAL_WORK_SERBIAN);
	translationSerbian.furtherWork.LoadString(IDS_STRING_TRANSLATIONS_FURTHER_WORK_SERBIAN);
	listTranslations.push_back(translationSerbian);

	// Spanish translation
	Translation translationSpanish;
	translationSpanish.heading.LoadString(IDS_STRING_TRANSLATIONS_HEADING_SPANISH);
	translationSpanish.initialWork.LoadString(IDS_STRING_TRANSLATIONS_INITIAL_WORK_SPANISH);
	translationSpanish.furtherWork.LoadString(IDS_STRING_TRANSLATIONS_FURTHER_WORK_SPANISH);
	listTranslations.push_back(translationSpanish);

	// now insert all translations into the text field
	for(std::list<Translation>::iterator iter=listTranslations.begin(); iter!=listTranslations.end(); iter++) {
		CString heading = (*iter).heading;
		CString initialWork = (*iter).initialWork;
		CString furtherWork = (*iter).furtherWork;
		
		translationsInformation.Append(heading);
		translationsInformation.Append("\r\n");
		// do some magic to underline the heading with "=" characters
		for(int i=0; i<heading.GetLength()*2/3; i++)
			translationsInformation.Append("=");
		translationsInformation.Append("\r\n");
		translationsInformation.Append(initialWork);
		translationsInformation.Append("\r\n");
		translationsInformation.Append(furtherWork);
		translationsInformation.Append("\r\n");
		translationsInformation.Append("\r\n");
		translationsInformation.Append("\r\n");
	}

	UpdateData(false);
	
	return TRUE;
}