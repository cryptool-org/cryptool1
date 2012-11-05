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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\libNTL\include" /I ".." /I ".\\" /I "..\Secude" /I "..\Libec\include" /I "..\libmiracl\include" /I "..\ChallengeResponse" /I "C:\Program files\HTML Help Workshop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\LibAnalyse\Release\LibAnalyse.lib ..\Libec\Lib\EcBibV2.lib ..\libmiracl\Release\LibMiracl.lib ..\libNTL\Release\libNTL.lib "C:\Programme\HTML Help Workshop\lib\htmlhelp.lib" ..\OpenSSL\libeay32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /libpath:"C:\Program Files\HTML Help Workshop\lib"
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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\OpenSSL" /I "..\libNTL\include" /I ".." /I ".\\" /I "..\Secude" /I "..\Libec\include" /I "..\libmiracl\include" /I "..\ChallengeResponse" /I "C:\Programme\HTML Help Workshop\include" /I "..\scintilla\include" /I "..\libVolRen" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\LibAnalyse\Debug\LibAnalyse.lib ..\Libec\Lib\EcBibV2D.lib ..\libmiracl\Debug\LibMiracl.lib ..\OpenSSL\libeay32.lib "C:\Programme\HTML Help Workshop\lib\htmlhelp.lib" ..\libNTL\Debug\libNTL.lib opengl32.lib /nologo /subsystem:windows /profile /map /debug /machine:I386 /nodefaultlib:"libcd" /libpath:"C:\Programme\HTML Help Workshop\lib"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\openSSL" /I "..\libNTL\include" /I ".." /I ".\\" /I "..\Secude" /I "..\Libec\include" /I "..\libmiracl\include" /I "..\ChallengeResponse" /I "C:\Programme\HTML Help Workshop\include" /I "..\scintilla\include" /I "..\libVolRen" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
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
# ADD LINK32 ..\LibAnalyse\Release\LibAnalyse.lib ..\Libec\Lib\EcBibV2.lib ..\libmiracl\Release\LibMiracl.lib ..\OpenSSL\libeay32.lib "C:\Programme\HTML Help Workshop\lib\htmlhelp.lib" ..\libNTL\Release\libNTL.lib opengl32.lib /nologo /subsystem:windows /profile /debug /machine:I386 /nodefaultlib:"libc" /libpath:"C:\Program Files\HTML Help Workshop\lib"
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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\openSSL" /I "..\libNTL\include" /I ".." /I ".\\" /I "..\Secude" /I "..\Libec\include" /I "..\libmiracl\include" /I "..\ChallengeResponse" /I "C:\Programme\HTML Help Workshop\include" /I "..\scintilla\include" /I "..\libVolRen" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
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
# ADD LINK32 ..\LibAnalyse\Release\LibAnalyse.lib ..\Libec\Lib\EcBibV2.lib ..\libmiracl\Release\LibMiracl.lib ..\OpenSSL\libeay32.lib "C:\Programme\HTML Help Workshop\lib\htmlhelp.lib" ..\libNTL\Release\libNTL.lib opengl32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /libpath:"C:\Programme\HTML Help Workshop\lib"
# SUBTRACT LINK32 /map

!ENDIF 

# Begin Target

# Name "CrypTool - Win32 Release"
# Name "CrypTool - Win32 Debug"
# Name "CrypTool - Win32 Release_de"
# Name "CrypTool - Win32 Release_en"
# Begin Source File

SOURCE=.\res\3dcheck.bmp
# End Source File
# Begin Source File

SOURCE=.\3DVisOpt.cpp
# End Source File
# Begin Source File

SOURCE=.\3DVisOpt.h
# End Source File
# Begin Source File

SOURCE=.\res\95check.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\gifs\ab_arrow_deactivated.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\gifs\ab_arrow_transmission.gif
# End Source File
# Begin Source File

SOURCE=.\adfgvx.cpp
# End Source File
# Begin Source File

SOURCE=.\adfgvx.h
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

SOURCE=..\libVolRen\ArcBall.cpp
# End Source File
# Begin Source File

