LANG=en
SRC=script-$(LANG).tex chapters/*.tex figures/*.pdf figures/*.eps figures/*.latex
PDF=script-$(LANG).pdf
DVI=script-$(LANG).dvi
TEX=script-$(LANG).tex
IDX=script-$(LANG).idx
TMP=*.aux *.idx *.ilg *.ind *.log *.out *.toc auto
all: pdf

pdf: $(PDF)
dvi: $(DVI)

$(PDF): $(SRC) style.ist
	echo q | latex $(TEX) | tail
	echo q | latex $(TEX) | tail
	makeindex -s style.ist $(IDX)
	echo q | latex $(TEX) | tail
	echo q | latex $(TEX) | tail
	dvipdf $(DVI) $(PDF)

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
