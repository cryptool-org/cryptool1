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
#include <stdio.h>

//#include <Wxdebug.h>


/*--------------------------------------------------------------------*/
/* class playfair_letter                                              */
/*--------------------------------------------------------------------*/
// Je mehr Infos über einen Buchstaben vorliegen, desto mehr Gewicht
// bekommt er. Das entscheidet die Reihenfolge nachher bei der Erstellung
// der Matrix
#define WEIGHT_neighbour	0120	// Gewicht für möglichen Nachbarn
#define WEIGHT_rowsure		0050	// Gewicht für sichere Zeile
#define WEIGHT_row			0030	// Gewicht für mögliche Zeile
#define WEIGHT_colsure		0040	// Gewicht für sichere Zeile
#define WEIGHT_col			0005	// Gewicht für mögliche Zeile

#define	C2I(x)	((my_matrixsize==6)?((((x)>='A')&&((x)<='Z'))?(x)-'A':(x)-'0'+'Z'-'A'+1):(((x)>='J')?(x)-'A'-1:(x)-'A'))
#define I2C(x)	((char) (my_matrixsize==6)?(((x)<=('Z'-'A'))?(x)+'A':(x)+'0'+'A'-'Z'-1):(((x)<'J'-'A')?(x)+'A':(x)+'A'+1))
#define L2U(x)	((char) (((x)>='a')&&((x)<='z'))?(x)-'a'+'A':(x))

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
	my_maxsetsize		= MAXDIM;
	my_value = c;
	clear_letter();
} // playfair_letter(char c)

int playfair_letter::my_maxsetsize = MAXDIM;


void playfair_letter::clear_letter()
{
    my_above = NULL;
    my_below = NULL;
    my_right = NULL;
    my_left = NULL;
	my_cnt_rightorbelow = 0;
    my_cnt_leftorabove  = 0;
    my_cnt_row_sure     = 0;
    my_cnt_col_sure     = 0;
    my_cnt_roworbelow   = 0;
    my_cnt_roworabove   = 0;
    my_cnt_roworcol     = 0;
	for (int i=0; i<my_maxsetsize; i++) {
	    my_row_sure[i] = NULL;
		my_col_sure[i] = NULL;
		my_rightorbelow[i] = NULL;
		my_leftorabove[i] = NULL;
		my_roworbelow[i] = NULL;
		my_roworabove[i] = NULL;
	}
	for (i=0; i<2*my_maxsetsize; i++) {
		my_roworcol[i] = NULL;
	}
	my_weight = 0;
} // clear_letter()

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

bool playfair_letter::isinset(playfair_set set, playfair_letter* s)
{
        assert (set); assert (s);
        int i=0;
		switch (set) {
		  case row_sure:
			while ((i<my_maxsetsize)&&(i<my_cnt_row_sure)){
                if (my_row_sure[i++]==s) return (true);
			} break;
		  case col_sure:
			while ((i<my_maxsetsize)&&(i<my_cnt_col_sure)){
                if (my_col_sure[i++]==s) return (true);
			} break;
		  case rightorbelow:
			while ((i<2)&&(i<my_cnt_rightorbelow)){
                if (my_rightorbelow[i++]==s) return (true);
			} break;
		  case leftorabove:
			while ((i<2)&&(i<my_cnt_leftorabove)){
                if (my_leftorabove[i++]==s) return (true);
			} break;
		  case roworbelow:
			while ((i<my_maxsetsize)&&(i<my_cnt_roworbelow)){
                if (my_roworbelow[i++]==s) return (true);
			} break;
		  case roworabove:
			while ((i<my_maxsetsize)&&(i<my_cnt_roworabove)){
                if (my_roworabove[i++]==s) return (true);
			} break;
		  case roworcol:
			while ((i<2*my_maxsetsize)&&(i<my_cnt_roworcol)){
                if (my_roworcol[i++]==s) return (true);
			} break;
        }
        return (false);
} // isinset(playfair_set set, playfair_letter* s)

/*bool playfair_letter::forall_row(<nicht spezifiziert> callroutine)
{

}
*/

void playfair_letter::insert2set(playfair_set set, playfair_letter* s)
{
        assert (s);
        int i=0;
		playfair_letter* x;
        switch (set) {
        case row_sure:
			if (!isinset(row_sure, s)) { // falls der Eintrag nicht schon erfolgte,
				if (my_cnt_row_sure > my_maxsetsize-1) // und die Liste noch nicht voll ist,
					throw playfair_error(101, this);
				my_row_sure[my_cnt_row_sure++] = s;  //dann erfolgt er jetzt
				incWeight (WEIGHT_rowsure);
				// im folgenden werden implizite Regeln angewandt.
				s->insert2set (row_sure, this);
				insert2set (roworabove, s);
				insert2set (roworbelow, s);
				insert2set (roworcol, s);
				// explizite Regeln
				//die schon gesicherten Buchstaben des neuen, habe ich auch in meiner Zeile
				for (i=0; s->my_cnt_row_sure > i; i++) {
					x = s->my_row_sure[i];
					if (x != this)
						insert2set (row_sure, x);
				}
				//Regeln, wenn die Liste jetzt voll ist
				if (my_cnt_row_sure == my_maxsetsize-1) {
					//dann kann das Element in der Schnittmenge roworabove mit not rowsure nur drüber liegen.
					for (i=0; my_cnt_row_sure > i; i++)
						if (!isinset(row_sure, my_roworabove[i]))
							setNeighbour (above, my_roworabove[i]);
					//analog mit roworbelow
					for (i=0; my_cnt_row_sure > i; i++)
						if (!isinset(row_sure, my_roworbelow[i]))
							setNeighbour (below, my_roworbelow[i]);
					//analog mit roworcol
					for (i=0; my_cnt_roworcol > i; i++)
						if (!isinset(row_sure, my_roworcol[i]))
							insert2set (col_sure, my_roworcol[i]);
				}
			}
			break;
        case col_sure:
			if (!isinset(col_sure, s)) { // falls der Eintrag nicht schon erfolgte,
				if (my_cnt_col_sure > my_maxsetsize-1) // und die Liste noch nicht voll ist,
					throw playfair_error(102, this);
				my_col_sure[my_cnt_col_sure++] = s;  //dann erfolgt er jetzt
				incWeight (WEIGHT_colsure);
				// im folgenden werden implizite Regeln angewandt.
				s->insert2set (col_sure, this);
				insert2set (roworcol, s);
				// explizite Regeln
				//die schon gesicherten Buchstaben des neuen, habe ich auch in meiner Spalte
				for (i=0; s->my_cnt_col_sure > i; i++) {
					x = s->my_col_sure[i];
					if (x != this)
						insert2set (col_sure, x);
				}
			}
			break;
        case rightorbelow:
			if (!isinset(rightorbelow, s)) { // falls der Eintrag nicht schon erfolgte,
				if (my_cnt_rightorbelow > 1) // und die Liste noch nicht voll ist,
					throw playfair_error(103, this);
				my_rightorbelow[my_cnt_rightorbelow++] = s;  //dann erfolgt er jetzt
				incWeight (WEIGHT_neighbour);
				// im folgenden werden implizite Regeln angewandt.
				s->insert2set (leftorabove, this);
				insert2set (roworcol, s);
				// explizite Regeln
				// wenn row_sure schon voll ist, dann liegt s sicher drunter
				if ((my_cnt_row_sure == my_maxsetsize-1) && (!isinset(row_sure, s)))
					setNeighbour (below, s);
				//rechts | drunter und Reihe sicher in der Spalte -> drunter
				if (isinset(col_sure, s)) {
					setNeighbour (below, s);
					if (my_cnt_rightorbelow > 1) { // gibt's schon einen rechts oder drunter Kandidaten? -> dieser ist rechts
						setNeighbour(right, my_rightorbelow[0]);
					}
					if (isinset(roworabove, s)) throw playfair_error(113, this);
				} else
				//rechts | drunter und Reihe | drüber -> rechts
				if (isinset(roworabove, s)) {
					setNeighbour (right, s);
					if (my_cnt_rightorbelow > 1) { // gibt's schon einen rechts oder drunter Kandidaten? -> dieser ist drunter
						setNeighbour(below, my_rightorbelow[0]);
					}
				}
			}
			break;
        case leftorabove:
			if (!isinset(leftorabove, s)) { // falls der Eintrag nicht schon erfolgte,
				if (my_cnt_leftorabove > 1) // und die Liste noch nicht voll ist,
					throw playfair_error(104, this);
				my_leftorabove[my_cnt_leftorabove++] = s;  //dann erfolgt er jetzt
				incWeight (WEIGHT_neighbour);
				// im folgenden werden implizite Regeln angewandt.
				s->insert2set (rightorbelow, this);
				insert2set (roworcol, s);
				// explizite Regeln
				// wenn row_sure schon voll ist, dann liegt s sicher drüber
				if ((my_cnt_row_sure == my_maxsetsize-1) && (!isinset(row_sure, s)))
					setNeighbour (above, s);
				if (isinset(col_sure, s)) { //links | drüber und Reihe sicher in der Spalte -> drüber
					setNeighbour (above, s);
					if (my_cnt_leftorabove > 1) { // gibt's schon einen rechts oder drunter Kandidaten? -> dieser ist rechts
						setNeighbour(left, my_leftorabove[0]);
					}
					if (isinset(roworbelow, s)) throw playfair_error(114, this);
				} else
				if (isinset(roworbelow, s)) { //links | drüber und Reihe | drunter -> links
					setNeighbour (left, s);
					if (my_cnt_leftorabove > 1) { // gibt's schon einen links oder drüber Kandidaten? -> dieser ist drüber
						setNeighbour(above, my_leftorabove[0]);
					}
				}
			}
			break;
        case roworabove:
			if (!isinset(roworabove, s)) { // falls der Eintrag nicht schon erfolgte,
				if (my_cnt_roworabove > my_maxsetsize-1) // und die Liste noch nicht voll ist,
					throw playfair_error(105, this);
				my_roworabove[my_cnt_roworabove++] = s;  //dann erfolgt er jetzt
				incWeight (WEIGHT_row);
				// im folgenden werden implizite Regeln angewandt.
				s->insert2set (roworbelow, this);
				insert2set (roworcol, s);
				// explizite Regeln
				// wenn row_sure schon voll ist, dann liegt s sicher drüber
				if ((my_cnt_row_sure == my_maxsetsize-1) && (!isinset(row_sure, s)))
					setNeighbour (above, s);
				if (isinset(rightorbelow, s)) { //rechts | drunter und Reihe | drüber -> rechts
					setNeighbour (right, s);
				}
				if (isinset(roworbelow, s)) { //Reihe | drüber und Reihe | drunter -> sicher in Reihe
					insert2set (row_sure, s);
				}
				//wenn A und X Zeichen S in roworabove haben -> alle sicher in Reihe
				//da dann X auch in Ss roworbelow enthalten ist, folgendes vorgehen:
				//durchsuche jedes Zeichen (X) in S.roworbelow, S in X.roworabove vorhanden ist.
				//Hm, stimmt doch nicht.

			}
			break;
        case roworbelow:
			if (!isinset(roworbelow, s)) { // falls der Eintrag nicht schon erfolgte,
				if (my_cnt_roworbelow > my_maxsetsize-1) // und die Liste noch nicht voll ist,
					throw playfair_error(106, this);
				my_roworbelow[my_cnt_roworbelow++] = s;  //dann erfolgt er jetzt
				incWeight (WEIGHT_row);
				// im folgenden werden implizite Regeln angewandt.
				s->insert2set (roworabove, this);
				insert2set (roworcol, s);
				// explizite Regeln
				// wenn row_sure schon voll ist, dann liegt s sicher drunter
				if ((my_cnt_row_sure == my_maxsetsize-1) && (!isinset(row_sure, s)))
					setNeighbour (below, s);
				if (isinset(leftorabove, s)) { //links | drüber und Reihe | drunter -> links
					setNeighbour (left, s);
				}
				if (isinset(roworabove, s)) { //Reihe | drüber und Reihe | drunter -> sicher in Reihe
					insert2set (row_sure, s);
				}
			}
			break;
        case roworcol:
			if (!isinset(roworcol, s)) { // falls der Eintrag nicht schon erfolgte,
				if (my_cnt_roworcol > 2*my_maxsetsize-1) // und die Liste noch nicht voll ist,
					throw playfair_error(107, this);
				my_roworcol[my_cnt_roworcol++] = s;  //dann erfolgt er jetzt
				incWeight (WEIGHT_col);
				// im folgenden werden implizite Regeln angewandt.
				s->insert2set (roworcol, this);
				// explizite Regeln
				// wenn row_sure schon voll ist, dann liegt s sicher in der Spalte
				if ((my_cnt_row_sure == my_maxsetsize-1) && (!isinset(row_sure, s)))
					insert2set (col_sure, s);
			}
			break;
        other :
                assert(0);
        }
} // playfair_letter::insert2set(playfair_set set, playfair_letter* s)

