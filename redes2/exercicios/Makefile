LATEX=pdflatex
FILE=exercicios

PDFVIEWR=evince

all: pdf clean

pdf:
	# Compila duas vezes para gerar o sumário
	$(LATEX) $(FILE).tex
	$(LATEX) $(FILE).tex
	$(PDFVIEWR) $(FILE).pdf &

clean:
	rm -f *.aux *.out *.log *.toc

cleanup: clean
	rm *.pdf
