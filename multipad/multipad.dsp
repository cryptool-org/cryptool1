# Microsoft Developer Studio Project File - Name="multipad" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=multipad - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "multipad.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "multipad.mak" CFG="multipad - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "multipad - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "multipad - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "multipad - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".." /I "..\Secude" /I "..\Libec\include" /I "..\libmiracl\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\LibAnalyse\Release\LibAnalyse.lib ..\Libec\Lib\EcBibV2.lib /nologo /subsystem:windows /debug /machine:I386 /out:"release\CrypTool.exe"
# SUBTRACT LINK32 /map

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /I "..\libmiracl\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\LibAnalyse\Debug\LibAnalyse.lib ..\Libec\Lib\EcBibV2D.lib /nologo /subsystem:windows /profile /debug /machine:I386 /nodefaultlib:"libcd" /out:"Debug/cryptool.exe"

!ENDIF 

# Begin Target

# Name "multipad - Win32 Release"
# Name "multipad - Win32 Debug"
# Begin Group "hlp-de"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\hlp-de\AfxCore.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-de\AfxPrint.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-de\CrypTool.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-de\multipad.hpj"

!IF  "$(CFG)" == "multipad - Win32 Release"

USERDEP__MULTI="$(ProjDir)\hlp-de\AfxCore.rtf"	"$(ProjDir)\hlp-de\AfxPrint.rtf"	"$(ProjDir)\hlp-de\CrypTool.rtf"	"$(ProjDir)\hlp-de\Primzahlen.rtf"	"$(ProjDir)\hlp-de\szenarien.rtf"	"$(ProjDir)\hlp-de\tutorial.rtf"	
# Begin Custom Build - Deutsche Hilfedatei wird erzeugt ($(InputPath))...
OutDir=.\Release
ProjDir=.
TargetName=CrypTool
InputPath=".\hlp-de\multipad.hpj"

"$(OutDir)\$(TargetName)-de.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp-de.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

USERDEP__MULTI="$(ProjDir)\hlp-de\AfxCore.rtf"	"$(ProjDir)\hlp-de\AfxPrint.rtf"	"$(ProjDir)\hlp-de\CrypTool.rtf"	"$(ProjDir)\hlp-de\Primzahlen.rtf"	"$(ProjDir)\hlp-de\szenarien.rtf"	"$(ProjDir)\hlp-de\tutorial.rtf"	
# Begin Custom Build - Deutsche Hilfedatei wird erzeugt ($(InputPath))...
OutDir=.\Debug
ProjDir=.
TargetName=cryptool
InputPath=".\hlp-de\multipad.hpj"

"$(OutDir)\$(TargetName)-de.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp-de.bat"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\hlp-de\Primzahlen.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-de\szenarien.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-de\tutorial.rtf"
# End Source File
# End Group
# Begin Group "hlp-en"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\hlp-en\AfxCore.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-en\AfxPrint.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-en\CrypTool.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-en\multipad.hpj"

!IF  "$(CFG)" == "multipad - Win32 Release"

USERDEP__MULTI="$(ProjDir)\hlp-en\AfxCore.rtf"	"$(ProjDir)\hlp-en\AfxPrint.rtf"	"$(ProjDir)\hlp-en\CrypTool.rtf"	"$(ProjDir)\hlp-en\szenarien.rtf"	"$(ProjDir)\resource.h"	
# Begin Custom Build - Englische Hilfedatei wird erzeugt ($(InputPath))...
OutDir=.\Release
ProjDir=.
TargetName=CrypTool
InputPath=".\hlp-en\multipad.hpj"

"$(OutDir)\$(TargetName)-en.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp-en.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

USERDEP__MULTI="$(ProjDir)\hlp-en\AfxCore.rtf"	"$(ProjDir)\hlp-en\AfxPrint.rtf"	"$(ProjDir)\hlp-en\CrypTool.rtf"	"$(ProjDir)\hlp-en\szenarien.rtf"	"$(ProjDir)\resource.h"	
# Begin Custom Build - Englische Hilfedatei wird erzeugt ($(InputPath))...
OutDir=.\Debug
ProjDir=.
TargetName=cryptool
InputPath=".\hlp-en\multipad.hpj"

"$(OutDir)\$(TargetName)-en.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp-en.bat"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\hlp-en\Primzahlen.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-en\szenarien.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-en\tutorial.rtf"
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\3dcheck.bmp
# End Source File
# Begin Source File

