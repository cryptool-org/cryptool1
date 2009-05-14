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

#include "automated_permanalysis.h"
#include "resource.h"
#include "FileTools.h"

perm_table::perm_table() :
	data(0),
	permSize(0),
	size(0),
	readDir(row_dir),
	permDir(row_dir),
	ofsList(0)
{
}

int  perm_table::loadFile(const char *filename, int TEXTMODE, unsigned int REFSIZE)
{
	if ( data )
	{
		delete []data; data = 0; size = 0;
	}
	int tSize;
	int ret = readSource( filename, data, tSize, TEXTMODE );
	size = (int)tSize;
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
	delete []ofsList;
}

void perm_table::setParam(int READDIR, int PERMDIR, unsigned int PERMSIZE, int ofsKnown) 
{ 
	readDir		= READDIR; 
	permDir		= PERMDIR; 
	permSize	= PERMSIZE;

	delete []ofsList;
	ofsList = new unsigned int[permSize+1];

	ofsList[0] = (ofsKnown) ? permSize : 0;
	ofsList[1] = 0;
	for (unsigned int i=2; i<=permSize; i++)
		ofsList[i] = (ofsKnown) ? ofsList[i-1] + size/permSize + (i <= size%permSize) : 0;
}

int perm_table::get(int r, int c)
{
	if ( ofsList[0] < permSize ) 
		return TABLE_ERROR;

	unsigned int ndx = 0;
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
		ndx = ofsList[cr] + (rc-1);

	ASSERT( 0 <= ndx && ndx < refSize );
	return (ndx < size) ? data[ndx] : CHR_UNDEFINED;
}

int perm_table::get(unsigned int c)
{
	ASSERT( 1<=c && c<=refSize );
	return (c<=size) ? data[c-1] : CHR_UNDEFINED;
}

int perm_table::findStr (const int *str, int *permTable)
{
	unsigned int i, j;
	int marker = 0;
	for (j=1; j<=permSize; j++) if ( permTable[j] <= 0 )
	{
		int found = 1;
		for (i=1; i<=refSize/permSize + (unsigned int)(j <= (refSize%permSize)) && found; i++)
		{
			unsigned int jj, ii;
			jj = ( permDir == row_dir ) ? j : i;
			ii = ( permDir == row_dir ) ? i : j;
			if ( (get( jj, ii ) != str[i-1]) )
			{
				if ( get(jj, ii) == CHR_UNDEFINED || str[i-1] == CHR_UNDEFINED )
					found = -1;
				else
					found = 0; 
			}
		}
		if ( found == 1 )
			return j;
		if ( found == -1 && !marker )
			marker = -1*((int)j);
	}
	return marker;
}

void perm_table::buildStr(int *str, unsigned int ofs, unsigned int lastStep)
{
	unsigned int i;
	if ( readDir == permDir )
	{
		for (i=ofs; i<ofs+(refSize/permSize); i++)
			str[i-ofs] = get(i);
		if ( (i<refSize) && (refSize%permSize) )
			str[i-ofs] = get(i);
	}
	else
	{
		unsigned int k = ofs;
		for (i=0; i<(refSize/permSize); i++,k+=permSize)
			str[i] = get(k);
		if ( lastStep ) 
			str[i] = get(k + lastStep);
	}
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

int automated_permanalysis::get_key(unsigned int permSize, int it_perm)
{
	int found = 1;

	unsigned int j, ofs = 0, lastStep = permSize, incr = 1;
	int *str  = new int[ptPlain.getSize()/permSize +1];
	int *perm = new int[permSize+1];
	for ( j=1; j<=permSize; j++ )
	{
		ptCipher.buildStr(str, ofs, lastStep);
		int index = ptPlain.findStr(str, perm);
		if ( index != 0 )
		{
			perm[j] = index;
			if ( index < 0 )
				index *= -1;
			if ( index <= (int)permSize )
				lastStep--;
			ASSERT(lastStep >= 0);
		}
		else
			break;
		ofs += incr + ( (ptCipher.permDir != ptCipher.readDir) && (index <= (int)permSize) );
	}

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

int automated_permanalysis::analyse(unsigned int permSize, int it_plain, int it_perm, int it_cipher)
{
	ptPlain.setParam (it_plain, it_perm, permSize, 1);
	ptCipher.setParam(it_cipher, it_perm, permSize, 0);
	get_key( permSize, it_perm );
	return 0; 
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

