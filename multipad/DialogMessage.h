#ifndef __DIALOG_MESSAGE_H
#define __DIALOG_MESSAGE_H

#include "stdafx.h"
#include "multipad.h"

//////////////////////////////////////////////////////////////////
//
//
//

#define IDS_STRINGLENGTH 1024
void Message(int IDS_STRING_ID, int FLAGS, int No1 = 0, int No2 = 0);
void Message(int IDS_STRING_ID, int FLAGS, int No, const char * str, bool transpose = false);
void Message(int IDS_STRING_ID, int FLAGS, const char* str1, const char* str2 = NULL);


#endif
