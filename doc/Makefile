TEX  = wam.tex header.tex title.tex
TEX += intro.tex literature.tex tutorial.tex disclaimer.tex organization.tex
TEX += unification.tex termrepr.tex cmplqueries.tex cmplprograms.tex argregs.tex
TEX += flatres.tex facts.tex rules.tex

LATEX = pdflatex -halt-on-error

wam.pdf: $(TEX)
	$(LATEX) $< && $(LATEX) $<