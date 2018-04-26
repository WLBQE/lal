	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.section	__TEXT,__literal16,16byte_literals
	.p2align	4               ## -- Begin function main
LCPI0_0:
	.long	30                      ## 0x1e
	.long	24                      ## 0x18
	.long	18                      ## 0x12
	.long	84                      ## 0x54
LCPI0_1:
	.long	69                      ## 0x45
	.long	54                      ## 0x36
	.long	138                     ## 0x8a
	.long	114                     ## 0x72
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset %rbx, -24
	movaps	LCPI0_0(%rip), %xmm0    ## xmm0 = [30,24,18,84]
	movaps	%xmm0, -48(%rbp)
	movaps	LCPI0_1(%rip), %xmm0    ## xmm0 = [69,54,138,114]
	movaps	%xmm0, -32(%rbp)
	movl	$90, -16(%rbp)
	leaq	L_.str(%rip), %rbx
	movl	$30, %esi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_printf
	movl	$24, %esi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_printf
	movl	$18, %esi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_printf
	movl	$84, %esi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_printf
	movl	$69, %esi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_printf
	movl	-28(%rbp), %esi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_printf
	movl	-24(%rbp), %esi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_printf
	movl	-20(%rbp), %esi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_printf
	movl	-16(%rbp), %esi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_printf
	xorl	%eax, %eax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d\n"


.subsections_via_symbols
