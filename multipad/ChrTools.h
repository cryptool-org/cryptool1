//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

BOOL MyIsLower(char c);
BOOL MyIsUpper(char c);
char MyToUpper(char c);
char MyToLower(char c);
char *MyToUpper(char *str);
char *MyToLower(char *str);
void MyToUpper(CString &str);
void MyToLower(CString &str);

int  encodeASCII( char *strOut, int &strOutPtr, const int strOutSize, const char chrIn, const char* filter);
int  encodeASCII(      char *strOut,       int &strOutPtr, const int strOutSize, 
	  		     const char *strIn,  const int  strInPtr,  const int length, const char* filter);
int codedASCIIBlockLength( CString &StrIn, const int start, const int length );
int  decodeASCII(      char *strOut, int &strOutPtr, const int strOutSize, 
	  		     const char *strIn,  int strInPtr,  const int length );