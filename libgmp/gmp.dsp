# Microsoft Developer Studio Project File - Name="gmp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=gmp - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "gmp.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "gmp.mak" CFG="gmp - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "gmp - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "gmp - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gmp - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/gmp.lib"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/gmpDebug.lib"

!ENDIF 

# Begin Target

# Name "gmp - Win32 Release"
# Name "gmp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\mpf\abs.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\abs.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\abs.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\add.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\add.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\add.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\add_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\add_n.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"
# ADD CPP /D "OPERATION_add_n"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"
# ADD CPP /D "OPERATION_add_n"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\add_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\add_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\addmul_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"
# ADD CPP /D "OPERATION_addmul_1"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"
# ADD CPP /D "OPERATION_addmul_1"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\and.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\aors.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\aorsmul.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\aorsmul_i.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\array_init.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\printf\asprintf.c
# End Source File
# Begin Source File

SOURCE=.\printf\asprntffuns.c
# End Source File
# Begin Source File

SOURCE=.\assert.c
# End Source File
# Begin Source File

SOURCE=.\mpn\generic\bdivmod.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\bin_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\bin_uiui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\canonicalize.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cdiv_q.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cdiv_q_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cdiv_qr.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cdiv_qr_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cdiv_r.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cdiv_r_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cdiv_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\ceilfloor.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cfdiv_q_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cfdiv_r_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\clear.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\clear.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\clear.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\clrbit.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\cmp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\cmp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\cmp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cmp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\cmp_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cmp_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\cmp_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\cmp_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cmp_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\cmp_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\cmp_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cmp_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cmpabs.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cmpabs_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cmpabs_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\com.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\compat.c
# End Source File
# Begin Source File

SOURCE=.\mpz\cong.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cong_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\cong_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\dc_divrem_n.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\div.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\div.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\div_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\div_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\dive_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\dive_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\diveby3.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\divegcd.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\divexact.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\divis.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\divis.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\divis_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\divis_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\divrem.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\divrem_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\divrem_2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\printf\doprnt.c
# End Source File
# Begin Source File

SOURCE=.\printf\doprntf.c
# End Source File
# Begin Source File

SOURCE=.\printf\doprnti.c
# End Source File
# Begin Source File

SOURCE=.\scanf\doscan.c
# End Source File
# Begin Source File

SOURCE=.\mpf\dump.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\dump.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\dump.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\eq.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\equal.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\errno.c
# End Source File
# Begin Source File

SOURCE=".\extract-dbl.c"
# End Source File
# Begin Source File

SOURCE=.\mpz\fac_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fdiv_q.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fdiv_q_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fdiv_qr.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fdiv_qr_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fdiv_r.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fdiv_r_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fdiv_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\fib2_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fib2_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fib_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\fits_sint.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fits_sint.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\fits_slong.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fits_slong.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\fits_sshort.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fits_sshort.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\fits_uint.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fits_uint.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\fits_ulong.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fits_ulong.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\fits_ushort.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\fits_ushort.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\printf\fprintf.c
# End Source File
# Begin Source File

SOURCE=.\scanf\fscanf.c
# End Source File
# Begin Source File

SOURCE=.\scanf\fscanffuns.c
# End Source File
# Begin Source File

SOURCE=.\mpn\generic\gcd.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\gcd.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\gcd_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\gcd_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\gcdext.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\gcdext.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\get_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\get_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\get_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\get_d_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\get_d_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\get_den.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\get_dfl_prec.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\get_num.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\get_prc.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\get_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\get_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\get_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\get_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\get_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\get_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\get_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\get_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\getlimbn.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\hamdist.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\hamdist.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\init.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\init.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\init.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\init2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\init2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\inp_raw.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\inp_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\inp_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\inp_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\insert-dbl.c"
# End Source File
# Begin Source File

SOURCE=.\mpf\int_p.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\inv.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\invert.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\ior.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\iset.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\iset.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\iset_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\iset_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\iset_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\iset_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\iset_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\iset_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\iset_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\iset_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\jacbase.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\jacobi.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\kronsz.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\kronuz.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\kronzs.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\kronzu.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\lcm.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\lcm_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\lshift.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\lucnum2_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\lucnum_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\md_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\memory.c
# End Source File
# Begin Source File

SOURCE=.\mpz\millerrabin.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\mod.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\mod_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\mod_34lsub1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\mode1o.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\mp_bases.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mp_bpl.c
# End Source File
# Begin Source File

SOURCE=.\mp_clz_tab.c
# End Source File
# Begin Source File

SOURCE=.\mp_minv_tab.c
# End Source File
# Begin Source File

SOURCE=.\mp_set_fns.c
# End Source File
# Begin Source File

SOURCE=.\mpf\mul.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\mul.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\mul.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\mul.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\mul_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\mul_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\mul_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\mul_basecase.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\mul_fft.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\mul_n.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\mul_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\mul_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\mul_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\n_pow_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\neg.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\neg.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\neg.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\nextprime.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\printf\obprintf.c
# End Source File
# Begin Source File

