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
  char m_szFrequency[36];
	int m_iHighestFrequency;

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
  void adfgvx::SetFrequencyTable(char* szFrequency, int iHighestFrequency);
	
	//***** INPUT VALIDATION *****//
	int adfgvx::CheckPassword(int minLength, int maxLength, CString password);
	CString adfgvx::CleansePassword(int errorCode, CString password);
	CString adfgvx::LettersToNumbers(CString password);
	int adfgvx::CheckStringBox(CString input);
};

bool alphaSort  (pmlistelem l1, pmlistelem l2);
bool numberSort (pmlistelem l1, pmlistelem l2);
bool frequencySort (cblistelem l1, cblistelem l2);