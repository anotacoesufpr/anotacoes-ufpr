LATEX=pdflatex


all: compile clean


compile:
	$(LATEX) resolucoes.tex
	$(LATEX) resolucoes.tex
	evince resolucoes.pdf 2> /dev/null &


clean:
	rm -f *.aux *.toc *.log *.out
	rm -f resolucoes/*.aux resolucoes/*.toc resolucoes/*.log resolucoes/*.out


cleanup: clean
	rm -f resolucoes.pdf
