perl -e 1
if errorlevel 1 goto noperl

perl CheckPopupMenuIDs.pl CrypToolPopupMenuIDs.txt CrypToolPopupMenuIDs.log
if errorlevel 1 exit 1

goto end

:noperl
echo can't execute perl
echo please make sure that perl is installed and in PATH
exit 1

:end
