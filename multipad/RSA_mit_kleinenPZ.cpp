// RSA_mit_kleinenPZ.cpp: Implementierungsdatei
//
#include "stdafx.h"
#include "Afx.h"
#include "multipad.h"
#include "RSA_mit_kleinenPZ.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld RSA_mit_kleinenPZ 


RSA_mit_kleinenPZ::RSA_mit_kleinenPZ(CWnd* pParent /*=NULL*/)
: CDialog(RSA_mit_kleinenPZ::IDD, pParent) 
{
	
	//{{AFX_DATA_INIT(RSA_mit_kleinenPZ)
	m_eingabe_p = _T("");
	m_eingabe_q = _T("");
	m_geheime_parameter = _T("");
	m_oeffentliche_parameter_pq = _T("");
	m_oeffentliche_schluessel_e = _T("3");
	m_geheime_schluessel_d = _T("");
	m_edit10 = _T("");
	m_edit11 = _T("");
	m_edit12 = _T("");
	m_Encryption = _T("");
	m_HeaderPlainCipherText = _T("");
	m_CodingDecryption = _T("");
	m_TextOptions = 0;
	m_CryptMode = 0;
	//}}AFX_DATA_INIT

	LoadString(AfxGetInstanceHandle(),IDS_RSA_MKPZ_PLAINTEXT,pc_str,STR_LAENGE_STRING_TABLE);
	m_HeaderPlainCipherText = pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_RSA_MKPZ_CODING_PLAINTEXT,pc_str,STR_LAENGE_STRING_TABLE);
	m_CodingDecryption = pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_RSA_MKPZ_ENCRYPTION,pc_str,STR_LAENGE_STRING_TABLE);
	m_Encryption = pc_str;
}


void RSA_mit_kleinenPZ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RSA_mit_kleinenPZ)
	DDX_Control(pDX, IDC_EDIT11, m_control_edit11);
	DDX_Control(pDX, IDC_EDIT12, m_control_edit12);
	DDX_Control(pDX, IDC_EDIT10, m_control_edit10);
	DDX_Control(pDX, IDC_EDIT2, m_control_q);
	DDX_Control(pDX, IDC_EDIT1, m_control_p);
	DDX_Text(pDX, IDC_EDIT1, m_eingabe_p);
	DDX_Text(pDX, IDC_EDIT2, m_eingabe_q);
	DDX_Text(pDX, IDC_EDIT4, m_geheime_parameter);
	DDX_Text(pDX, IDC_EDIT3, m_oeffentliche_parameter_pq);
	DDX_Text(pDX, IDC_EDIT5, m_oeffentliche_schluessel_e);
	DDX_Text(pDX, IDC_EDIT6, m_geheime_schluessel_d);
	DDX_Text(pDX, IDC_EDIT10, m_edit10);
	DDX_Text(pDX, IDC_EDIT11, m_edit11);
	DDX_Text(pDX, IDC_EDIT12, m_edit12);
	DDX_Text(pDX, IDC_ENCRYPTION, m_Encryption);
	DDX_Text(pDX, IDC_HEADER_PLAIN_CIPHER_TEXT, m_HeaderPlainCipherText);
	DDX_Text(pDX, IDC_CODING_DECRYPTION, m_CodingDecryption);
	DDX_Radio(pDX, IDC_STANDARD_ALPHABET, m_TextOptions);
	DDX_Radio(pDX, IDC_VERSCHLUESSELN, m_CryptMode);
	//}}AFX_DATA_MAP
}
//******************************************************************************



void RSA_mit_kleinenPZ::CheckEdit_Input(CString & m_edit, int & sels, int & sele)

		// sorgt daf�r, da� keine syntaktisch falsche Eingabe in die Eingabefelder
		// m�glich ist, f�hrende Nullen werden entfernt, die Variablen sels und sele dienen der
		// Formatierung
{
	while((0==m_edit.IsEmpty())&&('0'==m_edit.GetAt(0)))
		//Ruft Funktion IsEmpty auf. Diese gibt 0 zur�ck, wenn der CString nicht leer ist
		//GetAt(a) gibt Zeichen zur�ck, das an der a. Position steht
		//in diesem Fall, wenn dieses Zeichen 0 ist, dann geht er in die Schleife
		//Diese Funktionen gelten f�r die �bergebenen Wert aus dem Dialog.
		//* �berpr�fung, ob �berhaupt was in dem Eingabefeld steht, UND ob das erste Zeichen 0 ist.
	{
		m_edit=m_edit.Right(m_edit.GetLength()-1);
		//* Var. m_edit ist Beispielsweise 0567. Der R�ckgabe der Funktion Right gibt dir letzten x
		//* Stellen eines CStrings zur�ck, in diesem Fall gibt er mir 3 Stllen zur�ck (length-1), so dass die 0 gel�scht wird
		sels=sele=0;								
	}

	int exp_counter=0;
	for(int i=0;i<m_edit.GetLength();i++)
	{
		char ch=m_edit.GetAt(i);
		//* GetAt=holt sich das Zeichen an der i. Stelle
		if((ch>='0')&&(ch<='9'))
		{
			
		}
		else
		{
			m_edit=m_edit.Left(i)+m_edit.Right(m_edit.GetLength()-i-1);	
			//* die ersten i Stellen von links werden mit den Stellen rechts vom ung�ltigen Zeichen verbunden
			//* -1 damit das Zeichen an der Position i von m_edit gel�scht wird.

			if(i<=sele)
			{
				sele--;
				sels--;
			}
			i--;
		}
	}

}
//***********************************************************************


