// HybridEncr.cpp: Implementierungsdatei
//


#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgHybridEncryptionDemo.h"
#include <fstream.h>
#include "FileTools.h"
#include <sys\stat.h>
#include "DlgRSAEncryption.h"
#include "DlgKeyHexAnalysis.h"
#include "Cryptography.h"
#include "CryptDoc.h"
#include "DlgKeyHex.h"	// Dialog-Box für die Schlüsseleingabe
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
	m_iIsTxtAlreadySel = false;
	m_iIsGenSymKey = false;
	m_iIsGenAsymKey = false;
	CString m_strPfadEditorDat = "";

	for(int i=0;i<10;i++)
	{
		m_barrSetCondition[i] = false;
	}
	
	//Array mit den Voraussetzungen

	for(i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			m_check[i][j]=false;
		}
	}
	m_check[2][1]=true;
	m_check[4][3]=true;
	m_check[5][0]=true;
	m_check[5][1]=true;
	m_check[6][1]=true;
	m_check[6][3]=true;
	m_check[7][0]=true;
	m_check[8][5]=true;
	m_check[9][6]=true;
	m_strEdit1 = 0;

	
}


void CDlgHybridEncryptionDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHybridEncryptionDemo)
	//DDX_Control(pDX, IDC_BMP, m_ctrlBG);
	DDX_Text(pDX, IDC_EDIT_TXT, m_strEdit);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHybridEncryptionDemo, CDialog)
	//{{AFX_MSG_MAP(CDlgHybridEncryptionDemo)
	ON_BN_CLICKED(IDC_BUTTON1_TXT_EINFUEGEN, OnButton1TxtEinfuegen)
	ON_BN_CLICKED(IDC_BUTTON_ENC_KEY_ASYM, OnButtonEncKeyAsym)
	ON_BN_CLICKED(IDC_BUTTON_ENC_TXT_SYM, OnButtonEncTxtSym)
	ON_BN_CLICKED(IDC_BUTTON_GEN_SYM_KEY, OnButtonGenSymKey)
	ON_BN_CLICKED(IDC_BUTTON_GET_ASYM_KEY, OnButtonGetAsymKey)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_SYM_KEY, OnButtonShowSymKey)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_ASYM_KEY, OnButtonShowAsymKey)
	ON_BN_CLICKED(IDC_BUTTON_SHOWTXT, OnButtonShowtxt)
	ON_BN_CLICKED(IDC_BUTTON2, OnShowEncTxt)
	ON_BN_CLICKED(IDC_BUTTON3, OnShowEncSymKey)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgHybridEncryptionDemo 
