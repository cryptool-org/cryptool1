/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/


//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <io.h>
#include "CrypToolApp.h"

#include "KeyFileHandling.h"
#include "DlgKeyAsymGeneration.h"

#include "s_ecconv.h"
#include "arithmet.h"
#include "secure.h"
#include "af.h"
#include "FileTools.h"
#include "pkcs.h"
#include "DialogeMessage.h"

#include <time.h>
#include <algorithm>

// Globale Variablen
extern char *Pfad, *PseVerzeichnis; // siehe CrypTool.cpp

CKeyFile::CKeyFile(void)
{  
	// Standardkonstruktor
}

int CKeyFile::DeleteUserKeyFiles(CString user_file, CString& passwd, int filetype = 0)
// filetype == 0 bedeutet: lösche Elliptische Kurven Schlüsseldateien
// filetype == 1 bedeutet: lösche RSA/DSA (verschlüsselte) Schlüsseldatei
{
	// CString FileEntry;
	CString PubDataFile = (CString) PseVerzeichnis + ((CString)"/") + user_file;
	CString PseDataFile =  PubDataFile + ((CString)PSE_FILE_SUFFIX);
	
	PSE PseHandle;
	// OctetString *ostr;
	// OctetString *privKeyOctStr;

	LPTSTR string1 = new TCHAR[PseDataFile.GetLength()+1];
	_tcscpy(string1, PseDataFile);		
	char *psefile_name = string1;

	LPTSTR string2 = new TCHAR[passwd.GetLength()+1];
	_tcscpy(string2, passwd);		
	char *user_pincode = string2;

	// Die Gültigkeit des Passworts passwd ist sichergestellt, wenn man die PSE damit lesen kann
	PseHandle = theApp.SecudeLib.af_open (psefile_name, NULL, user_pincode, NULL); // Auslesen aus psefile_name
	if (PseHandle==NULL)
	{
		if (theApp.SecudeLib.LASTERROR==EPIN)
		{
			// falsche PIN-Nummer benutzt
			delete string1;
			delete string2;
			return -1;
		}
		// sonstige fehler beim öffnen der PSE
		delete string1;
		delete string2;
		return -2;
	}
	// ostr = (OctetString*) af_pse_get(PseHandle, "EcPrivKey", *theApp.SecudeLib.Uid_OID);
	theApp.SecudeLib.af_close (PseHandle);
	
	// privKeyOctStr = d_OctetString(ostr);

	// aux_OctetString2LN2(userCurveParam->privKey, privKeyOctStr); // OctetString in L_NUMBER umwandeln

	// passwd is allright, so the user has permission to delete the File psefile_name

	// check file status

	CFileStatus status;

	CFile::GetStatus( PseDataFile, status );
	if(status.m_attribute == readOnly)
	{
		// file has read only flag		
		// Message(IDS_STRING_XXX,MB_ICONSTOP);
		delete string1;
		delete string2;
		return -3;
	}

	if (filetype == 0)
	{
		CFile::GetStatus( PubDataFile, status );
		if(status.m_attribute == readOnly)
		{
			// file has read only flag
			// Message(IDS_STRING_XXX,MB_ICONSTOP);
			delete string1;
			delete string2;
			return -4;
		}
	}
	CFile::Remove(PseDataFile); // delete PSE File
	if (filetype == 0) CFile::Remove(PubDataFile); // delete Public Data File

	delete string1;
	delete string2;
	return 0;
}

