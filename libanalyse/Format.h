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

#ifndef _FORMAT_H
#define _FORMAT_H 1

/////////////////////////////////////////////////////////////////////
// class Format - siehe Format2.h
#include "Format2.h"

#define FNUM(X) static const Format::Index X;
#define FSTRING(X) static const Format::SIndex X;

/////////////////////////////////////////////////////////////////////
// Namen mit __*Format: entsprechende Format-Klasse
//            _*Format: Formatdefinitionen (zur Namenskapselung)
//			   *Format: beides zusammen

typedef NFormat<int,Format,0> __CommonFormat;

class _CommonFormat
{
public:
	FSTRING(Sep)		// zwischen Werten ausgeben
	FSTRING(LF)			// am Zeilenende ausgeben
	FNUM(Hex)			// Ganzzahlen als Hex anzeigen
};

//class CommonFormat : public __CommonFormat, public _CommonFormat
//{};

/////////////////////////////////////////////////////////////////////
class _Converter {};
typedef NFormat<_Converter,__CommonFormat,1024> __ConverterFormat;

class ConverterFormat : public _CommonFormat, public __ConverterFormat
{
public:
	FNUM(RawData)
	FNUM(SymbolsperLine)

	FSTRING(TupleBegin)	// bei Tupeln: Voher ausgeben
	FSTRING(TupleSep)	// dazwischen
	FSTRING(TupleEnd)	// am Ende
	
	class _BracketTuples : public Manipulator<Format>
	{
		void manip(Format& b) const
		{b << ConverterFormat::TupleBegin("(") << ConverterFormat::TupleSep(",") << ConverterFormat::TupleEnd(")");}
	};
	static _BracketTuples BracketTuples() {return _BracketTuples();}
};

/////////////////////////////////////////////////////////////////////

class _OStream {};
typedef NFormat<_OStream,__CommonFormat,1024> __OStreamFormat;

class _OStreamFormat : public _CommonFormat
{
public:
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
};

//class OStreamFormat : public __OStreamFormat, public _OStreamFormat
//{};

/////////////////////////////////////////////////////////////////////

#undef FNUM
#undef FSTRING


#endif /* _FORMAT_H */