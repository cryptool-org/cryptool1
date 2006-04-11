/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/error.h
 *###
 *### global functions:
 *###
 *###*****************************************//* This file contains the new (af2) error codes. If you want to add an error or other text,
this is the only file you have to change.  */

/************************************************************/
/* texts                                                   */
/************************************************************/
/* token IF texts 1 - 99*/
Macro4(T2TKE_URL_FINISHED,1,"URL komplett","URL complete")
Macro4(T2TKE_URL_P11_DRIVER,2,"PKCS #11 Treiber","PKCS #11 driver")
Macro4(T2TKE_URL_SCT_DRIVER,3,"SECUDE-Treiber für SmartCard Leser","SECUDE driver for SmartCard reader")
Macro4(T2TKE_URL_SLOT,4,"Anschluß","Slot")
Macro4(T2TKE_URL_SW_TOKEN_NAME,5,"Tokenname für Dateibasiertes Token","Soft token name")
Macro4(T2TKE_URL_FILE_WITH_PATH,6,"Dateiname des Tokens mit Pfad","File name and path of soft token")
Macro4(T2TKE_URL_NEW_FILE_WITH_PATH,7,"Dateiname des neuen Tokens mit Pfad","File name and path of new soft token")



/* special token texts 100 - 199*/
/*tcos texts 100-119 */
Macro4(T2TCOSTTIKS12,100,"TIKS (TCOS 1.2)","TIKS (TCOS 1.2)")
Macro4(T2TCOSTPKS,101,"PKS","PKS")
Macro4(T2TCOSTNETKEY,102,"NetKey","NeyKey")
Macro4(T2TCOSTNETKEYE4,103,"NetKeyE4","NetKeyE4")
Macro4(T2TCOSTTIKS,104,"TIKS","TIKS")
Macro4(T2TCOSTPOST,105,"SignTrust","SignTrust")
Macro4(T2TCOSTSECUDE,106,"TCOS 2.0 min","TCOS 2.0 min")

/* sw token texts 120 -139 */
 Macro4(T2SWNEWTOKEN,120,"Neues Token","new token")
 Macro4(T2SWEXISTFILE,121, "Token in anderem Ordener", "token in another directory")

/* PKCS#11 token texts 140-159*/
Macro4(T2SOPIN, 140, "Administrator-PIN", "Security Officer PIN")
Macro4(T2CARDPIN, 141, "Karten-PIN", "Card PIN")
 
/************************************************************/
/* errors                                                   */
/************************************************************/

/* system errors 1 - 19*/
Macro4(E2MALLOC,-1,"Nicht genügend Speicher","Not enough memory")
Macro4(E2SECNOTINIT,-2,"SECUDE nicht initialisiert","SECUDE not initialized")
Macro4(E2NOTSUPPORTED,-3,"Funktion wird nicht unterstützt","Function not supported")

/* attribute errors 20 - 39*/
Macro4(E2ATTRNOTSUPPORTED,-20,"Attribut wird nicht unterstützt","Attribute not supported")
Macro4(E2ATTRNOTAVAIL,-21,"Attribut nicht verfügbar","Attribute not available")

/* file errors 40 - 49*/
Macro4(E2FILENOTFOUND,-40,"Datei nicht gefunden","File not found")

/* programming errors 50 - 69*/
Macro4(E2INVALIDPARM,-50,"Funktionsparameter ungültig","Function parameter invalid")

/* encoding errors 70 - 79*/
Macro4(E2ENCODE,-70,"Structur nicht kodierbar","Structure not encodable")
Macro4(E2DECODE,-71,"Daten nicht dekodierbar","Data not decodable")

/* SmartCard errors 100 - 199*/
Macro4(E2SCWRONGCARDSYSTEM,-100,"Die SmartCard scheint ein falsches Betriebssystem zu haben","Seems to be the wrong SmartCard operationg system")
Macro4(E2SCUNKNOWNSCERR,-101,"Unbekannter SmartCard Fehler","Unknown SmartCard error")
Macro4(E2SCWRONGRETLEN,-102,"SmartCard Fehler: Antwortlänge falsch","SmartCard error: responce length wrong")
Macro4(E2SCACCESSDENIED,-103,"SmartCard Fehler: Zugriff verweigert","SmartCard error: access denied")
Macro4(E2SCWRONGCARDPROFILE,-104,"Das Profil der SmartCard wird nicht unterstützt","SmartCard profile not supported")


