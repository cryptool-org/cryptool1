# Microsoft Developer Studio Project File - Name="CrypTool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CrypTool - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "CrypTool.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "CrypTool.mak" CFG="CrypTool - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "CrypTool - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "CrypTool - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE "CrypTool - Win32 Release_de" (basierend auf  "Win32 (x86) Application")
!MESSAGE "CrypTool - Win32 Release_en" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CrypTool - Win32 Release"

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
# ADD LINK32 ..\LibAnalyse\Release\LibAnalyse.lib ..\Libec\Lib\EcBibV2.lib ..\libmiracl\Release\LibMiracl.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc"
# SUBTRACT LINK32 /map

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

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
# ADD LINK32 ..\LibAnalyse\Debug\LibAnalyse.lib ..\Libec\Lib\EcBibV2D.lib ..\libmiracl\Debug\LibMiracl.lib /nologo /subsystem:windows /profile /debug /machine:I386 /nodefaultlib:"libcd"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CrypTool___Win32_Release_de"
# PROP BASE Intermediate_Dir "CrypTool___Win32_Release_de"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release_de"
# PROP Intermediate_Dir "..\Release_de"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I ".." /I "..\Secude" /I "..\Libec\include" /I "..\libmiracl\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".." /I "..\Secude" /I "..\Libec\include" /I "..\libmiracl\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_DEU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\LibAnalyse\Release\LibAnalyse.lib ..\Libec\Lib\EcBibV2.lib ..\libmiracl\Release\LibMiracl.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc"
# SUBTRACT BASE LINK32 /map
# ADD LINK32 ..\LibAnalyse\Release\LibAnalyse.lib ..\Libec\Lib\EcBibV2.lib ..\libmiracl\Release\LibMiracl.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc"
# SUBTRACT LINK32 /map

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CrypTool___Win32_Release_en"
# PROP BASE Intermediate_Dir "CrypTool___Win32_Release_en"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release_en"
# PROP Intermediate_Dir "..\Release_en"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I ".." /I "..\Secude" /I "..\Libec\include" /I "..\libmiracl\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".." /I "..\Secude" /I "..\Libec\include" /I "..\libmiracl\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_DEU"
# ADD RSC /l 0x809 /d "NDEBUG" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_ENG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\LibAnalyse\Release\LibAnalyse.lib ..\Libec\Lib\EcBibV2.lib ..\libmiracl\Release\LibMiracl.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc"
# SUBTRACT BASE LINK32 /map
# ADD LINK32 ..\LibAnalyse\Release\LibAnalyse.lib ..\Libec\Lib\EcBibV2.lib ..\libmiracl\Release\LibMiracl.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc"
# SUBTRACT LINK32 /map

!ENDIF 

# Begin Target

# Name "CrypTool - Win32 Release"
# Name "CrypTool - Win32 Debug"
# Name "CrypTool - Win32 Release_de"
# Name "CrypTool - Win32 Release_en"
# Begin Group "hlp-de"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\hlp-de\AfxCore.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-de\AfxPrint.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-de\CrypTool.hpj"

!IF  "$(CFG)" == "CrypTool - Win32 Release"

USERDEP__CRYPT="$(ProjDir)\hlp-de\AfxCore.rtf"	"$(ProjDir)\hlp-de\AfxPrint.rtf"	"$(ProjDir)\hlp-de\CrypTool.rtf"	"$(ProjDir)\hlp-de\szenarien.rtf"	
# Begin Custom Build - Deutsche Hilfedatei wird erzeugt ($(InputPath))...
OutDir=.\Release
ProjDir=.
TargetName=CrypTool
InputPath=".\hlp-de\CrypTool.hpj"

"$(OutDir)\$(TargetName)-de.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat" de

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

