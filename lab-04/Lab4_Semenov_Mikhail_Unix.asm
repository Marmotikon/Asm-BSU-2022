                    global AsmProduct
                    global AsmSpecialSum
                    global AsmArrayFormula
                    global AsmCompare
                    global AsmSimpleModify
                    global AsmSetToSequence
                    global AsmRotateInGroups
                    global AsmRemoveIfSimilar
                    global AsmReplaceWithGroup
                    global AsmMerge
                    global AsmModify2D
                    global AsmFindSorted

                    section .text


AsmProduct:         ;rdi - &array, esi - size, edx - module
                    movsxd r8, edx  ;module
                    mov rax, 1  ;answer
                    xor r9, r9  ;counter
    .loop_begin:
                    cmp r9d, esi
                    je .loop_end

                    cqo
                    movsxd r10, DWORD[rdi + r9 * 4]
                    imul r10
                    idiv r8
                    cmp rdx, 0
                    jge .pos_remainder
                    add rdx, r8
        .pos_remainder:
                    mov rax, rdx
                    inc r9
                    jmp .loop_begin
    .loop_end:
                    ret


AsmSpecialSum:      ;rdi - &array, rsi - size, rdx - module
                    mov r8, rdx  ;module
                    xor r11, r11  ;answer
                    xor rcx, rcx  ;counter
    .loop_begin:
                    cmp rcx, rsi
                    je .loop_end

                    mov r10, QWORD[rdi + rcx * 8]  ;current number

                    mov rax, r10
                    xor rdx, rdx
                    mov r9, 3
                    div r9
                    cmp rdx, 1
                    jne .skip_number

                    mov rax, r10
                    xor rdx, rdx
                    mov r9, 5
                    div r9
                    cmp rdx, 1
                    je .add_number
                    cmp rdx, 3
                    jne .skip_number
        .add_number:
                    add r11, r10
        .skip_number:
                    inc rcx
                    jmp .loop_begin
    .loop_end:
                    mov rax, r11
                    ret


AsmArrayFormula:    ;rdi - &array, esi - size
                    xor rax, rax
                    mov eax, esi
                    mov r8, 2
                    cqo
                    idiv r8
                    mov rsi, rax  ;number of pairs
                    xor r11, r11  ;answer
                    xor rcx, rcx  ;pair counter

    .loop_begin:
                    cmp rcx, rsi
                    je .loop_end

                    movsxd r10, DWORD[rdi + rcx * 8]  ;first number in pair
                    mov rax, rcx
                    imul r8
                    inc rax
                    mov r9, rax
                    imul r10
                    inc r9
                    imul r9
                    movsxd r10, DWORD[rdi + rcx * 8 + 4]  ;second number in pair
                    imul r10
                    mov r9, rax  ;current bracket

                    mov rax, rcx
                    xor rdx, rdx
                    div r8
                    cmp rdx, 0
                    je .even_bracket
                    neg r9  ;odd_bracket
    .even_bracket:
                    add r11, r9
                    inc rcx
                    jmp .loop_begin
    .loop_end:
                    mov rax, r11
                    ret


AsmCompare:         ;rdi - *array1, rsi - size1, rdx - *array2, rcx - size2
                    xor rax, rax ;rax - answer

    .loop1_begin:
                    cmp rsi, 0
                    je .loop1_end
                    dec rsi

                    mov r9, QWORD[rdi + rsi * 8]  ;element of first
                    mov r8, rcx  ;index in second
        .loop2_begin:
                    cmp r8, 0
                    je .loop2_end

                    cmp r9, QWORD[rdx + r8 * 8 - 8]
                    je .loop2_end
                    dec r8
                    jmp .loop2_begin
        .loop2_end:
                    cmp r8, 0
                    jne .loop1_begin
                    inc rax
                    jmp .loop1_begin
    .loop1_end:
                    ret


AsmSimpleModify:    ;rdi - *array
                    movsxd rsi, esi  ;rsi - size
                    mov r8, 5
                    mov r9, 2

    .loop_begin:
                    cmp rsi, 0
                    je .loop_end
                    dec rsi

                    movsxd rax, DWORD[rdi + rsi * 4]
                    cqo
                    div r8
                    cmp rdx, 0
                    jne .skip1
                    mov DWORD[rdi + rsi * 4], 0
                    jmp .loop_begin
        .skip1:
                    mov rax, rdx
                    cqo
                    div r9
                    cmp rdx, 0
                    jne .skip2
                    mov DWORD[rdi + rsi * 4], 1
                    jmp .loop_begin
        .skip2:
                    mov DWORD[rdi + rsi * 4], -1
                    jmp .loop_begin
    .loop_end:
                    ret


