# Microsoft Developer Studio Generated NMAKE File, Based on multipad.dsp
!IF "$(CFG)" == ""
CFG=multipad - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. multipad - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "multipad - Win32 Release" && "$(CFG)" != "multipad - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "multipad.mak" CFG="multipad - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "multipad - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "multipad - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "multipad - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\Release\cryptool.hlp" "$(OUTDIR)\cryptool.exe"

!ELSE 

ALL : "LibEc - Win32 Release" "LibAnalyse - Win32 Release" ".\Release\cryptool.hlp" "$(OUTDIR)\cryptool.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LibAnalyse - Win32 ReleaseCLEAN" "LibEc - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\aes.obj"
	-@erase "$(INTDIR)\asymmetric.obj"
	-@erase "$(INTDIR)\automatic.obj"
	-@erase "$(INTDIR)\Autoren.obj"
	-@erase "$(INTDIR)\brute.obj"
	-@erase "$(INTDIR)\ChrTools.obj"
	-@erase "$(INTDIR)\crypt.obj"
	-@erase "$(INTDIR)\cryptdoc.obj"
	-@erase "$(INTDIR)\CryptDocTemplate.obj"
	-@erase "$(INTDIR)\dia1.obj"
	-@erase "$(INTDIR)\DialogCert.obj"
	-@erase "$(INTDIR)\DialogKeyHex.obj"
	-@erase "$(INTDIR)\DialogLaenge.obj"
	-@erase "$(INTDIR)\DialogLaengeBin.obj"
	-@erase "$(INTDIR)\DialogVienereKey.obj"
	-@erase "$(INTDIR)\DialoKeyCaesar.obj"
	-@erase "$(INTDIR)\Dlg_SubstResult.obj"
	-@erase "$(INTDIR)\DlgAsymKeyCreat.obj"
	-@erase "$(INTDIR)\DlgAsymKeys.obj"
	-@erase "$(INTDIR)\DlgEcKeysCreat.obj"
	-@erase "$(INTDIR)\DlgFortschritt.obj"
	-@erase "$(INTDIR)\DlgMono.obj"
	-@erase "$(INTDIR)\DlgShowPrivEcKeys.obj"
	-@erase "$(INTDIR)\DlgShowPubEcKeys.obj"
	-@erase "$(INTDIR)\DlgSign.obj"
	-@erase "$(INTDIR)\DlgSignExtract.obj"
	-@erase "$(INTDIR)\DlgSignSteps.obj"
	-@erase "$(INTDIR)\DlgSignVerif.obj"
	-@erase "$(INTDIR)\DlgSignVerifSteps.obj"
	-@erase "$(INTDIR)\DlgSubstAna.obj"
	-@erase "$(INTDIR)\dozip.obj"
	-@erase "$(INTDIR)\Ecssa.obj"
	-@erase "$(INTDIR)\fileutil.obj"
	-@erase "$(INTDIR)\fixedview.obj"
	-@erase "$(INTDIR)\hexdialog.obj"
	-@erase "$(INTDIR)\HexEdit1.obj"
	-@erase "$(INTDIR)\HexView.obj"
	-@erase "$(INTDIR)\hill.obj"
	-@erase "$(INTDIR)\HillEingabe.obj"
	-@erase "$(INTDIR)\HillEingabeGross.obj"
	-@erase "$(INTDIR)\HillSchluesselAusgabe.obj"
	-@erase "$(INTDIR)\HillSchluesselAusgabeGross.obj"
	-@erase "$(INTDIR)\KeyFileHandling.obj"
	-@erase "$(INTDIR)\KeySearch.obj"
	-@erase "$(INTDIR)\mars-opt.obj"
	-@erase "$(INTDIR)\multipad.obj"
	-@erase "$(INTDIR)\MultiPad.res"
	-@erase "$(INTDIR)\MyDocument.obj"
	-@erase "$(INTDIR)\MyEditView.obj"
	-@erase "$(INTDIR)\OptionsDialog.obj"
	-@erase "$(INTDIR)\PinCodeDialog.obj"
	-@erase "$(INTDIR)\playfair.obj"
	-@erase "$(INTDIR)\PlotDoc.obj"
	-@erase "$(INTDIR)\PlotView.obj"
	-@erase "$(INTDIR)\rc6.obj"
	-@erase "$(INTDIR)\Read_Ini_File.obj"
	-@erase "$(INTDIR)\rijndael-alg-fst.obj"
	-@erase "$(INTDIR)\rijndael-api-fst.obj"
	-@erase "$(INTDIR)\RsaDec.obj"
	-@erase "$(INTDIR)\RsaEnc.obj"
	-@erase "$(INTDIR)\s_prng.obj"
	-@erase "$(INTDIR)\SchluesselAusgabeLinear.obj"
	-@erase "$(INTDIR)\secude.obj"
	-@erase "$(INTDIR)\SecudeLib.obj"
	-@erase "$(INTDIR)\SERPENT.OBJ"
	-@erase "$(INTDIR)\sq_mat.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\TextEingabeHillAngriff.obj"
	-@erase "$(INTDIR)\TextOptions.obj"
	-@erase "$(INTDIR)\TWOFISH2.OBJ"
	-@erase "$(INTDIR)\ValueList.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\zbits.obj"
	-@erase "$(INTDIR)\zdeflate.obj"
	-@erase "$(INTDIR)\zfile_io.obj"
	-@erase "$(INTDIR)\zglobals.obj"
	-@erase "$(INTDIR)\zinflate.obj"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "$(INTDIR)\zipup.obj"
	-@erase "$(INTDIR)\ztrees.obj"
	-@erase "$(INTDIR)\zunzip.obj"
	-@erase "$(OUTDIR)\cryptool.exe"
	-@erase "$(OUTDIR)\cryptool.pdb"
	-@erase ".\Release\cryptool.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\MultiPad.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\multipad.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=..\LibAnalyse\Release\LibAnalyse.lib ..\Libec\Lib\EcBibV2.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\cryptool.pdb" /debug /machine:I386 /out:"$(OUTDIR)\cryptool.exe" 
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\aes.obj" \
	"$(INTDIR)\asymmetric.obj" \
	"$(INTDIR)\automatic.obj" \
	"$(INTDIR)\Autoren.obj" \
	"$(INTDIR)\brute.obj" \
	"$(INTDIR)\ChrTools.obj" \
	"$(INTDIR)\crypt.obj" \
	"$(INTDIR)\cryptdoc.obj" \
	"$(INTDIR)\CryptDocTemplate.obj" \
	"$(INTDIR)\dia1.obj" \
	"$(INTDIR)\DialogCert.obj" \
	"$(INTDIR)\DialogKeyHex.obj" \
	"$(INTDIR)\DialogLaenge.obj" \
	"$(INTDIR)\DialogLaengeBin.obj" \
	"$(INTDIR)\DialogVienereKey.obj" \
	"$(INTDIR)\DialoKeyCaesar.obj" \
	"$(INTDIR)\Dlg_SubstResult.obj" \
	"$(INTDIR)\DlgAsymKeyCreat.obj" \
	"$(INTDIR)\DlgAsymKeys.obj" \
	"$(INTDIR)\DlgEcKeysCreat.obj" \
	"$(INTDIR)\DlgFortschritt.obj" \
	"$(INTDIR)\DlgMono.obj" \
	"$(INTDIR)\DlgShowPrivEcKeys.obj" \
	"$(INTDIR)\DlgShowPubEcKeys.obj" \
	"$(INTDIR)\DlgSign.obj" \
	"$(INTDIR)\DlgSignExtract.obj" \
	"$(INTDIR)\DlgSignSteps.obj" \
	"$(INTDIR)\DlgSignVerif.obj" \
	"$(INTDIR)\DlgSignVerifSteps.obj" \
	"$(INTDIR)\DlgSubstAna.obj" \
	"$(INTDIR)\dozip.obj" \
	"$(INTDIR)\Ecssa.obj" \
	"$(INTDIR)\fileutil.obj" \
	"$(INTDIR)\fixedview.obj" \
	"$(INTDIR)\hexdialog.obj" \
	"$(INTDIR)\HexEdit1.obj" \
	"$(INTDIR)\HexView.obj" \
	"$(INTDIR)\hill.obj" \
	"$(INTDIR)\HillEingabe.obj" \
	"$(INTDIR)\HillEingabeGross.obj" \
	"$(INTDIR)\HillSchluesselAusgabe.obj" \
	"$(INTDIR)\HillSchluesselAusgabeGross.obj" \
	"$(INTDIR)\KeyFileHandling.obj" \
	"$(INTDIR)\KeySearch.obj" \
	"$(INTDIR)\mars-opt.obj" \
	"$(INTDIR)\multipad.obj" \
	"$(INTDIR)\MyDocument.obj" \
	"$(INTDIR)\MyEditView.obj" \
	"$(INTDIR)\OptionsDialog.obj" \
	"$(INTDIR)\PinCodeDialog.obj" \
	"$(INTDIR)\playfair.obj" \
	"$(INTDIR)\PlotDoc.obj" \
	"$(INTDIR)\PlotView.obj" \
	"$(INTDIR)\rc6.obj" \
	"$(INTDIR)\Read_Ini_File.obj" \
	"$(INTDIR)\rijndael-alg-fst.obj" \
	"$(INTDIR)\rijndael-api-fst.obj" \
	"$(INTDIR)\RsaDec.obj" \
	"$(INTDIR)\RsaEnc.obj" \
	"$(INTDIR)\s_prng.obj" \
	"$(INTDIR)\SchluesselAusgabeLinear.obj" \
	"$(INTDIR)\secude.obj" \
	"$(INTDIR)\SecudeLib.obj" \
	"$(INTDIR)\SERPENT.OBJ" \
	"$(INTDIR)\sq_mat.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\TextEingabeHillAngriff.obj" \
	"$(INTDIR)\TextOptions.obj" \
	"$(INTDIR)\TWOFISH2.OBJ" \
	"$(INTDIR)\ValueList.obj" \
	"$(INTDIR)\zbits.obj" \
	"$(INTDIR)\zdeflate.obj" \
	"$(INTDIR)\zfile_io.obj" \
	"$(INTDIR)\zglobals.obj" \
	"$(INTDIR)\zinflate.obj" \
	"$(INTDIR)\zip.obj" \
	"$(INTDIR)\zipup.obj" \
	"$(INTDIR)\ztrees.obj" \
	"$(INTDIR)\zunzip.obj" \
	"$(INTDIR)\MultiPad.res" \
	"..\LibAnalyse\Release\LibAnalyse.lib" \
	"..\LibEc\lib\EcBibV2.lib"

