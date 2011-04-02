vAmostra=10
echo "Tamanho da amostra="$vAmostra
echo "extraindo informacoes de out1ms.tr"
rm saida1ms
awk -v saida=saida1ms -v amostra=$vAmostra -f taxa.awk out1ms.tr
echo "extraindo informacoes de out10ms.tr"
rm saida10ms
awk -v saida=saida10ms -v amostra=$vAmostra -f taxa.awk out10ms.tr
echo "extraindo informacoes de out100ms.tr"
rm saida100ms
awk -v saida=saida100ms -v amostra=$vAmostra -f taxa.awk out100ms.tr
echo "extraindo informacoes de out1000ms.tr"
rm saida1000ms
awk -v saida=saida1000ms -v amostra=$vAmostra -f taxa.awk out1000ms.tr
echo "gerando grafico da Taxa de entrega"
rm geradorGraficoTaxa
echo "
set   autoscale
set title \"Taxa de Entrega da Rede\"
set xlabel \"Pacotes (media de uma amostra de "$vAmostra" pacotes)\"
set ylabel \"Taxa de entrega (%)\"
set yr [0:110]
set key right bottom
set term png size 2000, 600
set output \"graficoTaxa.png\"
plot \"saida1ms\" using 1:2 title '1ms' with lines, \
\"saida10ms\" using 1:2 title '10ms' with lines, \
\"saida100ms\" using 1:2 title '100ms' with lines, \
\"saida1000ms\" using 1:2 title '1000ms' with lines" >> geradorGraficoTaxa
gnuplot geradorGraficoTaxa
