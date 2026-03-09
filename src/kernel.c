#include <stdint.h>

extern void vga_clear();
extern void handle_key(uint8_t);
extern void irq1_handler();

static inline uint8_t inb(uint16_t p) {
    uint8_t v; __asm__ volatile ("inb %1,%0":"=a"(v):"Nd"(p)); return v;
}
static inline void outb(uint16_t p, uint8_t v) {
    __asm__ volatile ("outb %1,%0"::"Nd"(p),"a"(v));
}

void kernel_main() {
    vga_clear();
    handle_key(0); // вызовем один раз для инициализации меню

    __asm__ volatile ("sti");
    while(1) __asm__ volatile ("hlt");
}
