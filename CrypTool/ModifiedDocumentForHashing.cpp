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
}