"$(OUTDIR)\cryptool.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "LibEc - Win32 Release" "LibAnalyse - Win32 Release" ".\Release\cryptool.hlp" "$(OUTDIR)\cryptool.exe"
   copy Release\CrypTool.* ..\CrypTool\*.*
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\Debug\cryptool.hlp" "$(OUTDIR)\cryptool.exe" "$(OUTDIR)\multipad.bsc"

!ELSE 

ALL : "LibEc - Win32 Debug" "LibAnalyse - Win32 Debug" ".\Debug\cryptool.hlp" "$(OUTDIR)\cryptool.exe" "$(OUTDIR)\multipad.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LibAnalyse - Win32 DebugCLEAN" "LibEc - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\aes.obj"
	-@erase "$(INTDIR)\aes.sbr"
	-@erase "$(INTDIR)\asymmetric.obj"
	-@erase "$(INTDIR)\asymmetric.sbr"
	-@erase "$(INTDIR)\automatic.obj"
	-@erase "$(INTDIR)\automatic.sbr"
	-@erase "$(INTDIR)\Autoren.obj"
	-@erase "$(INTDIR)\Autoren.sbr"
	-@erase "$(INTDIR)\brute.obj"
	-@erase "$(INTDIR)\brute.sbr"
	-@erase "$(INTDIR)\ChrTools.obj"
	-@erase "$(INTDIR)\ChrTools.sbr"
	-@erase "$(INTDIR)\crypt.obj"
	-@erase "$(INTDIR)\crypt.sbr"
	-@erase "$(INTDIR)\cryptdoc.obj"
	-@erase "$(INTDIR)\cryptdoc.sbr"
	-@erase "$(INTDIR)\CryptDocTemplate.obj"
	-@erase "$(INTDIR)\CryptDocTemplate.sbr"
	-@erase "$(INTDIR)\dia1.obj"
	-@erase "$(INTDIR)\dia1.sbr"
	-@erase "$(INTDIR)\DialogCert.obj"
	-@erase "$(INTDIR)\DialogCert.sbr"
	-@erase "$(INTDIR)\DialogKeyHex.obj"
	-@erase "$(INTDIR)\DialogKeyHex.sbr"
	-@erase "$(INTDIR)\DialogLaenge.obj"
	-@erase "$(INTDIR)\DialogLaenge.sbr"
	-@erase "$(INTDIR)\DialogLaengeBin.obj"
	-@erase "$(INTDIR)\DialogLaengeBin.sbr"
	-@erase "$(INTDIR)\DialogVienereKey.obj"
	-@erase "$(INTDIR)\DialogVienereKey.sbr"
	-@erase "$(INTDIR)\DialoKeyCaesar.obj"
	-@erase "$(INTDIR)\DialoKeyCaesar.sbr"
	-@erase "$(INTDIR)\Dlg_SubstResult.obj"
	-@erase "$(INTDIR)\Dlg_SubstResult.sbr"
	-@erase "$(INTDIR)\DlgAsymKeyCreat.obj"
	-@erase "$(INTDIR)\DlgAsymKeyCreat.sbr"
	-@erase "$(INTDIR)\DlgAsymKeys.obj"
	-@erase "$(INTDIR)\DlgAsymKeys.sbr"
	-@erase "$(INTDIR)\DlgEcKeysCreat.obj"
	-@erase "$(INTDIR)\DlgEcKeysCreat.sbr"
	-@erase "$(INTDIR)\DlgFortschritt.obj"
	-@erase "$(INTDIR)\DlgFortschritt.sbr"
	-@erase "$(INTDIR)\DlgMono.obj"
	-@erase "$(INTDIR)\DlgMono.sbr"
	-@erase "$(INTDIR)\DlgShowPrivEcKeys.obj"
	-@erase "$(INTDIR)\DlgShowPrivEcKeys.sbr"
	-@erase "$(INTDIR)\DlgShowPubEcKeys.obj"
	-@erase "$(INTDIR)\DlgShowPubEcKeys.sbr"
	-@erase "$(INTDIR)\DlgSign.obj"
	-@erase "$(INTDIR)\DlgSign.sbr"
	-@erase "$(INTDIR)\DlgSignExtract.obj"
	-@erase "$(INTDIR)\DlgSignExtract.sbr"
	-@erase "$(INTDIR)\DlgSignSteps.obj"
	-@erase "$(INTDIR)\DlgSignSteps.sbr"
	-@erase "$(INTDIR)\DlgSignVerif.obj"
	-@erase "$(INTDIR)\DlgSignVerif.sbr"
	-@erase "$(INTDIR)\DlgSignVerifSteps.obj"
	-@erase "$(INTDIR)\DlgSignVerifSteps.sbr"
	-@erase "$(INTDIR)\DlgSubstAna.obj"
	-@erase "$(INTDIR)\DlgSubstAna.sbr"
	-@erase "$(INTDIR)\dozip.obj"
	-@erase "$(INTDIR)\dozip.sbr"
	-@erase "$(INTDIR)\Ecssa.obj"
	-@erase "$(INTDIR)\Ecssa.sbr"
	-@erase "$(INTDIR)\fileutil.obj"
	-@erase "$(INTDIR)\fileutil.sbr"
	-@erase "$(INTDIR)\fixedview.obj"
	-@erase "$(INTDIR)\fixedview.sbr"
	-@erase "$(INTDIR)\hexdialog.obj"
	-@erase "$(INTDIR)\hexdialog.sbr"
	-@erase "$(INTDIR)\HexEdit1.obj"
	-@erase "$(INTDIR)\HexEdit1.sbr"
	-@erase "$(INTDIR)\HexView.obj"
	-@erase "$(INTDIR)\HexView.sbr"
	-@erase "$(INTDIR)\hill.obj"
	-@erase "$(INTDIR)\hill.sbr"
	-@erase "$(INTDIR)\HillEingabe.obj"
	-@erase "$(INTDIR)\HillEingabe.sbr"
	-@erase "$(INTDIR)\HillEingabeGross.obj"
	-@erase "$(INTDIR)\HillEingabeGross.sbr"
	-@erase "$(INTDIR)\HillSchluesselAusgabe.obj"
	-@erase "$(INTDIR)\HillSchluesselAusgabe.sbr"
	-@erase "$(INTDIR)\HillSchluesselAusgabeGross.obj"
	-@erase "$(INTDIR)\HillSchluesselAusgabeGross.sbr"
	-@erase "$(INTDIR)\KeyFileHandling.obj"
	-@erase "$(INTDIR)\KeyFileHandling.sbr"
	-@erase "$(INTDIR)\KeySearch.obj"
	-@erase "$(INTDIR)\KeySearch.sbr"
	-@erase "$(INTDIR)\mars-opt.obj"
	-@erase "$(INTDIR)\mars-opt.sbr"
	-@erase "$(INTDIR)\multipad.obj"
	-@erase "$(INTDIR)\MultiPad.res"
	-@erase "$(INTDIR)\multipad.sbr"
	-@erase "$(INTDIR)\MyDocument.obj"
	-@erase "$(INTDIR)\MyDocument.sbr"
	-@erase "$(INTDIR)\MyEditView.obj"
	-@erase "$(INTDIR)\MyEditView.sbr"
	-@erase "$(INTDIR)\OptionsDialog.obj"
	-@erase "$(INTDIR)\OptionsDialog.sbr"
	-@erase "$(INTDIR)\PinCodeDialog.obj"
	-@erase "$(INTDIR)\PinCodeDialog.sbr"
	-@erase "$(INTDIR)\playfair.obj"
	-@erase "$(INTDIR)\playfair.sbr"
	-@erase "$(INTDIR)\PlotDoc.obj"
	-@erase "$(INTDIR)\PlotDoc.sbr"
	-@erase "$(INTDIR)\PlotView.obj"
	-@erase "$(INTDIR)\PlotView.sbr"
	-@erase "$(INTDIR)\rc6.obj"
	-@erase "$(INTDIR)\rc6.sbr"
	-@erase "$(INTDIR)\Read_Ini_File.obj"
	-@erase "$(INTDIR)\Read_Ini_File.sbr"
	-@erase "$(INTDIR)\rijndael-alg-fst.obj"
	-@erase "$(INTDIR)\rijndael-alg-fst.sbr"
	-@erase "$(INTDIR)\rijndael-api-fst.obj"
	-@erase "$(INTDIR)\rijndael-api-fst.sbr"
	-@erase "$(INTDIR)\RsaDec.obj"
	-@erase "$(INTDIR)\RsaDec.sbr"
	-@erase "$(INTDIR)\RsaEnc.obj"
	-@erase "$(INTDIR)\RsaEnc.sbr"
	-@erase "$(INTDIR)\s_prng.obj"
	-@erase "$(INTDIR)\s_prng.sbr"
	-@erase "$(INTDIR)\SchluesselAusgabeLinear.obj"
	-@erase "$(INTDIR)\SchluesselAusgabeLinear.sbr"
	-@erase "$(INTDIR)\secude.obj"
	-@erase "$(INTDIR)\secude.sbr"
	-@erase "$(INTDIR)\SecudeLib.obj"
	-@erase "$(INTDIR)\SecudeLib.sbr"
	-@erase "$(INTDIR)\SERPENT.OBJ"
	-@erase "$(INTDIR)\SERPENT.SBR"
	-@erase "$(INTDIR)\sq_mat.obj"
	-@erase "$(INTDIR)\sq_mat.sbr"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\stdafx.sbr"
	-@erase "$(INTDIR)\TextEingabeHillAngriff.obj"
	-@erase "$(INTDIR)\TextEingabeHillAngriff.sbr"
	-@erase "$(INTDIR)\TextOptions.obj"
	-@erase "$(INTDIR)\TextOptions.sbr"
	-@erase "$(INTDIR)\TWOFISH2.OBJ"
	-@erase "$(INTDIR)\TWOFISH2.SBR"
	-@erase "$(INTDIR)\ValueList.obj"
	-@erase "$(INTDIR)\ValueList.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\zbits.obj"
	-@erase "$(INTDIR)\zbits.sbr"
	-@erase "$(INTDIR)\zdeflate.obj"
	-@erase "$(INTDIR)\zdeflate.sbr"
	-@erase "$(INTDIR)\zfile_io.obj"
	-@erase "$(INTDIR)\zfile_io.sbr"
	-@erase "$(INTDIR)\zglobals.obj"
	-@erase "$(INTDIR)\zglobals.sbr"
	-@erase "$(INTDIR)\zinflate.obj"
	-@erase "$(INTDIR)\zinflate.sbr"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "$(INTDIR)\zip.sbr"
	-@erase "$(INTDIR)\zipup.obj"
	-@erase "$(INTDIR)\zipup.sbr"
	-@erase "$(INTDIR)\ztrees.obj"
	-@erase "$(INTDIR)\ztrees.sbr"
	-@erase "$(INTDIR)\zunzip.obj"
	-@erase "$(INTDIR)\zunzip.sbr"
	-@erase "$(OUTDIR)\cryptool.exe"
	-@erase "$(OUTDIR)\multipad.bsc"
	-@erase ".\Debug\cryptool.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\MultiPad.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\multipad.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\aes.sbr" \
	"$(INTDIR)\asymmetric.sbr" \
	"$(INTDIR)\automatic.sbr" \
	"$(INTDIR)\Autoren.sbr" \
	"$(INTDIR)\brute.sbr" \
	"$(INTDIR)\ChrTools.sbr" \
	"$(INTDIR)\crypt.sbr" \
	"$(INTDIR)\cryptdoc.sbr" \
	"$(INTDIR)\CryptDocTemplate.sbr" \
	"$(INTDIR)\dia1.sbr" \
	"$(INTDIR)\DialogCert.sbr" \
	"$(INTDIR)\DialogKeyHex.sbr" \
	"$(INTDIR)\DialogLaenge.sbr" \
	"$(INTDIR)\DialogLaengeBin.sbr" \
	"$(INTDIR)\DialogVienereKey.sbr" \
	"$(INTDIR)\DialoKeyCaesar.sbr" \
	"$(INTDIR)\Dlg_SubstResult.sbr" \
	"$(INTDIR)\DlgAsymKeyCreat.sbr" \
	"$(INTDIR)\DlgAsymKeys.sbr" \
	"$(INTDIR)\DlgEcKeysCreat.sbr" \
	"$(INTDIR)\DlgFortschritt.sbr" \
	"$(INTDIR)\DlgMono.sbr" \
	"$(INTDIR)\DlgShowPrivEcKeys.sbr" \
	"$(INTDIR)\DlgShowPubEcKeys.sbr" \
	"$(INTDIR)\DlgSign.sbr" \
	"$(INTDIR)\DlgSignExtract.sbr" \
	"$(INTDIR)\DlgSignSteps.sbr" \
	"$(INTDIR)\DlgSignVerif.sbr" \
	"$(INTDIR)\DlgSignVerifSteps.sbr" \
	"$(INTDIR)\DlgSubstAna.sbr" \
	"$(INTDIR)\dozip.sbr" \
	"$(INTDIR)\Ecssa.sbr" \
	"$(INTDIR)\fileutil.sbr" \
	"$(INTDIR)\fixedview.sbr" \
	"$(INTDIR)\hexdialog.sbr" \
	"$(INTDIR)\HexEdit1.sbr" \
	"$(INTDIR)\HexView.sbr" \
	"$(INTDIR)\hill.sbr" \
	"$(INTDIR)\HillEingabe.sbr" \
	"$(INTDIR)\HillEingabeGross.sbr" \
	"$(INTDIR)\HillSchluesselAusgabe.sbr" \
	"$(INTDIR)\HillSchluesselAusgabeGross.sbr" \
	"$(INTDIR)\KeyFileHandling.sbr" \
	"$(INTDIR)\KeySearch.sbr" \
	"$(INTDIR)\mars-opt.sbr" \
	"$(INTDIR)\multipad.sbr" \
	"$(INTDIR)\MyDocument.sbr" \
	"$(INTDIR)\MyEditView.sbr" \
	"$(INTDIR)\OptionsDialog.sbr" \
	"$(INTDIR)\PinCodeDialog.sbr" \
	"$(INTDIR)\playfair.sbr" \
	"$(INTDIR)\PlotDoc.sbr" \
	"$(INTDIR)\PlotView.sbr" \
	"$(INTDIR)\rc6.sbr" \
	"$(INTDIR)\Read_Ini_File.sbr" \
	"$(INTDIR)\rijndael-alg-fst.sbr" \
	"$(INTDIR)\rijndael-api-fst.sbr" \
	"$(INTDIR)\RsaDec.sbr" \
	"$(INTDIR)\RsaEnc.sbr" \
	"$(INTDIR)\s_prng.sbr" \
	"$(INTDIR)\SchluesselAusgabeLinear.sbr" \
	"$(INTDIR)\secude.sbr" \
	"$(INTDIR)\SecudeLib.sbr" \
	"$(INTDIR)\SERPENT.SBR" \
	"$(INTDIR)\sq_mat.sbr" \
	"$(INTDIR)\stdafx.sbr" \
	"$(INTDIR)\TextEingabeHillAngriff.sbr" \
	"$(INTDIR)\TextOptions.sbr" \
	"$(INTDIR)\TWOFISH2.SBR" \
	"$(INTDIR)\ValueList.sbr" \
	"$(INTDIR)\zbits.sbr" \
	"$(INTDIR)\zdeflate.sbr" \
	"$(INTDIR)\zfile_io.sbr" \
	"$(INTDIR)\zglobals.sbr" \
	"$(INTDIR)\zinflate.sbr" \
	"$(INTDIR)\zip.sbr" \
	"$(INTDIR)\zipup.sbr" \
	"$(INTDIR)\ztrees.sbr" \
	"$(INTDIR)\zunzip.sbr"

