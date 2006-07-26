@echo off
echo Create and populate setup-%lang% directory ...
if not exist template\nul goto errortemplate
if x%1==xde goto ok
if x%1==xen goto ok

echo Error: invalid or no argument
echo Usage: setup1lang de  or  setup1lang en
goto end

:ok 
set lang=%1

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