USERDEP__CRYPT="$(ProjDir)\hlp-de\AfxCore.rtf"	"$(ProjDir)\hlp-de\AfxPrint.rtf"	"$(ProjDir)\hlp-de\CrypTool.rtf"	"$(ProjDir)\hlp-de\szenarien.rtf"	
# Begin Custom Build - Deutsche Hilfedatei wird erzeugt ($(InputPath))...
OutDir=.\Debug
ProjDir=.
TargetName=CrypTool
InputPath=".\hlp-de\CrypTool.hpj"

"$(OutDir)\$(TargetName)-de.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat" de

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

USERDEP__CRYPT="$(ProjDir)\hlp-de\AfxCore.rtf"	"$(ProjDir)\hlp-de\AfxPrint.rtf"	"$(ProjDir)\hlp-de\CrypTool.rtf"	"$(ProjDir)\hlp-de\szenarien.rtf"	
# Begin Custom Build - Deutsche Hilfedatei wird erzeugt ($(InputPath))...
OutDir=.\..\Release_de
ProjDir=.
TargetName=CrypTool
InputPath=".\hlp-de\CrypTool.hpj"

"$(OutDir)\$(TargetName)-de.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat" de

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

USERDEP__CRYPT="$(ProjDir)\hlp-de\AfxCore.rtf"	"$(ProjDir)\hlp-de\AfxPrint.rtf"	"$(ProjDir)\hlp-de\CrypTool.rtf"	"$(ProjDir)\hlp-de\szenarien.rtf"	
# Begin Custom Build - Deutsche Hilfedatei wird erzeugt ($(InputPath))...
OutDir=.\..\Release_en
ProjDir=.
TargetName=CrypTool
InputPath=".\hlp-de\CrypTool.hpj"

"$(OutDir)\$(TargetName)-de.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat" de

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\hlp-de\CrypTool.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-de\szenarien.rtf"
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

SOURCE=".\hlp-en\CrypTool.hpj"

!IF  "$(CFG)" == "CrypTool - Win32 Release"

USERDEP__CRYPT="$(ProjDir)\hlp-en\AfxCore.rtf"	"$(ProjDir)\hlp-en\AfxPrint.rtf"	"$(ProjDir)\hlp-en\CrypTool.rtf"	"$(ProjDir)\hlp-en\szenarien.rtf"	"$(ProjDir)\resource.h"	
# Begin Custom Build - Englische Hilfedatei wird erzeugt ($(InputPath))...
OutDir=.\Release
ProjDir=.
TargetName=CrypTool
InputPath=".\hlp-en\CrypTool.hpj"

"$(OutDir)\$(TargetName)-en.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat" en

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

USERDEP__CRYPT="$(ProjDir)\hlp-en\AfxCore.rtf"	"$(ProjDir)\hlp-en\AfxPrint.rtf"	"$(ProjDir)\hlp-en\CrypTool.rtf"	"$(ProjDir)\hlp-en\szenarien.rtf"	"$(ProjDir)\resource.h"	
# Begin Custom Build - Englische Hilfedatei wird erzeugt ($(InputPath))...
OutDir=.\Debug
ProjDir=.
TargetName=CrypTool
InputPath=".\hlp-en\CrypTool.hpj"

"$(OutDir)\$(TargetName)-en.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat" en

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

USERDEP__CRYPT="$(ProjDir)\hlp-en\AfxCore.rtf"	"$(ProjDir)\hlp-en\AfxPrint.rtf"	"$(ProjDir)\hlp-en\CrypTool.rtf"	"$(ProjDir)\hlp-en\szenarien.rtf"	"$(ProjDir)\resource.h"	
# Begin Custom Build - Englische Hilfedatei wird erzeugt ($(InputPath))...
OutDir=.\..\Release_de
ProjDir=.
TargetName=CrypTool
InputPath=".\hlp-en\CrypTool.hpj"

"$(OutDir)\$(TargetName)-en.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat" en

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

