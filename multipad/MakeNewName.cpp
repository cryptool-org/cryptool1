
#include "MakeNewName.h"
#include "string.h"
#include "stdio.h"

/* Die folgende Funktionen generieren aus dem Namen des Fensters mit den zu bearbeitenden
   Daten einen Namen für das Fenster, in dem die Ausgabe dargestellt wird		*/

void MakeNewName(char *dest, unsigned int len, const char *format, const char *old)
{
    if(strlen(format)+strlen(old)<(size_t)len)
        sprintf(dest,format,old);
    else
        sprintf(dest,format,"...");
}

void MakeNewName2(char *dest, int len, const char *format, const char *old, const char *alg)
{
    if(strlen(format)+strlen(old)+strlen(alg)<(size_t)len)
        sprintf(dest,format,alg,old);
    else
        sprintf(dest,format,alg,"...");
}

void MakeNewName3(char *dest, unsigned int len, const char *format, const char *alg, const char *old, const char *key)
{
    if(strlen(format)+strlen(alg)+strlen(old)+strlen(key)<(size_t)len)
        sprintf(dest,format,alg,old,key);
    else {
	    if(strlen(format)+strlen(alg)+3+strlen(key)<(size_t)len)
	        sprintf(dest,format,alg,"...",key);
		else
	        sprintf(dest,format,alg,"...","...");
	}
}
