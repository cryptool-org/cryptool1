# Microsoft Developer Studio Project File - Name="shellext" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=shellext - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "SHELLEXT.MAK".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "SHELLEXT.MAK" CFG="shellext - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "shellext - Win32 Release" (basierend auf  "Win32 (x86) External Target")
!MESSAGE "shellext - Win32 Debug" (basierend auf  "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "shellext - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "shellext.dll"
# PROP Bsc_Name "shellext.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "shellext - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "makefile.exe"
# PROP BASE Bsc_Name "makefile.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "shellext.dll"
# PROP Bsc_Name "shellext.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "shellext - Win32 Release"
# Name "shellext - Win32 Debug"

!IF  "$(CFG)" == "shellext - Win32 Release"

!ELSEIF  "$(CFG)" == "shellext - Win32 Debug"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CTXMENU.CPP
# End Source File
# Begin Source File

SOURCE=.\ICONHDLR.CPP
# End Source File
# Begin Source File

SOURCE=.\PROPSHET.CPP
# End Source File
# Begin Source File

SOURCE=.\SHELLEXT.CPP
# End Source File
# Begin Source File

SOURCE=.\SHELLEXT.DEF
# End Source File
# Begin Source File

SOURCE=.\SHEXINIT.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PRIV.H
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.H
# End Source File
# Begin Source File

SOURCE=.\SHELLEXT.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GAK.ICO
# End Source File
# Begin Source File

SOURCE=.\GAK2.ICO
# End Source File
# Begin Source File

SOURCE=.\GAK3.ICO
# End Source File
# Begin Source File

SOURCE=.\SHELLEXT.RC
# End Source File
# End Group
# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# End Target
# End Project
