//////////////////////////////////////////////////////////////////
// Copyright 2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Matej Matejicek 2001
// Deutsche Bank AG Frankfurt - IT Security
//////////////////////////////////////////////////////////////////
//
// Zufallsgenerator_Tests_Alles.h: Schnittstelle für die Klasse Zufallsgenerator_Tests.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUFALLSGENERATOR_TESTS_ALLES_H__F59A6EF7_8003_11D5_A855_00025532117A__INCLUDED_)
#define AFX_ZUFALLSGENERATOR_TESTS_ALLES_H__F59A6EF7_8003_11D5_A855_00025532117A__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

double EntropyBin_mod(const char *infile, const char *OldTitle);
double Entropy_mod( const char* infile, SymbolArray &text );

class Zufallsgenerator_Tests  
{

protected:

	//Die Variablen

	UINT testlen;
	UINT offs;
	UINT degr;				//Kein ID sondern das Wert von den Freiheitsgrad v
	double test_ergeb;		//Das Test-Ergebnis
	double def_param;		//parameter mit dem man das Ergebnis vergleicht
	BOOL bestanden;			//Ob das Test bestanden ist oder nicht
	
	//Die Member-Funktionen

	void vergleiche_test_ergeb(); //Die Vergleichung von def_param und test_ergeb
	void Set_test_ergeb( double n ) { test_ergeb = n; }
	void Set_result( BOOL n ) { bestanden = n; }
	double Get_test_ergeb() { return test_ergeb; }
	double Get_DefParam() { return def_param; }
	const char *infile;    //für die test() Funktion
	const char *oldtitle;  //für die test() Funktion



public:
	BOOL fips;
	UINT tupel;
	void Set_degr( UINT n ) { degr = n; }
	void Set_infile( const char *n ) { infile = n; }
	void Set_oldtitle( const char *n ) { oldtitle = n; }
	void Set_DefParam( double n ) { def_param = n; }
	virtual void test() = 0;
	BOOL GetResult() { return bestanden; }
	BOOL SetOffset( UINT n );
	BOOL SetTestLength( UINT n );
	UINT Get_degr() { return degr; }
	BOOL def, def2; // def ist für default Offset und Testlänge
					// def2 ist für Random Offset und Testlänge

	//Konstruktor-Destruktor

	Zufallsgenerator_Tests();
	virtual ~Zufallsgenerator_Tests();

};

// Frequency Test
class Freq_Test : public Zufallsgenerator_Tests  
{
public:
	long einsen;
	UINT tupel;

	//Konstruktor-Destruktor

	Freq_Test();
	virtual ~Freq_Test();

	//Definition von der virtuellen Funktion test()

	void test();

};


class Serial_Test : public Zufallsgenerator_Tests  
{
public:
	void test();
	Serial_Test();
	virtual ~Serial_Test();

};


class Long_Run_Test : public Zufallsgenerator_Tests  
{
public:
	BOOL fips_flag;
	UINT longrun_lang;
	void test();
	BOOL longrun ( CString infile, int runs_groesse);
	Long_Run_Test();
	virtual ~Long_Run_Test();

};



class Runs_Test : public Zufallsgenerator_Tests  
{
public:
	long runlang;
	double erwartet ( long folge, int i );
	long zaehle_luck_block ( long lang, BOOL was, const char *infile, unsigned int offset, unsigned int bis );
	void Set_runlang ( long n ) { runlang = n; }
	void Set_degr ( UINT n ) { degr = ((n*2)-2); }
	void test();
	Runs_Test();
	virtual ~Runs_Test();

};


class Poker_Test : public Zufallsgenerator_Tests  
{
public:
	double tmp_Test_Ergebnis;
	void test();
	Poker_Test();
	virtual ~Poker_Test();
};

#endif // !defined(AFX_ZUFALLSGENERATOR_TESTS_ALLES_H__F59A6EF7_8003_11D5_A855_00025532117A__INCLUDED_)

