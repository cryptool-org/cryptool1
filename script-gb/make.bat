pdflatex  script-gb.tex
pdflatex  script-gb.tex
makeindex script-gb.idx
pdflatex  script-gb.tex
pdflatex  script-gb.tex
del       script-gb.aux
del       script-gb.idx
del       script-gb.ilg
del       script-gb.log
del       script-gb.toc
del       script-gb.out
del       script-gb.ind
cp        script-gb.pdf ..\multipad\Debug
cp        script-gb.pdf ..\multipad\Release
cp        script-gb.pdf ..\..\release\install
cp        script-gb.pdf ..\..\release\web-site