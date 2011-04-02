#--GLOBAIS---------------------------------------------------------------------#

  .section .data
      inicio_heap:  .long 0
      brk_atual:    .long 0
      tam_anterior: .long 0

#--CONSTANTES------------------------------------------------------------------#

  .equ HDR_TAM, 12      # Tamanho do cabeçalho
  .equ POS_AVAL, 0      # Posição de "avaliável" no cabeçalho
  .equ POS_TAM, 4       # Posição do tamanho no cabeçalho
  .equ TAM_ANT, 8

  .equ INDISP, 0        # Constante para memória indisponível
  .equ DISP, 1          # Constante para memória disponível

  .equ BRK, 45
  .equ SYSCALL, 0x80

#------------------------------------------------------------------------------#

  .section .text

#--meuAlocaMem-----------------------------------------------------------------#

.globl  meuAlocaMem
.type   meuAlocaMem, @function

#------------------------------------------------------------------------------#

  .equ TAM_MEM, 8

  # %eax - Endereço de memória analisado
  # %ebx - brk_atual
  # %ecx - Tamanho a ser alocado
  # %edx - Tamanho do segmento de memória analisado

#------------------------------------------------------------------------------#

meuAlocaMem:

      pushl %ebp
      movl %esp, %ebp

      cmpl $0, inicio_heap           # Se inicio_heap é vazio,
      jne end_if                     # verifica-se o tamanho da brk
      movl $BRK, %eax                #
      movl $0, %ebx                  #
      int $SYSCALL                   #
  
      incl %eax                      # Incrementa em 1 o valor da brk
      movl %eax, brk_atual           # e salva esse valor em brk_atual
      movl %eax, inicio_heap         # e inicio_heap


  end_if:

      movl inicio_heap, %eax         # Carrega as variáveis globais e o
      movl brk_atual, %ebx           # tamanho a ser alocado em registradores 
      movl TAM_MEM(%ebp), %ecx       #


  procura_espaco:

      cmpl %ebx, %eax                # Se o endereço de memória analisado for
      je aumenta_brk                 # igual a brk, aumentamos a brk

      movl POS_TAM(%eax), %edx       # edx recebe o tamanho do segmento atual
      cmpl $INDISP, POS_AVAL(%eax)   # Se o segmento estiver ocupado
      je prox_segmento               # desvia para o próximo segmento

      cmpl %edx, %ecx                # Se o segmento é do mesmo tamanho que
      je aloca_igual                 # precisamos alocar

      cmpl %edx, %ecx                # Se o segmento é maior que o que queremos
      jl aloca_menor                 # alocar


  prox_segmento:

      movl POS_TAM(%eax), %edx
      movl %edx, tam_anterior

      addl POS_TAM(%eax), %eax       # Se o segmento analisado for menor que o
      addl $HDR_TAM, %eax            # que queremos alocar, soma-se o tamanho
      jmp procura_espaco             # do segmento e o tamanho do cabeçalho
                                     # para ir ao próximo segmento

  aumenta_brk:

      addl %ecx, %ebx                # Soma em ebx o tamanho a ser alocado
      addl $HDR_TAM, %ebx            # e o tamanho do cabeçalho

      pushl %eax                     # Salva os registradores necessários
      pushl %ebx                     # na pilha
      pushl %ecx                     #

      movl $BRK, %eax                # Chamada de sistema para verificar a brk
      int $SYSCALL                   #
    
      cmpl $0, %eax                  # Verifica se foi possível aumentar a brk
      je erro                        #

      popl %ecx                      # Desempilha registradores salvos
      popl %ebx                      # anteriormente
      popl %eax                      #

      movl $INDISP, POS_AVAL(%eax)   # Define o status como indisponível
      movl %ecx, POS_TAM(%eax)       # e o tamanho do segmento

      movl tam_anterior, %ecx
      movl %ecx, TAM_ANT(%eax)

      addl $HDR_TAM, %eax            # 
      movl %ebx, brk_atual           # Salva o novo valor da brk
      popl %ebp                      #
      ret                            #


  aloca_igual:

      movl $INDISP, POS_AVAL(%eax)   # Se o segmento tem o mesmo tamanho do que
      addl $HDR_TAM, %eax            # queremos alocar, definimos o status como
      popl %ebp                      # indisponível no cabeçalho
      ret                            #


  aloca_menor:

      subl $HDR_TAM, %edx            # Verifica se o segmento tem pelo menos o 
      cmpl %ecx, %edx                # tamanho que queremos alocar somado em 9
      jle prox_segmento              # (8 do cabeçalho e 1 do espaço novo), que
                                     # é o minimo necessario para outro segmento
  
      movl $INDISP, POS_AVAL(%eax)   # Define o status como indisponível e o
      movl %ecx, POS_TAM(%eax)       # tamanho do segmento

      addl %ecx, %eax                # Segue para o pedaço livre que sobrou do
      addl $HDR_TAM, %eax            # segmento
    
      subl %ecx, %edx                #
      movl %edx, POS_TAM(%eax)       # Define o tamanho que restou do segmento
      movl $DISP, POS_AVAL(%eax)     # e o status como disponível

      subl %ecx, %eax                # Volta para o segmento anterior
      popl %ebp                      # na primeira posição após o cabeçalho
      ret


  erro:

      movl $0, %eax                  # Se não for possível aumentar a brk
      popl %ebp                      # a funcao retorna 0
      ret