/* SmartCard reader errors 200 - 299*/
Macro4(E2SCTNOSCTDRIVER,-200,"SECUDE-Treiber für SmartCard Leser nicht gefunden","SECUDE driver for SmartCard reader not found")
Macro4(E2SCTCANNOTOPENSCT,-201,"SmartCard-Leser kann nicht angesprochen werden","Cannot access SmartCard reader")
Macro4(E2SCTUNKNOWNSCTERR,-202,"Unbekannter SmartCard-Leser Fehler","Unknown SmartCard reader error")
Macro4(E2SCTUSERBREAK,-203,"Abbruch durch Benutzer am SmartCard Leser","User break on SmartCard reader")
Macro4(E2SCTTIMEOUT,-204,"Wartezeit am SmartCard Leser abgelaufen","Time out on SmartCard reader")

/* TokenIF errors 300 - 399*/
Macro4(E2TOKBADURL,-300,"Token URL ist falsch","Token URL wrong")
Macro4(E2TOKNOTOKENDRIVER,-301,"SECUDE-Treiber für Token nicht gefunden","SECUDE driver for token not found")
Macro4(E2TOKCANNOTOPENTOKEN,-302,"Token kann nicht angesprochen werden","Cannot access token")
Macro4(E2TOKTOKENCHANGED,-303,"Token gewechselt","Token was changed")
Macro4(E2TOKNEEDTOKENTOUSETHREADS,-305,"Die Karte muß eingelegt sein, um mit weiteren Threads zuzugreifen","SmartCard must be inserted for access with additional Threads")
Macro4(E2TOKNEEDPINTOUSETHREADS,-306,"Der Benutzer muß angemeldet sein, um mit weiteren Threads zuzugreifen","User must be logged in for access with additional Threads")
Macro4(E2P11LIBNOTLOADED,-350,"PKCS#11 Treiber konnte nicht geladen werden", "Cannot load PKCS#11 driver")
Macro4(E2P11SLOTINVALID, -351,"Ungültiger Slotname in URL", "Invalid slot name in URL")

Macro4(E2SWTOKDIRNOTFOUND, -370, "Standard Ordner für software Tokens nicht gefunden", "Could not find saoftware token default directory")

/* Threads and Mutex errors 400 - 419*/
Macro4(E2MUTEXLOCK,-401,"Mutexfunktion LOCK fehlgeschlagen","Mutex lock failed")
Macro4(E2MUTEXUNLOCK,-402,"Mutexfunktion UNLOCK fehlgeschlagen","Mutex unlock failed")
Macro4(E2MUTEXCREATE,-403,"Mutex kann nicht erzeugt werden","Mutex creation failed")
Macro4(E2MUTEXNOTFOUND,-404,"Mutex kann nicht gefunden werden","Mutex not found")
Macro4(E2MUTEXDESTROY,-405,"Mutex kann nicht freigegeben werden","Mutex destruction failed")
Macro4(E2MUTEXFUNC,-406,"Keine Mutexfunktionen verfügbar","No mutex functions available")
Macro4(E2TOKNOTHREADS,-407,"Mehrere Threads für dieses Token nicht angegeben","Multithread access for this token not defined")
Macro4(E2TOKFUNKTIONNOTALLOWEDWITHTHREADS,-408,"Funktion nicht erlaubt, wenn mehrere Threads auf das Token zugreifen","Function not allowed in multi thread mode")

