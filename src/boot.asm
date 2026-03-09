[BITS 16]
[ORG 0x7C00]

    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    sti

    ; Вывод приветствия
    mov si, msg
    call print_str

    ; Загрузка ядра (сектор 2, 10 секторов)
    mov ah, 0x02
    mov al, 10
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0x80
    mov bx, 0x1000
    int 0x13

    jmp 0x1000:0x0

print_str:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print_str
.done:
    ret

msg db 'MyOS v0.1', 0 0xA, 0

times 510 - ($ - db 0
dw 0xAA55
