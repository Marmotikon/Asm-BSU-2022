                    global StrLen
                    global StrComp


                    section .text
StrLen:             ;rdi - str
                    mov rcx, 2000000000
;                    mov rdx, rdi
                    mov al, 0
                    repne scasb
                    mov rax, 2000000000
                    inc rcx
                    sub rax, rcx
                    ret

StrComp:            ;rdi - str1, rsi - str2
                    mov rcx, 2000000000
                    mov al, 0
                    mov rdx, rdi
                    repne scasb
                    mov rax, 2000000000
;                    inc rcx
                    sub rax, rcx
                    mov rcx, rax

                    mov rdi, rdx
                    repe cmpsb
;                    jrcxz .skip_dec
                    je .equal
                    dec rdi
                    dec rsi
    .skip_dec:
                    mov al, BYTE[rdi]
                    cmp al, BYTE[rsi]
                    jl .less
                    jg .greater
    .equal:
                    xor rax, rax
                    ret
    .less:
                    mov rax, -1
                    ret
    .greater:
                    mov rax, 1
                    ret
