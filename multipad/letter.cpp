//////////////////////////////////////////////////////////////////
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// created 26.6.01 by Thomas Gauweiler (FZI, Karlsruhe)
//////////////////////////////////////////////////////////////////
// letter.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "assert.h"
#include "string.h"
#include "multipad.h"

#include "letter.h"

//////////////////////////////////////////////////////////////////

/*alphabet::alphabet() : my_letters(NULL), my_isoVharset(NULL)
{
}*/

alphabet::~alphabet()
{
//	assert (my_letters);
//	assert (my_validletters);
	if (my_letters) delete[] my_letters;
//testweise	delete[] my_validletters;
}

alphabet::alphabet(char lower_letter/* = A*/, char upper_letter/* = Z*/, int the_max_count/* = 128*/)
{
	my_max_count = the_max_count;
	my_letters = new letter[my_max_count];
	my_validletters = new bool[my_max_count];

	for (int i=0; i<my_max_count; i++)
		my_validletters[i] = false;

	my_count = 0;
	for (char c=lower_letter; (c<=upper_letter) && (my_count<=my_max_count); c++) {
		my_letters[my_count].setValue(c);
		my_validletters[my_count] = true;
		my_count++;
	}
}

letter alphabet::addLetter(char let)
{
	letter ret_let;
	if ((int)&(ret_let = getLetter(let)) != NULL)
		return ret_let;

	if (my_count<my_max_count) {
		my_letters[my_count].setValue(let);
		my_validletters[my_count] = true;
		my_count++;
		return (my_letters[my_count-1]);
	}

	return NULL;
}

void alphabet::delLetter(char let)
{
	for (int i=0; i<my_max_count; i++)
		if ((my_validletters[i]) && (my_letters[i].getValue()==let)) {
			my_letters[i].setValue(-1);
			my_validletters[i] = false;
		}
}

void alphabet::delLetter(letter let)
{
	for (int i=0; i<my_max_count; i++)
		if ((my_validletters[i]) && (my_letters[i]==let)) {
			my_letters[i].setValue(-1);
			my_validletters[i] = false;
		}
}

letter alphabet::getLetter(char let, int isDigitsOk, int isPlayfairTypical)
{
	let = replaceInvalidLetter (let, isDigitsOk, isPlayfairTypical);
	if (let=='\0') 	return NULL;
	for (int i=0; i<my_max_count; i++)
		if ((my_validletters[i]) && ((my_letters[i].getValue()==let)||(my_letters[i].getValue()==toupper(let))))
			return my_letters[i];
	return NULL;
}

char alphabet::replaceInvalidLetter(char let, int isDigitsOk, int isPlayfairTypical)
{
	if ((let>='a') && (let<='z')) let = let - 'a' + 'A';  // a-z in Großbuchstaben wandeln;
	if ((let == 'J') && isPlayfairTypical) return ('I');
	if ((let>='A') && (let<='Z')) return (let);
	if ((let>='0') && (let<='9') && isDigitsOk && !isPlayfairTypical) return (let);

	if ((let>='à') && (let<='ý')) let = let - 'à' + 'À';  // in Großbuchstaben wandeln;
	switch (let) { // jetzt Sonderzeichen wandeln
	case 'À': case 'Á': case 'Â': case 'Ã': case 'Ä': case 'Å': case 'Æ': case '@':
		return ('A');
	case 'Ç': case '¢':
		return ('C');
	case 'Ð':
		return ('D');
	case 'È': case 'É': case 'Ê': case 'Ë': case '€':
		return ('E');
	case 'Ì': case 'Í': case 'Î': case 'Ï':
		return ('I');
	case 'Ñ':
		return ('N');
	case 'Ò': case 'Ó': case 'Ô': case 'Õ':  case 'Ö':   case 'Ø': case 'Œ':
		return ('O');
	case 'Š':
		return ('S');
	case 'Ù': case 'Ú': case 'Û': case 'Ü':
		return ('U');
	case 'ÿ': case 'Ÿ': case '¥': case 'Ý':
		return ('Y');
	case 'Ž':
		return ('Z');
	}
	return '\0';
}
//////////////////////////////////////////////////////////////////

letter::letter() : my_value(-1)
{
}

letter::letter(int the_value)
{
	my_value = the_value;
}

letter::~letter()
{
	my_value = -1;
}

//////////////////////////////////////////////////////////////////


/*keymatrix::keymatrix() : my_size(5),
                        my_elements(NULL)
{
	keymatrix (5);
}*/

keymatrix::keymatrix(int the_size, letter* the_NullElement)
{
	my_size = the_size;
	my_NullElement = the_NullElement;
//	my_elements = new letter [my_size];
	my_elements = (letter **) malloc (my_size*my_size*sizeof(letter*));
	clear();
}

void keymatrix::clear(letter* the_NullElement)
{
	if (the_NullElement == NULL)
		for (int i=0; i< my_size*my_size; i++)
			my_elements[i] = my_NullElement;
	else
		for (int i=0; i< my_size*my_size; i++)
			my_elements[i] = the_NullElement;
}

keymatrix::~keymatrix()
{
	assert (my_elements);
//	delete (my_elements);
	free (my_elements); my_elements = NULL;
}

bool keymatrix::operator==(const keymatrix &other)
{
	if (my_size = other.my_size) {
	  for (int i=0; i < my_size*my_size; i++)
	    if (my_elements[i] != other.my_elements[i])
          return false;
      return true;
	}
    return false;
}

