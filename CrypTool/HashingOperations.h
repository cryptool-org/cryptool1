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


// HashingOperations.h: Schnittstelle für die Klasse HashingOperations.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HASHINGOPERATIONS_H__94B56021_D434_11D6_9DEF_000629718A52__INCLUDED_)
#define AFX_HASHINGOPERATIONS_H__94B56021_D434_11D6_9DEF_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ErrorcodesForSignatureAttack.h"

typedef void (*fp_Init_t) (void *context);
typedef void (*fp_Update_t) (void *context, void *data, unsigned long len);
typedef void (*fp_Final_t) (void *hash, void *context);

struct HashAlgorithmsFP
{
	fp_Init_t fp_Init;
	fp_Update_t fp_Update;
	fp_Final_t fp_Final;
	void *Context;
	int ContextSize;
	int BitLength;
	char *Name;
	int HashOpsPerSecond;	// ausgehend von einem Rechner mit ???-Prozessor und ??? MHz Taktfrequenz
};

struct HashAlgorithmsFP HAFP[];

class HashingOperations  
{
	void *m_HashContext;
	int m_HashAlgorithmID;
	void SetData(int HashAlgorithmID);
	int m_Errorcode;
	int m_AlgorithmCounter;

public:
			 HashingOperations(int HashAlgorithmID) { SetData(HashAlgorithmID); }
	virtual ~HashingOperations();

	int		GetHashAlgorithmBitLength() const;
	char   *GetHashAlgorithmName() const;
	int		GetHashOpsPerSecond() const;
	int		GetErrorcode() const
	{ // 0 = OK, 1 = kein Hash-Algorithmus implementiert, 2 = ungültige Hash-Algorithmus-ID;
		return m_Errorcode;
	}
	int		GetHashAlgorithmID() const { return m_HashAlgorithmID; }
	void	DoHash(char *OriginalDocument, const int OriginalDocumentLength, char *ResultingHashValue) const;
	HashAlgorithmsFP *getHashAlgorithmsFP() { return &(HAFP[m_HashAlgorithmID]); };	
	// these three functions provide a public access for hashing in chunks
	void	chunkHashInit();
	void	chunkHashUpdate(void *_message, const int _messageLength);
	void	chunkHashFinal(char *_messageDigest);
};

#endif // !defined(AFX_HASHINGOPERATIONS_H__94B56021_D434_11D6_9DEF_000629718A52__INCLUDED_)
