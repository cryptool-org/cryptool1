# Microsoft Developer Studio Project File - Name="MFC-ZahlenHai" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MFC-ZahlenHai - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "MFC-ZahlenHai.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "MFC-ZahlenHai.mak" CFG="MFC-ZahlenHai - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "MFC-ZahlenHai - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE "MFC-ZahlenHai - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MFC-ZahlenHai - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_MBCS" /Yu"stdafx.h" /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_MBCS" /Yu"stdafx.h" /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x407 /i "$(IntDir)" /d "_DEBUG"
# ADD RSC /l 0x407 /i "$(IntDir)" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:IX86 /out:"Debug/Zahlenhai.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MFC-ZahlenHai - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /Zi /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W4 /GX /Zi /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x407 /i "$(IntDir)" /d "NDEBUG"
# ADD RSC /l 0x407 /i "$(IntDir)" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /opt:ref /opt:icf
# ADD LINK32 /nologo /subsystem:windows /debug /machine:IX86 /out:"Release/Zahlenhai.exe" /pdbtype:sept /opt:ref /opt:icf
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "MFC-ZahlenHai - Win32 Debug"
# Name "MFC-ZahlenHai - Win32 Release"
# Begin Group "Quelldateien"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=.\ColorButton.cpp
# End Source File
# Begin Source File

SOURCE=.\EvoZahlenHai.cpp
DEP_CPP_EVOZA=\
	".\EvoZahlenHai.h"\
	".\Msg.h"\
	".\stdafx.h"\
	".\zahl.h"\
	
# End Source File
# Begin Source File

SOURCE=".\MFC-ZahlenHai.cpp"
DEP_CPP_MFC_Z=\
	".\EvoZahlenHai.h"\
	".\HeaderCtrlExt.h"\
	".\MFC-ZahlenHai.h"\
	".\MFC-ZahlenHaiDlg.h"\
	".\Msg.h"\
	".\stdafx.h"\
	".\WBButton.h"\
	".\zahl.h"\
	".\ZahlenHaiOptionen.h"\
	
# End Source File
# Begin Source File

SOURCE=".\MFC-ZahlenHaiDlg.cpp"
DEP_CPP_MFC_ZA=\
	".\EvoZahlenHai.h"\
	".\HeaderCtrlExt.h"\
	".\MFC-ZahlenHai.h"\
	".\MFC-ZahlenHaiDlg.h"\
	".\Msg.h"\
	".\stdafx.h"\
	".\WBButton.h"\
	".\zahl.h"\
	".\ZahlenHaiOptionen.h"\
	
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\Msg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "MFC-ZahlenHai - Win32 Debug"

# ADD CPP /nologo /GX /Yc"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "MFC-ZahlenHai - Win32 Release"

# ADD CPP /nologo /GX /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\zahl.cpp
DEP_CPP_ZAHL_=\
	".\EvoZahlenHai.h"\
	".\Msg.h"\
	".\stdafx.h"\
	".\zahl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\ZahlenHaiOptionen.cpp
DEP_CPP_ZAHLE=\
	".\EvoZahlenHai.h"\
	".\HeaderCtrlExt.h"\
	".\MFC-ZahlenHai.h"\
	".\MFC-ZahlenHaiDlg.h"\
	".\Msg.h"\
	".\stdafx.h"\
	".\WBButton.h"\
	".\zahl.h"\
	".\ZahlenHaiOptionen.h"\
	
# End Source File
# End Group
# Begin Group "Headerdateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# Begin Source File

SOURCE=.\ColorButton.h
# End Source File
# Begin Source File

SOURCE=.\EvoZahlenHai.h
# End Source File
# Begin Source File

SOURCE=".\MFC-ZahlenHai.h"
# End Source File
# Begin Source File

SOURCE=".\MFC-ZahlenHaiDlg.h"
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\zahl.h
# End Source File
# Begin Source File

SOURCE=.\ZahlenHaiOptionen.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx"
# Begin Source File

SOURCE=.\Bilder\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\Bilder\hai01.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=".\res\MFC-ZahlenHai.ico"
# End Source File
# Begin Source File

SOURCE=".\MFC-ZahlenHai.rc"
# End Source File
# Begin Source File

SOURCE=".\res\MFC-ZahlenHai.rc2"
# End Source File
# Begin Source File

SOURCE=".\Bilder\muschel-rot-5.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=".\res\MFC-ZahlenHai.manifest"
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
