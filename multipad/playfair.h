//////////////////////////////////////////////////////////////////
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

/*--------------------------------------------------------------------*/
/* Playfair-Algorithmus                                               */
/* - fuer 5x5 und 6x6 Quadrate                                        */
/* - incl. Ausgabe der Matrix und der Digramme (Buchstabenpaare)      */
/* - Verschluesselung und Entschluesselung                            */
/* - Ausgabe der Haeufigkeit der Digramme                             */
/* - Defaultwerte fuer Aufruf ohne Argumente fest eingestellt.        */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////
// playfair.h : Header f�r Playfair Algorithmus
//
/////////////////////////////////////////////////////////////////////////////
#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include "stdafx.h"
#include "commdlg.h"
#include <iostream.h>
#include <stdio.h>
#include "fileutil.h"
#include "resource.h"
#include "letter.h"
#include "assert.h"

/* used for uiUseOfDoublesInPass_s; default: doubles are eliminated ..*/
#define ELIMINATE_DOUBLES                   0  /* default */
/* Effect: password given:  playfair  ->  pass used:  PLAYFIR   */

#define IF_DOUBLES_TAKE_NEXT_UNUSED_LETTER  1  /* replace double letter */
/* Effect: password given:  nummer    ->  pass used:  NUMOER    */
/*                          playfair  ->  pass used:  PLAYFBIR  */
/*                          pbayfair  ->  pass used:  PBAYFCIR  */

#define MAXDIM        6          /* maximum dimension of the matrix ..*/
#define MAXDIGRAMMS  MAXDIM*MAXDIM*MAXDIM*MAXDIM /* maximum counts of digramms (36*36 = 1296) ..*/

enum playfair_neighbour
{
		undefined_pfnb,
        above,
        below,
        left,
        right
};
enum playfair_set
{
		undefined_pfset,
        row_sure,
        col_sure,
        rightorbelow,
        leftorabove,
        roworbelow,
        roworabove,
        roworcol
};

class playfair_letter        : public letter
{
public:
        playfair_letter (char c='\0');
        ~playfair_letter();
        bool operator==(const playfair_letter &other);
        bool operator!=(const playfair_letter &other);
		void clear_letter();
        playfair_letter* getAbove() const
        {
                 return my_above;
        }
/*        void setAbove(playfair_letter* the_above)
        {
                 my_above = the_above;
        }
*/
        playfair_letter* getBelow() const
        {
                 return my_below;
        }
/*        void setBelow(playfair_letter* the_below)
        {
                 my_below = the_below;
        }
*/
        playfair_letter* getRight() const
        {
                 return my_right;
        }
/*        void setRight(playfair_letter* the_right)
        {
                 my_right = the_right;
        }
*/
        playfair_letter* getLeft() const
        {
                 return my_left;
        }
/*        void setLeft(playfair_letter* the_left)
        {
                 my_left = the_left;
        }
*/
        bool isinset(playfair_set set, playfair_letter *s);
        //bool forall_row(<nicht spezifiziert> callroutine);
        void insert2set(playfair_set set, playfair_letter *s);
        void setNeighbour(playfair_neighbour pos, playfair_letter *s);
        void printdata(char *buffer);
		void getNeighboursString(char *s, int slen);
		void getRowString(char *s, int slen);
		void getColString(char *s, int slen);
		void getRoworcolString(char *s, int slen);
		void getUndefinedNeighboursString(char *s, int slen);
		void setSetSize(int size) { my_maxsetsize = size; }
		int getSetSize() { return my_maxsetsize; }
		void setWeight (int w) { my_weight = w; }
		void incWeight (int w=1) { my_weight += w; }
		int getWeight () { return my_weight; }
protected:
private:
        playfair_letter* my_left;
        playfair_letter* my_right;
        playfair_letter* my_above;
        playfair_letter* my_below;
        playfair_letter* my_rightorbelow[MAXDIM]; // array von Zeigern auf Symbol
        playfair_letter* my_leftorabove[MAXDIM];
        playfair_letter* my_row_sure[MAXDIM];
        playfair_letter* my_col_sure[MAXDIM];
        playfair_letter* my_roworbelow[MAXDIM];
        playfair_letter* my_roworabove[MAXDIM];
        playfair_letter* my_roworcol[2*MAXDIM];
        int my_cnt_rightorbelow; // array von Zeigern auf Symbol
        int my_cnt_leftorabove;
        int my_cnt_row_sure;
        int my_cnt_col_sure;
        int my_cnt_roworbelow;
        int my_cnt_roworabove;
        int my_cnt_roworcol;
		static int my_maxsetsize;
		int my_weight;
}; // class playfair_letter