"$(OUTDIR)\multipad.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=..\LibAnalyse\Debug\LibAnalyse.lib ..\Libec\Lib\EcBibV2D.lib /nologo /subsystem:windows /profile /debug /machine:I386 /nodefaultlib:"libcd" /out:"$(OUTDIR)\cryptool.exe" 
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\aes.obj" \
	"$(INTDIR)\asymmetric.obj" \
	"$(INTDIR)\automatic.obj" \
	"$(INTDIR)\Autoren.obj" \
	"$(INTDIR)\brute.obj" \
	"$(INTDIR)\ChrTools.obj" \
	"$(INTDIR)\crypt.obj" \
	"$(INTDIR)\cryptdoc.obj" \
	"$(INTDIR)\CryptDocTemplate.obj" \
	"$(INTDIR)\dia1.obj" \
	"$(INTDIR)\DialogCert.obj" \
	"$(INTDIR)\DialogKeyHex.obj" \
	"$(INTDIR)\DialogLaenge.obj" \
	"$(INTDIR)\DialogLaengeBin.obj" \
	"$(INTDIR)\DialogVienereKey.obj" \
	"$(INTDIR)\DialoKeyCaesar.obj" \
	"$(INTDIR)\Dlg_SubstResult.obj" \
	"$(INTDIR)\DlgAsymKeyCreat.obj" \
	"$(INTDIR)\DlgAsymKeys.obj" \
	"$(INTDIR)\DlgEcKeysCreat.obj" \
	"$(INTDIR)\DlgFortschritt.obj" \
	"$(INTDIR)\DlgMono.obj" \
	"$(INTDIR)\DlgShowPrivEcKeys.obj" \
	"$(INTDIR)\DlgShowPubEcKeys.obj" \
	"$(INTDIR)\DlgSign.obj" \
	"$(INTDIR)\DlgSignExtract.obj" \
	"$(INTDIR)\DlgSignSteps.obj" \
	"$(INTDIR)\DlgSignVerif.obj" \
	"$(INTDIR)\DlgSignVerifSteps.obj" \
	"$(INTDIR)\DlgSubstAna.obj" \
	"$(INTDIR)\dozip.obj" \
	"$(INTDIR)\Ecssa.obj" \
	"$(INTDIR)\fileutil.obj" \
	"$(INTDIR)\fixedview.obj" \
	"$(INTDIR)\hexdialog.obj" \
	"$(INTDIR)\HexEdit1.obj" \
	"$(INTDIR)\HexView.obj" \
	"$(INTDIR)\hill.obj" \
	"$(INTDIR)\HillEingabe.obj" \
	"$(INTDIR)\HillEingabeGross.obj" \
	"$(INTDIR)\HillSchluesselAusgabe.obj" \
	"$(INTDIR)\HillSchluesselAusgabeGross.obj" \
	"$(INTDIR)\KeyFileHandling.obj" \
	"$(INTDIR)\KeySearch.obj" \
	"$(INTDIR)\mars-opt.obj" \
	"$(INTDIR)\multipad.obj" \
	"$(INTDIR)\MyDocument.obj" \
	"$(INTDIR)\MyEditView.obj" \
	"$(INTDIR)\OptionsDialog.obj" \
	"$(INTDIR)\PinCodeDialog.obj" \
	"$(INTDIR)\playfair.obj" \
	"$(INTDIR)\PlotDoc.obj" \
	"$(INTDIR)\PlotView.obj" \
	"$(INTDIR)\rc6.obj" \
	"$(INTDIR)\Read_Ini_File.obj" \
	"$(INTDIR)\rijndael-alg-fst.obj" \
	"$(INTDIR)\rijndael-api-fst.obj" \
	"$(INTDIR)\RsaDec.obj" \
	"$(INTDIR)\RsaEnc.obj" \
	"$(INTDIR)\s_prng.obj" \
	"$(INTDIR)\SchluesselAusgabeLinear.obj" \
	"$(INTDIR)\secude.obj" \
	"$(INTDIR)\SecudeLib.obj" \
	"$(INTDIR)\SERPENT.OBJ" \
	"$(INTDIR)\sq_mat.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\TextEingabeHillAngriff.obj" \
	"$(INTDIR)\TextOptions.obj" \
	"$(INTDIR)\TWOFISH2.OBJ" \
	"$(INTDIR)\ValueList.obj" \
	"$(INTDIR)\zbits.obj" \
	"$(INTDIR)\zdeflate.obj" \
	"$(INTDIR)\zfile_io.obj" \
	"$(INTDIR)\zglobals.obj" \
	"$(INTDIR)\zinflate.obj" \
	"$(INTDIR)\zip.obj" \
	"$(INTDIR)\zipup.obj" \
	"$(INTDIR)\ztrees.obj" \
	"$(INTDIR)\zunzip.obj" \
	"$(INTDIR)\MultiPad.res" \
	"..\LibAnalyse\Debug\LibAnalyse.lib" \
	"..\LibEc\lib\EcBibV2D.lib"

