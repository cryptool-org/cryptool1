@IF EXIST BC.exe GOTO OK
@echo bc.exe not found
@GOTO END

:OK
@echo This takes a bit ...
@echo It factorizes 9979787976011101, prints all dividers, and writes it to res.txt
bc -lq prims.txt calc.txt | find /V "Poll" | find /V "|" | sort > res.txt
@type res.txt

:END
@rem exit (exit would end the cmd window too)

