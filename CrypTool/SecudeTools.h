//////////////////////////////////////////////////////////////////
//
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//
// SecudeTools
//
// $Id$
//
// Toolbox for complex Secude SDK operations
//
// 2001 Martin Bartosch <m.bartosch@cynops.de>; Cynops GmbH
//
// $Log$
// Revision 1.1  2002/02/27 12:48:24  idj100
// CrypTool develop 1.3.01
//
// Revision 1.1  2001/11/09 15:37:35  idj100
// Sourcen von Martin Bartosch mit Eingebunden
// RSA-Demo überarbeitet
//
//

#ifndef _SECUDE_TOOLS_H_
#define _SECUDE_TOOLS_H_

#include <af.h>


// extract certificates and private key from PSE and stuff
// them into an OctetString ready for export
// returns NULL on error; client must free memory via 
// aux_free_OctetString()
OctetString * PKCS12_encode(PSE pse, OctetString *PIN, int iterationcount, int encrypt_priv_key);

// import certificate and private key from PKCS#12 object and store data
// in PSE
int PKCS12_import(PSE pse, OctetString *input, OctetString *password, int newpse);

// get Object ID for PSEName
ObjId * CrypToolPSEName_OID();

#endif