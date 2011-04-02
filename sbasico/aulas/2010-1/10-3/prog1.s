ection .data
   i: .int 0
   a: .int 0
   .section .text
   .globl _start
   _start:
   movl $0, i
   movl $0, a
   while:
       movl i, %eax
       movl $10, %ebx
       cmpl %ebx, %eax
       jge fim_while
       movl a, %ecx
       movl i, %eax
       addl %eax, %ecx
       movl %ecx, a
       addl $1, %eax
       movel %ebx, i
       jmp while
   fim_while:
   movl $1, %eax
   int $0x80

