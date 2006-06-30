/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/



#pragma once

#include "afxcoll.h"

//library for filestreams
#include <fstream>
//library for standardIO
#include <iostream>
//library for c standard functions
#include <cstdlib>
//library for vectors
#include <vector>
//library for queues
#include <queue>
//library for iterators
#include <iterator>
#include <string>


//queue-definition for the permutation matrix
typedef std::vector<char> pmvector;
	
//define elements for the list of the permutation matrix
struct pmlistelem {
		char passCharacter;
		int position;
		pmvector column;
};

//define elements for the list of the permutation matrix
struct cblistelem {
		int index;
		float frequency;
};

//list definition for the permutation matrix
typedef std::vector<pmlistelem> pmlist;
typedef std::vector<cblistelem> cblist;

class adfgvx {

private:
	char codeMatrix[6][6];
	char compMatrix[36][2];
	char subChars[2];
	pmlist permMatrix;
	pmlist::iterator permMatrixIterator;
	int adfgvx::valueOf (char ch);
	CString lastPasswordFound;
	
public:

	cblist countBigrammVector;
	void adfgvx::countBigram();
	float countMatrix[6][6];

	adfgvx();

	int encrypt(const char* ifile, const char* ofile, const char* pass, int blockSizeStage2, bool newLineStage2, bool printStage1, int blockSizeStage1, bool newLineStage1, const char* stage1);
	int decrypt(const char* ifile, const char* ofile, const char* pass, int blockSizeStage2, bool newLineStage2, bool printStage1, int blockSizeStage1, bool newLineStage1, const char* stage1);

	friend bool alphaSort (pmlistelem l1, pmlistelem l2);
	friend bool numberSort (pmlistelem l1, pmlistelem l2);

	std::string plaintext;
	std::string ciphertext;
	std::string stage1String;
	
	void setMatrix(int row, int col, char c) ;
	char getMatrix(int row, int col) ;
	int checkMatrix();

	char* substitute(char input);
	char resubstitute(char c1, char c2);
	
	void substitution(const char* pass);
	void resubstitution();
	
	void permutation();
	void repermutation(const char* pass);
	
	void readPlaintext(const char* ifile);
	void writePlaintext(const char* ofile);
	int readCiphertext(const char* ifile);
	void writeCiphertext(const char* ofile, int blockSizeStage2, bool newLineStage2);
	void writeStage1(const char* stage1, int blockSizeStage1, bool newLineStage1);

	//***** ANALYSIS FUNCTIONS *****//

	CString adfgvx::nextPassword(int minlength, int maxlength, CString start);
	bool adfgvx::goodenough(bool forcePassword);
	void adfgvx::ForcePassword(CString pwd);
	
	//***** INPUT VALIDATION *****//
	int adfgvx::CheckPassword(int minLength, int maxLength, CString password);
	CString adfgvx::CleansePassword(int errorCode, CString password);
	CString adfgvx::LettersToNumbers(CString password);
	int adfgvx::CheckStringBox(CString input);
};

bool alphaSort  (pmlistelem l1, pmlistelem l2);
bool numberSort (pmlistelem l1, pmlistelem l2);
bool frequencySort (cblistelem l1, cblistelem l2);