BOOL CDlgHybridEncryptionDemo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_bCursor = false;
	
	m_ctrlBmpSechseck1.AutoLoad(IDC_BUTTON1_TXT_EINFUEGEN,this);
	m_ctrlBmpSechseck2.AutoLoad(IDC_BUTTON_GEN_SYM_KEY,this);
	m_ctrlBmpSechseck3.AutoLoad(IDC_BUTTON_GET_ASYM_KEY,this);
	m_ctrlBmpRaute1.AutoLoad(IDC_BUTTON_SHOWTXT,this);
	m_ctrlBmpRaute2.AutoLoad(IDC_BUTTON_SHOW_SYM_KEY,this);
	m_ctrlBmpRaute3.AutoLoad(IDC_BUTTON_SHOW_ASYM_KEY,this);
	m_ctrlBmpRaute4.AutoLoad(IDC_BUTTON2,this);
	m_ctrlBmpRaute5.AutoLoad(IDC_BUTTON3,this);
	m_ctrlBmpViereck1.AutoLoad(IDC_BUTTON_ENC_TXT_SYM,this);
	m_ctrlBmpViereck2.AutoLoad(IDC_BUTTON_ENC_KEY_ASYM,this);
	if(!m_bAuswahlDat)
	{
		m_barrSetCondition[0]=true;
	}
	//wenn m_bAuswahlDat auf false gesetzt ist, wurde Text aus dem CrypTool-Editor in das Editfeld des 
	//HybridverfahrenDialogs geladen, d.h. es muss keine Datei mehr ausgewählt werden.
	//Der Button um den Text anzuzeigen wird aktiviert indem m_barrSetCondition[0]auf true gesetzt wird
	EnDisButtons();
	ShowButtons();
	

	// Schriftart im Textfeld "aktuelle Datei", Felder in denen die Hashwerte und die Differenz angezeigt 
	// werden, "Courier" definieren
	LOGFONT lf={14,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"Courier"};
	//Struktur lf wird deklariert und initialisiert
	m_font.CreateFontIndirect(&lf);
	//Objekt der Klasse CFont (m_font) wird gesetzt initialisiert
	CWnd* pStatic=GetDlgItem(IDC_EDIT_TXT);
	pStatic->SetFont(&m_font,false);


	

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgHybridEncryptionDemo::OnButton1TxtEinfuegen() 
{
	
	int DatGroesse=0;
	CString loc_filename = "";
	CString loc_title = "";
	m_strEdit = "";
	m_strTitle = "";
	UpdateData(false);
	
	CFileDialog m_dlgFile( TRUE ); // TRUE = Datei öffnen,FALSE = Datei speichern 
	if( m_dlgFile.DoModal() == IDOK ) 
	//wenn auf den OK Button geklickt wird, wird der Pfadname und der Titel der gewählten Datei in 
	//lokale Variablen geschrieben
	//ausserdem wird die Dateigröße ermittelt und ebenfalls in eine Variable geschrieben
	{ 
		theApp.DoWaitCursor(1);
		loc_filename = m_dlgFile.GetPathName();
		loc_title = m_dlgFile.GetFileName();
		struct stat *obj;
		obj = new (struct stat);
		//Groesse der Datei die ausgelesen werden soll wird 
		//ermittelt und in m_iDataGroesse geschrieben
		//und ob die Datei vorhanden ist 
		obj->st_size;
	    if ( 0 != stat((const char*)loc_filename,obj))
		//Get status information on a file
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_Hashdemo_FileNotFound,pc_str,100);
			AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
			delete obj;
			return;
		}

		DatGroesse = obj->st_size;
		
		delete obj;
 	} 
	else
	//wenn auf Abbrechen geklickt wurde, wird abgebrochen
	{
		return;
	}
	
	m_strTitle1 = loc_title;
	m_strPathnameTxt = loc_filename;

	ifstream test(loc_filename.GetBuffer(0),ios::in|ios::binary);
	char* in=new char[DatGroesse];
	test.read(in,DatGroesse);
	//Datei wird gelesen
	//und in der Variablen "in" gespeichert

	m_gc=test.gcount();
	test.close();

	in[m_gc]='\0';
	m_strEdit1=new char[m_gc+1];
	memcpy(m_strEdit1,in,m_gc);
	//"in" wird in "m_strEdit1" geschrieben

	UpdateData();
	//m_strEdit1=in;
	theApp.DoWaitCursor(0);
	m_iIsTxtAlreadySel=true;
	m_barrSetCondition[0] = true;
	EnDisButtons();
	ShowButtons();
	UpdateData(false); // Variablen ---> Felder 	
	
}

