[BITS 32]

extern keyboard_handler
extern vga_put_char
extern vga_clear

; IRQ1 — клавиатура
irq1:
    pusha
    in al, 0x60
    push eax
    call keyboard_handler
    pop eax
    mov al, 0x20
    out 0x20, al
    popa
    iret

; VGA — текстовый режим (0x03), буфер 0xB8000
vga_clear:
    pusha
    mov edi, 0xB8000
    mov ecx, 80 * 25
    mov eaxx0720   ; белый фон, чёрный текст, пробел
    rep stosd
    popa
    ret

vga_put_char:
    pusha
    mov edi, 0xB8000
    mov eax, [esp+36]   ; char
    mov ebx, [esp+40]   ; attr (по умолчанию 0x07)
    mov ecx, [esp+44]   ; x
    mov edx, [esp+48]   ; y
    mov esi, 80
    mul esi
    add eax, ecx
    shl eax, 1
    add edi, eax
    mov [edi], bx
    popa
    ret
