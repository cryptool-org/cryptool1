# Microsoft Developer Studio Project File - Name="LibEc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LibEc - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "LibEc.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "LibEc.mak" CFG="LibEc - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "LibEc - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "LibEc - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LibEc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\Secude" /I "include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\EcBibV2.lib"

!ELSEIF  "$(CFG)" == "LibEc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /I "..\Secude" /I "include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\EcBibV2D.lib"

!ENDIF 

# Begin Target

# Name "LibEc - Win32 Release"
# Name "LibEc - Win32 Debug"
# Begin Source File

SOURCE=.\sources\ECsecude.c
# End Source File
# Begin Source File

SOURCE=.\include\ECsecude.h
# End Source File
# Begin Source File

SOURCE=.\sources\Ecssa.c
# End Source File
# Begin Source File

SOURCE=.\include\ECSSA.H
# End Source File
# Begin Source File

SOURCE=.\sources\EMSA1.C
# End Source File
# Begin Source File

SOURCE=.\include\EMSA1.H
# End Source File
# Begin Source File

SOURCE=.\sources\s_bithdl.c
# End Source File
# Begin Source File

SOURCE=.\include\s_bithdl.h
# End Source File
# Begin Source File

SOURCE=.\sources\s_ecconv.c
# End Source File
# Begin Source File

SOURCE=.\include\s_ecconv.h
# End Source File
# Begin Source File

SOURCE=.\sources\s_ecDSA.c
# End Source File
# Begin Source File

SOURCE=.\include\s_ecDSA.h
# End Source File
# Begin Source File

SOURCE=.\include\s_ecFp.h
# End Source File
# Begin Source File

SOURCE=.\sources\s_ecmath.c
# End Source File
# Begin Source File

SOURCE=.\include\s_ecmath.h
# End Source File
# Begin Source File

SOURCE=.\sources\s_ecNR.c
# End Source File
# Begin Source File

SOURCE=.\include\s_ecNR.h
# End Source File
# Begin Source File

SOURCE=.\sources\s_ecpara.c
# End Source File
# Begin Source File

SOURCE=.\sources\s_ecparp.c
# End Source File
# Begin Source File

SOURCE=.\sources\s_ecpcur.c
# End Source File
# Begin Source File

SOURCE=.\sources\s_ecppta.c
# End Source File
# Begin Source File

SOURCE=.\sources\s_ecpptc.c
# End Source File
# Begin Source File

SOURCE=.\sources\s_ecpptp.c
# End Source File
# Begin Source File

SOURCE=.\sources\s_ecprpt.c
# End Source File
# Begin Source File

SOURCE=.\sources\s_ecpX9c.c
# End Source File
# Begin Source File

SOURCE=.\sources\s_ecvali.c
# End Source File
# Begin Source File

SOURCE=.\include\s_ecvali.h
# End Source File
# Begin Source File

SOURCE=.\sources\s_prng.c
# End Source File
# Begin Source File

SOURCE=.\include\s_prng.h
# End Source File
# End Target
# End Project