void keymatrix::setSize(int the_size)
{
	assert (my_elements);
//	delete (my_elements);
//	my_elements = new letter [my_size];
	free (my_elements);
	my_elements = (letter **) malloc (my_size*my_size*sizeof(letter*));
	for (int i=0; i< my_size*my_size; i++)
		my_elements[i] = my_NullElement;
}

letter* keymatrix::getElement(int row, int col)
{
//	if (!((col>=0)&&(col<my_size)))
//		int i=0;
	assert (my_elements!=NULL);
	assert ((col>=0)&&(col<(my_size==6?my_size:my_size+1)));
	assert ((row>=0)&&(row<(my_size==6?my_size:my_size+1)));

	if ((row>=0)&&(col>=0)&&(row<my_size)&&(col<my_size))
		return (my_elements [row*my_size+col]);
	else
		return (my_NullElement);
}

void keymatrix::setElement(letter* newLetter, int row, int col)
{
	assert (my_elements!=NULL);
	assert ((row>=0)&&(row<my_size));
	assert ((col>=0)&&(col<my_size));

	my_elements [row*my_size+col] = newLetter;
}

void keymatrix::findElement(letter* looksymbol, int &row, int &col)
{
	assert (my_elements!=NULL);

	row = -1; col = -1;
	for (int i=0; i<my_size; i++)
		for (int j=0; j<my_size; j++)
			if (looksymbol == my_elements [i*my_size+j]) {
				row = i; col = j;
				return;
			}
	return;
}

void keymatrix::print(char *s)
{
	assert (s);
	int i;

	for (i=0; i<my_size*my_size; i++)
		s[i] = my_elements [i]->getValue();
	s[i++] = '\n';
	s[i] = '\0';
	return;
}

void keymatrix::setRow(letter **newRow, int rowNo)
{
	assert (my_elements!=NULL);
	assert (newRow!=NULL);
	assert ((rowNo>=0)&&(rowNo<my_size));

	for (int i=0; i<my_size; i++)
		setElement(newRow[i], rowNo, i);
}

void keymatrix::getRow(letter **buf, int rowNo)
{
	assert (my_elements!=NULL);
	assert (buf!=NULL);
	assert ((rowNo>=0)&&(rowNo<my_size));

	for (int i=0; i<my_size; i++)
		buf[i] = getElement(rowNo, i);
}

void keymatrix::setCol(letter **newCol, int colNo)
{
	assert (my_elements!=NULL);
	assert (newCol!=NULL);
	assert (*newCol!=NULL);
	assert ((colNo>=0)&&(colNo<my_size));

	for (int i=0; i<my_size; i++)
		setElement(newCol[i], i, colNo);
}

void keymatrix::getCol(letter **buf, int colNo)
{
	assert (my_elements!=NULL);
	assert (buf!=NULL);
	assert (*buf!=NULL);
	assert ((colNo>=0)&&(colNo<my_size));

	for (int i=0; i<my_size; i++)
		buf[i] = getElement(i, colNo);
}

int keymatrix::findRow(letter *let)
{
	assert (my_elements!=NULL);
//	assert (let!=NULL);

	int i, j;
	assert (my_elements!=NULL);
	findElement (let, i, j);
	return i;
}

int keymatrix::findCol(letter *let)
{
	assert (my_elements!=NULL);
//	assert (let!=NULL);

	int i, j;
	assert (my_elements!=NULL);
	findElement (let, i, j);
	return j;
}

void keymatrix::switchRow(int k, int l)
{
	assert (my_elements!=NULL);
	assert ((k>=0)&&(k<my_size));
	assert ((l>=0)&&(l<my_size));

	letter *h;
	for (int i=0; i<my_size; i++) {
		h = getElement(k, i);
		setElement (getElement(l, i), k, i);
		setElement (h, l, i);
	}
}

void keymatrix::switchCol(int k, int l)
{
	assert (my_elements!=NULL);
	assert ((k>=0)&&(k<my_size));
	assert ((l>=0)&&(l<my_size));

	letter *h;
	for (int i=0; i<my_size; i++) {
		h = getElement(i, k);
		setElement (getElement(l, i), i, k);
		setElement (h, i, l);
	}
}

void keymatrix::rotate(int row, int col)
{
	assert (my_elements!=NULL);

	letter *h;
	int x, y, v, w;
	// normalise row and col in the range of 0.. my_size-1
	row = rangeIt(row);
	col = rangeIt(col);
	if ((row==0)&&(col==0))
		return;
	else if (row==0) {
		for (int i=0; i<my_size; i++) {
			x = i; y = 0; v = rangeIt(i-row), w = rangeIt(-col);
			h = getElement(x, y);
			while (w != 0) {
				setElement (getElement(v, w), x, y);
				x = v; y = w; v = rangeIt(x-row), w = rangeIt(y-col);
			}
			setElement(h, v, w);
		}
	} else {
		for (int i=0; i<my_size; i++) { // for all elements in the first row
			// change cyclical: element (x,y) becomes (v,w)
			x = 0; y = i; v = rangeIt(-row), w = rangeIt(i-col);
			h = getElement(x, y);
			while (v != 0) {
				setElement (getElement(v, w), x, y);
				x = v; y = w; v = rangeIt(x-row), w = rangeIt(y-col);
			}
			setElement(h, v, w);
		}
	}
}