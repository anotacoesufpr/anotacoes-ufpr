# EAX > sempre contera onde comecam as headers
# EBX > posicao corrente da brk
# ECX > tamanho do bloco
# EDX > tamanho a ser alocado
.section .data
#Variáveis globais#
	inicio_Heap: .int 0
	pos_Corrente: .int 0
	total_Livre: .int 0
	total_Ocupado: .int 0
	segmentos_Ocupados: .int 0 
	segmentos_Livres: .int 0
#Constantes#
	.equ TAM_CABECALHO, 8
	.equ BRK, 45
	.equ LINUX_SYSCALL, 0x80
	.equ DISPONIVEL , 1
	.equ INDISPONIVEL , 0
#Strings#
	str: .string "Aqui\n"
	str_Inicio: .string "Inicio bss: %p \n"	
	str_Livre: .string "Segmento %d: %d bytes livres\n"
	str_Ocupado: .string "Segmento %d: %d bytes ocupados\n"
	livres: .string "Segmentos Livres: %d/%d bytes\n"
	ocupados: .string "Segmentos Ocupados: %d/%d bytes\n"
	str_Aviso: .string "Não foi alocado nada ainda!!!\n"
.section .text
.globl inicio_aloca
.type inicio_aloca ,@function

inicio_aloca: #Serve para guardar o inicio da heap na primeira vez que é executado o aloca
	pushl %ebp
	movl %esp , %ebp

	movl $BRK,%eax  
	movl $0,%ebx #retorna posição do último endereço válido em eax	
	int $LINUX_SYSCALL

	incl %eax #Incrementa em 1 o endereço contido em eax, pois retorna o primeiro endereço
		#válido , mas se quer o último invalido para começo da heap , como se fosse uma
		#pilha.
	movl %eax , inicio_Heap
	movl %eax , pos_Corrente	
	movl %ebp , %esp
	popl %ebp 
	ret
.globl aloca
.type aloca ,@function
inicio:
	call inicio_aloca
	jmp continua
aloca:
	pushl %ebp
	movl %esp , %ebp

	cmpl $0, inicio_Heap #vê se é a primeira vez que chama a função no programa
	je inicio
	
	jmp continua	
continua:
	movl inicio_Heap ,%eax
	movl pos_Corrente ,%ebx
	movl 8(%ebp),%edx
	
	jmp verifica_para_alocar	
verifica_para_alocar:
	cmpl %eax, %ebx	#se a posição corrente for igual ao endereço de procura precisa de mais memória!
	je mais_memoria #abre mais memoria
	movl 4(%eax) , %ecx #pega o tamanho do bloco

	cmpl $INDISPONIVEL,0(%eax) #se o espaço não esta disponível, verifica próximo endereço
	je proximo_endereco

	cmpl %ecx,%edx #se o espaço estiver disponível e for o suficiente , aloca aqui mesmo			
	jle alocar_aqui
	
	jmp proximo_endereco #se for pequeno o espaço e não der para alocar vai para o proximo endereço
mais_memoria:
	addl $TAM_CABECALHO,%ebx #adiciona o espaço para o cabeçalho 
	addl %edx, %ebx	#e também o tamanho que quer alocar.

	pushl %eax #empilha os valores para fazer a SYSCALL pedindo mais memória
	pushl %ebx
	pushl %edx
	movl $BRK , %eax
	int $LINUX_SYSCALL #Retorna o novo endereço em eax caso Murphy permita. Caso não , retorna 0 em eax (Erro).  

	cmpl $0,%eax
	je deu_erro		
	popl %edx #restaura os valores
	popl %ebx
	popl %eax
	
	movl $INDISPONIVEL,0(%eax)	#monta o cabeçalho
	movl %edx, 4(%eax)
	
	addl $TAM_CABECALHO , %eax #agora sim , eax contém o endereço da memória usável que é depois do cabeçalho
					#é também o retorno do aloca
	movl %ebx , pos_Corrente #atualiza a posição para controle da heap
	
	movl %ebp , %esp
	popl %ebp
	ret
deu_erro:
	movl $0,%eax #No erro retorna-se 0
	movl %ebp , %esp
	popl %ebp
	ret
proximo_endereco:
	addl $TAM_CABECALHO, %eax #o próximo endereço para verificação é o cabeçalho + tamanho do espaço atual que não
	addl %ecx,%eax	#esta disponivel
	jmp verifica_para_alocar
alocar_aqui:
	movl $INDISPONIVEL, 0(%eax)
	addl $TAM_CABECALHO,%eax	#eax fica com o valor da memória usável depois do cabeçalho , pois é o valor real de retorno

	movl %ebp , %esp
	popl %ebp
	ret
##############################################################################################################################
#Função de liberar memória!
.globl libera_memoria
.type libera_memoria ,@function	
libera_memoria:
	pushl %ebp
	movl %esp , %ebp
	movl 8(%ebp),%eax
	movl $DISPONIVEL , -8(%eax)	
	movl %ebp , %esp
	popl %ebp
	ret
##############################################################################################################################
#Função que imprime um mapa!!
.globl imprMapa
.type imprMapa ,@function	
imprMapa:
	pushl %ebp
	movl %esp , %ebp
	movl inicio_Heap ,%eax
	movl pos_Corrente ,%ebx 
	cmpl %eax, %ebx
	je nao_usou_aloca

	pushl inicio_Heap
	pushl $str_Inicio
	call printf
	addl $8,%esp

	movl $1,%eax # Contador de segmentos
	movl inicio_Heap,%ebx
	jmp analisando_mapa
analisando_mapa:
	pushl 4(%ebx)  # empilha o tamanho do bloco
	pushl %eax     # empilha o contador de segmentos
	cmpl $INDISPONIVEL,0(%ebx)
	je imprime_ocupado
	jmp imprime_livre 
continua_mapa:
	popl %eax
	popl 4(%ebx)
	movl %ebx,%ecx
	addl $TAM_CABECALHO,%ecx
	addl 4(%ebx),%ecx
	movl %ecx,%ebx

	cmpl pos_Corrente, %ebx
	je terminando_mapa
	addl $1,%eax
	jmp analisando_mapa
imprime_ocupado:
	movl total_Ocupado,%edx
	movl segmentos_Ocupados,%ecx

	addl 4(%ebx),%edx
	addl $1,%ecx
	movl %edx,total_Ocupado
	movl %ecx,segmentos_Ocupados
	pushl $str_Ocupado	#
	call printf         	#Demais parâmetros empilhados nas linhas 196 e 197
	addl $4,%esp        	#
	jmp continua_mapa
imprime_livre:
	movl total_Livre,%edx
	movl segmentos_Livres,%ecx
	addl 4(%ebx),%edx	
	addl $1,%ecx

	movl %edx,total_Livre
	movl %ecx,segmentos_Livres

	pushl $str_Livre	
	call printf
	addl $4,%esp
	jmp continua_mapa
terminando_mapa:
	pushl total_Ocupado
	pushl segmentos_Ocupados
	pushl $ocupados

	call printf
	addl $12,%esp

	pushl total_Livre
	pushl segmentos_Livres
	pushl $livres

	call printf
	addl $12,%esp
	
	movl $0,total_Livre
	movl $0,segmentos_Livres
	movl $0,total_Ocupado
	movl $0,segmentos_Ocupados

	movl %ebp , %esp
	popl %ebp
	ret
nao_usou_aloca:
	pushl $str_Aviso
	call printf
	
	movl %ebp , %esp
	popl %ebp
	ret
