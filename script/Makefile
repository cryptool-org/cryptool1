all: de en
pdf1: pdf1-de pdf1-en

de:
	$(MAKE) -C de all
en:
	$(MAKE) -C en all

pdf1-de:
	$(MAKE) -C de pdf1
pdf1-en:
	$(MAKE) -C en pdf1

zip:
	rm -f script-`date -I`.zip
	zip script-`date -I`.zip */*.tex */chapters/*.tex de/*.pdf en/*.pdf

clean:
	$(MAKE) -C de clean
	$(MAKE) -C en clean

.PHONY: all de en zip clean
