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

// TODO Cryptovision

#pragma once
#include "stdafx.h"
#define CHR_UNDEFINED 0x0100
#define TABLE_ERROR   0x0101


enum direction { row_dir = 0, col_dir = 1, both_dir = 2 };

class perm_table {

public:
	char		   *data;
	unsigned int    size;
	unsigned int    refSize;

	unsigned int    permSize;
	unsigned int   *ofsList;

	int				readDir;
	int				permDir;

public: 
	perm_table();
	~perm_table();

	int  loadFile(const char *filename, int TEXTMODE, unsigned int REFSIZE = 0);
	void setParam(int READDIR, int PERMDIR, unsigned int PERMSIZE, int ofsKnown);
	unsigned int  getSize() { return refSize; }

	int  get		(int r, int c);
	int  get		(unsigned int c);
	int  findStr (const int *str, int *permTable);
	void buildStr(int *str, unsigned int ofs, unsigned int lastStep);
};

struct permkey {
	permkey *next;
	int  permSize;
	int *permKey;
	int  dirPlain, dirCipher, dirPerm;
	permkey(int *perm_key, int perm_size, 
		int dir_plain, int dir_cipher, int dir_perm, permkey *nxt );
	~permkey();
};


class automated_permanalysis {
	int			 psUpperLimit, psLowerLimit;
	int    	     rangePlain, rangeCipher, rangePerm, refSize;
	permkey     *keyList;
	perm_table   ptPlain, ptCipher;

	int get_key(unsigned int permSize, int it_perm);
	int analyse(unsigned int permSize, int it_plain, int it_perm, int it_cipher);
public:
	automated_permanalysis();
	~automated_permanalysis();
	int setFilenames( const char *fn_plain, const char *fn_cipher, int TEXTMODE, int refPlain = 0 );
	int setAnalyseParam( int ps_lowerLimit, int ps_upperLimit,
						 int range_plain, int range_perm, int range_cipher); 
	const permkey *getKeyList() { return keyList; }
	int iterate_key_param();
};