BEGIN_MESSAGE_MAP(RSA_mit_kleinenPZ, CDialog)
	//{{AFX_MSG_MAP(RSA_mit_kleinenPZ)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdateEdit2)
	ON_BN_CLICKED(IDC_BUTTON_PZ_GENERIEREN, OnButtonPzGenerieren)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonParameterGenerieren)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonSchluesselGenerieren)
	ON_EN_UPDATE(IDC_EDIT10, OnUpdateEdit10)
	ON_EN_UPDATE(IDC_EDIT11, OnUpdateEdit11)
	ON_EN_UPDATE(IDC_EDIT12, OnUpdateEdit12)
	ON_BN_CLICKED(IDC_BUTTON_VER_ENT_SCHLUESSELN, OnButtonEnDeCrypt)
	ON_BN_CLICKED(IDC_VERSCHLUESSELN, OnSelectVerschluesseln)
	ON_BN_CLICKED(IDC_ENTSCHLUESSELN, OnSelectEntschluesseln)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten RSA_mit_kleinenPZ 





void RSA_mit_kleinenPZ::Verschluesseln() 
{
	UpdateData(true);

	m_geheime_parameter=RSAB.konvertiere_Big_CString((RSAB.konvertiere_CString_Big(m_eingabe_p)-1)*(RSAB.konvertiere_CString_Big(m_eingabe_q)-1));

	m_oeffentliche_parameter_pq=RSAB.konvertiere_Big_CString((RSAB.konvertiere_CString_Big(m_eingabe_p))*(RSAB.konvertiere_CString_Big(m_eingabe_q)));

	Big eingabe_p=RSAB.konvertiere_CString_Big(m_eingabe_p);
	Big eingabe_q=RSAB.konvertiere_CString_Big(m_eingabe_q);
	Big geheime_parameter= (eingabe_p -1)*(eingabe_q -1);
	Big geheime_schluessel_d;
	Big oeffentliche_schluessel_e;
	Big oeffentliche_parameter_pq=eingabe_p * eingabe_q;

//	Fehler Meldung "Eingegebene Zahl eingabe_p ist keine Primzahl"
//	if (0==prime(einagbe_q))
//	{
//		m_eingabe_q=_T("");
//		m_geheime_parameter = _T("");
//		m_oeffentliche_parameter_pq = _T("");
//		m_oeffentliche_schluessel_e = _T("3");
//		m_geheime_schluessel_d = _T("");
//	}



//	Fehler Meldung "Eingegebene Zahl eingabe_q ist keine Primzahl"
//	if (0==prime(einagbe_q))
//	{
//		m_eingabe_q=_T("");
//		m_geheime_parameter = _T("");
//		m_oeffentliche_parameter_pq = _T("");
//		m_oeffentliche_schluessel_e = _T("3");
//		m_geheime_schluessel_d = _T("");
//	}


	// Falls alle Eingaben korrekt sind.

	if (0==m_eingabe_p.IsEmpty() && 0==m_eingabe_q.IsEmpty() && m_eingabe_p!=_T("0") && m_eingabe_q!=_T("0") && 1==prime(eingabe_p) && 1==prime(eingabe_q))
	{
		if ((-1)!=RSAB.extended_euclidian_algorithm((RSAB.konvertiere_CString_Big(m_eingabe_p)-1)*(RSAB.konvertiere_CString_Big(m_eingabe_q)-1),RSAB.konvertiere_CString_Big(m_oeffentliche_schluessel_e)))
		{
			oeffentliche_schluessel_e=RSAB.konvertiere_CString_Big(m_oeffentliche_schluessel_e);
			geheime_schluessel_d=RSAB.extended_euclidian_algorithm((eingabe_p -1) * (eingabe_q -1), oeffentliche_schluessel_e);
			m_geheime_schluessel_d.GetBuffer(500)<<geheime_schluessel_d;
		}
		else
		{
			//Fehler Meldung
			// "Der angegebene �ffentliche Parameter ist nicht geeignet. Es wird ein zuf�lliger �ffentlicher Parameter erzeugt."
			
			//oeffentliche Schluessel ausrechnen 

			oeffentliche_schluessel_e=RSAB.erzeuge_oeffentliche_Schluessel_e(geheime_parameter);
			m_oeffentliche_schluessel_e.GetBuffer(500)<<oeffentliche_schluessel_e;
			
			//geheime Schuessel ausrechnen
			
			geheime_schluessel_d=RSAB.extended_euclidian_algorithm((eingabe_p -1) * (eingabe_q -1), oeffentliche_schluessel_e);
			m_geheime_schluessel_d.GetBuffer(500)<<geheime_schluessel_d;
			
		}
	
		long anzahl_buchstaben;
		
		// Option: Dies sollte auch als option eingestellt werden.
		anzahl_buchstaben=256; 

		// Blockl�nge - Berechnung

		long block_laenge;

		// Option: Dies sollte auch als option eingestellt werden.
		block_laenge=1;

//		block_laenge=RSAB.RSA_BlockLaengeBerechnung(eingabe_p * eingabe_q,anzahl_buchstaben); // Hier verwenden wir alle 256 ASCII-Zeichen

		m_edit11=m_edit10;
		m_edit12=m_edit10; 

//		text_laenge und anzahl_bloecke ausrechnen
		
		long text_laenge=m_edit10.GetLength();
		long anzahl_bloecke ;
		long laenge_last_block;
		if (text_laenge % block_laenge==0)
		{	
			anzahl_bloecke=text_laenge / block_laenge;
			laenge_last_block= block_laenge;
		}
		else
		{
			
			anzahl_bloecke = (text_laenge / block_laenge)+1;
			laenge_last_block = text_laenge % block_laenge; // beachte, dass  Falls der Text eine Block-Vielfache ist, so ist laenge_last_block=0
			text_laenge=text_laenge -laenge_last_block + block_laenge; 
		}	
		
	
		char *text_char;
		char *text_char2;
		Big *text;
		
		char anschauen[100]; // Wir verwenden nur Zahlen mit h�chstens 100 Dezimalstellen!!!!!
		anschauen<<oeffentliche_parameter_pq;


		int neu_text_laenge;
		for (int i=0;i<=100;i++)
		{
			if (anschauen[i]>='0' && anschauen[i]<='9')
			{
				neu_text_laenge=i+1;
			}
			else 
			{
				neu_text_laenge=neu_text_laenge+1;
				goto arret;
			}
		}
arret:
		
		text_char=(char *) calloc(text_laenge,sizeof(char)); 
		text_char2=(char *) calloc(neu_text_laenge*anzahl_bloecke,sizeof(char)); 

		text = new Big[text_laenge];

		Big **werte;

		werte = new Big*[anzahl_bloecke];

		for (i=0;i<=anzahl_bloecke-1;i++)
		{
			werte[i] = new Big[block_laenge];
		}
		
		for (i=0;i<=m_edit10.GetLength()-1;i++)
		{
			text_char[i]=m_edit10.GetAt(i);
		}
		for (i=m_edit10.GetLength();i<=text_laenge-1;i++)
		{
			text_char[i]=' ';
		}

		int zaehler=0;
		for (i=0;i<=text_laenge-1;i++) 
		{
			// konvertiere Ascii-Zeichen in Big-Werte.
			char ptr[1];
			ptr[0]=text_char[i];
			Big z;
			z=from_binary(1,ptr);
			text[i]=z;
						
			long l_test;
			l_test = text[i].get(1);

			char anschauen2[100]; // Wir verwenden nur Zahlen mit h�chstens 100 Dezimalstellen!!!!!
			anschauen2<<z;

			int neu_text_laenge_block;
			
			for (int j=0;j<=100;j++)
			{
				if (anschauen2[j]>='0' && anschauen2[j]<='9')
				{
					neu_text_laenge_block=j+1;
					text_char2[zaehler+j]=anschauen2[j];
				}
				else 
				{
					neu_text_laenge_block=neu_text_laenge_block+1;
					if (i!= text_laenge-1) text_char2[zaehler+j]=' ';
					goto arret2;
				}
			}
arret2:;
		zaehler=zaehler+neu_text_laenge_block;
		} 

		m_edit11.GetBufferSetLength(neu_text_laenge*anzahl_bloecke);
		for (i=0;i<m_edit11.GetLength();i++)
		{
			
			char trans;
			trans=text_char2[i];
			m_edit11.SetAt(i,trans);
		}

		for (i=0;i<=m_edit10.GetLength()-1;i++)
		{
			text_char[i]=m_edit10.GetAt(i);
		}
		for (i=m_edit10.GetLength();i<=text_laenge-1;i++)
		{
			text_char[i]=' ';
		}
		long faktor=0;

			for (i=0; i<=anzahl_bloecke-1;i++)  
			{
				for (int j=0; j<=block_laenge-1;j++) 
				{
					werte[i][j]=text[j+faktor];
				}
				faktor=faktor + block_laenge;
			
			}
			
		long ausgabe;
		ausgabe=0;
		
		// Blockweisen-Verschl�sselung

		for (i=0;i<=anzahl_bloecke-1;i++)
			{
				RSAB.encrypt_block(werte[i], block_laenge, anzahl_buchstaben, ausgabe,oeffentliche_parameter_pq,oeffentliche_schluessel_e);
			}
		
			faktor=0;
			for (i=0; i<=anzahl_bloecke-1;i++)
			{
				for (int j=0; j<=block_laenge-1;j++)
				{
					text[j+faktor]=werte[i][j];
				}
				faktor=faktor + block_laenge;
			
			}

  
			zaehler=0;	
			faktor=0;
			for (i=0;i<=anzahl_bloecke-1;i++) //text_laenge-1
			{
				// konvertiere Big in ASCII-Zeichen.
				
				Big z;
				z=text[faktor]; 
				long l_test;
				l_test = z.get(1);
				
				char anschauen3[100]; // Wir verwenden nur Zahlen mit h�chstens 100 Dezimalstellen!!!!!
				anschauen3<<z;


				int neu_text_laenge_block;
				
				for (int j=0;j<=100;j++)
				{
					
					if (anschauen3[j]>='0' && anschauen3[j]<='9')
					{
						neu_text_laenge_block=j+1;
						text_char2[zaehler+j]=anschauen3[j];
					}
					else 
					{
						neu_text_laenge_block=neu_text_laenge_block+1;
						if (i!= text_laenge-1) text_char2[zaehler+j]=' ';
						goto arret3;
					}
				}
arret3:;
				zaehler=zaehler+neu_text_laenge_block;
			faktor =faktor +block_laenge;
			} 

			m_edit12.GetBufferSetLength(neu_text_laenge*anzahl_bloecke);
			for (i=0;i<m_edit12.GetLength();i++)
			{
				
				char trans;
				trans=text_char2[i];
				m_edit12.SetAt(i,trans);
			}
		
		
	}
	else
	{
		return;		
	}
	UpdateData(false);	
	
}


