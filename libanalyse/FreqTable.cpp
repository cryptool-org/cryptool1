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
