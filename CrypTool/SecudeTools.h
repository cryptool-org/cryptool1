/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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