"$(OUTDIR)\cryptool.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("multipad.dep")
!INCLUDE "multipad.dep"
!ELSE 
!MESSAGE Warning: cannot find "multipad.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "multipad - Win32 Release" || "$(CFG)" == "multipad - Win32 Debug"

!IF  "$(CFG)" == "multipad - Win32 Release"

"LibAnalyse - Win32 Release" : 
   cd "\Eigene Dateien\cryptool\analyse\LibAnalyse"
   $(MAKE) /$(MAKEFLAGS) /F ".\LibAnalyse.mak" CFG="LibAnalyse - Win32 Release" 
   cd "..\multipad"

"LibAnalyse - Win32 ReleaseCLEAN" : 
   cd "\Eigene Dateien\cryptool\analyse\LibAnalyse"
   $(MAKE) /$(MAKEFLAGS) /F ".\LibAnalyse.mak" CFG="LibAnalyse - Win32 Release" RECURSE=1 CLEAN 
   cd "..\multipad"

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

"LibAnalyse - Win32 Debug" : 
   cd "\Eigene Dateien\cryptool\analyse\LibAnalyse"
   $(MAKE) /$(MAKEFLAGS) /F ".\LibAnalyse.mak" CFG="LibAnalyse - Win32 Debug" 
   cd "..\multipad"