int CKeyFile::CreateEcKeyFiles(CString filename, CString& passwd, EcDomParam_ac_ptr userCurveParam, EcDomParamAcAsString *ecParamString)
{
	// filename ist der zu erzeugende Dateiname ohne Suffix PSE_FILE_SUFFIX
	//Message(IDS_STRING_XXX,MB_ICONINFORMATION, inputfile );

	OctetString *privateKeyOct;
	OctetString *ostr;

	PSE PseHandle;

	CStdioFile PubFile; // File for saving public data

	CString pubfilename_path = (CString) PseVerzeichnis + ((CString)"/") + filename;
	CString privfilename = pubfilename_path + ((CString)PSE_FILE_SUFFIX);
	CString privfilename_path = (CString) PseVerzeichnis + ((CString)"/") + privfilename;

	// Kopieren von CString privfilename nach char *privfile_name
	LPTSTR string1 = new TCHAR[privfilename.GetLength()+1];
	_tcscpy(string1, privfilename);		
	char *privfile_name = string1;

	// save domainparameter and public key (all not encrypted) in the File pubfilename_path
	
	if ( privfilename.GetLength() > _MAX_FNAME)
	{
		// privfilename is to long, choose a shorter filename
		Message(IDS_STRING_MSG_FILENAME_TO_LONG,MB_ICONSTOP, privfilename);
		return -7;
	}
	if (privfilename_path.GetLength() > _MAX_PATH)
	{
		// Maximum length of full path is to long
		Message(IDS_STRING_MSG_PATHNAME_TO_LONG,MB_ICONSTOP, privfilename_path);
		return -8;
	}
 
	if(PubFile.Open(pubfilename_path, CFile::modeCreate | CFile::modeWrite)==FALSE)
	{
		// error the file could not been created
		delete string1;
		return -9;
	}
	else
	{
		// file is succesfully created
		// Keine Überprüfung ob eine Datei gleichen Namens existiert und jetzt eventuell überschrieben wird.	
		PubFile.WriteString(ecParamString->a+((CString)"\n"));
		PubFile.WriteString(ecParamString->b+((CString)"\n"));
		PubFile.WriteString(ecParamString->p+((CString)"\n"));
		PubFile.WriteString(ecParamString->G_xcoord+((CString)"\n"));
		PubFile.WriteString(ecParamString->G_ycoord+((CString)"\n"));
		PubFile.WriteString(ecParamString->k+((CString)"\n"));
		PubFile.WriteString(ecParamString->r+((CString)"\n"));
		PubFile.WriteString(ecParamString->pubKey_xcoord+((CString)"\n"));
		PubFile.WriteString(ecParamString->pubKey_ycoord+((CString)"\n"));
		
		PubFile.Close();
	}

	// save private key (encrypted) in the PSE
	
	// privateKey = aux_LN2OctetString(ecParam->privKey, size);
	// int number_of_bits = lngtouse(ecParam->privKey)+1;
	// int octsnumb = number_of_bits/8+1;

	privateKeyOct = theApp.SecudeLib.aux_LN2OctetString(userCurveParam->privKey, (theApp.SecudeLib.lngtouse(userCurveParam->privKey)+7)/8);

	//L_NUMBER pk1[MAXLGTH];
	//L_NUMBER pk2[MAXLGTH];
	//aux_OctetString2LN2(pk1, privateKeyOct);

	// Anlegen einer PSE für den neuen Benutzer 
	// Erklärung der Parameter
	// priv_file_name: Name der PSE samt absoluter Pfad
	// NULL	         : PSE für Benutzer anlegen
	// user_pincode  : PIN-Nummer
	// NULL          : Software-PSE anlegen
	// TRUE          : Dieser Parameter hat bei Ellipt. Kurven Schlüsseln zur Zeit keine Bedeutung.

	LPTSTR string2 = new TCHAR[passwd.GetLength()+1];
	_tcscpy(string2, passwd);		
	char *user_pincode = string2;

	PseHandle=theApp.SecudeLib.af_create (privfile_name, NULL, user_pincode, NULL, FALSE);
	if (PseHandle==NULL)
	{
		// irgendein fehler beim erzeugen der PSE ist aufgetreten
		delete string1;
		delete string2;
		return -1;
	}
	ostr = theApp.SecudeLib.e_OctetString(privateKeyOct);
	theApp.SecudeLib.af_pse_update(PseHandle, "EcPrivKey", ostr, *theApp.SecudeLib.Uid_OID);
	theApp.SecudeLib.af_close (PseHandle);

	PseHandle = theApp.SecudeLib.af_open (privfile_name, NULL, user_pincode, NULL); // Auslesen aus privfile_name
	if (PseHandle==NULL)
	{
		// irgendein fehler beim öffnen der PSE ist aufgetreten
		delete string1;
		delete string2;
		return -2;
	}
	ostr = (OctetString*) theApp.SecudeLib.af_pse_get(PseHandle, "EcPrivKey", *theApp.SecudeLib.Uid_OID);
	theApp.SecudeLib.af_close (PseHandle);

	// OctetString *testOctet = d_OctetString(ostr);

	// aux_OctetString2LN2(pk2, testOctet);

	delete string1;
	delete string2;

	return 0;
}


