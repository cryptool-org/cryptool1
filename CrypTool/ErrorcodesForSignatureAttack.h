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