class playfair_alphabet        : public alphabet
{
public:
        //playfair_alphabet();
        ~playfair_alphabet();
        playfair_alphabet(int size=5);
		void clear_letters();
        playfair_letter* addLetter(char let);
        playfair_letter* getLetter(char let);
        playfair_letter* getLetter(int letindex){
			assert (letindex >= 0);
			assert (letindex < MAXDIM*MAXDIM +1);
            return &my_pfletters[letindex];
		}
        playfair_letter *getLetters() //const
        {
            return my_pfletters;
        }
        playfair_letter *getNullElement() const
        {
            return my_nullElement;
        }
protected:
private:
		playfair_letter my_pfletters[MAXDIM*MAXDIM +1];
		playfair_letter *my_nullElement;
}; // class playfair_alphabet


class playfair_letterlist
{
public:
		playfair_letterlist(playfair_alphabet* the_alphabet, char *input, int len, int the_maxLen=(MAXDIM*MAXDIM));
		playfair_letterlist(playfair_alphabet* the_alphabet, bool isCopyAllValid=true, int the_maxLen=(MAXDIM*MAXDIM));
		~playfair_letterlist();
		playfair_letter* getLetter(int i);
		void getString (char *buf, int len=0);
		void addLetter (playfair_letter* let);
		int getLen() {return my_len;}
		int getMaxLen() {return my_maxLen;}
		void sortViaWeight ();
		void copy (playfair_letterlist* dst, playfair_letterlist* src);
		void setVisited (int i, bool flag=true) { my_visited[i] = flag; }
		bool getVisited (int i) { return my_visited[i]; }
		void reset_visited(bool flag=false); // reset all flags
		void print (char *s, bool withWeight=false);
		// use a length for *s at least 6 times of list length
protected:
private:
		int my_len, my_maxLen;
		playfair_letter** my_pfletters;
		playfair_alphabet* my_alphabet;
		bool *my_visited; // for matrix generation
}; // class playfair_letterlist


class playfair_digramm
{
public:
        playfair_digramm(playfair_alphabet* ab, int msize, char letter1, char letter2, char chiffre1, char chiffre2);
        playfair_digramm(playfair_alphabet* ab=NULL, int msize=MAXDIM);
        ~playfair_digramm();
        bool operator==(const playfair_digramm &other);

        playfair_letter* getLetter1() const
        {
                 return my_letter1;
        }
        playfair_letter* getLetter2() const
        {
                 return my_letter2;
        }
        playfair_letter* getChiffre1() const
        {
                 return my_chiffre1;
        }
        playfair_letter* getChiffre2() const
        {
                 return my_chiffre2;
        }
        int getCount() const
        {
                 return my_count;
        }
        void setCount(int the_count)
        {
                 my_count = the_count;
        }
        void incCount(int amount=1)
        {
                 my_count += amount;
        }
        playfair_alphabet* getAlphabet() const
        {
                 return my_alphabet;
        }
        void setAlphabet(playfair_alphabet* the_alphabet)
        {
                 my_alphabet = the_alphabet;
        }
        void setLetters(char c1, char c2);
        void setLetters(playfair_letter* c1, playfair_letter* c2);
        void setChiffres(char c1, char c2);
        void setChiffres(playfair_letter* c1, playfair_letter* c2);
        int getIndex();
        int getIndex(char chiffre1, char chiffre2);
        int getIndex(playfair_letter* c1, playfair_letter* c2);
		bool getVisited () { return my_visited; }
		void setVisited (bool flag) { my_visited = flag; }
protected:
private:
        playfair_letter* my_letter1;
        playfair_letter* my_letter2;
        playfair_letter* my_chiffre1;
        playfair_letter* my_chiffre2;
        int my_count; // Statistik
		playfair_alphabet* my_alphabet;
		int my_matrixsize;
		bool my_visited; //nur um doppelte Analysen zu vermeiden
}; // class playfair_digramm

class playfair_digrammlist
{
public:
		playfair_digrammlist(playfair_alphabet* the_alphabet, playfair_digramm* digramsbase, char *plain, char *chiffre, int charlen, int the_maxDigLen=0);
		playfair_digrammlist(playfair_alphabet* the_alphabet, int the_maxDigLen);
		~playfair_digrammlist();
		playfair_digramm* getDigramm(int i);
		void getPlainString (char *buf, int charlen=0);
		void getChiffreString (char *buf, int charlen=0);
		void addDigramm (playfair_digramm* dig);
		int getLen() {return my_len;}
		int getMaxLen() {return my_maxLen;}
protected:
private:
		int my_len, my_maxLen;
		playfair_digramm** my_digramms;
		playfair_alphabet* my_alphabet;
}; // class playfair_digrammlist


