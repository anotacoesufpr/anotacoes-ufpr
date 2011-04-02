#!/bin/bash
#
# Cria um arquivo com o preâmbulo do Latex e as tags básicas
# Também cria um Makefile para a compilação
#
# A compilação é feita com o pdflatex. Caso não possua esse programa, instale o
# pacote texlive, disponível nos repositórios do Debian/Ubuntu
#
# ./initLatex.sh [nome_arquivo]
#
# Caso não seja passado o parâmetro nome_arquivo, cria texto.tex


# função para criar arquivo. Verifica se já existe um arquivo homônimo. Caso
# exista, questiona o usuário sobre o que fazer.
# ( opções não muito tolerantes... =P )
# @param filename Nome do arquivo a ser criado
criarArquivo()
{
	if [ $# -ne 1 ]
	then
		echo "Erro. Uso: criarArquivo <nome_do_arquivo>";
		exit
	fi
	
	local FILE=$1

	if [ -f $FILE ]
	then
		echo "O arquivo " $FILE " já existe. Deseja sobrescrevê-lo? [S/N]"
		read -n 1  op
		echo ""

		if [ "$op" == "s" ] || [ "$op" == "S" ]
		then
			rm -f $FILE
		elif [ "$op" == "n" ] || [ "$op" == "N" ]
		then
			echo -e "Besta!\nRode o programa com outro parâmetro"
			exit
		else
			echo -e "Besta!\nOpção inválida"
			exit
		fi
	fi

	touch $FILE
}


# Número de parâmetros do programa principal
if [ $# -gt 0 ]
then
	FILE=$1
else
	FILE="texto.tex"
fi


criarArquivo $FILE 
criarArquivo "Makefile"




#############################
## CRIAÇÃO DO ARQUIVO .TEX
#############################

echo "\documentclass{article}" >> $FILE
echo -e "\n" >> $FILE
echo "\usepackage[utf8]{inputenc}" >> $FILE
echo "\usepackage[T1]{fontenc}" >> $FILE
echo "\usepackage[brazil]{babel}" >> $FILE
echo "\usepackage[pdftex,pagebackref=true,colorlinks=true,linkcolor=blue,unicode]{hyperref}" >> $FILE
echo "\usepackage[paper=a4paper,lmargin=2.0cm, rmargin=2.0cm, tmargin=2.0cm, bmargin=2.0cm]{geometry}" >> $FILE
echo "\usepackage{graphicx}" >> $FILE
echo "\usepackage{makeidx}" >> $FILE
echo "\usepackage{hyperref}" >> $FILE
echo "\usepackage{enumerate}" >> $FILE
echo "\usepackage{indentfirst}" >> $FILE
echo -e "\n" >> $FILE
echo "\title{}" >> $FILE
echo "\author{}" >> $FILE
echo "%\date{}" >> $FILE
echo -e "\n" >> $FILE
echo "\makeindex" >> $FILE
echo -e "\n" >> $FILE
echo "\begin{document}" >> $FILE
echo -e "\n" >> $FILE
echo "\maketitle" >> $FILE
echo "\tableofcontents" >> $FILE
echo -e "\n" >> $FILE
echo "\newpage" >> $FILE
echo -e "\n" >> $FILE
echo "%====================================================" >> $FILE
echo -e "\n\n" >> $FILE
echo "%====================================" >> $FILE
echo -e "\n\n" >> $FILE
echo "\printindex" >> $FILE
echo -e "\n\n" >> $FILE
echo "\end{document}" >> $FILE




########################
## CRIAÇÃO DO MAKEFILE
#######################

echo "FILE="${FILE%.*} >> "Makefile"
echo "LATEX=pdflatex" >> "Makefile"
echo "PDFVIEWR=evince" >> "Makefile"
echo -e "\n\n" >> "Makefile"
echo "all: pdf clean" >> "Makefile"
echo -e "\n\n" >> "Makefile"
echo "pdf:" >> "Makefile"
echo "	# Compila duas vezes para gerar sumário, links internos, indexação etc" >> "Makefile"
echo "	\$(LATEX) \$(FILE).tex" >> "Makefile"
echo "	\$(LATEX) \$(FILE).tex" >> "Makefile"
echo "	\$(PDFVIEWR) \$(FILE).pdf &" >> "Makefile"
echo -e "\n\n" >> "Makefile"
echo "clean:" >> "Makefile"
echo "	rm -f *.aux *.out *.log *.toc *.idx" >> "Makefile"
echo -e "\n\n" >> "Makefile"
echo "cleanup: clean" >> "Makefile"
echo "	rm -f *.pdf" >> "Makefile"

#########################################


echo "Gerado base do LaTeX no arquivo \""$FILE"\", com o Makefile correspondente.
Basta digitar \"make\" para compilar e abrir o PDF"

