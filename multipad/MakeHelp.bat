@echo off
REM -- Zuerst Zuordnungsdatei der mit Microsoft Visual C++ erzeugten resource.h erstellen
echo // Von MAKEHELP.BAT erzeugte Hilfe-Zuordnungsdatei. Wird verwendet von multipad.HPJ. >"hlp\multipad.hm"
echo. >>"hlp\multipad.hm"
echo // Befehle (ID_* and IDM_*) >>"hlp\multipad.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\multipad.hm"
echo. >>"hlp\multipad.hm"
echo // Eingabeaufforderungen (IDP_*) >>"hlp\multipad.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\multipad.hm"
echo. >>"hlp\multipad.hm"
echo // Ressourcen (IDR_*) >>"hlp\multipad.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\multipad.hm"
echo. >>"hlp\multipad.hm"
echo // Dialogfelder (IDD_*) >>"hlp\multipad.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\multipad.hm"
echo. >>"hlp\multipad.hm"
echo // Rahmen-Steuerelemente (IDW_*) >>"hlp\multipad.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\multipad.hm"
REM -- Hilfe erstellen fÅr Projekt multipad


echo Win32 Hilfedateien werden erstellt...
start /wait hcw /C /E /M "hlp\multipad.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\CrypTool-de.hlp" goto :ErrorDatei
if not exist "hlp\CrypTool-de.cnt" goto :ErrorDatei
echo.
if exist Debug\nul copy "hlp\CrypTool-de.hlp" Debug
if exist Debug\nul copy "hlp\CrypTool-de.cnt" Debug
if exist Release\nul copy "hlp\CrypTool-de.hlp" Release
if exist Release\nul copy "hlp\CrypTool-de.cnt" Release
echo.
goto :done

:Error
echo hlp\multipad.hpj(1) : error: Problem beim Erstellen der Hilfedatei festgestellt: Hilfecompiler konnte nicht fehlerfrei compilieren
goto :done

:ErrorDatei
echo hlp\multipad.hpj(1) : error: Problem beim Erstellen der Hilfedatei festgestellt: Mindestens eine Datei wurde nicht erstellt
goto :done

:done
echo.
