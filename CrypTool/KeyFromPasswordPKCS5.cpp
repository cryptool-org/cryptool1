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


/******************************************************************************************************/
/*                  Schluessel_gen.cpp: Implementierung der Klasse Schluessel_gen.                    */
/*                     Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main                        */
/*                                                                                                    */
/*                         Programmiert von Roger Oyono März 2001                                     */
/*                                                                                                    */
/*                         Deutsche Bank AG Frankfurt - IT Security                                   */
/******************************************************************************************************/

#include "stdafx.h"
#include "stdafx.h"


#include "CrypToolApp.h"
#include "KeyFromPasswordPKCS5.h"
#include "DialogeMessage.h"
//#include "DlgKeyHex.h"	// Dialog-Box für die Schlüsseleingabe

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////////////////////////////////////

CKeyFromPasswordPKCS5::CKeyFromPasswordPKCS5()
{

}

CKeyFromPasswordPKCS5::~CKeyFromPasswordPKCS5()
{

}

/****************************************************************************************************/

int CKeyFromPasswordPKCS5::password_based_key_deriv_funct(CString Passwort, CString Salt, CString dkLen, int AlgId, CString zaehler)
{
	if (atoi(zaehler) < 0)
	{// Der Zahler muß positiv sein
		Message(IDS_STRING_PKCS5_KEYGEN_ITERATIONS_NEGATIVE, MB_ICONEXCLAMATION);
		return -1;
	}
	else if (atoi(dkLen) <=0 )
	{// Byte-Länge darf nicht negativ sein!
		Message(IDS_STRING_PKCS5_KEYGEN_KEYLENGTH_NEGATIVE, MB_ICONEXCLAMATION, (AlgId<2) ? 16 : 20);
		return -1;
	}
	// dkLen <=16 für MD2 u. MD5, dkLen <=20 für SHA-1.
	else if (atoi(dkLen) >16 && AlgId<2)
	{// Byte-Länge ist zu groß (für D2 bzw MD5).
		Message(IDS_STRING_PKCS5_KEYGEN_KEYLENGTH_EXCCEDED, MB_ICONEXCLAMATION, 16, 16);
		return -1;
	}
	else if (atoi(dkLen) >20 && AlgId ==2)
	{// Byte-Länge ist zu groß (für SHA-1)
		Message(IDS_STRING_PKCS5_KEYGEN_KEYLENGTH_EXCCEDED, MB_ICONEXCLAMATION, 20, 20);
		return -1;
	}
	else if (atoi(zaehler) > 100000)
	{
		Message(IDS_STRING_PKCS5_KEYGEN_ITERATIONS_EXCEEDED, MB_ICONEXCLAMATION );
		return -1;
	}
	else
	{	
		hash.noctets=0;

		/* 
		Zuerst sollte man überprüfen: Len(Password) + Len (Salt)<=2^(61)-1 octet für SHA-1,
		bzw. MD2 sowie MD5.
		Ich setze voraus, dass die immer erfüllt wird!!
		*/
		
		
		// CString Passwort nach OctetString Passwort_octetstring.noctets umwandeln
		
			Passwort_octetstring.noctets=(Passwort.GetLength());
			Passwort_octetstring.octets= (char*) malloc ((Passwort_octetstring.noctets+1)*sizeof(char));
			if (Passwort_octetstring.octets==NULL) return -1; // error. keine Speicherallokation
			int k;
			for (k=0; k<(Passwort.GetLength()); k++)
			{
				Passwort_octetstring.octets[k]=Passwort[k];
			}

		// CString Salt nach OctetString Salt_octetstring.noctets umwandeln
			
			Salt_octetstring.noctets=(Salt.GetLength());
			Salt_octetstring.octets= (char*) malloc ((Salt_octetstring.noctets+1)*sizeof(char));
			if (Salt_octetstring.octets==NULL) return -1; // error. keine Speicherallokation
			for (k=0; k<(Salt.GetLength()); k++)
			{
				Salt_octetstring.octets[k]=Salt[k];
			}
			
		//free (Passwort_octetstring.noctets.octets); // dynamischen Speicher freigeben


			help3.octets = (char *) malloc((Passwort_octetstring.noctets + Salt_octetstring.noctets +1) *sizeof(char));
			if (help3.octets == NULL)	return -1;  // error. keine Speicherallokation
			help3.noctets=(Passwort.GetLength() + Salt.GetLength());
			for (k=0; k<Passwort.GetLength(); k++)
			{
				help3.octets[k] = Passwort_octetstring.octets[k]; 
			}
			for (k=Passwort.GetLength(); k<(Passwort.GetLength() + Salt.GetLength()); k++)
			{
				help3.octets[k] = Salt_octetstring.octets[k-Passwort_octetstring.noctets]; 
			}
		

		switch (AlgId){
			case 0://MD2
				theApp.SecudeLib.sec_hash_all(&help3,&hash,theApp.SecudeLib.md2_aid,NULL);
				if (atoi(zaehler)<=1) break;
				for (k=0; k<=atoi(zaehler)-2;k++)
				{
					theApp.SecudeLib.sec_hash_all(&hash,&hash,theApp.SecudeLib.md2_aid,NULL);	
				}
				break;
			case 1://MD5
				theApp.SecudeLib.sec_hash_all(&help3,&hash,theApp.SecudeLib.md5_aid,NULL);
				if (atoi(zaehler)<=1) break;
				for (k=0; k<=atoi(zaehler)-2;k++)
				{
					theApp.SecudeLib.sec_hash_all(&hash,&hash,theApp.SecudeLib.md5_aid,NULL);	
				}
				break;
			case 2://SHA-1
				theApp.SecudeLib.sec_hash_all(&help3,&hash,theApp.SecudeLib.sha1_aid,NULL);
				if (atoi(zaehler)<=1) break;
				for (k=0; k<=atoi(zaehler)-2;k++)
				{
					theApp.SecudeLib.sec_hash_all(&hash,&hash,theApp.SecudeLib.sha1_aid,NULL);	
				}			
				break;
		}

		// Teil-Schluessel des Schluessels ausgeben (PKCS#5)

			help2.octets = (char *) malloc(atoi(dkLen));
			if (help2.octets == NULL) return -1;
			help2.noctets = atoi(dkLen); 
			for (k=0; k<atoi(dkLen); k++)
			{
				help2.octets[k] = hash.octets[k]; // Hashwert beginnen bei hash[0]
			}


		base=16;  // Damit wird das Ergebnis hexadazimal dargestellt. Man kann aber auch andere Darstellungen haben.
		if ( (base == 8) || (base == 10) || (base == 16) )
				{
					// wandele hash (Octetstring) in hashwert (L_NUMBERS)
					
					theApp.SecudeLib.aux_OctetString2LN2(hashwert, &help2); 
					
					// wandele hashwert (L_NUMBERs) nach Zahlen (string) in Basis "base"

					err = ln_to_string (hashwert, &str, base); // Dezimalsystem

					// flomar, 01/02/2009
					// at this point we have a hash value with a leading "0x", but unfortunately leading 
					// zeros of the hash value itself are omitted (i.e. "0x0E" is displayed as "0xE");
					// so we prepend leading zeros to the hash value until the length of the result 
					// equals length of hash value + 2
					int missingZeros = (atoi(dkLen) * 2 + 2) - strlen(str);
					if(missingZeros > 0) {
						// this is ugly, but 1k should be enough
						char tempString[1024];
						memset(tempString, 0, 1024);
						memcpy(tempString + 0, str, 2);
						for(int i=0; i<missingZeros; i++)
							strncat(tempString + 2, "0", 1);
						memcpy(tempString + 2 + missingZeros, str + 2, strlen(str) - 2);
						memset(str, 0, strlen(tempString) + 1);
						memcpy(str, tempString, strlen(tempString));
					}

					if (err)
					{
						// Fehler.
						return -1;
					}
					//free(str);
				}
		}
		return 0;
}

