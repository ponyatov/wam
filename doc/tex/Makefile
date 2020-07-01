TEX  = wam_ru.tex header.tex title.tex bib.tex
TEX += intro.tex foreword.tex 
TEX += literature.tex tutorial.tex disclaimer.tex organization.tex
TEX += unification.tex termrepr.tex cmplqueries.tex cmplprograms.tex argregs.tex
TEX += flatres.tex facts.tex rules.tex
TEX += prolog.tex envprotect.tex choicepoint.tex
TEX += optimizing.tex heaprepr.tex listvars.tex set.tex regalloc.tex
TEX += tailcall.tex chain.tex envtrim.tex
TEX += stackvars.tex binding.tex unsafe.tex nestref.tex
TEX += varclass.tex indexing.tex cut.tex
TEX += conclusion.tex nutshell.tex
TEX += ataglance.tex WAMins.tex WAMancops.tex WAMmemory.tex

LATEX = pdflatex -halt-on-error

wam_ru.pdf: $(TEX)
	$(LATEX) $< && $(LATEX) $<