// HybridEncr.cpp: Implementierungsdatei
//


#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgHybridEncryptionDemo.h"
#include "DialogeMessage.h"
#include <fstream.h>
#include "FileTools.h"
#include <sys\stat.h>
#include "DlgRSAEncryption.h"
#include "DlgKeyHexAnalysis.h"
#include "Cryptography.h"
#include "CryptDoc.h"
#include "DlgKeyHex.h"	// Dialog-Box f�r die Schl�sseleingabe
#include "AppDocument.h"
#include "DlgKeyHexAnalysis.h"
#include <mbstring.h>
#include "DlgKeyAsymGeneration.h"
#include "DlgShowKeyParameter.h"
#include "s_ecconv.h"
#include "IntegerArithmetic.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern char* CaPseDatei;
extern char* CaPseVerzeichnis;
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHybridEncryptionDemo 



CDlgHybridEncryptionDemo::CDlgHybridEncryptionDemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHybridEncryptionDemo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHybridEncryptionDemo)
	m_strEdit = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
	
	for(int i=0;i<11;i++)
	{
		m_ButtonStatus[i] = inactive;
		m_ActionPerformed[i] = false;
	}
	
	m_ButtonStatus[0] = active_not_pressed;		// diese drei Buttons k�nnen am Anfang schon gedr�ckt werden, daher
	m_ButtonStatus[1] = active_not_pressed;		// werden sie auf active_not_pressed gesetzt
	m_ButtonStatus[3] = active_not_pressed;

	//Array mit den Voraussetzungen

	for(i=0;i<11;i++)
	{
		for(int j=0;j<11;j++)
		{
			m_setMatrix[i][j]=false;
		}
	}
	m_setMatrix[2][1]=true;
	m_setMatrix[4][3]=true;
	m_setMatrix[5][0]=true;
	m_setMatrix[5][1]=true;
	m_setMatrix[6][1]=true;
	m_setMatrix[6][3]=true;
	m_setMatrix[7][0]=true;
	m_setMatrix[8][5]=true;
	m_setMatrix[9][6]=true;
	m_setMatrix[10][0]=true;
	m_setMatrix[10][1]=true;
	m_setMatrix[10][3]=true;
	m_setMatrix[10][5]=true;
	m_setMatrix[10][6]=true;

	PlainText = CipherText = 0;
	m_bAuswahlDat = true;
}


void CDlgHybridEncryptionDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHybridEncryptionDemo)
	DDX_Text(pDX, IDC_EDIT_TXT, m_strEdit);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHybridEncryptionDemo, CDialog)
	//{{AFX_MSG_MAP(CDlgHybridEncryptionDemo)
	ON_BN_CLICKED(IDC_BUTTON1_TXT_EINFUEGEN, OnButtonGetDocument)
	ON_BN_CLICKED(IDC_BUTTON_ENC_KEY_ASYM, OnButtonEncKeyAsym)
	ON_BN_CLICKED(IDC_BUTTON_ENC_TXT_SYM, OnButtonEncDocumentSym)
	ON_BN_CLICKED(IDC_BUTTON_GEN_SYM_KEY, OnButtonGenSymKey)
	ON_BN_CLICKED(IDC_BUTTON_GET_ASYM_KEY, OnButtonGetAsymKey)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_SYM_KEY, OnButtonShowSymKey)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_ASYM_KEY, OnButtonShowAsymKey)
	ON_BN_CLICKED(IDC_BUTTON_SHOWTXT, OnButtonShowDocument)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonShowEncDocument)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonShowEncSymKey)
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_BUTTON_DATENAUSGABE, OnButtonDatenausgabe)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgHybridEncryptionDemo 
BOOL CDlgHybridEncryptionDemo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrlBmpSechseck1.AutoLoad(IDC_BUTTON1_TXT_EINFUEGEN,this);
	m_ctrlBmpSechseck2.AutoLoad(IDC_BUTTON_GEN_SYM_KEY,this);
	m_ctrlBmpSechseck3.AutoLoad(IDC_BUTTON_GET_ASYM_KEY,this);
	m_ctrlBmpRaute1.AutoLoad(IDC_BUTTON_SHOWTXT,this);
	m_ctrlBmpRaute2.AutoLoad(IDC_BUTTON_SHOW_SYM_KEY,this);
	m_ctrlBmpRaute3.AutoLoad(IDC_BUTTON_SHOW_ASYM_KEY,this);
	m_ctrlBmpRaute4.AutoLoad(IDC_BUTTON2,this);
	m_ctrlBmpRaute5.AutoLoad(IDC_BUTTON3,this);
	m_ctrlBmpRechteck1.AutoLoad(IDC_BUTTON_ENC_TXT_SYM,this);
	m_ctrlBmpRechteck2.AutoLoad(IDC_BUTTON_ENC_KEY_ASYM,this);
	m_ctrlBmpOval1.AutoLoad(IDCANCEL,this);
	m_ctrlBmpOval2.AutoLoad(IDC_BUTTON_DATENAUSGABE,this);

	//Laden der Bitmaps und als Steuerelemte anzeigen

	if(!m_bAuswahlDat)
	{
		m_ActionPerformed[0]=true;
	}
	//wenn m_bAuswahlDat auf false gesetzt ist, wurde Text aus dem CrypTool-Editor in das Editfeld des 
	//HybridverfahrenDialogs geladen, d.h. es muss keine Datei mehr ausgew�hlt werden.
	//Der Button um den Text anzuzeigen wird aktiviert indem m_ActionPerformed[0]auf true gesetzt wird
	EnDisButtons();
	//Aktualisieren der gegebenen Voraussetzungen
	ShowButtons();
	//Aktivieren /Deaktivieren der Buttons
	

	// Schriftart im Textfeld "aktuelle Datei", Felder in denen die Hashwerte und die Differenz angezeigt 
	// werden, "Courier" definieren
	LOGFONT lf={14,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"Courier"};
	//Struktur lf wird deklariert und initialisiert
	m_font.CreateFontIndirect(&lf);
	//Objekt der Klasse CFont (m_font) wird gesetzt initialisiert
	CWnd* pStatic=GetDlgItem(IDC_EDIT_TXT);
	pStatic->SetFont(&m_font,false);
	

	// Falls ein Dokument vorliegt, wird es initial im Demo-Dialog angezeigt
	if (!m_strPathSelDoc.IsEmpty())
	{
		// Den Fokus _nur_ dann auf den Button "Dokument" legen (und deshalb FALSE zur�ckgeben),
		// wenn auch wirklich ein Dokument vorliegt; f�r diesen Fall liefert DateiOeffnen(...) TRUE zur�ck!
		if(DateiOeffnen(m_strPathSelDoc))
		{
			EnDisButtons();
			ShowButtons();
			OnButtonShowDocument();	
			m_ctrlBmpRaute1.SetFocus();
			return FALSE;
		}

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

void CDlgHybridEncryptionDemo::OnButtonGetDocument() 
{
	m_ButtonStatus[0]=active_pressed;

	// Attributwerte sichern
	CString s_strBuffTitle, s_strEdit, s_strTitle;
	s_strBuffTitle = m_strBuffTitle;
	s_strEdit = m_strEdit;
	s_strTitle = m_strTitle;

	m_strBuffTitle = "";
	m_strEdit = "";
	m_strTitle = "";

	
	CFileDialog m_dlgFile( TRUE ); // TRUE = Datei �ffnen,FALSE = Datei speichern 
	if( m_dlgFile.DoModal() == IDOK ) 
	{
	//wenn auf den OK Button geklickt wird, wird der Pfadname und der Titel der gew�hlten Datei in 
	//lokale Variablen geschrieben
	//ausserdem wird die Dateigr��e ermittelt und ebenfalls in eine Variable geschrieben
		CString loc_filename = "";
		UpdateData(false);
		loc_filename = m_dlgFile.GetPathName();
		m_strBuffTitle = m_dlgFile.GetFileName();
		DateiOeffnen(loc_filename);
		m_strPathSelDoc = loc_filename;
		ShowButtons();
 	} 
	else
	//wenn auf Abbrechen geklickt wurde, wird abgebrochen
	{
		// Attribute zur�cksetzen (siehe oben)
		m_strBuffTitle = s_strBuffTitle;
		m_strEdit = s_strEdit;
		m_strTitle = s_strTitle;

		UpdateData(false);

		return;
	}
}

void CDlgHybridEncryptionDemo::OnButtonGenSymKey() 
{
	//Generieren eines symmetrischen Schluessels mit einem Zufallsgenerator

	m_ButtonStatus[1]=active_pressed;
	UpdateData(true);
	m_strSymKey="";
	m_strEdit = "";
	m_strTitle="";
	unsigned char o;
	
	for ( int j=0; j<KEY_LEN; j++ )
	{
		o=0;
		for(int i=0;i<8;i++)
		{
			o|=(_rand_bit())<<i;
		}
		SymKey[j]=o;
	}
	//Zufallsgenerator
	//SymKey beeinhaltet den symmetrischen Schl�ssel

	for (j=0;j<KEY_LEN;j++)
	{
		
			char array[3];
			_snprintf(array,3,"%02.2X",(unsigned char) SymKey[j]);
			m_strSymKey+=array;					
	}

	SetCondition(1,true);

	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnButtonShowSymKey() 
{
	if(inactive==m_ButtonStatus[2])	
	{
		Message( IDS_STRING_HYB_SHOW_SYM_KEY, MB_ICONEXCLAMATION );
		return;
	}
	
	CString SymKeyInHexDump = "";
	
	for (int i=0;i<32;i++)
	{
		SymKeyInHexDump += m_strSymKey[i];
		if(i%2==1)
		{
			SymKeyInHexDump += ' ';
		}
		
	}
	//Symmetrischer Schl�ssel soll hexadezimal angezeigt werden

	m_strEdit = SymKeyInHexDump;
	m_strTitle.LoadString(IDS_STRING_HYBRID_ENC_SYM_KEY);
	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnButtonEncDocumentSym() 
{
	if(inactive==m_ButtonStatus[5])	
	{
		Message(IDS_STRING_HYB_ENC_DOC_SYM, MB_ICONEXCLAMATION);
		return;
	}

	m_ButtonStatus[5]=active_pressed;

	UpdateData(true);

	int AlgId=3;
	
	// Henrik Koy, 19. April 2002,
	// Programm unter Windows XP-abgest�rzt: 20 Zeichen Speicher sind zu wenig
	char strPathEncDocument[CRYPTOOL_PATH_LENGTH];
	GetTmpName(strPathEncDocument,"cry",".tmp");
	//Name f�r eine tempor�re Datei wird erzeugt, in der 
	//der Verschluesselte Text geschrieben werden soll
	//der Name wird in die Variable strPathEncDocument geschrieben
	char key[100];
	strcpy(key,(LPCTSTR)m_strSymKey);

	SHOW_HOUR_GLASS

	AESCrypt((char*)(LPCTSTR)m_strPathSelDoc, "", AlgId,true,strPathEncDocument,key);
	//das Dokument wird mit AES verschl�sselt

	if ( CipherText )
		theApp.SecudeLib.aux_free_OctetString(&CipherText);
	CipherText = theApp.SecudeLib.aux_file2OctetString(strPathEncDocument);
	if (!CipherText)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_Hashdemo_FileNotFound,pc_str,100);
		AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
		return;
	}		

	UpdateData();
	m_strBuffEditEncDoc = "";
	m_strTitle = "";
	m_strEdit = "";

	HIDE_HOUR_GLASS

	SetCondition(5,true);

	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnButtonGetAsymKey() 
{	
	rsaDlg.disableButtons = true;

	if ( IDOK == rsaDlg.DoModal() ) 
	{
		CKeyFile KeyHandling;
		CString caDB_entry_name = KeyHandling.CreateDistName(rsaDlg.Name, rsaDlg.Firstname, rsaDlg.CreatTime);
		LPTSTR string1 = new TCHAR[caDB_entry_name.GetLength()+1];
		_tcscpy(string1, caDB_entry_name);
		char *Auswahl=string1; // Auswahl entspricht caDB_entry_name
		PSE PseHandle;
		PseHandle=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
		if (PseHandle==NULL)
		{
			// Fehler beim �ffnen der CA-Datenbank
			SetCondition(3,false);
			Message(IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			delete string1;
			return;
		}
		
		//Routine f�r das Holen von Zertifikaten aus der CA-Datenbank
		SET_OF_IssuedCertificate *Zert;
		Zert=theApp.SecudeLib.af_cadb_get_user(PseHandle, Auswahl);
		if (Zert==NULL)
		{
			// Fehler beim lesen des Zertifikats
			SetCondition(3,false);
			char *Fehler=theApp.SecudeLib.LASTTEXT;
			CString Fehler2=Fehler;
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_GET_PSE,pc_str,STR_LAENGE_STRING_TABLE);
			CString Fehler3=(CString)pc_str+(CString)Fehler2;
			AfxMessageBox (Fehler3,MB_ICONSTOP);
			// Freigeben von dynamisch angelegtem Speicher
			delete string1;
			theApp.SecudeLib.af_close(PseHandle);
			return;
		}
		theApp.SecudeLib.af_close(PseHandle);
		m_ButtonStatus[3]=active_pressed;
		SetCondition(3,true);
	}
	UserKeyId=rsaDlg.UserKeyId;
	UpdateData(false);
}



void CDlgHybridEncryptionDemo::RSAEncrypt()
{
	// Dialogbox zur Auswahl des zu benutzenden (�ffentlichen) Schl�ssels anzeigen
	
	if(m_ActionPerformed[3])
	{
		// Initialisierung der Variablen
		OctetString *in=new OctetString;
		BitString out;
		in->octets=new char[KEY_LEN];	
		memcpy(in->octets,SymKey,KEY_LEN);
		in->noctets=KEY_LEN;

		int max_RSA_keysize_in_octs = ((MAX_RSA_MODULSIZE+1)+7)/8; // siehe DlgAsymKeyCreat.h for MAX_RSA_MODULSIZE
		int number_outbits_in_wc = in->noctets + in->noctets/37 + max_RSA_keysize_in_octs; // Blocksize ~ 37
		
		out.nbits=0;
		out.bits=(char*)malloc(number_outbits_in_wc);
		if (out.bits == NULL)
		{
			// Fehler. Speicher kann nicht allokiert werden
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_MEMORY_RSA_ENCRYPTION,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (pc_str,MB_ICONSTOP);
			return;
		}
		
		CKeyFile KeyHandling;
		CString caDB_keyid_name = KeyHandling.CreateDistName(rsaDlg.Name, rsaDlg.Firstname, rsaDlg.CreatTime);
		// caDB_keyid_name: unter diesem Bezeichner/Namen wurde das Zertifikat in die CA-Datenbank geschrieben
		
		LPTSTR string3 = new TCHAR[caDB_keyid_name.GetLength()+1];
		_tcscpy(string3, caDB_keyid_name);
		char *string4=string3; // string4 wird benutzt, um in der CA-Datenbank die Parameter abzufragen 
		
		// �ffnen der CA-PSE
		PSE PseHandle;
		PseHandle=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
		if (PseHandle==NULL)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.aux_free_OctetString(&in);
			free(out.bits);
			delete string3;
			return;
		}
		
		// Besorgen des Zertifikates der Adressaten
		SET_OF_IssuedCertificate *Liste;
		Liste=theApp.SecudeLib.af_cadb_get_user (PseHandle, string4);
		if (Liste==NULL)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_ON_LOAD_CERTIFICATE,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.af_close (PseHandle);
			theApp.SecudeLib.aux_free_OctetString(&in);
			free(out.bits);
			delete string3;
			return;
		}
		
		Certificate *Zert;
		OctetString *SNummer;
		SNummer=Liste->element->serial;
		Zert=theApp.SecudeLib.af_cadb_get_Certificate (PseHandle, SNummer);
		if (Zert==NULL)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_ON_LOAD_CERTIFICATE,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.aux_free_SET_OF_IssuedCertificate (&Liste);
			theApp.SecudeLib.af_close (PseHandle);
			theApp.SecudeLib.aux_free_OctetString(&in);
			free(out.bits);
			delete string3;
			return;
		}
		
		// Besorgen des �ffentlichen Schl�ssels des Adressaten aus seinem Zertifikat
		Key Schluessel;
		Schluessel.key=Zert->tbs->subjectPK;
		Schluessel.pse_sel=NULL;
		Schluessel.alg=theApp.SecudeLib.rsa_aid;
		Schluessel.add_object=NULL;
		Schluessel.add_object_type=NULL;
		Schluessel.key_size=NULL;
		Schluessel.private_key=NULL;
		
		// Verschl�sselung der Daten
		int fret = theApp.SecudeLib.af_encrypt_all(PseHandle, in, &out, &Schluessel, NULL);
		if (fret==-1)
		{  
			// Fehler bei der Entschl�sselung
			// Ausgabe einer Fehlermeldung
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_ERROR,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.af_close (PseHandle);
			theApp.SecudeLib.aux_free_SET_OF_IssuedCertificate (&Liste);
			theApp.SecudeLib.aux_free_Certificate (&Zert);
			theApp.SecudeLib.aux_free_OctetString(&in);
			free(out.bits);
			delete string3;
			return;
		}
		delete []in->octets;
		delete in;

		// Ausgabe der verschl�sselten Daten

		EncSymKey = theApp.SecudeLib.aux_BString2OString(&out);
		
	
		
		theApp.SecudeLib.af_close (PseHandle);
		theApp.SecudeLib.aux_free_SET_OF_IssuedCertificate (&Liste);
		theApp.SecudeLib.aux_free_Certificate (&Zert);
		delete string3;	
	}
}