int CKeyFile::GetEcPublicParam(CString user_file, EcDomParam_ac_ptr userCurveParam)
{
	int error=0;
	EcDomParamAcAsString userCurveParamStr;
	CString PubDataFile = (CString) PseVerzeichnis + ((CString)"/") + user_file;
	CString PseDataFile = PubDataFile + ((CString)PSE_FILE_SUFFIX);

	if(DataFile.Open(PubDataFile, CFile::modeRead)==FALSE)
	{
		// error: couldn't open inputfile
		return -1; // error: couldn't open inputfile
	}
	else
	{
		DataFile.ReadString(userCurveParamStr.a);
		DataFile.ReadString(userCurveParamStr.b);
		DataFile.ReadString(userCurveParamStr.p);
		DataFile.ReadString(userCurveParamStr.G_xcoord);
		DataFile.ReadString(userCurveParamStr.G_ycoord);
		DataFile.ReadString(userCurveParamStr.k);
		DataFile.ReadString(userCurveParamStr.r);
		DataFile.ReadString(userCurveParamStr.pubKey_xcoord);
		DataFile.ReadString(userCurveParamStr.pubKey_ycoord);
		
		DataFile.Close();

		/*
		LPTSTR string1 = new TCHAR[privfilename.GetLength()+1];
		_tcscpy(string1, privfilename);		
		char *privfile_name = string1;
		*/

		LPTSTR temp = new TCHAR[userCurveParamStr.a.GetLength()+1];
		_tcscpy(temp, userCurveParamStr.a);
		char *str_a = temp;
		error += string_to_ln(str_a, userCurveParam->E->a);
		delete str_a;

		LPTSTR temp2 =  new TCHAR[userCurveParamStr.b.GetLength()+1];
		_tcscpy(temp2, userCurveParamStr.b);
		char *str_b = temp2;
		error += string_to_ln(str_b, userCurveParam->E->b);
		delete str_b;
	
		LPTSTR temp3 = new TCHAR[userCurveParamStr.p.GetLength()+1];
		_tcscpy(temp3, userCurveParamStr.p);
		char *str_p = temp3; 
		error += string_to_ln(str_p, userCurveParam->E->p);
		delete str_p;

		LPTSTR temp4 = new TCHAR[userCurveParamStr.G_xcoord.GetLength()+1];
		_tcscpy(temp4, userCurveParamStr.G_xcoord);
		char *str_Gx = temp4;
		error += string_to_ln(str_Gx, userCurveParam->G->x);
		delete str_Gx;

		LPTSTR temp5 = new TCHAR[userCurveParamStr.G_ycoord.GetLength()+1];
		_tcscpy(temp5, userCurveParamStr.G_ycoord);
		char *str_Gy = temp5;
		error += string_to_ln(str_Gy, userCurveParam->G->y);
		delete str_Gy;

		userCurveParam->G->infinity=0;

		LPTSTR temp6 = new TCHAR[userCurveParamStr.k.GetLength()+1];
		_tcscpy(temp6, userCurveParamStr.k);
		char *str_k = temp6; 
		error += string_to_ln(str_k, userCurveParam->k);
		delete str_k;
	
		LPTSTR temp7 = new TCHAR[userCurveParamStr.r.GetLength()+1];
		_tcscpy(temp7, userCurveParamStr.r);
		char *str_r = temp7;
		error += string_to_ln(str_r, userCurveParam->r);
		delete str_r;

		LPTSTR temp8 = new TCHAR[userCurveParamStr.pubKey_xcoord.GetLength()+1];
		_tcscpy(temp8, userCurveParamStr.pubKey_xcoord);
		char *str_Pubx = temp8;
		error += string_to_ln(str_Pubx, userCurveParam->pubKey->x);
		delete str_Pubx;

		LPTSTR temp9 = new TCHAR[userCurveParamStr.pubKey_ycoord.GetLength()+1];
		_tcscpy(temp9, userCurveParamStr.pubKey_ycoord);
		char *str_Puby = temp9;
		error += string_to_ln(str_Puby, userCurveParam->pubKey->y);
		delete str_Puby;

		userCurveParam->pubKey->infinity=0;
	}
	return error;
}