USERDEP__CRYPT="$(ProjDir)\hlp-en\AfxCore.rtf"	"$(ProjDir)\hlp-en\AfxPrint.rtf"	"$(ProjDir)\hlp-en\CrypTool.rtf"	"$(ProjDir)\hlp-en\szenarien.rtf"	"$(ProjDir)\resource.h"	
# Begin Custom Build - Englische Hilfedatei wird erzeugt ($(InputPath))...
OutDir=.\..\Release_en
ProjDir=.
TargetName=CrypTool
InputPath=".\hlp-en\CrypTool.hpj"

"$(OutDir)\$(TargetName)-en.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat" en

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\hlp-en\CrypTool.rtf"
# End Source File
# Begin Source File

SOURCE=".\hlp-en\szenarien.rtf"
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\3dcheck.bmp
# End Source File
# Begin Source File

SOURCE=.\res\95check.bmp
# End Source File
# Begin Source File

SOURCE=.\AESEncryption.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AppDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\AppDocument.h
# End Source File
# Begin Source File

SOURCE=.\AppEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\AppEditView.h
# End Source File
# Begin Source File

SOURCE=.\res\arrben.bmp
# End Source File
# Begin Source File

SOURCE=.\res\arrdown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\ARROW_BEND.bmp
# End Source File
# Begin Source File

SOURCE=.\AscEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\AscEdit.h
# End Source File
# Begin Source File

SOURCE=.\AsymmetricEncryption.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AsymmetricEncryption.h
# End Source File
# Begin Source File

SOURCE=.\AutomaticAnalysis.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AutomaticAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\res\background2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\backgroundHybr.bmp
# End Source File
# Begin Source File

SOURCE=".\res\backward-grey.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\backward.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap10_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap12.bmp
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

SOURCE=.\res\bitmap8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmapLetsStart.bmp
# End Source File
# Begin Source File

SOURCE=.\BlockView.cpp
# End Source File
# Begin Source File

SOURCE=.\BlockView.h
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
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

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00012.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00013.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00014.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00015.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00016.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00017.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00018.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00019.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00020.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00021.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00022.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00023.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00024.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00025.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00026.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00027.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00028.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00029.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00030.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00031.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00032.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00033.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00034.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00035.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00036.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00037.bmp
# End Source File
# Begin Source File

SOURCE=.\BruteForceAnalysis.cpp
# End Source File
# Begin Source File

SOURCE=.\res\cancel_g.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CANCEL_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CANCEL_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CANCEL_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CANCEL_Y_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CANCEL_Y_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CANCEL_Y_U.bmp
# End Source File
# Begin Source File

SOURCE=.\ChrTools.cpp
# End Source File
# Begin Source File

SOURCE=.\ChrTools.h
# End Source File
# Begin Source File

SOURCE=.\res\combine_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMBINE_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMBINE_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMBINE_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMBINE_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMBINE_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMBINE_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMBINE_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\COMFLASH.CPP
# End Source File
# Begin Source File

SOURCE=.\COMFLASH.H
# End Source File
# Begin Source File

SOURCE=.\res\compute_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMPUTE_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMPUTE_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMPUTE_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMPUTE_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMPUTE_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMPUTE_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMPUTE_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\CPlotDocument.h
# End Source File
# Begin Source File

SOURCE=.\CryptDoc.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CryptDoc.h
# End Source File
# Begin Source File

SOURCE=.\CryptDocTemplate.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CryptDocTemplate.h
# End Source File
# Begin Source File

SOURCE=.\Cryptography.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

# ADD CPP /W3

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Cryptography.h
# End Source File
# Begin Source File

SOURCE=.\CrypTool.rc
# End Source File
# Begin Source File

SOURCE=.\CrypToolApp.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CrypToolApp.h
# End Source File
# Begin Source File

SOURCE=.\CrypToolPopupMenuIDs.txt

!IF  "$(CFG)" == "CrypTool - Win32 Release"

USERDEP__CRYPTO="CrypTool.rc"	
# Begin Custom Build - Checking CrypTool.rc and $(InputPath) (->CheckResourceIDs.*)
InputPath=.\CrypToolPopupMenuIDs.txt

