/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


// SignatureAttackMFC.h: Schnittstelle für die Klasse SignatureAttackMFC.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGNATUREATTACKMFC_H__8BCF9CB3_E0C4_11D6_9DF9_000629718A52__INCLUDED_)
#define AFX_SIGNATUREATTACKMFC_H__8BCF9CB3_E0C4_11D6_9DF9_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SignatureAttack.h"


class SignatureAttackMFC : public SignatureAttack, public CProgressModel
{
public:
	SignatureAttackMFC();
	SignatureAttackMFC(OptionsForSignatureAttack *OptForSigAtt, FILE *SigAttTest,
									   int TotalAttemptsCounter, HWND hWnd, UINT messageID);
	virtual ~SignatureAttackMFC();
	static UINT StaticThreadFunction(void * param)
	{
		SignatureAttack *SA = (SignatureAttack *) param;
		ASSERT(NULL != SA);
		return SA->Do_Floyd();
	}

private:
	char m_Text[256];
	int m_SearchMode;
	CString m_ProgressText;
	HWND m_hwnd;
	__int64 m_OldProgressPercentage;
	__int64 m_NewProgressPercentage;
	UINT m_messageID;

	virtual bool CheckCanceledProgress();
	virtual void StartShowProgress();
	virtual double getProgress();
	virtual void SignalEnd();
	virtual void SetProgressTextNewRun(const bool IsNewRun);

};

#endif // !defined(AFX_SIGNATUREATTACKMFC_H__8BCF9CB3_E0C4_11D6_9DF9_000629718A52__INCLUDED_)
