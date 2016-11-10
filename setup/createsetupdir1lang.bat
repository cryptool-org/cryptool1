@echo off
if not exist template\nul goto errortemplate
if x%1==xde goto ok
if x%1==xen goto ok
if x%1==xes goto ok
if x%1==xpl goto ok
if x%1==xrs goto ok
if x%1==xel goto ok
if x%1==xfr goto ok

echo Error: invalid or no argument
echo Usage: setup1lang [de, en, es, pl, rs, el, fr]
goto end

:ok 
set lang=%1
set lang_sub=%lang%

rem all languages except de+en use some English (en) files 
if x%lang%==xes set lang_sub=en
if x%lang%==xpl set lang_sub=en
if x%lang%==xrs set lang_sub=en
if x%lang%==xel set lang_sub=en
if x%lang%==xfr set lang_sub=en

echo Create and populate setup-%lang% directory ...
if exist setup-%lang%\nul rmdir /q/s setup-%lang%

echo Copying template ...
xcopy /s/q template\*.* setup-%lang%\

echo Copying template-%lang% ...
xcopy /s/q template-%lang%\*.* setup-%lang%\   
if x%lang%==xes xcopy /s/q template-en\*.* setup-%lang%\ & del setup-%lang%\license-en.rtf & del setup-%lang%\CrypToolPresentation-en.pdf & del setup-%lang%\Rijndael-Inspector.exe & del setup-%lang%\Rijndael-Animation.exe & del setup-%lang%\Enigma_en.exe & del setup-%lang%\Enigma-Help_en.html & del setup-%lang%\enigma_screenshot1.png
if x%lang%==xpl xcopy /s/q template-en\*.* setup-%lang%\ & del setup-%lang%\license-en.rtf & del setup-%lang%\Enigma_en.exe & del setup-%lang%\Enigma-Help_en.html & del setup-%lang%\enigma_screenshot1.png
if x%lang%==xrs xcopy /s/q template-en\*.* setup-%lang%\ & del setup-%lang%\license-en.rtf
if x%lang%==xel xcopy /s/q template-en\*.* setup-%lang%\ & del setup-%lang%\license-en.rtf
if x%lang%==xfr xcopy /s/q template-en\*.* setup-%lang%\ & del setup-%lang%\license-en.rtf

echo Copying ..\release_%lang%\*.exe ...
copy ..\release_%lang%\*.exe setup-%lang%

echo Copying ..\release_%lang_sub%\*-%lang_sub%.chm ...
copy ..\release_%lang_sub%\*-%lang_sub%.chm setup-%lang%

echo Copying ..\dialoguesisters\%lang_sub%\*.pdf setup-%lang%  ...
copy ..\dialoguesisters\%lang_sub%\*.pdf setup-%lang%

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
xcopy /q ..\CrypTool\hlp_%lang_sub%\images\enigma_screenshot1.png setup-%lang%

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
