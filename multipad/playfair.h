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

/* used for uiUseOfDoublesInPass_s; default: doubles are eliminated ..*/
#define ELIMINATE_DOUBLES                   0  /* default */
/* Effect: password given:  playfair  ->  pass used:  PLAYFIR   */

#define IF_DOUBLES_TAKE_NEXT_UNUSED_LETTER  1  /* replace double letter */
/* Effect: password given:  nummer    ->  pass used:  NUMOER    */
/*                          playfair  ->  pass used:  PLAYFBIR  */
/*                          pbayfair  ->  pass used:  PBAYFCIR  */

#define MAXDIM        6          /* maximum dimension of the matrix ..*/

struct digram
{
	char di[3];   /* aus szText_s bestimmtes Cleartext-Digramm */
	char ciphdi[3];
	int  anz;     /* wie haeufig kam es vor */
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
	int genliste(anadigramme *);
	int genliste2(anadigramme *);
	void CreateMatrixFromPass();
	void ApplyPlayfairToInput( int );
	void ApplyPlayfairPreformat( int,char *,char *);
	void DoCipher( int, int);
	BOOL myisalpha( char );
	void movechar(int,char *);
	void PlayfairCipher (int , int , int ,int , int , char *,int );
	void PrintMatrix(char *);
	void UpdateDigrams(int);
	void AnalyseDigramme(int *,struct digram *);
	int findcol(char,char [6][6]);
	int findrow(char,char [6][6]);
	void switchrows(int,int,char [6][6]);
	void switchcols(int,int,char [6][6]);
	void SetSize(int);
	void ana_addtri(tripel *,int,char [6][6],bool flag=0);
	void ana_addqua(quads *,int,char [6][6],bool flag=0);
	void ana_sortrowtri(tripel *,int,char [6][6]);
	void addchar(char *,char);
	void addmat(char [6][6],int,char);
	int matlen(char [6][6],int);
	void SetPass(char * );

 	void PassUse(int);
 	int str_in(char *,int,char *,int);
 	char *CreatePassfromMatrix();
 	int maxkeyval(char *,int);
 	int keyval(char);
 	char valkey(int);
	int navmatrix(int,int,int);

	Playfair(char *,int,const char *,const char *,int,int,int);
	Playfair(void);
	~Playfair(void);
	int IsElement( char *, char  );
	void GetDiGrams(void);
	
	char matrix[MAXDIM][MAXDIM];
	char passphrase[50];  /* used passphrase ........*/
	int size,ReFormat,ConvertCase;
	
	FILE *infp,*outfp;  /* file to read input text from .......................*/
	int inbuflen,outbuflen;
	char infile[300],outfile[300],*inbuf,*outbuf;
	struct digram *digrams;
	int numdigrams;
	unsigned int UseOfDoublesInPass;
};

#endif