SOURCE=..\libVolRen\ArcBall.h
# End Source File
# Begin Source File

SOURCE=.\res\arrben.bmp
# End Source File
# Begin Source File

SOURCE=.\res\arrdown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\arrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\ARROW_BEND.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\ArrowsAnimation.gif
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\ArrowsAnimationBasis.gif
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\ArrowsAnimationBasis0.gif
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\ArrowsExchange.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\ArrowsExchange2.bmp
# End Source File
# Begin Source File

SOURCE=.\AscEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\AscEdit.h
# End Source File
# Begin Source File

SOURCE=.\ASN1Decoder.cpp
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

SOURCE=..\ChallengeResponse\res\backgrou.bmp
# End Source File
# Begin Source File

SOURCE=.\res\backgrou.bmp
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

SOURCE=.\base64.cpp
# End Source File
# Begin Source File

SOURCE=.\base64.h
# End Source File
# Begin Source File

SOURCE=.\base64error.cpp
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

SOURCE=.\res\bitmap11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap13.bmp
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

SOURCE=.\res\bitmap9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmapLetsStart.bmp
# End Source File
# Begin Source File

SOURCE=.\BitParity.cpp
# End Source File
# Begin Source File

SOURCE=.\BitParity.h
# End Source File
# Begin Source File

SOURCE=.\BloemerMayAttack.cpp
# End Source File
# Begin Source File

SOURCE=.\BloemerMayAttack.h
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

SOURCE=.\res\bmp00038.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00039.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00040.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00041.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00042.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00043.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00044.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00045.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00046.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00047.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00048.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00049.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00050.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00051.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00052.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00053.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00054.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00055.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00056.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00057.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00058.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00059.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00060.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00061.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00062.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00063.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00064.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00065.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00066.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00067.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00068.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00069.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00070.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00071.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00072.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00073.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00074.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00075.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00076.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00077.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00078.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00079.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00080.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00081.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00082.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00083.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00084.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00085.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00086.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00087.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00088.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00089.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00090.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00091.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00092.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00093.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00094.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00095.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00096.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00097.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00098.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00099.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00100.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00101.bmp
# End Source File
# Begin Source File

SOURCE=.\BruteForceAnalysis.cpp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button10_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button10_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button10_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button10_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button10_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button10_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button10_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button10_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button10_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button10_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button10_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button10_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button10_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button10_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button10_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button10_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button1_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button1_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button1_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button1_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button1_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button1_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button1_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button1_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button1_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button1_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button1_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button1_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button1_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button1_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button1_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button1_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button1_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button1_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button1_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button1_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button1_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button1_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button1_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button1_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button1_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button1_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button1_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button1_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button1_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button1_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button1_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button1_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button2_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button2_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button2_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button2_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button2_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button2_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button2_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button2_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button2_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button2_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button2_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button2_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button2_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button2_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button2_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button2_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button2_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button2_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button2_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button2_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button2_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button2_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button2_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button2_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button2_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button2_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button2_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button2_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button2_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button2_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button2_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button2_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button3_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button3_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button3_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button3_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button3_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button3_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button3_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button3_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button3_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button3_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button3_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button3_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button3_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button3_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button3_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button3_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button3_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button3_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button3_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button3_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button3_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button3_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button3_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button3_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button3_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button3_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button3_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button3_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button3_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button3_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button3_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button3_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button4_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button4_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button4_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button4_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button4_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button4_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button4_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button4_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button4_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button4_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button4_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button4_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button4_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button4_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button4_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button4_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button4_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button4_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button4_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button4_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button4_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button4_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button4_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button4_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button4_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button4_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button4_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button4_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button4_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button4_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button4_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button4_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button5_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button5_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button5_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button5_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button5_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button5_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button5_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button5_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button5_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button5_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button5_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button5_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button5_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button5_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button5_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button5_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button5_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button5_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button5_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button5_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button5_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button5_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button5_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button5_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button5_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button5_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button5_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button5_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Button5_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Button5_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button5_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button5_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button6_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button6_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button6_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button6_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button6_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button6_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button6_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button6_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button6_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button6_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button6_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button6_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button6_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button6_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button6_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button6_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button7_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button7_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button7_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button7_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button7_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button7_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button7_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button7_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button7_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button7_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button7_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button7_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button7_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button7_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button7_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button7_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button8_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button8_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button8_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button8_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button8_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button8_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button8_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button8_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button8_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button8_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button8_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button8_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button8_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button8_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button8_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button8_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button9_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button9_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button9_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button9_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button9_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button9_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button9_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button9_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button9_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button9_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button9_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button9_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button9_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button9_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\Button9_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\Button9_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\ButtonControl.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonControl.h
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Calculate_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Calculate_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Calculate_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Calculate_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Calculate_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Calculate_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Calculate_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Calculate_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Calculate_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Calculate_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Calculate_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Calculate_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Calculate_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Calculate_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Calculate_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Calculate_R_X.bmp
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

