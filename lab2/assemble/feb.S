.data 
n:
    .word   0
	.text
    .section .rodata
    .align 2
str0: 
    .ascii "%d\n"
	.align 2
str1:
	.ascii	"%d"

    .global main 
    .global func
    .text 
main:  
    push {fp, lr}
    ldr r1, _bridge  @load n
	ldr r0, _bridge+8  @load str1
	bl  __isoc99_scanf  @scanf("%d", &n);
	ldr r10, _bridge
    ldr r10, [r10]
    mov r4, #0  @a=0
    mov r5, #1  @b=1
    mov r6, #1  @i=1
LOOP:
    cmp r6, r10 @i-n
    beq END
    mov r7, r5  
    add r5, r5, r4
    ldr r0, _bridge+4
    mov r1, r5
    bl printf  @prinf("%d\n", b);
    mov r4, r7
    add r6, r6, #1
    b LOOP

END:
    pop {fp, pc}

_bridge:
    .word   n
    .word   str0
    .word 	str1
