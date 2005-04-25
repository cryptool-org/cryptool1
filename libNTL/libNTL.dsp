# Microsoft Developer Studio Project File - Name="libNTL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libNTL - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "libNTL.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "libNTL.mak" CFG="libNTL - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "libNTL - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "libNTL - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libNTL - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libNTL - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "libNTL - Win32 Release"
# Name "libNTL - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\ctools.cpp
# End Source File
# Begin Source File

SOURCE=.\src\FacVec.cpp
# End Source File
# Begin Source File

SOURCE=.\src\FFT.cpp
# End Source File
# Begin Source File

SOURCE=.\src\fileio.cpp
# End Source File
# Begin Source File

SOURCE=.\src\G_LLL_FP.cpp
# End Source File
# Begin Source File

SOURCE=.\src\G_LLL_QP.cpp
# End Source File
# Begin Source File

SOURCE=.\src\G_LLL_RR.cpp
# End Source File
# Begin Source File

SOURCE=.\src\G_LLL_XD.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GetTime.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GF2.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GF2E.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GF2EX.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GF2EXFactoring.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GF2X.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GF2X1.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GF2XFactoring.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GF2XVec.cpp
# End Source File
# Begin Source File

SOURCE=.\src\HNF.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lip.cpp
# End Source File
# Begin Source File

SOURCE=.\src\LLL.cpp
# End Source File
# Begin Source File

SOURCE=.\src\LLL_FP.cpp
# End Source File
# Begin Source File

SOURCE=.\src\LLL_QP.cpp
# End Source File
# Begin Source File

SOURCE=.\src\LLL_RR.cpp
# End Source File
# Begin Source File

SOURCE=.\src\LLL_XD.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lzz_p.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lzz_pE.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lzz_pEX.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lzz_pEXFactoring.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lzz_pX.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lzz_pX1.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lzz_pXCharPoly.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lzz_pXFactoring.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mat_GF2.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mat_GF2E.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mat_lzz_p.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mat_lzz_pE.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mat_poly_lzz_p.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mat_poly_ZZ.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mat_poly_ZZ_p.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mat_RR.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mat_ZZ.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mat_ZZ_p.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mat_ZZ_pE.cpp
# End Source File
# Begin Source File

SOURCE=.\src\pair_GF2EX_long.cpp
# End Source File
# Begin Source File

SOURCE=.\src\pair_GF2X_long.cpp
# End Source File
# Begin Source File

SOURCE=.\src\pair_lzz_pEX_long.cpp
# End Source File
# Begin Source File

SOURCE=.\src\pair_lzz_pX_long.cpp
# End Source File
# Begin Source File

SOURCE=.\src\pair_ZZ_pEX_long.cpp
# End Source File
# Begin Source File

SOURCE=.\src\pair_ZZ_pX_long.cpp
# End Source File
# Begin Source File

SOURCE=.\src\pair_ZZX_long.cpp
# End Source File
# Begin Source File

SOURCE=.\src\quad_float.cpp
# End Source File
# Begin Source File

SOURCE=.\src\RR.cpp
# End Source File
# Begin Source File

SOURCE=.\src\tools.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_double.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_GF2.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_GF2E.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_GF2XVec.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_long.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_lzz_p.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_lzz_pE.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_quad_float.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_RR.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_ulong.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_vec_GF2.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_vec_GF2E.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_vec_long.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_vec_lzz_p.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_vec_lzz_pE.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_vec_RR.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_vec_ulong.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_vec_ZZ.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_vec_ZZ_p.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_vec_ZZ_pE.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_xdouble.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_ZZ.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_ZZ_p.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_ZZ_pE.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vec_ZZVec.cpp
# End Source File
# Begin Source File

SOURCE=.\src\WordVector.cpp
# End Source File
# Begin Source File

SOURCE=.\src\xdouble.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZ.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZ_p.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZ_pE.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZ_pEX.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZ_pEXFactoring.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZ_pX.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZ_pX1.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZ_pXCharPoly.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZ_pXFactoring.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZVec.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZX.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZX1.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZXCharPoly.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ZZXFactoring.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\NTL\c_lip.h
# End Source File
# Begin Source File

SOURCE=.\src\c_lip_impl.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\config.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\ctools.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\def_config.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\FacVec.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\FFT.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\fileio.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\g_lip.h
# End Source File
# Begin Source File

SOURCE=.\src\g_lip_impl.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\GF2.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\GF2E.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\GF2EX.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\GF2EXFactoring.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\GF2X.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\GF2XFactoring.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\GF2XVec.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\HNF.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\lip.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\LLL.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\lzz_p.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\lzz_pE.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\lzz_pEX.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\lzz_pEXFactoring.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\lzz_pX.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\lzz_pXFactoring.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\mach_desc.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\mat_GF2.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\mat_GF2E.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\mat_lzz_p.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\mat_lzz_pE.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\mat_poly_lzz_p.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\mat_poly_ZZ.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\mat_poly_ZZ_p.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\mat_RR.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\mat_ZZ.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\mat_ZZ_p.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\mat_ZZ_pE.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\matrix.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\new.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\pair.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\pair_GF2EX_long.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\pair_GF2X_long.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\pair_lzz_pEX_long.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\pair_lzz_pX_long.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\pair_ZZ_pEX_long.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\pair_ZZ_pX_long.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\pair_ZZX_long.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\quad_float.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\RR.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\tools.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_double.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_GF2.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_GF2E.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_GF2XVec.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_long.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_lzz_p.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_lzz_pE.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_quad_float.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_RR.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_ulong.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_vec_GF2.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_vec_GF2E.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_vec_long.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_vec_lzz_p.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_vec_lzz_pE.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_vec_RR.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_vec_ulong.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_vec_ZZ.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_vec_ZZ_p.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_vec_ZZ_pE.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_xdouble.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_ZZ.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_ZZ_p.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_ZZ_pE.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vec_ZZVec.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\vector.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\version.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\WordVector.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\xdouble.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\ZZ.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\ZZ_p.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\ZZ_pE.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\ZZ_pEX.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\ZZ_pEXFactoring.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\ZZ_pX.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\ZZ_pXFactoring.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\ZZVec.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\ZZX.h
# End Source File
# Begin Source File

SOURCE=.\include\NTL\ZZXFactoring.h
# End Source File
# End Group
# End Target
# End Project
