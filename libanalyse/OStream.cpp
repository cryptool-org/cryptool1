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

#include "la_ostream.h"

#include <stdlib.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////
// OStream 

OStream::OStream(ostream& out /*=cout*/) : m_out(&out)
{
	m_freeout=0;
	Init();
}
OStream::OStream(const char* s)
{
	m_freeout=0;
	m_out=new ofstream(s);
	if (!m_out) { // ERROR
		m_out=&cout;
	} else 
		m_freeout=1;
	Init();
}
OStream::~OStream() 
{
	if (m_freeout) delete m_out;
}

void OStream::Init()
{
	(*this) << Sep(" ") << LF("\n") << Description(1) << Summary(1);
	(*this) << MaxN(-1) << MinN(-1);
	(*this) << Precision(6);
}


/////////////////////////////////////////////////////////////////////
// PlotStream functions

PlotStream::PlotStream(const char* s) : OStream(s), m_filename(s)
{
	(*this) << Sorted(0) << Sep("\n") << LF("\n");
	//(*this) << Float(0);
	(*this) << Title(0) << Description(0) << Summary(0);

}
PlotStream::~PlotStream() 
{
	const char *scriptname="plot.cmd";

	if (!(*this)[DontShow]) { // Plot anzeigen
		// Plot-Script erzeugen
		ofstream script(scriptname);
		if ((*this)[PostScript]) 
			script << "set terminal postscript eps\n";
		script << "plot \"" << m_filename << "\"";
		if ((*this)[PlotTitle]!=NULLSTRING) 
			script << " title \"" << ((*this)[PlotTitle]) << "\"";
		if ((*this)[Boxes]) script << " with boxes\n";
		else script << " with lines\n";
		if (!(*this)[PostScript]) 
			script << "pause -1 \"Press return to continue\"\n";
        if (m_freeout) delete m_out;
        m_freeout = 0;
 		script.close();
		// gnuplot starten
		String gnucmd("gnuplot ");
		gnucmd+=scriptname;
		if ((*this)[PostScript]) {
			gnucmd+=" >";
			if ((*this)[EPSName]!=NULLSTRING) gnucmd+=(*this)[EPSName];
			else gnucmd+="plot.eps";
		}
		system(gnucmd);
	}

	if (!(*this)[DontDelete]) {
		// temporaere Dateien loeschen
		remove(m_filename);
		remove(scriptname);
	}
}
