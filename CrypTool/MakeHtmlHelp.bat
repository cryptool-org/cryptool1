@echo off

if not x%1==x set LANG=%1
if x%LANG%==x set LANG=de

if x%OUTDIR%==x set OUTDIR=.\Debug

rem if MSVCdir is not set call vcvars32 to fix
if x%MSVCdir%==x call vcvars32

set HLP=hlp_%LANG%
set HM=%HLP%\CrypTool.hm

if exist makehelp.no goto :skip									
if exist "%HLP%\makehelp.no" goto :skip								

REM -- Zuerst Zuordnungsdatei der mit Microsoft Visual C++ erzeugten resource.h erstellen
echo // Automatically generated file while compilation. Do NOT edit this file manually. >%HM%		
echo. >>%HM%
echo // Commands (ID_* and IDM_*) >>%HM%								
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>%HM%
echo. >>%HM%
echo // Prompts (IDP_*) >>%HM%									
makehm IDP_,HIDP_,0x30000 resource.h >>%HM%
echo. >>%HM%
echo // Ressources (IDR_*) >>%HM%								
makehm IDR_,HIDR_,0x20000 resource.h >>%HM%
echo. >>%HM%
echo // Dialogs (IDD_*) >>%HM%									
makehm IDD_,HIDD_,0x20000 resource.h >>%HM%
echo. >>%HM%
echo // Frame Controls (IDW_*) >>%HM%									
makehm IDW_,HIDW_,0x50000 resource.h >>%HM%
REM -- Hilfe erstellen fuer Projekt CrypTool


echo Converting CrypTool.hm to CrypTool_helpIDs.h by means of hh_generator.pl 

perl -e 1
if errorlevel 1 goto noperl

perl hh_generator.pl %LANG%

if errorlevel 1 exit 1

echo Compiling the help: CrypTool-%LANG%.chm 

start /wait hhc.exe %HLP%\CrypTool.hhp
REM For some reason, HHC returns one on success.
if not errorlevel 1 goto Error

echo copy "%HLP%\CrypTool-%LANG%.chm" %OUTDIR% 
copy "%HLP%\CrypTool-%LANG%.chm" %OUTDIR% 

goto done

:noperl
echo can't execute perl
echo please make sure that perl is installed and in PATH
exit 1

:Error													
echo %HLP%\CrypTool.hhp : FAILURE: the help compiler could not compile without failures. Please see %HLP%\CrypTool.log.
goto done

:skip														
echo Skipping help file generation. Remove "makehelp.no" and "%HLP%\makehelp.no" if this is not what you want	
goto done													

:done													
echo.

