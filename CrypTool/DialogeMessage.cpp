
#include "DialogeMessage.h"

//////////////////////////////////////////////////////////////////////////////
//
// Message Box Handling
//

int Message( int IDS_STRING_ID, int FLAGS, int No1, int No2 )
{
	char line[IDS_STRINGLENGTH];

	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID, pc_str,STR_LAENGE_STRING_TABLE);
	sprintf( line, pc_str, No1, No2);
	return AfxMessageBox(line, FLAGS);
}

int Message(int IDS_STRING_ID, int FLAGS, int No, const char * str, bool transpose)
{
	char line[IDS_STRINGLENGTH];

	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID, pc_str,STR_LAENGE_STRING_TABLE);
	if ( transpose )
	{
		sprintf( line, pc_str, str, No );
	}
	else
	{
		sprintf( line, pc_str, No, str );
	}
	return AfxMessageBox (line, FLAGS);
}

int Message(int IDS_STRING_ID, int FLAGS, const char* str1, const char* str2)
{
	char line[IDS_STRINGLENGTH];

	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID, pc_str,STR_LAENGE_STRING_TABLE);
	if ( NULL == str2 )
	{
		sprintf( line, pc_str, str1 );
	}
	else
	{
		sprintf( line, pc_str, str1, str2 );
	}
	return AfxMessageBox (line, FLAGS);
}



