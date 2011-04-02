.section .text
.globl _start
_start:
	movl $0, %eax
	movl $10, %ebx
loop:
	cmpl %ebx, %eax # EFLAGS |<>|>|>=|<|<=|=|, %ebx <- %eax (sentido)
	jge fim_loop # pula se for maior (jl, je etc)
	add $1, %eax
	jmp loop
fim_loop:
	movl $1, %eax
	int $0x80