SOURCE=.\res\95check.bmp
# End Source File
# Begin Source File

SOURCE=.\aasb.h
# End Source File
# Begin Source File

SOURCE=.\About.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\About.h
# End Source File
# Begin Source File

SOURCE=.\aes.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AESSuche.cpp
# End Source File
# Begin Source File

SOURCE=.\AESSuche.h
# End Source File
# Begin Source File

SOURCE=.\AnalyseNGram.cpp
# End Source File
# Begin Source File

SOURCE=.\AnalyseNGram.h
# End Source File
# Begin Source File

SOURCE=.\AscEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\AscEdit.h
# End Source File
# Begin Source File

SOURCE=.\asymmetric.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asymmetric.h
# End Source File
# Begin Source File

SOURCE=.\automatic.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\automatic.h
# End Source File
# Begin Source File

SOURCE=.\Autoren.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Autoren.h
# End Source File
# Begin Source File

SOURCE=.\BIG.CPP
# End Source File
# Begin Source File

SOURCE=..\LibMiracl\include\BIG.H
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmapLetsStart.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\brute.cpp
# End Source File
# Begin Source File

SOURCE=.\ChrTools.cpp
# End Source File
# Begin Source File

SOURCE=.\ChrTools.h
# End Source File
# Begin Source File

SOURCE=.\COMFLASH.CPP
# End Source File
# Begin Source File

SOURCE=.\COMFLASH.H
# End Source File
# Begin Source File

SOURCE=.\crypt.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

# ADD CPP /W3

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\crypt.h
# End Source File
# Begin Source File

SOURCE=.\cryptdoc.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cryptdoc.h
# End Source File
# Begin Source File

SOURCE=.\CryptDocTemplate.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CryptDocTemplate.h
# End Source File
# Begin Source File

SOURCE=.\CryptologyUsingMiracl.cpp
# End Source File
# Begin Source File

SOURCE=.\CryptologyUsingMiracl.h
# End Source File
# Begin Source File

SOURCE=.\res\DerEinstiegInCrypTool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DerEinstiegInCrypTool_de.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DerEinstiegInCrypTool_deutsch.bmp
# End Source File
# Begin Source File

SOURCE=.\dia1.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dia1.h
# End Source File
# Begin Source File

SOURCE=.\DialogCert.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DialogCert.h
# End Source File
# Begin Source File

SOURCE=.\DialogKeyHex.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DialogKeyHex.h
# End Source File
# Begin Source File

SOURCE=.\DialogLaenge.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DialogLaenge.h
# End Source File
# Begin Source File

SOURCE=.\DialogLaengeBin.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DialogLaengeBin.h
# End Source File
# Begin Source File

SOURCE=.\DialogPeriodeOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogPeriodeOutput.h
# End Source File
# Begin Source File

SOURCE=.\DialogPermutation.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogPermutation.h
# End Source File
# Begin Source File

SOURCE=.\DialogPlayfair.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogPlayfair.h
# End Source File
# Begin Source File

SOURCE=.\DialogVienereKey.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DialogVienereKey.h
# End Source File
# Begin Source File

SOURCE=.\DialoKeyCaesar.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DialoKeyCaesar.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_homophone.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_homophone.h
# End Source File
# Begin Source File

SOURCE=.\DLG_param.cpp
# End Source File
# Begin Source File

SOURCE=.\DLG_param.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_PlayfairKey.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_PlayfairKey.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Schluessel_gen.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Schluessel_gen.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_SubstResult.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Dlg_SubstResult.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Tests.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Tests.h
# End Source File
# Begin Source File

SOURCE=.\DlgAsymKeyCreat.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgAsymKeyCreat.h
# End Source File
# Begin Source File

SOURCE=.\DlgAsymKeys.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgAsymKeys.h
# End Source File
# Begin Source File

SOURCE=.\DlgCertTutorial.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCertTutorial.h
# End Source File
# Begin Source File

SOURCE=.\DlgDetailsFactorisation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDetailsFactorisation.h
# End Source File
# Begin Source File

SOURCE=.\DlgEcKeysCreat.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgEcKeysCreat.h
# End Source File
# Begin Source File

SOURCE=.\DlgFortschritt.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFortschritt.h
# End Source File
# Begin Source File

SOURCE=.\DlgGenRandomData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGenRandomData.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyTutorial.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKeyTutorial.h
# End Source File
# Begin Source File

SOURCE=.\DlgMono.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgMono.h
# End Source File
# Begin Source File