void CDlgHybridEncryptionDemo::OnButtonEncKeyAsym() 
{
	if(inactive==m_ButtonStatus[6])	
	{
		Message(IDS_STRING_HYB_ENC_KEY_ASYM,MB_ICONEXCLAMATION);
		return;
	}

	m_ButtonStatus[6]=active_pressed;

	SHOW_HOUR_GLASS
	//Sanduhr als Cursor

	RSAEncrypt();
	UpdateData();
	m_strBuffEditEncKeyAsym = "";
	m_strEdit = "";
	for (unsigned int j=0;j<EncSymKey->noctets;j++)
	{
			char array[3];
			_snprintf(array,3,"%02.2X",(unsigned char) EncSymKey->octets[j]);
			m_strBuffEditEncKeyAsym+=array;					
	}
	m_strTitle = "";

	

	UpdateData(false);


	SetCondition(6,true);
	UpdateData(false);
	HIDE_HOUR_GLASS
	//Sanduhr durch einen Pfeil ersetzen
}


void CDlgHybridEncryptionDemo::OnButtonShowAsymKey() 
{

	if(inactive==m_ButtonStatus[4])	
	{
		Message(IDS_STRING_HYB_SHOW_ASYM_KEY, MB_ICONEXCLAMATION);
		return;
	}
	UpdateData(true);
	m_strEdit = "";
	m_strTitle = "";
	UpdateData(false);
	OctetString *in=new OctetString;
	BitString out;
	in->octets=new char[KEY_LEN];	
	memcpy(in->octets,SymKey,KEY_LEN);
	in->noctets=KEY_LEN;

	int max_RSA_keysize_in_octs = ((MAX_RSA_MODULSIZE+1)+7)/8; // siehe DlgAsymKeyCreat.h for MAX_RSA_MODULSIZE
	int number_outbits_in_wc = in->noctets + in->noctets/37 + max_RSA_keysize_in_octs; // Blocksize ~ 37
	
	out.nbits=0;
	out.bits=(char*)malloc(number_outbits_in_wc);
	if (out.bits == NULL)
	{
		// Fehler. Speicher kann nicht allokiert werden
		Message(IDS_STRING_ERR_MEMORY_RSA_ENCRYPTION,MB_ICONSTOP);
		return;
	}
	
	CKeyFile KeyHandling;
	CString caDB_keyid_name = KeyHandling.CreateDistName(rsaDlg.Name, rsaDlg.Firstname, rsaDlg.CreatTime);
	// cDB_keyid_name: unter diesem Bezeichner/Namen wurde das Zertifikat in die CA-Datenbank geschrieben
	
	
	LPTSTR string3 = new TCHAR[caDB_keyid_name.GetLength()+1];
	_tcscpy(string3, caDB_keyid_name);
	char *string4=string3; // string4 wird benutzt, um in der CA-Datenbank die Parameter abzufragen 
	
	// �ffnen der CA-PSE
	PSE PseHandle;
	PseHandle=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
	if (PseHandle==NULL)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
		// Freigeben von dynamisch angelegtem Speicher
		theApp.SecudeLib.aux_free_OctetString(&in);
		free(out.bits);
		delete string3;
		return;
	}
	
	// Besorgen des Zertifikates der Adressaten
	SET_OF_IssuedCertificate *Liste;
	Liste=theApp.SecudeLib.af_cadb_get_user (PseHandle, string4);
	if (Liste==NULL)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_ON_LOAD_CERTIFICATE,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
		// Freigeben von dynamisch angelegtem Speicher
		theApp.SecudeLib.af_close (PseHandle);
		theApp.SecudeLib.aux_free_OctetString(&in);
		free(out.bits);
		delete string3;
		return;
	}
	
	Certificate *Zert;
	OctetString *SNummer;
	SNummer=Liste->element->serial;
	Zert=theApp.SecudeLib.af_cadb_get_Certificate (PseHandle, SNummer);
	if (Zert==NULL)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_ON_LOAD_CERTIFICATE,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
		// Freigeben von dynamisch angelegtem Speicher
		theApp.SecudeLib.aux_free_SET_OF_IssuedCertificate (&Liste);
		theApp.SecudeLib.af_close (PseHandle);
		theApp.SecudeLib.aux_free_OctetString(&in);
		free(out.bits);
		delete string3;
		return;
	}
	
	// Besorgen des �ffentlichen Schl�ssels des Adressaten aus seinem Zertifikat
	Key Schluessel;
	Schluessel.key=Zert->tbs->subjectPK;
	Schluessel.pse_sel=NULL;
	Schluessel.alg=theApp.SecudeLib.rsa_aid;
	Schluessel.add_object=NULL;
	Schluessel.add_object_type=NULL;
	Schluessel.key_size=NULL;
	Schluessel.private_key=NULL;

	CDlgShowKeyParameter dlg;
	dlg.m_Title.LoadString(IDS_STRING_HYBRID_ENC_PUBLIC_KEY_OF);
	dlg.m_Title+=rsaDlg.Name;
	dlg.m_Title+=" ";
	dlg.m_Title+= rsaDlg.Firstname;

	
	dlg.disableOkButton = true;
	KeyBits *ki;
	ki=theApp.SecudeLib.d_KeyBits(&(Schluessel.key->subjectkey));
	int mlen = ki->part1.noctets;
	unsigned char* buf = (unsigned char*) ki->part1.octets;
	L_NUMBER temp[MAXLGTH];
	sprintf(pc_str,"0x");
	for (int i=0;i<mlen;i++)
	{
		sprintf(pc_str+2+(2*i),"%02X",buf[i]);
	
	}
	string_to_ln(pc_str,temp);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_MODUL,pc_str,STR_LAENGE_STRING_TABLE);
	dlg.addentry(pc_str,temp);

	int mlen2 = ki->part2.noctets;
	unsigned char* buf2 = (unsigned char*) ki->part2.octets;
	sprintf(pc_str,"0x");
	for (i=0;i<mlen2;i++)
	{
		sprintf(pc_str+2+(2*i),"%02X",buf2[i]);
	
	}
	string_to_ln(pc_str,temp);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EXPONENT,pc_str,STR_LAENGE_STRING_TABLE);
	dlg.addentry(pc_str,temp);
	
	dlg.DoModal();
	UpdateData(false);	
}