"CheckResourceIDs.log" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	CheckResourceIDs.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

USERDEP__CRYPTO="CrypTool.rc"	
# Begin Custom Build - Checking CrypTool.rc and $(InputPath) (->CheckResourceIDs.*)
InputPath=.\CrypToolPopupMenuIDs.txt

"CheckResourceIDs.log" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	CheckResourceIDs.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

USERDEP__CRYPTO="CrypTool.rc"	
# Begin Custom Build - Checking CrypTool.rc and $(InputPath) (->CheckResourceIDs.*)
InputPath=.\CrypToolPopupMenuIDs.txt

"CheckResourceIDs.log" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	CheckResourceIDs.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

USERDEP__CRYPTO="CrypTool.rc"	
# Begin Custom Build - Checking CrypTool.rc and $(InputPath) (->CheckResourceIDs.*)
InputPath=.\CrypToolPopupMenuIDs.txt

"CheckResourceIDs.log" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	CheckResourceIDs.bat

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CrypToolTools.cpp
# End Source File
# Begin Source File

SOURCE=.\CrypToolTools.h
# End Source File
# Begin Source File

SOURCE=.\res\DerEinstiegInCrypTool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DerEinstiegInCrypTool_de.bmp
# End Source File
# Begin Source File

SOURCE=.\DialogeMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogeMessage.h
# End Source File
# Begin Source File

SOURCE=.\DialogLaengeBin.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DialogLaengeBin.h
# End Source File
# Begin Source File

SOURCE=.\DlgAbout.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgAbout.h
# End Source File
# Begin Source File

SOURCE=.\DlgAuthors.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgAuthors.h
# End Source File
# Begin Source File

SOURCE=.\DlgBruteForceAES.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBruteForceAES.h
# End Source File
# Begin Source File

SOURCE=.\DlgCaesarAnalysis.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgCaesarAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\DlgCertificateGeneration.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCertificateGeneration.h
# End Source File
# Begin Source File

SOURCE=.\DlgChangePIN.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgChangePIN.h
# End Source File
# Begin Source File

SOURCE=.\DlgDemoRSAKeyGeneration.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDemoRSAKeyGeneration.h
# End Source File
# Begin Source File

SOURCE=.\DlgECGeneration.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgECGeneration.h
# End Source File
# Begin Source File

SOURCE=.\DlgECSignatureStepByStep.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgECSignatureStepByStep.h
# End Source File
# Begin Source File

SOURCE=.\DlgEntropyInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEntropyInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgExtractSignature.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgExtractSignature.h
# End Source File
# Begin Source File

SOURCE=.\DlgFactorisationDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFactorisationDemo.h
# End Source File
# Begin Source File

SOURCE=.\DlgFactorisationList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFactorisationList.h
# End Source File
# Begin Source File

SOURCE=.\DlgHashDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHashDemo.h
# End Source File
# Begin Source File

SOURCE=.\DlgHillAnalysis.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgHillAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\DlgHybridDecryptionDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHybridDecryptionDemo.h
# End Source File
# Begin Source File

SOURCE=.\DlgHybridEncryptionDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHybridEncryptionDemo.h
# End Source File
# Begin Source File

SOURCE=.\DlgICGRandomParamater.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgICGRandomParamater.h
# End Source File
# Begin Source File

SOURCE=.\DlgKey.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgKey.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyAsym.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgKeyAsym.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyAsymGeneration.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgKeyAsymGeneration.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyFromPassword.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKeyFromPassword.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyHex.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKeyHex.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyHexAnalysis.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgKeyHexAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyHill10x10.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgKeyHill10x10.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyHill5x5.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgKeyHill5x5.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyHomophone.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKeyHomophone.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyLength.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgKeyLength.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyPermutation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKeyPermutation.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyPlayfair.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKeyPlayfair.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeySubstitution.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgKeySubstitution.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyVigenere.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgKeyVigenere.h
# End Source File
# Begin Source File