void CDlgHybridEncryptionDemo::OnButtonGenSymKey() 
{
	//Generieren eines Schluessels 
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
	//SymKey beeinhaltet den symmetrischen Schlüssel

	for (j=0;j<KEY_LEN;j++)
	{
		
			char array[3];
			_snprintf(array,3,"%02.2X",(unsigned char) SymKey[j]);
			m_strSymKey+=array;					
	}
	m_barrSetCondition[1] = true; 
	EnDisButtons();
	ShowButtons();
	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnButtonShowSymKey() 
{
	if(!m_arrSetButtons[2])	
	{
		AfxMessageBox("Dieser Button ist im Moment inaktiv! Sie müssen vorher einen Schlüssel generieren!\n\nMit F1 erhalten Sie Informationen darüber, in welcher Reihenfolge Sie die Aktivitäten im Datenflussplan steuern können.",MB_ICONEXCLAMATION);
		return;
	}
	
	CString SymKeyInHexDump = "";
	//dataToHexDump(m_strSymKey,16,SymKeyInHexDump);

	for (int i=0;i<32;i++)
	{
		SymKeyInHexDump += m_strSymKey[i];
		if(i%2==1)
		{
			SymKeyInHexDump += ' ';
		}
		
	}
	m_strEdit = SymKeyInHexDump;
	m_strTitle = "symmetrischer Schlüssel:";
	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnButtonEncTxtSym() 
{
	if(!m_arrSetButtons[5])	
	{
		AfxMessageBox("Dieser Button ist im Moment inaktiv!\n\nMit F1 erhalten Sie Informationen darüber,in welcher Reihenfolge\nSie die Aktivitäten im Datenflussplan steuern können",MB_ICONEXCLAMATION);
		return;
	}
		UpdateData(true);
	
		char* strPathEncTxt;
		strPathEncTxt=new char[20];
		int AlgId=3;


		const char* path=m_strPathnameTxt.GetBuffer(0);
		ifstream test(path,ios::in|ios::binary);
		//normaler Text wird aus der ausgewählten Datei ausgelesen

		if(!test)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_Hashdemo_FileNotFound,pc_str,100);
			AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
			return;
		}

		
		{
			struct stat *obj;
			obj = new (struct stat);
			obj->st_size;
			stat((const char*)m_strPathnameTxt,obj);
			m_iDatGroesse1 = obj->st_size;
			delete obj;
		}
		//Groesse der Datei die ausgelesen werden soll wird 
		//ermittelt und in m_iDataGroesse geschrieben

		// unsigned char* in=new unsigned char[m_iDatGroesse1];
		// test.read(in,m_iDatGroesse1);
		//Gewählte Datei wird ausgelesen und in "in" gespeichert

		GetTmpName(strPathEncTxt,"cry",".tmp");
		//Name für eine temporäre Datei wird erzeugt, in der 
		//der Verschluesselte Text geschrieben werden soll

		char key[100];
		theApp.DoWaitCursor(1);
		strcpy(key,m_strSymKey.GetBuffer(0));
		AESCrypt((char*)path, "", AlgId,strPathEncTxt,key);
		
		unsigned char* cryTxt;
		cryTxt=new unsigned char[m_iDatGroesse1+32];

		ifstream crypt(strPathEncTxt,ios::in|ios::binary);
		crypt.read(cryTxt,m_iDatGroesse1+KEY_LEN);


		int srcSize = crypt.gcount();

		int len = 20;
		int destSize; 
		{
			int linelen;
			int lines, rest;

			linelen = 11 + len * 4;
			lines = (srcSize+len) / len;
			rest = (srcSize+1) % len;
			destSize = lines * linelen - len + rest;
		}
		char *strCryHex = new char [destSize+1];
		int err = HexDumpMem(strCryHex,destSize,cryTxt,srcSize, len);
		UpdateData();
		m_strEdit3 = "";
		m_strEdit3 = strCryHex;
		m_strTitle = "";
		m_strEdit = "";
		theApp.DoWaitCursor(0);

		m_barrSetCondition[5] = true;
		EnDisButtons();
		ShowButtons();
		UpdateData(false);
		delete[] strCryHex;
		delete[] cryTxt;
}

void CDlgHybridEncryptionDemo::OnButtonGetAsymKey() 
{	
	RsaDialog1.disableButtons = true;

	if ( IDOK == RsaDialog1.DoModal() ) 
	{
		m_iIsGenAsymKey = true;
		m_barrSetCondition[3] = true;
		EnDisButtons();
		ShowButtons();
	}
	
	UpdateData(false);
}



