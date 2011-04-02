echo "Simulando rede com atraso de 1ms"
ns simulacao1ms.tcl
echo "Simulando rede com atraso de 10ms"
ns simulacao10ms.tcl
echo "Simulando rede com atraso de 100ms"
ns simulacao100ms.tcl
echo "Simulando rede com atraso de 1000ms"
ns simulacao1000ms.tcl
./filtrar_gerarGraficoLatencia.sh
./filtrar_gerarGraficoTaxa.sh