SOURCE=.\DlgParamRandSECUDE.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgParamRandSECUDE.h
# End Source File
# Begin Source File

SOURCE=.\DlgPrimesGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPrimesGenerator.h
# End Source File
# Begin Source File

SOURCE=.\DlgRandomParameterLCG.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRandomParameterLCG.h
# End Source File
# Begin Source File

SOURCE=.\DlgRandParameter_x2_mod_N.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRandParameter_x2_mod_N.h
# End Source File
# Begin Source File

SOURCE=.\DlgRandParamICG.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRandParamICG.h
# End Source File
# Begin Source File

SOURCE=.\DlgRSAwithSmallPrimesOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRSAwithSmallPrimesOptions.h
# End Source File
# Begin Source File

SOURCE=.\DlgRuntime.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRuntime.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelHash.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelHash.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowHash.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgShowHash.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowPrivEcKeys.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgShowPrivEcKeys.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowPubEcKeys.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgShowPubEcKeys.h
# End Source File
# Begin Source File

SOURCE=.\DlgSign.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgSign.h
# End Source File
# Begin Source File

SOURCE=.\DlgSignExtract.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgSignExtract.h
# End Source File
# Begin Source File

SOURCE=.\DlgSignSteps.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgSignSteps.h
# End Source File
# Begin Source File

SOURCE=.\DlgSignTutorial.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSignTutorial.h
# End Source File
# Begin Source File

SOURCE=.\DlgSignVerif.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgSignVerif.h
# End Source File
# Begin Source File

SOURCE=.\DlgSignVerifSteps.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgSignVerifSteps.h
# End Source File
# Begin Source File

SOURCE=.\DlgSubstAna.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgSubstAna.h
# End Source File
# Begin Source File

SOURCE=.\DlgTipsAndTricks.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTipsAndTricks.h
# End Source File
# Begin Source File

SOURCE=.\DlgTutorialFactorisation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTutorialFactorisation.h
# End Source File
# Begin Source File

SOURCE=.\dozip.cpp
# End Source File
# Begin Source File

SOURCE=.\dozip.h
# End Source File
# Begin Source File

SOURCE=..\LibEc\sources\Ecssa.c
# End Source File
# Begin Source File

SOURCE=..\LibEc\include\ECSSA.H
# End Source File
# Begin Source File

SOURCE=..\LibMiracl\SOURCE\ECSVER.C
# End Source File
# Begin Source File

SOURCE=.\res\EditPaste.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EditPastebmp.bmp
# End Source File
# Begin Source File

SOURCE=.\ELLIPTIC.CPP
# End Source File
# Begin Source File

SOURCE=.\ELLIPTIC.H
# End Source File
# Begin Source File

SOURCE=..\LibEc\include\EMSA1.H
# End Source File
# Begin Source File

SOURCE=.\ExtEuclid.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtEuclid.h
# End Source File
# Begin Source File

SOURCE=.\fileutil.cpp
# End Source File
# Begin Source File

SOURCE=.\fileutil.h
# End Source File
# Begin Source File

SOURCE=.\fixedview.cpp
# End Source File
# Begin Source File

SOURCE=.\fixedview.h
# End Source File
# Begin Source File

SOURCE=.\FLASH.CPP
# End Source File
# Begin Source File

SOURCE=.\FLASH.H
# End Source File
# Begin Source File

SOURCE=.\FPOLY.CPP
# End Source File
# Begin Source File

SOURCE=.\FPOLY.H
# End Source File
# Begin Source File

SOURCE=.\GenEcKurve.cpp
# End Source File
# Begin Source File

SOURCE=.\GenEcKurve.h
# End Source File
# Begin Source File

SOURCE=.\Hashdemo.cpp
# End Source File
# Begin Source File

SOURCE=.\Hashdemo.h
# End Source File
# Begin Source File

SOURCE=.\res\help.cur
# End Source File
# Begin Source File

SOURCE=.\hexdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\hexdialog.h
# End Source File
# Begin Source File

SOURCE=.\HexEdit1.cpp
# End Source File
# Begin Source File

SOURCE=.\HexEdit1.h
# End Source File
# Begin Source File

SOURCE=.\HexView.cpp
# End Source File
# Begin Source File

SOURCE=.\HexView.h
# End Source File
# Begin Source File

SOURCE=.\hill.cpp
# End Source File
# Begin Source File

SOURCE=.\hill.h
# End Source File
# Begin Source File