"LibAnalyse - Win32 DebugCLEAN" : 
   cd "\Eigene Dateien\cryptool\analyse\LibAnalyse"
   $(MAKE) /$(MAKEFLAGS) /F ".\LibAnalyse.mak" CFG="LibAnalyse - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\multipad"

!ENDIF 

!IF  "$(CFG)" == "multipad - Win32 Release"

"LibEc - Win32 Release" : 
   cd "\Eigene Dateien\cryptool\analyse\LibEc"
   $(MAKE) /$(MAKEFLAGS) /F ".\LibEc.mak" CFG="LibEc - Win32 Release" 
   cd "..\multipad"

"LibEc - Win32 ReleaseCLEAN" : 
   cd "\Eigene Dateien\cryptool\analyse\LibEc"
   $(MAKE) /$(MAKEFLAGS) /F ".\LibEc.mak" CFG="LibEc - Win32 Release" RECURSE=1 CLEAN 
   cd "..\multipad"

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

"LibEc - Win32 Debug" : 
   cd "\Eigene Dateien\cryptool\analyse\LibEc"
   $(MAKE) /$(MAKEFLAGS) /F ".\LibEc.mak" CFG="LibEc - Win32 Debug" 
   cd "..\multipad"

"LibEc - Win32 DebugCLEAN" : 
   cd "\Eigene Dateien\cryptool\analyse\LibEc"
   $(MAKE) /$(MAKEFLAGS) /F ".\LibEc.mak" CFG="LibEc - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\multipad"

