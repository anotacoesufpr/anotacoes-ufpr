FILE=texto

all:latex clean


latex:
	pdflatex $(FILE).tex
	bibtex $(FILE)
	pdflatex $(FILE).tex
	pdflatex $(FILE).tex
	#evince $(FILE).pdf 

clean:
	rm -f *.aux *.out *.log *.bbl *.blg *.toc 2> /dev/null


cleanup: clean
	rm -f *.pdf 2> /dev/null
