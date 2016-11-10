
IF EXIST BC.exe GOTO OK

Z:
cd ..
cd \Numbertheory\BC

:OK
bc -lq prims.txt calc.txt | find /V "Poll" | find /V "|" | sort > res.txt
exit

