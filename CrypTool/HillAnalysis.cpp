#include "HillAnalysis.h"

#include "stdafx.h"
#include "HillEncryption.h"
#include "CrypToolApp.h"
#include "FileTools.h"
#include "DialogeMessage.h"
#include "DlgTextOptions.h"
#include "DlgShowKeyHill5x5.h"
#include "DlgShowKeyHill10x10.h"


CHillAnalysis::CHillAnalysis(void) 
: fn_plain(0)
, fn_cipher(0)
, dim_from(1)
, dim_to(10)
, alphabet_offset(0)
, mul_direction(0)
{
}

CHillAnalysis::~CHillAnalysis(void)
{
}


int CHillAnalysis::init(const char *fn_Plain, const char *fn_Cipher, int dim_From, int dim_To, int alphabet_Offset, int mul_Direction)
{
	return 0;
}

int CHillAnalysis::analyze()
{
	CHillEncryption hillklasse((const char*)theApp.TextOptions.getAlphabet());
	char *d_plain = 0, *d_cipher = 0;
	int   s_plain,  s_cipher;

// load files and perform checks
	if ( 0 > readSource( fn_plain, d_plain, s_plain, 1 ) )
	{
		// FIXME
	}
	if ( 0 > readSource( fn_cipher, d_cipher, s_cipher, 1 ) )
	{
		// FIXME
	}
	if ( 0 >= d_plain || 0 >= d_cipher )
	{
		// Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		return -1;
	}
	if(theApp.TextOptions.getIgnoreCase())
	{
		int i;
		for (i=0; i<s_plain; i++) d_plain[i]  = MyToUpper(d_plain[i]);
		for (i=0; i<s_cipher;i++) d_cipher[i] = MyToUpper(d_cipher[i]);
	}

	hillklasse.set_plaintext (d_plain);
	hillklasse.set_ciphertext(d_cipher);

	delete []d_plain;
	delete []d_cipher;

	CSquareMatrixModN *mat;
	int hill_rc_dims[HILL_MAX_DIM_GROSS];
	int hill_rc = hillklasse.angriff(dim_from, dim_to, &mat, hill_rc_dims);

	// Rueckgabewerte siehe hill.h
	switch ( hill_rc ) {
		case HILL_OK:
		case HILL_OK_LAENGE_UNTERSCHIEDLICH:
			{
				if (hill_rc == HILL_OK_LAENGE_UNTERSCHIEDLICH)
					Message(IDS_STRING_MSG_DATALENGTH_MISMATCH,MB_ICONINFORMATION);

				if (mat->get_dim() <= 5)
				{	
					CDlgShowKeyHill5x5 dlg;		
					dlg.MatrixAnzeigen(*mat, mat->get_dim(), hillklasse);
					dlg.m_decrypt = FALSE;
					dlg.DoModal();
				}
				else
				{
					CDlgShowKeyHill10x10 dlg;
					dlg.MatrixAnzeigen(*mat, mat->get_dim(), hillklasse);
					dlg.m_decrypt = FALSE;
					dlg.DoModal();
				}
				delete mat;
			}
			break;

		case HILL_NICHT_OK_NICHT_GEFUNDEN:
			Message(IDS_STRING_MSG_KEY_NOT_FOUND_SHORT_TEXT, MB_ICONSTOP);
			break;
		case HILL_NICHT_OK_WIDERSPRUCH:
			Message(IDS_STRING_MSG_KEY_NOT_FOUND_CONFLICT, MB_ICONSTOP);
			break;
		case HILL_UNDEF:
			{
				// Es gibt mindestens einmal HILL_NICHT_OK_NICHT_GEFUNDEN
				// und einmal HILL_NICHT_OK_WIDERSPRUCH. Daher die Ergebnisse
				// fuer alle Dimensionen ausgeben.
				CString cstr; // Ausgabefeld aufbauen
				CString nicht_gefunden, widerspruch, zahl;
				int i;
				
				for (i=dim_from; i<=dim_to; i++)
				{
					zahl.Format("%d", i);

					if (hill_rc_dims[i-1] == HILL_NICHT_OK_NICHT_GEFUNDEN)
					{
						if (!nicht_gefunden.IsEmpty()) nicht_gefunden += ", ";
						nicht_gefunden += zahl; 
					}
					else if (hill_rc_dims[i-1] == HILL_NICHT_OK_WIDERSPRUCH)
					{
						if (!widerspruch.IsEmpty())	widerspruch += ", ";
						widerspruch += zahl; 
					}
				}
				
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_KEY_NOT_FOUND_CONFLICT_2,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(pc_str1,pc_str,widerspruch.GetBuffer(0));
				cstr += pc_str1; cstr += "\n";
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_KEY_NOT_FOUND_2,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(pc_str1,pc_str,nicht_gefunden.GetBuffer(0));
				cstr += pc_str1;
				
				AfxMessageBox(cstr.GetBuffer(0), MB_ICONSTOP);
			}
			break;
		default:
			Message(IDS_STRING_MSG_KEY_NOT_FOUND, MB_ICONSTOP);
	}

	return 0;
}