AsmSetToSequence:   ;rdi - *array<32>
                    movsxd rsi, esi  ;size
                    mov rdx, QWORD[rdi]  ;min element
                    xor r8, r8  ;pos of min
                    mov rcx, QWORD[rdi]  ;max element
                    xor r9, r9  ;pos of max
                    xor r10, r10  ;counter

    .loop1_begin:  ;find min & max
                    cmp r10, rsi
                    je .loop1_end

                    mov r11, QWORD[rdi + r10 * 8]  ;current element
                    cmp r11, rdx
                    jge .new_min_skip
                    mov rdx, r11
                    mov r8, r10
        .new_min_skip:
                    cmp r11, rcx
                    jle .new_max_skip
                    mov rcx, r11
                    mov r9, r10
        .new_max_skip:
                    inc r10
                    jmp .loop1_begin
    .loop1_end:

                    cmp r8, r9
                    jle .skip_swap
                    mov r11, r8
                    mov r8, r9
                    mov r9, r11
    .skip_swap:

                    xor r10, r10
    .loop2_begin:  ;replace elements with "1,2,3..."
                    cmp r8, r9
                    jg .loop2_end
                    inc r10
                    mov QWORD[rdi + r8 * 8], r10
                    inc r8
                    jmp .loop2_begin
    .loop2_end:
                    ret


AsmRotateInGroups:  ;rdi - *array<int64_t>
                    movsxd rsi, esi  ;size
                    movsxd rcx, edx  ;k
                    mov rax, rsi
                    cqo
                    div rcx  ;rdx - elements in last group - 1
                    dec rax  ;rax - group count - 1

    .loop_for_groups_begin:
                    cmp rax, 0
                    jl .loop_for_groups_end

                    mov r9, QWORD[rdi]  ;buffer for first in group
                    mov r8, 1  ;element counter

        .loop_for_elements_begin:
                    cmp r8, rcx
                    je .loop_for_elements_end

                    mov r10, QWORD[rdi + r8 * 8]
                    mov QWORD[rdi + r8 * 8 - 8], r10

                    inc r8
                    jmp .loop_for_elements_begin
        .loop_for_elements_end:

                    lea rdi, [rdi + rcx * 8]  ;next group
                    mov QWORD[rdi - 8], r9

                    dec rax
                    jmp .loop_for_groups_begin
    .loop_for_groups_end:

                    cmp rdx, 0
                    je .end
                    mov r9, QWORD[rdi]  ;buffer
                    mov r8, 1  ;element counter

    .loop_for_last_group_begin:
                    cmp r8, rdx
                    je .loop_for_last_group_end

                    mov r10, QWORD[rdi + r8 * 8]
                    mov QWORD[rdi + r8 * 8 - 8], r10

                    inc r8
                    jmp .loop_for_last_group_begin
    .loop_for_last_group_end:

                    mov QWORD[rdi + rdx * 8 - 8], r9

    .end:
                    ret


AsmRemoveIfSimilar:  ;rdi - *array[64], rcx - d
                    mov r8, rdx
                    sub r8, rcx  ;x - d
                    mov r9, rdx
                    add r9, rcx  ;x + d

                    movsxd rsi, esi  ;raw array size
                    xor r10, r10  ;index in answer
                    xor r11, r11  ;index in raw
                    mov rcx, 2

    .loop_begin:
                    cmp r11, rsi
                    je .loop_end

                    mov rax, QWORD[rdi + r11 * 8]  ;current number
                    cmp rax, 0
                    jle .save_number
                    cmp rax, r8
                    jl .save_number
                    cmp rax, r9
                    jg .save_number
                    cqo
                    idiv rcx
                    imul rax, rcx
                    cmp rdx, 0
                    je .save_number

                    inc r11
                    jmp .loop_begin
        .save_number:
                    mov QWORD[rdi + r10 * 8], rax
                    inc r10
                    inc r11
                    jmp .loop_begin
    .loop_end:
                    mov rax, r10
                    ret


