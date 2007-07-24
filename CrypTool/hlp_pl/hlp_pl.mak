#tworzenie pliku pomocy

CrypTool-pl.chm: *.html *.html.in CrypTool.hhp CrypTool.hhk cryptool.hhc CrypTool_Alias.h images\*.gif 
	cd..
	MakeHtmlHelp.bat pl

#aby wyeliminowaæ b³¹d PRJ0003 error spawning, muszê jeszcze napisac target clean