#ifndef __MAKE_NEW_NAME_H
#define __MAKE_NEW_MAME_H

void MakeNewName (char *dest, unsigned int len, const char *format, const char *old);
void MakeNewName2(char *dest, int len, const char *format, const char *old, const char *alg);
void MakeNewName3(char *dest, unsigned int len, const char *format, const char *alg, const char *old, const char *key);


#endif