SOURCE=..\ChallengeResponse\ChallengeResponseDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\ChallengeResponseDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChrTools.cpp
# End Source File
# Begin Source File

SOURCE=.\ChrTools.h
# End Source File
# Begin Source File

SOURCE=..\libVolRen\CMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\libVolRen\CMatrix.h
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

SOURCE=..\ChallengeResponse\Computer.cpp
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\Computer.h
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\ComputerList.cpp
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\ComputerList.h
# End Source File
# Begin Source File

SOURCE=.\CPlotDocument.h
# End Source File
# Begin Source File

SOURCE=..\libVolRen\CPosition.cpp
# End Source File
# Begin Source File

SOURCE=..\libVolRen\CPosition.h
# End Source File
# Begin Source File

SOURCE=..\libVolRen\CQuaternion.cpp
# End Source File
# Begin Source File

SOURCE=..\libVolRen\CQuaternion.h
# End Source File
# Begin Source File

SOURCE=.\res\cr_backg.bmp
# End Source File
# Begin Source File

SOURCE=..\libmiracl\source\CRT.CPP
# End Source File
# Begin Source File

SOURCE=..\libmiracl\include\CRT.H
# End Source File
# Begin Source File

SOURCE=.\res\CRT_0key.gif
# End Source File
# Begin Source File

SOURCE=.\res\CRT_1key.gif
# End Source File
# Begin Source File

SOURCE=.\res\CRT_2key.gif
# End Source File
# Begin Source File

SOURCE=.\res\CRT_3key.gif
# End Source File
# Begin Source File

SOURCE=.\res\CRT_4key.gif
# End Source File
# Begin Source File

SOURCE=.\res\CRT_5key.gif
# End Source File
# Begin Source File

SOURCE=.\res\CRT_6key.gif
# End Source File
# Begin Source File

SOURCE=.\res\CRT_7key.gif
# End Source File
# Begin Source File

SOURCE=.\res\crt_astr.bin
# End Source File
# Begin Source File

SOURCE=.\res\CRT_blank.gif
# End Source File
# Begin Source File

SOURCE=.\res\CRT_true.gif
# End Source File
# Begin Source File

SOURCE=.\res\CRT_wrong.gif
# End Source File
# Begin Source File

SOURCE=.\res\CRT\CrtAstronomy.gif
# End Source File
# Begin Source File

SOURCE=.\res\CrtAstronomy.gif
# End Source File
# Begin Source File

SOURCE=.\res\CRT\CrtKgrz.bmp
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

SOURCE=.\CrypToolCheckHelp.txt

!IF  "$(CFG)" == "CrypTool - Win32 Release"

USERDEP__CRYPT="CrypTool.rc"
# Begin Custom Build - Checking CrypTool Help
InputPath=.\CrypToolCheckHelp.txt

"CrypToolCheckHelp.log" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	CheckHelp.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

USERDEP__CRYPT="CrypTool.rc"
# Begin Custom Build - Checking CrypTool Help
InputPath=.\CrypToolCheckHelp.txt

"CrypToolCheckHelp.log" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	CheckHelp.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

