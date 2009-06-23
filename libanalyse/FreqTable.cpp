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

#include "FreqTable.h"

#ifndef _OSTREAM_H
#include "la_ostream.h"
#endif
#ifndef _ITERATOR2_H
#include "Iterator2.h"
#endif

///////////////////////////////////////////////////////////////////
//  FreqTable

FreqTable::FreqTable(int rows /*=1*/, int columns /*=1*/)
{
	ASSERT(rows*columns>0);
	m_Rows=rows;
	m_Columns=columns;
	m_hcount.SetSize(rows*columns);
	m_TotalCount=0;
}

void FreqTable::Load(istream& stream)
{
	LoadObject(m_TotalCount,stream);
	m_hcount.Load(stream);
}

void FreqTable::Save(ostream& stream) const
{
	SaveObject(m_TotalCount,stream);
	m_hcount.Save(stream);
}

void FreqTable::Show(OStream& out /*=DefaultOStream*/) const
{

	if (out[OStream::Summary]) {
		out << "Gesamtzahl: " << m_TotalCount << endl;
	}
	
	if (out[OStream::Float] || out[OStream::Percent]) {
		if (m_Rows==1 || m_Columns==1)
			((baseclass*)this)->Show(out,1);
		else
			((baseclass*)this)->Show(out,m_Rows,m_Columns);
	} else {
		if (m_Rows==1 || m_Columns==1)
			FreqCountTable(*this).Show(out,1);
		else
			FreqCountTable(*this).Show(out,m_Rows,m_Columns);
	}

}
