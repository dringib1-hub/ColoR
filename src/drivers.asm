[BITS 32]

extern keyboard_handler
extern vga_clear
extern vga_put_char

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

; VGA text mode (0xB8000)
vga_clear:
    pusha
    mov edi, 0xB8000
    mov ecx, 80 * 25
    mov eax, 0x0720   ; attr=07, char=20 (space)
    rep stosd
    popa
    ret

vga_put_char:
    pusha
    mov ebx, 0xB8000
    mov eax, [esp+36]   ; char
    mov edx, [esp+40]   ; attr
    mov ecx, [esp+44]   ; x
    mov esi, [esp+48]   ; y
    mov edi, esi
    mov eax, 80
    mul edi
    add eax, ecx
    shl eax, 1
    add ebx, eax
    mov [ebx], dx
    popa
    ret