!ENDIF 

SOURCE=.\About.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\About.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\aes.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\aes.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\aes.obj"	"$(INTDIR)\aes.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\asymmetric.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\asymmetric.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\asymmetric.obj"	"$(INTDIR)\asymmetric.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\automatic.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\automatic.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\automatic.obj"	"$(INTDIR)\automatic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Autoren.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Autoren.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Autoren.obj"	"$(INTDIR)\Autoren.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\brute.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\brute.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\brute.obj"	"$(INTDIR)\brute.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ChrTools.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\ChrTools.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\ChrTools.obj"	"$(INTDIR)\ChrTools.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\crypt.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\crypt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\crypt.obj"	"$(INTDIR)\crypt.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\cryptdoc.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\cryptdoc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\cryptdoc.obj"	"$(INTDIR)\cryptdoc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CryptDocTemplate.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\CryptDocTemplate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\CryptDocTemplate.obj"	"$(INTDIR)\CryptDocTemplate.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\dia1.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dia1.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dia1.obj"	"$(INTDIR)\dia1.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DialogCert.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DialogCert.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DialogCert.obj"	"$(INTDIR)\DialogCert.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DialogKeyHex.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DialogKeyHex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DialogKeyHex.obj"	"$(INTDIR)\DialogKeyHex.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DialogLaenge.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DialogLaenge.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DialogLaenge.obj"	"$(INTDIR)\DialogLaenge.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DialogLaengeBin.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DialogLaengeBin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DialogLaengeBin.obj"	"$(INTDIR)\DialogLaengeBin.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DialogVienereKey.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DialogVienereKey.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DialogVienereKey.obj"	"$(INTDIR)\DialogVienereKey.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DialoKeyCaesar.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DialoKeyCaesar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DialoKeyCaesar.obj"	"$(INTDIR)\DialoKeyCaesar.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg_SubstResult.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Dlg_SubstResult.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Dlg_SubstResult.obj"	"$(INTDIR)\Dlg_SubstResult.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DlgAsymKeyCreat.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgAsymKeyCreat.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgAsymKeyCreat.obj"	"$(INTDIR)\DlgAsymKeyCreat.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DlgAsymKeys.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgAsymKeys.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgAsymKeys.obj"	"$(INTDIR)\DlgAsymKeys.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DlgEcKeysCreat.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgEcKeysCreat.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgEcKeysCreat.obj"	"$(INTDIR)\DlgEcKeysCreat.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DlgFortschritt.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\DlgFortschritt.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\DlgFortschritt.obj"	"$(INTDIR)\DlgFortschritt.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DlgMono.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgMono.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgMono.obj"	"$(INTDIR)\DlgMono.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DlgShowPrivEcKeys.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgShowPrivEcKeys.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgShowPrivEcKeys.obj"	"$(INTDIR)\DlgShowPrivEcKeys.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DlgShowPubEcKeys.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgShowPubEcKeys.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgShowPubEcKeys.obj"	"$(INTDIR)\DlgShowPubEcKeys.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DlgSign.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgSign.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgSign.obj"	"$(INTDIR)\DlgSign.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DlgSignExtract.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgSignExtract.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgSignExtract.obj"	"$(INTDIR)\DlgSignExtract.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DlgSignSteps.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgSignSteps.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgSignSteps.obj"	"$(INTDIR)\DlgSignSteps.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DlgSignVerif.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgSignVerif.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgSignVerif.obj"	"$(INTDIR)\DlgSignVerif.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DlgSignVerifSteps.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgSignVerifSteps.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgSignVerifSteps.obj"	"$(INTDIR)\DlgSignVerifSteps.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DlgSubstAna.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgSubstAna.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgSubstAna.obj"	"$(INTDIR)\DlgSubstAna.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\dozip.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\dozip.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\dozip.obj"	"$(INTDIR)\dozip.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=..\LibEc\sources\Ecssa.c

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\Ecssa.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\Ecssa.obj"	"$(INTDIR)\Ecssa.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\fileutil.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\fileutil.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\fileutil.obj"	"$(INTDIR)\fileutil.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\fixedview.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\fixedview.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\fixedview.obj"	"$(INTDIR)\fixedview.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\hexdialog.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\hexdialog.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\hexdialog.obj"	"$(INTDIR)\hexdialog.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\HexEdit1.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\HexEdit1.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\HexEdit1.obj"	"$(INTDIR)\HexEdit1.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\HexView.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\HexView.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\HexView.obj"	"$(INTDIR)\HexView.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\hill.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\hill.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\hill.obj"	"$(INTDIR)\hill.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\HillEingabe.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\HillEingabe.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\HillEingabe.obj"	"$(INTDIR)\HillEingabe.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\HillEingabeGross.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\HillEingabeGross.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\HillEingabeGross.obj"	"$(INTDIR)\HillEingabeGross.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\HillSchluesselAusgabe.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\HillSchluesselAusgabe.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\HillSchluesselAusgabe.obj"	"$(INTDIR)\HillSchluesselAusgabe.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\HillSchluesselAusgabeGross.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\HillSchluesselAusgabeGross.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\HillSchluesselAusgabeGross.obj"	"$(INTDIR)\HillSchluesselAusgabeGross.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\KeyFileHandling.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\KeyFileHandling.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\KeyFileHandling.obj"	"$(INTDIR)\KeyFileHandling.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\KeySearch.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\KeySearch.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\KeySearch.obj"	"$(INTDIR)\KeySearch.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\AES\Mars\mars-opt.c"

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\mars-opt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\mars-opt.obj"	"$(INTDIR)\mars-opt.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\multipad.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\multipad.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\multipad.obj"	"$(INTDIR)\multipad.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\hlp\multipad.hpj