USERDEP__CRYPT="CrypTool.rc"
# Begin Custom Build - Checking CrypTool Help
InputPath=.\CrypToolCheckHelp.txt

"CrypToolCheckHelp.log" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	CheckHelp.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

USERDEP__CRYPT="CrypTool.rc"
# Begin Custom Build - Checking CrypTool Help
InputPath=.\CrypToolCheckHelp.txt

"CrypToolCheckHelp.log" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	CheckHelp.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug_de"

USERDEP__CRYPT="CrypTool.rc"
# Begin Custom Build - Checking CrypTool Help
InputPath=.\CrypToolCheckHelp.txt

"CrypToolCheckHelp.log" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	CheckHelp.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug_en"

USERDEP__CRYPT="CrypTool.rc"
# Begin Custom Build - Checking CrypTool Help
InputPath=.\CrypToolCheckHelp.txt

"CrypToolCheckHelp.log" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	CheckHelp.bat

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=.\CrypToolPopupMenuIDs.txt

!IF  "$(CFG)" == "CrypTool - Win32 Release"

USERDEP__CRYPT="CrypTool.rc"	
# Begin Custom Build - Checking CrypTool.rc and $(InputPath) (->CheckResourceIDs.*)
InputPath=.\CrypToolPopupMenuIDs.txt

"CheckResourceIDs.log" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	CheckResourceIDs.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Debug"

USERDEP__CRYPT="CrypTool.rc"	
# Begin Custom Build - Checking CrypTool.rc and $(InputPath) (->CheckResourceIDs.*)
InputPath=.\CrypToolPopupMenuIDs.txt

"CheckResourceIDs.log" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	CheckResourceIDs.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_de"

USERDEP__CRYPT="CrypTool.rc"	
# Begin Custom Build - Checking CrypTool.rc and $(InputPath) (->CheckResourceIDs.*)
InputPath=.\CrypToolPopupMenuIDs.txt

"CheckResourceIDs.log" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	CheckResourceIDs.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "CrypTool - Win32 Release_en"

USERDEP__CRYPT="CrypTool.rc"	
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

SOURCE=.\CrypToolView.cpp
# End Source File
# Begin Source File

SOURCE=.\CrypToolView.h
# End Source File
# Begin Source File

SOURCE=.\CrypToolVolRen.cpp
# End Source File
# Begin Source File

SOURCE=.\CrypToolVolRen.h
# End Source File
# Begin Source File

SOURCE=..\libVolRen\CVector.cpp
# End Source File
# Begin Source File

SOURCE=..\libVolRen\CVector.h
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\Data.cpp
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\Data.h
# End Source File
# Begin Source File

SOURCE=.\DefinesForSignatureAttack.h
# End Source File
# Begin Source File

SOURCE=.\res\DerEinstiegInCrypTool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DerEinstiegInCrypTool_de.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dh_arrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dh_gapfi.bmp
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

SOURCE=.\DiffieHellmanButtonControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DiffieHellmanButtonControl.h
# End Source File
# Begin Source File

SOURCE=.\DiffieHellmanLogFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DiffieHellmanLogFile.h
# End Source File
# Begin Source File

SOURCE=.\DiffieHellmanParty.cpp
# End Source File
# Begin Source File

SOURCE=.\DiffieHellmanParty.h
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

SOURCE=.\DlgADFGVX.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgADFGVX.h
# End Source File
# Begin Source File

SOURCE=.\DlgAdfgvxIntro.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAdfgvxIntro.h
# End Source File
# Begin Source File

SOURCE=.\DlgAdfgvxManual.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAdfgvxManual.h
# End Source File
# Begin Source File

SOURCE=.\DlgASN1PSEPINPrompt.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgASN1PSEPINPrompt.h
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

SOURCE=.\DlgAutoSubstitutionAnalysis.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAutoSubstitutionAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\DlgAutoSubstitutionAnalysisAlgorithmChoice.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAutoSubstitutionAnalysisAlgorithmChoice.h
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

SOURCE=.\DlgCrtAstronomy.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCrtAstronomy.h
# End Source File
# Begin Source File

