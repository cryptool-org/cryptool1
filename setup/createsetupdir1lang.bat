rem create and populate setup-%lang% directory 
if not exist template\nul goto errortemplate
if x%1==xde goto ok
if x%1==xen goto ok

echo error: invalid or no argument
echo usage: setup1lang de  or  setup1lang en
goto end

:ok 
set lang=%1
set otherlang=de
if %lang%==de set otherlang=en

if exist setup-%lang%\nul rmdir /q/s setup-%lang%
xcopy /s/q template\*.* setup-%lang%\
copy ..\release_%lang%\*.exe setup-%lang%
copy ..\release_%lang%\CrypTool-%lang%.hlp setup-%lang%
copy ..\release_%lang%\CrypTool-%lang%.cnt setup-%lang%
copy ..\script\%lang%\script-%lang%.pdf setup-%lang%
copy ..\dialoguesisters\%lang%\*.pdf setup-%lang%


cd setup-%lang%
rmdir /s/q CVS
rmdir /s/q examples\CVS
rmdir /s/q pse\CVS
rmdir /s/q pse\pseca\CVS
rmdir /s/q reference\CVS
del ReadMe-%otherlang%.txt

set sum=md5sum
%sum% * 2>nul  | perl -pe "$_ = '' if m{ReadMe-...txt}" >..\%sum%-%lang%.txt 
%sum% examples\* 2>nul | perl -pe "s{\\\\}{\\}g;s{^\\}{}" >>..\%sum%-%lang%.txt
%sum% pse\pseca\* 2>nul | perl -pe "s{\\\\}{\\}g;s{^\\}{}" >>..\%sum%-%lang%.txt
%sum% reference\* 2>nul | perl -pe "s{\\\\}{\\}g;s{^\\}{}" >>..\%sum%-%lang%.txt
perl -i.bak -p ..\subst.pl XXX%sum%XXX ..\%sum%-%lang%.txt ReadMe-%lang%.txt
del ReadMe-%lang%.txt.bak >nul
del ..\%sum%-%lang%.txt >nul

set sum=sha1sum
%sum% * 2>nul  | perl -pe "$_ = '' if m{ReadMe-...txt}" >..\%sum%-%lang%.txt 
%sum% examples/* 2>nul | perl -pe "s{/}{\\}g" >>..\%sum%-%lang%.txt
%sum% pse/pseca/* 2>nul | perl -pe "s{/}{\\}g" >>..\%sum%-%lang%.txt
%sum% reference/* 2>nul | perl -pe "s{/}{\\}g" >>..\%sum%-%lang%.txt
perl -i.bak -p ..\subst.pl XXX%sum%XXX ..\%sum%-%lang%.txt ReadMe-%lang%.txt
del ReadMe-%lang%.txt.bak >nul
del ..\%sum%-%lang%.txt >nul

cd ..


goto end

:errortemplate
echo template dir not found!
echo cd to the setup directory.
goto end


:end
