FILE=texto
LATEX=pdflatex
PDFVIEWR=evince



all: pdf clean



pdf:
	# Compila duas vezes para gerar sumário, links internos, indexação etc
	$(LATEX) $(FILE).tex
	makeindex $(FILE).idx
	$(LATEX) $(FILE).tex
	$(PDFVIEWR) $(FILE).pdf 2> /dev/null &



clean:
	rm -f *.aux *.out *.log *.toc *.idx



cleanup: clean
	rm -f *.pdf
