SRC=*.tex
PDF=DialogueSisters.pdf
DVI=DialogueSisters.dvi
TEX=DialogueSisters.tex
TMP=*.aux *.idx *.ilg *.ind *.log *.out *.toc auto
all: pdf

pdf: $(PDF)
dvi: $(DVI)

$(PDF): $(SRC)
	echo q | pdflatex $(TEX) | tail

$(DVI): $(SRC)
	echo q | latex $(TEX) | tail

cleantmp: 
	-rm -rf $(TMP)

clean: cleantmp
	-rm -f $(PDF) $(DVI)