SOURCE=.\HillEingabe.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HillEingabe.h
# End Source File
# Begin Source File

SOURCE=.\HillEingabeGross.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HillEingabeGross.h
# End Source File
# Begin Source File

SOURCE=.\HillSchluesselAusgabe.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HillSchluesselAusgabe.h
# End Source File
# Begin Source File

SOURCE=.\HillSchluesselAusgabeGross.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HillSchluesselAusgabeGross.h
# End Source File
# Begin Source File

SOURCE=.\Homophone_Ber.cpp
# End Source File
# Begin Source File

SOURCE=.\Homophone_Ber.h
# End Source File
# Begin Source File

SOURCE=.\HybridEncr.cpp
# End Source File
# Begin Source File

SOURCE=.\HybridEncr.h
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_hext.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\KeyEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyEdit.h
# End Source File
# Begin Source File

SOURCE=.\KeyFileHandling.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KeyFileHandling.h
# End Source File
# Begin Source File

SOURCE=.\letter.cpp
# End Source File
# Begin Source File

SOURCE=.\letter.h
# End Source File
# Begin Source File

SOURCE=.\res\magnify.cur
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=".\MakeHelp-de.bat"
# End Source File
# Begin Source File

SOURCE=.\MakeHelp.bat
# End Source File
# Begin Source File

SOURCE="..\AES\Mars\mars-opt.c"
# End Source File
# Begin Source File

SOURCE=..\AES\Mars\mars.h
# End Source File
# Begin Source File

SOURCE=.\res\minifwnd.bmp
# End Source File
# Begin Source File

SOURCE=.\MONTY.CPP
# End Source File
# Begin Source File

SOURCE=.\MONTY.H
# End Source File
# Begin Source File

SOURCE=.\res\move4way.cur
# End Source File
# Begin Source File

SOURCE=.\multipad.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\multipad.h
# End Source File
# Begin Source File

SOURCE=.\MultiPad.rc
# End Source File
# Begin Source File

SOURCE=.\MyDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\MyDocument.h
# End Source File
# Begin Source File

SOURCE=.\MyEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\MyEditView.h
# End Source File
# Begin Source File

SOURCE=.\MyPlayFairEdit1.cpp
# End Source File
# Begin Source File

SOURCE=.\res\nodrop.cur
# End Source File
# Begin Source File

SOURCE=.\res\ntcheck.bmp
# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.h
# End Source File
# Begin Source File

SOURCE=.\res\paddoc.ico
# End Source File
# Begin Source File

SOURCE=.\PinAndNewPinDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PinAndNewPinDialog.h
# End Source File
# Begin Source File

SOURCE=.\PinCodeDialog.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PinCodeDialog.h
# End Source File
# Begin Source File

SOURCE=.\playfair.cpp
# End Source File
# Begin Source File

SOURCE=.\playfair.h
# End Source File
# Begin Source File

SOURCE=.\PlotDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\PlotDoc.h
# End Source File
# Begin Source File

SOURCE=.\res\plottype.ico
# End Source File
# Begin Source File

SOURCE=.\PlotView.cpp
# End Source File
# Begin Source File

SOURCE=.\PlotView.h
# End Source File
# Begin Source File

SOURCE=.\POLY.CPP
# End Source File
# Begin Source File

SOURCE=.\POLY.H
# End Source File
# Begin Source File

SOURCE=.\POLYMOD.CPP
# End Source File
# Begin Source File

SOURCE=.\POLYMOD.H
# End Source File
# Begin Source File

SOURCE=..\AES\RC6\rc6.c
# End Source File
# Begin Source File

SOURCE=..\AES\RC6\rc6.h
# End Source File
# Begin Source File

SOURCE=.\Read_Ini_File.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Read_Ini_File.h
# End Source File
# Begin Source File

SOURCE=.\Read_Ini_File_2.cpp
# End Source File
# Begin Source File

SOURCE=.\Read_Ini_File_2.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE="..\AES\Rijndael\rijndael-alg-fst.c"
# End Source File
# Begin Source File

SOURCE="..\AES\Rijndael\rijndael-alg-fst.h"
# End Source File
# Begin Source File

SOURCE="..\AES\Rijndael\rijndael-api-fst.c"
# End Source File
# Begin Source File

SOURCE="..\AES\Rijndael\rijndael-api-fst.h"
# End Source File
# Begin Source File

SOURCE=.\RSA_mit_kleinenPZ.cpp
# End Source File
# Begin Source File

