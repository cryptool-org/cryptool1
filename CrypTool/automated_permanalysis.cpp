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


#include "automated_permanalysis.h"
#include "resource.h"
#include "FileTools.h"

perm_table::perm_table() :
	data(0),
	permSize(0),
	size(0),
	readDir(row_dir),
	permDir(row_dir)
{
}

int  perm_table::loadFile(const char *filename, int TEXTMODE, int REFSIZE)
{
	if ( data )
	{
		delete []data; data = 0; size = 0;
	}
	int ret = readSource( filename, data, size, TEXTMODE );
	if ( REFSIZE ) 
	{
		if ( size > REFSIZE )
			ret = -1;
		else
			refSize = REFSIZE;
	}
	else refSize = size;
	return ret;
}

perm_table::~perm_table()
{
	delete []data;
}

int  perm_table::setParam(int READDIR, int PERMDIR, int PERMSIZE) 
{ 
	readDir = READDIR; permDir = PERMDIR; permSize = PERMSIZE; 
	return 1; // FIXME 
}

int perm_table::get(int r, int c)
{
	int ndx = 0;
	int dRowCol, rc, cr;
	if ( permDir == col_dir )
	{ 
		dRowCol = col_dir; rc = r; cr = c;
	}
	else
	{	
		dRowCol = row_dir; rc = c; cr = r;
	}

	if ( readDir == dRowCol )
		ndx = (rc-1)*permSize + (cr-1);
	else
	{
		ndx = size % permSize;
		if ( ndx && cr <= ndx ) ndx = cr;
		ndx += (cr-1) * (size/permSize) + rc-1;
	}

	ASSERT( 0 <= ndx && ndx < refSize );
	return (ndx < size) ? data[ndx] : CHR_UNDEFINED;
}

int perm_table::get(int c)
{
	ASSERT( 1<=c && c<=refSize );
	return (c<=size) ? data[c-1] : CHR_UNDEFINED;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

permkey::permkey(int *perm_key, int perm_size, 
		int dir_plain, int dir_cipher, int dir_perm, permkey *nxt ) 
{
	next		= nxt;
	permSize	= perm_size;
	permKey		= perm_key;
	dirPlain	= dir_plain;
	dirCipher	= dir_cipher;
	dirPerm		= dir_perm;
}

permkey::~permkey()
{
	delete []permKey;
	// TODO
}


////////////////////////////////////////////////////////////////////////////////////////////////

automated_permanalysis::automated_permanalysis()
{
	keyList		= 0;
	refSize	= 0;
	rangePlain	= both_dir;
	rangePerm	= both_dir;
	rangeCipher = both_dir;
}

automated_permanalysis::~automated_permanalysis()
{
	while ( keyList )
	{
		permkey *delKey = keyList;
		keyList = keyList->next;
		delete delKey;
	}
}

int automated_permanalysis::setFilenames( const char *fn_plain, const char *fn_cipher, int TEXTMODE, int refPlain )
{
	if ( refPlain )
	{ // FIXME ERROR
		ptPlain.loadFile(fn_plain, TEXTMODE);
		refSize = ptPlain.getSize();
		ptCipher.loadFile(fn_cipher, TEXTMODE, refSize);
	}
	else
	{ // FIXME ERROR
		ptCipher.loadFile(fn_plain, TEXTMODE);
		refSize = ptCipher.getSize();
		ptPlain.loadFile(fn_cipher, TEXTMODE, refSize);
	}
	return 1; // FIXME 
}

int automated_permanalysis::setAnalyseParam(int ps_lowerLimit, int ps_upperLimit, int range_plain, int range_perm, int range_cipher)
{
	if (ps_upperLimit != -1 && ps_lowerLimit > ps_upperLimit)
		return IDS_PA_LIMITRANGE_ERROR;

	if (ps_lowerLimit <= 0 || ps_upperLimit == 0 || ps_upperLimit < -1)
		return IDS_PA_LIMITRANGE_ERROR;
	
	if (range_plain < 0 || range_plain > 2 || range_perm < 0 || range_perm > 2 || range_cipher < 0 || range_cipher > 2)
		return IDS_PA_DIRECTION_ERROR; //ERROR Muss hier ein ERROR geworfen werden wenn wir eh nur die 3 zur auswahl haben und 2 der default ist und wir nicht unter 0 kommen???

	if (ps_upperLimit == -1)
		psUpperLimit = refSize;
	else
		psUpperLimit = ps_upperLimit;

	psLowerLimit = ps_lowerLimit;
	rangePlain   = range_plain;
	rangePerm	 = range_perm;
	rangeCipher	 = range_cipher;
	return 0;
}

int automated_permanalysis::get_key(int permSize, int it_perm)
{
	int found = 1;
#if 0
	int* key = new int[permSize];
	bool* used_in_key = new bool [permSize];

	memset(used_in_key, false, permSize*sizeof(bool));// If not used = false

	int i, j;
	for (i=0; i<permSize; i++)// "i" goes through the column table_plain
	{
		for (j=0; j<permSize; j++)// "j" goes through the column in table_cipher
		{
		// Column "i" from table "table_plain" is compared with column "j" in "table_cipher"
		// We check if "j" is already entered into the array "used_in_key[]"
			if(!used_in_key[j] && !(memcmp(ptPlain.table[i], ptCipher.table[j], ptCipher.colSize)))
				break;
		}
		// The result "j" is saved in the array "key[]" 
		if(j == permSize)// If with go through to the table no column are found
		{
			found = 0;
			break;
		}
		used_in_key[j] = true;
		key[i] = j+1;
	}

	if ( found )
	{
		permkey *newKey;
		newKey = new permkey(key, permSize, ptPlain.dir, ptCipher.dir, it_perm, keyList);
		keyList = newKey;
		
	}
	else
		delete []key;

	delete []used_in_key;
#endif 
	return found;
}

int automated_permanalysis::analyse(int permSize, int it_plain, int it_perm, int it_cipher)
{
	ptPlain.setParam(it_plain, it_perm, permSize);
	ptCipher.setParam(it_cipher, it_perm, permSize);
	return get_key( permSize, it_perm );
}

inline 
int check( int it, int ref)
{
	return ( ref == both_dir || ref == it );
}

int automated_permanalysis::iterate_key_param()
{
	int permSize;
	int it_perm, it_cipher;

	for(permSize=psUpperLimit; permSize>=psLowerLimit; permSize--)
		for ( it_perm = row_dir; it_perm <= col_dir; it_perm++ ) if (check(it_perm, rangePerm))
			for (it_cipher = row_dir; it_cipher <= col_dir; it_cipher++ ) if (check(it_cipher, rangeCipher ))
				analyse(permSize, ( it_perm == col_dir ) ? col_dir : row_dir, it_perm, it_cipher);

	return (int)(keyList);
}

