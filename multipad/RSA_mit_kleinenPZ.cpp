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
	//m_edit13 = 0;
	//}}AFX_DATA_INIT

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
//	DDX_Text(pDX, IDC_EDIT13, m_edit13);
	//}}AFX_DATA_MAP
}
//******************************************************************************



void RSA_mit_kleinenPZ::CheckEdit_Input(CString & m_edit, int & sels, int & sele)

		// sorgt dafür, daß keine syntaktisch falsche Eingabe in die Eingabefelder
		// möglich ist, führende Nullen werden entfernt, die Variablen sels und sele dienen der
		// Formatierung
{
	while((0==m_edit.IsEmpty())&&('0'==m_edit.GetAt(0)))
		//Ruft Funktion IsEmpty auf. Diese gibt 0 zurück, wenn der CString nicht leer ist
		//GetAt(a) gibt Zeichen zurück, das an der a. Position steht
		//in diesem Fall, wenn dieses Zeichen 0 ist, dann geht er in die Schleife
		//Diese Funktionen gelten für die übergebenen Wert aus dem Dialog.
		//* Überprüfung, ob überhaupt was in dem Eingabefeld steht, UND ob das erste Zeichen 0 ist.
	{
		m_edit=m_edit.Right(m_edit.GetLength()-1);
		//* Var. m_edit ist Beispielsweise 0567. Der Rückgabe der Funktion Right gibt dir letzten x
		//* Stellen eines CStrings zurück, in diesem Fall gibt er mir 3 Stllen zurück (length-1), so dass die 0 gelöscht wird
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
			//* die ersten i Stellen von links werden mit den Stellen rechts vom ungültigen Zeichen verbunden
			//* -1 damit das Zeichen an der Position i von m_edit gelöscht wird.

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
	ON_BN_CLICKED(IDC_BUTTON_VERSCHLUESSELN, OnButtonVerschluesseln)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdateEdit2)
	ON_BN_CLICKED(IDC_BUTTON_PZ_GENERIEREN, OnButtonPzGenerieren)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonParameterGenerieren)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonSchluesselGenerieren)
	ON_BN_CLICKED(IDC_BUTTON_ENTSCHLUESSELN, OnButtonEntschluesseln)
	ON_EN_UPDATE(IDC_EDIT10, OnUpdateEdit10)
	ON_EN_UPDATE(IDC_EDIT11, OnUpdateEdit11)
	ON_EN_UPDATE(IDC_EDIT12, OnUpdateEdit12)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten RSA_mit_kleinenPZ 





