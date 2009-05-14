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
// Revision 1.4  2004/04/30 12:09:41  clausius
// Compiles with VS.NET C++
//
// Revision 1.3  2003/12/17 17:49:15  clausius
// GPL Header hinzugefuegt
//
// Revision 1.2  2002/06/07 16:15:12  bdf100
// display of certificates: do not obmit the public key
//
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

// like, aux_sprint_Certificate, but include the public key
char *sprint_Certificate_with_key(PSE pse_handle, char *stringornull, Certificate *cert);

#endif