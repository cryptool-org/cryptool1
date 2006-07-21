@echo off
if not x%1==x set LANG=%1
if x%LANG%==x set LANG=de

if x%OUTDIR%==x set OUTDIR=.\Debug

	rem if MSVCdir is not set call vcvars32 to fix
if x%MSVCdir%==x call vcvars32

set HLP=hlp-%LANG%
set HM=%HLP%\NumberShark.hm

if exist makehelp.no goto :skip
if exist "%HLP%\makehelp.no" goto :skip

REM -- Zuerst Zuordnungsdatei der mit Microsoft Visual C++ erzeugten resource.h erstellen
echo // Von MAKEHELP.BAT erzeugte Hilfe-Zuordnungsdatei. Wird verwendet von NumberShark.HPJ. >%HM%
echo. >>%HM%
echo // Befehle (ID_* and IDM_*) >>%HM%
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>%HM%
echo. >>%HM%
echo // Eingabeaufforderungen (IDP_*) >>%HM%
makehm IDP_,HIDP_,0x30000 resource.h >>%HM%
echo. >>%HM%
echo // Ressourcen (IDR_*) >>%HM%
makehm IDR_,HIDR_,0x20000 resource.h >>%HM%
echo. >>%HM%
echo // Dialogfelder (IDD_*) >>%HM%
makehm IDD_,HIDD_,0x20000 resource.h >>%HM%
echo. >>%HM%
echo // Rahmen-Steuerelemente (IDW_*) >>%HM%
makehm IDW_,HIDW_,0x50000 resource.h >>%HM%
REM -- Hilfe erstellen fr Projekt NumberShark

REM deactivate compression for Debug builds
type "%HLP%\NumberShark.hpj" >"%HLP%\NumberShark.tm1"
if x%OUTDIR%==x.\Debug find /V "COMPRESS=" <"%HLP%\NumberShark.hpj" >"%HLP%\NumberShark.tm1"
REM replace relative path with absolute one
find /V /I "\include\Afxhelp.hm" <"%HLP%\NumberShark.tm1" >"%HLP%\NumberShark.tmp"
del "%HLP%\NumberShark.tm1" >nul:

if "%FrameworkSDKDir%"=="" goto VS6
REM VS.NET
echo #include %MSVCDir%\atlmfc\include\afxhelp.hm >>"%HLP%\NumberShark.tmp"
goto tmpdone
:VS6
echo #include %MSVCDir%\mfc\include\afxhelp.hm >>"%HLP%\NumberShark.tmp"
:tmpdone

echo Creating Win32 Help File...  (Create empty "makehelp.no" or "%HLP%\makehelp.no" to skip)

start /wait hcw /C /E /M "%HLP%\NumberShark.tmp"
if errorlevel 1 goto :Error
if not exist "%HLP%\NumberShark.hlp" goto :ErrorDatei
if not exist "%HLP%\NumberShark.cnt" goto :ErrorDatei
echo.

if exist %OUTDIR%\nul copy "%HLP%\NumberShark.hlp" %OUTDIR%\NumberShark-%LANG%.hlp >nul
if exist %OUTDIR%\nul copy "%HLP%\NumberShark.cnt" %OUTDIR%\NumberShark-%LANG%.cnt >nul
echo.
goto :done

:Error
echo %HLP%\NumberShark.hpj(1) : error: Problem beim Erstellen der Hilfedatei festgestellt: Hilfecompiler konnte nicht fehlerfrei compilieren
goto :done

:ErrorDatei
echo %HLP%\NumberShark.hpj(1) : error: Problem beim Erstellen der Hilfedatei festgestellt: Mindestens eine Datei wurde nicht erstellt
goto :done

:skip
echo Skipping help file generation. Remove "makehelp.no" and "%HLP%\makehelp.no" if this is not what you want
goto :done

:done
echo.
