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

/////////////////////////////////////////////////////////////////////
// NGramm
// Dieses Testprogramm liest den Referenztext deutsch.txt ein
// und ermittelt dessen Haeufigkeits- und Bigrammverteilung
// sowie die Entropie und Redundanz.

int main()
{

        SymbolArray dtext(AlphaConv);
	dtext.Read("deutsch.txt");
	NGram d(dtext);
	NGram d2(dtext,2);
	d.Show(OStream() << OStream::Percent());
	//d.Show(PlotStream() << OStream::Boxes() << OStream::Float());
	//d2.Show(OStream() << OStream::Percent());

	// Beispiel
	cout << "Entropie:   " << d.Entropie() << endl;
	cout << "Redundanz:  " << d.Redundanz() << endl;
	cout << "Bigramm-" << endl;
	cout << "Entropie:   " << d2.Entropie() << endl;
	cout << "Redundanz:  " << d2.Redundanz() << endl;

	cout << "Entropie3: " << Entropie(dtext,3) << endl;
	// cout << "Entropie4: " << Entropie(dtext,4) << endl;
	//cout << "Entropie5: " << Entropie(dtext,5) << endl;

	// Beispiel
	cout << "Koinzidenzindex: " << d.Koinzidenz() <<  endl;

}



