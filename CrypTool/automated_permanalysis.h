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

//////////////////////////////////////////////////////////////////////
// virtual permutation table
class perm_table {

public:
	char		   *data;
	unsigned int    size;
	unsigned int    permSize;

	int				readDir;
	int				permDir;

public: 
	perm_table();
	~perm_table();
	int  loadFile(const char *filename, int TEXTMODE);

	void setParam(int READDIR, int PERMDIR, unsigned int PERMSIZE, int noPermutation)
	{ readDir = READDIR; permDir = PERMDIR; permSize = PERMSIZE; }
	unsigned int getSize() 
	{ return size; }
	unsigned int getSize(unsigned int ndx)
	{
		unsigned int l = size/permSize;
		if (ndx <= size % permSize) l++;
		return l;
	}

	unsigned int  get(unsigned int c)
	{ 
		ASSERT( 1<=c && c<=size ); 
		unsigned int ret = data[c-1]; 
		return ret;
	}
	int  get(unsigned int r, unsigned int c)
	{
		unsigned int x, p = size/permSize, q = size % permSize;
		if ( permDir == row_dir )
			if ( readDir == row_dir ) { x = (r <= q) ? r-1 : q; x += (r-1)*p + c; }
			else                      { x = (c-1)*permSize + r; }
		else
		{
			if ( readDir == col_dir ) { x = (c <= q) ? c-1 : q; x += (c-1)*p + r; }
			else                      { x = (r-1)*permSize + c; }
		}
		return get(x);
	}
};

///////////////////////////////////////////////////////////////////////////
// List of permutation key candidates
struct permkey {
	permkey *next;
	unsigned int  permSize;
	unsigned int *permKey;
	int  dirPlain, dirCipher, dirPerm;
	permkey(unsigned int *perm_key, unsigned int perm_size, 
		int dir_plain, int dir_cipher, int dir_perm, permkey *nxt );
	~permkey();
};

//////////////////////////////////////////////////////////////////////////
//
class automated_permanalysis {
	int			 psUpperLimit, psLowerLimit;
	int    	     rangePlain, rangeCipher, rangePerm, size;
	permkey     *keyList;
	perm_table   ptPlain, ptCipher;

	int analyse(unsigned int permSize, int it_plain, int it_perm, int it_cipher);

	int found( unsigned long t_ndx, unsigned long p_ndx, char *rem, unsigned int *pk, unsigned int extra );
	int seek_linear   ( int f, unsigned long t_ndx, unsigned long p_ndx, char *rem, unsigned int *pk );

	int found_s( unsigned long p_ndx, unsigned long ur, char *rem, unsigned int *pk, unsigned int extra );
	int seek_scattered( int f, unsigned long p_ndx, unsigned long ur,    char *rem, unsigned int *pk );

public:
	automated_permanalysis();
	~automated_permanalysis();
	int setFilenames( const char *fn_plain, const char *fn_cipher, int TEXTMODE, int refPlain = 0 );
	int setAnalyseParam( int ps_lowerLimit, int ps_upperLimit,
						 int range_plain, int range_perm, int range_cipher); 
	const permkey *getKeyList() { return keyList; }
	int iterate_key_param();
};