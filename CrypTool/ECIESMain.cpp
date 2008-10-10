
//cvact-Library
#include "actInit.h"
#include "actAlgorithm.h"
#include "actTools.h"
#include "actDate.h"
#include "actIRNGAlg.h"

#include "stdafx.h"
#include "CrypToolApp.h"
#include "ECIESMain.h"
#include "DlgECCEncReceiver.h"
//#include "DlgECCEncSender.h"
#include "DlgECCDecReceiver.h"
#include "FileTools.h"
#include "CrypToolTools.h"
#include "s_ecFp.h" // elliptic curve stuff
#include "s_ecconv.h"
#include <time.h>

#include "DialogeMessage.h" // ## Sp�ter Ersetzen durch Tools.h


extern char *Pfad; // Directory Path of the main programm
extern char pc_str[STR_LAENGE_STRING_TABLE]; // from multipad.cpp
extern char *CaPseDatei, *CaPseVerzeichnis, *Pfad, *PseVerzeichnis; 


/*
Funktion zur Verschl�sselung der Daten im aktuellen Fenster mittels ECC
*/
void ECCEnc(char* infile, const char *OldTitle){
#ifndef DISABLE_CV
//Initialisierung der Library
act::Init();

// Variablen des Senders
	
CString SenderName="";
CString SenderFirstname="";
CString SenderKeyType="";
CString Senderpasswd="";
CString SenderUserKeyId="";
CString SenderprivKey="";

// Variablen des Emp�ngers
CString ReceiverName="";
CString ReceiverFirstname="";
CString ReceiverKeyType="";	
CString ReceiverUserKeyId="";
CString ReceiverpubKey_xcoord="";
CString ReceiverpubKey_ycoord="";
	
clock_t sigStart;
clock_t sigFinish;
double duration;
int error;
	


	//########################## Dialog Sender #################################
/*
CDlgECCEncSender ECCEncDialogSender;
	if(ECCEncDialogSender.DoModal()==IDOK)
	
		{

		// *********************** Sender Key ermitteln 
		
		
		//Konvertieren der Pin-Nummer von CString nach char *
		LPTSTR string1 = new TCHAR[ECCEncDialogSender.m_PinCode.GetLength()+1];
		_tcscpy(string1, ECCEncDialogSender.m_PinCode);
		char *PIN=string1;
			
		
		// SenderName,SenderVorname,SenderKeyType und Sender Pin speichern
		SenderName=ECCEncDialogSender.Name;
		SenderFirstname=ECCEncDialogSender.Firstname;
		SenderKeyType=ECCEncDialogSender.KeyType;
		Senderpasswd=ECCEncDialogSender.m_PinCode;
		SenderUserKeyId=ECCEncDialogSender.UserKeyId;
		
		//Pfad mit Dateinamen der PSE des Entschl�sselers in char * konvertieren
		CString help2=(CString)PseVerzeichnis+((CString)"/")+ECCEncDialogSender.UserKeyId+((CString)PSE_FILE_SUFFIX);
		LPTSTR string2 = new TCHAR[help2.GetLength()+1];
		_tcscpy(string2, help2);
		char *PfadNeu=string2;
		
		//�ffnen der PSE des Entschl�sselers

		PSE PseHandle;
		PseHandle = theApp.SecudeLib.af_open(PfadNeu, NULL, PIN, NULL);
		if (PseHandle==NULL)
		{
			if (theApp.SecudeLib.LASTERROR==EPIN)
			{
				// falsche PIN-Nummer benutzt
				Message(IDS_STRING_PRIVKEY_WRONG_PIN, MB_ICONEXCLAMATION);
				// Freigeben von dynamisch angelegtem Speicher
			//	theApp.SecudeLib.aux_free_OctetString(&help);
			//	free(out.octets);
				delete string1;
				delete string2;
				return;
			}
			Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			// Freigeben von dynamisch angelegtem Speicher
		//	theApp.SecudeLib.aux_free_OctetString(&help);
		//	free(out.octets);
			delete string1;
			delete string2;
			return;
		}
		
		// PSE des Senders wurde erfolgreich ermittelt

		//Besorgen des privaten Schl�ssels
		
		ShowPrivateKey(SenderUserKeyId,Senderpasswd,SenderprivKey);

		Senderpasswd="+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
		Senderpasswd="";
		
		
		//########################## Dialog Empf�nger #################################

		*/
		CDlgECCEncReceiver ECCEncDialogReceiver;
		ECCEncDialogReceiver.SenderKeyType=SenderKeyType;
		if(ECCEncDialogReceiver.DoModal()==IDOK)
		{

		// ReceiverName,ReceiverVorname,ReceiverKeyType und ReceiverUserKeyId speichern
		ReceiverName=ECCEncDialogReceiver.Name;
		ReceiverFirstname=ECCEncDialogReceiver.Firstname;
		ReceiverKeyType=ECCEncDialogReceiver.KeyType;
		ReceiverUserKeyId=ECCEncDialogReceiver.UserKeyId;
		
		// NEU
		SenderKeyType=ECCEncDialogReceiver.KeyType;
			// PSE des Empf�ngers  wurde erfogreich ermittelt

			//Besorgen des �ffentlichen Schl�ssels
			ShowPublicKey(ReceiverUserKeyId,ReceiverpubKey_xcoord,ReceiverpubKey_ycoord);
			
			SHOW_HOUR_GLASS
			
			sigStart = clock();

			//Verschl�sseln der Daten 
			
			SenderprivKey.AppendChar('\0');
			char* sS=new char[SenderprivKey.GetLength()];
			for(int i= 0;i<SenderprivKey.GetLength();i++)
				sS[i]=SenderprivKey.GetAt(i);
			ReceiverpubKey_xcoord.AppendChar('\0');
			char* R_xcoord=new char[ReceiverpubKey_xcoord.GetLength()];
			for(int i= 0;i<ReceiverpubKey_xcoord.GetLength();i++)
				R_xcoord[i]=ReceiverpubKey_xcoord.GetAt(i);
			ReceiverpubKey_ycoord.AppendChar('\0');
			char* R_ycoord=new char[ReceiverpubKey_ycoord.GetLength()];
			for(int i= 0;i<ReceiverpubKey_ycoord.GetLength();i++)
				R_ycoord[i]=ReceiverpubKey_ycoord.GetAt(i);

			act::Blob output;

			error=encrypt(output,SenderName,SenderFirstname,ReceiverName,ReceiverFirstname,sS,SenderKeyType,R_xcoord,R_ycoord,ReceiverKeyType,infile);
			//error-values: 0=ok, 11=no curve found (sender), 12=not on curve (sender), 21=no curve found (receiver) 22=not on curve (receiver)
			//encrypt terminated normally
			if (error==0)
			{
				newWindow(false,output, OldTitle,ReceiverName,ReceiverFirstname,ReceiverKeyType);

				
				//   **** Ende Verschl�sselung ****

				sigFinish = clock();
				duration = (double)(sigFinish - sigStart) / CLOCKS_PER_SEC;			


				HIDE_HOUR_GLASS 
				
				// Ben�tigte Zeit zum verschl�sseln ausgeben, falls gew�nscht
				if (ECCEncDialogReceiver.m_ShowDuration==TRUE)
				{
					LoadString(AfxGetInstanceHandle(),IDS_ECIES_ENC_TIME,pc_str1,STR_LAENGE_STRING_TABLE);
					char strDuration[20];
					double_fmt( duration, strDuration, 3 );
					sprintf(pc_str, pc_str1, strDuration);
					AfxMessageBox (((CString)pc_str),MB_ICONINFORMATION|MB_OK);
				}
//				theApp.SecudeLib.af_close (PseHandle);
			}

			//11=no curve found (sender)
			
			else if(error==11)
			{
				LoadString(AfxGetInstanceHandle(),IDS_ECIES_ENC_ERROR_11,pc_str,STR_LAENGE_STRING_TABLE);
				AfxMessageBox(pc_str);
			}
			else if(error==12)
			{
				LoadString(AfxGetInstanceHandle(),IDS_ECIES_ENC_ERROR_12,pc_str,STR_LAENGE_STRING_TABLE);
				AfxMessageBox(pc_str);
			}
			else if(error==21)
			{
				LoadString(AfxGetInstanceHandle(),IDS_ECIES_ENC_ERROR_21,pc_str,STR_LAENGE_STRING_TABLE);
				AfxMessageBox(pc_str);
			}
			else if(error==22)
			{
				LoadString(AfxGetInstanceHandle(),IDS_ECIES_ENC_ERROR_22,pc_str,STR_LAENGE_STRING_TABLE);
				AfxMessageBox(pc_str);
			}
			
		}
#endif
	}
