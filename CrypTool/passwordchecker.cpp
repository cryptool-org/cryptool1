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


// passwordchecker.cpp

// ****************************************************************************
//
// 11/06/2007 Florian Marchal
// integration of the password checking function developed with Henrik Koy
//
// ****************************************************************************

#include "stdafx.h"

#include "passwordchecker.h"
#include "resource.h"
#include "CrypToolTools.h"
#include "ChrTools.h"

#pragma warning(disable : 4996)

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

	#define MAX_PATTERN_SIZE 10

	char pattern[MAX_PATTERN_SIZE];
	int pwd_len = strlen(password);
	for (int i = 2; i <= pwd_len/2 && i <= MAX_PATTERN_SIZE; i++)
	{
		strncpy(pattern, password, i);
		char *ptr = password+i;
		int   steps = pwd_len / i;
		int j;
		for (j = 1; (j < steps) && !strncmp(ptr, pattern, i); j++ )
			ptr += i;
		if ( pwd_len % i )
		{
			steps++;
			if ( !strncmp(ptr, pattern, pwd_len % i) )
				j++;
		}
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
int checkPasswordForCompliance(char *password, int &pwLength, int &pwLengthMinimum, int &pwDigits, int &pwDigitsMinimum, int &pwSpecials, int &pwSpecialsMinimum) {
	// by default, every password is compliant
	int complianceCheckResult = IDS_PWD_POLICY_COMPLIANT;
	// stick to default values in case there are no registry entries
	unsigned long minimumLength = MINLEN;
	unsigned long minimumDigits = 1;
	unsigned long minimumSpecial = 1;
	unsigned long buffer = 1024;
	char *specialGroup = new char[buffer+1];
	memset(specialGroup, 0, buffer+1);
	memcpy(specialGroup, "^°!\"§$%&/()=?´`\\<>|,;:.-_#\'+*~@", 31);

	// try to read guidelines from registry 
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_READ, IDS_REGISTRY_SETTINGS, "PasswordGuidelines" ) == ERROR_SUCCESS )
	{
		CT_READ_REGISTRY(minimumLength, "MinimumLength");
		CT_READ_REGISTRY(minimumDigits, "MinimumDigits");
		CT_READ_REGISTRY(minimumSpecial, "MinimumSpecial");
		CT_READ_REGISTRY(specialGroup, "SpecialGroup", buffer);
		CT_CLOSE_REGISTRY();
		// alter special characters group
		pwd_chr_families[3] = specialGroup;
	}

	unsigned long	_APLHA   = 0,		 
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

	delete specialGroup;

	// evaluate policy checks
	if (strlen(password) < minimumLength) complianceCheckResult |= IDS_PWD_POLICY_TOOSHORT;
	if( _number < minimumDigits ) complianceCheckResult |= IDS_PWD_POLICY_TOOFEWDIGITS;
	if( _special < minimumSpecial ) complianceCheckResult |= IDS_PWD_POLICY_TOOFEWSPECIALCHARACTERS;

	// flomar, 01/22/2012: fill the parameters (see signature) for future use
	pwLength = (int)strlen(password);
	pwLengthMinimum = (int)minimumLength;
	pwDigits = (int)_number;
	pwDigitsMinimum = (int)minimumDigits;
	pwSpecials = (int)_special;
	pwSpecialsMinimum = (int)minimumSpecial;

	return complianceCheckResult;
}

