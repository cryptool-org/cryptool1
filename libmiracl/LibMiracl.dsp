# Microsoft Developer Studio Project File - Name="LibMiracl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LibMiracl - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "LibMiracl.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "LibMiracl.mak" CFG="LibMiracl - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "LibMiracl - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "LibMiracl - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\libmiracl\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../LibMiracl/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "LibMiracl - Win32 Release"
# Name "LibMiracl - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\source\BIG.CPP
# End Source File
# Begin Source File

SOURCE=.\source\MRAES.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRALLOC.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRARTH0.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRARTH1.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRARTH2.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRARTH3.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRBRICK.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRBUILD.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRCOMBA.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRCORE.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRCRT.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRCURVE.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRDOUBLE.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MREBRICK.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRECGF2M.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRFAST.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRFLASH.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRFLSH1.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRFLSH2.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRFLSH3.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRFLSH4.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRFRND.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRGCD.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRIO1.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRIO2.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRJACK.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRKCM.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRLUCAS.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRMONTY.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\mrmuldv.c

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRPI.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRPOWER.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRPRIME.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRRAND.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRROUND.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRSCRT.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRSHS.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRSHS256.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRSHS512.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRSMALL.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRSTRONG.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\MRXGCD.C

!IF  "$(CFG)" == "LibMiracl - Win32 Release"

!ELSEIF  "$(CFG)" == "LibMiracl - Win32 Debug"

# ADD CPP /I "..\include"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\BIG.H
# End Source File
# End Group
# End Target
# End Project
