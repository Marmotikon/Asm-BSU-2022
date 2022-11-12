                    global AsmBitCount
                    global AsmFactorial
                    global AsmIsSquare
                    global AsmRemoveDigits
                    global AsmFormula
                    global AsmBankDeposit
                    global AsmEvenDivisors
                    global AsmInfiniteManipulations

                    section .text

AsmBitCount:
                    ;rdi - x
                    popcnt rax, rdi
                    ret

AsmFactorial:
                    shl rdi, 32
                    shr rdi, 32  ;r10 - n
                    mov rax, 1  ;rax - r!
                    xor r8, r8  ;r8 - r
    .loop_begin:
                    cmp rax, rdi
                    jg .loop_end

                    inc r8
                    imul r8
                    jmp .loop_begin
    .loop_end:
                    ret
        
AsmIsSquare:
                    ; rdi - x
                    mov rax, rdi
                    cqo
                    mov r11, 2
                    idiv r11
                    inc rax
                    mov r10, rax  ; r10 - right border
                    mov rsi, 0xB504F333  ; sqrt(Max_int_64t)
                    cmp r10, rsi
                    jl .skip
                    mov r10, rsi
    .skip:
                    mov r8, 1  ; r8 - left border
    .loop_begin:
                    mov rax, r10
                    sub rax, r8
                    cqo
                    idiv r11
                    add rax, r8

                    mov r9, rax
                    imul rax
                    cmp rax, rdi
                    je .loop_end
                    jg .new_right_border
                    inc r9
                    mov r8, r9
                    jmp .check_borders
        .new_right_border:
                    mov r10, r9
        .check_borders:
                    cmp r8, r10
                    je .loop_end
                    jmp .loop_begin
    .loop_end:
                    imul r9, r9
                    cmp r9, rdi
                    je .true
                    xor rax, rax
                    jmp .end
    .true:
                    mov rax, 1
    .end:
                    ret
        
AsmRemoveDigits:
                    movsxd rax, edi  ; rax - input_val
                    xor r8, r8  ; r8 - output_val
                    mov r9, 1  ; r9 - 10^pos
                    mov r10, 10  ; needed in idiv
    .loop_begin:
                    cmp rax, 0
                    je .loop_end

                    cqo
                    idiv r10
                    mov r11, rdx
                    shl r11, 63
                    shr r11, 63
                    cmp r11, 1
                    jne .skip
                    imul rdx, r9
                    add r8, rdx
                    imul r9, r10
    .skip:
                    jmp .loop_begin
    .loop_end:
                    mov rax, r8
                    ret
        
AsmFormula:
                    ; rdi - x
                    ; rsi - n
                    mov rax, 1  ; rax - curr parenthesis
                    mov r8, 1
                    mov r9, 1  ; r9 - result
                    xor rcx, rcx  ; rcx - counter
    .loop_begin:
                    cmp rcx, rsi
                    je .loop_end
                    inc rcx

                    cmp r8, 0
                    jg .positive
                    dec r8
                    jmp .skip
        .positive:
                    inc r8
        .skip:
                    neg r8

                    imul rdi
                    jo .overflow_end
                    add rax, r8
                    jo .overflow_end
                    imul r9, rax
                    jo .overflow_end
                    jmp .loop_begin
    .overflow_end:
                    mov r9, -1
    .loop_end:
                    mov rax, r9
                    ret

AsmBankDeposit:
                    ; rdi - uint64_t initial_sum
                    movsx r8, esi  ; r8 - percentage
                    movsx rsi, edx  ; rsi - years
                    xor rcx, rcx  ; rcx - loop_counter
                    mov r10, 100
    .loop_begin:
                    cmp rcx, rsi
                    je .loop_end
                    inc rcx

                    xor rdx, rdx
                    mov rax, rdi
                    imul r8
                    idiv r10
                    add rdi, rax
                    jmp .loop_begin
    .loop_end:
                    mov rax, rdi
                    ret

AsmEvenDivisors:
                    movzx edi, di  ; edi - n
                    xor esi, esi  ; si - m
                    xor r8d, r8d  ; r8w - result
    .loop_begin:
                    inc esi
                    cmp esi, edi
                    jge .loop_end


                    mov eax, edi
                    xor edx, edx
                    idiv esi
                    cmp eax, edx
                    jne .loop_begin
                    inc r8d
                    jmp .loop_begin
    .loop_end:
                    mov eax, r8d
                    ret

AsmInfiniteManipulations:
                    ; rdi - x
                    popcnt rcx, rdi
                    neg cl
                    add cl, 64
                    mov r9, 0xFFFFFFFFFFFFFFFF
                    mov rax, r9
                    shl rax, cl
                    shr r9, cl
                    sub rax, r9
                    ret
