//////////////////////////////////////////////////////////////////
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// created 26.6.01 by Thomas Gauweiler (FZI, Karlsruhe)
//////////////////////////////////////////////////////////////////
// letter.h: Definitionsdatei (Header)
//
#include "assert.h"
#define NULLELEMENT '*'

class letter
{
public:
	letter();
	letter(int the_value);
	~letter();
	bool operator==(const letter &other)
	{
		return (my_value == other.my_value);
	}
	bool operator!=(const letter &other)
	{
		return (my_value != other.my_value);
	}
	bool operator>(const letter &other)
	{
		return (my_value > other.my_value);
	}
	bool operator<(const letter &other)
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
}; // class letter

//////////////////////////////////////////////////////////////////

class alphabet
{
public:
//        alphabet();
		alphabet(char lower_letter = 'A', char upper_letter = 'Z', int the_max_count = 128);
        ~alphabet();

        letter *getLetters() const
        {
                 return my_letters;
        }

        void setLetters(letter* &the_letters)
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
        letter addLetter(char let);
        void delLetter(char let);
        void delLetter(letter let);
        letter getLetter(char let, bool isConvert, bool isDigitsOk=1, bool isPlayfairTypical=0);
		char replaceInvalidLetter(bool isConvert, char let, bool isDigitsOk=1, bool isPlayfairTypical=0);
		bool getValidOfLetter(int no){
			return my_validletters[no];
		}
protected:
        letter* my_letters;
        short my_count;
        short my_max_count;
		bool* my_validletters;
//        char* my_isoCharset;
private:
}; // class alphabet

//////////////////////////////////////////////////////////////////

class keymatrix
{
public:
	keymatrix(int the_size, letter* the_NullElement = NULL);
	~keymatrix();
	bool operator==(const keymatrix &other);

	void clear(letter* the_NullElement = NULL);

	int getSize() const
	{
		return my_size;
	}

	void setSize(int the_size);

	letter** getElements() const
	{
		return my_elements;
	}

	letter* getElement(int row, int col);

	void setElement(letter* newLetter, int row, int col);

	void findElement(letter* looksymbol, int &row, int &col);

	void setRow(letter **newRow, int rowNo);

	void getRow(letter **buf, int rowNo);

	void setCol(letter **newCol, int colNo);

	void getCol(letter **buf, int colNo);

	int findRow(letter *let);

	int findCol(letter *let);

	void switchRow(int k, int l);

	void switchCol(int k, int l);

	int rangeIt(int k) const
	{
		return ((k<0) ? (k+(((-k)/my_size)+1)*my_size) : (k%my_size));
	}

	void rotate(int row, int col);

	void print (char *s); // String muß mind. 37 Zeichen lang sein.

	void setNullElement(letter* the_NullElement)
	{
		my_NullElement = the_NullElement;
	}

protected:

	void setElements(const letter* &the_elements)
	{
//                 my_elements = the_elements;
	}
private:

	int my_size;
	letter** my_elements;
	letter* my_NullElement;

//	keymatrix();

}; // class keymatrix
