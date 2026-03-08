[BITS 16]
[ORG 0x7C00]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Установка текстового режима 80x25
    mov ah, 0x00
    mov al, 0x03
    int 0x10

    ; Вывод сообщения
    mov si, msg
    call print_string

    ; Загрузка ядра с сектора 2 в 0x8000
    mov ah, 0x02
    mov al, 1
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0x80
    mov bx, 0x8000
    int 0x13
    jc boot_error
    jmp 0x0000:0x8000

boot_error:
    mov si, msg_err
    call print_string
    hlt
    jmp $

print_string:
    pusha
.next:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    mov bh, 0
    mov bl, 0x07
    int 0x10
    jmp .next
.done:
    popa
    ret

msg db 'MyOS Booting...',0x0D,0x0A,0
msg_err db 'Boot failed!',0x0D,0x0A,0

times 510 - ($ - $$) db 0
dw 0xAA55
