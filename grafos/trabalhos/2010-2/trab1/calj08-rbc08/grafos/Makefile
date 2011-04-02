

# Gera os grafos com o Graphviz
all:
	for file in `ls *.gv` ; do dot -Tpng $$file > $${file%.*}.png; done

clean:
	rm -f *.png
