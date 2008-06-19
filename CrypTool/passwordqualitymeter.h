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


// passwordqualitymeter.h

// ****************************************************************************
//
// 18.03.2007 Florian Marchal
// Implementierung eines Passwortqualitätsmessers
//
// ****************************************************************************

#ifndef _PASSWORDQUALITYMETER_
#define _PASSWORDQUALITYMETER_

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif

#include <ctype.h>
#include <string.h>
#include <math.h>

// ****************************************************************************
//
// SOME UTILITY FUNCTIONS
//
// ****************************************************************************

///This function indicates whether the argument is a lower case letter.
bool isLowerCaseLetter(char);
///This function indicates whether the argument is an upper case letter.
bool isUpperCaseLetter(char);
///This function indicates whether the argument is a digit.
bool isDigit(char);
///This function converts the string argument to lower case letters.
void stringToLowerCase(char*);
///This function capitalizes the string argument.
void stringCapitalize(char*);



// ****************************************************************************
//
// PASSWORD STRUCTURE (for password analysis)
//
// ****************************************************************************

///This struct implements a password structure used to store which different types of characters a password consists of. Supported character classes include upper and lower case letters, digits and special characters.
struct PasswordStructure
{
  ///The number of lower case letters in the password.
  int numLowerCaseLetters;
  ///The number of upper case letters in the password.
  int numUpperCaseLetters;
  ///The number of digits in the password.
  int numDigits;
  ///The number of special characters in the password.
  int numSpecials;

  ///Construction
  PasswordStructure()
  {
    numLowerCaseLetters = 0;
    numUpperCaseLetters = 0;
    numDigits = 0;
    numSpecials = 0;
  };
};



// ****************************************************************************
//
// PASSWORD CLASS
//
// ****************************************************************************

///This class implements passwords.<br><br>After the password characters are assigned, the password's structure is analyzed (see struct PasswordStructure) automatically. You can use the function structure() to return a reference to the previously analyzed password structure. <b>NOTE</b>: Each character not being a letter or a digit is considered a special character!
class Password
{
  ///A pointer to the characters of the password.
  char *pwCharacters;
  ///The length of the password.  
  int pwLength;
  ///The structure of the password.
  PasswordStructure pwStructure;
  ///This function analyzes the structure of the password.
  void analyzeStructure();
  ///This is the quality of the password (ranging from 0 to 100)
  double pwQuality;

public:
  ///Default constructor.
  Password();
  ///Constructor initializing the password characters.
  Password(const char*);
  ///Virtual destructor.
  virtual ~Password();
  ///This function returns the length of the password.
  int length() { return pwLength; };
  ///This function returns a pointer to the password characters.
  char *characters() { return pwCharacters; };
  ///This function returns a pointer to the password structure.
  PasswordStructure *structure() { return &pwStructure; };
  ///This function returns the quality of a password.
  double quality() { return pwQuality; };
  ///This function sets the quality of a password.
  void setQuality(double q) { pwQuality = q; };
  ///Overridden operator to assign the password characters.
  void operator=(const char*);
};



// ****************************************************************************
//
// PASSWORD FILE CLASS
//
// ****************************************************************************

///This class implements a password file for serial input of passwords.
class PasswordFile
{
  ///The password file name.
  char *pwFileCharacters;
  ///The length of the password file name.
  size_t pwFileLength;

public:
  ///Construction
  PasswordFile();
  ///Destruction
  virtual ~PasswordFile();
  ///This function returns the password file's name.
  char *characters() { return pwFileCharacters; };
  ///This function returns the length of the password file's name.
  size_t length() { return pwFileLength; };
  ///This overloaded operator assigns a specific file name.
  void operator=(const char*);
};



// ****************************************************************************
//
// GLOBAL PASSWORD QUALITY FUNCTIONS
//
// ****************************************************************************

int KeePassCharSpace( const char *_password, int &charSpace );
unsigned int password_bitQualityKeePass(const char *_password);

unsigned int passwordQualityKeePass(const char *_password);
unsigned int passwordQualityMozilla(const char *_password);
unsigned int passwordQualityPGP(const char *_password);



#endif