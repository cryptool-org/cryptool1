@echo off
if not x%1==x set LANG=%1
if x%LANG%==x set LANG=de

if x%OUTDIR%==x set OUTDIR=.\Debug

	rem if MSVCdir is not set call vcvars32 to fix
if x%MSVCdir%==x call vcvars32

set HLP=hlp-%LANG%
set HM=%HLP%\CrypTool.hm

if exist makehelp.no goto :skip
if exist "%HLP%\makehelp.no" goto :skip

REM -- Zuerst Zuordnungsdatei der mit Microsoft Visual C++ erzeugten resource.h erstellen
echo // Von MAKEHELP.BAT erzeugte Hilfe-Zuordnungsdatei. Wird verwendet von CrypTool.HPJ. >%HM%
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
REM -- Hilfe erstellen fr Projekt CrypTool

REM deactivate compression for Debug builds
type "%HLP%\CrypTool.hpj" >"%HLP%\CrypTool.tm1"
if x%OUTDIR%==x.\Debug find /V "COMPRESS=" <"%HLP%\CrypTool.hpj" >"%HLP%\CrypTool.tm1"
REM replace relative path with absolute one
find /V /I "\include\Afxhelp.hm" <"%HLP%\CrypTool.tm1" >"%HLP%\CrypTool.tmp"
del "%HLP%\CrypTool.tm1" >nul:

if "%FrameworkSDKDir%"=="" goto VS6
REM VS.NET
echo #include %MSVCDir%\atlmfc\include\afxhelp.hm >>"%HLP%\CrypTool.tmp"
goto tmpdone
:VS6
echo #include %MSVCDir%\mfc\include\afxhelp.hm >>"%HLP%\CrypTool.tmp"
:tmpdone

echo Creating Win32 Help File...  (Create empty "makehelp.no" or "%HLP%\makehelp.no" to skip)

start /wait hcw /C /E /M "%HLP%\CrypTool.tmp"
if errorlevel 1 goto :Error
if not exist "%HLP%\CrypTool.hlp" goto :ErrorDatei
if not exist "%HLP%\CrypTool.cnt" goto :ErrorDatei
echo.

if exist %OUTDIR%\nul copy "%HLP%\CrypTool.hlp" %OUTDIR%\CrypTool-%LANG%.hlp >nul
if exist %OUTDIR%\nul copy "%HLP%\CrypTool.cnt" %OUTDIR%\CrypTool-%LANG%.cnt >nul
echo.
goto :done

:Error
echo %HLP%\CrypTool.hpj(1) : error: Problem beim Erstellen der Hilfedatei festgestellt: Hilfecompiler konnte nicht fehlerfrei compilieren
goto :done

:ErrorDatei
echo %HLP%\CrypTool.hpj(1) : error: Problem beim Erstellen der Hilfedatei festgestellt: Mindestens eine Datei wurde nicht erstellt
goto :done

:skip
echo Skipping help file generation. Remove "makehelp.no" and "%HLP%\makehelp.no" if this is not what you want
goto :done

:done
echo.
