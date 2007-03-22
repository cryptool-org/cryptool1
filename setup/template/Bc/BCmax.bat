IF EXIST BC.exe GOTO OK

Z:
cd ..
cd \Zahlentheorie\Bc

:OK
cls
bc -lq prims.txt dislog.txt ecm.txt quadRest.txt sieb.txt seed