/////////////////////
// Klassen f�r Analyse nach Peer Wichmann

class playfair_data
{
public:
        char a1,a2,c1,c2;
        int is_in(char c);
};

class playfair_liste
{
public:
        int n;
        playfair_data *d;
        playfair_liste( void );
        init( int msize );
        playfair_liste(int msize, int l );
        ~playfair_liste( void );
        void read(char *pname, char*cname);
        void memread(char *pstr, char*cstr, int plen, int clen);
private:
		int my_matrixsize;

};

class playfair_charinfo {
public:
        char required, set, possible, freq, dirty;
        char p[MAXDIM][MAXDIM];
        playfair_charinfo( void );
        playfair_charinfo_init(int msize);
        ~playfair_charinfo();
private:
		int my_matrixsize;
};

class playfair_arrinfo {
public:
        int missing;
        int test_rule(playfair_data d);
        playfair_charinfo c[MAXDIM*MAXDIM];
        char possible[MAXDIM][MAXDIM];
        char m[MAXDIM][MAXDIM];
        char dirty;
        playfair_arrinfo( void );
        playfair_arrinfo_init( int msize );
        ~playfair_arrinfo( void );
        int force_col_or_row( char ch, int x1, int y2);
        int force_row_or_pos( char ch, int y1, int x2, int y2);
        int force_col_or_pos( char ch, int x1, int x2, int y2);
        int force_col( char ch, int x1 );
        int set( char ch, int x, int y );
        int disable(char ch, int x, int y);
private:
		int my_matrixsize;
};

class playfair_backtrace {
public:
        void read(char *pname, char *cname);
        void memread(char *pstr, char*cstr, int plen, int clen);
        void analyse( void );
        bool analyse( keymatrix *km, playfair_alphabet *pfalpha );
        int level;
        playfair_arrinfo a[MAXDIM*MAXDIM];
        playfair_liste l;
        playfair_backtrace(int msize);
        ~playfair_backtrace();
        test(char ch, int x1, int y1, int level);
private:
		int my_matrixsize;
};


