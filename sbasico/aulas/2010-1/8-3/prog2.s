.section .data
A: .int 999 
B: .int 999
.section .text
.globl _start
_start:
movl $6,A
movl $7,B
movl A,%eax
movl B,%ebx
addl %eax,%ebx
movl $1,%eax
int $0x80
