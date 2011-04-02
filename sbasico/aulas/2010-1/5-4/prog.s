.section .data
.section .text
.globl _start
 fatorial:
pushl %ebp
movl %esp, %ebp
subl $4, %esp
movl $1, %eax
movl 12(%ebp), %ebx
cmpl %eax, %ebx
jg else
movl 8(%ebp), %eax
movl %1, (%eax)
 else:
movl 12(%ebp), %eax
subl 1, %eax
imul 	
pushl %eax
pushl 8(%ebp)
call fatorial
_start:
pushl %ebp
movl %esp, %ebp
subk 4, %esp

