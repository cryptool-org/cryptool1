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


// ResultsOfSignatureAttack.cpp: Implementierung der Klasse ResultsOfSignatureAttack.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "ResultsOfSignatureAttack.h"
#include "ErrorcodesForSignatureAttack.h"
#include "HashingOperations.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ResultsOfSignatureAttack::ResultsOfSignatureAttack()
{
	c_filename_fake = c_filename_original = m_MatchingHashBytes = NULL;
}

ResultsOfSignatureAttack::ResultsOfSignatureAttack(const int HashAlgorithmID, const int BitLength)
{
	c_filename_fake = c_filename_original = m_MatchingHashBytes = NULL;
	SetData(HashAlgorithmID, BitLength);	
}

void ResultsOfSignatureAttack::SetFilenames(const char *filenameOriginal, const char *filenameFake)
{
	if ( filenameFake )
	{
		if (c_filename_fake) delete []c_filename_fake;
		c_filename_fake = new char[strlen(filenameFake)+1];
		strcpy(c_filename_fake, filenameFake);
	}	
	if ( filenameOriginal )
	{
		if (c_filename_original) delete []c_filename_original;
		c_filename_original = new char[strlen(filenameOriginal)+1];
		strcpy(c_filename_original, filenameOriginal);
	}
}

ResultsOfSignatureAttack::~ResultsOfSignatureAttack()
{
	delete []m_MatchingHashBytes;
	delete []c_filename_fake;
	delete []c_filename_original;
}

void ResultsOfSignatureAttack::SetData(const int &HashAlgorithmID, const int &BitLength)
{
	int ii;

	m_FloydResult = _SIG_ATT_NO_DOCUMENTS_FOUND;
	for (ii = 0; ii < _MAX_RUNS_SIG_ATT; ii ++)
	{
		m_StepsPerRun[ii].StepsUntilCollision		= 0;
		m_StepsPerRun[ii].StepsUntilConfirmation	= 0;
		m_StepsPerRun[ii].TotalSteps				= 0;
	}

	m_ExpectedSteps = (long long)ceil((double)(pow((double)2, ((double) BitLength / 2)) * 1.25 * 2));	// stimmt 1.25 ?
	m_Runs						= 0;
	m_TotalSteps				= 0;
	m_EffectiveTime				= 0.0;
	m_HashOperationsPerformed	= 0;
	HashingOperations HO(HashAlgorithmID);
	m_HashAlgorithmID			= HashAlgorithmID;

	m_ExpectedTime				= (double) m_ExpectedSteps * 5 / HO.GetHashOpsPerSecond();	// rechnerabhängig!
	m_BitLength					= BitLength;
	m_MatchingHashBytes			= new char[BitLength / 8];
}

void ResultsOfSignatureAttack::SetMatchingHashBytes(const char *MatchingHashBytes, const int CompleteByteLength)
{
	int ii;
	
	for (ii = 0; ii < CompleteByteLength; ii ++)
	{
		m_MatchingHashBytes[ii] = MatchingHashBytes[ii];
	}
}
