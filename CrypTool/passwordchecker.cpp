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


// passwordchecker.cpp

// ****************************************************************************
//
// 06.11.2007 Florian Marchal
// Integration des mit Henrik Koy entwickelten Passwort-Checkers in CrypTool
//
// ****************************************************************************

#include "passwordchecker.h"

// these are the patterns a password is checked against
static char *pwd_patterns[] = {
	"ddpddpdddd",
	"ddpddpdd",
	"ddsddsdddd", 
	"ddsddsdd",
	(char *)0
};

// this function checks a password against patterns
char *checkPasswordAgainstPatterns(char *password) {
	char *pattern_found = pwd_patterns[0];

	for (int i = 0; pattern_found != 0; i++ )
	{
		if ( PMatch(pattern_found, password ) )
		{
			char *str_found = new char[strlen(password)+1];
			strcpy(str_found, password);
			return str_found;
		}
		pattern_found = pwd_patterns[i];
	}

	#define MAX_PATTERN_SIZE 6

	char pattern[MAX_PATTERN_SIZE];
	int pwd_len = strlen(password);
	for (int i = 2; i <= pwd_len/2 && i <= MAX_PATTERN_SIZE; i++)
	{
		if (  pwd_len % i )
			continue;
		strncpy(pattern, password, i);
		char *ptr = password+i;
		int   steps = pwd_len / i;
		for ( int j = 1; (j < steps) && !strncmp(ptr, pattern, i); j++ )
			ptr += i;
		if ( j == steps )
		{
			char *str_found = new char[pwd_len+1];
			strcpy(str_found, password);
			return str_found;
		}
	}
	return ((char *)0);
}

// this function checks a password against sequences
char *checkPasswordAgainstSequences(char *password) {
	char *ptr, *kbd_serial;
	int end_max = 0, i;

	kbd_serial = new char[strlen(password)+1];

	for (int delta = -1; delta <= 1; delta++)
	{
		i = 1;
		ptr = password;
		while ((ptr[0] && ptr[1]) && (ptr[0] == (char)(ptr[1] + delta)) )
		{
			i++;
			ptr++;
		}
		if ( i > MAXSTEP && i > end_max )
			end_max = i;
	}
	if ( end_max  >= (int)strlen(password) )
	{
		strncpy(kbd_serial, password, i);
		kbd_serial[i] = '\0';
		return kbd_serial;
	}

	delete []kbd_serial;
	return ((char *)0);
}

// these are keyboard sequences a password is checked against
static char *pwd_kbd_serials[] = {
	"^1234567890ß",
	"°!\"§$%&/()=?",
	"qwertzuiopü+",
	"QWERTZUIOPÜ*",
	"asdfghjklöä#",
	"ASDFGHJKLÖÄ'",
	"<yxcvbnm,.-",
	">YXCVBNM;:_",
	(char *)0
};

// this function checks a password against keyboard sequences
char *checkPasswordAgainstKeyboardSequences(char *password) {
	int end_max = 0;
	char *pm, *ptr, *kbd_serial;

	kbd_serial = new char[strlen(password)+1];

	for ( int delta = -1; delta <= 1; delta += 2 )
	{
		int k = 0;
		while ( pwd_kbd_serials[k] != 0 )
		{
			ptr = password;
			if ( pm = strchr(pwd_kbd_serials[k], ptr[0]) )
			{
				int i = 0;
				while ( ptr[0] && ptr[0] == *pm )
				{
					ptr++;
					pm += delta;
					i++;
					if ( pm == pwd_kbd_serials[k] || *pm == '\0' )
						break;
				}
				if ( i > MAXSTEP && i > end_max )
				{
					end_max = i;
					strncpy(kbd_serial, password, i);
					kbd_serial[i] = '\0';
				}
			}
			k++;
		}
	}	
	if ( end_max >= (int)strlen(password) )
	{
		return kbd_serial;
	}

	delete []kbd_serial;	
	return ((char *)0);
}

// this function checks a password against a cracklib dictionary
char *checkPasswordAgainstCracklibDictionary(char *password, PWDICT *pwp, unsigned long int notfound) {
	if ( pwp )
	{
		if ( FindPW(pwp, password) != notfound )
		{
			char *dictionary_word;
			dictionary_word = new char[strlen(password)+1];
			strcpy(dictionary_word, password);
			return dictionary_word;
		}
	}
	return ((char *)0);
}

