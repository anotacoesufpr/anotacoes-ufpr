# Script AWK para medir a taxa de entrega da rede
#
# Para calcular a taxa de entrega , pega-se todos os pacotes recebidos
# que começam com 'r' no trace file e divide-se pela soma total de dados
# que é feita com a soma dos recebidos e descartados(que começa com 'd' na
# simulação do ns). 

BEGIN {
	idAux = -1 #é para auxiliar no controle de pacotes.
}


# trata linha por linha do trace

{
	
	

# se o pacote foi recebido
if ( $1 == "r" )
{
	controle=1 #esse controle é para quando volta nos pacotes iniciais ele ficar 0 e não somar novamente os dados "em progresso"
	idPacote = $12 #pega a id do pacote no tracefile.	
        # Soma de pacote a cada intervalo de tempo. Ex: indice 0 é a soma dos tempos de 0 a valor do intervalo segundos
	# obs - $2 é a coluna 2 que contém o instante que ocorreu a ação da coluna 1 no arquivo trace do ns 
        indice = int($2/intervalo)
	
	
        if (idPacote < idAux)
			controle = 0
	#Aqui ocorre a soma de todos os dados recebidos
	#obs - $6 é a coluna 6 que contém o tamanho do pacote no arquivo de trace
        
	#aqui para somar mais dados , eles tem que ser novos, ou seja um pacote diferente e novo.
        if ( idPacote > idAux && controle) {
			recebidos[indice]=recebidos[indice]+$6
        	idAux = idPacote
        }
}


# se o pacote foi descartado
else if ( $1 == "d" )
{ 
	indice = int($2/intervalo) 
	
	#Aqui ocorre a soma de todos os dados descartados
	dropped[indice]=dropped[indice]+$6
	recebidos[indice]=recebidos[indice]-$6
}
}


#---------------------------------#


END {
	#ponto inicial
	print "0 100" >> output
	# Aqui pega tamanho do array para fazer algumas operações com ele
	tam_array = length(recebidos)
	total = 0
	#Tamanho de recebidos e dropped é igual então esse for é para percorrer os dois para poder obter a taxa e imprimir no
	#formato para gerar gráfico
	for ( i = 0; i < tam_array; i++ )
	{
           
	#Esse prints abaixo estão comentados pq eles mostram na tela algumas informações , para mostrá-las só descomentar
        #if ( (recebidos[i] + dropped[i]) != 0)
	#print "Taxa "intervalo*i" até "intervalo*i+intervalo" segundos = "( recebidos[i] /(recebidos[i] + dropped[i]) )*100"%\n"
	#print "Total recebido "intervalo*i" segundos = "recebidos[i]
	#if ( dropped[i] = " " )
		#dropped[i] = 0 
	#print "Total dropped "intervalo*i" segundos = "dropped[i]"\n \n"  

        total = recebidos[i] + dropped[i] + total
	# Não pode haver divisão por 0
		if ( recebidos[i] + dropped[i] != 0 )
 		#Da um print de duas colunas para gerar o gráfico. 1a coluna - Taxa e 2a coluna - Total enviado e
		#redireciona para o output , isso para geração de gráfico
                #diminui dropped de recebidos porque se o pacote foi descartado perdeu-se aqueles dados.
			print total/1000000" "(recebidos[i] /(recebidos[i] + dropped[i]))*100 >> output  
	}
}
