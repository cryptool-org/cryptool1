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

#include "assert.h"
#include "playfair.h"
#include "multipad.h"


/*--------------------------------------------------------------------*/
/* class playfair_letter                                              */
/*--------------------------------------------------------------------*/
playfair_letter::playfair_letter(char c)        : letter()/*,
                        my_row_sure(NULL),
                        my_col_sure(NULL),
                        my_roworbelow(NULL),
                        my_roworabove(NULL),
                        my_roworcol(NULL)*/
{
/*        my_row_sure = new ;
        my_col_sure = new ;
        my_roworbelow = new ;
        my_roworabove = new ;
        my_roworcol = new ;
*/
    my_above = NULL;
    my_below = NULL;
    my_right = NULL;
    my_left = NULL;
	for (int i=0; i<MAXDIM; i++) {
	    my_row_sure[i] = NULL;
		my_col_sure[i] = NULL;
		my_roworbelow[i] = NULL;
		my_roworabove[i] = NULL;
		my_roworcol[i] = NULL;
	}
	my_value = c;
}

playfair_letter::~playfair_letter()
{
/*        delete (my_row_sure);
        delete (my_col_sure);
        delete (my_roworbelow);
        delete (my_roworabove);
        delete (my_roworcol);
*/
}

inline bool playfair_letter::operator==(const playfair_letter &other)
{
        return (this->getValue()==other.getValue());
}
inline bool playfair_letter::operator!=(const playfair_letter &other)
{
        return (this->getValue()!=other.getValue());
}

bool playfair_letter::isinset(playfair_set set, int setlen, playfair_letter* s)
{
        assert (set); assert (s);
        int i=0;
		switch (set) {
		  case row_sure:
			while (i<setlen){
                if (my_row_sure[i]==s) return (true);
			} break;
		  case col_sure:
			while (i<setlen){
                if (my_col_sure[i]==s) return (true);
			} break;
		  case roworbelow:
			while (i<setlen){
                if (my_roworbelow[i]==s) return (true);
			} break;
		  case roworabove:
			while (i<setlen){
                if (my_roworabove[i]==s) return (true);
			} break;
		  case roworcol:
			while (i<setlen){
                if (my_roworcol[i]==s) return (true);
			} break;
        }
        return (false);
}

/*bool playfair_letter::forall_row(<nicht spezifiziert> callroutine)
{

}
*/

void playfair_letter::insert2set(playfair_set set, int setlen, playfair_letter* s)
{
        assert (s);
        int i=0;
        switch (set) {
        case row_sure:
                while ((my_row_sure[i]) && (i<setlen-1)) i++;
                if (i<setlen) my_row_sure[i] = s; else throw ;
                s->insert2set (row_sure, setlen, this);
                break;
        case col_sure:
                s->insert2set (col_sure, setlen, this);
                break;
        case roworabove:
                break;
        case roworbelow:
                break;
        case roworcol:
                s->insert2set (roworcol, setlen, this);
                break;
        other :
                assert(0);
        }
}

void playfair_letter::setNeighbour(playfair_neighbour pos, playfair_letter* s)
{
        assert (s);
        switch (pos)
        {
        case above:
                setAbove(s);
                s->setNeighbour (below, this);
                break;
        case below:
                break;
        case left:
                break;
        case right:
                break;
        other :
                assert(0);
        }
}

void playfair_letter::getNeighboursString(char *s, int slen)
{
	assert (s);
	s[0] = (my_left) ?my_left ->getValue():'*';
	s[1] = (my_right)?my_right->getValue():'*';
	s[2] = (my_above)?my_above->getValue():'*';
	s[3] = (my_below)?my_below->getValue():'*';
	s[4] = '\0';
}

void playfair_letter::getRowString(char *s, int slen)
{
	int i,j;
	char c[2];
	assert (s);
	memset(s,0,slen);

	i=0;
	j=0;
	while ((j<MAXDIM) && (my_row_sure[j]!=NULL)) {
		s[i++] = my_row_sure[j++]->getValue();
		s[i++] = '!'; s[i++] = ',';
	}
	c[1]='\0';
	while ((j<MAXDIM) && (my_roworbelow[j]!=NULL)) {
		c[0] = my_roworbelow[j++]->getValue();
		if (strstr(s,c)) {
			s[i++] = c[0];
			s[i++] = ',';
		}
	}
	while ((j<MAXDIM) && (my_roworabove[j]!=NULL)) {
		c[0] = my_roworbelow[j++]->getValue();
		if (strstr(s,c)) {
			s[i++] = c[0];
			s[i++] = ',';
		}
	}
	s[i-1]='\0';
}

void playfair_letter::getColString(char *s, int slen)
{
	int i,j;
	char c[2];
	assert (s);
	memset(s,0,slen);

	i=0;
	j=0;
	while ((j<MAXDIM) && (my_col_sure[j]!=NULL)) {
		s[i++] = my_row_sure[j++]->getValue();
		s[i++] = '!'; s[i++] = ',';
	}
	c[1]='\0';
	while ((j<MAXDIM) && (my_roworcol[j]!=NULL)) {
		c[0] = my_roworbelow[j++]->getValue();
		if (strstr(s,c)) {
			s[i++] = c[0];
			s[i++] = ',';
		}
	}
	s[i-1]='\0';
}

void playfair_letter::printdata(char *buffer)
{
	assert (0);
}

/*--------------------------------------------------------------------*/
/* class playfair_alphabet                                            */
/*--------------------------------------------------------------------*/
/*playfair_alphabet::playfair_alphabet()        : alphabet()
{
}
*/

playfair_alphabet::~playfair_alphabet()
{
	assert (my_validletters);
	assert (my_pfletters);
	delete[] (my_validletters); my_validletters = NULL;
	delete my_letters;
//jetzt als Feld	delete[] (my_pfletters);    my_pfletters = NULL;
}

playfair_alphabet::playfair_alphabet(int size)
{
	assert ((size==5)||(size==6));
    my_count = (size==5) ? 5*5 : 6*6;
	my_validletters = new short[(my_max_count+1)];
	my_max_count = MAXDIM * MAXDIM;
	my_letters = new letter[1];  //dummy
// jetzt als Feld	my_pfletters = new playfair_letter[my_max_count+1];
	my_pfletters[0] = playfair_letter('*');
	my_validletters[0] = false;
	my_nullElement = &my_pfletters[0];
	int i; char c;
	for (i=1, c='A'; c<='Z'; i++, c++) {
		my_pfletters[i] = playfair_letter(c);
		my_validletters[i] = true;
	}
	my_validletters['J'-'A'+1] = (size==6);
	for (c='0'; c<='9'; i++, c++) {
		my_pfletters[i] = playfair_letter(c);
		my_validletters[i] = (size==6);
	}
	return;
}

playfair_letter* playfair_alphabet::addLetter(char let)
{
	assert (0);
	return NULL;
}

playfair_letter* playfair_alphabet::getLetter(char let)
{
	if (let=='\0') return &my_pfletters[0];
	for (int i=0; i<=my_max_count; i++)
		if ((my_validletters[i]) && ((my_pfletters[i].getValue()==let)||(my_pfletters[i].getValue()==toupper(let))))
			return &my_pfletters[i];
	switch (let) {
	case 'Ä': case 'ä': case 'Á': case 'á': case 'À': case 'à': case 'Â': case 'â': case '@':
		let = 'A'; break;
	case 'ç':
		let = 'C'; break;
	case 'É': case 'é': case 'È': case 'è':
		let = 'E'; break;
	case 'î': case 'Î': case 'ï': case 'í':  case 'Í': case 'ì': case 'Ì':
		let = 'I'; break;
	case 'ñ': //case 'ñ':
		let = 'N'; break;
	case 'J': case 'j':
		let = (my_count==5*5)?'J':'I'; break;
	case 'Ö': case 'ö': case 'Ô': case 'ô': case 'Ó': case 'ó': case 'Ò': case 'ò':
		let = 'O'; break;
	case 'Ü': case 'ü': case 'Û': case 'û': case 'µ':
		let = 'U'; break;
	}
	for (i=0; i<=my_max_count; i++)
		if ((my_validletters[i]) && (my_letters[i].getValue()==let))
			return &my_pfletters[i];
	return &my_pfletters[0];
}