int CKeyFile::GetEcAllParam(CString user_file, CString& passwd, EcDomParam_ac_ptr userCurveParam)
{
	int error=0;
	EcDomParamAcAsString userCurveParamStr;

	CString PubDataFile = (CString) PseVerzeichnis + ((CString)"/") + user_file;
	CString PseDataFile =  PubDataFile + ((CString)PSE_FILE_SUFFIX);

	// Get Secret Key from PSE
	PSE PseHandle;
	OctetString *ostr;
	OctetString *privKeyOctStr;

	LPTSTR string1 = new TCHAR[PseDataFile.GetLength()+1];
	_tcscpy(string1, PseDataFile);		
	char *psefile_name = string1;

	LPTSTR string2 = new TCHAR[passwd.GetLength()+1];
	_tcscpy(string2, passwd);		
	char *user_pincode = string2;

	PseHandle = theApp.SecudeLib.af_open (psefile_name, NULL, user_pincode, NULL); // Auslesen aus psefile_name
	if (PseHandle==NULL)
	{
		if (theApp.SecudeLib.LASTERROR==EPIN)
		{
			// Fehler: falsche PIN
			// Freigeben von dynamisch angelegtem Speicher
			delete string1;
			delete string2;
			return -1;
		}
		// Sonstige Fehler beim öffnene der PSE
		// Freigeben von dynamisch angelegtem Speicher
		delete string1;
		delete string2;
		return -2;
	}
	ostr = (OctetString*) theApp.SecudeLib.af_pse_get(PseHandle, "EcPrivKey", *theApp.SecudeLib.Uid_OID);
	theApp.SecudeLib.af_close (PseHandle);
	
	privKeyOctStr = theApp.SecudeLib.d_OctetString(ostr);

	theApp.SecudeLib.aux_OctetString2LN2(userCurveParam->privKey, privKeyOctStr); // OctetString in L_NUMBER umwandeln

	if(DataFile.Open(PubDataFile, CFile::modeRead)==FALSE)
	{
		// error: couldn't open inputfile

		LPTSTR string3 = new TCHAR[PubDataFile.GetLength()+1];
		_tcscpy(string3, PubDataFile);		
		char *toc_file = string3;

		Message(IDS_STRING_EC_ERROR_LOADING_KEYFILE,MB_ICONINFORMATION, toc_file);
		delete string1;
		delete string2;
		delete string3;
		return -3; // error: couldn't open inputfile
	}
	else
	{
		DataFile.ReadString(userCurveParamStr.a);
		DataFile.ReadString(userCurveParamStr.b);
		DataFile.ReadString(userCurveParamStr.p);
		DataFile.ReadString(userCurveParamStr.G_xcoord);
		DataFile.ReadString(userCurveParamStr.G_ycoord);
		DataFile.ReadString(userCurveParamStr.k);
		DataFile.ReadString(userCurveParamStr.r);
		DataFile.ReadString(userCurveParamStr.pubKey_xcoord);
		DataFile.ReadString(userCurveParamStr.pubKey_ycoord);
		
		DataFile.Close();

		/*
		LPTSTR string1 = new TCHAR[privfilename.GetLength()+1];
		_tcscpy(string1, privfilename);		
		char *privfile_name = string1;
		*/

		LPTSTR temp = new TCHAR[userCurveParamStr.a.GetLength()+1];
		_tcscpy(temp, userCurveParamStr.a);
		char *str_a = temp;
		error += string_to_ln(str_a, userCurveParam->E->a);
		delete str_a;

		LPTSTR temp2 =  new TCHAR[userCurveParamStr.b.GetLength()+1];
		_tcscpy(temp2, userCurveParamStr.b);
		char *str_b = temp2;
		error += string_to_ln(str_b, userCurveParam->E->b);
		delete str_b;
	
		LPTSTR temp3 = new TCHAR[userCurveParamStr.p.GetLength()+1];
		_tcscpy(temp3, userCurveParamStr.p);
		char *str_p = temp3; 
		error += string_to_ln(str_p, userCurveParam->E->p);
		delete str_p;

		LPTSTR temp4 = new TCHAR[userCurveParamStr.G_xcoord.GetLength()+1];
		_tcscpy(temp4, userCurveParamStr.G_xcoord);
		char *str_Gx = temp4;
		error += string_to_ln(str_Gx, userCurveParam->G->x);
		delete str_Gx;

		LPTSTR temp5 = new TCHAR[userCurveParamStr.G_ycoord.GetLength()+1];
		_tcscpy(temp5, userCurveParamStr.G_ycoord);
		char *str_Gy = temp5;
		error += string_to_ln(str_Gy, userCurveParam->G->y);
		delete str_Gy;

		userCurveParam->G->infinity=0;

		LPTSTR temp6 = new TCHAR[userCurveParamStr.k.GetLength()+1];
		_tcscpy(temp6, userCurveParamStr.k);
		char *str_k = temp6; 
		error += string_to_ln(str_k, userCurveParam->k);
		delete str_k;
	
		LPTSTR temp7 = new TCHAR[userCurveParamStr.r.GetLength()+1];
		_tcscpy(temp7, userCurveParamStr.r);
		char *str_r = temp7;
		error += string_to_ln(str_r, userCurveParam->r);
		delete str_r;

		LPTSTR temp8 = new TCHAR[userCurveParamStr.pubKey_xcoord.GetLength()+1];
		_tcscpy(temp8, userCurveParamStr.pubKey_xcoord);
		char *str_Pubx = temp8;
		error += string_to_ln(str_Pubx, userCurveParam->pubKey->x);
		delete str_Pubx;

		LPTSTR temp9 = new TCHAR[userCurveParamStr.pubKey_ycoord.GetLength()+1];
		_tcscpy(temp9, userCurveParamStr.pubKey_ycoord);
		char *str_Puby = temp9;
		error += string_to_ln(str_Puby, userCurveParam->pubKey->y);
		delete str_Puby;

		userCurveParam->pubKey->infinity=0;
	}
	delete string1;
	delete string2;
	return error;
}

int CKeyFile::GetEcPrivateKey(CString user_file, CString& passwd, L_NUMBER * privKey)
{
	CString PseDataFile = (CString)PseVerzeichnis + ((CString)"/") + user_file + ((CString)PSE_FILE_SUFFIX);

	// Get Secret Key from PSE
	PSE PseHandle;
	OctetString *ostr;
	OctetString *privKeyOctStr;

	LPTSTR string1 = new TCHAR[PseDataFile.GetLength()+1];
	_tcscpy(string1, PseDataFile);		
	char *psefile_name = string1;

	LPTSTR string2 = new TCHAR[passwd.GetLength()+1];
	_tcscpy(string2, passwd);		
	char *user_pincode = string2;

	PseHandle = theApp.SecudeLib.af_open (psefile_name, NULL, user_pincode, NULL); // Auslesen aus psefile_name
	if (PseHandle==NULL)
	{
		if (theApp.SecudeLib.LASTERROR==EPIN)
		{
			// falsche PIN-Nummer benutzt
			/*
			Message(IDS_STRING_PRIVKEY_WRONG_PIN, MB_ICONEXCLAMATION);
			*/
			// Freigeben von dynamisch angelegtem Speicher
			delete string1;
			delete string2;
			return -1;
		}
		// sonstiger Fehler beim öffnender PSE
		/*
		Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE, ,MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
		*/
		delete string1;
		delete string2;
		return -2;
	}
	ostr = (OctetString*) theApp.SecudeLib.af_pse_get(PseHandle, "EcPrivKey", *theApp.SecudeLib.Uid_OID);
	theApp.SecudeLib.af_close (PseHandle);
	
	privKeyOctStr = theApp.SecudeLib.d_OctetString(ostr);

	theApp.SecudeLib.aux_OctetString2LN2(privKey, privKeyOctStr); // OctetString in L_NUMBER umwandeln

	delete string1;
	delete string2;
	return 0;
}

