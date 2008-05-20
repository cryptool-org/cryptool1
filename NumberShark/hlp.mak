# this file is include from sharkHelp_*\hlp_*.mak

$(OUTDIR)\NumberShark-$(LANG).chm: *.html NumberShark.hhp NumberShark.hhk NumberShark.hhc Pictures_$(LANG)\*.png
	..\MakeHtmlHelp.bat $(LANG)