//}

/*
Funktion zur Entschl�sselung der Daten im aktuellen Fenster mittels ECC
*/
void ECCDec(char* infile, const char *OldTitle)
{
#ifndef DISABLE_CV
//Initialisierung der Library
act::Init();

// Variablen des Emp�ngers
CString ReceiverName="";
CString ReceiverFirstname="";
CString ReceiverKeyType="";	
CString ReceiverUserKeyId="";
CString Receiverpasswd="";
CString ReceiverprivKey="";
	
//	char outfile[128], title[128];
//    CAppDocument *NewDoc;
//	GetTmpName(outfile,"cry",".tmp");

clock_t sigStart;
clock_t sigFinish;
double duration;
int error;

	
	//########################## Dialog Empf�nger #################################
	CDlgECCDecReceiver ECCDecDialogReceiver;
	if(ECCDecDialogReceiver.DoModal()==IDOK)
	{
			
		// ReceiverName,ReceiverVorname,ReceiverKeyType und ReceiverUserKeyId speichern
		
		ReceiverName=ECCDecDialogReceiver.Name;
		ReceiverFirstname=ECCDecDialogReceiver.Firstname;
		ReceiverKeyType=ECCDecDialogReceiver.KeyType;
		ReceiverUserKeyId=ECCDecDialogReceiver.UserKeyId;
		Receiverpasswd=ECCDecDialogReceiver.m_PinCode;
		
	
		//Konvertieren der Pin-Nummer von CString nach char *
		LPTSTR string1 = new TCHAR[ECCDecDialogReceiver.m_PinCode.GetLength()+1];
		_tcscpy(string1, ECCDecDialogReceiver.m_PinCode);
		char *PIN=string1;
		
		//Pfad mit Dateinamen der PSE des Entschl�sselers in char * konvertieren
		CString help2=(CString)PseVerzeichnis+((CString)"/")+ECCDecDialogReceiver.UserKeyId+((CString)PSE_FILE_SUFFIX);
		LPTSTR string2 = new TCHAR[help2.GetLength()+1];
		_tcscpy(string2, help2);
		char *PfadNeu=string2;
		
		//�ffnen der PSE des Entschl�sselers
		PSE PseHandle;
		PseHandle = theApp.SecudeLib.af_open(PfadNeu, NULL, PIN, NULL);
		if (PseHandle==NULL)
		{
			if (theApp.SecudeLib.LASTERROR==EPIN)
			{
				// falsche PIN-Nummer benutzt
				Message(IDS_STRING_PRIVKEY_WRONG_PIN, MB_ICONEXCLAMATION);
				// Freigeben von dynamisch angelegtem Speicher
				//theApp.SecudeLib.aux_free_OctetString(&help);
				//free(out.octets);
				delete string1;
				delete string2;
				return;
			}
			Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			// Freigeben von dynamisch angelegtem Speicher
			//theApp.SecudeLib.aux_free_OctetString(&help);
			//free(out.octets);
			delete string1;
			delete string2;
			return;
		}
		
		// PSE des Empf�ngers  wurde erfogreich ermittelt
		//Besorgen des privaten Schl�ssels
		ShowPrivateKey(ReceiverUserKeyId,Receiverpasswd,ReceiverprivKey);

		SHOW_HOUR_GLASS
		
		sigStart = clock();

		//Entschl�sseln der Daten 
		
		ReceiverprivKey.AppendChar('\0');
		char* sR=new char[ReceiverprivKey.GetLength()];
		for(int i= 0;i<ReceiverprivKey.GetLength();i++)
			sR[i]=ReceiverprivKey.GetAt(i);

		act::Blob output;
		error=decrypt(output,ReceiverName,ReceiverFirstname,sR,ReceiverKeyType,infile);
		//error-values: 0=file ok, 1=corrupt header, 2=corrupt encrypted session key, 3=corrupt ciphertext, 42=wrong ECIES-key, 5=bad ciphertext or bad AES-Key, don't match
		if(error==1)
		{
			LoadString(AfxGetInstanceHandle(),IDS_ECIES_DEC_ERROR_01,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str);
		}
		//2=corrupt encrypted session key
		else if(error==2)
		{
			LoadString(AfxGetInstanceHandle(),IDS_ECIES_DEC_ERROR_02,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str);
		}
		//3=corrupt ciphertext
		else if(error==3)
		{
			LoadString(AfxGetInstanceHandle(),IDS_ECIES_DEC_ERROR_03,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str);
		}
		//42=wrong ECIES-key
		else if(error==42)
		{
			LoadString(AfxGetInstanceHandle(),IDS_ECIES_DEC_ERROR_42,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str);
		}
		//5=bad ciphertext or bad AES-Key, don't match
		else if(error==5)
		{
			LoadString(AfxGetInstanceHandle(),IDS_ECIES_DEC_ERROR_05,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str);
		}
		else if(error==0)
		{
			newWindow(true,output,OldTitle,ReceiverName,ReceiverFirstname,ReceiverKeyType);
		}
		//
		sigFinish = clock();
		duration = (double)(sigFinish - sigStart) / CLOCKS_PER_SEC;			

		//theApp.SecudeLib.aux_free_OctetString(&help);
		
		//Ausgabe der verschluesselten Daten
		//theApp.SecudeLib.aux_OctetString2file(&out, outfile, 2);
		//free(out.octets);
		
		//theApp.SecudeLib.aux_free_BitString(&in);
		//free(in.bits);
		
		//NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
		//remove(outfile);
		
		HIDE_HOUR_GLASS // theApp.DoWaitCursor(0);
		
		//if(NewDoc) {
		//	LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_RSA_DECRYPTION_OF,pc_str,STR_LAENGE_STRING_TABLE);
		//	MakeNewName(title,sizeof(title),pc_str,OldTitle);
		//	NewDoc->SetTitle(title);
		//}

		// Ben�tigte Zeit zum entschl�sseln ausgeben, falls gew�nscht
		if (ECCDecDialogReceiver.m_ShowDuration==TRUE)
		{
			LoadString(AfxGetInstanceHandle(),IDS_ECIES_DEC_TIME,pc_str1,STR_LAENGE_STRING_TABLE);
			char strDuration[20];
			double_fmt( duration, strDuration, 3 );
			sprintf(pc_str, pc_str1, strDuration);
			AfxMessageBox (((CString)pc_str),MB_ICONINFORMATION|MB_OK);
		}
		theApp.SecudeLib.af_close (PseHandle);
		// Freigeben von dynamisch angelegtem Speicher
		delete string1;
		delete string2;
		Receiverpasswd="+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
		Receiverpasswd="";
		
	}
#endif
}
//////////////////////////////////////////////////////////////////////////////////////
// �ffentliche Schl�sselparameter anzeigen f�r
// - EC-Schl�ssel
// pubKey_xcoord, pubKey_ycoord wird in den Parametern zur�ckgegeben

