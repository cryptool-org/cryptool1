if not exist template\nul goto error

set lang=de
if exist setup-%lang%\nul rmdir /q/s setup-%lang%
xcopy /s/q template\*.* setup-%lang%\
copy ..\release_%lang%\*.exe setup-%lang%

cd setup-%lang%
rmdir /s/q CVS
rmdir /s/q examples\CVS
rmdir /s/q pse\CVS
rmdir /s/q pse\pseca\CVS
rmdir /s/q reference\CVS
set sum=md5sum
%sum% * 2>nul  | perl -pe "$_ = '' if m{ReadMe-...txt}" >..\%sum%-%lang%.txt 
%sum% examples\* 2>nul | perl -pe "s{\\\\}{\\}g;s{^\\}{}" >>..\%sum%-%lang%.txt
%sum% pse\pseca\* 2>nul | perl -pe "s{\\\\}{\\}g;s{^\\}{}" >>..\%sum%-%lang%.txt
%sum% reference\* 2>nul | perl -pe "s{\\\\}{\\}g;s{^\\}{}" >>..\%sum%-%lang%.txt

set sum=sha1sum
%sum% * 2>nul  | perl -pe "$_ = '' if m{ReadMe-...txt}" >..\%sum%-%lang%.txt 
%sum% examples/* 2>nul | perl -pe "s{/}{\\}g" >>..\%sum%-%lang%.txt
%sum% pse/pseca/* 2>nul | perl -pe "s{/}{\\}g" >>..\%sum%-%lang%.txt
%sum% reference/* 2>nul | perl -pe "s{/}{\\}g" >>..\%sum%-%lang%.txt

cd ..

set lang=en
if exist setup-%lang%\nul rmdir /q/s setup-%lang%
xcopy /s/q template\*.* setup-%lang%\
copy ..\release_%lang%\*.exe setup-%lang%

cd setup-%lang%
rmdir /s/q CVS
rmdir /s/q examples\CVS
rmdir /s/q pse\CVS
rmdir /s/q pse\pseca\CVS
rmdir /s/q reference\CVS
set sum=md5sum
%sum% * 2>nul  | perl -pe "$_ = '' if m{ReadMe-...txt}" >..\%sum%-%lang%.txt 
%sum% examples\* 2>nul | perl -pe "s{\\\\}{\\}g;s{^\\}{}" >>..\%sum%-%lang%.txt
%sum% pse\pseca\* 2>nul | perl -pe "s{\\\\}{\\}g;s{^\\}{}" >>..\%sum%-%lang%.txt
%sum% reference\* 2>nul | perl -pe "s{\\\\}{\\}g;s{^\\}{}" >>..\%sum%-%lang%.txt

set sum=sha1sum
%sum% * 2>nul  | perl -pe "$_ = '' if m{ReadMe-...txt}" >..\%sum%-%lang%.txt 
%sum% examples/* 2>nul | perl -pe "s{/}{\\}g" >>..\%sum%-%lang%.txt
%sum% pse/pseca/* 2>nul | perl -pe "s{/}{\\}g" >>..\%sum%-%lang%.txt
%sum% reference/* 2>nul | perl -pe "s{/}{\\}g" >>..\%sum%-%lang%.txt

cd ..


rem set sum=md5sum
rem set sum=sha1sum
rem perl -pe "$|=1; if (/XXX%sum%XXX/) { $_=''; open(F,'<..\\%sum%.txt') or die 'open'; undef $/; print <F>; close F;}" ..\template\ReadMe-%lang%.txt  > ReadMe-%lang%.txt


goto end

:error
echo template dir not found!
echo cd to the setup directory.

:end