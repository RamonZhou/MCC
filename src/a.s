	.text
	.file	"main"
	.globl	printi                          # -- Begin function printi
	.p2align	4, 0x90
	.type	printi,@function
printi:                                 # @printi
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	%edi, %esi
	movl	%edi, 4(%rsp)
	movl	$.L__unnamed_1, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	printi, .Lfunc_end0-printi
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3                               # -- Begin function main
.LCPI1_0:
	.quad	0x3fb999999999999a              # double 0.10000000000000001
.LCPI1_1:
	.quad	0x4024000000000000              # double 10
	.text
	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$168, %rsp
	.cfi_def_cfa_offset 176
	movl	$10, 8(%rsp)
	movl	$12, 12(%rsp)
	leaq	8(%rsp), %rsi
	movl	$.L__unnamed_2, %edi
	xorl	%eax, %eax
	callq	scanf@PLT
	movl	8(%rsp), %esi
	movl	$.L__unnamed_3, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	movabsq	$4591870180066957722, %rax      # imm = 0x3FB999999999999A
	movq	%rax, 16(%rsp)
	movl	$5, gl(%rip)
	movl	8(%rsp), %eax
	movl	12(%rsp), %ecx
	leal	1(%rax,%rcx), %eax
	cvtsi2sd	%eax, %xmm0
	addsd	.LCPI1_0(%rip), %xmm0
	movl	$.L__unnamed_4+2, %edi
	movb	$1, %al
	callq	printf@PLT
	movl	$0, 4(%rsp)
	jmp	.LBB1_1
	.p2align	4, 0x90
.LBB1_3:                                # %then
                                        #   in Loop: Header=BB1_1 Depth=1
	movslq	4(%rsp), %rax
	movl	72(%rsp,%rax,4), %eax
	imull	gl(%rip), %eax
	xorps	%xmm0, %xmm0
	cvtsi2sd	%eax, %xmm0
	addsd	16(%rsp), %xmm0
	cvttsd2si	%xmm0, %edi
	callq	printi@PLT
	incl	4(%rsp)
.LBB1_1:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	xorps	%xmm0, %xmm0
	cvtsi2sdl	4(%rsp), %xmm0
	movsd	.LCPI1_1(%rip), %xmm1           # xmm1 = mem[0],zero
	ucomisd	%xmm0, %xmm1
	jb	.LBB1_5
# %bb.2:                                # %body
                                        #   in Loop: Header=BB1_1 Depth=1
	movslq	4(%rsp), %rax
	movl	%eax, 72(%rsp,%rax,4)
	cmpl	$5, 4(%rsp)
	je	.LBB1_3
# %bb.4:                                # %else
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	4(%rsp), %esi
	movl	$.L__unnamed_5, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	incl	4(%rsp)
	jmp	.LBB1_1
.LBB1_5:                                # %end14
	xorl	%eax, %eax
	addq	$168, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_1,@object           # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	": %d\n"
	.size	.L__unnamed_1, 6

	.type	gl,@object                      # @gl
	.data
	.p2align	2
gl:
	.long	2                               # 0x2
	.size	gl, 4

	.type	.L__unnamed_2,@object           # @1
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_2:
	.asciz	"%d"
	.size	.L__unnamed_2, 3

	.type	.L__unnamed_3,@object           # @2
.L__unnamed_3:
	.asciz	"A: %d\n"
	.size	.L__unnamed_3, 7

	.type	.L__unnamed_4,@object           # @3
.L__unnamed_4:
	.asciz	"--Hello world! %.1lf!\n"
	.size	.L__unnamed_4, 23

	.type	.L__unnamed_5,@object           # @4
.L__unnamed_5:
	.asciz	"! i = %d\n"
	.size	.L__unnamed_5, 10

	.section	".note.GNU-stack","",@progbits
