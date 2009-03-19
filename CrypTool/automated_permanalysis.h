/*********************************************************************

Copyright (C) CrypTool project contributors, 1998-2009

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

CrypTool is distributed in the hope that it will be useful, but WITHOUT
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

TODO Cryptovision 

**********************************************************************/


#pragma once
#include "stdafx.h"

enum direction { row_dir = 0, col_dir = 1, both_dir = 2 };

struct perm_table {
	char  **table;
	int	permSize;
	int	colSize;
	int dir; 

	perm_table();
	~perm_table();
	void remove();
	int  realloc( int FILESIZE, int PERMSIZE );
	int  readFile( ifstream &fin, int DIR );
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
	ifstream     plainFile, cipherFile;
	int		     fileSize;
	int			 psUpperLimit, psLowerLimit;
	int    	     rangePlain, rangeCipher, rangePerm;
	permkey     *keyList;
	perm_table   ptPlain, ptCipher;

	int get_file_size(ifstream &fstrm, int &filesize);
	int read_file_in_table(ifstream &fstrm, perm_table &pt, int permSize, int DIR);
	int get_key(int permSize, int it_perm);
	int analyse(int permSize, int it_plain, int it_perm, int it_cipher);
public:
	automated_permanalysis();
	~automated_permanalysis();
	int setFilenames( const char *fn_plain, const char *fn_cipher );
	int setAnalyseParam( int ps_lowerLimit, int ps_upperLimit,
						 int range_plain, int range_perm, int range_cipher); 
	const permkey *getKeyList() { return keyList; }
	int iterate_key_param();
};