void ShowPublicKey(CString &UserKeyId, CString &pubKey_xcoord, CString &pubKey_ycoord) 
{
#ifndef DISABLE_CV

		EcDomParam_ac_ptr curveParameter;
		
		curveParameter = (EcDomParam_ac_ptr) malloc(sizeof(__DomParamAc_struct)); // Allocate memory. !! DELETE with destruktor!!
		if (curveParameter == NULL) return; // error. keine Speicherallokation
		curveParameter->E = (ecFp_curve_t) malloc(sizeof(__CurveFp_struct));
		if (curveParameter->E == NULL) return; // error. keine Speicherallokation
		curveParameter->G = (ecFp_point_ac_t) malloc(sizeof(__PointAc_struct));
		if (curveParameter->G == NULL) return; // error. keine Speicherallokation
		curveParameter->pubKey = (ecFp_point_ac_t) malloc(sizeof(__PointAc_struct));
		if (curveParameter->pubKey == NULL) return; // error. keine Speicherallokation
		curveParameter->pubKey->infinity=1; // pubKey is not defined yet
		inttoln(0, curveParameter->privKey); // initialize privKey = 0 (not defined yet)

		CKeyFile KeyFileHandling;
		int ret;
		ret = KeyFileHandling.GetEcPublicParam(UserKeyId, curveParameter);
		if ( ret == -1 )
		{
			// error. Die Datei "UserKeyId" konnte nicht ge�ffnet werden
			CString PubDataFile = (CString) PseVerzeichnis + ((CString)"/") + (CString) UserKeyId;
			{
				LPTSTR string3 = new TCHAR[PubDataFile.GetLength()+1];
				_tcscpy(string3, PubDataFile);		
				char *toc_file = string3;

				Message(IDS_STRING_EC_ERROR_LOADING_KEYFILE, MB_ICONINFORMATION, toc_file);
				delete string3;
			}
			free (curveParameter->pubKey);
			free (curveParameter->G);
			free (curveParameter->E);
			free (curveParameter);		
			return;
		}
		else if ( ret != 0)
		{
			// error. sonstige Fehler in der Methode CKeyFile::GetEcPublicParam()
			free (curveParameter->pubKey);
			free (curveParameter->G);
			free (curveParameter->E);
			free (curveParameter);		
			return;
		}

		
		// Dialog anzeigen
		//CDlgShowPublicKeyEC PubParamDlg(UserKeyId, "Name", "Firstname", "CreatTime", "KeyType", curveParameter);
		//PubParamDlg.DoModal();			
	
	if (curveParameter->pubKey->infinity == 0)
	{
		// pubkey ist nicht neutrales Element der ellipt. Kurve Gruppe
		pubKey_xcoord = (CString) ecFp_point_getstr_xcoord_ac (curveParameter->pubKey, 16);
		pubKey_ycoord = (CString) ecFp_point_getstr_ycoord_ac (curveParameter->pubKey, 16);
	}
	else
	{
		// pubkey ist neutrales Element O=(inf,inf) der ellipt. Kurve Gruppe
		pubKey_xcoord  = (CString) "inf";
		pubKey_ycoord = (CString) "inf";
	}

	if (pubKey_xcoord.GetLength()>2) pubKey_xcoord.SetAt(1,'x'); // wichtig : Offest muss ein kleines x sein
	if (pubKey_ycoord.GetLength()>2) pubKey_ycoord.SetAt(1,'x'); // wichtig : Offest muss ein kleines x sein

		free (curveParameter->pubKey);
		free (curveParameter->G);
		free (curveParameter->E);
		free (curveParameter);
#endif		
}

