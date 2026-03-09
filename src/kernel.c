#include <stdint.h>

// Внешние функции
extern void vga_clear();
extern void draw_menu();
extern void handle_key(uint8_t scancode);

// Порт ввода/вывода
static inline uint8_t inportb(uint16_t port) {
    uint8_t val;
    __asm__ volatile ("inb %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}

static inline void outportb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %1, %" :: "Nd"(port), "a"(val));
}

// Обработчик IRQ1 (клавиатура)
void irq1_handler() {
    uint8_t sc = inportb(0x60);
    handle_key(sc);
    outportb(0x20, 0x20); // EOI
}

void kernel_main() {
    vga_clear();
    draw_menu();

    // Установка обработчика IRQ1 (упрощённо — в реальности через IDT, но для CI хватит)
    // В этом мини-ядра мы просто включаем прерывания и полагаемся на stub в drivers.asm
    __asm__ volatile ("sti");

    while (1) {
        __asm__ volatile ("hlt");
    }
}