void CDlgHybridEncryptionDemo::SetCondition(int button,bool state)
{
	m_ActionPerformed[button] = state;
	ResetDependent(button);
	EnDisButtons();
	ShowButtons();
}

void CDlgHybridEncryptionDemo::ResetDependent(int button)
{
	int i;
	for (i = 0; i < 11; i++)
	{
		if (m_setMatrix[i][button] && m_ActionPerformed[i])
		{
			m_ActionPerformed[i] = false;
			ResetDependent(i);
		}
	}
}

void CDlgHybridEncryptionDemo::EnDisButtons()
{
	for(int i=0;i<11;i++)
	{
		if(!m_ActionPerformed[i])
		{
			m_ButtonStatus[i]=active_not_pressed;
		}
		else
		{
			m_ButtonStatus[i]=active_pressed;
		}

		for(int j=0;j<11;j++)
		{
			if(m_setMatrix[i][j])
			{
				if(!m_ActionPerformed[j])
				{
					m_ButtonStatus[i]=inactive;
					break;
				}
			}
		}
	}
}

void CDlgHybridEncryptionDemo::OnButtonShowDocument() 
{
	if(inactive==m_ButtonStatus[7])	
	{
		Message(IDS_STRING_HYB_SHOW_DOC, MB_ICONEXCLAMATION);
		return;
	}
	m_strTitle = m_strBuffTitle;

	int destSize; 
	{
		int linelen;
		int lines, rest;

		linelen = 11 + INFO_TEXT_COLUMNS * 4;
		lines = (m_iDocSize+INFO_TEXT_COLUMNS-1) / INFO_TEXT_COLUMNS;
		rest  = (m_iDocSize) % INFO_TEXT_COLUMNS;
		destSize = lines * linelen; // - INFO_TEXT_COLUMNS + rest;
	}
	char *dest = new char [destSize+1];
	SHOW_HOUR_GLASS
	
	int err = HexDumpMem(dest,destSize,(unsigned char*)PlainText->octets,m_iDocSize, INFO_TEXT_COLUMNS);

	m_strEdit = dest;
	HIDE_HOUR_GLASS
	delete []dest;

	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnButtonShowEncDocument() 
{
	if(inactive==m_ButtonStatus[8])	
	{
		Message(IDS_STRING_HYB_SHOW_ENC_DOC, MB_ICONEXCLAMATION);
		return;
	}

	m_strTitle.LoadString(IDS_STRING_HYBRID_ENC_SYM_ENC_DOC);

	int destSize; 
	{
		int linelen;
		int lines, rest;

		linelen = 11 + INFO_TEXT_COLUMNS * 4;
		lines = (CipherText->noctets+INFO_TEXT_COLUMNS-1) / INFO_TEXT_COLUMNS;
		rest  = (CipherText->noctets) % INFO_TEXT_COLUMNS;
		destSize = lines * linelen; // - INFO_TEXT_COLUMNS + rest;
	}
	char *dest = new char [destSize+1];
	SHOW_HOUR_GLASS
	
	int err = HexDumpMem(dest,destSize,(unsigned char*)CipherText->octets,m_iDocSize, INFO_TEXT_COLUMNS);

	m_strEdit = dest;
	HIDE_HOUR_GLASS
	delete []dest;

	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnButtonShowEncSymKey() 
{
	if(inactive==m_ButtonStatus[9])	
	{
		Message(IDS_STRING_HYB_ENC_SYM_KEY, MB_ICONEXCLAMATION);
		return;
	}
	SHOW_HOUR_GLASS
	m_strTitle.LoadString(IDS_STRING_HYBRID_ENC_ASYM_ENC_KEY);
	m_strEdit = m_strBuffEditEncKeyAsym;
	UpdateData(false);
	HIDE_HOUR_GLASS
}

void CDlgHybridEncryptionDemo::ShowButtons()
{
	m_hFocus = GetFocus();

	for(int i=0;i<11;i++)
	{
		switch(i)
		{
		case 0:if(active_not_pressed==m_ButtonStatus[i])
			   {
					m_ctrlBmpSechseck1.LoadBitmaps("SECHSECK1_R_U", "SECHSECK1_R_D", "SECHSECK1_R_F", NULL);
					m_ctrlBmpSechseck1.ShowWindow(SW_HIDE);
					m_ctrlBmpSechseck1.ShowWindow(SW_SHOW);
			   }
				else if(active_pressed==m_ButtonStatus[i])
			   {
					m_ctrlBmpSechseck1.LoadBitmaps("SECHSECK1_G_U", "SECHSECK1_G_D", "SECHSECK1_G_F", NULL);
					m_ctrlBmpSechseck1.ShowWindow(SW_HIDE);
					m_ctrlBmpSechseck1.ShowWindow(SW_SHOW);
			   };break;

		case 1:if(active_not_pressed==m_ButtonStatus[i])
			   {
					m_ctrlBmpSechseck2.LoadBitmaps("SECHSECK2_R_U", "SECHSECK2_R_D", "SECHSECK2_R_F", NULL);
					m_ctrlBmpSechseck2.ShowWindow(SW_HIDE);
					m_ctrlBmpSechseck2.ShowWindow(SW_SHOW);
			   }
				else if(active_pressed==m_ButtonStatus[i])
			   {
					m_ctrlBmpSechseck2.LoadBitmaps("SECHSECK2_G_U", "SECHSECK2_G_D", "SECHSECK2_G_F", NULL);
					m_ctrlBmpSechseck2.ShowWindow(SW_HIDE);
					m_ctrlBmpSechseck2.ShowWindow(SW_SHOW);
			   };break;

		case 2:if(m_ButtonStatus[i])
			   {
					m_ctrlBmpRaute2.LoadBitmaps("RAUTE2_B_U", "RAUTE2_B_D", "RAUTE2_B_F", NULL);
					m_ctrlBmpRaute2.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute2.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpRaute2.LoadBitmaps("RAUTE2_X_U", NULL, NULL, NULL);
					m_ctrlBmpRaute2.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute2.ShowWindow(SW_SHOW);
			   
			   };break;

		case 3:if(active_not_pressed==m_ButtonStatus[i])
			   {
					m_ctrlBmpSechseck3.LoadBitmaps("SECHSECK3_R_U", "SECHSECK3_R_D", "SECHSECK3_R_F", NULL);
					m_ctrlBmpSechseck3.ShowWindow(SW_HIDE);
					m_ctrlBmpSechseck3.ShowWindow(SW_SHOW);
			   }
				else if(active_pressed==m_ButtonStatus[i])
			   {
					m_ctrlBmpSechseck3.LoadBitmaps("SECHSECK3_G_U", "SECHSECK3_G_D", "SECHSECK3_G_F", NULL);
					m_ctrlBmpSechseck3.ShowWindow(SW_HIDE);
					m_ctrlBmpSechseck3.ShowWindow(SW_SHOW);
			   };break;

		case 4:if(m_ButtonStatus[i])
			   {
					m_ctrlBmpRaute3.LoadBitmaps("RAUTE3_B_U", "RAUTE3_B_D", "RAUTE3_B_F", NULL);
					m_ctrlBmpRaute3.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute3.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpRaute3.LoadBitmaps("RAUTE3_X_U", NULL, NULL, NULL);
					m_ctrlBmpRaute3.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute3.ShowWindow(SW_SHOW);
			   
			   };break;

		case 5:if(active_not_pressed==m_ButtonStatus[i])
			   {
					m_ctrlBmpRechteck1.LoadBitmaps("RECHTECK1_R_U", "RECHTECK1_R_D", "RECHTECK1_R_F", NULL);
					m_ctrlBmpRechteck1.ShowWindow(SW_HIDE);
					m_ctrlBmpRechteck1.ShowWindow(SW_SHOW);
			   }
				else if(active_pressed==m_ButtonStatus[i])
			   {
					m_ctrlBmpRechteck1.LoadBitmaps("RECHTECK1_G_U", "RECHTECK1_G_D", "RECHTECK1_G_F", NULL);
					m_ctrlBmpRechteck1.ShowWindow(SW_HIDE);
					m_ctrlBmpRechteck1.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpRechteck1.LoadBitmaps("RECHTECK1_X_U", NULL, NULL, NULL);
					m_ctrlBmpRechteck1.ShowWindow(SW_HIDE);
					m_ctrlBmpRechteck1.ShowWindow(SW_SHOW);
			   
			   };break;

		case 6:if(active_not_pressed==m_ButtonStatus[i])
			   {
					m_ctrlBmpRechteck2.LoadBitmaps("RECHTECK2_R_U", "RECHTECK2_R_D", "RECHTECK2_R_F", NULL);
					m_ctrlBmpRechteck2.ShowWindow(SW_HIDE);
					m_ctrlBmpRechteck2.ShowWindow(SW_SHOW);
			   }
				else if(active_pressed==m_ButtonStatus[i])
			   {
					m_ctrlBmpRechteck2.LoadBitmaps("RECHTECK2_G_U", "RECHTECK2_G_D", "RECHTECK2_G_F", NULL);
					m_ctrlBmpRechteck2.ShowWindow(SW_HIDE);
					m_ctrlBmpRechteck2.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpRechteck2.LoadBitmaps("RECHTECK2_X_U", NULL, NULL, NULL);
					m_ctrlBmpRechteck2.ShowWindow(SW_HIDE);
					m_ctrlBmpRechteck2.ShowWindow(SW_SHOW);
			   
			   };break;

		case 7:if(m_ButtonStatus[i])
			   {
					m_ctrlBmpRaute1.LoadBitmaps("RAUTE1_B_U", "RAUTE1_B_D", "RAUTE1_B_F", NULL);
					m_ctrlBmpRaute1.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute1.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpRaute1.LoadBitmaps("RAUTE1_X_U", NULL, NULL, NULL);
					m_ctrlBmpRaute1.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute1.ShowWindow(SW_SHOW);
			   
			   };break;

		case 8:if(m_ButtonStatus[i])
			   {
					m_ctrlBmpRaute4.LoadBitmaps("RAUTE4_B_U", "RAUTE4_B_D", "RAUTE4_B_F", NULL);
					m_ctrlBmpRaute4.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute4.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpRaute4.LoadBitmaps("RAUTE4_X_U", NULL, NULL, NULL);
					m_ctrlBmpRaute4.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute4.ShowWindow(SW_SHOW);
			   
			   };break;

		case 9:if(m_ButtonStatus[i])
			   {
					m_ctrlBmpRaute5.LoadBitmaps("RAUTE5_B_U", "RAUTE5_B_D", "RAUTE5_B_F", NULL);
					m_ctrlBmpRaute5.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute5.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpRaute5.LoadBitmaps("RAUTE5_X_U", NULL, NULL, NULL);
					m_ctrlBmpRaute5.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute5.ShowWindow(SW_SHOW);
			   
			   };break;

   	   case 10:if(m_ButtonStatus[i])
			   {
					m_ctrlBmpOval2.LoadBitmaps("OVAL2_G_U", "OVAL2_G_D", "OVAL2_G_F", NULL);
					m_ctrlBmpOval2.ShowWindow(SW_HIDE);
					m_ctrlBmpOval2.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpOval2.LoadBitmaps("OVAL2_X_U", NULL, NULL, NULL);
					m_ctrlBmpOval2.ShowWindow(SW_HIDE);
					m_ctrlBmpOval2.ShowWindow(SW_SHOW);
			   
			   };break;
		}
	}

	m_hFocus->SetFocus();
}

CDlgHybridEncryptionDemo::~CDlgHybridEncryptionDemo()
{
	if(CipherText)
		theApp.SecudeLib.aux_free_OctetString(&CipherText);
	if(PlainText)
		theApp.SecudeLib.aux_free_OctetString(&PlainText);
}

bool CDlgHybridEncryptionDemo::DateiOeffnen(const CString &DateiPfadName)
{

	SHOW_HOUR_GLASS

	if ( PlainText )
		theApp.SecudeLib.aux_free_OctetString(&PlainText);
	PlainText = theApp.SecudeLib.aux_file2OctetString(DateiPfadName);
	if (!PlainText)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_Hashdemo_FileNotFound,pc_str,100);
		AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
		return false;
	}
	m_iDocSize=PlainText->noctets;
	if(m_iDocSize == 0)
	//wenn in der Datei nichts steht
	{
		return false;
	}
	m_bAuswahlDat = false;
	m_strPathSelDoc = DateiPfadName;

	HIDE_HOUR_GLASS

	//Schalter f�r EnDisButtons() siehe OnInitDialog()
	SetCondition(0,true);
	
	return true;
}

