# this file is include from hlp_*\hlp_*.mak

$(OUTDIR)\CrypTool-$(LANG).chm: *.html *.html.in CrypTool.hhp CrypTool.hhk cryptool.hhc CrypTool_Alias.h images\*.gif ..\..\setup\template-$(LANG)\ReadMe-$(LANG).txt 
	..\MakeHtmlHelp.bat $(LANG)
