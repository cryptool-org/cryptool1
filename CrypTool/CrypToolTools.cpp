///////////////////////////////////////////////////////////////////////////////////
//
//
//

#include "CrypToolTools.h"
#include "DialogeMessage.h"
#include "MakeNewName.h"

BOOL CheckAlphabet( int minSize )
{
	if (theApp.TextOptions.m_alphabet.GetLength() < minSize )
	{
		Message(IDS_STRING_MSG_ON_ALPHABET, MB_ICONEXCLAMATION, minSize);
		return FALSE;
	}
	return TRUE;
}


BOOL CheckTextSize( SymbolArray &text, int Threshold )
{
	if(text.GetSize() < Threshold ) 
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, Threshold);
		return FALSE;
	}
	return TRUE;
}


void LoadText( const char *infile, SymbolArray &text )
{
	CWaitCursor WCursor;
	text.Read(infile);
	WCursor.Restore();
}


void GetNewDocTitle(const char *outfile, const char* keyStr, const char* OldTitle, 
					int IDS_STRING_ID, char* title, long titleLength, BOOL Decrypt, int KeyType )
{
	if(Decrypt)
		LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
	else
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID,pc_str,STR_LAENGE_STRING_TABLE);
    MakeNewName3(title,titleLength,pc_str1,pc_str,OldTitle,keyStr);
}

void OpenNewDoc( const char *outfile, const char* keyStr, const char* OldTitle, int IDS_STRING_ID, 
				 BOOL Decrypt, int KeyType )
{
	char title[128];
	CAppDocument *NewDoc;
	NewDoc = theApp.OpenDocumentFileNoMRU( outfile, keyStr, KeyType );
    remove(outfile);
    if(NewDoc) 
	{
		GetNewDocTitle(outfile, keyStr, OldTitle, IDS_STRING_ID, title, 128, Decrypt, KeyType);
	    NewDoc->SetTitle(title);
	}
}