void CDlgHybridEncryptionDemo::OnButtonDatenausgabe() 
{
	if(!m_ButtonStatus[10])	
	{
		Message(IDS_STRING_HYB_SHOW_DATA, MB_ICONEXCLAMATION);
		return;
	}
	char outfile[128], title[128];
	CAppDocument *NewDoc;
	GetTmpName(outfile,"cry",".hex");
	//----------------------------------------------------------------------------------------------------------	
	// Ausgabe von Reciever, Symmetriche- , asymmetrische Methode, verschl.Session Key und 
	// Ciphertext in einem Fenster
	//----------------------------------------------------------------------------------------------------------
	OctetString Text;
	char helptext[100];
	// Ausgabe Empf�nger
		// Umwandeln von CString nach char*
	LPTSTR string_tmp1 = new TCHAR[UserKeyId.GetLength()+1];
	_tcscpy(string_tmp1, UserKeyId);
	char *UserKeyId_tmp=string_tmp1;

	LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_RECIEVER,helptext,100);
	Text.noctets=strlen(helptext);
	Text.octets=helptext;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,2);
	Text.noctets=strlen(UserKeyId_tmp);
	Text.octets=UserKeyId_tmp;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	// Ausgabe Encrypted Session key
	// Umwandeln von CString nach char*
