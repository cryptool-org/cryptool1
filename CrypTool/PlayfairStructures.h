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
// letter.h: Definitionsdatei (Header)
//
#include "assert.h"
#define NULLELEMENT '*'

class CPlayfairLetter
{
public:
	CPlayfairLetter();
	CPlayfairLetter(int the_value);
	~CPlayfairLetter();
	bool operator==(const CPlayfairLetter &other)
	{
		return (my_value == other.my_value);
	}
	bool operator!=(const CPlayfairLetter &other)
	{
		return (my_value != other.my_value);
	}
	bool operator>(const CPlayfairLetter &other)
	{
		return (my_value > other.my_value);
	}
	bool operator<(const CPlayfairLetter &other)
	{
		return (my_value < other.my_value);
	}

	int getValue() const
	{
		assert (my_value<='Z'); assert (my_value>=NULLELEMENT);

		return my_value;
	}

	void setValue(int the_value)
	{
		my_value = the_value;
	}
protected:
	int my_value;
private:
}; // class CPlayfairLetter

//////////////////////////////////////////////////////////////////

class CPlayfairAlphabet
{
public:
//        CPlayfairAlphabet();
		CPlayfairAlphabet(char lower_letter = 'A', char upper_letter = 'Z', int the_max_count = 128);
        ~CPlayfairAlphabet();

        CPlayfairLetter *getLetters() const
        {
                 return my_letters;
        }

        void setLetters(CPlayfairLetter* &the_letters)
        {
                 my_letters = the_letters;
        }

        short getCount() const
        {
                 return my_count;
        }

        void setCount(short the_count)
        {
                 my_count = the_count;
        }

        short getMaxCount() const
        {
                 return my_max_count;
        }

/*
        char* getIsoCharset() const
        {
                 return my_isoCharset;
        }

        void setIsoCharset(char* the_isoCharset)
        {
                 my_isoCharset = the_isoCharset;
        }
*/
        CPlayfairLetter addLetter(char let);
        void delLetter(char let);
        void delLetter(CPlayfairLetter let);
        CPlayfairLetter getLetter(char let, bool withConvert, bool isDigitsOk=true, bool isPlayfairTypical=false);
		bool myisalpha( char ch );
		char replaceInvalidLetter(bool withConvert, char let, bool isDigitsOk=true, bool isPlayfairTypical=false);
		bool getValidOfLetter(int no){
			return my_validletters[no];
		}
protected:
        CPlayfairLetter* my_letters;
        short my_count;
        short my_max_count;
		bool* my_validletters;
//        char* my_isoCharset;
private:
}; // class CPlayfairAlphabet

//////////////////////////////////////////////////////////////////

class keymatrix
{
public:
	keymatrix(int the_size, CPlayfairLetter* the_NullElement = NULL);
	~keymatrix();
	bool operator==(const keymatrix &other);

	void clear(CPlayfairLetter* the_NullElement = NULL);

	int getSize() const
	{
		return my_size;
	}

	void setSize(int the_size);

	CPlayfairLetter** getElements() const
	{
		return my_elements;
	}

	CPlayfairLetter* getElement(int row, int col);

	void setElement(CPlayfairLetter* newLetter, int row, int col);

	void findElement(CPlayfairLetter* looksymbol, int &row, int &col);

	void setRow(CPlayfairLetter **newRow, int rowNo);

	void getRow(CPlayfairLetter **buf, int rowNo);

	void setCol(CPlayfairLetter **newCol, int colNo);

	void getCol(CPlayfairLetter **buf, int colNo);

	int findRow(CPlayfairLetter *let);

	int findCol(CPlayfairLetter *let);

	void switchRow(int k, int l);

	void switchCol(int k, int l);

	int rangeIt(int k) const
	{
		return ((k<0) ? (k+(((-k)/my_size)+1)*my_size) : (k%my_size));
	}

	void rotate(int row, int col);

	void print (char *s); // String muß mind. 37 Zeichen lang sein.

	void setNullElement(CPlayfairLetter* the_NullElement)
	{
		my_NullElement = the_NullElement;
	}

protected:

	void setElements(const CPlayfairLetter* &the_elements)
	{
//                 my_elements = the_elements;
	}
private:

	int my_size;
	CPlayfairLetter** my_elements;
	CPlayfairLetter* my_NullElement;

//	keymatrix();

}; // class keymatrix
