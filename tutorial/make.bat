pdflatex  tutorial.tex
pdflatex  tutorial.tex
makeindex tutorial.idx
pdflatex  tutorial.tex
pdflatex  tutorial.tex
del       tutorial.aux
del       tutorial.idx
del       tutorial.ilg
del       tutorial.log
del       tutorial.toc
del       tutorial.out
del       tutorial.ind
cp        tutorial.pdf ..\multipad\Debug
cp        tutorial.pdf ..\multipad\Release
cp        tutorial.pdf ..\..\release\install
cp        tutorial.pdf ..\..\release\web-site