// character classes for password compliance checks
static char *pwd_chr_families[] = {
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",			// uppercase
	"abcdefghijklmnopqrstuvwxyz",			// lowercase
	"1234567890",							// digits
	"^°!\"§$%&/()=?´`\\<>|,;:.-_#\'+*~@",	// special
	(char *)0
};

// this function checks a password for compliance
int checkPasswordForCompliance(char *password) {
    if (strlen(password) < MINLEN)
    {
		return IDS_PWD_POLICY_TOOSHORT;
	}

	int _APLHA   = 0,		 
		_alpha   = 0, 
		_number  = 0, 
		_special = 0,
		_other   = 0,
		_char_set = 0;

	for (int i=0; i<(int)strlen(password); i++)
	{
		char *set_ptr; 
		int j = 0;
		while ( (char*)0 != (set_ptr = pwd_chr_families[j]) )
		{
			if ( strchr(set_ptr, int(password[i])) )
			{
				switch (j) {
					case 0: _APLHA++;
							_char_set |= 1;
						break;
					case 1: _alpha++;
						    _char_set |= 2;
						break;
					case 2: _number++;
						    _char_set |= 4;
						break;
					case 3: _special++;
						    _char_set |= 8;
						break;
					default: _other++;
				}
			}
			j++;
		}
	}

// See IS Standard for Identity Authentication 2.2.1 requirment 5:
// "Passwords MUST contain alpha and numeric characters and should 
//  preferably require upper- and lowercase as well as special characters.
//  Passwords for privileged users MUST contain alpha, numeric and special
//  characters."
	if ( (_char_set & 15) == 15 )
	{ // should
		return IDS_PWD_POLICY_RECOMMENDED;
	}
	if ( (_char_set & 13) == 13 || (_char_set & 14) == 14 )
	{  // must for admins
		return IDS_PWD_POLICY_PRIVILEGED;
	}
	if ( (_char_set & 5 ) == 5  || (_char_set & 6 ) == 6  )
	{  // must for all
		return IDS_PWD_POLICY_MINIMAL;
	}

	return IDS_PWD_POLICY_NOT_COMPLIANT;
}

// this function checks a password's charset
int checkPasswordCharset(char *password) {
	char *jptr, junk[256];
    jptr = junk;
    *jptr = '\0';

    for (int i = 0; i < STRINGSIZE && password[i]; i++)
    {
		if (!strchr(junk, password[i]))
		{
			*(jptr++) = password[i];
			*jptr = '\0';
		}
    }

    if (strlen(junk) < MINDIFF)
    {
		return IDS_PWD_NOT_ENOUGH_DIFF_CHARS;
    }

	return 0;
}

/* return a pointer to an lowercase */
char *Lowercase(register char *str) {
    register char *ptr;
    static char area[STRINGSIZE];
    ptr = area;
    while (*str)
    {
	//FIXME: *(ptr++) = CRACK_TOLOWER(*str);
	*(ptr++) = CRACK_TOLOWER(*str);
	str++;
    }
    *ptr = '\0';

    return (area);
}

char *prepare_password(char *password)
{	
	char pwd_prepared[STRINGSIZE+1];
	char *ptr_pwd_prepared = pwd_prepared;
	int password_len = strlen(password); 

	if ( strlen(password) > STRINGSIZE )
		password_len = STRINGSIZE;
	strncpy(pwd_prepared, Lowercase(password), password_len);
	pwd_prepared[password_len] = '\0';

// Why the trimming??
	Trim(pwd_prepared);
    while (*ptr_pwd_prepared && isspace(*ptr_pwd_prepared))
    {
		ptr_pwd_prepared++;
    }

	char *pwd = strdup(ptr_pwd_prepared);
	return pwd;
}

/* Closure matrix */
	struct closure_info {
		int flags;
		int pred;
	};


