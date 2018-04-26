	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main
	.p2align	4, 0x90
_main:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	pushq	%rax
	.cfi_offset %rbx, -24
	leaq	L_.str(%rip), %rbx
	movl	$20, %esi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_printf
	movl	$14, %esi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_printf
	movl	$56, %esi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_printf
	movl	$41, %esi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_printf
	xorl	%eax, %eax
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
	.cfi_endproc
	.section	__TEXT,__cstring,cstring_literals
L_.str:
	.asciz	"%d\n"
.subsections_via_symbols
