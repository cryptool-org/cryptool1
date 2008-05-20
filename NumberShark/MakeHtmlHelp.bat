@echo off

if not x%1==x set LANG=%1
if x%LANG%==x set LANG=de

if x%OUTDIR%==x set OUTDIR=.\Debug

rem if MSVCdir is not set call vcvars32 to fix
if "%MSVCdir%"=="" call vcvars32

set HLP=sharkHelp_%LANG%
set HM=NumberShark.hm



echo Compiling the help: NumberShark-%LANG%.chm 

start /wait hhc.exe NumberShark.hhp
REM For some reason, HHC returns one on success.
if not errorlevel 1 goto Error

mkdir %OUTDIR% 2>nul
echo copy "NumberShark-%LANG%.chm" %OUTDIR% 
copy "NumberShark-%LANG%.chm" %OUTDIR% 
if errorlevel 1 exit 1

goto done

:noperl
echo can't execute perl
echo please make sure that perl is installed and in PATH
exit 1

:Error													
echo NumberShark.hhp : FAILURE: the help compiler could not compile without failures. Please see NumberShark.log.
goto done

:skip														
echo Skipping help file generation. Remove "makehelp.no" and "makehelp.no" if this is not what you want	
goto done													

:done													
echo.

