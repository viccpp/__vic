################################################################
# GNU Make Makefile. Building the doc using Oracle XML-utils

LANGS = en

.PHONY: all en check

all: $(LANGS) ;

en: en.html ;

en.html: html.xsl en/*.xml
	(cd en && xsl ../html.xsl index.xml) > $@

check:
	cd en && xml index.xml
