@echo For sample calls see CT1 online help about BC or click F8 in the program "Number Theory"
@echo Sample usage: quadsieb( 57599823021569033350933 )
@echo Remark: Almost always crashed under Windows (be).
@echo Output just after starting -- written into res.txt
@echo ## Hier klar, welcher Aufruf in sieb.txt diesen Output bewirkt.
@echo 17401
@echo 7927
@echo ## Welcher Aufruf in sieb.txt führt zu diesem Output?
@echo |||||||||||||Primteiler: 15261481 653920021 
@echo Teiler
@echo                1
@echo         15261481
@echo        653920021
@echo 9979787976011101
@echo Summe: 9979788645192604
@echo Anzahl: 4
@rem bc -lq prims.txt quadrest.txt sieb.txt seed calc.txt
bc -lq prims.txt quadrest.txt sieb.txt seed calc.txt > res.txt

