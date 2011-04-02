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
			temposRecebe[ $12 ] = 0
		}
	}
	# Define os momentos de recebimento
	else if ( $1 == "r" ) 
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
	somaAmostra = 0
	for ( i = 0; i < arrSize; i++ )
	{
		if ( temposRecebe[i] == 0 ) {
			cont++
		}else{
			somaAmostra += 	temposRecebe[i]-temposEnvio[i]
			cont++
			if ( cont == amostra ){
				print ( (i+1)/amostra )" "somaAmostra/amostra >> saida
				somaAmostra = 0
				cont = 0
			}
		}
	}
}
