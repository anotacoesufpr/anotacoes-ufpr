#!/bin/bash
#
# Script que executa o filtro.sh quatro vezes, um para cada número de transmissores (30 ,40, 50, 60)

# Inclui o arquivo de configurações
. config.conf


for (( i = 0; i < ${#arrTransmissores[@]}; i++ ))
do
	echo ${STR_CONFIG}${arrTransmissores[$i]} > $TCL_CONFIG_FILE
	echo "Gerando simulação para rede com "${arrTransmissores[$i]}" transmissores... (isso pode levar alguns segundos)"
	ns $TCL_SIMULACAO
done

# Remove o arquivo de configuração do TCL gerado dinamicamente pelo Shell
rm -f $TCL_CONFIG_FILE

bash $FILTER_SHELL_SCRIPT
