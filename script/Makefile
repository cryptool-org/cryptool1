all:
	make -C de all
	make -C en all

zip:
	rm -f script-`date -I`.zip
	zip script-`date -I`.zip */*.tex */chapters/*.tex de/*.pdf en/*.pdf

clean:
	make -C de clean
	make -C en clean