/* return a pointer to an lowercase */
char *Lowercase(register char *str) {
    register char *ptr;
    static char area[STRINGSIZE];
    ptr = area;
    while (*str) {
		*(ptr++) = CRACK_TOLOWER((unsigned char)*str);
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

	/* Why the trimming?? */
	Trim(pwd_prepared);
    while (*ptr_pwd_prepared && isspace((unsigned char)*ptr_pwd_prepared))
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

struct pwd_coord { 
	int ndx;
	int len; 
};

#define MINLEN_SUBSTR 3
#define PATTERN				 1
#define SERIALS				 2
#define KBD_SERIALS			 4 
#define DICT_WORDS			 8
#define COMPOSED_DICT_WORDS	16
#define CLOSURE				32


void get_pwd_substrings( int pwd_len, closure_info **closure_matrix, int FLAG, 
						 char *password, int hidePassword,
						char *str_fnds, char **word_list, int &word_listSize)
{
	/* this character is used when the password is to be checked secretly; that means 
	instead of the actual password, the user is shown an array of wildcard characters */
	const char wildcard = '*';
	const int wildcardArraySize = 1024;
	char wildcardArray[wildcardArraySize];
	memset(wildcardArray, 0, wildcardArraySize);

	int t_flag = 0;

	for (int j=0; j<=pwd_len; j++)
		for (int i=0; i<=pwd_len; i++)
			if ( closure_matrix[j][i].flags & FLAG ) 
			{
				if ( !t_flag )
				{
					t_flag++;
				}
				else
					strcat(str_fnds, ", "); 
				if ( !hidePassword )
				{
					strncat(str_fnds, password+j, i); 
					word_list[word_listSize][i] = '\0';
					memcpy(word_list[word_listSize++], password+j, i);
				}
				else {
					memset(wildcardArray, 0, wildcardArraySize);
					if(i>wildcardArraySize) i = wildcardArraySize;
					memset(wildcardArray, wildcard, i);
					strncat(str_fnds, wildcardArray, strlen(wildcardArray));
				}
				char tmp_str[256];
				sprintf(tmp_str, "(%i aus %i Zeichen)", i, strlen(password));
			}
	if (!t_flag)
		strcat(str_fnds, " -");
}



/* **********************************
   05/10/2008 Florian Marchal
   integrated the new Password Entropy Checker based on Henrik Koy's password checking approach
   ********************************** */

class PasswordEntropyChecker {
public:
	// constructor
	PasswordEntropyChecker(const std::string &_password, closure_info **_closureMatrix, unsigned long dict_size = 0);
	// destructor
	~PasswordEntropyChecker();

	// password checking function
	void check(const int &_depth, const int &_length, const double &_entropy);

	// returns the determined entropy
	double getPasswordEntropy() const { return passwordEntropy[passwordLength]; };
	// returns a string with the determined password components
	std::string getPasswordComponents() const { return passwordComponentsString; };

private:
	// the password to be checked
	std::string password;
	double bits_perChar;
	double entropy_dictionary_word;
	// the length of the password
	int passwordLength;
	// the closure matrix based on a dictionary
	closure_info **closureMatrix;

	// the determined password entropy
	double *passwordEntropy;
	// the determined password components as string (separated with the '+' character)
	std::string passwordComponentsString;

	// the password components
	char **passwordComponents;
};

PasswordEntropyChecker::PasswordEntropyChecker(const std::string &_password, closure_info **_closureMatrix, unsigned long dict_size) {
	password = _password;
	closureMatrix = _closureMatrix;

	// determine the password length
	passwordLength = password.length();

	// allocate memory for the password components
	passwordComponents = new char*[passwordLength];
	passwordEntropy    = new double[passwordLength+1];

	if ( !dict_size )
		entropy_dictionary_word = 14.0; // FIXME arbitrary value 
	else
		entropy_dictionary_word = log((double)dict_size);

	int charSpace;
	KeePassCharSpace(password.c_str(), charSpace);
	if ( charSpace > 0 )
		bits_perChar = log((double)charSpace)/log(2.0);
	else
		bits_perChar = 0.0;
	for (int i=0; i<passwordLength; i++)
		passwordComponents[i] = new char[passwordLength+1];
	for (int i=0; i<=passwordLength; i++)
		passwordEntropy[i] = (double)((i+1) * 8);
}

PasswordEntropyChecker::~PasswordEntropyChecker() {
	// free memory of the password components
	for (int i=0; i<passwordLength; i++)
		delete []passwordComponents[i];
	delete []passwordComponents;
	delete []passwordEntropy;
}

void PasswordEntropyChecker::check(const int &_depth, const int &_length, const double &_entropy) 
{
	double delta_entropy;

	if ( _length >= passwordLength )
	{
		// build the password components string based on all the password substrings
		passwordComponentsString = passwordComponents[0];
		for(int i=1; i<_depth; i++) {
			passwordComponentsString.append(" + ");
			passwordComponentsString.append(passwordComponents[i]);
		}
		return;
	}

	passwordComponents[_depth][0] = password[_length];
	passwordComponents[_depth][1] = '\0';
	delta_entropy = bits_perChar;
	if ( _entropy + delta_entropy < passwordEntropy[_length+1] )
	{
		passwordEntropy[_length+1] = _entropy+delta_entropy;
		check(_depth+1, _length+1, _entropy+delta_entropy); // fixme 
	}

	for ( int i=2; i<=passwordLength-_length; i++ )
	{
		strncpy(passwordComponents[_depth], password.c_str() +_length, i);
		passwordComponents[_depth][i] = '\0';
		int charSpace;
		KeePassCharSpace(passwordComponents[_depth], charSpace);
		double charBits = log((double)charSpace)/log(2.0);
		double delta_min = i*8.0;
		if ( closureMatrix[_length][i].flags & PATTERN )
		{
			delta_entropy = 2*charBits+(i-2)*1.0;
			if ( delta_min > delta_entropy )
				delta_min = delta_entropy;
		}
		if ( closureMatrix[_length][i].flags & SERIALS ) 
		{
			delta_entropy = 2*charBits+(i-2)*1.0;
			if ( delta_min > delta_entropy )
				delta_min = delta_entropy;
		}
		if ( closureMatrix[_length][i].flags & KBD_SERIALS ) 
		{
			delta_entropy = 2*charBits+(i-2)*1.0;
			if ( delta_min > delta_entropy )
				delta_min = delta_entropy;
		}
		if ( closureMatrix[_length][i].flags & DICT_WORDS ) 
		{
			delta_entropy = entropy_dictionary_word;
			if ( delta_min > delta_entropy )
				delta_min = delta_entropy;
		}
		if ( delta_min < i*8.0 )
		{
			if ( _entropy + delta_min < passwordEntropy[_length+i] )
			{
				passwordEntropy[_length+i] = _entropy+delta_min;
				check(_depth+1, _length+i, _entropy+delta_min);
			}
		}
	}

	return;
}



// this is the main password checking function; it returns 0 if the given path 
// for the cracklib dictionary is invalid

const int cryptool_pwd_checker_length = 32;

char *checkPassword(char *password, char *path, int hidePassword, double *determinedPasswordEntropy, std::string *determinedPasswordComponents) {
    static char lastpath[STRINGSIZE];
    static PWDICT *pwp;
    char pwtrunced[STRINGSIZE];
    unsigned long int dict_size;

    /* security problem: assume we may have been given a really long
       password (buffer attack) and so truncate it to a workable size;
       try to define workable size as something from which we cannot
       extend a buffer beyond its limits in the rest of the code */
    strncpy(pwtrunced, password, cryptool_pwd_checker_length);
    pwtrunced[cryptool_pwd_checker_length] = '\0'; /* enforce */

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
			// return 0 to indicate the cracklib dictionary could not be found
			perror("PWOpen");
			return 0;
		}
		strncpy(lastpath, path, STRINGSIZE);
    }
    dict_size = PW_WORDS(pwp);


	// flomar, 01/22/2012: save a few parameters for future use (extended GUI)
	int pwLength = 0;
	int pwLengthMinimum = 0;
	int pwDigits = 0;
	int pwDigitsMinimum = 0;
	int pwSpecials = 0;
	int pwSpecialsMinimum = 0;

	int complianceCheckResult = checkPasswordForCompliance(pwtrunced, pwLength, pwLengthMinimum, pwDigits, pwDigitsMinimum, pwSpecials, pwSpecialsMinimum);
	
	LoadString(AfxGetInstanceHandle(), IDS_PQM_PASSWORD_COMPLIANT, pc_str, STR_LAENGE_STRING_TABLE);
	strcat(str_fnds, pc_str);

	// construct password evaluation messages
	if(complianceCheckResult == IDS_PWD_POLICY_COMPLIANT) {
		// password seems to be compliant
		LoadString(AfxGetInstanceHandle(), IDS_PQM_PASSWORD_IS_COMPLIANT, pc_str, STR_LAENGE_STRING_TABLE);
		strcat(str_fnds, pc_str);
	}
	// password does not seem to be compliant
	else {
    if(complianceCheckResult & IDS_PWD_POLICY_TOOSHORT) {
			// password is TOO SHORT
			CString warningMessage;
			warningMessage.Format(IDS_PQM_PASSWORD_NOT_COMPLIANT_TOO_SHORT, pwLength, pwLengthMinimum);
			strcat(str_fnds, warningMessage.GetBuffer());
		}
		if(complianceCheckResult & IDS_PWD_POLICY_TOOFEWDIGITS) {
			// password contains TOO FEW DIGITS
			CString warningMessage;
			warningMessage.Format(IDS_PQM_PASSWORD_NOT_COMPLIANT_TOO_FEW_DIGITS, pwDigits, pwDigitsMinimum);
			strcat(str_fnds, warningMessage.GetBuffer());
		}
		if(complianceCheckResult & IDS_PWD_POLICY_TOOFEWSPECIALCHARACTERS) {
			// password contains TOO FEW SPECIAL CHARACTERS
			CString warningMessage;
			warningMessage.Format(IDS_PQM_PASSWORD_NOT_COMPLIANT_TOO_FEW_SPECIAL_CHARACTERS, pwSpecials, pwSpecialsMinimum);
			strcat(str_fnds, warningMessage.GetBuffer());
		}
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
			if ( substr = checkPasswordAgainstCracklibDictionary( pwd_substr, pwp, dict_size ) )
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
	   new passoword entropy model
	   ********************************* */

	// if we're in the sophisticated CrypTool checking mode, the last two input parameters
	// of this function are not null, and the result is stored in those two parameters
	if(pwd_len) {
		PasswordEntropyChecker passwordEntropyChecker(pwtrunced, closure_matrix, dict_size);
		passwordEntropyChecker.check(0, 0, 0.0);
		double thePasswordEntropy = passwordEntropyChecker.getPasswordEntropy();
		std::string thePasswordComponents = passwordEntropyChecker.getPasswordComponents();

		// set output parameters
		*determinedPasswordEntropy = thePasswordEntropy;
		*determinedPasswordComponents = thePasswordComponents;
	}

	/* *********************************
	   clean up set of substrings
	   *********************************/


	clean_up(closure_matrix, pwd_len, PATTERN, PATTERN);
	clean_up(closure_matrix, pwd_len, SERIALS, SERIALS);
	clean_up(closure_matrix, pwd_len, KBD_SERIALS, KBD_SERIALS);
	clean_up(closure_matrix, pwd_len, DICT_WORDS, DICT_WORDS);
	clean_up(closure_matrix, pwd_len, PATTERN + SERIALS + KBD_SERIALS + DICT_WORDS + COMPOSED_DICT_WORDS + CLOSURE, CLOSURE);


	/* ********************************
	   show substrings 
	   ********************************/
	char **word_list;
	int word_listSize = 0;
	word_list = new char*[pwd_len*pwd_len];
	for (int i=0; i<pwd_len*pwd_len; i++) 
		word_list[i] = new char[pwd_len+1];

	LoadString(AfxGetInstanceHandle(), IDS_PQM_PASSWORD_RECONSTRUCTION, pc_str, STR_LAENGE_STRING_TABLE);
    strcat(str_fnds, pc_str);
	LoadString(AfxGetInstanceHandle(), IDS_PQM_PASSWORD_RECONSTRUCTION_FOUND, pc_str, STR_LAENGE_STRING_TABLE);
	strcat(str_fnds, pc_str);
	get_pwd_substrings( pwd_len, closure_matrix, CLOSURE, password, hidePassword, str_fnds, word_list, word_listSize);

	LoadString(AfxGetInstanceHandle(), IDS_PQM_PASSWORD_RECONSTRUCTION_PATTERNS, pc_str, STR_LAENGE_STRING_TABLE);
    strcat(str_fnds, pc_str);
	get_pwd_substrings( pwd_len, closure_matrix, PATTERN, password, hidePassword, str_fnds, word_list, word_listSize);

	LoadString(AfxGetInstanceHandle(), IDS_PQM_PASSWORD_RECONSTRUCTION_SEQUENCES, pc_str, STR_LAENGE_STRING_TABLE);
    strcat(str_fnds, pc_str);
	get_pwd_substrings( pwd_len, closure_matrix, SERIALS, password, hidePassword, str_fnds, word_list, word_listSize);

	LoadString(AfxGetInstanceHandle(), IDS_PQM_PASSWORD_RECONSTRUCTION_KEYBOARDSEQUENCES, pc_str, STR_LAENGE_STRING_TABLE);
    strcat(str_fnds, pc_str);
	get_pwd_substrings( pwd_len, closure_matrix, KBD_SERIALS, password, hidePassword, str_fnds, word_list, word_listSize);

	// flomar, 03/24/2010
	// we add the dict size to the line that displays dictionary hits (extern feature request)
	CString reconstructionDictionaryWords;
	// flomar, 01/24/2012: add integral separators (i.e. '1999' -> '1.999')
	CString stringDictSize = createStringNumberWithDigitGrouping(dict_size);
	reconstructionDictionaryWords.Format(IDS_PQM_PASSWORD_RECONSTRUCTION_DICTIONARYWORDS, stringDictSize);
	strcat(str_fnds, (LPCTSTR)(reconstructionDictionaryWords));
	get_pwd_substrings( pwd_len, closure_matrix, DICT_WORDS, password, hidePassword, str_fnds, word_list, word_listSize);

	for (int i=0; i<pwd_len*pwd_len; i++) 
		delete []word_list[i];
	delete []word_list;

	delete []word_stack;
	for ( int i=0; i<=pwd_len; i++ )
		delete []closure_matrix[i];
	delete []closure_matrix;

	return str_fnds;
}



// ****************************************************************************
//
// GLOBAL PASSWORD QUALITY FUNCTIONS
//
// ****************************************************************************

/* ************************************************
   * KEEPASS
   ************************************************ */

#define KEEPASS_CHLOWER              1
#define KEEPASS_CHUPPER              2
#define KEEPASS_CHNUMBER             4
#define KEEPASS_CHSIMPLE_SPECIAL     8
#define KEEPASS_CHEXT_SPECIAL       16
#define KEEPASS_CHHIGH              32
#define KEEPASS_CHESCAPE            64  

int bitset_KeePassCharSet(char ch)
{
	int bitset;
	if (  ch < ' ')					  bitset = KEEPASS_CHESCAPE;		// bChEscape = true;
	if (( ch >= 'A') && ( ch <= 'Z')) bitset = KEEPASS_CHUPPER;			// bChUpper = true;
	if (( ch >= 'a') && ( ch <= 'z')) bitset = KEEPASS_CHLOWER;			// bChLower = true;
	if (( ch >= '0') && ( ch <= '9')) bitset = KEEPASS_CHNUMBER;		// bChNumber = true;
	if (( ch >= ' ') && ( ch <= '/')) bitset = KEEPASS_CHSIMPLE_SPECIAL;// bChSimpleSpecial = true;
	if (( ch >= ':') && ( ch <= '@')) bitset = KEEPASS_CHEXT_SPECIAL;	// bChExtSpecial = true;
	if (( ch >= '[') && ( ch <= '`')) bitset = KEEPASS_CHEXT_SPECIAL;	// bChExtSpecial = true;
	if (( ch >= '{') && ( ch <= '~')) bitset = KEEPASS_CHEXT_SPECIAL;	// bChExtSpecial = true;
	if (  ch > '~')                   bitset = KEEPASS_CHHIGH;			// bChHigh = true;
	return bitset;
}

int KeePassCharSpace(int bitset)
{
	int dwCharSpace = 0;

	const unsigned int CHARSPACE_ESCAPE      = 60;
	const unsigned int CHARSPACE_ALPHA       = 26;
	const unsigned int CHARSPACE_NUMBER      = 10;
	const unsigned int CHARSPACE_SIMPSPECIAL = 16;
	const unsigned int CHARSPACE_EXTSPECIAL  = 17;
	const unsigned int CHARSPACE_HIGH        = 112;

	if (bitset & KEEPASS_CHESCAPE)         dwCharSpace += CHARSPACE_ESCAPE;
	if (bitset & KEEPASS_CHUPPER )         dwCharSpace += CHARSPACE_ALPHA;
	if (bitset & KEEPASS_CHLOWER )         dwCharSpace += CHARSPACE_ALPHA;
	if (bitset & KEEPASS_CHNUMBER)         dwCharSpace += CHARSPACE_NUMBER;
	if (bitset & KEEPASS_CHSIMPLE_SPECIAL) dwCharSpace += CHARSPACE_SIMPSPECIAL;
	if (bitset & KEEPASS_CHEXT_SPECIAL)    dwCharSpace += CHARSPACE_EXTSPECIAL;
	if (bitset & KEEPASS_CHHIGH)           dwCharSpace += CHARSPACE_HIGH;

	return dwCharSpace;
}

int KeePassCharSpace( const char *_password, int &charSpace )
{
	Password password(_password);
	char *pszPassword = password.characters();
	int   dwLen = strlen(pszPassword);
	charSpace = 0;

	if(dwLen == 0)
		return 0;

	int bitset_charSpace = 0;
	for(int i=0; i<dwLen; i++)
		bitset_charSpace |= bitset_KeePassCharSet(pszPassword[i]); 

	charSpace = KeePassCharSpace(bitset_charSpace);
	return dwLen;
}

unsigned int password_bitQualityKeePass(const char *_password)
{
	int dwCharSpace;
	int dwLen = KeePassCharSpace( _password, dwCharSpace );

	if (dwLen == 0 || dwCharSpace == 0)
		return 0;

	double dblBitsPerChar = log((double)dwCharSpace) / log(2.00);
	return (int)(ceil(dblBitsPerChar * (double)dwLen));
}

unsigned int passwordQualityKeePass(const char *_password)
{
	int q = password_bitQualityKeePass(_password);
	return ( q > 128 ) ? 100 : (q * 100) / 128;
}

/* ************************************************
   * MOZILLA
   ************************************************ */

unsigned int passwordQualityMozilla(const char *_password)
{
	Password password(_password);

	int q = 0;
  int len = password.length();
  int dig = password.structure()->numDigits;
  int spe = password.structure()->numSpecials;
  int upp = password.structure()->numUpperCaseLetters;

  if(len >= 1 && len <= 5)
    q += len * 10;
  if(len > 5)
    q += 50;
  q -= 20;

  if(dig >= 1 && dig <= 3)
    q += dig * 10;
  if(dig > 3)
    q += 30;

  if(spe >= 1 && spe <= 3)
    q += spe * 15;
  if(spe > 3)
    q += 45;

  if(upp >= 1 && upp <= 3)
    q += upp * 10;
  if(upp > 3)
    q += 30;

  if(q < 0) q = 0;
  if(q > 100) q = 100;

	return q;
}

/* ************************************************
   * PGP
   ************************************************ */
int pgpEstimatePassphraseQuality(const char*);
int pgpEstimateMinEntropyBits(const char*);
int pgpEstimateMaxEntropyBits(const char*);
int sLog2(const int);
int sGetCategory(const int);
int sGetCategoryLength(const int);

unsigned int passwordQualityPGP(const char *_password)
{
	return pgpEstimatePassphraseQuality(_password);
}

typedef struct pgpAsciiRange_
{
    int base;
    short length;
    short total_length;
} pgpAsciiRange;

static const pgpAsciiRange sAsciiSpace[] = {
 { 0x000000, 32, 32 },
 { 0x000020, 1, 1 },
 { 0x000021, 3, 15 },
 { 0x000024, 1, 1 },
 { 0x000025, 3, 15 },
 { 0x000028, 1, 3 },
 { 0x000029, 1, 3 },
 { 0x00002a, 1, 15 },
 { 0x00002b, 1, 6 },
 { 0x00002c, 1, 15 },
 { 0x00002d, 1, 1 },
 { 0x00002e, 2, 15 },
 { 0x000030, 10, 10 },
 { 0x00003a, 2, 15 },
 { 0x00003c, 3, 6 },
 { 0x00003f, 2, 15 }, 
 { 0x000041, 26, 26 },
 { 0x00005b, 1, 3 },
 { 0x00005c, 1, 15 },
 { 0x00005d, 1, 3 },
 { 0x00005e, 1, 2 },
 { 0x00005f, 1, 1 },
 { 0x000060, 1, 2 },
 { 0x000061, 26, 26 }, 
 { 0x00007b, 1, 3 },
 { 0x00007c, 1, 6 },
 { 0x00007d, 1, 3 },
 { 0x00007e, 1, 6 },
 { 0x00007f, 33, 33 }
};

#define kNumRanges (sizeof(sAsciiSpace)/sizeof(sAsciiSpace[0]))


int pgpEstimatePassphraseQuality(const char *password)
{
  int result = 0;

  int min = pgpEstimateMinEntropyBits(password);
  int max = pgpEstimateMaxEntropyBits(password);

  if(min > max)
    return 0;

  result = max - min;

  result = strlen(password) ? (min + result/2) : (1 * strlen(password)/2);

  return ( result > 128) ? 100 : (result * 100 / 128);
}

int pgpEstimateMinEntropyBits(const char *password)
{
  int result = 0;

  for(int i=0; i<(int)strlen(password); i++)
    result += sLog2( sGetCategoryLength((int)(password[i])));
  
  return result;
}

int pgpEstimateMaxEntropyBits(const char *password)
{
  int i;
  int scope=0;
  int idx;
  int num_unrecognized_ranges=0;

  bool haveRanges[kNumRanges];

  int max_index=0;

  memset(haveRanges, 0, sizeof(haveRanges));

  for( i=0; i<(int)strlen(password); i++ )
  {
    idx = sGetCategory( (int)password[i] );
    if( idx != (int)-1 )
    {
      haveRanges[idx] = true;
      if( idx > max_index )
        max_index = idx;
    }
    else
      num_unrecognized_ranges++;
  }

  for( i=0; i<=max_index; i++ )
  {
    if( haveRanges[i] )
    {
      scope += sAsciiSpace[i].total_length;
      haveRanges[i] = false;
    }
  }

  scope += 1*num_unrecognized_ranges;

  int result = strlen(password) * sLog2( scope );

  return result;
}

// counts the number of bits in c
int sLog2(const int c)
{
  int mask  = (int)(-1);
  int mask1 = 1;
  int log_v = 0;

  if(!c)
    return 0;

  while( c & mask )
  {
    mask <<= 1;
    mask1 <<= 1;
    log_v++;
  }

  /* round */
  mask1 >>= 1;    /* while executed at least once */

  if( c - mask1 < mask1/2 )
    log_v--;

  return log_v;
}

int sGetCategory(const int c)
{
  int i_l = 0;
  int i_r = sizeof(sAsciiSpace)/sizeof(sAsciiSpace[0]);
  int i=i = (i_r-i_l)/2;

  while( i_l < i_r-1 )
  {
    if( c < sAsciiSpace[i].base )
    {
      i_r = i;
      i = (i_l+i)/2;
      continue;
    }

    if( c > sAsciiSpace[i].base + sAsciiSpace[i].length - 1 )
    {
      i_l = i;
      i = (i+i_r)/2;
      continue;
    }

    /* c==sAsciiSpace[i].base */
    return i;
  }

  /* here we have one of 3 possibilities: 'c' is in [i_l], 
     in [i_r], or in between, which means that we don't
     recognize this character */

  if( c >= sAsciiSpace[i_l].base && c < sAsciiSpace[i_l].base+sAsciiSpace[i_l].length )
  {
    return i_l;
  }

  if( c >= sAsciiSpace[i_r].base && c < sAsciiSpace[i_r].base+sAsciiSpace[i_r].length )
  {
    return i_r;
  }

  return -1;	/* not found */
}

int sGetCategoryLength(const int c)
{
  int idx = sGetCategory(c);

  if(idx != -1)
    return sAsciiSpace[idx].total_length;

  return 1;
}



// ****************************************************************************
//
// SOME UTILITY FUNCTIONS
//
// ****************************************************************************

bool isLowerCaseLetter(char c)
{
  if((int)(c) >= (int)('a') && (int)(c) <= (int)('z'))
    return true;
  
  return false;

}

bool isUpperCaseLetter(char c)
{
  if((int)(c) >= (int)('A') && (int)(c) <= (int)('Z'))
    return true;

  return false;
}

bool isDigit(char c)
{
  if((int)(c) >= (int)('0') && (int)(c) <= (int)('9'))
    return true;

  return false;
}

void stringToLowerCase(char *s)
{
  if(!s) return;

  for(unsigned int i=0; i<strlen(s); i++)
    s[i] = (char)(int)(MyToLower(s[i]));
}

void stringCapitalize(char *s)
{
  if(!s) return;

  stringToLowerCase(s);

  s[0] = (char)(int)(MyToUpper(s[0]));
}



// ****************************************************************************
//
// PASSWORD CLASS
//
// ****************************************************************************

Password::Password()
{
  pwCharacters = 0;
  pwLength = 0;

  memset(&pwStructure, 0, sizeof(PasswordStructure));

  pwQuality = 0.0;
}

Password::Password(const char *c)
{
  (*this) = c;

  analyzeStructure();
}

Password::~Password()
{
  if(pwCharacters) delete pwCharacters;
}

void Password::operator=(const char *c)
{
	pwCharacters = 0;
    pwLength = 0;

  if(!c)
  {
    if(pwCharacters) delete pwCharacters;  
    return;
  }

  pwLength = strlen(c);

  if(pwCharacters) delete pwCharacters;
  pwCharacters = new char[pwLength+1];
  memset(pwCharacters, 0, pwLength+1);
  memcpy(pwCharacters, c, pwLength);

  analyzeStructure();
}

void Password::analyzeStructure()
{
  memset(&pwStructure, 0, sizeof(PasswordStructure));

  if(!pwLength || !pwCharacters) return;

  for(int i=0; i<pwLength; i++)
  {
    if(isLowerCaseLetter(pwCharacters[i]))
      pwStructure.numLowerCaseLetters++;
    else if(isUpperCaseLetter(pwCharacters[i]))
      pwStructure.numUpperCaseLetters++;
    else if(isDigit(pwCharacters[i]))
      pwStructure.numDigits++;
    else
      pwStructure.numSpecials++;
  }
}



// ****************************************************************************
//
// PASSWORD FILE CLASS
//
// ****************************************************************************

PasswordFile::PasswordFile()
{
  pwFileCharacters = 0;
  pwFileLength = 0;
}

PasswordFile::~PasswordFile()
{

}

void PasswordFile::operator=(const char *c)
{
  if(!c)
  {
    if(pwFileCharacters) delete pwFileCharacters;
    pwFileCharacters = 0;
    pwFileLength = 0;
    return;
  }

  pwFileLength = strlen(c);

  if(!pwFileLength) return;

  pwFileCharacters = new char[pwFileLength+1];
  memset(pwFileCharacters, 0, pwFileLength+1);
  memcpy(pwFileCharacters, c, pwFileLength);
}