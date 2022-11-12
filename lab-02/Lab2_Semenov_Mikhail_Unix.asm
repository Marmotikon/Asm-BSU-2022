                    global Positivity
                    global CheckOverflow
                    global Function
                    global IsInCircle
                    global TwoIntegers
                    global CountNumbers
                    global Switch
                    global MagicMetric

                    section .data
pos_message:    db  'Yeah) It', 39, 's positive :D', 0
neg_message:    db  'Ohh.. so much negative :(', 0

case_1_text:    db  'That', 39, 's bad', 0
case_2_text:    db  'No comments.', 0
case_3_text:    db  'Not bad...', 0
case_4_text:    db  'Nice :)', 0
case_5_text:    db  'Perfecto!!!', 0
default_text:   db  'Ooops', 0
                    section .text

Positivity:
                    cmp rdi, 0
                    jg .pos
                    mov rax, neg_message
                    jmp .if_end
    .pos:           mov rax, pos_message
    .if_end:        ret

CheckOverflow:      ;rdi - x
                    ;rsi - y
                    mov rax, rdi
                    add rax, rsi
                    jz .overflow
                    jo .overflow
                    imul rax
                    jo .overflow

                    mov rax, rsi
                    imul rsi
                    jo .overflow
                    mov r8, rax     ;r8 - y^2

                    mov rax, rdi
                    imul rdi
                    jo .overflow
                    imul rax
                    jo .overflow
                    add rax, 8
                    jo .overflow
                    mov rax, 0
                    jmp .end
    .overflow:
                    mov rax, 1
    .end:
                    ret
        
Function:           ; rdi - x
                    cmp rdi, -1
                    jl .first_case
                    cmp rdi, 17
                    jle .second_case
                    jmp .third_case
    .first_case:
                    mov rax, rdi
                    imul rdi
                    shl rax, 1
                    sub rax, 3
                    jmp .end
    .second_case:
                    mov rax, rdi
                    mov r11, 3
                    imul r11
                    neg rax
                    add rax, 10
                    cmp rax, 0
                    je .third_case
                    mov r8, rax
                    mov rax, rdi
                    imul rdi
                    neg rax
                    add rax, 36
                    cqo
                    idiv r8
                    cmp rax, 0
                    jl .end
                    cmp rdx, 0
                    je .end
                    inc rax
                    jmp .end
    .third_case:
                    mov rax, rdi
                    imul rdi
                    imul rdi
                    neg rax
                    sub rax, 2
                    jmp .end
    .end:
                    ret
        
IsInCircle:         ;rdi - x
                    ;rsi - y
                    ;rdx - D
                    imul rdi, rdi
                    imul rsi, rsi
                    mov r11, rdi
                    add r11, rsi ;r11 = x^2 + y^2
                    mov rax, rdx ;rax - D
                    cqo
                    mov r8, 2
                    idiv r8
                    mov r10, rax
                    imul r10, r10
                    cmp rdx, 0
                    je .radius_integer
                    add r10, rax
    .radius_integer:
                    ; r10 = (D/2)^2
                    xor rax, rax
                    cmp r11, r10
                    jg .not_in_circle
                    mov rax, 1
    .not_in_circle:
                    ret
        
TwoIntegers:        ;rdi - x
                    ;rsi - y
                    mov rax, rdi
                    cqo
                    div rsi
                    cmp rdx, 0
                    je .yes
                    mov rax, rsi
                    cqo
                    div rdi
                    cmp rdx, 0
                    je .yes
                    mov rax, 0
                    jmp .end
    .yes:
                    mov rax, 1
    .end:
                    ret

CountNumbers:       ; rdi - a, rsi - b, rdx - c
                    mov rcx, rdx       ;rcx - c
                    ; r8 - min(a,b,c)
                    cmp rdi, rsi
                    jl .first_if_else
                    mov r8, rsi
                    jmp .first_if_end
    .first_if_else:
                    mov r8, rdi
    .first_if_end:

                    cmp r8, rcx
                    jl .second_if_end
                    mov r8, rcx
    .second_if_end:
;                    cmp rdi, rsi
;                    jg .b_or_c
;                    ; a_or_c
;                    cmp rdi, rcx
;                    jg .is_c
;                    ; is_a
;                    mov r8, rdi
;                    jmp .end_min_search
;    .b_or_c:
;                    cmp rsi, rcx
;                    jg .is_c
;                    ; is_b
;                    mov r8, rsi
;                    jmp .end_min_search
;    .is_c:
;                    mov r8, rcx
;    .end_min_search:
                    xor r9, r9
                    mov rax, rdi
                    cqo
                    idiv r8
                    and rdx, 1
                    jz .not_a
                    inc r9
    .not_a:
                    mov rax, rsi
                    cqo
                    idiv r8
                    and rdx, 1
                    jz .not_b
                    inc r9
    .not_b:
                    mov rax, rcx
                    cqo
                    idiv r8
                    and rdx, 1
                    jz .not_c
                    inc r9
    .not_c:
                    mov rax, r9
                    ret

Switch:             ;rdi - x
                    cmp rdi, 0
                    je .case_1
                    cmp rdi, 1
                    je .case_1
                    cmp rdi, 2
                    je .case_1
                    cmp rdi, 5
                    je .case_1

                    cmp rdi, 4
                    je .case_2
                    cmp rdi, 42
                    je .case_2
                    cmp rdi, 43
                    je .case_2

                    cmp rdi, 13
                    je .case_3

                    cmp rdi, -99
                    je .case_4
                    cmp rdi, -100
                    je .case_4

                    cmp rdi, 10
                    je .case_5
                    cmp rdi, 100
                    je .case_5
                    cmp rdi, 1000
                    je .case_5
                    ;default
                    mov rax, default_text
                    jmp .end_of_switch
    .case_1:
                    mov rax, case_1_text
                    jmp .end_of_switch
    .case_2:
                    mov rax, case_2_text
                    jmp .end_of_switch
    .case_3:
                    mov rax, case_3_text
                    jmp .end_of_switch
    .case_4:
                    mov rax, case_4_text
                    jmp .end_of_switch
    .case_5:
                    mov rax, case_5_text
                    jmp .end_of_switch
    .end_of_switch:
                    ret

MagicMetric:
                    mov rax, rdi
                    xor si, si
                    ;check for 8 signs
                    cmp rax, 10000000
                    jl .end
                    cmp rax, 99999999
                    jg .end
                    or si, 0x100
                    mov rdi, 10
                    ;rax - x
                    ;rdi - 10
                    ;rdx - current x sign
                    ;r8, r9, r10, r11 - 0-3 signs of x
                    ;si[1-8 bit] - how many of 1-3 conditions are true
                    ;si[9 bit] - is 4th condition true
                    ;rcx - 5th and 7th signs sum

                    xor rdx, rdx
                    idiv rdi
                    mov r8, rdx
                    xor rdx, rdx
                    idiv rdi
                    mov r9, rdx
                    xor rdx, rdx
                    idiv rdi
                    mov r10, rdx
                    xor rdx, rdx
                    idiv rdi
                    mov r11, rdx

                    ;first condition
                    cmp r8, 2
                    je .condition_1_true
                    cmp r9, 2
                    je .condition_1_true
                    cmp r10, 2
                    je .condition_1_true
                    cmp r11, 2
                    je .condition_1_true
                    jmp .condition_1_false
    .condition_1_true:
                    inc si
    .condition_1_false:

                    ;4-th sign
                    xor rdx, rdx
                    idiv rdi
                    cmp rdx, r11
                    je .skip_1
                    and si, 0xFF
    .skip_1:
                    ;5-th sign
                    xor rdx, rdx
                    idiv rdi
                    mov rcx, rdx
                    cmp rdx, r10
                    je .skip_2
                    and si, 0xFF
    .skip_2:

                    ;6th sign
                    xor rdx, rdx
                    idiv rdi
                    cmp rdx, r9
                    je .skip_3
                    and si, 0xFF
    .skip_3:
                    cmp rdx, r10
                    jne .condition_3_false
                    inc si
    .condition_3_false:

                    ;7 sign
                    xor rdx, rdx
                    idiv rdi
                    cmp rdx, r8
                    je .skip_4
                    and si, 0xFF
    .skip_4:
                    add rcx, rdx
                    cmp rcx, 5
                    jle .condition_2_false
                    inc si
    .condition_2_false:
    .end:
                    cmp si, 0x100
                    jl .condition_4_false
                    inc si
    .condition_4_false:
                    mov al, sil
                    ret