void RSA_mit_kleinenPZ::OnUpdateEdit1() 
{
	UpdateData(true);
	int sels,sele;
	m_control_p.GetSel(sels,sele);
	CheckEdit_Input(m_eingabe_p,sels,sele);
	UpdateData(false);
	m_control_p.SetSel(sels,sele);
	
}

void RSA_mit_kleinenPZ::OnUpdateEdit2() 
{
	UpdateData(true);
	int sels,sele;
	m_control_q.GetSel(sels,sele);
	CheckEdit_Input(m_eingabe_q,sels,sele);
	UpdateData(false);
	m_control_q.SetSel(sels,sele);
	
}

// Primzahlen erzeugen:

void RSA_mit_kleinenPZ::OnButtonPzGenerieren() 
{
	UpdateData(true);
	DlgPrimesGenerator DPG;
	DPG.DoModal();
	atol(DPG.m_edit5);
	ltoa(atol(DPG.m_edit5),m_eingabe_p.GetBuffer(20),10);
	ltoa(atol(DPG.m_edit6),m_eingabe_q.GetBuffer(20),10);

	m_geheime_parameter = _T("");
	m_oeffentliche_parameter_pq = _T("");
	m_oeffentliche_schluessel_e = _T("3");
	m_geheime_schluessel_d = _T("");

	UpdateData(false);
}


