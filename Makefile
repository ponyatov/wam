CWD     = $(CURDIR)
MODULE  = $(shell echo $(notdir $(CWD)) | tr "[:upper:]" "[:lower:]" )
OS     ?= $(shell uname -s)

NOW = $(shell date +%d%m%y)
REL = $(shell git rev-parse --short=4 HEAD)

NIMBLE  = $(HOME)/.nimble/bin/nimble
NIM     = $(HOME)/.nimble/bin/nim
NPRETTY = $(HOME)/.nimble/bin/nimpretty



.PHONY: all
all: $(MODULE) $(MODULE).ini
	./$^

SRC = $(shell find $(CWD)/src -type f -regex .+.nim$$)

$(MODULE): $(SRC) $(MODULE).nimble Makefile
	echo $(SRC) | xargs -n1 -P0 nimpretty --indent:2
	nimble --cc:tcc build



.PHONY: doc
doc: doc/wambook.pdf
	cd doc ; echo $(SRC) | xargs -n1 -P0 nim doc
doc/wambook.pdf:
	wget -c -P doc http://wambook.sourceforge.net/wambook.pdf



.PHONY: install update

install: $(OS)_install $(NIMBLE)
update: $(OS)_update

$(NIMBLE):
	curl https://nim-lang.org/choosenim/init.sh -sSf | sh

.PHONY: Linux_install Linux_update

Linux_install Linux_update:
	sudo apt update
	sudo apt install -u `cat apt.txt`




.PHONY: master shadow release

MERGE  = Makefile README.md .gitignore .vscode apt.txt
MERGE += $(MODULE).ini
MERGE += $(MODULE).nimble src tests doc

master:
	git checkout $@
	git pull -v
	git checkout shadow -- $(MERGE)

shadow:
	git checkout $@
	git pull -v

release:
	git tag $(NOW)-$(REL)
	git push -v && git push -v --tags
	$(MAKE) shadow
