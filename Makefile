
NOW = $(shell date +%d%m%Y)

release: WAM_ru_$(NOW).pdf
	git tag $(NOW)
WAM_ru_$(NOW).pdf: doc/wam_ru.pdf
	cp $< $@
doc/wam_ru.pdf:
	cd doc ; $(MAKE)
	
doc/wambook.pdf:
	wget -c -P doc http://wambook.sourceforge.net/wambook.pdf