SOURCE=.\printf\obprntffuns.c
# End Source File
# Begin Source File

SOURCE=.\printf\obvprintf.c
# End Source File
# Begin Source File

SOURCE=.\mpz\out_raw.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\out_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\out_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\out_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\perfpow.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\perfsqr.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\perfsqr.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\popcount.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\popcount.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\pow_1.c
# End Source File
# Begin Source File

SOURCE=.\mpf\pow_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\pow_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\powm.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\powm_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\pprime_p.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\pre_divrem_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\pre_mod_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\printf\printf.c
# End Source File
# Begin Source File

SOURCE=.\printf\printffuns.c
# End Source File
# Begin Source File

SOURCE=.\rand.c
# End Source File
# Begin Source File

SOURCE=.\randclr.c
# End Source File
# Begin Source File

SOURCE=.\randdef.c
# End Source File
# Begin Source File

SOURCE=.\randlc.c
# End Source File
# Begin Source File

SOURCE=.\randlc2s.c
# End Source File
# Begin Source File

SOURCE=.\randlc2x.c
# End Source File
# Begin Source File

SOURCE=.\mpn\generic\random.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\random.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\random2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\random2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\random2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\randraw.c
# End Source File
# Begin Source File

SOURCE=.\rands.c
# End Source File
# Begin Source File

SOURCE=.\randsd.c
# End Source File
# Begin Source File

SOURCE=.\randsdui.c
# End Source File
# Begin Source File

SOURCE=.\mpz\realloc.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\realloc2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\reldiff.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\remove.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\printf\repl-vsnprintf.c"
# End Source File
# Begin Source File

SOURCE=.\mpz\root.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\rootrem.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\rrandomb.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\rshift.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\sb_divrem_mn.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\scan0.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\scan0.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\scan1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\scan1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\scanf\scanf.c
# End Source File
# Begin Source File

SOURCE=.\mpf\set.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\set.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\set.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\set_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\set_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\set_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\set_den.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\set_dfl_prec.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\set_f.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\set_f.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\set_num.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\set_prc.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\set_prc_raw.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\set_q.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\set_q.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\set_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\set_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\set_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\set_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\set_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\set_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\set_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\set_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\set_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\set_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\set_z.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\set_z.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\setbit.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\size.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\size.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\sizeinbase.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\printf\snprintf.c
# End Source File
# Begin Source File

SOURCE=.\printf\snprntffuns.c
# End Source File
# Begin Source File

SOURCE=.\printf\sprintf.c
# End Source File
# Begin Source File

SOURCE=.\printf\sprintffuns.c
# End Source File
# Begin Source File

SOURCE=.\mpn\generic\sqr_basecase.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\sqrt.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\sqrt.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\sqrt_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\sqrtrem.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\sqrtrem.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\scanf\sscanf.c
# End Source File
# Begin Source File

SOURCE=.\scanf\sscanffuns.c
# End Source File
# Begin Source File

SOURCE=.\mpf\sub.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\sub.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\sub.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\sub_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\sub_n.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"
# ADD CPP /D "OPERATION_sub_n"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"
# ADD CPP /D "OPERATION_sub_n"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\sub_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\sub_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\submul_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"
# ADD CPP /D "OPERATION_submul_1"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"
# ADD CPP /D "OPERATION_submul_1"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\swap.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpq\swap.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpq"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpq"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\swap.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\tdiv_q.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\tdiv_q_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\tdiv_q_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpn\generic\tdiv_qr.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpn"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpn"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\tdiv_qr.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\tdiv_qr_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\tdiv_r.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\tdiv_r_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\tdiv_r_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\tdiv_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\trunc.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\tstbit.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\ui_div.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\ui_pow_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\ui_sub.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpf\urandomb.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpf"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpf"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\urandomb.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mpz\urandomm.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\printf\vasprintf.c
# End Source File
# Begin Source File

SOURCE=.\version.c
# End Source File
# Begin Source File

SOURCE=.\printf\vfprintf.c
# End Source File
# Begin Source File

SOURCE=.\scanf\vfscanf.c
# End Source File
# Begin Source File

SOURCE=.\printf\vprintf.c
# End Source File
# Begin Source File

SOURCE=.\scanf\vscanf.c
# End Source File
# Begin Source File

SOURCE=.\printf\vsnprintf.c
# End Source File
# Begin Source File

SOURCE=.\printf\vsprintf.c
# End Source File
# Begin Source File

SOURCE=.\scanf\vsscanf.c
# End Source File
# Begin Source File

SOURCE=.\mpz\xor.c

!IF  "$(CFG)" == "gmp - Win32 Release"

# PROP Intermediate_Dir "Release\mpz"

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

# PROP Intermediate_Dir "Debug\mpz"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