SOURCE=.\DlgLCGRandomParameter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLCGRandomParameter.h
# End Source File
# Begin Source File

SOURCE=.\DlgManualSubstAnalysis.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgManualSubstAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\DlgNGramAnalysis.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNGramAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsAnalysis.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgOptionsAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsRSADemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsRSADemo.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsSubstitutionAnalysis.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgOptionsSubstitutionAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\DlgPeriodicityAnalysis.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPeriodicityAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\DlgPINAccess.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgPINAccess.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayfairAnalysis.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayfairAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\DlgPrimesGeneratorDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPrimesGeneratorDemo.h
# End Source File
# Begin Source File

SOURCE=.\DlgProgressFactorisation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProgressFactorisation.h
# End Source File
# Begin Source File

SOURCE=.\DlgRandomGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRandomGenerator.h
# End Source File
# Begin Source File

SOURCE=.\DlgRandomParameterSECUDE.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRandomParameterSECUDE.h
# End Source File
# Begin Source File

SOURCE=.\DlgRSADecryption.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgRSADecryption.h
# End Source File
# Begin Source File

SOURCE=.\DlgRSADemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRSADemo.h
# End Source File
# Begin Source File

SOURCE=.\DlgRSAEncryption.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgRSAEncryption.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelectHashFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelectHashFunction.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowCertificate.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgShowCertificate.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowHash.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgShowHash.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowKey.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgShowKey.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowKeyHill10x10.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgShowKeyHill10x10.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowKeyHill5x5.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgShowKeyHill5x5.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowKeyParameter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgShowKeyParameter.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowParameterKeyEC.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgShowParameterKeyEC.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowPrivateKeyEC.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgShowPrivateKeyEC.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgShowProgress.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowPublicKeyEC.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgShowPublicKeyEC.h
# End Source File
# Begin Source File

SOURCE=.\DlgSignature.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgSignature.h
# End Source File
# Begin Source File

SOURCE=.\DlgSignatureDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSignatureDemo.h
# End Source File
# Begin Source File

SOURCE=.\DlgStatRandTests.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStatRandTests.h
# End Source File
# Begin Source File

SOURCE=.\DlgTextOptions.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgTextOptions.h
# End Source File
# Begin Source File

SOURCE=.\DlgTipsAndTricks.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTipsAndTricks.h
# End Source File
# Begin Source File

SOURCE=.\DlgVerifyECSignatureStepByStep.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgVerifyECSignatureStepByStep.h
# End Source File
# Begin Source File

SOURCE=.\DlgVerifySignature.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgVerifySignature.h
# End Source File
# Begin Source File

SOURCE=.\DlgX2ModNRandomParamater.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgX2ModNRandomParamater.h
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

SOURCE=.\res\EMPTY1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EMPTY1b.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EMPTY2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EMPTY2b.bmp
# End Source File
# Begin Source File

SOURCE=..\LibEc\include\EMSA1.H
# End Source File
# Begin Source File

SOURCE=.\res\ENCRYPT_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ENCRYPT_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ENCRYPT_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ENCRYPT_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ENCRYPT_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ENCRYPT_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ENCRYPT_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\FileTools.cpp
# End Source File
# Begin Source File

SOURCE=.\FileTools.h
# End Source File
# Begin Source File

SOURCE=.\FLASH.CPP
# End Source File
# Begin Source File

SOURCE=.\FLASH.H
# End Source File
# Begin Source File

SOURCE=".\res\foreward-grey.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\foreward.bmp
# End Source File
# Begin Source File

SOURCE=.\FPOLY.CPP
# End Source File
# Begin Source File

SOURCE=.\FPOLY.H
# End Source File
# Begin Source File