SOURCE=.\DlgCrtSecretSharing.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCrtSecretSharing.h
# End Source File
# Begin Source File

SOURCE=.\DlgCrtSecretSharing_Facts.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCrtSecretSharing_Facts.h
# End Source File
# Begin Source File

SOURCE=.\DlgCrtSecretSharing_Info.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCrtSecretSharing_Info.h
# End Source File
# Begin Source File

SOURCE=.\DlgCrtSecretSharing_Log.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCrtSecretSharing_Log.h
# End Source File
# Begin Source File

SOURCE=.\DlgCrtSecretSharingOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCrtSecretSharingOptions.h
# End Source File
# Begin Source File

SOURCE=.\DlgCrtTransformation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCrtTransformation.h
# End Source File
# Begin Source File

SOURCE=.\DlgDemoRSAKeyGeneration.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDemoRSAKeyGeneration.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanCreateSharedKey.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanCreateSharedKey.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanExchangeSharedKeys.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanExchangeSharedKeys.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanFinalInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanFinalInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanGenerateFinalKey.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanGenerateFinalKey.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanIntro.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanIntro.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanKeyInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanKeyInformation.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanPublicParameters.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanPublicParameters.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanSecretInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanSecretInput.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanSetPublicParameters.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanSetPublicParameters.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanSetSecrets.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanSetSecrets.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanVisualization.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiffieHellmanVisualization.h
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

SOURCE=.\DlgFileProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFileProperties.h
# End Source File
# Begin Source File

SOURCE=.\DlgFindAndReplace.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFindAndReplace.h
# End Source File
# Begin Source File

SOURCE=.\DlgFurtherOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFurtherOptions.h
# End Source File
# Begin Source File

SOURCE=.\DlgGeneratePrime.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGeneratePrime.h
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

SOURCE=.\DlgHMAC.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHMAC.h
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

SOURCE=.\DlgKeyHexFixedLen.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKeyHexFixedLen.h
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

SOURCE=.\DlgKeyPermutationInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKeyPermutationInfo.h
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

SOURCE=.\DlgMonSubst.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMonSubst.h
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

SOURCE=.\DlgOptionsAutoSubstitutionAnalysis.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsAutoSubstitutionAnalysis.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsRSADemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsRSADemo.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsSignatureAttack.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsSignatureAttack.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsStartoptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsStartoptions.h
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

SOURCE=.\DlgRot13Caesar.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRot13Caesar.h
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

SOURCE=.\DlgSideChannelAttackVisualizationHE.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHE.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEAlice.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEAlice.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEAttackCycle.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEAttackCycle.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEBob.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEBob.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEFinished.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEFinished.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEIntroduction.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEIntroduction.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEMessageInterception.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEMessageInterception.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEMessageTransmission.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEMessageTransmission.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEPreparations.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEPreparations.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEPreparationsRequest1.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEPreparationsRequest1.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEPreparationsRequest2.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEPreparationsRequest2.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEPreparationsRequest3.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEPreparationsRequest3.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEPSEPINPrompt.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEPSEPINPrompt.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEReport.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHEReport.h
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHETrudy.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSideChannelAttackVisualizationHETrudy.h
# End Source File
# Begin Source File

SOURCE=.\DlgSigAttModificDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSigAttModificDemo.h
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

SOURCE=.\DlgSignatureAttack.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSignatureAttack.h
# End Source File
# Begin Source File

SOURCE=.\DlgSignatureDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSignatureDemo.h
# End Source File
# Begin Source File

SOURCE=.\DlgSolitaire.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSolitaire.h
# End Source File
# Begin Source File

SOURCE=.\DlgSolitaireAnalyse.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSolitaireAnalyse.h
# End Source File
# Begin Source File

SOURCE=.\DlgStatisticsSignatureAttack.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStatisticsSignatureAttack.h
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

SOURCE=.\DocumentForHashing.h
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

SOURCE=.\ErrorcodesForSignatureAttack.h
# End Source File
# Begin Source File

