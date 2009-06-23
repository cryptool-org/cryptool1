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

/////////////////////////////////////////////////////////////////
//
// Diese Datei ist Bestandteil der Diplomarbeit
// "Eine C++-Bibliothek zur informationstheoretischen Kryptanalyse 
// von Stromchiffren und PZ-Folgen" am Europaeischen Institut fuer
// Systemsicherheit, Prof. Dr. Th. Beth
//
// von und (c) 1997-98 Michael Friedrich
//
/////////////////////////////////////////////////////////////////

// Diese Datei enthaelt globale Objekte, die voneinander abhaengig sind
// und deswegen in einer bestimmten Reihenfolgen initialisiert werden muessen

#include "Converter.h"

#ifndef _FORMAT_H
#include "Format.h"
#endif

/*
#ifndef _CONVERTER_H
#include "Converter.h"
#endif
*/

#define FNUM(X) const Format::Index _FCLASS_ :: X = _FCLASS2_ :: NewIndex();
#define FSTRING(X) const Format::SIndex _FCLASS_ :: X = _FCLASS2_ :: NewString();

/////////////////////////////////////////////////////////////////////
// Format - static members

String NULLSTRING("");

int Format::currentindex=0;
int Format::currentstringindex=0;
int Format::currentoffset=0;

/////////////////////////////////////////////////////////////////////
// CommonFormat

#undef _FCLASS_
#undef _FCLASS2_
#define _FCLASS_ _CommonFormat
#define _FCLASS2_ __CommonFormat
	FSTRING(Sep)
	FSTRING(LF)
	FNUM(Hex)			// Ganzzahlen als Hex anzeigen

/////////////////////////////////////////////////////////////////////
// ConverterFormat

#undef _FCLASS_
#undef _FCLASS2_
#define _FCLASS_ ConverterFormat
#define _FCLASS2_ ConverterFormat
	FNUM(RawData)
	FNUM(SymbolsperLine)

//	FSTRING(Sep)
//	FSTRING(LF)
	FSTRING(TupleBegin)
	FSTRING(TupleSep)
	FSTRING(TupleEnd)

/////////////////////////////////////////////////////////////////////
// OStreamFormat

#undef _FCLASS_
#undef _FCLASS2_
#define _FCLASS_ _OStreamFormat
#define _FCLASS2_ __OStreamFormat
	FNUM(Details)		// 0..7, z.Z. nur von LFSR benutzt
//
	FNUM(Title)			// Titel ausgeben
	FNUM(Description)	// Beschreibung ausgeben (bei Tabellen, Matrix)
	FNUM(Summary)		// FreqTable: TotalCount
// Bereich und Sortierung
	FNUM(Start)			// Auszugebenden Bereich einschraenken
	FNUM(Size)			// dito
	FNUM(Sorted)		// sortierte Ausgabe: 0=aus, 1=an (aufsteigend), 2=an (absteigend)
	FNUM(MaxN)			// ersten N maximale u. minmale Werte ausgeben
	FNUM(MinN)			// (-1/-1: aus), sortierung mit Sorted(1) einschalten!!!
// Zahlenformat
	FNUM(Float)			// Darstellung bevorzugt als Float (FreqTable, NGram, ...)
	FNUM(Percent)		// Darstellung bevorzugt in Prozent
//	FNUM(Align)			// 0=links, 1=rechts, 2=zentriert
    FNUM(Width)			// entspricht ios::width
	FNUM(Precision)		// entspricht ios::precision
// PlotStream
	FNUM(PostScript)	// nicht anzeigen, sondern als PS ausgeben
	FNUM(Boxes)			// Plot-Ausgabe mit Rechtecken, nicht Linien
	FSTRING(PlotTitle)	// Titel der Plotausgabe festlegen
	FSTRING(EPSName)	// Name der EPS-Datei, falls PostScript aktiviert
	FNUM(DontShow)		// nur Datei schreiben, nicht gnuplot aufrufen
	FNUM(DontDelete)	// PlotDateien nicht loeschen

/////////////////////////////////////////////////////////////////////

#undef FNUM
#undef FSTRING




/////////////////////////////////////////////////////////////////////
// Global converter objects

const IdConverter IdConv;
const AlphaConverter AlphaConv;
const AlphaSpaceConverter AlphaSpaceConv;
const BinConverter BinConv;
const NumConverter NumConv;
const NumConverter NullConv;
AppConverter AppConv;

/////////////////////////////////////////////////////////////////////
// Global OStream objects

#ifndef _OSTREAM_H
#include "la_ostream.h"
#endif

OStream DefaultOStream;



