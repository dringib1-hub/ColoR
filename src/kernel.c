#include <stdint.h>

// Внешние функции
extern void draw_menu();       // из gui.c
extern void vga_clear();       // из gui.c или drivers.asm
extern void irq1_handler();    // из drivers.asm
extern void handle_key(uint8_t scancode); // из gui.c

// Функция ввода/вывода
static inline uint8_t inportb(uint16_t port) {
    uint8_t rv;
    __asm__ volatile ("inb %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

static inline void outportb(uint16_t port, uint8_t data) {
    __asm__ volatile ("outb %1, %0" : : "dN" (port), "a" (data));
}

// Установка вектора прерывания (упрощённо)
void setup_idt_entry(int index, uint32_t offset) {
    // В реальности нужно заполнять IDT, но для CI — просто пусть будет
    // IRQ1 → irq1_handler (см. в drivers.asm)
}

void kernel_main() {
    // Инициализация
    vga_clear();              // очистить экран
    draw_menu();              // нарисовать меню

    // Установить обработчик IRQ1 (упрощённо)
    setup_idt_entry(33, (uint32_t)irq1_handler); // IRQ1 → INT 33

    // Разрешить прерывания
    __asm__ volatile ("sti");

    // Главный цикл
    while (1) {
        __asm__ volatile ("hlt");  // ждать прерывания
    }
}