void RSA_mit_kleinenPZ::OnButtonParameterGenerieren() 
{
	UpdateData(true);

	Big eingabe_p=RSAB.konvertiere_CString_Big(m_eingabe_p);
	Big eingabe_q=RSAB.konvertiere_CString_Big(m_eingabe_q);
	Big geheime_parameter=(eingabe_p-1)*(eingabe_q -1);
	Big oeffentliche_parameter_pq=eingabe_p * eingabe_q;



	if (1==m_eingabe_p.IsEmpty() || 1==m_eingabe_q.IsEmpty() || m_eingabe_p==_T("0") || m_eingabe_q==_T("0"))
	{
		// Fehler Meldung : "Unvollst�ndige Eingaben! Primzahlen p und q eingeben / generieren"
		m_eingabe_p= _T("");
		m_eingabe_q= _T("");
		m_oeffentliche_parameter_pq= _T("");
		m_geheime_parameter= _T("");
		m_geheime_schluessel_d= _T("");
		goto end;
	}
	if (m_eingabe_p == _T("1") || m_eingabe_q==_T("1"))
		{// 1 ist keine Primzahl! Geben Sie eine andere Primzahl ein!
			m_eingabe_p=_T("");
			m_eingabe_q= _T("");
			m_oeffentliche_parameter_pq= _T("");
			m_geheime_parameter= _T("");
			//m_oeffentliche_schluessel_e= _T("");
			m_geheime_schluessel_d= _T("");
			goto end;
		}

	if (0==prime(eingabe_p))
	{
		// "Eingegebene Zahl p ist keine Primzahl!"
		m_eingabe_p= _T("");
		m_oeffentliche_parameter_pq= _T("");
		m_geheime_parameter= _T("");
		m_geheime_schluessel_d= _T("");
		goto end;
	}
	if (0==prime(eingabe_q))
	{
		// "Eingegebene Zahl q ist keine Primzahl!"
		m_eingabe_q= _T("");
		m_oeffentliche_parameter_pq= _T("");
		m_geheime_parameter= _T("");
		m_geheime_schluessel_d= _T("");
		goto end;
	}

	m_geheime_parameter=RSAB.konvertiere_Big_CString((RSAB.konvertiere_CString_Big(m_eingabe_p)-1)*(RSAB.konvertiere_CString_Big(m_eingabe_q)-1));

	m_oeffentliche_parameter_pq=RSAB.konvertiere_Big_CString((RSAB.konvertiere_CString_Big(m_eingabe_p))*(RSAB.konvertiere_CString_Big(m_eingabe_q)));
		
	end:
	UpdateData(false);

	
}