SOURCE=.\FactorHint.cpp
# End Source File
# Begin Source File

SOURCE=.\FactorHint.h
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

SOURCE=.\res\DHBitmaps\bmps\GapFiller.bmp
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

SOURCE=.\res\gif2.bin
# End Source File
# Begin Source File

SOURCE=.\res\gif3.bin
# End Source File
# Begin Source File

SOURCE=.\res\gif4.bin
# End Source File
# Begin Source File

SOURCE=.\HashingOperations.cpp
# End Source File
# Begin Source File

SOURCE=.\HashingOperations.h
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

SOURCE=.\HexEditBase.cpp
# End Source File
# Begin Source File

SOURCE=.\HexEditBase.h
# End Source File
# Begin Source File

SOURCE=.\HexEditCtrlDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\HexEditCtrlDoc.h
# End Source File
# Begin Source File

SOURCE=.\HexEditCtrlView.cpp
# End Source File
# Begin Source File

SOURCE=.\HexEditCtrlView.h
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

SOURCE=.\res\hybrid_b.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hybrid_speichern_links.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hybrid_speichern_rechts.bmp
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

SOURCE=.\res\DHBitmaps\bmps\Key_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Key_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Key_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Key_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Key_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Key_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Key_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Key_X.bmp
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

SOURCE=.\Mac.h
# End Source File
# Begin Source File

SOURCE=.\res\magnify.cur
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\MainBackground.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\MainBackground.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\MainBackground.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\MainBackground.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\MakeHtmlHelp.bat
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

SOURCE=..\OpenSSL\md2.h
# End Source File
# Begin Source File

SOURCE=..\OpenSSL\md4.h
# End Source File
# Begin Source File

SOURCE=..\OpenSSL\md5.h
# End Source File
# Begin Source File

SOURCE=.\res\minifwnd.bmp
# End Source File
# Begin Source File

SOURCE=.\ModifiedDocument_Attachments.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifiedDocument_Attachments.h
# End Source File
# Begin Source File

SOURCE=.\ModifiedDocument_Blanks.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifiedDocument_Blanks.h
# End Source File
# Begin Source File

SOURCE=.\ModifiedDocumentForHashing.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifiedDocumentForHashing.h
# End Source File
# Begin Source File

SOURCE=.\MonoSubstCracker.cpp
# End Source File
# Begin Source File

SOURCE=.\MonoSubstCracker.h
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

SOURCE=.\NTLExpPars.cpp
# End Source File
# Begin Source File

SOURCE=.\NTLExpPars.h
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

SOURCE=.\OpenGL.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenGL.h
# End Source File
# Begin Source File

SOURCE=.\OpenGLDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenGLDoc.h
# End Source File
# Begin Source File

SOURCE=.\OpenGLView.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenGLView.h
# End Source File
# Begin Source File

SOURCE=..\OpenSSL\opensslconf.h
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

SOURCE=.\OptionsForSignatureAttack.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsForSignatureAttack.h
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

SOURCE=.\res\Bitmaps\Oval1_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval1_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval1_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval1_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval1_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval1_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval1_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval1_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval2_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval2_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Oval2_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval2_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval2_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Oval2_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval2_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval2_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval2_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval2_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval2_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval2_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval2_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval2_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Oval2_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Bitmaps_en\Oval2_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval2_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval2_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Oval2_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Oval2_X_U.bmp
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\Packet.cpp
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\Packet.h
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

SOURCE=.\PictureEx.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureEx.h
# End Source File
# Begin Source File

SOURCE=.\PictureExLoop.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureExLoop.h
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

SOURCE=.\res\Bitmaps\Raute1_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute1_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute1_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute1_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute1_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute1_B_U.bmp
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

SOURCE=.\res\Bitmaps\Raute1_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute1_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute2_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute2_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute2_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute2_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute2_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute2_B_U.bmp
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

SOURCE=.\res\Bitmaps\Raute2_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute2_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute3_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute3_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute3_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute3_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute3_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute3_B_U.bmp
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

