// Zufallsgenerator_Tests_Alles.h: Schnittstelle für die Klasse Zufallsgenerator_Tests.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUFALLSGENERATOR_TESTS_ALLES_H__F59A6EF7_8003_11D5_A855_00025532117A__INCLUDED_)
#define AFX_ZUFALLSGENERATOR_TESTS_ALLES_H__F59A6EF7_8003_11D5_A855_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Zufallsgenerator_Tests  
{

protected:
	UINT TEST_ID;
	double alpha;
	double x1;
	BOOL bestanden;
	void vergleiche_x1();
	void Set_x1( double n ) { x1 = n; }
	void Set_result( BOOL n ) { bestanden = n; }

	double Get_x1() { return x1; }
	double Get_alpha() { return alpha; }

public:
	const char *infile;
	const char *oldtitle;
	void Set_infile( const char *n ) { infile = n; }
	void Set_oldtitle( const char *n ) { oldtitle = n; }
	virtual void test() = 0;
	BOOL GetResult() { return bestanden; }
	void Set_alpha( double n ) { alpha = n; }
	Zufallsgenerator_Tests();
	virtual ~Zufallsgenerator_Tests();

};


class Freq_Test : public Zufallsgenerator_Tests  
{
public:
	void test();
	Freq_Test();
	virtual ~Freq_Test();

};

#endif // !defined(AFX_ZUFALLSGENERATOR_TESTS_ALLES_H__F59A6EF7_8003_11D5_A855_00025532117A__INCLUDED_)