//////////////////////////////////////////////////////////////////////////////////////
// Private Schl�sselparameter anzeigen f�r
// - EC-Schl�ssel
// privKey wird in den Parametern zur�ckgegeben

void ShowPrivateKey(CString &UserKeyId, CString &passwd, CString &privKey) 
{
#ifndef DISABLE_CV

	EcDomParam_ac_ptr curveParameter;
	
	curveParameter = (EcDomParam_ac_ptr) malloc(sizeof(__DomParamAc_struct)); // Allocate memory. !! DELETE with destruktor!!
	if (curveParameter == NULL) return; // error. keine Speicherallokation
	curveParameter->E = (ecFp_curve_t) malloc(sizeof(__CurveFp_struct));
	if (curveParameter->E == NULL) return; // error. keine Speicherallokation
	curveParameter->G = (ecFp_point_ac_t) malloc(sizeof(__PointAc_struct));
	if (curveParameter->G == NULL) return; // error. keine Speicherallokation
	curveParameter->pubKey = (ecFp_point_ac_t) malloc(sizeof(__PointAc_struct));
	if (curveParameter->pubKey == NULL) return; // error. keine Speicherallokation
	curveParameter->pubKey->infinity=1; // pubKey is not defined yet
	inttoln(0, curveParameter->privKey); // initialize privKey = 0 (not defined yet)

	CKeyFile KeyFileHandling;
	int ret;
	ret = KeyFileHandling.GetEcAllParam(UserKeyId, passwd, curveParameter);
	if ( ret == -1)
	{
		// falsche PIN-Nummer zum �ffnen der PSE benutzt
		Message(IDS_STRING_PRIVKEY_WRONG_PIN, MB_ICONEXCLAMATION);
		// Speicher freigeben
		free (curveParameter->pubKey);
		free (curveParameter->G);
		free (curveParameter->E);
		free (curveParameter);
		return;
	}
	else if ( ret == -2)
	{
		// sonstiger Fehler beim �ffnen der PSE
		Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE, MB_ICONSTOP);
		// Speicher freigeben
		free (curveParameter->pubKey);
		free (curveParameter->G);
		free (curveParameter->E);
		free (curveParameter);
		return;
	}
	else if (ret != 0)
	{
		// sonstiger Fehler in CKeyFile::GetEcAllParam()
		// Speicher freigeben
		free (curveParameter->pubKey);
		free (curveParameter->G);
		free (curveParameter->E);
		free (curveParameter);
		return;
	}
	//Dialog anzeigen
	
	//CDlgShowPrivateKeyEC PrivParamDlg(UserKeyId, "Name", "Firstname", "CreatTime", "KeyType",curveParameter);
	//PrivParamDlg.DoModal();	

	char *privKeyStr;
	int error = 0;	
	
	error += ln_to_string (curveParameter->privKey, &privKeyStr, 16);
	privKey = (CString) privKeyStr;
	free(privKeyStr);
	// if error > 0 then something is wrong
	//*privKeyStr[1]='x';
	if (privKey.GetLength()>2) privKey.SetAt(1,'x'); // wichtig : Offest muss ein kleines x sein
	
	passwd="";
	free (curveParameter->pubKey);
	free (curveParameter->G);
	free (curveParameter->E);
	free (curveParameter);
