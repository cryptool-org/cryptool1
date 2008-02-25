perl.exe -e 1
if errorlevel 1 goto noperl

perl.exe CheckHelp.pl GERMAN hlp_de
perl.exe CheckHelp.pl ENGLISH hlp_en
perl.exe CheckHelp.pl POLISH hlp_pl

if errorlevel 1 exit 1

goto end

:noperl
echo can't execute perl
echo please make sure that perl is installed and in PATH
echo %PATH%
exit 1

:end