/*--------------------------------------------------------------------*/
/* class playfair_letterlist                                             */
/*--------------------------------------------------------------------*/
playfair_letterlist::playfair_letterlist(playfair_alphabet* the_alphabet, char *input, int len, int the_maxLen)
{
	my_alphabet = the_alphabet;
	my_maxLen = max (the_maxLen, len);
	my_pfletters = (playfair_letter**) malloc(my_maxLen*sizeof(playfair_letter*));
	for (my_len=0; my_len < len; my_len++)  // evtl. Probleme, wenn doppelte Zeichen erlaubt
		my_pfletters[my_len] = my_alphabet->getLetter (input[my_len]);
	for (int i = my_len; my_len < my_maxLen; i++)
		my_pfletters[i] = my_alphabet->getNullElement();
}
playfair_letterlist::playfair_letterlist(playfair_alphabet* the_alphabet, int the_maxLen)
{
	my_alphabet = the_alphabet;
	my_maxLen = the_maxLen;
	my_pfletters = (playfair_letter**) malloc(my_maxLen*sizeof(playfair_letter*));
	my_len=0;
	for (int i = 0; i < my_maxLen; i++)
		my_pfletters[i] = my_alphabet->getNullElement();
}
playfair_letterlist::~playfair_letterlist()
{
	free (my_pfletters);
}

playfair_letter* playfair_letterlist::getLetter(int i)
{
	assert (i < my_maxLen);
	assert (i < my_len);
	return my_pfletters[i];
}

void playfair_letterlist::getString (char *buf, int len)
{
	len = (len<=0) ? my_len : min (len-1, my_len);
	for (int i = 0; i < len; i++)
		buf[i] = my_pfletters[i]->getValue();
	buf[i] = '\0';
}

void playfair_letterlist::addLetter (playfair_letter* let)
{
	assert (my_len < my_maxLen);
	assert ((let != NULL) || (let == my_alphabet->getNullElement()));
	my_pfletters[my_len++] = let;
}

/*--------------------------------------------------------------------*/
/* class playfair_digramm                                             */
/*--------------------------------------------------------------------*/
playfair_digramm::playfair_digramm(playfair_alphabet* ab, char letter1, char letter2, char chiffre1, char chiffre2)
{
	setLetters(letter1, letter2);
	setChiffres(chiffre1, chiffre2);
	my_count = 1;
	my_alphabet = ab;
}

playfair_digramm::playfair_digramm(playfair_alphabet* ab)
{
	if (ab)
		playfair_digramm(ab, '\0','\0','\0','\0');
}

playfair_digramm::~playfair_digramm()
{
}


inline bool playfair_digramm::operator==(const playfair_digramm &other)
{
	playfair_letter* nullEl = my_alphabet->getLetter('\0') ;
    return ( (my_alphabet == other.my_alphabet) &&
			 (((*my_letter1 == *nullEl) && (*my_chiffre1 == *nullEl)) || 
			  ((*my_letter1 != *nullEl) && (*nullEl != *other.my_letter1) && 
				(*my_letter1 == *other.my_letter1) && (*my_letter2 == *other.my_letter2)) ||
			  ((*my_chiffre1 != *nullEl) && (*nullEl != *other.my_chiffre1) &&
				(*my_chiffre1 == *other.my_chiffre1) && (*my_chiffre2 == *other.my_chiffre2)))
		   );
    /* auf jeden Fall beide das gleiche Alphabet,
	   falls beide Pärchen (Klarbuchstaben, bzw. Chiffrebuchstaben) leer (Nullte Element des Alphabets) 
	      dann ok,
	   ansonsten falls eines der Pärchen gesetzt, 
	      dann muß das Pärchen mit dem des anderen Digramms übereinstimmen. */
}

inline void playfair_digramm::setLetters(char c1,  char c2)
{
	my_letter1 = my_alphabet->getLetter(c1);
	my_letter2 = my_alphabet->getLetter(c2);
}

inline void playfair_digramm::setLetters(playfair_letter* c1, playfair_letter* c2)
{
	my_letter1 = c1;
	my_letter2 = c2;
}

inline void playfair_digramm::setChiffres(char c1, char c2)
{
	my_chiffre1 = my_alphabet->getLetter(c1);
	my_chiffre2 = my_alphabet->getLetter(c2);
}

inline void playfair_digramm::setChiffres(playfair_letter* c1, playfair_letter* c2)
{
	my_chiffre1 = c1;
	my_chiffre2 = c2;
}

int playfair_digramm::getIndex()
{
	return ((my_chiffre1->getValue()-'A')*MAXDIM*MAXDIM + my_chiffre2->getValue()-'A');
}

int playfair_digramm::getIndex(char chiffre1, char chiffre2)
{
	return ((chiffre1-'A')*MAXDIM*MAXDIM + chiffre2-'A');
}

int playfair_digramm::getIndex(playfair_letter* c1, playfair_letter* c2)
{
//	int i=((c1->getValue()-'A')*MAXDIM*MAXDIM + c2->getValue()-'A');
	return ((c1->getValue()-'A')*MAXDIM*MAXDIM + c2->getValue()-'A');
}

/*--------------------------------------------------------------------*/
/* class playfair_letterlist                                             */
/*--------------------------------------------------------------------*/
playfair_digrammlist::playfair_digrammlist(playfair_alphabet* the_alphabet, playfair_digramm* digramsbase, char *plain, char *chiffre, int charlen, int the_maxDigLen)
{
	int j;
	playfair_digramm* dig;
	my_alphabet = the_alphabet;
	my_maxLen = max (the_maxDigLen, 2*charlen);
	my_digramms = (playfair_digramm**) malloc(my_maxLen*sizeof(playfair_digramm*));
	for (j=0, my_len=0; my_len < charlen/2; my_len++, j+=2) {  // evtl. Probleme, wenn doppelte Zeichen erlaubt
		dig = &digramsbase[dig->getIndex(chiffre[j], chiffre[j+1])];
		dig->setLetters (plain[j], plain[j+1]);
		my_digramms[my_len] =  dig;
	}
	for (int i = my_len; i < my_maxLen; i++)
		my_digramms[i] = NULL;
}
playfair_digrammlist::playfair_digrammlist(playfair_alphabet* the_alphabet, int the_maxDigLen)
{
	my_alphabet = the_alphabet;
	my_maxLen = the_maxDigLen;
	my_digramms = (playfair_digramm**) malloc(my_maxLen*sizeof(playfair_digramm*));
	my_len=0;
	for (int i = 0; i < my_maxLen; i++)
		my_digramms[i] = NULL;
}
playfair_digrammlist::~playfair_digrammlist()
{
	free (my_digramms);
}

playfair_digramm* playfair_digrammlist::getDigramm(int i)
{
	assert (i < my_maxLen);
	assert (i < my_len);
	return my_digramms[i];
}

void playfair_digrammlist::getChiffreString (char *buf, int charlen)
{
	int i, j;
	int len = (charlen<=0) ? my_len : min (charlen-1, my_len);
	for (i = 0, j = 0; i < len; i++, j+=2){
		buf[j]   = my_digramms[i]->getChiffre1()->getValue();
		buf[j+1] = my_digramms[i]->getChiffre2()->getValue();
	}
	buf[j] = '\0';
}

void playfair_digrammlist::getPlainString (char *buf, int charlen)
{
	int i, j;
	int len = (charlen<=0) ? my_len : min (charlen-1, my_len);
	for (i = 0, j = 0; i < len; i++, j+=2){
		buf[j]   = my_digramms[i]->getLetter1()->getValue();
		buf[j+1] = my_digramms[i]->getLetter2()->getValue();
	}
	buf[j] = '\0';
}

void playfair_digrammlist::addDigramm (playfair_digramm* dig)
{
	assert (my_len < my_maxLen);
	assert (dig != NULL);
	my_digramms[my_len++] = dig;
} // class playfair_digrammlist


/*--------------------------------------------------------------------*/
/* class 'playfair_main'                                                */
/*--------------------------------------------------------------------*/
void Playfair::insertChiffre2Digrams (char c1, char c2)
{
	playfair_digramm* d=NULL;
	d = &my_digrams[d->getIndex(c1,c2)];
	if (d->getCount()==0)
		d->setChiffres(c1,c2);
	d->setCount(d->getCount()+1);
}

void Playfair::insertChiffre2Digrams (playfair_letter* c1, playfair_letter* c2)
{
	insertChiffre2Digrams (c1->getValue(), c2->getValue());
}


/*--------------------------------------------------------------------*/


const char *alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const char *alphs = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

