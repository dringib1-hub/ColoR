// gui.c — простой GUI (20 строк)
// Загружается по адресу 0x9000 (сектор 3)

void outb(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" :: "a"(val), "Nd"(port));
}

void draw_pixel(int x, int y, unsigned char color) {
    __asm__ volatile (
        "mov $0x0C, %%ah\n"
        "mov %0, %%al\n"
        "mov %1, %%cx\n"
        "mov %2, %%dx\n"
        "mov $0x0D, %%bh\n"
        "int $0x10"
        :
        : "m"(color), "m"(x), "m"(y)
        : "ax", "cx", "dx", "bh"
    );
}

void draw_rect(int x, int y, int w, int h, unsigned char color) {
    for (int dy = 0; dy < h;)
        for (int dx = 0; dx < w; ++dx)
            draw_pixel(x + dx, y + dy, color);
}

void _start() {
    // Переключаемся в графический режим 320x200
    __asm__ volatile ("mov $0x13, %%ax; int $0x10" ::: "ax");

    // Рисуем рамку (синяя)
    draw_rect(10, 10, 300, 180, 0x01);

    // Выводим надпись (белый текст на чёрном фоне — через пиксели)
    for (int i = 0; i < 12; ++i)
        draw_pixel(50 + i*10, 100, 0x0F);  // 'M', 'y', 'O', 'S' — упрощённо

    // Зацикливаемся
    while (1) __asm__ volatile ("hlt");
}
