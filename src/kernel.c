void outb(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" :: "a"(val), "Nd"(port));
}

unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void draw_pixel(int x, int y, unsigned char col) {
    if (x < 0 || x >= 320 || y < 0 || y >= 200) return;
    __asm__ volatile (
        "mov $0x0C, %%ah\n\t"
        "mov %0, %%al\n\t"
        "mov %1, %%cx\n\t"
        "mov %2, %%dx\n\t"
        "mov $0x0D, %%bh\n\t"
        "int $0x10"
        :
        : "r"(col), "r"(x), "r"(y)
        : "ax", "cx", "dx", "bh"
    );
}

void draw_rect(int x, int y, int w, int h, unsigned char col) {
    for (int dy = 0; dy < h; dy++)
        for (int dx = 0; dx < w; dx++)
            draw_pixel(x + dx, y + dy, col);
}

void _start() {
    // VGA 320x200
    __asm__ volatile ("mov $0x13, %%ax; int $0x10" ::: "ax");

    // Окно
    draw_rect(50, 50, 220, 100, 0x1F); // серая рамка
    draw_rect(52, 52, 216, 96, 0x00); // чёрный фон

    // Надпись
    const char* s = "ColorOS";
    for (int i = 0; s[i]; i++) {
        draw_pixel(60 + i*8, 70, 0x0F);
    }

    // Цикл
    while (1) {
        if (inb(0x64) & 1) {
            unsigned char sc = inb(0x60);
            if (sc == 0x3B) { // F1
                // Загрузка snake.clr в 0x2000
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
        }
        __asm__ volatile ("hlt");
    }
}
