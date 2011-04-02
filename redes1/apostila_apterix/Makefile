LATEX=pdflatex
FILE=apostila

all: pdf

pdf:
	# Compila duas vezes para gerar o sumário
	$(LATEX) $(FILE).tex
	$(LATEX) $(FILE).tex

clean:
	rm -f *.aux *.out *.log *.toc

cleanup: clean
	rm *.pdf
