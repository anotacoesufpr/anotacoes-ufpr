#!/bin/bash
#
# Filtra os tracefiles do ns e gera o gŕafico com o gnuplot(1)


# Inclui o arquivo de configurações
. config.conf


#-----------------------------------------------------------------------------------------------------
######### LATÊNCIA DE REDE 

for (( i = 0 ; i < 4; i++ ))
do
	output=$ARQ_LATENCIA_XY""$i
	awk -v output=$output -v intervalo=$intervalo -f $SCRIPT_LATENCIA ${TRACEFILE[$i]}
done



# Criação do arquivo de configuração do GNUPlot para a latência
echo -e "
set title 'Latência da Rede'
set xlabel 'Numero de pacotes'
set ylabel 'latência (ms)'
set key right bottom
set terminal png
set output '"$ARQ_LATENCIA_GRAPH"'
plot '"$ARQ_LATENCIA_XY"0""' using 1:2 with lines title '30 transmissores', \\
'"$ARQ_LATENCIA_XY"1""' using 1:2 with lines title '40 transmissores', \\
'"$ARQ_LATENCIA_XY"2""' using 1:2 with lines title '50 transmissores', \\
'"$ARQ_LATENCIA_XY"3""' using 1:2 with lines title '60 transmissores'
" > $ARQ_LATENCIA_GNU



# Gera o gráfico de latência
gnuplot $ARQ_LATENCIA_GNU

#se o gnuplot rodou com sucesso
if [ $? -eq 0 ]
then
	echo "Gráfico da latência da rede gerado no arquivo '"$ARQ_LATENCIA_GRAPH"'"
else
	echo "Erro ao gerar arquivo do gráfico da latência de rede"
fi



#-----------------------------------------------------------------------------------------------------
##### TAXA DE ENTREGA

for (( i = 0; i < 4; i++ ))
do
	output=$ARQ_TAXA_XY""$i
	awk -v output=$output -v intervalo=$intervalo -f $SCRIPT_TAXA ${TRACEFILE[$i]}
done 



# Criação do arquivo de configuração do GNUPlot para a taxa de entrega
echo -e "
set title 'Taxa de entrega'
set xlabel 'Total Enviado (Mbytes)'
set ylabel 'Taxa de entrega (%)'
set yrange [0:118]
set key right bottom
set terminal png
set output '"$ARQ_TAXA_GRAPH"'
plot '"$ARQ_TAXA_XY"0""' using 1:2 title '30 transmissores' with lines, \\
'"$ARQ_TAXA_XY"1""' using 1:2 title '40 transmissores' with lines, \\
'"$ARQ_TAXA_XY"2""' using 1:2 title '50 transmissores' with lines, \\
'"$ARQ_TAXA_XY"3""' using 1:2 title '60 transmissores' with lines \\
" > $ARQ_TAXA_GNU

# Gera o gráfico de taxa de entrega
gnuplot $ARQ_TAXA_GNU

#se o gnuplot rodou com sucesso
if [ $? -eq 0 ]
then
	echo "Gráfico da taxa de entrega gerado no arquivo '"$ARQ_TAXA_GRAPH"'"
else
	echo "Erro ao gerar arquivo do gráfico da taxa de entrega da rede"
fi

#-----------------------------------------------------------------------------------------------------

# Remove os arquivos temporários
rm $ARQ_LATENCIA_GNU
rm $ARQ_TAXA_GNU
rm *.xy*