//	LPTSTR string_tmp = new TCHAR[m_strBuffEditEncDoc.GetLength()+1];
//	_tcscpy(string_tmp, m_strBuffEditEncDoc);
//	char *EncSessionKey=string_tmp;
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_LENGTH_ENC_KEY,helptext,100);
	Text.noctets=strlen(helptext);
	Text.octets=helptext;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	int Keylength=8*(EncSymKey->noctets);
	char Keylen_in_bits_str[20];
	// schreibe die zahl Keylength im Dezimalsystem nach Keylen_in_bits_str
	_itoa(Keylength, Keylen_in_bits_str, 10);
	Text.noctets=strlen(Keylen_in_bits_str);
	Text.octets=Keylen_in_bits_str;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_ENC_KEY,helptext,100);
	Text.noctets=strlen(helptext);
	Text.octets=helptext;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
//	Text.noctets=strlen(EncSessionKey);
//	Text.octets=EncSessionKey;
//	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	theApp.SecudeLib.aux_OctetString2file(EncSymKey,outfile,3);
	
	// Ausgabe Symmetric method
	LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_SYM_METHOD,helptext,100);
	Text.noctets=strlen(helptext);
	Text.octets=helptext;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	Text.noctets=strlen("AES");
	Text.octets="AES";
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);

	// Ausgabe Asymmetric method
	LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_ASYM_METHOD,helptext,100);
	Text.noctets=strlen(helptext);
	Text.octets=helptext;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	Text.noctets=strlen("RSA");
	Text.octets="RSA";
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);

	// Ciphertext
	LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_CIPHERTEXT,helptext,100);
	Text.noctets=strlen(helptext);
	Text.octets=helptext;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	theApp.SecudeLib.aux_OctetString2file(CipherText,outfile,3);
	
	NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
	remove(outfile);
		
	HIDE_HOUR_GLASS
		
	if(NewDoc)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_ENC_TITLE,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName(title,sizeof(title),pc_str,m_strBuffTitle);
		NewDoc->SetTitle(title);
	}
	CDialog::OnOK();
	
}