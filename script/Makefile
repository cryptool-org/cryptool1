all: de en

de:
	$(MAKE) -C de all
en:
	$(MAKE) -C en all

zip:
	rm -f script-`date -I`.zip
	zip script-`date -I`.zip */*.tex */chapters/*.tex de/*.pdf en/*.pdf

clean:
	$(MAKE) -C de clean
	$(MAKE) -C en clean

.PHONY: all de en zip clean
