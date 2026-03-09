#include <stdint.h>

extern void vga_clear();
extern void vga_put_char(char c, uint8_t attr, int x, int y);

#define ATTR_WHITE_ON_BLACK 0x07
#define MAX_MENU_ITEMS 3

const char* menu_items[] = {
    "Start Shell",
    "Reboot",
    "Shutdown"
};

int selected = 0;

void gui_draw_menu() {
    vga_clear();
    for (int i = 0; i < MAX_MENU_ITEMS; i++) {
        uint8_t attr = (i == selected) ? 0x70 : ATTR_WHITE_ON_BLACK;
        vga_put_char('>', attr, 2, 5 + i);
        for (int j = 0; j < strlen(menu_items[i]); j++) {
            vga_put_char(menu_items[i][j], attr, 4 + j, 5 + i);
        }
    }
}

void gui_handle_key(uint8_t scancode) {
    if (scancode == 0x48) { // ↑
        selected = (selected - 1 + MAX_MENU_ITEMS) % MAX_MENU_ITEMS;
        gui_draw_menu();
    } else if (scancode == 0x50) { // ↓
        selected = (selected + 1) % MAX_MENU_ITEMS;
        gui_draw_menu();
    } else if (scancode == 0x1C) { // Enter
        if (selected == 0) {
            // запуск shell — пока просто очистка
            vga_clear();
            vga_put_char('S', 0x0F, 10, 10);
            vga_put_char('H', 0x0F, 11, 10);
            vga_put_char('E', 0x0F, 12, 10);
            vga_put_char('L', 0x0F, 13, 10);
            vga_put_char('L', 0x0F, 14, 10);
        }
    }
}
