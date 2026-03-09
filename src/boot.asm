; MyOS Bootloader — 16-bit MBR → protected mode
[BITS 16]
[ORG 0x7C00]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    sti

    ; Print 'MyOS'
    mov si, msg
    call print_string

    ; Load kernel (10 sectors from LBA 1)
    mov ah, 0x02
    mov al, 10
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0x80
    mov bx, 0x1000
    int 0x13

    ; GDT
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode

print_string:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print_string
.done:
    ret

msg db 'MyOS v0.2', 0xD, 0xA, 0

gdt_start:
    dq 0
    dw 0xFFFF, 0, 0x9A20, 0xCF
    dw 0xFFFF, 0, 0x9200, 0xCF
gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

[BITS 32]
protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000
    jmp 01000:0x0

times 510 - ($ - $$) db 0
dw 0xAA55
