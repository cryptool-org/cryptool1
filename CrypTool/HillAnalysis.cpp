#include "HillAnalysis.h"

#include "stdafx.h"
#include "HillEncryption.h"
#include "CrypToolApp.h"
#include "FileTools.h"
#include "DlgTextOptions.h"


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
	char *d_plain, *d_cipher;
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
	if(theApp.TextOptions.getIgnoreCase())
	{
		// CHECK TO UPPER OR TOLOWER ???
	}

	if ( 0 >= d_plain || 0 >= d_cipher )
	{
		// Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		return -1;
	}

	return 0;
}

#if 0
	
	// Überprüfung, ob Eingabedatei mindestens ein Zeichen enthält. 
	CFile datei(infile, CFile::modeRead);
	long infile_zeichen_anz = 0;
	char c;
	while(datei.Read(&c,1))
	{
		// Falls Gross-/Kleinschreibung ignoriert werden soll,
		// muessen auch die Kleinbuchstaben mitgezaehlt werden.
		if ( hillklasse.ist_erlaubtes_zeichen(c) ||
			( (theApp.TextOptions.getIgnoreCase()) && (MyIsLower(c)) && 
			(hillklasse.ist_erlaubtes_zeichen(MyToUpper(c))) ) )
		{
			infile_zeichen_anz++;
		}
	}
	datei.Close();
	
	if (! infile_zeichen_anz)
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		return;
	}
	// jetzt hat die Eingabedatei auf jeden Fall mehr als ein zu verschlüsselndes Zeichen
	
	// Eingabe des Klartextes bzw. verschluesselten Textes 
	CDlgHillAnaylsis EingabeDialog;	
	
	if (EingabeDialog.DoModal() == IDOK)
	{
		SHOW_HOUR_GLASS
		
		// Falls Gross-/Kleinschreibung ignoriert werden soll:
		// Es werden alle Kleinbuchstaben in Grossbuchstaben umgewandelt
		if(theApp.TextOptions.getIgnoreCase())
		{
			MyToUpper(EingabeDialog.m_EingabeFeld);
		}
		
		int laenge = EingabeDialog.m_EingabeFeld.GetLength();
		
		char *str;
		str = new char[laenge+1];
		// wir legen vielleicht einiges zuviel an Speicher an 
		// (falls viele nicht zu verschluesselnde Zeichen in der Datei vorhanden sind)
		long laenge_str = 0;
		
		int i;
		for (i=0; i<laenge; i++)
		{
			// Kleinbuchstaben wurden schon zu Grossbuchstaben konvertiert, sofern erforderlich;
			// deshalb muss dies hier nicht mehr beruecksichtigt werden.
			if ( hillklasse.ist_erlaubtes_zeichen(EingabeDialog.m_EingabeFeld[i]) )
			{
				str[laenge_str++] = EingabeDialog.m_EingabeFeld[i];
			}
		}
		str[laenge_str] = '\0';
		
		// Hat auch die andere Datei mindestens ein zu verschlüsselndes Zeichen ?
		if (!laenge_str)
		{
			Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		}
		else
		{
			// aus dem Text nur die erlaubten Zeichen uebernehmen und den Text in einen String einlesen
			// infile hat infile_zeichen_anz erlaubte Zeichen
			CFile datei(infile, CFile::modeRead);
			
			char *anderer_str;
			// wir legen vielleicht einiges zuviel an Speicher an
			// (falls viele nicht zu verschluesselnde Zeichen in der Datei vorhanden sind)
			anderer_str = new char[infile_zeichen_anz+1];
			long laenge_anderer_str = 0;
			
			char c;
			while(datei.Read(&c,1))
			{
				if ( hillklasse.ist_erlaubtes_zeichen(c) )
				{
					anderer_str[laenge_anderer_str++] = c;
				}
				// Falls Gross-/Kleinschreibung ignoriert werden soll:
				// Es werden alle Kleinbuchstaben in Grossbuchstaben umgewandelt
				else if ( (theApp.TextOptions.getIgnoreCase()) && MyIsLower(c) && 
					hillklasse.ist_erlaubtes_zeichen(MyToUpper(c)) )
				{
					anderer_str[laenge_anderer_str++] = MyToUpper(c);
				}
			}
			anderer_str[laenge_anderer_str] = '\0';
			datei.Close();
			
			// In das Eingabefeld fuer den Text koennen zwar ueber die Zwischenablage  
			// grosse Dokumente eingegeben werden, aber sie werden nur bis zu einer 
			// gewissen Groesse ins Feld uebernommen.
			// Daher kann es vorkommen, dass der Schluessel gefunden wird, jedoch
			// nicht komplett ueberprueft werden kann. -> Returncode aus der Hillklasse
			
			if (EingabeDialog.m_Klartext == 0)
			{
				// Es wurde ein Klartext eingegeben, also ist der 
				// Text im Fenster der verschluesselte
				hillklasse.set_plaintext(str);
				hillklasse.set_ciphertext(anderer_str);
			}
			else
			{
				// Es wurde ein Klartext eingegeben, also ist der 
				// Text im Fenster der verschluesselte
				hillklasse.set_plaintext(anderer_str);
				hillklasse.set_ciphertext(str);
			}
			
			delete[] str;
			delete[] anderer_str;
			
			
			// Plaintext-Angriff durchfuehren
			CSquareMatrixModN *mat;
			
			int hill_rc;
			int hill_rc_dims[HILL_MAX_DIM_GROSS];

			hill_rc = hillklasse.angriff(EingabeDialog.von, EingabeDialog.bis, &mat, hill_rc_dims);
			
			// Rueckgabewerte siehe hill.h
			if (hill_rc == HILL_OK || hill_rc == HILL_OK_LAENGE_UNTERSCHIEDLICH)	
			{
				if (mat->get_dim() <= 5)
				{
					// Inhalt von mat anzeigen
					CDlgShowKeyHill5x5 AusgabeFenster;
					
					// War einer der Texte kuerzer ?
					if (hill_rc == HILL_OK_LAENGE_UNTERSCHIEDLICH)
					{
						Message(IDS_STRING_MSG_DATALENGTH_MISMATCH,MB_ICONINFORMATION);
					}
					
					// Jetzt muessen die Werte der Matrix in den Variablen der
					// Klasse gespeichert werden.
					AusgabeFenster.MatrixAnzeigen(*mat, mat->get_dim(), hillklasse);
					
					// Es wird immer der Schluessel zum Verschluesseln angezeigt
					AusgabeFenster.m_decrypt = FALSE;
					
					// Fenster anzeigen
					AusgabeFenster.DoModal();
				}
				else
				{
					// Inhalt von mat anzeigen
					CDlgShowKeyHill10x10 AusgabeFenster;
					
					// War einer der Texte kuerzer ?
					if (hill_rc == HILL_OK_LAENGE_UNTERSCHIEDLICH)
					{
						Message(IDS_STRING_MSG_DATALENGTH_MISMATCH,MB_ICONINFORMATION);
					}
					
					// Jetzt muessen die Werte der Matrix in den Variablen der
					// Klasse gespeichert werden.
					AusgabeFenster.MatrixAnzeigen(*mat, mat->get_dim(), hillklasse);
					
					// Es wird immer der Schluessel zum Verschluesseln angezeigt
					AusgabeFenster.m_decrypt = FALSE;
					
					// Fenster anzeigen
					AusgabeFenster.DoModal();
				}
				
				delete mat;
			}
			else if (hill_rc == HILL_NICHT_OK_NICHT_GEFUNDEN)
			{
				Message(IDS_STRING_MSG_KEY_NOT_FOUND_SHORT_TEXT, MB_ICONSTOP);
			}
			else if (hill_rc == HILL_NICHT_OK_WIDERSPRUCH)
			{
				Message(IDS_STRING_MSG_KEY_NOT_FOUND_CONFLICT, MB_ICONSTOP);
			}
			else if (hill_rc == HILL_UNDEF)
			{
				// Es gibt mindestens einmal HILL_NICHT_OK_NICHT_GEFUNDEN
				// und einmal HILL_NICHT_OK_WIDERSPRUCH. Daher die Ergebnisse
				// fuer alle Dimensionen ausgeben.
				CString cstr; // Ausgabefeld aufbauen
				CString nicht_gefunden, 
					widerspruch,
					zahl;
				
				for (i=EingabeDialog.von; i<=EingabeDialog.bis; i++)
				{
					zahl.Format("%d", i);
					
					if (hill_rc_dims[i-1] == HILL_NICHT_OK_NICHT_GEFUNDEN)
					{
						if (! nicht_gefunden.IsEmpty())
						{
							nicht_gefunden += ", ";
						}
						nicht_gefunden += zahl; 
					}
					else if (hill_rc_dims[i-1] == HILL_NICHT_OK_WIDERSPRUCH)
					{
						if (! widerspruch.IsEmpty())
						{
							widerspruch += ", ";
						}
						widerspruch += zahl; 
					}
				}
				
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_KEY_NOT_FOUND_CONFLICT_2,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(pc_str1,pc_str,widerspruch.GetBuffer(0));
				cstr += pc_str1;
				cstr += "\n";
				
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_KEY_NOT_FOUND_2,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(pc_str1,pc_str,nicht_gefunden.GetBuffer(0));
				cstr += pc_str1;
				
				AfxMessageBox(cstr.GetBuffer(0), MB_ICONSTOP);
			}
			else // Das darf nicht passieren, wir geben aus: Der Schluessel wurde nicht gefunden
			{
				Message(IDS_STRING_MSG_KEY_NOT_FOUND, MB_ICONSTOP);
			}
		}
		
		HIDE_HOUR_GLASS
	}
#endif