vAmostra=70
echo "valor da amostra="$vAmostra
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
gnuplot geradorGraficoTaxa
