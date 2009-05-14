/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/


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
#include "CrypToolApp.h"

#include "PlayfairStructures.h"

//////////////////////////////////////////////////////////////////

/*CPlayfairAlphabet::CPlayfairAlphabet() : my_letters(NULL), my_isoVharset(NULL)
{
}*/

CPlayfairAlphabet::~CPlayfairAlphabet()
{
//	assert (my_letters);
//	assert (my_validletters);
	if (my_letters) delete[] my_letters;
//testweise	delete[] my_validletters;
}

CPlayfairAlphabet::CPlayfairAlphabet(char lower_letter/* = A*/, char upper_letter/* = Z*/, int the_max_count/* = 128*/)
{
	my_max_count = the_max_count;
	my_letters = new CPlayfairLetter[my_max_count];
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

CPlayfairLetter CPlayfairAlphabet::addLetter(char let)
{
	CPlayfairLetter ret_let;
	if ((int)&(ret_let = getLetter(let, true)) != NULL)
		return ret_let;

	if (my_count<my_max_count) {
		my_letters[my_count].setValue(let);
		my_validletters[my_count] = true;
		my_count++;
		return (my_letters[my_count-1]);
	}

	return NULL;
}

void CPlayfairAlphabet::delLetter(char let)
{
	for (int i=0; i<my_max_count; i++)
		if ((my_validletters[i]) && (my_letters[i].getValue()==let)) {
			my_letters[i].setValue(-1);
			my_validletters[i] = false;
		}
}

void CPlayfairAlphabet::delLetter(CPlayfairLetter let)
{
	for (int i=0; i<my_max_count; i++)
		if ((my_validletters[i]) && (my_letters[i]==let)) {
			my_letters[i].setValue(-1);
			my_validletters[i] = false;
		}
}

CPlayfairLetter CPlayfairAlphabet::getLetter(char let, bool isConvert, bool isDigitsOk, bool isPlayfairTypical)
{
	let = replaceInvalidLetter (isConvert, let, isDigitsOk, isPlayfairTypical);
	if (let=='\0') 	return NULL;
	for (int i=0; i<my_max_count; i++)
		if ((my_validletters[i]) && ((my_letters[i].getValue()==let)||(my_letters[i].getValue()==MyToUpper(let))))
			return my_letters[i];
	return NULL;
}

bool CPlayfairAlphabet::myisalpha( char ch )
// prüft auf korrekte Zeichen
{
	if (my_count == 36)
	{
		return ((ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||(ch>='a'&&ch<='z'));
	} 
	else 	if (my_count == 25) {
		return (((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z'))&&(ch!='j')&&(ch!='J'));
	}
	assert (0); 
	return (false);
}

char CPlayfairAlphabet::replaceInvalidLetter(bool withConvert, char let, bool isDigitsOk, bool isPlayfairTypical)
{
	if ((let>='a') && (let<='z')) let = let - 'a' + 'A';  // a-z in Großbuchstaben wandeln;
	if ((let == 'J') && isPlayfairTypical) return ('I');
	if ((let>='A') && (let<='Z')) return (let);
	if ((let>='0') && (let<='9') && isDigitsOk && !isPlayfairTypical) return (let);

	if (!withConvert) return (let);

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

CPlayfairLetter::CPlayfairLetter() : my_value(-1)
{
}

CPlayfairLetter::CPlayfairLetter(int the_value)
{
	my_value = the_value;
}

CPlayfairLetter::~CPlayfairLetter()
{
	my_value = -1;
}

//////////////////////////////////////////////////////////////////


/*keymatrix::keymatrix() : my_size(5),
                        my_elements(NULL)
{
	keymatrix (5);
}*/

keymatrix::keymatrix(int the_size, CPlayfairLetter* the_NullElement)
{
	my_size = the_size;
	my_NullElement = the_NullElement;
//	my_elements = new CPlayfairLetter [my_size];
	my_elements = (CPlayfairLetter **) malloc (my_size*my_size*sizeof(CPlayfairLetter*));
	clear();
}

void keymatrix::clear(CPlayfairLetter* the_NullElement)
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
//	my_elements = new CPlayfairLetter [my_size];
	free (my_elements);
	my_elements = (CPlayfairLetter **) malloc (my_size*my_size*sizeof(CPlayfairLetter*));
	for (int i=0; i< my_size*my_size; i++)
		my_elements[i] = my_NullElement;
}

CPlayfairLetter* keymatrix::getElement(int row, int col)
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

void keymatrix::setElement(CPlayfairLetter* newLetter, int row, int col)
{
	assert (my_elements!=NULL);
	assert ((row>=0)&&(row<my_size));
	assert ((col>=0)&&(col<my_size));

	my_elements [row*my_size+col] = newLetter;
}

void keymatrix::findElement(CPlayfairLetter* looksymbol, int &row, int &col)
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

void keymatrix::setRow(CPlayfairLetter **newRow, int rowNo)
{
	assert (my_elements!=NULL);
	assert (newRow!=NULL);
	assert ((rowNo>=0)&&(rowNo<my_size));

	for (int i=0; i<my_size; i++)
		setElement(newRow[i], rowNo, i);
}

void keymatrix::getRow(CPlayfairLetter **buf, int rowNo)
{
	assert (my_elements!=NULL);
	assert (buf!=NULL);
	assert ((rowNo>=0)&&(rowNo<my_size));

	for (int i=0; i<my_size; i++)
		buf[i] = getElement(rowNo, i);
}

void keymatrix::setCol(CPlayfairLetter **newCol, int colNo)
{
	assert (my_elements!=NULL);
	assert (newCol!=NULL);
	assert (*newCol!=NULL);
	assert ((colNo>=0)&&(colNo<my_size));

	for (int i=0; i<my_size; i++)
		setElement(newCol[i], i, colNo);
}

void keymatrix::getCol(CPlayfairLetter **buf, int colNo)
{
	assert (my_elements!=NULL);
	assert (buf!=NULL);
	assert (*buf!=NULL);
	assert ((colNo>=0)&&(colNo<my_size));

	for (int i=0; i<my_size; i++)
		buf[i] = getElement(i, colNo);
}

int keymatrix::findRow(CPlayfairLetter *let)
{
	assert (my_elements!=NULL);
//	assert (let!=NULL);

	int i, j;
	assert (my_elements!=NULL);
	findElement (let, i, j);
	return i;
}

int keymatrix::findCol(CPlayfairLetter *let)
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

	CPlayfairLetter *h;
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

	CPlayfairLetter *h;
	for (int i=0; i<my_size; i++) {
		h = getElement(i, k);
		setElement (getElement(l, i), i, k);
		setElement (h, i, l);
	}
}

void keymatrix::rotate(int row, int col)
{
	assert (my_elements!=NULL);

	CPlayfairLetter *h;
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