void CDlgHybridEncryptionDemo::RSAEncrypt()
{
	// Dialogbox zur Auswahl des zu benutzenden (öffentlichen) Schlüssels anzeigen
	
	
	if(m_iIsGenAsymKey)
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
		CString caDB_keyid_name = KeyHandling.CreateDistName(RsaDialog1.Name, RsaDialog1.Firstname, RsaDialog1.CreatTime);
		// caDB_keyid_name: unter diesem Bezeichner/Namen wurde das Zertifikat in die CA-Datenbank geschrieben
		
		LPTSTR string3 = new TCHAR[caDB_keyid_name.GetLength()+1];
		_tcscpy(string3, caDB_keyid_name);
		char *string4=string3; // string4 wird benutzt, um in der CA-Datenbank die Parameter abzufragen 
		
		// Öffnen der CA-PSE
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
		
		// Besorgen des öffentlichen Schlüssels des Adressaten aus seinem Zertifikat
		Key Schluessel;
		Schluessel.key=Zert->tbs->subjectPK;
		Schluessel.pse_sel=NULL;
		Schluessel.alg=theApp.SecudeLib.rsa_aid;
		Schluessel.add_object=NULL;
		Schluessel.add_object_type=NULL;
		Schluessel.key_size=NULL;
		Schluessel.private_key=NULL;
		
		// Verschlüsselung der Daten
		int fret = theApp.SecudeLib.af_encrypt_all(PseHandle, in, &out, &Schluessel, NULL);
		if (fret==-1)
		{  
			// Fehler bei der Entschlüsselung
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

		// Ausgabe der verschlüsselten Daten

		EncSymKey = theApp.SecudeLib.aux_BString2OString(&out);
		
	
		
		theApp.SecudeLib.af_close (PseHandle);
		theApp.SecudeLib.aux_free_SET_OF_IssuedCertificate (&Liste);
		theApp.SecudeLib.aux_free_Certificate (&Zert);
		delete string3;	
	}

	
}

void CDlgHybridEncryptionDemo::OnButtonEncKeyAsym() 
{
	if(!m_arrSetButtons[6])	
	{
		AfxMessageBox("Dieser Button ist im Moment inaktiv!\n\nMit F1 erhalten Sie Informationen darüber, in welcher Reihenfolge\nSie die Aktivitäten im Datenflussplan steuern können",MB_ICONEXCLAMATION);
		return;
	}
	theApp.DoWaitCursor(1);
	RSAEncrypt();
	UpdateData();
	m_strEdit4 = "";
	m_strEdit = "";
	for (unsigned int j=0;j<EncSymKey->noctets;j++)
	{
			char array[3];
			_snprintf(array,3,"%02.2X",(unsigned char) EncSymKey->octets[j]);
			m_strEdit4+=array;					
	}
	m_strTitle = "";
	m_barrSetCondition[6] = true;
	EnDisButtons();
	ShowButtons();
	UpdateData(false);
	theApp.DoWaitCursor(0);
}




