.section .data
A: .int 0
B: .int 0
.section .text
.globl _start
soma:
	pushl %ebp
	movl %esp, %ebp
	subl $4, %esp
	movl 8(%ebp), %eax
	addl 12(%ebp), %eax
	movl %eax, -4(%ebp)
	addl $4, %esp
	popl %ebp
	ret
_start:
	movl $4, A
	movl $5, B
	pushl B
	pushl A
	call soma
	addl $8, %esp
	movl %eax, B
	movl $1, %eax
	int $0x80
