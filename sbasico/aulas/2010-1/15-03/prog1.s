.section .data
   i: .int 0
   maior: .int 0
#   data_items: .int 3, 67, 34, 222, 45, 75, 54, 34, 44, 33, 22, 11, 66, 0
	data_items: .int 0
   .section .text
   .globl _start
   _start:
   movl $0, %edi
   movl data_items(, %edi, 4), %ebx
   movl $1, %edi
   loop:
   movl data_items(, %edi, 4), %eax
   cmpl $0, %eax
   je fim_loop
   cmpl %ebx, %eax
   jle fim_if
   movl %eax, %ebx
   fim_if:
   addl $1, %edi
   jmp loop
   fim_loop:
   movl $1, %eax
   int $0x80

