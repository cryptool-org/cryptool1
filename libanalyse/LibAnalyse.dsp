# Microsoft Developer Studio Project File - Name="LibAnalyse" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LibAnalyse - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "LibAnalyse.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "LibAnalyse.mak" CFG="LibAnalyse - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "LibAnalyse - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "LibAnalyse - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LibAnalyse - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LibAnalyse - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "LibAnalyse - Win32 Release"
# Name "LibAnalyse - Win32 Debug"
# Begin Source File

SOURCE=.\analyse.h
# End Source File
# Begin Source File

SOURCE=.\Array.h
# End Source File
# Begin Source File

SOURCE=.\Array2.h
# End Source File
# Begin Source File

SOURCE=.\Array3.h
# End Source File
# Begin Source File

SOURCE=.\Builtin.h
# End Source File
# Begin Source File

SOURCE=.\Chi2.cpp
# End Source File
# Begin Source File

SOURCE=.\Chi2.h
# End Source File
# Begin Source File

SOURCE=.\Cipher.cpp
# End Source File
# Begin Source File

SOURCE=.\Cipher.h
# End Source File
# Begin Source File

SOURCE=.\Converter.cpp
# End Source File
# Begin Source File

SOURCE=.\Converter.h
# End Source File
# Begin Source File

SOURCE=.\Correlation.h
# End Source File
# Begin Source File

SOURCE=.\Correlation2.h
# End Source File
# Begin Source File

SOURCE=.\Default.h
# End Source File
# Begin Source File

SOURCE=.\Des.cpp
# End Source File
# Begin Source File

SOURCE=.\Des.h
# End Source File
# Begin Source File

SOURCE=.\FFT.CPP
# End Source File
# Begin Source File

SOURCE=.\Format.h
# End Source File
# Begin Source File

SOURCE=.\Format2.h
# End Source File
# Begin Source File

SOURCE=.\FreqTable.cpp
# End Source File
# Begin Source File

SOURCE=.\FreqTable.h
# End Source File
# Begin Source File

SOURCE=.\Iterator.h
# End Source File
# Begin Source File

SOURCE=.\Iterator2.h
# End Source File
# Begin Source File

SOURCE=.\la_ostream.h
# End Source File
# Begin Source File

SOURCE=.\la_string.h
# End Source File
# Begin Source File

SOURCE=.\LFSR.CPP
# End Source File
# Begin Source File

SOURCE=.\LFSR.H
# End Source File
# Begin Source File

SOURCE=.\MYMATH.CPP
# End Source File
# Begin Source File

SOURCE=.\MYMATH.H
# End Source File
# Begin Source File

SOURCE=.\mytemplates.alt.h
# End Source File
# Begin Source File

SOURCE=.\mytemplates.h
# End Source File
# Begin Source File

SOURCE=.\NGram.cpp
# End Source File
# Begin Source File

SOURCE=.\NGram.h
# End Source File
# Begin Source File

SOURCE=.\OStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Permutation.cpp
# End Source File
# Begin Source File

SOURCE=.\Permutation.h
# End Source File
# Begin Source File

SOURCE=.\REGEX.H
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SBox.cpp
# End Source File
# Begin Source File

SOURCE=.\SBox.h
# End Source File
# Begin Source File

SOURCE=.\SortedArray.h
# End Source File
# Begin Source File

SOURCE=.\SortPair.h
# End Source File
# Begin Source File

SOURCE=.\StaticObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\STDINC.H
# End Source File
# Begin Source File

SOURCE=.\String.cpp
# End Source File
# Begin Source File

SOURCE=.\SubArray.h
# End Source File
# Begin Source File

SOURCE=.\Symbol.cpp
# End Source File
# Begin Source File

SOURCE=.\Symbol.h
# End Source File
# Begin Source File

SOURCE=.\SymbolArray.cpp
# End Source File
# Begin Source File

SOURCE=.\SymbolArray.h
# End Source File
# End Target
# End Project
