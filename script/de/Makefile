LANG=de
SRC=script-$(LANG).tex references.bib chapters/*.tex figures/*.pdf figures/*.eps figures/*.latex
PDF=script-$(LANG).pdf
DVI=script-$(LANG).dvi
TEX=script-$(LANG).tex
IDX=script-$(LANG).idx
TMP=*.aux *.idx *.ilg *.ind *.log *.out *.toc *.bbl *.blg auto
all: pdf

pdf: $(PDF)

$(PDF): $(SRC) style.ist
	echo q | pdflatex $(TEX) | tail
	echo q | pdflatex $(TEX) | tail
	for f in bu*.aux; do bibtex $$f; done
	makeindex -s style.ist $(IDX)
	echo q | pdflatex $(TEX) | tail
	echo q | pdflatex $(TEX) | tail

pdf1: 
	echo q | pdflatex $(TEX) | tail

dvi: $(DVI)

script-$(LANG).ind: script-$(LANG).idx style.ist
	makeindex -s style.ist script-$(LANG).idx

script-$(LANG).idx: $(SRC) 
	echo q | latex $(TEX) | tail

$(DVI): $(TEX) figures/* chapters/* script-$(LANG).ind
	echo q | latex $(TEX) | tail

cleantmp: 
	-rm -rf $(TMP)

clean: cleantmp
	-rm -f $(PDF) $(DVI)