AsmReplaceWithGroup:  ;rdi - *array[64], rsi - *size[32], edx - k
                    movsxd rcx, edx  ;k
                    xor r8, r8
                    mov r8d, DWORD[rsi]  ;answer array size

    .loop_begin:
                    cmp DWORD[rsi], 0
                    je .loop_end

                    mov rax, QWORD[rdi]
                    cqo
                    idiv rcx
                    cmp rdx, 0
                    jne .skip
                    dec rax
        .skip:
                    xor r9, r9
                    mov r9d, DWORD[rsi]  ;index
                    dec r9
        .shift_right_begin:
                    cmp r9, 0
                    je .shift_right_end

                    lea rdx, [rdi + r9 * 8]
                    mov r10, QWORD[rdx]  ;buffer
                    mov QWORD[rdx + rax * 8], r10

                    dec r9
                    jmp .shift_right_begin
        .shift_right_end:

                    mov r9, rax
                    mov r10, QWORD[rdi]  ;value
        .copy_value_begin:
                    cmp r9, 0
                    je .copy_value_end

                    mov QWORD[rdi + r9 * 8], r10

                    dec r9
                    jmp .copy_value_begin
        .copy_value_end:

                    lea rdi, [rdi + rax * 8 + 8]
                    add r8, rax
                    dec DWORD[rsi]
                    jmp .loop_begin
    .loop_end:
                    mov DWORD[rsi], r8d
                    ret


AsmMerge:           ;rdi - const *array1[64], rsi - size1
                    ;rdx - const *array2[64], rcx - size2
                    ;r8 - *array_result[64]
                    mov r10, rsi
                    add r10, rcx
                    dec r10  ;index in array_result
                    dec rcx  ;index in array2
                    dec rsi  ;index in array1
    .loop_begin:
                    cmp r10, 0
                    jl .loop_end

                    cmp rsi, 0
                    jl .choose_from_2
                    cmp rcx, 0
                    jl .choose_from_1
                    mov r11, QWORD[rdi + rsi * 8]  ;element from 1
                    cmp r11, QWORD[rdx + rcx * 8]
                    jg .choose_from_1
                    jmp .choose_from_2
        .choose_from_1:
                    mov r9, QWORD[rdi + rsi * 8]
                    mov QWORD[r8 + r10 * 8], r9
                    dec rsi
                    dec r10
                    jmp .loop_begin
        .choose_from_2:
                    mov r9, QWORD[rdx + rcx * 8]
                    mov QWORD[r8 + r10 * 8], r9
                    dec rcx
                    dec r10
                    jmp .loop_begin
    .loop_end:
                    ret


AsmModify2D:  ;rdi - **array[64], rsi - n, rdx - m
                    lea rdi, [rdi]  ;*array[i]
                    mov r11, rsi  ;m
                    mov rsi, rdx
                    dec rsi  ;n - 1
                    mov r10, 2

    .loop_for_n_begin:
                    cmp rsi, 0
                    jl .loop_for_n_end

                    mov r8, QWORD[rdi]
;                    lea r8, [r8 + rsi * 8]  ;*array[64]
                    xor r9, r9  ;index in array[rsi]
        .loop_for_m_begin:
                    cmp r9, r11
                    je .loop_for_m_end

                    mov rax, QWORD[r8 + r9 * 8]  ;element
                    cmp rax, 0
                    jl .negative
                    jg .positive
                    inc r9
                    jmp .loop_for_m_begin
            .negative:
                    add rax, 1
                    mov QWORD[r8 + r9 * 8], rax
                    inc r9
                    jmp .loop_for_m_begin
            .positive:
                    imul rax, r10
                    mov QWORD[r8 + r9 * 8], rax
                    inc r9
                    jmp .loop_for_m_begin
        .loop_for_m_end:

                    dec rsi
                    add rdi, 8
                    jmp .loop_for_n_begin
    .loop_for_n_end:
                    ret


AsmFindSorted:  ;rdi - **array[32], esi - n, edx - m
                    movsxd rsi, esi
                    movsxd rdx, edx
                    dec rdx
                    xor rax, rax  ;answer
                    lea r9, [rdi + rdx * 8]
    .loop_m_begin:
                    cmp rdx, 0
                    jl .loop_m_end

                    mov r8, QWORD[r9]  ;*array[rdx]
                    mov r10d, DWORD[r8]  ;prev element
                    mov r11, 1  ;index in array[rdx]

        .loop_n_begin:
                    cmp r11, rsi
                    je .loop_n_end

                    cmp r10d, DWORD[r8 + r11 * 4]
                    jge .skip_row

                    mov r10d, DWORD[r8 + r11 * 4]
                    inc r11
                    jmp .loop_n_begin
        .loop_n_end:

                    add rax, rdx
        .skip_row:
                    dec rdx
                    sub r9, 8
                    jmp .loop_m_begin
    .loop_m_end:
                    ret