#--meuLiberaMem----------------------------------------------------------------#

.globl  meuLiberaMem
.type   meuLiberaMem, @function

#------------------------------------------------------------------------------#

  .equ LIBERA, 4

  # %eax - Endereço a ser liberado
  # %ebx - 
  # %ecx - 
  # %edx - 

#------------------------------------------------------------------------------#

meuLiberaMem:

      movl LIBERA(%esp), %eax        # Acessa o parâmetro
      subl $HDR_TAM, %eax            # eax para inicio do segmento
      movl $DISP, POS_AVAL(%eax)     # coloca ele como livre
      movl POS_TAM(%eax), %ecx

      movl %eax, %ebx
      addl %ecx, %ebx
      addl $HDR_TAM, %ebx

      cmpl brk_atual, %ebx
      jge parte_1

      cmpl $DISP, POS_AVAL(%ebx)
      jne parte_1


      movl POS_TAM(%eax), %ecx       # eax terá o tam do segmento e do prox
      movl POS_TAM(%ebx), %edx
      addl $HDR_TAM, %edx
      addl %ecx, %edx
      movl %edx, POS_TAM(%eax)


  parte_1:

      movl %eax, %ebx
      cmpl $0, TAM_ANT(%eax)
      je parte_2

      subl TAM_ANT(%eax), %ebx
      subl $HDR_TAM, %ebx

      cmpl $DISP, POS_AVAL(%ebx)
      jne parte_2

      movl POS_TAM(%eax), %ecx     # eax terá o tam do segmento e do prox
      movl TAM_ANT(%eax), %edx
      addl $HDR_TAM, %edx
      addl %ecx, %edx
      movl %edx, POS_TAM(%ebx)
      movl %ebx, %eax


  parte_2:

      movl %eax, %ebx
      addl $HDR_TAM, %ebx
      addl POS_TAM(%eax), %ebx

      cmpl brk_atual, %ebx
      jl fim


  diminui_brk:

      movl %eax, %ebx
      movl $BRK, %eax 
      int $SYSCALL
      movl %eax, brk_atual


  fim:

      ret


#--imprMapa--------------------------------------------------------------------#

.globl  imprMapa
.type   imprMapa, @function

