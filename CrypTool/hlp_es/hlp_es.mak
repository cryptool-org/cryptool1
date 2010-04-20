# based on hlp.mak, but depends on english Readme

$(OUTDIR)\CrypTool-$(LANG).chm: *.html *.html.in CrypTool.hhp CrypTool.hhk cryptool.hhc CrypTool_Alias.h images\*.gif ..\..\setup\template-en\ReadMe-en.txt 
	..\MakeHtmlHelp.bat $(LANG)



# !INCLUDE ..\hlp.mak
