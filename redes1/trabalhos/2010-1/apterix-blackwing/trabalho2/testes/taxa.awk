# Script AWK para medir a taxa de entrega da rede
#
# Taxa de entrega, porcentagem de pacotes entregues.

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
	arrSize = length( temposEnvio )
	cont = 0
	pacotesPerdidosNaAmostra = 0
	for ( i = 0; i < arrSize; i++ )
	{
		cont++
		if ( temposRecebe[i] == 0 ) {
			pacotesPerdidosNaAmostra++
		}
		if ( cont == amostra ){
			print ( i/amostra )" "( ( ( amostra-pacotesPerdidosNaAmostra)/amostra )*100 ) >> saida
			somaAmostra = 0
			cont = 0
		}
	}
}
