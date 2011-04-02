# Script AWK para medir a latência da rede
#
# Para calcular a latência, consideramos a diferença de tempo
# entre o envio do pacote (primira vez em que é enfilado ("+")) e o
# recebimento (último "r")
# Consideremos o índice 0 como o momento de envio e o índice 1 como o de recebimento

# Como o AWK não suporta arrays multidimensionais, usaremos um array unidimensional, tratado como bidimensional

BEGIN {
	graficoPacotes = 100 #média de pacotes usado para gerar o gráfico.
}


{
# Define os momentos de envio
if ( $1 == "+" )
{
 # verifica se é o primeiro envio do pacote
 	if ( tempos[ $12*2 ] == "" ) 
	{
		#iguala ao tempo do primeiro pacote e seta o tempo recebimento 0.
 		tempos[ $12*2 ] = $2
 		tempos[ $12*2 +1 ] = 0
 	}
}
# Define os momentos de recebimento
else if ( $1 == "r" ) 
{	
	#pega o último recebimento que é o destino
	if ( tempos[ $12*2+1 ] < $2 ) 
	{
 		tempos[ $12*2+1 ] = $2
 	}
}


#pacote desconsiderado
else if ( $1 == "d" ) 
{
	tempos[ $12*2 ] = -1;
}

}

#--------------------------#


END {

# É necessário inserir o ponto (0,0) no arquivo com os pontos X e Y como ponto inicial
print "0 0" >> output

# Como o array é unidimensional, tratado como bidimensinoal, o seu tamanho é length() / 2
arrSize = length( tempos ) / 2

#como o array é unidimensinal, tem que ajustar o que é o que. 
recebimento = i*2+1
envio = i*2 

#Aqui que a variavel graficoPacotes tem sentido. Uma essa variavel como indexador, então a cada
#$graficoPacotes pacotes , soma-se a latencia de cada um e se faz a média.
for ( i = 0; i < arrSize; i++ )
{	
	#a cada $graficoPacotes pacotes. Para calcular a média depois 
	indice = int( i / graficoPacotes )
	
	if ( (tempos[ recebimento ] != "") && (tempos[ envio ] >= 0) )
	{	
		#latencia = tempo de recebimento menos o de envio
		diff[ indice ] += tempos[ recebimento] - tempos[ envio ]
	}
}

#pega o tamanho do array com as latências somadas de acordo com graficoPacotes
total = length( diff )
#gerar dados para gráfico
for ( i = 0; i < total; i++ )
{	
	#Formação do gráfico : 1a coluna: numero de pacotes , 2a coluna: latência (média dos 100 pacotes)
	print (i+1)*graficoPacotes" "(diff[i]/graficoPacotes) >> output
}

}
