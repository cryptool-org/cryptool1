//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <ctype.h>
#include "ChrTools.h"

//static char lowercase[]="abcdefghijklmnopqrstuvwxyzäöüáàâéèêíìîóòôúùûı";
//static char uppercase[]="ABCDEFGHIJKLMNOPQRSTUVWXYZÄÖÜÁÀÂÉÈÊÍÌÎÓÒÔÚÙÛİ";

BOOL MyIsLower(char c)
{
	return islower(c);
}

BOOL MyIsUpper(char c)
{
	return isupper(c);
}

char MyToUpper(char c)
{
	return toupper(c);
}

char MyToLower(char c)
{
	return tolower(c);
}

char *MyToUpper(char *str)
{
	char *p;
	
	for(p=str;*p;p++) *p = MyToUpper(*p);
	return str;
}


char *MyToLower(char *str)
{
	char *p;
	
	for(p=str;*p;p++) *p = MyToLower(*p);
	return str;
}

void MyToUpper(CString &str)
{
	MyToUpper(str.GetBuffer(0));
	str.ReleaseBuffer();
}

void MyToLower(CString &str)
{
	MyToLower(str.GetBuffer(0));
	str.ReleaseBuffer();
}