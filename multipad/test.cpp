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

// Dies ist eine Beispieldatei zur Analyse-Bibliothek.

#include "libanalyse/stdinc.h"
#include "libanalyse/Des.h"

int main()
{
	DES des(0x01234567,0x89abcdef);

	SymbolArray s1(NumConverter(0xFFFFFFFF) << Converter::Hex(),10000);
	s1.Apply(des);

	SymbolArray s2(NumConverter(0xFFFFFFFF),10000);
	s2[0]=1;
	s2.Apply(des);	

	cout << "Autokorrelation von s1" << endl;
	SCorrelation c(s1);
	c.Show( OStream() << OStream::Sorted() << OStream::MaxN(20));

	// s1 und s2 in Bytes umwandeln
	SymbolArray s3=s1.ByteStream();
	s3 << Converter::Hex();
	SymbolArray s4=s2.ByteStream();
	s3 << Converter::Hex();

	s3+=0;
	s4+=0;
	cout << "Entropie von s1    " << Entropie(s3) << endl;
	cout << "Entropie von s2    " << Entropie(s4) << endl;
	s3^=s4;
	cout << "Entropie von s1^x2 " << Entropie(s3) << endl;


}
}
}
