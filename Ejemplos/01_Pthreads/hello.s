	.file	"hello.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"Hello world from thread number # %zu\n"
	.text
	.globl	helloWorld
	.type	helloWorld, @function
helloWorld:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	helloWorld, .-helloWorld
	.section	.rodata
	.align 8
.LC1:
	.string	"Error, invalid number of parameters\n"
.LC2:
	.string	"Hello world from main thread"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movq	$0, -16(%rbp)
	cmpl	$1, -36(%rbp)
	jle	.L4
	movq	-48(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtoul@PLT
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	salq	$3, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	$0, -32(%rbp)
	jmp	.L7
.L4:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$36, %edx
	movl	$1, %esi
	leaq	.LC1(%rip), %rdi
	call	fwrite@PLT
	movl	$1, %eax
	jmp	.L6
.L8:
	movq	-32(%rbp), %rax
	movq	-32(%rbp), %rdx
	leaq	0(,%rdx,8), %rcx
	movq	-8(%rbp), %rdx
	leaq	(%rcx,%rdx), %rdi
	movq	%rax, %rcx
	leaq	helloWorld(%rip), %rdx
	movl	$0, %esi
	call	pthread_create@PLT
	addq	$1, -32(%rbp)
.L7:
	movq	-32(%rbp), %rax
	cmpq	-16(%rbp), %rax
	jb	.L8
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	movq	$0, -24(%rbp)
	jmp	.L9
.L10:
	movq	-24(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	addq	$1, -24(%rbp)
.L9:
	movq	-24(%rbp), %rax
	cmpq	-16(%rbp), %rax
	jb	.L10
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movl	$0, %eax
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
