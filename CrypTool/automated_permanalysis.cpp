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

int compare(perm_table &ptPlain, perm_table &ptCipher, unsigned int px, unsigned int cx)
{
	if ( ptCipher.getSize() - cx < ptPlain.getSize(px) -1 )
		return 0;
	for ( unsigned int i=1; i<=ptPlain.getSize(px); i++ )
		if ( ptPlain.permDir == row_dir ) { if ( ptPlain.get(px, i) != ptCipher.get(cx-1+i) ) return 0; }
		else                              { if ( ptPlain.get(i, px) != ptCipher.get(cx-1+i) ) return 0; }
	return 1;
}

int compare(perm_table &ptPlain, perm_table &ptCipher, unsigned int px, unsigned int rx, unsigned int ur)
{
	for ( unsigned int i=1; i<=ptPlain.getSize(px); i++ )
	{
		unsigned int p, o = ptPlain.size/ptPlain.permSize ;
		p = ( i > o ) ? o*ptPlain.permSize + ur : rx+(i-1)*ptPlain.permSize;
		if ( p > ptCipher.size ) return 0;
		if ( ptPlain.permDir == row_dir ) { if ( ptPlain.get(px, i) != ptCipher.get(p) ) return 0; }
		else                              { if ( ptPlain.get(i, px) != ptCipher.get(p) ) return 0; }
	}
	return 1;
}

//////////////////////////////////////////////////////////////////////
// Precheck: Check if Histogram(data1) == Histogram(data2)
int  cmpHistogram(char *data1, char *data2, size_t size)
{
	size_t hist1[256], hist2[256], i;
	memset(hist1, '\0', 256*sizeof(size_t));
	memset(hist2, '\0', 256*sizeof(size_t));
	for (i=0; i<size; i++)
	{
		hist1[(unsigned char)data1[i]]++;
		hist2[(unsigned char)data2[i]]++;
	}
	return memcmp(hist1, hist2, 256*sizeof(size_t));
}

///////////////////////////////////////////////////////////////////////
//
perm_table::perm_table() :
	data(0),
	permSize(0),
	size(0),
	readDir(row_dir),
	permDir(row_dir)
{
}

int  perm_table::loadFile(const char *filename, int TEXTMODE)
{
	if ( data )
	{
		delete []data; data = 0; size = 0;
	}

	int tSize;
	int ret = readSource( filename, data, tSize, TEXTMODE );
	size = (unsigned int)tSize;

	return ret;
}

