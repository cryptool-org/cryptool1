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


// ModifiedDocumentForHashing.cpp: Implementierung der Klasse ModifiedDocumentForHashing.
//
// Jan Blumenstein, Deutsche Bank AG, September 2002
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModifiedDocumentForHashing.h"
#include "CrypToolApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

void ModifiedDocumentForHashing::SetData(const char *OriginalDocument, const int OriginalDocumentLength,
									 const int SignificantBitLength)
// Beschreibung:	Reserviert den Speicher, den das modifizierte Dokument maximal benötigen könnte (wenn alle signifikanten
//					bits gesetzt sind),
//					setzt m_GeneralPositionsTable - in ihr sind die Positionen gespeichert, an denen Veränderungen im
//					Dokument vorgenommen werden können - in m_ModifiablePositions ist die Anzahl der Positionen abgelegt
// Parameter:		das Originaldokument (= Ausgangsbasis für Modifikationen) (OriginalDocument [Zeiger auf const char]),
//					Länge des Originaldokuments (OriginalDocumentLength [const int]),
//					Bitlänge des verwendeten Hash-Algorithmus' (HashAlgorithmBitLength [const int]);
// Rückgabewert:	keiner;
{
	m_DocumentLength = OriginalDocumentLength + SignificantBitLength;
	m_DocumentData = new char[m_DocumentLength];
	m_OriginalDocument = new DocumentForHashing(OriginalDocument, OriginalDocumentLength);
	m_ModifiedBytes = 0;
}
