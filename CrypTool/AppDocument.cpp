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
#include "AppDocument.h"
#include "Windows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppDocument

IMPLEMENT_DYNCREATE(CAppDocument, CDocument)

CAppDocument::CAppDocument()
{
	hWndVaterFenster = NULL;
	CWndVaterFenster = NULL;
	// go with "Arial 10" as default font
	fontSize = 10;
	fontFace = "Arial";
}

BOOL CAppDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CAppDocument::~CAppDocument()
{
}


BEGIN_MESSAGE_MAP(CAppDocument, CDocument)
	//{{AFX_MSG_MAP(CAppDocument)
	ON_UPDATE_COMMAND_UI(ID_GOTO_VATER, OnUpdateGotoVater)
	ON_UPDATE_COMMAND_UI(ID_SHOW_KEY, OnUpdateShowKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose CAppDocument

#ifdef _DEBUG
void CAppDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CAppDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Serialisierung CAppDocument 

void CAppDocument::Serialize(CArchive& ar)
{
	CObject::Serialize( ar );
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Code zum Speichern hier einfügen
	}
	else
	{
		// ZU ERLEDIGEN: Code zum Laden hier einfügen
	}
}

/////////////////////////////////////////////////////////////////////////////
// Befehle CAppDocument 

void CAppDocument::OnUpdateGotoVater(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen
	if(IsWindow(hWndVaterFenster))
	{
        pCmdUI->Enable(TRUE);
	}
	else
	{
        pCmdUI->Enable(FALSE);
	}
}

void CAppDocument::OnUpdateShowKey(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen
	
	if(csSchluessel.GetLength() > 0)
	{
        pCmdUI->Enable(TRUE);
	}
	else
	{
        pCmdUI->Enable(FALSE);
	}
}

void CAppDocument::SetData(int i)
{
}


BOOL CAppDocument::DoSave(LPCTSTR lpszPathName, BOOL bReplace)
{
	CString newName = lpszPathName;
	if (newName.IsEmpty())
	{
		CDocTemplate* pTemplate = GetDocTemplate();
		ASSERT(pTemplate != NULL);

		newName = m_strPathName;
		if (bReplace && newName.IsEmpty())
		{
			newName = m_strTitle;
			int i1, i3, i2;
			i2 = newName.FindOneOf(_T(">"));
			newName.ReleaseBuffer(i2);
			i1 = newName.ReverseFind('<');
			i3 = newName.ReverseFind('.');
			if (i3 >= i1) 
			{
				newName.ReleaseBuffer(i3);
				i2 = i3;
			}
			
			CString descr = _T("");
			if ( i1 >= 0 && i2 > i1 )
			{
				descr = newName.Mid(i1+1, i2-i1-1);
			}
			// check for dubious filename
			int iBad = newName.FindOneOf(_T(" -#%;/\\"));
			if (iBad != -1)
				newName.ReleaseBuffer(iBad);

			newName = CString("Cry-") + newName;
			if (descr.GetLength()) newName += CString("-") + descr;
			// append the default suffix if there is one
			CString strExt;
			if (pTemplate->GetDocString(strExt, CDocTemplate::filterExt) &&
			  !strExt.IsEmpty())
			{
				ASSERT(strExt[0] == '.');
				newName += strExt;
			}
		}

		if (!AfxGetApp()->DoPromptFileName(newName,
		  bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
		  OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, pTemplate))
			return FALSE;       // don't even attempt to save
		lpszPathName = newName;
	}

	return CDocument::DoSave(lpszPathName, bReplace );
}




