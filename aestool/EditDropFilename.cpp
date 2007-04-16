// EditDropFilename.cpp : implementation file
//

#include "stdafx.h"
#include "aestool.h"
#include "EditDropFilename.h"
#include ".\editdropfilename.h"
#include "atlcomcli.h"
#include "string.h"



// CEditDropFilename

IMPLEMENT_DYNAMIC(CEditDropFilename, CEdit)
CEditDropFilename::CEditDropFilename()
{
}

CEditDropFilename::~CEditDropFilename()
{
}


BEGIN_MESSAGE_MAP(CEditDropFilename, CEdit)
	ON_WM_CREATE()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()



// CEditDropFilename message handlers


int CEditDropFilename::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	DragAcceptFiles();
	return 0;
}

void CEditDropFilename::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default
	int numDroppedFiles = DragQueryFile(hDropInfo, -1, NULL, 0 );
	int fPathLength, ndx = 0;
	char *fPath = 0; 
	while ( ndx < numDroppedFiles )
	{
		if ( fPathLength = DragQueryFile(hDropInfo, ndx, NULL, 0) )
		{
			fPath = new char[fPathLength+1];
			if ( !fPath )
			{	// FIXME, current if allocating fails the program continues without drop file 
				break;
			}
			DragQueryFile(hDropInfo, ndx, fPath, fPathLength+1);
			break;
		}				
		ndx++;
	}
	// FIXME, message if more than one file is dropped 
	
	DragFinish(hDropInfo);

	if ( fPath ) 
	{
		CFileStatus fStatus;
		CFile testFile;

		CString filename = expandShortCut( fPath );

		if ( testFile.GetStatus( filename, fStatus ) )
		{
			filename = fStatus.m_szFullName;
			if ( fStatus.m_attribute == 0x10 )
				filename += "\\*.*";
			SetWindowText(filename);
			SetSel(filename.GetLength(), filename.GetLength());
			SetFocus();
		}
		delete []fPath;
	}

	// CEdit::OnDropFiles(hDropInfo);
}

//////////////////////////////////////////////////////////////////
//	expand shortcuts (synbolic links)

#define __MAX_FULLPATH_SIZE 1024

CString CEditDropFilename::expandShortCut(LPTSTR f_str)
{
    ASSERT(f_str != 0);
	CString outFile = f_str;

    IShellLink* ptr_sl;
	// Create instance for shell link
	if (   SUCCEEDED(::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, 
							IID_IShellLink, (LPVOID*) &ptr_sl) )
		&&  SUCCEEDED( ptr_sl->SetPath(f_str)) )
	{	
		CComQIPtr<IPersistFile> ptr_PersistFile(ptr_sl);
		WCHAR wf_str[__MAX_FULLPATH_SIZE];
		MultiByteToWideChar(CP_ACP, 0, f_str, -1, wf_str, __MAX_FULLPATH_SIZE);

		if (   SUCCEEDED(ptr_PersistFile->Load(wf_str, STGM_READ)) 
			&& SUCCEEDED(ptr_sl->Resolve( NULL, SLR_UPDATE | SLR_NO_UI )) ) // no warning-message "SLR_NO_UI" as of infty loops
		{
			char fullPath[__MAX_FULLPATH_SIZE];
			if ( SUCCEEDED(ptr_sl->GetPath( fullPath, __MAX_FULLPATH_SIZE, NULL, SLGP_UNCPRIORITY )) )
				outFile = fullPath;
		}
	}

	// if this fails, outFile == ""
    return outFile;
}