SOURCE=.\res\Bitmaps\Raute3_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute3_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute4_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute4_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute4_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute4_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute4_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute4_B_U.bmp
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

SOURCE=.\res\Bitmaps\Raute4_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute4_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute5_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute5_B_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute5_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute5_B_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Raute5_B_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute5_B_U.bmp
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

SOURCE=.\res\Bitmaps\Raute5_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Raute5_X_U.bmp
# End Source File
# Begin Source File

SOURCE=..\AES\RC6\rc6.c
# End Source File
# Begin Source File

SOURCE=..\AES\RC6\rc6.h
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck1_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck1_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck1_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck1_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck1_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck1_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck1_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck1_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck1_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck1_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck1_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck1_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck1_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck1_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck2_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck2_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck2_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck2_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck2_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck2_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck2_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck2_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck2_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck2_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck2_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck2_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Rechteck2_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Rechteck2_X_U.bmp
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ResultsOfSignatureAttack.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultsOfSignatureAttack.h
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

SOURCE=..\OpenSSL\ripemd.h
# End Source File
# Begin Source File

SOURCE=.\RSABloemerMayDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\rsabloemermaydlg.h
# End Source File
# Begin Source File

SOURCE=.\RSAFactorHintDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\rsafactorhintdlg.h
# End Source File
# Begin Source File

SOURCE=.\rsastereotypedmsgdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\rsastereotypedmsgdlg.h
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

SOURCE=.\res\SCABitmaps\gifs\sca_ab_arrow_failure.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\gifs\sca_ab_arrow_failure.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\gifs\sca_ab_arrow_interception.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\gifs\sca_ab_arrow_interception.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\gifs\sca_ab_arrow_static.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\gifs\sca_ab_arrow_static.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\gifs\sca_ab_arrow_success.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\gifs\sca_ab_arrow_success.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\gifs\sca_ab_arrow_transmission.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\gifs\sca_ab_arrow_transmission.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\gifs\sca_ab_arrow_transmission_trudybob.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\gifs\sca_ab_arrow_transmission_trudybob.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\sca_alice_small.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\sca_alice_small.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\sca_allremainingsteps_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\sca_allremainingsteps_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\sca_allremainingsteps_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\sca_allremainingsteps_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\sca_bob_small.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\sca_bob_small.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\sca_gapfiller.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\sca_gapfiller.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sca_green_success.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\sca_lights.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\gifs\sca_lights.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\gifs\sca_lights.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\gifs\sca_lights_green.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\gifs\sca_lights_green.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\gifs\sca_lights_red.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\gifs\sca_lights_red.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\sca_nextstep_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\sca_nextstep_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\sca_nextstep_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\sca_nextstep_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sca_red_error.gif
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps\bmps\sca_trudy_small.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SCABitmaps_en\bmps\sca_trudy_small.bmp
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\Scenario.cpp
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\Scenario.h
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\ScenarioObject.cpp
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\ScenarioObject.h
# End Source File
# Begin Source File

SOURCE=.\ScintillaDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ScintillaDoc.h
# End Source File
# Begin Source File

SOURCE=.\ScintillaView.cpp
# End Source File
# Begin Source File

SOURCE=.\ScintillaView.h
# End Source File
# Begin Source File

SOURCE=.\ScintillaWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ScintillaWnd.h
# End Source File
# Begin Source File

SOURCE=.\res\sechseck.bmp
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

SOURCE=.\res\Bitmaps\Sechseck1_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck1_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck1_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck1_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck1_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck1_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck1_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck1_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck1_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck1_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck1_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck1_R_U.bmp
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

SOURCE=.\res\Bitmaps\Sechseck2_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck2_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck2_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck2_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck2_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck2_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck2_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck2_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck2_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck2_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck2_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck2_R_U.bmp
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

