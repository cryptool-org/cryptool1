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