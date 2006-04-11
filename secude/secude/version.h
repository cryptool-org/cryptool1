/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/version.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#ifndef SECUDE_VERSION_H_
#define SECUDE_VERSION_H_

/* SECUDE_VERSION should be defined here */

#ifndef SECUDE_VERSION_MAJ
#include <secude/secver.h>
#endif

/*
#define SECUDE_VERSION_UTIL
#define SECUDE_VERSION_PL
#define SECUDE_VERSION_TYPE
#define SECUDE_VERSION_LIB (SECUDE_VERSION_MAJ * 1000 + SECUDE_VERSION_MIN * 100 + SECUDE_VERSION_BUG)
*/

#define SEC_STRINGIFY(s) #s

#define MAKE_SECUDE_DOTTED_VERSION(maj, min, bug, state) \
    SEC_STRINGIFY(maj) "." SEC_STRINGIFY(min) "." SEC_STRINGIFY(bug) state

#define SECUDE_DOTTED_VERSION \
    MAKE_SECUDE_DOTTED_VERSION(SECUDE_VERSION_MAJ, SECUDE_VERSION_MIN, SECUDE_VERSION_BUG, SECUDE_VERSION_STATE)

#endif

