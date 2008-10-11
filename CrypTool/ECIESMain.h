
#include "s_ecFp.h" // elliptic curve stuff
#ifndef DISABLE_CV
#include "actKey.h"//beinhaltet Blob
#endif

void ECCEnc(char* infile, const char *OldTitle);
void ECCDec(char* infile, const char *OldTitle);
void ShowPrivateKey(CString &UserKeyId, CString &passwd, CString &privKey);
void ShowPublicKey(CString &UserKeyId, CString &pubKey_xcoord, CString &pubKey_ycoord);

#ifndef DISABLE_CV
int encrypt(act::Blob &encBlob, const CString &sName, const CString &sVorname, const CString &rName, const CString &rVorname, const char* sS, const CString &curveS, const char* xR, const char* yR, const CString curveR, const char* ifile);
int decrypt(act::Blob &decBlob, const CString &rName, const CString &rVorname, const char* sR, const CString &curveR, const char* ifile);
int importKey(act::Key& key, const CString kurve, const char* x, const char* y, const char* s);
void encryptSessionKey(const act::Key &pubRecECIES, const act::Key &privSendECIES,  const act::Blob &sessionKey, act::Blob &encryptedSessionKey);
int decryptSessionKey(const act::Key &privRecECIES, const act::Blob &encryptedSessionKey, act::Blob &sessionKey);
void encryptData(const act::Blob &plaintext, act::Blob &sessionKey, act::Blob &ciphertext);
int decryptData(const act::Blob &ciphertext, const act::Blob &sessionKey, act::Blob &plaintext);
act::Blob writeEncFile(const CString &ofile, const CString &sName, const CString &sVorname, const CString &rName, const CString &rVorname, const CString curveR, const act::Blob &encryptedSessionKey, const act::Blob &ciphertext);
int readEncFile(const CString &ifile, CString &sName, CString &sVorname, CString &rName, CString &rVorname, CString curveR, act::Blob &encryptedSessionKey, act::Blob &ciphertext);
void newWindow(const bool &plain, const act::Blob &output, const char* &OldTitle, const CString &ReceiverName, const CString &ReceiverFirstname, const CString &ReceiverKeyType);
#endif