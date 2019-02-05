################################################################
# GNU Make Makefile. Building the doc using XML-tools

LANGS = en ru
CHECKS := $(addprefix check-,$(LANGS))

# Oracle tools
XSLTPROC = xsl
XMLVALIDATOR = xml
# libxml2/libxslt
#XSLTPROC = xsltproc
#XMLVALIDATOR = xmllint --valid -noout

.PHONY: all check $(LANGS) $(CHECKS) clean

all: $(LANGS) ;
check: $(CHECKS) ;

define lang_template =
$(1): $(1).html ;
$(1).html: html.xsl $(1)/*.xml
	(cd $(1) && $(XSLTPROC) ../html.xsl index.xml) > $$@
check-$(1):
	cd $(1) && $(XMLVALIDATOR) index.xml
endef

$(foreach lang,$(LANGS),$(eval $(call lang_template,$(lang))))

clean:
	del /Q /F *.html 2>nul
