perl.exe -e 1
if errorlevel 1 goto noperl

perl.exe CheckResourceIDs.pl CrypToolPopupMenuIDs.txt CheckResourceIDs.log
if errorlevel 1 exit 1

goto end

:noperl
echo can't execute perl
echo please make sure that perl is installed and in PATH
echo %PATH%
exit 1

:end