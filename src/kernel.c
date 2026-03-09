void _start() {
    // Загрузка GUI
    __asm__ volatile ("call 0x9000");  // gui.c

    // Загрузка CLR-файла (snake.clr)
    __asm__ volatile (
        "mov $0x02, %%ah\n\t"
        "mov $8, %%al\n\t"
        "mov $0, %%ch\n\t"
        "mov $15, %%cl\n\t"
        "mov $0, %%dh\n\t"
        "mov $0x80, %%dl\n\t"
        "mov $0x2000, %%bx\n\t"
        "int $0x13\n\t"
        "jmp 0x0000:0x2000"
        :
        :
        : "ax", "bx", "cx", "dx"
    );
}