/*
struct digram
{
	char di[3];   // aus szText_s bestimmtes Cleartext-Digramm
	char ciphdi[3];
	int  anz;     // wie haeufig kam es vor
};

#define WAAG    1
#define SENK    2
#define ECK     4
#define MATRIX  8

typedef struct doubs
{
	char d[2];
	int posa;
	int flag;
} doub;
typedef struct tripel
{
	char d[3];
	int posa;
	int flag;
} tripel;
typedef struct quads
{
	char d[4];
	int posa,posb;
	int flag;
} quads;
typedef struct anadigramme
{
	int size;
	doub *dou;
	int d;
	tripel *tri;
	int t;
	quads *qua;
	int q;
	char matrix[36];
	char *data;
} anadigramme;

int compdigram(struct digram *,struct digram *);
*/
class Playfair
{
public:
	void ApplyPlayfairToInput( int ); //used in crypt.cpp
	void ApplyPlayfairPreformat( int,char *,char *); //used in crypt.cpp
/*private:
	int genliste(anadigramme *);
	int genliste2(anadigramme *);
*/
public:
	void CreateMatrixFromPass(); //used in DialogPlayfair.cpp
	bool DoCipher( int Dec, int len, char *stipulation=NULL, int stiplen=0); //used in DialogPlayfair.cpp
//	BOOL myisalpha( char );  //used in DialogPlayfair.cpp
	BOOL myisalpha2( char );  //used in DialogPlayfair.cpp
private:
//	void movechar(int,char *);
	void PlayfairCipher (int , int , int ,int , int , char *,int );
	void PrintMatrix(char *);
public:
	void UpdateDigrams(int);  //used in DialogPlayfair.cpp
//	void AnalyseDigramme(int *,struct digram *);  //used in DialogPlayfair.cpp
/*private:
	int findcol(char,char [6][6]);
	int findrow(char,char [6][6]);
	void switchrows(int,int,char [6][6]);
	void switchcols(int,int,char [6][6]);
*/
  public:
	void SetSize(int); //used in DialogPlayfair.cpp
/*private:
	void ana_addtri(tripel *,int,char [6][6],bool flag=0);
	void ana_addqua(quads *,int,char [6][6],bool flag=0);
	void ana_sortrowtri(tripel *,int,char [6][6]);
	void addchar(char *,char);
	void addmat(char [6][6],int,char);
	int matlen(char [6][6],int);
*/
public:
	void SetPass(char * );  //used in DialogPlayfair.cpp

public:
 	void PassUse(int);  //used in DialogPlayfair.cpp
private:
 	int str_in(char *,int,char *,int);
public:
 	char *CreatePassfromMatrix();  //used in DialogPlayfair.cpp
private:
 	int maxkeyval(char *,int);
 	int keyval(char);
 	char valkey(int);
//	int navmatrix(int,int,int);
public:
	Playfair(char *,int,const char *,const char *,int,int,int);  //used in DialogPlayfair.cpp
private:
	Playfair(void);
public:
	~Playfair(void); //used in DialogPlayfair.cpp
private:
	int IsElement( char *, char  );
public:
	void GetDiGrams(void);  //used in DialogPlayfair.cpp


private:
	//char matrix[MAXDIM][MAXDIM];  //used in DialogPlayfair.cpp
private:
	char passphrase[50];  // used passphrase ........
public:
	int ReFormat,ConvertCase;  //all used in DialogPlayfair.cpp
	int getSize () { return (mysize); }
private:
	int mysize;
	
private:
	FILE *infp,*outfp;  // file to read input text from .......................
public:
	int inbuflen,outbuflen;  //inbuflen used in DialogPlayfair.cpp
	char infile[300],outfile[300],*inbuf,*outbuf;  //inbuf, outbuf used in DialogPlayfair.cpp
	struct digram *digrams;  //used in DialogPlayfair.cpp
	int numdigrams;  //used in DialogPlayfair.cpp
private:
	unsigned int UseOfDoublesInPass;
/*--------------------------------------------------------------------*/
	playfair_alphabet *myAlphabet;
	playfair_letterlist *myLetterlist;
	//alphabet myAlphabet;
	keymatrix *my_matrix;

public:
	void setElMatrix (char c, int x, int y)
	{
		assert (c<='Z'); assert (c>=NULLELEMENT);
		my_matrix->setElement (myAlphabet->getLetter(c), x, y);
	}
	void setElMatrix (playfair_letter* c, int x, int y)
	{
		my_matrix->setElement (c, x, y);
	}
	char getCharOfMatrix (int x, int y)
	{
		letter *let = my_matrix->getElement (x, y);
		return (my_matrix->getElement (x, y))->getValue();
	}
	playfair_letter* getLetterOfMatrix (int x, int y)
	{
		return ((playfair_letter*) my_matrix->getElement (x, y));
	}
	playfair_alphabet *getAlphabet ()
	{
		return myAlphabet;
	}
	playfair_letterlist *getLetterlist ()
	{
		return myLetterlist;
	}

	playfair_digramm* getDigrams() const
	{
		return my_digrams;
	}

	void DeleteLetterGraph();
	void AnalyseDigramme(playfair_digrammlist* dl);

	bool CreateMatrixStandalone (char *stipulation=NULL, int len=0); // Analyse nach Peer Wichmann
	bool CreateMatrixfromLettergraph(char *stipulation=NULL, int len=0); // Analyse nach Thomas Gauweiler

private:
	enum  AnaLg_Look {AnaLg_matrix, AnaLg_row, AnaLg_col};
	bool AnaLg_LookPlaceFirst(AnaLg_Look thetype, int& x, int& y, int no=0);
	bool AnaLg_LookPlaceNext(AnaLg_Look thetype, int& x, int& y, int no=0);
	bool AnaLg_InsertLetter (playfair_letter *theLetter, int theIndex, int x, int y);
	bool AnaLg_RemoveLetter (playfair_letter *theLetter, int theIndex, int x, int y);
	bool AnaLg_RekLetter (int theIndex, char *stipulation, int len);
	FILE *debugfile;

public:
/*void setDigrams(const playfair_digramm* &the_digrams)
{
	my_digrams = the_digrams;
}*/

private:
	playfair_digramm* my_digrams;
	int my_cntdigrams;
	void insertChiffre2Digrams(char c1, char c2);
	void insertChiffre2Digrams(playfair_letter* c1, playfair_letter* c2);
}; //class Playfair

class playfair_error
{
public:
	playfair_error(int i, playfair_letter* thisletter=NULL) : my_code(i), my_letter(thisletter) {}
	int getCode () { return my_code; }
	playfair_letter* getLetter () { return my_letter; }
private:
	int my_code;
	playfair_letter* my_letter;
};


#endif
