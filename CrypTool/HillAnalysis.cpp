
#include "HillAnalysis.h"
#include "HillEncryption.h"
#include "CrypToolApp.h"
#include "FileTools.h"
#include "DialogeMessage.h"
#include "DlgTextOptions.h"
#include "keyHillBase.h"
#include "assert.h"


CHillAnalysis::CHillAnalysis(void) 
: fn_plain(0)
, fn_cipher(0)
, dim_from(1)
, dim_to(10)
, mul_direction(0)
{
}

CHillAnalysis::~CHillAnalysis(void)
{
	delete []fn_cipher;
	delete []fn_plain;
}


int CHillAnalysis::init(const char *fn_Plain, const char *fn_Cipher, int dim_From, int dim_To, int mul_Direction)
{
	delete []fn_cipher; 
	fn_cipher = new char[strlen(fn_Cipher)+1]; 
	if ( fn_cipher ) 
		strcpy(fn_cipher, fn_Cipher); 
	else return -1;

	delete []fn_plain;  
	fn_plain  = new char[strlen(fn_Plain)+1];  
	if ( fn_plain ) 
		strcpy(fn_plain, fn_Plain); 
	else return -1;

	assert( dim_From > 0 );
	dim_from = dim_From; 
	assert ( dim_To >= dim_From && dim_To <= 10 );
	dim_to   = dim_To;

	mul_direction = mul_Direction;

	return 0;
}

int CHillAnalysis::analyze(CString &err_str)
{
	CHillEncryption hillklasse((const char*)theApp.TextOptions.getAlphabet());
	char *d_plain = 0, *d_cipher = 0;
	int   s_plain,  s_cipher;
	err_str = _T("");

// load files and perform checks
	if ( 0 > readSource( fn_plain, d_plain, s_plain, 1 ) )
	{
		err_str.LoadString(IDS_PA_COULDNOTOPEN_PLAINFILE);
		return -1;
	}
	if ( 0 > readSource( fn_cipher, d_cipher, s_cipher, 1 ) )
	{
		err_str.LoadString(IDS_PA_COULDNOTOPEN_CIPHERFILE);
		return -1;
	}
	if ( 0 >= d_plain || 0 >= d_cipher )
	{
		err_str.LoadString(IDS_STRING_ERR_INPUT_TEXT_LENGTH);
		return -1;
	}

// Text Options
	if(theApp.TextOptions.getIgnoreCase())
	{
		int i;
		for (i=0; i<s_plain; i++) 
			d_plain[i]  = MyToUpper(d_plain[i]);
		for (i=0; i<s_cipher;i++) 
			d_cipher[i] = MyToUpper(d_cipher[i]);
	}

// Known Plaintext Attack
	hillklasse.set_plaintext (d_plain);
	hillklasse.set_ciphertext(d_cipher);
	delete []d_plain;
	delete []d_cipher;
	CSquareMatrixModN *mat = 0;
	int hill_rc_dims[HILL_MAX_DIM_GROSS];
	int hill_rc = hillklasse.angriff(dim_from, dim_to, mat, hill_rc_dims);

// Evaluate Results
	if ( HILL_OK == hill_rc || HILL_OK_LAENGE_UNTERSCHIEDLICH == hill_rc )
	{ // SUCCESS ...
		if ( mul_direction )
		{ // transpose
			long t;
			int i, j;
			for (i=0; i<mat->get_dim(); i++)
				for (j=0; j<i; j++)
				{
					t = mat->operator ()(i, j);
					mat->operator ()(i, j) = mat->operator ()(j,i);
					mat->operator ()(j,i) = t;
				}
		}

		if (hill_rc == HILL_OK_LAENGE_UNTERSCHIEDLICH)
			Message(IDS_STRING_MSG_DATALENGTH_MISMATCH,MB_ICONINFORMATION);

      CKeyHillBase keyHill;
      keyHill.run_showKey( mat, mul_direction );

      delete mat;
		return 0;
	}
	else
	{ // KEY NOT FOUND ...
		switch ( hill_rc ) { // ERROR CASES
			case HILL_NICHT_OK_NICHT_GEFUNDEN:
				err_str.LoadString(IDS_STRING_MSG_KEY_NOT_FOUND_SHORT_TEXT);
				break;
			case HILL_NICHT_OK_WIDERSPRUCH:
				err_str.LoadString(IDS_STRING_MSG_KEY_NOT_FOUND_CONFLICT);
				break;
			case HILL_UNDEF:
				{
					// Es gibt mindestens einmal HILL_NICHT_OK_NICHT_GEFUNDEN
					// und einmal HILL_NICHT_OK_WIDERSPRUCH. Daher die Ergebnisse
					// fuer alle Dimensionen ausgeben.
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
					err_str = pc_str1; err_str += "\n";
					LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_KEY_NOT_FOUND_2,pc_str,STR_LAENGE_STRING_TABLE);
					sprintf(pc_str1,pc_str,nicht_gefunden.GetBuffer(0));
					err_str += pc_str1;
				}
				break;
			default:
				err_str.LoadString(IDS_STRING_MSG_KEY_NOT_FOUND);
				break;
		}
		return -2;
	}

	return 0;
}