SOURCE=.\RSA_mit_kleinenPZ.h
# End Source File
# Begin Source File

SOURCE=.\RsaDec.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RsaDec.h
# End Source File
# Begin Source File

SOURCE=.\RsaEnc.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RsaEnc.h
# End Source File
# Begin Source File

SOURCE=..\LibEc\sources\s_prng.c
# End Source File
# Begin Source File

SOURCE=..\LibEc\include\s_prng.h
# End Source File
# Begin Source File

SOURCE=.\res\sarrows.cur
# End Source File
# Begin Source File

SOURCE=.\Schluessel_gen.cpp
# End Source File
# Begin Source File

SOURCE=.\Schluessel_gen.h
# End Source File
# Begin Source File

SOURCE=.\SchluesselAusgabeLinear.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SchluesselAusgabeLinear.h
# End Source File
# Begin Source File

SOURCE=.\secude.cpp
# End Source File
# Begin Source File

SOURCE=.\secude.h
# End Source File
# Begin Source File

SOURCE=.\SecudeLib.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SecudeLib.h
# End Source File
# Begin Source File

SOURCE=.\SecudeTools.cpp
# End Source File
# Begin Source File

SOURCE=.\SecudeTools.h
# End Source File
# Begin Source File

SOURCE=.\secure.h
# End Source File
# Begin Source File

SOURCE=.\SelctAHashfunction.cpp
# End Source File
# Begin Source File

SOURCE=.\SelctAHashfunction.h
# End Source File
# Begin Source File

SOURCE=..\AES\Serpent\SERPENT.C
# End Source File
# Begin Source File

SOURCE=..\AES\Serpent\SERPENT.H
# End Source File
# Begin Source File

SOURCE=.\res\splith.cur
# End Source File
# Begin Source File

SOURCE=.\res\splitv.cur
# End Source File
# Begin Source File

SOURCE=.\sq_mat.cpp
# End Source File
# Begin Source File

SOURCE=.\sq_mat.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\TextAnalyse.cpp
# End Source File
# Begin Source File

SOURCE=.\TextAnalyse.h
# End Source File
# Begin Source File

SOURCE=.\TextEingabeHillAngriff.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TextEingabeHillAngriff.h
# End Source File
# Begin Source File

SOURCE=.\TextOptions.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TextOptions.h
# End Source File
# Begin Source File

SOURCE=.\res\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\trck4way.cur
# End Source File
# Begin Source File

SOURCE=.\res\trcknesw.cur
# End Source File
# Begin Source File

SOURCE=.\res\trckns.cur
# End Source File
# Begin Source File

SOURCE=.\res\trcknwse.cur
# End Source File
# Begin Source File

SOURCE=.\res\trckwe.cur
# End Source File
# Begin Source File

SOURCE=.\TutorialCert.cpp
# End Source File
# Begin Source File

SOURCE=.\TutorialCert.h
# End Source File
# Begin Source File

SOURCE=..\AES\Twofish\Twofish.h
# End Source File
# Begin Source File

SOURCE=..\AES\Twofish\TWOFISH2.C
# End Source File
# Begin Source File

SOURCE=.\ValueList.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ValueList.h
# End Source File
# Begin Source File

SOURCE=.\zip\zbits.c
# End Source File
# Begin Source File

SOURCE=.\zip\zdeflate.c
# End Source File
# Begin Source File

SOURCE=.\zip\zfile_io.c
# End Source File
# Begin Source File

SOURCE=.\zip\zglobals.c
# End Source File
# Begin Source File

SOURCE=.\zip\zinflate.c
# End Source File
# Begin Source File

SOURCE=.\zip\zip.c
# End Source File
# Begin Source File

SOURCE=.\zip\zipup.c
# End Source File
# Begin Source File

SOURCE=.\zip\ztrees.c
# End Source File
# Begin Source File

SOURCE=.\Zufallsgenerator_Tests_Alles.cpp
# End Source File
# Begin Source File

SOURCE=.\Zufallsgenerator_Tests_Alles.h
# End Source File
# Begin Source File

SOURCE=.\zip\zunzip.c
# End Source File
# Begin Source File

SOURCE=.\zzahlanalyes.cpp
# End Source File
# Begin Source File

SOURCE=.\zzahlanalyse.h
# End Source File
# Begin Source File

SOURCE=.\zzgen.cpp
# End Source File
# Begin Source File

SOURCE=.\zzgen.h
# End Source File
# End Target
# End Project