CString CKeyFile::CreateFilename
	(CString Name, CString Firstname, CString AlgType, CString KeySize, CString CreatTime, CString KeyInfo)
{
	CString UserKeyId;
	if (KeyInfo.GetLength() > 0) UserKeyId = ((CString)"[") + KeyInfo + ((CString)"]");
	else UserKeyId=""; // leerer String

	UserKeyId = ((CString)"[") + Name + ((CString)"][") + Firstname + ((CString)"][") + AlgType + ((CString)"-") + KeySize + ((CString)"][") + CreatTime + ((CString)"]")+ UserKeyId;

	return UserKeyId;
}

CString CKeyFile::CreateFilename2
	(CString Name, CString Firstname, CString AlgTypeWithKeySize, CString CreatTime, CString KeyInfo)
{
	CString UserKeyId;
	if (KeyInfo.GetLength() > 0) UserKeyId = ((CString)"[") + KeyInfo + ((CString)"]");
	else UserKeyId=""; // leerer String

	UserKeyId = ((CString)"[") + Name + ((CString)"][") + Firstname + ((CString)"][") + AlgTypeWithKeySize + ((CString)"][") + CreatTime + ((CString)"]")+ UserKeyId;

	return UserKeyId;
}


CString CKeyFile::CreateDistName(CString Name, CString Firstname, CString CreatTime)
{
	return (CString)"CN="+Firstname + ((CString)" ") + Name + ((CString)" [") + CreatTime + ((CString)"], ") + CString(DN_SUFFIX);
}


bool CKeyFile::FilenameExisting(CString user_file)
{
	// ermittele die zur Verfügung stehenden Schlüssel(-bezeichner)
	
	long filehandle;
	int pos;
	struct _finddata_t fileinfo;
	
	// ermittele die Dateien, die in PseVerzeichnis liegen

	CString filename = (CString) PseVerzeichnis + ((CString)"/*.*");
	CString key_identifier;
		
	LPTSTR help1 = new TCHAR[filename.GetLength()+1];
	_tcscpy(help1, filename);
	char *filename2=help1;

	filehandle = _findfirst(filename2, &fileinfo);
	if (filehandle != -1)
	{
		// es gibt mindestens eine Datei im Verzeichnis PseVerzeichnis
		key_identifier = (CString) fileinfo.name;
		pos=key_identifier.Find(user_file);
		if (pos != -1)
		{
			delete help1;
			return true; // es gibt bereits eine Datei mit dem Namen user_file 
		}
		while(_findnext(filehandle, &fileinfo) == 0)
		{
			// es gibt mindestens noch eine weitere Datei im Verzeichnis PseVerzeichnis
			key_identifier = (CString) fileinfo.name;
			pos=key_identifier.Find(user_file);
			if (pos != -1)
			{
				delete help1;
				return true; // es gibt bereits eine Datei mit dem Namen user_file
			}
		}
		_findclose(filehandle);
	}
	delete help1;
	return false;
}