perm_table::~perm_table()
{
	delete []data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

permkey::permkey(unsigned int *perm_key, unsigned int perm_size, 
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
// FIXME 
int automated_permanalysis::found( unsigned long t_ndx, unsigned long p_ndx, char *rem, unsigned int *pk, unsigned int extra )
{
	if ( extra && !(ptPlain.size % ptPlain.permSize) )
		return 0;
	unsigned int i = (extra) ? 1                               : ptPlain.size % ptPlain.permSize +1;
	unsigned int j = (extra) ? ptPlain.size % ptPlain.permSize : ptPlain.permSize;
	for ( ; i<=j; i++ )
		if ( rem[i] && compare( ptPlain, ptCipher, i, t_ndx ) )
		{
			pk[i]  = p_ndx;
			rem[i] = 0;
			return i;
		}
	return 0;
}

int automated_permanalysis::seek_linear( int f, unsigned long t_ndx, unsigned long p_ndx, char *rem, unsigned int *pk )
{	
	if ( !f )
		return 0;
	unsigned int el = ptPlain.size / ptPlain.permSize;
	if ( t_ndx > ptPlain.size ) 
		if ( p_ndx > ptPlain.permSize ) return 1;
		else	                        return 0;
	if ( seek_linear( found( t_ndx, p_ndx, rem, pk, 0), t_ndx+el  , p_ndx+1, rem, pk) )
		return 1;
	if ( seek_linear( found( t_ndx, p_ndx, rem, pk, 1), t_ndx+el+1, p_ndx+1, rem, pk) )
		return 1;
	rem[f] = 1;

	return 0;
}

int automated_permanalysis::found_s( unsigned long p_ndx, unsigned long ur, char *rem, unsigned int *pk, unsigned int extra )
{
	if ( extra && !(ptPlain.size % ptPlain.permSize) )
		return 0;
	unsigned int i = (extra) ? 1                               : ptPlain.size % ptPlain.permSize +1;
	unsigned int j = (extra) ? ptPlain.size % ptPlain.permSize : ptPlain.permSize;
	for ( ; i<=j; i++ )
		if ( rem[i] && compare( ptPlain, ptCipher, p_ndx, i, ur) )
		{
			pk[i]  = p_ndx;
			rem[i] = 0;
			return i;
		}
	return 0;
}

int automated_permanalysis::seek_scattered( int f, unsigned long p_ndx, unsigned long ur, char *rem, unsigned int *pk )
{	
	if ( !f )
		return 0;
	unsigned int el = ptPlain.size / ptPlain.permSize;
	if ( p_ndx > ptPlain.permSize ) 
		return 1;
	if ( seek_scattered( found_s( p_ndx, ur, rem, pk, 0), ur,   p_ndx+1, rem, pk) )
		return 1;
	if ( seek_scattered( found_s( p_ndx, ur, rem, pk, 1), ur+1, p_ndx+1, rem, pk) )
		return 1;
	rem[f] = 1;

	return 0;
}



int automated_permanalysis::analyse(unsigned int permSize, int it_plain, int it_perm, int it_cipher)
{
	ptPlain.setParam (it_plain,  it_perm, permSize, 1);
	ptCipher.setParam(it_cipher, it_perm, permSize, 0);

	char			*rem = new char[permSize+1];
	unsigned int	*pk  = new unsigned int[permSize+1];
	memset(rem, 1, permSize+1);
	memset(pk,  0, (permSize+1)*sizeof(unsigned int));

	if ( it_perm == it_cipher )
	{
		if ( seek_linear( 1, 1, 1, rem, pk ) )
		{
			keyList = new permkey(pk, permSize, it_plain, it_cipher, it_perm, keyList);
			delete []rem;
			return 1;
		}
	}
	else
	{
		if ( seek_scattered( 1, 1, 1, rem, pk ) )
		{
			keyList = new permkey(pk, permSize, it_plain, it_cipher, it_perm, keyList);
			delete []rem;
			return 1;
		}
	}

	delete []rem;
	delete []pk;
	return 0; 
}

automated_permanalysis::automated_permanalysis()
{
	keyList		= 0;
	size	    = 0;
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
	int error = 0;
	if ( refPlain )
	{ // FIXME ERROR
		error = ptPlain.loadFile(fn_plain, TEXTMODE);
		if ( error ) return error;
		size = ptPlain.getSize();
		error = ptCipher.loadFile(fn_cipher, TEXTMODE);
	}
	else
	{ // FIXME ERROR
		error = ptCipher.loadFile(fn_plain, TEXTMODE);
		if ( error ) return error;
		size = ptCipher.getSize();
		error = ptPlain.loadFile(fn_cipher, TEXTMODE);
	}
	if ( !error )
	{
		if (ptCipher.getSize() != ptPlain.getSize() ) 
			return 1; // different file sizes
		if ( cmpHistogram(ptPlain.data, ptCipher.data, ptCipher.getSize()) )
			return 2; // different histograms
	}
	return error;  
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
		psUpperLimit = size;
	else
		psUpperLimit = ps_upperLimit;

	psLowerLimit = ps_lowerLimit;
	rangePlain   = range_plain;
	rangePerm	 = range_perm;
	rangeCipher	 = range_cipher;
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

	for(permSize=psLowerLimit; permSize<=psUpperLimit; permSize++)
		for ( it_perm = row_dir; it_perm <= col_dir; it_perm++ ) if (check(it_perm, rangePerm))
			for (it_cipher = row_dir; it_cipher <= col_dir; it_cipher++ ) if (check(it_cipher, rangeCipher ))
				analyse(permSize, ( it_perm == col_dir ) ? col_dir : row_dir, it_perm, it_cipher);

	return (int)(keyList);
}

