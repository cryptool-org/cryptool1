// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   propshet.cpp
//
//  PURPOSE:   Implements the IShellPropSheetExt member functions necessary to 
//             support the property sheet page of this shell extension.  This
//             page is displayed when the user selects "Properties..." after
//             right clicking on a .GAK file
//

#include "priv.h"
#include "shellext.h"
#include "resource.h"

extern UINT g_cRefThisDll;         // Reference count of this DLL.
extern HINSTANCE g_hmodThisDll; // Handle to this DLL itself.

//
//  FUNCTION: GAKPageCallback(HWND, UINT, LPPROPSHEETPAGE)
//
//  PURPOSE: Callback  procedure for the property page
//
//  PARAMETERS:
//    hWnd      - Reserved (will always be NULL)
//    uMessage  - Action flag: Are we being created or released
//    ppsp      - The page that is being created or destroyed
//
//  RETURN VALUE:
//
//    Depends on message. 
//
//    For PSPCB_CREATE it's TRUE to let the page be created
//    or false to prevent it from being created.  
//    For PSPCB_RELEASE the return value is ignored.
//
//  COMMENTS:
//
UINT CALLBACK
GAKPageCallback(HWND hWnd,
                UINT uMessage,
                LPPROPSHEETPAGE  ppsp)
{
    return TRUE;
}

//
//  FUNCTION: GAKPageDlgProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Callback dialog procedure for the property page
//
//  PARAMETERS:
//    hDlg      - Dialog box window handle
//    uMessage  - current message
//    wParam    - depends on message
//    lParam    - depends on message
//
//  RETURN VALUE:
//
//    Depends on message.  In general, return TRUE if we process it.
//
//  COMMENTS:
//

BOOL CALLBACK GAKPageDlgProc(HWND hDlg, 
                             UINT uMessage, 
                             WPARAM wParam, 
                             LPARAM lParam)
{
    return FALSE;
}


//
//  FUNCTION: CShellExt::AddPages(LPFNADDPROPSHEETPAGE, LPARAM)
//
//  PURPOSE: Called by the shell just before the property sheet is displayed.
//
//  PARAMETERS:
//    lpfnAddPage -  Pointer to the Shell's AddPage function
//    lParam      -  Passed as second parameter to lpfnAddPage
//
//  RETURN VALUE:
//
//    NOERROR in all cases.  If for some reason our pages don't get added,
//    the Shell still needs to bring up the Properties... sheet.
//
//  COMMENTS:
//

STDMETHODIMP CShellExt::AddPages(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
{
    return NOERROR;
}

//
//  FUNCTION: CShellExt::ReplacePage(UINT, LPFNADDPROPSHEETPAGE, LPARAM)
//
//  PURPOSE: Called by the shell only for Control Panel property sheet 
//           extensions
//
//  PARAMETERS:
//    uPageID         -  ID of page to be replaced
//    lpfnReplaceWith -  Pointer to the Shell's Replace function
//    lParam          -  Passed as second parameter to lpfnReplaceWith
//
//  RETURN VALUE:
//
//    E_FAIL, since we don't support this function.  It should never be
//    called.

//  COMMENTS:
//

STDMETHODIMP CShellExt::ReplacePage(UINT uPageID, 
                                    LPFNADDPROPSHEETPAGE lpfnReplaceWith, 
                                    LPARAM lParam)
{
    return E_FAIL;
}
