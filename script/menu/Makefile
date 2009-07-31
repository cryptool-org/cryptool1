RC = /tmp/CrypTool.rc
all: $(RC)
	perl ./rcmenu.pl -l GERMAN $(RC) >cryptool-menu-de.html
	#perl ./rcmenu.pl -d -l GERMAN $(RC) >cryptool-menu-detail-de.html
	perl ./rcmenu.pl -l ENGLISH $(RC) >cryptool-menu-en.html
	#perl ./rcmenu.pl -d -l ENGLISH $(RC) >cryptool-menu-detail-en.html

$(RC):
	svn cat https://www.cryptool.org/svn/CrypTool/trunk/CrypTool/CrypTool.rc > $(RC)

ps:
	for f in *.pdf; do pdf2ps $$f; done
clean:
	-rm -f cryptool-menu-*.html