void RSA_mit_kleinenPZ::OnButtonSchluesselGenerieren() 
{
	UpdateData(true);
	Big eingabe_p=RSAB.konvertiere_CString_Big(m_eingabe_p);
	Big eingabe_q=RSAB.konvertiere_CString_Big(m_eingabe_q);
	Big geheime_parameter=(eingabe_p-1)*(eingabe_q -1);
	//m_geheime_parameter.GetBuffer(500)<<geheime_parameter;
	Big geheime_schluessel_d;
	Big oeffentliche_schluessel_e;
	Big oeffentliche_parameter_pq=eingabe_p * eingabe_q;

	m_geheime_parameter=RSAB.konvertiere_Big_CString((RSAB.konvertiere_CString_Big(m_eingabe_p)-1)*(RSAB.konvertiere_CString_Big(m_eingabe_q)-1));

	m_oeffentliche_parameter_pq=RSAB.konvertiere_Big_CString((RSAB.konvertiere_CString_Big(m_eingabe_p))*(RSAB.konvertiere_CString_Big(m_eingabe_q)));

	if (1==m_eingabe_p.IsEmpty() || 1==m_eingabe_q.IsEmpty() || m_eingabe_p==_T("0") || m_eingabe_q==_T("0"))
	{
		// Fehler Meldung : "Unvollst�ndige Eingaben! Primzahlen p und q eingeben / generieren"
		m_eingabe_p= _T("");
		m_eingabe_q= _T("");
		m_oeffentliche_parameter_pq= _T("");
		m_geheime_parameter= _T("");
		m_geheime_schluessel_d= _T("");
		goto end;
	}
	if (m_eingabe_p == _T("1") || m_eingabe_q==_T("1"))
		{// 1 ist keine Primzahl! Geben Sie eine andere Primzahl ein!
			m_eingabe_p=_T("");
			m_eingabe_q= _T("");
			m_oeffentliche_parameter_pq= _T("");
			m_geheime_parameter= _T("");
			//m_oeffentliche_schluessel_e= _T("");
			m_geheime_schluessel_d= _T("");
			goto end;
		}


	 //zuerst das PARN umschreiben----Roger
	if (0==prime(eingabe_p))
	{
		// "Eingegebene Zahl p ist keine Primzahl!"
		m_eingabe_p= _T("");
		m_oeffentliche_parameter_pq= _T("");
		m_geheime_parameter= _T("");
		m_geheime_schluessel_d= _T("");
		goto end;
	}
	if (0==prime(eingabe_q))
	{
		// "Eingegebene Zahl q ist keine Primzahl!"
		m_eingabe_q= _T("");
		m_oeffentliche_parameter_pq= _T("");
		m_geheime_parameter= _T("");
		m_geheime_schluessel_d= _T("");
		goto end;
	}

	

	if ((-1)!=RSAB.extended_euclidian_algorithm((RSAB.konvertiere_CString_Big(m_eingabe_p)-1)*(RSAB.konvertiere_CString_Big(m_eingabe_q)-1),RSAB.konvertiere_CString_Big(m_oeffentliche_schluessel_e)))
		{
			oeffentliche_schluessel_e=RSAB.konvertiere_CString_Big(m_oeffentliche_schluessel_e);
			geheime_schluessel_d=RSAB.extended_euclidian_algorithm((eingabe_p -1) * (eingabe_q -1), oeffentliche_schluessel_e);
			m_geheime_schluessel_d.GetBuffer(500)<<geheime_schluessel_d;
		}
		else
		{
			//Fehler Meldung
			// "Der angegebene �ffentliche Parameter ist nicht geeignet. Es wird ein zuf�lliger �ffentlicher Parameter erzeugt."
			
			//oeffentliche Schluessel ausrechnen 

			oeffentliche_schluessel_e=RSAB.erzeuge_oeffentliche_Schluessel_e(geheime_parameter);
			m_oeffentliche_schluessel_e.GetBuffer(500)<<oeffentliche_schluessel_e;
			
			//geheime Schuessel ausrechnen
			
			geheime_schluessel_d=RSAB.extended_euclidian_algorithm((eingabe_p -1) * (eingabe_q -1), oeffentliche_schluessel_e);
			m_geheime_schluessel_d.GetBuffer(500)<<geheime_schluessel_d;
		}

	end:
	UpdateData(false);	
}