void playfair_letter::setNeighbour(playfair_neighbour pos, playfair_letter* s)
{
        assert (s);
        switch (pos)
        {
        case above:
			if ((my_above) && (*my_above != *s)) throw playfair_error(201, this);
			if ((my_above) && (*my_above == *s)) return;
			else {
                my_above = s;
                s->setNeighbour (below, this);
				incWeight (WEIGHT_neighbour);
				insert2set (col_sure, s);
			}
			break;
        case below:
			if ((my_below) && (*my_below != *s)) throw playfair_error(202, this);
			if ((my_below) && (*my_below == *s)) return;
			else {
                my_below = s;
                s->setNeighbour (above, this);
				incWeight (WEIGHT_neighbour);
				insert2set (col_sure, s);
			}
			break;
        case left:
			if ((my_left) && (*my_left != *s)) throw playfair_error(203, this);
			if ((my_left) && (*my_left == *s)) return;
			else {
                my_left = s;
                s->setNeighbour (right, this);
				incWeight (WEIGHT_neighbour);
				insert2set (row_sure, s);
			}
			break;
        case right:
			if ((my_right) && (*my_right != *s)) throw playfair_error(204, this);
			if ((my_right) && (*my_right == *s)) return;
			else {
                my_right = s;
                s->setNeighbour (left, this);
				incWeight (WEIGHT_neighbour);
				insert2set (row_sure, s);
			}
			break;
        other :
                assert(0);
        }
} //playfair_letter::setNeighbour

void playfair_letter::getNeighboursString(char *s, int slen)
{
	assert (s);
	s[0] = (my_left) ?my_left ->getValue():NULLELEMENT;
	s[1] = (my_right)?my_right->getValue():NULLELEMENT;
	s[2] = (my_above)?my_above->getValue():NULLELEMENT;
	s[3] = (my_below)?my_below->getValue():NULLELEMENT;
	s[4] = '\0';
}

void playfair_letter::getUndefinedNeighboursString(char *s, int slen)
{
	int i,j;
	assert (s);
	memset(s,0,slen);

	i=0;
	j=0;
	if (my_cnt_leftorabove>0) {
		s[i++] = my_leftorabove[0]->getValue();
		if (my_cnt_leftorabove>1) {
			s[i++] = ',';
			s[i++] = my_leftorabove[1]->getValue();
		}
	}
	s[i++] = '/';
	if (my_cnt_rightorbelow>0) {
		s[i++] = my_rightorbelow[0]->getValue();
		if (my_cnt_rightorbelow>1) {
			s[i++] = ',';
			s[i++] = my_rightorbelow[1]->getValue();
		}
	}
	assert (i<slen);
	s[i] = '\0';
}

void playfair_letter::getRowString(char *s, int slen)
{
	int i,j;
	char c[2];
	assert (s);
	memset(s,0,slen);

	i=0;
	j=0;
	while ((j<my_maxsetsize) && (j<my_cnt_row_sure)) {
		s[i++] = my_row_sure[j++]->getValue();
		s[i++] = '!'; s[i++] = ',';
	}
	c[1]='\0';
	while ((j<my_maxsetsize) && (j<my_cnt_roworbelow)) {
		c[0] = my_roworbelow[j++]->getValue();
		if (!strstr(s,c)) {
			s[i++] = c[0];
			s[i++] = '.';
			s[i++] = ',';
		}
	}
	while ((j<my_maxsetsize) && (j<my_cnt_roworabove)) {
		c[0] = my_roworabove[j++]->getValue();
		if (!strstr(s,c)) {
			s[i++] = c[0];
			s[i++] = '°';
			s[i++] = ',';
		}
	}
	assert (i<slen);
	if (i>0)
		s[i-1]='\0';
}

void playfair_letter::getColString(char *s, int slen)
{
	int i,j;
	assert (s);
	//memset(s,0,slen);
	for (i=0; i<slen; i++)
		s[i]='\0';

	i=0;
	j=0;
	while ((j<my_maxsetsize) && (j<my_cnt_col_sure)) {
		s[i++] = my_col_sure[j++]->getValue();
		s[i++] = '!'; s[i++] = ',';
	}
	assert (i<slen);
	if (i>0)
		s[i-1]='\0';
}

void playfair_letter::getRoworcolString(char *s, int slen)
{
	int i,j;
	char c[2];
	assert (s);
	memset(s,0,slen);

	i=0;
	j=0;
	c[1]='\0';
	while ((j<2*my_maxsetsize) && (j<my_cnt_roworcol)) {
		s[i++] = my_roworcol[j++]->getValue();
		s[i++] = ',';
	}
	assert (i<slen);
	if (i>0)
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
//	delete[] (my_visited); my_visited = NULL;
	delete[] (my_letters); my_letters = NULL;
//jetzt als Feld	delete[] (my_pfletters);    my_pfletters = NULL;
}

