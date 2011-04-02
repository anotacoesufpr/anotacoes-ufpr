LATEX=pdflatex
FILENAME=trabalho

all: compile clean


compile:
	$(LATEX) $(FILENAME).tex
	makeindex $(FILENAME)
	$(LATEX) $(FILENAME).tex
	evince $(FILENAME).pdf 2> /dev/null &

clean:
	rm -f *.aux *.toc *.log *.out *.lof *bak *idx *ilg *ind


cleanup: clean
	rm -f $(FILENAME).pdf