SOURCE=.\res\GB_CANCEL_Y_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_CANCEL_Y_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_CANCEL_Y_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_ENCRYPT_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_ENCRYPT_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_ENCRYPT_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_ENCRYPT_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_ENCRYPT_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_ENCRYPT_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_ENCRYPT_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_GENCERT_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_GENCERT_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_GENCERT_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_GENCERT_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_GENCERT_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_GENCERT_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_GENKEY_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_GENKEY_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_GENKEY_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_GENKEY_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_GENKEY_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_GENKEY_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOALG_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOALG_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOALG_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOALG_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOCERT_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOCERT_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOCERT_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOCERT_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFODOC_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFODOC_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFODOC_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFODOC_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOENC_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOENC_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOENC_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOENC_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOHASH_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOHASH_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOHASH_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOHASH_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOKEY_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOKEY_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOKEY_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOKEY_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOSIGN_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOSIGN_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOSIGN_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GB_INFOSIGN_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GENCERT_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GENCERT_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GENCERT_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GENCERT_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GENCERT_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GENCERT_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GENKEY_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GENKEY_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GENKEY_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GENKEY_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GENKEY_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GENKEY_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\help.cur
# End Source File
# Begin Source File

SOURCE=.\HexEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\HexEdit.h
# End Source File
# Begin Source File

SOURCE=.\HexView.cpp
# End Source File
# Begin Source File

SOURCE=.\HexView.h
# End Source File
# Begin Source File

SOURCE=.\HillEncryption.cpp
# End Source File
# Begin Source File

SOURCE=.\HillEncryption.h
# End Source File
# Begin Source File

SOURCE=.\HomophoneEncryption.cpp
# End Source File
# Begin Source File

SOURCE=.\HomophoneEncryption.h
# End Source File
# Begin Source File

SOURCE=".\res\hybrid-background.bmp"
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

SOURCE=.\res\INFDOC_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFDOC_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFDOC_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFDOC_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\infoalg_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOALG_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOALG_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOALG_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOALG_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOCERT_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOCERT_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOCERT_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOCERT_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFODOC_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFODOC_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFODOC_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFODOC_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOENC_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOENC_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOENC_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOENC_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOHASH_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOHASH_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOHASH_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOHASH_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOKEY_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOKEY_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOKEY_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOKEY_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOSIGN_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOSIGN_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOSIGN_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\INFOSIGN_B_X.bmp
# End Source File
# Begin Source File

SOURCE=.\IntegerArithmetic.cpp
# End Source File
# Begin Source File

SOURCE=.\IntegerArithmetic.h
# End Source File
# Begin Source File

SOURCE=.\KeyEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyEdit.h
# End Source File
# Begin Source File

SOURCE=.\KeyFileHandling.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KeyFileHandling.h
# End Source File
# Begin Source File

SOURCE=.\KeyFromPasswordPKCS5.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyFromPasswordPKCS5.h
# End Source File
# Begin Source File

SOURCE=.\KeyParameterHomophone.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyParameterHomophone.h
# End Source File
# Begin Source File

SOURCE=.\KeyRepository.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyRepository.h
# End Source File
# Begin Source File

SOURCE=.\res\Layout.bmp
# End Source File
# Begin Source File

SOURCE=".\res\link-hybrid-down-right.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\link-hybrid-down.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\link-hybrid-right-down-right.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\logo_db.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo_fzi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo_sec.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo_secude.bmp
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

SOURCE=.\MakeNewName.cpp
# End Source File
# Begin Source File

SOURCE=.\MakeNewName.h
# End Source File
# Begin Source File

SOURCE=.\MakeZip.cpp
# End Source File
# Begin Source File

SOURCE=.\MakeZip.h
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

SOURCE=.\res\nodrop.cur
# End Source File
# Begin Source File

SOURCE=.\res\ntcheck.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OK_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OK_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OK_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OK_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\opendoc_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OPENDOC_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OPENDOC_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OPENDOC_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OPENDOC_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OPENDOC_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OPENDOC_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OPNDOC_F_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OPNDOC_F_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OPNDOC_F_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OPNDOC_T_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OPNDOC_T_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OPNDOC_T_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval1_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval1_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval1_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval1_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval1_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval1_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Oval2_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Oval2_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Oval2_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval2_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\paddoc.ico
# End Source File
# Begin Source File

