.section .text
.section .data
a: .int 4
b: .int 5
.globl _start
_start:
movl a,%eax
movl b,%ebx
cmpl %ebx,%eax
jge else
addl %eax,%ebx
movl %eax,a
jmp fim
else:
subl %eax,%ebx
movl %eax,a
jmp fim
fim:
int $0x80

