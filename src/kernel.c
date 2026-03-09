#include <stdint.h>

extern void vga_clear();
extern void gui_draw_menu();
extern void gui_handle_key(uint8_t scancode);

// Прототипы из drivers.asm
void keyboard_init();
void irq_install_handler(int irq, void (*handler)());

void kernel_main() {
    vga_clear();
    gui_draw_menu();

    keyboard_init(); // Устанавливает IRQ1 → handler

    while (1) {
        __asm__ volatile ("hlt");
    }
}