#endif
}


#ifndef DISABLE_CV

int encrypt(act::Blob &encBlob, const CString &sName, const CString &sVorname, const CString &rName, const CString &rVorname, const char* sS, const CString &curveS, const char* xR, const char* yR, const CString curveR, const char* ifile)
{
	//error-values: 0=key ok, 1=no curve found, 2=not on curve (invalid key)
	//return-values: 0=ok, 11=no curve found (sender), 12=invalid key (sender), 21=no curve found (receiver) 22=invalid key (receiver)
	int error;
	//privater ECIES-Schl�ssel des Senders
	act::Key privSendECIES("IES");
	
	// NEU
		if(curveR=="EC-prime192v1")
			privSendECIES.SetParam(act::CURVE,act::ANSIp192r1);
		else if(curveR=="EC-prime192v2")
			privSendECIES.SetParam(act::CURVE,act::ANSIp192r2);
		else if(curveR=="EC-prime192v3")
			privSendECIES.SetParam(act::CURVE,act::ANSIp192r3);
		else if(curveR=="EC-prime239v1")
			privSendECIES.SetParam(act::CURVE,act::ANSIp239r1);
		else if(curveR=="EC-prime239v2")
			privSendECIES.SetParam(act::CURVE,act::ANSIp239r2);
		else if(curveR=="EC-prime239v3")
			privSendECIES.SetParam(act::CURVE,act::ANSIp239r3);
		else if(curveR=="EC-prime256v1")
			privSendECIES.SetParam(act::CURVE,act::ANSIp256r1);
	privSendECIES.Generate();
	// Ende Neu


	/*
	error=importKey(privSendECIES,curveS,"","",sS);
	//error-values: 0=key ok, 1=no curve found, 2=not on curve (invalid key)
	if(error==1)
		return 11;
	else if(error==2)
		return 12;

	*/

	//�ffentlicher ECIES-Schl�ssel des Empf�ngers
	act::Key pubRecECIES("IES");	
	error=importKey(pubRecECIES,curveR,xR,yR,"");
	//error-values: 0=key ok, 1=no curve found, 2=not on curve (invalid key)
	
	if(error==1)
		return 21;
	else if(error==2)
		return 22;
	
	//symmetrische Datenverschl�sselung
	act::Blob plaintext,ciphertext,sessionKey;
	act::file2blob(ifile, plaintext);
	encryptData(plaintext, sessionKey, ciphertext);
	
	//sessionkey wird ECIES-verschl�sselt
	act::Blob encryptedSessionKey;
	encryptSessionKey(pubRecECIES,privSendECIES,sessionKey,encryptedSessionKey);

	encBlob= writeEncFile("", sName, sVorname, rName, rVorname, curveR, encryptedSessionKey, ciphertext);
	return 0;
	
}