/* PKCS#11 errors */
Macro4(E2CKR_OK                                ,-0x5000,
"Der verwendete Smartcardtreiber (PKCS#11) meldete das Ergebnis CKR_OK: Funktion war erfolgreich",  
"The smartcard driver (PKCS#11) being used has reported the code CKR_OK: function has completed successfully")  
Macro4(E2CKR_CANCEL                            ,-0x5001,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_CANCEL: Funktion sollte abgebrochen werden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_CANCEL: function should be canceled")  
Macro4(E2CKR_HOST_MEMORY                       ,-0x5002,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_HOST_MEMORY: Nicht genug Speicher im Rechenr",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_HOST_MEMORY: not enough memory on host")  
Macro4(E2CKR_SLOT_ID_INVALID                   ,-0x5003,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_SLOT_ID_INVALID: Leserreferenz ist ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_SLOT_ID_INVALID: slot ID is invalid")  
Macro4(E2CKR_FLAGS_INVALID                     ,-0x5004,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_FLAGS_INVALID: Eigenschaften sind ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_FLAGS_INVALID: flags are invalid")  	   
Macro4(E2CKR_GENERAL_ERROR                     ,-0x5005,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_GENERAL_ERROR: Allgemeiner Fehler",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_GENERAL_ERROR: general error")  
Macro4(E2CKR_FUNCTION_FAILED                   ,-0x5006,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_FUNCTION_FAILED: Die aufgerufene Funktion wurde während der Ausführung abgebrochen",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_FUNCTION_FAILED: The requested function could not be performed")  
Macro4(E2CKR_ARGUMENTS_BAD                     ,-0x5007,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_ARGUMENTS_BAD: die an die Cryptoki-Funktion übergebenen Parameter waren fehlerhaft",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_ARGUMENTS_BAD: the arguments supplied to the Cryptoki function were in some way not appropriate")  
Macro4(E2CKR_NO_EVENT                          ,-0x5008,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_NO_EVENT: GetSlotEvent wurde im nicht-blockierenden Modus aufgerufen, und es konnten keine neue Anschlüsse zurückgeben werden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_NO_EVENT: GetSlotEvent is called in non-blocking mode and there are no new slot events to return")  
Macro4(E2CKR_NEED_TO_CREATE_THREADS            ,-0x5009,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_NEED_TO_CREATE_THREADS: Die Bibliothek kann nicht einwandfrei arbeiten, ohne dass sie neue Threads öffnen kann",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_NEED_TO_CREATE_THREADS: The library cannot function properly without being able to spawn new threads ")  
Macro4(E2CKR_CANT_LOCK                         ,-0x500A,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_CANT_LOCK: Die von der Anwendung für die Thread-Sicherheit angeforderte Art des Lockings ist in dieser Bibliothek nicht verfügbar",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_CANT_LOCK: the type of locking requested by the application for thread-safety is not available in this library")  
Macro4(E2CKR_ATTRIBUTE_READ_ONLY               ,-0x5010,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_ATTRIBUTE_READ_ONLY: Attribut kann nicht geändert werden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_ATTRIBUTE_READ_ONLY: attribute cannot be modified")  
Macro4(E2CKR_ATTRIBUTE_SENSITIVE               ,-0x5011,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_ATTRIBUTE_SENSITIVE: Attribut ist sensitiv und kann nicht gelesen werden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_ATTRIBUTE_SENSITIVE: attribute is sensitive and cannot be revealed")  
Macro4(E2CKR_ATTRIBUTE_TYPE_INVALID            ,-0x5012,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_ATTRIBUTE_TYPE_INVALID: Attributtyp ist ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_ATTRIBUTE_TYPE_INVALID: attribute type is invalid")  
Macro4(E2CKR_ATTRIBUTE_VALUE_INVALID           ,-0x5013,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_ATTRIBUTE_VALUE_INVALID: Attributwert ist ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_ATTRIBUTE_VALUE_INVALID: attribute value is invalid")  
Macro4(E2CKR_DATA_INVALID                      ,-0x5020,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_DATA_INVALID: Daten sind ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_DATA_INVALID: data is invalid")  
Macro4(E2CKR_DATA_LEN_RANGE                    ,-0x5021,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_DATA_LEN_RANGE: Datenlänge ist nicht erlaubt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_DATA_LEN_RANGE: data length is out of range")  
Macro4(E2CKR_DEVICE_ERROR                      ,-0x5030,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_DEVICE_ERROR: Gerätefehler",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_DEVICE_ERROR: device error")  
Macro4(E2CKR_DEVICE_MEMORY                     ,-0x5031,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_DEVICE_MEMORY: Nicht genug Speicher in der Karte",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_DEVICE_MEMORY: not enough memory on device")  
Macro4(E2CKR_DEVICE_REMOVED                    ,-0x5032,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_DEVICE_REMOVED: Karte wurde gezogen",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_DEVICE_REMOVED: device has been removed")  
Macro4(E2CKR_ENCRYPTED_DATA_INVALID            ,-0x5040,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_ENCRYPTED_DATA_INVALID: Verschlüsselte Daten sind ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_ENCRYPTED_DATA_INVALID: encrypted data is invalid")  
Macro4(E2CKR_ENCRYPTED_DATA_LEN_RANGE          ,-0x5041,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_ENCRYPTED_DATA_LEN_RANGE: Länge der verschlüsselten Daten ist ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_ENCRYPTED_DATA_LEN_RANGE: encrypted data length is out of range")  
Macro4(E2CKR_FUNCTION_CANCELED                 ,-0x5050,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_FUNCTION_CANCELED: Funktion wurde abgebrochen",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_FUNCTION_CANCELED: function has been canceled")  
Macro4(E2CKR_FUNCTION_NOT_PARALLEL             ,-0x5051,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_FUNCTION_NOT_PARALLEL: Keine Funktion wird parallel ausgeführt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_FUNCTION_NOT_PARALLEL: no function is executing in parallel")  
Macro4(E2CKR_FUNCTION_PARALLEL                 ,-0x5052,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_FUNCTION_PARALLEL: Funktion wird parallel ausgeführt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_FUNCTION_PARALLEL: function is executing in parallel")  
Macro4(E2CKR_FUNCTION_NOT_SUPPORTED            ,-0x5054,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_FUNCTION_NOT_SUPPORTED: Die aufgerufene Funktion wird von dieser Cryptoki-Bibliothek nicht unterstützt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_FUNCTION_NOT_SUPPORTED: The requested function is not supported by this Cryptoki library")  
Macro4(E2CKR_KEY_HANDLE_INVALID                ,-0x5060,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_KEY_HANDLE_INVALID: Schlüsselreferenz ist ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_KEY_HANDLE_INVALID: key handle is invalid")  
Macro4(E2CKR_KEY_SENSITIVE                     ,-0x5061,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_KEY_SENSITIVE: Schlüssel ist sensitiv und kann nicht gelesen werden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_KEY_SENSITIVE: key is sensitive and cannot be revealed")  
Macro4(E2CKR_KEY_SIZE_RANGE                    ,-0x5062,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_KEY_SIZE_RANGE: Schlüssellänge ist nicht erlaubt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_KEY_SIZE_RANGE: key size is out of range")  
Macro4(E2CKR_KEY_TYPE_INCONSISTENT             ,-0x5063,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_KEY_TYPE_INCONSISTENT: Schlüsseltyp paßt nicht zum Mechanismus",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_KEY_TYPE_INCONSISTENT: key type is inconsistent with mechanism")  
Macro4(E2CKR_KEY_NOT_NEEDED                    ,-0x5064,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_KEY_NOT_NEEDED: Ein fremder Schlüssel wurde übergeben",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_KEY_NOT_NEEDED: An extraneous key was supplied")  
Macro4(E2CKR_KEY_CHANGED                       ,-0x5065,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_KEY_CHANGED: Ein übergebener Schlüssel stimmt nicht mit dem aus der ursprünglichen gespeicherten Kartenverbindung überein",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_KEY_CHANGED: one of the keys specified is not the same key that was being used in the original saved session")  
Macro4(E2CKR_KEY_NEEDED                        ,-0x5066,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_KEY_NEEDED: Die Kartenverbindung kann nicht wiederhergestellt werden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_KEY_NEEDED: the session state cannot be restored ")  
Macro4(E2CKR_KEY_INDIGESTIBLE                  ,-0x5067,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_KEY_INDIGESTIBLE: Zu dem angegebenen Schlüssel kann kein Digest erzeugt werden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_KEY_INDIGESTIBLE: the value of the specified key cannot be digested ")  
Macro4(E2CKR_KEY_FUNCTION_NOT_PERMITTED        ,-0x5068,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_KEY_FUNCTION_NOT_PERMITTED: Es wurde versucht, einen Schlüssel zu einem Zweck zu verwenden, den die Schlüsselattribute nicht erlauben",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_KEY_FUNCTION_NOT_PERMITTED: An attempt has been made to use a key for a cryptographic purpose that the key's attributes are not set to allow it to do")
Macro4(E2CKR_KEY_NOT_WRAPPABLE                 ,-0x5069,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_KEY_NOT_WRAPPABLE: Schlüssel kann nicht verpackt werden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_KEY_NOT_WRAPPABLE: Cryptoki (or the token) is unable to wrap the key as requested ")  
Macro4(E2CKR_KEY_UNEXTRACTABLE                 ,-0x506A,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_KEY_UNEXTRACTABLE: Der angebene private oder geheime Schlüssel kann nicht verpackt werden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_KEY_UNEXTRACTABLE: The specified private or secret key can't be wrapped ")  
Macro4(E2CKR_MECHANISM_INVALID                 ,-0x5070,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_MECHANISM_INVALID: Ungültiger Mechanismus",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_MECHANISM_INVALID: mechanism is invalid")  
Macro4(E2CKR_MECHANISM_PARAM_INVALID           ,-0x5071,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_MECHANISM_PARAM_INVALID: Falscher Mechanismusparameter",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_MECHANISM_PARAM_INVALID: mechanism parameter is invalid")  
Macro4(E2CKR_OBJECT_CLASS_INCONSISTENT         ,-0x5080,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_OBJECT_CLASS_INCONSISTENT: Objektklasse paßt nicht zum Mechanismus",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_OBJECT_CLASS_INCONSISTENT: object class is inconsistent with mechanism")  
Macro4(E2CKR_OBJECT_CLASS_INVALID              ,-0x5081,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_OBJECT_CLASS_INVALID: Objektklasse ist ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_OBJECT_CLASS_INVALID: object class is invalid")  
Macro4(E2CKR_OBJECT_HANDLE_INVALID             ,-0x5082,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_OBJECT_HANDLE_INVALID: Objektreferenz ist ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_OBJECT_HANDLE_INVALID: object handle is invalid")  
Macro4(E2CKR_OPERATION_ACTIVE                  ,-0x5090,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_OPERATION_ACTIVE: Eine andere Operation ist gerade aktiv",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_OPERATION_ACTIVE: another operation is already active")  
Macro4(E2CKR_OPERATION_NOT_INITIALIZED         ,-0x5091,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_OPERATION_NOT_INITIALIZED: Operation wurde nicht initialisiert",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_OPERATION_NOT_INITIALIZED: operation has not been initialized")  
Macro4(E2CKR_PIN_INCORRECT                     ,-0x50A0,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_PIN_INCORRECT: Paßwort ist falsch",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_PIN_INCORRECT: PIN is incorrect")  
Macro4(E2CKR_PIN_INVALID                       ,-0x50A1,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_PIN_INVALID: Neues Paßwort enthält unerlaubte Zeichen",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_PIN_INVALID: new PIN contains invalid characters")  
Macro4(E2CKR_PIN_LEN_RANGE                     ,-0x50A2,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_PIN_LEN_RANGE: Länge des neuen Paßworts ist nicht erlaubt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_PIN_LEN_RANGE: new PIN length is out of range (assuming token specifies range)")  
Macro4(E2CKR_PIN_EXPIRED                       ,-0x50A3,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_PIN_EXPIRED: Das angegebene Passwort ist abgelaufen",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_PIN_EXPIRED: The specified PIN has expired")  
Macro4(E2CKR_PIN_LOCKED                        ,-0x50A4,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_PIN_LOCKED: Das angegebene Passwort ist gesperrt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_PIN_LOCKED: The specified PIN is locked")  
Macro4(E2CKR_SESSION_CLOSED                    ,-0x50B0,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_SESSION_CLOSED: Kartenverbindung ist bereits geschlossen ",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_SESSION_CLOSED: session has been closed")  
Macro4(E2CKR_SESSION_COUNT                     ,-0x50B1,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_SESSION_COUNT: Es kann keine weitere Kartenverbindung mehr aufgebaut werden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_SESSION_COUNT: session limits have been reached")  
Macro4(E2CKR_SESSION_EXCLUSIVE_EXISTS          ,-0x50B2,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_SESSION_EXCLUSIVE_EXISTS: Es existiert bereits eine exklusive Kartenverbindung",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_SESSION_EXCLUSIVE_EXISTS: an exclusive session already exists")  
Macro4(E2CKR_SESSION_HANDLE_INVALID            ,-0x50B3,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_SESSION_HANDLE_INVALID: Kartenverbindungsreferenz ist ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_SESSION_HANDLE_INVALID: session handle is invalid")  
Macro4(E2CKR_SESSION_PARALLEL_NOT_SUPPORTED    ,-0x50B4,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_SESSION_PARALLEL_NOT_SUPPORTED: Parallele Kartenverbindung wird nicht unterstützt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_SESSION_PARALLEL_NOT_SUPPORTED: parallel execution is not supported")  
Macro4(E2CKR_SESSION_READ_ONLY                 ,-0x50B5,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_SESSION_READ_ONLY: Kartenverbindung ist schreibgeschützt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_SESSION_READ_ONLY: session is read-only")  
Macro4(E2CKR_SESSION_EXISTS                    ,-0x50B6,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_SESSION_EXISTS: Es ist bereits eine Verbindung mit der Karte offen",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_SESSION_EXISTS: a session with the token is already open")  
Macro4(E2CKR_SESSION_READ_ONLY_EXISTS          ,-0x50B7,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_SESSION_READ_ONLY_EXISTS: Es existiert bereits eine Kartenverbindung mit ausschliesslichem Lesezugriff",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_SESSION_READ_ONLY_EXISTS: A read-only session already exists")  
Macro4(E2CKR_SESSION_READ_WRITE_SO_EXISTS      ,-0x50B8,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_SESSION_READ_WRITE_SO_EXISTS: Es existiert bereits eine Kartenverbindung für den Sicherheitsadministrator im Schreib/Lesezugriff",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_SESSION_READ_WRITE_SO_EXISTS: A read/write SO session already exists")  
Macro4(E2CKR_SIGNATURE_INVALID                 ,-0x50C0,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_SIGNATURE_INVALID: Signatur ist ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_SIGNATURE_INVALID: signature is invalid")  
Macro4(E2CKR_SIGNATURE_LEN_RANGE               ,-0x50C1,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_SIGNATURE_LEN_RANGE: Signaturlänge ist nicht erlaubt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_SIGNATURE_LEN_RANGE: signature length is out of range")  
Macro4(E2CKR_TEMPLATE_INCOMPLETE               ,-0x50D0,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_TEMPLATE_INCOMPLETE: Schablone ist unvollständig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_TEMPLATE_INCOMPLETE: template is incomplete")  
Macro4(E2CKR_TEMPLATE_INCONSISTENT             ,-0x50D1,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_TEMPLATE_INCONSISTENT: Schablone ist inkonsitent",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_TEMPLATE_INCONSISTENT: template is inconsistent")  
Macro4(E2CKR_TOKEN_NOT_PRESENT                 ,-0x50E0,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_TOKEN_NOT_PRESENT: Es ist keine Karte eingelegt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_TOKEN_NOT_PRESENT: slot does not contain a token")  
Macro4(E2CKR_TOKEN_NOT_RECOGNIZED              ,-0x50E1,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_TOKEN_NOT_RECOGNIZED: Kartentyp ist unbekannt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_TOKEN_NOT_RECOGNIZED: the token was not recognized")  
Macro4(E2CKR_TOKEN_WRITE_PROTECTED             ,-0x50E2,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_TOKEN_WRITE_PROTECTED: Karte ist schreibgeschützt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_TOKEN_WRITE_PROTECTED: token is write-protected")  
Macro4(E2CKR_UNWRAPPING_KEY_HANDLE_INVALID     ,-0x50F0,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_UNWRAPPING_KEY_HANDLE_INVALID: Ungültige Referenz eines Entschlüsselungsschlüssels",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_UNWRAPPING_KEY_HANDLE_INVALID: unwrapping key handle is invalid")  
Macro4(E2CKR_UNWRAPPING_KEY_SIZE_RANGE         ,-0x50F1,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_UNWRAPPING_KEY_SIZE_RANGE: Länge des Entschlüsselungsschlüssels ist nicht erlaubt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_UNWRAPPING_KEY_SIZE_RANGE: unwrapping key size is out of range")  
Macro4(E2CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT  ,-0x50F2,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT: Typ des Entschlüsselungsschlüssels paßt nicht zum Mechanismus",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT: unwrapping key type is inconsistent with mechanism")  
Macro4(E2CKR_USER_ALREADY_LOGGED_IN            ,-0x5100,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_USER_ALREADY_LOGGED_IN: Es ist bereits ein Benutzer angemeldet",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_USER_ALREADY_LOGGED_IN: a user is already logged in")  
Macro4(E2CKR_USER_NOT_LOGGED_IN                ,-0x5101,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_USER_NOT_LOGGED_IN: Kein Benutzer ist angemeldet",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_USER_NOT_LOGGED_IN: a user is not logged in")  
Macro4(E2CKR_USER_PIN_NOT_INITIALIZED          ,-0x5102,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_USER_PIN_NOT_INITIALIZED: Das Paßwort des Benutzers ist noch nicht initialisiert",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_USER_PIN_NOT_INITIALIZED: the user's PIN has not been intialized")  
Macro4(E2CKR_USER_TYPE_INVALID                 ,-0x5103,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_USER_TYPE_INVALID: Benutzertyp ist ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_USER_TYPE_INVALID: user type is invalid")  
Macro4(E2CKR_USER_ANOTHER_ALREADY_LOGGED_IN    ,-0x5104,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_USER_ANOTHER_ALREADY_LOGGED_IN: Ein anderer Benutzer ist bereits angemeldet",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_USER_ANOTHER_ALREADY_LOGGED_IN: another user is already logged into the session")  
Macro4(E2CKR_USER_TOO_MANY_TYPES               ,-0x5105,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_USER_TOO_MANY_TYPES: Es wurde versucht, mehr unterschiedliche Benutzer als erlaubt anzumelden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_USER_TOO_MANY_TYPES: An attempt was made to have more distinct users simultaneously logged into the token than the token and/or library permits")
Macro4(E2CKR_WRAPPED_KEY_INVALID               ,-0x5110,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_WRAPPED_KEY_INVALID: Der verpackte Schlüssel ist ungültig",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_WRAPPED_KEY_INVALID: wrapped key is invalid")  
Macro4(E2CKR_WRAPPED_KEY_LEN_RANGE             ,-0x5112,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_WRAPPED_KEY_LEN_RANGE: Länge des verpackten Schlüssels ist nicht erlaubt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_WRAPPED_KEY_LEN_RANGE: wrapped key length is out of range")  
Macro4(E2CKR_WRAPPING_KEY_HANDLE_INVALID       ,-0x5113,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_WRAPPING_KEY_HANDLE_INVALID: Ungültige Referenz eines Verschlüsselungsschlüssels",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_WRAPPING_KEY_HANDLE_INVALID: wrapping key handle is invalid")  
Macro4(E2CKR_WRAPPING_KEY_SIZE_RANGE           ,-0x5114,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_WRAPPING_KEY_SIZE_RANGE: Länge des Verschlüsselungsschlüssels ist nicht erlaubt",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_WRAPPING_KEY_SIZE_RANGE: wrapping key size is out of range")  
Macro4(E2CKR_WRAPPING_KEY_TYPE_INCONSISTENT    ,-0x5115,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_WRAPPING_KEY_TYPE_INCONSISTENT: Typ des Verschlüsselungsschlüssels paßt nicht zum Mechanismus",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_WRAPPING_KEY_TYPE_INCONSISTENT: wrapping key type is inconsistent with mechanism")
Macro4(E2CKR_RANDOM_SEED_NOT_SUPPORTED         ,-0x5120,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_RANDOM_SEED_NOT_SUPPORTED: Der Zufallszahlengenerator des Geräts akzeptiert keinen von der Anwendung übergebenen Anfangswert",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_RANDOM_SEED_NOT_SUPPORTED: the token's random number generator does not accept seeding from an application")  
Macro4(E2CKR_RANDOM_NO_RNG                     ,-0x5121,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_RANDOM_NO_RNG: Das angegebene Gerät hat keinen Zufallszahlengenerator",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_RANDOM_NO_RNG: the specified token doesn't have a random number generator")  
Macro4(E2CKR_BUFFER_TOO_SMALL                  ,-0x5150,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_BUFFER_TOO_SMALL: Die Ausgabe der Funktion passt nicht in den übergebenen Puffer",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_BUFFER_TOO_SMALL: The output of the function is too large to fit in the supplied buffer")  
Macro4(E2CKR_SAVED_STATE_INVALID               ,-0x5160,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_SAVED_STATE_INVALID: der übergebene Zustand der Kartenverbindung ist ungültig und kann nicht wiederhergestellt werden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_SAVED_STATE_INVALID: the supplied saved cryptographic operations state is invalid and cannot be restored")  
Macro4(E2CKR_INFORMATION_SENSITIVE             ,-0x5170,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_INFORMATION_SENSITIVE: Die angeforderte Information wurde nicht übermittelt, weil das Gerät sie als sensitiv betrachtet",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_INFORMATION_SENSITIVE: The information requested could not be obtained because the token considers it sensitive")  
Macro4(E2CKR_STATE_UNSAVEABLE                  ,-0x5180,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_STATE_UNSAVEABLE: Der derzeitige Zustand der angegebenen Kartenverbindung kann nicht gespeichert werden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_STATE_UNSAVEABLE: The cryptographic operations state of the specified session cannot be saved ")  
Macro4(E2CKR_CRYPTOKI_NOT_INITIALIZED          ,-0x5190,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_CRYPTOKI_NOT_INITIALIZED: Die Cryptoki-Bibliothek ist noch nicht initialisiert worden",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_CRYPTOKI_NOT_INITIALIZED: Cryptoki library has not yet been initialized ")  
Macro4(E2CKR_CRYPTOKI_ALREADY_INITIALIZED      ,-0x5191,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_CRYPTOKI_ALREADY_INITIALIZED: Die Cryptoki-Bibliothek wurde bereits initialisiert",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_CRYPTOKI_ALREADY_INITIALIZED: Cryptoki library has already been initialized ")  
Macro4(E2CKR_MUTEX_BAD                         ,-0x51A0,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_MUTEX_BAD: Es wurde ein ungültiges Mutexobjekt übergeben",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_MUTEX_BAD: a bad mutex object was passed")  
Macro4(E2CKR_MUTEX_NOT_LOCKED                  ,-0x51A1,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_MUTEX_NOT_LOCKED: Der an die Mutex-unlocking Funktion übergebene Mutex war nicht \"gelockt\"",  
"The smartcard driver (PKCS#11) being used has reported the error CKR_MUTEX_NOT_LOCKED: the mutex supplied to the mutex-unlocking function was not locked")  
Macro4(E2CKR_VENDOR_DEFINED                    ,-0xD000,
"Der verwendete Smartcardtreiber (PKCS#11) meldete den Fehler CKR_VENDOR_DEFINED: Ein herstellerabhängiger Fehler ist aufgetreten",
"The smartcard driver (PKCS#11) being used has reported the error CKR_VENDOR_DEFINED: A vendor-defined error occurred")

