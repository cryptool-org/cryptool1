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
if x%lang%==xpl xcopy /s/q template-en\*.* setup-%lang%\
echo Copying ..\release_%lang%\*.exe ...
copy ..\release_%lang%\*.exe setup-%lang%
rem script-%lang%.pdf is now in template-%lang%
rem echo Copying ..\release_%lang%\CrypTool-%lang%.chm ...
copy ..\release_%lang%\*-%lang%.chm setup-%lang%
rem echo Copying ..\script\%lang%\script-%lang%.pdf  ...
rem copy ..\script\%lang%\script-%lang%.pdf setup-%lang%
echo Copying ..\dialoguesisters\%lang%\*.pdf setup-%lang%  ...
copy ..\dialoguesisters\%lang%\*.pdf setup-%lang%
echo Copying ..\smimedemo\*.* setup-%lang%\smimedemo ...
REM FIXME: SMIMEDEMO selective copying ...
xcopy /s/q/i ..\smimedemo\font          setup-%lang%\smimedemo\font
xcopy /s/q/i ..\smimedemo\images        setup-%lang%\smimedemo\images
xcopy /s/q/i ..\smimedemo\krypto        setup-%lang%\smimedemo\krypto
xcopy /s/q/i ..\smimedemo\lib           setup-%lang%\smimedemo\lib
xcopy /s/q/i ..\smimedemo\mail          setup-%lang%\smimedemo\mail
xcopy /s/q/i ..\smimedemo\main          setup-%lang%\smimedemo\main
xcopy /s/q/i ..\smimedemo\texte         setup-%lang%\smimedemo\texte
xcopy /s/q/i ..\smimedemo\userinterface setup-%lang%\smimedemo\userinterface
xcopy /s/q/i ..\smimedemo\utils         setup-%lang%\smimedemo\utils
xcopy /q ..\smimedemo\*.* setup-%lang%\smimedemo
echo Copying ..\AES_flow_visualisation\*.* setup-%lang%
xcopy /q ..\AES_flow_visualisation\AES_Flussvisualisierung.jar setup-%lang%
xcopy /q ..\AES_flow_visualisation\rijndael-poster-de.pdf setup-%lang%

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
