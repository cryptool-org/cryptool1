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


#ifndef _ERRORCODES_FORSIGNATURE_ATTACK
#define _ERRORCODES_FORSIGNATURE_ATTACK

#define _MAX_HASH_BIT_LENGTH	160
#define _MAX_HASH_BYTE_LENGTH	((_MAX_HASH_BIT_LENGTH - 1) / 8 + 1)


#define _SIG_ATT_SPEED_INCREMENT
// wenn dieses #define einkommentiert ist, erhöht sich die Geschwindigkeit des Floyd-Algorithmus
// u.a. Prämodifizierung

//#define _SIG_ATT_HASH_ONLY
// wenn dieses #define einkommentiert ist, wird nur gehasht, nicht modifiziert

#define _SIG_ATT_MODIFYING_OPTIMIZER
// wenn dieses #define einkommentiert ist, läuft das Modifizieren schneller

#define _SIG_ATT_ALWAYS_INIT_HASH
// wenn dieses #define einkommentiert ist, wird bei jedem Hashfunktion-Aufruf die HashInit-Funktion aufgerufen -
// unter Secude läuft es dann langsamer, mit OpenSSL schneller!


enum _SIG_ATT_ERR { _SIG_ATT_OK,
					_SIG_ATT_BAD_HARMLESS_FILE,
					_SIG_ATT_BAD_DANGEROUS_FILE,
					_SIG_ATT_BAD_HASH_ALGORITHM,
					_SIG_ATT_NO_HASH_ALGORITHM_IMPLEMENTED,
					_SIG_ATT_DOCUMENTS_FOUND,
					_SIG_ATT_NO_DOCUMENTS_FOUND,
					_SIG_ATT_UNMODIFIABLE_DOC,
					_SIG_ATT_FLOYD_NOT_CANCELED,				
					_SIG_ATT_FLOYD_CANCELED,
					_SIG_ATT_BAD_MODIFIABILITY,
					_SIG_ATT_TEST_SERIES_STOPPED
};

#define _SIG_ATT_LOG		"_Log.txt"
#define _SIG_ATT_HEADER		"_Header.txt"
#define _SIG_ATT_HARMLESS	"_Harmless.txt"
#define _SIG_ATT_DANGEROUS	"_Dangerous.txt"

#define _SIG_ATT_PRE_RPE_MODIFY
// wenn dieses #define einkommentiert ist, werden die Dokumente in einer Versuchsreihe nicht nur vor jedem Run, sonden
// auch vor jedem Try modifiziert - auf diese Weise durchläuft man immer wieder ein anderes Random Mapping

#endif

