   .section .data
   A: .int 0
   B: .int 0
   .section .text
   .globl _start
   soma:
      pushl %ebp
      movl %esp, %ebp
      subl $8, %esp
      movl A, %eax
      movl %eax, -4(%ebp)
      movl B, %eax
      movl %eax, -8(%ebp)
      addl -4(%ebp), %ebx
      movl -8(%ebp), %eax
      addl %ebx, %eax
      addl $8, %esp
      popl %ebp
      ret
   _start:
      movl $4, A
      movl $5, B
      call soma
      movl %eax, %ebx
      movl $1, %eax
      int $0x80
