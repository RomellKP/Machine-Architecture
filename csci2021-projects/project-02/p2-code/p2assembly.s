	.file	"thermo_update.c"
	.text
	.globl	thermo_update
	.type	thermo_update, @function
thermo_update:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-12(%rbp), %rax
	movq	%rax, %rdi
	call	set_temp_from_ports
	movl	%eax, -20(%rbp)
	movl	-12(%rbp), %eax
	leaq	THERMO_DISPLAY_PORT(%rip), %rsi
	movl	%eax, %edi
	call	set_display_from_temp
	movl	%eax, -16(%rbp)
	cmpl	$0, -20(%rbp)
	jg	.L2
	cmpl	$0, -16(%rbp)
	jle	.L3
.L2:
	movl	$1, %eax
	jmp	.L5
.L3:
	movl	$0, %eax
.L5:
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L6
	call	__stack_chk_fail@PLT
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	thermo_update, .-thermo_update
	.globl	set_temp_from_ports
	.type	set_temp_from_ports, @function
set_temp_from_ports:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movl	$1, -16(%rbp)
	movl	-16(%rbp), %eax
	sall	$2, %eax
	movl	%eax, -12(%rbp)
	movzwl	THERMO_SENSOR_PORT(%rip), %eax
	testw	%ax, %ax
	js	.L8
	movzwl	THERMO_SENSOR_PORT(%rip), %eax
	cmpw	$28800, %ax
	jg	.L8
	movzbl	THERMO_STATUS_PORT(%rip), %eax
	movzbl	%al, %eax
	andl	-12(%rbp), %eax
	testl	%eax, %eax
	je	.L9
.L8:
	movq	-40(%rbp), %rax
	movw	$0, (%rax)
	movq	-40(%rbp), %rax
	movb	$3, 2(%rax)
	movl	$1, %eax
	jmp	.L10
.L9:
	movzwl	THERMO_SENSOR_PORT(%rip), %eax
	sarw	$5, %ax
	movw	%ax, -20(%rbp)
	movzwl	THERMO_SENSOR_PORT(%rip), %eax
	andl	$31, %eax
	movw	%ax, -18(%rbp)
	cmpw	$15, -18(%rbp)
	jle	.L11
	movzwl	-20(%rbp), %eax
	addl	$1, %eax
	movw	%ax, -20(%rbp)
.L11:
	movzwl	-20(%rbp), %eax
	subw	$450, %ax
	movw	%ax, -20(%rbp)
	movl	$1, -8(%rbp)
	movl	-8(%rbp), %eax
	sall	$5, %eax
	movl	%eax, -4(%rbp)
	movzbl	THERMO_STATUS_PORT(%rip), %eax
	movzbl	%al, %eax
	andl	-4(%rbp), %eax
	testl	%eax, %eax
	je	.L12
	movswl	-20(%rbp), %edx
	movl	%edx, %eax
	sall	$3, %eax
	addl	%edx, %eax
	movslq	%eax, %rdx
	imulq	$1717986919, %rdx, %rdx
	shrq	$32, %rdx
	sarl	%edx
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	addw	$320, %ax
	movw	%ax, -20(%rbp)
	movq	-40(%rbp), %rax
	movzwl	-20(%rbp), %edx
	movw	%dx, (%rax)
	movq	-40(%rbp), %rax
	movb	$2, 2(%rax)
	jmp	.L13
.L12:
	movq	-40(%rbp), %rax
	movzwl	-20(%rbp), %edx
	movw	%dx, (%rax)
	movq	-40(%rbp), %rax
	movb	$1, 2(%rax)
.L13:
	movl	$0, %eax
.L10:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	set_temp_from_ports, .-set_temp_from_ports
	.globl	set_display_from_temp
	.type	set_display_from_temp, @function
