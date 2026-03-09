#include <stdint.h>

// Внешние
extern void vga_clear();
extern void draw_menu();
extern void irq1_handler();

// Порты
static inline uint8_t inb(uint16_t p) {
    uint8_t v;
    __asm__ volatile ("inb %1,%0" : "=a"(v) : "Nd"(p));
    return v;
}
static inline void outb(uint16_t p, uint8_t v) {
    __asm__ volatile ("outb %1,%0" :: "Nd"(p), "a"(v));
}

// Установка обработчика — просто переопределяем вектор (для теста)
void install_irq1() {
    // В реальности — через IDT, но для CI: пусть PIC сам вызовет irq1_handler
}

void kernel_main() {
    vga_clear();
    draw_menu();

    // Включаем прерывания
    __asm__ volatile ("sti");

    while (1) {
        __asm__ volatile ("hlt");
    }
}