!IF  "$(CFG)" == "multipad - Win32 Release"

OutDir=.\Release
ProjDir=.
TargetName=cryptool
InputPath=.\hlp\multipad.hpj
USERDEP__MULTI="$(ProjDir)\hlp\AfxCore.rtf"	"$(ProjDir)\hlp\AfxPrint.rtf"	

"$(INTDIR)\cryptool.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__MULTI)
	<<tempfile.bat 
	@echo off 
	call "$(ProjDir)\makehelp.bat"
<< 
	

!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

OutDir=.\Debug
ProjDir=.
TargetName=cryptool
InputPath=.\hlp\multipad.hpj
USERDEP__MULTI="$(ProjDir)\hlp\AfxCore.rtf"	"$(ProjDir)\hlp\AfxPrint.rtf"	

"$(INTDIR)\cryptool.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__MULTI)
	<<tempfile.bat 
	@echo off 
	call "$(ProjDir)\makehelp.bat"
<< 
	

!ENDIF 

SOURCE=.\MultiPad.rc

"$(INTDIR)\MultiPad.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MyDocument.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\MyDocument.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\MyDocument.obj"	"$(INTDIR)\MyDocument.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MyEditView.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\MyEditView.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\MyEditView.obj"	"$(INTDIR)\MyEditView.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\OptionsDialog.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\OptionsDialog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\OptionsDialog.obj"	"$(INTDIR)\OptionsDialog.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\PinCodeDialog.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\PinCodeDialog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\PinCodeDialog.obj"	"$(INTDIR)\PinCodeDialog.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\playfair.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\playfair.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\playfair.obj"	"$(INTDIR)\playfair.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\PlotDoc.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\PlotDoc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\PlotDoc.obj"	"$(INTDIR)\PlotDoc.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\PlotView.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\PlotView.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\PlotView.obj"	"$(INTDIR)\PlotView.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=..\AES\RC6\rc6.c

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\rc6.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\rc6.obj"	"$(INTDIR)\rc6.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Read_Ini_File.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Read_Ini_File.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Read_Ini_File.obj"	"$(INTDIR)\Read_Ini_File.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\AES\Rijndael\rijndael-alg-fst.c"

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\rijndael-alg-fst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\rijndael-alg-fst.obj"	"$(INTDIR)\rijndael-alg-fst.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\AES\Rijndael\rijndael-api-fst.c"

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\rijndael-api-fst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\rijndael-api-fst.obj"	"$(INTDIR)\rijndael-api-fst.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\RsaDec.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RsaDec.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RsaDec.obj"	"$(INTDIR)\RsaDec.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\RsaEnc.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RsaEnc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\RsaEnc.obj"	"$(INTDIR)\RsaEnc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\LibEc\sources\s_prng.c

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\s_prng.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\s_prng.obj"	"$(INTDIR)\s_prng.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\SchluesselAusgabeLinear.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\SchluesselAusgabeLinear.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\SchluesselAusgabeLinear.obj"	"$(INTDIR)\SchluesselAusgabeLinear.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\secude.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\secude.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\secude.obj"	"$(INTDIR)\secude.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SecudeLib.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\SecudeLib.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\SecudeLib.obj"	"$(INTDIR)\SecudeLib.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\AES\Serpent\SERPENT.C

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\SERPENT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\SERPENT.OBJ"	"$(INTDIR)\SERPENT.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sq_mat.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\sq_mat.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\sq_mat.obj"	"$(INTDIR)\sq_mat.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\stdafx.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\stdafx.obj"	"$(INTDIR)\stdafx.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\TextEingabeHillAngriff.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\TextEingabeHillAngriff.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\TextEingabeHillAngriff.obj"	"$(INTDIR)\TextEingabeHillAngriff.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TextOptions.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\TextOptions.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\TextOptions.obj"	"$(INTDIR)\TextOptions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\AES\Twofish\TWOFISH2.C

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\TWOFISH2.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\TWOFISH2.OBJ"	"$(INTDIR)\TWOFISH2.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\ValueList.cpp

