section .text
default rel
bits 64

global asmfunc
asmfunc:
    mov rax, rcx             ; rax = n (counter)
    mov r10, rdx             ; r10 = x1 pointer
    mov r11, r8              ; r11 = x2 pointer
    mov r12, r9              ; r12 = y1 pointer
    mov r13, [rsp+0x28]      ; r13 = y2 pointer
    mov r14, [rsp+0x30]      ; r14 = z pointer
    xor r15, r15             ; r15 = loop index

.loop:
    cmp r15, rax
    jge .done

    movsd xmm0, [r11+r15*8]  
    subsd xmm0, [r10+r15*8]  
    mulsd xmm0, xmm0          

    movsd xmm1, [r13+r15*8]  
    subsd xmm1, [r12+r15*8]  
    mulsd xmm1, xmm1          

    addsd xmm0, xmm1          
    sqrtsd xmm0, xmm0         

    movsd [r14+r15*8], xmm0  

    inc r15
    jmp .loop

.done:
    xor rax, rax
    ret