void clean_up(closure_info **closure_matrix, int pwd_len, int check_flags, int rem_flag)
{
	for (int j=0; j<=pwd_len; j++)
		for (int i=0; i<=pwd_len; i++)
			if ( closure_matrix[j][i].flags & rem_flag ) 
			{
				int break_loop = 0;
				for (int l=0; l<=j && !break_loop; l++)
					for (int k=i + (j-l); k<=pwd_len; k++)
						if ( (closure_matrix[l][k].flags & check_flags) && !(l == j && i == k) )
						{
							closure_matrix[j][i].flags -= rem_flag;
							break_loop++;
							break;
						}
			}

}

struct pwd_coord { int ndx, len; };

// this is the main password checking function; it returns 0 if the given path 
// for the cracklib dictionary is invalid
char *checkPassword(char *password, char *path, int hidePassword) {
    static char lastpath[STRINGSIZE];
    static PWDICT *pwp;
    char pwtrunced[STRINGSIZE];
    unsigned long int notfound;

    /* security problem: assume we may have been given a really long
       password (buffer attack) and so truncate it to a workable size;
       try to define workable size as something from which we cannot
       extend a buffer beyond its limits in the rest of the code */
    strncpy(pwtrunced, password, TRUNCSTRINGSIZE);
    pwtrunced[TRUNCSTRINGSIZE - 1] = '\0'; /* enforce */

	char *str_fnds;
	str_fnds = new char[strlen(pwtrunced)*strlen(pwtrunced) + 10000];
	str_fnds[0] = '\0';

	/* preparations */
    if (pwp && strncmp(lastpath, path, STRINGSIZE))
    {
		PWClose(pwp);
		pwp = (PWDICT *)0;
    }

    if (!pwp)
    {
		if (!(pwp = PWOpen(path, "r")))
		{
			perror("PWOpen");
			// Florian Marchal, 08.11.2007
			// return 0 to indicate the cracklib dictionary could not be found
			// exit(-1);
			return 0;
		}
		strncpy(lastpath, path, STRINGSIZE);
    }
    notfound = PW_WORDS(pwp);

	int id_err;
	id_err = checkPasswordForCompliance(pwtrunced);
	strcat(str_fnds, "Deutsche Bank Passwort Policy erfüllt:\r\n");

#if 0
	switch (id_err) {
		case IDS_PWD_POLICY_TOOSHORT:
			strcat(str_fnds, " - Nein (Länge ist kleiner 8)");
			break;
		case IDS_PWD_POLICY_NOT_COMPLIANT:
			strcat(str_fnds, " - Nein (nicht alphanumerisch)");
			break;
		case IDS_PWD_POLICY_MINIMAL:
			strcat(str_fnds, " - Ja für normale Anwendungen \r\n - Nein für kritische Anwendungen (keine Sonderzeichen)");
			break;
		case IDS_PWD_POLICY_PRIVILEGED:
		case IDS_PWD_POLICY_RECOMMENDED:
			strcat(str_fnds, " - Ja für normale Anwendungen\r\n - Ja für kritische Anwendungen");
			break;
	};
#endif

#if 1
	switch (id_err) {
		case IDS_PWD_POLICY_TOOSHORT:
			strcat(str_fnds, " - Nein für normale Anwendungen (Länge ist kleiner 8)\r\n - Nein für kritische Anwendungen (Länge ist kleiner 8)");
			break;
		case IDS_PWD_POLICY_NOT_COMPLIANT:
			strcat(str_fnds, " - Nein für normale Anwendungen (nicht alphanumerisch)\r\n - Nein für kritische Anwendungen (nicht alphanumerisch oder keine Sonderzeichen)");
			break;
		case IDS_PWD_POLICY_MINIMAL:
			strcat(str_fnds, " - Ja für normale Anwendungen \r\n - Nein für kritische Anwendungen (keine Sonderzeichen)");
			break;
		case IDS_PWD_POLICY_PRIVILEGED:
		case IDS_PWD_POLICY_RECOMMENDED:
			strcat(str_fnds, " - Ja für normale Anwendungen\r\n - Ja für kritische Anwendungen");
			break;
	};
#endif

	id_err = checkPasswordCharset(pwtrunced);
	if ( id_err )
	{
		// FIXME 
		// return 0;
	}

	char *check_password = prepare_password(pwtrunced);
	int   pwd_len = strlen(check_password);

	struct closure_info **closure_matrix;
	int i,j;
	char pwd_substr[STRINGSIZE];

	closure_matrix = new struct closure_info*[pwd_len+1];
	for ( i=0; i<=pwd_len; i++ )
	{
		closure_matrix[i] = new struct closure_info [pwd_len+1];
		for ( j=0; j<=pwd_len; j++ )
		{
			closure_matrix[i][j].flags = 0;
			closure_matrix[i][j].pred = 0;
		}
	}

#define MINLEN_SUBSTR 3
#define PATTERN				 1
#define SERIALS				 2
#define KBD_SERIALS			 4 
#define DICT_WORDS			 8
#define COMPOSED_DICT_WORDS	16
#define CLOSURE				32

/* Seek for weak substrings */
	for ( i = MINLEN_SUBSTR; i<=pwd_len; i++ )
	{
		for (j = 0; j<=pwd_len-i; j++)
		{
			strncpy(pwd_substr, check_password+j, i);
			pwd_substr[i] = '\0';
			char *substr = 0;

		/*                           */
			if ( substr = checkPasswordAgainstPatterns(pwd_substr ) )
			{
				closure_matrix[j][i].flags |= PATTERN;
			}
		/*                           */
			if ( substr = checkPasswordAgainstSequences(pwd_substr ) )
			{
				closure_matrix[j][i].flags |= SERIALS;
			}
		/*                           */
			if ( substr = checkPasswordAgainstKeyboardSequences(pwd_substr ) )
			{
				closure_matrix[j][i].flags |= KBD_SERIALS;
			}
		/*                           */
			if ( substr = checkPasswordAgainstCracklibDictionary( pwd_substr, pwp, notfound ) )
				closure_matrix[j][i].flags |= DICT_WORDS;

			if ( substr )
				delete []substr;

		}
	}


/* ***************************************************************
	closure 
   ***************************************************************/
	struct pwd_coord * word_stack;
	word_stack = new pwd_coord[pwd_len*pwd_len];
	int ptr_word_stack = 0;

#if 0
	/* ***********************************
	   pwd closure 
	   ***********************************/
	for (int i=0; i<=pwd_len; i++)
	{
		for (j=0; j<=pwd_len; j++)
		{
			if ( closure_matrix[j][i].flags & DICT_WORDS ) 
			{
				word_stack[ptr_word_stack].ndx = j;
				word_stack[ptr_word_stack].len = i;
				ptr_word_stack++;
			}
		}
	}

	/* build pwd closure */
	while ( ptr_word_stack )
	{
		ptr_word_stack--;
		int i = word_stack[ptr_word_stack].len, 
			j = word_stack[ptr_word_stack].ndx;
		for (int k=MINLEN_SUBSTR; k<pwd_len; k++)
			if ( (closure_matrix[j+i][k].flags & DICT_WORDS + COMPOSED_DICT_WORDS) && !(closure_matrix[j][i+k].flags & DICT_WORDS + COMPOSED_DICT_WORDS) )
			{
				closure_matrix[j][i+k].flags |= COMPOSED_DICT_WORDS;
				closure_matrix[j][i+k].pred = i;
				word_stack[ptr_word_stack].ndx = j;
				word_stack[ptr_word_stack].len = i+k;
				ptr_word_stack++;
			}
	}		

	/* ***********************************
	   full closure 
	   ***********************************/
#endif 

	ptr_word_stack = 0;

	for (int i=0; i<=pwd_len; i++)
	{
		for (j=0; j<=pwd_len; j++)
		{
			if ( closure_matrix[j][i].flags ) 
			{
				word_stack[ptr_word_stack].ndx = j;
				word_stack[ptr_word_stack].len = i;
				ptr_word_stack++;
			}
		}
	}

	/* build full closure */
	while ( ptr_word_stack )
	{
		ptr_word_stack--;
		int i = word_stack[ptr_word_stack].len, 
			j = word_stack[ptr_word_stack].ndx;
		for (int k=MINLEN_SUBSTR; k<pwd_len; k++)
			if ( (closure_matrix[j+i][k].flags) && !(closure_matrix[j][i+k].flags) )
			{
				closure_matrix[j][i+k].flags |= CLOSURE;
				closure_matrix[j][i+k].pred = i;
				word_stack[ptr_word_stack].ndx = j;
				word_stack[ptr_word_stack].len = i+k;
				ptr_word_stack++;
			}
	}		


	/* *********************************
	   clean up set of substrings
	   *********************************/


	clean_up(closure_matrix, pwd_len, PATTERN, PATTERN);
	clean_up(closure_matrix, pwd_len, SERIALS, SERIALS);
	clean_up(closure_matrix, pwd_len, KBD_SERIALS, KBD_SERIALS);
	clean_up(closure_matrix, pwd_len, DICT_WORDS, DICT_WORDS);
	// clean_up(closure_matrix, pwd_len, COMPOSED_DICT_WORDS + DICT_WORDS, COMPOSED_DICT_WORDS);
	clean_up(closure_matrix, pwd_len, PATTERN + SERIALS + KBD_SERIALS + DICT_WORDS + COMPOSED_DICT_WORDS + CLOSURE, CLOSURE);


	/* ********************************
	   show substrings 
	   ********************************/
char joker[] = "********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************";

    strcat(str_fnds, "\r\n\r\nRekonstruktion aus Wörtern, Folgen und Mustern:");
	int t_flag = 0;

	for (int j=0; j<=pwd_len; j++)
		for (int i=0; i<=pwd_len; i++)
			if ( closure_matrix[j][i].flags & CLOSURE ) 
			{
				if ( !t_flag )
				{
					t_flag++;
					strcat(str_fnds, "\r\nGefunden wurde(n): ");
				}
				else
					strcat(str_fnds, ", "); 
				if ( !hidePassword )
					strncat(str_fnds, password+j, i); 
				else
					strncat(str_fnds, joker, i);
				char tmp_str[256];
				sprintf(tmp_str, "(%i aus %i Zeichen)", i, strlen(password));
			}
		
	strcat(str_fnds, "\r\nMuster: ");
	t_flag = 0;
	for (int j=0; j<=pwd_len; j++)
		for (int i=0; i<=pwd_len; i++)
			if ( closure_matrix[j][i].flags & PATTERN ) 
			{
				if ( !t_flag )
					t_flag++;
				else
					strcat(str_fnds, ", "); 
				if ( !hidePassword )
					strncat(str_fnds, password+j, i); 
				else
					strncat(str_fnds, joker, i);
			}
	if (!t_flag)
		strcat(str_fnds, " -");

	strcat(str_fnds, "\r\nFolgen: ");
	t_flag = 0;
	for (int j=0; j<=pwd_len; j++)
		for (int i=0; i<=pwd_len; i++)
			if ( closure_matrix[j][i].flags & SERIALS ) 
			{
				if ( !t_flag )
					t_flag++;
				else
					strcat(str_fnds, ", "); 
				if ( !hidePassword )
					strncat(str_fnds, password+j, i); 
				else
					strncat(str_fnds, joker, i);

			}
	if (!t_flag)
		strcat(str_fnds, " -");

	strcat(str_fnds, "\r\nTastatur-Folgen: ");
	t_flag = 0;
	for (int j=0; j<=pwd_len; j++)
		for (int i=0; i<=pwd_len; i++)
			if ( closure_matrix[j][i].flags & KBD_SERIALS ) 
			{
				if ( !t_flag )
					t_flag++;
				else
					strcat(str_fnds, ", "); 
				if ( !hidePassword )
					strncat(str_fnds, password+j, i); 
				else
					strncat(str_fnds, joker, i);
			}
	if (!t_flag)
		strcat(str_fnds, " -");

	strcat(str_fnds, "\r\nWörterbuch-Einträge: ");
	t_flag = 0;
	for (int j=0; j<=pwd_len; j++)
		for (int i=0; i<=pwd_len; i++)
			if ( closure_matrix[j][i].flags & DICT_WORDS ) 
			{
				if ( !t_flag )
					t_flag++;
				else
					strcat(str_fnds, ", "); 
				if ( !hidePassword )
					strncat(str_fnds, password+j, i); 
				else
					strncat(str_fnds, joker, i);

			}
	if (!t_flag)
		strcat(str_fnds, " -");

	delete []word_stack;
	for ( int i=0; i<=pwd_len; i++ )
		delete []closure_matrix[i];
	delete [] closure_matrix;


/* ******************************************************* */

	return str_fnds;
}