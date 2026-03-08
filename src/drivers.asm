; drivers.asm — драйверы устройств (заглушка)
; Загружается в сектор 4 (0x0C00)

[BITS 16]
[ORG 0x0C00]

drivers_start:
    ; Сохраняем регистры
    pusha
    mov ax, cs
    mov ds, ax
    mov es, ax

    ; Сообщение: "Drivers loaded"
    mov si, msg_loaded
    call print_string

    ; Инициализация клавиатуры (пример)
    call init_keyboard

    ; Возвращаем управление
    popa
    ret

; ——— Подпрограммы ———
print_string:
    pusha
.next_char:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    mov bh, 0
    mov bl, 0x07
    int 0x10
    jmp .next_char
.done:
    popa
    ret

init_keyboard:
    ; Просто сброс контроллера клавиатуры
    in al, 0x64
    test al, 2
    jnz init_keyboard
    mov al, 0xAE
    out 0x64, al
    ret

; ——— Данные ———
msg_loaded db 'Drivers loaded.', 0x0D, 0x0A, 0

; ——— Заглушка ———
times 510 - ($ - $$) db 0
dw 0xAA55
