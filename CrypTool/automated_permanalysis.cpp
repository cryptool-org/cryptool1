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

perm_table::perm_table()
{
	table = 0;
	permSize = 0;
	colSize = 0;
	dir = both_dir;
}

perm_table::~perm_table()
{
	remove();
}

void perm_table::remove()
{
	if ( table ) 
	{
		for (int i= 0; i<permSize; i++)
			delete []table[i];
		delete []table;
	}
}

int perm_table::realloc( int FILESIZE, int PERMSIZE )
{
	if ( FILESIZE % PERMSIZE )
		return -1;

	remove();
	permSize = PERMSIZE;
	colSize = FILESIZE / permSize;
	table = new char*[permSize];
	for (int i= 0; i<permSize; i++)
		table[i] = new char[colSize];

	return 0;
}

int  perm_table::readFile( ifstream &fin, int DIR)
{
	char c;
	fin.clear();
	fin.seekg(0, ios::beg);
	dir = DIR;
	for(int i=0; ;i++)
	{
		fin.get(c);
		if (!fin.gcount())
			break;
		if(dir == col_dir)
			table[i/colSize][i%colSize] = c;
		else
			table[i%permSize][i/permSize] = c;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

permkey::permkey(int *perm_key, int perm_size, 
		int dir_plain, int dir_cipher, int dir_perm, permkey *nxt ) 
{
	next = nxt;
	permSize = perm_size;
	permKey = perm_key;
	dirPlain = dir_plain;
	dirCipher = dir_cipher;
	dirPerm = dir_perm;
}

permkey::~permkey()
{
	delete []permKey;
	// TODO
}


////////////////////////////////////////////////////////////////////////////////////////////////

automated_permanalysis::automated_permanalysis()
{
	keyList = 0;
	fileSize = 0;
	rangePlain = 2;
	rangePerm = 2;
	rangeCipher = 2;
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

int automated_permanalysis::get_file_size(ifstream &fstrm)
{
	if(!fstrm.is_open())
	{
		MessageBox(NULL,"Die Textdatei konnte nicht geöffnet werden!","Fehler",MB_ICONSTOP);
		return -1;
	}
	
	fstrm.clear(); // Go to the beginning of the file
	fstrm.seekg(0, ios::end);
	return fstrm.tellg();
}

int automated_permanalysis::setFilenames( const char *fn_plain, const char *fn_cipher )
{
	/*if ( fn_plain == 0) 
	{
		MessageBox(NULL,"Bitte geben Sie eine Klartext-Datei an!","Fehler",MB_ICONSTOP);
		return -1;
	}
	
	if ( fn_cipher == 0 )
	{
		MessageBox(NULL,"Bitte geben Sie eine Geheimtext-Datei an!","Fehler",MB_ICONSTOP);
		return -1;
	}*/

	plainFile.open( fn_plain );
	if ( 1 > (fileSize = get_file_size( plainFile )) )
	{
		MessageBox(NULL,"Die angegebenen Textdateien sind leer.","Fehler",MB_ICONSTOP);
		return -1;
	}
	cipherFile.open( fn_cipher );
	if ( fileSize != get_file_size( cipherFile ) )
	{
		MessageBox(NULL,"Die angegebenen Textdateien sind ungleich lang.","Fehler",MB_ICONSTOP);
		cipherFile.close();
		plainFile.close();
		return -1;
	}
	return 1; // SUCCESS 
}

int automated_permanalysis::read_file_in_table(ifstream &fstrm, perm_table &pt, int permSize, int DIR )
{
	if ( 0 > pt.realloc( fileSize, permSize ) )
		return -1; // FIXME: ErrorCode

	if ( 0 > pt.readFile( fstrm, DIR ) )
		return -1; // FIXME: ErrorCode

	return 0;
}

int automated_permanalysis::get_key(int permSize, int it_perm)
{
	int found = 1;

	int* key = new int[permSize];
	bool* used_in_key = new bool [permSize];

	memset(used_in_key, false, permSize*sizeof(bool));// If not used = false

	int i, j;
	for(i = 0; i < permSize; i++)// "i" goes through the column table_plain
	{
		for(j = 0; j < permSize; j++)// "j" goes through the column in table_cipher
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

	return found;
}

int automated_permanalysis::analyse(int permSize, int it_plain, int it_perm, int it_cipher)
{
	read_file_in_table(plainFile, ptPlain, permSize, it_plain);
	read_file_in_table(cipherFile, ptCipher, permSize, it_cipher);
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

	for(permSize=psUpperLimit; permSize>=psLowerLimit; permSize--) if ( !( fileSize % permSize ) )
		for ( it_perm = col_dir; it_perm <= row_dir; it_perm++ ) if (check(it_perm, rangePerm))
			for (it_cipher = col_dir; it_cipher <= row_dir; it_cipher++ ) if (check(it_cipher, rangeCipher ))
				analyse(permSize, ( it_perm == col_dir ) ? col_dir : row_dir, it_perm, it_cipher);

	return (int)(keyList);
}

int automated_permanalysis::setAnalyseParam(int ps_lowerLimit, int ps_upperLimit, int range_plain, int range_perm, int range_cipher)
{
	if(ps_upperLimit != -1 && ps_lowerLimit > ps_upperLimit)
	{
		MessageBox(NULL,"Die Untergrenze darf nicht die Obergrenze der Permutationsgröße überschreiten!","Fehler",MB_ICONSTOP);
		return -1;
	}

	if(ps_lowerLimit <= 0 || ps_upperLimit == 0 || ps_upperLimit < -1)
	{
		MessageBox(NULL,"Es können nur positive ganze Zahlen angegeben werden!","Fehler",MB_ICONSTOP);
		return -1;	
	}
	
	if(range_plain < 0 || range_plain > 2 || range_perm < 0 || range_perm > 2 || range_cipher < 0 || range_cipher > 2)
		return -1; //ERROR Muss hier ein ERROR geworfen werden wenn wir eh nur die 3 zur auswahl haben und 2 der default ist und wir nicht unter 0 kommen???

	if(ps_upperLimit == -1)
		psUpperLimit = fileSize;
	else
		psUpperLimit = ps_upperLimit;

	psLowerLimit = ps_lowerLimit;
	rangePlain   = range_plain;
	rangePerm	 = range_perm;
	rangeCipher	 = range_cipher;
	return 0;
}