int decrypt(act::Blob &decBlob,const CString &rName, const CString &rVorname, const char* sR, const CString &curveR, const char* ifile)
{
	int error;

	//privater ECIES-Schl�ssel des Empf�ngers
	act::Key privRecECIES("IES");	
	error=importKey(privRecECIES,curveR,"","",sR);

	//error-values: 0=key ok, 1=no curve found, 2=not on curve (invalid key)
	if(error==1)
		return 11;
	else if(error==2)
		return 12;

	act::Blob ciphertext, decryptedtext, encryptedSessionKey, decryptedSessionKey;
	CString sNameInFile, sVornameInFile, rNameInFile, rVornameInFile;

	error=readEncFile(ifile, sNameInFile, sVornameInFile, rNameInFile, rVornameInFile, curveR, encryptedSessionKey, ciphertext);
	//error-values: 0=file ok, 1=corrupt header, 2=corrupt encrypted session key, 3=corrupt ciphertext, 42=wrong ECIES-key, 5=bad ciphertext or bad AES-Key, don't match

	if(error==0)
	{
		//ECIES-entschl�sselung des sessionkey
		error=decryptSessionKey(privRecECIES,encryptedSessionKey,decryptedSessionKey);

		if (error==0)
			//symmetrische Daten-Entschl�sselung
			error=decryptData(ciphertext, decryptedSessionKey, decBlob);
	}

	return error;
}
int importKey(act::Key& key, const CString kurve, const char* x, const char* y, const char* s)
{
	try
	{
		//error-values: 0=ok, 1=no curve found, 2=not on curve

		if(kurve=="EC-prime192v1")
			key.SetParam(act::CURVE,act::ANSIp192r1);
		else if(kurve=="EC-prime192v2")
			key.SetParam(act::CURVE,act::ANSIp192r2);
		else if(kurve=="EC-prime192v3")
			key.SetParam(act::CURVE,act::ANSIp192r3);
		else if(kurve=="EC-prime239v1")
			key.SetParam(act::CURVE,act::ANSIp239r1);
		else if(kurve=="EC-prime239v2")
			key.SetParam(act::CURVE,act::ANSIp239r2);
		else if(kurve=="EC-prime239v3")
			key.SetParam(act::CURVE,act::ANSIp239r3);
		else if(kurve=="EC-prime256v1")
			key.SetParam(act::CURVE,act::ANSIp256r1);
		else
			return 1;
		
		//act::Blob xB=act::hex2blob(x);
		//act::Blob yB=act::hex2blob(y);
		//act::Blob sB=act::hex2blob(s);


		//wenn ein privater Schl�ssel existiert, werden die �ffentlichen Parameter aus diesem generiert
		if(s!="")
			key.SetParam(act::PRIVATEKEY, s);
		else
		{
			key.SetParam(act::PUBLIC_X, x);
			key.SetParam(act::PUBLIC_Y, y);
			//wenn die Parameter x und y beide gesetzt sind, wird getestet, 
			//ob der durch sie definierte Punkt auf der Kurve liegt

		}
		return 0;

	}

	catch (act::InvalidKeyException & e)
	{
		return 2;
	}
	catch(act::Exception & e)
	{
		return 2;
	}
}

void encryptSessionKey(const act::Key &pubRecECIES, const act::Key &privSendECIES,  const act::Blob &sessionKey, act::Blob &encryptedSessionKey)
{
	try
	{			
		act::Blob publicBlob;

		pubRecECIES.Export(publicBlob,act::PUBLIC);

		act::Algorithm Encrypt(privSendECIES,act::ENCRYPT,publicBlob);
		Encrypt.Write(sessionKey);
		Encrypt.Finalize();
		Encrypt.Read(encryptedSessionKey);

	}
	catch(act::InvalidAlgorithmParameterException & e)
	{

	}
	catch(act::Exception & e)
			{
				cout << "Exception: " << typeid(e).name() << endl;
				cout << "what: " << e.what() << endl;
				cout << "where: " << e.where() << endl;
				
			}
 
}