SOURCE=.\res\Bitmaps\Sechseck3_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck3_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck3_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck3_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck3_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck3_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck3_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck3_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck3_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck3_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck3_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck3_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Sechseck3_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps_en\Sechseck3_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Secret_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Secret_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Secret_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Secret_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Secret_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Secret_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Secret_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Secret_G_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Secret_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Secret_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Secret_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Secret_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Secret_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Secret_R_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Secret_R_X.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Secret_R_X.bmp
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

SOURCE=..\OpenSSL\sha.h
# End Source File
# Begin Source File

SOURCE=.\SideChannelAttack.cpp
# End Source File
# Begin Source File

SOURCE=.\SideChannelAttack.h
# End Source File
# Begin Source File

SOURCE=.\SideChannelAttackButtonControl.cpp
# End Source File
# Begin Source File

SOURCE=.\SideChannelAttackButtonControl.h
# End Source File
# Begin Source File

SOURCE=.\SignatureAttack.cpp
# End Source File
# Begin Source File

SOURCE=.\SignatureAttack.h
# End Source File
# Begin Source File

SOURCE=.\SignatureAttackMFC.cpp
# End Source File
# Begin Source File

SOURCE=.\SignatureAttackMFC.h
# End Source File
# Begin Source File

SOURCE=.\SizingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SizingDialog.h
# End Source File
# Begin Source File

SOURCE=.\Solitaire.cpp
# End Source File
# Begin Source File

SOURCE=.\Solitaire.h
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

SOURCE=.\res\DHBitmaps\bmps\Step_1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Step_1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Step_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Step_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Step_3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Step_3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Step_4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Step_4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\Step_5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps_en\bmps\Step_5.bmp
# End Source File
# Begin Source File

SOURCE=.\StereotypedAttack.cpp
# End Source File
# Begin Source File

SOURCE=.\StereotypedAttack.h
# End Source File
# Begin Source File

SOURCE=.\StreamToVolume.cpp
# End Source File
# Begin Source File

SOURCE=.\StreamToVolume.h
# End Source File
# Begin Source File

SOURCE=.\res\DHBitmaps\bmps\test.gif
# End Source File
# Begin Source File

SOURCE=.\res\TEST_F_D.bmp
# End Source File
# Begin Source File

SOURCE=.\TimeCalculation.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeCalculation.h
# End Source File
# Begin Source File

SOURCE=.\res\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=..\libVolRen\Trapezeditor.cpp
# End Source File
# Begin Source File

SOURCE=..\libVolRen\Trapezeditor.h
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

SOURCE=.\res\Bitmaps\Viereck1_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck1_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck1_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck1_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck1_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck1_R_U.bmp
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

SOURCE=.\res\Bitmaps\Viereck1_X_U.bmp
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

SOURCE=.\res\Bitmaps\Viereck2_G_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck2_G_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck2_G_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck2_R_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck2_R_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\Viereck2_R_U.bmp
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

SOURCE=.\res\Bitmaps\Viereck2_X_U.bmp
# End Source File
# Begin Source File

SOURCE=..\libVolRen\Volume.cpp
# End Source File
# Begin Source File

SOURCE=..\libVolRen\Volume.h
# End Source File
# Begin Source File

SOURCE=..\libVolRen\VolumeUtilities.cpp
# End Source File
# Begin Source File

SOURCE=..\libVolRen\VolumeUtilities.h
# End Source File
# Begin Source File

SOURCE=.\res\white.bmp
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\Wire.cpp
# End Source File
# Begin Source File

SOURCE=..\ChallengeResponse\Wire.h
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

SOURCE=.\ZZ_helpers.cpp
# End Source File
# Begin Source File

SOURCE=.\ZZ_helpers.h
# End Source File
# Begin Source File

SOURCE=.\zzgen.cpp
# End Source File
# Begin Source File

SOURCE=.\zzgen.h
# End Source File
# Begin Source File

SOURCE=.\ZZXY.cpp
# End Source File
# Begin Source File

SOURCE=.\ZZXY.h
# End Source File
# End Target
# End Project
