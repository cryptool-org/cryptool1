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


// passwordqualitymeter.cpp

// ****************************************************************************
//
// 18.03.2007 Florian Marchal
// Implementierung eines Passwortqualitätsmessers
//
// ****************************************************************************
#include "stdafx.h"
#include "passwordqualitymeter.h"
#include "ChrTools.h"

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
