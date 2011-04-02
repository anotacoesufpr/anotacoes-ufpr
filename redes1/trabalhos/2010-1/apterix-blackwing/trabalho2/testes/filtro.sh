#!/bin/bash
#

SCRIPT_LATENCIA=latencia.awk
#SCRIPT_TAXA=taxa.awk

# Path para o trace file
declare -a TRACEFILE
TRACEFILE[0]=out-30.tr
TRACEFILE[1]=out-40.tr
TRACEFILE[2]=out-50.tr
TRACEFILE[3]=out-60.tr


# Path para o arquivo onde ficarão os pontos X e Y para geração do gŕafico da latência e de taxa de entrega respectivamente
ARQ_LATENCIA_XY=latencia.xy
ARQ_TAXA_XY=taxa.xy

# Path para o arquivo onde ficarão as configurações do GNUPlot para geração do gŕafico da latência e de taxa de entrega respectivamente
ARQ_LATENCIA_GNU=latencia.gnu
ARQ_TAXA_GNU=taxa.gnu

# Path para o arquivo PNG onde ficará o gráfico da latência e de taxa de entrega respectivamente.
ARQ_LATENCIA_GRAPH=latencia.png
ARQ_TAXA_GRAPH=taxa.png


#-----------------------------------------------------------------------------------------------------
######### LATÊNCIA DE REDE 

for (( i = 0 ; i < 4; i++ ))
do
	output=$ARQ_LATENCIA_XY""$i
	awk -v saida=$output -v intervalo=$intervalo -f $SCRIPT_LATENCIA ${TRACEFILE[$i]}
done

i=0
while [ $i -le 180 ]
do
	echo $i >> tempo.txt
	i=$(expr $i + $intervalo)
done

paste tempo.txt latencia.xy* > $ARQ_LATENCIA_XY



# Criação do arquivo de configuração do GNUPlot para a latência
      echo "set   autoscale                      
      unset log                 
      unset label
      set xtic auto
      set ytic auto
      set title \"Latencia\"
      set xlabel \"pacote\"
      set ylabel \"latencia\"
      plot    \"saidaTest\" using 1:2 title 'Column' with linespoints"


echo -e "
set title 'Latência da Rede'
set xlabel 'tempo (s)'
set ylabel 'latência (%)'
set key right bottom
set terminal png
set output '"$ARQ_LATENCIA_GRAPH"'
plot '"$ARQ_LATENCIA_XY"' using 1:2 with lines title '30', \\
'"$ARQ_LATENCIA_XY"' using 1:3 with lines title '40', \\
'"$ARQ_LATENCIA_XY"' using 1:4 with lines title '50', \\
'"$ARQ_LATENCIA_XY"' using 1:5 with lines title '60'
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

paste tempo.txt taxa.xy* > $ARQ_TAXA_XY

# Criação do arquivo de configuração do GNUPlot para a taxa de entrega
echo -e "
set title 'Taxa de entrega'
set xlabel 'tempo (s)'
set ylabel 'Taxa de entrega (%)'
set yr [0:110]
set xr [0:180]
set key right bottom
set terminal png
set output '"$ARQ_TAXA_GRAPH"'
plot '"$ARQ_TAXA_XY"' using 1:2 title '30' with lines, \\
'"$ARQ_TAXA_XY"' using 1:3 title '40' with lines, \\
'"$ARQ_TAXA_XY"' using 1:4 title '50' with lines, \\
'"$ARQ_TAXA_XY"' using 1:5 title '60' with lines \\
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
rm $ARQ_LATENCIA_XY

rm $ARQ_TAXA_GNU
rm $ARQ_TAXA_XY

rm *.xy*
rm tempo.txt