void RSA_mit_kleinenPZ::Entschluesseln() 
{
	UpdateData(true);

	m_edit11=m_edit10;

	Big eingabe_p=RSAB.konvertiere_CString_Big(m_eingabe_p);
	Big eingabe_q=RSAB.konvertiere_CString_Big(m_eingabe_q);
	Big geheime_parameter=(eingabe_p-1)*(eingabe_q -1);
	m_geheime_parameter.GetBuffer(500)<<geheime_parameter;
	Big geheime_schluessel_d;
	Big oeffentliche_schluessel_e;
	Big oeffentliche_parameter_pq=eingabe_p * eingabe_q;

//	Fehler Meldung "Eingegebene Zahl eingabe_p ist keine Primzahl"
//	if (0==prime(einagbe_q))
//	{
//		m_eingabe_q=_T("");
//		m_geheime_parameter = _T("");
//		m_oeffentliche_parameter_pq = _T("");
//		m_oeffentliche_schluessel_e = _T("3");
//		m_geheime_schluessel_d = _T("");
//	}



//	Fehler Meldung "Eingegebene Zahl eingabe_q ist keine Primzahl"
//	if (0==prime(einagbe_q))
//	{
//		m_eingabe_q=_T("");
//		m_geheime_parameter = _T("");
//		m_oeffentliche_parameter_pq = _T("");
//		m_oeffentliche_schluessel_e = _T("3");
//		m_geheime_schluessel_d = _T("");
//	}


	if (0==m_eingabe_p.IsEmpty() && 0==m_eingabe_q.IsEmpty() && m_eingabe_p!=_T("0") && m_eingabe_q!=_T("0") && 1==prime(eingabe_p) && 1==prime(eingabe_q))
	{
		if ((-1)!=RSAB.extended_euclidian_algorithm((RSAB.konvertiere_CString_Big(m_eingabe_p)-1)*(RSAB.konvertiere_CString_Big(m_eingabe_q)-1),RSAB.konvertiere_CString_Big(m_oeffentliche_schluessel_e)))
		{
			oeffentliche_schluessel_e=RSAB.konvertiere_CString_Big(m_oeffentliche_schluessel_e);
			geheime_schluessel_d=RSAB.extended_euclidian_algorithm((eingabe_p -1) * (eingabe_q -1), oeffentliche_schluessel_e);
			m_geheime_schluessel_d.GetBuffer(500)<<geheime_schluessel_d;
		}
		else
		{
			//Fehler Meldung
			// "Der angegebene �ffentliche Parameter ist nicht geeignet. Es wird ein zuf�lliger �ffentlicher Parameter erzeugt."
			
			//oeffentliche Schluessel ausrechnen 

			oeffentliche_schluessel_e=RSAB.erzeuge_oeffentliche_Schluessel_e(geheime_parameter);
			m_oeffentliche_schluessel_e.GetBuffer(500)<<oeffentliche_schluessel_e;
			
			//geheime Schuessel ausrechnen
			
			geheime_schluessel_d=RSAB.extended_euclidian_algorithm((eingabe_p -1) * (eingabe_q -1), oeffentliche_schluessel_e);
			m_geheime_schluessel_d.GetBuffer(500)<<geheime_schluessel_d;
		}
	
		long anzahl_buchstaben;
		
		// Option: Dies sollte auch als option eingestellt werden.
		anzahl_buchstaben=256; 

		// Blockl�nge - Berechnung

		long block_laenge;

		// Option: Dies sollte auch als option eingestellt werden.
		block_laenge=1;
//		block_laenge=RSAB.RSA_BlockLaengeBerechnung(eingabe_p * eingabe_q,anzahl_buchstaben); // Hier verwenden wir alle 256 ASCII-Zeichen
		
		m_edit12=m_edit10; 
		
		/*
		Bei der Entschl�sselung muss man darauf achten, da� Eingabe-text (m_edit10) nur aus Zahlen gefolgt von Leerzeichen
		bestehen mu�. Sonst Fehler Meldung anzeigen.
		*/

		long text_laenge;
		int leer_zeichen=0;
		for (int i=0;i<=m_edit10.GetLength()-1;i++)
		{
			if (m_edit10.GetAt(i)==' ') leer_zeichen=leer_zeichen+1;
		}
		text_laenge=block_laenge*(leer_zeichen+1);
		long anzahl_bloecke ;
		long laenge_last_block;
		if (text_laenge % block_laenge==0)
		{	
			anzahl_bloecke=text_laenge / block_laenge;
			laenge_last_block= block_laenge;
		}
		else
		{
			
			anzahl_bloecke = (text_laenge / block_laenge)+1;
			laenge_last_block = text_laenge % block_laenge;
			text_laenge=text_laenge -laenge_last_block + block_laenge;
		}	
		//
	
		char *text_char;
		char *text_char2;
		
		Big *text;
		text_char=(char *) calloc(text_laenge,sizeof(char)); 
		text_char2=(char *) calloc(m_edit10.GetLength()+1,sizeof(char)); 

		long big_text_laenge=leer_zeichen+1;
		text = new Big[big_text_laenge];

		Big **werte;

	
		werte = new Big*[anzahl_bloecke];

		for (i=0;i<=anzahl_bloecke-1;i++)
		{
			werte[i] = new Big[block_laenge];
		}



		long newlaenge;
		m_edit10.GetBufferSetLength(m_edit10.GetLength()+1); 
			
		for (i=0;i<=m_edit10.GetLength()-2;i++)
		{
			text_char2[i]=m_edit10.GetAt(i);
		}
		text_char2[m_edit10.GetLength()-1]=' ';
		
		int count;
		count=0;
		int count2;
		count2=0;
		int count3;
		count3=0;
		Big wert;
		for (i=0;i<=m_edit10.GetLength()-1;)
		{
			if (text_char2[i] !=' ') 
			{
				count++;
				count2++;
			}
			else
			{
					char output[100];
					char ptr[100];
					char ausgabe_char[100];
					output[count]='\0';
					ptr[count]='\0';
					ausgabe_char[count]='\0';
					for (int j=0;j<=count-1;j++)
					{
						
						output[j]=text_char2[j+count2-count];
						ptr[j]=output[j];
					}
					
					wert=ptr;
					
					ausgabe_char<<wert;
					text[count3]=wert;
					count3++;
					
			count2++;
			count=0;
			}
			i++;
		}
		
		m_edit11.GetBufferSetLength(m_edit10.GetLength());
		for (i=0;i<m_edit11.GetLength();i++)
		{
			
			char trans;
			trans=text_char2[i];
			m_edit11.SetAt(i,trans);
		}


		long faktor=0;
		if (laenge_last_block==block_laenge)
		{
			for (i=0; i<=anzahl_bloecke-1;i++)  
			{
				for (int j=0; j<=block_laenge-1;j++) 
				{
					werte[i][j]=text[j+faktor];
					char z[100];
					z<<werte[i][j];
				}
				faktor=faktor + block_laenge;
			
			}
		}
		else
		{
			for (i=0; i<=anzahl_bloecke-1;i++)   
			{
				for (int j=0; j<=block_laenge-1;j++) 
				{
					werte[i][j]=text[j+faktor];
				}
				faktor=faktor + block_laenge;
			}
		}
		long ausgabe;
		ausgabe=0;
		
		// Blockweisen-Verschl�sselung

//		if (laenge_last_block==block_laenge)
//		{
			for (i=0;i<=anzahl_bloecke-1;i++)
			{
				RSAB.encrypt_block(werte[i], block_laenge, anzahl_buchstaben, ausgabe,oeffentliche_parameter_pq,geheime_schluessel_d);
			}
		
			faktor=0;
			for (i=0; i<=anzahl_bloecke-1;i++)
			{
				for (int j=0; j<=block_laenge-1;j++)
				{
					text[j+faktor]=werte[i][j];
				}
				faktor=faktor + block_laenge;
			
			}

  
		
			for (i=0;i<=leer_zeichen;i++)
			{
				// konvertiere Big in ASCII-Zeichen.
				Big z;
				z=text[i];
				long l_test;
				l_test = z.get(1);
				text_char[i]=l_test;
			}
			
			m_edit12.GetBufferSetLength(leer_zeichen+1);
			for (i=0;i<m_edit12.GetLength();i++)
			{
				
				char trans;
				trans=text_char[i];
				m_edit12.SetAt(i,trans);
			}
			for (i=0;i<m_edit12.GetLength();i++)
			{
				
				char trans;
				trans=text_char[i];
				m_edit12.SetAt(i,trans);
			}
		
//		}
		//else
		//{
		//	for (i=0;i<=anzahl_bloecke-1;i++)
		//	{
		//		RSAB.encrypt_block(werte[i], block_laenge, anzahl_buchstaben, ausgabe,atol(m_oeffentliche_parameter_pq),atol(m_oeffentliche_schluessel_e));
		//	}
		//	
		//	
		//	faktor=0;
		//	for (i=0; i<=anzahl_bloecke-1;i++)//-2
		//	{
		//		for (int j=0; j<=block_laenge-1;j++)
		//		{
		//			text[j+faktor]=werte[i][j];
		//		}
		//		faktor=faktor + block_laenge;
		//	}
		//	
		//
		//	for (i=0;i<=text_laenge-1;i++)
		//	{
		//		// konvertiere Big in ASCII-Zeichen.
		//		Big z;
		//		z=text[i];
		//		long l_test;
		//		l_test = z.get(1);
		//		char tmp[3];
		//		sprintf(tmp, "%2X", l_test);
		//		if ( ' ' == tmp[0] ) tmp[0] = '0';
		//		text_char[3*i] = tmp[0];
		//		text_char[3*i+1] = tmp[1];
		//		if ( i<text_laenge-1 ) text_char[3*i+2] = ' ';
		//	}
		//	text_char[3*text_laenge-1] = 0;	
		//	//
		//	
		//	m_edit12.GetBufferSetLength(text_laenge);
		//	for (i=0;i<m_edit12.GetLength();i++)
		//	{
		//		
		//		char trans;
		//		trans=text_char[i];
		//		m_edit12.SetAt(i,trans);
		//	}
		
		//}
		delete []text;
		for (i=0;i<=anzahl_bloecke-1;i++)
		{
			delete []werte[i];		
		}
		delete []werte;
		
	}
	else
	{
		return;		
	}
	//CString

	UpdateData(false);	
}

