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

//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Autoren.cpp: Implementierungsdatei
//

// for file locations relative to CrypTool
extern char *Pfad;

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgAuthors.h"
#include "DlgPrimesGeneratorDemo.h" // FIXME???
#include <stdio.h>
#include "HashingOperations.h"
#include "SecudeCryptography.h"

#include <string>
#include <list>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// this is a static hash value (used for integrity of the authors.txt file)
static const CString authorsFileHash = "AB 72 69 8A 36 79 90 FF 85 D4 72 1C 50 CA 5D BC 6E B5 A9 35 EC 9C 91 06 EB 57 C6 17 C1 21 39 73 4E 4A 5B 3E 62 DB 52 DE 1B 22 EB B6 36 63 54 09 D3 1C 13 AC 2A 65 68 AB 3E F5 B9 9D EC 70 98 4F";

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAuthors 

CDlgAuthors::CDlgAuthors(CWnd* pParent /*=NULL*/)
: CDialog(CDlgAuthors::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAuthors)
	// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}

void CDlgAuthors::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAuthors)
	// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	DDX_Text(pDX, IDC_EDIT_AUTHORS_1, authorsImplementationDocumentationTranslation);
	DDX_Text(pDX, IDC_EDIT_AUTHORS_2, authorsReviewFeedback);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgAuthors, CDialog)
//{{AFX_MSG_MAP(CDlgAuthors)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgAuthors 

BOOL CDlgAuthors::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// read authors from authors.txt
	readAuthors();

	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgAuthors::readAuthors()
{
	// maximum number of characters per line before a line break is inserted
	const int maxCharsPerLine = 65;

	// build path to the "authors.txt" file
	const CString authorsFileName = Pfad + CString("authors.txt");

	// check the hash value of the authors file (SHA-512)
	char messageDigest[64+1];
	memset(messageDigest, 0, 64+1);
	FILE *in = fopen((char*)(LPCTSTR)authorsFileName,"rb");
	ASSERT(in);
	long m_pos = 0;
	fseek(in,0,SEEK_END);
	long m_size = ftell(in);
	fseek(in,0,SEEK_SET);
	size_t n;

	char *buffer = new char[m_size+1];
	memset(buffer, 0, m_size+1);
	n = fread(buffer, 1, m_size, in);

	// create hashing operations object (index 7 = SHA-512)
	HashingOperations hashingOperations(7);
	hashingOperations.DoHash(buffer, n, messageDigest);
	
	delete buffer;

	CString messageDigestString;
	dataToHexDump(messageDigest, 64, messageDigestString);

	// compare message digest string to built-in string
	if(authorsFileHash != messageDigestString) {
		// don't display any authors if strings don't match
		LoadString(AfxGetInstanceHandle(), IDS_AUTHORS_FILE_CORRUPTED, pc_str, STR_LAENGE_STRING_TABLE);
		authorsImplementationDocumentationTranslation = pc_str;
		authorsReviewFeedback = pc_str;
	}
	// at this point the hash value seems fine, read authors and proceed...
	else {
		// create a handle for authors file
		std::ifstream fileAuthors;
		fileAuthors.open(authorsFileName);
		if(!fileAuthors) {
			// display error message and return
			LoadString(AfxGetInstanceHandle(), IDS_AUTHORS_FILE_MISSING, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
			return;
		}

		// two lists of authors (due to the two differenct sections in the authors file)
		std::list<CString> listAuthors[2];

		// misc variables
		std::string temp;
		CString tempString;
		CString authorName;
		CString authorFirstName;
		CString authorLastName;

		// the authors file consists of different (up to now: two) sections
		int currentSection = 0;

		while(!fileAuthors.eof()) {
			getline(fileAuthors, temp);
			tempString = temp.c_str();
			// discard empty lines
			if(tempString.IsEmpty()) continue;
			// check for section 1: IMPLEMENTATION DOCUMENTATION TRANSLATION
			if(tempString.Find("[IMPLEMENTATION DOCUMENTATION TRANSLATION]") != -1) {
				currentSection++;
				continue;
			}
			// check for section 2: REVIEW FEEDBACK
			if(tempString.Find("[REVIEW FEEDBACK]") != -1) {
				currentSection++;
				continue;
			}
			// discard lines beginning with a hash
			if(tempString.Find("#") == 0) {
				continue;
			}

			// now extract the author's name
			authorName = tempString;
			// if the author's name consists of more than one word, we have a first and a last name;
			// in case of more than two words, only the first one is considered as first name, the 
			// remainder (everything after the first space character) is considered as last name
			int indexSpace = 0;
			if((indexSpace = authorName.Find(" ")) != -1) {
				authorFirstName = authorName.Left(indexSpace);
				authorName.Delete(0, indexSpace + 1);
				authorLastName = authorName;
			}
			else {
				authorFirstName = "";
				authorLastName = authorName;
			}
			// we now format the author's name as follows: "[LASTNAME] [ , [FIRSTNAME] ]"
			authorName = authorLastName + ", " + authorFirstName;
			// now add the formatted author's name to the list
			if(currentSection == 1) listAuthors[0].push_back(authorName);
			if(currentSection == 2) listAuthors[1].push_back(authorName);
		}

		// close authors file
		fileAuthors.close();

		// sort the author's lists
		listAuthors[0].sort();
		listAuthors[1].sort();

		// fill the GUI elements
		for(int listNo=0; listNo<2; listNo++) {
			for(std::list<CString>::iterator iter=listAuthors[listNo].begin(); iter!=listAuthors[listNo].end(); iter++) {
				int indexComma = 0;
				if((indexComma = (*iter).Find(",")) != -1) {
					authorFirstName = (*iter);
					authorLastName = (*iter);
					authorFirstName.Delete(0, indexComma + 2);
					authorLastName.Delete(indexComma, authorLastName.GetLength() - indexComma);
					authorName = authorFirstName + " " + authorLastName;
				}
				else {
					authorName = (*iter);
				}
				// if this is not the first author in the list, prepend a comma (append it to the existing string)
				if(iter != listAuthors[listNo].begin()) {
					if(listNo == 0) {
						authorsImplementationDocumentationTranslation.Append(", ");
					}
					if(listNo == 1) {
						authorsReviewFeedback.Append(", ");
					}
				}
				// add the authors to the lists
				if(listNo == 0) {
					// quick and dirty: because the Windows controls don't support automatic line breaks,
					// we will manually override this behavior
					if(authorsImplementationDocumentationTranslation.GetLength() - authorsImplementationDocumentationTranslation.ReverseFind('\n') > maxCharsPerLine)
						authorsImplementationDocumentationTranslation.Append("\r\n");
					authorsImplementationDocumentationTranslation.Append(authorName);
				}
				if(listNo == 1) {
					// quick and dirty: because the Windows controls don't support automatic line breaks,
					// we will manually override this behavior
					if(authorsReviewFeedback.GetLength() - authorsReviewFeedback.ReverseFind('\n') > maxCharsPerLine)
						authorsReviewFeedback.Append("\n");
					authorsReviewFeedback.Append(authorName);
				}
			}
		}

		// append "..." to indicate there were additional authors that didn't want to be listed
		this->authorsImplementationDocumentationTranslation.Append(" ...");
		this->authorsReviewFeedback.Append(" ...");
	}
}