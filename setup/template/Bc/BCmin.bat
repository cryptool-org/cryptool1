
IF EXIST Bc.exe GOTO OK

Z:
cd ..
cd \Zahlentheorie\BC

:OK
bc -lq prims.txt dislog.txt ecm.txt quadRest.txt calc.txt > res.txt
exit
