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

// stdafx.h : Includedatei f�r Standardsystem-Includedateien,
// oder h�ufig verwendete, projektspezifische Includedateien,
// die nur in unregelm��igen Abst�nden ge�ndert werden.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header nicht einbinden
#endif

// �ndern Sie folgende Definitionen f�r Plattformen, die �lter als die unten angegebenen sind.
// Unter MSDN finden Sie die neuesten Informationen �ber die entsprechenden Werte f�r die unterschiedlichen Plattformen.
#ifndef WINVER				// Lassen Sie die Verwendung von Features spezifisch f�r Windows 95 und Windows NT 4 oder sp�ter zu.
#define WINVER 0x0501		// �ndern Sie den entsprechenden Wert, um auf Windows 98 und mindestens Windows 2000 abzuzielen.
#endif

#ifndef _WIN32_WINNT		// Lassen Sie die Verwendung von Features spezifisch f�r Windows NT 4 oder sp�ter zu.
#define _WIN32_WINNT 0x0501		// �ndern Sie den entsprechenden Wert, um auf Windows 98 und mindestens Windows 2000 abzuzielen.
#endif						

#ifndef _WIN32_WINDOWS		// Lassen Sie die Verwendung von Features spezifisch f�r Windows 98 oder sp�ter zu.
#define _WIN32_WINDOWS 0x0501 // �ndern Sie den entsprechenden Wert, um auf mindestens Windows Me abzuzielen.
#endif

#ifndef _WIN32_IE			// Lassen Sie die Verwendung von Features spezifisch f�r IE 4.0 oder sp�ter zu.
#define _WIN32_IE 0x0500	// �ndern Sie den entsprechenden Wert, um auf mindestens IE 5.0 abzuzielen.
#endif

#define _CRT_SECURE_NO_WARNINGS
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// einige CString-Konstruktoren sind explizit

// Deaktiviert das Ausblenden von einigen h�ufigen und oft ignorierten Warnungen
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen
#include <afxdisp.h>        // MFC-Automatisierungsklassen
////////////////////////////////
#include "Msg.h"
////////////////////////////////

#include <afxdtctl.h>		// MFC-Unterst�tzung f�r allgemeine Steuerelemente von Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC-Unterst�tzung f�r allgemeine Windows-Steuerelemente
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxdhtml.h>
#include <afxdlgs.h>
//#include <afxdhtml.h>