!IF  "$(CFG)" == "multipad - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\ValueList.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "..\Secude" /I "..\Libec\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\multipad.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\ValueList.obj"	"$(INTDIR)\ValueList.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\zip\zbits.c

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\zbits.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\zbits.obj"	"$(INTDIR)\zbits.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\zip\zdeflate.c

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\zdeflate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\zdeflate.obj"	"$(INTDIR)\zdeflate.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\zip\zfile_io.c

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\zfile_io.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\zfile_io.obj"	"$(INTDIR)\zfile_io.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\zip\zglobals.c

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\zglobals.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\zglobals.obj"	"$(INTDIR)\zglobals.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\zip\zinflate.c

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\zinflate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\zinflate.obj"	"$(INTDIR)\zinflate.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\zip\zip.c

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\zip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\zip.obj"	"$(INTDIR)\zip.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\zip\zipup.c

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\zipup.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\zipup.obj"	"$(INTDIR)\zipup.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\zip\ztrees.c

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\ztrees.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\ztrees.obj"	"$(INTDIR)\ztrees.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\zip\zunzip.c

!IF  "$(CFG)" == "multipad - Win32 Release"


"$(INTDIR)\zunzip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "multipad - Win32 Debug"


"$(INTDIR)\zunzip.obj"	"$(INTDIR)\zunzip.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

