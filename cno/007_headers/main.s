	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 6
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	L_.str(%rip), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	__Z3LogPKc
	movl	$2, %edi
	movl	$6, %esi
	callq	__Z3Addii
	movl	$4, %edi
	movl	$15, %esi
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	callq	__Z3Mulii
	xorl	%ecx, %ecx
	movq	%rax, -24(%rbp)         ## 8-byte Spill
	movl	%ecx, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Log message"

.subsections_via_symbols
