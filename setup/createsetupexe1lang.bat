@echo off
set lang=%1
set nsi=CrypTool-Setup.nsi
if x%1==xde goto langok
if x%1==xen goto langok
if x%1==xpl goto langok
if x%1==xes goto langok
echo Error: invalid or no argument
echo Usage: %0 [de, en, pl, es] 
goto end

:langok 
if not exist %nsi% goto errorsetup
if not exist setup-%lang%\nul goto errorsetup
goto ok

:errorsetup
echo Error: must be called in a %nsi% and setup-%lang%
goto end

:ok

makensis /DLANGUAGE_STR=%lang% %nsi%
if not errorlevel 1 echo Created SetupCrypTool_%lang%.exe ...

:end

