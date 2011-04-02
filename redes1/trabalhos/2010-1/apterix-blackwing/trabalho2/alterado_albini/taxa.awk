# Script AWK para medir a taxa de entrega da rede
#
# Taxa de entrega, porcentagem de pacotes entregues.

{
	# Define os momentos de envio
	if ( $1 == "+" )
	{
		# verifica se é o primeiro envio do pacote
		if ( envios[ $12 ] == "" ) {
			envios[ $12 ] = 1
		}
	}
	# Define os momentos de recebimento
	else if ( $1 == "d" ) 
	{
			envios[ $12 ] = -1
	}
}

END{
	arrSize = length( envios )
	cont = 0
	pacotesPerdidosNaAmostra = 0
	for ( i = 0; i < arrSize; i++ )
	{
		cont++
		if ( envios[i] == -1 ) {
			pacotesPerdidosNaAmostra++
		}
		if ( cont == amostra ){
			print ( i/amostra )" "( ( ( amostra-pacotesPerdidosNaAmostra)/amostra )*100 ) >> saida
			pacotesPerdidosNaAmostra = 0
			cont = 0
		}
	}
}