int decryptSessionKey(const act::Key &privRecECIES, const act::Blob &encryptedSessionKey, act::Blob &sessionKey)
{
	try
	{			
		//act::Blob publicBlob;
		//pubSendECIES.Export(publicBlob,act::PUBLIC);

		act::Algorithm Decrypt(privRecECIES,act::DECRYPT);//,publicBlob);
		Decrypt.Write(encryptedSessionKey);
		Decrypt.Finalize();
		Decrypt.Read(sessionKey);
		return 0;
	}
	catch(act::Exception & e)
			{
				//wrong key
				return 42;	
			}
}
void encryptData(const act::Blob &plaintext, act::Blob &sessionKey, act::Blob &ciphertext)
{
	try
	{
		act::Key blockCipher("BlockCipher");
		blockCipher.SetParam(act::CIPHER, "AES");
		blockCipher.SetParam(act::BCMODE, "CBC");
		blockCipher.SetParam(act::KEYSIZE,32);
		//zus�tzliches Random Element bei der Erzeugung des session key
		act::Blob salt;
		act::Algorithm saltGen(act::CreateBBS());
		saltGen.Write(act::Date());
		saltGen.Read(salt,256);

		blockCipher.Derive(plaintext,salt);
		salt.clear();
		blockCipher.GetParam(act::RAWKEY,sessionKey);

		act::Algorithm encrypt(blockCipher,act::ENCRYPT);
		encrypt.Write(plaintext);
		encrypt.Finalize();
		encrypt.Read(ciphertext);
	}

	catch(act::Exception & e)
			{
				cout << "Exception: " << typeid(e).name() << endl;
				cout << "what: " << e.what() << endl;
				cout << "where: " << e.where() << endl;
				
			}
}

int decryptData(const act::Blob &ciphertext, const act::Blob &sessionKey, act::Blob &plaintext)
{
	try
	{
		act::Key blockCipher("BlockCipher");
		blockCipher.SetParam(act::CIPHER, "AES");
		blockCipher.SetParam(act::BCMODE, "CBC");
		blockCipher.SetParam(act::RAWKEY,sessionKey);

		act::Algorithm decrypt(blockCipher,act::DECRYPT);
		decrypt.Write(ciphertext);
		decrypt.Finalize();
		decrypt.Read(plaintext);
		return 0;
	}
	
	catch(act::Exception & e)
			{
				//bad ciphertext or bad AES-key
				return 5;	
			}
}

