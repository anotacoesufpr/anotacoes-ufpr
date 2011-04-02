SHELL=/bin/bash

LATEX=pdflatex


all: graph compile clean


compile:
	$(LATEX) resolucoes.tex
	$(LATEX) resolucoes.tex
	evince resolucoes.pdf 2> /dev/null &

# Gera os grafos com o Graphviz
# Também redimensiona a imagem, proporcionalmente, para ter, no máximo, 500 pixels de laurgura
graph:
	for file in `ls gv` ; do dot -Tpng gv/$$file > img/$${file%.*}.png; mogrify -resize 500 img/$${file%.*}.png; done


clean:
	rm -f *.aux *.toc *.log *.out *.lof
	rm -f resolucoes/*.aux resolucoes/*.toc resolucoes/*.log resolucoes/*.out resolucoes/*.lof
	rm -rf img/*


cleanup: clean
	rm -f resolucoes.pdf
