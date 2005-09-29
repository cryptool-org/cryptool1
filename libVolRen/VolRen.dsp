# Microsoft Developer Studio Project File - Name="VolRen" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=VolRen - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "VolRen.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "VolRen.mak" CFG="VolRen - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "VolRen - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VolRen - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VolRen - Win32 Release"

# PROP BASE Use_MFC 6
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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include\glh" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 opengl32.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "VolRen - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include\glh" /D "VOLREN_EXPORTS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib /nologo /subsystem:windows /dll /pdb:"..\CrypTool\Debug\VolRen.pdb" /debug /machine:I386 /def:".\VolRen.def" /out:"..\CrypTool\Debug\VolRen.dll" /implib:"..\CrypTool\Debug\VolRen.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "VolRen - Win32 Release"
# Name "VolRen - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ArcBall.cpp

!IF  "$(CFG)" == "VolRen - Win32 Release"

# ADD CPP /I "D:\SDK\NV_OpenGL\include\glh" /D "VOLREN_EXPORTS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "VolRen - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CMatrix.cpp

!IF  "$(CFG)" == "VolRen - Win32 Release"

# ADD CPP /I "D:\SDK\NV_OpenGL\include\glh" /D "VOLREN_EXPORTS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "VolRen - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CPosition.cpp

!IF  "$(CFG)" == "VolRen - Win32 Release"

# ADD CPP /I "D:\SDK\NV_OpenGL\include\glh" /D "VOLREN_EXPORTS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "VolRen - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CQuaternion.cpp

!IF  "$(CFG)" == "VolRen - Win32 Release"

# ADD CPP /I "D:\SDK\NV_OpenGL\include\glh" /D "VOLREN_EXPORTS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "VolRen - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CVector.cpp

!IF  "$(CFG)" == "VolRen - Win32 Release"

# ADD CPP /I "D:\SDK\NV_OpenGL\include\glh" /D "VOLREN_EXPORTS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "VolRen - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EditorDialog.cpp

!IF  "$(CFG)" == "VolRen - Win32 Release"

# ADD CPP /I "D:\SDK\NV_OpenGL\include\glh" /D "VOLREN_EXPORTS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "VolRen - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "VolRen - Win32 Release"

# ADD CPP /I "D:\SDK\NV_OpenGL\include\glh" /D "VOLREN_EXPORTS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "VolRen - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Trapezeditor.cpp
# End Source File
# Begin Source File

SOURCE=.\VolRen.cpp

!IF  "$(CFG)" == "VolRen - Win32 Release"

# ADD CPP /I "D:\SDK\NV_OpenGL\include\glh" /D "VOLREN_EXPORTS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "VolRen - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VolRen.def

!IF  "$(CFG)" == "VolRen - Win32 Release"

!ELSEIF  "$(CFG)" == "VolRen - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Volume.cpp

!IF  "$(CFG)" == "VolRen - Win32 Release"

# ADD CPP /I "D:\SDK\NV_OpenGL\include\glh" /D "VOLREN_EXPORTS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "VolRen - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VolumeRenderer.cpp

!IF  "$(CFG)" == "VolRen - Win32 Release"

# ADD CPP /I "D:\SDK\NV_OpenGL\include\glh" /D "VOLREN_EXPORTS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "VolRen - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VolumeUtilities.cpp

!IF  "$(CFG)" == "VolRen - Win32 Release"

# ADD CPP /I "D:\SDK\NV_OpenGL\include\glh" /D "VOLREN_EXPORTS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "VolRen - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ArcBall.h
# End Source File
# Begin Source File

SOURCE=.\CMatrix.h
# End Source File
# Begin Source File

SOURCE=.\CPosition.h
# End Source File
# Begin Source File

SOURCE=.\CQuaternion.h
# End Source File
# Begin Source File

SOURCE=.\CVector.h
# End Source File
# Begin Source File

SOURCE=.\EditorDialog.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Trapezeditor.h
# End Source File
# Begin Source File

SOURCE=.\Volume.h
# End Source File
# Begin Source File

SOURCE=.\VolumeRenderer.h
# End Source File
# Begin Source File

SOURCE=.\VolumeUtilities.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\VolRen.rc
# End Source File
# End Group
# End Target
# End Project
# Section VolRen : {977350AB-45D8-443D-A8BC-ABE09C33B105}
# 	2:5:Class:CGtTrapezEditor
# 	2:10:HeaderFile:gttrapezeditor.h
# 	2:8:ImplFile:gttrapezeditor.cpp
# End Section
# Section VolRen : {0641504A-4AFB-41B0-AFBD-1DFEBEF66857}
# 	2:5:Class:CTransFuncEditor
# 	2:10:HeaderFile:transfunceditor.h
# 	2:8:ImplFile:transfunceditor.cpp
# End Section
# Section VolRen : {F8120F9E-E8DC-4E87-A67B-DA8B958C8C8F}
# 	2:21:DefaultSinkHeaderFile:transfunceditor.h
# 	2:16:DefaultSinkClass:CTransFuncEditor
# End Section
# Section VolRen : {90393A34-2F31-48A4-9323-8CEC42C73954}
# 	2:21:DefaultSinkHeaderFile:gttrapezeditor.h
# 	2:16:DefaultSinkClass:CGtTrapezEditor
# End Section
