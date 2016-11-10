IF EXIST BC.exe GOTO OK

Z:
cd ..
cd \Zahlentheorie\Bc

:OK
cls
@rem Feb2012: Sorted out quadratic sieve function within ZT tutorial, as bc with sieb.txt crashes under Win7
@rem Nov2016: Worked under Win10 both directly calling bcmax and from within NT (sometimes problems with dislog.txt?)
@rem bc -lq prims.txt dislog.txt ecm.txt quadRest.txt sieb.txt seed
@echo Use  quit  to exit
bc -lq prims.txt dislog.txt ecm.txt quadRest.txt seed


