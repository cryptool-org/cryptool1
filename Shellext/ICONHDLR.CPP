// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
// Modudule: ICONHDLR.CPP
//
// Purpose:  Implements the IExtractIcon and IPersistFile member
//           functions necessary to support the icon handler portion
//           of this shell extension.
//

#include "priv.h"
#include "shellext.h"

extern HINSTANCE g_hmodThisDll; // Handle to this DLL itself.

// *********************** IExtractIcon Implementation *************************

STDMETHODIMP CShellExt::GetIconLocation(UINT   uFlags,
                                        LPSTR  szIconFile,
                                        UINT   cchMax,
                                        int   *piIndex,
                                        UINT  *pwFlags)
{
    *piIndex = 0;

    return S_OK;
}


STDMETHODIMP CShellExt::Extract(LPCSTR pszFile,
                                UINT   nIconIndex,
                                HICON  *phiconLarge,
                                HICON  *phiconSmall,
                                UINT   nIconSize)
{
    return S_FALSE;
}


// *********************** IPersistFile Implementation ******************

STDMETHODIMP CShellExt::GetClassID(LPCLSID lpClassID)
{
    return E_FAIL;
}

STDMETHODIMP CShellExt::IsDirty()
{
    return S_FALSE;
}

STDMETHODIMP CShellExt::Load(LPCOLESTR lpszFileName, DWORD grfMode)
{
    return NOERROR;
}

STDMETHODIMP CShellExt::Save(LPCOLESTR lpszFileName, BOOL fRemember)
{
    return E_FAIL;
}

STDMETHODIMP CShellExt::SaveCompleted(LPCOLESTR lpszFileName)
{
    return E_FAIL;
}

STDMETHODIMP CShellExt::GetCurFile(LPOLESTR FAR* lplpszFileName)
{
    return E_FAIL;
}