int CKeyFile::ExtractData(CString filename, char **ctstr, char **creatime, char **name, char **firstname, char **keyType, char **keyID)
{
	// ExtractData() ermittelt aus dem String filenname die folgenden Daten:
	// ctstr: Time in seconds since UTC 1/1/70 (Zeitpunkt der Schlüsselerzeugung),
	// creatime: ctstr in menschlich lesbare Form und lokal angepasst,
	// den Namen, Vornamen, Schlüsseltype und die Schlüsselkennung (KeyInfo)
	// "filename" muss ein Dateiname (als CString) sein, der in der Form von "UserKeyId" in
	// CDlgKeyAsymGeneration::CCreateAsymKeys() erzeugt wurde,
	// also MUSS filename den folgenden Muster entsprechen, sonst wird nichts extrahiert:

	// [Name][Vorname][schlüsseltyp][ctstr][schlüsselkennung].pse

	// (ctstr ist vom Typ time_t in einen String umgewandelt)

	// für char *ctstr, char *creatime, char *name, char *firstname, char *keyType und eventuell für char *keyID
	// wird in dieser Funktion Speicher
	// alloziert, diser muss später (auserhalb dieser Funktion) wieder freigegeben werden!
	
	*name=NULL;
	*firstname=NULL;
	*keyType=NULL;
	*keyID=NULL;
	*creatime=NULL;
	*ctstr=NULL;

	CString Name;
	CString Firstname;
	CString KeyType;
	CString CreatTime;
	CString KeyInfo;
	char *undersc="_";
	int pos1;
	int pos2;

	// Ermittele den Namen
	pos1 = filename.Find("[");
	pos2 = filename.Find("]");
	if ( (pos1 == -1) || (pos2 == -1) )
	{
		// filename einen falschen Aufbau!
		return -1;
	}
	Name = filename.Mid(pos1+1, pos2-(pos1+1));
	Name.TrimLeft();
	Name.TrimRight();	
	LPTSTR string1 = new TCHAR[Name.GetLength()+1];
	_tcscpy(string1, Name);
	*name = string1;

	// mache aus dem "[" bei pos1 und dem "]" bei pos2 jeweils ein "_"
	filename.SetAt(pos1, undersc[0]);
	filename.SetAt(pos2, undersc[0]);

	// Ermittele den Nachnamen
	pos1 = filename.Find("[");
	pos2 = filename.Find("]");
	if ( (pos1 == -1) || (pos2 == -1) )
	{
		// filename einen falschen Aufbau!
		delete string1;
		*name = NULL;
		return -2;
	}
	Firstname = filename.Mid(pos1+1, pos2-(pos1+1));
	Firstname.TrimLeft();
	Firstname.TrimRight();	
	LPTSTR string2 = new TCHAR[Firstname.GetLength()+1];
	_tcscpy(string2, Firstname);
	*firstname = string2;

	// mache aus dem "[" bei pos1 und dem "]" bei pos2 jeweils ein "_"
	filename.SetAt(pos1, undersc[0]);
	filename.SetAt(pos2, undersc[0]);

	// Ermittele den Schlüsseltyp
	pos1 = filename.Find("[");
	pos2 = filename.Find("]");
	if ( (pos1 == -1) || (pos2 == -1) )
	{
		// filename einen falschen Aufbau!
		delete string1;
		*name = NULL;
		delete string2;
		*firstname = NULL;
		return -3;
	}
	KeyType = filename.Mid(pos1+1, pos2-(pos1+1));
	KeyType.TrimLeft();
	KeyType.TrimRight();	
	LPTSTR string3 = new TCHAR[KeyType.GetLength()+1];
	_tcscpy(string3, KeyType);
	*keyType = string3;

	// mache aus dem "[" bei pos1 und dem "]" bei pos2 jeweils ein "_"
	filename.SetAt(pos1, undersc[0]);
	filename.SetAt(pos2, undersc[0]);

	// Schreibe time_t time_of_creation in die Variable tcreat;
	pos1 = filename.Find("[");
	pos2 = filename.Find("]");
	if ( (pos1 == -1) || (pos2 == -1) )
	{
		// filename einen falschen Aufbau!
		delete string1;
		*name = NULL;
		delete string2;
		*firstname = NULL;
		delete string3;
		*keyType = NULL;
		return -4;
	}
	CreatTime = filename.Mid(pos1+1, pos2-(pos1+1));
	CreatTime.TrimLeft();
	CreatTime.TrimRight();
	LPTSTR string4 = new TCHAR[CreatTime.GetLength()+1];
	_tcscpy(string4, CreatTime);
	*ctstr = string4; // ctstr: Time in seconds since UTC 1/1/70
	time_t elapstime = atol( *ctstr ); // Zeitpunkt der Erstellung als time_t Typ
	struct tm *timeofcreat;
	timeofcreat = localtime( &elapstime );
	char sec[3];
	_itoa(timeofcreat->tm_sec, sec, 10);
	CString Sec = (CString) sec;
	if (Sec.GetLength() < 2) Sec = ((CString)"0") + Sec; // 0,1,2, .., 9 sek --> 00,01,02, .., 09 sek
	char min[3];
	_itoa(timeofcreat->tm_min, min, 10);
	CString Min = (CString) min;
	if (Min.GetLength() < 2) Min = ((CString)"0") + Min; // 0,1,2, .., 9 min --> 00,01,02, .., 09 min
	char hour[3];
	_itoa(timeofcreat->tm_hour, hour, 10);
	CString Hour = (CString) hour;
	if (Hour.GetLength() < 2) Hour = ((CString)"0") + Hour; // 0,1,2, .., 9 std --> 00,01,02, .., 09 std
	char mday[3];
	_itoa(timeofcreat->tm_mday, mday, 10);
	CString Mday = (CString) mday;
	if (Mday.GetLength() < 2) Mday = ((CString)"0") + Mday; // 1,2, .., 9  --> 01,02, .., 09 
	char month[3];
	_itoa(timeofcreat->tm_mon+1, month, 10);
	CString Month = (CString) month;
	if (Month.GetLength() < 2) Month = ((CString)"0") + Month; // 1,2, .., 9  --> 01,02, .., 09 
	char year[5];
	_itoa(timeofcreat->tm_year+1900, year, 10);

	CreatTime = Mday + ((CString)".") + Month + ((CString)".") + (CString) year + ((CString)" ") + Hour + ((CString)":") + Min + ((CString)":") + Sec; 
	LPTSTR string5 = new TCHAR[CreatTime.GetLength()+1];
	_tcscpy(string5, CreatTime);
	*creatime = string5;

	// mache aus dem "[" bei pos1 und dem "]" bei pos2 jeweils ein "_"
	filename.SetAt(pos1, undersc[0]);
	filename.SetAt(pos2, undersc[0]);

	pos1 = filename.Find("["); // suche nach "["
	if (pos1 == -1)
	{
		// bei der Schlüsselerzeugung wurde keine Schlüsselkennung angegeben
		*keyID = NULL;
	}
	else
	{
		pos2 = filename.Find("]"); // zwischen dem ersten "[" und dem erstem "]" liegt die Schlüsselkennung
		// "]" muss im String filename vorkommen, falls "[" vorkommt, sonst hat filename falschen Aufbau
		if (pos2 == -1) *keyID = NULL; // irgendwas stimmt nicht mit dem Aufbau von filename
		KeyInfo = filename.Mid(pos1+1, pos2-(pos1+1));
		KeyInfo.TrimLeft();
		KeyInfo.TrimRight();	
		LPTSTR string6 = new TCHAR[KeyInfo.GetLength()+1];
		_tcscpy(string6, KeyInfo);
		*keyID = string6;
	}
	return 0;
}


