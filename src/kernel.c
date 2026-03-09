#include <stdint.h>

extern void vga_clear();
extern void draw_menu();
extern void handle_key(uint8_t sc);
extern void irq_install(int irq, void (*handler)());

void keyboard_init() {
    // stub — real impl in drivers.asm
}

void kernel_main() {
    vga_clear();
    draw_menu();

    // Enable interrupts
    __asm__ volatile ("sti");

    while (1) {
        __asm__ volatile ("hlt");
    }
}
