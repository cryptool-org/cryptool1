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


// SignatureAttack.h: Schnittstelle für die Klasse SignatureAttack.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGNATUREATTACK_H__C4452B93_B590_11D6_9DD3_000629718A52__INCLUDED_)
#define AFX_SIGNATUREATTACK_H__C4452B93_B590_11D6_9DD3_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BitParity.h"
#include "HashingOperations.h"
#include "OptionsForSignatureAttack.h"
#include "ResultsOfSignatureAttack.h"
#include "sys\timeb.h"

class SignatureAttack  
{
	double CalculateTimeSpan(_timeb &Start, _timeb &Finish);
	bool CollisionConfirmation(char *HashValue_single_step, char *HashValue_init);
	bool HashEqual(const char *HashValue_single_step, const char *HashValue_double_step) const;
	void InternalStep(int &HashValueParity, char *HashValue);

protected:
	virtual void SignalEnd() { ; }
	virtual bool CheckCanceledProgress() { return false; }
	virtual void StartShowProgress() { ; }
	virtual void SetProgressTextNewRun(const bool IsNewRun) { ; }
	BitParity m_BitPar;
	OptionsForSignatureAttack *m_OptSigAtt;
	ResultsOfSignatureAttack *m_ResSigAtt;
	FILE *m_TestFile;
	int m_TotalAttemptsCounter;

public:
	SignatureAttack();
	SignatureAttack(OptionsForSignatureAttack *m_OptSigAtt);
	SignatureAttack(OptionsForSignatureAttack *m_OptSigAtt, FILE *SigAttTest, int TotalAttemptsCounter);
	virtual ~SignatureAttack();
	UINT Do_Floyd();
	ResultsOfSignatureAttack *GetResults() const { return m_ResSigAtt; }
	
};

#endif // !defined(AFX_SIGNATUREATTACK_H__C4452B93_B590_11D6_9DD3_000629718A52__INCLUDED_)