CAsymmKeyAttrib::CAsymmKeyAttrib(int sortflag)
{
	// Konstruktor

	// durch den int Parameter 'sortflag' wird festgelegt nach welchen Kriterien die Liste sortiert wird:
	// BY_NAME
	// BY_FIRSTNAME
	// BY_KEYTYPE
	// BY_CREATTIME
	// BY_PERS_KEYID
	sortby = sortflag;
}


CAvailabAsymmKeys::CAvailabAsymmKeys(void)
{
	// Konstruktor
}


int CAvailabAsymmKeys::GetKeyList(CSortAsymKeyList& sortedAsymKeyList, unsigned nKeyType, int sortflag)
{
	// Erstellt eine sortierte Liste sortedAsymKeyList

	// durch den int Parameter 'sortflag' wird festgelegt nach welchen Kriterien die Liste sortiert wird:
	// BY_NAME
	// BY_FIRSTNAME
	// BY_KEYTYPE
	// BY_CREATTIME
	// BY_PERS_KEYID

	// nKeyType gibt an, welche Schlüsselbezeichner in die Liste aufgenommen werden:
	// nKeyType == ASYM_KEY : alle (EC, RSA, DSA)
	// nKeyType == EC_KEY  : nur EC
	// nKeyType == RSA_KEY : nur RSA
	// nKeyType == DSA_KEY : nur DSA
	// nKeyType == RSA_KEY | EC_KEY  : RSA und EC
	// usw.

	CAsymmKeyAttrib userfile(sortflag);

	sortedAsymKeyList.RemoveAll(); // Liste neu anlegen
	if ( (nKeyType == 0) || (nKeyType > 7) )
	{
		// nKeyType hat ungültige Werte
		return -1; // sortedAsymKeyList ist eine leere Liste
	}

	// ermittele die zur Verfügung stehenden Schlüssel(-bezeichner)

	long filehandle;
	int pos;
	int ret;
	struct _finddata_t fileinfo;
	CKeyFile KeyfileName;
	char *ctstr = NULL;
	char *creatime = NULL;
	char *name = NULL;
	char *firstname = NULL;
	char *keyType = NULL;
	char *keyID = NULL;

	CString key_identifier;
	
	// ermittele die Dateien, die in PseVerzeichnis liegen

	CString filename=(CString)PseVerzeichnis+((CString)"/*.*");		
	LPTSTR help1 = new TCHAR[filename.GetLength()+1];
	_tcscpy(help1, filename);
	char *filename2=help1;

	filehandle = _findfirst(filename2, &fileinfo);
	if (filehandle != -1)
	{
		// es gibt mindestens eine Datei im Verzeichnis PseVerzeichnis

		userfile.UserKeyfileName = (CString) fileinfo.name;
		key_identifier = (CString) fileinfo.name;

		pos = key_identifier.Find(PSE_FILE_SUFFIX);
		if (pos != -1)
		{
			// key_identifier sind von der Form "xxxx.PSE_FILE_SUFFIX"
			key_identifier = key_identifier.Left(pos); // entferne PSE_FILE_SUFFIX

			ret = KeyfileName.ExtractData(key_identifier, &ctstr, &creatime, &name, &firstname, &keyType, &keyID);// Speicherfreigabe!
			// Zuweisen der Werte
			userfile.UTCstring = (CString) ctstr; // Time in seconds since UTC 1/1/70
			userfile.CreatTime = (CString) creatime; // Date and time of creation
			userfile.Name = (CString) name; // Name of owner
			userfile.Firstname = (CString) firstname; // Firstname of owner
			userfile.KeyType = (CString) keyType; // Key Type {EC-xxx, RSA-xxx, DSA-xxx}
			userfile.PersKeyInfo = (CString) keyID; // Prrsönliche Schlüsselkennung des Schlüsselerzeugers
			
			// Für Definitionen EC_KEYFILE_IDSTRING, RSA_KEYFILE_IDSTRING, DSA_KEYFILE_IDSTRING siehe DlgAsymKeyCreat.h
			if (nKeyType == ASYM_KEY)
			{
				// alle verfügbaren Schlüssel einfügen

				sortedAsymKeyList.AddTail(userfile); // Objekt in Liste einfügen
			}
			else
			{
				// Kombination von verschiedenen Schlüsseltypen möglich

				if ((nKeyType & EC_KEY) == EC_KEY)
				{
					if (userfile.KeyType.Find(EC_KEYFILE_IDSTRING) > -1)
						sortedAsymKeyList.AddTail(userfile); // Objekt in Liste einfügen
				}
				if ((nKeyType & RSA_KEY) == RSA_KEY)
				{
					if (userfile.KeyType.Find(RSA_KEYFILE_IDSTRING) > -1)
						sortedAsymKeyList.AddTail(userfile); // Objekt in Liste einfügen
				}
				if ((nKeyType & DSA_KEY) == DSA_KEY)
				{
					if (userfile.KeyType.Find(DSA_KEYFILE_IDSTRING) > -1)
						sortedAsymKeyList.AddTail(userfile); // Objekt in Liste einfügen
				}
			}

			if (ctstr != NULL){ delete ctstr; ctstr = NULL; }
			if (creatime != NULL){ delete creatime;creatime = NULL; }
			if (name != NULL){ delete name;name = NULL; }
			if (firstname != NULL){ delete firstname;firstname = NULL; }
			if (keyType != NULL){ delete keyType;keyType = NULL; }
			if (keyID != NULL){ delete keyID;keyID = NULL; }
		}
		while(_findnext(filehandle, &fileinfo) == 0)
		{
			// es gibt mindestens noch eine weitere Datei im Verzeichnis PseVerzeichnis

			userfile.UserKeyfileName = (CString) fileinfo.name;
			key_identifier = (CString) fileinfo.name;

			pos = key_identifier.Find(PSE_FILE_SUFFIX);
			if (pos != -1)
			{
				// key_identifier sind von der Form "xxxx.PSE_FILE_SUFFIX"
				key_identifier = key_identifier.Left(pos); // entferne PSE_FILE_SUFFIX

				ret = KeyfileName.ExtractData(key_identifier, &ctstr, &creatime, &name, &firstname, &keyType, &keyID);// Speicherfreigabe!
				// Zuweisen der Werte
				userfile.UTCstring = (CString) ctstr; // Time in seconds since UTC 1/1/70
				userfile.CreatTime = (CString) creatime; // Date and time of creation
				userfile.Name = (CString) name; // Name of owner
				userfile.Firstname = (CString) firstname; // Firstname of owner
				userfile.KeyType = (CString) keyType; // Key Type {EC-xxx, RSA-xxx, DSA-xxx}
				userfile.PersKeyInfo = (CString) keyID; // Prrsönliche Schlüsselkennung des Schlüsselerzeugers

				// Für Definitionen EC_KEYFILE_IDSTRING, RSA_KEYFILE_IDSTRING, DSA_KEYFILE_IDSTRING siehe DlgAsymKeyCreat.h
				if (nKeyType == ASYM_KEY)
				{
					// alle verfügbaren Schlüssel einfügen

					sortedAsymKeyList.AddTail(userfile); // Objekt in Liste einfügen
				}
				else
				{
					// Kombination von verschiedenen Schlüsseltypen möglich

					if ((nKeyType & EC_KEY) == EC_KEY)
					{
						if (userfile.KeyType.Find(EC_KEYFILE_IDSTRING) > -1)
							sortedAsymKeyList.AddTail(userfile); // Objekt in Liste einfügen
					}
					if ((nKeyType & RSA_KEY) == RSA_KEY)
					{
						if (userfile.KeyType.Find(RSA_KEYFILE_IDSTRING) > -1)
							sortedAsymKeyList.AddTail(userfile); // Objekt in Liste einfügen
					}
					if ((nKeyType & DSA_KEY) == DSA_KEY)
					{
						if (userfile.KeyType.Find(DSA_KEYFILE_IDSTRING) > -1)
							sortedAsymKeyList.AddTail(userfile); // Objekt in Liste einfügen
					}
				}
				if (ctstr != NULL){ delete ctstr; ctstr = NULL; }
				if (creatime != NULL){ delete creatime;creatime = NULL; }
				if (name != NULL){ delete name;name = NULL; }
				if (firstname != NULL){ delete firstname;firstname = NULL; }
				if (keyType != NULL){ delete keyType;keyType = NULL; }
				if (keyID != NULL){ delete keyID;keyID = NULL; }
			}
		}
		_findclose(filehandle);
	}
	return 0;
}

//extern 	CAsymmKeyAttrib CAsymmKeyAttrib::operator<(const CSortAsymKeyList& op2) const;  // Überladen des < Operators


/*
bool CAsymmKeyAttrib::operator<(const CAsymmKeyAttrib& op2) // Überladen des < Operators
{	
	return (UTCstring < op2.UTCstring);
}
*/

int CAvailabAsymmKeys::SortList(CSortAsymKeyList& sortedAsymKeyList, int sortby)
{
	// Umsortieren der Liste sortedAsymKeyList

	// CAsymmKeyAttrib dummy(sortby);


	// template void sort( CAsymmKeyAttrib, CAsymmKeyAttrib );

	//template
	//std::stable_sort( sortedAsymKeyList.GetHeadPosition(), sortedAsymKeyList.GetTailPosition() );

	return 0;
}