void RSA_mit_kleinenPZ::OnButtonVerschluesseln() 
{
	UpdateData(true);

	m_eingabe_p=_T("101");//101
	
	m_eingabe_q=_T("113");//113

	m_geheime_parameter=_T("11200");//11200
	//m_geheime_parameter=RSAB.konvertiere_Big_CString((RSAB.konvertiere_CString_Big(m_eingabe_p)-1)*(RSAB.konvertiere_CString_Big(m_eingabe_q)-1));

	m_oeffentliche_parameter_pq=_T("11413");//11413
	//m_oeffentliche_parameter_pq=RSAB.konvertiere_Big_CString((RSAB.konvertiere_CString_Big(m_eingabe_p))*(RSAB.konvertiere_CString_Big(m_eingabe_q)));

	
	//m_oeffentliche_schluessel_e=_T("3");//3
	
	//	m_geheime_schluessel_d =_T("7467");//7467
	

	Big eingabe_p=RSAB.konvertiere_CString_Big(m_eingabe_p);
	Big eingabe_q=RSAB.konvertiere_CString_Big(m_eingabe_q);
	Big geheime_parameter=RSAB.konvertiere_CString_Big(m_geheime_parameter);
	Big geheime_schluessel_d=RSAB.konvertiere_CString_Big(m_geheime_schluessel_d);
	Big oeffentliche_schluessel_e=3;
	Big oeffentliche_parameter_pq=eingabe_p * eingabe_q;



	if (0==m_eingabe_p.IsEmpty() && 0==m_eingabe_q.IsEmpty() && m_eingabe_p!=_T("0") && m_eingabe_q!=_T("0"))
	{
		if ((-1)!=RSAB.extended_euclidian_algorithm((RSAB.konvertiere_CString_Big(m_eingabe_p)-1)*(RSAB.konvertiere_CString_Big(m_eingabe_q)-1),RSAB.konvertiere_CString_Big(m_oeffentliche_schluessel_e)))
		{
			m_geheime_schluessel_d=RSAB.konvertiere_Big_CString(RSAB.extended_euclidian_algorithm((RSAB.konvertiere_CString_Big(m_eingabe_p)-1)*(RSAB.konvertiere_CString_Big(m_eingabe_q)-1),RSAB.konvertiere_CString_Big(m_oeffentliche_schluessel_e)));
		}
		else
		{
			//Fehler Meldung
			// Der angegene öffentliche Parameter ist nicht geeignet. Es wird ein zufälliger öffentlicher Parameter erzeugt.
			
			//oeffentliche Schluessel ausrechnen 

			oeffentliche_schluessel_e=RSAB.erzeuge_oeffentliche_Schluessel_e(geheime_parameter);
			m_oeffentliche_schluessel_e.GetBuffer(500)<<oeffentliche_schluessel_e;
			
			
			//geheime Schuessel ausrechnen
			
			geheime_schluessel_d=RSAB.extended_euclidian_algorithm((eingabe_p -1) * (eingabe_q -1), oeffentliche_schluessel_e);
			m_geheime_schluessel_d.GetBuffer(500)<<geheime_schluessel_d;
			
		}
	
		long anzahl_buchstaben;
		anzahl_buchstaben=256; // Dies sollte auch als option eingestellt werden.

		// Blocklänge - Berechnung

		long block_laenge;
		block_laenge=RSAB.RSA_BlockLaengeBerechnung(eingabe_p * eingabe_q,anzahl_buchstaben); // Hier verwenden wir alle 256 ASCII-Zeichen
//		itoa(block_laenge,m_edit9.GetBuffer(20),10);
		
		//
		m_edit11=m_edit10;
		m_edit12=m_edit10; 
		
		//was ist wenn Block_laenge > Text_laenge?????? Noch zu bearbeiten.
		// Dann sollte Meldung Zahl zu gross angezeigt werden
		// und Blocklänge =textlaenge
		// oder auch Buchstabenweise verschlüsseln?????????????????ß

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
			text_laenge=text_laenge -laenge_last_block + block_laenge; // neu von Roger
		}	
		//
	
		char *text_char;
		char *text_char2;
		//long *text;
		Big *text;
		
		char anschauen[100]; // Wir verwenden nur Zahlen mit höchstens 100 Dezimalstellen!!!!!
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
		
		//neu_text_laenge=numdig(oeffentliche_parameter_pq);

		text_char=(char *) calloc(text_laenge,sizeof(char)); 
		//text_char=(char *) calloc(neu_text_laenge*anzahl_bloecke,sizeof(char)); 
		//text_char2=(char *) calloc(text_laenge,sizeof(char)); 
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
		for (i=0;i<=text_laenge-1;i++) //text_laenge-1
		{
			// konvertiere Ascii-Zeichen in Big-Werte.
			char ptr[1];
			ptr[0]=text_char[i];
			Big z;
			z=from_binary(1,ptr);
			text[i]=z;
						
			long l_test;
			l_test = text[i].get(1);

			char anschauen2[100]; // Wir verwenden nur Zahlen mit höchstens 100 Dezimalstellen!!!!!
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
			//char *tmp;
			
			//tmp=(char *) calloc(neu_text_laenge_block,sizeof(char));
			//sprintf(tmp, "%li", l_test);
//			char tmp[3];
//			sprintf(tmp, "%2X", l_test);
//			if ( ' ' == tmp[0] ) tmp[0] = '0';
//			text_char2[3*i] = tmp[0];
//			text_char2[3*i+1] = tmp[1];
			//text_char2[i+j]=anschauen2[j];
//			if ( i<text_laenge-1 ) text_char2[3*i+2] = ' ';
		} 
//		text_char2[3*text_laenge-1] = 0;	

		//

//	long i;
//	long j;



		m_edit11.GetBufferSetLength(neu_text_laenge*anzahl_bloecke); //m_edit10.GetLength()
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
		
		// Blockweisen-Verschlüsselung

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
				z=text[faktor]; //i
				long l_test;
				l_test = z.get(1);
				
				char anschauen3[100]; // Wir verwenden nur Zahlen mit höchstens 100 Dezimalstellen!!!!!
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

			m_edit12.GetBufferSetLength(neu_text_laenge*anzahl_bloecke); //m_edit10.GetLength()
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
	
	if (1==m_eingabe_p.IsEmpty() || 1==m_eingabe_q.IsEmpty() || m_eingabe_p==_T("0") || m_eingabe_q==_T("0"))
	{
		// Fehler Meldung : Geben/Generieren Sie die Primzahlen!
		m_eingabe_p= _T("");
		m_eingabe_q= _T("");
		m_oeffentliche_parameter_pq= _T("");
		m_geheime_parameter= _T("");
		//m_oeffentliche_schluessel_e= _T("");
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

	/* //zuerst das PARN umschreiben----Roger
	if (false==PARN.Prime_test_Miller_Rabin(atol(m_eingabe_p),100))
	{
		// Eingegebene Zahl p ist keine Primzahl!
		m_eingabe_p= _T("");
		m_oeffentliche_parameter_pq= _T("");
		m_geheime_parameter= _T("");
		//m_oeffentliche_schluessel_e= _T("");
		m_geheime_schluessel_d= _T("");
		goto end;
	}
	if (false==PARN.Prime_test_Miller_Rabin(atol(m_eingabe_q),100))
	{
		// Eingegebene Zahl q ist keine Primzahl!
		m_eingabe_q= _T("");
		m_oeffentliche_parameter_pq= _T("");
		m_geheime_parameter= _T("");
		//m_oeffentliche_schluessel_e= _T("");
		m_geheime_schluessel_d= _T("");
		goto end;
	}
*/


	/*
	//oeffentliche Parameter ausrechnen
	ltoa(atol(m_eingabe_p)*atol(m_eingabe_q),m_oeffentliche_parameter_pq.GetBuffer(20),10);
	
	//geheime Parameter ausrechnen
	ltoa((atol(m_eingabe_p)-1)*(atol(m_eingabe_q)-1),m_geheime_parameter.GetBuffer(20),10);
*/
	end:
	UpdateData(false);

	
}

void RSA_mit_kleinenPZ::OnButtonSchluesselGenerieren() 
{
	UpdateData(true);
/*	
	//was ist wenn Primzahl noch nicht angegeben sind-->Fehlermeldung:Primzahleingeben oder generieren!
	if (1==m_eingabe_p.IsEmpty() || 1==m_eingabe_q.IsEmpty() || m_eingabe_p==_T("0") || m_eingabe_q==_T("0"))
	{
		// Fehler Meldung : Geben/Generieren Sie die Primzahlen!
		m_eingabe_p= _T("");
		m_eingabe_q= _T("");
		m_oeffentliche_parameter_pq= _T("");
		m_geheime_parameter= _T("");
		//m_oeffentliche_schluessel_e= _T("");
		m_geheime_schluessel_d= _T("");
		goto fin;
	}
	
	if (m_eingabe_p == _T("1") || m_eingabe_q==_T("1"))
	{// 1 ist keine Primzahl! Geben Sie eine andere Primzahl ein!
		
		m_eingabe_p=_T("");
		m_eingabe_q= _T("");
		m_oeffentliche_parameter_pq= _T("");
		m_geheime_parameter= _T("");
		//m_oeffentliche_schluessel_e= _T("");
		m_geheime_schluessel_d= _T("");
		goto fin;
	}
	if (false==PARN.Prime_test_Miller_Rabin(atol(m_eingabe_p),100))
	{
		// Eingegebene Zahl p ist keine Primzahl!
		m_eingabe_p= _T("");
		m_oeffentliche_parameter_pq= _T("");
		m_geheime_parameter= _T("");
		//m_oeffentliche_schluessel_e= _T("");
		m_geheime_schluessel_d= _T("");
		goto fin;
	}
	if (false==PARN.Prime_test_Miller_Rabin(atol(m_eingabe_q),100))
	{
		// Eingegebene Zahl q ist keine Primzahl!
		m_eingabe_q= _T("");
		m_oeffentliche_parameter_pq= _T("");
		m_geheime_parameter= _T("");
		//m_oeffentliche_schluessel_e= _T("");
		m_geheime_schluessel_d= _T("");
		goto fin;
	}
	
	//oeffentliche Parameter ausrechnen
	ltoa(atol(m_eingabe_p)*atol(m_eingabe_q),m_oeffentliche_parameter_pq.GetBuffer(20),10);
	
	//geheime Parameter ausrechnen
	ltoa((atol(m_eingabe_p)-1)*(atol(m_eingabe_q)-1),m_geheime_parameter.GetBuffer(20),10);

	
	if (0==m_oeffentliche_parameter_pq.IsEmpty())
		{
		//oeffentliche Parameter ausrechnen
		
		ltoa(atol(m_eingabe_p)*atol(m_eingabe_q),m_oeffentliche_parameter_pq.GetBuffer(20),10);
		
		//geheime Parameter ausrechnen
		ltoa((atol(m_eingabe_p)-1)*(atol(m_eingabe_q)-1),m_geheime_parameter.GetBuffer(20),10);
		}
	

	if ((m_eingabe_p==_T("2") && m_eingabe_q==_T("3")) || (m_eingabe_p==_T("3") && m_eingabe_q==_T("2")))
		{

			goto fin;
		}
	if ((-1)!=RSAB.extended_euclidian_algorithm((atol(m_eingabe_p)-1)*(atol(m_eingabe_q)-1),atol(m_oeffentliche_schluessel_e)))
	{
		ltoa(RSAB.extended_euclidian_algorithm((atol(m_eingabe_p)-1)*(atol(m_eingabe_q)-1),atol(m_oeffentliche_schluessel_e)),m_geheime_schluessel_d.GetBuffer(20),10);
	}
	else
	{
		//Fehler Meldung
		// Der angegene öffentliche Parameter ist nicht geeignet. Es wird ein zufälliger öffentlicher Parameter erzeugt.
		
		//oeffentliche Schluessel ausrechnen
		if ((m_eingabe_p==_T("2") && m_eingabe_q==_T("3")) || (m_eingabe_p==_T("3") && m_eingabe_q==_T("2")))
			{

				
				goto fin;
			}
		
		ltoa(RSAB.erzeuge_oeffentliche_Schluessel_e(atol(m_geheime_parameter)),m_oeffentliche_schluessel_e.GetBuffer(20),10);
		
		//geheime Schuessel ausrechnen
		ltoa(RSAB.extended_euclidian_algorithm((atol(m_eingabe_p)-1)*(atol(m_eingabe_q)-1),atol(m_oeffentliche_schluessel_e)),m_geheime_schluessel_d.GetBuffer(20),10);

	}

	// Hier wird die Blockgröße, die beim RSA benutzt wird, ausgerechnet.
	//itoa(RSAB.RSA_BlockLaengeBerechnung(atol(m_eingabe_p)*atol(m_eingabe_q),129),m_edit9.GetBuffer(20),10);
fin:
*/
	UpdateData(false);

	
}

void RSA_mit_kleinenPZ::OnButtonEntschluesseln() 
{
	UpdateData(true);

	m_edit11=m_edit10;
	m_eingabe_p=_T("101");//101
	
	m_eingabe_q=_T("113");//113

	m_geheime_parameter=_T("11200");//11200
	//m_geheime_parameter=RSAB.konvertiere_Big_CString((RSAB.konvertiere_CString_Big(m_eingabe_p)-1)*(RSAB.konvertiere_CString_Big(m_eingabe_q)-1));

	m_oeffentliche_parameter_pq=_T("11416");//11413
	//m_oeffentliche_parameter_pq=RSAB.konvertiere_Big_CString((RSAB.konvertiere_CString_Big(m_eingabe_p))*(RSAB.konvertiere_CString_Big(m_eingabe_q)));

	
	//m_oeffentliche_schluessel_e=_T("3");//3
	
	m_geheime_schluessel_d =_T("7467");//7467
	

	Big eingabe_p=RSAB.konvertiere_CString_Big(m_eingabe_p);
	Big eingabe_q=RSAB.konvertiere_CString_Big(m_eingabe_q);
	Big geheime_parameter=RSAB.konvertiere_CString_Big(m_geheime_parameter);
	Big geheime_schluessel_d=RSAB.konvertiere_CString_Big(m_geheime_schluessel_d);
	Big oeffentliche_schluessel_e=3; ///////////////////////77
	Big oeffentliche_parameter_pq=eingabe_p * eingabe_q;



	if (0==m_eingabe_p.IsEmpty() && 0==m_eingabe_q.IsEmpty() && m_eingabe_p!=_T("0") && m_eingabe_q!=_T("0"))
	{
		if ((-1)!=RSAB.extended_euclidian_algorithm((RSAB.konvertiere_CString_Big(m_eingabe_p)-1)*(RSAB.konvertiere_CString_Big(m_eingabe_q)-1),RSAB.konvertiere_CString_Big(m_oeffentliche_schluessel_e)))
		{
			m_geheime_schluessel_d=RSAB.konvertiere_Big_CString(RSAB.extended_euclidian_algorithm((RSAB.konvertiere_CString_Big(m_eingabe_p)-1)*(RSAB.konvertiere_CString_Big(m_eingabe_q)-1),RSAB.konvertiere_CString_Big(m_oeffentliche_schluessel_e)));
		}
		else
		{
			//Fehler Meldung
			// Der angegene öffentliche Parameter ist nicht geeignet. Es wird ein zufälliger öffentlicher Parameter erzeugt.
			
			//oeffentliche Schluessel ausrechnen 

			oeffentliche_schluessel_e=RSAB.erzeuge_oeffentliche_Schluessel_e(geheime_parameter);
			m_oeffentliche_schluessel_e.GetBuffer(500)<<oeffentliche_schluessel_e;
			
			
			//geheime Schuessel ausrechnen
			
			geheime_schluessel_d=RSAB.extended_euclidian_algorithm((eingabe_p -1) * (eingabe_q -1), oeffentliche_schluessel_e);
			m_geheime_schluessel_d.GetBuffer(500)<<geheime_schluessel_d;
			
		}
	
		long anzahl_buchstaben;
		anzahl_buchstaben=256; // Dies sollte auch als option eingestellt werden.

		// Blocklänge - Berechnung

		long block_laenge;
		block_laenge=RSAB.RSA_BlockLaengeBerechnung(eingabe_p * eingabe_q,anzahl_buchstaben); // Hier verwenden wir alle 256 ASCII-Zeichen
		m_edit12=m_edit10; 

		//was ist wenn Block_laenge > Text_laenge?????? Noch zu bearbeiten.
		// Dann sollte Meldung Zahl zu gross angezeigt werden
		// und Blocklänge =textlaenge
		// oder auch Buchstabenweise verschlüsseln?????????????????ß

		long text_laenge;//=(m_edit10.GetLength()+1)/3;
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
			laenge_last_block = text_laenge % block_laenge; // beachte, dass  Falls der Text eine Block-Vielfache ist, so ist laenge_last_block=0
			text_laenge=text_laenge -laenge_last_block + block_laenge; // neu von Roger
		}	
		//
	
		char *text_char;
		char *text_char2;
		//long *text;
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
		m_edit10.GetBufferSetLength(m_edit10.GetLength()+1); //m_edit10.GetLength()
		//newlaenge=
			
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
		
		m_edit11.GetBufferSetLength(m_edit10.GetLength()); //m_edit10.GetLength()
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
			for (i=0; i<=anzahl_bloecke-1;i++)   //-2
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
		
		// Blockweisen-Verschlüsselung
		if (laenge_last_block==block_laenge)
		{
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

  
		
			for (i=0;i<=leer_zeichen;i++) //text_laenge-1
			{
				// konvertiere Big in ASCII-Zeichen.
				Big z;
				z=text[i];
				long l_test;
				l_test = z.get(1);
				text_char[i]=l_test;
			}
			
			m_edit12.GetBufferSetLength(leer_zeichen+1);//m_edit10.GetLength()/3
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
		
		}
		else
		{
			for (i=0;i<=anzahl_bloecke-1;i++) //-2
			{
				RSAB.encrypt_block(werte[i], block_laenge, anzahl_buchstaben, ausgabe,atol(m_oeffentliche_parameter_pq),atol(m_oeffentliche_schluessel_e));
			}
			
			//RSAB.encrypt_block(werte[anzahl_bloecke-1], block_laenge, anzahl_buchstaben, ausgabe,atol(m_oeffentliche_parameter_pq),atol(m_oeffentliche_schluessel_e));

			faktor=0;
			for (i=0; i<=anzahl_bloecke-1;i++)//-2
			{
				for (int j=0; j<=block_laenge-1;j++)
				{
					text[j+faktor]=werte[i][j];
				}
				faktor=faktor + block_laenge;
			}
			//
			//for (int j=0; j<=block_laenge-1;j++)
			//{
			//	text[j+faktor]=werte[anzahl_bloecke-1][j];
			//}
			//
		
			for (i=0;i<=text_laenge-1;i++)
			{
				// konvertiere Big in ASCII-Zeichen.
				Big z;
				z=text[i];
				long l_test;
				l_test = z.get(1);
				char tmp[3];
				sprintf(tmp, "%2X", l_test);
				if ( ' ' == tmp[0] ) tmp[0] = '0';
				text_char[3*i] = tmp[0];
				text_char[3*i+1] = tmp[1];
				if ( i<text_laenge-1 ) text_char[3*i+2] = ' ';
			}
			text_char[3*text_laenge-1] = 0;	
			//
			
			m_edit12.GetBufferSetLength(text_laenge);
			for (i=0;i<m_edit12.GetLength();i++)
			{
				
				char trans;
				trans=text_char[i];
				m_edit12.SetAt(i,trans);
			}
		
		}
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