void RSA_mit_kleinenPZ::OnUpdateEdit10() 
{
	UpdateData(true);
	int sels,sele;
	m_control_edit10.GetSel(sels,sele);
	//CheckEdit_Input(m_edit10,sels,sele);
	UpdateData(false);
	m_control_edit10.SetSel(sels,sele);
	
}

void RSA_mit_kleinenPZ::OnUpdateEdit11() 
{
	UpdateData(true);
	int sels,sele;
	m_control_edit11.GetSel(sels,sele);
	//CheckEdit_Input(m_edit11,sels,sele);
	UpdateData(false);
	m_control_edit11.SetSel(sels,sele);
	
}

void RSA_mit_kleinenPZ::OnUpdateEdit12() 
{
	UpdateData(true);
	int sels,sele;
	m_control_edit12.GetSel(sels,sele);
	//CheckEdit_Input(m_edit12,sels,sele);
	UpdateData(false);
	m_control_edit12.SetSel(sels,sele);
}

void RSA_mit_kleinenPZ::OnButtonEnDeCrypt() 
{
	UpdateData(true);
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	if ( m_CryptMode == 0 ) Verschluesseln();
	else					Entschluesseln();
	UpdateData(false);
}


void RSA_mit_kleinenPZ::OnSelectVerschluesseln() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	UpdateData(true);
	LoadString(AfxGetInstanceHandle(),IDS_RSA_MKPZ_PLAINTEXT,pc_str,STR_LAENGE_STRING_TABLE);
	m_HeaderPlainCipherText = pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_RSA_MKPZ_CODING_PLAINTEXT,pc_str,STR_LAENGE_STRING_TABLE);
	m_CodingDecryption = pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_RSA_MKPZ_ENCRYPTION,pc_str,STR_LAENGE_STRING_TABLE);
	m_Encryption = pc_str;
	UpdateData(false);
}

void RSA_mit_kleinenPZ::OnSelectEntschluesseln() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	UpdateData(true);
	LoadString(AfxGetInstanceHandle(),IDS_RSA_MKPZ_CIPHERTEXT,pc_str,STR_LAENGE_STRING_TABLE);
	m_HeaderPlainCipherText = pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_RSA_MKPZ_ENCIPHERED_TEXT,pc_str,STR_LAENGE_STRING_TABLE);
	m_CodingDecryption = pc_str;
	// LoadString(AfxGetInstanceHandle(),IDS_RSA_MKPZ_ENCRYPTION,pc_str,STR_LAENGE_STRING_TABLE);
	m_Encryption = "";
	m_edit12 = "";
	UpdateData(false);	
}
