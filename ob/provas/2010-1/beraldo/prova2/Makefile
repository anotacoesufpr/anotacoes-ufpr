all:
	pdflatex texto.tex && \
	bibtex texto && \
	pdflatex texto.tex && \
	pdflatex texto.tex && \
	evince texto.pdf  &

clean:
	rm *.aux *.out *.log *.bbl *.blg


cleanup: clean
	rm *.pdf
