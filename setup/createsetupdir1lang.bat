@echo off
if not exist template\nul goto errortemplate
if x%1==xde goto ok
if x%1==xen goto ok
if x%1==xpl goto ok

echo Error: invalid or no argument
echo Usage: setup1lang de  or  setup1lang en  or  setup1lang pl
goto end

:ok 
set lang=%1
echo Create and populate setup-%lang% directory ...

if exist setup-%lang%\nul rmdir /q/s setup-%lang%
echo Copying template ...
xcopy /s/q template\*.* setup-%lang%\
echo Copying template-%lang% ...
xcopy /s/q template-%lang%\*.* setup-%lang%\
echo Copying ..\release_%lang%\*.exe ...
copy ..\release_%lang%\*.exe setup-%lang%
echo Copying ..\release_%lang%\CrypTool-%lang%.chm ...
copy ..\release_%lang%\*-%lang%.chm setup-%lang%
echo Copying ..\script\%lang%\script-%lang%.pdf  ...
copy ..\script\%lang%\script-%lang%.pdf setup-%lang%
echo Copying ..\dialoguesisters\%lang%\*.pdf setup-%lang%  ...
copy ..\dialoguesisters\%lang%\*.pdf setup-%lang%
echo Copying ..\smimedemo\*.* setup-%lang% ...
REM FIXME: SMIMEDEMO selective copying ...
xcopy /q ..\smimedemo\*.* setup-%lang%
xcopy /s/q/i ..\smimedemo\font          setup-%lang%\font
xcopy /s/q/i ..\smimedemo\images        setup-%lang%\images
xcopy /s/q/i ..\smimedemo\krypto        setup-%lang%\krypto
xcopy /s/q/i ..\smimedemo\lib           setup-%lang%\lib
xcopy /s/q/i ..\smimedemo\mail          setup-%lang%\mail
xcopy /s/q/i ..\smimedemo\main          setup-%lang%\main
xcopy /s/q/i ..\smimedemo\texte         setup-%lang%\texte
xcopy /s/q/i ..\smimedemo\userinterface setup-%lang%\userinterface
xcopy /s/q/i ..\smimedemo\utils         setup-%lang%\utils


cd setup-%lang%

set sum=md5sum
echo Creating %sum%.txt ...
perl ..\finddigest.pl %sum% . >..\%sum%.txt 

set sum=sha1sum
echo Creating %sum%.txt ...
perl ..\finddigest.pl %sum% . >..\%sum%.txt 

move ..\md5sum.txt .
move ..\sha1sum.txt .
cd ..

echo.

goto end

:errortemplate
echo template dir not found!
echo cd to the setup directory.
goto end


:end