act::Blob writeEncFile(const CString &ofile, const CString &sName, const CString &sVorname, const CString &rName, const CString &rVorname, const CString curveR, const act::Blob &encryptedSessionKey, const act::Blob &ciphertext)
{
	//encryptedSessionKey in Hex konvertieren und in Blob schreiben
	//act::Blob hexKey(encryptedSessionKey.size()*2+1);
	//act::blob2hex(encryptedSessionKey,reinterpret_cast<char*>(&hexKey[0]));
	//ciphertext in Hex konvertieren und in Blob schreiben
	//act::Blob hexCipher(ciphertext.size()*2+1);
	//act::blob2hex(ciphertext, reinterpret_cast<char*>(&hexCipher[0]));

	//assemble the header 
	//name & firstname of receiver
	//LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_01,pc_str,STR_LAENGE_STRING_TABLE);
	//CString message=pc_str;
	//message.Append(sName);message.Append(", ");
	//message.Append(sVorname);
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_02,pc_str,STR_LAENGE_STRING_TABLE);
	//message.Append(pc_str);
	CString message=pc_str;
	message.Append(rName);
	message.Append(", ");
	message.Append(rVorname);
	//curve parameter
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_03,pc_str,STR_LAENGE_STRING_TABLE);
	message.Append(pc_str);
	message.Append(curveR);
	//encrypted session key length
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_04,pc_str,STR_LAENGE_STRING_TABLE);
	message.Append(pc_str);
	char* keylength=new char[3];
	itoa((int)encryptedSessionKey.size(),keylength,10);
	message.Append(keylength);
	//ciphertext length
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_05,pc_str,STR_LAENGE_STRING_TABLE);
	message.Append(pc_str);
	char* ciphertextlength=new char[10];
	itoa((int)ciphertext.size(),ciphertextlength,10);
	message.Append(ciphertextlength);
	//key tag
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_06,pc_str,STR_LAENGE_STRING_TABLE);
	message.Append(pc_str);

	//alles in output-Blob schreiben
	act::Blob output(message);
	output.insert(output.end(),encryptedSessionKey.begin(),encryptedSessionKey.end());
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_07,pc_str,STR_LAENGE_STRING_TABLE);
	act::Blob header07(pc_str);
	output.insert(output.end(),header07.begin(),header07.end());
	header07.clear();
	
	//output.insert(output.end(),hexCipher.begin(),hexCipher.end());
	output.insert(output.end(),ciphertext.begin(),ciphertext.end());
	//Koy fragen!
	//delete [] keylength;
	//delete [] ciphertextlength;
	
	return output;
	//act::blob2file(ofile,output);
}
int readEncFile(const CString &ifile, CString &sName, CString &sVorname, CString &rName, CString &rVorname, CString curveR, act::Blob &encryptedSessionKey, act::Blob &ciphertext)
{
	act::Blob input;
	act::file2blob(ifile,input);

	CString message,tag;
	message=reinterpret_cast<char*>(&input[0]);
	/* alt: mit sender-key und name
	//Sender
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_01,pc_str,STR_LAENGE_STRING_TABLE);
	tag=pc_str;
	int sNameTag=message.Find(tag);
	int sNameStart=sNameTag+tag.GetLength();
	int sNameEnd=message.Find(',',sNameStart);

	int& sVornameTag=sNameEnd;
	int sVornameStart=sVornameTag+2;
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_02,pc_str,STR_LAENGE_STRING_TABLE);
	tag=pc_str;
	int sVornameEnd=message.Find(tag,sVornameStart);
	
	//Receiver
	int& rNameTag=sVornameEnd;
	int rNameStart=rNameTag+tag.GetLength();
	int rNameEnd=message.Find(',',rNameStart);

	int& rVornameTag=rNameEnd;
	int rVornameStart=rVornameTag+2;
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_03,pc_str,STR_LAENGE_STRING_TABLE);
	tag=pc_str;
	int rVornameEnd=message.Find(tag,rVornameStart);
	*/

	//neu: nur receiver-key
	//Receiver
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_02,pc_str,STR_LAENGE_STRING_TABLE);
	tag=pc_str;
	int rNameTag=message.Find(tag);
	int rNameStart=rNameTag+tag.GetLength();
	int rNameEnd=message.Find(',',rNameStart);

	int& rVornameTag=rNameEnd;
	int rVornameStart=rVornameTag+2;
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_03,pc_str,STR_LAENGE_STRING_TABLE);
	tag=pc_str;
	int rVornameEnd=message.Find(tag,rVornameStart);
	
	//curveR
	int& curveRTag=rVornameEnd;
	int curveRStart=curveRTag+tag.GetLength();
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_04,pc_str,STR_LAENGE_STRING_TABLE);
	tag=pc_str;
	int curveREnd=message.Find(tag,rVornameStart);

	//AES-KeyLength
	int& keyLengthTag=curveREnd;
	int keyLengthStart=keyLengthTag+tag.GetLength();
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_05,pc_str,STR_LAENGE_STRING_TABLE);
	tag=pc_str;
	int keyLengthEnd=message.Find(tag,keyLengthStart);
	int keylength=atoi(message.Mid(keyLengthStart,(keyLengthEnd-keyLengthStart)));

	//ciphertext length
	int& ctLengthTag=keyLengthEnd;
	int ctLengthStart=ctLengthTag+tag.GetLength();
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_06,pc_str,STR_LAENGE_STRING_TABLE);
	tag=pc_str;
	int ctLengthEnd=message.Find(tag,ctLengthStart);
	int ctLength=atoi(message.Mid(ctLengthStart,(ctLengthEnd-ctLengthStart)));

	//AES-Key
	int& keyTag=ctLengthEnd;
	int keyStart=keyTag+tag.GetLength();
	int keyEnd=keyStart+keylength;

	//Ciphertext
	LoadString(AfxGetInstanceHandle(),IDS_ECIES_HEADER_07,pc_str,STR_LAENGE_STRING_TABLE);
	tag=pc_str;
	int ctStart=keyEnd+tag.GetLength();
	

	message=message.Left(ctLengthEnd);
	//sName=message.Mid(sNameStart,(sNameEnd-sNameStart));
	//sVorname=message.Mid(sVornameStart,(sVornameEnd-sVornameStart));
	rName=message.Mid(rNameStart,(rNameEnd-rNameStart));
	rVorname=message.Mid(rVornameStart,(rVornameEnd-rVornameStart));
	curveR=message.Mid(curveRStart,(curveREnd-curveRStart));

	act::Blob key;
	key.insert(key.begin(),&input[keyStart],&input[keyEnd]);

	act::Blob ctext;
	ctext.insert(ctext.begin(),&input[ctStart],&input[input.size()]);

	encryptedSessionKey=key;
	ciphertext=ctext;
	if(/*sNameTag==-1||sVornameTag==-1||*/rNameTag==-1||rVornameTag==-1||curveRTag==-1||keyLengthTag==-1||ctLengthTag==-1||keyTag==-1)
		//corrupt header
		return 1;
	if(keylength!=(int)encryptedSessionKey.size())
		//corrupt encrypted sessionkey
		return 2;
	if(ctLength!=(int)ciphertext.size())
		//corrupt ciphertext
		return 3;
	//file ok
	return 0;
}
void newWindow(const bool &plain, const act::Blob &output, const char* &OldTitle, const CString &ReceiverName, const CString &ReceiverFirstname, const CString &ReceiverKeyType)
{
	char outfile[128], title[128];
    CAppDocument *NewDoc;
	GetTmpName(outfile,"cry",".tmp");
	act::blob2file(outfile,output);
	OpenNewDoc(outfile,ReceiverName+", "+ReceiverFirstname+", "+ReceiverKeyType,OldTitle,IDS_ECIES_CRYPT,plain,0);
}
#endif