void CDlgHybridEncryptionDemo::OnButtonShowAsymKey() 
{
	if(!m_arrSetButtons[4])	
	{
		AfxMessageBox("Dieser Button ist im Moment inaktiv, sie müssen vorher einen Schlüssel wählen!\n\nMit F1 erhalten Sie Informationen darüber, in welcher Reihenfolge\nSie die Aktivitäten im Datenflussplan steuern können",MB_ICONEXCLAMATION);
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
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_MEMORY_RSA_ENCRYPTION,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (pc_str,MB_ICONSTOP);
		return;
	}
	
	CKeyFile KeyHandling;
	CString caDB_keyid_name = KeyHandling.CreateDistName(RsaDialog1.Name, RsaDialog1.Firstname, RsaDialog1.CreatTime);
	// caDB_keyid_name: unter diesem Bezeichner/Namen wurde das Zertifikat in die CA-Datenbank geschrieben
	
	LPTSTR string3 = new TCHAR[caDB_keyid_name.GetLength()+1];
	_tcscpy(string3, caDB_keyid_name);
	char *string4=string3; // string4 wird benutzt, um in der CA-Datenbank die Parameter abzufragen 
	
	// Öffnen der CA-PSE
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
	
	// Besorgen des öffentlichen Schlüssels des Adressaten aus seinem Zertifikat
	Key Schluessel;
	Schluessel.key=Zert->tbs->subjectPK;
	Schluessel.pse_sel=NULL;
	Schluessel.alg=theApp.SecudeLib.rsa_aid;
	Schluessel.add_object=NULL;
	Schluessel.add_object_type=NULL;
	Schluessel.key_size=NULL;
	Schluessel.private_key=NULL;

	CDlgShowKeyParameter dlg;
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


void CDlgHybridEncryptionDemo::EnDisButtons()
{
	for(int i=0;i<10;i++)
	{
		m_arrSetButtons[i]=true;
		for(int j=0;j<10;j++)
		{
			if(m_check[i][j])
			{
				if(!m_barrSetCondition[j])
				{
					m_arrSetButtons[i]=false;
					break;
				}
				
			}
		}
	}

}

void CDlgHybridEncryptionDemo::GetCertificateData(Certificate *Zert)
{

}

void CDlgHybridEncryptionDemo::OnButtonShowtxt() 
{
	if(!m_arrSetButtons[7])	
	{
		AfxMessageBox("Dieser Button ist im Moment inaktiv, sie müssen vorher eine Datei auswählen!\n\nMit F1 erhalten Sie Informationen darüber, in welcher Reihenfolge\nSie die Aktivitäten im Datenflussplan steuern können",MB_ICONEXCLAMATION);
		return;
	}
	m_strTitle = m_strTitle1;


	int len = 20;
	int destSize; 
	{
		int linelen;
		int lines, rest;

		linelen = 11 + len * 4;
		lines = (m_gc+len) / len;
		rest = (m_gc+1) % len;
		destSize = lines * linelen - len + rest;
	}
	char *dest = new char [destSize+1];
	theApp.DoWaitCursor(1);
	int err = HexDumpMem(dest,destSize,(unsigned char*)m_strEdit1,m_gc, len);
	m_strEdit = dest;
	theApp.DoWaitCursor(0);
	
	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnShowEncTxt() 
{
	if(!m_arrSetButtons[8])	
	{
		AfxMessageBox("Dieser Button ist im Moment inaktiv! Sie müssen vorher die Datei mit dem symmetrischen Schlüssel verschlüsseln!\n\nMit F1 erhalten Sie Informationen darüber, in welcher Reihenfolge\nSie die Aktivitäten im Datenflussplan steuern können",MB_ICONEXCLAMATION);
		return;
	}
	theApp.DoWaitCursor(1);
	m_strEdit = m_strEdit3;
	m_strTitle = "symmetrisch verschlüsselter Text: ";
	UpdateData(false);
	theApp.DoWaitCursor(0);
}

void CDlgHybridEncryptionDemo::OnShowEncSymKey() 
{
	if(!m_arrSetButtons[9])	
	{
		AfxMessageBox("Dieser Button ist im Moment inaktiv! Sie müssen vorher den symmetrischen Schlüssel\nasymmetrisch verschlüsseln!\n\nMit F1 erhalten Sie Informationen darüber, in welcher Reihenfolge\nSie die Aktivitäten im Datenflussplan steuern können",MB_ICONEXCLAMATION);
		return;
	}
	theApp.DoWaitCursor(1);
	m_strTitle = "asymmetrisch verschlüsselter symmetrischer Schlüssel :";
	m_strEdit = m_strEdit4;
	UpdateData(false);
	theApp.DoWaitCursor(0);
}

void CDlgHybridEncryptionDemo::ShowButtons()
{

	for(int i=0;i<10;i++)
	{
	
		switch(i)
		{
		case 0:break;
		case 1:break;
		case 2:if(m_arrSetButtons[i])
			   {
					m_ctrlBmpRaute2.LoadBitmaps("RAUTE2U","RAUTE2D","RAUTE2F",NULL);
					m_ctrlBmpRaute2.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute2.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpRaute2.LoadBitmaps("RAUTE2X",NULL,NULL,NULL);
					m_ctrlBmpRaute2.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute2.ShowWindow(SW_SHOW);
			   
			   };break;
		case 3:break;
		case 4:if(m_arrSetButtons[i])
			   {
					m_ctrlBmpRaute3.LoadBitmaps("RAUTE3U","RAUTE3D","RAUTE3F",NULL);
					m_ctrlBmpRaute3.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute3.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpRaute3.LoadBitmaps("RAUTE3X",NULL,NULL,NULL);
					m_ctrlBmpRaute3.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute3.ShowWindow(SW_SHOW);
			   
			   };break;
		case 5:if(m_arrSetButtons[i])
			   {
					m_ctrlBmpViereck1.LoadBitmaps("VIERECK1U","VIERECK1D","VIERECK1F",NULL);
					m_ctrlBmpViereck1.ShowWindow(SW_HIDE);
					m_ctrlBmpViereck1.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpViereck1.LoadBitmaps("VIERECK1X",NULL,NULL,NULL);
					m_ctrlBmpViereck1.ShowWindow(SW_HIDE);
					m_ctrlBmpViereck1.ShowWindow(SW_SHOW);
			   
			   };break;
		case 6:if(m_arrSetButtons[i])
			   {
					m_ctrlBmpViereck2.LoadBitmaps("VIERECK2U","VIERECK2D","VIERECK2F",NULL);
					m_ctrlBmpViereck2.ShowWindow(SW_HIDE);
					m_ctrlBmpViereck2.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpViereck2.LoadBitmaps("VIERECK2X",NULL,NULL,NULL);
					m_ctrlBmpViereck2.ShowWindow(SW_HIDE);
					m_ctrlBmpViereck2.ShowWindow(SW_SHOW);
			   
			   };break;
		case 7:if(m_arrSetButtons[i])
			   {
					m_ctrlBmpRaute1.LoadBitmaps("RAUTE1U","RAUTE1D","RAUTE1F",NULL);
					m_ctrlBmpRaute1.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute1.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpRaute1.LoadBitmaps("RAUTE1X",NULL,NULL,NULL);
					m_ctrlBmpRaute1.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute1.ShowWindow(SW_SHOW);
			   
			   };break;
		case 8:if(m_arrSetButtons[i])
			   {
					m_ctrlBmpRaute4.LoadBitmaps("RAUTE4U","RAUTE4D","RAUTE4F",NULL);
					m_ctrlBmpRaute4.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute4.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpRaute4.LoadBitmaps("RAUTE4X",NULL,NULL,NULL);
					m_ctrlBmpRaute4.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute4.ShowWindow(SW_SHOW);
			   
			   };break;
		case 9:if(m_arrSetButtons[i])
			   {
					m_ctrlBmpRaute5.LoadBitmaps("RAUTE5U","RAUTE5D","RAUTE5F",NULL);
					m_ctrlBmpRaute5.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute5.ShowWindow(SW_SHOW);
			   }
			   else
			   {
					m_ctrlBmpRaute5.LoadBitmaps("RAUTE5X",NULL,NULL,NULL);
					m_ctrlBmpRaute5.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute5.ShowWindow(SW_SHOW);
			   
			   };break;

		}
	}
}

BOOL CDlgHybridEncryptionDemo::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	 if (m_bCursor)
	 return TRUE;
	 else	
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

CDlgHybridEncryptionDemo::~CDlgHybridEncryptionDemo()
{
	if(m_strEdit1)
	//wenn für m_strEdit1 Speicher allokiert wurde, dann wird hier der Speicher wieder freigegeben
	{
		delete []m_strEdit1;
	}

}