set_display_from_temp:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
	movl	%edi, -116(%rbp)
	movq	%rsi, -128(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-128(%rbp), %rax
	movl	$0, (%rax)
	movl	$123, -48(%rbp)
	movl	$72, -44(%rbp)
	movl	$61, -40(%rbp)
	movl	$109, -36(%rbp)
	movl	$78, -32(%rbp)
	movl	$103, -28(%rbp)
	movl	$119, -24(%rbp)
	movl	$73, -20(%rbp)
	movl	$127, -16(%rbp)
	movl	$111, -12(%rbp)
	movl	$4, -64(%rbp)
	movl	$0, -60(%rbp)
	movl	$55, -56(%rbp)
	movl	$95, -52(%rbp)
	movl	$0, -100(%rbp)
	movzwl	-116(%rbp), %eax
	cwtl
	movl	%eax, -96(%rbp)
	movzbl	-114(%rbp), %eax
	cmpb	$1, %al
	je	.L15
	movzbl	-114(%rbp), %eax
	cmpb	$2, %al
	je	.L15
	movl	-56(%rbp), %eax
	orl	%eax, -100(%rbp)
	sall	$7, -100(%rbp)
	movl	-52(%rbp), %eax
	orl	%eax, -100(%rbp)
	sall	$7, -100(%rbp)
	movl	-52(%rbp), %eax
	orl	%eax, -100(%rbp)
	sall	$7, -100(%rbp)
	movl	-60(%rbp), %eax
	orl	%eax, -100(%rbp)
	movq	-128(%rbp), %rax
	movl	-100(%rbp), %edx
	movl	%edx, (%rax)
	movl	$1, %eax
	jmp	.L29
.L15:
	movzbl	-114(%rbp), %eax
	cmpb	$1, %al
	jne	.L17
	movzwl	-116(%rbp), %eax
	cmpw	$-450, %ax
	jl	.L18
	movzwl	-116(%rbp), %eax
	cmpw	$450, %ax
	jle	.L17
.L18:
	movl	-56(%rbp), %eax
	orl	%eax, -100(%rbp)
	sall	$7, -100(%rbp)
	movl	-52(%rbp), %eax
	orl	%eax, -100(%rbp)
	sall	$7, -100(%rbp)
	movl	-52(%rbp), %eax
	orl	%eax, -100(%rbp)
	sall	$7, -100(%rbp)
	movl	-60(%rbp), %eax
	orl	%eax, -100(%rbp)
	movq	-128(%rbp), %rax
	movl	-100(%rbp), %edx
	movl	%edx, (%rax)
	movl	$1, %eax
	jmp	.L29
.L17:
	movzbl	-114(%rbp), %eax
	cmpb	$2, %al
	jne	.L19
	movzwl	-116(%rbp), %eax
	cmpw	$-490, %ax
	jl	.L20
	movzwl	-116(%rbp), %eax
	cmpw	$1130, %ax
	jle	.L19
.L20:
	movl	-56(%rbp), %eax
	orl	%eax, -100(%rbp)
	sall	$7, -100(%rbp)
	movl	-52(%rbp), %eax
	orl	%eax, -100(%rbp)
	sall	$7, -100(%rbp)
	movl	-52(%rbp), %eax
	orl	%eax, -100(%rbp)
	sall	$7, -100(%rbp)
	movl	-60(%rbp), %eax
	orl	%eax, -100(%rbp)
	movq	-128(%rbp), %rax
	movl	-100(%rbp), %edx
	movl	%edx, (%rax)
	movl	$1, %eax
	jmp	.L29
.L19:
	movl	$0, -92(%rbp)
	movzwl	-116(%rbp), %eax
	testw	%ax, %ax
	jns	.L21
	movl	-64(%rbp), %eax
	orl	%eax, -100(%rbp)
	sall	$7, -100(%rbp)
	negl	-96(%rbp)
	movl	$1, -92(%rbp)
.L21:
	movl	$99, -88(%rbp)
	cmpl	$0, -92(%rbp)
	jne	.L22
	movl	-96(%rbp), %edx
	movslq	%edx, %rax
	imulq	$1717986919, %rax, %rax
	shrq	$32, %rax
	movl	%eax, %ecx
	sarl	$2, %ecx
	movl	%edx, %eax
	sarl	$31, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	addl	%eax, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -88(%rbp)
	movl	-96(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$1717986919, %rdx, %rdx
	shrq	$32, %rdx
	sarl	$2, %edx
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -96(%rbp)
.L22:
	movl	-96(%rbp), %edx
	movslq	%edx, %rax
	imulq	$1717986919, %rax, %rax
	shrq	$32, %rax
	movl	%eax, %ecx
	sarl	$2, %ecx
	movl	%edx, %eax
	sarl	$31, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	addl	%eax, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -80(%rbp)
	movl	-96(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$1717986919, %rdx, %rdx
	shrq	$32, %rdx
	sarl	$2, %edx
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -96(%rbp)
	movl	-96(%rbp), %edx
	movslq	%edx, %rax
	imulq	$1717986919, %rax, %rax
	shrq	$32, %rax
	movl	%eax, %ecx
	sarl	$2, %ecx
	movl	%edx, %eax
	sarl	$31, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	addl	%eax, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -76(%rbp)
	movl	-96(%rbp), %eax
	movslq	%eax, %rdx
	imulq	$1717986919, %rdx, %rdx
	shrq	$32, %rdx
	sarl	$2, %edx
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -96(%rbp)
	movl	-96(%rbp), %edx
	movslq	%edx, %rax
	imulq	$1717986919, %rax, %rax
	shrq	$32, %rax
	movl	%eax, %ecx
	sarl	$2, %ecx
	movl	%edx, %eax
	sarl	$31, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	addl	%eax, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -72(%rbp)
	cmpl	$0, -72(%rbp)
	je	.L23
	movl	-72(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %eax
	orl	%eax, -100(%rbp)
	sall	$7, -100(%rbp)
.L23:
	cmpl	$0, -76(%rbp)
	jne	.L24
	cmpl	$0, -72(%rbp)
	je	.L25
.L24:
	movl	-76(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %eax
	orl	%eax, -100(%rbp)
	sall	$7, -100(%rbp)
.L25:
	movl	-80(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %eax
	orl	%eax, -100(%rbp)
	cmpl	$99, -88(%rbp)
	je	.L26
	sall	$7, -100(%rbp)
	movl	-88(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %eax
	orl	%eax, -100(%rbp)
.L26:
	movl	$0, -84(%rbp)
	movzbl	-114(%rbp), %eax
	cmpb	$1, %al
	jne	.L27
	movl	$28, -84(%rbp)
	jmp	.L28
.L27:
	movl	$29, -84(%rbp)
.L28:
	movl	-84(%rbp), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	movl	%eax, -68(%rbp)
	movl	-68(%rbp), %eax
	orl	%eax, -100(%rbp)
	movq	-128(%rbp), %rax
	movl	-100(%rbp), %edx
	movl	%edx, (%rax)
	movl	$0, %eax
.L29:
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L30
	call	__stack_chk_fail@PLT
.L30:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	set_display_from_temp, .-set_display_from_temp
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0"
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