playfair_alphabet::playfair_alphabet (int size)
{
	assert ((size==5)||(size==6));
	my_count = (size==5) ? 5*5 : 6*6;
	my_max_count = MAXDIM * MAXDIM;
	my_validletters = new bool[(my_max_count+1)];
	my_letters = new letter[1];  //dummy
// jetzt als Feld	my_pfletters = new playfair_letter[my_max_count+1];
	my_pfletters[0] = playfair_letter(NULLELEMENT);
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

void playfair_alphabet::clear_letters()
{
	for (int i=0; i < sizeof(my_pfletters)/sizeof(my_pfletters[0]); i++) {
		my_pfletters[i].clear_letter();
	}
}

playfair_letter* playfair_alphabet::addLetter(char let)
{
	assert (0);
	return NULL;
}

playfair_letter* playfair_alphabet::getLetter(char let)
{
	assert (let>=0);
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
		if ((my_validletters[i]) && (my_pfletters[i].getValue()==let))
			return &my_pfletters[i];
	return &my_pfletters[0];
} // getLetter


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
playfair_letterlist::playfair_letterlist(playfair_alphabet* the_alphabet, bool isCopyAllValid, int the_maxLen)
{
	int i, j;
	my_alphabet = the_alphabet;
	my_maxLen = the_maxLen;
	my_pfletters = (playfair_letter**) malloc(my_maxLen*sizeof(playfair_letter*));
//	my_pfletters = new *playfair_letter[my_maxLen];
	my_visited = new bool[(my_maxLen)];
	my_len=0;
	i=0;
	if (isCopyAllValid)
		//jetzt kopiere alle gültigen Zeichen aus dem Alphabet in die Liste
		for (j=0; (my_len < my_maxLen) && (j <= my_alphabet->getMaxCount()); j++) {
			if (my_alphabet->getValidOfLetter(j)) {
				char c = my_alphabet->getLetter(j)->getValue();
				my_pfletters[my_len] = my_alphabet->getLetter(j);
				my_visited[my_len] = false;
				my_len++;
			}
		}
	// der Rest wird mit dem Null-Element aufgefüllt.
	for (i = my_len; i < my_maxLen; i++) {
		my_pfletters[i] = my_alphabet->getNullElement();
		my_visited[i] = false;
	}
}
playfair_letterlist::~playfair_letterlist()
{
	delete[] (my_visited); my_visited = NULL;
//	delete[] (my_pfletters);    my_pfletters = NULL;
	free (my_pfletters);
}

void playfair_letterlist::reset_visited(bool flag)
{
	for (int i=0; i < my_maxLen; i++) {
		my_visited[i] = flag;
	}
}

void playfair_letterlist::print (char *s, bool withWeight)
{
	char s2[7*40];
	s2[0] = '\0';
	for (int i=0; i < my_maxLen; i++) {
		sprintf (s, "%s%c%d ", s2, my_pfletters[i]->getValue(), my_pfletters[i]->getWeight());
		sprintf (s2, "%s", s);
	}
	sprintf (s, "%s\n", s);
}

void playfair_letterlist::copy (playfair_letterlist* dst, playfair_letterlist* src)
{
	int i;
	assert (dst->my_maxLen==src->my_maxLen);
	dst->my_len = src->my_len;
	for (i=0; i < dst->my_len; i++) {
		dst->my_pfletters[i]	= src->my_pfletters[i];
		dst->my_visited[i]		= src->my_visited[i];
	}
	for (; i < dst->my_maxLen; i++) {
		dst->my_pfletters[i]	= dst->my_alphabet->getNullElement();
		dst->my_visited[i]		= false;
	}
}

playfair_letter* playfair_letterlist::getLetter(int i)
{
	assert (i >= 0);
	assert (i < my_maxLen);
	assert (i <= my_len);
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

void playfair_letterlist::sortViaWeight ()
// selection sort
{
	bool flag;
	playfair_letter *let;
	int maxweight, index;

	for (int i=0; i < my_len; i++) {
		maxweight = my_pfletters[i]->getWeight();
		index = i;
		for (int j = i+1; j < my_len; j++) { // suche größten Wert
			if (maxweight < my_pfletters[j]->getWeight()) {
				maxweight = my_pfletters[j]->getWeight();
				index = j;
			}
		}
		if (index != i) {
			let = my_pfletters[i]; my_pfletters[i] = my_pfletters[index]; my_pfletters[index] = let;
			if (my_visited[i] != my_visited[index]) {
				flag = my_visited[i]; my_visited[i] = my_visited[index]; my_visited[index] = flag;
			}
		}
	}
} // sortViaWeight

/*--------------------------------------------------------------------*/
/* class playfair_digramm                                             */
/*--------------------------------------------------------------------*/
playfair_digramm::playfair_digramm(playfair_alphabet* ab, int msize, char letter1, char letter2, char chiffre1, char chiffre2)
{
	my_matrixsize = msize;
	setLetters(L2U(letter1), L2U(letter2));
	setChiffres(L2U(chiffre1), L2U(chiffre2));
	my_count = 1;
	my_alphabet = ab;
}

playfair_digramm::playfair_digramm(playfair_alphabet* ab, int msize)
{
	my_matrixsize = msize;
	assert ((my_matrixsize==5) || (my_matrixsize==6));
	my_visited = false;
	my_count = 0;
	if (ab)
		playfair_digramm(ab, msize, '\0','\0','\0','\0');
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
	my_letter1 = my_alphabet->getLetter((char)L2U(c1));
	my_letter2 = my_alphabet->getLetter((char)L2U(c2));
}

inline void playfair_digramm::setLetters(playfair_letter* c1, playfair_letter* c2)
{
	my_letter1 = c1;
	my_letter2 = c2;
}

inline void playfair_digramm::setChiffres(char c1, char c2)
{
	my_chiffre1 = my_alphabet->getLetter((char)L2U(c1));
	my_chiffre2 = my_alphabet->getLetter((char)L2U(c2));
}

inline void playfair_digramm::setChiffres(playfair_letter* c1, playfair_letter* c2)
{
	my_chiffre1 = c1;
	my_chiffre2 = c2;
}

int playfair_digramm::getIndex()
{
	assert ((my_matrixsize==5) || (my_matrixsize==6));
	int ret = (C2I(my_chiffre1->getValue()))*MAXDIM*MAXDIM + C2I(my_chiffre2->getValue());
	assert ((ret>=0) && (ret<MAXDIGRAMMS));
	return ret;
}

int playfair_digramm::getIndex(char chiffre1, char chiffre2)
{
	chiffre1 = L2U(chiffre1);
	chiffre2 = L2U(chiffre2);
	assert ((my_matrixsize==5) || (my_matrixsize==6));
	int ret = (C2I(chiffre1))*MAXDIM*MAXDIM + C2I(chiffre2);
	int a = (C2I(chiffre1))*MAXDIM*MAXDIM;
	int b = C2I(chiffre2);
	assert ((ret>=0) && (ret<MAXDIGRAMMS));
	return ret;
}

int playfair_digramm::getIndex(playfair_letter* c1, playfair_letter* c2)
{
	assert ((my_matrixsize==5) || (my_matrixsize==6));
//	int i=((c1->getValue()-'A')*MAXDIM*MAXDIM + c2->getValue()-'A');
	int ret (C2I(c1->getValue())*MAXDIM*MAXDIM + C2I(c2->getValue()));
	assert ((ret>=0) && (ret<MAXDIGRAMMS));
	return ret;
}

/*--------------------------------------------------------------------*/
/* class playfair_letterlist                                             */
/*--------------------------------------------------------------------*/
playfair_digrammlist::playfair_digrammlist(playfair_alphabet* the_alphabet, playfair_digramm* digramsbase, char *plain, char *chiffre, int charlen, int the_maxDigLen)
{
	int j, iseol = 0;
	playfair_digramm* dig=digramsbase;
	my_alphabet = the_alphabet;
	my_maxLen = max (the_maxDigLen, charlen/2);
	my_digramms = (playfair_digramm**) malloc(my_maxLen*sizeof(playfair_digramm*));
	j=0;
	for (my_len=0; my_len < charlen/2; my_len++) {  // evtl. Probleme, wenn doppelte Zeichen erlaubt
		char c1, c2, p1, p2;
		do { c1=chiffre[j]; p1=plain[j++]; } while (!my_alphabet->myisalpha(c1));
		do { c2=chiffre[j]; p2=plain[j++]; } while (!my_alphabet->myisalpha(c2));
		dig = &digramsbase[dig->getIndex(c1, c2)];
		dig->setChiffres (c1, c2);
		iseol = iseol || (p1=='\0') || (p2=='\0');
		if (!iseol)
			dig->setLetters (p1, p2);
		my_digramms[my_len] =  dig;
		assert (dig->getLetter1() && dig->getLetter2() && dig->getChiffre1() && dig->getChiffre2());
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
	d->incCount();
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
	myAlphabet = new playfair_alphabet(6);
	myLetterlist = new playfair_letterlist(myAlphabet);
	UseOfDoublesInPass=0; /* default: only use the first appearance of distinguished letters in passphrase */
	strcpy(passphrase,"PLAYFIR");
	ReFormat=1;
	ConvertCase=1;
	SetSize(1);
	my_cntdigrams=0;
	my_digrams = new playfair_digramm [MAXDIGRAMMS];//(&myAlphabet);
//	memset(my_digrams,0,MAXDIGRAMMS * sizeof(playfair_digramm));

}

/*BOOL Playfair::myisalpha( char ch )
// prüft auf korrekte Zeichen
{
	if (size == 6)
	return FALSE;
	return FALSE;
}
*/
BOOL Playfair::myisalpha2( char ch )
// prüft auf korrekte Zeichen
{
	if (mysize == 6)
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
	mysize=(sechs)?6:5;
/*	if(sechs)
	{
		strncpy(pc_str,alph,36);
		pc_str[36]=0;
	}
	else
	{
		strncpy(pc_str,alphs,25);
		pc_str[25]=0;
	}
	AppConv.SetAlphabet(pc_str,ConvertCase);
	theApp.TextOptions.m_alphabet=pc_str;
	// TG[25.10.01]: Überschreiben des Alphabets ist nicht mehr gewünscht.
*/

	if (my_digrams)		{ delete[] (my_digrams);	my_digrams = NULL; }
	if (my_matrix)		{ delete (my_matrix);		my_matrix = NULL; }
	if (myLetterlist)	{ delete (myLetterlist);	myLetterlist = NULL; }
	if (myAlphabet)		{ delete (myAlphabet);		myAlphabet = NULL; }
	myAlphabet		= new playfair_alphabet((sechs)?6:5);
	myLetterlist	= new playfair_letterlist(myAlphabet);
	my_matrix		= new keymatrix(mysize, myAlphabet->getNullElement());

	CreateMatrixFromPass();

	my_cntdigrams=0;
	my_digrams = new playfair_digramm [MAXDIGRAMMS];//(&myAlphabet);
//	memset(my_digrams,0,MAXDIGRAMMS * sizeof(playfair_digramm));
	assert (my_digrams);
	for (int i=0; i<MAXDIGRAMMS; i++){
		my_digrams[i].setAlphabet(myAlphabet);
		my_digrams[i].setCount(0);
		my_digrams[i].setLetters(myAlphabet->getNullElement(),myAlphabet->getNullElement());
		my_digrams[i].setChiffres(myAlphabet->getNullElement(),myAlphabet->getNullElement());
	}

}

char *Playfair::CreatePassfromMatrix()
{
	int i,j;
	char p[37];

	if (mysize==6)
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
	if(mysize==6)
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
	if(mysize==6)
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
	
	myAlphabet = NULL;	myLetterlist = NULL;
	my_matrix = NULL;	my_digrams = NULL;
	passphrase[0]='\0';
//	myAlphabet = new playfair_alphabet((sechs)?6:5);
//	myLetterlist = new playfair_letterlist(myAlphabet);
//	my_matrix = new keymatrix(6, myAlphabet->getNullElement());
	mysize=(sechs)?6:5;
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
		inbuflen = fread(inbuf, 1, inbuflen, infp);
		fclose(infp);
	}
	//GetDiGrams();
}

void Playfair::DeleteLetterGraph() {
	myAlphabet->clear_letters();
}

void Playfair::GetDiGrams()
{
//	int dgt[36*36],i,j;
	int i;
	playfair_digramm* dig = &my_digrams[0];
	
/*	for (i=0;i<36*36;i++)
		dgt[i]=0;*/
	i=0;
	while (i<inbuflen-1) // zähle, wie oft jedes Digramm vorkommt
	{
		playfair_letter *a, *b;
		a = myAlphabet->getNullElement();
		b = myAlphabet->getNullElement();
		while ((i<inbuflen) && (a==myAlphabet->getNullElement()))
			a = myAlphabet->getLetter(inbuf[i++]);
		if (i>=inbuflen) break;
		while ((i<inbuflen) && (b==myAlphabet->getNullElement()))
			b = myAlphabet->getLetter(inbuf[i++]);
		dig = &my_digrams[dig->getIndex(a,b)]; //dig->getIndex(a,b) ist Klassenfunktion, dh. es ist egal auf welches Digramm vorher der Zeiger verweist
		dig->setChiffres(a,b);
		dig->incCount();
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
		for ( j=0; j<mysize; j++ )
		{
			for ( k=0; k<mysize; k++ )
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

/*
int compdigram(struct digram *x,struct digram *y)
{
	return y->anz - x->anz;
}
*/

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
	delete (myLetterlist); myLetterlist = NULL;
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
	iLenA = (mysize==6)?36:25;
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
	
	tmp[MAXDIM*MAXDIM]=0;
//	for(i=0;i<100;i++)
//		assert (tmp[i] > 0);
	assert (tmp[0] >= 0);
	
	char ordered_alph[MAXDIM*MAXDIM+1];
	char marked[MAXDIM*MAXDIM]; /* '1' if letter in pass; '0' else */
	
	/*    initialisiere marked .........................................*/
	for ( i=0; i<MAXDIM*MAXDIM; i++ )
		marked[i] = '0';  /* default; this letter is not in pass .........*/
	
	/*    markiere die Buchstaben aus pucAlph_s, die in pass enthalten sind, mit 1 */
	iLenP = strlen(tmp);
	
	for ( j=0; j<iLenP; j++ )
		marked[keyval(tmp[j])]='1';
	
	
	/*    fill ordered_alph for matrix (the letters from pass are       */
	/*    written at the beginning)  ...................................*/
	for ( i=0; i<MAXDIM*MAXDIM+1; i++ )
		ordered_alph[i] = NULLELEMENT;

	if (iLenP)
		strcpy((char *)ordered_alph, tmp);
	for ( i=0, j=iLenP; i<iLenA; i++ )
	{
		if ( '0'== marked[i] )
			ordered_alph[j++] = valkey(i);
	}
	
	
	/*    Fill Matrix using ordered_alph .............................*/
	if (mysize == 6)
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
void Playfair::ApplyPlayfairPreformat( bool DecEnc,char *prename,char *o)
{
	FILE *pre;
	char *prebuf;
	int i,j;
	char old,c;
	char ex,aex;
	
	ex=theApp.TextOptions.m_trenn[0];            // Buchstabe zum einfügen
	aex=(ex=='Z')?'Y':ex+1;                      // alternative
	if(mysize==5)
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
/*		if (mysize==5&&(c=='J'||c=='j'))           // bei 5x5 Matrix 
			c='I';                               // wird J zu I*/
		if(!myisalpha2(c))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
			c = myAlphabet->replaceInvalidLetter(true, c);
		/* white spaces oder sonstige Buchstaben werden durch obige Routine nicht ersetzt.
		Daher können immer noch  falsche Buchstaben erscheinen */
		if(myisalpha2(c))
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
	
	DoCipher(true, DecEnc,inbuflen);
	
	strcpy(outfile,o);
	outfp=fopen(outfile,"wb");
	fwrite(outbuf,1,outbuflen,outfp);
	fclose(outfp);
}

/*
ApplyPlayfairToInput():
Apply PLAYFAIR to the input text.
Danach bei Bedarf wieder vormatieren.
TG: Diese Routine wird nur angesprungen, wenn im
Dialog PlayfairKey die Option vorformatieren
abgeschaltet ist.
*/
void Playfair::ApplyPlayfairToInput( bool DecEnc)
{
	int i,j,k;
	
	DoCipher(false, DecEnc,inbuflen);
	
	if(!ReFormat)
	{
		outfp=fopen(outfile,"wb");
		fwrite(outbuf,1,outbuflen,outfp);
		fclose(outfp);
		return;
	}
	for(i=j=0;i<inbuflen;i++)
	{
		if(!myisalpha2(inbuf[i]))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
			inbuf[i] = myAlphabet->replaceInvalidLetter(false, inbuf[i]);
		if(myisalpha2(inbuf[i]))
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
Gauweiler, 23.10.01: erweitert um eine Vorgabe zu berücksichtigen.
Keine Änderung bei nicht gesetzter Vorgabe.
Sobald des Entschlüsselungsergebnis von der Vorgabe
abweicht, bricht die Routine mit false ab.
*/
bool Playfair::DoCipher( bool withConvert, bool Dec, int len, char *stipulation, int stiplen)
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

	outbuflen=0;

	if (len>inbuflen)
		len=inbuflen;
	
	for ( i=0; i<len; i++ ) 
	{
		char ib1,ib2;
		
		c1 = -1; r1 = -1; c2 = -1; r2 = -1;
		if(withConvert && !myisalpha2(inbuf[i]))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
			inbuf[i] = getAlphabet()->replaceInvalidLetter(withConvert, inbuf[i]);
		while (!myisalpha2(inbuf[i])&&i<inbuflen)
			i++;
		if(i<inbuflen)
		{
			ib1=toupper(inbuf[i]);
			i++;
			if(withConvert && !myisalpha2(inbuf[i]))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
				inbuf[i] = getAlphabet()->replaceInvalidLetter(withConvert, inbuf[i]);
			while(!myisalpha2(inbuf[i])&&i<inbuflen)
				i++;
			if(i<inbuflen)
				ib2=toupper(inbuf[i]);
			else
				ib2=inbuf[inbuflen++]=theApp.TextOptions.m_trenn[0];
		}
		else
			break;
		if (mysize ==5)
		{
			if (ib1 == 'J')
				ib1='I';
			if (ib2 == 'J')
				ib2='I';
		}
		for ( j=0; j<mysize; j++ )
		{
			for ( k=0; k<mysize; k++ )
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

		if ((r1 < 0) || (r2 < 0)) {
			// Buchstabe in der Matrix nicht gefunden
			CipherBufTemp [outbuflen] = myAlphabet->getNullElement()->getValue();
			CipherBufTemp [outbuflen+1] = myAlphabet->getNullElement()->getValue();
		} else
			PlayfairCipher( Dec, r1, r2, c1, c2, CipherBufTemp, outbuflen );

		if (stipulation != NULL) {
			if (outbuflen+1 == stiplen) {
				// falls Länge der ungeraden Vorgabe (stiplen) erreicht ist.
				bool flag = (stipulation [outbuflen] == CipherBufTemp [outbuflen]);
				free(CipherBufTemp);
				return (flag);
			}
			if ((stipulation [outbuflen] != CipherBufTemp [outbuflen]) ||
				(stipulation [outbuflen+1] != CipherBufTemp [outbuflen+1]))
			{
				free(CipherBufTemp);
				return false;
			}
			if (outbuflen+2 == stiplen) {
				// Länge der (geraden) Vorgabe ist erreicht
				free(CipherBufTemp);
				return true;
			}
		}
		outbuflen+=2;
	}
	
/*	if(outbuf[outbuflen-1]=='X')
	{
		--outbuflen;
		--inbuflen;
	}*/

	// Gehört mit zum BugFix (Koy 23. Nov 2000)
	free(outbuf);
	outbuf = (char*)malloc(outbuflen+1);
	strncpy(outbuf, CipherBufTemp, outbuflen);
	outbuf[outbuflen]=0;
	free(CipherBufTemp);
	return (true);
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
	
	assert ((r1>=0)&&(r1<mysize));	// [TG]	
	assert ((r2>=0)&&(r2<mysize));	
	assert ((c1>=0)&&(c1<mysize));	
	assert ((c2>=0)&&(c2<mysize));	

	if (dec_enc)
		move = mysize - 1;
	else
		move = 1;
	
	if ( r1 == r2 ) /*enc: nehme wrap-around den Buchstaben rechts davon*/
	{
		cipher[i]   = getCharOfMatrix (r1, (c1+move)%mysize);
		cipher[i+1] = getCharOfMatrix (r1, (c2+move)%mysize);
	}
	else if ( c1 == c2 )  /* enc: nehme den Buchstaben darunter ........*/
	{
		cipher[i]   = getCharOfMatrix ((r1+move)%mysize, c1);
		cipher[i+1] = getCharOfMatrix ((r2+move)%mysize, c1);
	}
	else  /* nehme in der gl. Zeile den Buchstaben, der in der Spalte */
        /* des anderen Buchstabens steht  ..........................*/
	{
		cipher[i]   = getCharOfMatrix (r1, c2);
		cipher[i+1] = getCharOfMatrix (r2, c1);
	}
	
}

void Playfair::AnalyseDigramme(playfair_digrammlist* dl)
{
	playfair_digramm* dig;
	myAlphabet->getNullElement()->setSetSize(mysize);
	int i, j=0;
	for (i=0; i < dl->getLen(); i++)
		dl->getDigramm(i)->setVisited(false);
	for (i=0; i < dl->getLen(); i++) {
		dig = dl->getDigramm(i);
		assert (dig);
		assert (dig->getLetter1()->getValue()<='Z'); assert (dig->getLetter1()->getValue()>=NULLELEMENT);
		assert (dig->getLetter2()->getValue()<='Z'); assert (dig->getLetter2()->getValue()>=NULLELEMENT);

		if (dig->getVisited() || (dig->getLetter1() == myAlphabet->getNullElement()) || (dig->getLetter2() == myAlphabet->getNullElement()))
			continue;
		// Jetzt folgt der trivialste Teil der Erstellung der Graphen:
		// Ein Klarschrift-Buchstabe stimmt mit einem der Codebuchstaben überein
		if (dig->getLetter1() == dig->getChiffre1())
			throw playfair_error(1, dig->getLetter1());

		if (dig->getLetter2() == dig->getChiffre2())
			throw playfair_error(1, dig->getLetter2());

		if (dig->getLetter1() == dig->getChiffre2()) { // Bei ABC: BA->CB
			dig->getLetter1()->insert2set (rightorbelow, dig->getChiffre1());
			dig->getLetter2()->insert2set (rightorbelow, dig->getChiffre2());
			if (dig->getLetter2() == dig->getChiffre1())
				throw playfair_error(2, dig->getLetter2());
		} else if (dig->getLetter2() == dig->getChiffre1()) { // Bei ABC: AB->BC
			dig->getLetter1()->insert2set (rightorbelow, dig->getChiffre1());
			dig->getLetter2()->insert2set (rightorbelow, dig->getChiffre2());
			if (dig->getLetter1() == dig->getChiffre2())
				throw playfair_error(2, dig->getLetter1());
		} else {
			dig->getLetter1()->insert2set (roworbelow, dig->getChiffre1());
			dig->getLetter2()->insert2set (roworbelow, dig->getChiffre2());
			dig->getLetter1()->insert2set (roworcol, dig->getChiffre2());
			dig->getLetter2()->insert2set (roworcol, dig->getChiffre1());
		}
		dig->setVisited(true);
	}
} // AnalyseDigramme



///////////////////////////////////////////////////////////////////////////////////
// Analyse nach Peer Wichmann

bool Playfair::CreateMatrixStandalone (char *stipulation, int len)
// stipulation enthält die Klartextvorgabe. Sofern eine versuchte Entschlüsselung
// der Vorlage entspricht, ist eine (erstmal) gültige Matrix gefunden.
{
	char tmp_inbuf [302];
	int i, j;

	playfair_backtrace trace (getSize());

	myLetterlist->sortViaWeight();
	my_matrix->clear(myAlphabet->getNullElement());

	// copy inbuf to tmp_inbuf, but only the valid chars
	i=0; j=0;
	while ((i<=301) && (i<len) && (inbuf[j]) && (i<inbuflen)) {
		if (myisalpha2(toupper(inbuf[j]))) {
			tmp_inbuf [i] = toupper(inbuf[j]);
			if (tmp_inbuf [i] = stipulation [i])
				return false;
			i++;
		}
		j++;
	}
	tmp_inbuf[i]='\0';

	trace.memread(stipulation, tmp_inbuf, len, i);
	trace.analyse(my_matrix, myAlphabet);

	// jetzt sind alle Möglichkeiten durchprobiert
	return (DoCipher (false, 1, 300, stipulation, len));
} // CreateMatrix


#define ALEN	my_matrixsize
#define ASIZE	(ALEN*ALEN)

#define MAXINT	0x07ffff
#define R(x)	((x + ALEN) % ALEN)

//#define C2I(x)	((((x)>='A')&&((x)<='Z'))?(x)-'A':(x)-'0'+'Z'-'A'+1)
//#define I2C(x)	(((x)<=('Z'-'A'))?(x)+'A':(x)+'0'+'A'-'Z'-1)


class playfair_backthrow {
public:
        playfair_backthrow() {};
        ~playfair_backthrow() {};
        int reason;
};

class playfair_success {
public:
        playfair_success(playfair_arrinfo *a) {array = a;};
        ~playfair_success() {};
        playfair_arrinfo *array;
};

playfair_charinfo::playfair_charinfo( )
{
//	assert (0);
}

playfair_charinfo::playfair_charinfo_init(int msize)
{
        int i,j;

		my_matrixsize = msize;
        required = dirty = freq = 0;
        set = -1;
        possible = ASIZE;
        for(i=0;i<ALEN;i++)
                for(j=0;j<ALEN;j++)
                        p[i][j] = 1;
}

playfair_charinfo::~playfair_charinfo()
{
}

playfair_arrinfo::playfair_arrinfo( )
{
//	assert (0);
}
playfair_arrinfo::playfair_arrinfo_init(int msize)
{
        int i, j;

		my_matrixsize = msize;
        for(i=0;i<ASIZE;i++)
			c[i].playfair_charinfo_init(msize);

        for(i=0;i<ALEN;i++)
                for(j=0;j<ALEN;j++) {
                        m[i][j] = -1;
                        possible[i][j]=ASIZE;
                }
        dirty = 0;
        missing = ASIZE;
}

playfair_arrinfo::~playfair_arrinfo( void )
{
}

int playfair_arrinfo::disable( char ch, int x, int y )
{
        int i;

        if(c[ch].p[x][y]) { // ein Datum löschen
                c[ch].p[x][y] = 0;
                c[ch].possible--;
                if(c[ch].possible == 0) // Widerspruch --> backtrack!
                        throw playfair_backthrow();
                c[ch].dirty = 1;
                c[ch].required = 1;
                possible[x][y]--;
                if(possible[x][y] == 1) // deterministischen Fall gefunden!
                        for ( i=0; i< ASIZE; i++)
                                if(c[i].p[x][y]) {
                                        set( i, x, y);
                                        break;
                                }
                dirty = 1;
        }
        return 0;
}

int playfair_arrinfo::force_col_or_row( char ch, int x1, int y1)
{
        int x,y;

        for(x=0;x<ALEN;x++)
                for(y=0;y<ALEN;y++) {
                        if((y != y1) && (x != x1))
                                disable( ch, x, y );
                }
        return 0;
}

int playfair_arrinfo::force_row_or_pos( char ch, int y1, int x2, int y2)
{
        int x,y;

        for(x=0;x<ALEN;x++)
                for(y=0;y<ALEN;y++) {
                        if((y != y1) && ((x != x2) || (y!=y2)))
                                disable( ch, x, y );
                }
        return 0;
}

int playfair_arrinfo::force_col_or_pos( char ch, int x1, int x2, int y2)
{
        int x,y;

        for(x=0;x<ALEN;x++)
                for(y=0;y<ALEN;y++) {
                        if((x != x1) && ((x != x2) || (y!=y2)))
                                disable( ch, x, y );
                }
        return 0;
}

int playfair_arrinfo::force_col( char ch, int x1 )
{
        int x,y;

        for(x=0;x<ALEN;x++)
                for(y=0;y<ALEN;y++) {
                        if(x != x1)
                                disable( ch, x, y );
                }
        return 0;
}

int playfair_arrinfo::set(char ch, int x1, int y1)
{
        int i, x, y;

        if(!c[ch].p[x1][y1])
                throw playfair_backthrow(); // Widerspruch!
        if(m[x1][y1] == ch) return 0;
        c[ch].set = x1 + (y1 << 4);
        m[x1][y1] = ch;
        missing--;
        for(i=0;i<ASIZE;i++)
                if(i!=ch)
                        disable( i, x1,y1 );
        for(x=0;x<ALEN;x++)
                for(y=0;y<ALEN;y++) {
                        if((x != x1) || (y!=y1))
                                disable( ch, x, y );
                }
        c[ch].dirty = 1;
        dirty = 1;

        if(missing == 0)
                throw playfair_success(this);
        return 0;
}

playfair_backtrace::playfair_backtrace(int msize)
{
	int i;
		my_matrixsize = msize;
        for(i=0;i<ASIZE;i++)
			a[i].playfair_arrinfo_init(msize);
		l.init(my_matrixsize);

        level = 0;
}

void playfair_backtrace::analyse()
{
        char c1;
        int maxn,i, x, y;

        maxn = 0;
        for(i=0;i<ASIZE;i++) {
                if(maxn < a[level].c[i].freq) {
                        c1 = i;
                        maxn = a[level].c[i].freq;
                }
        }
        try {
                test(c1, 0, 0, 0);
                printf("Lösung gefunden");
        }
        catch(playfair_success s) {
                printf("Lösung gefunden\n");
                for(y=ALEN-1;y>=0;y--) {
                        for(x=0;x<ALEN;x++) {
                                if(s.array->m[x][y] < 'J'-'A') printf("%c ",s.array->m[x][y]+'A');
                                else printf("%c ",s.array->m[x][y]+'B');
                        }
                        printf("\n");
                }
        }
        catch(playfair_backthrow e) {
                printf("Fehler, Hauptsuche abgebrochen\n");
        }
}

bool playfair_backtrace::analyse( keymatrix *km, playfair_alphabet *pfalpha )
{
        char c1;
        int maxn,i, x, y;
		playfair_letter *pflet;

        maxn = 0;
        for(i=0;i<ASIZE;i++) {
                if(maxn < a[level].c[i].freq) {
                        c1 = i;
                        maxn = a[level].c[i].freq;
                }
        }
        try {
//                test(0, 0, 0, 0);
                test(c1, 0, 0, 0);
//                printf("Lösung gefunden");
        }
        catch(playfair_success s) {
                for(y=ALEN-1;y>=0;y--) {
                        for(x=0;x<ALEN;x++) {
							c1 = I2C(s.array->m[y][ALEN-x-1]);
							pflet = pfalpha->getLetter(c1);
							km->setElement(pflet, x, y);
                        }
                }
				return true;
        }
        catch(playfair_backthrow e) {
				return false;
        }
		assert (0);
		return false;
}

playfair_backtrace::~playfair_backtrace()
{
}

playfair_backtrace::test(char ch, int x1, int y1, int level)
{
        char c1;
        int i, minn, maxf, x, y;
        playfair_arrinfo *info = &(a[level]);

        // setzen des ersten Wertes
        info->set(ch, x1, y1);

        // Updaten der Restriktionen bis sich alles stabilisiert hat
        while(info->dirty) {
                info->dirty = false;
                for(c1 = 0; c1 < ASIZE; c1++) {
                        if(!info->c[c1].dirty) continue;
                        info->c[c1].dirty = 0;
                        for(i=0;i<l.n;i++)
                                if(l.d[i].is_in(c1))
                                        info->test_rule( l.d[i] );
                }
        }

        // Auswählen des nächsten Kandidaten und Rekursion
        minn = MAXINT;
        maxf = 0;
        c1 = -1;
        for(i=0;i<ASIZE;i++) {
                if(a[level].c[i].set == -1) {
                        if(minn > a[level].c[i].possible) {
                                c1 = i;
                                minn = a[level].c[i].possible;
                                maxf = a[level].c[i].freq;
                        }
                        else if(minn > a[level].c[i].possible && maxf < a[level].c[i].freq) {
                                c1 = i;
                                minn = a[level].c[i].possible;
                                maxf = a[level].c[i].freq;
                        }
                }
        }
        for(x=0; x<ALEN; x++)
                for(y=0; y<ALEN; y++)
                        if(info->c[c1].p[x][y]) {
                                a[level+1] = a[level];
                                try {
                                        test(c1, x, y, level+1);
                                        return 0;
                                }
                                catch(playfair_backthrow e) {
                                }
                        }
        throw playfair_backthrow();
        return 0;
}

int playfair_arrinfo::test_rule(playfair_data d )
{
        int i;
        int a1_set, a1_x, a1_y, a1p_x, a1p_y;
        int a2_set, a2_x, a2_y, a2p_x, a2p_y;
        int c1_set, c1_x, c1_y, c1p_x, c1p_y;
        int c2_set, c2_x, c2_y, c2p_x, c2p_y;
        // Vorberechnungen
        a1_set = (c[d.a1].set != -1);
        a2_set = (c[d.a2].set != -1);
        c1_set = (c[d.c1].set != -1);
        c2_set = (c[d.c2].set != -1);
        a1_x = c[d.a1].set & 0x0f;
        a1_y = c[d.a1].set >> 4;
        a2_x = c[d.a2].set & 0x0f;
        a2_y = c[d.a2].set >> 4;
        c1_x = c[d.c1].set & 0x0f;
        c1_y = c[d.c1].set >> 4;
        c2_x = c[d.c2].set & 0x0f;
        c2_y = c[d.c2].set >> 4;
        // a1, a2 gesetzt
        if(a1_set && a2_set) {
                // Chiffrat berechnen
                if(a1_x == a2_x) { // eine Spalte
                        c1p_y = R(a1_y - 1);
                        c2p_y = R(a2_y - 1);
                        c1p_x = c2p_x = a1_x;
                }
                else if(a1_y == a2_y) { // eine Zeile
                        c1p_x = R(a1_x + 1);
                        c2p_x = R(a2_x + 1);
                        c1p_y = c2p_y = a1_y;
                }
                else { // Rechteck
                        c1p_x = a2_x;
                        c1p_y = a1_y;
                        c2p_x = a1_x;
                        c2p_y = a2_y;
                }
                if(c1_set & (c1p_x != c1_x || (c1p_y != c1_y)))
                        throw playfair_backthrow(); // widerspruch --> backtrace
                if(c2_set & (c2p_x != c2_x || (c2p_y != c2_y)))
                        throw playfair_backthrow(); // widerspruch --> backtrace
                set(d.c1, c1p_x, c1p_y);
                set(d.c2, c2p_x, c2p_y);
                return 0;
        }
        // c1, c2 gesetzt ********************************************************************************
        if(c1_set && c2_set) {
                if(c1_x == c2_x) { // eine Spalte
                        a1p_y = R(c1_y + 1);
                        a2p_y = R(c2_y + 1);
                        a1p_x = a2p_x = c1_x;
                }
                else if(c1_y == c2_y) { // eine Zeile
                        a1p_x = R(c1_x - 1);
                        a2p_x = R(c2_x - 1);
                        a1p_y = a2p_y = c1_y;
                }
                else {
                        a1p_x = c2_x;
                        a1p_y = c1_y;
                        a2p_x = c1_x;
                        a2p_y = c2_y;
                }
                if(a1_set & (a1p_x != a1_x || (a1p_y != a1_y)))
                        throw playfair_backthrow(); // widerspruch --> backtrace
                if(a2_set & (a2p_x != a2_x || (a2p_y != a2_y)))
                        throw playfair_backthrow(); // widerspruch --> backtrace
                set(d.a1, a1p_x, a1p_y);
                set(d.a2, a2p_x, a2p_y);
                return 0;
        }
        // a1, c1 gesetzt
        if(a1_set && c1_set) {
                if(a1_x == c1_x) { // Sonderfall einer Spalte
                        if(a1_y != R(c1_y+1))
                                throw playfair_backthrow();
                        // a2, c2 müssen in der gleichen Spalte sein
                        force_col(d.a2, a1_x);
                        force_col(d.c2, a1_x);
                        // Nachbaren berücksichtigen (c2 hat um 1 kleinere y-Koordinate wie a2)
                        for(i=0;i<ALEN;i++) {
                                if(!c[d.c2].p[a1_x][i]) // c2 hier nicht möglich
                                        disable(d.a2, a1_x, R(i + 1));
                                else if(!c[d.a2].p[a1_x][i]) // a2 hier nicht möglich
                                        disable(d.c2, a1_x, R(i - 1));
                        }
                        return 0;
                }
                if(c1_y != a1_y)
                        throw playfair_backthrow();
                force_col_or_row(d.c2, a1_x, a1_y);
                force_col_or_row(d.a2, c1_x, c1_y);
                // Nachbarschaften berücksichtigen / Normalfall (Rechteck)
                for(i=0;i<ALEN;i++) {
                        if(!c[d.c2].p[a1_x][i]) // c2 hier nicht möglich
                                disable(d.a2, c1_x, i); // A2 disablen
                        else if(!c[d.a2].p[c1_x][i]) // a2 hier nicht möglich
                                disable(d.c2, a1_x, i); // C2 disablen
                }
                if(a1_x == R(c1_x-1)) { // eventuell Sonderfall in Zeile
                        for(i=0;i<ALEN;i++) {
                                if(!c[d.a2].p[i][a1_y]) // a2 hier nicht möglich
                                        disable(d.c2, R(i + 1), a1_y);  // C2 disablen
                                else if(!c[d.c2].p[i][a1_y]) // c2 hier nicht möglich
                                        disable(d.a2, R(i - 1), a1_y); // C2 disablen
                        }
                }
                return 0;
        }
        // a2, c2 gesetzt
        if(a2_set && c2_set) {
                if(a2_x == c2_x) { // Sonderfall einer Spalte
                        if(c2_y != R(a2_y-1))
                                throw playfair_backthrow();
                        // a1, c1 müssen in der gleichen Spalte sein
                        force_col(d.a1, a2_x);
                        force_col(d.c1, a2_x);
                        // Nachbaren berücksichtigen (c2 hat um 1 kleinere Koord wie a2)
                        for(i=0;i<ALEN;i++) {
                                if(!c[d.c1].p[a2_x][i]) // c1 hier nicht möglich
                                        disable(d.a1, a2_x, R(i + 1));
                                else if(!c[d.a1].p[a2_x][i]) // a1 hier nicht möglich
                                        disable(d.c1, a2_x, R(i - 1));
                        }
                        return 0;
                }
                // Standardfall
                if(c2_y != a2_y)
                        throw playfair_backthrow();
                force_col_or_row(d.c1, a2_x, a2_y);
                force_col_or_row(d.a1, c2_x, c2_y);
                // Nachbarschaften berücksichtigen
                for(i=0;i<ALEN;i++) {
                        if(!c[d.c1].p[a2_x][i]) // c1 hier nicht möglich
                                disable(d.a1, c2_x, i); // A1 disablen
                        else if(!c[d.a1].p[c2_x][i]) // a1 hier nicht möglich
                                disable(d.c1, a2_x, i); // C2 disablen
                }
                if(a2_x == R(c2_x-1)) { // eventuell Sonderfall in Zeile
                        for(i=0;i<ALEN;i++) {
                                if(!c[d.a1].p[i][a2_y]) // a1 hier nicht möglich
                                        disable(d.c1, R(i + 1), a2_y);  // C1 disablen
                                else if(!c[d.c1].p[i][a2_y]) // c1 hier nicht möglich
                                        disable(d.a1, R(i - 1), a2_y); // a1 disablen
                        }
                }
                return 0;
        }
        // a1, c2 gesetzt *******************************************************************
        if(a1_set && c2_set) {
                if(d.a1 == d.c2) { // Sonderfall "3-Senkrecht" oder "3-waagerecht"
                        force_row_or_pos(d.c1, a1_y, a1_x, R(a1_y-1));
                        force_col_or_pos(d.c1, a1_x, R(a1_x+1), a1_y);
                        force_row_or_pos(d.a2, a1_y, a1_x, R(a1_y+1));
                        force_col_or_pos(d.a2, a1_x, R(a1_x-1), a1_y);
                        if(!c[d.a2].p[R(a1_x-1)][a1_y])
                                disable(d.c1, R(a1_x+1), a1_y);
                        else if(!c[d.c1].p[R(a1_x+1)][a1_y])
                                disable(d.a2, R(a1_x-1), a1_y);
                        if(!c[d.a2].p[a1_x][R(a1_y-1)])
                                disable(d.c1, a1_x, R(a1_y+1));
                        else if(!c[d.c1].p[a1_x][R(a1_y+1)])
                                disable(d.a2, a1_x, R(a1_y-1));

                        if(c[d.a2].p[R(a1_x-1)][a1_y]) { // waagerecht geht! senkrecht nicht? dann deterministisch
                                if(c[d.a2].p[a1_x][R(a1_y+1)]) // waagerecht und senkrecht gehen, keine Info
                                        return 0;
                                else { //waagerecht geht, senkrecht nicht --> deterministisch
                                        set(d.a2, R(a1_x-1), a1_y);
                                        set(d.c1, R(a1_x+1), a1_y);
                                }
                        }
                        else {
                                if(c[d.a2].p[a1_x][R(a1_y+1)]) {// waagerecht gehtnicht, senkrecht geht, -->deterministisch
                                        set(d.a2, a1_x, R(a1_y+1));
                                        set(d.c1, a1_x, R(a1_y-1));
                                }
                                else //waagerecht geht nicht, senkrecht nicht --> Widerspruch
                                        throw playfair_backthrow();
                        }
                        return 0;
                }
                if(a1_y == c2_y) { // Sonderfall, alle in einer Reihe
                        set(d.c1, R(a1_x + 1), a1_y);
                        set(d.a2, R(c2_x - 1), a1_y);
                        return 0;
                }
                // Standardfall
                if(a1_x != c2_x)
                        throw playfair_backthrow();
                force_row_or_pos(d.c1, a1_y, a1_x, R(a1_y - 1));
                force_row_or_pos(d.a2, c2_y, c2_x, R(c2_y + 1));
                // Nachbarschaften Rechteck
                for(i=0;i<ALEN;i++) {
                        if(!c[d.c1].p[i][a1_y]) // c1 hier nicht möglich
                                disable(d.a2, i, c2_y); // a2 disablen
                        else if(!c[d.a2].p[i][c2_y]) // a2 hier nicht möglich
                                disable(d.c1, i, a1_y); // c1 disablen
                }
                // eventuell Sonderfall Spalte
                if(!c[d.c1].p[a1_x][R(a1_y-1)]) // c1 hier nicht möglich
                        disable(d.a2, a1_x, R(c2_y+1)); // a2 disablen
                else if(!c[d.a2].p[a1_x][R(c2_y+1)]) // a2 hier nicht möglich
                        disable(d.c1, a1_x, R(a1_y-1)); // c1 disablen
                return 0;
        }
        // a2, c1 gesetzt ********************************************************************
        if(a2_set && c1_set) {
                if(d.a2 == d.c1) { // Sonderfall "3-Senkrecht" oder "3-waagerecht"
                        force_row_or_pos(d.c2, a2_y, a2_x, R(a2_y-1));
                        force_col_or_pos(d.c2, a2_x, R(a2_x+1), a2_y);
                        force_row_or_pos(d.a1, a2_y, a2_x, R(a2_y+1));
                        force_col_or_pos(d.a1, a2_x, R(a2_x-1), a2_y);
                        if(!c[d.a1].p[R(a2_x-1)][a2_y])
                                disable(d.c2, R(a2_x+1), a2_y);
                        else if(!c[d.c2].p[R(a2_x+1)][a2_y])
                                disable(d.a1, R(a2_x-1), a2_y);
                        if(!c[d.a1].p[a2_x][R(a2_y-1)])
                                disable(d.c2, a2_x, R(a2_y+1));
                        else if(!c[d.c2].p[a2_x][R(a2_y+1)])
                                disable(d.a1, a2_x, R(a2_y-1));

                        if(c[d.a1].p[R(a2_x-1)][a2_y]) { // waagerecht geht! senkrecht nicht? dann deterministisch
                                if(c[d.a1].p[a2_x][R(a2_y+1)]) // waagerecht und senkrecht gehen, keine Info
                                        return 0;
                                else { //waagerecht geht, senkrecht nicht --> deterministisch
                                        set(d.a1, R(a2_x-1), a2_y);
                                        set(d.c2, R(a2_x+1), a2_y);
                                }
                        }
                        else {
                                if(c[d.a1].p[a2_x][R(a2_y+1)]) {// waagerecht geht nicht, senkrecht geht, -->deterministisch
                                        set(d.a1, a2_x, R(a2_y+1));
                                        set(d.c2, a2_x, R(a2_y-1));
                                }
                                else //waagerecht geht nicht, senkrecht nicht --> Widerspruch
                                        throw playfair_backthrow();
                        }

                        return 0;
                }

                if(a2_y == c1_y) { // Sonderfall, alle in einer Reihe
                        set(d.c2, R(a2_x + 1), a2_y);
                        set(d.a1, R(c1_x - 1), c1_y);
                        return 0;
                }
                // Standardfall
                if(a2_x != c1_x)
                        throw playfair_backthrow();
                force_row_or_pos(d.c2, a2_y, a2_x, R(a2_y - 1));
                force_row_or_pos(d.a1, c1_y, c1_x, R(c1_y + 1));
                // Nachbarschaften im Rechteck testen
                for(i=0;i<ALEN;i++) {
                        if(!c[d.c2].p[i][a2_y]) // c2 hier nicht möglich
                                disable(d.a1, i, c1_y); // a1 disablen
                        else if(!c[d.a1].p[i][c1_y]) // a1 hier nicht möglich
                                disable(d.c2, i, a2_y); // c2 disablen
                }
                // eventueller Sonderfall alle in einer Spalte
                if(!c[d.c2].p[a2_x][R(a2_y-1)]) // c2 hier nicht möglich
                        disable(d.a1, a2_x, R(c1_y+1)); // a1 disablen
                else if(!c[d.a1].p[a2_x][R(c1_y+1)]) // a1 hier nicht möglich
                        disable(d.c2, a2_x, R(a2_y-1)); // c2 disablen
                return 0;
        }
        // a1 gesetzt
        if(a1_set) {
                force_row_or_pos(d.c1, a1_y, a1_x, R(a1_y-1));
                force_col_or_row(d.c2, a1_x, a1_y);
                return 0;
        }
        // a2 gesetzt
        if(a2_set) {
                force_row_or_pos(d.c2, a2_y, a2_x, R(a2_y-1));
                force_col_or_row(d.c1, a2_x, a2_y);
                return 0;
        }
        // c1 gesetzt
        if(c1_set) {
                force_row_or_pos(d.a1, c1_y, c1_x, R(c1_y+1));
                force_col_or_row(d.a2, c1_x, c1_y);
                return 0;
        }
        // c2 gesetzt
        if(c2_set) {
                force_row_or_pos(d.a2, c2_y, c2_x, R(c2_y+1));
                force_col_or_row(d.a1, c2_x, c2_y);
                return 0;
        }
        return 0;
}

void playfair_backtrace::read(char *pname, char *cname)
{
        int i;
        l.read(pname, cname);

        for(i=0;i<l.n;i++) {
                a[0].c[l.d[i].a1].freq++;
                a[0].c[l.d[i].a2].freq++;
                a[0].c[l.d[i].c1].freq++;
                a[0].c[l.d[i].c2].freq++;
        }
}

void playfair_backtrace::memread(char *pstr, char *cstr, int plen, int clen)
{
        int i;
        l.memread(pstr, cstr, plen, clen);

        for(i=0;i<l.n;i++) {
                a[0].c[l.d[i].a1].freq++;
                a[0].c[l.d[i].a2].freq++;
                a[0].c[l.d[i].c1].freq++;
                a[0].c[l.d[i].c2].freq++;
        }
}

int playfair_data::is_in(char c)
{
        if(c == a1) return 1;
        if(c == a2) return 1;
        if(c == c1) return 1;
        if(c == c2) return 1;
        return 0;
}

playfair_liste::playfair_liste( )
{
		my_matrixsize = -1;
        n=0;
        d= NULL;
}

playfair_liste::init( int msize )
{
	my_matrixsize = msize;
        n=0;
        d= NULL;
}

playfair_liste::~playfair_liste(void)
{
        if(d) delete[n+2] d;
}

playfair_liste::playfair_liste(int msize, int l)
{
		my_matrixsize = msize;
        n = l;
        d = new playfair_data[l+2];
}

void playfair_liste::read(char *pname, char *cname)
{
        FILE *fp, *fc;
        char p[2], c[2];
        int l;

        fp = fopen(pname,"rb");
        fc = fopen(cname,"rb");

        fseek(fp, 0, SEEK_END);
        n = ftell(fp)/2;
        fseek(fp, 0, SEEK_SET);

        if(d) delete[] d;
        d = new playfair_data[n+2];

        l = 0;
        do {
                fread(p, 1, 2, fp);
                if(p[0] > 'J') p[0]--;
                if(p[1] > 'J') p[1]--;
                fread(c, 1, 2, fc);
                if(c[0] > 'J') c[0]--;
                if(c[1] > 'J') c[1]--;
                d[l].a1 = p[0]-'A';
                d[l].a2 = p[1]-'A';
                d[l].c1 = c[0]-'A';
                d[l].c2 = c[1]-'A';
                l++;
        } while(!feof(fp));
        fclose(fp);
        fclose(fc);
}

void playfair_liste::memread(char *pstr, char *cstr, int plen, int clen)
{
//	char pc; int pi;
//	pc = 'A'; pi = C2I(pc);
//	pc = 'I'; pi = C2I(pc);
//	pc = 'J'; pi = C2I(pc);
//	pc = 'K'; pi = C2I(pc);
//	pc = 'Z'; pi = C2I(pc);
//	pc = '0'; pi = C2I(pc);
//	pc = '1'; pi = C2I(pc);
//	pc = '9'; pi = C2I(pc);
//	pc = 'A'; pi = C2I(pc); pc = I2C(pi);
//	pc = 'Z'; pi = C2I(pc); pc = I2C(pi);
//	pc = '0'; pi = C2I(pc); pc = I2C(pi);
//	pc = '1'; pi = C2I(pc); pc = I2C(pi);
//	pc = '9'; pi = C2I(pc); pc = I2C(pi);
	int l;

	n = ((plen<clen)? plen : clen) / 2;

	if(d) delete[] d;
	d = new playfair_data[n+2];

	l = 0;
	while (l<n) {
		d[l].a1 = C2I(pstr[2*l]);
		d[l].a2 = C2I(pstr[2*l+1]);
		d[l].c1 = C2I(cstr[2*l]);
		d[l].c2 = C2I(cstr[2*l+1]);
		l++;
	}
}


///////////////////////////////////////////////////////////////////////////////////
// Analyse-Versuch von Gauweiler
// Funktionen zur Matrix-Erzeugung. Vorausgesetzt wird ein gültiger Buchstabengraph
bool Playfair::AnaLg_LookPlaceFirst(AnaLg_Look thetype, int& x, int& y, int no)
{
	assert (no>=0);
	assert (no<mysize);
	switch (thetype) {
	case AnaLg_matrix:
		x=0; y=-1;
		break;
	case AnaLg_row:
		y=no; x=-1;
		break;
	case AnaLg_col:
		x=no; y=-1;
		break;
	}
	return AnaLg_LookPlaceNext(thetype, x, y, no);
}
bool Playfair::AnaLg_LookPlaceNext(AnaLg_Look thetype, int& x, int& y, int no)
{
	assert (no>=0);
	assert (no<mysize);

	int i0=x, j0=y, im=mysize, jm=mysize;
	switch (thetype) {
	case AnaLg_matrix:
		j0++;
		break;
	case AnaLg_row:
		j0=no; jm=no+1; i0++;
		break;
	case AnaLg_col:
		i0=no; im=no+1; j0++;
		break;
	}

	for (int i=i0; i<im; i++)
		for (int j=j0; j<jm; j++)
			if (my_matrix->getElement(i,j) == myAlphabet->getNullElement()) {
				x=i; y=j; return (true);
			}
	return (false);
}

bool Playfair::AnaLg_InsertLetter (playfair_letter *theLetter, int theIndex, int x, int y)
// falls Buchstabe passend eingefügt wird, gib true zurück
{
	assert ((x>=0)&&(x<mysize));
	assert ((y>=0)&&(y<mysize));
	assert (theLetter);

	if (myAlphabet->getNullElement() == theLetter)
		return false;
	if (myAlphabet->getNullElement() != getLetterOfMatrix(x,y))
		return (getLetterOfMatrix(x,y) == theLetter);
	if (myLetterlist->getVisited(theIndex))
		// keine doppelten Einträge zulassen
		return false;
	setElMatrix (theLetter, x, y);
	myLetterlist->setVisited(theIndex, true);

	// ...

	if (false) {
		setElMatrix (myAlphabet->getNullElement(), x, y);
		myLetterlist->setVisited(theIndex, false);
		return false;
	}

	return true;
}
bool Playfair::AnaLg_RemoveLetter (playfair_letter *theLetter, int theIndex, int x, int y)
{
	assert (getLetterOfMatrix(x,y) == myLetterlist->getLetter(theIndex));
	setElMatrix (myAlphabet->getNullElement(), x, y);
	myLetterlist->setVisited(theIndex, false);
	return false;
}

/*
  forall buchstaben
    setze die Nachbarn -> evtl. Konflikte falls schon andere Nachbarn gesetzt
	setze potentielle Nachbarn
		-> Konflikte falls andere Nachbarn eingesetzt, 
		-> backtracking (Nachbarn tauschen)
	forall sicher in der Zeile
	  suche eine freie Position und setze ein
		-> Konflikt, wenn kein Platz frei
		-> backtracking (nächste Platz suchen)
	forall in Zeile oder drüber, bzw drunter
	  analog
	forall in der Spalte oder ZeileoderSpalte
	  analog
*/

bool Playfair::AnaLg_RekLetter (int theIndex, char *stipulation, int len)
{
	playfair_letter *pflet;
	bool isLsgFound = false;
	bool isInserted = false;
	int x=0, y=0;
	int *xp=&x;
	char debugstr[6*40];

	if ((theIndex < myLetterlist->getLen()) && myLetterlist->getLetter(theIndex)->getWeight()) {
		//bin noch im ersten Durchlauf
		if (!AnaLg_LookPlaceFirst(AnaLg_matrix, x, y)) {
			assert (0); // ein Platz muß noch frei sein!
			return false;
		}
		do {
			isInserted = AnaLg_InsertLetter (myLetterlist->getLetter(theIndex), theIndex, x, y);
					// die erste freie Stelle war InsertLetter nicht genehm, also suchen wir weiter
		} while (!isInserted && (AnaLg_LookPlaceNext(AnaLg_matrix, x, y)));
		if (!isInserted)
			return false;

		isLsgFound = AnaLg_RekLetter (theIndex+1, stipulation, len);

		while (!isLsgFound) {
			isInserted = AnaLg_RemoveLetter (myLetterlist->getLetter(theIndex), theIndex, x, y);
			while (!isInserted && (AnaLg_LookPlaceNext(AnaLg_matrix, x, y))) {
				isInserted = AnaLg_InsertLetter (myLetterlist->getLetter(theIndex), theIndex, x, y);
			}
			if (!isInserted)
				return false;

			isLsgFound = AnaLg_RekLetter (theIndex+1, stipulation, len);
		}

		return (isLsgFound);

	} else {
		// am Ende der relevanten Buchstaben oder der ganzen Liste, folgt der Test auf die Vorgabe
		my_matrix->print (debugstr);
//		DbgOutString (debugfile, debugstr);
		fprintf (debugfile, debugstr);
		if (DoCipher (false, 1, 300, stipulation, len)) {
			fclose (debugfile);
			return (true);
		}
		return false;
	}
} // Playfair::AnaLg_RekLetter


/*	for (j=0; j < myLetterlist-> getLen(); j++) {
	  for (i=j; i < myLetterlist-> getLen(); i++) {
		// durchlaufe alle Buchstaben der Liste
		if (!myLetterlist->getVisited(i) && myLetterlist->getLetter(i)->getWeight()) {
			// falls Buchstabe noch nicht i.d. Matrix eingetragen
			if (AnaLg_LookPlaceFirst(AnaLg_matrix, x, y))
				do {
					pflet = myLetterlist->getLetter(i);
					//einsetzen
					//ausprobieren
					//löschen
					isok = (AnaLg_InsertLetter (pflet, i, x, y));
					my_matrix->print (debugstr);
//					DbgOutString (debugfile, debugstr);
					fprintf (debugfile, debugstr);
			if (DoCipher (1, 300, stipulation, len)) {
				fclose (debugfile);
				return (true);
			} else {
//				setElMatrix (myAlphabet->getNullElement(), x, y);
//				myLetterlist->setVisited(i, false);
			}

				} while (!isok && (AnaLg_LookPlaceNext(AnaLg_matrix, x, y)));
			else {// kein Platz mehr in der Matrix frei
//				fclose (debugfile);
//				return false;
			}
			// zum Ende ein Check, ob schon alles stimmt
//			if (DoCipher (1, 300, stipulation, len)) {
//				fclose (debugfile);
//				return (true);
//			}
		}
		my_matrix->findElement(myLetterlist->getLetter(i), x, y);
		if (x>=0)	setElMatrix (myAlphabet->getNullElement(), x, y);
//		setElMatrix (myAlphabet->getNullElement(), x, y);
		myLetterlist->setVisited(i, false);
	  }
//		my_matrix->findElement(myLetterlist->getLetter(j), x, y);
//		if (x>=0)	setElMatrix (myAlphabet->getNullElement(), x, y);
//		myLetterlist->setVisited(j, false);
	}
	*/

bool Playfair::CreateMatrixfromLettergraph(char *stipulation, int len)
// stipulation enthält die Klartextvorgabe. Sofern eine versuchte Entschlüsselung
// der Vorlage entspricht, ist eine (erstmal) gültige Matrix gefunden.
{
//	playfair_letter *pflet;
//	int i, j, k;
	int x=0,y=0;
	bool isok = false;
	char debugstr[6*40];
/*
	debugfile = fopen( "debugplayfair.txt", "w" );
*/
	myLetterlist->sortViaWeight();
	my_matrix->clear(myAlphabet->getNullElement());
	myLetterlist->reset_visited();
/*
	myLetterlist->print(debugstr);
	fprintf (debugfile, debugstr);
*/
	AnaLg_RekLetter (0, stipulation, len);

/*	for (j=0; j < myLetterlist-> getLen(); j++) {
	  for (i=j; i < myLetterlist-> getLen(); i++) {
		// durchlaufe alle Buchstaben der Liste
		if (!myLetterlist->getVisited(i) && myLetterlist->getLetter(i)->getWeight()) {
			// falls Buchstabe noch nicht i.d. Matrix eingetragen
			if (AnaLg_LookPlaceFirst(AnaLg_matrix, x, y))
				do {
					pflet = myLetterlist->getLetter(i);
					//einsetzen
					//ausprobieren
					//löschen
					isok = (AnaLg_InsertLetter (pflet, i, x, y));
					my_matrix->print (debugstr);
//					DbgOutString (debugfile, debugstr);
					fprintf (debugfile, debugstr);
			if (DoCipher (1, 300, stipulation, len)) {
				fclose (debugfile);
				return (true);
			} else {
//				setElMatrix (myAlphabet->getNullElement(), x, y);
//				myLetterlist->setVisited(i, false);
			}

				} while (!isok && (AnaLg_LookPlaceNext(AnaLg_matrix, x, y)));
			else {// kein Platz mehr in der Matrix frei
//				fclose (debugfile);
//				return false;
			}
			// zum Ende ein Check, ob schon alles stimmt
//			if (DoCipher (1, 300, stipulation, len)) {
//				fclose (debugfile);
//				return (true);
//			}
		}
		my_matrix->findElement(myLetterlist->getLetter(i), x, y);
		if (x>=0)	setElMatrix (myAlphabet->getNullElement(), x, y);
//		setElMatrix (myAlphabet->getNullElement(), x, y);
		myLetterlist->setVisited(i, false);
	  }
//		my_matrix->findElement(myLetterlist->getLetter(j), x, y);
//		if (x>=0)	setElMatrix (myAlphabet->getNullElement(), x, y);
//		myLetterlist->setVisited(j, false);
	}
	*/
/*	for (i=0; i < myLetterlist-> getLen(); i++) {
		// durchlaufe alle Buchstaben der Liste
		if (!myLetterlist->getVisited(i) && myLetterlist->getLetter(i)->getWeight()) {
			// falls Buchstabe noch nicht i.d. Matrix eingetragen
			if (AnaLg_LookPlaceFirst(AnaLg_matrix, x, y))
				do {
					pflet = myLetterlist->getLetter(i);
					isok = (AnaLg_InsertLetter (pflet, i, x, y));
				} while (!isok && (AnaLg_LookPlaceNext(AnaLg_matrix, x, y)));
					my_matrix->print (debugstr);
//					DbgOutString (debugfile, debugstr);
					fprintf (debugfile, debugstr);
			else {// kein Platz mehr in der Matrix frei
//				fclose (debugfile);
//				return false;
			}
			// zum Ende ein Check, ob beim ersten Einsetzen schon alles stimmt
			if (DoCipher (1, 300, stipulation, len)) {
				fclose (debugfile);
				return (true);
			}
		}
	}
	// jetzt werden alle folgenden Matrix-Möglichkeiten ausgelotet.
	//for (j=0; j < myLetterlist-> getLen(); j++) {
	  for (i=myLetterlist->getLen()-1; i>0; i--) {
		// durchlaufe alle Buchstaben der Liste, aber jetzt von hinten
		if (myLetterlist->getLetter(i)->getWeight()) {
			// zum verschieben, erstmal löschen
			my_matrix->findElement(myLetterlist->getLetter(i), x, y);
			setElMatrix (myAlphabet->getNullElement(), x, y);
			myLetterlist->setVisited(i, false);
			// zum verschieben, neuen freien Platz suchen
			isok = false;
			while (!isok && (AnaLg_LookPlaceNext(AnaLg_matrix, x, y))) {
				pflet = myLetterlist->getLetter(i);
				isok = (AnaLg_InsertLetter (pflet, i, x, y));
			}
			// Test, ob Bedingung erfüllt

			if (!isok) {// kein Platz mehr in der Matrix frei
				assert (0);
//				fclose (debugfile);
//				return false;
			}

			/*			for (k=i+1; k < myLetterlist-> getLen(); k++) {
				//lösche alle untergebenen Buchst., d.h. alle mit kleinerm Gewicht
				my_matrix->findElement(myLetterlist->getLetter(k), x, y);
				if (x>=0)	setElMatrix (myAlphabet->getNullElement(), x, y);
				myLetterlist->setVisited(k, false);
			}
**
			// zum Ende ein Check, ob schon alles stimmt
//			if (DoCipher (1, 300, stipulation, len)) {
//				fclose (debugfile);
//				return (true);
//			}
		}
		my_matrix->findElement(myLetterlist->getLetter(i), x, y);
		if (x>=0)	setElMatrix (myAlphabet->getNullElement(), x, y);
//		setElMatrix (myAlphabet->getNullElement(), x, y);
		myLetterlist->setVisited(i, false);
	  }
//		my_matrix->findElement(myLetterlist->getLetter(j), x, y);
//		if (x>=0)	setElMatrix (myAlphabet->getNullElement(), x, y);
//		myLetterlist->setVisited(j, false);
	}
*/

	fclose (debugfile);

	// jetzt sind alle Möglichkeiten durchprobiert
	return (DoCipher (false, 1, 300, stipulation, len));
} // CreateMatrixfromLettergraph


/* ab hier ist alles veraltet
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

	for(i=0;i<t;i++)                   //halbe einträge einfügen - DER EINZIGE ORIGINAL KOMMENTAR
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

	for(i=0;i<t;i++)                              //zeilen anpassen - UPS, NOCH EINER
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
	for(i=0;i<oldm->d;i++)                          //eintragen welche zeichen in der gleichen Zeilen stehen könnten - DOCH SCHON DREI
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
		for(f=i+1;f<36;f++)                        // sammeln der Zeileninfo - NOCH EINER
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
			if(tp==1)                                //nichts falls nur ein Zeichen gleich - NR 6
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
*/