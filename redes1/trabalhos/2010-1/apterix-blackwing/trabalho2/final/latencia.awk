# Script AWK para medir a latência da rede
#
# Latência, tempo decorrido do envio até a entrega o pacote.


{
	# Define os momentos de envio
	if ( $1 == "+" )
	{
		# verifica se é o primeiro envio do pacote
		if ( temposEnvio[ $12 ] == "" ) {
			temposEnvio[ $12 ] = $2
			temposRecebe[ $12 ] = -1
		}
	}
	# Define os momentos de recebimento
	else if ( $1 == "r" && $4 == $10) 
	{
		if ( temposRecebe[ $12 ] < $2 ) {
			temposRecebe[ $12 ] = $2
		}
	}
}


END{

	# inserindo o ponto (0,0) no arquivo com os pontos X e Y
	print "0 0" >> saida

	arrSize = length( temposEnvio )
	cont = 0
	perdas = 0
	somaAmostra = 0
	for ( i = 0; i < arrSize; i++ )
	{
		if ( temposRecebe[i] == -1 ) {
			perdas++
		}else{
			somaAmostra += 	temposRecebe[i]-temposEnvio[i]
			cont++
			if ( cont == amostra ){
				print ( ( (i+1-perdas)/amostra )" "somaAmostra/amostra) >> saida
				somaAmostra = 0
				cont = 0
			}
		}
	}
}