Playfair::Playfair(void)
{
	my_matrix = NULL;
	my_matrix = new keymatrix(6);
	UseOfDoublesInPass=0; /* default: only use the first appearance of distinguished letters in passphrase */
	strcpy(passphrase,"PLAYFIR");
	ReFormat=1;
	ConvertCase=1;
	SetSize(1);
	my_cntdigrams=0;
	my_digrams = new playfair_digramm [MAXDIGRAMMS];//(&myAlphabet);
	memset(my_digrams,0,MAXDIGRAMMS * sizeof(playfair_digramm));

}

BOOL Playfair::myisalpha( char ch )
// prüft auf korrekte Zeichen
{
	if (size == 6)
	{
		if ((ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||(ch>='a'&&ch<='z'))
			return TRUE;
		return FALSE;
	}
	if (((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z'))&&(ch!='j')&&(ch!='J'))
		return TRUE;
	return FALSE;	
}

int Playfair::IsElement( char *sz, char ch )
{
	int i;
	int iLenSZ;
	
	iLenSZ = strlen(sz);
	
	
	for (i=0; i<iLenSZ; i++)
	{
		
		if ( sz[i] == ch )
			return 1;
	}
	
	return 0;   /* ch is not identical with an element in sz ...........*/
	
}    /* end of IsElement() .........................................*/

void Playfair::PassUse(int use)
{
	UseOfDoublesInPass=use;
	CreateMatrixFromPass();
}

void Playfair::SetSize(int sechs)
// 5x5 oder 6x6 Matrix verwenden
{
//	if (!my_matrix) delete my_matrix;
//	my_matrix = new keymatrix((sechs)?6:5);

	if(sechs)
	{
		size=6;
		strncpy(pc_str,alph,36);
		pc_str[36]=0;
	}
	else
	{
		size=5;
		strncpy(pc_str,alphs,25);
		pc_str[25]=0;
	}
	AppConv.SetAlphabet(pc_str,ConvertCase);
	theApp.TextOptions.m_alphabet=pc_str;
	CreateMatrixFromPass();
}

char *Playfair::CreatePassfromMatrix()
{
	int i,j;
	char p[37];

	if (size==6)
	{
		for (j=0;j<36;j++)
			p[j] = getCharOfMatrix (j/6, j%6);
	}
	else
	{
		for (i=0,j=0;i<25;i++)
			p[j++] = getCharOfMatrix (i/5,i%5);
	}
	p[j--]=0;
	while (maxkeyval(p,j)+1==keyval(p[j])&&j>=0)
		p[j--]=0;
	
	strcpy(passphrase,p);
	return passphrase;
}

int Playfair::keyval(char a)
{
	if(size==6)
	{
		if (a >= 'A' && a <= 'Z')
			return a-'A';
		if (a >= '0' && a <= '9')
			return a-'0'+26;
	}
	else
	{
		if(a >= 'A' && a <= 'I')
			return a-'A';
		if(a >= 'K' && a <= 'Z')
			return a-'B';
	}
	return -1;
} 

char Playfair::valkey(int a)
{
	if(size==6)
	{
		if (a >= 0 && a <= 25)
			return a+'A';
		if (a >= 26 && a <= 36)
			return a+'0'-26;
	}
	else
	{
		if (a >= 0 && a <= 8)
			return a+'A';
		if (a >= 9 && a <= 24)
			return a+1+'A';
	}
	return 0;
}

int Playfair::maxkeyval(char *a,int b)
{
	int i;
	char mark[37];
	
	for (i=0;i<37;i++)
		mark[i]=0;
	for (i=0;i<b;i++)
		mark[keyval(a[i])]=1;
	i=0;
	while (mark[i])
		i++;
	return i-1;
}

Playfair::Playfair(char *p,int sechs,const char *in,const char *out,int r,int c,int use)
{
	UseOfDoublesInPass=use;
	ReFormat=r;
	ConvertCase=c;
	strcpy(infile,in);
	strcpy(outfile,out);
	
	myAlphabet = new playfair_alphabet((sechs)?6:5);
	my_matrix = new keymatrix(6, myAlphabet->getNullElement());
	size=6;
	SetSize(sechs);
	SetPass(p);
	infp = fopen(infile,"rb");
	if(infp)
	{
		fseek(infp, 0, SEEK_END);
		inbuflen=ftell(infp);
		fseek(infp, 0, SEEK_SET);
	}
	else
		inbuflen=0;
	inbuf = (char *) malloc(inbuflen+1);
	outbuf = (char *) malloc(inbuflen+1);
	outbuf[0]=0;
	if(infp)
	{
		fread(inbuf, 1, inbuflen, infp);
		fclose(infp);
	}
	my_cntdigrams=0;
	my_digrams = new playfair_digramm [MAXDIGRAMMS];//(&myAlphabet);
	memset(my_digrams,0,MAXDIGRAMMS * sizeof(playfair_digramm));
	assert (my_digrams);
	for (int i=0; i<MAXDIGRAMMS; i++){
		my_digrams[i].setAlphabet(myAlphabet);
//		my_digrams[i].setCount(0); // macht memset ja schon
	}
	GetDiGrams();
}

void Playfair::GetDiGrams()
{
	int dgt[36*36],i,j;
	playfair_digramm* dig = &my_digrams[0];
	
/*	for (i=0;i<36*36;i++)
		dgt[i]=0;*/
	i=0;
	while (i<inbuflen-1) // zähle, wie oft jedes Digramm vorkommt
	{
//		char a,b;
		playfair_letter *a, *b;
//		a=inbuf[i];
		a=myAlphabet->getLetter(inbuf[i++]);
//		while(!myisalpha(a)&&i<inbuflen)
//			a=inbuf[++i];
		b=myAlphabet->getLetter(inbuf[i++]);
//		b=inbuf[++i];
//		while(!myisalpha(b)&&i<inbuflen)
//			b=inbuf[++i];
/*		if (i<inbuflen)
		{
			i++;
			a=keyval(toupper(a));
			b=keyval(toupper(b));
			dgt[b*36+a]++;
		}
		else
			break;
*/
		dig = &my_digrams[dig->getIndex(a,b)]; //dig->getIndex() ist Klassenfunktion, dh. es ist egal auf welches Digramm der Zeiger verweist
		dig->setChiffres(a,b);
		dig->setCount(dig->getCount()+1);
	}
	numdigrams=my_cntdigrams=0;
	for (i=0;i<MAXDIGRAMMS;i++) // zähle Anzahl der unterschiedlichen Digramme
	{
		if ( my_digrams[i].getCount() != 0 )
			numdigrams++;
	}
	my_cntdigrams = numdigrams;
/*
	digrams=(struct digram *)malloc((numdigrams)*sizeof(struct digram));
	i=j=0;
	while (i<36*36) // übertrage die lokalen Daten der Digramme in die Objektvariablen
	{
		if (dgt[i])
		{
			digrams[j].anz=dgt[i];
			digrams[j].di[2]=0;
			digrams[j].ciphdi[2]=0;
			sprintf(digrams[j].di,"%c%c",valkey(i%36),valkey(i/36));
			j++;
		}
		i++;
	}
	qsort(digrams,numdigrams,sizeof(struct digram),(int (__cdecl *)(const void *,const void *))compdigram);
*/
}

void Playfair::UpdateDigrams(int Dec)
{
	/*
	int j,k,c1,r1,c2,r2,x;
	
	for (x=0;x<numdigrams;x++)
	{
		for ( j=0; j<size; j++ )
		{
			for ( k=0; k<size; k++ )
			{
				if ( getCharOfMatrix (j,k) == digrams[x].di[0] )
				{
					c1 = k;
					r1 = j;
				}
				if ( getCharOfMatrix (j,k) == digrams[x].di[1] )
				{
					c2 = k;
					r2 = j;
				}
			}
		}
		PlayfairCipher( Dec, r1, r2, c1, c2, digrams[x].ciphdi, 0 );
	}
	*/
}

int compdigram(struct digram *x,struct digram *y)
{
	return y->anz - x->anz;
}

Playfair::~Playfair()
{
	assert (inbuf);
	assert (outbuf);
	assert (digrams);
//	assert (my_digrams);
	assert (my_matrix);

	free(inbuf); inbuf = NULL;
	free(outbuf); outbuf = NULL;
//	free(digrams); digrams = NULL;
	
	delete[](my_digrams); my_digrams = NULL;
//	delete (myAlphabet); myAlphabet = NULL; //blos nicht freigeben, sonst Fehler
	delete (my_matrix); my_matrix = NULL;
}

void Playfair::PrintMatrix(char *out)
{
	int i,j,k;
	
	k=0;
	for(i=0;i<6;i++)
	{
		for(j=0;j<6;j++)
		{
			out[k++] = getCharOfMatrix (i,j);
		}
		out[k++]='\n';
	}
	out[k]=0;
}

/*--------------------------------------------------------------------*/
/* CreateMatrixFromPass                                               */
/*                                                                    */
/* Create matrix using given password.                                */
/* This matrix is necessary to do playfair encryption.                */
/*                                                                    */
/*--------------------------------------------------------------------*/
void Playfair::SetPass(char *passw)
{
	int i,j;
	char tmp[100];

	strcpy(tmp,passw);
	strupr( tmp ); /* only capital letters allowed */
	for(i=0,j=0;i<(int)strlen(tmp);i++)
	{
		if(keyval(tmp[i])!=-1)
			passphrase[j++]=tmp[i];
	}
	passphrase[j]=0;

	CreateMatrixFromPass();
}

void Playfair::CreateMatrixFromPass()
{
	int iLenP,iLenA,i,j;
	char tmp[100];
	
	for(i=0;i<100;i++)
		tmp[i]=0;
	
	/* take away double letters within the password .................*/
	iLenA = (size==6)?36:25;
	iLenP = min((int)strlen(passphrase),iLenA);

	if ( UseOfDoublesInPass == 1 )    /* default */
	{
		int j;
		
		for ( i=0, j=0;  i<iLenP;  i++, j++ )
		{
			if ( IsElement((char *)tmp, passphrase[i]) )
				j--;
			else
				tmp[j] = passphrase[i] ;
		}
	}
	else if (UseOfDoublesInPass==0)
	{
		int i,ka;	  
		
		for ( i=0; i<iLenP; i++ )
		{
			if ( IsElement((char *)tmp, passphrase[i]) )
			{
				ka=(keyval(passphrase[i])+1)%iLenA; // die Suche nach noch nicht verwendeten Buchstaben
				while(IsElement((char *)tmp,valkey(ka)))
					ka=(ka+1)%iLenA;
				tmp[i]=valkey(ka);
			}
			else
				tmp[i] = passphrase[i] ;
		}
	}
	
	tmp[36]=0;
	
	char ordered_alph[36+1];
	char marked[36]; /* '1' if letter in pass; '0' else */
	
	/*    initialisiere marked .........................................*/
	for ( i=0; i<36; i++ )
		marked[i] = '0';  /* default; this letter is not in pass .........*/
	
	/*    markiere die Buchstaben aus pucAlph_s, die in pass enthalten sind, mit 1 */
	iLenP = strlen(tmp);
	
	for ( j=0; j<iLenP; j++ )
		marked[keyval(tmp[j])]='1';
	
	
	/*    fill ordered_alph for matrix (the letters from pass are       */
	/*    written at the beginning)  ...................................*/
	for ( i=0; i<36; i++ )
		ordered_alph[i] = 0;

	strcpy((char *)ordered_alph, tmp);
	for ( i=0, j=iLenP; i<iLenA; i++ )
	{
		if ( '0'== marked[i] )
			ordered_alph[j++] = valkey(i);
	}
	
	
	/*    Fill Matrix using ordered_alph .............................*/
	if (size == 6)
	{
		for ( i=0; i<6; i++ )
		{
			for ( j=0; j<6; j++ )
				setElMatrix (ordered_alph[(i*6)+j], i,j);
		}
	}
	else
	{
		for ( i=0; i<5; i++ )
		{
			for ( j=0; j<5; j++ )
				setElMatrix (ordered_alph[(i*5)+j], i,j);
		}
	}
	return;
}

/*
ApplyPlayfairPreformat() führt die Ver-/Entschlüsselung mit vorherigem 
umformatieren (wird in prename abgespeichert) durch und schreibt das 
Ergebnis nach o. 
*/
void Playfair::ApplyPlayfairPreformat( int DecEnc,char *prename,char *o)
{
	FILE *pre;
	char *prebuf;
	int i,j;
	char old,c;
	char ex,aex;
	
	ex=theApp.TextOptions.m_trenn[0];            // Buchstabe zum einfügen
	aex=(ex=='Z')?'Y':ex+1;                      // alternative
	if(size==5)
	{
		if(ex=='J')
			ex='I';
		if(aex=='J')
			aex='K';
	}
	prebuf=(char *)malloc(inbuflen*2);
	old=0;
	for (i=j=0;i<inbuflen;i++)
	{
		c=inbuf[i];
		if (size==5&&(c=='J'||c=='j'))           // bei 5x5 Matrix 
			c='I';                               // wird J zu I
		if(!myisalpha(c))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
			c = myAlphabet->replaceInvalidLetter(c);
		if(myisalpha(c))
		{
			c=toupper(c);
			if(c==old&&theApp.TextOptions.m_addx)// soll getrennt werden
				prebuf[j++]=(old==ex)?aex:ex;    // falls zwei X
			prebuf[j++]=c;                       // ein Q einfügen
			old=c;                               // sonst Doppelbuchstaben
		}                                        // mit Xen trennen
	}
	free(inbuf);
	inbuflen=j;
    inbuf=(char *)malloc(inbuflen+1);
	strncpy(inbuf, prebuf, inbuflen);
	inbuf[inbuflen] = 0;
	free(prebuf);
	
	pre=fopen(prename,"wb");
	fwrite(inbuf,1,inbuflen,pre);
	fclose(pre);
	
	DoCipher(DecEnc,inbuflen);
	
	strcpy(outfile,o);
	outfp=fopen(outfile,"wb");
	fwrite(outbuf,1,outbuflen,outfp);
	fclose(outfp);
}

/*
ApplyPlayfairToInput():
Apply PLAYFAIR to the input text.
Danach bei Bedarf wieder vormatieren.
*/
void Playfair::ApplyPlayfairToInput( int DecEnc)
{
	int i,j,k;
	
	DoCipher(DecEnc,inbuflen);
	
	if(!ReFormat)
	{
		outfp=fopen(outfile,"wb");
		fwrite(outbuf,1,outbuflen,outfp);
		fclose(outfp);
		return;
	}
	for(i=j=0;i<inbuflen;i++)
	{
		if(myisalpha(inbuf[i]))
		{
			if(islower(inbuf[i])&&ConvertCase)
				inbuf[i] = tolower(outbuf[j]);
			else
				inbuf[i] = outbuf[j];
			j++;
			k++;
			if(j>=outbuflen)
				break;
		}
	}
	
	outfp=fopen(outfile,"wb");
	fwrite(inbuf,1,inbuflen,outfp);
	fclose(outfp);
	
} 

/*
DoCipher() Den EingabeText verschlüsseln.
(len gibt die zu verschlüsselnde Länge an)
Benutzt PlayfairCipher().
*/
void Playfair::DoCipher( int Dec, int len)
{
	int  r1, r2, c1, c2,i,j,k;
	char *CipherBufTemp;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Henrik Koy 23. Nov. 2000 BugFix:
	// Die Größe des Ausgabepuffers (outbuf) steht erst
	// nach der Verschlüsselung fest, deswegen wird der 
	// Ciphertext zunächst in CipherBufTemp geschrieben
	// (durch Wiederholungen im Klartext müssen zusätzliche
	//  Xe eingefügt werden.)
	CipherBufTemp = (char*)malloc(2*len);

	free(outbuf);
	outbuflen=0;

	if (len>inbuflen)
		len=inbuflen;
	
	for ( i=0; i<len; i++ ) 
	{
		char ib1,ib2;
		
		c1 = 0; r1 = 0; c2 = 0; r2 = 0;
		while(!myisalpha(inbuf[i])&&i<inbuflen)
			i++;
		if(i<inbuflen)
		{
			ib1=toupper(inbuf[i]);
			i++;
			while(!myisalpha(inbuf[i])&&i<inbuflen)
				i++;
			if(i<inbuflen)
				ib2=toupper(inbuf[i]);
			else
				ib2=inbuf[inbuflen++]=theApp.TextOptions.m_trenn[0];
		}
		else
			break;
		if (size ==5)
		{
			if (ib1 == 'J')
				ib1='I';
			if (ib2 == 'J')
				ib2='I';
		}
		for ( j=0; j<size; j++ )
		{
			for ( k=0; k<size; k++ )
			{
				if ( getCharOfMatrix(j,k) == ib1 )
				{
					c1 = k;
					r1 = j;
				}
				if ( getCharOfMatrix(j,k) == ib2 )
				{
					c2 = k;
					r2 = j;
				}
			}
		}
		
		PlayfairCipher( Dec, r1, r2, c1, c2, CipherBufTemp, outbuflen );
		outbuflen+=2;
	}
	
/*	if(outbuf[outbuflen-1]=='X')
	{
		--outbuflen;
		--inbuflen;
	}*/

	// Gehört mit zum BugFix (Koy 23. Nov 2000)
	outbuf = (char*)malloc(outbuflen+1);
	strncpy(outbuf, CipherBufTemp, outbuflen);
	outbuf[outbuflen]=0;
	free(CipherBufTemp);
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

/*
PlayfairCipher() eigentliche VERSCHLUESSELUNG 
Nachdem fuer szText_s[i und i+1] jeweils Spalte und Zeile bestimmt 
wurden, wird das zu diesem Klartextpaar gehoerende Cipherpaar      
ermittelt.                                                         
Fall 1: r1 = r2: beide in derselben Zeile 
Fall 2: c1 = c2: beide in derselben Spalte 
Fall 3: sonst    
Bem.:                                                              
- nur in Fall 1 und 2 unterscheiden sich die Ver- und die          
Entschluesselung.                                                
*/
void Playfair::PlayfairCipher (int dec_enc, int r1, int r2, int c1, int c2, char *cipher, int i)
{
	int move;
	
	
	if (dec_enc)
		move = size - 1;
	else
		move = 1;
	
	if ( r1 == r2 ) /*enc: nehme wrap-around den Buchstaben rechts davon*/
	{
		cipher[i]   = getCharOfMatrix (r1, (c1+move)%size);
		cipher[i+1] = getCharOfMatrix (r1, (c2+move)%size);
	}
	else if ( c1 == c2 )  /* enc: nehme den Buchstaben darunter ........*/
	{
		cipher[i]   = getCharOfMatrix ((r1+move)%size, c1);
		cipher[i+1] = getCharOfMatrix ((r2+move)%size, c1);
	}
	else  /* nehme in der gl. Zeile den Buchstaben, der in der Spalte */
        /* des anderen Buchstabens steht  ..........................*/
	{
		cipher[i]   = getCharOfMatrix (r1, c2);
		cipher[i+1] = getCharOfMatrix (r2, c1);
	}
	
}

void Playfair::AnalyseDigramme(int *num,struct digram *di)
{
	int i,j,
		d,t,q, // Anzahl der gefundenen Doubles, Tripel, Quadrupel
		s,
		res;
	char a[4],b[4];
	anadigramme *m;

	// hole mir auf einen Schlag gleich den ganzen benötigten Speicher
	if(!(m=(anadigramme *)malloc(s=sizeof(anadigramme)+(*num)*(sizeof(doub)+sizeof(tripel)+sizeof(quads)))))
		return;
	// jetzt wird der Speicher verteilt
	m->data=((char *)m+sizeof(anadigramme));
	m->dou=(doubs *)(m->data);
	m->tri=(tripel *)((char *)(m->dou)+(*num)*sizeof(doub));
	m->qua=(quads *)((char *)(m->tri)+(*num)*sizeof(tripel));

	do // solange genliste (s.u.) noch nicht zufrieden ist
	{
		for(i=d=t=q=0;i<(*num);i++) // mach mal für jedes Digramm
		{
			a[0]=di[i].di[0];
			a[1]=di[i].ciphdi[0];
			a[2]=di[i].di[1];
			a[3]=di[i].ciphdi[1];
			
			if(a[0]==a[2]) // gleicher Buchstabe des Klartextes
			{
				m->dou[d].d[0]=a[0];
				m->dou[d].d[1]=a[1]; // dann merke nur die Klartextzeichen
				m->dou[d++].flag=WAAG;
			}
			else if (a[0]==a[3]) // erster Buchstabe Klartext == zweiter Buchstabe Chiffrat
			{
				m->tri[t].d[0]=a[2]; // merke 2.Klarbuchstaben
				m->tri[t].d[1]=a[0]; // merke 1.Klarbuchstaben
				m->tri[t].d[2]=a[1]; // merke 1.Chiffrezeichen
				m->tri[t++].flag=WAAG|SENK|ECK;
			}
			else if (a[1]==a[2]) // zweiter Buchstabe Klartext == erster Buchstabe Chiffrat
			{
				m->tri[t].d[0]=a[0]; // merke 1.Klarbuchstaben
				m->tri[t].d[1]=a[1]; // merke 1.Chiffrezeichen
				m->tri[t].d[2]=a[3]; // merke 2.Chiffrezeichen
				m->tri[t++].flag=WAAG|SENK|ECK;
			}
			else
			{
				strncpy(m->qua[q].d,a,4); // merke alles vor
				m->qua[q++].flag=WAAG|SENK|ECK;
			}
		}
		for(i=0;i<t;i++)  // für jedes identifizierte Trippel
		{
			for(j=0;j<d;j++) // durchlaufe für jedes Trippel alle Doubles
			{
				if (2==str_in(m->dou[j].d,2,m->tri[i].d,3)) // wenn beide Zeichen aus dem Double im Trippel vorkommen
					m->tri[i].flag=WAAG;
			}
			for(j=0;j<q;j++) // durchlaufe für jedes Trippel alle Quadrupel
			{
				a[0]=m->qua[j].d[0];  // 1.Klarbuchstaben
				a[1]=m->qua[j].d[2];  // 2.Klarbuchstaben
				b[0]=m->qua[j].d[1];  // 1.Chiffrezeichen
				b[1]=m->qua[j].d[3];  // 2.Chiffrezeichen
				// wenn entweder beide Klarbuchstaben oder beide Chiffrezeichen im aktuellen Trippel vorkommen
				if(2==str_in(a,2,m->tri[i].d,3)||2==str_in(b,2,m->tri[i].d,3))
					m->qua[j].flag&=WAAG|SENK;
			}
		}
		for(i=0;i<q;i++) // für jedes gefundene Quadrupel
		{
			for(j=0;j<d;j++)
			{
				a[0]=m->qua[i].d[0];  // 1.Klarbuchstaben
				a[1]=m->qua[i].d[2];  // 2.Klarbuchstaben
				b[0]=m->qua[i].d[1];  // 1.Chiffrezeichen
				b[1]=m->qua[i].d[3];  // 2.Chiffrezeichen
				// wenn beide Buchstaben eines Doubles in den beiden Klarbuchstaben oder in den beiden Chiffrezeichen eines Quadrupels vorkommen
				if (2==str_in(m->dou[j].d,2,a,2)||2==str_in(m->dou[j].d,2,b,2))
					m->qua[i].flag=WAAG;
			}
		}
		
		for(i=0;i<36;i++)
			m->matrix[i]=0;
		m->d=d;
		m->t=t;
		m->q=q;
		m->size=s;
		
		res=genliste(m);
		(*num)--;
	}while(res!=0);

	(*num)++;
	for(i=0;i<36;i++)
		setElMatrix (m->matrix[i], i/6, i%6);
		
	free(m);
}

void Playfair::ana_addqua(quads *qua,int q,char mat[6][6],bool flag)
{
	int i,j,k,l,m,n;

	for(i=0;i<q;i++)
	{
		j=str_in(qua[i].d,4,(char *)mat,36);
		if(j==3)
		{
			k=findrow(qua[i].d[0],mat);
			l=findrow(qua[i].d[1],mat);
			m=findrow(qua[i].d[2],mat);
			n=findrow(qua[i].d[3],mat);
			if(n==-1&&k==l)
				addmat(mat,m,qua[i].d[3]);
			else if(m==-1&&k==l)
				addmat(mat,n,qua[i].d[2]);
			else if(l==-1&&m==n)
				addmat(mat,k,qua[i].d[1]);
			else if(k==-1&&m==n)
				addmat(mat,l,qua[i].d[0]);
		}
		else if(j==2)
		{
			k=findrow(qua[i].d[0],mat);
			l=findrow(qua[i].d[1],mat);
			m=findrow(qua[i].d[2],mat);
			n=findrow(qua[i].d[3],mat);
			if(k==-1&&n==-1)
			{
				addmat(mat,l,qua[i].d[0]);
				addmat(mat,m,qua[i].d[3]);
			}
			else if(l==-1&&m==-1)
			{
				addmat(mat,k,qua[i].d[1]);
				addmat(mat,n,qua[i].d[2]);
			}
			else if(k==-1&&l==-1&&flag)
			{
				bool run;

				run=true;
				for(j=0;j<size&&run;j++)
				{
					if(matlen(mat,j)==0)
					{
						addmat(mat,j,qua[i].d[0]);
						addmat(mat,j,qua[i].d[1]);
						run=false;
					}
				}
				for(j=0;j<size&&run;j++)
				{
					if(matlen(mat,j)<size-1)
					{
						addmat(mat,j,qua[i].d[0]);
						addmat(mat,j,qua[i].d[1]);
						run=false;
					}
				}
			}
			else if(m==-1&&n==-1&&flag)
			{
				bool run;

				run=true;
				for(j=0;j<size&&run;j++)
				{
					if(matlen(mat,j)<size-2)
					{
						addmat(mat,j,qua[i].d[2]);
						addmat(mat,j,qua[i].d[3]);
						run=false;
					}
				}
				for(j=0;j<size&&run;j++)
				{
					if(matlen(mat,j)<size-2)
					{
						addmat(mat,j,qua[i].d[2]);
						addmat(mat,j,qua[i].d[3]);
						run=false;
					}
				}
			}
		}
	}
}

void Playfair::ana_addtri(tripel *tri,int t,char mat[6][6],bool flag)
{
	int i,j,f,zx,zy,k,l;

	for(i=0;i<t;i++)                   /*halbe einträge einfügen*/
	{
		k=str_in(tri[i].d,3,(char *)mat,36);
		if(k==2)
		{
			zx=zy=-1;
			for(f=0;f<size;f++)
			{
				zx=str_in(tri[i].d,3,mat[f],size);
				if(zx==2)
				{
					if(matlen(mat,f)<size)
					{
						zx=0;
						while(str_in(tri[i].d+zx,1,mat[f],size)==1)
							zx++;
						addmat(mat,f,tri[i].d[zx]);
					}
					f=6;
				}
				else if(zx==1)
				{
					if(zy==-1)
						zy=f;
					else
					{
						zx=0;
						while(str_in(tri[i].d+zx,1,(char *)mat,36)==1)
							zx++;
						switch(zx)
						{
						case 0:
							j=str_in(tri[i].d+1,1,mat[f],6);
							if((zy-f+size)%size==1&&j==1)
								addmat(mat,(f+size-1)%size,tri[i].d[zx]);
							if((f-zy+size)%size==1&&j==0)
								addmat(mat,(f+size-2)%size,tri[i].d[zx]);
							break;
						case 1:
							j=str_in(tri[i].d,1,mat[f],6);
							if((zy-f+size)%size==2&&j==1)
								addmat(mat,(f+1)%size,tri[i].d[zx]);
							if((f-zy+size)%size==2&&j==0)
								addmat(mat,(f+size-1)%size,tri[i].d[zx]);
							break;
						case 2:
							j=str_in(tri[i].d,1,mat[f],6);
							if((zy-f+size)%size==1&&j==1)
								addmat(mat,(f+2)%size,tri[i].d[zx]);
							if((f-zy+size)%size==1&&j==0)
								addmat(mat,(f+1)%size,tri[i].d[zx]);
							break;
						}
					}
				}
			}
		}
		else if (k==1)
		{
			j=findrow(tri[i].d[0],mat);
			k=findrow(tri[i].d[1],mat);
			l=findrow(tri[i].d[2],mat);
			if(j!=-1)
			{
				if(matlen(mat,j)+2>size&&flag)
				{
					mat[(j+1)%size][strlen(mat[(j+1)%size])]=tri[i].d[1];
					mat[(j+2)%size][strlen(mat[(j+2)%size])]=tri[i].d[2];
				}
				if((matlen(mat,(j+1)%size)==size||matlen(mat,(j+2)%size)==size))
				{
					addmat(mat,j,tri[i].d[1]);
					addmat(mat,j,tri[i].d[2]);
				}
			}
			else if(k!=-1)
			{
				if(matlen(mat,k)+2>size&&flag)
				{
					mat[(k+size-1)%size][strlen(mat[(k+size-1)%size])]=tri[i].d[0];
					mat[(k+1)%size][strlen(mat[(k+1)%size])]=tri[i].d[2];
				}
				if((matlen(mat,(k+1)%size)==size||matlen(mat,(k-1+size)%size)==size))
				{
					addmat(mat,k,tri[i].d[0]);
					addmat(mat,k,tri[i].d[2]);
				}
			}
			else
			{
				if(matlen(mat,l)+2>size&&flag)
				{
					mat[(l+size-2)%size][strlen(mat[(l+size-2)%size])]=tri[i].d[0];
					mat[(l+size-1)%size][strlen(mat[(l+size-1)%size])]=tri[i].d[1];
				}
				if((matlen(mat,(l+size-2)%size)==size||matlen(mat,(l+size-1)%size)==size))
				{
					addmat(mat,l,tri[i].d[0]);
					addmat(mat,l,tri[i].d[1]);
				}
			}
		}
	}
}

void Playfair::ana_sortrowtri(tripel *tri,int t,char mat[6][6])
{
	int i,j,k,zx,zy,f;

	for(i=0;i<t;i++)                              /*zeilen anpassen*/
	{
		if(str_in(tri[i].d,3,(char *)mat,36)==3)
		{
			k=0;
			for(j=0;j<size;j++)
			{
				if(str_in(tri[i].d,3,mat[j],size)>1)
					k++;
			}
			if(k==0)
			{
				j=findrow(tri[i].d[0],mat);
				f=findrow(tri[i].d[1],mat);
				zy=(f+size-j)%size;
				if(zy!=1)
				{
					char trow[6];

					strncpy(trow,mat[f],size);
					for(zx=zy;zx>1;zx--)
						strncpy(mat[(j+zx)%size],mat[(j+zx-1)%size],size);
					strncpy(mat[(j+1)%size],trow,size);
				}
				f=findrow(tri[i].d[2],mat);
				zy=(f+size-j)%size;
				if(zy!=2)
				{
					char trow[6];

					strncpy(trow,mat[f],size);
					for(zx=zy;zx>2;zx--)
						strncpy(mat[(j+zx)%size],mat[(j+zx-1)%size],size);
					strncpy(mat[(j+2)%size],trow,size);
				}
			}
		}
	}
}

void Playfair::addchar(char *z,char a)
{
	if(str_in(&a,1,z+1,z[0])==0&&a!=-1)
		z[++z[0]]=a;
}

void Playfair::addmat(char b[6][6],int z,char a)
{
	int i;

	if(str_in(&a,1,b[z],size)!=0)
		return;
	i=0;
	while(i<size)
	{
		if(b[z][i]==0)
		{
			b[z][i]=a;
			return;
		}
		i++;
	}
}

int Playfair::matlen(char b[6][6],int z)
{
	int i,j;

	i=0;
	for(j=0;j<size;j++)
	{
		if(b[z][j]!=0)
			i++;
	}
	return i;
}

int Playfair::genliste(anadigramme *oldm)
// an Peter Gruber: was macht das Ding hier?
{
	char nebr[36],nebc[36],zeilen[36][37],spalten[36][37],zmat[6][6],tmat[6][6],outa[100],tmp[37];
	int i,s,f,pa,tnum;
	char j,k,zx,zy;

	for(i=0;i<36;i++)
	{
		zeilen[i][0]=0;
		zmat[i/6][i%6]=0;
		tmat[i/6][i%6]=0;
		nebr[i]=-1;
		nebc[i]=-1;
	}
	for(i=0;i<oldm->d;i++)                          /*eintragen welche zeichen in der gleichen Zeilen stehen könnten*/
	{
		j=keyval(oldm->dou[i].d[0]);
		k=keyval(oldm->dou[i].d[1]);
		addchar(zeilen[j],k);
		addchar(zeilen[k],j);
	}
	for(i=0;i<oldm->q;i++)
	{
		j=keyval(oldm->qua[i].d[0]);
		k=keyval(oldm->qua[i].d[1]);
		addchar(zeilen[j],k);
		j=keyval(oldm->qua[i].d[2]);
		k=keyval(oldm->qua[i].d[3]);
		addchar(zeilen[j],k);
	}
	for(i=0;i<oldm->t;i++)
	{
		j=keyval(oldm->tri[i].d[0]);
		k=keyval(oldm->tri[i].d[1]);
		addchar(zeilen[j],k);
		j=keyval(oldm->tri[i].d[1]);
		k=keyval(oldm->tri[i].d[2]);
		addchar(zeilen[j],k);
	}
	s=0;
	for(i=0;i<36;i++)
	{
		pa=0;
		for(f=i+1;f<36;f++)                        /*sammeln der Zeileninfo*/
		{
			char tp,op;

			for(j=0;j<36;j++)
				tmp[j]=0;
			for(j=0;j<zeilen[i][0];j++)
			{
				k=zeilen[i][j+1];
				if(k!=i)
					tmp[k]++;
			}
			for(j=0;j<zeilen[f][0];j++)
			{
				k=zeilen[f][j+1];
				if(k!=f)
					tmp[k]++;
			}
			tmp[i]++;
			tmp[f]++;
			tp=0;
			op=pa;
			for(j=0;j<36;j++)
			{
				k=valkey(j);
				if(tmp[j]==2)
				{
					tp++;
					if(0==str_in(&k,1,outa,pa))
						*(outa+(pa++))=k;
				}
			}
			if(tp==1)                                /*nichts falls nur ein Zeichen gleich*/
				pa=op;
		}
		outa[pa]=0;
		zx=-1;
		f=0;
		while(f<size&&(j=str_in(outa,pa,zmat[f],size))==0)
			f++;
		if(0<j&&j<pa)
		{
			if(pa-j+matlen(zmat,f)>size)
				return 2;
			for(j=0;j<pa;j++)
				addmat(zmat,f,outa[j]);
			zx=f;
			for(j=0;j<size;j++)
			{
				if(j!=f&&str_in(outa,pa,zmat[j],size)>0)
				{
					if(matlen(zmat,f)+matlen(zmat,j)-str_in(zmat[j],size,zmat[f],size)<=size)
					{
						for(zy=0;zy<size;zy++)
						{
							addmat(zmat,f,zmat[j][zy]);
							zmat[j][zy]=0;
						}
					}
				}
			}
		}
		else if(j==pa)
			zx=f;
		if(zx==-1)
		{
			pa=min(pa,size);
			f=0;
			while(f<size&&matlen(zmat,f)!=0)
				f++;
			if(f<size)
				strncpy(zmat[f],outa,min(pa,size));
			else
			{
				f=0;
				while(f<size&&matlen(zmat,f)>=size-pa)
					f++;
				if(f<size)
				{
					for(j=0;j<pa;j++)
						addmat(zmat,f,outa[j]);
				}
			}
		}
		ana_addtri(oldm->tri,oldm->t,zmat);
	}

	f=0;
	for(i=0;i<size;i++)
		f+=matlen(zmat,i);
	if(f==0&&oldm->q>0)
	{
		addmat(zmat,0,oldm->qua[0].d[0]);
		addmat(zmat,0,oldm->qua[0].d[1]);
		addmat(zmat,1,oldm->qua[0].d[3]);
		addmat(zmat,1,oldm->qua[0].d[2]);
	}
	ana_addqua(oldm->qua,oldm->q,zmat);
	ana_sortrowtri(oldm->tri,oldm->t,zmat);
	ana_sortrowtri(oldm->tri,oldm->t,zmat);
	ana_sortrowtri(oldm->tri,oldm->t,zmat);
	ana_addqua(oldm->qua,oldm->q,zmat);
	ana_addtri(oldm->tri,oldm->t,zmat);
	ana_addqua(oldm->qua,oldm->q,zmat);
	ana_addtri(oldm->tri,oldm->t,zmat);
	ana_addqua(oldm->qua,oldm->q,zmat);
	ana_sortrowtri(oldm->tri,oldm->t,zmat);
	ana_sortrowtri(oldm->tri,oldm->t,zmat);
	ana_addqua(oldm->qua,oldm->q,zmat,true);
	ana_addtri(oldm->tri,oldm->t,zmat);
	ana_addqua(oldm->qua,oldm->q,zmat);
	ana_sortrowtri(oldm->tri,oldm->t,zmat);
	ana_sortrowtri(oldm->tri,oldm->t,zmat);
	ana_addqua(oldm->qua,oldm->q,zmat,true);
	ana_addtri(oldm->tri,oldm->t,zmat);
	ana_addqua(oldm->qua,oldm->q,zmat);

	for(i=0;i<36;i++)
	{
		char c[36];
		bool run;

		run=false;

		for(f=0;f<zeilen[i][0];f++)
			c[f]=findrow(valkey(zeilen[i][f+1]),zmat);
		j=findrow(valkey(i),zmat);
		if(j!=-1)
		{
			for(f=0;f<zeilen[i][0];f++)
			{
				if(c[f]!=-1&&j!=c[f])
					run=true;
			}
			if(run)
			{
				for(f=0;f<zeilen[i][0];f++)
				{
					if(c[f]==-1)
						addmat(zmat,j,zeilen[i][f+1]);
				}
			}
		}
	}
	
	tnum=0;
	do
	{
		memcpy((char *)tmat,(char *)zmat,36);
		for(i=0;i<36;i++)
		{
			zeilen[i][0]=0;
			spalten[i][0]=0;
		}
		for(i=0;i<size*size;i++)
		{
			j=keyval(zmat[i/size][i%size]);
			if(j!=-1)
			{
				for(f=0;f<min((int)strlen(zmat[i/size]),size);f++)
				{
					addchar(zeilen[j],keyval(zmat[i/size][f]));
					if(zeilen[j][0]>size)
						return 2;
				}
			}
		}
		for(i=0;i<oldm->q;i++)
		{
			if(str_in(oldm->qua[i].d,4,(char *)zmat,36)>1)
			{
				f=0;
				while((zy=str_in(oldm->qua[i].d,4,zmat[f],6))==0)
					f++;
				switch (zy)
				{
				case 1:
					for(f=0;f<4;f++)
					{
						addchar(spalten[keyval(oldm->qua[i].d[0])],keyval(oldm->qua[i].d[(0+f)%4]));
						addchar(spalten[keyval(oldm->qua[i].d[1])],keyval(oldm->qua[i].d[(1+f)%4]));
						addchar(spalten[keyval(oldm->qua[i].d[2])],keyval(oldm->qua[i].d[(2+f)%4]));
						addchar(spalten[keyval(oldm->qua[i].d[3])],keyval(oldm->qua[i].d[(3+f)%4]));
					}
					nebc[keyval(oldm->qua[i].d[0])]=keyval(oldm->qua[i].d[1]);
					nebc[keyval(oldm->qua[i].d[2])]=keyval(oldm->qua[i].d[3]);
					break;
				case 2:
					addchar(spalten[keyval(oldm->qua[i].d[0])],keyval(oldm->qua[i].d[3]));
					addchar(spalten[keyval(oldm->qua[i].d[3])],keyval(oldm->qua[i].d[0]));
					addchar(spalten[keyval(oldm->qua[i].d[1])],keyval(oldm->qua[i].d[2]));
					addchar(spalten[keyval(oldm->qua[i].d[2])],keyval(oldm->qua[i].d[1]));
					break;
				case 4:
					nebr[keyval(oldm->qua[i].d[0])]=keyval(oldm->qua[i].d[1]);
					nebr[keyval(oldm->qua[i].d[2])]=keyval(oldm->qua[i].d[3]);
					break;
				}
			}
		}
		for(i=0;i<oldm->t;i++)
		{
			if(str_in(oldm->tri[i].d,3,(char *)zmat,36)>1)
			{
				f=0;
				while((zy=str_in(oldm->tri[i].d,3,zmat[f],6))==0)
					f++;
				if(zy==1)
				{
					for(f=0;f<3;f++)
					{
						addchar(spalten[keyval(oldm->tri[i].d[0])],keyval(oldm->tri[i].d[f]));
						addchar(spalten[keyval(oldm->tri[i].d[1])],keyval(oldm->tri[i].d[(f+1)%3]));
						addchar(spalten[keyval(oldm->tri[i].d[2])],keyval(oldm->tri[i].d[(f+2)%3]));
					}
					nebc[keyval(oldm->tri[i].d[0])]=keyval(oldm->tri[i].d[1]);
					nebc[keyval(oldm->tri[i].d[1])]=keyval(oldm->tri[i].d[2]);
				}
				else if(zy==3)
				{
					nebr[keyval(oldm->tri[i].d[0])]=keyval(oldm->tri[i].d[1]);
					nebr[keyval(oldm->tri[i].d[1])]=keyval(oldm->tri[i].d[2]);
				}
			}
		}
		for(j=0;j<36;j++)
		{
			for(f=1;f<36;f++)
			{
				if(str_in(&j,1,spalten[f]+1,spalten[f][0])==1)
				{
					for(i=0;i<spalten[f][0];i++)
						addchar(spalten[j],spalten[f][i+1]);
				}
			}
		}
		
		for(i=0;i<36;i++)
			zmat[i/6][i%6]=0;
		for(i=f=0;i<36;i++)
		{
			char a[36];
			int p;

			p=min((int)zeilen[i][0],size);			
			for(j=0;j<p;j++)
				a[j]=valkey(zeilen[i][j+1]);
			
			if(str_in(a,p,(char *)zmat,36)==0&&p>0&&f<size)
			{
				strncpy(zmat[f],a,p);
				f++;
			}
		}
		k=0;
		while(nebc[k]==-1&&k<36)
			k++;
		if(k<36)
		{
			char a,b,c;
			
			a=findrow(valkey(k),zmat);
			b=findrow(valkey(nebc[k]),zmat);
			if(a!=-1&&b!=-1)
			{
				switchrows(0,a,zmat);
				switchrows(1,b==0?a:b,zmat);
			}
			else if(b!=-1)
			{
				i=0;
				while(matlen(zmat,i)==size&&i<size)
					i++;
				switchrows(0,i,zmat);
				switchrows(1,b==0?i:b,zmat);
				addmat(zmat,0,valkey(k));
			}
			else if(a!=-1)
			{
				i=1;
				while(matlen(zmat,i)==size&&i<size)
					i++;
				switchrows(0,a,zmat);
				switchrows(1,i==0?a:i,zmat);
				addmat(zmat,1,valkey(nebc[k]));
			}
			nebc[k]=-1;
			i=2;
			while(i<size)
			{
				bool run;
				
				run=true;
				for(c=0;c<size;c++)
				{
					b=keyval(zmat[i-1][c]);
					if(b!=-1&&nebc[b]!=-1)
					{
						a=findrow(valkey(nebc[b]),zmat);
						if(a!=-1&&a>=i)
						{
							switchrows(a,i,zmat);
							run=false;
						}
						nebc[b]=-1;
					}
				}
				if(run&&i<size-1)
				{
					k=0;
					while(nebc[k]==-1&&k<36)
						k++;
					a=findrow(valkey(k),zmat);
					b=findrow(valkey(nebc[k]),zmat);
					if(a!=-1&&b!=-1)
					{
						switchrows(i,a,zmat);
						switchrows(i+1,b==i?a:b,zmat);
					}
					else if(b!=-1)
					{
						j=i;
						while(matlen(zmat,j)==size&&j<size)
							j++;
						switchrows(i,j,zmat);
						switchrows(i+1,b==i?j:b,zmat);
						addmat(zmat,i,valkey(k));
					}
					else if(a!=-1)
					{
						j=i+1;
						while(matlen(zmat,j)==size&&j<size)
							j++;
						switchrows(i,a,zmat);
						switchrows(i+1,j==i?a:j,zmat);
						addmat(zmat,i+1,valkey(nebc[k]));
					}
					if(k==36)
						nebc[k]=-1;
					for(k=0;k<oldm->t;k++)
					{
						if(str_in(oldm->tri[k].d+1,1,zmat[i],size)&&!str_in(oldm->tri[k].d,1,zmat[i-1],size)&&matlen(zmat,i-1)==size)
						{
							for(f=i+2;f<size;f++)
							{
								if(matlen(zmat,f)<size)
								{
									switchrows(i,f,zmat);
									switchrows(i+1,f,zmat);
									switchrows(i+2,f,zmat);
									i++;
									f=size;
								}
							}
						}
					}
					i++;
				}
				i++;
			}
		}
		for(j=0;j<size-1;j++)
		{
			for(i=0;i<size;i++)
			{
				if(zmat[j][i]!=0)
				{
					for(f=j+1;f<size;f++)
					{
						int a,b;
						
						for(a=0;a<size;a++)
						{
							for(b=0;b<spalten[keyval(zmat[j][i])][0];b++)
							{
								if(spalten[keyval(zmat[j][i])][b+1]==keyval(zmat[f][a]))
								{
									char c;	
									
									c=zmat[f][i];
									zmat[f][i]=zmat[f][a];
									zmat[f][a]=c;
									a=b=100;
								}
							}
						}
					}
				}
			}
		}
		k=0;
		while(nebr[k]==-1&&k<36)
			k++;
		if(k<36)
		{
			char a,b,c;
			
			a=findcol(valkey(k),zmat);
			b=findcol(valkey(nebr[k]),zmat);
			if(a!=-1&&b!=-1)
			{
				switchcols(0,a,zmat);
				switchcols(1,b==0?a:b,zmat);
			}
			nebr[k]=-1;
			i=2;
			while(i<size)
			{
				bool run;
				
				run=true;
				for(c=0;c<size;c++)
				{
					b=keyval(zmat[c][i-1]);
					if(nebr[b]!=-1&&b!=-1)
					{
						a=findcol(valkey(nebr[b]),zmat);
						if(a!=-1&&a>=i)
						{
							switchcols(a,i,zmat);
							run=false;
						}
						nebr[b]=-1;
					}
				}
				if(run&&i<size-1)
				{
					k=0;
					while(nebr[k]==-1&&k<36)
						k++;
					a=findcol(valkey(k),zmat);
					b=findcol(valkey(nebr[k]),zmat);
					if(a!=-1&&b!=-1)
					{
						switchcols(i,a,zmat);
						switchcols(i+1,b==i?a:b,zmat);
					}
					if(k<36)
						nebr[k]=-1;
					i++;
				}
				i++;
			}
		}
		ana_addtri(oldm->tri,oldm->t,zmat,true);
		ana_addqua(oldm->qua,oldm->q,zmat);
		ana_addtri(oldm->tri,oldm->t,zmat,true);
		ana_addqua(oldm->qua,oldm->q,zmat,true);
		for(i=0;i<37;i++)
			tmp[i]=0;
		for(i=0;i<size*size;i++)
			tmp[keyval(zmat[i/size][i%size])+1]++;
		f=0;
		
		for(i=0;i<size*size;i++)
		{
			if(zmat[i/size][i%size]==0)
			{
				while(tmp[f+1]!=0)
					f++;
				zmat[i/size][i%size]=valkey(f++);
			}
		}
		for(i=0;i<size;i++)
		{
			for(f=0;f<size;f++)
			{
				oldm->matrix[(i*6)+f]=zmat[i][f];
			}
		}
	}
	while(tnum++<10&&memcmp(tmat,zmat,36)!=0);
	return 0;
}

void Playfair::movechar(int i,char *a)
{
	char tmp[6];
	int j;

	for (j=0;j<size;j++)
		tmp[(j+i+size)%size]=a[j];
	for (j=0;j<size;j++)
		a[j]=tmp[j];
}

int Playfair::findcol(char a,char b[6][6])
{
	int i;

	if(a==0)
		return -1;
	for(i=0;i<36;i++)
	{
		if(a==b[i/6][i%6])
			return i%6;
	}
	return -1;
}

void Playfair::switchrows(int k,int l,char b[6][6])
{
	char a[6];

	if(l==k)
		return;
	strncpy(a,b[k],6);
	strncpy(b[k],b[l],6);
	strncpy(b[l],a,6);
}

void Playfair::switchcols(int k,int l,char b[6][6])
{
	char c;
	int i;

	if(l==k)
		return;
	for(i=0;i<6;i++)
	{
		c=b[i][k];
		b[i][k]=b[i][l];
		b[i][l]=c;
	}
}

int Playfair::findrow(char a,char b[6][6])
{
	int i;

	if(a==0)
		return -1;
	for(i=0;i<36;i++)
	{
		if(a==b[i/6][i%6])
			return i/6;
	}
	return -1;
}

int Playfair::navmatrix(int pos,int x,int y)
{
	int i,j;

	j=pos/size;
	i=pos%size;
	return ((i+x)%size)+((j+y)%size)*6;
}
	
int Playfair::str_in(char *in,int s,char *str,int l)
// wieviele Buchstaben von in tauchen mindestens einmal in str auf
{
	int i,j,ret;
	
	ret=0;
	for (i=0;i<s;i++)
	{
		for (j=0;j<l;j++)
		{
			if(in[i]==str[j])
			{
				ret++;
				break;
			}
		}
	}
	return ret;
}
