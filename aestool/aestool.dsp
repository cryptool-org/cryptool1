# Microsoft Developer Studio Project File - Name="aestool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=aestool - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "aestool.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "aestool.mak" CFG="aestool - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "aestool - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "aestool - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE "aestool - Win32 Release_aes_de" (basierend auf  "Win32 (x86) Application")
!MESSAGE "aestool - Win32 Release_aes_en" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "aestool - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /incremental:yes
# Begin Special Build Tool
TargetPath=.\Release\aestool.exe
SOURCE="$(InputPath)"
PostBuild_Desc=change windows subsystem to console
PostBuild_Cmds=editbin /subsystem:console $(TargetPath)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "aestool - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\CrypTool\Debug/aestool.exe" /pdbtype:sept
# Begin Special Build Tool
TargetPath=\data\src\CrypTool\source\CrypTool\Debug\aestool.exe
SOURCE="$(InputPath)"
PostBuild_Desc=change windows subsystem to console
PostBuild_Cmds=editbin /subsystem:console $(TargetPath)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "aestool - Win32 Release_aes_de"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "aestool___Win32_Release_aes_de"
# PROP BASE Intermediate_Dir "aestool___Win32_Release_aes_de"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release_aes_de"
# PROP Intermediate_Dir "..\Release_aes_de"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_DEU"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"../CrypTool/Release/aestool.exe"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../Release_de/aestool.exe"
# SUBTRACT LINK32 /incremental:yes
# Begin Special Build Tool
TargetPath=\data\src\CrypTool\source\Release_de\aestool.exe
SOURCE="$(InputPath)"
PostBuild_Desc=change windows subsystem to console
PostBuild_Cmds=editbin /subsystem:console $(TargetPath)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "aestool - Win32 Release_aes_en"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "aestool___Win32_Release_aes_en"
# PROP BASE Intermediate_Dir "aestool___Win32_Release_aes_en"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release_aes_en"
# PROP Intermediate_Dir "..\Release_aes_en"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_DEU"
# ADD RSC /l 0x809 /d "NDEBUG" /d "AFX_RESOURCE_DLL" /d "AFX_TARG_ENG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"../CrypTool/Release/aestool.exe"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../Release_en/aestool.exe"
# SUBTRACT LINK32 /incremental:yes
# Begin Special Build Tool
TargetPath=\data\src\CrypTool\source\Release_en\aestool.exe
SOURCE="$(InputPath)"
PostBuild_Desc=change windows subsystem to console
PostBuild_Cmds=editbin /subsystem:console $(TargetPath)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "aestool - Win32 Release"
# Name "aestool - Win32 Debug"
# Name "aestool - Win32 Release_aes_de"
# Name "aestool - Win32 Release_aes_en"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\aestool.cpp
# End Source File
# Begin Source File

SOURCE=.\aestool.rc
# End Source File
# Begin Source File

SOURCE=.\aestoolcrypto.cpp
# End Source File
# Begin Source File

SOURCE=.\aestoolDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Help.cpp
# End Source File
# Begin Source File

SOURCE=.\HexEdit1.cpp
# End Source File
# Begin Source File

SOURCE=".\rijndael-alg-fst.c"
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=".\rijndael-api-fst.c"
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\aestool.h
# End Source File
# Begin Source File

SOURCE=.\aestoolcrypto.h
# End Source File
# Begin Source File

SOURCE=.\aestoolDlg.h
# End Source File
# Begin Source File

SOURCE=.\Help.h
# End Source File
# Begin Source File

SOURCE=.\HexEdit1.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=".\rijndael-alg-fst.h"
# End Source File
# Begin Source File

SOURCE=".\rijndael-api-fst.h"
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\3dcheck.bmp
# End Source File
# Begin Source File

SOURCE=.\res\95check.bmp
# End Source File
# Begin Source File

SOURCE=.\res\aestool.ico
# End Source File
# Begin Source File

SOURCE=.\res\aestool.rc2
# End Source File
# Begin Source File

SOURCE=.\res\help.cur
# End Source File
# Begin Source File

SOURCE=.\res\minifwnd.bmp
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

SOURCE=.\res\sarrows.cur
# End Source File
# Begin Source File

SOURCE=.\res\splith.cur
# End Source File
# Begin Source File

SOURCE=.\res\splitv.cur
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
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
