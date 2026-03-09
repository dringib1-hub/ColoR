[BITS 32]
global irq1_handler
extern handle_key

irq1_handler:
    pusha
    in al, 0x60
    push eax
    call handle_key
    pop eax
    mov al, 0x20
    out 0x20, al
    popa
    iret
