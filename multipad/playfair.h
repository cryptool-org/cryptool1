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
// playfair.h : Header für Playfair Algorithmus
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
        above,
        below,
        left,
        right
};
enum playfair_set
{
        row_sure,
        col_sure,
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
        playfair_letter* getAbove() const
        {
                 return my_above;
        }
        void setAbove(playfair_letter* the_above)
        {
                 my_above = the_above;
        }
        playfair_letter* getBelow() const
        {
                 return my_below;
        }
        void setBelow(playfair_letter* the_below)
        {
                 my_below = the_below;
        }
        playfair_letter* getRight() const
        {
                 return my_right;
        }
        void setRight(playfair_letter* the_right)
        {
                 my_right = the_right;
        }
        playfair_letter* getLeft() const
        {
                 return my_left;
        }
        void setLeft(playfair_letter* the_left)
        {
                 my_left = the_left;
        }
        bool isinset(playfair_set set, int setlen, playfair_letter *s);
        //bool forall_row(<nicht spezifiziert> callroutine);
        void insert2set(playfair_set set, int setlen, playfair_letter *s);
        void setNeighbour(playfair_neighbour pos, playfair_letter *s);
        void printdata(char *buffer);
		void getNeighboursString(char *s, int slen);
		void getRowString(char *s, int slen);
		void getColString(char *s, int slen);
protected:
private:
        playfair_letter* my_left;
        playfair_letter* my_right;
        playfair_letter* my_above;
        playfair_letter* my_below;
        playfair_letter* my_row_sure[MAXDIM]; // array von Zeigern auf Symbol
        playfair_letter* my_col_sure[MAXDIM];
        playfair_letter* my_roworbelow[MAXDIM];
        playfair_letter* my_roworabove[MAXDIM];
        playfair_letter* my_roworcol[MAXDIM];
}; // class playfair_letter

class playfair_alphabet        : public alphabet
{
public:
        //playfair_alphabet();
        ~playfair_alphabet();
        playfair_alphabet(int size=5);
        playfair_letter* addLetter(char let);
        playfair_letter* getLetter(char let);
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
		playfair_letterlist(playfair_alphabet* the_alphabet, char *input, int len, int the_maxLen=0);
		playfair_letterlist(playfair_alphabet* the_alphabet, int the_maxLen);
		~playfair_letterlist();
		playfair_letter* getLetter(int i);
		void getString (char *buf, int len=0);
		void addLetter (playfair_letter* let);
		int getLen() {return my_len;}
		int getMaxLen() {return my_maxLen;}
protected:
private:
		int my_len, my_maxLen;
		playfair_letter** my_pfletters;
		playfair_alphabet* my_alphabet;
}; // class playfair_letterlist


class playfair_digramm
{
public:
        playfair_digramm(playfair_alphabet* ab, char letter1, char letter2, char chiffre1, char chiffre2);
        playfair_digramm(playfair_alphabet* ab=NULL);
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
protected:
private:
        playfair_letter* my_letter1;
        playfair_letter* my_letter2;
        playfair_letter* my_chiffre1;
        playfair_letter* my_chiffre2;
        int my_count; // Statistik
		playfair_alphabet* my_alphabet;
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


/* */
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
class Playfair
{
public:
	void ApplyPlayfairToInput( int ); //used in crypt.cpp
	void ApplyPlayfairPreformat( int,char *,char *); //used in crypt.cpp
private:
	int genliste(anadigramme *);
	int genliste2(anadigramme *);
public:
	void CreateMatrixFromPass(); //used in DialogPlayfair.cpp
	void DoCipher( int, int); //used in DialogPlayfair.cpp
	BOOL myisalpha( char );  //used in DialogPlayfair.cpp
private:
	void movechar(int,char *);
	void PlayfairCipher (int , int , int ,int , int , char *,int );
	void PrintMatrix(char *);
public:
	void UpdateDigrams(int);  //used in DialogPlayfair.cpp
	void AnalyseDigramme(int *,struct digram *);  //used in DialogPlayfair.cpp
private:
	int findcol(char,char [6][6]);
	int findrow(char,char [6][6]);
	void switchrows(int,int,char [6][6]);
	void switchcols(int,int,char [6][6]);
public:
	void SetSize(int); //used in DialogPlayfair.cpp
private:
	void ana_addtri(tripel *,int,char [6][6],bool flag=0);
	void ana_addqua(quads *,int,char [6][6],bool flag=0);
	void ana_sortrowtri(tripel *,int,char [6][6]);
	void addchar(char *,char);
	void addmat(char [6][6],int,char);
	int matlen(char [6][6],int);
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
	int navmatrix(int,int,int);

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
	int size,ReFormat,ConvertCase;  //all used in DialogPlayfair.cpp
	
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
	//alphabet myAlphabet;
	keymatrix *my_matrix;

public:
	void setElMatrix (char c, int x, int y)
	{
		my_matrix->setElement (myAlphabet->getLetter(c), x, y);
	}
	void setElMatrix (playfair_letter* c, int x, int y)
	{
		my_matrix->setElement (c, x, y);
	}
	char getCharOfMatrix (int x, int y)
	{
		return (my_matrix->getElement (x, y))->getValue();
	}
/*	playfair_letter* getLetterOfMatrix (int x, int y)
	{
		return (my_matrix->getElement (x, y));
	}
*/
	playfair_alphabet *getAlphabet ()
	{
		return myAlphabet;
	}

playfair_digramm* getDigrams() const
{
	return my_digrams;
}

/*void setDigrams(const playfair_digramm* &the_digrams)
{
	my_digrams = the_digrams;
}*/

private:
	playfair_digramm* my_digrams;
	int my_cntdigrams;
	void insertChiffre2Digrams(char c1, char c2);
	void insertChiffre2Digrams(playfair_letter* c1, playfair_letter* c2);

#endif

}; //class Playfair