#------------------------------------------------------------------------------#

   msg1: .string "\nInicio bss: %p\n"
   msg2: .string "Segmento %d: %d bytes ocupados\n"
   msg3: .string "Segmento %d: %d bytes livres\n"
   msg4: .string "Segmentos Ocupados: %d / %d bytes\n"
   msg5: .string "Segmentos Livres: %d / %d bytes\n---------"

  .equ HEAP_ATUAL, -4
  .equ TOTAL_OCUPADOS, -8       # Guarda quantos segmentos são ocupados
  .equ TOTAL_LIVRES, -12        # Guarda quantos segmentos são livre
  .equ TOTAL_SEG_OCUPADOS, -16  # Guarda o espaço usado pelos segmentos ocupados
  .equ TOTAL_SEG_LIVRES, -20    # Guarda o espaço usado pelos segmentos livres
  .equ INC, -24                 # Número do segmento atual

#------------------------------------------------------------------------------#

imprMapa:

      pushl %ebp
      movl %esp, %ebp

      subl $24, %esp                  # Aumenta pilha para alocar vars locais
    
      movl $0, TOTAL_OCUPADOS(%ebp)
      movl $0, TOTAL_LIVRES(%ebp)
      movl $0, TOTAL_SEG_OCUPADOS(%ebp)
      movl $0, TOTAL_SEG_LIVRES(%ebp)
      movl $1, INC(%ebp)
    
      pushl inicio_heap               # Empilha os parâmetros do printf para
      pushl $msg1                     # para imprimir a msg1
      call printf                     #
      addl $8, %esp                   # Restaura a pilha

      movl inicio_heap, %eax          #


  loop_seg:

      cmpl brk_atual, %eax            #
      je fim_loop                     #
  

  if_ocupado:

      cmpl $INDISP, POS_AVAL(%eax)    # Verifica se o segmento está ocupado
      jne else_ocupado                # Se estiver livre, vai para else_ocupado

      addl $1, TOTAL_OCUPADOS(%ebp)        # Incrementa TOTAL_OCUPADOS
      movl POS_TAM(%eax), %ebx             #
      addl %ebx, TOTAL_SEG_OCUPADOS(%ebp)  # Soma o tamanho do segmento atual em
                                           # TOTAL_SEG_OCUPADOS

      pushl %eax

      pushl POS_TAM(%eax)             # Empilha os parâmetros do printf para
      pushl INC(%ebp)                 # imprimir a msg2
      pushl $msg2                     #
      call printf                     #
      addl $12, %esp                  # Restaura a pilha

      popl %eax                       #
    
      jmp proximo_seg                 #


  else_ocupado:

      addl $1, TOTAL_LIVRES(%ebp)         # Incrementa TOTAL_LIVRES
      movl POS_TAM(%eax), %ebx            #
      addl %ebx, TOTAL_SEG_LIVRES(%ebp)   # Soma o tamanho do segmento atual em
                                          # TOTAL_SEG_LIVRES
    
      pushl %eax
    
      pushl POS_TAM(%eax)             # Empilha os parâmetros do printf para 
      pushl INC(%ebp)                 # imprimir a msg3
      pushl $msg3                     #
      call printf                     #
      addl $12, %esp                  # Restaura a pilha
    
      popl %eax                       #


  proximo_seg:

      addl $1, INC(%ebp)              # Incrementa INC
      addl POS_TAM(%eax), %eax        # Soma o tamanho do segmento e cabeçalho
      addl $HDR_TAM, %eax             # para ir para o próximo segmento

      jmp loop_seg                    #


  fim_loop:

      pushl TOTAL_SEG_OCUPADOS(%ebp)  # Empilha os parâmetros do printf para
      pushl TOTAL_OCUPADOS(%ebp)      # imprimir a msg4
      pushl $msg4                     #
      call printf                     #
      addl $12, %esp                  # Restaura a pilha

      pushl TOTAL_SEG_LIVRES(%ebp)    # Empilha os parametros do printf para
      pushl TOTAL_LIVRES(%ebp)        # imprimir a msg5
      pushl $msg5                     #
      call printf                     #
      addl $12, %esp                  # Restaura a pilha

      addl $24, %esp                  #
      popl %ebp                       #
      ret                             #

#------------------------------------------------------------------------------#