SOURCE=.\ParseIniFile.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ParseIniFile.h
# End Source File
# Begin Source File

SOURCE=.\ParseIniFile2.cpp
# End Source File
# Begin Source File

SOURCE=.\ParseIniFile2.h
# End Source File
# Begin Source File

SOURCE=.\res\PfeilUnten.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PfeilUntenKlein.bmp
# End Source File
# Begin Source File

SOURCE=.\PlayfairAnalysis.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayfairAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\PlayfairEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayfairStructures.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayfairStructures.h
# End Source File
# Begin Source File

SOURCE=.\PlotDocument.cpp
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

SOURCE=.\PSEDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\PSEDemo.h
# End Source File
# Begin Source File

SOURCE=.\RandomAnalysisTools.cpp
# End Source File
# Begin Source File

SOURCE=.\RandomAnalysisTools.h
# End Source File
# Begin Source File

SOURCE=.\RandomTest.cpp
# End Source File
# Begin Source File

SOURCE=.\RandomTest.h
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute1_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute1_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute1_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute1_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute1_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute1_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute1_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute1_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute2_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute2_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute2_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute2_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute2_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute2_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute2_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute2_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute3_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute3_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute3_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute3_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute3_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute3_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute3_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute3_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute4_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute4_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute4_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute4_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute4_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute4_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute4_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute4_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute5_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute5_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute5_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute5_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute5_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute5_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute5_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute5_X.bmp
# End Source File
# Begin Source File

SOURCE=".\hlp-de\bitmaps\RauteDaten.bmp"
# End Source File
# Begin Source File

SOURCE=..\AES\RC6\rc6.c
# End Source File
# Begin Source File

SOURCE=..\AES\RC6\rc6.h
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

SOURCE=..\LibEc\sources\s_prng.c
# End Source File
# Begin Source File

SOURCE=..\LibEc\include\s_prng.h
# End Source File
# Begin Source File

SOURCE=.\res\sarrows.cur
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck1_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck1_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck1_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck1_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck1_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck1_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck2_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck2_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck2_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck2_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck2_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck2_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck3_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck3_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck3_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck3_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck3_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck3_U.bmp
# End Source File
# Begin Source File

SOURCE=.\SecudeCryptography.cpp
# End Source File
# Begin Source File

SOURCE=.\SecudeCryptography.h
# End Source File
# Begin Source File

SOURCE=.\SecudeLib.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

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

SOURCE=.\res\selectal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SELECTALG_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SELECTALG_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SELECTALG_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SELECTALG_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SELECTALG_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SELECTALG_R_U.bmp
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

SOURCE=.\SquareMatrixModN.cpp
# End Source File
# Begin Source File

SOURCE=.\SquareMatrixModN.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\res\TEST_F_D.bmp
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

SOURCE=..\AES\Twofish\Twofish.h
# End Source File
# Begin Source File

SOURCE=..\AES\Twofish\TWOFISH2.C
# End Source File
# Begin Source File

SOURCE=.\ValueList.cpp

!IF  "$(CFG)" == "CrypTool - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

# ADD BASE CPP /O1
# ADD CPP /O1

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

# ADD BASE CPP /O1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ValueList.h
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck1_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Viereck1_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck1_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Viereck1_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck1_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Viereck1_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck1_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Viereck1_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck2_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Viereck2_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck2_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Viereck2_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck2_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Viereck2_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck2_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Viereck2_X.bmp
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

SOURCE=.\zip\zunzip.c
# End Source File
# Begin Source File

SOURCE=.\zzgen.cpp
# End Source File
# Begin Source File

SOURCE=.\zzgen.h
# End Source File
# End Target
# End Project
